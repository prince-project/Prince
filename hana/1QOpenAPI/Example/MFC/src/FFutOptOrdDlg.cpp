/*----------------------------------------*
| ���α׷��� : �ϳ��������� Open API ����
| ��      �� : v 
| ����  ���� :
| ��      Ÿ :
*----------------------------------------*/
// IndexFutSiseDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "HFCommClient.h"
#include "FFutOptOrdDlg.h"

#define ID_SECOND_TIMER		100	//1�� ���� Ÿ�̸�

#define SELL_BK_COLOR		RGB(206, 232, 255)	//�ŵ� ����
#define BUY_BK_COLOR		RGB(251, 221, 255)	//�ż� ����

//��� ����ü ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern void NumericString(CString& strValue, BOOL bNotDisplayZero = FALSE);

static char* g_szPriceCond[] = { "1", "2", "3"}; //1:������, 2:���尡, 3:STOPMARKET

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

// CFFutOptOrdDlg ��ȭ ����
CFFutOptOrdDlg::CFFutOptOrdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFFutOptOrdDlg::IDD, pParent)
{
	m_bCommConnect		= FALSE;

	m_nRqIdAccNoList		= 0;	//������ȸ Request ID
	m_nRqIdFDemoAccNoList	= 0;	//�ؿܸ��� ������ȸ Request ID

	m_nRqIdSellOrd			= 0;	//�ŵ��ֹ� Request ID
	m_nRqIdBuyOrd			= 0;	//�ż��ֹ� Request ID
	m_nRqIdChangeOrd		= 0;	//�����ֹ� Request ID
	m_nRqIdCancelOrd		= 0;	//����ֹ� Request ID

	m_nRqIdNonExecList		= 0;		//��ü�᳻�� Request ID
	m_nRqIdExecList			= 0;	//�ֹ�ü�᳻�� Request ID
	m_nRqIdDepositList		= 0;	//�����ݳ��� Request ID

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_nSeverType			= 0;	//0-����, 1-��������, 2-�ؿܹ���

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFFutOptOrdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, m_editUserID);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDC_EDIT_AUTH_PWD, m_editAuthPwd);
	DDX_Text(pDX, IDC_EDIT_ID, m_strLoginID);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strLoginPwd);
	DDX_Text(pDX, IDC_EDIT_AUTH_PWD, m_strCertPwd);
	DDX_Control(pDX, IDC_LIST_ORD, m_listExec);
	DDX_Control(pDX, IDC_LIST_ACCNO, m_listAccNo);
	DDX_Control(pDX, IDC_LIST_DEPOSIT, m_listDeposit);
	DDX_Control(pDX, IDC_LIST_NON_EXE, m_listNonExec);
	DDX_Control(pDX, IDC_LIST_BALANCE, m_listBalance);
	DDX_Control(pDX, IDC_CMB_ORD_TYPE, m_cmdOrdType);
	DDX_Control(pDX, IDC_LIST_REAL, m_listReal);
	DDX_Control(pDX, IDC_DATETIME1, m_dateTime1);
}

BEGIN_MESSAGE_MAP(CFFutOptOrdDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_LOGIN, &CFFutOptOrdDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_LOGOUT, &CFFutOptOrdDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDOK, &CFFutOptOrdDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELL, &CFFutOptOrdDlg::OnBnClickedBtnSell)
	ON_BN_CLICKED(IDC_BTN_BUY, &CFFutOptOrdDlg::OnBnClickedBtnBuy)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CFFutOptOrdDlg::OnBnClickedBtnChange)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CFFutOptOrdDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST, &CFFutOptOrdDlg::OnBnClickedBtnReqExecList)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST_NEXT, &CFFutOptOrdDlg::OnBnClickedBtnReqExecListNext)
	ON_BN_CLICKED(IDC_BTN_REQ_ACCNO, &CFFutOptOrdDlg::OnBnClickedBtnReqAccno)
	ON_BN_CLICKED(IDC_BTN_REQ_DEPOSIT, &CFFutOptOrdDlg::OnBnClickedBtnReqDeposit)
	ON_BN_CLICKED(IDC_BTN_REQ_DEPOSIT_NEXT, &CFFutOptOrdDlg::OnBnClickedBtnReqDepositNext)
	ON_BN_CLICKED(IDC_BTN_REQ_NON_EXEC_LIST, &CFFutOptOrdDlg::OnBnClickedBtnReqNonExecList)
	ON_BN_CLICKED(IDC_BTN_REQ_NON_EXEC_LIST_NEXT, &CFFutOptOrdDlg::OnBnClickedBtnReqNonExecListNext)
	ON_BN_CLICKED(IDC_BTN_REQ_BALANCE, &CFFutOptOrdDlg::OnBnClickedBtnReqBalance)
	ON_BN_CLICKED(IDC_BTN_REQ_BALANCE_NEXT, &CFFutOptOrdDlg::OnBnClickedBtnReqBalanceNext)
	ON_BN_CLICKED(IDC_BTN_LOAD_USER_ACC, &CFFutOptOrdDlg::OnBnClickedBtnLoadUserAcc)
	ON_COMMAND_RANGE(IDC_CON_REAL, IDC_CON_F_DEMO, &CFFutOptOrdDlg::OnRdoSelectServer)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCNO, &CFFutOptOrdDlg::OnNMDblclkListAccNo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NON_EXE, &CFFutOptOrdDlg::OnNMDblclkListNonExec)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BALANCE, &CFFutOptOrdDlg::OnNMDblclkListBalance)

	ON_BN_CLICKED(IDC_BTN_ACCINFO, &CFFutOptOrdDlg::OnBnClickedBtnAccinfo)
	ON_BN_CLICKED(IDC_BUTTON2, &CFFutOptOrdDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

// agent�κ��� �̺�Ʈ ���� �Լ��� �����Ѵ�.
BEGIN_EVENTSINK_MAP(CFFutOptOrdDlg, CDialog)
	ON_EVENT(CFFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 1, CFFutOptOrdDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CFFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 2, CFFutOptOrdDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CFFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 3, CFFutOptOrdDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
	ON_EVENT(CFFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 4, CFFutOptOrdDlg::OnAgentEventHandler, VTS_I4 VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

// CFFutOptOrdDlg �޽��� ó����
void CFFutOptOrdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CFFutOptOrdDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

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
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CFFutOptOrdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CFFutOptOrdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.

	//ȣ�� ����ĥ
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_COMM_STATUS:
	{
		if (m_bCommConnect)
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetBkColor(BUY_BK_COLOR);
			hbr = m_brushBuyBack;
		}
		else
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetBkColor(SELL_BK_COLOR);
			hbr = m_brushSellBack;
		}
	}
	break;
	case IDC_LOGIN_STATE:
	{
		if (m_CommAgent.GetLoginState())
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetBkColor(BUY_BK_COLOR);
			hbr = m_brushBuyBack;
		}
		else
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetBkColor(SELL_BK_COLOR);
			hbr = m_brushSellBack;
		}
	}
	}//End of switch

	return hbr;
}

void CFFutOptOrdDlg::OnNMDblclkListAccNo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	//TCHAR *strTitle[] = { _T("���¹�ȣ"), _T("��ü��ȣ"), _T("���»�ǰ��ȣ"), _T("���¸�"), _T("����Ư��"), _T("���࿬�迩��") };

	CString strAccNo = m_listAccNo.GetItemText(nSelectRow, 0);
	CString strPrdtNo = m_listAccNo.GetItemText(nSelectRow, 2);

	GetDlgItem(IDC_EDIT_ACCNO)->SetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->SetWindowText(strPrdtNo);
}

void CFFutOptOrdDlg::OnNMDblclkListNonExec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	/*TCHAR *strTitle[] = { 0_T("��������"), 1_T("���հ��¹�ȣ"), 2_T("�ֹ���ȣ"), 3_T("��ǰ�ڵ�"),
		4_T("���ֹ���ȣ"), 5_T("���ֹ���ȣ"), 6_T("�ֹ��׷��ȣ"), 7_T("�ֹ�����"),
		8_T("����"), 9_T("�ŵ��ż������ڵ�"), 10_T("�ֹ�����"), 11_T("�ֹ�����"),
		12_T("��������"), 13_T("��Ҽ���"), 14_T("ü�����"), 15_T("�ܿ�����"),
		_T("�������Ǳ����ڵ�"), _T("ü�����Ǳ����ڵ�"), _T("1����������"), _T("���ü�ᰡ��"),
		_T("ü����"), _T("���簡��"), _T("��ü�����ڵ�"), _T("�ֹ������ڵ�"),
		_T("�ֹ����±����ڵ�"), _T("FCM�ֹ���ȣ"), _T("�����ID"), _T("����IP�ּ�"),
		_T("�����ð�"), _T("ü��ð�"), _T("���������ð�"), _T("����ü��ð�"), _T("��ȭ�ڵ�") };*/

	CString strOrdNo = m_listNonExec.GetItemText(nSelectRow, 2);
	CString strSymbol = m_listNonExec.GetItemText(nSelectRow, 3);
	CString strOrdPrice = m_listNonExec.GetItemText(nSelectRow, 10);
	CString strOrdSu = m_listNonExec.GetItemText(nSelectRow, 11);

	GetDlgItem(IDC_EDIT_ORG_NO)->SetWindowText(strOrdNo);
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);
	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);
}

void CFFutOptOrdDlg::OnNMDblclkListBalance(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	/*
		TCHAR *strTitle[] = { 0_T("���հ��¹�ȣ"), 1_T("��ü���հ��¹�ȣ"), 2_T("���»�ǰ��ȣ"), 3_T("����"),
		4_T("��ǰ�ڵ�"), 5_T("��ǰ��"), 6_T("�ŵ��ż������ڵ�"), 7_T("�̰�����������"),
		8_T("�Ÿ���մܰ�"), 9_T("û�갡�ɼ���"), 10_T("�ֹ��ܿ�����"), 11_T("���簡��"),
		12_T("���ϴ��"), 13_T("���ϴ����"), 14_T("�򰡱ݾ�"), 15_T("�򰡼��ͱݾ�"),
		16_T("������"), 17_T("�̰��������ݾ�"), 18_T("ȯ��¼�"), 19_T("�����ɼǱ����ڵ�"),
		20_T("��ȭ�ڵ�"), 21_T("���������ڵ�"), 22_T("����������"), 23_T("���������ȣ"),
		24_T("�����ڸ�"), 25_T("���ݼҼ������ϱ���"), 26_T("ǥ�ð���"), 27_T("��������") };*/

	CString strSymbol = m_listBalance.GetItemText(nSelectRow, 4);
	CString strOrdPrice = m_listBalance.GetItemText(nSelectRow, 8);
	CString strOrdSu = m_listBalance.GetItemText(nSelectRow, 7);

	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);
	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);
}

void CFFutOptOrdDlg::OnDestroy()
{
	//��� �ǽð������ �����Ѵ�.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();
	
	CDialog::OnDestroy();
}

void CFFutOptOrdDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CFFutOptOrdDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� �Ǵ� �⺻���� ȣ���մϴ�.
	switch (nIDEvent)
	{
	case ID_SECOND_TIMER:
	{
		BOOL bConnectState = m_CommAgent.CommGetConnectState();

		if (bConnectState)
			GetDlgItem(IDC_COMM_STATUS)->SetWindowText(_T("�����"));
		else
			GetDlgItem(IDC_COMM_STATUS)->SetWindowText(_T("���� ����"));

		m_bCommConnect = bConnectState;

		BOOL bLoginState = m_CommAgent.GetLoginState();
		if (bLoginState)
			GetDlgItem(IDC_LOGIN_STATE)->SetWindowText(_T("�α���"));
		else
			GetDlgItem(IDC_LOGIN_STATE)->SetWindowText(_T("�α׾ƿ�"));

		GetDlgItem(IDC_COMM_STATUS)->Invalidate();
		GetDlgItem(IDC_LOGIN_STATE)->Invalidate();
	}
	break;
	}//End of switch

	CDialog::OnTimer(nIDEvent);
}

//*******************************************************************
// Function Name : OnRdoSelectServer
// Function      : 
// Param         : UINT nID
// Return        : void 
// Create        : 
// Comment       : ���Ӽ����� �����Ѵ�.
//******************************************************************
void CFFutOptOrdDlg::OnRdoSelectServer(UINT nID)
{
	m_nSeverType = nID - IDC_CON_REAL;

	/*----------------------------------
	  ���Ӽ����� �����Ѵ�.(0 - ����, 1 - ��������, 2 - �ؿܸ���)
	 *----------------------------------*/
	m_CommAgent.SetLoginMode(0, m_nSeverType);
}

//*******************************************************************
// Function Name : OnBnClickedBtnAccinfo
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : �ֹ��븮�� ��Ͽ���
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnAccinfo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strAccNo;
	CString strAPNO;

	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ
	
	CString strReturn = m_CommAgent.GetAccInfo(198, strAccNo + strAPNO);

	::AfxMessageBox(strReturn);
}


//*******************************************************************
// Function Name : OnInitDialog
// Function      : ���̾�α� �ʱ�ȭ
// Param         : 
// Return        : BOOL 
// Create        : 
// Comment       : 
//******************************************************************
BOOL CFFutOptOrdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CString strTitle;
	strTitle.Format("%s-[�ؿܼ����ֹ�](%s)", PROGRAM_NAME, VERSION_INFO);
	SetWindowText(strTitle);
	
	/**********************************
	 * Open API Agent ��Ʈ�� �����츦 �����Ѵ�.
	 **********************************/
	BOOL bRtn = m_CommAgent.Create(_T("HFCOMMAGENT.HFCommAgentCtrl.1"), NULL, WS_CHILD, CRect(0, 0, 0, 0), this, IDC_HFCOMMAGENTCTRL1);
	if (!bRtn)
	{
		::AfxMessageBox("Open API Agent ��Ʈ�� ������ ������ �����߽��ϴ�!");
		return FALSE;
	}

	/**********************************
	 * 1�� ���� Ÿ�̸�
	 **********************************/
	SetTimer(ID_SECOND_TIMER, 1000, NULL);

	/**********************************
	* ����Ʈ ��Ʈ�� �ʱ�ȭ
	**********************************/
	InitListAccNo();	//���¸��
	InitListReal();		//�ǽð� �ֹ��޽���
	InitListNonExec();	//�ֹ���ü��
	InitListExec();		//�ֹ�ü��
	InitListDeposit();	//������
	InitListBalance();	//�ܰ�

	/**********************************
	 * HFCommAgent.dll(API Agent DLL���� ��ġ�� ���)
	 **********************************/
	CString strApidAgentModulePath = m_CommAgent.GetApiAgentModulePath();
	GetDlgItem(IDC_API_AGENT_PATH)->SetWindowText(strApidAgentModulePath);

	/**********************************
	 * ���Ӽ��� ����
	 **********************************/
	m_nSeverType = m_CommAgent.GetLoginMode(0);
	switch (m_nSeverType)
	{
		case 1: //�������Ǽ���
			((CButton*)GetDlgItem(IDC_CON_DEMO))->SetCheck(1);
		break;
		case 2: //�ؿܸ��Ǽ���
			((CButton*)GetDlgItem(IDC_CON_F_DEMO))->SetCheck(1);
		break;
		default: //�ǰŷ�����
			((CButton*)GetDlgItem(IDC_CON_REAL))->SetCheck(1);
		break;
	}//End of switch

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

