/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.plugin;

import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Hashtable;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;

public class IAPAlipay implements InterfaceIAP {

	private static final String LOG_TAG = "IAPAlipay";
	private static Activity mContext = null;
	private static boolean bDebug = false;
	private static Handler mHandler = null;
	private static IAPAlipay mAdapter = null;

	protected static void LogE(String msg, Exception e) {
		Log.e(LOG_TAG, msg, e);
		e.printStackTrace();
	}

	protected static void LogD(String msg) {
		if (bDebug) {
			Log.d(LOG_TAG, msg);
		}
	}

	public IAPAlipay(Context context) {
		mContext = (Activity) context;
		mAdapter = this;

		PluginWrapper.runOnMainThread(new Runnable() {

			@Override
			public void run() {
				initUIHandle();
			}
		});
	}

	@Override
	public void configDeveloperInfo(Hashtable<String, String> cpInfo) {
		LogD("initDeveloperInfo invoked " + cpInfo.toString());
		try {
			PartnerConfig.PARTNER = cpInfo.get("AlipayPartner");
			PartnerConfig.SELLER = cpInfo.get("AlipaySeller");
			PartnerConfig.RSA_PRIVATE = cpInfo.get("AlipayRsaPrivate");
			PartnerConfig.RSA_ALIPAY_PUBLIC = cpInfo.get("AlipayPublic");
			PartnerConfig.ALIPAY_PLUGIN_NAME = cpInfo.get("AlipayPluginName");

			strPayAccount = cpInfo.get("AlipayRoyPayAccount");
			strReceiveAccount = cpInfo.get("AlipayRoyReceiveAccount");
			fPayPercent = ((cpInfo.get("AlipayRoyPercent") == null) ? 0.0f : Float.parseFloat(cpInfo.get("AlipayRoyPercent")));
			strRoyTip = cpInfo.get("AlipayRoyTip");
			strNotifyUrl = ((null == cpInfo.get("AlipayNotifyUrl")) ? "" : cpInfo.get("AlipayNotifyUrl"));
		} catch (Exception e) {
			LogE("Developer info is wrong!", e);
		}
	}

