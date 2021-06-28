/*----------------------------------------*
| ���α׷��� : �ϳ��������� Open API ����
| ��      �� : v 
| ����  ���� :
| ��      Ÿ :
*----------------------------------------*/
// EurexOptSiseDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "HFCommClient.h"
#include "EurexOptSiseDlg.h"

#define ID_SECOND_TIMER		100	//1�� ���� Ÿ�̸�

#define SELL_BK_COLOR		RGB(206, 232, 255)	//�ŵ� ����
#define BUY_BK_COLOR		RGB(251, 221, 255)	//�ż� ����

//��� ����ü ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

// CEurexOptSiseDlg ��ȭ ����
CEurexOptSiseDlg::CEurexOptSiseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEurexOptSiseDlg::IDD, pParent)
{
	m_bCommConnect = FALSE;
	m_nRqIdHoga = 0;
	m_nRqIdCurPrice = 0;
	m_nRqIdTick = 0;
	m_nRqIdCodeList = 0;
	m_nRqIdChart = 0;
	m_nSeverType = 0;

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEurexOptSiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, m_editUserID);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDC_EDIT_AUTH_PWD, m_editAuthPwd);
	DDX_Text(pDX, IDC_EDIT_ID, m_strLoginID);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strLoginPwd);
	DDX_Text(pDX, IDC_EDIT_AUTH_PWD, m_strCertPwd);
	DDX_Control(pDX, IDC_EDIT_SYMBOL, m_editSymbol);
	DDX_Control(pDX, IDC_EDIT_SYMBOL_PRICE, m_editSymbolPrice);
	DDX_Control(pDX, IDC_LIST_TICK, m_listTick);
	DDX_Control(pDX, IDC_EDIT_SYMBOL_TICK, m_editSymbolTick);
	DDX_Control(pDX, IDC_LIST_SYMBOL, m_listCode);
	DDX_Control(pDX, IDC_EDIT_SYMBOL_CHART, m_editSymbolChart);
	DDX_Control(pDX, IDC_CHK_AUTO_REQ_CHART, m_chkAutoReqChart);
	DDX_Control(pDX, IDC_LIST_CHART, m_listChart);
	DDX_Control(pDX, IDC_EDIT_CHART_CNT, m_editChartCnt);
	DDX_Control(pDX, IDC_DATETIME_FROM, m_dateTimeFrom);
	DDX_Control(pDX, IDC_DATETIME_TO, m_dateTimeTo);
}

BEGIN_MESSAGE_MAP(CEurexOptSiseDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_LOGIN, &CEurexOptSiseDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_LOGOUT, &CEurexOptSiseDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_INITCOMM, &CEurexOptSiseDlg::OnBnClickedInitcomm)
	ON_BN_CLICKED(IDC_TERMINATE, &CEurexOptSiseDlg::OnBnClickedTerminate)
	ON_BN_CLICKED(IDC_BTN_REQ_HOGA, &CEurexOptSiseDlg::OnBnClickedBtnReqHoga)
	ON_BN_CLICKED(IDC_BTN_REQ_PRICE, &CEurexOptSiseDlg::OnBnClickedBtnReqPrice)
	ON_BN_CLICKED(IDC_BTN_REQ_TICK, &CEurexOptSiseDlg::OnBnClickedBtnReqTick)
	ON_BN_CLICKED(IDC_BTN_REQ_TICK_NEXT, &CEurexOptSiseDlg::OnBnClickedBtnReqTickNext)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE_LIST, &CEurexOptSiseDlg::OnBnClickedBtnReqCodeList)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE_LIST_NEXT, &CEurexOptSiseDlg::OnBnClickedBtnReqCodeListNext)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SYMBOL, &CEurexOptSiseDlg::OnNMDblclkListSymbol)
	ON_BN_CLICKED(IDOK, &CEurexOptSiseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_REQ_CHART, &CEurexOptSiseDlg::OnBnClickedBtnReqChart)
	ON_BN_CLICKED(IDC_BTN_REQ_CHART_NEXT, &CEurexOptSiseDlg::OnBnClickedBtnReqChartNext)
	ON_COMMAND_RANGE(IDC_RADIO_TICK, IDC_RADIO_MON, &CEurexOptSiseDlg::OnRadioChartTerm)
	ON_COMMAND_RANGE(IDC_CON_REAL, IDC_CON_F_DEMO, &CEurexOptSiseDlg::OnRdoSelectServer)
END_MESSAGE_MAP()

// agent�κ��� �̺�Ʈ ���� �Լ��� �����Ѵ�.
BEGIN_EVENTSINK_MAP(CEurexOptSiseDlg, CDialog)
	ON_EVENT(CEurexOptSiseDlg, IDC_HFCOMMAGENTCTRL1, 1, CEurexOptSiseDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CEurexOptSiseDlg, IDC_HFCOMMAGENTCTRL1, 2, CEurexOptSiseDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CEurexOptSiseDlg, IDC_HFCOMMAGENTCTRL1, 3, CEurexOptSiseDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
END_EVENTSINK_MAP()

// CEurexOptSiseDlg �޽��� ó����

void CEurexOptSiseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CEurexOptSiseDlg::OnPaint()
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
HCURSOR CEurexOptSiseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CEurexOptSiseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.

	//ȣ�� ����ĥ
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_SELL_1:
	case IDC_SELL_2:
	case IDC_SELL_3:
	case IDC_SELL_4:
	case IDC_SELL_5:
	case IDC_SELL_REMAIN_1:
	case IDC_SELL_REMAIN_2:
	case IDC_SELL_REMAIN_3:
	case IDC_SELL_REMAIN_4:
	case IDC_SELL_REMAIN_5:
	case IDC_SELL_CNT1:
	case IDC_SELL_CNT2:
	case IDC_SELL_CNT3:
	case IDC_SELL_CNT4:
	case IDC_SELL_CNT5:
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(SELL_BK_COLOR);
		hbr = m_brushSellBack;
	}
	break;
	case IDC_BUY_1:
	case IDC_BUY_2:
	case IDC_BUY_3:
	case IDC_BUY_4:
	case IDC_BUY_5:
	case IDC_BUY_REMAIN_1:
	case IDC_BUY_REMAIN_2:
	case IDC_BUY_REMAIN_3:
	case IDC_BUY_REMAIN_4:
	case IDC_BUY_REMAIN_5:
	case IDC_BUY_CNT1:
	case IDC_BUY_CNT2:
	case IDC_BUY_CNT3:
	case IDC_BUY_CNT4:
	case IDC_BUY_CNT5:
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(BUY_BK_COLOR);
		hbr = m_brushBuyBack;
	}
	break;
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

void CEurexOptSiseDlg::OnDestroy()
{
	//��� �ǽð������ �����Ѵ�.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();

	CDialog::OnDestroy();
}

void CEurexOptSiseDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CEurexOptSiseDlg::OnTimer(UINT_PTR nIDEvent)
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

void CEurexOptSiseDlg::OnNMDblclkListSymbol(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;

	CString strSymbol = m_listCode.GetItemText(nSelectRow, 0); //�����ڵ�
	CString strStandardCode = m_listCode.GetItemText(nSelectRow, 1); //ǥ�������ڵ�
	CString strSymbolName = m_listCode.GetItemText(nSelectRow, 2); //�ѱ������
	CString strPrice = m_listCode.GetItemText(nSelectRow, 3); //���ذ�

	if (strSymbol.IsEmpty())
		return;

	//�����ڵ带 �Է��Ѵ�.
	m_editSymbol.SetWindowText(strSymbol);		//5�ܰ�ȣ�� �����ڵ�(�ɺ�)
	m_editSymbolPrice.SetWindowText(strSymbol);	//���簡 �����ڵ�(�ɺ�)
	m_editSymbolTick.SetWindowText(strSymbol);	//�ð��뺰ü�� �����ڵ�(�ɺ�)
	m_editSymbolChart.SetWindowText(strSymbol);	//��Ʈ �����ڵ�(�ɺ�)

	GetDlgItem(IDC_SYMBOL_NAME)->SetWindowText(strSymbolName);		//5�ܰ�ȣ�� �����
	GetDlgItem(IDC_SYMBOL_NAME_PRICE)->SetWindowText(strSymbolName);//���簡 �����
	GetDlgItem(IDC_SYMBOL_NAME_TICK)->SetWindowText(strSymbolName);	//�ð��뺰ü�� �����
	GetDlgItem(IDC_SYMBOL_NAME_CHART)->SetWindowText(strSymbolName);//��Ʈ ������ �����

	//�Էµ� �����ڵ�� ����ȸ ��û�� �Ѵ�.
	OnBnClickedBtnReqPrice();	//Eurex�ɼ� ���簡 ��ȸ
	OnBnClickedBtnReqHoga();	//Eurex�ɼ� 5�ܰ�ȣ�� ��ȸ
	OnBnClickedBtnReqTick();	//Eurex�ɼ� �ð��뺰ü�� ��ȸ
	OnBnClickedBtnReqChart();	//Eurex�ɼ� ��Ʈ������ ��ȸ
}

