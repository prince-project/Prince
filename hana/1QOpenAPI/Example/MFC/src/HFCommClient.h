/*----------------------------------------*
| ���α׷��� : �ϳ��������� Open API ����
| ��      �� : v 
| ����  ���� :
| ��      Ÿ :
*----------------------------------------*/

// HFCommClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CHFCommClientApp:
// �� Ŭ������ ������ ���ؼ��� HFCommClient.cpp�� �����Ͻʽÿ�.
//

class CHFCommClientApp : public CWinAppEx
{
public:
	CHFCommClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	CString m_sAppPath;
	int RegisterOCX(CString strFileName);

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CHFCommClientApp theApp;