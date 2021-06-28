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
#include "FxMarginOrdDlg.h"

#define ID_SECOND_TIMER		100	//1�� ���� Ÿ�̸�

#define SELL_BK_COLOR		RGB(206, 232, 255)	//�ŵ� ����
#define BUY_BK_COLOR		RGB(251, 221, 255)	//�ż� ����

//��� ����ü ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern void NumericString(CString& strValue, BOOL bNotDisplayZero = FALSE);

static char* g_szPriceCond[] = { "2", "1", "3"}; //1:���尡, 2:������, 3:��������

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

// CFxMarginOrdDlg ��ȭ ����
CFxMarginOrdDlg::CFxMarginOrdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFxMarginOrdDlg::IDD, pParent)
{
	m_bCommConnect		= FALSE;

	m_nRqIdAccNoList		= 0;	//������ȸ Request ID
	m_nRqIdFDemoAccNoList	= 0;	//�ؿܸ��� ������ȸ Request ID

	m_nRqIdSellOrd			= 0;	//�ŵ��ֹ� Request ID
	m_nRqIdBuyOrd			= 0;	//�ż��ֹ� Request ID
	m_nRqIdChangeOrd		= 0;	//�����ֹ� Request ID
	m_nRqIdCancelOrd		= 0;	//����ֹ� Request ID

	m_nRqIdNonExecList		= 0;	//��ü�᳻�� Request ID
	m_nRqIdExecList			= 0;	//�ֹ�ü�᳻�� Request ID
	m_nRqIdDepositList		= 0;	//�����ݳ��� Request ID

	m_nRqIdCloseOrd			= 0;	//û���ֹ� Request ID
	m_nRqIdModSLOrd			= 0;	//SL�����ֹ� Request ID
	m_nRqIdCanSLOrd			= 0;	//SL����ֹ� Request ID

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_nSeverType			= 0;	//0-����, 1-��������, 2-�ؿܹ���

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFxMarginOrdDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_DATETIME_N1, m_dateTimeN1);
	DDX_Control(pDX, IDC_DATETIME_N2, m_dateTimeN2);
	DDX_Control(pDX, IDC_DATETIME_E1, m_dateTimeE1);
	DDX_Control(pDX, IDC_DATETIME_E2, m_dateTimeE2);
}

BEGIN_MESSAGE_MAP(CFxMarginOrdDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_LOGIN, &CFxMarginOrdDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_LOGOUT, &CFxMarginOrdDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDOK, &CFxMarginOrdDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELL, &CFxMarginOrdDlg::OnBnClickedBtnSell)
	ON_BN_CLICKED(IDC_BTN_BUY, &CFxMarginOrdDlg::OnBnClickedBtnBuy)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CFxMarginOrdDlg::OnBnClickedBtnChange)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CFxMarginOrdDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST, &CFxMarginOrdDlg::OnBnClickedBtnReqExecList)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST_NEXT, &CFxMarginOrdDlg::OnBnClickedBtnReqExecListNext)
	ON_BN_CLICKED(IDC_BTN_REQ_ACCNO, &CFxMarginOrdDlg::OnBnClickedBtnReqAccno)
	ON_BN_CLICKED(IDC_BTN_REQ_DEPOSIT, &CFxMarginOrdDlg::OnBnClickedBtnReqDeposit)
	ON_BN_CLICKED(IDC_BTN_REQ_DEPOSIT_NEXT, &CFxMarginOrdDlg::OnBnClickedBtnReqDepositNext)
	ON_BN_CLICKED(IDC_BTN_REQ_NON_EXEC_LIST, &CFxMarginOrdDlg::OnBnClickedBtnReqNonExecList)
	ON_BN_CLICKED(IDC_BTN_REQ_NON_EXEC_LIST_NEXT, &CFxMarginOrdDlg::OnBnClickedBtnReqNonExecListNext)
	ON_BN_CLICKED(IDC_BTN_REQ_BALANCE, &CFxMarginOrdDlg::OnBnClickedBtnReqBalance)
	ON_BN_CLICKED(IDC_BTN_REQ_BALANCE_NEXT, &CFxMarginOrdDlg::OnBnClickedBtnReqBalanceNext)
	ON_BN_CLICKED(IDC_BTN_LOAD_USER_ACC, &CFxMarginOrdDlg::OnBnClickedBtnLoadUserAcc)
	ON_COMMAND_RANGE(IDC_CON_REAL, IDC_CON_F_DEMO, &CFxMarginOrdDlg::OnRdoSelectServer)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCNO, &CFxMarginOrdDlg::OnNMDblclkListAccNo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NON_EXE, &CFxMarginOrdDlg::OnNMDblclkListNonExec)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BALANCE, &CFxMarginOrdDlg::OnNMDblclkListBalance)
	ON_BN_CLICKED(IDC_BTN_ACCINFO, &CFxMarginOrdDlg::OnBnClickedBtnAccinfo)
	ON_BN_CLICKED(IDC_RADIO_EX1, &CFxMarginOrdDlg::OnBnClickedRadioEx1)
	ON_BN_CLICKED(IDC_RADIO_EX2, &CFxMarginOrdDlg::OnBnClickedRadioEx2)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CFxMarginOrdDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_MODSL, &CFxMarginOrdDlg::OnBnClickedBtnModsl)
	ON_BN_CLICKED(IDC_BTN_CALSL, &CFxMarginOrdDlg::OnBnClickedBtnCalsl)
END_MESSAGE_MAP()

// agent�κ��� �̺�Ʈ ���� �Լ��� �����Ѵ�.
BEGIN_EVENTSINK_MAP(CFxMarginOrdDlg, CDialog)
	ON_EVENT(CFxMarginOrdDlg, IDC_HFCOMMAGENTCTRL1, 1, CFxMarginOrdDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CFxMarginOrdDlg, IDC_HFCOMMAGENTCTRL1, 2, CFxMarginOrdDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CFxMarginOrdDlg, IDC_HFCOMMAGENTCTRL1, 3, CFxMarginOrdDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
	ON_EVENT(CFxMarginOrdDlg, IDC_HFCOMMAGENTCTRL1, 4, CFxMarginOrdDlg::OnAgentEventHandler, VTS_I4 VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

// CFxMarginOrdDlg �޽��� ó����
void CFxMarginOrdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CFxMarginOrdDlg::OnPaint()
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
HCURSOR CFxMarginOrdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CFxMarginOrdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CFxMarginOrdDlg::OnNMDblclkListAccNo(NMHDR *pNMHDR, LRESULT *pResult)
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

void CFxMarginOrdDlg::OnNMDblclkListNonExec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	CString strOrdNo = m_listNonExec.GetItemText(nSelectRow, 3);
	CString strSymbol = m_listNonExec.GetItemText(nSelectRow, 5);
	CString strHouseCode = m_listNonExec.GetItemText(nSelectRow, 4);
	CString strOrdPrice = m_listNonExec.GetItemText(nSelectRow, 13);
	CString strStopPrice = m_listNonExec.GetItemText(nSelectRow, 26);
	CString strLimitPrice = m_listNonExec.GetItemText(nSelectRow, 27);
	CString strTStopPrice = m_listNonExec.GetItemText(nSelectRow, 28);
	CString strOrdSu = m_listNonExec.GetItemText(nSelectRow, 14);
	CString strOrderType = m_listNonExec.GetItemText(nSelectRow, 22);

	GetDlgItem(IDC_EDIT_ORG_NO)->SetWindowText(strOrdNo);
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_EDIT_SYMBOL_HOUSE)->SetWindowText(strHouseCode);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);

	GetDlgItem(IDC_EDIT_STOP_PRC)->SetWindowText(strStopPrice);
	GetDlgItem(IDC_EDIT_LIMIT_PRC)->SetWindowText(strLimitPrice);
	GetDlgItem(IDC_EDIT_T_STOP_PRC)->SetWindowText(strTStopPrice);

	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);

	static char* g_szPriceCond[] = { "2", "1", "3" }; //1:���尡, 2:������, 3:��������
	for (int i = 0; i < 3; i++)
	{
		if (strOrderType == g_szPriceCond[i])
			m_cmdOrdType.SetCurSel(i);
	}
}

void CFxMarginOrdDlg::OnNMDblclkListBalance(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;

	CString strPosNo = m_listBalance.GetItemText(nSelectRow, 0);
	CString strSymbol = m_listBalance.GetItemText(nSelectRow, 8);
	CString strSellBuyDiv = m_listBalance.GetItemText(nSelectRow, 10);
	CString strOrdPrice = m_listBalance.GetItemText(nSelectRow, 11);
	CString strOrdSu = m_listBalance.GetItemText(nSelectRow, 15);
	CString strHouseCode = m_listBalance.GetItemText(nSelectRow, 7);
	CString strOrdNo = m_listBalance.GetItemText(nSelectRow, 31);

	CString strStop = m_listBalance.GetItemText(nSelectRow, 49);
	CString strLimit = m_listBalance.GetItemText(nSelectRow, 50);
	CString strTS = m_listBalance.GetItemText(nSelectRow, 51);

	GetDlgItem(IDC_EDIT_ORG_NO)->SetWindowText(strPosNo);
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_POS_SELLBUY)->SetWindowText(strSellBuyDiv);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);
	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);
	GetDlgItem(IDC_EDIT_SYMBOL_HOUSE)->SetWindowText(strHouseCode);
	GetDlgItem(IDC_ORDER_NO)->SetWindowText(strOrdNo);

	GetDlgItem(IDC_EDIT_STOP_PRC)->SetWindowText(strStop);
	GetDlgItem(IDC_EDIT_LIMIT_PRC)->SetWindowText(strLimit);
	GetDlgItem(IDC_EDIT_T_STOP_PRC)->SetWindowText(strTS);
}

void CFxMarginOrdDlg::OnDestroy()
{
	//��� �ǽð������ �����Ѵ�.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();
	
	CDialog::OnDestroy();
}

void CFxMarginOrdDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CFxMarginOrdDlg::OnTimer(UINT_PTR nIDEvent)
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
void CFxMarginOrdDlg::OnRdoSelectServer(UINT nID)
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
void CFxMarginOrdDlg::OnBnClickedBtnAccinfo()
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
BOOL CFxMarginOrdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CString strTitle;
	strTitle.Format("%s-[FX�����ֹ�](%s)", PROGRAM_NAME, VERSION_INFO);
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

	((CButton*)GetDlgItem(IDC_RADIO_EX1))->SetCheck(1);

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
void CFxMarginOrdDlg::InitListAccNo()
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
void CFxMarginOrdDlg::InitListReal()
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
void CFxMarginOrdDlg::InitListNonExec()
{
	CRect rc;
	m_listNonExec.GetClientRect(rc);
	m_listNonExec.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("�����Ͽ콺������"),
		_T("���¹�ȣ"),
		_T("��ü��ȣ"),
		_T("�ֹ���ȣ"),
		_T("�����Ͽ콺������ȣ"),
		_T("��ǰ�ڵ�"),
		_T("���ֹ���ȣ"),
		_T("���ֹ���ȣ"),
		_T("�ֹ��׷��ȣ"),
		_T("�ֹ�����"),
		_T("���»�ǰ��ȣ"),
		_T("����"),
		_T("�Ÿű����ڵ�"),
		_T("�ֹ�����"),
		_T("�ֹ�����"),
		_T("��������"),
		_T("��Ҽ���"),
		_T("ü�����"),
		_T("�ֹ��ܿ�����"),
		_T("�������ݾ�"),
		_T("FX�ֹ��ѱݾ�"),
		_T("FX�ܿ��ѱݾ�"),
		_T("�������Ǳ����ڵ�"),
		_T("ü�����Ǳ����ڵ�"),
		_T("1����ž�ν�����"),
		_T("1������������"),
		_T("1����ž�ν�����"),
		_T("1����������"),
		_T("1�����������Ű���"),
		_T("2����ž�ν�����"),
		_T("2������������"),
		_T("2����ž�ν�����"),
		_T("2����������"),
		_T("2�����������Ű���"),
		_T("���ü�ᰡ��"),
		_T("ü����"),
		_T("���簡��"),
		_T("��Ÿ�ü�����ڵ�"),
		_T("�ֹ����������ڵ�"),
		_T("�ֹ����±����ڵ�"),
		_T("FCM�ֹ���ȣ"),
		_T("�����ID"),
		_T("����IP�ּ�"),
		_T("�ŷ��������ð�"),
		_T("�ŷ���ü��ð�"),
		_T("�ֹ��ð�"),
		_T("ü��ð�"),
		_T("��ȭ�ڵ�"),
		_T("���ݼҼ������ϱ���"),
		_T("�ŸŰ������̳���") };

	int i;
	for (i = 0; i < 50; i++)
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
void CFxMarginOrdDlg::InitListExec()
{
	CRect rc;
	m_listExec.GetClientRect(rc);
	m_listExec.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("�����Ͽ콺������"),
		_T("���¹�ȣ"),
		_T("��ü��ȣ"),
		_T("�ֹ���ȣ"),
		_T("�����Ͽ콺������ȣ"),
		_T("��ǰ�ڵ�"),
		_T("���ֹ���ȣ"),
		_T("���ֹ���ȣ"),
		_T("�ֹ��׷��ȣ"),
		_T("�ֹ�����"),
		_T("���»�ǰ��ȣ"),
		_T("����"),
		_T("�Ÿű����ڵ�"),
		_T("�ֹ�����"),
		_T("�ֹ�����"),
		_T("��������"),
		_T("��Ҽ���"),
		_T("ü�����"),
		_T("�ֹ��ܿ�����"),
		_T("�������ݾ�"),
		_T("FX�ֹ��ѱݾ�"),
		_T("FX�ܿ��ѱݾ�"),
		_T("�������Ǳ����ڵ�"),
		_T("ü�����Ǳ����ڵ�"),
		_T("1����ž�ν�����"),
		_T("1������������"),
		_T("1����ž�ν�����"),
		_T("1����������"),
		_T("1�����������Ű���"),
		_T("2����ž�ν�����"),
		_T("2������������"),
		_T("2����ž�ν�����"),
		_T("2����������"),
		_T("2�����������Ű���"),
		_T("���ü�ᰡ��"),
		_T("ü����"),
		_T("���簡��"),
		_T("��Ÿ�ü�����ڵ�"),
		_T("�ֹ����������ڵ�"),
		_T("�ֹ����±����ڵ�"),
		_T("FCM�ֹ���ȣ"),
		_T("�����ID"),
		_T("����IP�ּ�"),
		_T("�ŷ��������ð�"),
		_T("�ŷ���ü��ð�"),
		_T("�ֹ��ð�"),
		_T("ü��ð�"),
		_T("��ȭ�ڵ�"),
		_T("���ݼҼ������ϱ���"),
		_T("�ŸŰ������̳���") };

	int i;
	for (i = 0; i < 50; i++)
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
void CFxMarginOrdDlg::InitListDeposit()
{
	CRect rc;
	m_listDeposit.GetClientRect(rc);
	m_listDeposit.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("��ȭ"), _T("���������ܾ�"), _T("����ݾ�"), _T("FX������"), _T("�ѿ�������"),
		_T("���Ͽ�Ź��"), _T("û��ݾ�"), _T("�̰����򰡼���"), _T("�򰡿�Ź"),
		_T("��Ź���ű�"), _T("�߰����ű�"), _T("�̼��ݾ�"), _T("�ֹ����ɱݾ�"), _T("���Ⱑ�ɱݾ�"), _T("�������ű�"), _T("������") };

	int i;
	for (i = 0; i < 16; i++)
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
void CFxMarginOrdDlg::InitListBalance()
{
	CRect rc;
	m_listBalance.GetClientRect(rc);
	m_listBalance.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("�����ǹ�ȣ"),
		_T("��ü��ȣ"),
		_T("���¹�ȣ"),
		_T("���»�ǰ��ȣ"),
		_T("ü������"),
		_T("��������"),
		_T("��Ź�ڱⱸ��"),
		_T("�����Ͽ콺��ȣ"),
		_T("��ǰ"),
		_T("ȣ��������ȣ"),
		_T("�ŵ��ż�����"),
		_T("ü�ᰡ��"),
		_T("����ü�����"),
		_T("û�����"),
		_T("ü����Ұŷ�����"),
		_T("�̰�����������"),
		_T("�̰��������ݾ�2"),
		_T("�̰��������ݾ�3"),
		_T("ü��PIP��ġ�ݾ�"),
		_T("�����ݾ�"),
		_T("�̰��������ݾ�"),
		_T("����ȯ��"),
		_T("���갡��"),
		_T("�򰡼��ͱݾ�"),
		_T("PIP��ġ�ݾ�"),
		_T("ȯ���򰡼��ͱݾ�"),
		_T("���걳��ȯ��"),
		_T("�¶��ΰŷ�����"),
		_T("ü���ȣ"),
		_T("���������ǿ���"),
		_T("��뿩��"),
		_T("�ֹ���ȣ"),
		_T("���ֹ���ȣ"),
		_T("���ֹ���ȣ"),
		_T("�ֹ��׷��ȣ"),
		_T("�ֹ�����"),
		_T("����"),
		_T("�ֹ�����"),
		_T("���尡�����뼳���ݾ�"),
		_T("�ֹ�����"),
		_T("��������"),
		_T("��Ҽ���"),
		_T("ü�����"),
		_T("�ֹ��ܿ�����"),
		_T("�������Ǳ���"),
		_T("ü�����Ǳ���"),
		_T("1����ž�ν�����"),
		_T("1������������"),
		_T("1�����п���"),
		_T("1����ž�ν�����"),
		_T("1����������"),
		_T("1�����������Ű���"),
		_T("�������ݾ�"),
		_T("�ֹ����ⱸ��"),
		_T("���ü�ᰡ��"),
		_T("���簡��"),
		_T("��ǰ2")	};

	int i;
	for (i = 0; i < 57; i++)
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
void CFxMarginOrdDlg::OnBnClickedLogin()
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
	//��ü��/ü�� �ǽð� �뺸
	m_CommAgent.RegisterReal("FX0", m_strLoginID);
	
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : �α׾ƿ�
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedLogout()
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
void CFxMarginOrdDlg::OnBnClickedOk()
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
void CFxMarginOrdDlg::OnBnClickedBtnReqAccno()
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
void CFxMarginOrdDlg::OnBnClickedBtnLoadUserAcc()
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
CString CFxMarginOrdDlg::GetAccAPNO(CString strAccNo)
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
void CFxMarginOrdDlg::RequestAccList()
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
void CFxMarginOrdDlg::RequestFDemoAccList()
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
BOOL CFxMarginOrdDlg::SendSellBuyOrder(CString strDealingSide, int nRqId, CString strOrderKind /*= _T("")*/)
{
	CString strTrCode = "OTS5901U31";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5901U31_in";		//�Է� ���ڵ��(���ҽ����� ����)

	//[1] Request ID����
	CString strCTNO;		//���հ��´�ü��ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strPWD;			//��й�ȣ
	CString strFDM_UNQ_NO;	//�����Ͽ콺������ȣ
	CString strPRDT_CD;		//��ǰ�ڵ�
	CString strNMPR_UNQ_NO;	//ȣ��������ȣ
	CString strENTR_CLR_DCD;//����û�걸���ڵ�
	CString strPST_NO;		//�����ǹ�ȣ
	CString strODRV_SELL_BUY_DCD;		//�ؿ��Ļ��ŵ��ż������ڵ�
	CString strPRC_CND_DCD;		//�������Ǳ����ڵ�
	CString strODRV_ORDR_PRC;		//�ؿ��Ļ��ֹ�����
	CString strORDR_QNT;		//�ֹ�����
	CString strSQ1_STLS_YN;		//1����ž�ν�����
	CString strSQ1_APMPR_YN;		//1������������
	CString strSQ1_STLS_PRC;		//1����ž�ν�����
	CString strSQ1_APPN_PRC;		//1����������
	CString strSQ1_CHAS_STLS_PRC;		//1�����������Ű���
	CString strSQ2_STLS_YN;		//2����ž�ν�����
	CString strSQ2_APMPR_YN;		//2������������
	CString strSQ2_STLS_PRC;		//2����ž�ν�����
	CString strSQ2_APPN_PRC;		//2����������
	CString strSQ2_CHAS_STLS_PRC;		//2�����������Ű���
	CString strORDR_DRCN_DCD;		//�ֹ����ⱸ���ڵ�
	CString strORDR_SRC_DCD;		//�ֹ���õ�����ڵ�
	CString strTRDE_PRC_DFRN_CTNS;		//�ŸŰ������̳���

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//��й�ȣ
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//��ǰ�ڵ�

	//�����Ͽ콺������ȣ
	GetDlgItem(IDC_EDIT_SYMBOL_HOUSE)->GetWindowText(strFDM_UNQ_NO);
	
	//��ǰ�ڵ�
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//ȣ��������ȣ
	strNMPR_UNQ_NO = _T("0");

	//�ֹ�����
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	//1����ž�ν�����(STOP)
	GetDlgItem(IDC_EDIT_STOP_PRC)->GetWindowText(strSQ1_STLS_PRC);
	//1����ž�ν�����(STOP)
	if (_ttof(strSQ1_STLS_PRC))
		strSQ1_STLS_YN = _T("Y");
	else
		strSQ1_STLS_YN = _T("N");

	//1����������(LIMIT)
	GetDlgItem(IDC_EDIT_LIMIT_PRC)->GetWindowText(strSQ1_APPN_PRC);
	//1������������(LIMIT)
	if (_ttof(strSQ1_APPN_PRC))
		strSQ1_APMPR_YN = _T("Y");
	else
		strSQ1_APMPR_YN = _T("N");

	//1�����������Ű���(T.Stop)
	GetDlgItem(IDC_EDIT_T_STOP_PRC)->GetWindowText(strSQ1_CHAS_STLS_PRC);
	//2����ž�ν�����
	if (_ttof(strSQ1_CHAS_STLS_PRC))
		strSQ2_STLS_YN = _T("Y");
	else
		strSQ2_STLS_YN = _T("N");

	strSQ2_STLS_PRC = _T("0");		//2����ž�ν�����(������)
	strSQ2_APPN_PRC = _T("0");		//2����������(������)
	strSQ2_APMPR_YN = _T("N");		//2������������(������)
	strSQ2_CHAS_STLS_PRC = _T("0");		//2�����������Ű���(������)

	//�ֹ����ⱸ���ڵ�(N-�Ϲ��ֹ�, W-����ֹ� (�Ϲ��ֹ��� ���))
	strORDR_DRCN_DCD = _T("N");

	//�ֹ���õ�����ڵ�(C-�Ϲ��ֹ�)
	strORDR_SRC_DCD = _T("C");

	//�ŸŰ������̳���(������)
	strTRDE_PRC_DFRN_CTNS.Empty();
	
	//û���ֹ�, SL�ֹ�
	if (!strOrderKind.CompareNoCase(_T("CloseOrder")) ||
		!strOrderKind.CompareNoCase(_T("SLOrder")))
	{

		/***************************************************
		* ***** ���� *****
		* û���ֹ���(�ݴ�Ÿ� û�� ����) Stop, Limit�� ��� �Ŀ�
		* �����մϴ�.
		***************************************************/

		//����û�걸���ڵ�(C - û��, O - �ű�)
		strENTR_CLR_DCD = _T("C");

		//�����ǹ�ȣ(û���ֹ� �ʿ�)
		GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strPST_NO);

		//û���� �ű��ֹ��� �ݴ� �Ÿű������� �ֹ��� ����.
		if (!strDealingSide.CompareNoCase(_T("S")))
			strODRV_SELL_BUY_DCD = _T("B");
		else
			strODRV_SELL_BUY_DCD = _T("S");

		strPRC_CND_DCD = _T("2"); //û���ֹ��� �ֹ������� ���尡�� �Ѵ�.

		CString strSLOrderNo;
		GetDlgItem(IDC_ORDER_NO)->GetWindowText(strSLOrderNo);
		strSLOrderNo.Trim();

		//SL�ֹ��̸� �ֹ������� �����Ѵ�.
		if (!strOrderKind.CompareNoCase(_T("SLOrder")))
		{
			//T.S
			if (!strSQ2_STLS_YN.CompareNoCase(_T("Y")))
			{
				strPRC_CND_DCD = _T("6");
			}
			//Stop �Ǵ� Limit
			else if (!strSQ1_STLS_YN.CompareNoCase(_T("Y")) ||
					 !strSQ1_APMPR_YN.CompareNoCase(_T("Y")))
			{
				strPRC_CND_DCD = _T("4");
			}
			//OCO �ֹ�
			else if (!strSQ1_STLS_YN.CompareNoCase(_T("Y")) &&
					 !strSQ1_APMPR_YN.CompareNoCase(_T("Y")))
			{
				strPRC_CND_DCD = _T("5");
			}
		}
	}
	else
	{
		//����û�걸���ڵ�(C - û��, O - �ű�)
		strENTR_CLR_DCD = _T("O");

		//�ؿ��Ļ��ŵ��ż������ڵ�(S-�ŵ�, B-�ż�)
		strODRV_SELL_BUY_DCD = strDealingSide;

		//�������Ǳ����ڵ�
		if (m_cmdOrdType.GetCurSel() >= 0)
			strPRC_CND_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];		//�������Ǳ����ڵ�
	}

	//�ؿ��Ļ��ֹ�����
	if (strPRC_CND_DCD == _T("1") || strPRC_CND_DCD == _T("3"))	//������, ��������(STOP)
		GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strODRV_ORDR_PRC);
	else //���尡
		strODRV_ORDR_PRC = _T("0");

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "PWD", strPWD);		//��й�ȣ
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//�����Ͽ콺������ȣ
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "NMPR_UNQ_NO", strNMPR_UNQ_NO);		//ȣ��������ȣ
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "ENTR_CLR_DCD", strENTR_CLR_DCD);		//����û�걸���ڵ�
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "PST_NO", strPST_NO);		//�����ǹ�ȣ
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//�ؿ��Ļ��ŵ��ż������ڵ�
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "PRC_CND_DCD", strPRC_CND_DCD);		//�������Ǳ����ڵ�
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "ODRV_ORDR_PRC", strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ1_STLS_YN", strSQ1_STLS_YN);		//1����ž�ν�����
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ1_APMPR_YN", strSQ1_APMPR_YN);		//1������������
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ1_STLS_PRC", strSQ1_STLS_PRC);		//1����ž�ν�����
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ1_APPN_PRC", strSQ1_APPN_PRC);		//1����������
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ1_CHAS_STLS_PRC", strSQ1_CHAS_STLS_PRC);		//1�����������Ű���
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ2_STLS_YN", strSQ2_STLS_YN);		//2����ž�ν�����
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ2_APMPR_YN", strSQ2_APMPR_YN);		//2������������
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ2_STLS_PRC", strSQ2_STLS_PRC);		//2����ž�ν�����
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ2_APPN_PRC", strSQ2_APPN_PRC);		//2����������
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ2_CHAS_STLS_PRC", strSQ2_CHAS_STLS_PRC);		//2�����������Ű���
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//�ֹ����ⱸ���ڵ�
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "ORDR_SRC_DCD", strORDR_SRC_DCD);		//�ֹ���õ�����ڵ�
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "TRDE_PRC_DFRN_CTNS", strTRDE_PRC_DFRN_CTNS);		//�ŸŰ������̳���

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
void CFxMarginOrdDlg::OnBnClickedBtnSell()
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
void CFxMarginOrdDlg::OnBnClickedBtnBuy()
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
void CFxMarginOrdDlg::OnBnClickedBtnChange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5901U32";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5901U32_in";	//�Է� ���ڵ��(���ҽ����� ����)
	
	//[1] Request ID����
	m_nRqIdChangeOrd = m_CommAgent.CreateRequestID();

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	CString strODRV_OR_ODNO;		//�ؿ��Ļ����ֹ���ȣ
	CString strCTNO;		//���հ��´�ü��ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strPWD;		//��й�ȣ
	CString strODRV_SELL_BUY_DCD;		//�ؿ��Ļ��ŵ��ż������ڵ�
	CString strFDM_UNQ_NO;		//�����Ͽ콺������ȣ
	CString strPRDT_CD;		//��ǰ�ڵ�
	CString strNMPR_UNQ_NO;		//ȣ��������ȣ
	CString strCNCS_CND_DCD;		//ü�����Ǳ����ڵ�
	CString strORDR_EXPR_DT;		//�ֹ���������
	CString strPRC_CND_DCD;		//�������Ǳ����ڵ�
	CString strODRV_ORDR_PRC;		//�ؿ��Ļ��ֹ�����
	CString strORDR_QNT;		//�ֹ�����
	CString strSQ1_STLS_YN;		//1����ž�ν�����
	CString strSQ1_APMPR_YN;		//1������������
	CString strSQ1_STLS_PRC;		//1����ž�ν�����
	CString strSQ1_APPN_PRC;		//1����������
	CString strSQ1_CHAS_STLS_PRC;		//1�����������Ű���
	CString strSQ2_STLS_YN;		//2����ž�ν�����
	CString strSQ2_STLS_PRC;		//2����ž�ν�����
	CString strSQ2_APMPR_YN;		//2������������
	CString strSQ2_APPN_PRC;		//2����������
	CString strSQ2_CHAS_STLS_PRC;		//2�����������Ű���
	CString strORDR_DRCN_DCD;		//�ֹ����ⱸ���ڵ�
	CString strTRDE_PRC_DFRN_CTNS;		//�ŸŰ������̳���

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//��й�ȣ
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//��ǰ�ڵ�

	//�ؿ��Ļ����ֹ���ȣ
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strODRV_OR_ODNO);

	//�����Ͽ콺������ȣ
	GetDlgItem(IDC_EDIT_SYMBOL_HOUSE)->GetWindowText(strFDM_UNQ_NO);

	//��ǰ�ڵ�
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//ȣ��������ȣ
	strNMPR_UNQ_NO = _T("0");

	//�ؿ��Ļ��ŵ��ż������ڵ�
	if (m_cmdOrdType.GetCurSel() >= 0)
		strODRV_SELL_BUY_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];		//�������Ǳ����ڵ�

	//�ֹ�����
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	//1����ž�ν�����(STOP)
	GetDlgItem(IDC_EDIT_STOP_PRC)->GetWindowText(strSQ1_STLS_PRC);
	//1����ž�ν�����(STOP)
	if (_ttof(strSQ1_STLS_PRC))
		strSQ1_STLS_YN = _T("Y");
	else
		strSQ1_STLS_YN = _T("N");

	//1����������(LIMIT)
	GetDlgItem(IDC_EDIT_LIMIT_PRC)->GetWindowText(strSQ1_APPN_PRC);
	//1������������(LIMIT)
	if (_ttof(strSQ1_APPN_PRC))
		strSQ1_APMPR_YN = _T("Y");
	else
		strSQ1_APMPR_YN = _T("N");

	//1�����������Ű���(T.Stop)
	GetDlgItem(IDC_EDIT_T_STOP_PRC)->GetWindowText(strSQ1_CHAS_STLS_PRC);
	//2����ž�ν�����
	if (_ttof(strSQ1_CHAS_STLS_PRC))
		strSQ2_STLS_YN = _T("Y");
	else
		strSQ2_STLS_YN = _T("N");

	strSQ2_STLS_PRC = _T("0");		//2����ž�ν�����(������)
	strSQ2_APPN_PRC = _T("0");		//2����������(������)
	strSQ2_APMPR_YN = _T("N");		//2������������(������)
	strSQ2_CHAS_STLS_PRC = _T("0");		//2�����������Ű���(������)

	//�ֹ����ⱸ���ڵ�(N-�Ϲ��ֹ�, W-����ֹ� (�Ϲ��ֹ��� ���))
	strORDR_DRCN_DCD = _T("N");

	//�ŸŰ������̳���(������)
	strTRDE_PRC_DFRN_CTNS.Empty();

	//�������Ǳ����ڵ�
	if (m_cmdOrdType.GetCurSel() >= 0)
		strPRC_CND_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];

	//�ؿ��Ļ��ֹ�����
	if (strPRC_CND_DCD == _T("1") || strPRC_CND_DCD == _T("3"))	//������, ��������(STOP)
		GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strODRV_ORDR_PRC);
	else //���尡
		strODRV_ORDR_PRC = _T("0");

	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "PWD", strPWD);		//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//�ؿ��Ļ��ŵ��ż������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//�����Ͽ콺������ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "NMPR_UNQ_NO", strNMPR_UNQ_NO);		//ȣ��������ȣ
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "CNCS_CND_DCD", strCNCS_CND_DCD);		//ü�����Ǳ����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "ORDR_EXPR_DT", strORDR_EXPR_DT);		//�ֹ���������
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "PRC_CND_DCD", strPRC_CND_DCD);		//�������Ǳ����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "ODRV_ORDR_PRC", strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_STLS_YN", strSQ1_STLS_YN);		//1����ž�ν�����
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_APMPR_YN", strSQ1_APMPR_YN);		//1������������
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_STLS_PRC", strSQ1_STLS_PRC);		//1����ž�ν�����
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_APPN_PRC", strSQ1_APPN_PRC);		//1����������
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_CHAS_STLS_PRC", strSQ1_CHAS_STLS_PRC);		//1�����������Ű���
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_STLS_YN", strSQ2_STLS_YN);		//2����ž�ν�����
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_STLS_PRC", strSQ2_STLS_PRC);		//2����ž�ν�����
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_APMPR_YN", strSQ2_APMPR_YN);		//2������������
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_APPN_PRC", strSQ2_APPN_PRC);		//2����������
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_CHAS_STLS_PRC", strSQ2_CHAS_STLS_PRC);		//2�����������Ű���
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//�ֹ����ⱸ���ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "TRDE_PRC_DFRN_CTNS", strTRDE_PRC_DFRN_CTNS);		//�ŸŰ������̳���

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
void CFxMarginOrdDlg::OnBnClickedBtnCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5901U33";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5901U33_in";	//�Է� ���ڵ��(���ҽ����� ����)

	//[1] Request ID����
	m_nRqIdCancelOrd = m_CommAgent.CreateRequestID();

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	CString strODRV_OR_ODNO;		//�ؿ��Ļ����ֹ���ȣ
	CString strCTNO;		//���հ��´�ü��ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strPWD;		//��й�ȣ
	CString strFDM_UNQ_NO;		//�����Ͽ콺������ȣ
	CString strPRDT_CD;		//��ǰ�ڵ�
	CString strORDR_QNT;		//�ֹ�����
	CString strORDR_DRCN_DCD;		//�ֹ����ⱸ���ڵ�

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//��й�ȣ
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//��ǰ�ڵ�

	//�ؿ��Ļ����ֹ���ȣ
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strODRV_OR_ODNO);

	//�����Ͽ콺������ȣ
	GetDlgItem(IDC_EDIT_SYMBOL_HOUSE)->GetWindowText(strFDM_UNQ_NO);

	//��ǰ�ڵ�
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//�ֹ�����
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	
	//�ֹ����ⱸ���ڵ�(N-�Ϲ��ֹ�, W-����ֹ� (�Ϲ��ֹ��� ���))
	strORDR_DRCN_DCD = _T("N");

	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "PWD", strPWD);		//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//�����Ͽ콺������ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//�ֹ����ⱸ���ڵ�

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
void CFxMarginOrdDlg::OnBnClickedBtnReqDeposit()
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

	CString strTrCode = "OTS5914Q51";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5914Q51_in";			//�Է� ���ڵ��(���ҽ����� ����)

	/*-------------------------------*
	 [1] Request ID����
	*-------------------------------*/
	m_nRqIdDepositList = m_CommAgent.CreateRequestID();

	CString strINQ_DT;			//��������
	CString strCTNO;			//��ü���հ��¹�ȣ
	CString strAPNO;			//���»�ǰ��ȣ
	CString strPWD;				//��й�ȣ(�ܹ��� ��ȣȭ�� �Ѵ�.)

	//��ȸ����
	m_dateTime1.GetWindowText(strINQ_DT);
	strINQ_DT.Remove('-');
	
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
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "INQ_DT", strINQ_DT);	//��������
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "CTNO", strCTNO);		//��ü���հ��¹�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "ACNT_PWD", strPWD);		//��й�ȣ

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
void CFxMarginOrdDlg::OnBnClickedBtnReqDepositNext()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5914Q51";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5914Q51_in";			//�Է� ���ڵ��(���ҽ����� ����)

	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdDepositList = m_CommAgent.CreateRequestID();

	CString strINQ_DT;		//��������
	CString strCTNO;		//��ü���հ��¹�ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strPWD;			//��й�ȣ

	//��ȸ����
	m_dateTime1.GetWindowText(strINQ_DT);
	strINQ_DT.Remove('-');

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
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "INQ_DT", strINQ_DT);	//��������
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "CTNO", strCTNO);		//��ü���հ��¹�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "ACNT_PWD", strPWD);		//��й�ȣ

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
void CFxMarginOrdDlg::OnBnClickedBtnReqNonExecList()
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

	CString strTrCode = "OTS5913Q53";				//Tran�ڵ�(���ҽ����� ����)
	
	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdNonExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] �Է� �Ǽ��� �Է��Ѵ�.
	*-------------------------------*/
	CString strAccNo;
	CString strINQ_STRT_DT;		//��ȸ��������
	CString strINQ_END_DT;		//��ȸ��������
	CString strSORT_MTH;		//���Ĺ��
	CString strCTNO;			//���հ��´�ü��ȣ
	CString strAPNO;			//���»�ǰ��ȣ
	CString strPRDT_CD;			//��ǰ�ڵ�
	CString strACNT_PWD;		//���º�й�ȣ
	CString strINQ_DVSN;		//��ȸ����

	//��ȸ��������
	m_dateTimeN1.GetWindowText(strINQ_STRT_DT);
	strINQ_STRT_DT.Remove('-');

	//��ȸ��������
	m_dateTimeN2.GetWindowText(strINQ_END_DT);
	strINQ_END_DT.Remove('-');

	//���Ĺ��(1-����, 2 ����)
	strSORT_MTH = _T("1");

	// ��ȸ���� 0:��ü(��ü��+�ź�), 1:��ü��
	if(((CButton*)GetDlgItem(IDC_RADIO_EX1))->GetCheck())
		strINQ_DVSN = "1";	//��ü�Ḹ ��ȸ
	else
		strINQ_DVSN = "0"; //��ü�� + �ź� ��ȸ


	//���´�ü��ȣ�� ���´�.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);

	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);
	
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ

	//���º�й�ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);

	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "INQ_STRT_DT", strINQ_STRT_DT);		//��ȸ��������
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "INQ_END_DT", strINQ_END_DT);		//��ȸ��������
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "SORT_MTH", strSORT_MTH);		//���Ĺ��
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "INQ_DVSN", strINQ_DVSN);		//��ȸ����

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
void CFxMarginOrdDlg::OnBnClickedBtnReqNonExecListNext()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strTrCode = "OTS5913Q53";				//Tran�ڵ�(���ҽ����� ����)
	
	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdNonExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] �Է� �Ǽ��� �Է��Ѵ�.
	*-------------------------------*/
	CString strAccNo;
	CString strINQ_STRT_DT;		//��ȸ��������
	CString strINQ_END_DT;		//��ȸ��������
	CString strSORT_MTH;		//���Ĺ��
	CString strCTNO;			//���հ��´�ü��ȣ
	CString strAPNO;			//���»�ǰ��ȣ
	CString strPRDT_CD;			//��ǰ�ڵ�
	CString strACNT_PWD;		//���º�й�ȣ
	CString strINQ_DVSN;		//��ȸ����

	//��ȸ��������
	m_dateTimeN1.GetWindowText(strINQ_STRT_DT);
	strINQ_STRT_DT.Remove('-');

	//��ȸ��������
	m_dateTimeN2.GetWindowText(strINQ_END_DT);
	strINQ_END_DT.Remove('-');

	//���Ĺ��(1-����, 2 ����)
	strSORT_MTH = _T("1");

	// ��ȸ���� 0:��ü(��ü��+�ź�), 1:��ü��
	if (((CButton*)GetDlgItem(IDC_RADIO_EX1))->GetCheck())
		strINQ_DVSN = "1";	//��ü�Ḹ ��ȸ
	else
		strINQ_DVSN = "0"; //��ü�� + �ź� ��ȸ

	//���´�ü��ȣ�� ���´�.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);

	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ

	//���º�й�ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);

	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "INQ_STRT_DT", strINQ_STRT_DT);		//��ȸ��������
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "INQ_END_DT", strINQ_END_DT);		//��ȸ��������
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "SORT_MTH", strSORT_MTH);		//���Ĺ��
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ

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
void CFxMarginOrdDlg::OnBnClickedBtnReqExecList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_listExec.DeleteAllItems();
	m_strListExecNextRqKey.Empty(); //����Ű�� �ʱ�ȭ��Ų��.

	CString strTrCode = "OTS5913Q52";				//Tran�ڵ�(���ҽ����� ����)
	
	/*-------------------------------*
		[1] Request ID����
	 *-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
		[2] �Է� �Ǽ��� �Է��Ѵ�.
	 *-------------------------------*/
	CString strAccNo;
	CString strINQ_STRT_DT;		//��ȸ��������
	CString strINQ_END_DT;		//��ȸ��������
	CString strSORT_MTH;		//���Ĺ��
	CString strCTNO;		//���հ��´�ü��ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strPRDT_CD;		//��ǰ�ڵ�
	CString strACNT_PWD;		//���º�й�ȣ

	//[3] Tran��ȸ �Է°��� �Է��Ѵ�.

	//��ȸ��������
	m_dateTimeE1.GetWindowText(strINQ_STRT_DT);
	strINQ_STRT_DT.Remove('-');

	//��ȸ��������
	m_dateTimeE2.GetWindowText(strINQ_END_DT);
	strINQ_END_DT.Remove('-');

	//���Ĺ��
	strSORT_MTH = _T("0");

	//���´�ü��ȣ�� ���´�.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);

	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ

	//���º�й�ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);

	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "INQ_STRT_DT", strINQ_STRT_DT);		//��ȸ��������
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "INQ_END_DT", strINQ_END_DT);		//��ȸ��������
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "SORT_MTH", strSORT_MTH);		//���Ĺ��
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ

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
void CFxMarginOrdDlg::OnBnClickedBtnReqExecListNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5913Q52";				//Tran�ڵ�(���ҽ����� ����)

	/*-------------------------------*
	[1] Request ID����
	*-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] �Է� �Ǽ��� �Է��Ѵ�.
	*-------------------------------*/
	CString strAccNo;
	CString strINQ_STRT_DT;		//��ȸ��������
	CString strINQ_END_DT;		//��ȸ��������
	CString strSORT_MTH;		//���Ĺ��
	CString strCTNO;		//���հ��´�ü��ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strPRDT_CD;		//��ǰ�ڵ�
	CString strACNT_PWD;		//���º�й�ȣ

	//[3] Tran��ȸ �Է°��� �Է��Ѵ�.

	//��ȸ��������
	m_dateTimeE1.GetWindowText(strINQ_STRT_DT);
	strINQ_STRT_DT.Remove('-');

	//��ȸ��������
	m_dateTimeE2.GetWindowText(strINQ_END_DT);
	strINQ_END_DT.Remove('-');

	//���Ĺ��
	strSORT_MTH = _T("0");

	//���´�ü��ȣ�� ���´�.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);

	//���»�ǰ��ȣ
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ

	//���º�й�ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);

	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "INQ_STRT_DT", strINQ_STRT_DT);		//��ȸ��������
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "INQ_END_DT", strINQ_END_DT);		//��ȸ��������
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "SORT_MTH", strSORT_MTH);		//���Ĺ��
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ

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
void CFxMarginOrdDlg::OnBnClickedBtnReqBalance()
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

	CString strTrCode = "OTS5919Q51";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName1 = "OTS5919Q51_in";	//�Է� ���ڵ��(���ҽ����� ����)
	CString strInRecName2 = "OTS5919Q51_in_sub01";	//�Է� ���ڵ��(���ҽ����� ����)

	CString strODRV_SELL_BUY_DCD;	//�ؿ��Ļ��ŵ��ż������ڵ�(0:��ü, B:�ż�, S:�ŵ�)
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
	/*	REC_NAME=OTS5919Q51_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
	ARRAY �� '0'���� ũ�� �Է��� �������̴�.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdBalanceList, strTrCode, strInRecName2, 1);

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
void CFxMarginOrdDlg::OnBnClickedBtnReqBalanceNext()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5919Q51";				//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName1 = "OTS5919Q51_in";	//�Է� ���ڵ��(���ҽ����� ����)
	CString strInRecName2 = "OTS5919Q51_in_sub01";	//�Է� ���ڵ��(���ҽ����� ����)

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
void CFxMarginOrdDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
		CString strFDM_UNQ_NO_PRDT_CD, strCANO, strCTNO, strODRV_ODNO, strFDM_UNQ_NO, strPRDT_CD,
			strODRV_OR_ODNO, strODRV_MO_ODNO, strORDR_GRUP_NO, strORDR_DT, strAPNO, strCUST_NM,
			strODRV_SELL_BUY_DCD, strODRV_ORDR_PRC, strORDR_QNT, strRVSE_QNT, strCNCL_QNT, strCNCS_QNT,
			strORDR_RMN_QNT, strCTRT_UN_AMT, strFX_ORDR_TOT_AMT, strFX_RMN_TOT_AMT, strPRC_CND_DCD, strCNCS_CND_DCD,
			strSQ1_STLS_YN, strSQ1_APMPR_YN, strSQ1_STLS_PRC, strSQ1_APPN_PRC, strSQ1_CHAS_STLS_PRC, strSQ2_STLS_YN,
			strSQ2_APMPR_YN, strSQ2_STLS_PRC, strSQ2_APPN_PRC, strSQ2_CHAS_STLS_PRC, strAVR_CNCS_PRC, strCNCS_RT,
			strODRV_NOW_PRC, strCOMM_MDIA_DCD, strODRV_ORDR_TP_DCD, strORDR_STTS_DCD, strFCM_ODNO, strUSR_ID,
			strATHZ_IP_ADDR, strEXCG_ACPT_TM, strEXCG_CNCS_TM, strORDR_TM, strCNCS_TM, strCRRY_CD,
			strPRC_DCPN_BLW_LNG, strTRDE_PRC_DFRN_CTNS;

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

		strOutRecName = "OTS5913Q53_out_sub01";

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, strOutRecName);
		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strFDM_UNQ_NO_PRDT_CD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FDM_UNQ_NO_PRDT_CD", nRow);		//�����Ͽ콺������ȣ��ǰ�ڵ�
			strCANO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
			strCTNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CTNO", nRow);		//���հ��´�ü��ȣ
			strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_ODNO", nRow);		//�ؿ��Ļ��ֹ���ȣ
			strFDM_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FDM_UNQ_NO", nRow);		//�����Ͽ콺������ȣ
			strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
			strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_OR_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
			strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_MO_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
			strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_GRUP_NO", nRow);		//�ֹ��׷��ȣ
			strORDR_DT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_DT", nRow);		//�ֹ�����
			strAPNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "APNO", nRow);		//���»�ǰ��ȣ
			strCUST_NM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CUST_NM", nRow);		//����
			strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//�ؿ��Ļ��ŵ��ż������ڵ�
			strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_ORDR_PRC", nRow);		//�ؿ��Ļ��ֹ�����
			strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
			strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "RVSE_QNT", nRow);		//��������
			strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCL_QNT", nRow);		//��Ҽ���
			strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_QNT", nRow);		//ü�����
			strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
			strCTRT_UN_AMT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CTRT_UN_AMT", nRow);		//�������ݾ�
			strFX_ORDR_TOT_AMT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FX_ORDR_TOT_AMT", nRow);		//FX�ֹ��ѱݾ�
			strFX_RMN_TOT_AMT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FX_RMN_TOT_AMT", nRow);		//FX�ܿ��ѱݾ�
			strPRC_CND_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "PRC_CND_DCD", nRow);		//�������Ǳ����ڵ�
			strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_CND_DCD", nRow);		//ü�����Ǳ����ڵ�
			strSQ1_STLS_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_STLS_YN", nRow);		//1����ž�ν�����
			strSQ1_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_APMPR_YN", nRow);		//1������������
			strSQ1_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_STLS_PRC", nRow);		//1����ž�ν�����
			strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_APPN_PRC", nRow);		//1����������
			strSQ1_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_CHAS_STLS_PRC", nRow);		//1�����������Ű���
			strSQ2_STLS_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_STLS_YN", nRow);		//2����ž�ν�����
			strSQ2_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_APMPR_YN", nRow);		//2������������
			strSQ2_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_STLS_PRC", nRow);		//2����ž�ν�����
			strSQ2_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_APPN_PRC", nRow);		//2����������
			strSQ2_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_CHAS_STLS_PRC", nRow);		//2�����������Ű���
			strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "AVR_CNCS_PRC", nRow);		//���ü�ᰡ��
			strCNCS_RT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_RT", nRow);		//ü����
			strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_NOW_PRC", nRow);		//�ؿ��Ļ����簡��
			strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "COMM_MDIA_DCD", nRow);		//��Ÿ�ü�����ڵ�
			strODRV_ORDR_TP_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_ORDR_TP_DCD", nRow);		//�ؿ��Ļ��ֹ����������ڵ�
			strORDR_STTS_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_STTS_DCD", nRow);		//�ֹ����±����ڵ�
			strFCM_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FCM_ODNO", nRow);		//FCM�ֹ���ȣ
			strUSR_ID = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "USR_ID", nRow);		//�����ID
			strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ATHZ_IP_ADDR", nRow);		//����IP�ּ�
			strEXCG_ACPT_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "EXCG_ACPT_TM", nRow);		//�ŷ��������ð�
			strEXCG_CNCS_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "EXCG_CNCS_TM", nRow);		//�ŷ���ü��ð�
			strORDR_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_TM", nRow);		//�ֹ��ð�
			strCNCS_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_TM", nRow);		//ü��ð�
			strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
			strPRC_DCPN_BLW_LNG = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "PRC_DCPN_BLW_LNG", nRow);		//���ݼҼ������ϱ���
			strTRDE_PRC_DFRN_CTNS = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "TRDE_PRC_DFRN_CTNS", nRow);		//�ŸŰ������̳���

			strFDM_UNQ_NO_PRDT_CD.Trim();		//�����Ͽ콺������ȣ��ǰ�ڵ�
			strCANO.Trim();		//���հ��¹�ȣ
			strCTNO.Trim();		//���հ��´�ü��ȣ
			strODRV_ODNO.Trim();		//�ؿ��Ļ��ֹ���ȣ
			strFDM_UNQ_NO.Trim();		//�����Ͽ콺������ȣ
			strPRDT_CD.Trim();		//��ǰ�ڵ�
			strODRV_OR_ODNO.Trim();		//�ؿ��Ļ����ֹ���ȣ
			strODRV_MO_ODNO.Trim();		//�ؿ��Ļ����ֹ���ȣ
			strORDR_GRUP_NO.Trim();		//�ֹ��׷��ȣ
			strORDR_DT.Trim();		//�ֹ�����
			strAPNO.Trim();		//���»�ǰ��ȣ
			strCUST_NM.Trim();		//����
			strODRV_SELL_BUY_DCD.Trim();		//�ؿ��Ļ��ŵ��ż������ڵ�
			NumericString(strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
			NumericString(strORDR_QNT);		//�ֹ�����
			NumericString(strRVSE_QNT);		//��������
			NumericString(strCNCL_QNT);		//��Ҽ���
			NumericString(strCNCS_QNT);		//ü�����
			NumericString(strORDR_RMN_QNT);		//�ֹ��ܿ�����
			NumericString(strCTRT_UN_AMT);		//�������ݾ�
			NumericString(strFX_ORDR_TOT_AMT);		//FX�ֹ��ѱݾ�
			NumericString(strFX_RMN_TOT_AMT);		//FX�ܿ��ѱݾ�
			strPRC_CND_DCD.Trim();		//�������Ǳ����ڵ�
			strCNCS_CND_DCD.Trim();		//ü�����Ǳ����ڵ�
			strSQ1_STLS_YN.Trim();		//1����ž�ν�����
			strSQ1_APMPR_YN.Trim();		//1������������
			NumericString(strSQ1_STLS_PRC);		//1����ž�ν�����
			NumericString(strSQ1_APPN_PRC);		//1����������
			NumericString(strSQ1_CHAS_STLS_PRC);		//1�����������Ű���
			strSQ2_STLS_YN.Trim();		//2����ž�ν�����
			strSQ2_APMPR_YN.Trim();		//2������������
			strSQ2_STLS_PRC.Trim();		//2����ž�ν�����
			strSQ2_APPN_PRC.Trim();		//2����������
			NumericString(strSQ2_CHAS_STLS_PRC);		//2�����������Ű���
			NumericString(strAVR_CNCS_PRC);		//���ü�ᰡ��
			NumericString(strCNCS_RT);		//ü����
			NumericString(strODRV_NOW_PRC);		//�ؿ��Ļ����簡��
			strCOMM_MDIA_DCD.Trim();		//��Ÿ�ü�����ڵ�
			strODRV_ORDR_TP_DCD.Trim();		//�ؿ��Ļ��ֹ����������ڵ�
			strORDR_STTS_DCD.Trim();		//�ֹ����±����ڵ�
			strFCM_ODNO.Trim();		//FCM�ֹ���ȣ
			strUSR_ID.Trim();		//�����ID
			strATHZ_IP_ADDR.Trim();		//����IP�ּ�
			strEXCG_ACPT_TM.Trim();		//�ŷ��������ð�
			strEXCG_CNCS_TM.Trim();		//�ŷ���ü��ð�
			strORDR_TM.Trim();		//�ֹ��ð�
			strCNCS_TM.Trim();		//ü��ð�
			strCRRY_CD.Trim();		//��ȭ�ڵ�
			strPRC_DCPN_BLW_LNG.Trim();		//���ݼҼ������ϱ���
			strTRDE_PRC_DFRN_CTNS.Trim();		//�ŸŰ������̳���

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listNonExec.InsertItem(&lvItem);

			m_listNonExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strFDM_UNQ_NO_PRDT_CD);		//�����Ͽ콺������ȣ��ǰ�ڵ�
			m_listNonExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strCANO);		//���հ��¹�ȣ
			m_listNonExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strCTNO);		//���հ��´�ü��ȣ
			m_listNonExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strODRV_ODNO);		//�ؿ��Ļ��ֹ���ȣ
			m_listNonExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strFDM_UNQ_NO);		//�����Ͽ콺������ȣ
			m_listNonExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strPRDT_CD);		//��ǰ�ڵ�
			m_listNonExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
			m_listNonExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strODRV_MO_ODNO);		//�ؿ��Ļ����ֹ���ȣ
			m_listNonExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strORDR_GRUP_NO);		//�ֹ��׷��ȣ
			m_listNonExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strORDR_DT);		//�ֹ�����
			m_listNonExec.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strAPNO);		//���»�ǰ��ȣ
			m_listNonExec.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strCUST_NM);		//����
			m_listNonExec.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strODRV_SELL_BUY_DCD);		//�ؿ��Ļ��ŵ��ż������ڵ�
			m_listNonExec.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
			m_listNonExec.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strORDR_QNT);		//�ֹ�����
			m_listNonExec.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strRVSE_QNT);		//��������
			m_listNonExec.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strCNCL_QNT);		//��Ҽ���
			m_listNonExec.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strCNCS_QNT);		//ü�����
			m_listNonExec.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strORDR_RMN_QNT);		//�ֹ��ܿ�����
			m_listNonExec.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strCTRT_UN_AMT);		//�������ݾ�
			m_listNonExec.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strFX_ORDR_TOT_AMT);		//FX�ֹ��ѱݾ�
			m_listNonExec.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strFX_RMN_TOT_AMT);		//FX�ܿ��ѱݾ�
			m_listNonExec.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strPRC_CND_DCD);		//�������Ǳ����ڵ�
			m_listNonExec.SetItemText(nListIndex, 23, (LPTSTR)(LPCTSTR)strCNCS_CND_DCD);		//ü�����Ǳ����ڵ�
			m_listNonExec.SetItemText(nListIndex, 24, (LPTSTR)(LPCTSTR)strSQ1_STLS_YN);		//1����ž�ν�����
			m_listNonExec.SetItemText(nListIndex, 25, (LPTSTR)(LPCTSTR)strSQ1_APMPR_YN);		//1������������
			m_listNonExec.SetItemText(nListIndex, 26, (LPTSTR)(LPCTSTR)strSQ1_STLS_PRC);		//1����ž�ν�����
			m_listNonExec.SetItemText(nListIndex, 27, (LPTSTR)(LPCTSTR)strSQ1_APPN_PRC);		//1����������
			m_listNonExec.SetItemText(nListIndex, 28, (LPTSTR)(LPCTSTR)strSQ1_CHAS_STLS_PRC);		//1�����������Ű���
			m_listNonExec.SetItemText(nListIndex, 29, (LPTSTR)(LPCTSTR)strSQ2_STLS_YN);		//2����ž�ν�����
			m_listNonExec.SetItemText(nListIndex, 30, (LPTSTR)(LPCTSTR)strSQ2_APMPR_YN);		//2������������
			m_listNonExec.SetItemText(nListIndex, 31, (LPTSTR)(LPCTSTR)strSQ2_STLS_PRC);		//2����ž�ν�����
			m_listNonExec.SetItemText(nListIndex, 32, (LPTSTR)(LPCTSTR)strSQ2_APPN_PRC);		//2����������
			m_listNonExec.SetItemText(nListIndex, 33, (LPTSTR)(LPCTSTR)strSQ2_CHAS_STLS_PRC);		//2�����������Ű���
			m_listNonExec.SetItemText(nListIndex, 34, (LPTSTR)(LPCTSTR)strAVR_CNCS_PRC);		//���ü�ᰡ��
			m_listNonExec.SetItemText(nListIndex, 35, (LPTSTR)(LPCTSTR)strCNCS_RT);		//ü����
			m_listNonExec.SetItemText(nListIndex, 36, (LPTSTR)(LPCTSTR)strODRV_NOW_PRC);		//�ؿ��Ļ����簡��
			m_listNonExec.SetItemText(nListIndex, 37, (LPTSTR)(LPCTSTR)strCOMM_MDIA_DCD);		//��Ÿ�ü�����ڵ�
			m_listNonExec.SetItemText(nListIndex, 38, (LPTSTR)(LPCTSTR)strODRV_ORDR_TP_DCD);		//�ؿ��Ļ��ֹ����������ڵ�
			m_listNonExec.SetItemText(nListIndex, 39, (LPTSTR)(LPCTSTR)strORDR_STTS_DCD);		//�ֹ����±����ڵ�
			m_listNonExec.SetItemText(nListIndex, 40, (LPTSTR)(LPCTSTR)strFCM_ODNO);		//FCM�ֹ���ȣ
			m_listNonExec.SetItemText(nListIndex, 41, (LPTSTR)(LPCTSTR)strUSR_ID);		//�����ID
			m_listNonExec.SetItemText(nListIndex, 42, (LPTSTR)(LPCTSTR)strATHZ_IP_ADDR);		//����IP�ּ�
			m_listNonExec.SetItemText(nListIndex, 43, (LPTSTR)(LPCTSTR)strEXCG_ACPT_TM);		//�ŷ��������ð�
			m_listNonExec.SetItemText(nListIndex, 44, (LPTSTR)(LPCTSTR)strEXCG_CNCS_TM);		//�ŷ���ü��ð�
			m_listNonExec.SetItemText(nListIndex, 45, (LPTSTR)(LPCTSTR)strORDR_TM);		//�ֹ��ð�
			m_listNonExec.SetItemText(nListIndex, 46, (LPTSTR)(LPCTSTR)strCNCS_TM);		//ü��ð�
			m_listNonExec.SetItemText(nListIndex, 47, (LPTSTR)(LPCTSTR)strCRRY_CD);		//��ȭ�ڵ�
			m_listNonExec.SetItemText(nListIndex, 48, (LPTSTR)(LPCTSTR)strPRC_DCPN_BLW_LNG);		//���ݼҼ������ϱ���
			m_listNonExec.SetItemText(nListIndex, 49, (LPTSTR)(LPCTSTR)strTRDE_PRC_DFRN_CTNS);		//�ŸŰ������̳���

			nListIndex++;

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
		CString strFDM_UNQ_NO_PRDT_CD, strCANO, strCTNO, strODRV_ODNO, strFDM_UNQ_NO, strPRDT_CD,
			strODRV_OR_ODNO, strODRV_MO_ODNO, strORDR_GRUP_NO, strORDR_DT, strAPNO, strCUST_NM,
			strODRV_SELL_BUY_DCD, strODRV_ORDR_PRC, strORDR_QNT, strRVSE_QNT, strCNCL_QNT, strCNCS_QNT,
			strORDR_RMN_QNT, strCTRT_UN_AMT, strFX_ORDR_TOT_AMT, strFX_RMN_TOT_AMT, strPRC_CND_DCD, strCNCS_CND_DCD,
			strSQ1_STLS_YN, strSQ1_APMPR_YN, strSQ1_STLS_PRC, strSQ1_APPN_PRC, strSQ1_CHAS_STLS_PRC, strSQ2_STLS_YN,
			strSQ2_APMPR_YN, strSQ2_STLS_PRC, strSQ2_APPN_PRC, strSQ2_CHAS_STLS_PRC, strAVR_CNCS_PRC, strCNCS_RT,
			strODRV_NOW_PRC, strCOMM_MDIA_DCD, strODRV_ORDR_TP_DCD, strORDR_STTS_DCD, strFCM_ODNO, strUSR_ID,
			strATHZ_IP_ADDR, strEXCG_ACPT_TM, strEXCG_CNCS_TM, strORDR_TM, strCNCS_TM, strCRRY_CD,
			strPRC_DCPN_BLW_LNG, strTRDE_PRC_DFRN_CTNS;

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

		strOutRecName = "OTS5913Q52_out_sub01";

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, strOutRecName);
		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strFDM_UNQ_NO_PRDT_CD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "FDM_UNQ_NO_PRDT_CD", nRow);		//�����Ͽ콺������ȣ��ǰ�ڵ�
			strCANO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
			strCTNO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CTNO", nRow);		//���հ��´�ü��ȣ
			strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_ODNO", nRow);		//�ؿ��Ļ��ֹ���ȣ
			strFDM_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "FDM_UNQ_NO", nRow);		//�����Ͽ콺������ȣ
			strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
			strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_OR_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
			strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_MO_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
			strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ORDR_GRUP_NO", nRow);		//�ֹ��׷��ȣ
			strORDR_DT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ORDR_DT", nRow);		//�ֹ�����
			strAPNO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "APNO", nRow);		//���»�ǰ��ȣ
			strCUST_NM = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CUST_NM", nRow);		//����
			strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//�ؿ��Ļ��ŵ��ż������ڵ�
			strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_ORDR_PRC", nRow);		//�ؿ��Ļ��ֹ�����
			strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
			strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "RVSE_QNT", nRow);		//��������
			strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CNCL_QNT", nRow);		//��Ҽ���
			strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CNCS_QNT", nRow);		//ü�����
			strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
			strCTRT_UN_AMT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CTRT_UN_AMT", nRow);		//�������ݾ�
			strFX_ORDR_TOT_AMT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "FX_ORDR_TOT_AMT", nRow);		//FX�ֹ��ѱݾ�
			strFX_RMN_TOT_AMT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "FX_RMN_TOT_AMT", nRow);		//FX�ܿ��ѱݾ�
			strPRC_CND_DCD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "PRC_CND_DCD", nRow);		//�������Ǳ����ڵ�
			strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CNCS_CND_DCD", nRow);		//ü�����Ǳ����ڵ�
			strSQ1_STLS_YN = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ1_STLS_YN", nRow);		//1����ž�ν�����
			strSQ1_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ1_APMPR_YN", nRow);		//1������������
			strSQ1_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ1_STLS_PRC", nRow);		//1����ž�ν�����
			strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ1_APPN_PRC", nRow);		//1����������
			strSQ1_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ1_CHAS_STLS_PRC", nRow);		//1�����������Ű���
			strSQ2_STLS_YN = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ2_STLS_YN", nRow);		//2����ž�ν�����
			strSQ2_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ2_APMPR_YN", nRow);		//2������������
			strSQ2_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ2_STLS_PRC", nRow);		//2����ž�ν�����
			strSQ2_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ2_APPN_PRC", nRow);		//2����������
			strSQ2_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ2_CHAS_STLS_PRC", nRow);		//2�����������Ű���
			strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "AVR_CNCS_PRC", nRow);		//���ü�ᰡ��
			strCNCS_RT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CNCS_RT", nRow);		//ü����
			strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_NOW_PRC", nRow);		//�ؿ��Ļ����簡��
			strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "COMM_MDIA_DCD", nRow);		//��Ÿ�ü�����ڵ�
			strODRV_ORDR_TP_DCD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_ORDR_TP_DCD", nRow);		//�ؿ��Ļ��ֹ����������ڵ�
			strORDR_STTS_DCD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ORDR_STTS_DCD", nRow);		//�ֹ����±����ڵ�
			strFCM_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "FCM_ODNO", nRow);		//FCM�ֹ���ȣ
			strUSR_ID = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "USR_ID", nRow);		//�����ID
			strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ATHZ_IP_ADDR", nRow);		//����IP�ּ�
			strEXCG_ACPT_TM = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "EXCG_ACPT_TM", nRow);		//�ŷ��������ð�
			strEXCG_CNCS_TM = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "EXCG_CNCS_TM", nRow);		//�ŷ���ü��ð�
			strORDR_TM = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ORDR_TM", nRow);		//�ֹ��ð�
			strCNCS_TM = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CNCS_TM", nRow);		//ü��ð�
			strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
			strPRC_DCPN_BLW_LNG = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "PRC_DCPN_BLW_LNG", nRow);		//���ݼҼ������ϱ���
			strTRDE_PRC_DFRN_CTNS = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "TRDE_PRC_DFRN_CTNS", nRow);		//�ŸŰ������̳���

			strFDM_UNQ_NO_PRDT_CD.Trim();		//�����Ͽ콺������ȣ��ǰ�ڵ�
			strCANO.Trim();		//���հ��¹�ȣ
			strCTNO.Trim();		//���հ��´�ü��ȣ
			strODRV_ODNO.Trim();		//�ؿ��Ļ��ֹ���ȣ
			strFDM_UNQ_NO.Trim();		//�����Ͽ콺������ȣ
			strPRDT_CD.Trim();		//��ǰ�ڵ�
			strODRV_OR_ODNO.Trim();		//�ؿ��Ļ����ֹ���ȣ
			strODRV_MO_ODNO.Trim();		//�ؿ��Ļ����ֹ���ȣ
			strORDR_GRUP_NO.Trim();		//�ֹ��׷��ȣ
			strORDR_DT.Trim();		//�ֹ�����
			strAPNO.Trim();		//���»�ǰ��ȣ
			strCUST_NM.Trim();		//����
			strODRV_SELL_BUY_DCD.Trim();		//�ؿ��Ļ��ŵ��ż������ڵ�
			NumericString(strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
			NumericString(strORDR_QNT);		//�ֹ�����
			NumericString(strRVSE_QNT);		//��������
			NumericString(strCNCL_QNT);		//��Ҽ���
			NumericString(strCNCS_QNT);		//ü�����
			NumericString(strORDR_RMN_QNT);		//�ֹ��ܿ�����
			NumericString(strCTRT_UN_AMT);		//�������ݾ�
			NumericString(strFX_ORDR_TOT_AMT);		//FX�ֹ��ѱݾ�
			NumericString(strFX_RMN_TOT_AMT);		//FX�ܿ��ѱݾ�
			strPRC_CND_DCD.Trim();		//�������Ǳ����ڵ�
			strCNCS_CND_DCD.Trim();		//ü�����Ǳ����ڵ�
			strSQ1_STLS_YN.Trim();		//1����ž�ν�����
			strSQ1_APMPR_YN.Trim();		//1������������
			NumericString(strSQ1_STLS_PRC);		//1����ž�ν�����
			NumericString(strSQ1_APPN_PRC);		//1����������
			NumericString(strSQ1_CHAS_STLS_PRC);		//1�����������Ű���
			strSQ2_STLS_YN.Trim();		//2����ž�ν�����
			strSQ2_APMPR_YN.Trim();		//2������������
			strSQ2_STLS_PRC.Trim();		//2����ž�ν�����
			strSQ2_APPN_PRC.Trim();		//2����������
			NumericString(strSQ2_CHAS_STLS_PRC);		//2�����������Ű���
			NumericString(strAVR_CNCS_PRC);		//���ü�ᰡ��
			NumericString(strCNCS_RT);		//ü����
			NumericString(strODRV_NOW_PRC);		//�ؿ��Ļ����簡��
			strCOMM_MDIA_DCD.Trim();		//��Ÿ�ü�����ڵ�
			strODRV_ORDR_TP_DCD.Trim();		//�ؿ��Ļ��ֹ����������ڵ�
			strORDR_STTS_DCD.Trim();		//�ֹ����±����ڵ�
			strFCM_ODNO.Trim();		//FCM�ֹ���ȣ
			strUSR_ID.Trim();		//�����ID
			strATHZ_IP_ADDR.Trim();		//����IP�ּ�
			strEXCG_ACPT_TM.Trim();		//�ŷ��������ð�
			strEXCG_CNCS_TM.Trim();		//�ŷ���ü��ð�
			strORDR_TM.Trim();		//�ֹ��ð�
			strCNCS_TM.Trim();		//ü��ð�
			strCRRY_CD.Trim();		//��ȭ�ڵ�
			strPRC_DCPN_BLW_LNG.Trim();		//���ݼҼ������ϱ���
			strTRDE_PRC_DFRN_CTNS.Trim();		//�ŸŰ������̳���

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listExec.InsertItem(&lvItem);

			m_listExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strFDM_UNQ_NO_PRDT_CD);		//�����Ͽ콺������ȣ��ǰ�ڵ�
			m_listExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strCANO);		//���հ��¹�ȣ
			m_listExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strCTNO);		//���հ��´�ü��ȣ
			m_listExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strODRV_ODNO);		//�ؿ��Ļ��ֹ���ȣ
			m_listExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strFDM_UNQ_NO);		//�����Ͽ콺������ȣ
			m_listExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strPRDT_CD);		//��ǰ�ڵ�
			m_listExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
			m_listExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strODRV_MO_ODNO);		//�ؿ��Ļ����ֹ���ȣ
			m_listExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strORDR_GRUP_NO);		//�ֹ��׷��ȣ
			m_listExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strORDR_DT);		//�ֹ�����
			m_listExec.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strAPNO);		//���»�ǰ��ȣ
			m_listExec.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strCUST_NM);		//����
			m_listExec.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strODRV_SELL_BUY_DCD);		//�ؿ��Ļ��ŵ��ż������ڵ�
			m_listExec.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
			m_listExec.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strORDR_QNT);		//�ֹ�����
			m_listExec.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strRVSE_QNT);		//��������
			m_listExec.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strCNCL_QNT);		//��Ҽ���
			m_listExec.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strCNCS_QNT);		//ü�����
			m_listExec.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strORDR_RMN_QNT);		//�ֹ��ܿ�����
			m_listExec.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strCTRT_UN_AMT);		//�������ݾ�
			m_listExec.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strFX_ORDR_TOT_AMT);		//FX�ֹ��ѱݾ�
			m_listExec.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strFX_RMN_TOT_AMT);		//FX�ܿ��ѱݾ�
			m_listExec.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strPRC_CND_DCD);		//�������Ǳ����ڵ�
			m_listExec.SetItemText(nListIndex, 23, (LPTSTR)(LPCTSTR)strCNCS_CND_DCD);		//ü�����Ǳ����ڵ�
			m_listExec.SetItemText(nListIndex, 24, (LPTSTR)(LPCTSTR)strSQ1_STLS_YN);		//1����ž�ν�����
			m_listExec.SetItemText(nListIndex, 25, (LPTSTR)(LPCTSTR)strSQ1_APMPR_YN);		//1������������
			m_listExec.SetItemText(nListIndex, 26, (LPTSTR)(LPCTSTR)strSQ1_STLS_PRC);		//1����ž�ν�����
			m_listExec.SetItemText(nListIndex, 27, (LPTSTR)(LPCTSTR)strSQ1_APPN_PRC);		//1����������
			m_listExec.SetItemText(nListIndex, 28, (LPTSTR)(LPCTSTR)strSQ1_CHAS_STLS_PRC);		//1�����������Ű���
			m_listExec.SetItemText(nListIndex, 29, (LPTSTR)(LPCTSTR)strSQ2_STLS_YN);		//2����ž�ν�����
			m_listExec.SetItemText(nListIndex, 30, (LPTSTR)(LPCTSTR)strSQ2_APMPR_YN);		//2������������
			m_listExec.SetItemText(nListIndex, 31, (LPTSTR)(LPCTSTR)strSQ2_STLS_PRC);		//2����ž�ν�����
			m_listExec.SetItemText(nListIndex, 32, (LPTSTR)(LPCTSTR)strSQ2_APPN_PRC);		//2����������
			m_listExec.SetItemText(nListIndex, 33, (LPTSTR)(LPCTSTR)strSQ2_CHAS_STLS_PRC);		//2�����������Ű���
			m_listExec.SetItemText(nListIndex, 34, (LPTSTR)(LPCTSTR)strAVR_CNCS_PRC);		//���ü�ᰡ��
			m_listExec.SetItemText(nListIndex, 35, (LPTSTR)(LPCTSTR)strCNCS_RT);		//ü����
			m_listExec.SetItemText(nListIndex, 36, (LPTSTR)(LPCTSTR)strODRV_NOW_PRC);		//�ؿ��Ļ����簡��
			m_listExec.SetItemText(nListIndex, 37, (LPTSTR)(LPCTSTR)strCOMM_MDIA_DCD);		//��Ÿ�ü�����ڵ�
			m_listExec.SetItemText(nListIndex, 38, (LPTSTR)(LPCTSTR)strODRV_ORDR_TP_DCD);		//�ؿ��Ļ��ֹ����������ڵ�
			m_listExec.SetItemText(nListIndex, 39, (LPTSTR)(LPCTSTR)strORDR_STTS_DCD);		//�ֹ����±����ڵ�
			m_listExec.SetItemText(nListIndex, 40, (LPTSTR)(LPCTSTR)strFCM_ODNO);		//FCM�ֹ���ȣ
			m_listExec.SetItemText(nListIndex, 41, (LPTSTR)(LPCTSTR)strUSR_ID);		//�����ID
			m_listExec.SetItemText(nListIndex, 42, (LPTSTR)(LPCTSTR)strATHZ_IP_ADDR);		//����IP�ּ�
			m_listExec.SetItemText(nListIndex, 43, (LPTSTR)(LPCTSTR)strEXCG_ACPT_TM);		//�ŷ��������ð�
			m_listExec.SetItemText(nListIndex, 44, (LPTSTR)(LPCTSTR)strEXCG_CNCS_TM);		//�ŷ���ü��ð�
			m_listExec.SetItemText(nListIndex, 45, (LPTSTR)(LPCTSTR)strORDR_TM);		//�ֹ��ð�
			m_listExec.SetItemText(nListIndex, 46, (LPTSTR)(LPCTSTR)strCNCS_TM);		//ü��ð�
			m_listExec.SetItemText(nListIndex, 47, (LPTSTR)(LPCTSTR)strCRRY_CD);		//��ȭ�ڵ�
			m_listExec.SetItemText(nListIndex, 48, (LPTSTR)(LPCTSTR)strPRC_DCPN_BLW_LNG);		//���ݼҼ������ϱ���
			m_listExec.SetItemText(nListIndex, 49, (LPTSTR)(LPCTSTR)strTRDE_PRC_DFRN_CTNS);		//�ŸŰ������̳���
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
		m_nRqIdFDemoAccNoList = 0;	//������¸���Ʈ
	}
	//������ ��ȸ
	else if (m_nRqIdDepositList == nRequestId)
	{
		CString strCRRY_CD, strBFDT_CSH_BLCE_CTNS, strODRV_IPP_AMT_CTNS, strFX_FEE_CTNS, strROVR_INTR_CTNS,
			strTHDT_DPSA_CTNS, strODRV_CLR_AMT_CTNS, strUSTL_EVL_PFLS_AMT_CTNS, strODRV_EVL_DPST_TOT_AMT_CTNS,
			strODRV_CSGN_WMY_CTNS, strODRV_ADIT_WMY_CTNS, strODRV_RCVB_AMT_CTNS, strODRV_ORDR_PSBL_AMT_CTNS,
			strODRV_WDRW_PSBL_AMT_CTNS, strODRV_MNTN_WMY_CTNS, strRSK_RT_CTNS;

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

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OTS5914Q51_out_sub01");

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
			strBFDT_CSH_BLCE_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "BFDT_CSH_BLCE_CTNS", nRow);		//���������ܾ׳���
			strODRV_IPP_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_IPP_AMT_CTNS", nRow);		//�ؿ��Ļ�����ݾ׳���
			strFX_FEE_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "FX_FEE_CTNS", nRow);		//FX�����᳻��
			strROVR_INTR_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ROVR_INTR_CTNS", nRow);		//�ѿ������ڳ���
			strTHDT_DPSA_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "THDT_DPSA_CTNS", nRow);		//���Ͽ�Ź�ݳ���
			strODRV_CLR_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_CLR_AMT_CTNS", nRow);		//�ؿ��Ļ�û��ݾ׳���
			strUSTL_EVL_PFLS_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "USTL_EVL_PFLS_AMT_CTNS", nRow);		//�̰����򰡼��ͱݾ׳���
			strODRV_EVL_DPST_TOT_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_EVL_DPST_TOT_AMT_CTNS", nRow);		//�ؿ��Ļ��򰡿�Ź�ѱݾ׳���
			strODRV_CSGN_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_CSGN_WMY_CTNS", nRow);		//�ؿ��Ļ���Ź���űݳ���
			strODRV_ADIT_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_ADIT_WMY_CTNS", nRow);		//�ؿ��Ļ��߰����űݳ���
			strODRV_RCVB_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_RCVB_AMT_CTNS", nRow);		//�ؿ��Ļ��̼��ݾ׳���
			strODRV_ORDR_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_ORDR_PSBL_AMT_CTNS", nRow);		//�ؿ��Ļ��ֹ����ɱݾ׳���
			strODRV_WDRW_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_WDRW_PSBL_AMT_CTNS", nRow);		//�ؿ��Ļ����Ⱑ�ɱݾ׳���
			strODRV_MNTN_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_MNTN_WMY_CTNS", nRow);		//�ؿ��Ļ��������űݳ���
			strRSK_RT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "RSK_RT_CTNS", nRow);		//����������

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listDeposit.InsertItem(&lvItem);

			strCRRY_CD.Trim();
			NumericString(strBFDT_CSH_BLCE_CTNS);
			NumericString(strODRV_IPP_AMT_CTNS);
			NumericString(strFX_FEE_CTNS);
			NumericString(strROVR_INTR_CTNS);
			NumericString(strTHDT_DPSA_CTNS);
			NumericString(strODRV_CLR_AMT_CTNS);
			NumericString(strUSTL_EVL_PFLS_AMT_CTNS);
			NumericString(strODRV_EVL_DPST_TOT_AMT_CTNS);
			NumericString(strODRV_CSGN_WMY_CTNS);
			NumericString(strODRV_ADIT_WMY_CTNS);
			NumericString(strODRV_RCVB_AMT_CTNS);
			NumericString(strODRV_ORDR_PSBL_AMT_CTNS);
			NumericString(strODRV_WDRW_PSBL_AMT_CTNS);
			NumericString(strODRV_MNTN_WMY_CTNS);
			NumericString(strRSK_RT_CTNS);

			m_listDeposit.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strCRRY_CD);
			m_listDeposit.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strBFDT_CSH_BLCE_CTNS);
			m_listDeposit.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strODRV_IPP_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strFX_FEE_CTNS);
			m_listDeposit.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strROVR_INTR_CTNS);
			m_listDeposit.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strTHDT_DPSA_CTNS);
			m_listDeposit.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strODRV_CLR_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strUSTL_EVL_PFLS_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strODRV_EVL_DPST_TOT_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strODRV_CSGN_WMY_CTNS);
			m_listDeposit.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strODRV_ADIT_WMY_CTNS);
			m_listDeposit.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strODRV_RCVB_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strODRV_ORDR_PSBL_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strODRV_WDRW_PSBL_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strODRV_MNTN_WMY_CTNS);
			m_listDeposit.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strRSK_RT_CTNS);

			nListIndex++;
		}//End of for

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
		CString strPST_NO, strCTNO, strCANO, strAPNO, strCNCS_DT, strMNGM_BDCD, strODRV_CSGN_SLF_DCD, strFDM_UNQ_NO, strPRDT_CD,
			strNMPR_UNQ_NO, strODRV_SELL_BUY_DCD, strODRV_CNCS_PRC, strFRS_CNCS_QNT, strCLR_QNT, strCNCS_CNCL_TR_QNT,
			strUSTL_CTRC_QNT, strUSTL_CTRC_AMT2, strUSTL_CTRC_AMT3, strCNCS_PIP_VALU_AMT, strODRV_CTRC_AMT,
			strUSTL_CTRC_AMT, strCRSS_EXRT, strODRV_EXCAL_PRC, strODRV_EVL_PFLS_AMT, strPIP_VALU_AMT, strTRSL_EVL_PFLS_AMT,
			strEXCAL_CRSS_EXRT, strONL_TR_YN, strODRV_CNCS_NO, strHOLD_PST_YN, strUSE_YN, strODRV_ODNO, strODRV_OR_ODNO,
			strODRV_MO_ODNO, strORDR_GRUP_NO, strORDR_DT, strCUST_NM, strODRV_ORDR_PRC, strMKT_PRC_APLY_STUP_AMT,
			strORDR_QNT, strRVSE_QNT, strCNCL_QNT, strCNCS_QNT, strORDR_RMN_QNT, strPRC_CND_DCD, strCNCS_CND_DCD,
			strSQ1_STLS_YN, strSQ1_APMPR_YN, strSQ1_DVSN_YN, strSQ1_STLS_PRC, strSQ1_APPN_PRC, strSQ1_CHAS_STLS_PRC,
			strCTRT_UN_AMT, strORDR_DRCN_DCD, strAVR_CNCS_PRC, strODRV_NOW_PRC, strPRDT_CD2;

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

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OTS5919Q51_out_sub01");

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strPST_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PST_NO", nRow);		//�����ǹ�ȣ
			strCTNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CTNO", nRow);		//���հ��´�ü��ȣ
			strCANO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
			strAPNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "APNO", nRow);		//���»�ǰ��ȣ
			strCNCS_DT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_DT", nRow);		//ü������
			strMNGM_BDCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "MNGM_BDCD", nRow);		//���������ڵ�
			strODRV_CSGN_SLF_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CSGN_SLF_DCD", nRow);		//�ؿ��Ļ���Ź�ڱⱸ���ڵ�
			strFDM_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "FDM_UNQ_NO", nRow);		//�����Ͽ콺������ȣ
			strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
			strNMPR_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "NMPR_UNQ_NO", nRow);		//ȣ��������ȣ
			strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//�ؿ��Ļ��ŵ��ż������ڵ�
			strODRV_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CNCS_PRC", nRow);		//�ؿ��Ļ�ü�ᰡ��
			strFRS_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "FRS_CNCS_QNT", nRow);		//����ü�����
			strCLR_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CLR_QNT", nRow);		//û�����
			strCNCS_CNCL_TR_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_CNCL_TR_QNT", nRow);		//ü����Ұŷ�����
			strUSTL_CTRC_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_QNT", nRow);		//�̰�����������
			strUSTL_CTRC_AMT2 = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_AMT2", nRow);		//�̰��������ݾ�2
			strUSTL_CTRC_AMT3 = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_AMT3", nRow);		//�̰��������ݾ�3
			strCNCS_PIP_VALU_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_PIP_VALU_AMT", nRow);		//ü��PIP��ġ�ݾ�
			strODRV_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CTRC_AMT", nRow);		//�ؿ��Ļ������ݾ�
			strUSTL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_AMT", nRow);		//�̰��������ݾ�
			strCRSS_EXRT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CRSS_EXRT", nRow);		//����ȯ��
			strODRV_EXCAL_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_EXCAL_PRC", nRow);		//�ؿ��Ļ����갡��
			strODRV_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_EVL_PFLS_AMT", nRow);		//�ؿ��Ļ��򰡼��ͱݾ�
			strPIP_VALU_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PIP_VALU_AMT", nRow);		//PIP��ġ�ݾ�
			strTRSL_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "TRSL_EVL_PFLS_AMT", nRow);		//ȯ���򰡼��ͱݾ�
			strEXCAL_CRSS_EXRT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "EXCAL_CRSS_EXRT", nRow);		//���걳��ȯ��
			strONL_TR_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ONL_TR_YN", nRow);		//�¶��ΰŷ�����
			strODRV_CNCS_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CNCS_NO", nRow);		//�ؿ��Ļ�ü���ȣ
			strHOLD_PST_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "HOLD_PST_YN", nRow);		//���������ǿ���
			strUSE_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USE_YN", nRow);		//��뿩��
			strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_ODNO", nRow);		//�ؿ��Ļ��ֹ���ȣ
			strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_OR_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
			strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_MO_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
			strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_GRUP_NO", nRow);		//�ֹ��׷��ȣ
			strORDR_DT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_DT", nRow);		//�ֹ�����
			strCUST_NM = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CUST_NM", nRow);		//����
			strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_ORDR_PRC", nRow);		//�ؿ��Ļ��ֹ�����
			strMKT_PRC_APLY_STUP_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "MKT_PRC_APLY_STUP_AMT", nRow);		//���尡�����뼳���ݾ�
			strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
			strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "RVSE_QNT", nRow);		//��������
			strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCL_QNT", nRow);		//��Ҽ���
			strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_QNT", nRow);		//ü�����
			strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
			strPRC_CND_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PRC_CND_DCD", nRow);		//�������Ǳ����ڵ�
			strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_CND_DCD", nRow);		//ü�����Ǳ����ڵ�
			strSQ1_STLS_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_STLS_YN", nRow);		//1����ž�ν�����
			strSQ1_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_APMPR_YN", nRow);		//1������������
			strSQ1_DVSN_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_DVSN_YN", nRow);		//1�����п���
			strSQ1_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_STLS_PRC", nRow);		//1����ž�ν�����
			strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_APPN_PRC", nRow);		//1����������
			strSQ1_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_CHAS_STLS_PRC", nRow);		//1�����������Ű���
			strCTRT_UN_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CTRT_UN_AMT", nRow);		//�������ݾ�
			strORDR_DRCN_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_DRCN_DCD", nRow);		//�ֹ����ⱸ���ڵ�
			strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "AVR_CNCS_PRC", nRow);		//���ü�ᰡ��
			strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_NOW_PRC", nRow);		//�ؿ��Ļ����簡��
			strPRDT_CD2 = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PRDT_CD2", nRow);		//��ǰ�ڵ�2

			strPST_NO.Trim();		//�����ǹ�ȣ
			strCTNO.Trim();		//���հ��´�ü��ȣ
			strCANO.Trim();		//���հ��¹�ȣ
			strAPNO.Trim();		//���»�ǰ��ȣ
			strCNCS_DT.Trim();		//ü������
			strMNGM_BDCD.Trim();		//���������ڵ�
			strODRV_CSGN_SLF_DCD.Trim();		//�ؿ��Ļ���Ź�ڱⱸ���ڵ�
			strFDM_UNQ_NO.Trim();		//�����Ͽ콺������ȣ
			strPRDT_CD.Trim();		//��ǰ�ڵ�
			strNMPR_UNQ_NO.Trim();		//ȣ��������ȣ
			strODRV_SELL_BUY_DCD.Trim();		//�ؿ��Ļ��ŵ��ż������ڵ�
			NumericString(strODRV_CNCS_PRC);		//�ؿ��Ļ�ü�ᰡ��
			NumericString(strFRS_CNCS_QNT);		//����ü�����
			NumericString(strCLR_QNT);		//û�����
			NumericString(strCNCS_CNCL_TR_QNT);		//ü����Ұŷ�����
			NumericString(strUSTL_CTRC_QNT);		//�̰�����������
			NumericString(strUSTL_CTRC_AMT2);		//�̰��������ݾ�2
			NumericString(strUSTL_CTRC_AMT3);		//�̰��������ݾ�3
			NumericString(strCNCS_PIP_VALU_AMT);		//ü��PIP��ġ�ݾ�
			NumericString(strODRV_CTRC_AMT);		//�ؿ��Ļ������ݾ�
			NumericString(strUSTL_CTRC_AMT);		//�̰��������ݾ�
			NumericString(strCRSS_EXRT);		//����ȯ��
			NumericString(strODRV_EXCAL_PRC);		//�ؿ��Ļ����갡��
			NumericString(strODRV_EVL_PFLS_AMT);		//�ؿ��Ļ��򰡼��ͱݾ�
			NumericString(strPIP_VALU_AMT);		//PIP��ġ�ݾ�
			NumericString(strTRSL_EVL_PFLS_AMT);		//ȯ���򰡼��ͱݾ�
			NumericString(strEXCAL_CRSS_EXRT);		//���걳��ȯ��
			strONL_TR_YN.Trim();		//�¶��ΰŷ�����
			strODRV_CNCS_NO.Trim();		//�ؿ��Ļ�ü���ȣ
			strHOLD_PST_YN.Trim();		//���������ǿ���
			strUSE_YN.Trim();		//��뿩��
			strODRV_ODNO.Trim();		//�ؿ��Ļ��ֹ���ȣ
			strODRV_OR_ODNO.Trim();		//�ؿ��Ļ����ֹ���ȣ
			strODRV_MO_ODNO.Trim();		//�ؿ��Ļ����ֹ���ȣ
			strORDR_GRUP_NO.Trim();		//�ֹ��׷��ȣ
			strORDR_DT.Trim();		//�ֹ�����
			strCUST_NM.Trim();		//����
			NumericString(strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
			NumericString(strMKT_PRC_APLY_STUP_AMT);		//���尡�����뼳���ݾ�
			NumericString(strORDR_QNT);		//�ֹ�����
			NumericString(strRVSE_QNT);		//��������
			NumericString(strCNCL_QNT);		//��Ҽ���
			NumericString(strCNCS_QNT);		//ü�����
			NumericString(strORDR_RMN_QNT);		//�ֹ��ܿ�����
			strPRC_CND_DCD.Trim();		//�������Ǳ����ڵ�
			strCNCS_CND_DCD.Trim();		//ü�����Ǳ����ڵ�
			strSQ1_STLS_YN.Trim();		//1����ž�ν�����
			strSQ1_APMPR_YN.Trim();		//1������������
			strSQ1_DVSN_YN.Trim();		//1�����п���
			NumericString(strSQ1_STLS_PRC);		//1����ž�ν�����
			NumericString(strSQ1_APPN_PRC);		//1����������
			NumericString(strSQ1_CHAS_STLS_PRC);		//1�����������Ű���
			NumericString(strCTRT_UN_AMT);		//�������ݾ�
			strORDR_DRCN_DCD.Trim();		//�ֹ����ⱸ���ڵ�
			NumericString(strAVR_CNCS_PRC);		//���ü�ᰡ��
			NumericString(strODRV_NOW_PRC);		//�ؿ��Ļ����簡��
			strPRDT_CD2.Trim();		//��ǰ�ڵ�2

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listBalance.InsertItem(&lvItem);

			m_listBalance.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strPST_NO);		//�����ǹ�ȣ
			m_listBalance.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strCTNO);		//���հ��´�ü��ȣ
			m_listBalance.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strCANO);		//���հ��¹�ȣ
			m_listBalance.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strAPNO);		//���»�ǰ��ȣ
			m_listBalance.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strCNCS_DT);		//ü������
			m_listBalance.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strMNGM_BDCD);		//���������ڵ�
			m_listBalance.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strODRV_CSGN_SLF_DCD);		//�ؿ��Ļ���Ź�ڱⱸ���ڵ�
			m_listBalance.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strFDM_UNQ_NO);		//�����Ͽ콺������ȣ
			m_listBalance.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strPRDT_CD);		//��ǰ�ڵ�
			m_listBalance.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strNMPR_UNQ_NO);		//ȣ��������ȣ
			m_listBalance.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strODRV_SELL_BUY_DCD);		//�ؿ��Ļ��ŵ��ż������ڵ�
			m_listBalance.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strODRV_CNCS_PRC);		//�ؿ��Ļ�ü�ᰡ��
			m_listBalance.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strFRS_CNCS_QNT);		//����ü�����
			m_listBalance.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strCLR_QNT);		//û�����
			m_listBalance.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strCNCS_CNCL_TR_QNT);		//ü����Ұŷ�����
			m_listBalance.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strUSTL_CTRC_QNT);		//�̰�����������
			m_listBalance.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strUSTL_CTRC_AMT2);		//�̰��������ݾ�2
			m_listBalance.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strUSTL_CTRC_AMT3);		//�̰��������ݾ�3
			m_listBalance.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strCNCS_PIP_VALU_AMT);		//ü��PIP��ġ�ݾ�
			m_listBalance.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strODRV_CTRC_AMT);		//�ؿ��Ļ������ݾ�
			m_listBalance.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strUSTL_CTRC_AMT);		//�̰��������ݾ�
			m_listBalance.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strCRSS_EXRT);		//����ȯ��
			m_listBalance.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strODRV_EXCAL_PRC);		//�ؿ��Ļ����갡��
			m_listBalance.SetItemText(nListIndex, 23, (LPTSTR)(LPCTSTR)strODRV_EVL_PFLS_AMT);		//�ؿ��Ļ��򰡼��ͱݾ�
			m_listBalance.SetItemText(nListIndex, 24, (LPTSTR)(LPCTSTR)strPIP_VALU_AMT);		//PIP��ġ�ݾ�
			m_listBalance.SetItemText(nListIndex, 25, (LPTSTR)(LPCTSTR)strTRSL_EVL_PFLS_AMT);		//ȯ���򰡼��ͱݾ�
			m_listBalance.SetItemText(nListIndex, 26, (LPTSTR)(LPCTSTR)strEXCAL_CRSS_EXRT);		//���걳��ȯ��
			m_listBalance.SetItemText(nListIndex, 27, (LPTSTR)(LPCTSTR)strONL_TR_YN);		//�¶��ΰŷ�����
			m_listBalance.SetItemText(nListIndex, 28, (LPTSTR)(LPCTSTR)strODRV_CNCS_NO);		//�ؿ��Ļ�ü���ȣ
			m_listBalance.SetItemText(nListIndex, 29, (LPTSTR)(LPCTSTR)strHOLD_PST_YN);		//���������ǿ���
			m_listBalance.SetItemText(nListIndex, 30, (LPTSTR)(LPCTSTR)strUSE_YN);			//��뿩��
			m_listBalance.SetItemText(nListIndex, 31, (LPTSTR)(LPCTSTR)strODRV_ODNO);		//�ؿ��Ļ��ֹ���ȣ
			m_listBalance.SetItemText(nListIndex, 32, (LPTSTR)(LPCTSTR)strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
			m_listBalance.SetItemText(nListIndex, 33, (LPTSTR)(LPCTSTR)strODRV_MO_ODNO);		//�ؿ��Ļ����ֹ���ȣ
			m_listBalance.SetItemText(nListIndex, 34, (LPTSTR)(LPCTSTR)strORDR_GRUP_NO);		//�ֹ��׷��ȣ
			m_listBalance.SetItemText(nListIndex, 35, (LPTSTR)(LPCTSTR)strORDR_DT);				//�ֹ�����
			m_listBalance.SetItemText(nListIndex, 36, (LPTSTR)(LPCTSTR)strCUST_NM);				//����
			m_listBalance.SetItemText(nListIndex, 37, (LPTSTR)(LPCTSTR)strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
			m_listBalance.SetItemText(nListIndex, 38, (LPTSTR)(LPCTSTR)strMKT_PRC_APLY_STUP_AMT);		//���尡�����뼳���ݾ�
			m_listBalance.SetItemText(nListIndex, 39, (LPTSTR)(LPCTSTR)strORDR_QNT);			//�ֹ�����
			m_listBalance.SetItemText(nListIndex, 40, (LPTSTR)(LPCTSTR)strRVSE_QNT);			//��������
			m_listBalance.SetItemText(nListIndex, 41, (LPTSTR)(LPCTSTR)strCNCL_QNT);			//��Ҽ���
			m_listBalance.SetItemText(nListIndex, 42, (LPTSTR)(LPCTSTR)strCNCS_QNT);			//ü�����
			m_listBalance.SetItemText(nListIndex, 43, (LPTSTR)(LPCTSTR)strORDR_RMN_QNT);		//�ֹ��ܿ�����
			m_listBalance.SetItemText(nListIndex, 44, (LPTSTR)(LPCTSTR)strPRC_CND_DCD);			//�������Ǳ����ڵ�
			m_listBalance.SetItemText(nListIndex, 45, (LPTSTR)(LPCTSTR)strCNCS_CND_DCD);		//ü�����Ǳ����ڵ�
			m_listBalance.SetItemText(nListIndex, 46, (LPTSTR)(LPCTSTR)strSQ1_STLS_YN);			//1����ž�ν�����
			m_listBalance.SetItemText(nListIndex, 47, (LPTSTR)(LPCTSTR)strSQ1_APMPR_YN);		//1������������
			m_listBalance.SetItemText(nListIndex, 48, (LPTSTR)(LPCTSTR)strSQ1_DVSN_YN);			//1�����п���
			m_listBalance.SetItemText(nListIndex, 49, (LPTSTR)(LPCTSTR)strSQ1_STLS_PRC);		//1����ž�ν�����
			m_listBalance.SetItemText(nListIndex, 50, (LPTSTR)(LPCTSTR)strSQ1_APPN_PRC);		//1����������
			m_listBalance.SetItemText(nListIndex, 51, (LPTSTR)(LPCTSTR)strSQ1_CHAS_STLS_PRC);	//1�����������Ű���
			m_listBalance.SetItemText(nListIndex, 52, (LPTSTR)(LPCTSTR)strCTRT_UN_AMT);			//�������ݾ�
			m_listBalance.SetItemText(nListIndex, 53, (LPTSTR)(LPCTSTR)strORDR_DRCN_DCD);		//�ֹ����ⱸ���ڵ�
			m_listBalance.SetItemText(nListIndex, 54, (LPTSTR)(LPCTSTR)strAVR_CNCS_PRC);		//���ü�ᰡ��
			m_listBalance.SetItemText(nListIndex, 55, (LPTSTR)(LPCTSTR)strODRV_NOW_PRC);		//�ؿ��Ļ����簡��
			m_listBalance.SetItemText(nListIndex, 56, (LPTSTR)(LPCTSTR)strPRDT_CD2);			//��ǰ�ڵ�2

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
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U31_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
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
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U31_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
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
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U32_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
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
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U33_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		 �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdCancelOrd = 0;
	}
	//û���ֹ� Request ID
	else if (m_nRqIdCloseOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U31_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		 �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdCloseOrd = 0;
	}
	//SL�����ֹ� Request ID
	else if (m_nRqIdModSLOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U31_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		 �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdModSLOrd = 0;
	}
	//SL����ֹ� Request ID
	else if (m_nRqIdCanSLOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U33_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		 �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdCanSLOrd = 0;
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
void CFxMarginOrdDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
void CFxMarginOrdDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/*	���� : OnGetRealData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
		�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/
	CString strRealMessage;

	/***************************************
	 * ��ü��/ü��Ȯ��
	 ****************************************/
	if (!_tcscmp(strRealName, "FX0"))
	{
		/*--------------------------------------
		 �����۸����� ���ŵ� �ǽð� �����͸� �׸񺰷� ������.
		 ---------------------------------------*/
		CString strrltm_dpch_dcd = m_CommAgent.GetRealOutputData("FX0", "rltm_dpch_dcd");		//�ǽð��뺸�����ڵ�
		CString strusr_id = m_CommAgent.GetRealOutputData("FX0", "usr_id");		//�����ID
		CString strrltm_dpch_prcs_dcd = m_CommAgent.GetRealOutputData("FX0", "rltm_dpch_prcs_dcd");		//�ǽð��뺸ó�������ڵ�
		CString strcano = m_CommAgent.GetRealOutputData("FX0", "cano");		//���հ��¹�ȣ
		CString strfdm_unq_no = m_CommAgent.GetRealOutputData("FX0", "fdm_unq_no");		//�����Ͽ콺������ȣ
		CString strprdt_cd = m_CommAgent.GetRealOutputData("FX0", "prdt_cd");		//��ǰ�ڵ�
		CString strodrv_ordr_tp_dcd = m_CommAgent.GetRealOutputData("FX0", "odrv_ordr_tp_dcd");		//�ؿ��Ļ��ֹ����������ڵ�
		CString strordr_stts_dcd = m_CommAgent.GetRealOutputData("FX0", "ordr_stts_dcd");		//�ֹ����±����ڵ�
		CString strodrv_odno = m_CommAgent.GetRealOutputData("FX0", "odrv_odno");		//�ؿ��Ļ��ֹ���ȣ
		CString strodrv_or_odno = m_CommAgent.GetRealOutputData("FX0", "odrv_or_odno");		//�ؿ��Ļ����ֹ���ȣ
		CString strordr_dt = m_CommAgent.GetRealOutputData("FX0", "ordr_dt");		//�ֹ�����
		CString strapno = m_CommAgent.GetRealOutputData("FX0", "apno");		//���»�ǰ��ȣ
		CString strcust_nm = m_CommAgent.GetRealOutputData("FX0", "cust_nm");		//����
		CString strodrv_sell_buy_dcd = m_CommAgent.GetRealOutputData("FX0", "odrv_sell_buy_dcd");		//�ؿ��Ļ��ŵ��ż������ڵ�
		CString strodrv_ordr_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "odrv_ordr_prc_ctns");		//�ؿ��Ļ��ֹ����ݳ���
		CString strordr_qnt_ctns = m_CommAgent.GetRealOutputData("FX0", "ordr_qnt_ctns");		//�ֹ���������
		CString strodrv_prc_dcd = m_CommAgent.GetRealOutputData("FX0", "odrv_prc_dcd");		//�ؿ��Ļ����ݱ����ڵ�
		CString strcncs_cnd_dcd = m_CommAgent.GetRealOutputData("FX0", "cncs_cnd_dcd");		//ü�����Ǳ����ڵ�
		CString strodrv_ctrt_un_amt_ctns = m_CommAgent.GetRealOutputData("FX0", "odrv_ctrt_un_amt_ctns");		//�ؿ��Ļ��������ݾ׳���
		CString strfx_ordr_tot_amt_ctns = m_CommAgent.GetRealOutputData("FX0", "fx_ordr_tot_amt_ctns");		//FX�ֹ��ѱݾ׳���
		CString strcomm_mdia_dcd = m_CommAgent.GetRealOutputData("FX0", "comm_mdia_dcd");		//��Ÿ�ü�����ڵ�
		CString strexcg_acpt_tm = m_CommAgent.GetRealOutputData("FX0", "excg_acpt_tm");		//�ŷ��������ð�
		CString strexcg_cncs_tm = m_CommAgent.GetRealOutputData("FX0", "excg_cncs_tm");		//�ŷ���ü��ð�
		CString strordr_tm = m_CommAgent.GetRealOutputData("FX0", "ordr_tm");		//�ֹ��ð�
		CString strcncs_tm = m_CommAgent.GetRealOutputData("FX0", "cncs_tm");		//ü��ð�
		CString strcncs_dt = m_CommAgent.GetRealOutputData("FX0", "cncs_dt");		//ü������
		CString strodrv_cncs_no = m_CommAgent.GetRealOutputData("FX0", "odrv_cncs_no");		//�ؿ��Ļ�ü���ȣ
		CString strcncs_qnt_ctns = m_CommAgent.GetRealOutputData("FX0", "cncs_qnt_ctns");		//ü���������
		CString strodrv_cncs_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "odrv_cncs_prc_ctns");		//�ؿ��Ļ�ü�ᰡ�ݳ���
		CString strodrv_cncs_amt_ctns = m_CommAgent.GetRealOutputData("FX0", "odrv_cncs_amt_ctns");		//�ؿ��Ļ�ü��ݾ׳���
		CString strtrsl_odrv_cncs_amt_char = m_CommAgent.GetRealOutputData("FX0", "trsl_odrv_cncs_amt_char");		//ȯ���ؿ��Ļ�ü��ݾ׹���
		CString strcrry_cd = m_CommAgent.GetRealOutputData("FX0", "crry_cd");		//��ȭ�ڵ�
		CString strsq1_stls_yn = m_CommAgent.GetRealOutputData("FX0", "sq1_stls_yn");		//1����ž�ν�����
		CString strsq1_apmpr_yn = m_CommAgent.GetRealOutputData("FX0", "sq1_apmpr_yn");		//1������������
		CString strsq1_stls_prc_char = m_CommAgent.GetRealOutputData("FX0", "sq1_stls_prc_char");		//1����ž�ν����ݹ���
		CString strsq1_appn_prc_char = m_CommAgent.GetRealOutputData("FX0", "sq1_appn_prc_char");		//1���������ݹ���
		CString strsq1_chas_stls_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "sq1_chas_stls_prc_ctns");		//1�����������Ű��ݳ���
		CString strsq2_stls_yn = m_CommAgent.GetRealOutputData("FX0", "sq2_stls_yn");		//2����ž�ν�����
		CString strsq2_apmpr_yn = m_CommAgent.GetRealOutputData("FX0", "sq2_apmpr_yn");		//2������������
		CString strsq2_stls_prc_char = m_CommAgent.GetRealOutputData("FX0", "sq2_stls_prc_char");		//2����ž�ν����ݹ���
		CString strsq2_appn_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "sq2_appn_prc_ctns");		//2���������ݳ���
		CString strsq2_chas_stls_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "sq2_chas_stls_prc_ctns");		//2�����������Ű��ݳ���
		CString strtrde_prc_dfrn_ctns = m_CommAgent.GetRealOutputData("FX0", "trde_prc_dfrn_ctns");		//�ŸŰ������̳���
		CString strctno = m_CommAgent.GetRealOutputData("FX0", "ctno");		//���հ��´�ü��ȣ
		CString strfiller_100 = m_CommAgent.GetRealOutputData("FX0", "filler_100");		//�ʷ�_100

		strrltm_dpch_dcd.Trim();  //�ǽð��뺸�����ڵ�
		strusr_id.Trim(); //�����ID
		strrltm_dpch_prcs_dcd.Trim(); //�ǽð��뺸ó�������ڵ�
		strcano.Trim(); //���հ��¹�ȣ
		strfdm_unq_no.Trim(); //�����Ͽ콺������ȣ
		strprdt_cd.Trim();  //��ǰ�ڵ�
		strodrv_ordr_tp_dcd.Trim(); //�ؿ��Ļ��ֹ����������ڵ�
		strordr_stts_dcd.Trim();  //�ֹ����±����ڵ�
		strodrv_odno.Trim();  //�ؿ��Ļ��ֹ���ȣ
		strodrv_or_odno.Trim(); //�ؿ��Ļ����ֹ���ȣ
		strordr_dt.Trim();  //�ֹ�����
		strapno.Trim(); //���»�ǰ��ȣ
		strcust_nm.Trim();  //����
		strodrv_sell_buy_dcd.Trim();  //�ؿ��Ļ��ŵ��ż������ڵ�
		strodrv_ordr_prc_ctns.Trim(); //�ؿ��Ļ��ֹ����ݳ���
		strordr_qnt_ctns.Trim();  //�ֹ���������
		strodrv_prc_dcd.Trim(); //�ؿ��Ļ����ݱ����ڵ�
		strcncs_cnd_dcd.Trim(); //ü�����Ǳ����ڵ�
		strodrv_ctrt_un_amt_ctns.Trim();  //�ؿ��Ļ��������ݾ׳���
		strfx_ordr_tot_amt_ctns.Trim(); //FX�ֹ��ѱݾ׳���
		strcomm_mdia_dcd.Trim();  //��Ÿ�ü�����ڵ�
		strexcg_acpt_tm.Trim(); //�ŷ��������ð�
		strexcg_cncs_tm.Trim(); //�ŷ���ü��ð�
		strordr_tm.Trim();  //�ֹ��ð�
		strcncs_tm.Trim();  //ü��ð�
		strcncs_dt.Trim();  //ü������
		strodrv_cncs_no.Trim(); //�ؿ��Ļ�ü���ȣ
		strcncs_qnt_ctns.Trim();  //ü���������
		strodrv_cncs_prc_ctns.Trim(); //�ؿ��Ļ�ü�ᰡ�ݳ���
		strodrv_cncs_amt_ctns.Trim(); //�ؿ��Ļ�ü��ݾ׳���
		strtrsl_odrv_cncs_amt_char.Trim();  //ȯ���ؿ��Ļ�ü��ݾ׹���
		strcrry_cd.Trim();  //��ȭ�ڵ�
		strsq1_stls_yn.Trim();  //1����ž�ν�����
		strsq1_apmpr_yn.Trim(); //1������������
		strsq1_stls_prc_char.Trim();  //1����ž�ν����ݹ���
		strsq1_appn_prc_char.Trim();  //1���������ݹ���
		strsq1_chas_stls_prc_ctns.Trim(); //1�����������Ű��ݳ���
		strsq2_stls_yn.Trim();  //2����ž�ν�����
		strsq2_apmpr_yn.Trim(); //2������������
		strsq2_stls_prc_char.Trim();  //2����ž�ν����ݹ���
		strsq2_appn_prc_ctns.Trim();  //2���������ݳ���
		strsq2_chas_stls_prc_ctns.Trim(); //2�����������Ű��ݳ���
		strtrde_prc_dfrn_ctns.Trim(); //�ŸŰ������̳���
		strctno.Trim(); //���հ��´�ü��ȣ
		strfiller_100.Trim(); //�ʷ�_100

		/*--------------------------------------
		��ȸ ������ ����� �ֽ� ���簡 �ǽð�Ű�� �������� ��
		---------------------------------------*/
		if (m_strLoginID == strRealKey)
		{
			strRealMessage.Format("[%s][����:%s][��ǰ:%s][��ü��/ü��:%s]", strRealName, strcano, strprdt_cd, strordr_qnt_ctns);
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
void CFxMarginOrdDlg::OnAgentEventHandler(long nEventType, long nParam, LPCTSTR strParam)
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


void CFxMarginOrdDlg::OnBnClickedRadioEx1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnBnClickedBtnReqNonExecList();
}