void CEurexOptSiseDlg::OnRadioChartTerm(UINT nID)
{
	CString strCaption;

	GetDlgItem(IDC_STATIC_CHART)->SetWindowText(NULL);

	switch (nID)
	{
	case IDC_RADIO_TICK:	//ƽ
	{
		GetDlgItem(IDC_STATIC_CHART)->SetWindowText(_T("�Ǽ�"));
	}
	break;
	case IDC_RADIO_MIN:		//��
	{
		GetDlgItem(IDC_STATIC_CHART)->SetWindowText(_T("��"));
	}
	break;
	case IDC_RADIO_DAY:		//��
	{
	}
	break;
	case IDC_RADIO_WEEK:	//��
	{
	}
	break;
	case IDC_RADIO_MON:		//��
	{
	}
	break;
	default:
	{

	}
	break;
	}
}

//*******************************************************************
// Function Name : OnInitDialog
// Function      : ���̾�α� �ʱ�ȭ
// Param         : 
// Return        : BOOL 
// Create        : 
// Comment       : 
//******************************************************************
BOOL CEurexOptSiseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CString strTitle;
	strTitle.Format("%s-[�߰��ɼ�(Eurex) �ü�](%s)", PROGRAM_NAME, VERSION_INFO);
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
	* Eurex�ɼ� �ð��뺰ü�ᰡ ����Ʈ ��Ʈ�� �ʱ�ȭ
	**********************************/
	InitListTick();

	/**********************************
	* Eurex�ɼ� ���� ����Ʈ ��Ʈ�� �ʱ�ȭ
	**********************************/
	InitListCode();

	/**********************************
	* Eurex�ɼ� ��Ʈ ����Ʈ ��Ʈ�� �ʱ�ȭ
	**********************************/
	InitListChart();

	/**********************************
	* HFCommAgent.dll(API Agent DLL���� ��ġ�� ���)
	**********************************/
	CString strApidAgentModulePath = m_CommAgent.GetApiAgentModulePath();
	GetDlgItem(IDC_API_AGENT_PATH)->SetWindowText(strApidAgentModulePath);

	/**********************************
	* ��ȸTr, �ǽð� ��� I/O ���� ���ҽ� ���� �ε�
	**********************************/
	//�ǽýð� ��� ���ҽ������� �����ڰ� ���� ��θ� ���� �ε����� ������
	//HFCommAgent.dll������ ��ġ�� RealRes �������� �ڵ����� �ε��Ѵ�.
#if 0
	//Eurex�ɼ�ü�� �ǽð� I/O ���� ���ҽ� ����
	if (!m_CommAgent.LoadRealResource(strApidAgentModulePath + "/RealRes/O30.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());

	//Eurex�ɼ�ȣ�� �ǽð� I/O ���� ���ҽ� ����
	if (!m_CommAgent.LoadRealResource(strApidAgentModulePath + "/RealRes/O31.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
#endif

	//��Ʈ Eurex�ɼ� ���� ƽ���� ����
	((CButton*)GetDlgItem(IDC_RADIO_MIN))->SetCheck(1);
	GetDlgItem(IDC_EDIT_CHART_CNT)->SetWindowText("60");
	GetDlgItem(IDC_STATIC_CHART)->SetWindowText("��");

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
// Function Name : OnRdoSelectServer
// Function      : 
// Param         : UINT nID
// Return        : void 
// Create        : 
// Comment       : ���Ӽ����� �����Ѵ�.
//******************************************************************
void CEurexOptSiseDlg::OnRdoSelectServer(UINT nID)
{
	m_nSeverType = nID - IDC_CON_REAL;

	/*----------------------------------
	���Ӽ����� �����Ѵ�.(0 - ����, 1 - ��������, 2 - �ؿܸ���)
	*----------------------------------*/
	m_CommAgent.SetLoginMode(0, m_nSeverType);
}

//*******************************************************************
// Function Name : InitListTick
// Function      : Eurex�ɼ� �ð��뺰ü�� ����Ʈ ��Ʈ�� �ʱ�ȭ
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::InitListTick()
{
	CRect rc;
	m_listTick.GetClientRect(rc);
	m_listTick.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int arrWidth[5] = { 0x00 };
	int nWidth = rc.Width() - ::GetSystemMetrics(SM_CYHSCROLL);

	arrWidth[0] = (int)(nWidth * 0.2);
	arrWidth[1] = (int)(nWidth * 0.2);
	arrWidth[2] = (int)(nWidth * 0.2);
	arrWidth[3] = (int)(nWidth * 0.2);
	arrWidth[4] = (int)(nWidth * 0.2);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("�ð�"), _T("ü�ᰡ"), _T("���"), _T("�����"), _T("ü�ᷮ") };

	int i;
	for (i = 0; i < 5; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		if (i == 0)
			lvcolumn.fmt = LVCFMT_CENTER;
		else
			lvcolumn.fmt = LVCFMT_LEFT;

		lvcolumn.pszText = strTitle[i];

		lvcolumn.iSubItem = i;
		lvcolumn.cx = arrWidth[i];
		m_listTick.InsertColumn(i, &lvcolumn);
	}
}

//*******************************************************************
// Function Name : InitListCode
// Function      : Eurex�ɼ� ���� ����Ʈ ��Ʈ�� �ʱ�ȭ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::InitListCode()
{
	int arrWidth[6] = { 0x00 };
	m_listCode.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("�����ڵ�"), _T("ǥ���ڵ�"), _T("�����"), _T("ATM����"), _T("�ŷ��¼�"), _T("��������") };

	int i;
	CDC* pDC = GetDC();
	CSize size;

	for (i = 0; i < 6; i++)
	{
		size = pDC->GetTextExtent(strTitle[i]);
		arrWidth[i] = size.cx;
	}

	for (i = 0; i < 6; i++)
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

//*******************************************************************
// Function Name : InitListChart
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::InitListChart()
{
	CRect rc;
	m_listChart.GetClientRect(rc);
	m_listChart.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int arrWidth[8] = { 60, 60, 70, 70, 70, 70, 80, 80 };

	int nWidth = rc.Width() - ::GetSystemMetrics(SM_CYHSCROLL);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("����"), _T("�ð�"), _T("����"), _T("�ð�"), _T("��"), _T("����"), _T("ü�ᷮ"), _T("�ŷ���") };

	int i;
	for (i = 0; i < 8; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		if (i == 0)
			lvcolumn.fmt = LVCFMT_CENTER;
		else
			lvcolumn.fmt = LVCFMT_LEFT;

		lvcolumn.pszText = strTitle[i];

		lvcolumn.iSubItem = i;
		lvcolumn.cx = arrWidth[i];
		m_listChart.InsertColumn(i, &lvcolumn);
	}
}

//*******************************************************************
// Function Name : GetDiffSign
// Function      : ����ȣ
// Param         : CString strSignCode
// Return        : CString 
// Create        :
// Comment       : 
//******************************************************************
CString CEurexOptSiseDlg::GetDiffSign(CString strSignCode)
{
	if (strSignCode == _T("2"))			// ���
		return _T("��");
	else if (strSignCode == _T("1"))	// ����
		return _T("��");
	else if (strSignCode == _T("3"))	// ����
		return _T("-");
	else if (strSignCode == _T("5"))	// �϶�
		return _T("��");
	else if (strSignCode == _T("4"))	// ���Ѱ�
		return _T("��");

	return _T("");
}

//*******************************************************************
// Function Name : SetHogaData
// Function      : ȣ�������� ��Ʈ�� ǥ��
// Param         :	CString* arrSellHoga,	�ŵ� 5�ܰ�ȣ��
//					CString* arrBuyHoga,	�ż� 5�ܰ�ȣ��
//					CString* arrSellRemain,	�ŵ� 5�ܰ�ȣ���ܷ�
//					CString* arrBuyRemain	�ż� 5�ܰ�ȣ���ܷ�
//					CString* arrSellCnt,
//					CString* arrBuyCnt
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::SetHogaData(CString* arrSellHoga, CString* arrBuyHoga, CString* arrSellRemain,
	CString* arrBuyRemain, CString* arrSellCnt, CString* arrBuyCnt)
{
	//���鹮�� ����
	arrSellHoga[0].Trim();		arrSellHoga[1].Trim();
	arrSellHoga[2].Trim();		arrSellHoga[3].Trim();
	arrSellHoga[4].Trim();

	arrSellRemain[0].Trim();	arrSellRemain[1].Trim();
	arrSellRemain[2].Trim();	arrSellRemain[3].Trim();
	arrSellRemain[4].Trim();

	arrBuyHoga[0].Trim();		arrBuyHoga[1].Trim();
	arrBuyHoga[2].Trim();		arrBuyHoga[3].Trim();
	arrBuyHoga[4].Trim();

	arrBuyRemain[0].Trim();		arrBuyRemain[1].Trim();
	arrBuyRemain[2].Trim();		arrBuyRemain[3].Trim();
	arrBuyRemain[4].Trim();

	arrSellCnt[0].Trim();		arrSellCnt[1].Trim();
	arrSellCnt[2].Trim();		arrSellCnt[3].Trim();
	arrSellCnt[4].Trim();

	arrBuyCnt[0].Trim();		arrBuyCnt[1].Trim();
	arrBuyCnt[2].Trim();		arrBuyCnt[3].Trim();
	arrBuyCnt[4].Trim();

	//�ŵ�ȣ�� ��Ʈ�� �Է�
	GetDlgItem(IDC_SELL_1)->SetWindowText(arrSellHoga[0]);
	GetDlgItem(IDC_SELL_2)->SetWindowText(arrSellHoga[1]);
	GetDlgItem(IDC_SELL_3)->SetWindowText(arrSellHoga[2]);
	GetDlgItem(IDC_SELL_4)->SetWindowText(arrSellHoga[3]);
	GetDlgItem(IDC_SELL_5)->SetWindowText(arrSellHoga[4]);

	//�ŵ�ȣ���ܷ� ��Ʈ�� �Է�
	GetDlgItem(IDC_SELL_REMAIN_1)->SetWindowText(arrSellRemain[0]);
	GetDlgItem(IDC_SELL_REMAIN_2)->SetWindowText(arrSellRemain[1]);
	GetDlgItem(IDC_SELL_REMAIN_3)->SetWindowText(arrSellRemain[2]);
	GetDlgItem(IDC_SELL_REMAIN_4)->SetWindowText(arrSellRemain[3]);
	GetDlgItem(IDC_SELL_REMAIN_5)->SetWindowText(arrSellRemain[4]);

	//�ŵ�ȣ���Ǽ� ��Ʈ�� �Է�
	GetDlgItem(IDC_SELL_CNT1)->SetWindowText(arrSellRemain[0]);
	GetDlgItem(IDC_SELL_CNT2)->SetWindowText(arrSellRemain[1]);
	GetDlgItem(IDC_SELL_CNT3)->SetWindowText(arrSellRemain[2]);
	GetDlgItem(IDC_SELL_CNT4)->SetWindowText(arrSellRemain[3]);
	GetDlgItem(IDC_SELL_CNT5)->SetWindowText(arrSellRemain[4]);

	//�ż�ȣ�� ��Ʈ�� �Է�
	GetDlgItem(IDC_BUY_1)->SetWindowText(arrBuyHoga[0]);
	GetDlgItem(IDC_BUY_2)->SetWindowText(arrBuyHoga[1]);
	GetDlgItem(IDC_BUY_3)->SetWindowText(arrBuyHoga[2]);
	GetDlgItem(IDC_BUY_4)->SetWindowText(arrBuyHoga[3]);
	GetDlgItem(IDC_BUY_5)->SetWindowText(arrBuyHoga[4]);

	//�ż�ȣ���ܷ� ��Ʈ�� �Է�
	GetDlgItem(IDC_BUY_REMAIN_1)->SetWindowText(arrBuyRemain[0]);
	GetDlgItem(IDC_BUY_REMAIN_2)->SetWindowText(arrBuyRemain[1]);
	GetDlgItem(IDC_BUY_REMAIN_3)->SetWindowText(arrBuyRemain[2]);
	GetDlgItem(IDC_BUY_REMAIN_4)->SetWindowText(arrBuyRemain[3]);
	GetDlgItem(IDC_BUY_REMAIN_5)->SetWindowText(arrBuyRemain[4]);

	//�ż�ȣ���Ǽ� ��Ʈ�� �Է�
	GetDlgItem(IDC_BUY_CNT1)->SetWindowText(arrSellRemain[0]);
	GetDlgItem(IDC_BUY_CNT2)->SetWindowText(arrSellRemain[1]);
	GetDlgItem(IDC_BUY_CNT3)->SetWindowText(arrSellRemain[2]);
	GetDlgItem(IDC_BUY_CNT4)->SetWindowText(arrSellRemain[3]);
	GetDlgItem(IDC_BUY_CNT5)->SetWindowText(arrSellRemain[4]);
}

//*******************************************************************
// Function Name : OnBnClickedInitcomm
// Function      : ��Ÿ�� �ʱ�ȭ �� ��� ����
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::OnBnClickedInitcomm()
{
	if (m_bCommConnect)
	{
		::AfxMessageBox("�̹� ��� ���ӵǾ����ϴ�!");
		return;
	}

	//��Ÿ�� �ʱ�ȭ �� ��� ����
	if (m_CommAgent.CommInit() < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());

	//�������(TRUE : ����, FALSE : ����)
	m_bCommConnect = m_CommAgent.CommGetConnectState();
}

//*******************************************************************
// Function Name : OnBnClickedTerminate
// Function      : ��ſ��� ����
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::OnBnClickedTerminate()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("�̹� ��� ������ ������ϴ�!");
		return;
	}

	//��� �ǽð������ �����Ѵ�.
	m_CommAgent.AllUnRegisterReal();

	//��ſ��� ����
	m_CommAgent.CommTerminate(TRUE);

	//�������(TRUE : ����, FALSE : ����)
	m_bCommConnect = m_CommAgent.CommGetConnectState();
}