	@Override
	public void payForProduct(Hashtable<String, String> info) {
		LogD("payForProduct invoked " + info.toString());
		if (! networkReachable()) {
			payResult(IAPWrapper.PAYRESULT_FAIL, "???????????????");
			return;
		}

		final Hashtable<String, String> productInfo = info;
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				MobileSecurePayHelper mspHelper = new MobileSecurePayHelper(mContext);
				boolean bInstalled = mspHelper.detectMobile_sp();
				if (! bInstalled) {
					payResult(IAPWrapper.PAYRESULT_FAIL, "????????????????????????");
					return;
				}

				// start pay for this order.
				// ????????????????????????????????????
				try {
					// prepare the order info.
					// ??????????????????
					String orderInfo = getOrderInfo(productInfo);
					// ???????????????????????????????????????????????????
					String signType = getSignType();
					String strsign = sign(signType, orderInfo);
					// ?????????????????????
					strsign = URLEncoder.encode(strsign);
					// ???????????????
					String info = orderInfo + "&sign=" + "\"" + strsign + "\"" + "&" + getSignType();
					LogD("pay info : " + info);
					// start the pay.
					// ??????pay??????????????????
					MobileSecurePayer msp = new MobileSecurePayer();
					boolean bRet = msp.pay(info, mHandler, AlixId.RQF_PAY, mContext);

					if (bRet) {
						// show the progress bar to indicate that we have started
						// paying.
						// ?????????????????????????????????
						closeProgress();
						mProgress = BaseHelper.showProgress(mContext, null, "????????????", false, true);
					} else {
						payResult(IAPWrapper.PAYRESULT_FAIL, "????????????");
						return;
					}
				} catch (Exception ex) {
					LogE("Remote call failed", ex);
					payResult(IAPWrapper.PAYRESULT_FAIL, "remote call failed");
					return;
				}
			}
		});
	}

	@Override
	public void setDebugMode(boolean debug) {
		bDebug = debug;
	}

	@Override
	public String getSDKVersion() {
		return "Unknown version";
	}

	static class AlixOnCancelListener implements DialogInterface.OnCancelListener {
		Activity mcontext;
		AlixOnCancelListener(Activity context) {
			mcontext = context;
		}

		public void onCancel(DialogInterface dialog) {
			mcontext.onKeyDown(KeyEvent.KEYCODE_BACK, null);
		}
	}

	private static void initUIHandle() {
		//
		// the handler use to receive the pay result.
		// ?????????????????????????????????????????????????????????
		mHandler = new Handler() {
			public void handleMessage(Message msg) {
				try {
					String strRet = (String) msg.obj;
					LogD("handle msg : " + msg.toString());

					switch (msg.what) {
					case AlixId.RQF_PAY: {
						LogD("msg.what is RQF_PAY");
						mAdapter.closeProgress();

						// ????????????????????????
						try {
							// ??????????????????????????????????????????????????????
							String memo = "memo=";
							int imemoStart = strRet.indexOf("memo=");
							imemoStart += memo.length();
							int imemoEnd = strRet.indexOf(";result=");
							memo = strRet.substring(imemoStart, imemoEnd);
							// ?????????????????????
							ResultChecker resultChecker = new ResultChecker(strRet);

							int retVal = resultChecker.checkSign();
							// ????????????????????????????????????
							if (retVal == ResultChecker.RESULT_CHECK_SIGN_FAILED) {
								payResult(IAPWrapper.PAYRESULT_FAIL, "??????????????????");
							} else if (retVal == ResultChecker.RESULT_CHECK_SIGN_SUCCEED && resultChecker.isPayOk()) {
								payResult(IAPWrapper.PAYRESULT_SUCCESS, "????????????");
							} else {
								payResult(IAPWrapper.PAYRESULT_FAIL, "????????????");
							}
						} catch (Exception e) {
							e.printStackTrace();
							payResult(IAPWrapper.PAYRESULT_FAIL, "??????????????????");
						}
					}
						break;
					default:
						mAdapter.closeProgress();
						payResult(IAPWrapper.PAYRESULT_FAIL, "????????????");
						break;
					}

					super.handleMessage(msg);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		};
	}
	/**
	 * get the selected order info for pay. ????????????????????????
	 * 
	 * @param position
	 *            ???????????????????????????
	 * @return
	 */
	private static String strPayAccount = "";
	private static String strReceiveAccount = "";
	private static float fPayPercent = 0.0f;
	private static String strRoyTip = "";
	private static String strNotifyUrl = "";
	private String getOrderInfo(Hashtable<String, String> info) {
		String strRet = null;
		try {
			float price = Float.parseFloat(info.get("productPrice"));//IAPProducts.getProductPrice(productID);
			String productName = info.get("productName");
			String productDesc = info.get("productDesc");
			String royParam = "";
			if (fPayPercent > 0 ) {
				float royValue = fPayPercent * price;
				royParam = strPayAccount + "^" + strReceiveAccount + "^" + royValue + "^"+ strRoyTip;
				royParam = "&royalty_parameters=\""+ royParam + "\"" + "&royalty_type=\"10" + "\"";
			}

			strRet = "partner=\"" + PartnerConfig.PARTNER + "\""
						+ "&seller=\"" + PartnerConfig.SELLER + "\""
						+ "&out_trade_no=\"" + getOutTradeNo() + "\""
						+ "&subject=\"" + productName + "\""
						+ "&body=\"" + productDesc + "\""
						+ "&total_fee=\"" + price + "\""
						+ "&notify_url=\"" + strNotifyUrl + "\""
						+ royParam;
		} catch (Exception e) {
			LogE("Product info parse error", e);
		}

		LogD("order info : " + strRet);
		return strRet;
	}

	/**
	 * get the out_trade_no for an order.
	 * ?????????????????????
	 * 
	 * @return
	 */
	String getOutTradeNo() {
		SimpleDateFormat format = new SimpleDateFormat("yyyyMMddHHmmss");
		Date date = new Date();
		String strKey = format.format(date);

		java.util.Random r = new java.util.Random();
		strKey = strKey + r.nextInt(10000);
		return strKey;
	}

	//
	//
	/**
	 *  sign the order info.
	 *  ???????????????????????????
	 *  
	 * @param signType	???????????? 
	 * @param content		?????????????????????
	 * @return
	 */
	private String sign(String signType, String content) {
		LogD("sign params :");
		LogD("type : " + signType + ", content : " + content + ", private : " + PartnerConfig.RSA_PRIVATE);
		return Rsa.sign(content, PartnerConfig.RSA_PRIVATE);
	}

	/**
	 * get the sign type we use.
	 * ??????????????????
	 * 
	 * @return
	 */
	private String getSignType() {
		String getSignType = "sign_type=" + "\"" + "RSA" + "\"";
		return getSignType;
	}
	
	private ProgressDialog mProgress = null;
	void closeProgress() {
		try {
			if (mProgress != null) {
				mProgress.dismiss();
				mProgress = null;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private boolean networkReachable() {
		boolean bRet = false;
		try {
			ConnectivityManager conn = (ConnectivityManager)mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
			NetworkInfo netInfo = conn.getActiveNetworkInfo();
			bRet = (null == netInfo) ? false : netInfo.isAvailable();
		} catch (Exception e) {
			LogE("Fail to check network status", e);
		}
		LogD("NetWork reachable : " + bRet);
		return bRet;
	}

	private static void payResult(int ret, String msg) {
		IAPWrapper.onPayResult(mAdapter, ret, msg);
		LogD("Alipay result : " + ret + " msg : " + msg);
	}

	@Override
	public String getPluginVersion() {
		return "0.2.0";
	}
}
