
// ExCEFDlg.h : 헤더 파일
//

#pragma once

#include "ClientHandler.h"
#include "afxwin.h"
#include "DlgJsAlert.h"

// CExCEFDlg 대화 상자
class CExCEFDlg : public CDialogEx
{
    // 생성입니다.
public:
    CExCEFDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

    // 대화 상자 데이터입니다.
    enum { IDD = IDD_EXCEF_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
    HICON m_hIcon;
    BOOL m_bSetSafeCloseTimer;
    CDlgJsAlert m_dlgJsAlert;
    CefWindowInfo m_infoFirst;
    CefWindowInfo m_infoSecond;
    CefBrowserSettings m_BrowserSettings;
    CefRefPtr<CClienteHandler> m_Handler;

    CStatic m_lblFirst;
    CStatic m_lblSecond;

    // 생성된 메시지 맵 함수
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();

    DECLARE_MESSAGE_MAP()

public:
    void ResizeChromeWindow(int _nID, int _nWidth, int _nHeight);
    
    LRESULT OnPostMessage(WPARAM _wParam, LPARAM _lParam);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedGoNaver();
    afx_msg void OnBnClickedIsLoading();
    afx_msg void OnBnClickedSafeExit();
    afx_msg void OnBnClickedResizeBrowser();
    afx_msg void OnBnClickedReloadBrowser();
    afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};
