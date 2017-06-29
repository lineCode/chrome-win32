
// ExCEF.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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


// CExCEFApp 생성

CExCEFApp::CExCEFApp()
{
    // 다시 시작 관리자 지원
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

    // TODO: 여기에 생성 코드를 추가합니다.
    // InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CExCEFApp 개체입니다.

CExCEFApp theApp;
CefRefPtr<CCefClientApp> m_app(new CCefClientApp);

// CExCEFApp 초기화

void CExCEFApp::InitCEF()
{
    CefMainArgs main_args(m_hInstance);

    TCHAR tszPath[MAX_PATH] = {0};
    GetCurrentDirectory(MAX_PATH, tszPath);
    DBGW(L"Current Directory [%s]", tszPath);


    CefSettings settings;
    settings.no_sandbox = true;
    /// CEF Lib에서 권장하는 설정값은 single_process의 값이 true 이다.
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
    // 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
    // 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
    // InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
    // 이 항목을 설정하십시오.
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    InitCEF();
    DBGA("Call InitCEF");
    CWinApp::InitInstance();
    SetClassName();
    Test();

    AfxEnableControlContainer();

    // 대화 상자에 셸 트리 뷰 또는
    // 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
    CShellManager *pShellManager = new CShellManager;

    // 표준 초기화
    // 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
    // 아래에서 필요 없는 특정 초기화
    // 루틴을 제거해야 합니다.
    // 해당 설정이 저장된 레지스트리 키를 변경하십시오.
    // TODO: 이 문자열을 회사 또는 조직의 이름과 같은
    // 적절한 내용으로 수정해야 합니다.
    SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

    CExCEFDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
        //  코드를 배치합니다.
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
        //  코드를 배치합니다.
    }

    // 위에서 만든 셸 관리자를 삭제합니다.
    if (pShellManager != NULL)
    {
        delete pShellManager;
    }




    // 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
    // 반환합니다.
    return FALSE;
}

void CExCEFApp::UnInitCEF()
{
    CefShutdown();
}


int CExCEFApp::ExitInstance()
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    UnInitCEF();
    DBGA("Call UnInitCEF");
    return CWinApp::ExitInstance();
}
