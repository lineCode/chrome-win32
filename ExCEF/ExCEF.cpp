
// ExCEF.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "ExCEF.h"
#include "ExCEFDlg.h"


#include "ClientHandler.h"
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"
#include "CefClientApp.h"
#include "MemFileEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "libcef.lib")
#pragma comment(lib, "libcef_dll_wrapper.lib")

#if defined (DEBUG)
#  if defined (UNICODE)
#    pragma comment(lib, "libjson-mt-unicode-debug.lib")
#  else
#    pragma comment(lib, "libjson-mt-multibyte-debug.lib")
#  endif
#else
#  if defined (UNICODE)
#    pragma comment(lib, "libjson-mt-unicode-release.lib")
#  else
#    pragma comment(lib, "libjson-mt-multibyte-release.lib")
#  endif
#endif

// CExCEFApp

BEGIN_MESSAGE_MAP(CExCEFApp, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CExCEFApp ����

CExCEFApp::CExCEFApp()
{
    // �ٽ� ���� ������ ����
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

    // TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
    // InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CExCEFApp ��ü�Դϴ�.

CExCEFApp theApp;
CefRefPtr<CCefClientApp> m_app(new CCefClientApp);

// CExCEFApp �ʱ�ȭ

void CExCEFApp::InitCEF()
{
    CefMainArgs main_args(m_hInstance);

    TCHAR tszPath[MAX_PATH] = {0};
    GetCurrentDirectory(MAX_PATH, tszPath);
    DBGW(L"Current Directory [%s]", tszPath);


    CefSettings settings;
    settings.no_sandbox = true;
    /// CEF Lib���� �����ϴ� �������� single_process�� ���� true �̴�.
    settings.single_process = false;
    settings.remote_debugging_port = 8088;
    settings.multi_threaded_message_loop = false;

    m_dwPID = ::GetCurrentProcessId();
    CefInitialize(main_args, settings, m_app.get(), nullptr);
}

void CExCEFApp::SetClassName()
{
    WNDCLASS wc;

    // Get the info for this class.
    // #32770 is the default class name for dialogs boxes.
    ::GetClassInfo(AfxGetInstanceHandle(), _T("#32770"), &wc);

    // Change the name of the class.
    wc.lpszClassName = _T("ExCEF");

    // Register this class so that MFC can use it.
    AfxRegisterClass(&wc);	
}

void Test()
{
    int nID = 777;
    std::string sName = "james";
    
    
    JsParam jp;
    CMemFileEx mFile;
    jp.m_nBrowserID = 777;
    jp.m_nJsonParamLen = sName.length();

    mFile.Write(&jp, sizeof(JsParam));
    mFile.Write(sName.c_str(), sName.length());


    void *p = mFile.GetBuffer();

    char szParam[0xFF] = {0};
    JsParam jsLoad;
    CMemFileEx mLoadFile;
    mLoadFile.Write(p, (UINT)mFile.GetLength());
    mLoadFile.SeekToBegin();
    mLoadFile.Read(&jsLoad, sizeof(JsParam));
    mLoadFile.Read(szParam, jsLoad.m_nJsonParamLen);
    //ar << nID;
    //ar.w sName.c_str();
    //ar.Close();

   
    DBGA("mFile Length [%d]", (int)mFile.GetLength());
}

BOOL CExCEFApp::InitInstance()
{
    // ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
    // ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
    // InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
    // �� �׸��� �����Ͻʽÿ�.
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    InitCEF();
    DBGA("Call InitCEF");
    CWinApp::InitInstance();
    SetClassName();
    Test();

    AfxEnableControlContainer();

    // ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
    // �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
    CShellManager *pShellManager = new CShellManager;

    // ǥ�� �ʱ�ȭ
    // �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
    // �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
    // ��ƾ�� �����ؾ� �մϴ�.
    // �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
    // TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
    // ������ �������� �����ؾ� �մϴ�.
    SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

    CExCEFDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
        //  �ڵ带 ��ġ�մϴ�.
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
        //  �ڵ带 ��ġ�մϴ�.
    }

    // ������ ���� �� �����ڸ� �����մϴ�.
    if (pShellManager != NULL)
    {
        delete pShellManager;
    }




    // ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
    // ��ȯ�մϴ�.
    return FALSE;
}

void CExCEFApp::UnInitCEF()
{
    CefShutdown();
}


int CExCEFApp::ExitInstance()
{
    // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
    UnInitCEF();
    DBGA("Call UnInitCEF");
    return CWinApp::ExitInstance();
}
