
// ExCEFDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ExCEF.h"
#include "ExCEFDlg.h"
#include "afxdialogex.h"
#include "include/cef_app.h"
#include "json.h"
#include "MemFileEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // ��ȭ ���� �������Դϴ�.
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

    // �����Դϴ�.
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CExCEFDlg ��ȭ ����
#define TMR_STOP_LOAD                   10000
#define TMR_DESTORY_CHROME_WINDOW       10001
#define TMR_POST_WM_CLOSE               10002

CExCEFDlg::CExCEFDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CExCEFDlg::IDD, pParent)
{
    m_bSetSafeCloseTimer = FALSE;
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExCEFDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LBL_FIRST, m_lblFirst);
    DDX_Control(pDX, IDC_LBL_SECOND, m_lblSecond);
}

BEGIN_MESSAGE_MAP(CExCEFDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
    ON_MESSAGE(UM_POST_MESSAGE, OnPostMessage)
    ON_BN_CLICKED(IDC_GO_NAVER, &CExCEFDlg::OnBnClickedGoNaver)
    ON_BN_CLICKED(IDC_IS_LOADING, &CExCEFDlg::OnBnClickedIsLoading)
    ON_BN_CLICKED(IDC_SAFE_EXIT, &CExCEFDlg::OnBnClickedSafeExit)
    ON_BN_CLICKED(IDC_RESIZE_BROWSER, &CExCEFDlg::OnBnClickedResizeBrowser)
    ON_BN_CLICKED(IDC_RELOAD_BROWSER, &CExCEFDlg::OnBnClickedReloadBrowser)
    ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CExCEFDlg �޽��� ó����

BOOL CExCEFDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

    // IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
    //  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    // TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
    m_Handler = new CClienteHandler();
    m_Handler->SetOwner(this);

    RECT rectFirst, rectSecond;

    m_lblFirst.GetClientRect(&rectFirst);
    m_lblSecond.GetClientRect(&rectSecond);

    m_lblFirst.SetWindowTextW(L"I am first chrome window");
    m_lblSecond.SetWindowTextW(L"I am second chrome window");

    m_infoFirst.SetAsChild(m_lblFirst.m_hWnd, rectFirst);
    m_infoSecond.SetAsChild(m_lblSecond.m_hWnd, rectSecond);

    m_BrowserSettings.web_security = STATE_DISABLED;

    //m_Handler->CreateBrowser(info, browserSettings, CefString(_T("http://www.google.co.kr")));

    // Create the first browser window.
    std::string sFirstUrl = "http://www.daum.net";
    std::string sSecondUrl = "http://www.naver.com";

    sFirstUrl = "C:\\Spoqa\\ExWin32\\ExCEF\\main.html";

    CefBrowserHost::CreateBrowser(m_infoFirst, m_Handler.get(), sFirstUrl, m_BrowserSettings, NULL);
    CefBrowserHost::CreateBrowser(m_infoSecond, m_Handler.get(), sSecondUrl, m_BrowserSettings, NULL);

    WCHAR wszCurDir[MAX_PATH] = {0};
    GetCurrentDirectory(MAX_PATH, wszCurDir);
    GetDlgItem(IDC_TXT_CUR_DIR)->SetWindowText(wszCurDir);


    m_dlgJsAlert.Create(IDD_JS_ALERT, this);

    CString sCaption;
    sCaption.Format(_T("ExCEF PID : %d"), (int)::GetCurrentProcessId());
    SetWindowText(sCaption);

    return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CExCEFDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        if ((nID & 0xFFF0) == SC_CLOSE)
        {
            OnBnClickedSafeExit();
            return;
        }

        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CExCEFDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // �������� �׸��ϴ�.
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CExCEFDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

BOOL CExCEFDlg::PreTranslateMessage(MSG* pMsg)
{
    if (FALSE == ::IsWindow(m_lblFirst.m_hWnd) &&
        FALSE == ::IsWindow(m_lblSecond.m_hWnd))
    {

    }
    else
    {
        DBGA("Start CefRunMessageLoop");
        CefRunMessageLoop();
        DBGA("Finish CefRunMessageLoop");
        return TRUE;
    }

    return CDialogEx::PreTranslateMessage(pMsg);
}


void CExCEFDlg::OnTimer(UINT_PTR nIDEvent)
{
    switch(nIDEvent)
    {
    case TMR_STOP_LOAD:
        m_Handler->StopLoad();
        DBGA("StopLoad");
        KillTimer(nIDEvent);
        break;
    case TMR_DESTORY_CHROME_WINDOW:

        if (false == m_Handler->IsLoading())
        {
            m_lblFirst.DestroyWindow();
            m_lblSecond.DestroyWindow();
            DBGA("Destory Chrome Window");
            KillTimer(nIDEvent);
        }
        else
        {
            DBGA("Skip Destory Chrome Window");
        }
        
        break;
    case TMR_POST_WM_CLOSE:
        if (m_Handler->GetQuitMessageLoopTime() > 0)
        {
            DBGA("Quit Message Loop Elapsed Time [%I64d]", (time(0) - m_Handler->GetQuitMessageLoopTime()));
            PostMessage(WM_CLOSE);
            KillTimer(nIDEvent);
        }
        else
        {
            DBGA("Skip Post WM_CLOSE");
        }
        break;
    }

    CDialogEx::OnTimer(nIDEvent);
}

void CExCEFDlg::OnBnClickedGoNaver()
{
    CefRefPtr<CefBrowser> firstBrowser = m_Handler->GetBrowser(1);
    CefRefPtr<CefBrowser> secondBrowser = m_Handler->GetBrowser(2);

    firstBrowser->GetMainFrame()->LoadURL(CefString("http://www.naver.com"));
    secondBrowser->GetMainFrame()->LoadURL(CefString("http://www.naver.com"));
}

void CExCEFDlg::OnBnClickedIsLoading()
{
    m_Handler->IsLoading();
}

void CExCEFDlg::OnBnClickedSafeExit()
{
    /// ũ�ҿ��� �ε����� ���ҽ��� �����ϰ�,
    SetTimer(TMR_STOP_LOAD, 10, NULL);

    /// �ش� ���ҽ� �ε� �۾��� ������ �ǰ�����
    /// Host Windows�� Destory �ϰ�
    SetTimer(TMR_DESTORY_CHROME_WINDOW, 100, NULL);
    
    m_Handler->CloseAllJsAlertDialog();

    /// Chrome Message Loop�� Quit �ǰ� �� ����,
    /// ��μ� WM_CLOSE�� ���Ḧ �ؾ�����
    /// ����ϰ� ���ᰡ �����ϴ�.
    SetTimer(TMR_POST_WM_CLOSE, 100, NULL);
}

void CExCEFDlg::ResizeChromeWindow(int _nID, int _nWidth, int _nHeight)
{
    CRect rtHost;
    HWND hHost;

    if (_nID == 1)
    {
        hHost = m_lblFirst.GetSafeHwnd();
    }
    else if (_nID == 2)
    {
        hHost = m_lblSecond.GetSafeHwnd();
    }

    ::GetWindowRect(hHost, rtHost);
    ScreenToClient(rtHost);

    rtHost.right = rtHost.left + _nWidth;
    rtHost.bottom =rtHost.top + _nHeight;


    CefRefPtr<CefBrowser> pBrowser = m_Handler->GetBrowser(_nID);

    HWND hChrome = pBrowser->GetHost()->GetWindowHandle();
    ::MoveWindow(hHost, rtHost.left, rtHost.top, rtHost.Width(), rtHost.Height(), TRUE);
    ::MoveWindow(hChrome, 0, 0, rtHost.Width(), rtHost.Height(), TRUE);
}

void CExCEFDlg::OnBnClickedResizeBrowser()
{
    ResizeChromeWindow(1, 300, 300);
}

void CExCEFDlg::OnBnClickedReloadBrowser()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    CefRefPtr<CefBrowser> pBrowser = m_Handler->GetBrowser(1);
    pBrowser->Reload();
}

