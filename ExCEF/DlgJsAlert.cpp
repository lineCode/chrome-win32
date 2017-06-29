// DlgJsAlert.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ExCEF.h"
#include "DlgJsAlert.h"
#include "afxdialogex.h"


// CDlgJsAlert 대화 상자입니다.

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


// CDlgJsAlert 메시지 처리기입니다.


BOOL CDlgJsAlert::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  여기에 추가 초기화 작업을 추가합니다.

    return TRUE;  // return TRUE unless you set the focus to a control
    // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgJsAlert::SetJsAlertMsg(CString _sMsg)
{
    UpdateData(TRUE);
    m_sAlertMessage = _sMsg;
    UpdateData(FALSE);
}

void CDlgJsAlert::OnBnClickedOk()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CDialogEx::OnOK();
}