//*******************************************************************
// Function Name : OnBnClickedLogin
// Function      : �α���
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::OnBnClickedLogin()
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
	else
		OnBnClickedBtnReqCodeList(); //���񸮽�Ʈ(������) ��ȸ
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : �α׾ƿ�
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::OnBnClickedLogout()
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
// Function Name : OnBnClickedBtnReqCodeList
// Function      : Eurex�ɼ� ���� ����Ʈ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::OnBnClickedBtnReqCodeList()
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

	//Eurex�ɼ� ���� ����Ʈ(������) ��Ʈ�� ������ �ʱ�ȭ
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
	strMarketCode = _T("EU");	//Eurex�ɼ�

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("1899"));		//GID

	//�������� �������� ����׸��.
	CString strOutputFidList;

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	(1)�����ڵ�,(2)ǥ���ڵ�,(3)�ѱ������,(1373)ATM�����ڵ�[1:ATM 2:ITM 3:OTM ],
	(1773)�ŷ��¼�,	(2624)�ǽð��������ѿ���,(17)���Ѱ�,(18)���Ѱ�*/
	strOutputFidList = "1,2,3,1373,1773,2624,17,18";

	CString strScreenNo;
	strScreenNo = "9999";

	//������ȸ �ɼ� : '0':�̻��, '1'���, '2' : ���� ������ ��ȸ, '3' : ���� ������ ��ȸ
	CString strPreNext = "1";

	/**********************************
	* 5. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, "", strScreenNo, 9999);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqCodeListNext
// Function      : Eurex�ɼ� ���� ����Ʈ ���� ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::OnBnClickedBtnReqCodeListNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	/**********************************
	* 1. �����ȸ Request ID�� �����Ѵ�.
	**********************************/
	m_nRqIdCodeList = m_CommAgent.CreateRequestID();
	if (m_nRqIdCodeList == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("EU"); //Eurex�ɼ�

	/**********************************
	* 2. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("1899"));		//GID

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 3. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	(1)�����ڵ�,(2)ǥ���ڵ�,(3)�ѱ������,(1373)ATM�����ڵ�[1:ATM 2:ITM 3:OTM ],
	(1773)�ŷ��¼�,	(2624)�ǽð��������ѿ���,(17)���Ѱ�,(18)���Ѱ�*/
	strOutputFidList = "1,2,3,1373,1773,2624,17,18";

	CString strScreenNo;
	strScreenNo = "9999";

	CString strPreNext = "3"; //���� ������ ��ȸ

	/**********************************
	* 4. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, m_strCodeListNextRqKey, strScreenNo, 9999);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqPrice
// Function      : ���簡 ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::OnBnClickedBtnReqPrice()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strSymBol;			//�����ڵ�
	m_editSymbolPrice.GetWindowText(strSymBol); //�����ڵ�
	strSymBol.Trim();
	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("�����ڵ� �Է��� �ʼ��Դϴ�!");
		m_editSymbolPrice.SetFocus();
		return;
	}
	/**********************************
	* 1. �����ȸ Request ID�� �����Ѵ�.
	**********************************/
	m_nRqIdCurPrice = m_CommAgent.CreateRequestID();
	if (m_nRqIdCurPrice == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	/**********************************
	* 2. ������ ��ϵ� Eurex�ɼ�ü��(���簡) �ǽð���� ����.
	**********************************/
	if (!m_strCurPriceRealKey.IsEmpty())
	{
		CString strRealName;
		strRealName = _T("O30"); //Eurex�ɼ�ü�� Real name

		m_CommAgent.UnRegisterReal(strRealName, m_strCurPriceRealKey);
		m_strCurPriceRealKey.Empty();
	}

	CString strMarketCode;		//���屸��
	strMarketCode = _T("EU");	//Eurex�ɼ�

	//Eurex�ɼ�ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
	m_strCurPriceRealKey = strSymBol;

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCurPrice, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCurPrice, _T("9002"), strSymBol);		//�����ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCurPrice, _T("GID"), _T("1000"));		//GID

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	���簡(4), ��ȣ(6), ���ϴ��(5), �����(7), �ŷ���(11)
	���ϰŷ���(28), �ð�(13), ��(14), ����(15) */
	strOutputFidList = "4,6,5,7,11,28,13,14,15";

	CString strScreenNo;
	strScreenNo = "9999";

	/**********************************
	* 5. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFid(m_nRqIdCurPrice, strOutputFidList, strScreenNo);

	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqHoga
// Function      : Eurex�ɼ�ȣ�� ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::OnBnClickedBtnReqHoga()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strSymBol;			//�����ڵ�
	m_editSymbol.GetWindowText(strSymBol);

	strSymBol.Trim();
	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("�����ڵ� �Է��� �ʼ��Դϴ�!");
		m_editSymbol.SetFocus();
		return;
	}

	/**********************************
	* 1. �����ȸ Request ID�� �����Ѵ�.
	**********************************/
	m_nRqIdHoga = m_CommAgent.CreateRequestID();
	if (m_nRqIdHoga == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	/**********************************
	* 2. ������ ��ϵ� ����ȣ�� �ǽð���� ����
	**********************************/
	if (!m_strHogaRealKey.IsEmpty())
	{
		CString strRealName;
		strRealName = _T("O31");

		m_CommAgent.UnRegisterReal(strRealName, m_strHogaRealKey);
		m_strHogaRealKey.Empty();
	}

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("EU");

	//����ȣ�� �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
	m_strHogaRealKey = strSymBol;

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdHoga, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdHoga, _T("9002"), strSymBol);		//�����ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdHoga, _T("GID"), _T("1000"));		//GID

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	CString strSellHoga = _T("29,30,31,32,33");	//�ŵ� 1~5 ȣ��(FID)
	CString strSellRemain = _T("63,64,65,66,67"); //�ŵ� 1~5 ȣ���ܷ�(FID)
	CString strBuyHoga = _T("39,40,41,42,43");	//�ż� 1~5 ȣ��(FID)
	CString strBuyRemain = _T("73,74,75,76,77"); //�ż� 1~5 ȣ�� �ܷ�(FID)
	CString strSellCnt = _T("196,197,198,199,200"); //�ŵ� 1~5 ȣ���Ǽ�(FID)
	CString strBuyCnt = _T("201,202,203,204,205"); //�ż� 1~5 ȣ���Ǽ�(FID)

	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]*/
	CString strOutputFidList = strSellHoga + "," + strSellRemain + "," + strBuyHoga + "," +
		strBuyRemain + "," + strSellCnt + "," + strBuyCnt;

	CString strScreenNo;
	strScreenNo = "9999";

	/**********************************
	* 5. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFid(m_nRqIdHoga, strOutputFidList, strScreenNo);

	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqTick
// Function      : Eurex�ɼ� �ð��뺰ü�� ������ ��ȸ(���Ӱŷ� �����Ͱ� �ִ� ���)
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::OnBnClickedBtnReqTick()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strSymBol;			//����ɺ��ڵ�
	m_editSymbolTick.GetWindowText(strSymBol);
	strSymBol.Trim();

	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("�����ڵ� �Է��� �ʼ��Դϴ�!");
		m_editSymbolTick.SetFocus();
		return;
	}

	/**********************************
	* 1. ������ȸŰ �ʱ�ȭ
	**********************************/
	m_strTickNextRqKey.Empty();

	//Eurex�ɼ� �ð��뺰ü�� ����Ʈ ��Ʈ�� ������ �ʱ�ȭ
	m_listTick.DeleteAllItems();

	/**********************************
	* 2. �����ȸ Request ID�� �����Ѵ�.
	**********************************/
	m_nRqIdTick = m_CommAgent.CreateRequestID();

	if (m_nRqIdTick == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	/**********************************
	* 3. ������ ��ϵ� Eurex�ɼ�ü��(���簡) �ǽð���� ����.
	**********************************/
	if (!m_strTickRealKey.IsEmpty())
	{
		CString strRealName;
		strRealName = _T("O30");

		m_CommAgent.UnRegisterReal(strRealName, m_strTickRealKey);
		m_strTickRealKey.Empty();
	}

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("EU");

	//Eurex�ɼ�ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
	m_strTickRealKey = strSymBol;

	/**********************************
	* 4. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9002"), strSymBol);		//����ɺ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("GID"), _T("1001"));		//GID

	//�������� �������� ����׸��.
	CString strOutputFidList;

	/**********************************
	* 5. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	�ð�(8), ü�ᰡ(4), ���(5), �����(7), ü�ᷮ(83) */
	strOutputFidList = "8,4,5,7,83";

	CString strScreenNo;
	strScreenNo = "9999";

	//������ȸ �ɼ� : '0':�̻��, '1'���, '2' : ���� ������ ��ȸ, '3' : ���� ������ ��ȸ
	CString strPreNext = "1";

	/**********************************
	* 6. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdTick, strOutputFidList, strPreNext, "", strScreenNo, 0);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqTickNext
// Function      : Eurex�ɼ� �ð��뺰ü�� ���� ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::OnBnClickedBtnReqTickNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strSymBol;			//����ɺ��ڵ�
	m_editSymbolTick.GetWindowText(strSymBol);
	strSymBol.Trim();

	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("�����ڵ� �Է��� �ʼ��Դϴ�!");
		m_editSymbolTick.SetFocus();
		return;
	}


	/**********************************
	* 1. �����ȸ Request ID�� �����Ѵ�.
	**********************************/
	m_nRqIdTick = m_CommAgent.CreateRequestID();
	if (m_nRqIdTick == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("EU"); //Eurex�ɼ�

	/**********************************
	* 2. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9002"), strSymBol);		//����ɺ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("GID"), _T("1001"));		//GID

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 3. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	�ð�(8), ü�ᰡ(4), ���(5), �����(7), ü�ᷮ(83) */
	strOutputFidList = "8,4,5,7,83";

	CString strScreenNo;
	strScreenNo = "9999";

	CString strPreNext = "3"; //���� ������ ��ȸ

	/**********************************
	* 4. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdTick, strOutputFidList, strPreNext, m_strTickNextRqKey, strScreenNo, 0);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqChart
// Function      : Eurex�ɼ� ��Ʈ ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::OnBnClickedBtnReqChart()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strSymBol;			//����ɺ��ڵ�
	m_editSymbolChart.GetWindowText(strSymBol);
	strSymBol.Trim();

	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("�����ڵ� �Է��� �ʼ��Դϴ�!");
		m_editSymbolChart.SetFocus();
		return;
	}

	/**********************************
	* 1. ������ȸŰ �ʱ�ȭ
	**********************************/
	m_strTickNextRqKey.Empty();

	//Eurex�ɼ� �ð��뺰ü�� ����Ʈ ��Ʈ�� ������ �ʱ�ȭ
	m_listChart.DeleteAllItems();

	/**********************************
	* 2. �����ȸ Request ID�� �����Ѵ�.
	**********************************/
	m_nRqIdChart = m_CommAgent.CreateRequestID();

	if (m_nRqIdChart == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	CString strChartCnt;
	m_editChartCnt.GetWindowText(strChartCnt);

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("EU");

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	int nRecvCnt = 9999;
	CString strFromDate, strToDate;
	m_dateTimeFrom.GetWindowText(strFromDate);	//��ȸ ������
	m_dateTimeTo.GetWindowText(strToDate);		//��ȸ ������

	strFromDate.Remove('-'); strToDate.Remove('-');

	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9002"), strSymBol);		//����ɺ�
	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);		//������
	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);		//������

	if (((CButton*)GetDlgItem(IDC_RADIO_TICK))->GetCheck()) //ƽ
	{
		if (_ttoi(strChartCnt) > 0)
		{
			nRecvCnt = _ttoi(strChartCnt);
			m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strChartCnt);	//9119 : ƽ �Ǽ�
		}

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1002")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MIN))->GetCheck()) //��
	{
		CString strMin;
		strMin.Format(_T("%d"), _ttoi(strChartCnt) * 60);

		//9119 : �����ڵ�( 30: 30��, 60: 1��, 600: 10��, 3600: 60��, 60*N: N�� )
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strMin);

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1005")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_DAY))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1007")); //GID

	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_WEEK))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "W");				//��(W), ��(M)

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1009")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MON))->GetCheck()) //��
	{

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "M");				//��(W), ��(M)

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1009")); //GID
	}

	//�������� �������� ����׸��.
	CString strOutputFidList;

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	����(9), �ð�(8), ����(4), �ð�(13), ��(14), ����(15), ü�ᷮ(83), �ŷ���(11) */
	strOutputFidList = "9,8,4,13,14,15,83,11";

	CString strScreenNo;
	strScreenNo = "9999";

	//������ȸ �ɼ� : '0':�̻��, '1'���, '2' : ���� ������ ��ȸ, '3' : ���� ������ ��ȸ
	CString strPreNext = "1";

	/**********************************
	* 6. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdChart, strOutputFidList, strPreNext, "", strScreenNo, nRecvCnt);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqChartNext
// Function      : Eurex�ɼ� ��Ʈ ���� ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexOptSiseDlg::OnBnClickedBtnReqChartNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strSymBol;			//����ɺ��ڵ�
	m_editSymbolChart.GetWindowText(strSymBol);
	strSymBol.Trim();

	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("�����ڵ� �Է��� �ʼ��Դϴ�!");
		m_editSymbolChart.SetFocus();
		return;
	}


	/**********************************
	* 1. �����ȸ Request ID�� �����Ѵ�.
	**********************************/
	m_nRqIdChart = m_CommAgent.CreateRequestID();
	if (m_nRqIdChart == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	CString strChartCnt;
	m_editChartCnt.GetWindowText(strChartCnt);

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("EU"); //Eurex�ɼ�

	/**********************************
	* 2. �����ȸ ��û �Էµ�����
	**********************************/
	int nRecvCnt = 9999;
	CString strFromDate, strToDate;
	m_dateTimeFrom.GetWindowText(strFromDate);	//��ȸ ������
	m_dateTimeTo.GetWindowText(strToDate);		//��ȸ ������
	strFromDate.Remove('-'); strToDate.Remove('-');

	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9002"), strSymBol);		//����ɺ�
	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);	//������
	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);	//������

	if (((CButton*)GetDlgItem(IDC_RADIO_TICK))->GetCheck()) //ƽ
	{
		if (_ttoi(strChartCnt) > 0)
		{
			nRecvCnt = _ttoi(strChartCnt);
			m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strChartCnt);	//9119 : ƽ �Ǽ�
		}

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1002")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MIN))->GetCheck()) //��
	{
		CString strMin;
		strMin.Format(_T("%d"), _ttoi(strChartCnt) * 60);

		//9119 : �����ڵ�( 30: 30��, 60: 1��, 600: 10��, 3600: 60��, 60*N: N�� )
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strMin);

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1005")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_DAY))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1007")); //GID

	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_WEEK))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "W");				//��(W), ��(M)

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1009")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MON))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "M");				//��(W), ��(M)

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1009")); //GID
	}

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 3. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	����(9), �ð�(8), ����(4), �ð�(13), ��(14), ����(15), ü�ᷮ(83), �ŷ���(11) */
	strOutputFidList = "9,8,4,13,14,15,83,11";

	CString strScreenNo;
	strScreenNo = "9999";

	CString strPreNext = "3"; //���� ������ ��ȸ

	/**********************************
	* 4. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdChart, strOutputFidList, strPreNext, m_strChartNextRqKey, strScreenNo, nRecvCnt);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

void CEurexOptSiseDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	PostMessage(WM_CLOSE);
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
void CEurexOptSiseDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
{
	/* ���� : OnGetTranData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
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

	//��ȸ���� �ΰ��޽����ڵ�
	CString strSubMsgCode = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::SubMsgCode);

	//��ȸ���� �ΰ��޽���
	CString strSubMsg = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::SubMsg);

	//��������( "1" : ����, "0" : ����)
	CString strIsError = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::Error);

	CString strErrMsg = m_CommAgent.GetLastErrMsg();
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
void CEurexOptSiseDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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

	/***************************************
	* Eurex�ɼ� ���� ����Ʈ(������) ��ȸ ������ ���� ó��
	****************************************/
	if (m_nRqIdCodeList == nRequestId)
	{
		CString arrItemValue[8];

		m_listCode.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;

		/*--------------------------------------
		���� ��ȸ ������ �����̸� ������ ���� ����Ÿ �ڿ�
		�ٿ� �����Ѵ�.
		---------------------------------------*/
		int nViewScrollPos = 0;
		if (!m_strCodeListNextRqKey.IsEmpty())
		{
			nListIndex = m_listCode.GetItemCount();
			nViewScrollPos = nListIndex;
		}

		int nDataCnt = m_CommAgent.GetFidOutputRowCnt(nRequestId);


		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			arrItemValue[0] = m_CommAgent.GetFidOutputData(nRequestId, "1", i);	//�����ڵ�
			arrItemValue[1] = m_CommAgent.GetFidOutputData(nRequestId, "2", i);	//ǥ���ڵ�
			arrItemValue[2] = m_CommAgent.GetFidOutputData(nRequestId, "3", i);	//�ѱ������
			arrItemValue[3] = m_CommAgent.GetFidOutputData(nRequestId, "1373", i);//ATM�����ڵ�
			arrItemValue[4] = m_CommAgent.GetFidOutputData(nRequestId, "1773", i);//�ŷ��¼�
			arrItemValue[5] = m_CommAgent.GetFidOutputData(nRequestId, "2624", i);//�ǽð��������ѿ���
			arrItemValue[6] = m_CommAgent.GetFidOutputData(nRequestId, "17", i);//���Ѱ�
			arrItemValue[7] = m_CommAgent.GetFidOutputData(nRequestId, "18", i);//���Ѱ�

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listCode.InsertItem(&lvItem);

			//���񸮽�Ʈ ��Ʈ�ѿ� �� �Է�
			for (int col = 0; col < 6; col++)
				m_listCode.SetItemText(nListIndex, col, (LPTSTR)(LPCTSTR)arrItemValue[col]);

		}//End of for

		m_listCode.EnsureVisible(nViewScrollPos, FALSE);
		m_listCode.SetRedraw(TRUE);

		/*--------------------------------------
		������ȸŰ�� ������ ���´�.
		---------------------------------------*/
		m_strCodeListNextRqKey = strPreNextContext;

		/*--------------------------------------
		������ȸŰ�� '2', '3'�̸� '����'��ư�� Ȱ��ȭ ��Ų��.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_CODE_LIST_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_CODE_LIST_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdCodeList = 0;	//Eurex�ɼ� ���� ����Ʈ(������) ��ȸ Request ID
	}
	/***************************************
	* Eurex�ɼ� 5�ܰ�ȣ�� ��ȸ ������ ���� ó��
	****************************************/
	else if (m_nRqIdHoga == nRequestId)
	{
		CString arrSellHoga[5];
		CString arrBuyHoga[5];

		CString arrSellRemain[5];
		CString arrBuyRemain[5];

		CString arrSellCnt[5];
		CString arrBuyCnt[5];

		/*--------------------------------------
		FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
		---------------------------------------*/
		//�ŵ�ȣ��/�ܷ�
		arrSellHoga[0] = m_CommAgent.GetFidOutputData(nRequestId, "29", 0);	//�ŵ� 1ȣ��
		arrSellHoga[1] = m_CommAgent.GetFidOutputData(nRequestId, "30", 0);	//�ŵ� 2ȣ��
		arrSellHoga[2] = m_CommAgent.GetFidOutputData(nRequestId, "31", 0);	//�ŵ� 3ȣ��
		arrSellHoga[3] = m_CommAgent.GetFidOutputData(nRequestId, "32", 0);	//�ŵ� 4ȣ��
		arrSellHoga[4] = m_CommAgent.GetFidOutputData(nRequestId, "33", 0);	//�ŵ� 5ȣ��
		arrSellRemain[0] = m_CommAgent.GetFidOutputData(nRequestId, "63", 0);	//�ŵ� 1ȣ���ܷ�
		arrSellRemain[1] = m_CommAgent.GetFidOutputData(nRequestId, "64", 0);	//�ŵ� 2ȣ���ܷ�
		arrSellRemain[2] = m_CommAgent.GetFidOutputData(nRequestId, "65", 0);	//�ŵ� 3ȣ���ܷ�
		arrSellRemain[3] = m_CommAgent.GetFidOutputData(nRequestId, "66", 0);	//�ŵ� 4ȣ���ܷ�
		arrSellRemain[4] = m_CommAgent.GetFidOutputData(nRequestId, "67", 0);	//�ŵ� 5ȣ���ܷ�
		arrSellCnt[0] = m_CommAgent.GetFidOutputData(nRequestId, "196", 0);		//�ŵ� 1ȣ���Ǽ�
		arrSellCnt[1] = m_CommAgent.GetFidOutputData(nRequestId, "197", 0);		//�ŵ� 2ȣ���Ǽ�
		arrSellCnt[2] = m_CommAgent.GetFidOutputData(nRequestId, "198", 0);		//�ŵ� 3ȣ���Ǽ�
		arrSellCnt[3] = m_CommAgent.GetFidOutputData(nRequestId, "199", 0);		//�ŵ� 4ȣ���Ǽ�
		arrSellCnt[4] = m_CommAgent.GetFidOutputData(nRequestId, "200", 0);		//�ŵ� 5ȣ���Ǽ�

		//�ż�ȣ��/�ܷ�
		arrBuyHoga[0] = m_CommAgent.GetFidOutputData(nRequestId, "39", 0);		//�ż� 1ȣ��
		arrBuyHoga[1] = m_CommAgent.GetFidOutputData(nRequestId, "40", 0);		//�ż� 2ȣ��
		arrBuyHoga[2] = m_CommAgent.GetFidOutputData(nRequestId, "41", 0);		//�ż� 3ȣ��
		arrBuyHoga[3] = m_CommAgent.GetFidOutputData(nRequestId, "42", 0);		//�ż� 4ȣ��
		arrBuyHoga[4] = m_CommAgent.GetFidOutputData(nRequestId, "43", 0);		//�ż� 5ȣ��
		arrBuyRemain[0] = m_CommAgent.GetFidOutputData(nRequestId, "73", 0);	//�ż� 1ȣ���ܷ�
		arrBuyRemain[1] = m_CommAgent.GetFidOutputData(nRequestId, "74", 0);	//�ż� 2ȣ���ܷ�
		arrBuyRemain[2] = m_CommAgent.GetFidOutputData(nRequestId, "75", 0);	//�ż� 3ȣ���ܷ�
		arrBuyRemain[3] = m_CommAgent.GetFidOutputData(nRequestId, "76", 0);	//�ż� 4ȣ���ܷ�
		arrBuyRemain[4] = m_CommAgent.GetFidOutputData(nRequestId, "77", 0);	//�ż� 5ȣ���ܷ�
		arrBuyCnt[0] = m_CommAgent.GetFidOutputData(nRequestId, "201", 0);		//�ż� 1ȣ���Ǽ�
		arrBuyCnt[1] = m_CommAgent.GetFidOutputData(nRequestId, "202", 0);		//�ż� 2ȣ���Ǽ�
		arrBuyCnt[2] = m_CommAgent.GetFidOutputData(nRequestId, "203", 0);		//�ż� 3ȣ���Ǽ�
		arrBuyCnt[3] = m_CommAgent.GetFidOutputData(nRequestId, "204", 0);		//�ż� 4ȣ���Ǽ�
		arrBuyCnt[4] = m_CommAgent.GetFidOutputData(nRequestId, "205", 0);		//�ż� 5ȣ���Ǽ�

		/*--------------------------------------
		��ȸ�� ���� �����͸� ȭ�� ��Ʈ�ѿ� ǥ���Ѵ�.
		---------------------------------------*/
		SetHogaData(arrSellHoga, arrBuyHoga, arrSellRemain, arrBuyRemain, arrSellCnt, arrBuyCnt);

		/*--------------------------------------
		Eurex�ɼ�ȣ�� �ǽð�Ű�� �ǽð��� ����Ѵ�.
		�ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		---------------------------------------*/
		if (!m_strHogaRealKey.IsEmpty())
		{
			CString strRealName;
			strRealName = _T("O31");

			m_CommAgent.RegisterReal(strRealName, m_strHogaRealKey); //�ǽð� ���
		}

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdHoga = 0;	//Eurex�ɼ� 5�ܰ�ȣ�� ��ȸ Request ID
	}
	/***************************************
	* Eurex�ɼ� ���簡 ��ȸ ������ ���� ó��
	****************************************/
	else if (m_nRqIdCurPrice == nRequestId)
	{
		/*--------------------------------------
		FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
		---------------------------------------*/
		CString strCurPrice = m_CommAgent.GetFidOutputData(nRequestId, "4", 0);		//���簡
		CString strDiffSign = m_CommAgent.GetFidOutputData(nRequestId, "6", 0);		//��ȣ
		CString strDiff = m_CommAgent.GetFidOutputData(nRequestId, "5", 0);			//���ϴ��
		CString strDiffRate = m_CommAgent.GetFidOutputData(nRequestId, "7", 0);		//�����
		CString strVolume = m_CommAgent.GetFidOutputData(nRequestId, "11", 0);		//�ŷ���
		CString strPreVolume = m_CommAgent.GetFidOutputData(nRequestId, "28", 0);	//���ϰŷ���
		CString strOpenPrice = m_CommAgent.GetFidOutputData(nRequestId, "13", 0);	//�ð�
		CString strHighPrice = m_CommAgent.GetFidOutputData(nRequestId, "14", 0);	//��
		CString strLowPrice = m_CommAgent.GetFidOutputData(nRequestId, "15", 0);	//����

		GetDlgItem(IDC_CUR_PRICE)->SetWindowText(strCurPrice);
		GetDlgItem(IDC_DIFF)->SetWindowText(GetDiffSign(strDiffSign));
		GetDlgItem(IDC_DIFF_SIGN)->SetWindowText(strDiff);
		GetDlgItem(IDC_DIFF_RATE)->SetWindowText(strDiffRate);
		GetDlgItem(IDC_VOLUME)->SetWindowText(strVolume);
		GetDlgItem(IDC_PREV_VOLUME)->SetWindowText(strPreVolume);
		GetDlgItem(IDC_START_PRICE)->SetWindowText(strOpenPrice);
		GetDlgItem(IDC_HIGH_PRICE)->SetWindowText(strHighPrice);
		GetDlgItem(IDC_LOW_PRICE)->SetWindowText(strLowPrice);

		/*--------------------------------------
		���ɼ� ü��(���簡) �ǽð����Ű�� �ǽð��� ����Ѵ�.
		�ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		---------------------------------------*/
		if (!m_strCurPriceRealKey.IsEmpty())
		{
			CString strRealName;
			strRealName = _T("O30");

			m_CommAgent.RegisterReal(strRealName, m_strCurPriceRealKey); //�ǽð� ���
		}

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdCurPrice = 0;	//Eurex�ɼ� ���簡 ��ȸ Request ID
	}
	/***************************************
	* Eurex�ɼ� �ð��뺰ü�� ��ȸ ������ ���� ó��
	****************************************/
	else if (m_nRqIdTick == nRequestId)
	{
		CString strTime;		//�ð�
		CString strPrice;		//ü�ᰡ
		CString strDiff;		//���
		CString strDiffRate;	//���
		CString strVolume;		//ü�ᷮ

		m_listTick.SetRedraw(FALSE);
		LV_ITEM	lvItem;

		int nListIndex = 0;

		/*--------------------------------------
		���� ��ȸ ������ �����̸� ������ ���� ����Ÿ �ڿ�
		�ٿ� �����Ѵ�.
		---------------------------------------*/
		int nViewScrollPos = 0;
		if (!m_strTickNextRqKey.IsEmpty())
		{
			nListIndex = m_listTick.GetItemCount();
			nViewScrollPos = nListIndex;
		}

		int nDataCnt = m_CommAgent.GetFidOutputRowCnt(nRequestId);

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			strTime = m_CommAgent.GetFidOutputData(nRequestId, "8", i);	//�ð�
			strPrice = m_CommAgent.GetFidOutputData(nRequestId, "4", i);	//ü�ᰡ
			strDiff = m_CommAgent.GetFidOutputData(nRequestId, "5", i);	//���
			strDiffRate = m_CommAgent.GetFidOutputData(nRequestId, "7", i);	//���
			strVolume = m_CommAgent.GetFidOutputData(nRequestId, "83", i);//ü�ᷮ

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listTick.InsertItem(&lvItem);

			m_listTick.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strTime);	//�ð�
			m_listTick.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strPrice);	//ü�ᰡ
			m_listTick.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strDiff);	//���
			m_listTick.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strDiffRate);//���
			m_listTick.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strVolume);	//ü�ᷮ
		}

		m_listTick.EnsureVisible(nViewScrollPos, FALSE);
		m_listTick.SetRedraw(TRUE);

		/*--------------------------------------
		�ɼ�ü�� �ǽð��� ����Ѵ�.
		�ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		---------------------------------------*/
		if (!m_strTickRealKey.IsEmpty() && m_strTickNextRqKey.IsEmpty())
		{
			CString strRealName;
			strRealName = _T("O30");

			m_CommAgent.RegisterReal(strRealName, m_strTickRealKey); //�ǽð� ���
		}

		/*--------------------------------------
		������ȸŰ�� ������ ���´�.
		---------------------------------------*/
		m_strTickNextRqKey = strPreNextContext;

		/*--------------------------------------
		������ȸŰ�� '2', '3'�̸� '����'��ư�� Ȱ��ȭ ��Ų��.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_TICK_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_TICK_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdTick = 0;	//Eurex�ɼ� �ð��뺰ü�� ��ȸ Request ID

	}
	/***************************************
	* Eurex�ɼ� ��Ʈ ��ȸ ������ ���� ó��
	****************************************/
	else if (m_nRqIdChart == nRequestId)
	{
		CString arrItem[8];

		m_listChart.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;
		int nViewScrollPos = 0;

		/*--------------------------------------
		���� ��ȸ ������ �����̸� ������ ���� ����Ÿ �ڿ�
		�ٿ� �����Ѵ�.
		---------------------------------------*/
		if (!m_strChartNextRqKey.IsEmpty())
		{
			nListIndex = m_listChart.GetItemCount();
			nViewScrollPos = nListIndex;
		}

#if 1	/***************************************
		* ���ŵ����͸� ���� �����Ѵ�.(C++������ ��� ����)
		* ���񸮽�Ʈ, ��Ʈ ������ ���� �뷮�� ������ ó�� ��
		* ������Ʈ ��Ʈ���� GetFidOutputData �Լ� ȣ�⺸�� ���� ������ ���δ�.
		****************************************/

		CCommRecvData commRecvData;
		int nVecRowCnt = 0;	//������ �Ǽ�(��)
		int nVecColCnt = 0;	//������ �׸� �Ǽ�(��)

		//FID ��ȸ���� ������ �޸𸮸� ���´�.(C++������ ��� ����)
		if (m_CommAgent.GetCommFidDataBlock((long)&commRecvData) == TRUE)
		{
			nVecRowCnt = commRecvData.GetRowCnt();	//������ �Ǽ�(��)
			nVecColCnt = commRecvData.GetColCnt();	//������ �׸� �Ǽ�(��)
		}

		int nDataCnt = nVecRowCnt;

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			arrItem[0] = commRecvData.GetItem(i, 0);	//0009 : ����
			arrItem[1] = commRecvData.GetItem(i, 1);	//0008 : �ð�
			arrItem[2] = commRecvData.GetItem(i, 2);	//0004 : ����
			arrItem[3] = commRecvData.GetItem(i, 3);	//0013 : �ð�
			arrItem[4] = commRecvData.GetItem(i, 4);	//0014 : ��
			arrItem[5] = commRecvData.GetItem(i, 5);	//0015 : ����
			arrItem[6] = commRecvData.GetItem(i, 6);	//0083 : ü�ᷮ
			arrItem[7] = commRecvData.GetItem(i, 7);	//0011 : �ŷ���

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listChart.InsertItem(&lvItem);

			//����Ʈ ��Ʈ�ѿ� �׸� ����Ÿ �Է�
			for (int col = 0; col < 8; col++)
			{
				m_listChart.SetItemText(nListIndex, col, (LPTSTR)(LPCTSTR)arrItem[col]);
			}

		}//End of for

