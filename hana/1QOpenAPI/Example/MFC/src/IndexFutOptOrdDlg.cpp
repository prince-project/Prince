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
#include "IndexFutOptOrdDlg.h"

#define ID_SECOND_TIMER		100	//1�� ���� Ÿ�̸�

#define SELL_BK_COLOR		RGB(206, 232, 255)	//�ŵ� ����
#define BUY_BK_COLOR		RGB(251, 221, 255)	//�ż� ����

//��� ����ü ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern void NumericString(CString& strValue, BOOL bNotDisplayZero = FALSE);

static char* g_szOrderType[] = { "01", "02", "03", "04" }; //ȣ������ : 01:������, 02:���Ǻ�������, 03:���尡, 04:����������
static char g_cPriceCont[3] = { ' ' , 'I', 'F' };	//�ֹ����� : ����, IOC, FOK

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

// CIndexFutOptOrdDlg ��ȭ ����
CIndexFutOptOrdDlg::CIndexFutOptOrdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIndexFutOptOrdDlg::IDD, pParent)
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

void CIndexFutOptOrdDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_DATETIME1, m_dateTime1);
	DDX_Control(pDX, IDC_CMB_ORD_COND, m_cmbOrdCond);
	DDX_Control(pDX, IDC_DATETIME2, m_dateTime2);
	DDX_Control(pDX, IDC_DATETIME3, m_dateTime3);
}

BEGIN_MESSAGE_MAP(CIndexFutOptOrdDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_LOGIN, &CIndexFutOptOrdDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_LOGOUT, &CIndexFutOptOrdDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDOK, &CIndexFutOptOrdDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELL, &CIndexFutOptOrdDlg::OnBnClickedBtnSell)
	ON_BN_CLICKED(IDC_BTN_BUY, &CIndexFutOptOrdDlg::OnBnClickedBtnBuy)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CIndexFutOptOrdDlg::OnBnClickedBtnChange)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CIndexFutOptOrdDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST, &CIndexFutOptOrdDlg::OnBnClickedBtnReqExecList)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST_NEXT, &CIndexFutOptOrdDlg::OnBnClickedBtnReqExecListNext)
	ON_BN_CLICKED(IDC_BTN_REQ_ACCNO, &CIndexFutOptOrdDlg::OnBnClickedBtnReqAccno)
	ON_BN_CLICKED(IDC_BTN_REQ_DEPOSIT, &CIndexFutOptOrdDlg::OnBnClickedBtnReqDeposit)
	ON_BN_CLICKED(IDC_BTN_REQ_BALANCE, &CIndexFutOptOrdDlg::OnBnClickedBtnReqBalance)
	ON_BN_CLICKED(IDC_BTN_REQ_BALANCE_NEXT, &CIndexFutOptOrdDlg::OnBnClickedBtnReqBalanceNext)
	ON_BN_CLICKED(IDC_BTN_LOAD_USER_ACC, &CIndexFutOptOrdDlg::OnBnClickedBtnLoadUserAcc)
	ON_COMMAND_RANGE(IDC_CON_REAL, IDC_CON_F_DEMO, &CIndexFutOptOrdDlg::OnRdoSelectServer)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCNO, &CIndexFutOptOrdDlg::OnNMDblclkListAccNo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ORD, &CIndexFutOptOrdDlg::OnNMDblclkListExec)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BALANCE, &CIndexFutOptOrdDlg::OnNMDblclkListBalance)

END_MESSAGE_MAP()

// agent�κ��� �̺�Ʈ ���� �Լ��� �����Ѵ�.
BEGIN_EVENTSINK_MAP(CIndexFutOptOrdDlg, CDialog)
	ON_EVENT(CIndexFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 1, CIndexFutOptOrdDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CIndexFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 2, CIndexFutOptOrdDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CIndexFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 3, CIndexFutOptOrdDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
END_EVENTSINK_MAP()

// CIndexFutOptOrdDlg �޽��� ó����
void CIndexFutOptOrdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CIndexFutOptOrdDlg::OnPaint()
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
HCURSOR CIndexFutOptOrdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CIndexFutOptOrdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CIndexFutOptOrdDlg::OnNMDblclkListAccNo(NMHDR *pNMHDR, LRESULT *pResult)
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

void CIndexFutOptOrdDlg::OnNMDblclkListExec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;

	CString strOrdOrg = m_listExec.GetItemText(nSelectRow, 0);
	CString strSymbol = m_listExec.GetItemText(nSelectRow, 2);
	CString strOrdPrice = m_listExec.GetItemText(nSelectRow, 8);
	CString strOrdSu = m_listExec.GetItemText(nSelectRow, 15);
	
	GetDlgItem(IDC_EDIT_ORG_NO)->SetWindowText(strOrdOrg);
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);
	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);
}

void CIndexFutOptOrdDlg::OnNMDblclkListBalance(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	
	CString strSymbol = m_listBalance.GetItemText(nSelectRow, 0);
	CString strOrdPrice = m_listBalance.GetItemText(nSelectRow, 7);
	CString strOrdSu = m_listBalance.GetItemText(nSelectRow, 5);
	
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);
	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);
}

void CIndexFutOptOrdDlg::OnDestroy()
{
	//��� �ǽð������ �����Ѵ�.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();
	
	CDialog::OnDestroy();
}

void CIndexFutOptOrdDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CIndexFutOptOrdDlg::OnTimer(UINT_PTR nIDEvent)
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
void CIndexFutOptOrdDlg::OnRdoSelectServer(UINT nID)
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
BOOL CIndexFutOptOrdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CString strTitle;
	strTitle.Format("%s-[�������� �ֹ�](%s)", PROGRAM_NAME, VERSION_INFO);
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
void CIndexFutOptOrdDlg::InitListAccNo()
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
void CIndexFutOptOrdDlg::InitListReal()
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
void CIndexFutOptOrdDlg::InitListExec()
{
	CRect rc;
	m_listExec.GetClientRect(rc);
	m_listExec.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("�ֹ���ȣ"), _T("���ֹ���ȣ"), _T("��ǰ�ڵ�"), _T("�����ڵ�"), _T("��ǰ��"),
		_T("�Ÿű��и�"), _T("ȣ�������ڵ�"), _T("ȣ�������ڵ�"), _T("�ֹ����ݱݾ�"), _T("�ֹ�����"),
		_T("ü�ᱸ�и�"), _T("ü�����"), _T("ü�ᰡ�ݱݾ�"), _T("�ѱ�ü��ð�"), _T("�������Ȯ�μ���"), _T("��ü�����"),
		_T("���������ڵ�"), _T("�������и�"), _T("�ŷ��������ð�"), _T("�ŷ��Ҹ޽���"), _T("��Ÿ�ü����"),
		_T("�ܺα���źλ����ڵ�") };

	int i;
	for (i = 0; i < 22; i++)
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
void CIndexFutOptOrdDlg::InitListBalance()
{
	CRect rc;
	m_listBalance.GetClientRect(rc);
	m_listBalance.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("��ǰ�ڵ�"), _T("�����ǰ�ڵ�"), _T("��ǰ��"), _T("�Ÿű���"),
		_T("�Ÿű����ڵ�"), _T("�̰�������"), _T("��հ���"), _T("���簡��"), _T("���"),
		_T("�򰡱ݾ�"), _T("�򰡼���"), _T("������"), _T("û�갡��"), _T("���Աݾ�") };

	int i;
	for (i = 0; i < 14; i++)
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
void CIndexFutOptOrdDlg::OnBnClickedLogin()
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
	m_CommAgent.RegisterReal("IF0", m_strLoginID);
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : �α׾ƿ�
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CIndexFutOptOrdDlg::OnBnClickedLogout()
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
void CIndexFutOptOrdDlg::OnBnClickedOk()
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
void CIndexFutOptOrdDlg::OnBnClickedBtnReqAccno()
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
void CIndexFutOptOrdDlg::OnBnClickedBtnLoadUserAcc()
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
CString CIndexFutOptOrdDlg::GetAccAPNO(CString strAccNo)
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
void CIndexFutOptOrdDlg::RequestAccList()
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
void CIndexFutOptOrdDlg::RequestFDemoAccList()
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
BOOL CIndexFutOptOrdDlg::SendSellBuyOrder(CString strDealSide, int nRqId)
{
	CString strInRecName;
	CString strTrCode;
	
	//�Է��׸� ������
	CString strCTNO;				//��ü���հ��¹�ȣ
	CString strAPNO;				//���»�ǰ��ȣ
	CString strACNT_PWD;			//��й�ȣ
	CString strSELL_BUY_DCD;		//��ǰ�ڵ�
	CString strPRDT_CD;				//�ŵ��ż������ڵ�
	CString strDRVS_NMPR_DCD;		//�������Ǳ����ڵ�
	CString strORDR_PRC;			//�ֹ�����
	CString strORDR_QNT;			//�ֹ�����
	CString strPWD_CNFM_YN("Y");	//��й�ȣȮ�ο���
	CString strCVRG_YN("N");		//�ݴ�Ÿſ���
	CString strDRVS_ORDR_CND_DCD;	//�ֹ�����(' ' : ����, 'I' : IOC, 'F' : FOK)

	if (strDealSide == "S") //�ŵ�
	{
		strTrCode = "OTS2100U10";
		strSELL_BUY_DCD = "1";
	}
	else if (strDealSide == "B") //�ż�
	{
		strTrCode = "OTS2100U20";
		strSELL_BUY_DCD = "2";
	}

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
void CIndexFutOptOrdDlg::OnBnClickedBtnSell()
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
void CIndexFutOptOrdDlg::OnBnClickedBtnBuy()
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
void CIndexFutOptOrdDlg::OnBnClickedBtnChange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS2100U30";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS2100U30_in";	//�Է� ���ڵ��(���ҽ����� ����)
	
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
	
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //���հ��´�ü��ȣ ������

	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);			//��й�ȣ
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);						//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.

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

	CString strBenefitAcc = "N";		//�������ǰ��� ����
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
void CIndexFutOptOrdDlg::OnBnClickedBtnCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS2100U40";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS2100U40_in ";	//�Է� ���ڵ��(���ҽ����� ����)

	//[1] Request ID����
	m_nRqIdCancelOrd = m_CommAgent.CreateRequestID();

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	CString strCTNO;			//���հ��´�ü��ȣ
	CString strAPNO;			//���»�ǰ��ȣ
	CString strACNT_PWD;		//���º�й�ȣ
	CString strOR_ORDR_SN;		//���ֹ��Ϸù�ȣ
	CString strORDR_QNT;		//�ֹ�����
	CString strALL_YN;			//��ü����
	CString strPWD_CNFM_YN("Y");//��й�ȣȮ�ο���

	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//��ü���հ��¹�ȣ

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //���հ��´�ü��ȣ ������

	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);		//��й�ȣ
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);				//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.

	//���ֹ���ȣ
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strOR_ORDR_SN);

	//��Ҽ���
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

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
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ALL_YN", strALL_YN);			//��ü����
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "PWD_CNFM_YN", strPWD_CNFM_YN);	//��й�ȣȮ�ο���

	CString strBenefitAcc = "N";		//�������ǰ��� ����
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
void CIndexFutOptOrdDlg::OnBnClickedBtnReqDeposit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	GetDlgItem(IDC_EVL_DPST_TOT_AMT)->SetWindowText("");	GetDlgItem(IDC_EVL_DPST_CSH)->SetWindowText("");
	GetDlgItem(IDC_DPST_TOT_AMT)->SetWindowText("");		GetDlgItem(IDC_DPST_CSH)->SetWindowText("");
	GetDlgItem(IDC_DPST_SBST)->SetWindowText("");			GetDlgItem(IDC_WDRW_PSBL_TOT_AMT)->SetWindowText("");
	GetDlgItem(IDC_WDRW_PSBL_CSH)->SetWindowText("");		GetDlgItem(IDC_WDRW_PSBL_SBST_AMT)->SetWindowText("");
	GetDlgItem(IDC_ORDR_PSBL_TOT_AMT)->SetWindowText("");	GetDlgItem(IDC_ORDR_PSBL_CSH)->SetWindowText("");
	GetDlgItem(IDC_CSGN_WMY_TOT_AMT)->SetWindowText("");	GetDlgItem(IDC_CSGN_WMY_CSH)->SetWindowText("");
	GetDlgItem(IDC_MNMG_TOT_AMT)->SetWindowText("");		GetDlgItem(IDC_MNMG_CSH)->SetWindowText("");
	GetDlgItem(IDC_ADIT_WMY_TOT_AMT)->SetWindowText("");	GetDlgItem(IDC_ADIT_WMY_CSH)->SetWindowText("");
	GetDlgItem(IDC_EVL_AMT)->SetWindowText("");				GetDlgItem(IDC_EVL_PFLS)->SetWindowText("");
	GetDlgItem(IDC_FEE)->SetWindowText("");					GetDlgItem(IDC_RCVA)->SetWindowText("");
	GetDlgItem(IDC_THDT_PFLS_AMT)->SetWindowText("");

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS2850Q81";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS2850Q81_in";			//�Է� ���ڵ��(���ҽ����� ����)

	/*-------------------------------*
	 [1] Request ID����
	*-------------------------------*/
	m_nRqIdDepositList = m_CommAgent.CreateRequestID();

	CString strCTNO;			//���հ��´�ü��ȣ
	CString strAPNO;			//���»�ǰ��ȣ
	CString strPWD;				//��й�ȣ
	CString strINQ_DT;			//��ȸ����
	CString strINQ_DVSN("1");	//��ȸ����(1:������, 2:������ -  (1:��ü 2:�����ŷ����� �翵������ �ƴѰ��))
	
	//���¹�ȣ
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	
	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //���հ��´�ü��ȣ ������

	//���º��
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD); //��ȣȭ�Ѵ�.

	//��ȸ����
	m_dateTime1.GetWindowText(strINQ_DT);
	strINQ_DT.Remove('-');

	//��ȸ����(1:������, 2:������ -  (1:��ü 2:�����ŷ����� �翵������ �ƴѰ��))
	if (((CButton*)GetDlgItem(IDC_RD_DEP_OPT1))->GetCheck())
		strINQ_DVSN = "1";
	else if(((CButton*)GetDlgItem(IDC_RD_DEP_OPT2))->GetCheck())
		strINQ_DVSN = "2";
	

	/*-------------------------------*
	 [2] Tran��ȸ �Է°��� �Է��Ѵ�.
	 *-------------------------------*/
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "CTNO", strCTNO);			//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "APNO", strAPNO);			//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "PWD", strPWD);			//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "INQ_DT", strINQ_DT);		//��ȸ����
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "INQ_DVSN", strINQ_DVSN);	//��ȸ����

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	
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
void CIndexFutOptOrdDlg::OnBnClickedBtnReqExecList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_listExec.DeleteAllItems();
	m_strListExecNextRqKey.Empty(); //����Ű�� �ʱ�ȭ��Ų��.

	CString strTrCode = "OTS2850Q80";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS2850Q80_in";		//�Է� ���ڵ��(���ҽ����� ����)
	
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
	CString strORDR_STRT_SN;		//�ֹ������Ϸù�ȣ(�ʼ��Է¾ƴ�)
	CString strINQ_DT;				//��ȸ����
	CString strCNCS_NCNC_DCD("0");	//ü���ü�ᱸ���ڵ�(0: ��ü, 1: ü��, 2: ��ü��)
	CString strINQ_CHNL_DVSN("0");	//��ȸä�α���(0: ��ü, 1: ������, 2: ���̹�, 3: �ݼ���)
	CString strSORT_DCD("0");		//���ı����ڵ�(1: ����, �׿� ���� ����)

	//���´�ü��ȣ�� ���´�.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	
	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //���հ��´�ü��ȣ ������

	//���º�й�ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD);

	//��ȸ����
	m_dateTime3.GetWindowText(strINQ_DT);
	strINQ_DT.Remove('-');


	//ü���ü�ᱸ���ڵ�(0: ��ü, 1: ü��, 2: ��ü��)
	if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT1))->GetCheck())
		strCNCS_NCNC_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT2))->GetCheck())
		strCNCS_NCNC_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT3))->GetCheck())
		strCNCS_NCNC_DCD = "2";

	//���ı����ڵ�(1: ����, �׿� ���� ����)
	if (((CButton*)GetDlgItem(IDC_RD_EXE_SORT1))->GetCheck())
		strSORT_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_SORT2))->GetCheck())
		strSORT_DCD = "0";

	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO);						//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strAPNO);						//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD);						//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_STRT_SN", strORDR_STRT_SN);		//�ֹ������Ϸù�ȣ(�ʼ��Է¾ƴ�)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_DT", strINQ_DT);					//��ȸ����
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CNCS_NCNC_DCD", strCNCS_NCNC_DCD);	//ü���ü�ᱸ���ڵ�(0: ��ü, 1: ü��, 2: ��ü��)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_CHNL_DVSN", strINQ_CHNL_DVSN);	//��ȸä�α���(0: ��ü, 1: ������, 2: ���̹�, 3: �ݼ���)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "SORT_DCD", strSORT_DCD);				//���ı����ڵ�(1: ����, �׿� ���� ����)

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
void CIndexFutOptOrdDlg::OnBnClickedBtnReqExecListNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS2850Q80";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS2850Q80_in";		//�Է� ���ڵ��(���ҽ����� ����)

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
	CString strORDR_STRT_SN;		//�ֹ������Ϸù�ȣ(�ʼ��Է¾ƴ�)
	CString strINQ_DT;				//��ȸ����
	CString strCNCS_NCNC_DCD("0");	//ü���ü�ᱸ���ڵ�(0: ��ü, 1: ü��, 2: ��ü��)
	CString strINQ_CHNL_DVSN("0");	//��ȸä�α���(0: ��ü, 1: ������, 2: ���̹�, 3: �ݼ���)
	CString strSORT_DCD("1");		//���ı����ڵ�(1: ����, �׿� ���� ����)

	//���´�ü��ȣ�� ���´�.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	
	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //���հ��´�ü��ȣ ������

	//���º�й�ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD);

	//��ȸ����
	m_dateTime3.GetWindowText(strINQ_DT);
	strINQ_DT.Remove('-');

	//ü���ü�ᱸ���ڵ�(0: ��ü, 1: ü��, 2: ��ü��)
	if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT1))->GetCheck())
		strCNCS_NCNC_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT2))->GetCheck())
		strCNCS_NCNC_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT3))->GetCheck())
		strCNCS_NCNC_DCD = "2";

	//���ı����ڵ�(1: ����, �׿� ���� ����)
	if (((CButton*)GetDlgItem(IDC_RD_EXE_SORT1))->GetCheck())
		strSORT_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_SORT2))->GetCheck())
		strSORT_DCD = "0";

	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO);						//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strAPNO);						//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD);						//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_STRT_SN", strORDR_STRT_SN);		//�ֹ������Ϸù�ȣ(�ʼ��Է¾ƴ�)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_DT", strINQ_DT);					//��ȸ����
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CNCS_NCNC_DCD", strCNCS_NCNC_DCD);	//ü���ü�ᱸ���ڵ�(0: ��ü, 1: ü��, 2: ��ü��)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_CHNL_DVSN", strINQ_CHNL_DVSN);	//��ȸä�α���(0: ��ü, 1: ������, 2: ���̹�, 3: �ݼ���)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "SORT_DCD", strSORT_DCD);				//���ı����ڵ�(1: ����, �׿� ���� ����)

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "3";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

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
void CIndexFutOptOrdDlg::OnBnClickedBtnReqBalance()
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

	CString strTrCode = "OTS2850Q82";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName1 = "OTS2850Q82_in";	//�Է� ���ڵ��(���ҽ����� ����)
	CString strInRecName2 = "OTS2850Q82_in_sub01";	//�Է� ���ڵ��(���ҽ����� ����)

	CString strCTNO;			//��ü���հ��¹�ȣ
	CString strAPNO;			//���»�ǰ��ȣ
	CString strPWD;				//��й�ȣ
	CString strINQ_DT;			//��ȸ����
	CString strINQ_DVSN("1");	//��ȸ����(1:������, 2:������ -  (1:��ü 2:�����ŷ����� �翵������ �ƴѰ��))

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
		strINQ_DVSN = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_BAL_OPT2))->GetCheck())
		strINQ_DVSN = "2";


	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdBalanceList = m_CommAgent.CreateRequestID();

	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "CTNO", strCTNO);			//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "APNO", strAPNO);			//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "PWD", strPWD);				//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "INQ_DT", strINQ_DT);		//��ȸ����
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "INQ_DVSN", strINQ_DVSN);	//��ȸ����

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "1";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdBalanceList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", nRequestDataCnt) < 0)
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
void CIndexFutOptOrdDlg::OnBnClickedBtnReqBalanceNext()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strTrCode = "OTS2850Q82";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName1 = "OTS2850Q82_in";	//�Է� ���ڵ��(���ҽ����� ����)
	CString strInRecName2 = "OTS2850Q82_in_sub01";	//�Է� ���ڵ��(���ҽ����� ����)

	CString strCTNO;		//��ü���հ��¹�ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strPWD;			//��й�ȣ
	CString strINQ_DT;		//��ȸ����
	CString strINQ_DVSN("1");	//��ȸ����(1:������, 2:������ -  (1:��ü 2:�����ŷ����� �翵������ �ƴѰ��))

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
		strINQ_DVSN = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_BAL_OPT2))->GetCheck())
		strINQ_DVSN = "2";

	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdBalanceList = m_CommAgent.CreateRequestID();

	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "CTNO", strCTNO);			//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "APNO", strAPNO);			//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "PWD", strPWD);				//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "INQ_DT", strINQ_DT);		//��ȸ����
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "INQ_DVSN", strINQ_DVSN);	//��ȸ����

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "3";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdBalanceList, strTrCode, strBenefitAcc, strPreNext, m_strListBalanceNextRqKey, strScreenNo, "Q", nRequestDataCnt) < 0)
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
void CIndexFutOptOrdDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
		CString strFTR_SELL_QNT, strFTR_BUY_QNT, strIDX_CLPT_SELL_QNT, strIDX_PTPT_SELL_QNT, strIDX_CLPT_BUY_QNT;
		CString strIDX_PTPT_BUY_QNT, strKOSPI_FTR_SELL_QNT, strKOSPI_FTR_BUY_QNT, strSTK_FTR_SELL_QNT, strSTK_FTR_BUY_QNT;
		CString strSTK_OPT_SELL_QNT, strSTK_OPT_BUY_QNT, strCNCS_FTR_SELL_QNT, strCNCS_FTR_BUY_QNT, strCNCS_IDX_CLPT_SELL_QNT;
		CString strCNCS_IDX_PTPT_SELL_QNT, strCNCS_IDX_CLPT_BUY_QNT, strCNCS_IDX_PTPT_BUY_QNT, strCNCS_KOSPI_FTR_SELL_QNT;
		CString strCNCS_KOSPI_FTR_BUY_QNT, strCNCS_STK_FTR_SELL_QNT, strCNCS_STK_FTR_BUY_QNT, strCNCS_STK_OPT_SELL_QNT;
		CString strCNCS_STK_OPT_BUY_QNT;

		strFTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "FTR_SELL_QNT", 0);				//�����ŵ�����
		strFTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "FTR_BUY_QNT", 0);				//�����ż�����
		strIDX_CLPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "FTR_BUY_QNT", 0);			//�����ݿɼǸŵ�����
		strIDX_PTPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_PTPT_SELL_QNT", 0);	//����ǲ�ɼǸŵ�����
		strIDX_CLPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_PTPT_SELL_QNT", 0);	//�����ݿɼǸż�����
		strIDX_PTPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_PTPT_BUY_QNT", 0);		//����ǲ�ɼǸż�����
		strKOSPI_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "KOSPI_FTR_SELL_QNT", 0);	//�ڽ��Ǽ����ŵ�����
		strKOSPI_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "KOSPI_FTR_BUY_QNT", 0);	//�ڽ��Ǽ����ż�����
		strSTK_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_FTR_SELL_QNT", 0);		//�ֽļ����ŵ�����
		strSTK_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_FTR_BUY_QNT", 0);		//�ֽļ����ż�����
		strSTK_OPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_OPT_SELL_QNT", 0);		//�ֽĿɼǸŵ�����
		strSTK_OPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_OPT_BUY_QNT", 0);		//�ֽĿɼǸż�����
		strCNCS_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_FTR_SELL_QNT", 0);	//ü�ἱ���ŵ�����
		strCNCS_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_FTR_BUY_QNT", 0);		//ü�ἱ���ż�����
		strCNCS_IDX_CLPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_CLPT_SELL_QNT", 0);		//ü�������ݿɼǸŵ�����
		strCNCS_IDX_PTPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_PTPT_SELL_QNT", 0);		//ü������ǲ�ɼǸŵ�����
		strCNCS_IDX_CLPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_CLPT_BUY_QNT", 0);		//ü�������ݿɼǸż�����
		strCNCS_IDX_PTPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_PTPT_BUY_QNT", 0);		//ü������ǲ�ɼǸż�����
		strCNCS_KOSPI_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_KOSPI_FTR_SELL_QNT", 0);	//ü���ڽ��Ǽ����ŵ�����
		strCNCS_KOSPI_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_KOSPI_FTR_BUY_QNT", 0);		//ü���ڽ��Ǽ����ż�����
		strCNCS_STK_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_FTR_SELL_QNT", 0);		//ü���ֽļ����ŵ�����
		strCNCS_STK_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_FTR_BUY_QNT", 0);			//ü���ֽļ����ż�����
		strCNCS_STK_OPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_OPT_SELL_QNT", 0);		//ü���ֽĿɼǸŵ�����
		strCNCS_STK_OPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_OPT_BUY_QNT", 0);			//ü���ֽĿɼǸż�����
		
		NumericString(strFTR_SELL_QNT);				//�����ŵ�����
		NumericString(strFTR_BUY_QNT);				//�����ż�����
		NumericString(strIDX_CLPT_SELL_QNT);		//�����ݿɼǸŵ�����
		NumericString(strIDX_PTPT_SELL_QNT);		//����ǲ�ɼǸŵ�����
		NumericString(strIDX_CLPT_BUY_QNT);			//�����ݿɼǸż�����
		NumericString(strIDX_PTPT_BUY_QNT);			//����ǲ�ɼǸż�����
		NumericString(strKOSPI_FTR_SELL_QNT);		//�ڽ��Ǽ����ŵ�����
		NumericString(strKOSPI_FTR_BUY_QNT);		//�ڽ��Ǽ����ż�����
		NumericString(strSTK_FTR_SELL_QNT);			//�ֽļ����ŵ�����
		NumericString(strSTK_FTR_BUY_QNT);			//�ֽļ����ż�����
		NumericString(strSTK_OPT_SELL_QNT);			//�ֽĿɼǸŵ�����
		NumericString(strSTK_OPT_BUY_QNT);			//�ֽĿɼǸż�����
		NumericString(strCNCS_FTR_SELL_QNT);		//ü�ἱ���ŵ�����
		NumericString(strCNCS_FTR_BUY_QNT);			//ü�ἱ���ż�����
		NumericString(strCNCS_IDX_CLPT_SELL_QNT);	//ü�������ݿɼǸŵ�����
		NumericString(strCNCS_IDX_PTPT_SELL_QNT);	//ü������ǲ�ɼǸŵ�����
		NumericString(strCNCS_IDX_CLPT_BUY_QNT);	//ü�������ݿɼǸż�����
		NumericString(strCNCS_IDX_PTPT_BUY_QNT);	//ü������ǲ�ɼǸż�����
		NumericString(strCNCS_KOSPI_FTR_SELL_QNT);	//ü���ڽ��Ǽ����ŵ�����
		NumericString(strCNCS_KOSPI_FTR_BUY_QNT);	//ü���ڽ��Ǽ����ż�����
		NumericString(strCNCS_STK_FTR_SELL_QNT);	//ü���ֽļ����ŵ�����
		NumericString(strCNCS_STK_FTR_BUY_QNT);		//ü���ֽļ����ż�����
		NumericString(strCNCS_STK_OPT_SELL_QNT);	//ü���ֽĿɼǸŵ�����
		NumericString(strCNCS_STK_OPT_BUY_QNT);		//ü���ֽĿɼǸż�����


		/*-------------------------
		 OTS2850Q80_out_sub01 ������ ���
		 --------------------------*/
		CString strODNO, strOR_ODNO, strPRDT_CD, strSHTN_PRDT_CD, strPRDT_NM, strSELL_BUY_DVSN_NM;
		CString strDRVS_NMPR_DCD, strNMPR_DCD, strORDR_PRC_AMT, strORDR_QNT, strCNCS_DVSN_NM, strCNCS_QNT;
		CString strCNCS_PRC_AMT, strKOR_CNCS_TM, strRVSE_CNCL_CNFM_QNT, strNCNC_QNT, strDRVS_NMPR_ACPT_DCD;
		CString strDRVS_NMPR_ACPT_DVSN_NM, strEXCG_ACPT_HR, strKRX_MSG_NO, strCOMM_MDIA_DCD_NM, strXTNL_ISTT_RJCT_RSN_CD;

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

		strOutRecName = "OTS2850Q80_out_sub01";

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, strOutRecName);
		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strODNO = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "ODNO", nRow);		//�ֹ���ȣ
			strOR_ODNO = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "OR_ODNO", nRow);		//���ֹ���ȣ
			strPRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
			strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
			strPRDT_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "PRDT_NM", nRow);		//��ǰ��
			strSELL_BUY_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//�ŵ��ż����и�
			strDRVS_NMPR_DCD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "DRVS_NMPR_DCD", nRow);		//�Ļ���ǰȣ�������ڵ�
			strNMPR_DCD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "NMPR_DCD", nRow);		//ȣ�������ڵ�
			strORDR_PRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "ORDR_PRC_AMT", nRow);		//�ֹ����ݱݾ�
			strORDR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
			strCNCS_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "CNCS_DVSN_NM", nRow);		//ü�ᱸ�и�
			strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "CNCS_QNT", nRow);		//ü�����
			strCNCS_PRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "CNCS_PRC_AMT", nRow);		//ü�ᰡ�ݱݾ�
			strKOR_CNCS_TM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "KOR_CNCS_TM", nRow);		//�ѱ�ü��ð�
			strRVSE_CNCL_CNFM_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "RVSE_CNCL_CNFM_QNT", nRow);		//�������Ȯ�μ���
			strNCNC_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "NCNC_QNT", nRow);		//��ü�����
			strDRVS_NMPR_ACPT_DCD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "DRVS_NMPR_ACPT_DCD", nRow);		//�Ļ���ǰȣ�����������ڵ�
			strDRVS_NMPR_ACPT_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "DRVS_NMPR_ACPT_DVSN_NM", nRow);		//�Ļ���ǰȣ���������и�
			strEXCG_ACPT_HR = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "EXCG_ACPT_HR", nRow);		//�ŷ��������ð�
			strKRX_MSG_NO = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "KRX_MSG_NO", nRow);		//�ѱ��ŷ��Ҹ޽�����ȣ
			strCOMM_MDIA_DCD_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "COMM_MDIA_DCD_NM", nRow);		//��Ÿ�ü�����ڵ��
			strXTNL_ISTT_RJCT_RSN_CD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "XTNL_ISTT_RJCT_RSN_CD", nRow);		//�ܺα���źλ����ڵ�

			strODNO.Trim();							//�ֹ���ȣ
			strOR_ODNO.Trim();						//���ֹ���ȣ
			strPRDT_CD.Trim();						//��ǰ�ڵ�
			strSHTN_PRDT_CD.Trim();					//�����ǰ�ڵ�
			strPRDT_NM.Trim();						//��ǰ��
			strSELL_BUY_DVSN_NM.Trim();				//�ŵ��ż����и�
			strDRVS_NMPR_DCD.Trim();				//�Ļ���ǰȣ�������ڵ�
			strNMPR_DCD.Trim();						//ȣ�������ڵ�
			NumericString(strORDR_PRC_AMT);			//�ֹ����ݱݾ�
			NumericString(strORDR_QNT);				//�ֹ�����
			strCNCS_DVSN_NM.Trim();					//ü�ᱸ�и�
			NumericString(strCNCS_QNT);				//ü�����
			NumericString(strCNCS_PRC_AMT);			//ü�ᰡ�ݱݾ�
			strKOR_CNCS_TM.Trim();					//�ѱ�ü��ð�
			NumericString(strRVSE_CNCL_CNFM_QNT);	//�������Ȯ�μ���
			NumericString(strNCNC_QNT);				//��ü�����
			strDRVS_NMPR_ACPT_DCD.Trim();			//�Ļ���ǰȣ�����������ڵ�
			strDRVS_NMPR_ACPT_DVSN_NM.Trim();		//�Ļ���ǰȣ���������и�
			strEXCG_ACPT_HR.Trim();					//�ŷ��������ð�
			strKRX_MSG_NO.Trim();					//�ѱ��ŷ��Ҹ޽�����ȣ
			strCOMM_MDIA_DCD_NM.Trim();				//��Ÿ�ü�����ڵ��
			strXTNL_ISTT_RJCT_RSN_CD.Trim();		//�ܺα���źλ����ڵ�

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listExec.InsertItem(&lvItem);

			m_listExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strODNO);					//�ֹ���ȣ
			m_listExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strOR_ODNO);					//���ֹ���ȣ
			m_listExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strPRDT_CD);					//��ǰ�ڵ�
			m_listExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strSHTN_PRDT_CD);			//�����ǰ�ڵ�
			m_listExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strPRDT_NM);					//��ǰ��
			m_listExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strSELL_BUY_DVSN_NM);		//�ŵ��ż����и�
			m_listExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strDRVS_NMPR_DCD);			//�Ļ���ǰȣ�������ڵ�
			m_listExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strNMPR_DCD);				//ȣ�������ڵ�
			m_listExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strORDR_PRC_AMT);			//�ֹ����ݱݾ�
			m_listExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strORDR_QNT);				//�ֹ�����
			m_listExec.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strCNCS_DVSN_NM);			//ü�ᱸ�и�
			m_listExec.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strCNCS_QNT);				//ü�����
			m_listExec.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strCNCS_PRC_AMT);			//ü�ᰡ�ݱݾ�
			m_listExec.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strKOR_CNCS_TM);			//�ѱ�ü��ð�
			m_listExec.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strRVSE_CNCL_CNFM_QNT);		//�������Ȯ�μ���
			m_listExec.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strNCNC_QNT);				//��ü�����
			m_listExec.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strDRVS_NMPR_ACPT_DCD);		//�Ļ���ǰȣ�����������ڵ�
			m_listExec.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strDRVS_NMPR_ACPT_DVSN_NM);	//�Ļ���ǰȣ���������и�
			m_listExec.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strEXCG_ACPT_HR);			//�ŷ��������ð�
			m_listExec.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strKRX_MSG_NO);				//�ѱ��ŷ��Ҹ޽�����ȣ
			m_listExec.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strCOMM_MDIA_DCD_NM);		//��Ÿ�ü�����ڵ��
			m_listExec.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strXTNL_ISTT_RJCT_RSN_CD);	//�ܺα���źλ����ڵ�

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
		CString strEVL_DPST_TOT_AMT, strEVL_DPST_CSH, strDPST_TOT_AMT, strDPST_CSH, strDPST_SBST;
		CString strWDRW_PSBL_TOT_AMT, strWDRW_PSBL_CSH, strWDRW_PSBL_SBST_AMT, strORDR_PSBL_TOT_AMT;
		CString strORDR_PSBL_CSH, strCSGN_WMY_TOT_AMT, strCSGN_WMY_CSH, strMNMG_TOT_AMT, strMNMG_CSH;
		CString strADIT_WMY_TOT_AMT, strADIT_WMY_CSH, strEVL_AMT, strEVL_PFLS, strFEE, strRCVA;
		CString strTHDT_PFLS_AMT;

		strOutRecName = "OTS2850Q81_out";

		strEVL_DPST_TOT_AMT		= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "EVL_DPST_TOT_AMT", 0);	//�򰡿�Ź�ѱݾ�
		strEVL_DPST_CSH			= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "EVL_DPST_CSH", 0);		//�򰡿�Ź����;
		strDPST_TOT_AMT			= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "DPST_TOT_AMT", 0);		//��Ź�ѱݾ�;
		strDPST_CSH				= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "DPST_CSH", 0);			//��Ź����;
		strDPST_SBST			= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "DPST_SBST", 0);			//��Ź���;
		strWDRW_PSBL_TOT_AMT	= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "WDRW_PSBL_TOT_AMT", 0);	//���Ⱑ���ѱݾ�;
		strWDRW_PSBL_CSH		= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "WDRW_PSBL_CSH", 0);		//���Ⱑ������;
		strWDRW_PSBL_SBST_AMT	= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "WDRW_PSBL_SBST_AMT", 0);	//���Ⱑ�ɴ��ݾ�;
		strORDR_PSBL_TOT_AMT	= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_PSBL_TOT_AMT", 0);	//�ֹ������ѱݾ�;
		strORDR_PSBL_CSH		= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_PSBL_CSH", 0);		//�ֹ���������;
		strCSGN_WMY_TOT_AMT		= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CSGN_WMY_TOT_AMT", 0);	//��Ź���ű��ѱݾ�;
		strCSGN_WMY_CSH			= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CSGN_WMY_CSH", 0);		//��Ź���ű�����;
		strMNMG_TOT_AMT			= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "MNMG_TOT_AMT", 0);		//�������ű��ѱݾ�;
		strMNMG_CSH				= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "MNMG_CSH", 0);			//�������ű�����;
		strADIT_WMY_TOT_AMT		= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ADIT_WMY_TOT_AMT", 0);	//�߰����ű��ѱݾ�;
		strADIT_WMY_CSH			= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ADIT_WMY_CSH", 0);		//�߰����ű�����;
		strEVL_AMT				= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "EVL_AMT", 0);			//�򰡱ݾ�;
		strEVL_PFLS				= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "EVL_PFLS", 0);			//�򰡼���;
		strFEE					= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "FEE", 0);				//������;
		strRCVA					= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "RCVA", 0);				//�̼���;
		strTHDT_PFLS_AMT		= m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "THDT_PFLS_AMT", 0);		//���ϼ��ͱݾ�;
		
		NumericString(strEVL_DPST_TOT_AMT);
		NumericString(strEVL_DPST_CSH);
		NumericString(strDPST_TOT_AMT);
		NumericString(strDPST_CSH);
		NumericString(strDPST_SBST);
		NumericString(strWDRW_PSBL_TOT_AMT);
		NumericString(strWDRW_PSBL_CSH);
		NumericString(strWDRW_PSBL_SBST_AMT);
		NumericString(strORDR_PSBL_TOT_AMT);
		NumericString(strORDR_PSBL_CSH);
		NumericString(strCSGN_WMY_TOT_AMT);
		NumericString(strCSGN_WMY_CSH);
		NumericString(strMNMG_TOT_AMT);
		NumericString(strMNMG_CSH);
		NumericString(strADIT_WMY_TOT_AMT);
		NumericString(strADIT_WMY_CSH);
		NumericString(strEVL_AMT);
		NumericString(strEVL_PFLS);
		NumericString(strFEE);
		NumericString(strRCVA);
		NumericString(strTHDT_PFLS_AMT);

		GetDlgItem(IDC_EVL_DPST_TOT_AMT)->SetWindowText(strEVL_DPST_TOT_AMT);
		GetDlgItem(IDC_EVL_DPST_CSH)->SetWindowText(strEVL_DPST_CSH);
		GetDlgItem(IDC_DPST_TOT_AMT)->SetWindowText(strDPST_TOT_AMT);
		GetDlgItem(IDC_DPST_CSH)->SetWindowText(strDPST_CSH);
		GetDlgItem(IDC_DPST_SBST)->SetWindowText(strDPST_SBST);
		GetDlgItem(IDC_WDRW_PSBL_TOT_AMT)->SetWindowText(strWDRW_PSBL_TOT_AMT);
		GetDlgItem(IDC_WDRW_PSBL_CSH)->SetWindowText(strWDRW_PSBL_CSH);
		GetDlgItem(IDC_WDRW_PSBL_SBST_AMT)->SetWindowText(strWDRW_PSBL_SBST_AMT);
		GetDlgItem(IDC_ORDR_PSBL_TOT_AMT)->SetWindowText(strORDR_PSBL_TOT_AMT);
		GetDlgItem(IDC_ORDR_PSBL_CSH)->SetWindowText(strORDR_PSBL_CSH);
		GetDlgItem(IDC_CSGN_WMY_TOT_AMT)->SetWindowText(strCSGN_WMY_TOT_AMT);
		GetDlgItem(IDC_CSGN_WMY_CSH)->SetWindowText(strCSGN_WMY_CSH);
		GetDlgItem(IDC_MNMG_TOT_AMT)->SetWindowText(strMNMG_TOT_AMT);
		GetDlgItem(IDC_MNMG_CSH)->SetWindowText(strMNMG_CSH);
		GetDlgItem(IDC_ADIT_WMY_TOT_AMT)->SetWindowText(strADIT_WMY_TOT_AMT);
		GetDlgItem(IDC_ADIT_WMY_CSH)->SetWindowText(strADIT_WMY_CSH);
		GetDlgItem(IDC_EVL_AMT)->SetWindowText(strEVL_AMT);
		GetDlgItem(IDC_EVL_PFLS)->SetWindowText(strEVL_PFLS);
		GetDlgItem(IDC_FEE)->SetWindowText(strFEE);
		GetDlgItem(IDC_RCVA)->SetWindowText(strRCVA);
		GetDlgItem(IDC_THDT_PFLS_AMT)->SetWindowText(strTHDT_PFLS_AMT);

		/*--------------------------------------
		  �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdDepositList = 0;	//������

	}
	//�ܰ� ��ȸ
	else if (m_nRqIdBalanceList == nRequestId)
	{
		CString strPRDT_CD;				//��ǰ�ڵ�;
		CString strSHTN_PRDT_CD;		//�����ǰ�ڵ�;
		CString strPRDT_NM;				//��ǰ��;
		CString strSELL_BUY_DVSN_NM;	//�ŵ��ż����и�;
		CString strSELL_BUY_DCD;		//�ŵ��ż������ڵ�;
		CString strUSTL_QNT;			//�̰�������;
		CString strAVR_PRC;				//��հ���;
		CString strNOW_PRC;				//���簡��;
		CString strPRPT;				//���;
		CString strEVL_AMT;				//�򰡱ݾ�;
		CString strEVL_PFLS;			//�򰡼���;
		CString strPFLS_RT;				//������;
		CString strCLR_PSBL_QNT;		//û�갡�ɼ���;
		CString strPCHS_ACBK_AMT;		//������αݾ�;

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

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OTS2850Q82_out_sub01");

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strPRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
			strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
			strPRDT_NM = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PRDT_NM", nRow);		//��ǰ��
			strSELL_BUY_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//�ŵ��ż����и�
			strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "SELL_BUY_DCD", nRow);		//�ŵ��ż������ڵ�
			strUSTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "USTL_QNT", nRow);		//�̰�������
			strAVR_PRC = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "AVR_PRC", nRow);		//��հ���
			strNOW_PRC = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "NOW_PRC", nRow);		//���簡��
			strPRPT = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PRPT", nRow);		//���
			strEVL_AMT = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "EVL_AMT", nRow);		//�򰡱ݾ�
			strEVL_PFLS = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "EVL_PFLS", nRow);		//�򰡼���
			strPFLS_RT = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PFLS_RT", nRow);		//������
			strCLR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "CLR_PSBL_QNT", nRow);		//û�갡�ɼ���
			strPCHS_ACBK_AMT = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PCHS_ACBK_AMT", nRow);		//������αݾ�

			strPRDT_CD.Trim();
			strSHTN_PRDT_CD.Trim();
			strPRDT_NM.Trim();
			strSELL_BUY_DVSN_NM.Trim();
			strSELL_BUY_DCD.Trim();
			NumericString(strUSTL_QNT);
			NumericString(strAVR_PRC);
			NumericString(strNOW_PRC);
			NumericString(strPRPT);
			NumericString(strEVL_AMT);
			NumericString(strEVL_PFLS);
			NumericString(strPFLS_RT);
			NumericString(strCLR_PSBL_QNT);
			NumericString(strPCHS_ACBK_AMT);

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listBalance.InsertItem(&lvItem);

			m_listBalance.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strPRDT_CD);			//��ǰ�ڵ�;
			m_listBalance.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strSHTN_PRDT_CD);		//�����ǰ�ڵ�;
			m_listBalance.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strPRDT_NM);			//��ǰ��;
			m_listBalance.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strSELL_BUY_DVSN_NM);	//�ŵ��ż����и�;
			m_listBalance.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strSELL_BUY_DCD);		//�ŵ��ż������ڵ�;
			m_listBalance.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strUSTL_QNT);			//�̰�������;
			m_listBalance.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strAVR_PRC);			//��հ���;
			m_listBalance.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strNOW_PRC);			//���簡��;
			m_listBalance.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strPRPT);				//���;
			m_listBalance.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strEVL_AMT);			//�򰡱ݾ�;
			m_listBalance.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strEVL_PFLS);		//�򰡼���;
			m_listBalance.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strPFLS_RT);			//������;
			m_listBalance.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strCLR_PSBL_QNT);	//û�갡�ɼ���;
			m_listBalance.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strPCHS_ACBK_AMT);	//������αݾ�;

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
void CIndexFutOptOrdDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
void CIndexFutOptOrdDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/*	���� : OnGetRealData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
		�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/
	CString strRealMessage;
	CString strTemp;

	/***************************************
	 * ���������ɼ� �ֹ�Ȯ��/ü��/��ü��(����/���) �ǽð� �뺸
	 ****************************************/
	if (!_tcscmp(strRealName, "IF0"))
	{
		/*--------------------------------------
		 �����۸����� ���ŵ� �ǽð� �����͸� �׸񺰷� ������.
		 ---------------------------------------*/
		CString strsDataType = m_CommAgent.GetRealOutputData("IF0", "sDataType");		//�����ͱ���
		CString strsProcTime = m_CommAgent.GetRealOutputData("IF0", "sProcTime");		//ó���ð�
		CString strsComCode = m_CommAgent.GetRealOutputData("IF0", "sComCode");		//��ü����
		CString strsUserID = m_CommAgent.GetRealOutputData("IF0", "sUserID");		//�����ID
		CString strsCtno = m_CommAgent.GetRealOutputData("IF0", "sCtno");		//���´�ü��ȣ
		CString strsAcctNo = m_CommAgent.GetRealOutputData("IF0", "sAcctNo");		//���¹�ȣ
		CString strsAcctName = m_CommAgent.GetRealOutputData("IF0", "sAcctName");		//���¸�
		CString strsBidCode = m_CommAgent.GetRealOutputData("IF0", "sBidCode");		//�ֹ�����
		CString strsModType = m_CommAgent.GetRealOutputData("IF0", "sModType");		//������ұ���
		CString strsItemCode = m_CommAgent.GetRealOutputData("IF0", "sItemCode");		//���������ڵ�
		CString strsItemName = m_CommAgent.GetRealOutputData("IF0", "sItemName");		//�����
		CString strsOrdVol = m_CommAgent.GetRealOutputData("IF0", "sOrdVol");		//�ֹ�����
		CString strsOrdPrice = m_CommAgent.GetRealOutputData("IF0", "sOrdPrice");		//�ֹ�����
		CString strsHogaType = m_CommAgent.GetRealOutputData("IF0", "sHogaType");		//ȣ������
		CString strsOrderCon = m_CommAgent.GetRealOutputData("IF0", "sOrderCon");		//�ֹ�����
		CString strsBrnNo = m_CommAgent.GetRealOutputData("IF0", "sBrnNo");		//������ȣ
		CString strsOrdNo = m_CommAgent.GetRealOutputData("IF0", "sOrdNo");		//�ֹ���ȣ
		CString strsOrgOrdNo = m_CommAgent.GetRealOutputData("IF0", "sOrgOrdNo");		//���ֹ���ȣ
		CString strsContVol = m_CommAgent.GetRealOutputData("IF0", "sContVol");		//ü�����(������ ��� ����Ȯ�� ����)
		CString strsContPrice = m_CommAgent.GetRealOutputData("IF0", "sContPrice");		//ü�ᰡ��(������ ��� ����Ȯ�� ����)
		CString strsRejectCode = m_CommAgent.GetRealOutputData("IF0", "sRejectCode");		//�źλ����ڵ�
		CString strsRejectReason = m_CommAgent.GetRealOutputData("IF0", "sRejectReason");		//�źλ���
		CString strsUnContVol = m_CommAgent.GetRealOutputData("IF0", "sUnContVol");		//��ü�����
		CString strsFotsTradeUnit = m_CommAgent.GetRealOutputData("IF0", "sFotsTradeUnit");		//�ŷ��¼�(�Ļ���, ����:50��, �ɼ�:10��,  �� �����ʹ� *100000000)
		CString strsChegNo = m_CommAgent.GetRealOutputData("IF0", "sChegNo");		//ü���ȣ
		CString strsFstPrc = m_CommAgent.GetRealOutputData("IF0", "sFstPrc");		//�ٿ��� ü�ᰡ��(��������)
		CString strsSndPrc = m_CommAgent.GetRealOutputData("IF0", "sSndPrc");		//������ ü�ᰡ��(��������)
		CString strsWrapNo = m_CommAgent.GetRealOutputData("IF0", "sWrapNo");		//Wrap�ֹ���ȣ
		CString strsGroupNo = m_CommAgent.GetRealOutputData("IF0", "sGroupNo");		//�׷��ȣ
		CString strsSeqNo = m_CommAgent.GetRealOutputData("IF0", "sSeqNo");		//�ٽ��Ͻ�����
		CString strsFee = m_CommAgent.GetRealOutputData("IF0", "sFee");		//������
		CString strsFiller = m_CommAgent.GetRealOutputData("IF0", "sFiller");		//Filler

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
