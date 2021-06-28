
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#define VERSION_INFO	_T("v 2.2")
#define PROGRAM_NAME	_T("�ϳ��������� Open API ����")

#define UM_CHILD_CLOSE	WM_USER + 100	//�ڽ� ��ȭâ ����

/***********************************
* �����ȸ ���� �ɼǰ�
***********************************/
namespace CommRecvOpt
{
	enum
	{
		TranCode		= 0, //Tr�ڵ�
		PrevNextCode	= 1, //���ӵ���Ÿ ����(0:����, 1:����, 2:����, 3:����/����)
		PrevNextKey		= 2, //������ȸŰ
		MsgCode			= 3, //�޽����ڵ�
		Msg				= 4, //�޽���
		SubMsgCode		= 5, //�ΰ��޽����ڵ�
		SubMsg			= 6, //�ΰ��޽���
		Error			= 7	 //��������
	};
}

/***********************************
 * ��� ���� �̺�Ʈ
 ***********************************/
namespace CommEvent
{
	enum
	{
		Connected = 100,		// ���� �Ϸ�
		Connecting = 101,		// ���Ͽ�����
		Closed = 102,			// ���� ���� ����
		Closing = 103,			// ���� ���� ��
		ReconnectRequest = 104,	// ������ ��û
		ConnectFail = 105,		// ���� ���� ����

		//���� ���� �޽���
		NotifyMultiLogin = 150,	// �������� �˸� �޽���
		NotifyEmergency = 151,	// ��ް��� �޽���

		//�˾��޽���
		PopUpMsg = 160
	};
}

/***********************************
* FID ������ ������ 
* !!!!!!!!! ���� �Ʒ� �ҽ��� ���� �����Ͻø� �� �˴ϴ�!!!!!!!!!!!
***********************************/
class CCommRecvData
{
public:
	CCommRecvData()
	{
		m_ptrBuf = NULL;
		m_nRow = 0;
		m_nCol = 0;
	}

	virtual ~CCommRecvData() {}

	char** m_ptrBuf;
	int m_nRow;
	int m_nCol;

public:

	int GetRowCnt() { return m_nRow; }
	int GetColCnt() { return m_nCol; }

	char* GetItem(int nRow, int nCol)
	{
		if (!m_ptrBuf) return NULL;

		if (nRow < 0 || nCol < 0)
		{
			ASSERT(FALSE);
			return NULL;
		}

		if (nRow >= m_nRow || nCol >= m_nCol)
		{
			ASSERT(FALSE);
			return NULL;
		}

		int nArrIndex = (nRow * m_nCol) + nCol;
		return m_ptrBuf[nArrIndex];
	}
};
