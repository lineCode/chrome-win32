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
    // parm_size ��ŭ�� ���� �޸𸮸� �����Ѵ�.
    // ���μ����� ���μ������� �����͸� �ְ� ���� ���� heap �޸� ������ Ȱ���Ѵ�.
    char *pBuffer = (char *)::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, _sJson.length() + 0xFF);

    // ������ ���� �޸𸮿� �����ϰ��� �ϴ� �����͸� �����Ѵ�.
    // parm_size��ŭ parm_data�� ������ ������ ���� �޸��� p_buffer�� �����Ѵ�.
    if (pBuffer != NULL)
    {
        jp.m_nBrowserID = m_nOwnerBrowserID;
        jp.m_nJsonParamLen = _sJson.length();

        mFile.Write(&jp, sizeof(JsParam));
        mFile.Write(_sJson.c_str(), _sJson.length());
        mFile.SeekToBegin();

        memcpy(pBuffer, mFile.GetBuffer(), (size_t)mFile.GetLength());
    }

    // WM_COPYDATA �޽��� ������ ���� ����ü�� �ش� ������ �����Ѵ�.
    COPYDATASTRUCT tip;

    // ������ �������� ������ �����ϰԲ� �ϴ� ����� �����Ѵ�.
    tip.dwData = UM_POST_MESSAGE;
    tip.cbData = (DWORD)mFile.GetLength();

    // ������ �������� �޸𸮻� ������ġ �����Ѵ�.
    tip.lpData = pBuffer;

    // WM_COPYDATA �޽����� ����� �Ǵ� parm_wnd �����쿡 �����Ѵ�.
    // �̶� ����ȭ�� ������ ���� PostMessage()�Լ��� �ƴ� SendMessage()�Լ����� ����ؾ� �Ѵ�.
    
    if (TRUE == IsWindow(hHostApp))
    {
        ::SendMessage(hHostApp, WM_COPYDATA, NULL, (LPARAM)&tip);
        DBGA("SendMessage [%s]", _sJson.c_str());
    }

    // WM_COPYDATA�޼����� ���� �����쿡�� ó���� �� �Ǿ��ٸ�, �����޸𸮸� �����Ѵ�.
    ::HeapFree(::GetProcessHeap(), 0, pBuffer);
}


