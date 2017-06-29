
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// ExCEF.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"
#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>

namespace CPP
{
    #define LOG_HDR_SIZE    255
    #define LOG_BUFF_SIZE   2048
    static DWORD m_dwPID = ::GetCurrentProcessId();

    void DbgA(const char* _pszFunc, const int _nSrcLine, const char* _pszFormat, ...)
    {
        char szLogBuff[2048] = {0};
        va_list vArg;
        va_start(vArg, _pszFormat);
        
        int nLogLen = 0;
        SYSTEMTIME t = {0};

        ::GetLocalTime(&t);
        nLogLen = ::sprintf_s(szLogBuff, countof(szLogBuff)-1, "%04d/%02d/%02d %02d:%02d:%02d.%03d [P%ld:T%ld] [%s:%d] ", t.wYear, t.wMonth, t.wDay, 
            t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, 
            m_dwPID, ::GetCurrentThreadId(), _pszFunc, _nSrcLine);

        nLogLen += ::vsprintf_s(&szLogBuff[nLogLen], countof(szLogBuff)-nLogLen-1, _pszFormat, vArg);

        szLogBuff[nLogLen++] = '\n';
        szLogBuff[nLogLen++] = 0;

        ::OutputDebugStringA(szLogBuff);
        va_end(vArg);
    }

    void DbgW(const wchar_t* _pwszFunc, const int _nSrcLine, const wchar_t* _pwszFormat, ...)
    {
        wchar_t wszLogBuff[2048] = {0};
        va_list vArg;
        va_start(vArg, _pwszFormat);
        int nLogLen = 0;
        SYSTEMTIME t = {0};

        ::GetLocalTime(&t);
        nLogLen = ::swprintf_s(wszLogBuff, countof(wszLogBuff)-1, L"%04d/%02d/%02d %02d:%02d:%02d.%03d [P%ld:T%ld] [%s:%d] ", t.wYear, t.wMonth, t.wDay, 
            t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, 
            m_dwPID, ::GetCurrentThreadId(), _pwszFunc, _nSrcLine);

        nLogLen += ::vswprintf_s(&wszLogBuff[nLogLen], countof(wszLogBuff)-nLogLen-1, _pwszFormat, vArg);

        wszLogBuff[nLogLen++] = '\n';
        wszLogBuff[nLogLen++] = 0;

        ::OutputDebugStringW(wszLogBuff);
        va_end(vArg);
    }
}   /// end of namespace CPP