LRESULT CExCEFDlg::OnPostMessage(WPARAM _wParam, LPARAM _lParam)
{
    DBGA("wParam [%d] lParam [%d]", _wParam, _lParam);
    return 0L;
}

BOOL CExCEFDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
    std::string sJson, sMessage;
    Json::Value root;
    Json::Reader reader;
    CMemFileEx mFile;
    JsParam js;
    char *pJsonParam = NULL;

    switch (pCopyDataStruct->dwData)
    {
    case UM_POST_MESSAGE:

        mFile.Write(pCopyDataStruct->lpData, pCopyDataStruct->cbData);
        mFile.SeekToBegin();
        mFile.Read(&js, sizeof(JsParam));
        pJsonParam = (char*)_malloca(js.m_nJsonParamLen+32);
        mFile.Read(pJsonParam, js.m_nJsonParamLen);
        pJsonParam[js.m_nJsonParamLen] = 0;
        sJson = pJsonParam;
        DBGA("Browser ID [%d] Recv [%s]", js.m_nBrowserID, sJson.c_str());
        
        if (false == reader.parse(sJson, root))
        {
            DBGW(L"Json parse Failed");
            return FALSE;
        }
        
        sMessage = root.get("message", "").asString();
        if (sMessage == "UM_RESIZE_CHROME")
        {
            int nBrowserID = js.m_nBrowserID;
            int nWidth = root.get("width", 0).asUInt();
            int nHeight = root.get("height", 0).asUInt();
            ResizeChromeWindow(nBrowserID, nWidth, nHeight);
            DBGA("Resize chrome window browserid [%d] width [%d] height [%d]", nBrowserID, nWidth, nHeight);
        }


        break;
    default:
        break;
    }

    return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