//*******************************************************************
// Function Name : InitListAccNo
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::InitListAccNo()
{
	CRect rc;
	m_listAccNo.GetClientRect(rc);
	m_listAccNo.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("���¹�ȣ"), _T("��ü��ȣ"), _T("���»�ǰ��ȣ"), _T("���¸�"), _T("����Ư��"), _T("���࿬�迩��")};

	int i;
	for (i = 0; i < 6; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		if (i == 0)
			lvcolumn.fmt = LVCFMT_CENTER;
		else
			lvcolumn.fmt = LVCFMT_LEFT;

		lvcolumn.pszText = strTitle[i];

		lvcolumn.iSubItem = i;
		lvcolumn.cx = 80;
		m_listAccNo.InsertColumn(i, &lvcolumn);
	}
}

//*******************************************************************
// Function Name : InitListReal
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::InitListReal()
{
	m_listReal.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = {_T("�޽���")};

	int i;
	for (i = 0; i < 1; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		if (i == 0)
			lvcolumn.fmt = LVCFMT_CENTER;
		else
			lvcolumn.fmt = LVCFMT_LEFT;

		lvcolumn.pszText = strTitle[i];

		lvcolumn.iSubItem = i;
		lvcolumn.cx = 700;
		m_listReal.InsertColumn(i, &lvcolumn);
	}//End of for
}

//*******************************************************************
// Function Name : InitListNonExec
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::InitListNonExec()
{
	CRect rc;
	m_listNonExec.GetClientRect(rc);
	m_listNonExec.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("��������"), _T("���հ��¹�ȣ"), _T("�ֹ���ȣ"), _T("��ǰ�ڵ�"),
		_T("���ֹ���ȣ"), _T("���ֹ���ȣ"), _T("�ֹ��׷��ȣ"), _T("�ֹ�����"),
		_T("����"), _T("�ŵ��ż������ڵ�"), _T("�ֹ�����"), _T("�ֹ�����"),
		_T("��������"), _T("��Ҽ���"), _T("ü�����"), _T("�ܿ�����"),
		_T("�������Ǳ����ڵ�"), _T("ü�����Ǳ����ڵ�"), _T("1����������"), _T("���ü�ᰡ��"),
		_T("ü����"), _T("���簡��"), _T("��ü�����ڵ�"), _T("�ֹ������ڵ�"),
		_T("�ֹ����±����ڵ�"), _T("FCM�ֹ���ȣ"), _T("�����ID"), _T("����IP�ּ�"),
		_T("�����ð�"), _T("ü��ð�"), _T("���������ð�"), _T("����ü��ð�"), _T("��ȭ�ڵ�") };

	int i;
	for (i = 0; i < 33; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		if (i == 0)
			lvcolumn.fmt = LVCFMT_CENTER;
		else
			lvcolumn.fmt = LVCFMT_LEFT;

		lvcolumn.pszText = strTitle[i];

		lvcolumn.iSubItem = i;
		lvcolumn.cx = 80;
		m_listNonExec.InsertColumn(i, &lvcolumn);
	}
}

//*******************************************************************
// Function Name : InitListExec
// Function      : 
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::InitListExec()
{
	CRect rc;
	m_listExec.GetClientRect(rc);
	m_listExec.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("���հ��¹�ȣ"), _T("�ֹ���ȣ"), _T("��ǰ�ڵ�"), _T("���ֹ���ȣ"), _T("���ֹ���ȣ"),
		_T("�ֹ��׷��ȣ"), _T("�ֹ�����"), _T("���»�ǰ�ڵ�"), _T("����"), _T("�ŵ��ż������ڵ�"),
		_T("�ֹ�����"), _T("�ֹ�����"), _T("��������"), _T("��Ҽ���"), _T("ü�����"), _T("�ܿ�����"),
		_T("�������Ǳ����ڵ�"), _T("ü�����Ǳ����ڵ�"), _T("1����������"), _T("���ü�ᰡ��"),
		_T("ü����"), _T("���簡��"), _T("��ü�����ڵ�"), _T("�ֹ������ڵ�"), _T("�ֹ����±����ڵ�"),
		_T("FCM�ֹ���ȣ"), _T("�����ID"), _T("����IP�ּ�"), _T("�����ð�"), _T("ü��ð�"), _T("���������ð�"),
		_T("ü����Ͻ�"), _T("��ȭ�ڵ�") };

	int i;
	for (i = 0; i < 33; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		if (i == 0)
			lvcolumn.fmt = LVCFMT_CENTER;
		else
			lvcolumn.fmt = LVCFMT_LEFT;

		lvcolumn.pszText = strTitle[i];

		lvcolumn.iSubItem = i;
		lvcolumn.cx = 80;
		m_listExec.InsertColumn(i, &lvcolumn);
	}
}

//*******************************************************************
// Function Name : InitListDeposit
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : ������
//******************************************************************
void CFFutOptOrdDlg::InitListDeposit()
{
	CRect rc;
	m_listDeposit.GetClientRect(rc);
	m_listDeposit.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("��ȭ�ڵ�"), _T("����ȯ��"), _T("��������"), _T("�����Ա�"),
						_T("�������"), _T("û�����"), _T("�ɼǸŵ�"), _T("�ɼǸż�"),
						_T("������"), _T("��������"), _T("�򰡼���"), _T("�򰡿�Ź"),
						_T("�ɼ���"), _T("�Ѱ����ڻ�"), _T("�������ű�"), _T("�ֹ����ű�"),
						_T("�������ű�"), _T("���űݺ���"), _T("���Ⱑ��"), _T("ȯ������"),
						_T("�ֹ�����"), _T("�߰����ű�"), _T("�̼���ü����") };

	int i;
	for (i = 0; i < 23; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		if (i == 0)
			lvcolumn.fmt = LVCFMT_CENTER;
		else
			lvcolumn.fmt = LVCFMT_LEFT;

		lvcolumn.pszText = strTitle[i];

		lvcolumn.iSubItem = i;
		lvcolumn.cx = 80;
		m_listDeposit.InsertColumn(i, &lvcolumn);
	}
}

//*******************************************************************
// Function Name : InitListBalance
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::InitListBalance()
{
	CRect rc;
	m_listBalance.GetClientRect(rc);
	m_listBalance.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("���հ��¹�ȣ"), _T("��ü���հ��¹�ȣ"), _T("���»�ǰ��ȣ"), _T("����"),
		_T("��ǰ�ڵ�"), _T("��ǰ��"), _T("�ŵ��ż������ڵ�"), _T("�̰�����������"),
		_T("�Ÿ���մܰ�"), _T("û�갡�ɼ���"), _T("�ֹ��ܿ�����"), _T("���簡��"),
		_T("���ϴ��"), _T("���ϴ����"), _T("�򰡱ݾ�"), _T("�򰡼��ͱݾ�"),
		_T("������"), _T("�̰��������ݾ�"), _T("ȯ��¼�"), _T("�����ɼǱ����ڵ�"),
		_T("��ȭ�ڵ�"), _T("���������ڵ�"), _T("����������"), _T("���������ȣ"),
		_T("�����ڸ�"), _T("���ݼҼ������ϱ���"), _T("ǥ�ð���"), _T("��������") };

	int i;
	for (i = 0; i < 28; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		if (i == 0)
			lvcolumn.fmt = LVCFMT_CENTER;
		else
			lvcolumn.fmt = LVCFMT_LEFT;

		lvcolumn.pszText = strTitle[i];

		lvcolumn.iSubItem = i;
		lvcolumn.cx = 80;
		m_listBalance.InsertColumn(i, &lvcolumn);
	}
}

//*******************************************************************
// Function Name : OnBnClickedLogin
// Function      : �α���
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedLogin()
{
	//�α��� ID
	m_editUserID.GetWindowText(m_strLoginID);

	//�α��� ��й�ȣ
	m_editPwd.GetWindowText(m_strLoginPwd);

	//�������� ��й�ȣ
	m_editAuthPwd.GetWindowText(m_strCertPwd);

	if (m_strLoginID.IsEmpty() || m_strLoginPwd.IsEmpty())
	{
		::AfxMessageBox("ID, ����� �ʼ� �Է��Դϴ�.");
		return;
	}

	/**********************************
	* ���� ���� IP ����
	**********************************/
	CString strIpAddress;
	GetDlgItem(IDC_EDIT_IP)->GetWindowText(strIpAddress);
	m_CommAgent.SetConnectIPList(strIpAddress);

	if (!m_bCommConnect)
	{
		/**********************************
		 * ��Ÿ�� �ʱ�ȭ �� ��� ����
		 **********************************/
		if (m_CommAgent.CommInit() < 0)
			::AfxMessageBox(m_CommAgent.GetLastErrMsg());
	}

	//�������(TRUE : ����, FALSE : ����)
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}
	
	/**********************************
	* �α����� ��û�Ѵ�.
	**********************************/
	if (m_CommAgent.CommLogin(m_strLoginID, m_strLoginPwd, m_strCertPwd) == 0)
	{
		//�α��� ����
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());

		m_CommAgent.CommTerminate(TRUE);
	}

	/**********************************
	 * �α����� �Ϸ�Ǹ� �ֹ� �ǽð��� ����Ѵ�.
	 * �ֹ� �ǽð� �뺸�� �����ID�� ���Ű�� �ȴ�.
	 **********************************/
	//ü�� �ǽð� �뺸
	m_CommAgent.RegisterReal("EF1", m_strLoginID);
	//��ü�� �ǽð� �뺸
	m_CommAgent.RegisterReal("EF4", m_strLoginID);
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : �α׾ƿ�
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedLogout()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	/**********************************
	* �α׾ƿ��Ѵ�.
	**********************************/
	m_CommAgent.CommLogout(m_strLoginID);

	//��� �ǽð������ �����Ѵ�.
	m_CommAgent.AllUnRegisterReal();

	/**********************************
	 * ��ſ����� ���´�.
	 **********************************/
	m_CommAgent.CommTerminate(TRUE);

	//�������(TRUE : ����, FALSE : ����)
	m_bCommConnect = m_CommAgent.CommGetConnectState();
}

//*******************************************************************
// Function Name : OnBnClickedOk
// Function      : ��ȭâ ����
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	PostMessage(WM_CLOSE);
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqAccno
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnReqAccno()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	switch (m_nSeverType)
	{
		case 0 : //�ǰŷ�
			RequestAccList();
		break;
		case 1 : //��������
			OnBnClickedBtnLoadUserAcc();
		break;
		case 2 : //�ؿܸ���
			RequestFDemoAccList();
		break;
	}
}

//*******************************************************************
// Function Name : OnBnClickedBtnLoadUserAcc
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnLoadUserAcc()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_listAccNo.DeleteAllItems();

	//�������� ���� ��ȯ�Ѵ�.
	int nAccCnt = m_CommAgent.GetUserAccCnt();
	CString strAccNoPrtd; //���հ��¹�ȣ(8) + ��ǰ��ȣ(3)
	CString strAccNo;	//���¹�ȣ
	CString strAPNO;	//���´�ü��ȣ
	CString strPrdtNo;	//���»�ǰ��ȣ

	m_listAccNo.SetRedraw(FALSE);
	int nListIndex = 0;

	for (int i = 0; i < nAccCnt; i++)
	{
		//���հ��¹�ȣ(8) + ��ǰ��ȣ(3)
		strAccNoPrtd = m_CommAgent.GetUserAccNo(i);

		if(strAccNoPrtd.IsEmpty()) continue;

		//�տ� 8�ڸ��� ���հ��¹�ȣ
		strAccNo = strAccNoPrtd.Mid(0, 8);
		//�ڿ� 3�ڸ��� ���»�ǰ��ȣ
		strPrdtNo = strAccNoPrtd.Mid(8, 3);

		strAPNO = GetAccAPNO(strAccNo + strPrdtNo);	//���հ��´�ü��ȣ
		
		if (!strPrdtNo.IsEmpty())
		{
			LV_ITEM	lvItem;
			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listAccNo.InsertItem(&lvItem);

			m_listAccNo.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strAccNo);		//���հ��¹�ȣ
			m_listAccNo.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strAPNO);		//��ü���հ��¹�ȣ
			m_listAccNo.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strPrdtNo);		//���»�ǰ��ȣ
			m_listAccNo.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)"");		//���¸�
		}
	}

	m_listAccNo.SetRedraw(TRUE);
}

//*******************************************************************
// Function Name : GetAccAPNO
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : ���������� �� ���հ��´�ü��ȣ ������ �Լ�
//******************************************************************
CString CFFutOptOrdDlg::GetAccAPNO(CString strAccNo)
{
	CString strAPNO;

	//0-����, 1-��������, 2-�ؿܸ���
	switch (m_nSeverType)
	{
		case 0:	//����
		case 1:	//��������
		{
			strAPNO = m_CommAgent.GetAccInfo(0, strAccNo);
		}
		break;
		case 2:	//�ؿܸ���
		{
			strAccNo.Trim();

			if (strAccNo.GetLength() > 8)
				strAccNo = strAccNo.Mid(0, 8);

			//������ ���� ���ǿ� ������ȸ Tran���� ������ ��ü��ȣ�� ����Ѵ�.
			int nAccCnt = m_arrAccNo.GetSize();			//���¸��
			int nApnoCnt = m_arrAccAPNO.GetSize();		//���հ��´�ü��ȣ���

			if (nAccCnt != nApnoCnt) return strAPNO;

			for (int i = 0; i < nAccCnt; i++)
			{
				if (m_arrAccNo.GetAt(i) == strAccNo)
				{
					strAPNO = m_arrAccAPNO.GetAt(i);
					break;
				}
			}
		}
		break;

	}//End of switch

	return strAPNO;
}