void CFxMarginOrdDlg::OnBnClickedRadioEx2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnBnClickedBtnReqNonExecList();
}


//*******************************************************************
// Function Name : OnBnClickedBtnClose
// Function      : 
// Param         : 
// Return        : void 
// Create        : ������, 2017/07/31
// Comment       : û���ֹ�
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedBtnClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strSellBuy;
	GetDlgItem(IDC_POS_SELLBUY)->GetWindowText(strSellBuy);
	m_nRqIdCloseOrd = m_CommAgent.CreateRequestID();
	SendSellBuyOrder(strSellBuy, m_nRqIdCloseOrd, _T("CloseOrder"));
}


//*******************************************************************
// Function Name : OnBnClickedBtnModsl
// Function      : 
// Param         : 
// Return        : void 
// Create        : ������, 2017/07/31
// Comment       : S&L����
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedBtnModsl()
{
	/***************************************************
	 * ***** ���� *****
	 * �ŷ��ҿ� ���� Stop�� Limit�� ���� OCO �ֹ� �Ұ�
	 ***************************************************/

	//[1] Request ID����
	m_nRqIdModSLOrd = m_CommAgent.CreateRequestID();

	//�ؿ��Ļ����ֹ���ȣ
	CString strODRV_OR_ODNO;		//�ؿ��Ļ����ֹ���ȣ
	CString strODRV_SELL_BUY_DCD;		//�ؿ��Ļ��ŵ��ż������ڵ�

	GetDlgItem(IDC_ORDER_NO)->GetWindowText(strODRV_OR_ODNO);
	strODRV_OR_ODNO.Trim();

	/***************************************************
	 * SL�ֹ��� ó���̸� �ű��ֹ�Tr��  SL�ֹ��� ����.
	 * ���� SL�ֹ��� ������ �����ֹ�Tr�� SL�ֹ��� ����.
	 ***************************************************/
	if (strODRV_OR_ODNO.IsEmpty())
	{
		GetDlgItem(IDC_POS_SELLBUY)->GetWindowText(strODRV_SELL_BUY_DCD);
		SendSellBuyOrder(strODRV_SELL_BUY_DCD, m_nRqIdModSLOrd, _T("SLOrder"));

		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5901U32";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5901U32_in";	//�Է� ���ڵ��(���ҽ����� ����)

	

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	CString strCTNO;		//���հ��´�ü��ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strPWD;		//��й�ȣ
	CString strFDM_UNQ_NO;		//�����Ͽ콺������ȣ
	CString strPRDT_CD;		//��ǰ�ڵ�
	CString strNMPR_UNQ_NO;		//ȣ��������ȣ
	CString strCNCS_CND_DCD;		//ü�����Ǳ����ڵ�
	CString strORDR_EXPR_DT;		//�ֹ���������
	CString strPRC_CND_DCD;		//�������Ǳ����ڵ�
	CString strODRV_ORDR_PRC;		//�ؿ��Ļ��ֹ�����
	CString strORDR_QNT;		//�ֹ�����
	CString strSQ1_STLS_YN;		//1����ž�ν�����
	CString strSQ1_APMPR_YN;		//1������������
	CString strSQ1_STLS_PRC;		//1����ž�ν�����
	CString strSQ1_APPN_PRC;		//1����������
	CString strSQ1_CHAS_STLS_PRC;		//1�����������Ű���
	CString strSQ2_STLS_YN;		//2����ž�ν�����
	CString strSQ2_STLS_PRC;		//2����ž�ν�����
	CString strSQ2_APMPR_YN;		//2������������
	CString strSQ2_APPN_PRC;		//2����������
	CString strSQ2_CHAS_STLS_PRC;		//2�����������Ű���
	CString strORDR_DRCN_DCD;		//�ֹ����ⱸ���ڵ�
	CString strTRDE_PRC_DFRN_CTNS;		//�ŸŰ������̳���

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//��й�ȣ
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//��ǰ�ڵ�
	
	//�����Ͽ콺������ȣ
	GetDlgItem(IDC_EDIT_SYMBOL_HOUSE)->GetWindowText(strFDM_UNQ_NO);

	//��ǰ�ڵ�
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//ȣ��������ȣ
	strNMPR_UNQ_NO = _T("0");

	//�ؿ��Ļ��ŵ��ż������ڵ�
	strODRV_SELL_BUY_DCD = _T("6");

	//�ֹ�����
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	//1����ž�ν�����(STOP)
	GetDlgItem(IDC_EDIT_STOP_PRC)->GetWindowText(strSQ1_STLS_PRC);
	//1����ž�ν�����(STOP)
	if (_ttof(strSQ1_STLS_PRC))
		strSQ1_STLS_YN = _T("Y");
	else
		strSQ1_STLS_YN = _T("N");

	//1����������(LIMIT)
	GetDlgItem(IDC_EDIT_LIMIT_PRC)->GetWindowText(strSQ1_APPN_PRC);
	//1������������(LIMIT)
	if (_ttof(strSQ1_APPN_PRC))
		strSQ1_APMPR_YN = _T("Y");
	else
		strSQ1_APMPR_YN = _T("N");

	//1�����������Ű���(T.Stop)
	GetDlgItem(IDC_EDIT_T_STOP_PRC)->GetWindowText(strSQ1_CHAS_STLS_PRC);
	//2����ž�ν�����
	if (_ttof(strSQ1_CHAS_STLS_PRC))
		strSQ2_STLS_YN = _T("Y");
	else
		strSQ2_STLS_YN = _T("N");

	strSQ2_STLS_PRC = _T("0");		//2����ž�ν�����(������)
	strSQ2_APPN_PRC = _T("0");		//2����������(������)
	strSQ2_APMPR_YN = _T("N");		//2������������(������)
	strSQ2_CHAS_STLS_PRC = _T("0");		//2�����������Ű���(������)

	//�ֹ����ⱸ���ڵ�(N-�Ϲ��ֹ�, W-����ֹ� (�Ϲ��ֹ��� ���))
	strORDR_DRCN_DCD = _T("N");

	//�ŸŰ������̳���(������)
	strTRDE_PRC_DFRN_CTNS.Empty();

	//T.S
	if (!strSQ2_STLS_YN.CompareNoCase(_T("Y")))
	{
		strPRC_CND_DCD = _T("6");
	}
	//Stop �Ǵ� Limit
	else if (!strSQ1_STLS_YN.CompareNoCase(_T("Y")) ||
			 !strSQ1_APMPR_YN.CompareNoCase(_T("Y")))
	{
		strPRC_CND_DCD = _T("4");
	}
	//OCO �ֹ�
	else if (!strSQ1_STLS_YN.CompareNoCase(_T("Y")) &&
			 !strSQ1_APMPR_YN.CompareNoCase(_T("Y")))
	{
		strPRC_CND_DCD = _T("5");
	}
	
	//�ؿ��Ļ��ֹ�����
	if (strPRC_CND_DCD == _T("1") || strPRC_CND_DCD == _T("3"))	//������, ��������(STOP)
		GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strODRV_ORDR_PRC);
	else //���尡
		strODRV_ORDR_PRC = _T("0");

	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "PWD", strPWD);		//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//�ؿ��Ļ��ŵ��ż������ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//�����Ͽ콺������ȣ
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "NMPR_UNQ_NO", strNMPR_UNQ_NO);		//ȣ��������ȣ
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "CNCS_CND_DCD", strCNCS_CND_DCD);		//ü�����Ǳ����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "ORDR_EXPR_DT", strORDR_EXPR_DT);		//�ֹ���������
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "PRC_CND_DCD", strPRC_CND_DCD);		//�������Ǳ����ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "ODRV_ORDR_PRC", strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_STLS_YN", strSQ1_STLS_YN);		//1����ž�ν�����
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_APMPR_YN", strSQ1_APMPR_YN);		//1������������
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_STLS_PRC", strSQ1_STLS_PRC);		//1����ž�ν�����
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_APPN_PRC", strSQ1_APPN_PRC);		//1����������
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_CHAS_STLS_PRC", strSQ1_CHAS_STLS_PRC);		//1�����������Ű���
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_STLS_YN", strSQ2_STLS_YN);		//2����ž�ν�����
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_STLS_PRC", strSQ2_STLS_PRC);		//2����ž�ν�����
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_APMPR_YN", strSQ2_APMPR_YN);		//2������������
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_APPN_PRC", strSQ2_APPN_PRC);		//2����������
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_CHAS_STLS_PRC", strSQ2_CHAS_STLS_PRC);		//2�����������Ű���
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//�ֹ����ⱸ���ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "TRDE_PRC_DFRN_CTNS", strTRDE_PRC_DFRN_CTNS);		//�ŸŰ������̳���

	CString strBenefitAcc = "N";		//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.

	//[3] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdModSLOrd, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", nRequestDataCnt) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}


