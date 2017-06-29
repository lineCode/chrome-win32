#include "StdAfx.h"
#include "MyV8Handler.h"
#include "ExCEF.h"
#include "ExCEFDlg.h"
#include "json.h"
#include "MemFileEx.h"
#include "include/wrapper/cef_helpers.h"

extern CExCEFApp theApp;

MyV8Handler::MyV8Handler(void)
{
}


MyV8Handler::~MyV8Handler(void)
{
}

void MyV8Handler::SetOwnerBrowserID(int _nOwnerID)
{
    m_nOwnerBrowserID = _nOwnerID;
}

bool MyV8Handler::Execute(const CefString& name,
    CefRefPtr<CefV8Value> object,
    const CefV8ValueList& arguments,
    CefRefPtr<CefV8Value>& retval,
    CefString& exception)
{
    CefRefPtr<CefV8Value> v;
    std::string sJson, sMethodName;

    if (true == name.empty())
    {
        DBGA("JavaScript Name Empty!");
        return false;
    }

    sMethodName = name.ToString();
    DBGA("%s CALL, BrowserID [%d] Main PID [%d]", sMethodName.c_str(), m_nOwnerBrowserID, (int)theApp.m_dwPID);

    v = 0 < arguments.size() ? arguments.at(0) : NULL;
    
    if (v != NULL && v->IsNull() == false)
    {
        CefString sArgVal = v->GetStringValue();
        sJson = sArgVal.ToString();
    }
    
    if (name == "myfunc") 
    {
        // Return my string value.
        retval = CefV8Value::CreateString("My Value From Windows!" + sJson);
        return true;
    }
    else if (name == "PostMessage")
    {
        OnPostMessage(sJson);
        return true;
    }

    // Function does not exist.
    return false;
}

void MyV8Handler::OnPostMessage(const std::string& _sJson)
{
    HWND hHostApp = ::FindWindow(_T("ExCEF"), NULL);
    if (NULL == hHostApp)
    {
        DBGA("Can't find ExCEF");
        return;
    }

    JsParam jp;
    CMemFileEx mFile;
    // parm_size 만큼의 동적 메모리를 생성한다.
    // 프로세스와 프로세스간에 데이터를 주고 받을 때는 heap 메모리 영역에 활당한다.
    char *pBuffer = (char *)::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, _sJson.length() + 0xFF);

    // 생성된 동적 메모리에 전송하고자 하는 데이터를 복사한다.
    // parm_size만큼 parm_data의 내용을 생성된 동적 메모리인 p_buffer에 복사한다.
    if (pBuffer != NULL)
    {
        jp.m_nBrowserID = m_nOwnerBrowserID;
        jp.m_nJsonParamLen = _sJson.length();

        mFile.Write(&jp, sizeof(JsParam));
        mFile.Write(_sJson.c_str(), _sJson.length());
        mFile.SeekToBegin();

        memcpy(pBuffer, mFile.GetBuffer(), (size_t)mFile.GetLength());
    }

    // WM_COPYDATA 메시지 정보를 위한 구조체에 해당 정보를 설정한다.
    COPYDATASTRUCT tip;

    // 보내는 데이터의 종류를 구별하게끔 하는 헤더를 저장한다.
    tip.dwData = UM_POST_MESSAGE;
    tip.cbData = (DWORD)mFile.GetLength();

    // 보내는 데이터의 메모리상 시작위치 저장한다.
    tip.lpData = pBuffer;

    // WM_COPYDATA 메시지를 대상이 되는 parm_wnd 윈도우에 전송한다.
    // 이때 동기화의 문제로 인해 PostMessage()함수가 아닌 SendMessage()함수만을 사용해야 한다.
    
    if (TRUE == IsWindow(hHostApp))
    {
        ::SendMessage(hHostApp, WM_COPYDATA, NULL, (LPARAM)&tip);
        DBGA("SendMessage [%s]", _sJson.c_str());
    }

    // WM_COPYDATA메세지를 받은 윈도우에서 처리가 다 되었다면, 동적메모리를 해제한다.
    ::HeapFree(::GetProcessHeap(), 0, pBuffer);
}