//*******************************************************************
// Function Name : RequestAccList
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : ���¸�� ��ȸ
//******************************************************************
void CFFutOptOrdDlg::RequestAccList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	m_listAccNo.DeleteAllItems();

	CString strTrCode = "HHTACCNM01";	//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName1 = "InRec1";	//�Է� ���ڵ��(���ҽ����� ����)
	CString strInRecName2 = "InRec2";	//�Է� ���ڵ��(���ҽ����� ����)

	//InRec1 �Է�
	CString strfunc;		//��ɱ����ڵ�(Q:Query,U:UPDATE,M:Upate and Query)
	CString strusid;		//����ھ��̵�
	CString strerrc;		//�����ڵ�
	CString stremsg;		//�����޽���
	CString strnrec;		//�Է°Ǽ�

	//InRec2 �Է�
	CString straccn;		//���¹�ȣ
	CString strsub_accn;	//��ü���¹�ȣ
	CString stracnm;		//���¸�
	CString strachk;		//����Ư��(00:�⺻����,01: ȭ��� ������ �ʴ°���)
	CString strpwch;		//���࿬����¿���

	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdAccNoList = m_CommAgent.CreateRequestID();

	strfunc = "Q";			//��ɱ����ڵ�(Q:Query,U:UPDATE,M:Upate and Query)
	strusid = m_strLoginID;	//����ھ��̵�
	strnrec = "1";			//�Է°Ǽ�

	/*InRec1 ���ڵ�� �ܰ� �Է��̴�.*/
	m_CommAgent.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "func", strfunc); //��ɱ����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "usid", strusid); //����ھ��̵�
	m_CommAgent.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "errc", strerrc); //�����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "emsg", stremsg); //�����޽���
	m_CommAgent.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "nrec", strnrec); //�Է°Ǽ�

	/*InRec2 ���ڵ�� ������ �Է��̴�.*/
	/*	REC_NAME=InRec2, INOUT=0, ARRAY=3, ARRINFO=InRec1.nrec;
	ARRAY �� '0'���� ũ�� �Է��� �������̴�.	*/
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdAccNoList, strTrCode, strInRecName2, _ttoi(strnrec));

	for (int i = 0; i < _ttoi(strnrec); i++)
	{
		m_CommAgent.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "accn", straccn, i);			//���¹�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "sub_accn", strsub_accn, i);	//��ü���¹�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "acnm", stracnm, i);			//���¸�
		m_CommAgent.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "achk", strachk, i);			//����Ư��
		m_CommAgent.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "pwch", strpwch, i);			//���࿬����¿���
	}//End of for

	CString strBenefitAcc = "N";		//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdAccNoList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : RequestDemoAccList
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : �ؿܸ��� ���¸�� ��ȸ
//******************************************************************
void CFFutOptOrdDlg::RequestFDemoAccList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	m_listAccNo.DeleteAllItems();

	CString strTrCode = "OTS5991Q03";	//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName1 = "OTS5991Q03_in";	//�Է� ���ڵ��(���ҽ����� ����)
	
	CString strUSR_ID = m_strLoginID;		//�����ID

	/*-------------------------------*
		[1] Request ID����
	 *-------------------------------*/
	m_nRqIdFDemoAccNoList = m_CommAgent.CreateRequestID();
	m_CommAgent.SetTranInputData(m_nRqIdFDemoAccNoList, strTrCode, strInRecName1, "USR_ID", strUSR_ID);		//�����ID

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "1";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ

	/*-------------------------------*
		[2] ������ Tran��ȸ ��û�Ѵ�.
	 *-------------------------------*/
	if (m_CommAgent.RequestTran(m_nRqIdFDemoAccNoList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : SendSellBuyOrder
// Function      : 
// Param         : CString strDealingSide
// Return        : void 
// Create        : 
// Comment       : �ż�/�ŵ� �ֹ� ����
//******************************************************************
BOOL CFFutOptOrdDlg::SendSellBuyOrder(CString strDealingSide, int nRqId)
{
	CString strTrCode = "OTS5901U01";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5901U01_in";		//�Է� ���ڵ��(���ҽ����� ����)

	//[1] Request ID����
	
	CString strCTNO;			//��ü���հ��¹�ȣ
	CString strAPNO;			//���»�ǰ��ȣ
	CString strPWD;				//��й�ȣ
	CString strPRDT_CD;			//��ǰ�ڵ�
	CString strSELL_BUY_DCD;	//�ŵ��ż������ڵ�
	CString strPRC_CND_DCD;		//�������Ǳ����ڵ�
	CString strODRV_ORDR_PRC;	//�ؿ��Ļ��ֹ�����
	CString strORDR_QNT;		//�ֹ�����
	CString strSTLS_APPN_PRC;	//��ž�ν���������
	CString strORDR_HND_DCD;	//�ֹ����۱����ڵ�
	CString strORDR_DCD;		//�ֹ������ڵ�
	CString strETC_ORDR_DCD;	//��Ÿ�ֹ������ڵ�
	CString strCNCS_CND_DCD;	//ü�����Ǳ����ڵ�
	CString strCLR_PST_NO;		//û�������ǹ�ȣ
	CString strORDR_EXPR_DT;	//�ֹ���������

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//��й�ȣ
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//��ǰ�ڵ�

	strSELL_BUY_DCD = strDealingSide;								//�ŵ��ż������ڵ�(S:�ŵ�, B:�ż�)

	if (m_cmdOrdType.GetCurSel() >= 0)
		strPRC_CND_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];		//�������Ǳ����ڵ�

	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strODRV_ORDR_PRC);	//�ؿ��Ļ��ֹ�����
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);		//�ֹ�����
	GetDlgItem(IDC_EDIT_STOP_PRC)->GetWindowText(strSTLS_APPN_PRC); //��ž�ν���������

	strORDR_HND_DCD	= "C";					//�ֹ����۱����ڵ�(C:�Ϲ��ֹ�, M:�ݴ�Ÿ�, F:����û��, D:FND�ݴ�Ÿ�)
	strORDR_DCD		= "O";					//�ֹ������ڵ�
	strCNCS_CND_DCD	= "1";					//ü�����Ǳ����ڵ�(1:FAS(DAY), 6:GTD)

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "CTNO", strCTNO);						//��ü���հ��¹�ȣ
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "APNO", strAPNO);						//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "PWD", strPWD);						//��й�ȣ
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);				//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);		//�ŵ��ż������ڵ�
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "PRC_CND_DCD", strPRC_CND_DCD);		//�������Ǳ����ڵ�
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ODRV_ORDR_PRC", strODRV_ORDR_PRC);	//�ؿ��Ļ��ֹ�����
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);				//�ֹ�����

	if (strPRC_CND_DCD == "3")
		m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "STLS_APPN_PRC", strSTLS_APPN_PRC);	//��ž�ν���������

	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_HND_DCD", strORDR_HND_DCD);		//�ֹ����۱����ڵ�
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_DCD", strORDR_DCD);				//�ֹ������ڵ�
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ETC_ORDR_DCD", strETC_ORDR_DCD);		//��Ÿ�ֹ������ڵ�
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "CNCS_CND_DCD", strCNCS_CND_DCD);		//ü�����Ǳ����ڵ�
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "CLR_PST_NO", strCLR_PST_NO);			//û�������ǹ�ȣ
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_EXPR_DT", strORDR_EXPR_DT);		//�ֹ���������

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[3] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(nRqId, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", 0) < 0)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return FALSE;
	}

	return TRUE;
}

//*******************************************************************
// Function Name : OnBnClickedBtnSell
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : �ŵ��ֹ�
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnSell()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_nRqIdSellOrd = m_CommAgent.CreateRequestID();
	SendSellBuyOrder("S", m_nRqIdSellOrd);	//�ŵ��ֹ� ����
}

//*******************************************************************
// Function Name : OnBnClickedBtnBuy
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : �ż��ֹ�
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnBuy()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_nRqIdBuyOrd = m_CommAgent.CreateRequestID();
	SendSellBuyOrder("B", m_nRqIdBuyOrd);	//�ŵ��ֹ� ����
}

