#pragma once

#include "resource.h"
// CDlgJsAlert 대화 상자입니다.

class CDlgJsAlert : public CDialogEx
{
    DECLARE_DYNAMIC(CDlgJsAlert)

public:
    CDlgJsAlert(CWnd* pParent = NULL);   // 표준 생성자입니다.
    virtual ~CDlgJsAlert();

    // 대화 상자 데이터입니다.
    enum { IDD = IDD_JS_ALERT };

public:
    void SetJsAlertMsg(CString _sMsg);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CString m_sAlertMessage;
    afx_msg void OnBnClickedOk();
};