#else	/***************************************
		* ������Ʈ ��Ʈ���� ���� ���������� �׸� ����Ÿ�� ������.
		****************************************/
		int nDataCnt = m_CommAgent.GetFidOutputRowCnt(nRequestId);

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			arrItem[0] = m_CommAgent.GetFidOutputData(nRequestId, "9", i);	//0009 : ����
			arrItem[1] = m_CommAgent.GetFidOutputData(nRequestId, "8", i);	//0008 : �ð�
			arrItem[2] = m_CommAgent.GetFidOutputData(nRequestId, "4", i);	//0004 : ����
			arrItem[3] = m_CommAgent.GetFidOutputData(nRequestId, "13", i);	//0013 : �ð�
			arrItem[4] = m_CommAgent.GetFidOutputData(nRequestId, "14", i);	//0014 : ��
			arrItem[5] = m_CommAgent.GetFidOutputData(nRequestId, "15", i);	//0015 : ����
			arrItem[6] = m_CommAgent.GetFidOutputData(nRequestId, "83", i);	//0083 : ü�ᷮ
			arrItem[7] = m_CommAgent.GetFidOutputData(nRequestId, "11", i);	//0011 : �ŷ���

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listChart.InsertItem(&lvItem);

			//����Ʈ ��Ʈ�ѿ� �׸� ����Ÿ �Է�
			for (int col = 0; col < 8; col++)
			{
				m_listChart.SetItemText(nListIndex, col, (LPTSTR)(LPCTSTR)arrItem[col]);
			}

		}//End of for