//*******************************************************************
// Function Name : OnBnClickedBtnChange
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : �����ֹ�
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnChange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5901U02";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5901U02_in";	//�Է� ���ڵ��(���ҽ����� ����)
	
	//[1] Request ID����
	m_nRqIdChangeOrd = m_CommAgent.CreateRequestID();

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	CString strODRV_OR_ODNO;		//�ؿ��Ļ����ֹ���ȣ
	CString strCTNO;		//��ü���հ��¹�ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strPWD;		//��й�ȣ
	CString strPRDT_CD;		//��ǰ�ڵ�
	CString strPRC_CND_DCD;		//�������Ǳ����ڵ�
	CString strODRV_RVSE_PRC;		//�ؿ��Ļ���������
	CString strRVSE_QNT;		//��������
	CString strSTLS_APPN_PRC;		//��ž�ν���������
	CString strRMN_QNT_YN;		//�ܿ���������

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//��й�ȣ
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.
	
	//�ؿ��Ļ����ֹ���ȣ
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strODRV_OR_ODNO);
	
	//��ǰ�ڵ�
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);
	
	//�������Ǳ����ڵ�
	strPRC_CND_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];

	//�ؿ��Ļ���������
	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strODRV_RVSE_PRC);

	//��������
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strRVSE_QNT);

	//��ž�ν���������
	GetDlgItem(IDC_EDIT_STOP_PRC)->GetWindowText(strSTLS_APPN_PRC);

	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ODRV_OR_ODNO", strODRV_OR_ODNO);	//�ؿ��Ļ����ֹ���ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "CTNO", strCTNO);				//��ü���հ��¹�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "APNO", strAPNO);				//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PWD", strPWD);					//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PRC_CND_DCD", strPRC_CND_DCD);		//�������Ǳ����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ODRV_RVSE_PRC", strODRV_RVSE_PRC);		//�ؿ��Ļ���������
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "RVSE_QNT", strRVSE_QNT);		//��������
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "STLS_APPN_PRC", strSTLS_APPN_PRC);		//��ž�ν���������
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "RMN_QNT_YN", strRMN_QNT_YN);		//�ܿ���������

	CString strBenefitAcc = "N";		//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[3] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdChangeOrd, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", nRequestDataCnt) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnCancel
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : ����ֹ�
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5901U03";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5901U03_in";	//�Է� ���ڵ��(���ҽ����� ����)

	//[1] Request ID����
	m_nRqIdCancelOrd = m_CommAgent.CreateRequestID();

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	
	CString strCTNO;		//��ü���հ��¹�ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strPWD;		//��й�ȣ
	CString strODRV_OR_ODNO;		//�ؿ��Ļ����ֹ���ȣ
	CString strPRDT_CD;		//��ǰ�ڵ�
	CString strCNCL_QNT;		//��Ҽ���

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//��ü���հ��¹�ȣ
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//��й�ȣ
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.

	//�ؿ��Ļ����ֹ���ȣ
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strODRV_OR_ODNO);

	//��ǰ�ڵ�
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//��Ҽ���
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strCNCL_QNT);

	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, "OTS5901U03_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, "OTS5901U03_in", "CTNO", strCTNO);		//��ü���հ��¹�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, "OTS5901U03_in", "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, "OTS5901U03_in", "PWD", strPWD);		//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, "OTS5901U03_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, "OTS5901U03_in", "CNCL_QNT", strCNCL_QNT);		//��Ҽ���

	CString strBenefitAcc = "N";		//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[3] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdCancelOrd, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", nRequestDataCnt) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqDeposit
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnReqDeposit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_listDeposit.DeleteAllItems();
	m_strListDepositNextRqKey.Empty();				//����Ű�� �ʱ�ȭ��Ų��.

	CString strTrCode = "OTS5943Q01";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5943Q01_in";			//�Է� ���ڵ��(���ҽ����� ����)

	/*-------------------------------*
	 [1] Request ID����
	*-------------------------------*/
	m_nRqIdDepositList = m_CommAgent.CreateRequestID();

	CString strBSN_DT;			//��������
	CString strCTNO;			//��ü���հ��¹�ȣ
	CString strAPNO;			//���»�ǰ��ȣ
	CString strPWD;				//��й�ȣ(�ܹ��� ��ȣȭ�� �Ѵ�.)

	//��ȸ����
	m_dateTime1.GetWindowText(strBSN_DT);
	strBSN_DT.Remove('-');
	
	//���¹�ȣ
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	
	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);
	strCTNO = GetAccAPNO(strCTNO + strAPNO);	//���հ��´�ü��ȣ

	//���º��
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD); //��ȣȭ�Ѵ�.


	/*-------------------------------*
	 [2] Tran��ȸ �Է°��� �Է��Ѵ�.
	 *-------------------------------*/
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "BSN_DT", strBSN_DT);	//��������
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "CTNO", strCTNO);		//��ü���հ��¹�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "PWD", strPWD);		//��й�ȣ

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "1";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	/*-------------------------------*
	 [3] ������ Tran��ȸ ��û�Ѵ�.
	 *-------------------------------*/
	if(m_CommAgent.RequestTran(m_nRqIdDepositList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 35) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqDepositNext
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnReqDepositNext()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5943Q01";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5943Q01_in";			//�Է� ���ڵ��(���ҽ����� ����)

	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdDepositList = m_CommAgent.CreateRequestID();

	CString strBSN_DT;		//��������
	CString strCTNO;		//��ü���հ��¹�ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strPWD;			//��й�ȣ

	//��ȸ����
	m_dateTime1.GetWindowText(strBSN_DT);
	strBSN_DT.Remove('-');

	//���¹�ȣ
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);

	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);
	strCTNO = GetAccAPNO(strCTNO + strAPNO);	//���հ��´�ü��ȣ

	//���º��
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD); //��ȣȭ�Ѵ�.

	/*-------------------------------*
	[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	*-------------------------------*/
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "BSN_DT", strBSN_DT);	//��������
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "CTNO", strCTNO);		//��ü���հ��¹�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "PWD", strPWD);		//��й�ȣ

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "3";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	/*-------------------------------*
	[3] ������ Tran��ȸ ��û�Ѵ�.
	*-------------------------------*/
	if(m_CommAgent.RequestTran(m_nRqIdDepositList, strTrCode, strBenefitAcc, strPreNext, m_strListDepositNextRqKey, strScreenNo, "Q", 0) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqNonExecList
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnReqNonExecList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_listNonExec.DeleteAllItems();
	m_strListNonExecNextRqKey.Empty(); //����Ű�� �ʱ�ȭ��Ų��.

	CString strTrCode = "OTS5911Q41";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5911Q41_in_sub01";	//�Է� ���ڵ��(���ҽ����� ����)

	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdNonExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] �Է� �Ǽ��� �Է��Ѵ�.
	*-------------------------------*/
	/*	REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
	ARRAY �� '0'���� ũ�� �Է��� �������̴�.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdNonExecList, strTrCode, strInRecName, nInputCnt);
	
	CString strAccNo;	//���հ��¹�ȣ
	CString strCTNO;	//���´�ü��ȣ
	CString strPrdt;	//���»�ǰ��ȣ
	CString strPWD;		//���º�й�ȣ

	//[3] Tran��ȸ �Է°��� �Է��Ѵ�.
	for (int i = 0; i < nInputCnt; i++)
	{
		//���´�ü��ȣ�� ���´�.
		GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
		
		//���»�ǰ��ȣ
		GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strPrdt);

		strCTNO = GetAccAPNO(strAccNo + strPrdt);	//���հ��´�ü��ȣ

		//���º�й�ȣ
		GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
		strPWD = m_CommAgent.GetEncrpyt(strPWD);

		//��ü���հ��¹�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdNonExecList, strTrCode, strInRecName, "CTNO", strCTNO, i);

		//���»�ǰ��ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdNonExecList, strTrCode, strInRecName, "APNO", strPrdt, i);

		//���º�й�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdNonExecList, strTrCode, strInRecName, "PWD", strPWD, i);

	}

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "1";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if(m_CommAgent.RequestTran(m_nRqIdNonExecList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqNonExecListNext
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnReqNonExecListNext()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5911Q41";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5911Q41_in_sub01";	//�Է� ���ڵ��(���ҽ����� ����)

	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdNonExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] �Է� �Ǽ��� �Է��Ѵ�.
	*-------------------------------*/
	/*	REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
	ARRAY �� '0'���� ũ�� �Է��� �������̴�.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdNonExecList, strTrCode, strInRecName, nInputCnt);

	CString strAccNo;
	CString strCTNO;
	CString strPrdt;
	CString strPWD;

	//[3] Tran��ȸ �Է°��� �Է��Ѵ�.
	for (int i = 0; i < nInputCnt; i++)
	{
		//���´�ü��ȣ�� ���´�.
		GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
		
		//���»�ǰ��ȣ
		GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strPrdt);
		strCTNO = GetAccAPNO(strAccNo + strPrdt);	//���հ��´�ü��ȣ

		//���º�й�ȣ
		GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
		strPWD = m_CommAgent.GetEncrpyt(strPWD);

		//��ü���հ��¹�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdNonExecList, strTrCode, strInRecName, "CTNO", strCTNO, i);

		//���»�ǰ��ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdNonExecList, strTrCode, strInRecName, "APNO", strPrdt, i);

		//���º�й�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdNonExecList, strTrCode, strInRecName, "PWD", strPWD, i);
	}

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "3";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if(m_CommAgent.RequestTran(m_nRqIdNonExecList, strTrCode, strBenefitAcc, strPreNext, m_strListNonExecNextRqKey, strScreenNo, "Q", nRequestDataCnt) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}


//*******************************************************************
// Function Name : OnBnClickedBtnReqExecList
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : �ֹ�ü�᳻����ȸ
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnReqExecList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_listExec.DeleteAllItems();
	m_strListExecNextRqKey.Empty(); //����Ű�� �ʱ�ȭ��Ų��.

	CString strTrCode = "OTS5911Q52";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5911Q52_in_sub01";	//�Է� ���ڵ��(���ҽ����� ����)
	
	/*-------------------------------*
		[1] Request ID����
	 *-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
		[2] �Է� �Ǽ��� �Է��Ѵ�.
	 *-------------------------------*/
	/*	REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		ARRAY �� '0'���� ũ�� �Է��� �������̴�.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdExecList, strTrCode, strInRecName, nInputCnt);

	CString strAccNo;
	CString strCTNO;
	CString strPrdt;
	CString strPWD;

	//[3] Tran��ȸ �Է°��� �Է��Ѵ�.
	for (int i = 0; i < nInputCnt; i++)
	{
		//���´�ü��ȣ�� ���´�.
		GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
		
		//���»�ǰ��ȣ
		GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strPrdt);
		strCTNO = GetAccAPNO(strAccNo + strPrdt);	//���հ��´�ü��ȣ

		//���º�й�ȣ
		GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
		strPWD = m_CommAgent.GetEncrpyt(strPWD);

		//��ü���հ��¹�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO, i);

		//���»�ǰ��ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strPrdt, i);

		//���º�й�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD, i);
	}

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "1";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if(m_CommAgent.RequestTran(m_nRqIdExecList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqExecListNext
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnReqExecListNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5911Q52";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5911Q52_in_sub01";	//�Է� ���ڵ��(���ҽ����� ����)

	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] �Է� �Ǽ��� �Է��Ѵ�.
	*-------------------------------*/
	/*	REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		ARRAY �� '0'���� ũ�� �Է��� �������̴�.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdExecList, strTrCode, strInRecName, nInputCnt);

	CString strAccNo;
	CString strCTNO;
	CString strPrdt;
	CString strPWD;

	//[3] Tran��ȸ �Է°��� �Է��Ѵ�.
	for (int i = 0; i < nInputCnt; i++)
	{
		//���´�ü��ȣ�� ���´�.
		GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
		
		//���»�ǰ��ȣ
		GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strPrdt);
		strCTNO = GetAccAPNO(strAccNo + strPrdt); //���հ��´�ü��ȣ ��ȸ

		//���º�й�ȣ
		GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
		strPWD = m_CommAgent.GetEncrpyt(strPWD);

		//��ü���հ��¹�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO, i);

		//���»�ǰ��ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strPrdt, i);

		//���º�й�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD, i);
	}

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "3";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if(m_CommAgent.RequestTran(m_nRqIdExecList, strTrCode, strBenefitAcc, strPreNext, m_strListExecNextRqKey, strScreenNo, "Q", nRequestDataCnt) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqBalance
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnReqBalance()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_listBalance.DeleteAllItems();
	m_strListBalanceNextRqKey.Empty(); //����Ű�� �ʱ�ȭ��Ų��.

	CString strTrCode = "OTS5919Q41";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName1 = "OTS5919Q41_in";	//�Է� ���ڵ��(���ҽ����� ����)
	CString strInRecName2 = "OTS5919Q41_in_sub01";	//�Է� ���ڵ��(���ҽ����� ����)

	CString strODRV_SELL_BUY_DCD = "0";	//�ؿ��Ļ��ŵ��ż������ڵ�(0:��ü, B:�ż�, S:�ŵ�)
	CString strCTNO;				//��ü���հ��¹�ȣ
	CString strAPNO;				//���»�ǰ��ȣ
	
	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdBalanceList = m_CommAgent.CreateRequestID();

	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//�ؿ��Ļ��ŵ��ż������ڵ�

	/*-------------------------------*
	[2] �Է� �Ǽ��� �Է��Ѵ�.
	*-------------------------------*/
	/*	REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
	ARRAY �� '0'���� ũ�� �Է��� �������̴�.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdBalanceList, strTrCode, strInRecName2, 1);

	CString strAccNo;
	CString strPrdt;
	CString strPWD;

	//[3] Tran��ȸ �Է°��� �Է��Ѵ�.
	for (int i = 0; i < 3; i++)
	{
		//���´�ü��ȣ�� ���´�.
		GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
		
		//���»�ǰ��ȣ
		GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strPrdt);
		strCTNO = GetAccAPNO(strAccNo + strPrdt); //���հ��´�ü��ȣ ��ȸ

		//���º�й�ȣ
		GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
		strPWD = m_CommAgent.GetEncrpyt(strPWD);

		//��ü���հ��¹�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "CTNO", strCTNO, i);

		//���»�ǰ��ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "APNO", strPrdt, i);

		//���º�й�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "PWD", strPWD, i);
	}

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "1";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if(m_CommAgent.RequestTran(m_nRqIdBalanceList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}


//*******************************************************************
// Function Name : OnBnClickedBtnReqBalanceNext
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedBtnReqBalanceNext()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5919Q41";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName1 = "OTS5919Q41_in";	//�Է� ���ڵ��(���ҽ����� ����)
	CString strInRecName2 = "OTS5919Q41_in_sub01";	//�Է� ���ڵ��(���ҽ����� ����)

	CString strODRV_SELL_BUY_DCD = "0";	//�ؿ��Ļ��ŵ��ż������ڵ�(0:��ü, B:�ż�, S:�ŵ�)
	CString strCTNO;				//��ü���հ��¹�ȣ
	CString strAPNO;				//���»�ǰ��ȣ

	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdBalanceList = m_CommAgent.CreateRequestID();

	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//�ؿ��Ļ��ŵ��ż������ڵ�

	/*-------------------------------*
	[2] �Է� �Ǽ��� �Է��Ѵ�.
	*-------------------------------*/
	/*	REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
	ARRAY �� '0'���� ũ�� �Է��� �������̴�.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdBalanceList, strTrCode, strInRecName2, nInputCnt);
	
	CString strAccNo;
	CString strPrdt;
	CString strPWD;

	//[3] Tran��ȸ �Է°��� �Է��Ѵ�.
	for (int i = 0; i < nInputCnt; i++)
	{
		//���´�ü��ȣ�� ���´�.
		GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
		
		//���»�ǰ��ȣ
		GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strPrdt);
		strCTNO = GetAccAPNO(strAccNo + strPrdt); //���հ��´�ü��ȣ ��ȸ

		//���º�й�ȣ
		GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
		strPWD = m_CommAgent.GetEncrpyt(strPWD);

		//��ü���հ��¹�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "CTNO", strCTNO, i);

		//���»�ǰ��ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "APNO", strPrdt, i);

		//���º�й�ȣ
		m_CommAgent.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "PWD", strPWD, i);
	}

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "3";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if(m_CommAgent.RequestTran(m_nRqIdBalanceList, strTrCode, strBenefitAcc, strPreNext, m_strListBalanceNextRqKey, strScreenNo, "Q", 0) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}


//*******************************************************************
// Function Name : OnGetTranData
// Function      : Tran ��ȸ���� �̺�Ʈ
// Param         :	LONG nRequestId, ��ȸID
//					LPCTSTR pBlock, ��ȸ���� ������ ��
//					long nBlockLength ��ȸ���� ������ �� ũ��
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
{
	/* ���� : OnGetTranData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
	�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/

	CString strTrCode = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::TranCode);

	/*	0 : ������ȸ �̻��,		1 : ���� ������ ����,	2 : ���� ������ ����
		3 : ����/���� ������ ����	*/
	CString strPreNext = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::PrevNextCode);

	//������ȸŰ
	CString strPreNextContext = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::PrevNextKey);

	//��ȸ���� �޽����ڵ�
	CString strMsgCode = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::MsgCode);

	//��ȸ���� �޽���
	CString strMsg = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::Msg);

	//��ȸ���� �ΰ��޽����ڵ�
	CString strSubMsgCode = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::SubMsgCode);

	//��ȸ���� �ΰ��޽���
	CString strSubMsg = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::SubMsg);

	//��������( "1" : ����, "0" : ����)
	CString strIsError = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::Error);

	CString strErrMsg = m_CommAgent.GetLastErrMsg();

	CString strOutRecName;
	int nRowCnt = 0;

	/*---------------------------------------------
		��� �޽���
	 ---------------------------------------------*/
	if (!strErrMsg.IsEmpty())
		GetDlgItem(IDC_TRAN_MSG)->SetWindowText(strErrMsg);
	else
		GetDlgItem(IDC_TRAN_MSG)->SetWindowText(strMsg);

	//�ֹ���ü�᳻��
	if (nRequestId == m_nRqIdNonExecList)
	{
		CString strBSN_DT, strCANO, strODRV_ODNO, strPRDT_CD, strODRV_OR_ODNO, strODRV_MO_ODNO, strORDR_GRUP_NO;
		CString strORDR_DT, strCUST_NM, strSELL_BUY_DCD, strODRV_ORDR_PRC, strORDR_QNT, strRVSE_QNT, strCNCL_QNT;
		CString strCNCS_QNT, strRMN_QNT, strPRC_CND_DCD, strCNCS_CND_DCD, strSQ1_APPN_PRC, strAVR_CNCS_PRC, strCNCS_RT;
		CString strNOW_PRC, strMDIA_DCD, strORDR_DCD, strORDR_STTS_DCD, strFCM_ODNO, strUSER_ID, strATHZ_IP_ADDR;
		CString strACPT_TM, strCNCS_TM, strACPL_ACPT_TM, strACPL_CNCS_TM, strCRRY_CD;

		m_listNonExec.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;

		/*--------------------------------------
		���� ��ȸ ������ �����̸� ������ ���� ����Ÿ �ڿ�
		�ٿ� �����Ѵ�.
		---------------------------------------*/
		int nViewScrollPos = 0;
		if (!m_strListExecNextRqKey.IsEmpty())
		{
			nListIndex = m_listNonExec.GetItemCount();
			nViewScrollPos = nListIndex;
		}

		strOutRecName = "OTS5911Q41_out_sub01";

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, strOutRecName);
		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strBSN_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "BSN_DT", nRow);		//��������
			strCANO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CANO", nRow);		//���հ��¹�ȣ
			strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_ODNO", nRow);		//�ؿ��Ļ��ֹ���ȣ
			strPRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRDT_CD", nRow);		//��ǰ�ڵ�
			strODRV_OR_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_OR_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
			strODRV_MO_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_MO_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
			strORDR_GRUP_NO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_GRUP_NO", nRow);		//�ֹ��׷��ȣ
			strORDR_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DT", nRow);		//�ֹ�����
			strCUST_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CUST_NM", nRow);		//����
			strSELL_BUY_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SELL_BUY_DCD", nRow);		//�ŵ��ż������ڵ�
			strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_ORDR_PRC", nRow);		//�ؿ��Ļ��ֹ�����
			strORDR_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_QNT", nRow);		//�ֹ�����
			strRVSE_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "RVSE_QNT", nRow);		//��������
			strCNCL_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCL_QNT", nRow);		//��Ҽ���
			strCNCS_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT", nRow);		//ü�����
			strRMN_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "RMN_QNT", nRow);		//�ܿ�����
			strPRC_CND_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRC_CND_DCD", nRow);		//�������Ǳ����ڵ�
			strCNCS_CND_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_CND_DCD", nRow);		//ü�����Ǳ����ڵ�
			strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SQ1_APPN_PRC", nRow);		//1����������
			strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "AVR_CNCS_PRC", nRow);		//���ü�ᰡ��
			strCNCS_RT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_RT", nRow);		//ü����
			strNOW_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "NOW_PRC", nRow);		//���簡��
			strMDIA_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "MDIA_DCD", nRow);		//��ü�����ڵ�
			strORDR_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DCD", nRow);		//�ֹ������ڵ�
			strORDR_STTS_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_STTS_DCD", nRow);		//�ֹ����±����ڵ�
			strFCM_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "FCM_ODNO", nRow);		//FCM�ֹ���ȣ
			strUSER_ID = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "USER_ID", nRow);		//�����ID
			strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ATHZ_IP_ADDR", nRow);		//����IP�ּ�
			strACPT_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ACPT_TM", nRow);		//�����ð�
			strCNCS_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_TM", nRow);		//ü��ð�
			strACPL_ACPT_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ACPL_ACPT_TM", nRow);		//���������ð�
			strACPL_CNCS_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ACPL_CNCS_TM", nRow);		//����ü��ð�
			strCRRY_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CRRY_CD", nRow);		//��ȭ�ڵ�

			strBSN_DT.Trim();		//��������
			strCANO.Trim();		//���հ��¹�ȣ
			strODRV_ODNO.Trim();		//�ؿ��Ļ��ֹ���ȣ
			strPRDT_CD.Trim();		//��ǰ�ڵ�
			strODRV_OR_ODNO.Trim();		//�ؿ��Ļ����ֹ���ȣ
			strODRV_MO_ODNO.Trim();		//�ؿ��Ļ����ֹ���ȣ
			strORDR_GRUP_NO.Trim();		//�ֹ��׷��ȣ
			strORDR_DT.Trim();		//�ֹ�����
			strCUST_NM.Trim();		//����
			strSELL_BUY_DCD.Trim();		//�ŵ��ż������ڵ�
			NumericString(strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
			NumericString(strORDR_QNT);		//�ֹ�����
			NumericString(strRVSE_QNT);		//��������
			NumericString(strCNCL_QNT);		//��Ҽ���
			NumericString(strCNCS_QNT);		//ü�����
			NumericString(strRMN_QNT);		//�ܿ�����
			strPRC_CND_DCD.Trim();		//�������Ǳ����ڵ�
			strCNCS_CND_DCD.Trim();		//ü�����Ǳ����ڵ�
			NumericString(strSQ1_APPN_PRC);		//1����������
			NumericString(strAVR_CNCS_PRC);		//���ü�ᰡ��
			NumericString(strCNCS_RT);		//ü����
			NumericString(strNOW_PRC);		//���簡��
			strMDIA_DCD.Trim();		//��ü�����ڵ�
			strORDR_DCD.Trim();		//�ֹ������ڵ�
			strORDR_STTS_DCD.Trim();		//�ֹ����±����ڵ�
			strFCM_ODNO.Trim();		//FCM�ֹ���ȣ
			strUSER_ID.Trim();		//�����ID
			strATHZ_IP_ADDR.Trim();		//����IP�ּ�
			strACPT_TM.Trim();		//�����ð�
			strCNCS_TM.Trim();		//ü��ð�
			strACPL_ACPT_TM.Trim();		//���������ð�
			strACPL_CNCS_TM.Trim();		//����ü��ð�
			strCRRY_CD.Trim();		//��ȭ�ڵ�

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listNonExec.InsertItem(&lvItem);

			m_listNonExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strBSN_DT);		//��������
			m_listNonExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strCANO);		//���հ��¹�ȣ
			m_listNonExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strODRV_ODNO);		//�ؿ��Ļ��ֹ���ȣ
			m_listNonExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strPRDT_CD);		//��ǰ�ڵ�
			m_listNonExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
			m_listNonExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strODRV_MO_ODNO);		//�ؿ��Ļ����ֹ���ȣ
			m_listNonExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strORDR_GRUP_NO);		//�ֹ��׷��ȣ
			m_listNonExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strORDR_DT);		//�ֹ�����
			m_listNonExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strCUST_NM);		//����
			m_listNonExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strSELL_BUY_DCD);		//�ŵ��ż������ڵ�
			m_listNonExec.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
			m_listNonExec.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strORDR_QNT);		//�ֹ�����
			m_listNonExec.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strRVSE_QNT);		//��������
			m_listNonExec.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strCNCL_QNT);		//��Ҽ���
			m_listNonExec.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strCNCS_QNT);		//ü�����
			m_listNonExec.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strRMN_QNT);		//�ܿ�����
			m_listNonExec.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strPRC_CND_DCD);		//�������Ǳ����ڵ�
			m_listNonExec.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strCNCS_CND_DCD);		//ü�����Ǳ����ڵ�
			m_listNonExec.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strSQ1_APPN_PRC);		//1����������
			m_listNonExec.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strAVR_CNCS_PRC);		//���ü�ᰡ��
			m_listNonExec.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strCNCS_RT);		//ü����
			m_listNonExec.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strNOW_PRC);		//���簡��
			m_listNonExec.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strMDIA_DCD);		//��ü�����ڵ�
			m_listNonExec.SetItemText(nListIndex, 23, (LPTSTR)(LPCTSTR)strORDR_DCD);		//�ֹ������ڵ�
			m_listNonExec.SetItemText(nListIndex, 24, (LPTSTR)(LPCTSTR)strORDR_STTS_DCD);		//�ֹ����±����ڵ�
			m_listNonExec.SetItemText(nListIndex, 25, (LPTSTR)(LPCTSTR)strFCM_ODNO);		//FCM�ֹ���ȣ
			m_listNonExec.SetItemText(nListIndex, 26, (LPTSTR)(LPCTSTR)strUSER_ID);		//�����ID
			m_listNonExec.SetItemText(nListIndex, 27, (LPTSTR)(LPCTSTR)strATHZ_IP_ADDR);		//����IP�ּ�
			m_listNonExec.SetItemText(nListIndex, 28, (LPTSTR)(LPCTSTR)strACPT_TM);		//�����ð�
			m_listNonExec.SetItemText(nListIndex, 29, (LPTSTR)(LPCTSTR)strCNCS_TM);		//ü��ð�
			m_listNonExec.SetItemText(nListIndex, 30, (LPTSTR)(LPCTSTR)strACPL_ACPT_TM);		//���������ð�
			m_listNonExec.SetItemText(nListIndex, 31, (LPTSTR)(LPCTSTR)strACPL_CNCS_TM);		//����ü��ð�
			m_listNonExec.SetItemText(nListIndex, 32, (LPTSTR)(LPCTSTR)strCRRY_CD);		//��ȭ�ڵ�

		}//End of for

		m_listNonExec.EnsureVisible(nViewScrollPos, FALSE);
		m_listNonExec.SetRedraw(TRUE);

		/*--------------------------------------
		������ȸŰ�� ������ ���´�.
		---------------------------------------*/
		m_strListNonExecNextRqKey = strPreNextContext;

		/*--------------------------------------
		������ȸŰ�� '2', '3'�̸� '����'��ư�� Ȱ��ȭ ��Ų��.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_NON_EXEC_LIST_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_NON_EXEC_LIST_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdNonExecList = 0;	//�ֹ�ü����ȸ Rq ID

	}
	//�ֹ�ü�᳻�� ��ȸ
	else if (nRequestId == m_nRqIdExecList)
	{
		CString strCANO, strODRV_ODNO, strPRDT_CD, strODRV_OR_ODNO, strODRV_MO_ODNO, strORDR_GRUP_NO;
		CString strORDR_DT, strACNT_PRDT_CD, strCUST_NM, strSELL_BUY_DCD, strODRV_ORDR_PRC, strORDR_QNT,strRVSE_QNT;
		CString strCNCL_QNT, strCNCS_QNT, strRMN_QNT, strPRC_CND_DCD, strCNCS_CND_DCD, strSQ1_APPN_PRC, strAVR_CNCS_PRC;
		CString strCNCS_RT, strNOW_PRC, strMDIA_DCD, strORDR_DCD, strORDR_STTS_DCD, strFCM_ODNO, strUSER_ID;
		CString strATHZ_IP_ADDR, strACPT_TM, strCNCS_TM, strACPL_ACPT_TM, strCNCS_DETL_DTM, strCRRY_CD;

		m_listExec.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;

		/*--------------------------------------
		���� ��ȸ ������ �����̸� ������ ���� ����Ÿ �ڿ�
		�ٿ� �����Ѵ�.
		---------------------------------------*/
		int nViewScrollPos = 0;
		if (!m_strListExecNextRqKey.IsEmpty())
		{
			nListIndex = m_listExec.GetItemCount();
			nViewScrollPos = nListIndex;
		}

		strOutRecName = "OTS5911Q52_out_sub01";

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, strOutRecName);
		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strCANO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CANO", nRow);		//���հ��¹�ȣ
			strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_ODNO", nRow);		//�ؿ��Ļ��ֹ���ȣ
			strPRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRDT_CD", nRow);		//��ǰ�ڵ�
			strODRV_OR_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_OR_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
			strODRV_MO_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_MO_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
			strORDR_GRUP_NO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_GRUP_NO", nRow);		//�ֹ��׷��ȣ
			strORDR_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DT", nRow);		//�ֹ�����
			strACNT_PRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ACNT_PRDT_CD", nRow);		//���»�ǰ�ڵ�
			strCUST_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CUST_NM", nRow);		//����
			strSELL_BUY_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SELL_BUY_DCD", nRow);		//�ŵ��ż������ڵ�
			strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_ORDR_PRC", nRow);		//�ؿ��Ļ��ֹ�����
			strORDR_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_QNT", nRow);		//�ֹ�����
			strRVSE_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "RVSE_QNT", nRow);		//��������
			strCNCL_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCL_QNT", nRow);		//��Ҽ���
			strCNCS_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT", nRow);		//ü�����
			strRMN_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "RMN_QNT", nRow);		//�ܿ�����
			strPRC_CND_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRC_CND_DCD", nRow);		//�������Ǳ����ڵ�
			strCNCS_CND_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_CND_DCD", nRow);		//ü�����Ǳ����ڵ�
			strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SQ1_APPN_PRC", nRow);		//1����������
			strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "AVR_CNCS_PRC", nRow);		//���ü�ᰡ��
			strCNCS_RT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_RT", nRow);		//ü����
			strNOW_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "NOW_PRC", nRow);		//���簡��
			strMDIA_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "MDIA_DCD", nRow);		//��ü�����ڵ�
			strORDR_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DCD", nRow);		//�ֹ������ڵ�
			strORDR_STTS_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_STTS_DCD", nRow);		//�ֹ����±����ڵ�
			strFCM_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "FCM_ODNO", nRow);		//FCM�ֹ���ȣ
			strUSER_ID = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "USER_ID", nRow);		//�����ID
			strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ATHZ_IP_ADDR", nRow);		//����IP�ּ�
			strACPT_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ACPT_TM", nRow);		//�����ð�
			strCNCS_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_TM", nRow);		//ü��ð�
			strACPL_ACPT_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ACPL_ACPT_TM", nRow);		//���������ð�
			strCNCS_DETL_DTM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_DETL_DTM", nRow);		//ü����Ͻ�
			strCRRY_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CRRY_CD", nRow);		//��ȭ�ڵ�

			strCANO.Trim();		//���հ��¹�ȣ
			strODRV_ODNO.Trim();		//�ؿ��Ļ��ֹ���ȣ
			strPRDT_CD.Trim();		//��ǰ�ڵ�
			strODRV_OR_ODNO.Trim();		//�ؿ��Ļ����ֹ���ȣ
			strODRV_MO_ODNO.Trim();		//�ؿ��Ļ����ֹ���ȣ
			strORDR_GRUP_NO.Trim();		//�ֹ��׷��ȣ
			strORDR_DT.Trim();		//�ֹ�����
			strACNT_PRDT_CD.Trim();		//���»�ǰ�ڵ�
			strCUST_NM.Trim();		//����
			strSELL_BUY_DCD.Trim();		//�ŵ��ż������ڵ�
			NumericString(strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
			NumericString(strORDR_QNT);		//�ֹ�����
			NumericString(strRVSE_QNT);		//��������
			NumericString(strCNCL_QNT);		//��Ҽ���
			NumericString(strCNCS_QNT);		//ü�����
			NumericString(strRMN_QNT);		//�ܿ�����
			strPRC_CND_DCD.Trim();		//�������Ǳ����ڵ�
			strCNCS_CND_DCD.Trim();		//ü�����Ǳ����ڵ�
			NumericString(strSQ1_APPN_PRC);		//1����������
			NumericString(strAVR_CNCS_PRC);		//���ü�ᰡ��
			NumericString(strCNCS_RT);		//ü����
			NumericString(strNOW_PRC);		//���簡��
			strMDIA_DCD.Trim();		//��ü�����ڵ�
			strORDR_DCD.Trim();		//�ֹ������ڵ�
			strORDR_STTS_DCD.Trim();		//�ֹ����±����ڵ�
			strFCM_ODNO.Trim();		//FCM�ֹ���ȣ
			strUSER_ID.Trim();		//�����ID
			strATHZ_IP_ADDR.Trim();		//����IP�ּ�
			strACPT_TM.Trim();		//�����ð�
			strCNCS_TM.Trim();		//ü��ð�
			strACPL_ACPT_TM.Trim();		//���������ð�
			strCNCS_DETL_DTM.Trim();		//ü����Ͻ�
			strCRRY_CD.Trim();		//��ȭ�ڵ�

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listExec.InsertItem(&lvItem);

			m_listExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strCANO);		//���հ��¹�ȣ
			m_listExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strODRV_ODNO);		//�ؿ��Ļ��ֹ���ȣ
			m_listExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strPRDT_CD);		//��ǰ�ڵ�
			m_listExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
			m_listExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strODRV_MO_ODNO);		//�ؿ��Ļ����ֹ���ȣ
			m_listExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strORDR_GRUP_NO);		//�ֹ��׷��ȣ
			m_listExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strORDR_DT);		//�ֹ�����
			m_listExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strACNT_PRDT_CD);		//���»�ǰ�ڵ�
			m_listExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strCUST_NM);		//����
			m_listExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strSELL_BUY_DCD);		//�ŵ��ż������ڵ�
			m_listExec.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
			m_listExec.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strORDR_QNT);		//�ֹ�����
			m_listExec.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strRVSE_QNT);		//��������
			m_listExec.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strCNCL_QNT);		//��Ҽ���
			m_listExec.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strCNCS_QNT);		//ü�����
			m_listExec.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strRMN_QNT);		//�ܿ�����
			m_listExec.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strPRC_CND_DCD);		//�������Ǳ����ڵ�
			m_listExec.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strCNCS_CND_DCD);		//ü�����Ǳ����ڵ�
			m_listExec.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strSQ1_APPN_PRC);		//1����������
			m_listExec.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strAVR_CNCS_PRC);		//���ü�ᰡ��
			m_listExec.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strCNCS_RT);		//ü����
			m_listExec.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strNOW_PRC);		//���簡��
			m_listExec.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strMDIA_DCD);		//��ü�����ڵ�
			m_listExec.SetItemText(nListIndex, 23, (LPTSTR)(LPCTSTR)strORDR_DCD);		//�ֹ������ڵ�
			m_listExec.SetItemText(nListIndex, 24, (LPTSTR)(LPCTSTR)strORDR_STTS_DCD);		//�ֹ����±����ڵ�
			m_listExec.SetItemText(nListIndex, 25, (LPTSTR)(LPCTSTR)strFCM_ODNO);		//FCM�ֹ���ȣ
			m_listExec.SetItemText(nListIndex, 26, (LPTSTR)(LPCTSTR)strUSER_ID);		//�����ID
			m_listExec.SetItemText(nListIndex, 27, (LPTSTR)(LPCTSTR)strATHZ_IP_ADDR);		//����IP�ּ�
			m_listExec.SetItemText(nListIndex, 28, (LPTSTR)(LPCTSTR)strACPT_TM);		//�����ð�
			m_listExec.SetItemText(nListIndex, 29, (LPTSTR)(LPCTSTR)strCNCS_TM);		//ü��ð�
			m_listExec.SetItemText(nListIndex, 30, (LPTSTR)(LPCTSTR)strACPL_ACPT_TM);		//���������ð�
			m_listExec.SetItemText(nListIndex, 31, (LPTSTR)(LPCTSTR)strCNCS_DETL_DTM);		//ü����Ͻ�
			m_listExec.SetItemText(nListIndex, 32, (LPTSTR)(LPCTSTR)strCRRY_CD);		//��ȭ�ڵ�
		}//End of for

		m_listExec.EnsureVisible(nViewScrollPos, FALSE);
		m_listExec.SetRedraw(TRUE);
		
		/*--------------------------------------
		������ȸŰ�� ������ ���´�.
		---------------------------------------*/
		m_strListExecNextRqKey = strPreNextContext;

		/*--------------------------------------
		������ȸŰ�� '2', '3'�̸� '����'��ư�� Ȱ��ȭ ��Ų��.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_EXEC_LIST_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_EXEC_LIST_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdExecList = 0;	//�ֹ�ü����ȸ Rq ID

	}
	//���¸�� ��ȸ
	else if (m_nRqIdAccNoList == nRequestId)
	{
		CString strfunc, strusid, strerrc, stremsg, strnrec, straccn, strsub_accn;
		CString stracnm, strachk, strpwch;

		strfunc = m_CommAgent.GetTranOutputData(strTrCode, "OutRec1", "func", 0);		//��ɱ����ڵ�
		strusid = m_CommAgent.GetTranOutputData(strTrCode, "OutRec1", "usid", 0);		//����ھ��̵�
		strerrc = m_CommAgent.GetTranOutputData(strTrCode, "OutRec1", "errc", 0);		//�����ڵ�
		stremsg = m_CommAgent.GetTranOutputData(strTrCode, "OutRec1", "emsg", 0);		//�����޽���
		strnrec = m_CommAgent.GetTranOutputData(strTrCode, "OutRec1", "nrec", 0);		//��°Ǽ�
		
		m_listAccNo.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OutRec2");

		CString strAccNo;
		CString strPrdt;

		m_arrAccNo.RemoveAll();		//���հ��¹�ȣ
		m_arrAccAPNO.RemoveAll();	//���հ��´�ü��ȣ

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			straccn = m_CommAgent.GetTranOutputData(strTrCode, "OutRec2", "accn", nRow);		//���¹�ȣ
			strsub_accn = m_CommAgent.GetTranOutputData(strTrCode, "OutRec2", "sub_accn", nRow);		//��ü���¹�ȣ
			stracnm = m_CommAgent.GetTranOutputData(strTrCode, "OutRec2", "acnm", nRow);		//���¸�
			strachk = m_CommAgent.GetTranOutputData(strTrCode, "OutRec2", "achk", nRow);		//����Ư��
			strpwch = m_CommAgent.GetTranOutputData(strTrCode, "OutRec2", "pwch", nRow);		//���࿬����¿���

			straccn.Trim();
			strsub_accn.Trim();
			stracnm.Trim();
			strachk.Trim();
			strpwch.Trim();

			strAccNo = straccn.Mid(0, 8);
			strPrdt = straccn.Mid(8, 3);

			m_arrAccNo.Add(strAccNo);		//���հ��¹�ȣ
			m_arrAccAPNO.Add(strsub_accn);	//���հ��´�ü��ȣ

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listAccNo.InsertItem(&lvItem);

			m_listAccNo.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strAccNo);
			m_listAccNo.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strsub_accn);
			m_listAccNo.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strPrdt);
			m_listAccNo.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)stracnm);
			m_listAccNo.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strachk);
			m_listAccNo.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strpwch);
			nListIndex++;
		}

		m_listAccNo.EnsureVisible(0, FALSE);
		m_listAccNo.SetRedraw(TRUE);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdAccNoList = 0;	//���¸��
	}
	//���¸�� ��ȸ
	else if (m_nRqIdFDemoAccNoList == nRequestId)
	{
		CString strCTNO;		//���հ��´�ü��ȣ
		CString strCANO;		//���հ��¹�ȣ
		CString strAPNO;		//���»�ǰ��ȣ
		CString strCUST_NM;		//����

		m_listAccNo.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OTS5991Q03_out_sub01");

		m_arrAccNo.RemoveAll();			//���¸��
		m_arrAccAPNO.RemoveAll();		//���հ��´�ü��ȣ���

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strCTNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CTNO", nRow);		//����
			strCANO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
			strAPNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "APNO", nRow);		//���»�ǰ��ȣ
			strCUST_NM = m_CommAgent.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CUST_NM", nRow);		//����

			strCTNO.Trim();
			strCANO.Trim();
			strAPNO.Trim();
			strCUST_NM.Trim();

			m_arrAccNo.Add(strCANO);		//���հ��¹�ȣ
			m_arrAccAPNO.Add(strCTNO);		//���հ��´�ü��ȣ

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listAccNo.InsertItem(&lvItem);

			m_listAccNo.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strCANO);
			m_listAccNo.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strCTNO);
			m_listAccNo.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strAPNO);
			m_listAccNo.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strCUST_NM);
			nListIndex++;
		}

		m_listAccNo.EnsureVisible(0, FALSE);
		m_listAccNo.SetRedraw(TRUE);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdFDemoAccNoList = 0;	//�ؿܼ���������¸���Ʈ
	}
	//������ ��ȸ
	else if (m_nRqIdDepositList == nRequestId)
	{
		CString strCRRY_CD, strODRV_STDR_EXRT_CTNS, strBFDT_CSH_BLCE_CTNS, strODRV_CSH_RCTM_AMT_CTNS;
		CString strODRV_CSH_DRWG_AMT_CTNS, strODRV_CLR_PFLS_AMT_CTNS, strODRV_OPT_SELL_AMT_CTNS;
		CString strODRV_OPT_BUY_AMT_CTNS, strODRV_FEE_CTNS, strTHDT_CSH_BLCE_CTNS, strODRV_EVL_PFLS_AMT_CTNS;
		CString strEVL_DPST_AMT_CTNS, strODRV_OPT_EVL_AMT_CTNS, strTOT_ACC_ASST_VALU_AMT_CTNS;
		CString strOPNG_WMY_CTNS, strODRV_ORDR_WMY_CTNS, strODRV_MNTN_WMY_CTNS, strWMY_LACK_AMT_CTNS, strODRV_WDRW_PSBL_AMT_CTNS;
		CString strECHM_PSBL_AMT_CTNS, strODRV_ORDR_PSBL_AMT_CTNS, strODRV_ADIT_WMY_CTNS, strRCVB_OVDU_INTR_CTNS;

		m_listDeposit.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;
		/*--------------------------------------
		���� ��ȸ ������ �����̸� ������ ���� ����Ÿ �ڿ�
		�ٿ� �����Ѵ�.
		---------------------------------------*/
		int nViewScrollPos = 0;
		if (!m_strListDepositNextRqKey.IsEmpty())
		{
			nListIndex = m_listDeposit.GetItemCount();
			nViewScrollPos = nListIndex;
		}

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OTS5943Q01_out_sub01");

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strCRRY_CD = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
			strODRV_STDR_EXRT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_STDR_EXRT_CTNS", nRow);			//�ؿ��Ļ�����ȯ������
			strBFDT_CSH_BLCE_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "BFDT_CSH_BLCE_CTNS", nRow);			// ���������ܾ׳���
			strODRV_CSH_RCTM_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "BFDT_CSH_BLCE_CTNS", nRow);		//�ؿ��Ļ������Աݱݾ׳���
			strODRV_CSH_DRWG_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_CSH_DRWG_AMT_CTNS", nRow);		//�ؿ��Ļ�������ݱݾ׳���
			strODRV_CLR_PFLS_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_CLR_PFLS_AMT_CTNS", nRow);		//�ؿ��Ļ�û����ͱݾ׳���
			strODRV_OPT_SELL_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_OPT_SELL_AMT_CTNS", nRow);		//�ؿ��Ļ��ɼǸŵ��ݾ׳���
			strODRV_OPT_BUY_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_OPT_BUY_AMT_CTNS", nRow);		//�ؿ��Ļ��ɼǸż��ݾ׳���
			strODRV_FEE_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_FEE_CTNS", nRow);				//�ؿ��Ļ������᳻��
			strTHDT_CSH_BLCE_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "THDT_CSH_BLCE_CTNS", nRow);			//���������ܾ׳���
			strODRV_EVL_PFLS_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_EVL_PFLS_AMT_CTNS", nRow);		//�ؿ��Ļ��򰡼��ͱݾ׳���
			strEVL_DPST_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "EVL_DPST_AMT_CTNS", nRow);			//�򰡿�Ź�ݾ׳���
			strODRV_OPT_EVL_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_OPT_EVL_AMT_CTNS", nRow);		//�ؿ��Ļ��ɼ��򰡱ݾ׳���
			strTOT_ACC_ASST_VALU_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "TOT_ACC_ASST_VALU_AMT_CTNS", nRow);	//�Ѱ����ڻ갡ġ�ݾ׳���
			strOPNG_WMY_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "OPNG_WMY_CTNS", nRow);				//�������űݳ���
			strODRV_ORDR_WMY_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_ORDR_WMY_CTNS", nRow);			//�ؿ��Ļ��ֹ����űݳ���
			strODRV_MNTN_WMY_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_MNTN_WMY_CTNS", nRow);			//�ؿ��Ļ��������űݳ���
			strWMY_LACK_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "WMY_LACK_AMT_CTNS", nRow);			//���űݺ����ݾ׳���
			strODRV_WDRW_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_WDRW_PSBL_AMT_CTNS", nRow);		//�ؿ��Ļ����Ⱑ�ɱݾ׳���
			strECHM_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ECHM_PSBL_AMT_CTNS", nRow);			//ȯ�����ɱݾ׳���
			strODRV_ORDR_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_ORDR_PSBL_AMT_CTNS", nRow);		//�ؿ��Ļ��ֹ����ɱݾ׳���
			strODRV_ADIT_WMY_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_ADIT_WMY_CTNS", nRow);			//�ؿ��Ļ��߰����űݳ���
			strRCVB_OVDU_INTR_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "RCVB_OVDU_INTR_CTNS", nRow);			//�̼���ü���ڳ���

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listDeposit.InsertItem(&lvItem);

			strCRRY_CD.Trim();
			NumericString(strODRV_STDR_EXRT_CTNS);
			NumericString(strBFDT_CSH_BLCE_CTNS);
			NumericString(strODRV_CSH_RCTM_AMT_CTNS);
			NumericString(strODRV_CSH_DRWG_AMT_CTNS);
			NumericString(strODRV_CLR_PFLS_AMT_CTNS);
			NumericString(strODRV_OPT_SELL_AMT_CTNS);
			NumericString(strODRV_OPT_BUY_AMT_CTNS);
			NumericString(strODRV_FEE_CTNS);
			NumericString(strTHDT_CSH_BLCE_CTNS);
			NumericString(strODRV_EVL_PFLS_AMT_CTNS);
			NumericString(strEVL_DPST_AMT_CTNS);
			NumericString(strODRV_OPT_EVL_AMT_CTNS);
			NumericString(strTOT_ACC_ASST_VALU_AMT_CTNS);
			NumericString(strOPNG_WMY_CTNS);
			NumericString(strODRV_ORDR_WMY_CTNS);
			NumericString(strODRV_MNTN_WMY_CTNS);
			NumericString(strWMY_LACK_AMT_CTNS);
			NumericString(strODRV_WDRW_PSBL_AMT_CTNS);
			NumericString(strECHM_PSBL_AMT_CTNS);
			NumericString(strODRV_ORDR_PSBL_AMT_CTNS);
			NumericString(strODRV_ADIT_WMY_CTNS);
			NumericString(strRCVB_OVDU_INTR_CTNS);

			m_listDeposit.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strCRRY_CD);
			m_listDeposit.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strODRV_STDR_EXRT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strBFDT_CSH_BLCE_CTNS);
			m_listDeposit.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strODRV_CSH_RCTM_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strODRV_CSH_DRWG_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strODRV_CLR_PFLS_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strODRV_OPT_SELL_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strODRV_OPT_BUY_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strODRV_FEE_CTNS);
			m_listDeposit.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strTHDT_CSH_BLCE_CTNS);
			m_listDeposit.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strODRV_EVL_PFLS_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strEVL_DPST_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strODRV_OPT_EVL_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strTOT_ACC_ASST_VALU_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strOPNG_WMY_CTNS);
			m_listDeposit.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strODRV_ORDR_WMY_CTNS);
			m_listDeposit.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strODRV_MNTN_WMY_CTNS);
			m_listDeposit.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strWMY_LACK_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strODRV_WDRW_PSBL_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strECHM_PSBL_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strODRV_ORDR_PSBL_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strODRV_ADIT_WMY_CTNS);
			m_listDeposit.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strRCVB_OVDU_INTR_CTNS);

			nListIndex++;
		}

		m_listDeposit.EnsureVisible(0, FALSE);
		m_listDeposit.SetRedraw(TRUE);

		/*--------------------------------------
		������ȸŰ�� ������ ���´�.
		---------------------------------------*/
		m_strListDepositNextRqKey = strPreNextContext;

		/*--------------------------------------
		������ȸŰ�� '2', '3'�̸� '����'��ư�� Ȱ��ȭ ��Ų��.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_DEPOSIT_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_DEPOSIT_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdDepositList = 0;	//������

	}//End of if
	//�ܰ� ��ȸ
	else if (m_nRqIdBalanceList == nRequestId)
	{
		CString strCANO, strCTNO, strAPNO, strCUST_NM, strPRDT_CD, strPRDT_NM, strODRV_SELL_BUY_DCD;
		CString strUSTL_CTRC_QNT, strTRDE_AVR_UNPR, strCLR_PSBL_QNT, strORDR_RMN_QNT, strODRV_NOW_PRC;
		CString strODRV_BFDT_PRPT, strODRV_BFDT_PRPT_RT, strODRV_EVL_AMT, strODRV_EVL_PFLS_AMT;
		CString strODRV_PFLS_RT, strUSTL_CTRC_AMT, strTRSL_MLT, strODRV_FTOP_DCD, strCRRY_CD;
		CString strMNGM_BDCD, strMNGM_BR_NM, strMNGM_EMPNO, strMNGR_NM, strPRC_DCPN_BLW_LNG;
		CString strINDC_PRC, strBSN_DT;

		m_listBalance.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;
		/*--------------------------------------
		���� ��ȸ ������ �����̸� ������ ���� ����Ÿ �ڿ�
		�ٿ� �����Ѵ�.
		---------------------------------------*/
		int nViewScrollPos = 0;
		if (!m_strListBalanceNextRqKey.IsEmpty())
		{
			nListIndex = m_listBalance.GetItemCount();
			nViewScrollPos = nListIndex;
		}

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OTS5919Q41_out_sub01");

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strCANO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
			strCTNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CTNO", nRow);		//��ü���հ��¹�ȣ
			strAPNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "APNO", nRow);		//���»�ǰ��ȣ
			strCUST_NM = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CUST_NM", nRow);		//����
			strPRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
			strPRDT_NM = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "PRDT_NM", nRow);		//��ǰ��
			strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//�ؿ��Ļ��ŵ��ż������ڵ�
			strUSTL_CTRC_QNT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "USTL_CTRC_QNT", nRow);		//�̰�����������
			strTRDE_AVR_UNPR = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "TRDE_AVR_UNPR", nRow);		//�Ÿ���մܰ�
			strCLR_PSBL_QNT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CLR_PSBL_QNT", nRow);		//û�갡�ɼ���
			strORDR_RMN_QNT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
			strODRV_NOW_PRC = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_NOW_PRC", nRow);		//�ؿ��Ļ����簡��
			strODRV_BFDT_PRPT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_BFDT_PRPT", nRow);		//�ؿ��Ļ����ϴ��
			strODRV_BFDT_PRPT_RT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_BFDT_PRPT_RT", nRow);		//�ؿ��Ļ����ϴ����
			strODRV_EVL_AMT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_EVL_AMT", nRow);		//�ؿ��Ļ��򰡱ݾ�
			strODRV_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_EVL_PFLS_AMT", nRow);		//�ؿ��Ļ��򰡼��ͱݾ�
			strODRV_PFLS_RT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_PFLS_RT", nRow);		//�ؿ��Ļ�������
			strUSTL_CTRC_AMT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "USTL_CTRC_AMT", nRow);		//�̰��������ݾ�
			strTRSL_MLT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "TRSL_MLT", nRow);		//ȯ��¼�
			strODRV_FTOP_DCD = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_FTOP_DCD", nRow);		//�ؿ��Ļ������ɼǱ����ڵ�
			strCRRY_CD = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
			strMNGM_BDCD = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "MNGM_BDCD", nRow);		//���������ڵ�
			strMNGM_BR_NM = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "MNGM_BR_NM", nRow);		//����������
			strMNGM_EMPNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "MNGM_EMPNO", nRow);		//���������ȣ
			strMNGR_NM = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "MNGR_NM", nRow);		//�����ڸ�
			strPRC_DCPN_BLW_LNG = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "PRC_DCPN_BLW_LNG", nRow);		//���ݼҼ������ϱ���
			strINDC_PRC = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "INDC_PRC", nRow);		//ǥ�ð���
			strBSN_DT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "BSN_DT", nRow);		//��������


			strCANO.Trim();
			strCTNO.Trim();
			strAPNO.Trim();
			strCUST_NM.Trim();
			strPRDT_CD.Trim();
			strPRDT_NM.Trim();
			strODRV_SELL_BUY_DCD.Trim();
			NumericString(strUSTL_CTRC_QNT);		//�̰�����������
			NumericString(strTRDE_AVR_UNPR);		//�Ÿ���մܰ�
			NumericString(strCLR_PSBL_QNT);		//û�갡�ɼ���
			NumericString(strORDR_RMN_QNT);		//�ֹ��ܿ�����
			NumericString(strODRV_NOW_PRC);		//�ؿ��Ļ����簡��
			NumericString(strODRV_BFDT_PRPT);		//�ؿ��Ļ����ϴ��
			NumericString(strODRV_BFDT_PRPT_RT);		//�ؿ��Ļ����ϴ����
			NumericString(strODRV_EVL_AMT);		//�ؿ��Ļ��򰡱ݾ�
			NumericString(strODRV_EVL_PFLS_AMT);		//�ؿ��Ļ��򰡼��ͱݾ�
			NumericString(strODRV_PFLS_RT);		//�ؿ��Ļ�������
			NumericString(strUSTL_CTRC_AMT);		//�̰��������ݾ�
			NumericString(strTRSL_MLT);		//ȯ��¼�
			strODRV_FTOP_DCD.Trim();		//�ؿ��Ļ������ɼǱ����ڵ�
			strCRRY_CD.Trim();		//��ȭ�ڵ�
			strMNGM_BDCD.Trim();		//���������ڵ�
			strMNGM_BR_NM.Trim();		//����������
			strMNGM_EMPNO.Trim();		//���������ȣ
			strMNGR_NM.Trim();		//�����ڸ�
			NumericString(strPRC_DCPN_BLW_LNG);		//���ݼҼ������ϱ���
			NumericString(strINDC_PRC);		//ǥ�ð���
			strBSN_DT.Trim();		//��������

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listBalance.InsertItem(&lvItem);

			m_listBalance.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strCANO);		//���հ��¹�ȣ
			m_listBalance.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strCTNO);		//��ü���հ��¹�ȣ
			m_listBalance.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strAPNO);		//���»�ǰ��ȣ
			m_listBalance.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strCUST_NM);		//����
			m_listBalance.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strPRDT_CD);		//��ǰ�ڵ�
			m_listBalance.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strPRDT_NM);		//��ǰ��
			m_listBalance.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strODRV_SELL_BUY_DCD);		//�ؿ��Ļ��ŵ��ż������ڵ�
			m_listBalance.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strUSTL_CTRC_QNT);		//�̰�����������
			m_listBalance.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strTRDE_AVR_UNPR);		//�Ÿ���մܰ�
			m_listBalance.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strCLR_PSBL_QNT);		//û�갡�ɼ���
			m_listBalance.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strORDR_RMN_QNT);		//�ֹ��ܿ�����
			m_listBalance.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strODRV_NOW_PRC);		//�ؿ��Ļ����簡��
			m_listBalance.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strODRV_BFDT_PRPT);		//�ؿ��Ļ����ϴ��
			m_listBalance.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strODRV_BFDT_PRPT_RT);		//�ؿ��Ļ����ϴ����
			m_listBalance.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strODRV_EVL_AMT);		//�ؿ��Ļ��򰡱ݾ�
			m_listBalance.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strODRV_EVL_PFLS_AMT);		//�ؿ��Ļ��򰡼��ͱݾ�
			m_listBalance.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strODRV_PFLS_RT);		//�ؿ��Ļ�������
			m_listBalance.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strUSTL_CTRC_AMT);		//�̰��������ݾ�
			m_listBalance.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strTRSL_MLT);		//ȯ��¼�
			m_listBalance.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strODRV_FTOP_DCD);		//�ؿ��Ļ������ɼǱ����ڵ�
			m_listBalance.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strCRRY_CD);		//��ȭ�ڵ�
			m_listBalance.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strMNGM_BDCD);		//���������ڵ�
			m_listBalance.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strMNGM_BR_NM);		//����������
			m_listBalance.SetItemText(nListIndex, 23, (LPTSTR)(LPCTSTR)strMNGM_EMPNO);		//���������ȣ
			m_listBalance.SetItemText(nListIndex, 24, (LPTSTR)(LPCTSTR)strMNGR_NM);		//�����ڸ�
			m_listBalance.SetItemText(nListIndex, 25, (LPTSTR)(LPCTSTR)strPRC_DCPN_BLW_LNG);		//���ݼҼ������ϱ���
			m_listBalance.SetItemText(nListIndex, 26, (LPTSTR)(LPCTSTR)strINDC_PRC);		//ǥ�ð���
			m_listBalance.SetItemText(nListIndex, 27, (LPTSTR)(LPCTSTR)strBSN_DT);		//��������

			nListIndex++;
		}

		m_listBalance.EnsureVisible(0, FALSE);
		m_listBalance.SetRedraw(TRUE);

		/*--------------------------------------
		������ȸŰ�� ������ ���´�.
		---------------------------------------*/
		m_strListBalanceNextRqKey = strPreNextContext;

		/*--------------------------------------
		������ȸŰ�� '2', '3'�̸� '����'��ư�� Ȱ��ȭ ��Ų��.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_BALANCE_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_BALANCE_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdBalanceList = 0;	//�ֹ�ü����ȸ Rq ID

	}
	//�ŵ��ֹ� Request ID
	else if (m_nRqIdSellOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U01_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdSellOrd = 0;
	}
	//�ż��ֹ� Request ID
	else if (m_nRqIdBuyOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U01_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdBuyOrd = 0;
	}
	//�����ֹ� Request ID
	else if (m_nRqIdChangeOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U02_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdChangeOrd = 0;
	}
	//����ֹ� Request ID
	else if (m_nRqIdCancelOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U03_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdCancelOrd = 0;
	}

	if (!strErrMsg.IsEmpty())
		::AfxMessageBox(strErrMsg);
}

//*******************************************************************
// Function Name : OnGetFidData
// Function      : FID ��ȸ���� �̺�Ʈ
// Param         :	LONG nRequestId, ��ȸID
//					LPCTSTR pBlock, ��ȸ���� ������ ��
//					long nBlockLength ��ȸ���� ������ �� ũ��
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
{
	/* ���� : OnGetFidData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
	�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/

	/*	0 : ������ȸ �̻��,		1 : ���� ������ ����,	2 : ���� ������ ����
		3 : ����/���� ������ ����	*/
	CString strPreNext = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::PrevNextCode);

	//������ȸŰ
	CString strPreNextContext = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::PrevNextKey);

	//��ȸ���� �޽����ڵ�
	CString strMsgCode = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::MsgCode);

	//��ȸ���� �޽���
	CString strMsg = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::Msg);

	//��������( "1" : ����, "0" : ����)
	CString strIsError = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::Error);

	CString strErrMsg = m_CommAgent.GetLastErrMsg();
	
	if (!strErrMsg.IsEmpty())
		::AfxMessageBox(strErrMsg);
}

