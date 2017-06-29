// DlgJsAlert.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ExCEF.h"
#include "DlgJsAlert.h"
#include "afxdialogex.h"


// CDlgJsAlert ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgJsAlert, CDialogEx)

CDlgJsAlert::CDlgJsAlert(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgJsAlert::IDD, pParent)
    , m_sAlertMessage(_T(""))
{

}

CDlgJsAlert::~CDlgJsAlert()
{
}

void CDlgJsAlert::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_LBL_MESSAGE, m_sAlertMessage);
}


BEGIN_MESSAGE_MAP(CDlgJsAlert, CDialogEx)
    ON_BN_CLICKED(IDOK, &CDlgJsAlert::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgJsAlert �޽��� ó�����Դϴ�.


BOOL CDlgJsAlert::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

    return TRUE;  // return TRUE unless you set the focus to a control
    // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDlgJsAlert::SetJsAlertMsg(CString _sMsg)
{
    UpdateData(TRUE);
    m_sAlertMessage = _sMsg;
    UpdateData(FALSE);
}

void CDlgJsAlert::OnBnClickedOk()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    CDialogEx::OnOK();
}