#endif

		m_listChart.EnsureVisible(nViewScrollPos, FALSE);
		m_listChart.SetRedraw(TRUE);

		/*--------------------------------------
		������ȸŰ�� ������ ���´�.
		---------------------------------------*/
		m_strChartNextRqKey = strPreNextContext;

		/*--------------------------------------
		������ȸŰ�� '2', '3'�̸� '����'��ư�� Ȱ��ȭ ��Ų��.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_CHART_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_CHART_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdChart = 0;	//Eurex�ɼ� ���� ����Ʈ(������) ��ȸ Request ID

		/*--------------------------------------
		�ڵ� ���� ��ȸ
		---------------------------------------*/
		if (m_chkAutoReqChart.GetCheck() == 1 &&
			GetDlgItem(IDC_BTN_REQ_CHART_NEXT)->IsWindowEnabled())
		{
			OnBnClickedBtnReqChartNext();
		}
	}//End of if

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
void CEurexOptSiseDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/* ���� : OnGetRealData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
	�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/

	/***************************************
	* Eurex�ɼ� ȣ�� �ǽð� ������ ����
	****************************************/
	if (!_tcscmp(strRealName, "O31"))
	{
		/*--------------------------------------
		��ȸ ������ ����� Eurex�ɼ� ȣ�� �ǽð�Ű�� �������� ��
		---------------------------------------*/
		if (m_strHogaRealKey == strRealKey)
		{
			CString arrSellHoga[5];
			CString arrBuyHoga[5];

			CString arrSellRemain[5];
			CString arrBuyRemain[5];

			CString arrSellCnt[5];
			CString arrBuyCnt[5];

#if 1		/*--------------------------------------
			���ŵ� �ǽð� �����͸� ���� ������.(C++������ ��� ����)
			�뷮�� �ǽð� ������ ó�� �ÿ��� ������Ʈ ��Ʈ�� GetRealOutputData �Լ� ȣ�⺸�� ���� ������ ���δ�.
			---------------------------------------*/
			CCommRecvData realCommRecvData;
			int nItemCnt = 0;		//�׸� �Ǽ�

			//FID ��ȸ���� ������ �޸𸮸� ���´�.(C++������ ��� ����)
			if (m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData) == TRUE)
				nItemCnt = realCommRecvData.GetColCnt();		//�׸� �Ǽ�

			//F01.res ������  INDEX�ʵ� ��ȣ�� �ε����� ����Ѵ�.
			arrSellHoga[0] = realCommRecvData.GetItem(0, 2);		//�ŵ�1ȣ��
			arrSellHoga[1] = realCommRecvData.GetItem(0, 4);		//�ŵ�2ȣ��
			arrSellHoga[2] = realCommRecvData.GetItem(0, 6);		//�ŵ�3ȣ��
			arrSellHoga[3] = realCommRecvData.GetItem(0, 8);		//�ŵ�4ȣ��
			arrSellHoga[4] = realCommRecvData.GetItem(0, 10);	//�ŵ�5ȣ��

			arrSellRemain[0] = realCommRecvData.GetItem(0, 32);	//�ŵ�1ȣ���ܷ�
			arrSellRemain[1] = realCommRecvData.GetItem(0, 33);	//�ŵ�2ȣ���ܷ�
			arrSellRemain[2] = realCommRecvData.GetItem(0, 34);	//�ŵ�3ȣ���ܷ�
			arrSellRemain[3] = realCommRecvData.GetItem(0, 35);	//�ŵ�4ȣ���ܷ�
			arrSellRemain[4] = realCommRecvData.GetItem(0, 36);	//�ŵ�5ȣ���ܷ�

			arrSellCnt[0] = realCommRecvData.GetItem(0, 22);		//�ŵ�1ȣ���Ǽ�
			arrSellCnt[1] = realCommRecvData.GetItem(0, 23);		//�ŵ�2ȣ���Ǽ�
			arrSellCnt[2] = realCommRecvData.GetItem(0, 24);		//�ŵ�3ȣ���Ǽ�
			arrSellCnt[3] = realCommRecvData.GetItem(0, 25);		//�ŵ�4ȣ���Ǽ�
			arrSellCnt[4] = realCommRecvData.GetItem(0, 26);		//�ŵ�5ȣ���Ǽ�

			arrBuyHoga[0] = realCommRecvData.GetItem(0, 12);		//�ż�1ȣ��
			arrBuyHoga[1] = realCommRecvData.GetItem(0, 14);		//�ż�2ȣ��
			arrBuyHoga[2] = realCommRecvData.GetItem(0, 16);		//�ż�3ȣ��
			arrBuyHoga[3] = realCommRecvData.GetItem(0, 18);		//�ż�4ȣ��
			arrBuyHoga[4] = realCommRecvData.GetItem(0, 20);		//�ż�5ȣ��

			arrBuyRemain[0] = realCommRecvData.GetItem(0, 37);	//�ż�1ȣ���ܷ�
			arrBuyRemain[1] = realCommRecvData.GetItem(0, 38);	//�ż�2ȣ���ܷ�
			arrBuyRemain[2] = realCommRecvData.GetItem(0, 39);	//�ż�3ȣ���ܷ�
			arrBuyRemain[3] = realCommRecvData.GetItem(0, 40);	//�ż�4ȣ���ܷ�
			arrBuyRemain[4] = realCommRecvData.GetItem(0, 41);	//�ż�5ȣ���ܷ�

			arrBuyCnt[0] = realCommRecvData.GetItem(0, 27);		//�ż�1ȣ���Ǽ�
			arrBuyCnt[1] = realCommRecvData.GetItem(0, 28);		//�ż�2ȣ���Ǽ�
			arrBuyCnt[2] = realCommRecvData.GetItem(0, 29);		//�ż�3ȣ���Ǽ�
			arrBuyCnt[3] = realCommRecvData.GetItem(0, 30);		//�ż�4ȣ���Ǽ�
			arrBuyCnt[4] = realCommRecvData.GetItem(0, 31);		//�ż�5ȣ���Ǽ�

#else		/*--------------------------------------
			������Ʈ ��Ʈ���� GetRealOutputData �Լ��� �����ۺ� �����͸� ������.
			---------------------------------------*/
			/*--------------------------------------
			�����۸����� ���ŵ� �ǽð� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			//�ŵ� 1~5ȣ��
			arrSellHoga[0] = m_CommAgent.GetRealOutputData(strRealName, "ASKP1");
			arrSellHoga[1] = m_CommAgent.GetRealOutputData(strRealName, "ASKP2");
			arrSellHoga[2] = m_CommAgent.GetRealOutputData(strRealName, "ASKP3");
			arrSellHoga[3] = m_CommAgent.GetRealOutputData(strRealName, "ASKP4");
			arrSellHoga[4] = m_CommAgent.GetRealOutputData(strRealName, "ASKP5");
			//�ŵ� 1~5ȣ���ܷ�
			arrSellRemain[0] = m_CommAgent.GetRealOutputData(strRealName, "ASKP_RSQN1");
			arrSellRemain[1] = m_CommAgent.GetRealOutputData(strRealName, "ASKP_RSQN2");
			arrSellRemain[2] = m_CommAgent.GetRealOutputData(strRealName, "ASKP_RSQN3");
			arrSellRemain[3] = m_CommAgent.GetRealOutputData(strRealName, "ASKP_RSQN4");
			arrSellRemain[4] = m_CommAgent.GetRealOutputData(strRealName, "ASKP_RSQN5");
			//�ŵ� 1~5ȣ���Ǽ�
			arrSellCnt[0] = m_CommAgent.GetRealOutputData(strRealName, "ASKP_CSNU1");
			arrSellCnt[1] = m_CommAgent.GetRealOutputData(strRealName, "ASKP_CSNU2");
			arrSellCnt[2] = m_CommAgent.GetRealOutputData(strRealName, "ASKP_CSNU3");
			arrSellCnt[3] = m_CommAgent.GetRealOutputData(strRealName, "ASKP_CSNU4");
			arrSellCnt[4] = m_CommAgent.GetRealOutputData(strRealName, "ASKP_CSNU5");

			//�ż� 1~5ȣ��
			arrBuyHoga[0] = m_CommAgent.GetRealOutputData(strRealName, "BIDP1");
			arrBuyHoga[1] = m_CommAgent.GetRealOutputData(strRealName, "BIDP2");
			arrBuyHoga[2] = m_CommAgent.GetRealOutputData(strRealName, "BIDP3");
			arrBuyHoga[3] = m_CommAgent.GetRealOutputData(strRealName, "BIDP4");
			arrBuyHoga[4] = m_CommAgent.GetRealOutputData(strRealName, "BIDP5");
			//�ż� 1~5ȣ���ܷ�
			arrBuyRemain[0] = m_CommAgent.GetRealOutputData(strRealName, "BIDP_RSQN1");
			arrBuyRemain[1] = m_CommAgent.GetRealOutputData(strRealName, "BIDP_RSQN2");
			arrBuyRemain[2] = m_CommAgent.GetRealOutputData(strRealName, "BIDP_RSQN3");
			arrBuyRemain[3] = m_CommAgent.GetRealOutputData(strRealName, "BIDP_RSQN4");
			arrBuyRemain[4] = m_CommAgent.GetRealOutputData(strRealName, "BIDP_RSQN5");
			//�ż� 1~5ȣ���Ǽ�
			arrBuyCnt[0] = m_CommAgent.GetRealOutputData(strRealName, "BIDP_CSNU1");
			arrBuyCnt[1] = m_CommAgent.GetRealOutputData(strRealName, "BIDP_CSNU2");
			arrBuyCnt[2] = m_CommAgent.GetRealOutputData(strRealName, "BIDP_CSNU3");
			arrBuyCnt[3] = m_CommAgent.GetRealOutputData(strRealName, "BIDP_CSNU4");
			arrBuyCnt[4] = m_CommAgent.GetRealOutputData(strRealName, "BIDP_CSNU5");
#endif
			SetHogaData(arrSellHoga, arrBuyHoga, arrSellRemain, arrBuyRemain, arrSellCnt, arrBuyCnt);
		}//End of if
	}
	/***************************************
	* Eurex�ɼ� ü��(���簡) �ǽð� ������ ����
	****************************************/
	else if (!_tcscmp(strRealName, "O30"))
	{
		/*--------------------------------------
		�����۸����� ���ŵ� �ǽð� �����͸� �׸񺰷� ������.
		---------------------------------------*/
		CString strCurPrice = m_CommAgent.GetRealOutputData(strRealName, "PRPR");			//���簡
		CString strDiffSign = m_CommAgent.GetRealOutputData(strRealName, "PRDY_VRSS_SIGN");	//��ȣ
		CString strDiff = m_CommAgent.GetRealOutputData(strRealName, "PRDY_VRSS");		//���ϴ��
		CString strDiffRate = m_CommAgent.GetRealOutputData(strRealName, "PRDY_CTRT");		//�����
		CString strVolume = m_CommAgent.GetRealOutputData(strRealName, "ACML_VOL");		//�ŷ���

		CString strOpenPrice = m_CommAgent.GetRealOutputData(strRealName, "OPRC");			//�ð�
		CString strHighPrice = m_CommAgent.GetRealOutputData(strRealName, "HGPR");			//��
		CString strLowPrice = m_CommAgent.GetRealOutputData(strRealName, "LWPR");			//����

		CString strTime = m_CommAgent.GetRealOutputData(strRealName, "BSOP_HOUR");		//ü��ð�
		CString strExecVolume = m_CommAgent.GetRealOutputData(strRealName, "CNTG_VOL");		//ü�ᷮ

		strCurPrice.Trim();
		strDiffSign.Trim();
		strDiff.Trim();
		strDiffRate.Trim();
		strVolume.Trim();

		strOpenPrice.Trim();
		strHighPrice.Trim();
		strLowPrice.Trim();

		strTime.Trim();
		strExecVolume.Trim();

		/*--------------------------------------
		��ȸ ������ ����� Eurex�ɼ� ���簡 �ǽð�Ű�� �������� ��
		---------------------------------------*/
		if (m_strCurPriceRealKey == strRealKey)
		{
			GetDlgItem(IDC_CUR_PRICE)->SetWindowText(strCurPrice);
			GetDlgItem(IDC_DIFF)->SetWindowText(GetDiffSign(strDiffSign));
			GetDlgItem(IDC_DIFF_SIGN)->SetWindowText(strDiff);
			GetDlgItem(IDC_DIFF_RATE)->SetWindowText(strDiffRate);
			GetDlgItem(IDC_VOLUME)->SetWindowText(strVolume);

			GetDlgItem(IDC_START_PRICE)->SetWindowText(strOpenPrice);
			GetDlgItem(IDC_HIGH_PRICE)->SetWindowText(strHighPrice);
			GetDlgItem(IDC_LOW_PRICE)->SetWindowText(strLowPrice);
		}

		/*--------------------------------------
		��ȸ ������ ����� Eurex�ɼ� �ð��뺰 ü�� �ǽð�Ű�� �������� ��
		---------------------------------------*/
		if (m_strTickRealKey == strRealKey)
		{
			m_listTick.SetRedraw(FALSE);


			int nListRowCnt = m_listTick.GetItemCount();

			//������ 500���� ������ 100�Ǹ� ����� �����.
			if (nListRowCnt > 500)
			{
				for (int i = 100; i < 500; i++)
					m_listTick.DeleteItem(i);
			}

			LV_ITEM	lvItem;

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = 0;

			m_listTick.InsertItem(&lvItem);

			m_listTick.SetItemText(0, 0, (LPTSTR)(LPCTSTR)strTime);			//�ð�
			m_listTick.SetItemText(0, 1, (LPTSTR)(LPCTSTR)strCurPrice);		//ü�ᰡ
			m_listTick.SetItemText(0, 2, (LPTSTR)(LPCTSTR)strDiff);			//���
			m_listTick.SetItemText(0, 3, (LPTSTR)(LPCTSTR)strDiffRate);		//���
			m_listTick.SetItemText(0, 4, (LPTSTR)(LPCTSTR)strExecVolume);	//ü�ᷮ

			m_listTick.SetRedraw(TRUE);

		}//End of if

	}//End of if
}