//*******************************************************************
// Function Name : OnGetRealData
// Function      : �ǽð� �����͸� �����Ѵ�.
// Param         :	LPCTSTR strRealName : �ǽð� �ڵ��
//					LPCTSTR strRealKey : �ǽð� ���Ű
//					LPCTSTR pBlock, ��ȸ���� ������ ��
//					long nBlockLength ��ȸ���� ������ �� ũ��
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/*	���� : OnGetRealData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
		�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/
	CString strRealMessage;

	/***************************************
	 * �ؿܼ���ü��Ȯ��
	 ****************************************/
	if (!_tcscmp(strRealName, "EF1"))
	{
		/*--------------------------------------
		 �����۸����� ���ŵ� �ǽð� �����͸� �׸񺰷� ������.
		 ---------------------------------------*/
		CString strrltm_dpch_dcd	= m_CommAgent.GetRealOutputData(strRealName, "rltm_dpch_dcd");		//�ǽð��뺸�����ڵ�
		CString strusr_id	= m_CommAgent.GetRealOutputData(strRealName, "usr_id");		//�����ID
		CString strrltm_dpch_prcs_dcd = m_CommAgent.GetRealOutputData(strRealName, "rltm_dpch_prcs_dcd");		//�ǽð��뺸ó�������ڵ�
		CString strcano = m_CommAgent.GetRealOutputData(strRealName, "cano");		//���հ��¹�ȣ
		CString strctno = m_CommAgent.GetRealOutputData(strRealName, "ctno");		//��ü���հ��¹�ȣ
		CString strapno = m_CommAgent.GetRealOutputData(strRealName, "apno");		//���»�ǰ��ȣ
		CString strprdt_cd = m_CommAgent.GetRealOutputData(strRealName, "prdt_cd");		//��ǰ�ڵ�
		CString strodrv_ordr_tp_dcd = m_CommAgent.GetRealOutputData(strRealName, "odrv_ordr_tp_dcd");		//�ؿ��Ļ��ֹ����������ڵ�
		CString strordr_stts_dcd = m_CommAgent.GetRealOutputData(strRealName, "ordr_stts_dcd");		//�ֹ����±����ڵ�
		CString strodrv_odno = m_CommAgent.GetRealOutputData(strRealName, "odrv_odno");		//�ؿ��Ļ��ֹ���ȣ
		CString strodrv_or_odno = m_CommAgent.GetRealOutputData(strRealName, "odrv_or_odno");		//�ؿ��Ļ����ֹ���ȣ
		CString strordr_dt = m_CommAgent.GetRealOutputData(strRealName, "ordr_dt");		//�ֹ�����
		CString strcust_nm = m_CommAgent.GetRealOutputData(strRealName, "cust_nm");		//����
		CString strodrv_sell_buy_dcd = m_CommAgent.GetRealOutputData(strRealName, "odrv_sell_buy_dcd");		//�ؿ��Ļ��ŵ��ż������ڵ�
		CString strodrv_ordr_prc_ctns = m_CommAgent.GetRealOutputData(strRealName, "odrv_ordr_prc_ctns");		//�ؿ��Ļ��ֹ����ݳ���
		CString strordr_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "ordr_qnt_ctns");		//�ֹ���������
		CString strodrv_prc_dcd = m_CommAgent.GetRealOutputData(strRealName, "odrv_prc_dcd");		//�ؿ��Ļ����ݱ����ڵ�
		CString strcncs_cnd_dcd = m_CommAgent.GetRealOutputData(strRealName, "cncs_cnd_dcd");		//ü�����Ǳ����ڵ�
		CString strcnd_prc_ctns = m_CommAgent.GetRealOutputData(strRealName, "cnd_prc_ctns");		//���ǰ��ݳ���
		CString strcomm_mdia_dcd = m_CommAgent.GetRealOutputData(strRealName, "comm_mdia_dcd");		//��Ÿ�ü�����ڵ�
		CString stracpt_tm = m_CommAgent.GetRealOutputData(strRealName, "acpt_tm");		//�����ð�
		CString strexcg_cncs_tm = m_CommAgent.GetRealOutputData(strRealName, "excg_cncs_tm");		//�ŷ���ü��ð�
		CString stracpl_acpt_tm = m_CommAgent.GetRealOutputData(strRealName, "acpl_acpt_tm");		//���������ð�
		CString strcncs_tm = m_CommAgent.GetRealOutputData(strRealName, "cncs_tm");		//ü��ð�
		CString strcncs_dt = m_CommAgent.GetRealOutputData(strRealName, "cncs_dt");		//ü������
		CString strodrv_cncs_no = m_CommAgent.GetRealOutputData(strRealName, "odrv_cncs_no");		//�ؿ��Ļ�ü���ȣ
		CString strcncs_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "cncs_qnt_ctns");		//ü���������
		CString strodrv_cncs_prc_ctns = m_CommAgent.GetRealOutputData(strRealName, "odrv_cncs_prc_ctns");		//�ؿ��Ļ�ü�ᰡ�ݳ���
		CString strodrv_cncs_amt_ctns = m_CommAgent.GetRealOutputData(strRealName, "odrv_cncs_amt_ctns");		//�ؿ��Ļ�ü��ݾ׳���
		CString strcrry_cd = m_CommAgent.GetRealOutputData(strRealName, "crry_cd");		//��ȭ�ڵ�
		CString strordr_rmn_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "ordr_rmn_qnt_ctns");		//�ֹ��ܿ���������
		CString stracnt_dcd = m_CommAgent.GetRealOutputData(strRealName, "acnt_dcd");		//���±����ڵ�
		CString strentr_clr_dcd = m_CommAgent.GetRealOutputData(strRealName, "entr_clr_dcd");		//����û�걸���ڵ�
		CString strclr_pst_no = m_CommAgent.GetRealOutputData(strRealName, "clr_pst_no");		//û�������ǹ�ȣ

		strrltm_dpch_dcd.Trim();
		strusr_id.Trim();
		strrltm_dpch_prcs_dcd.Trim();
		strcano.Trim();
		strctno.Trim();
		strapno.Trim();
		strprdt_cd.Trim();
		strodrv_ordr_tp_dcd.Trim();
		strordr_stts_dcd.Trim();
		strodrv_odno.Trim();
		strodrv_or_odno.Trim();
		strordr_dt.Trim();
		strcust_nm.Trim();
		strodrv_sell_buy_dcd.Trim();
		strodrv_ordr_prc_ctns.Trim();
		strordr_qnt_ctns.Trim();
		strodrv_prc_dcd.Trim();
		strcncs_cnd_dcd.Trim();
		strcnd_prc_ctns.Trim();
		strcomm_mdia_dcd.Trim();
		stracpt_tm.Trim();
		strexcg_cncs_tm.Trim();
		stracpl_acpt_tm.Trim();
		strcncs_tm.Trim();
		strcncs_dt.Trim();
		strodrv_cncs_no.Trim();
		strcncs_qnt_ctns.Trim();
		strodrv_cncs_prc_ctns.Trim();
		strodrv_cncs_amt_ctns.Trim();
		strcrry_cd.Trim();
		strordr_rmn_qnt_ctns.Trim();
		stracnt_dcd.Trim();
		strentr_clr_dcd.Trim();
		strclr_pst_no.Trim();

		/*--------------------------------------
		��ȸ ������ ����� �ֽ� ���簡 �ǽð�Ű�� �������� ��
		---------------------------------------*/
		if (m_strLoginID == strRealKey)
		{
			strRealMessage.Format("[%s][����:%s][��ǰ:%s][ü��:%s]", strRealName, strcano, strprdt_cd, strcncs_qnt_ctns);
		}//End of if

	}
	/***************************************
	* �ؿܼ�����ü��
	****************************************/
	else if (!_tcscmp(strRealName, "EF4"))
	{
		CString strrltm_dpch_dcd = m_CommAgent.GetRealOutputData(strRealName, "rltm_dpch_dcd");		//�ǽð��뺸�����ڵ�
		CString strusr_id = m_CommAgent.GetRealOutputData(strRealName, "usr_id");		//�����ID
		CString strrltm_dpch_prcs_dcd = m_CommAgent.GetRealOutputData(strRealName, "rltm_dpch_prcs_dcd");		//�ǽð��뺸ó�������ڵ�
		CString strcano = m_CommAgent.GetRealOutputData(strRealName, "cano");		//���հ��¹�ȣ
		CString strctno = m_CommAgent.GetRealOutputData(strRealName, "ctno");		//��ü���հ��¹�ȣ
		CString strapno = m_CommAgent.GetRealOutputData(strRealName, "apno");		//���»�ǰ��ȣ
		CString strodrv_odno = m_CommAgent.GetRealOutputData(strRealName, "odrv_odno");		//�ؿ��Ļ��ֹ���ȣ
		CString strprdt_cd = m_CommAgent.GetRealOutputData(strRealName, "prdt_cd");		//��ǰ�ڵ�
		CString strodrv_or_odno = m_CommAgent.GetRealOutputData(strRealName, "odrv_or_odno");		//�ؿ��Ļ����ֹ���ȣ
		CString strodrv_mo_odno = m_CommAgent.GetRealOutputData(strRealName, "odrv_mo_odno");		//�ؿ��Ļ����ֹ���ȣ
		CString strordr_grup_no = m_CommAgent.GetRealOutputData(strRealName, "ordr_grup_no");		//�ֹ��׷��ȣ
		CString strordr_dt = m_CommAgent.GetRealOutputData(strRealName, "ordr_dt");		//�ֹ�����
		CString strcust_nm = m_CommAgent.GetRealOutputData(strRealName, "cust_nm");		//����
		CString strodrv_sell_buy_dcd = m_CommAgent.GetRealOutputData(strRealName, "odrv_sell_buy_dcd");		//�ؿ��Ļ��ŵ��ż������ڵ�
		CString strodrv_ordr_prc_ctns = m_CommAgent.GetRealOutputData(strRealName, "odrv_ordr_prc_ctns");		//�ؿ��Ļ��ֹ����ݳ���
		CString strordr_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "ordr_qnt_ctns");		//�ֹ���������
		CString strrvse_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "rvse_qnt_ctns");		//������������
		CString strcncl_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "cncl_qnt_ctns");		//��Ҽ�������
		CString strcncs_qnt_smm_ctns = m_CommAgent.GetRealOutputData(strRealName, "cncs_qnt_smm_ctns");		//ü������հ賻��
		CString strordr_rmn_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "ordr_rmn_qnt_ctns");		//�ֹ��ܿ���������
		CString strodrv_prc_dcd = m_CommAgent.GetRealOutputData(strRealName, "odrv_prc_dcd");		//�ؿ��Ļ����ݱ����ڵ�
		CString strcncs_cnd_dcd = m_CommAgent.GetRealOutputData(strRealName, "cncs_cnd_dcd");		//ü�����Ǳ����ڵ�
		CString strcnd_prc_ctns = m_CommAgent.GetRealOutputData(strRealName, "cnd_prc_ctns");		//���ǰ��ݳ���
		CString stravr_cncs_prc_ctns = m_CommAgent.GetRealOutputData(strRealName, "avr_cncs_prc_ctns");		//���ü�ᰡ�ݳ���
		CString strodrv_pv_ctns = m_CommAgent.GetRealOutputData(strRealName, "odrv_pv_ctns");		//�ؿ��Ļ����簡����
		CString strcncs_rt_ctns = m_CommAgent.GetRealOutputData(strRealName, "cncs_rt_ctns");		//ü��������
		CString strcomm_mdia_dcd = m_CommAgent.GetRealOutputData(strRealName, "comm_mdia_dcd");		//��Ÿ�ü�����ڵ�
		CString strodrv_ordr_tp_dcd = m_CommAgent.GetRealOutputData(strRealName, "odrv_ordr_tp_dcd");		//�ؿ��Ļ��ֹ����������ڵ�
		CString strordr_stts_dcd = m_CommAgent.GetRealOutputData(strRealName, "ordr_stts_dcd");		//�ֹ����±����ڵ�
		CString strfcm_odno = m_CommAgent.GetRealOutputData(strRealName, "fcm_odno");		//FCM�ֹ���ȣ
		CString strathz_ip_addr = m_CommAgent.GetRealOutputData(strRealName, "athz_ip_addr");		//����IP�ּ�
		CString stracpt_tm = m_CommAgent.GetRealOutputData(strRealName, "acpt_tm");		//�����ð�
		CString strexcg_cncs_tm = m_CommAgent.GetRealOutputData(strRealName, "excg_cncs_tm");		//�ŷ���ü��ð�
		CString stracpl_acpt_tm = m_CommAgent.GetRealOutputData(strRealName, "acpl_acpt_tm");		//���������ð�
		CString strcncs_tm = m_CommAgent.GetRealOutputData(strRealName, "cncs_tm");		//ü��ð�
		CString strcrry_cd = m_CommAgent.GetRealOutputData(strRealName, "crry_cd");		//��ȭ�ڵ�
		CString strcncs_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "cncs_qnt_ctns");		//ü���������
		CString strordr_expr_dt = m_CommAgent.GetRealOutputData(strRealName, "ordr_expr_dt");		//�ֹ���������
		CString stracnt_dcd = m_CommAgent.GetRealOutputData(strRealName, "acnt_dcd");		//���±����ڵ�
		CString strentr_clr_dcd = m_CommAgent.GetRealOutputData(strRealName, "entr_clr_dcd");		//����û�걸���ڵ�
		CString strclr_pst_no = m_CommAgent.GetRealOutputData(strRealName, "clr_pst_no");		//û�������ǹ�ȣ
		
		strrltm_dpch_dcd.Trim();
		strusr_id.Trim();
		strrltm_dpch_prcs_dcd.Trim();
		strcano.Trim();
		strctno.Trim();
		strapno.Trim();
		strodrv_odno.Trim();
		strprdt_cd.Trim();
		strodrv_or_odno.Trim();
		strodrv_mo_odno.Trim();
		strordr_grup_no.Trim();
		strordr_dt.Trim();
		strcust_nm.Trim();
		strodrv_sell_buy_dcd.Trim();
		strodrv_ordr_prc_ctns.Trim();
		strordr_qnt_ctns.Trim();
		strrvse_qnt_ctns.Trim();
		strcncl_qnt_ctns.Trim();
		strcncs_qnt_smm_ctns.Trim();
		strordr_rmn_qnt_ctns.Trim();
		strodrv_prc_dcd.Trim();
		strcncs_cnd_dcd.Trim();
		strcnd_prc_ctns.Trim();
		stravr_cncs_prc_ctns.Trim();
		strodrv_pv_ctns.Trim();
		strcncs_rt_ctns.Trim();
		strcomm_mdia_dcd.Trim();
		strodrv_ordr_tp_dcd.Trim();
		strordr_stts_dcd.Trim();
		strfcm_odno.Trim();
		strathz_ip_addr.Trim();
		stracpt_tm.Trim();
		strexcg_cncs_tm.Trim();
		stracpl_acpt_tm.Trim();
		strcncs_tm.Trim();
		strcrry_cd.Trim();
		strcncs_qnt_ctns.Trim();
		strordr_expr_dt.Trim();
		stracnt_dcd.Trim();
		strentr_clr_dcd.Trim();
		strclr_pst_no.Trim();

		/*--------------------------------------
		��ȸ ������ ����� �ֽ� ���簡 �ǽð�Ű�� �������� ��
		---------------------------------------*/
		if (m_strLoginID == strRealKey)
		{
			strRealMessage.Format("[%s][�ֹ�����:%s][����:%s][��ǰ:%s][�ֹ���:%s][������:%s][��Ҽ�:%s]",
								  strRealName, strordr_stts_dcd, strcano, strprdt_cd, strordr_qnt_ctns, strrvse_qnt_ctns, strcncl_qnt_ctns);
		}//End of if

	}//End of if

	if (!strRealMessage.IsEmpty())
	{
		m_listReal.SetRedraw(FALSE);
		int nListRowCnt = m_listReal.GetItemCount();

		//������ 500���� ������ 100�Ǹ� ����� �����.
		if (nListRowCnt > 500)
		{
			for (int i = 100; i < 500; i++)
				m_listReal.DeleteItem(i);
		}

		LV_ITEM	lvItem;

		lvItem.mask = LVIF_TEXT;
		lvItem.iSubItem = 0;
		lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
		lvItem.iItem = 0;

		m_listReal.InsertItem(&lvItem);
		m_listReal.SetItemText(0, 0, (LPTSTR)(LPCTSTR)strRealMessage);			//�޽���
		m_listReal.SetRedraw(TRUE);
	}
}

