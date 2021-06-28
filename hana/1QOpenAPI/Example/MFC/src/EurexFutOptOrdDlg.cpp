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
#include "EurexFutOptOrdDlg.h"

#define ID_SECOND_TIMER		100	//1�� ���� Ÿ�̸�

#define SELL_BK_COLOR		RGB(206, 232, 255)	//�ŵ� ����
#define BUY_BK_COLOR		RGB(251, 221, 255)	//�ż� ����

//��� ����ü ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern void NumericString(CString& strValue, BOOL bNotDisplayZero = FALSE);

static char* g_szOrderType[] = { "01", "03" }; //ȣ������ : 01:������, 03:���尡
static char g_cPriceCont[3] = { ' ' , 'I', 'F' };	//�ֹ����� : ����, IOC, FOK

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

// CEurexFutOptOrdDlg ��ȭ ����
CEurexFutOptOrdDlg::CEurexFutOptOrdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEurexFutOptOrdDlg::IDD, pParent)
{
	m_bCommConnect		= FALSE;

	m_nRqIdAccNoList		= 0;	//������ȸ Request ID
	m_nRqIdFDemoAccNoList	= 0;	//�ؿܸ��� ������ȸ Request ID

	m_nRqIdSellOrd			= 0;	//�ŵ��ֹ� Request ID
	m_nRqIdBuyOrd			= 0;	//�ż��ֹ� Request ID
	m_nRqIdChangeOrd		= 0;	//�����ֹ� Request ID
	m_nRqIdCancelOrd		= 0;	//����ֹ� Request ID

	m_nRqIdExecList			= 0;	//�ֹ�ü��(��ü��)���� Request ID
	m_nRqIdDepositList		= 0;	//�����ݳ��� Request ID

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_nSeverType			= 0;	//0-����, 1-��������, 2-�ؿܹ���

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEurexFutOptOrdDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_LIST_BALANCE, m_listBalance);
	DDX_Control(pDX, IDC_CMB_ORD_TYPE, m_cmdOrdType);
	DDX_Control(pDX, IDC_LIST_REAL, m_listReal);
	DDX_Control(pDX, IDC_CMB_ORD_COND, m_cmbOrdCond);
	DDX_Control(pDX, IDC_DATETIME2, m_dateTime2);
	DDX_Control(pDX, IDC_DATETIME3, m_dateTime3);
}

BEGIN_MESSAGE_MAP(CEurexFutOptOrdDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_LOGIN, &CEurexFutOptOrdDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_LOGOUT, &CEurexFutOptOrdDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDOK, &CEurexFutOptOrdDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELL, &CEurexFutOptOrdDlg::OnBnClickedBtnSell)
	ON_BN_CLICKED(IDC_BTN_BUY, &CEurexFutOptOrdDlg::OnBnClickedBtnBuy)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CEurexFutOptOrdDlg::OnBnClickedBtnChange)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CEurexFutOptOrdDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST, &CEurexFutOptOrdDlg::OnBnClickedBtnReqExecList)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST_NEXT, &CEurexFutOptOrdDlg::OnBnClickedBtnReqExecListNext)
	ON_BN_CLICKED(IDC_BTN_REQ_ACCNO, &CEurexFutOptOrdDlg::OnBnClickedBtnReqAccno)
	ON_BN_CLICKED(IDC_BTN_REQ_DEPOSIT, &CEurexFutOptOrdDlg::OnBnClickedBtnReqDeposit)
	ON_BN_CLICKED(IDC_BTN_REQ_BALANCE, &CEurexFutOptOrdDlg::OnBnClickedBtnReqBalance)
	ON_BN_CLICKED(IDC_BTN_LOAD_USER_ACC, &CEurexFutOptOrdDlg::OnBnClickedBtnLoadUserAcc)
	ON_COMMAND_RANGE(IDC_CON_REAL, IDC_CON_F_DEMO, &CEurexFutOptOrdDlg::OnRdoSelectServer)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCNO, &CEurexFutOptOrdDlg::OnNMDblclkListAccNo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ORD, &CEurexFutOptOrdDlg::OnNMDblclkListExec)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BALANCE, &CEurexFutOptOrdDlg::OnNMDblclkListBalance)

	ON_BN_CLICKED(IDC_BUTTON_TEST, &CEurexFutOptOrdDlg::OnBnClickedButtonTest)
END_MESSAGE_MAP()

// agent�κ��� �̺�Ʈ ���� �Լ��� �����Ѵ�.
BEGIN_EVENTSINK_MAP(CEurexFutOptOrdDlg, CDialog)
	ON_EVENT(CEurexFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 1, CEurexFutOptOrdDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CEurexFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 2, CEurexFutOptOrdDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CEurexFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 3, CEurexFutOptOrdDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
END_EVENTSINK_MAP()

// CEurexFutOptOrdDlg �޽��� ó����
void CEurexFutOptOrdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CEurexFutOptOrdDlg::OnPaint()
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
HCURSOR CEurexFutOptOrdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CEurexFutOptOrdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CEurexFutOptOrdDlg::OnNMDblclkListAccNo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	
	CString strAccNo = m_listAccNo.GetItemText(nSelectRow, 0);
	CString strPrdtNo = m_listAccNo.GetItemText(nSelectRow, 2);

	GetDlgItem(IDC_EDIT_ACCNO)->SetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->SetWindowText(strPrdtNo);
}

void CEurexFutOptOrdDlg::OnNMDblclkListExec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;

	CString strOrdOrg = m_listExec.GetItemText(nSelectRow, 4);
	CString strSymbol = m_listExec.GetItemText(nSelectRow, 5);
	CString strOrdPrice = m_listExec.GetItemText(nSelectRow, 9);
	CString strOrdSu = m_listExec.GetItemText(nSelectRow, 10);

	GetDlgItem(IDC_EDIT_ORG_NO)->SetWindowText(strOrdOrg);
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);
	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);
}

void CEurexFutOptOrdDlg::OnNMDblclkListBalance(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	
	CString strSymbol = m_listBalance.GetItemText(nSelectRow, 0);
	CString strOrdPrice = m_listBalance.GetItemText(nSelectRow, 6);
	CString strOrdSu = m_listBalance.GetItemText(nSelectRow, 10);
	
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);
	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);
}

void CEurexFutOptOrdDlg::OnDestroy()
{
	//��� �ǽð������ �����Ѵ�.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();
	
	CDialog::OnDestroy();
}

void CEurexFutOptOrdDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CEurexFutOptOrdDlg::OnTimer(UINT_PTR nIDEvent)
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
void CEurexFutOptOrdDlg::OnRdoSelectServer(UINT nID)
{
	m_nSeverType = nID - IDC_CON_REAL;

	/*----------------------------------
	  ���Ӽ����� �����Ѵ�.(0 - ����, 1 - ��������, 2 - �ؿܸ���)
	 *----------------------------------*/
	m_CommAgent.SetLoginMode(0, m_nSeverType);
}

