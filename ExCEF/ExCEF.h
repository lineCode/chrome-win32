
// ExCEF.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CExCEFApp:
// �� Ŭ������ ������ ���ؼ��� ExCEF.cpp�� �����Ͻʽÿ�.
//

class CExCEFApp : public CWinApp
{
public:
    CExCEFApp();

    // �������Դϴ�.
public:
    void InitCEF();
    void UnInitCEF();
    virtual BOOL InitInstance();

    // �����Դϴ�.

    DECLARE_MESSAGE_MAP()
    virtual int ExitInstance();

    void SetClassName();

public:
    DWORD m_dwPID;
};

extern CExCEFApp theApp;