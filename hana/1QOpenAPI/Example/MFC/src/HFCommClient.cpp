/*----------------------------------------*
| ���α׷��� : �ϳ��������� Open API ����
| ��      �� : v 
| ����  ���� :
| ��      Ÿ :
*----------------------------------------*/

// HFCommClient.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "HFCommClient.h"
#include "HFClientSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHFCommClientApp

BEGIN_MESSAGE_MAP(CHFCommClientApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CHFCommClientApp ����

CHFCommClientApp::CHFCommClientApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CHFCommClientApp ��ü�Դϴ�.

CHFCommClientApp theApp;


// CHFCommClientApp �ʱ�ȭ

BOOL CHFCommClientApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	/*----------------------------------
	  Application ��θ� �����Ѵ�.
	 -----------------------------------*/
	CString strFileName;
	char szPath[MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(), szPath, MAX_PATH);
	*strrchr(szPath, '\\') = '\0';
	m_sAppPath = szPath;

	CHFClientSampleDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}

//*******************************************************************
// Function Name : RegisterOCX
// Function      : OCX ������Ʈ�� ���
// Param         : CString strFileName
// Return        : int 
// Create        : 
// Comment       : 
//******************************************************************
int CHFCommClientApp::RegisterOCX(CString strFileName)
{
	int iReturn = 1;
	CString szErrorMsg;
	strFileName.Replace("/", "\\");

	if (FAILED(OleInitialize(NULL)))
	{
		AfxMessageBox(_T("DLLRegister OleInitialize ����"), MB_TOPMOST);
		return 1;
	}

	SetErrorMode(SEM_FAILCRITICALERRORS);

	HINSTANCE hLib = LoadLibraryEx(strFileName, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

	if (hLib == NULL)
	{
		szErrorMsg.Format(_T("File Name=%s, GetLastError() NO = 0x%08lx\n"), strFileName, GetLastError());
		AfxMessageBox(szErrorMsg, MB_TOPMOST);
		iReturn = 0;
		goto CleanupOle;
	}

	HRESULT(STDAPICALLTYPE * lpDllEntryPoint)(void);

	// Find the entry point.
	(FARPROC&)lpDllEntryPoint = GetProcAddress(hLib, _T("DllRegisterServer"));
	if (lpDllEntryPoint == NULL)
	{
		TCHAR szExt[_MAX_EXT];
		_tsplitpath_s(strFileName, NULL, sizeof(NULL), NULL, sizeof(NULL), NULL, sizeof(NULL), szExt, sizeof(szExt));

		if ((_stricmp(szExt, ".dll") != 0) && (_stricmp(szExt, ".ocx") != 0))
		{
			szErrorMsg.Format("File Name=%s, GetProcAddress Fail\n", strFileName);
			AfxMessageBox(szErrorMsg, MB_TOPMOST);
		}

		iReturn = 0;
		goto CleanupLibrary;
	}

	if (FAILED((*lpDllEntryPoint)()))
	{
		szErrorMsg.Format("File Name=%s, lpDllEntryPoint Fail\n", strFileName);
		AfxMessageBox(szErrorMsg, MB_TOPMOST);
		iReturn = 0;
		goto CleanupLibrary;
	}

CleanupLibrary:
	FreeLibrary(hLib);

CleanupOle:
	OleUninitialize();

	return iReturn;
}