//*******************************************************************
// Function Name : OnBnClickedBtnCalsl
// Function      : 
// Param         : 
// Return        : void 
// Create        : ������, 2017/07/31
// Comment       : S&L���
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedBtnCalsl()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTrCode = "OTS5901U33";			//Tran�ڵ�(���ҽ����� ����)
	CString strInRecName = "OTS5901U33_in";	//�Է� ���ڵ��(���ҽ����� ����)

	//[1] Request ID����
	m_nRqIdCanSLOrd = m_CommAgent.CreateRequestID();

	//[2] Tran��ȸ �Է°��� �Է��Ѵ�.
	CString strODRV_OR_ODNO;		//�ؿ��Ļ����ֹ���ȣ
	CString strCTNO;		//���հ��´�ü��ȣ
	CString strAPNO;		//���»�ǰ��ȣ
	CString strPWD;		//��й�ȣ
	CString strFDM_UNQ_NO;		//�����Ͽ콺������ȣ
	CString strPRDT_CD;		//��ǰ�ڵ�
	CString strORDR_QNT;		//�ֹ�����
	CString strORDR_DRCN_DCD;		//�ֹ����ⱸ���ڵ�

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//���»�ǰ��ȣ
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//���հ��´�ü��ȣ
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//��й�ȣ
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//���º�й�ȣ�� �ܹ��� ��ȣȭ�� �ؾߵȴ�.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//��ǰ�ڵ�

	//�ؿ��Ļ����ֹ���ȣ
	GetDlgItem(IDC_ORDER_NO)->GetWindowText(strODRV_OR_ODNO);

	//�����Ͽ콺������ȣ
	GetDlgItem(IDC_EDIT_SYMBOL_HOUSE)->GetWindowText(strFDM_UNQ_NO);

	//��ǰ�ڵ�
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//�ֹ�����
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	//�ֹ����ⱸ���ڵ�(N-�Ϲ��ֹ�, W-����ֹ� (�Ϲ��ֹ��� ���))
	strORDR_DRCN_DCD = _T("N");

	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "APNO", strAPNO);		//���»�ǰ��ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "PWD", strPWD);		//��й�ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//�����Ͽ콺������ȣ
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//�ֹ����ⱸ���ڵ�

	CString strBenefitAcc = "N";		//�������ǰ��� ����
	CString strPreNext = "0";		//������ȸ("0"-�Ϲ�, "1"-������ȸ ù ��ȸ, "2"-������ȸ, "3"-������ȸ)
	CString strScreenNo = "9999";	//ȭ���ȣ
	int nRequestDataCnt = 0; 		//���� ������ �Ǽ�(0���� �Է��ϸ� Default ���� �Ǽ��� �Էµȴ�.)

	//[3] ������ Tran��ȸ ��û�Ѵ�.
	if (m_CommAgent.RequestTran(m_nRqIdCanSLOrd, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", nRequestDataCnt) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}
