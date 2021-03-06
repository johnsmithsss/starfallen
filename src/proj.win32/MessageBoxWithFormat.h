#pragma once
#include<windows.h>
#include<tchar.h>
#include<stdio.h>
	class MessageBoxWithFormat
	{
	public:
		void CDECL MessageBoxPrintf(TCHAR * szCaption, TCHAR * szFormat, ...);
		static MessageBoxWithFormat* getInstance() { return instance; }
	private:
		MessageBoxWithFormat() {};
		~MessageBoxWithFormat() {};
		static MessageBoxWithFormat *instance;
	};
	MessageBoxWithFormat* MessageBoxWithFormat::instance = new MessageBoxWithFormat();
	void CDECL MessageBoxWithFormat::MessageBoxPrintf(TCHAR * szCaption, TCHAR * szFormat, ...)
	{
		TCHAR szBuffer[1024];
		va_list pArgList;
		//The va_start macro(defined in STDARG.H )is usually equivalent to;
		//pArgList = (char *) &szFormat + sizeof(szFromat);

		va_start(pArgList, szFormat);

		//The last argument to wvsprintf points to the arguments

		_vsntprintf(szBuffer, sizeof(szBuffer) / sizeof(TCHAR),
			szFormat, pArgList);

		//The va_end macro just zeroes out pArgList for no good reason

		va_end(pArgList);

		MessageBoxW(NULL, szBuffer, szCaption, 0);
	}

