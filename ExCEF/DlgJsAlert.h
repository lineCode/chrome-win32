#pragma once

#include "resource.h"
// CDlgJsAlert ��ȭ �����Դϴ�.

class CDlgJsAlert : public CDialogEx
{
    DECLARE_DYNAMIC(CDlgJsAlert)

public:
    CDlgJsAlert(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
    virtual ~CDlgJsAlert();

    // ��ȭ ���� �������Դϴ�.
    enum { IDD = IDD_JS_ALERT };

public:
    void SetJsAlertMsg(CString _sMsg);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CString m_sAlertMessage;
    afx_msg void OnBnClickedOk();
};