//*******************************************************************
// Function Name : OnInitDialog
// Function      : ���̾�α� �ʱ�ȭ
// Param         : 
// Return        : BOOL 
// Create        : 
// Comment       : 
//******************************************************************
BOOL CEurexFutOptOrdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CString strTitle;
	strTitle.Format("%s-[�߰����� �ֹ�](%s)", PROGRAM_NAME, VERSION_INFO);
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
	InitListExec();		//�ֹ�ü��
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

	((CButton*)GetDlgItem(IDC_CHK_AllQty))->SetCheck(1);

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
void CEurexFutOptOrdDlg::InitListAccNo()
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
void CEurexFutOptOrdDlg::InitListReal()
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
// Function Name : InitListExec
// Function      : 
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CEurexFutOptOrdDlg::InitListExec()
{
	CRect rc;
	m_listExec.GetClientRect(rc);
	m_listExec.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("���������ڵ�"), _T("����������"), _T("���ֹ��Ϸù�ȣ"), _T("�ֹ��Ϸù�ȣ"),
		_T("���ֹ��Ϸù�ȣ"), _T("��ǰ�ڵ�"), _T("��ǰ��"), _T("�Ļ���ǰȣ�������ڵ�"), _T("�Ļ���ǰȣ�����и�"),
		_T("�ֹ����ݳ���"), _T("�ֹ�����"), _T("ü�ᱸ�и�"), _T("ü�ᰡ�ݳ���"), _T("ü�����"),
		_T("ü��󼼽ð�"), _T("��ü�����"), _T("�Ļ���ǰȣ�����������ڵ�"), _T("�Ļ���ǰȣ���������и�"),
		_T("���ۻ��Ͻ�"), _T("�ѱ��ŷ��Ҹ޽�����ȣ"), _T("ü���Ϸù�ȣ"), _T("�ܺα���źλ����ڵ�"), _T("��Ÿ�ü�����ڵ�") };

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
		m_listExec.InsertColumn(i, &lvcolumn);
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
void CEurexFutOptOrdDlg::InitListBalance()
{
	CRect rc;
	m_listBalance.GetClientRect(rc);
	m_listBalance.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("��ǰ�ڵ�"), _T("��ǰ��"), _T("�Ÿű����ڵ�"), _T("�Ÿű��и�"),
						_T("�̰�����������"), _T("��հ���"), _T("���簡��"), _T("�򰡱ݾ�"), _T("�򰡼��ͱݾ�"),
						_T("������"), _T("û�갡�ɼ���"), _T("������αݾ�") };

	int i;
	for (i = 0; i < 12; i++)
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
void CEurexFutOptOrdDlg::OnBnClickedLogin()
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
	//�ֹ�Ȯ��/ü��/��ü��(����/���) �ǽð� �뺸
	m_CommAgent.RegisterReal("EF5", m_strLoginID);
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : �α׾ƿ�
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexFutOptOrdDlg::OnBnClickedLogout()
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
void CEurexFutOptOrdDlg::OnBnClickedOk()
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
void CEurexFutOptOrdDlg::OnBnClickedBtnReqAccno()
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
void CEurexFutOptOrdDlg::OnBnClickedBtnLoadUserAcc()
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

		strAPNO = GetAccAPNO(strAccNo + strPrdtNo); //���հ��´�ü��ȣ ������

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
CString CEurexFutOptOrdDlg::GetAccAPNO(CString strAccNo)
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
void CEurexFutOptOrdDlg::RequestAccList()
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
void CEurexFutOptOrdDlg::RequestFDemoAccList()
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
// Param         : CString strDealSide
// Return        : void 
// Create        : 
// Comment       : �ż�/�ŵ� �ֹ� ����
//******************************************************************
BOOL CEurexFutOptOrdDlg::SendSellBuyOrder(CString strDealSide, int nRqId)
{
	CString strInRecName;
	CString strTrCode;
	
	//�Է��׸� ������
	CString strCTNO;					//��ü���հ��¹�ȣ
	CString strAPNO;					//���»�ǰ��ȣ
	CString strACNT_PWD;				//��й�ȣ
	CString strSELL_BUY_DCD;			//��ǰ�ڵ�
	CString strPRDT_CD;					//�ŵ��ż������ڵ�
	CString strDRVS_NMPR_DCD;			//�������Ǳ����ڵ�
	CString strORDR_PRC;				//�ֹ�����
	CString strORDR_QNT;				//�ֹ�����
	CString strPWD_CNFM_YN("Y");		//��й�ȣȮ�ο���
	CString strCVRG_YN("N");			//�ݴ�Ÿſ���
	CString strDRVS_ORDR_CND_DCD;		//�ֹ�����(' ' : ����, 'I' : IOC, 'F' : FOK)
	CString strDFRT_HDGE_DCD("00");		//�������������ڵ�

	strTrCode = "OTS2850U30";

	if (strDealSide == "S") //�ŵ�
		strSELL_BUY_DCD = "1";
	else if (strDealSide == "B") //�ż�
		strSELL_BUY_DCD = "2";

	strInRecName.Format("%s_in", strTrCode);		//�Է� ���ڵ��(���ҽ����� ����)

	CString strAccNo;
	CString strAccPwd;

	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ

	strCTNO = GetAccAPNO(strAccNo + strAPNO); //���հ��´�ü��ȣ ������

	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strAccPwd);			//��й�ȣ
	strACNT_PWD = m_CommAgent.GetEncrpyt(strAccPwd);				//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//��ǰ�ڵ�

	if (m_cmdOrdType.GetCurSel() >= 0)
		strDRVS_NMPR_DCD = g_szOrderType[m_cmdOrdType.GetCurSel()];	//�Ļ���ǰȣ�������ڵ�

	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strORDR_PRC);		//�ֹ�����
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);		//�ֹ�����

	if(m_cmbOrdCond.GetCurSel() >= 0)
		strDRVS_ORDR_CND_DCD.Format("%c", g_cPriceCont[m_cmbOrdCond.GetCurSel()]);//�ֹ�����(' ' : ����, 'I' : IOC, 'F' : FOK)

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "CTNO", strCTNO);					//��ü���հ��¹�ȣ
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "APNO", strAPNO);					//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);			//��й�ȣ
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);	//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);			//�ŵ��ż������ڵ�
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "DRVS_NMPR_DCD", strDRVS_NMPR_DCD);//�������Ǳ����ڵ�
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_PRC", strORDR_PRC);			//�ֹ�����
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);			//�ֹ�����
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "PWD_CNFM_YN", strPWD_CNFM_YN);	//��й�ȣȮ�ο���
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "CVRG_YN", strCVRG_YN);			//�ݴ�Ÿſ���
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "DRVS_ORDR_CND_DCD", strDRVS_ORDR_CND_DCD);	//�ֹ�����(' ' : ����, 'I' : IOC, 'F' : FOK)
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "DFRT_HDGE_DCD", strDFRT_HDGE_DCD);	//�������������ڵ�
	

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	
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
void CEurexFutOptOrdDlg::OnBnClickedBtnSell()
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
void CEurexFutOptOrdDlg::OnBnClickedBtnBuy()
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
void CEurexFutOptOrdDlg::OnBnClickedBtnChange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS2850U32";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS2850U32_in";	//�Է� ���ڵ��(���ҽ����� ����)
	
	//[1] Request ID����
	m_nRqIdChangeOrd = m_CommAgent.CreateRequestID();

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	CString strCTNO;				//���հ��´�ü��ȣ
	CString strAPNO;				//���»�ǰ��ȣ
	CString strACNT_PWD;			//���º�й�ȣ
	CString strOR_ORDR_SN;			//���ֹ��Ϸù�ȣ
	CString strDRVS_NMPR_DCD;		//�Ļ���ǰȣ�������ڵ�
	CString strORDR_PRC;			//�ֹ�����
	CString strORDR_QNT;			//�ֹ�����
	CString strALL_YN;				//��ü����
	CString strDRVS_ORDR_CND_DCD;	//�Ļ���ǰ�ֹ����Ǳ����ڵ�
	CString strPWD_CNFM_YN("Y");	//��й�ȣȮ�ο���
	CString strCVRG_YN("N");		//�ݴ�Ÿſ���
	CString strDFRT_HDGE_DCD("00");	//�������������ڵ�
	
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ

	strCTNO = GetAccAPNO(strCTNO + strAPNO);						//���հ��´�ü��ȣ ������

	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);		//��й�ȣ
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);				//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.

	//���ֹ���ȣ
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strOR_ORDR_SN);

	//�������Ǳ����ڵ�
	if (m_cmdOrdType.GetCurSel() >= 0)
		strDRVS_NMPR_DCD = g_szOrderType[m_cmdOrdType.GetCurSel()];

	//��������
	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strORDR_PRC);

	//��������
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	//��ü����
	if (((CButton*)GetDlgItem(IDC_CHK_AllQty))->GetCheck() == 1)
		strALL_YN = "Y";
	else
		strALL_YN = "N";

	//�ֹ�����(' ' : ����, 'I' : IOC, 'F' : FOK)
	if (m_cmbOrdCond.GetCurSel() >= 0)
		strDRVS_ORDR_CND_DCD.Format("%c", g_cPriceCont[m_cmbOrdCond.GetCurSel()]);

	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "CTNO", strCTNO);					//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "APNO", strAPNO);					//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);			//���º�й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "OR_ORDR_SN", strOR_ORDR_SN);		//���ֹ��Ϸù�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "DRVS_NMPR_DCD", strDRVS_NMPR_DCD);	//�Ļ���ǰȣ�������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_PRC", strORDR_PRC);			//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);			//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ALL_YN", strALL_YN);				//��ü����
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "DRVS_ORDR_CND_DCD", strDRVS_ORDR_CND_DCD);	//�Ļ���ǰ�ֹ����Ǳ����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PWD_CNFM_YN", strPWD_CNFM_YN);		//��й�ȣȮ�ο���
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "CVRG_YN", strCVRG_YN);				//�ݴ�Ÿſ���
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "DFRT_HDGE_DCD", strDFRT_HDGE_DCD);	//�������������ڵ�

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	
	//[3] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdChangeOrd, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", 0) < 0)
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
void CEurexFutOptOrdDlg::OnBnClickedBtnCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS2850U33";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS2850U33_in ";	//�Է� ���ڵ��(���ҽ����� ����)

	//[1] Request ID����
	m_nRqIdCancelOrd = m_CommAgent.CreateRequestID();

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	CString strCTNO;			//���հ��´�ü��ȣ
	CString strAPNO;			//���»�ǰ��ȣ
	CString strACNT_PWD;		//���º�й�ȣ
	CString strOR_ORDR_SN;		//���ֹ��Ϸù�ȣ
	CString strORDR_QNT;		//�ֹ�����
	CString strORDR_PRC;		//�ֹ�����
	CString strALL_YN;			//��ü����
	CString strPWD_CNFM_YN("Y");//��й�ȣȮ�ο���
	CString strDFRT_HDGE_DCD("00");	//�������������ڵ�

	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//��ü���հ��¹�ȣ

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //���հ��´�ü��ȣ ������

	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);		//��й�ȣ
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);				//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.

	//���ֹ���ȣ
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strOR_ORDR_SN);

	//��Ҽ���
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	//�ֹ�����
	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strORDR_PRC);

	//��ü����
	if (((CButton*)GetDlgItem(IDC_CHK_AllQty))->GetCheck() == 1)
		strALL_YN = "Y";
	else
		strALL_YN = "N";

	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "APNO", strAPNO);				//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "OR_ORDR_SN", strOR_ORDR_SN);	//���ֹ��Ϸù�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);		//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ORDR_PRC", strORDR_PRC);			//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ALL_YN", strALL_YN);			//��ü����
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "PWD_CNFM_YN", strPWD_CNFM_YN);	//��й�ȣȮ�ο���
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "DFRT_HDGE_DCD", strDFRT_HDGE_DCD);	//�������������ڵ�

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	
	//[3] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdCancelOrd, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", 0) < 0)
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
void CEurexFutOptOrdDlg::OnBnClickedBtnReqDeposit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}
	
	GetDlgItem(IDC_EDIT_DEPOSIT)->SetWindowText("");

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS2850Q17";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS2850Q17_in";			//�Է� ���ڵ��(���ҽ����� ����)

	/*-------------------------------*
	 [1] Request ID����
	*-------------------------------*/
	m_nRqIdDepositList = m_CommAgent.CreateRequestID();

	CString strCTNO;			//���հ��´�ü��ȣ
	CString strAPNO;			//���»�ǰ��ȣ
	CString strPWD;				//��й�ȣ
	CString strINQ_DT;			//��ȸ����
	
	//���¹�ȣ
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	
	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //���հ��´�ü��ȣ ������

	//���º��
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD); //��ȣȭ�Ѵ�.


	/*-------------------------------*
	 [2] Tran��ȸ �Է°��� �Է��Ѵ�.
	 *-------------------------------*/
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "CTNO", strCTNO);			//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "APNO", strAPNO);			//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "PWD", strPWD);			//��й�ȣ

	CString strBenefitAcc	= "N";		//�������ǰ��� ����
	CString strPreNext		= "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo		= "9999";	//ȭ���ȣ


	/*-------------------------------*
	 [3] ������ Tran��ȸ ��û�Ѵ�.
	 *-------------------------------*/
	if(m_CommAgent.RequestTran(m_nRqIdDepositList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
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
void CEurexFutOptOrdDlg::OnBnClickedBtnReqExecList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_listExec.DeleteAllItems();
	m_strListExecNextRqKey.Empty(); //����Ű�� �ʱ�ȭ��Ų��.

	CString strTrCode = "OTS2850Q12";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS2850Q12_in";		//�Է� ���ڵ��(���ҽ����� ����)
	
	/*-------------------------------*
		[1] Request ID����
	 *-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
		[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	 *-------------------------------*/
	CString strCTNO;				//���հ��´�ü��ȣ
	CString strAPNO;				//���»�ǰ��ȣ
	CString strPWD;					//��й�ȣ
	CString strORDR_STRT_SN("0");	//�ֹ������Ϸù�ȣ
	CString strINQ_STDR_DT;			//��ȸ����
	CString strCNCS_DCD("0");		//ü�ᱸ���ڵ�(0: ��ü, 1: ü��, 2: ��ü��)
	CString strINQ_DVSN("1");		//���ı����ڵ�(1: ����, �׿� ���� ����)
	CString strFTOP_DCD("0");		//�����ɼǱ����ڵ�(0: ��ü, 1: ����, 2: �ɼ�)
	CString strSELL_BUY_DCD("0");	//�ż����ŵ�(0:��ü, 1:�ŵ�, 2:�ż�)
	CString strPRDT_CD;				//��ǰ�ڵ�(���� ������ ������)

	//���´�ü��ȣ�� ���´�.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	
	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //���հ��´�ü��ȣ ������

	//���º�й�ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD);

	//��ȸ����
	m_dateTime3.GetWindowText(strINQ_STDR_DT);
	strINQ_STDR_DT.Remove('-');

	//ü���ü�ᱸ���ڵ�(0: ��ü, 1: ü��, 2: ��ü��)
	if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT1))->GetCheck())
		strCNCS_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT2))->GetCheck())
		strCNCS_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT3))->GetCheck())
		strCNCS_DCD = "2";

	//���ı����ڵ�(1: ����, 2 : ����)
	if (((CButton*)GetDlgItem(IDC_RD_EXE_SORT1))->GetCheck())
		strINQ_DVSN = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_SORT2))->GetCheck())
		strINQ_DVSN = "2";

	//�����ɼǱ���(0:��ü, 1:����, 2:�ɼ�)
	if (((CButton*)GetDlgItem(IDC_RD_FO_OPT1))->GetCheck())
		strFTOP_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_FO_OPT2))->GetCheck())
		strFTOP_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_FO_OPT3))->GetCheck())
		strFTOP_DCD = "2";

	//�ż����ŵ�(0:��ü, 1:�ŵ�, 2:�ż�)
	if (((CButton*)GetDlgItem(IDC_RD_SB1))->GetCheck())
		strSELL_BUY_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_SB2))->GetCheck())
		strSELL_BUY_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_SB3))->GetCheck())
		strSELL_BUY_DCD = "2";

	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO);					//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strAPNO);					//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD);						//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_STRT_SN", strORDR_STRT_SN);	//�ֹ������Ϸù�ȣ(�ʼ��Է¾ƴ�)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_STDR_DT", strINQ_STDR_DT);		//��ȸ����
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CNCS_DCD", strCNCS_DCD);			//ü���ü�ᱸ���ڵ�(0: ��ü, 1: ü��, 2: ��ü��)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_DVSN", strINQ_DVSN);			//���ı����ڵ�(1: ����, 2 : ����)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "FTOP_DCD", strFTOP_DCD);			//�����ɼǱ����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);	//�ż��ŵ�����
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);				//��ǰ�ڵ�
	
	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "1";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdExecList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", nRequestDataCnt) < 0)
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
void CEurexFutOptOrdDlg::OnBnClickedBtnReqExecListNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS2850Q12";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS2850Q12_in";		//�Է� ���ڵ��(���ҽ����� ����)

	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	*-------------------------------*/
	CString strCTNO;				//���հ��´�ü��ȣ
	CString strAPNO;				//���»�ǰ��ȣ
	CString strPWD;					//��й�ȣ
	CString strORDR_STRT_SN("0");	//�ֹ������Ϸù�ȣ
	CString strINQ_STDR_DT;			//��ȸ����
	CString strCNCS_DCD("0");		//ü�ᱸ���ڵ�(0: ��ü, 1: ü��, 2: ��ü��)
	CString strINQ_DVSN("1");		//���ı����ڵ�(1: ����, �׿� ���� ����)
	CString strFTOP_DCD("0");		//�����ɼǱ����ڵ�(0: ��ü, 1: ����, 2: �ɼ�)
	CString strSELL_BUY_DCD("0");	//�ż����ŵ�(0:��ü, 1:�ŵ�, 2:�ż�)
	CString strPRDT_CD;				//��ǰ�ڵ�(���� ������ ������)

	//���´�ü��ȣ�� ���´�.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);

	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //���հ��´�ü��ȣ ������

	//���º�й�ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD);

	//��ȸ����
	m_dateTime3.GetWindowText(strINQ_STDR_DT);
	strINQ_STDR_DT.Remove('-');

	//ü���ü�ᱸ���ڵ�(0: ��ü, 1: ü��, 2: ��ü��)
	if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT1))->GetCheck())
		strCNCS_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT2))->GetCheck())
		strCNCS_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT3))->GetCheck())
		strCNCS_DCD = "2";

	//���ı����ڵ�(1: ����, 2 : ����)
	if (((CButton*)GetDlgItem(IDC_RD_EXE_SORT1))->GetCheck())
		strINQ_DVSN = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_SORT2))->GetCheck())
		strINQ_DVSN = "2";

	//�����ɼǱ���(0:��ü, 1:����, 2:�ɼ�)
	if (((CButton*)GetDlgItem(IDC_RD_FO_OPT1))->GetCheck())
		strFTOP_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_FO_OPT2))->GetCheck())
		strFTOP_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_FO_OPT3))->GetCheck())
		strFTOP_DCD = "2";

	//�ż����ŵ�(0:��ü, 1:�ŵ�, 2:�ż�)
	if (((CButton*)GetDlgItem(IDC_RD_SB1))->GetCheck())
		strSELL_BUY_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_SB2))->GetCheck())
		strSELL_BUY_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_SB3))->GetCheck())
		strSELL_BUY_DCD = "2";

	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO);					//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strAPNO);					//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD);						//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_STRT_SN", strORDR_STRT_SN);	//�ֹ������Ϸù�ȣ(�ʼ��Է¾ƴ�)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_STDR_DT", strINQ_STDR_DT);		//��ȸ����
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CNCS_DCD", strCNCS_DCD);			//ü���ü�ᱸ���ڵ�(0: ��ü, 1: ü��, 2: ��ü��)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_DVSN", strINQ_DVSN);			//���ı����ڵ�(1: ����, 2 : ����)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "FTOP_DCD", strFTOP_DCD);			//�����ɼǱ����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);	//�ż��ŵ�����
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);				//��ǰ�ڵ�

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "3";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.)

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdExecList, strTrCode, strBenefitAcc, strPreNext, m_strListExecNextRqKey, strScreenNo, "Q", nRequestDataCnt) < 0)
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
void CEurexFutOptOrdDlg::OnBnClickedBtnReqBalance()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_listBalance.DeleteAllItems();

	CString strTrCode = "OTS2850Q18";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName1 = "OTS2850Q18_in";	//�Է� ���ڵ��(���ҽ����� ����)

	CString strCTNO;			//��ü���հ��¹�ȣ
	CString strAPNO;			//���»�ǰ��ȣ
	CString strPWD;				//��й�ȣ
	CString strINQ_DT;			//��ȸ����
	CString strDCD("1");		//��ȸ����(1:������, 2:������ -  (1:��ü 2:�����ŷ����� �翵������ �ƴѰ��))

	//���´�ü��ȣ�� ���´�.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	
	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //���հ��´�ü��ȣ ������

	//���º�й�ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD);

	m_dateTime2.GetWindowText(strINQ_DT);
	strINQ_DT.Remove('-');

	//��ȸ����(1:������, 2:������ -  (1:��ü 2:�����ŷ����� �翵������ �ƴѰ��))
	if (((CButton*)GetDlgItem(IDC_RD_BAL_OPT1))->GetCheck())
		strDCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_BAL_OPT2))->GetCheck())
		strDCD = "2";


	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdBalanceList = m_CommAgent.CreateRequestID();

	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "CTNO", strCTNO);			//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "APNO", strAPNO);			//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "PWD", strPWD);				//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "INQ_DT", strINQ_DT);		//��ȸ����
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "DCD", strDCD);			//��ȸ����

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdBalanceList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", nRequestDataCnt) < 0)
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
void CEurexFutOptOrdDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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

	//�����޽���
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

	//�ֹ�ü�᳻�� ��ȸ
	if (nRequestId == m_nRqIdExecList)
	{
		/*-------------------------
		  OTS2850Q80_out �ܰ� ���
		 --------------------------*/
		CString strFTR_SELL_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_SELL_ORDR_QNT_SMM", 0);		//�����ŵ��ֹ������հ�
		CString strFTR_BUY_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_BUY_ORDR_QNT_SMM", 0);		//�����ż��ֹ������հ�
		CString strIDX_CLPT_SELL_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_SELL_ORDR_QNT_SMM", 0);		//�����ݿɼǸŵ��ֹ������հ�
		CString strIDX_PTPT_SELL_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_SELL_ORDR_QNT_SMM", 0);		//����ǲ�ɼǸŵ��ֹ������հ�
		CString strIDX_CLPT_BUY_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_BUY_ORDR_QNT_SMM", 0);		//�����ݿɼǸż��ֹ������հ�
		CString strIDX_PTPT_BUY_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_BUY_ORDR_QNT_SMM", 0);		//����ǲ�ɼǸż��ֹ������հ�
		CString strFTR_SELL_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_SELL_CNCS_QNT_SMM", 0);		//�����ŵ�ü������հ�
		CString strFTR_BUY_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_BUY_CNCS_QNT_SMM", 0);		//�����ż�ü������հ�
		CString strIDX_CLPT_SELL_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_SELL_CNCS_QNT_SMM", 0);		//�����ݿɼǸŵ�ü������հ�
		CString strIDX_PTPT_SELL_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_SELL_CNCS_QNT_SMM", 0);		//����ǲ�ɼǸŵ�ü������հ�
		CString strIDX_CLPT_BUY_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_BUY_CNCS_QNT_SMM", 0);		//�����ݿɼǸż�ü������հ�
		CString strIDX_PTPT_BUY_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_BUY_CNCS_QNT_SMM", 0);		//����ǲ�ɼǸż�ü������հ�
		
		NumericString(strFTR_SELL_ORDR_QNT_SMM);		//�����ŵ��ֹ������հ�
		NumericString(strFTR_BUY_ORDR_QNT_SMM);			//�����ż��ֹ������հ�
		NumericString(strIDX_CLPT_SELL_ORDR_QNT_SMM);	//�����ݿɼǸŵ��ֹ������հ�
		NumericString(strIDX_PTPT_SELL_ORDR_QNT_SMM);	//����ǲ�ɼǸŵ��ֹ������հ�
		NumericString(strIDX_CLPT_BUY_ORDR_QNT_SMM);	//�����ݿɼǸż��ֹ������հ�
		NumericString(strIDX_PTPT_BUY_ORDR_QNT_SMM);	//����ǲ�ɼǸż��ֹ������հ�
		NumericString(strFTR_SELL_CNCS_QNT_SMM);		//�����ŵ�ü������հ�
		NumericString(strFTR_BUY_CNCS_QNT_SMM);			//�����ż�ü������հ�
		NumericString(strIDX_CLPT_SELL_CNCS_QNT_SMM);	//�����ݿɼǸŵ�ü������հ�
		NumericString(strIDX_PTPT_SELL_CNCS_QNT_SMM);	//����ǲ�ɼǸŵ�ü������հ�
		NumericString(strIDX_CLPT_BUY_CNCS_QNT_SMM);	//�����ݿɼǸż�ü������հ�
		NumericString(strIDX_PTPT_BUY_CNCS_QNT_SMM);	//����ǲ�ɼǸż�ü������հ�


		/*-------------------------
		 OTS2850Q80_out_sub01 ������ ���
		 --------------------------*/
		CString strMNGM_BDCD, strMNGM_BD_NM, strMO_ORDR_SN, strORDR_SN, strOR_ORDR_SN, strPRDT_CD;
		CString strPRDT_NM, strDRVS_NMPR_DCD, strDRVS_NMPR_DVSN_NM, strORDR_PRC_CTNS, strORDR_QNT;
		CString strCNCS_DVSN_NM, strCNCS_PRC_CTNS, strCNCS_QNT, strCNCS_DTMD, strNCNC_QNT, strDRVS_NMPR_ACPT_DCD;
		CString strDRVS_NMPR_ACPT_DVSN_NM, strHND_DETL_DTM, strKRX_MSG_NO, strCNCS_SN, strXTNL_ISTT_RJCT_RSN_CD;
		CString strCOMM_MDIA_DCD;

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

		strOutRecName = "OTS2850Q12_out_sub01";

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, strOutRecName);
		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strMNGM_BDCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "MNGM_BDCD", nRow);		//���������ڵ�
			strMNGM_BD_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "MNGM_BD_NM", nRow);		//����������
			strMO_ORDR_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "MO_ORDR_SN", nRow);		//���ֹ��Ϸù�ȣ
			strORDR_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "ORDR_SN", nRow);		//�ֹ��Ϸù�ȣ
			strOR_ORDR_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "OR_ORDR_SN", nRow);		//���ֹ��Ϸù�ȣ
			strPRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
			strPRDT_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "PRDT_NM", nRow);		//��ǰ��
			strDRVS_NMPR_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_DCD", nRow);		//�Ļ���ǰȣ�������ڵ�
			strDRVS_NMPR_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_DVSN_NM", nRow);		//�Ļ���ǰȣ�����и�
			strORDR_PRC_CTNS = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "ORDR_PRC_CTNS", nRow);		//�ֹ����ݳ���
			strORDR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
			strCNCS_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_DVSN_NM", nRow);		//ü�ᱸ�и�
			strCNCS_PRC_CTNS = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_PRC_CTNS", nRow);		//ü�ᰡ�ݳ���
			strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_QNT", nRow);		//ü�����
			strCNCS_DTMD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_DTMD", nRow);		//ü��󼼽ð�
			strNCNC_QNT = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "NCNC_QNT", nRow);		//��ü�����
			strDRVS_NMPR_ACPT_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_ACPT_DCD", nRow);		//�Ļ���ǰȣ�����������ڵ�
			strDRVS_NMPR_ACPT_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_ACPT_DVSN_NM", nRow);		//�Ļ���ǰȣ���������и�
			strHND_DETL_DTM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "HND_DETL_DTM", nRow);		//���ۻ��Ͻ�
			strKRX_MSG_NO = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "KRX_MSG_NO", nRow);		//�ѱ��ŷ��Ҹ޽�����ȣ
			strCNCS_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_SN", nRow);		//ü���Ϸù�ȣ
			strXTNL_ISTT_RJCT_RSN_CD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "XTNL_ISTT_RJCT_RSN_CD", nRow);		//�ܺα���źλ����ڵ�
			strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "COMM_MDIA_DCD", nRow);		//��Ÿ�ü�����ڵ�

			strMNGM_BDCD.Trim();				//���������ڵ�
			strMNGM_BD_NM.Trim();				//����������
			NumericString(strMO_ORDR_SN);		//���ֹ��Ϸù�ȣ
			NumericString(strORDR_SN);			//�ֹ��Ϸù�ȣ
			NumericString(strOR_ORDR_SN);		//���ֹ��Ϸù�ȣ
			strPRDT_CD.Trim();					//��ǰ�ڵ�
			strPRDT_NM.Trim();					//��ǰ��
			strDRVS_NMPR_DCD.Trim();			//�Ļ���ǰȣ�������ڵ�
			strDRVS_NMPR_DVSN_NM.Trim();		//�Ļ���ǰȣ�����и�
			NumericString(strORDR_PRC_CTNS);	//�ֹ����ݳ���
			NumericString(strORDR_QNT);			//�ֹ�����
			strCNCS_DVSN_NM.Trim();				//ü�ᱸ�и�
			NumericString(strCNCS_PRC_CTNS);	//ü�ᰡ�ݳ���
			NumericString(strCNCS_QNT);			//ü�����
			strCNCS_DTMD.Trim();				//ü��󼼽ð�
			NumericString(strNCNC_QNT);			//��ü�����
			strDRVS_NMPR_ACPT_DCD.Trim();		//�Ļ���ǰȣ�����������ڵ�
			strDRVS_NMPR_ACPT_DVSN_NM.Trim();	//�Ļ���ǰȣ���������и�
			strHND_DETL_DTM.Trim();				//���ۻ��Ͻ�
			strKRX_MSG_NO.Trim();				//�ѱ��ŷ��Ҹ޽�����ȣ
			NumericString(strCNCS_SN);			//ü���Ϸù�ȣ
			strXTNL_ISTT_RJCT_RSN_CD.Trim();	//�ܺα���źλ����ڵ�
			strCOMM_MDIA_DCD.Trim();			//��Ÿ�ü�����ڵ�

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listExec.InsertItem(&lvItem);

			m_listExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strMNGM_BDCD);		//���������ڵ�
			m_listExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strMNGM_BD_NM);		//����������
			m_listExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strMO_ORDR_SN);		//���ֹ��Ϸù�ȣ
			m_listExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strORDR_SN);			//�ֹ��Ϸù�ȣ
			m_listExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strOR_ORDR_SN);		//���ֹ��Ϸù�ȣ
			m_listExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strPRDT_CD);			//��ǰ�ڵ�
			m_listExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strPRDT_NM);			//��ǰ��
			m_listExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strDRVS_NMPR_DCD);		//�Ļ���ǰȣ�������ڵ�
			m_listExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strDRVS_NMPR_DVSN_NM);	//�Ļ���ǰȣ�����и�
			m_listExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strORDR_PRC_CTNS);		//�ֹ����ݳ���
			m_listExec.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strORDR_QNT);		//�ֹ�����
			m_listExec.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strCNCS_DVSN_NM);	//ü�ᱸ�и�
			m_listExec.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strCNCS_PRC_CTNS);	//ü�ᰡ�ݳ���
			m_listExec.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strCNCS_QNT);		//ü�����
			m_listExec.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strCNCS_DTMD);		//ü��󼼽ð�
			m_listExec.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strNCNC_QNT);		//��ü�����
			m_listExec.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strDRVS_NMPR_ACPT_DCD);		//�Ļ���ǰȣ�����������ڵ�
			m_listExec.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strDRVS_NMPR_ACPT_DVSN_NM);	//�Ļ���ǰȣ���������и�
			m_listExec.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strHND_DETL_DTM);	//���ۻ��Ͻ�
			m_listExec.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strKRX_MSG_NO);		//�ѱ��ŷ��Ҹ޽�����ȣ
			m_listExec.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strCNCS_SN);		//ü���Ϸù�ȣ
			m_listExec.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strXTNL_ISTT_RJCT_RSN_CD);	//�ܺα���źλ����ڵ�
			m_listExec.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strCOMM_MDIA_DCD);	//��Ÿ�ü�����ڵ�

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
			strCTNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CTNO", nRow);		//���հ��´�ü��ȣ
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
	//������(��Ź��) ��ȸ
	else if (m_nRqIdDepositList == nRequestId)
	{
		CString strOPMK_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPMK_DPST_TOT_AMT", 0);		//���忹Ź�ѱݾ�
		CString strOPMK_DPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPMK_DPST_CSH", 0);		//���忹Ź����
		CString strOPMK_DPST_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPMK_DPST_SBST_AMT", 0);		//���忹Ź���ݾ�
		CString strFTR_EXCAL_DEB_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_EXCAL_DEB_AMT", 0);		//�����������ݱݾ�
		CString strOPT_STL_DEB_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_STL_DEB_AMT", 0);		//�ɼǰ������ݱݾ�
		CString strFEE_SMM_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FEE_SMM_AMT", 0);		//�������հ�ݾ�
		CString strRNDR_SMM = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "RNDR_SMM", 0);		//������հ�
		CString strEVL_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "EVL_DPST_TOT_AMT", 0);		//�򰡿�Ź�ѱݾ�
		CString strFTR_RLZ_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_RLZ_PFLS_AMT", 0);		//�����������ͱݾ�
		CString strOPT_RLZ_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_RLZ_PFLS_AMT", 0);		//�ɼǽ������ͱݾ�
		CString strFTR_FEE = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_FEE", 0);		//����������
		CString strRCTM_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "RCTM_AMT", 0);		//�Աݱݾ�
		CString strEVL_DPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "EVL_DPST_CSH", 0);		//�򰡿�Ź����
		CString strFTR_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_EVL_PFLS_AMT", 0);		//�����򰡼��ͱݾ�
		CString strOPT_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_EVL_PFLS_AMT", 0);		//�ɼ��򰡼��ͱݾ�
		CString strOPT_FEE = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_FEE", 0);		//�ɼǼ�����
		CString strDRWG_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DRWG_AMT", 0);		//��ݱݾ�
		CString strSTL_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "STL_DPST_TOT_AMT", 0);		//������Ź�ѱݾ�
		CString strDPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DPST_TOT_AMT", 0);		//��Ź�ѱݾ�
		CString strCSGN_WMY_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "CSGN_WMY_TOT_AMT", 0);		//��Ź���ű��ѱݾ�
		CString strADIT_WMY_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ADIT_WMY_TOT_AMT", 0);		//�߰����ű��ѱݾ�
		CString strORDR_PSBL_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ORDR_PSBL_TOT_AMT", 0);		//�ֹ������ѱݾ�
		CString strWDRW_PSBL_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WDRW_PSBL_TOT_AMT", 0);		//���Ⱑ���ѱݾ�
		CString strDPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DPST_CSH", 0);		//��Ź����
		CString strCSGN_WMY_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "CSGN_WMY_CSH", 0);		//��Ź���ű�����
		CString strADIT_WMY_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ADIT_WMY_CSH", 0);		//�߰����ű�����
		CString strORDR_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ORDR_PSBL_CSH", 0);		//�ֹ���������
		CString strWDRW_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WDRW_PSBL_CSH", 0);		//���Ⱑ������
		CString strDPST_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DPST_SBST_AMT", 0);		//��Ź���ݾ�
		CString strWMY_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WMY_SBST_AMT", 0);		//���űݴ��ݾ�
		CString strADIT_WMY_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ADIT_WMY_SBST_AMT", 0);		//�߰����űݴ��ݾ�
		CString strORDR_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ORDR_PSBL_SBST_AMT", 0);		//�ֹ����ɴ��ݾ�
		CString strWDRW_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WDRW_PSBL_SBST_AMT", 0);		//���Ⱑ�ɴ��ݾ�
		CString strFTR_USTL_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_USTL_TOT_QNT", 0);		//�����̰����Ѽ���
		CString strOPT_USTL_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_USTL_TOT_QNT", 0);		//�ɼǹ̰����Ѽ���
		CString strFTR_CTRC_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_CTRC_TOT_AMT", 0);		//���������ѱݾ�
		CString strOPT_CTRC_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_CTRC_TOT_AMT", 0);		//�ɼǾ����ѱݾ�
		CString strFTR_TR_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_TR_TOT_QNT", 0);		//�����ŷ��Ѽ���
		CString strOPT_TR_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_TR_TOT_QNT", 0);		//�ɼǰŷ��Ѽ���
		CString strFTR_SELL_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_SELL_USTL_QNT", 0);		//�����ŵ��̰�������
		CString strOPT_SELL_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_SELL_USTL_QNT", 0);		//�ɼǸŵ��̰�������
		CString strFTR_SELL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_SELL_CTRC_AMT", 0);		//�����ŵ������ݾ�
		CString strOPT_SELL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_SELL_CTRC_AMT", 0);		//�ɼǸŵ������ݾ�
		CString strFTR_SELL_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_SELL_TR_QNT", 0);		//�����ŵ��ŷ�����
		CString strOPT_SELL_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_SELL_TR_QNT", 0);		//�ɼǸŵ��ŷ�����
		CString strFTR_BUY_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_BUY_USTL_QNT", 0);		//�����ż��̰�������
		CString strOPT_BUY_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_BUY_USTL_QNT", 0);		//�ɼǸż��̰�������
		CString strFTR_BUY_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_BUY_CTRC_AMT", 0);		//�����ż������ݾ�
		CString strOPT_BUY_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_BUY_CTRC_AMT", 0);		//�ɼǸż������ݾ�
		CString strFTR_BUY_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_BUY_TR_QNT", 0);		//�����ż��ŷ�����
		CString strOPT_BUY_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_BUY_TR_QNT", 0);		//�ɼǸż��ŷ�����
		CString strNOW_TOT_WMY_RT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "NOW_TOT_WMY_RT", 0);		//���������ű���
		CString strCSH_WMY_RT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "CSH_WMY_RT", 0);		//�������ű���
		CString strMNTN_WMY = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "MNTN_WMY", 0);		//�������ű�

		NumericString(strOPMK_DPST_TOT_AMT);
		NumericString(strOPMK_DPST_CSH);
		NumericString(strOPMK_DPST_SBST_AMT);
		NumericString(strFTR_EXCAL_DEB_AMT);
		NumericString(strOPT_STL_DEB_AMT);
		NumericString(strFEE_SMM_AMT);
		NumericString(strRNDR_SMM);
		NumericString(strEVL_DPST_TOT_AMT);
		NumericString(strFTR_RLZ_PFLS_AMT);
		NumericString(strOPT_RLZ_PFLS_AMT);
		NumericString(strFTR_FEE);
		NumericString(strRCTM_AMT);
		NumericString(strEVL_DPST_CSH);
		NumericString(strFTR_EVL_PFLS_AMT);
		NumericString(strOPT_EVL_PFLS_AMT);
		NumericString(strOPT_FEE);
		NumericString(strDRWG_AMT);
		NumericString(strSTL_DPST_TOT_AMT);
		NumericString(strDPST_TOT_AMT);
		NumericString(strCSGN_WMY_TOT_AMT);
		NumericString(strADIT_WMY_TOT_AMT);
		NumericString(strORDR_PSBL_TOT_AMT);
		NumericString(strWDRW_PSBL_TOT_AMT);
		NumericString(strDPST_CSH);
		NumericString(strCSGN_WMY_CSH);
		NumericString(strADIT_WMY_CSH);
		NumericString(strORDR_PSBL_CSH);
		NumericString(strWDRW_PSBL_CSH);
		NumericString(strDPST_SBST_AMT);
		NumericString(strWMY_SBST_AMT);
		NumericString(strADIT_WMY_SBST_AMT);
		NumericString(strORDR_PSBL_SBST_AMT);
		NumericString(strWDRW_PSBL_SBST_AMT);
		NumericString(strFTR_USTL_TOT_QNT);
		NumericString(strOPT_USTL_TOT_QNT);
		NumericString(strFTR_CTRC_TOT_AMT);
		NumericString(strOPT_CTRC_TOT_AMT);
		NumericString(strFTR_TR_TOT_QNT);
		NumericString(strOPT_TR_TOT_QNT);
		NumericString(strFTR_SELL_USTL_QNT);
		NumericString(strOPT_SELL_USTL_QNT);
		NumericString(strFTR_SELL_CTRC_AMT);
		NumericString(strOPT_SELL_CTRC_AMT);
		NumericString(strFTR_SELL_TR_QNT);
		NumericString(strOPT_SELL_TR_QNT);
		NumericString(strFTR_BUY_USTL_QNT);
		NumericString(strOPT_BUY_USTL_QNT);
		NumericString(strFTR_BUY_CTRC_AMT);
		NumericString(strOPT_BUY_CTRC_AMT);
		NumericString(strFTR_BUY_TR_QNT);
		NumericString(strOPT_BUY_TR_QNT);
		NumericString(strNOW_TOT_WMY_RT);
		NumericString(strCSH_WMY_RT);
		NumericString(strMNTN_WMY);

		CString strOutString;
		strOutString = "���忹Ź����(" + strOPMK_DPST_CSH + "),\t\t\t���忹Ź���ݾ�(" + strOPMK_DPST_SBST_AMT + ")\r\n" +
			"�����������ݱݾ�(" + strFTR_EXCAL_DEB_AMT + "),\t\t\t�ɼǰ������ݱݾ�(" + strOPT_STL_DEB_AMT + ")\r\n" +
			"�������հ�ݾ�(" + strFEE_SMM_AMT + "),\t\t\t������հ�(" + strRNDR_SMM + ")\r\n" +
			"�򰡿�Ź�ѱݾ�(" + strEVL_DPST_TOT_AMT + "),\t\t\t�����������ͱݾ�(" + strFTR_RLZ_PFLS_AMT + ")\r\n" +
			"�ɼǽ������ͱݾ�(" + strOPT_RLZ_PFLS_AMT + "),\t\t\t����������(" + strFTR_FEE + ")\r\n" +
			"�Աݱݾ�(" + strRCTM_AMT + "),\t\t\t�򰡿�Ź����(" + strEVL_DPST_CSH + ")\r\n" +
			"�����򰡼��ͱݾ�(" + strFTR_EVL_PFLS_AMT + "),\t\t\t�ɼ��򰡼��ͱݾ�(" + strOPT_EVL_PFLS_AMT + ")\r\n" +
			"�ɼǼ�����(" + strOPT_FEE + "),\t\t\t��ݱݾ�(" + strDRWG_AMT + ")\r\n" +
			"������Ź�ѱݾ�(" + strSTL_DPST_TOT_AMT + "),\t\t\t��Ź�ѱݾ�(" + strDPST_TOT_AMT + ")\r\n" +
			"��Ź���ű��ѱݾ�(" + strCSGN_WMY_TOT_AMT + "),\t\t\t�߰����ű��ѱݾ�(" + strADIT_WMY_TOT_AMT + ")\r\n" +
			"�ֹ������ѱݾ�(" + strORDR_PSBL_TOT_AMT + "),\t\t\t���Ⱑ���ѱݾ�(" + strWDRW_PSBL_TOT_AMT + ")\r\n" +
			"��Ź����(" + strDPST_CSH + "),\t\t\t��Ź���ű�����(" + strCSGN_WMY_CSH + ")\r\n" +
			"�߰����ű�����(" + strADIT_WMY_CSH + "),\t\t\t�ֹ���������(" + strORDR_PSBL_CSH + ")\r\n" +
			"���Ⱑ������(" + strWDRW_PSBL_CSH + "),\t\t\t��Ź���ݾ�(" + strDPST_SBST_AMT + ")\r\n" +
			"���űݴ��ݾ�(" + strWMY_SBST_AMT + "),\t\t\t�߰����űݴ��ݾ�(" + strADIT_WMY_SBST_AMT + ")\r\n" +
			"�ֹ����ɴ��ݾ�(" + strORDR_PSBL_SBST_AMT + "),\t\t\t���Ⱑ�ɴ��ݾ�(" + strWDRW_PSBL_SBST_AMT + ")\r\n" +
			"�����̰����Ѽ���(" + strFTR_USTL_TOT_QNT + "),\t\t\t�ɼǹ̰����Ѽ���(" + strOPT_USTL_TOT_QNT + ")\r\n" +
			"���������ѱݾ�(" + strFTR_CTRC_TOT_AMT + "),\t\t\t�ɼǾ����ѱݾ�(" + strOPT_CTRC_TOT_AMT + ")\r\n" +
			"�����ŷ��Ѽ���(" + strFTR_TR_TOT_QNT + "),\t\t\t�ɼǰŷ��Ѽ���(" + strOPT_TR_TOT_QNT + ")\r\n" +
			"�����ŵ��̰�������(" + strFTR_SELL_USTL_QNT + "),\t\t\t�ɼǸŵ��̰�������(" + strOPT_SELL_USTL_QNT + ")\r\n" +
			"�����ŵ������ݾ�(" + strFTR_SELL_CTRC_AMT + "),\t\t\t�ɼǸŵ������ݾ�(" + strOPT_SELL_CTRC_AMT + ")\r\n" +
			"�����ŵ��ŷ�����(" + strFTR_SELL_TR_QNT + "),\t\t\t�ɼǸŵ��ŷ�����(" + strOPT_SELL_TR_QNT + ")\r\n" +
			"�����ż��̰�������(" + strFTR_BUY_USTL_QNT + "),\t\t\t�ɼǸż��̰�������(" + strOPT_BUY_USTL_QNT + ")\r\n" +
			"�����ż������ݾ�(" + strFTR_BUY_CTRC_AMT + "),\t\t\t�ɼǸż������ݾ�(" + strOPT_BUY_CTRC_AMT + ")\r\n" +
			"�����ż��ŷ�����(" + strFTR_BUY_TR_QNT + "),\t\t\t�ɼǸż��ŷ�����(" + strOPT_BUY_TR_QNT + ")\r\n" +
			"���������ű���(" + strNOW_TOT_WMY_RT + "),\t\t\t�������ű���(" + strCSH_WMY_RT + ")\r\n" +
			"�������ű�(" + strMNTN_WMY + ")";

		GetDlgItem(IDC_EDIT_DEPOSIT)->SetWindowText(strOutString);


		/*--------------------------------------
		  �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdDepositList = 0;	//������

	}
	//�ܰ� ��ȸ
	else if (m_nRqIdBalanceList == nRequestId)
	{
		CString strPRDT_CD;				//��ǰ�ڵ�
		CString strPRDT_NM;				//��ǰ��
		CString strSELL_BUY_DCD;		//�ŵ��ż������ڵ�
		CString strSELL_BUY_DVSN_NM;	//�ŵ��ż����и�
		CString strUSTL_CTRC_QNT;		//�̰�����������
		CString strAVR_PRC;				//��հ���
		CString strNOW_PRC;				//���簡��
		CString strEVL_AMT;				//�򰡱ݾ�
		CString strEVL_PFLS_AMT;		//�򰡼��ͱݾ�
		CString strPFLS_RT;				//������
		CString strCLR_PSBL_QNT;		//û�갡�ɼ���
		CString strPCHS_ACBK_AMT;		//������αݾ�

		m_listBalance.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;

		/*--------------------------------------
		  ���� ��ȸ ������ �����̸� ������ ���� ����Ÿ �ڿ�
		  �ٿ� �����Ѵ�.
		 ---------------------------------------*/
		int nViewScrollPos = 0;

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OTS2850Q18_out_sub01");

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strPRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
			strPRDT_NM = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "PRDT_NM", nRow);		//��ǰ��
			strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "SELL_BUY_DCD", nRow);		//�ŵ��ż������ڵ�
			strSELL_BUY_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//�ŵ��ż����и�
			strUSTL_CTRC_QNT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "USTL_CTRC_QNT", nRow);		//�̰�����������
			strAVR_PRC = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "AVR_PRC", nRow);		//��հ���
			strNOW_PRC = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "NOW_PRC", nRow);		//���簡��
			strEVL_AMT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "EVL_AMT", nRow);		//�򰡱ݾ�
			strEVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "EVL_PFLS_AMT", nRow);		//�򰡼��ͱݾ�
			strPFLS_RT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "PFLS_RT", nRow);		//������
			strCLR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "CLR_PSBL_QNT", nRow);		//û�갡�ɼ���
			strPCHS_ACBK_AMT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "PCHS_ACBK_AMT", nRow);		//������αݾ�

			strPRDT_CD.Trim();
			strPRDT_NM.Trim();
			strSELL_BUY_DVSN_NM.Trim();
			strSELL_BUY_DCD.Trim();
			NumericString(strUSTL_CTRC_QNT);
			NumericString(strAVR_PRC);
			NumericString(strNOW_PRC);
			NumericString(strEVL_AMT);
			NumericString(strEVL_PFLS_AMT);
			NumericString(strPFLS_RT);
			NumericString(strCLR_PSBL_QNT);
			NumericString(strPCHS_ACBK_AMT);

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listBalance.InsertItem(&lvItem);

			m_listBalance.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strPRDT_CD);				//��ǰ�ڵ�
			m_listBalance.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strPRDT_NM);				//��ǰ��
			m_listBalance.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strSELL_BUY_DCD);			//�ŵ��ż������ڵ�
			m_listBalance.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strSELL_BUY_DVSN_NM);		//�ŵ��ż����и�
			m_listBalance.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strUSTL_CTRC_QNT);		//�̰�����������
			m_listBalance.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strAVR_PRC);				//��հ���
			m_listBalance.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strNOW_PRC);				//���簡��
			m_listBalance.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strEVL_AMT);				//�򰡱ݾ�
			m_listBalance.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strEVL_PFLS_AMT);			//�򰡼��ͱݾ�
			m_listBalance.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strPFLS_RT);				//������
			m_listBalance.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strCLR_PSBL_QNT);		//û�갡�ɼ���
			m_listBalance.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strPCHS_ACBK_AMT);		//������αݾ�

			nListIndex++;
		}

		m_listBalance.EnsureVisible(0, FALSE);
		m_listBalance.SetRedraw(TRUE);

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
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS2100U10_out", "ORDR_SN", 0);		//�ֹ���ȣ
		NumericString(strODRV_ODNO, TRUE);

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		  �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdSellOrd = 0;
	}
	//�ż��ֹ� Request ID
	else if (m_nRqIdBuyOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS2100U20_out", "ORDR_SN", 0);		//�ֹ���ȣ
		NumericString(strODRV_ODNO, TRUE);

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		  �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdBuyOrd = 0;
	}
	//�����ֹ� Request ID
	else if (m_nRqIdChangeOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS2100U30_out", "ORDR_SN", 0);		//�ֹ���ȣ
		NumericString(strODRV_ODNO, TRUE);

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		  �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdChangeOrd = 0;
	}
	//����ֹ� Request ID
	else if (m_nRqIdCancelOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS2100U40_out", "ORDR_SN", 0);		//�ֹ���ȣ
		NumericString(strODRV_ODNO, TRUE);

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
void CEurexFutOptOrdDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
void CEurexFutOptOrdDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/*	���� : OnGetRealData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
		�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/
	CString strRealMessage;
	CString strTemp;

	/***************************************
	 * ���������ɼ� �ֹ�Ȯ��/ü��/��ü��(����/���) �ǽð� �뺸
	 ****************************************/
	if (!_tcscmp(strRealName, "EF5"))
	{
		/*--------------------------------------
		 �����۸����� ���ŵ� �ǽð� �����͸� �׸񺰷� ������.
		 ---------------------------------------*/
		CString strsDataType = m_CommAgent.GetRealOutputData("EF5", "sDataType");		//�����ͱ���
		CString strsProcTime = m_CommAgent.GetRealOutputData("EF5", "sProcTime");		//ó���ð�
		CString strsComCode = m_CommAgent.GetRealOutputData("EF5", "sComCode");		//��ü����
		CString strsUserID = m_CommAgent.GetRealOutputData("EF5", "sUserID");		//�����ID
		CString strsCtno = m_CommAgent.GetRealOutputData("EF5", "sCtno");		//���´�ü��ȣ
		CString strsAcctNo = m_CommAgent.GetRealOutputData("EF5", "sAcctNo");		//���¹�ȣ
		CString strsAcctName = m_CommAgent.GetRealOutputData("EF5", "sAcctName");		//���¸�
		CString strsBidCode = m_CommAgent.GetRealOutputData("EF5", "sBidCode");		//�ֹ�����
		CString strsModType = m_CommAgent.GetRealOutputData("EF5", "sModType");		//������ұ���
		CString strsItemCode = m_CommAgent.GetRealOutputData("EF5", "sItemCode");		//���������ڵ�
		CString strsItemName = m_CommAgent.GetRealOutputData("EF5", "sItemName");		//�����
		CString strsOrdVol = m_CommAgent.GetRealOutputData("EF5", "sOrdVol");		//�ֹ�����
		CString strsOrdPrice = m_CommAgent.GetRealOutputData("EF5", "sOrdPrice");		//�ֹ�����
		CString strsHogaType = m_CommAgent.GetRealOutputData("EF5", "sHogaType");		//ȣ������
		CString strsOrderCon = m_CommAgent.GetRealOutputData("EF5", "sOrderCon");		//�ֹ�����
		CString strsBrnNo = m_CommAgent.GetRealOutputData("EF5", "sBrnNo");		//������ȣ
		CString strsOrdNo = m_CommAgent.GetRealOutputData("EF5", "sOrdNo");		//�ֹ���ȣ
		CString strsOrgOrdNo = m_CommAgent.GetRealOutputData("EF5", "sOrgOrdNo");		//���ֹ���ȣ
		CString strsContVol = m_CommAgent.GetRealOutputData("EF5", "sContVol");		//ü�����
		CString strsContPrice = m_CommAgent.GetRealOutputData("EF5", "sContPrice");		//ü�ᰡ��
		CString strsRejectCode = m_CommAgent.GetRealOutputData("EF5", "sRejectCode");		//�źλ����ڵ�
		CString strsRejectReason = m_CommAgent.GetRealOutputData("EF5", "sRejectReason");		//�źλ���
		CString strsUnContVol = m_CommAgent.GetRealOutputData("EF5", "sUnContVol");		//��ü�����
		CString strsFotsTradeUnit = m_CommAgent.GetRealOutputData("EF5", "sFotsTradeUnit");		//�ŷ��¼�
		CString strsChegNo = m_CommAgent.GetRealOutputData("EF5", "sChegNo");		//ü���ȣ
		CString strsFstPrc = m_CommAgent.GetRealOutputData("EF5", "sFstPrc");		//�ٿ��� ü�ᰡ��(��������)
		CString strsSndPrc = m_CommAgent.GetRealOutputData("EF5", "sSndPrc");		//������ ü�ᰡ��(��������)
		CString strsWrapNo = m_CommAgent.GetRealOutputData("EF5", "sWrapNo");		//Wrap�ֹ���ȣ
		CString strsGroupNo = m_CommAgent.GetRealOutputData("EF5", "sGroupNo");		//�׷��ȣ
		CString strsSeqNo = m_CommAgent.GetRealOutputData("EF5", "sSeqNo");		//�ٽ��Ͻ�����
		CString strsFee = m_CommAgent.GetRealOutputData("EF5", "sFee");		//������
		CString strsDvrsExcgDcd = m_CommAgent.GetRealOutputData("EF5", "sDvrsExcgDcd");		//�Ļ���ǰ�ŷ��ұ����ڵ�
		CString strsFiller = m_CommAgent.GetRealOutputData("EF5", "sFiller");		//Filler

		strsAcctNo.Trim();
		strsItemName.Trim();

		NumericString(strsUnContVol);		//��ü�����
		NumericString(strsContVol);			//ü�����

		//01:ü��, 02 : ����Ȯ��, 03 : ���Ȯ��, 04 : �ź�, 21 : ����, 29 : ��������(01~21 �ŷ�������, 29 FEP����)
		switch (_ttoi(strsDataType))
		{
			case 1:		//ü��
			strTemp = "ü��";
			break;
			case 2:		//����Ȯ��
			strTemp = "����Ȯ��";
			break;
			case 3:		//���Ȯ��
			strTemp = "���Ȯ��";
			break;
			case 4:		//�ź�
			strTemp = "�ź�";
			break;
			case 21:	//����
			strTemp = "����";
			break;
			case 29:	//��������
			strTemp = "��������";
			break;
		}//End of switch

		/*--------------------------------------
		��ȸ ������ ����� �ֽ� ���簡 �ǽð�Ű�� �������� ��
		---------------------------------------*/
		if (m_strLoginID == strRealKey)
		{
			strRealMessage.Format("[%s][����:%s][����:%s][��ǰ:%s][��ü��:%s][Ȯ��/ü��:%s]", strRealName, strTemp, strsAcctNo, strsItemName, strsUnContVol, strsContVol);
		}//End of if

	}

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


void CEurexFutOptOrdDlg::OnBnClickedButtonTest()
{
	CString strAccNo, strAPNO;
	CString strAccPwd;

	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);		//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strAccPwd);	//��й�ȣ

	CString strCTNO = GetAccAPNO(strAccNo + strAPNO);		//���հ��´�ü��ȣ ������
	CString strACNT_PWD = m_CommAgent.GetEncrpyt(strAccPwd);//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.

	int nRequestId = m_CommAgent.CreateRequestID();

	m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "CTNO", strCTNO);			//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "APNO", strAPNO);			//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "PWD", strAccPwd);			//��й�ȣ
	m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "INQ_DVSN", _T("1"));		//��ȸ����
	m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "TRDE_CT_INCL_YN", _T("N"));//�Ÿź�����Կ���

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "DAPI";	//ȭ���ȣ

	if (m_CommAgent.RequestTran(nRequestId, "OTS1841Q00", strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}
