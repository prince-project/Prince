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
#include "StockOrdDlg.h"

#define ID_SECOND_TIMER		100	//1�� ���� Ÿ�̸�

#define SELL_BK_COLOR		RGB(206, 232, 255)	//�ŵ� ����
#define BUY_BK_COLOR		RGB(251, 221, 255)	//�ż� ����

//��� ����ü ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern void NumericString(CString& strValue, BOOL bNotDisplayZero = FALSE);

static char* g_szPriceCond[] = { "00", "03", "05", "06", "07"}; //00:������, 03:���尡, 05:���Ǻ�������, 06:������������, 07:�ֿ켱������

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

// CStockOrdDlg ��ȭ ����
CStockOrdDlg::CStockOrdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStockOrdDlg::IDD, pParent)
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
	m_nRqIdCodeList		= 0;	//�����ݳ��� Request ID

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_nSeverType			= 0;	//0-����, 1-��������, 2-�ؿܹ���

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStockOrdDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_LIST_CODE, m_listCode);
	DDX_Control(pDX, IDC_LIST_NON_EXE, m_listNonExec);
	DDX_Control(pDX, IDC_CMB_ORD_TYPE, m_cmdOrdType);
	DDX_Control(pDX, IDC_LIST_REAL, m_listReal);
	DDX_Control(pDX, IDC_DATETIME2, m_dateTimeNonExec);
	DDX_Control(pDX, IDC_DATETIME3, m_dateTimeExec);
}

BEGIN_MESSAGE_MAP(CStockOrdDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_LOGIN, &CStockOrdDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_LOGOUT, &CStockOrdDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDOK, &CStockOrdDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELL, &CStockOrdDlg::OnBnClickedBtnSell)
	ON_BN_CLICKED(IDC_BTN_BUY, &CStockOrdDlg::OnBnClickedBtnBuy)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CStockOrdDlg::OnBnClickedBtnChange)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CStockOrdDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST, &CStockOrdDlg::OnBnClickedBtnReqExecList)
	ON_BN_CLICKED(IDC_BTN_REQ_ACCNO, &CStockOrdDlg::OnBnClickedBtnReqAccno)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE, &CStockOrdDlg::OnBnClickedBtnReqMaster)
	ON_BN_CLICKED(IDC_BTN_REQ_NON_EXEC_LIST, &CStockOrdDlg::OnBnClickedBtnReqNonExecList)
	ON_BN_CLICKED(IDC_BTN_LOAD_USER_ACC, &CStockOrdDlg::OnBnClickedBtnLoadUserAcc)
	ON_COMMAND_RANGE(IDC_CON_REAL, IDC_CON_F_DEMO, &CStockOrdDlg::OnRdoSelectServer)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCNO, &CStockOrdDlg::OnNMDblclkListAccNo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NON_EXE, &CStockOrdDlg::OnNMDblclkListNonExec)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CODE, &CStockOrdDlg::OnNMDblclkListCode)
END_MESSAGE_MAP()

// agent�κ��� �̺�Ʈ ���� �Լ��� �����Ѵ�.
BEGIN_EVENTSINK_MAP(CStockOrdDlg, CDialog)
	ON_EVENT(CStockOrdDlg, IDC_HFCOMMAGENTCTRL1, 1, CStockOrdDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CStockOrdDlg, IDC_HFCOMMAGENTCTRL1, 2, CStockOrdDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CStockOrdDlg, IDC_HFCOMMAGENTCTRL1, 3, CStockOrdDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
	ON_EVENT(CStockOrdDlg, IDC_HFCOMMAGENTCTRL1, 4, CStockOrdDlg::OnAgentEventHandler, VTS_I4 VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

// CStockOrdDlg �޽��� ó����
void CStockOrdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CStockOrdDlg::OnPaint()
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
HCURSOR CStockOrdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CStockOrdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CStockOrdDlg::OnNMDblclkListAccNo(NMHDR *pNMHDR, LRESULT *pResult)
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

void CStockOrdDlg::OnNMDblclkListNonExec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
// 	TCHAR *strTitle[] = { _T("�ֹ��Ϸù�ȣ"), _T("���ֹ���ȣ"), _T("ǥ���ڵ�"), _T("�����ڵ�"), _T("�����"),
// 		_T("�ֹ�����"), _T("ȣ�����и�"), _T("�ֹ�����"), _T("ü�����"), _T("�ֹ��ܰ�") };

	CString strOrdNo = m_listNonExec.GetItemText(nSelectRow, 0);
	CString strSymbol = m_listNonExec.GetItemText(nSelectRow, 2);
	CString strOrdPrice = m_listNonExec.GetItemText(nSelectRow, 9);
	CString strOrdSu = m_listNonExec.GetItemText(nSelectRow, 7);

	GetDlgItem(IDC_EDIT_ORG_NO)->SetWindowText(strOrdNo);
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);
	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);
}

void CStockOrdDlg::OnNMDblclkListCode(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	
	CString strCode = m_listCode.GetItemText(nSelectRow, 1);
	CString strPrice = m_listCode.GetItemText(nSelectRow, 18);

	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strCode);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strPrice);
}


void CStockOrdDlg::OnDestroy()
{
	//��� �ǽð������ �����Ѵ�.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();
	
	CDialog::OnDestroy();
}

void CStockOrdDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CStockOrdDlg::OnTimer(UINT_PTR nIDEvent)
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
void CStockOrdDlg::OnRdoSelectServer(UINT nID)
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
BOOL CStockOrdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CString strTitle;
	strTitle.Format("%s-[�ֽ��ֹ�](%s)", PROGRAM_NAME, VERSION_INFO);
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
	InitListCode();		//�ֽĸ�����
	m_cmdOrdType.SetCurSel(0);

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
void CStockOrdDlg::InitListAccNo()
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
void CStockOrdDlg::InitListReal()
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
void CStockOrdDlg::InitListNonExec()
{
	CRect rc;
	m_listNonExec.GetClientRect(rc);
	m_listNonExec.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("�ֹ��Ϸù�ȣ"),_T("���ֹ���ȣ"), _T("ǥ���ڵ�"), _T("�����ڵ�"), _T("�����"),
		_T("�ֹ�����"), _T("ȣ�����и�"), _T("�ֹ�����"), _T("ü�����"), _T("�ֹ��ܰ�") };


	int i;
	for (i = 0; i < 10; i++)
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
void CStockOrdDlg::InitListExec()
{
	CRect rc;
	m_listExec.GetClientRect(rc);
	m_listExec.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("�ֹ��Ϸù�ȣ"), _T("���ֹ���ȣ"), _T("ǥ���ڵ�"), _T("�����ڵ�"), _T("�����"),
		_T("�ֹ�����"), _T("ȣ�����и�"), _T("�ֹ�����"), _T("ü�����"), _T("�ֹ��ܰ�") };


	int i;
	for (i = 0; i < 10; i++)
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
// Function Name : OnBnClickedLogin
// Function      : �α���
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockOrdDlg::OnBnClickedLogin()
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
	m_CommAgent.RegisterReal("IS0", m_strLoginID);
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : �α׾ƿ�
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockOrdDlg::OnBnClickedLogout()
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
void CStockOrdDlg::OnBnClickedOk()
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
void CStockOrdDlg::OnBnClickedBtnReqAccno()
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
void CStockOrdDlg::OnBnClickedBtnLoadUserAcc()
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
CString CStockOrdDlg::GetAccAPNO(CString strAccNo)
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
void CStockOrdDlg::RequestAccList()
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
void CStockOrdDlg::RequestFDemoAccList()
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
BOOL CStockOrdDlg::SendSellBuyOrder(CString strDealingSide, int nRequestId)
{
	CString strTrCode = "OTS1111U10";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS1111U10_in";		//�Է� ���ڵ��(���ҽ����� ����)
	if (strDealingSide == "B")
	{
		strTrCode = "OTS1111U20";
		strInRecName = "OTS1111U20_in";
	}

	CString strORDR_DT;		//�ֹ�����
	CString strCTNO;		//���հ��´�ü��ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strACNT_PWD;		//���º�й�ȣ
	CString strPRDT_CD;		//��ǰ�ڵ�
	CString strSPTX_DCD = "1";		//�и����������ڵ�
	CString strLOAN_SN = "0";		//�����Ϸù�ȣ
	CString strCRDT_TR_DCD = "00";		//�ſ�ŷ������ڵ�
	CString strSSS_NMPR_DCD = "00";		//���ŵ�ȣ�������ڵ�
	CString strFTS_ORDR_DCD = "00";		//��������ֹ������ڵ�
	CString strNMPR_DCD = "00";		//ȣ�������ڵ�
	CString strORDR_CND_DCD = "00";		//�ֹ����Ǳ����ڵ�
	CString strRSVN_ORDR_DCD = "0";		//�����ֹ������ڵ�
	CString strCVRG_PRCS_DCD = "00";		//�ݴ�Ÿ�ó�������ڵ�
	CString strORDR_QNT;		//�ֹ�����
	CString strORDR_UNPR;		//�ֹ��ܰ�
	CString strEMR_ORDR_MDIA_DCD = "000";		//����ֹ���ü�����ڵ�
	CString strWRAP_ORDR_KND_DCD = "00";		//WRAP�ֹ����������ڵ�
	CString strORDR_ANGT_ORDR_DCD = "0";		//�ֹ��븮���ֹ������ڵ�
	CString strPRTR_PANC_DCD = "00";		//���α׷��ŸŰ��ñ����ڵ�
	CString strHTRD_NEGO_NO = "00";		//�뷮�Ÿ������ȣ
	CString strSMLN_YN = "N";		//�ùķ��̼ǿ���

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);			//��й�ȣ
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);						//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//��ǰ�ڵ�

	if (m_cmdOrdType.GetCurSel() >= 0)
		strNMPR_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];		//�������Ǳ����ڵ�

	if (strNMPR_DCD == "03")
		GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText("");

	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strORDR_UNPR);	//�ֹ�����
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);		//�ֹ�����


	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "ORDR_DT", strORDR_DT);		//�ֹ�����
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "SPTX_DCD", strSPTX_DCD);		//�и����������ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "LOAN_SN", strLOAN_SN);		//�����Ϸù�ȣ
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "CRDT_TR_DCD", strCRDT_TR_DCD);		//�ſ�ŷ������ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "SSS_NMPR_DCD", strSSS_NMPR_DCD);		//���ŵ�ȣ�������ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "FTS_ORDR_DCD", strFTS_ORDR_DCD);		//��������ֹ������ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "NMPR_DCD", strNMPR_DCD);		//ȣ�������ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "ORDR_CND_DCD", strORDR_CND_DCD);		//�ֹ����Ǳ����ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "RSVN_ORDR_DCD", strRSVN_ORDR_DCD);		//�����ֹ������ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "CVRG_PRCS_DCD", strCVRG_PRCS_DCD);		//�ݴ�Ÿ�ó�������ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);		//�ֹ�����
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "ORDR_UNPR", strORDR_UNPR);		//�ֹ��ܰ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//����ֹ���ü�����ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "WRAP_ORDR_KND_DCD", strWRAP_ORDR_KND_DCD);		//WRAP�ֹ����������ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//�ֹ��븮���ֹ������ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "PRTR_PANC_DCD", strPRTR_PANC_DCD);		//���α׷��ŸŰ��ñ����ڵ�
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "HTRD_NEGO_NO", strHTRD_NEGO_NO);		//�뷮�Ÿ������ȣ
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "SMLN_YN", strSMLN_YN);		//�ùķ��̼ǿ���

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[3] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(nRequestId, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", 0) < 0)
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
void CStockOrdDlg::OnBnClickedBtnSell()
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
void CStockOrdDlg::OnBnClickedBtnBuy()
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
void CStockOrdDlg::OnBnClickedBtnChange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS1111U30";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS1111U30_in";	//�Է� ���ڵ��(���ҽ����� ����)
	
	//[1] Request ID����
	m_nRqIdChangeOrd = m_CommAgent.CreateRequestID();

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	CString strORDR_DT;		//�ֹ�����
	CString strCTNO;		//���հ��´�ü��ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strMNGM_BDCD;		//���������ڵ�
	CString strOR_ORDR_SN;		//���ֹ��Ϸù�ȣ
	CString strACNT_PWD;		//���º�й�ȣ
	CString strPRDT_CD;		//��ǰ�ڵ�
	CString strNMPR_DCD;		//ȣ�������ڵ�
	CString strORDR_CND_DCD;		//�ֹ����Ǳ����ڵ�
	CString strORDR_QNT;		//�ֹ�����
	CString strORDR_UNPR;		//�ֹ��ܰ�
	CString strEMR_ORDR_MDIA_DCD;		//����ֹ���ü�����ڵ�
	CString strGRUP_ODNO;		//�׷��ֹ���ȣ
	CString strBSK_ORDR_SN;		//�ٽ����ֹ��Ϸù�ȣ
	CString strMTS_KEY;		//MTSŰ
	CString strHTS_ORDR_PSBL_MDIA_YN;		//HTS�ֹ����ɸ�ü����
	CString strNMPR_PROP_XCP_YN;		//ȣ�����������ܿ���
	CString strORDR_ANGT_ORDR_DCD;		//�ֹ��븮���ֹ������ڵ�
	CString strBOND_ORDR_OR_UN_DCD;		//ä���ֹ������������ڵ�
	CString strPRT_ALL_DCD;		//�Ϻ���ü

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);			//��й�ȣ
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);						//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.
	
	//���ֹ���ȣ
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strOR_ORDR_SN);
	
	//��ǰ�ڵ�
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);
	
	//�������Ǳ����ڵ�
	if (m_cmdOrdType.GetCurSel() >= 0)
		strNMPR_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];

	if (strNMPR_DCD == "03")
		GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText("");
	//��������
	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strORDR_UNPR);

	//��������
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	strEMR_ORDR_MDIA_DCD = "000";
	strGRUP_ODNO = "0";
	strBOND_ORDR_OR_UN_DCD = "2";
	strPRT_ALL_DCD = "2";

	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_DT", strORDR_DT);		//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "MNGM_BDCD", strMNGM_BDCD);		//���������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "OR_ORDR_SN", strOR_ORDR_SN);		//���ֹ��Ϸù�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "NMPR_DCD", strNMPR_DCD);		//ȣ�������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_CND_DCD", strORDR_CND_DCD);		//�ֹ����Ǳ����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);		//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_UNPR", strORDR_UNPR);		//�ֹ��ܰ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//����ֹ���ü�����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "GRUP_ODNO", strGRUP_ODNO);		//�׷��ֹ���ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "BSK_ORDR_SN", strBSK_ORDR_SN);		//�ٽ����ֹ��Ϸù�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "MTS_KEY", strMTS_KEY);		//MTSŰ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "HTS_ORDR_PSBL_MDIA_YN", strHTS_ORDR_PSBL_MDIA_YN);		//HTS�ֹ����ɸ�ü����
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "NMPR_PROP_XCP_YN", strNMPR_PROP_XCP_YN);		//ȣ�����������ܿ���
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//�ֹ��븮���ֹ������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "BOND_ORDR_OR_UN_DCD", strBOND_ORDR_OR_UN_DCD);		//ä���ֹ������������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PRT_ALL_DCD", strPRT_ALL_DCD);		//�Ϻ���ü

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
void CStockOrdDlg::OnBnClickedBtnCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS1111U40";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS1111U40_in";	//�Է� ���ڵ��(���ҽ����� ����)

	//[1] Request ID����
	m_nRqIdCancelOrd = m_CommAgent.CreateRequestID();

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.	
	CString strORDR_DT;		//�ֹ�����
	CString strCTNO;		//���հ��´�ü��ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strMNGM_BDCD;		//���������ڵ�
	CString strOR_ORDR_SN;		//���ֹ��Ϸù�ȣ
	CString strACNT_PWD;		//���º�й�ȣ
	CString strPRDT_CD;		//��ǰ�ڵ�
	CString strORDR_QNT;		//�ֹ�����
	CString strEMR_ORDR_MDIA_DCD;		//����ֹ���ü�����ڵ�
	CString strGRUP_ODNO;		//�׷��ֹ���ȣ
	CString strBSK_ORDR_SN;		//�ٽ����ֹ��Ϸù�ȣ
	CString strMTS_KEY;		//MTSŰ
	CString strHTS_ORDR_PSBL_MDIA_YN;		//HTS�ֹ����ɸ�ü����
	CString strNMPR_PROP_XCP_YN;		//ȣ�����������ܿ���
	CString strORDR_ANGT_ORDR_DCD;		//�ֹ��븮���ֹ������ڵ�
	CString strBOND_ORDR_OR_UN_DCD;		//ä���ֹ������������ڵ�
	CString strPRT_ALL_DCD;		//�Ϻ���ü�����ڵ�
	CString strAccNo;

	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//��ü���հ��¹�ȣ
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);			//��й�ȣ
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);						//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.

	//���ֹ���ȣ
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strOR_ORDR_SN);

	//��ǰ�ڵ�
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//��Ҽ���
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ORDR_DT", strORDR_DT);		//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "MNGM_BDCD", strMNGM_BDCD);		//���������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "OR_ORDR_SN", strOR_ORDR_SN);		//���ֹ��Ϸù�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);		//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//����ֹ���ü�����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "GRUP_ODNO", strGRUP_ODNO);		//�׷��ֹ���ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "BSK_ORDR_SN", strBSK_ORDR_SN);		//�ٽ����ֹ��Ϸù�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "MTS_KEY", strMTS_KEY);		//MTSŰ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "HTS_ORDR_PSBL_MDIA_YN", strHTS_ORDR_PSBL_MDIA_YN);		//HTS�ֹ����ɸ�ü����
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "NMPR_PROP_XCP_YN", strNMPR_PROP_XCP_YN);		//ȣ�����������ܿ���
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//�ֹ��븮���ֹ������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "BOND_ORDR_OR_UN_DCD", strBOND_ORDR_OR_UN_DCD);		//ä���ֹ������������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "PRT_ALL_DCD", strPRT_ALL_DCD);		//�Ϻ���ü�����ڵ�
	
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
void CStockOrdDlg::OnBnClickedBtnReqMaster()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	/**********************************
	* 1. ������ȸŰ �ʱ�ȭ
	**********************************/
	m_strCodeListNextRqKey.Empty();

	//�ֽ� ���� ����Ʈ(������) ��Ʈ�� ������ �ʱ�ȭ
	m_listCode.DeleteAllItems();

	/**********************************
	* 2. �����ȸ Request ID�� �����Ѵ�.
	**********************************/
	m_nRqIdCodeList = m_CommAgent.CreateRequestID();

	if (m_nRqIdCodeList == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("J");	//�ֽ�

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("1199"));		//GID

	//�������� �������� ����׸��.
	CString strOutputFidList;

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	/* [�ֽ� ���񸮽�Ʈ(������) FID ��ȣ]
	0001 : �����ڵ�
	0002 : ǥ�������ڵ�
	0003 : �ѱ������
	0827 : ���屸��(1: KOSPI, 4 : KOSDAQ, A : ETN)
	1893 : ���Ǳ׷챸���ڵ�
	2574 : �ð��Ѿ� �Ը� �����ڵ�
	�������� : 0
	�ڽ��� 1: ������, 2: ������, 3: ������
	�ڽ��� 4: KOSDAQ100 5:KOSDAQmid300 6:KOSDAQsmall
	1993 : ���� ���� ��з� �ڵ�
	1994 : ���� ���� �ߺз� �ڵ�
	1995 : ���� ���� �Һз� �ڵ�
	2604 : ������ �����ڵ�(Y : �ش� N : ���ش�) = > mnin_cls_code
	2605 : ������� ���񿩺�(Y, N) = > dvdn_nmix_issu_yn
	2606 : ���豸���������(Y, N) = > sprn_strr_sprr_yn
	1257 : KOSPI200 ����
	0:�����̺з� 1:�Ǽ� 2:�߰��� 3:ö������
	4:������ȭ�� 5:������� 6:���� 7:�ʼ��Һ���
	8:�����Һ��� 9:�����  A:�ǰ�����
	1998 : KOSPI100, 50 ���� (1:KOSPI100, 2:KOSPI50)
	2607 : ��ó��� ���� Y, N = > sprn_strr_nmix_issu_yn
	1996 : KRX100 ���񿩺�
	0225 : ����
	0053 : �ֽľ׸鰡
	0016 : �ֽı��ذ�
	0056 : �ں���
	0055 : �����ּ�
	2067 : ��������
	0684 : �ſ��ܰ����
	1253 : �ŷ���������(N : ����, Y : �ŷ�����)
	1254 : �����Ÿſ���(N : ����, Y : �����Ÿ�)
	1258 : �������񿩺�(N : ����, Y : ��������)
	1251 : ���������ڵ�(00:���� 01:���� 02:��� 03:����)
	2608 : �����������ڵ� Y, N = > mrkt_alrm_risk_adnt_yn
	1252 : �Ҽ��ǰ������� ���� Y, N
	1992 : ��ȸ���屸�� Y, N
	1256 : �������ڵ�
	00:�ش����     01:�Ǹ���     02:����
	03:�й��       04:�ǹ��     05:�߰�����
	06:�Ǹ��߰�����  99:��Ÿ
	0222 : ��� �ſ� ����
	2129 : ���������� ���а� 1 : �ش� 0 : ���ش�
	2148 : Equity Rating���� A, B, C, D, F ����� X
	0019 : �ð��Ѿ�(��)
	0021 : �ܱ��κ�������
	1896 : �켱�� ���� �ڵ�(0:������, �׿� : �켱��)
	0:�ش����(������)
	1:�����켱��
	2:�����켱��
	9:�����ֱ�
	ST���� �ش� */
	strOutputFidList = "1,2,3,827,1893,2574,1993,1994,1995,2604,2605,"
		"2606,1257,1998,2607,1996,225,53,16,56,55,2067,"
		"684,1253,1254,1258,1251,2608,1252,1992,1256,"
		"222,2129,2148,19,21,1896";
	CString strScreenNo;
	strScreenNo = "9999";

	//������ȸ �ɼ� : '0':�̻��, '1'���, '2' : ���� ������ ��ȸ, '3' : ���� ������ ��ȸ
	CString strPreNext = "1";

	/**********************************
	* 5. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, "", strScreenNo, 3000);
	if (nReturn < 0)
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
void CStockOrdDlg::OnBnClickedBtnReqNonExecList()
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

	CString strTrCode = "OTS1201Q00";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS1201Q00_in";	//�Է� ���ڵ��(���ҽ����� ����)

	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdNonExecList = m_CommAgent.CreateRequestID();
	

	CString strPWD;		//��й�ȣ
	CString strCTNO;		//���հ��´�ü��ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strORDR_DT;		//�ֹ�����
	CString strPRDT_CD = "";		//��ǰ�ڵ�
	CString strORDR_SN = "999999999";		//�ֹ��Ϸù�ȣ
	CString strCNCS_DVSN = "2";		//ü�ᱸ��
	CString strINQ_ORD_DVSN = "3";		//��ȸ��������
	CString strPRDT_DVSN = "0";		//��ǰ����
	CString strMKT_TR_DCD = "0";		//����ŷ������ڵ�
	CString strCRDT_TR_DCD = "0";		//�ſ�ŷ������ڵ�
	CString strCOMM_MDIA_DCD = "000";		//��Ÿ�ü�����ڵ�
	CString strORDR_PRCS_STTS_DCD = "0";		//�ֹ�ó�����±����ڵ�
	CString strSELL_BUY_DCD = "0";		//�ŵ��ż�

	m_dateTimeNonExec.GetWindowText(strORDR_DT);
	strORDR_DT.Remove('-');
	//[3] Tran��ȸ �Է°��� �Է��Ѵ�.
	//���´�ü��ȣ�� ���´�.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);

	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO);	//���հ��´�ü��ȣ

	//���º�й�ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD);

	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "PWD", strPWD);		//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "ORDR_DT", strORDR_DT);		//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "ORDR_SN", strORDR_SN);		//�ֹ��Ϸù�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "CNCS_DVSN", strCNCS_DVSN);		//ü�ᱸ��
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "INQ_ORD_DVSN", strINQ_ORD_DVSN);		//��ȸ��������
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "PRDT_DVSN", strPRDT_DVSN);		//��ǰ����
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "MKT_TR_DCD", strMKT_TR_DCD);		//����ŷ������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "CRDT_TR_DCD", strCRDT_TR_DCD);		//�ſ�ŷ������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//��Ÿ�ü�����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "ORDR_PRCS_STTS_DCD", strORDR_PRCS_STTS_DCD);		//�ֹ�ó�����±����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);		//�ŵ��ż������ڵ�

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "1";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if(m_CommAgent.RequestTran(m_nRqIdNonExecList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
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
void CStockOrdDlg::OnBnClickedBtnReqExecList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_listExec.DeleteAllItems();
	m_strListExecNextRqKey.Empty(); //����Ű�� �ʱ�ȭ��Ų��.

	CString strTrCode = "OTS1201Q00";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS1201Q00_in";	//�Է� ���ڵ��(���ҽ����� ����)

	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	CString strPWD;		//��й�ȣ
	CString strCTNO;		//���հ��´�ü��ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strORDR_DT;		//�ֹ�����
	CString strPRDT_CD = "";		//��ǰ�ڵ�
	CString strORDR_SN = "999999999";		//�ֹ��Ϸù�ȣ
	CString strCNCS_DVSN = "0";		//ü�ᱸ��
	CString strINQ_ORD_DVSN = "3";		//��ȸ��������
	CString strPRDT_DVSN = "0";		//��ǰ����
	CString strMKT_TR_DCD = "0";		//����ŷ������ڵ�
	CString strCRDT_TR_DCD = "0";		//�ſ�ŷ������ڵ�
	CString strCOMM_MDIA_DCD = "000";		//��Ÿ�ü�����ڵ�
	CString strORDR_PRCS_STTS_DCD = "0";		//�ֹ�ó�����±����ڵ�
	CString strSELL_BUY_DCD = "0";		//�ŵ��ż�

	m_dateTimeExec.GetWindowText(strORDR_DT);
	strORDR_DT.Remove('-');
	//[3] Tran��ȸ �Է°��� �Է��Ѵ�.
	//���´�ü��ȣ�� ���´�.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);

	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO);	//���հ��´�ü��ȣ

	//���º�й�ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD);

	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD);		//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO);	//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_DT", strORDR_DT);		//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_SN", strORDR_SN);		//�ֹ��Ϸù�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CNCS_DVSN", strCNCS_DVSN);		//ü�ᱸ��
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_ORD_DVSN", strINQ_ORD_DVSN);		//��ȸ��������
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PRDT_DVSN", strPRDT_DVSN);		//��ǰ����
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "MKT_TR_DCD", strMKT_TR_DCD);		//����ŷ������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CRDT_TR_DCD", strCRDT_TR_DCD);		//�ſ�ŷ������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//��Ÿ�ü�����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_PRCS_STTS_DCD", strORDR_PRCS_STTS_DCD);		//�ֹ�ó�����±����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);		//�ŵ��ż������ڵ�

	CString strBenefitAcc = "N";	//�������ǰ��� ����
	CString strPreNext = "1";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[4] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdExecList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
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
void CStockOrdDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
		CString strMNGM_BDCD, strSELL_CNCS_QNT, strSELL_CNCS_AMT, strBUY_CNCS_QNT, strBUY_CNCS_AMT, strORDR_SN;
		CString strOR_ORDR_SN, strORDR_RVSE_CNCL_DVSN_NM, strPRDT_CD, strSHTN_PRDT_CD, strPRDT_NM, strORDR_DCD_NM, strNMPR_DVSN_NM, strORDR_QNT, strCNCS_QNT;
		CString strORDR_UNPR, strITG_BOND_ORDR_UNPR, strCNCS_UNPR, strITG_BOND_CNCS_UNPR, strORDR_RMN_QNT, strCNCS_QNT_SMM, strORDR_MDIA_NM, strORDR_PRCS_STTS_DCD;
		CString strORDR_TM, strLOAN_DT, strLOAN_SN, strORDR_DT, strCNCS_DT, strSCTS_DCD, strTRDE_STL_DE_DCD, strSELL_BUY_DCD, strORDR_PRCS_STTS_DVSN_NM;
		CString strCRDT_TR_DCD, strORDR_KND_DCD, strCSGN_TRDE_DCD;

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

		strOutRecName = "OTS1201Q00_out_sub01";

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, strOutRecName);
		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strORDR_SN = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_SN", nRow);		//�ֹ��Ϸù�ȣ
			strOR_ORDR_SN = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "OR_ORDR_SN", nRow);		//���ֹ��Ϸù�ȣ
			strORDR_RVSE_CNCL_DVSN_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_RVSE_CNCL_DVSN_NM", nRow);		//�ֹ�������ұ��и�
			strPRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRDT_CD", nRow);		//��ǰ�ڵ�
			strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
			strPRDT_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRDT_NM", nRow);		//��ǰ��
			strORDR_DCD_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DCD_NM", nRow);		//�ֹ������ڵ��
			strNMPR_DVSN_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "NMPR_DVSN_NM", nRow);		//ȣ�����и�
			strORDR_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_QNT", nRow);		//�ֹ�����
			strCNCS_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT", nRow);		//ü�����
			strORDR_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_UNPR", nRow);		//�ֹ��ܰ�
			strITG_BOND_ORDR_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ITG_BOND_ORDR_UNPR", nRow);		//�峻ä���ֹ��ܰ�
			strCNCS_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_UNPR", nRow);		//ü��ܰ�
			strITG_BOND_CNCS_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ITG_BOND_CNCS_UNPR", nRow);		//�峻ä��ü��ܰ�
			strORDR_RMN_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
			strCNCS_QNT_SMM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT_SMM", nRow);		//ü������հ�
			strORDR_MDIA_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_MDIA_NM", nRow);		//�ֹ���ü��
			strORDR_PRCS_STTS_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_PRCS_STTS_DCD", nRow);		//�ֹ�ó�����±����ڵ�
			strORDR_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_TM", nRow);		//�ֹ��ð�
			strLOAN_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "LOAN_DT", nRow);		//��������
			strLOAN_SN = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "LOAN_SN", nRow);		//�����Ϸù�ȣ
			strORDR_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DT", nRow);		//�ֹ�����
			strCNCS_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_DT", nRow);		//ü������
			strMNGM_BDCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "MNGM_BDCD", nRow);		//���������ڵ�
			strSCTS_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SCTS_DCD", nRow);		//�������Ǳ����ڵ�
			strTRDE_STL_DE_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "TRDE_STL_DE_DCD", nRow);		//�ŸŰ����ϱ����ڵ�
			strSELL_BUY_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SELL_BUY_DCD", nRow);		//�ŵ��ż������ڵ�
			strORDR_PRCS_STTS_DVSN_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_PRCS_STTS_DVSN_NM", nRow);		//�ֹ�ó�����±���
			strCRDT_TR_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CRDT_TR_DCD", nRow);		//�ſ�ŷ������ڵ�
			strORDR_KND_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_KND_DCD", nRow);		//�ֹ����������ڵ�
			strCSGN_TRDE_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CSGN_TRDE_DCD", nRow);		//��Ź�Ÿű����ڵ�

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listNonExec.InsertItem(&lvItem);

			long lORDR_QNT = atol(strORDR_QNT);
			strORDR_QNT.Format("%ld", lORDR_QNT);
			long lCNCS_QNT = atol(strCNCS_QNT);
			strCNCS_QNT.Format("%ld", lCNCS_QNT);
			long lORDR_UNPR = atol(strORDR_UNPR);
			strORDR_UNPR.Format("%ld", lORDR_UNPR);

			strORDR_SN.TrimRight();
			strOR_ORDR_SN.TrimRight();
			strPRDT_CD.TrimRight();
			strSHTN_PRDT_CD.TrimRight();
			strPRDT_NM.TrimRight();
			strORDR_DCD_NM.TrimRight();
			strNMPR_DVSN_NM.TrimRight();
			
			m_listNonExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strORDR_SN);			//�ֹ��Ϸù�ȣ
			m_listNonExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strOR_ORDR_SN);		//���ֹ���ȣ
			m_listNonExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strPRDT_CD);			//��ǰ�ڵ�
			m_listNonExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strSHTN_PRDT_CD);		//�����ڵ�
			m_listNonExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strPRDT_NM);			//�����
			m_listNonExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strORDR_DCD_NM);		//�ֹ������ڵ�
			m_listNonExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strNMPR_DVSN_NM);		//ȣ�����и�
			m_listNonExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strORDR_QNT);			//�ֹ�����
			m_listNonExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strCNCS_QNT);			//ü�����
			m_listNonExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strORDR_UNPR);		//�ֹ��ܰ�
		}

		m_listNonExec.EnsureVisible(nViewScrollPos, FALSE);
		m_listNonExec.SetRedraw(TRUE);

		/*--------------------------------------
		������ȸŰ�� ������ ���´�.
		---------------------------------------*/
		m_strListNonExecNextRqKey = strPreNextContext;

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdNonExecList = 0;	//�ֹ�ü����ȸ Rq ID

	}
	//�ֹ�ü�᳻�� ��ȸ
	else if (nRequestId == m_nRqIdExecList)
	{
		CString strMNGM_BDCD, strSELL_CNCS_QNT, strSELL_CNCS_AMT, strBUY_CNCS_QNT, strBUY_CNCS_AMT, strORDR_SN;
		CString strOR_ORDR_SN, strORDR_RVSE_CNCL_DVSN_NM, strPRDT_CD, strSHTN_PRDT_CD, strPRDT_NM, strORDR_DCD_NM, strNMPR_DVSN_NM, strORDR_QNT, strCNCS_QNT;
		CString strORDR_UNPR, strITG_BOND_ORDR_UNPR, strCNCS_UNPR, strITG_BOND_CNCS_UNPR, strORDR_RMN_QNT, strCNCS_QNT_SMM, strORDR_MDIA_NM, strORDR_PRCS_STTS_DCD;
		CString strORDR_TM, strLOAN_DT, strLOAN_SN, strORDR_DT, strCNCS_DT, strSCTS_DCD, strTRDE_STL_DE_DCD, strSELL_BUY_DCD, strORDR_PRCS_STTS_DVSN_NM;
		CString strCRDT_TR_DCD, strORDR_KND_DCD, strCSGN_TRDE_DCD;

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

		strOutRecName = "OTS1201Q00_out_sub01";

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, strOutRecName);
		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strORDR_SN = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_SN", nRow);		//�ֹ��Ϸù�ȣ
			strOR_ORDR_SN = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "OR_ORDR_SN", nRow);		//���ֹ��Ϸù�ȣ
			strORDR_RVSE_CNCL_DVSN_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_RVSE_CNCL_DVSN_NM", nRow);		//�ֹ�������ұ��и�
			strPRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRDT_CD", nRow);		//��ǰ�ڵ�
			strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
			strPRDT_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRDT_NM", nRow);		//��ǰ��
			strORDR_DCD_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DCD_NM", nRow);		//�ֹ������ڵ��
			strNMPR_DVSN_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "NMPR_DVSN_NM", nRow);		//ȣ�����и�
			strORDR_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_QNT", nRow);		//�ֹ�����
			strCNCS_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT", nRow);		//ü�����
			strORDR_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_UNPR", nRow);		//�ֹ��ܰ�
			strITG_BOND_ORDR_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ITG_BOND_ORDR_UNPR", nRow);		//�峻ä���ֹ��ܰ�
			strCNCS_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_UNPR", nRow);		//ü��ܰ�
			strITG_BOND_CNCS_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ITG_BOND_CNCS_UNPR", nRow);		//�峻ä��ü��ܰ�
			strORDR_RMN_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
			strCNCS_QNT_SMM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT_SMM", nRow);		//ü������հ�
			strORDR_MDIA_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_MDIA_NM", nRow);		//�ֹ���ü��
			strORDR_PRCS_STTS_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_PRCS_STTS_DCD", nRow);		//�ֹ�ó�����±����ڵ�
			strORDR_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_TM", nRow);		//�ֹ��ð�
			strLOAN_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "LOAN_DT", nRow);		//��������
			strLOAN_SN = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "LOAN_SN", nRow);		//�����Ϸù�ȣ
			strORDR_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DT", nRow);		//�ֹ�����
			strCNCS_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_DT", nRow);		//ü������
			strMNGM_BDCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "MNGM_BDCD", nRow);		//���������ڵ�
			strSCTS_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SCTS_DCD", nRow);		//�������Ǳ����ڵ�
			strTRDE_STL_DE_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "TRDE_STL_DE_DCD", nRow);		//�ŸŰ����ϱ����ڵ�
			strSELL_BUY_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SELL_BUY_DCD", nRow);		//�ŵ��ż������ڵ�
			strORDR_PRCS_STTS_DVSN_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_PRCS_STTS_DVSN_NM", nRow);		//�ֹ�ó�����±���
			strCRDT_TR_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CRDT_TR_DCD", nRow);		//�ſ�ŷ������ڵ�
			strORDR_KND_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_KND_DCD", nRow);		//�ֹ����������ڵ�
			strCSGN_TRDE_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CSGN_TRDE_DCD", nRow);		//��Ź�Ÿű����ڵ�

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listExec.InsertItem(&lvItem);

			long lORDR_QNT = atol(strORDR_QNT);
			strORDR_QNT.Format("%ld", lORDR_QNT);
			long lCNCS_QNT = atol(strCNCS_QNT);
			strCNCS_QNT.Format("%ld", lCNCS_QNT);
			long lORDR_UNPR = atol(strORDR_UNPR);
			strORDR_UNPR.Format("%ld", lORDR_UNPR);

			strORDR_SN.TrimRight();
			strOR_ORDR_SN.TrimRight();
			strPRDT_CD.TrimRight();
			strSHTN_PRDT_CD.TrimRight();
			strPRDT_NM.TrimRight();
			strORDR_DCD_NM.TrimRight();
			strNMPR_DVSN_NM.TrimRight();

			m_listExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strORDR_SN);			//�ֹ��Ϸù�ȣ
			m_listExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strOR_ORDR_SN);		//���ֹ���ȣ
			m_listExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strPRDT_CD);			//��ǰ�ڵ�
			m_listExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strSHTN_PRDT_CD);		//�����ڵ�
			m_listExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strPRDT_NM);			//�����
			m_listExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strORDR_DCD_NM);		//�ֹ������ڵ�
			m_listExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strNMPR_DVSN_NM);		//ȣ�����и�
			m_listExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strORDR_QNT);			//�ֹ�����
			m_listExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strCNCS_QNT);			//ü�����
			m_listExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strORDR_UNPR);		//�ֹ��ܰ�
		}

		m_listExec.EnsureVisible(nViewScrollPos, FALSE);
		m_listExec.SetRedraw(TRUE);
		
		/*--------------------------------------
		������ȸŰ�� ������ ���´�.
		---------------------------------------*/
		m_strListExecNextRqKey = strPreNextContext;

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
		m_nRqIdFDemoAccNoList = 0;	//������¸���Ʈ
	}
	//�ŵ��ֹ� Request ID
	else if (m_nRqIdSellOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS1111U10_out", "ORDR_SN", 0);		//�ֹ���ȣ
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
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS1111U20_out", "ORDR_SN", 0);		//�ֹ���ȣ
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
		CString strORDR_SN = m_CommAgent.GetTranOutputData(strTrCode, "OTS1111U30_out", "ORDR_SN", 0);		//�ֹ��Ϸù�ȣ
		strORDR_SN.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strORDR_SN);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdChangeOrd = 0;
	}
	//����ֹ� Request ID
	else if (m_nRqIdCancelOrd == nRequestId)
	{
		CString strORDR_SN = m_CommAgent.GetTranOutputData(strTrCode, "OTS1111U40_out", "ORDR_SN", 0);		//�ֹ���
		strORDR_SN.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strORDR_SN);

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
void CStockOrdDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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

	/***************************************
	* �ֽ� ���� ����Ʈ(������) ��ȸ ������ ���� ó��
	****************************************/
	if (m_nRqIdCodeList == nRequestId)
	{
		CString arrItem[37];			//���񸮽�Ʈ

		m_listCode.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;
		int nViewScrollPos = 0;

		/*--------------------------------------
		���� ��ȸ ������ �����̸� ������ ���� ����Ÿ �ڿ�
		�ٿ� �����Ѵ�.
		---------------------------------------*/
		if (!m_strCodeListNextRqKey.IsEmpty())
		{
			nListIndex = m_listCode.GetItemCount();
			nViewScrollPos = nListIndex;
		}


		/***************************************
		* ���ŵ����͸� ���� �����Ѵ�.(C++������ ��� ����)
		* ���񸮽�Ʈ, ��Ʈ ������ ���� �뷮�� ������ ó�� ��
		* ������Ʈ ��Ʈ���� GetFidOutputData �Լ� ȣ�⺸�� ���� ������ ���δ�.
		****************************************/

		/*[FID��ȸ ������ �Էµ� ���FID ������ ���� ���������.]
		�����ڵ�(FID:1), ǥ���߸��ڵ�(FID:2), �ѱ������(FID:3), ���ذ�(FID:16)
		strOutputFidList = "1,2,3,16";	*/
		CCommRecvData fidCommRecvData;
		int nVecRowCnt = 0;		//������ �Ǽ�(��)
		int nVecColCnt = 0;	//������ �׸� �Ǽ�(��)

		//FID ��ȸ���� ������ �޸𸮸� ���´�.(C++������ ��� ����)
		if (m_CommAgent.GetCommFidDataBlock((long)&fidCommRecvData) == TRUE)
		{
			nVecRowCnt = fidCommRecvData.GetRowCnt();	//������ �Ǽ�(��)
			nVecColCnt = fidCommRecvData.GetColCnt();	//������ �׸� �Ǽ�(��)
		}

		int nDataCnt = nVecRowCnt;

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			�ε����� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			arrItem[0] = fidCommRecvData.GetItem(i, 0);	//0001 : �����ڵ�
			arrItem[1] = fidCommRecvData.GetItem(i, 1);	//0002 : ǥ�������ڵ�
			arrItem[2] = fidCommRecvData.GetItem(i, 2);	//0003 : �ѱ������
			arrItem[3] = fidCommRecvData.GetItem(i, 3);	//0827 : ���屸��(1: KOSPI, 4 : KOSDAQ, A : ETN)
			arrItem[4] = fidCommRecvData.GetItem(i, 4);	//1893 : ���Ǳ׷챸���ڵ�
			arrItem[5] = fidCommRecvData.GetItem(i, 5);	//2574 : �ð��Ѿ� �Ը� �����ڵ�
			arrItem[6] = fidCommRecvData.GetItem(i, 6);	//1993 : ���� ���� ��з� �ڵ�
			arrItem[7] = fidCommRecvData.GetItem(i, 7);	//1994 : ���� ���� �ߺз� �ڵ�
			arrItem[8] = fidCommRecvData.GetItem(i, 8);	//1995 : ���� ���� �Һз� �ڵ�
			arrItem[9] = fidCommRecvData.GetItem(i, 9);	//2604 : ������ �����ڵ�(Y : �ش� N : ���ش�) = > mnin_cls_code
			arrItem[10] = fidCommRecvData.GetItem(i, 10);	//2605 : ������� ���񿩺�(Y, N) = > dvdn_nmix_issu_yn
			arrItem[11] = fidCommRecvData.GetItem(i, 11);	//2606 : ���豸���������(Y, N) = > sprn_strr_sprr_yn
			arrItem[12] = fidCommRecvData.GetItem(i, 12);	//1257 : KOSPI200 ����
			arrItem[13] = fidCommRecvData.GetItem(i, 13);	//1998 : KOSPI100, 50 ����(1:KOSPI100, 2 : KOSPI50)
			arrItem[14] = fidCommRecvData.GetItem(i, 14);	//2607 : ��ó��� ���� Y, N = > sprn_strr_nmix_issu_yn
			arrItem[15] = fidCommRecvData.GetItem(i, 15);	//1996 : KRX100 ���񿩺�
			arrItem[16] = fidCommRecvData.GetItem(i, 16);	//0225 : ����
			arrItem[17] = fidCommRecvData.GetItem(i, 17);	//0053 : �ֽľ׸鰡
			arrItem[18] = fidCommRecvData.GetItem(i, 18);	//0016 : �ֽı��ذ�
			arrItem[19] = fidCommRecvData.GetItem(i, 19);	//0056 : �ں���
			arrItem[20] = fidCommRecvData.GetItem(i, 20);	//0055 : �����ּ�
			arrItem[21] = fidCommRecvData.GetItem(i, 21);	//2067 : ��������
			arrItem[22] = fidCommRecvData.GetItem(i, 22);	//0684 : �ſ��ܰ����
			arrItem[23] = fidCommRecvData.GetItem(i, 23);	//1253 : �ŷ���������(N : ����, Y : �ŷ�����)
			arrItem[24] = fidCommRecvData.GetItem(i, 24);	//1254 : �����Ÿſ���(N : ����, Y : �����Ÿ�)
			arrItem[25] = fidCommRecvData.GetItem(i, 25);	//1258 : �������񿩺�(N : ����, Y : ��������)
			arrItem[26] = fidCommRecvData.GetItem(i, 26);	//1251 : ���������ڵ�(00:���� 01 : ���� 02 : ��� 03 : ����)
			arrItem[27] = fidCommRecvData.GetItem(i, 27);	//2608 : �����������ڵ� Y, N = > mrkt_alrm_risk_adnt_yn
			arrItem[28] = fidCommRecvData.GetItem(i, 28);	//1252 : �Ҽ��ǰ������� ���� Y, N
			arrItem[29] = fidCommRecvData.GetItem(i, 29);	//1992 : ��ȸ���屸�� Y, N
			arrItem[30] = fidCommRecvData.GetItem(i, 30);	//1256 : �������ڵ�
			arrItem[31] = fidCommRecvData.GetItem(i, 31);	//0222 : ��� �ſ� ����
			arrItem[32] = fidCommRecvData.GetItem(i, 32);	//2129 : ���������� ���а� 1 : �ش� 0 : ���ش�
			arrItem[33] = fidCommRecvData.GetItem(i, 33);	//2148 : Equity Rating���� A, B, C, D, F ����� X
			arrItem[34] = fidCommRecvData.GetItem(i, 34);	//0019 : �ð��Ѿ�(��)
			arrItem[35] = fidCommRecvData.GetItem(i, 35);	//0021 : �ܱ��κ�������
			arrItem[36] = fidCommRecvData.GetItem(i, 36);	//1896 : �켱�� ���� �ڵ�(0:������, �׿� : �켱��)

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listCode.InsertItem(&lvItem);

			//����Ʈ ��Ʈ�ѿ� �׸� ����Ÿ �Է�
			for (int col = 0; col < 37; col++)
			{
				m_listCode.SetItemText(nListIndex, col, (LPTSTR)(LPCTSTR)arrItem[col]);
			}

		}//End of for
		m_listCode.EnsureVisible(nViewScrollPos, FALSE);
		m_listCode.SetRedraw(TRUE);

		/*--------------------------------------
		������ȸŰ�� ������ ���´�.
		---------------------------------------*/
		m_strCodeListNextRqKey = strPreNextContext;

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdCodeList = 0;	//�ֽ� ���� ����Ʈ(������) ��ȸ Request ID

	}
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
void CStockOrdDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/*	���� : OnGetRealData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
		�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/
	CString strRealMessage;

	/***************************************
	 ü��Ȯ��
	 ****************************************/
	if (!_tcscmp(strRealName, "IS0"))
	{
		/*--------------------------------------
		 �����۸����� ���ŵ� �ǽð� �����͸� �׸񺰷� ������.
		 ---------------------------------------*/		
		CString strsDataType = m_CommAgent.GetRealOutputData("IS0", "sDataType");		//�����ͱ���
		CString strsProcTime = m_CommAgent.GetRealOutputData("IS0", "sProcTime");		//ó���ð�
		CString strsComCode = m_CommAgent.GetRealOutputData("IS0", "sComCode");		//��ü����
		CString strsUserID = m_CommAgent.GetRealOutputData("IS0", "sUserID");		//�����ID
		CString strsCtno = m_CommAgent.GetRealOutputData("IS0", "sCtno");		//���´�ü��ȣ
		CString strsAcctNo = m_CommAgent.GetRealOutputData("IS0", "sAcctNo");		//���¹�ȣ
		CString strsAcctName = m_CommAgent.GetRealOutputData("IS0", "sAcctName");		//���¸�
		CString strsBidCode = m_CommAgent.GetRealOutputData("IS0", "sBidCode");		//�ֹ�����
		CString strsModType = m_CommAgent.GetRealOutputData("IS0", "sModType");		//������ұ���
		CString strsBidDetail = m_CommAgent.GetRealOutputData("IS0", "sBidDetail");		//�ֹ��󼼱���
		CString strsItemCode = m_CommAgent.GetRealOutputData("IS0", "sItemCode");		//���������ڵ�
		CString strsItemName = m_CommAgent.GetRealOutputData("IS0", "sItemName");		//�����
		CString strsOrdVol = m_CommAgent.GetRealOutputData("IS0", "sOrdVol");		//�ֹ�����
		CString strsOrdPrice = m_CommAgent.GetRealOutputData("IS0", "sOrdPrice");		//�ֹ�����
		CString strsHogaType = m_CommAgent.GetRealOutputData("IS0", "sHogaType");		//ȣ������
		CString strsOrderCon = m_CommAgent.GetRealOutputData("IS0", "sOrderCon");		//�ֹ�����
		CString strsBrnNo = m_CommAgent.GetRealOutputData("IS0", "sBrnNo");		//������ȣ
		CString strsOrdNo = m_CommAgent.GetRealOutputData("IS0", "sOrdNo");		//�ֹ���ȣ
		CString strsOrgOrdNo = m_CommAgent.GetRealOutputData("IS0", "sOrgOrdNo");		//���ֹ���ȣ
		CString strsContVol = m_CommAgent.GetRealOutputData("IS0", "sContVol");		//ü�����
		CString strsContPrice = m_CommAgent.GetRealOutputData("IS0", "sContPrice");		//ü�ᰡ��
		CString strsOrderModName = m_CommAgent.GetRealOutputData("IS0", "sOrderModName");		//�ֹ�������ұ��и�
		CString strsOrderStatName = m_CommAgent.GetRealOutputData("IS0", "sOrderStatName");		//�ֹ�ó�����±��и�
		CString strsOrderTypeName = m_CommAgent.GetRealOutputData("IS0", "sOrderTypeName");		//�ֹ������ڵ��
		CString strsRejectCode = m_CommAgent.GetRealOutputData("IS0", "sRejectCode");		//�źλ����ڵ�
		CString strsRejectReason = m_CommAgent.GetRealOutputData("IS0", "sRejectReason");		//�źλ���
		CString strsUnContVol = m_CommAgent.GetRealOutputData("IS0", "sUnContVol");		//��ü�����
		CString strsCreditType = m_CommAgent.GetRealOutputData("IS0", "sCreditType");		//�ſ뱸��
		CString strsCreditLoanDate = m_CommAgent.GetRealOutputData("IS0", "sCreditLoanDate");		//�ſ������
		CString strsCreditSn = m_CommAgent.GetRealOutputData("IS0", "sCreditSn");		//�����Ϸù�ȣ
		CString strsCreditPayment = m_CommAgent.GetRealOutputData("IS0", "sCreditPayment");		//�ſ��/�����ȯ��
		CString strsWrapNo = m_CommAgent.GetRealOutputData("IS0", "sWrapNo");		//Wrap�ֹ���ȣ
		CString strsGroupNo = m_CommAgent.GetRealOutputData("IS0", "sGroupNo");		//�׷��ȣ
		CString strsSeqNo = m_CommAgent.GetRealOutputData("IS0", "sSeqNo");		//�ٽ��Ͻ�����
		CString strsBndlOrdrGrupSn = m_CommAgent.GetRealOutputData("IS0", "sBndlOrdrGrupSn");		//�ϰ��ֹ��׷��Ϸù�ȣ
		CString strsOrdrKndDcd = m_CommAgent.GetRealOutputData("IS0", "sOrdrKndDcd");		//�ֹ����������ڵ�
		CString strsFiller = m_CommAgent.GetRealOutputData("IS0", "sFiller");		//Filler


		/*--------------------------------------
		��ȸ ������ ����� �ֽ� ���簡 �ǽð�Ű�� �������� ��
		---------------------------------------*/
		if (m_strLoginID == strRealKey)
		{
			strRealMessage.Format("[%s][����:%s][��ǰ:%s][ü��:%s]", strRealName, strsAcctNo, strsItemCode, strsContVol);
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

//*******************************************************************
// Function Name : OnAgentEventHandler
// Function      : 
// Param         : long nEventType, long nParam, LPCTSTR strParam
// Return        : void 
// Create        : 2016/11/10
// Comment       : ������Ʈ �̺�Ʈ �ڵ鷯
//******************************************************************
void CStockOrdDlg::OnAgentEventHandler(long nEventType, long nParam, LPCTSTR strParam)
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

void CStockOrdDlg::InitListCode()
{
	CRect rc;
	m_listCode.GetClientRect(rc);
	m_listCode.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int arrWidth[37] = { 60, 80, 90, 60,
		70, 80, 80, 80,
		80, 80, 80, 80,
		80, 80, 80, 80,
		80, 80, 80, 80,
		80, 80, 80, 80,
		80, 80, 80, 80,
		80, 80, 80, 80,
		80, 80, 80, 80,
		80 };

	int nWidth = rc.Width() - ::GetSystemMetrics(SM_CYHSCROLL);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("�����ڵ�"), _T("ǥ���ڵ�"), _T("�����"), _T("���屸��"),
		_T("�����ڵ�"), _T("�ð����ڵ�"), _T("��з�"), _T("�ߺз�"),
		_T("�Һз�"), _T("������"), _T("�������"), _T("���豸��"),
		_T("KSP200"), _T("KSP100"), _T("��ó���"), _T("KRX100"),
		_T("����"), _T("�׸鰡"), _T("���ذ�"), _T("�ں���"),
		_T("�����ּ�"), _T("������"), _T("�ſ��ܰ�"), _T("�ŷ�����"),
		_T("�����Ÿ�"), _T("��������"), _T("������"), _T("������"),
		_T("�Ҽ���"), _T("��ȸ����"), _T("������"), _T("���ſ�"),
		_T("������"), _T("EQ Rating"), _T("�ð���"), _T("�ܱ���"),
		_T("�켱��") };

	int i;
	for (i = 0; i < 37; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		if (i == 0)
			lvcolumn.fmt = LVCFMT_CENTER;
		else
			lvcolumn.fmt = LVCFMT_LEFT;

		lvcolumn.pszText = strTitle[i];

		lvcolumn.iSubItem = i;
		lvcolumn.cx = arrWidth[i];
		m_listCode.InsertColumn(i, &lvcolumn);
	}
}

BOOL CStockOrdDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN )
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