//*******************************************************************
// Function Name : OnAgentEventHandler
// Function      : 
// Param         : long nEventType, long nParam, LPCTSTR strParam
// Return        : void 
// Create        : 2016/11/10
// Comment       : ������Ʈ �̺�Ʈ �ڵ鷯
//******************************************************************
void CFFutOptOrdDlg::OnAgentEventHandler(long nEventType, long nParam, LPCTSTR strParam)
{
	CString strEventMsg;

	switch (nEventType)
	{
		case CommEvent::Connecting:			// ������
		{
			strEventMsg = "[��� �̺�Ʈ] ��� ������";
			::AfxMessageBox(strEventMsg);
		}
		break;
		case CommEvent::Connected:			// ���� �Ϸ�
		{
			strEventMsg = "[��� �̺�Ʈ] ��� ���� �Ϸ�";
			::AfxMessageBox(strEventMsg);
		}
		break;
		case CommEvent::Closed:			// ���� ���� ����
		case CommEvent::Closing:			// ���� ���� ��
		case CommEvent::ReconnectRequest:	// ������ ��û
		{
			strEventMsg = "[��� �̺�Ʈ] ������ �����Ǿ����ϴ�.";
			::AfxMessageBox(strEventMsg);
		}
		break;
		case CommEvent::ConnectFail:		// ���� ���� ����
		{
			strEventMsg = "[��� �̺�Ʈ] ��ſ��� ����.";
			::AfxMessageBox(strEventMsg);
		}
		break;
		//���� ���� �޽���
		case CommEvent::NotifyMultiLogin:	// �������� �˸� �޽���
		{
			strEventMsg.Format("[�����α��� �̺�Ʈ] %s", strParam);
			::AfxMessageBox(strEventMsg);

			//nParam ���� 1 �̸� ������ �����϶�� �޽����̴�.
			//������ ���������� API ����ڰ� �˾Ƽ� �ڵ��Ѵ�.
			if (nParam == 1)
			{
				strEventMsg.Format("[�����α��� �̺�Ʈ] ���� �������� ���� ���� ����");
				::AfxMessageBox(strEventMsg);
			}
		}
		break;
		case CommEvent::NotifyEmergency:	// ��ް��� �޽���
		{
			strEventMsg.Format("[��ް��� �̺�Ʈ] %s", strParam);
			::AfxMessageBox(strEventMsg);
		}
		break;
		case CommEvent::PopUpMsg:			// �˾��޽���
		{
			strEventMsg.Format("[�˾� �̺�Ʈ] %s", strParam);
			::AfxMessageBox(strEventMsg);
		}
		break;

	}//End of switch
}

void CFFutOptOrdDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	for (int i = 0; i < 100; i++)
	{
		OnBnClickedBtnReqDeposit();
	}
}
