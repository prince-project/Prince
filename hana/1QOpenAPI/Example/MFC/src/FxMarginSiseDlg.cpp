/*----------------------------------------*
| ���α׷��� : �ϳ��������� Open API ����
| ��      �� : v 
| ����  ���� :
| ��      Ÿ :
*----------------------------------------*/
// FxMarginSiseDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "HFCommClient.h"
#include "FxMarginSiseDlg.h"

#define ID_SECOND_TIMER		100	//1�� ���� Ÿ�̸�

#define SELL_BK_COLOR		RGB(206, 232, 255)	//�ŵ� ����
#define BUY_BK_COLOR		RGB(251, 221, 255)	//�ż� ����

//��� ����ü ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

// CFxMarginSiseDlg ��ȭ ����
CFxMarginSiseDlg::CFxMarginSiseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFxMarginSiseDlg::IDD, pParent)
{
	m_bCommConnect = FALSE;
	m_nRqIdCurPrice = 0;
	m_nRqIdTick = 0;
	m_nRqIdCodeList = 0;
	m_nRqIdChart = 0;

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nSeverType = 0;	//0-����, 1-��������, 2-�ؿܹ���
}

void CFxMarginSiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, m_editUserID);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDC_EDIT_AUTH_PWD, m_editAuthPwd);
	DDX_Text(pDX, IDC_EDIT_ID, m_strLoginID);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strLoginPwd);
	DDX_Text(pDX, IDC_EDIT_AUTH_PWD, m_strCertPwd);
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

BEGIN_MESSAGE_MAP(CFxMarginSiseDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_LOGIN, &CFxMarginSiseDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_LOGOUT, &CFxMarginSiseDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_INITCOMM, &CFxMarginSiseDlg::OnBnClickedInitcomm)
	ON_BN_CLICKED(IDC_TERMINATE, &CFxMarginSiseDlg::OnBnClickedTerminate)
	ON_BN_CLICKED(IDC_BTN_REQ_PRICE, &CFxMarginSiseDlg::OnBnClickedBtnReqPrice)
	ON_BN_CLICKED(IDC_BTN_REQ_TICK, &CFxMarginSiseDlg::OnBnClickedBtnReqTick)
	ON_BN_CLICKED(IDC_BTN_REQ_TICK_NEXT, &CFxMarginSiseDlg::OnBnClickedBtnReqTickNext)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE_LIST, &CFxMarginSiseDlg::OnBnClickedBtnReqCodeList)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE_LIST_NEXT, &CFxMarginSiseDlg::OnBnClickedBtnReqCodeListNext)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SYMBOL, &CFxMarginSiseDlg::OnNMDblclkListSymbol)
	ON_BN_CLICKED(IDOK, &CFxMarginSiseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_REQ_CHART, &CFxMarginSiseDlg::OnBnClickedBtnReqChart)
	ON_BN_CLICKED(IDC_BTN_REQ_CHART_NEXT, &CFxMarginSiseDlg::OnBnClickedBtnReqChartNext)
	ON_COMMAND_RANGE(IDC_RADIO_TICK, IDC_RADIO_MON, &CFxMarginSiseDlg::OnRadioChartTerm)
	ON_COMMAND_RANGE(IDC_CON_REAL, IDC_CON_F_DEMO, &CFxMarginSiseDlg::OnRdoSelectServer)
END_MESSAGE_MAP()

// agent�κ��� �̺�Ʈ ���� �Լ��� �����Ѵ�.
BEGIN_EVENTSINK_MAP(CFxMarginSiseDlg, CDialog)
	ON_EVENT(CFxMarginSiseDlg, IDC_HFCOMMAGENTCTRL1, 1, CFxMarginSiseDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CFxMarginSiseDlg, IDC_HFCOMMAGENTCTRL1, 2, CFxMarginSiseDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CFxMarginSiseDlg, IDC_HFCOMMAGENTCTRL1, 3, CFxMarginSiseDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
	ON_EVENT(CFxMarginSiseDlg, IDC_HFCOMMAGENTCTRL1, 4, CFxMarginSiseDlg::OnAgentEventHandler, VTS_I4 VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

// CFxMarginSiseDlg �޽��� ó����

void CFxMarginSiseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CFxMarginSiseDlg::OnPaint()
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

void CFxMarginSiseDlg::OnRdoSelectServer(UINT nID)
{
	m_nSeverType = nID - IDC_CON_REAL;

	/*----------------------------------
	���Ӽ����� �����Ѵ�.(0 - ����, 1 - ��������, 2 - �ؿܸ���)
	*----------------------------------*/
	m_CommAgent.SetLoginMode(0, m_nSeverType);
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CFxMarginSiseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CFxMarginSiseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CFxMarginSiseDlg::OnDestroy()
{
	//��� �ǽð������ �����Ѵ�.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();

	CDialog::OnDestroy();
}

void CFxMarginSiseDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CFxMarginSiseDlg::OnTimer(UINT_PTR nIDEvent)
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

void CFxMarginSiseDlg::OnNMDblclkListSymbol(NMHDR *pNMHDR, LRESULT *pResult)
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
	m_editSymbolPrice.SetWindowText(strSymbol);	//���簡 �����ڵ�(�ɺ�)
	m_editSymbolTick.SetWindowText(strSymbol);	//�ð��뺰ü�� �����ڵ�(�ɺ�)
	m_editSymbolChart.SetWindowText(strSymbol);	//��Ʈ �����ڵ�(�ɺ�)

	GetDlgItem(IDC_SYMBOL_NAME_PRICE)->SetWindowText(strSymbolName);//���簡 �����
	GetDlgItem(IDC_SYMBOL_NAME_TICK)->SetWindowText(strSymbolName);	//�ð��뺰ü�� �����
	GetDlgItem(IDC_SYMBOL_NAME_CHART)->SetWindowText(strSymbolName);//��Ʈ ������ �����

	//�Էµ� �����ڵ�� ����ȸ ��û�� �Ѵ�.
	OnBnClickedBtnReqPrice();	//FX���� ���簡 ��ȸ
	OnBnClickedBtnReqTick();	//FX���� �ð��뺰ü�� ��ȸ
	OnBnClickedBtnReqChart();	//FX���� ��Ʈ������ ��ȸ
}

void CFxMarginSiseDlg::OnRadioChartTerm(UINT nID)
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
BOOL CFxMarginSiseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CString strTitle;
	strTitle.Format("%s-[FX���� �ü�](%s)", PROGRAM_NAME, VERSION_INFO);
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
	* FX���� �ð��뺰ü�ᰡ ����Ʈ ��Ʈ�� �ʱ�ȭ
	**********************************/
	InitListTick();

	/**********************************
	* FX���� ���� ����Ʈ ��Ʈ�� �ʱ�ȭ
	**********************************/
	InitListCode();

	/**********************************
	* FX���� ��Ʈ ����Ʈ ��Ʈ�� �ʱ�ȭ
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
	//FX����ü�� �ǽð� I/O ���� ���ҽ� ����
	if (!m_CommAgent.LoadRealResource(strApidAgentModulePath + "/RealRes/V00.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
#endif

	//��Ʈ FX���� ���� ƽ���� ����
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
// Function Name : InitListTick
// Function      : FX���� �ð��뺰ü�� ����Ʈ ��Ʈ�� �ʱ�ȭ
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::InitListTick()
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
	TCHAR *strTitle[] = { _T("��ýð�"), _T("�ŵ�"), _T("�ż�"), _T("��������"), _T("PIP��ġ") };

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
// Function      : FX���� ���� ����Ʈ ��Ʈ�� �ʱ�ȭ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::InitListCode()
{
	m_listCode.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int arrWidth[17] = { 0x00 };

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("HTS CODE"), _T("1171 - ��ȭ 1"), _T("��ȭ 2"), _T("Quote Mode"),
		_T("���ݼҼ���"), _T("���ݼҼ�������"), _T("���Ҽ���"), _T("���Ҽ�������"), _T("�������ڵ�"),
		_T("PL�����ȭ"), _T("PL�����"), _T("Pair ID FCM_CD"), _T("FX ��ǰ��"), _T("���� ������"),
		_T("�ŵ� ������"), _T("FDM ���� ������"), _T("FDM �ŵ� ������") };


	int i;
	CDC* pDC = GetDC();
	CSize size;

	for (i = 0; i < 17; i++)
	{
		size = pDC->GetTextExtent(strTitle[i]);
		arrWidth[i] = size.cx;
	}

	for (i = 0; i < 17; i++)
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
void CFxMarginSiseDlg::InitListChart()
{
	
	int arrWidth[13] = { 0x00 };
	m_listCode.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("�ð�"), _T("����"), _T("�ŵ��ð�"), _T("�ŵ���"), _T("�ŵ�����"),
		_T("�ŵ�����"), _T("����ȣ"), _T("�ż��ð�"), _T("�ż���"), _T("�ż�����"), _T("�ż�����"),
		_T("�ŵ���ȣ"), _T("��������") };

	int i;
	CDC* pDC = GetDC();
	CSize size;

	for (i = 0; i < 13; i++)
	{
		size = pDC->GetTextExtent(strTitle[i]);
		arrWidth[i] = size.cx;
	}
	
	for (i = 0; i < 13; i++)
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
CString CFxMarginSiseDlg::GetDiffSign(CString strSignCode)
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
// Function Name : OnBnClickedInitcomm
// Function      : ��Ÿ�� �ʱ�ȭ �� ��� ����
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedInitcomm()
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
void CFxMarginSiseDlg::OnBnClickedTerminate()
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
void CFxMarginSiseDlg::OnBnClickedLogin()
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
void CFxMarginSiseDlg::OnBnClickedLogout()
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
// Function      : FX���� ���� ����Ʈ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedBtnReqCodeList()
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

	//FX���� ���� ����Ʈ(������) ��Ʈ�� ������ �ʱ�ȭ
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
	strMarketCode = _T("FX");	//FX����

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("4199"));		//GID

	//�������� �������� ����׸��.
	CString strOutputFidList;

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	2609 - HTS CODE
	1171 - ��ȭ 1
	1268 - ��ȭ 2
	2617 - Quote Mode
	2456 - ���ݼҼ���
	2618 - ���ݼҼ�������
	2619 - ���Ҽ���
	2620 - ���Ҽ�������
	2621 - �������ڵ�
	2622 - PL�����ȭ
	2623 - PL�����
	0306 - Pair ID FCM_CD
	0003 - FX ��ǰ��
	1222 - ���� ������
	1223 - �ŵ� ������
	1220 - FDM ���� ������
	1221 - FDM �ŵ� ������
 */
	strOutputFidList = "2609,1171,1268,2617,2456,2618,2619,2620,2621,2622,"
						"2623,306,3,1222,1223,1220,1221";

	CString strScreenNo;
	strScreenNo = "9999";

	//������ȸ �ɼ� : '0':�̻��, '1'���, '2' : ���� ������ ��ȸ, '3' : ���� ������ ��ȸ
	CString strPreNext = "1";

	/**********************************
	* 5. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, "", strScreenNo, 0);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqCodeListNext
// Function      : FX���� ���� ����Ʈ ���� ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedBtnReqCodeListNext()
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

	CString strSymBol;			//����ɺ��ڵ�
	CString strMarketCode;		//���屸���ڵ�

	m_editSymbolTick.GetWindowText(strSymBol); //�����ڵ�
	strMarketCode = _T("FX"); //FX����

	/**********************************
	* 2. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("4199"));		//GID

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 3. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	2609 - HTS CODE
	1171 - ��ȭ 1
	1268 - ��ȭ 2
	2617 - Quote Mode
	2456 - ���ݼҼ���
	2618 - ���ݼҼ�������
	2619 - ���Ҽ���
	2620 - ���Ҽ�������
	2621 - �������ڵ�
	2622 - PL�����ȭ
	2623 - PL�����
	0306 - Pair ID FCM_CD
	0003 - FX ��ǰ��
	1222 - ���� ������
	1223 - �ŵ� ������
	1220 - FDM ���� ������
	1221 - FDM �ŵ� ������
	*/
	strOutputFidList = "2609,1171,1268,2617,2456,2618,2619,2620,2621,2622,"
		"2623,306,3,1222,1223,1220,1221";


	CString strScreenNo;
	strScreenNo = "9999";

	CString strPreNext = "3"; //���� ������ ��ȸ

	/**********************************
	* 4. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, m_strCodeListNextRqKey, strScreenNo, 0);
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
void CFxMarginSiseDlg::OnBnClickedBtnReqPrice()
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
	* 2. ������ ��ϵ� FX����ü��(���簡) �ǽð���� ����.
	**********************************/
	if (!m_strCurPriceRealKey.IsEmpty())
	{
		CString strRealName;
		strRealName = _T("V00"); //FX����ü�� Real name

		m_CommAgent.UnRegisterReal(strRealName, m_strCurPriceRealKey);
		m_strCurPriceRealKey.Empty();
	}

	CString strMarketCode;		//���屸��
	strMarketCode = _T("FX");	//FX����

	//FX����ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
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
	�ŵ�(29), �ż�(39), ��������(666), PIP ��ġ(2468), ��(14), ����(15), ����(S)(1220), ����(B)(1221)*/
	strOutputFidList = "29,39,666,2468,14,15,1220,1221";

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
// Function Name : OnBnClickedBtnReqTick
// Function      : FX���� �ð��뺰ü�� ������ ��ȸ(���Ӱŷ� �����Ͱ� �ִ� ���)
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedBtnReqTick()
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

	//FX���� �ð��뺰ü�� ����Ʈ ��Ʈ�� ������ �ʱ�ȭ
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
	* 3. ������ ��ϵ� FX����ü��(���簡) �ǽð���� ����.
	**********************************/
	if (!m_strTickRealKey.IsEmpty())
	{
		CString strRealName;
		strRealName = _T("V00");

		m_CommAgent.UnRegisterReal(strRealName, m_strTickRealKey);
		m_strTickRealKey.Empty();
	}

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("FX");

	//FX����ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
	m_strTickRealKey = strSymBol;

	/**********************************
	 * 4. �����ȸ ��û �Էµ�����
	 **********************************/
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9002"), strSymBol);		//����ɺ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9018"), "1");				//�Է±�������
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9119"), "");				//�Էº�ƽ
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("GID"), _T("1003"));		//GID

	//�������� �������� ����׸��.
	CString strOutputFidList;

	/**********************************
	 * 5. �����ȸ �������� ���� �׸� ����.
	 **********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	��ýð�(8), �ŵ�(29), �ż�(39), ��������(666), PIP��ġ(2468)*/
	strOutputFidList = "8,29,39,666,2468";

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
// Function      : FX���� �ð��뺰ü�� ���� ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedBtnReqTickNext()
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
	strMarketCode = _T("F"); //FX����

	/**********************************
	* 2. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9002"), strSymBol);		//����ɺ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9018"), "1");				//�Է±�������
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9119"), "");				//�Էº�ƽ
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("GID"), _T("1003"));		//GID

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 3. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	��ýð�(8), �ŵ�(29), �ż�(39), ��������(666), PIP��ġ(2468)*/
	strOutputFidList = "8,29,39,666,2468";

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
// Function      : FX���� ��Ʈ ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedBtnReqChart()
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

	//FX���� �ð��뺰ü�� ����Ʈ ��Ʈ�� ������ �ʱ�ȭ
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
	strMarketCode = _T("FX");

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

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1003")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MIN))->GetCheck()) //��
	{
		CString strMin;
		strMin.Format(_T("%d"), _ttoi(strChartCnt) * 60);

		//9119 : �����ڵ�( 30: 30��, 60: 1��, 600: 10��, 3600: 60��, 60*N: N�� )
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strMin);

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1006")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_DAY))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1008")); //GID

	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_WEEK))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "W");				//��(W), ��(M)

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1009")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MON))->GetCheck()) //��
	{

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "M");				//��(W), ��(M)

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1010")); //GID
	}

	//�������� �������� ����׸��.
	CString strOutputFidList;

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	0008 - �ð�
	0009 - ����
	0030 - �ŵ��ð�
	0031 - �ŵ���
	0032 - �ŵ�����
	0033 - �ŵ�����
	0006 - ���ϴ���ȣ(�����ʵ�� : �ż� ��ȣ)
	0040 - �ż��ð�
	0041 - �ż���
	0042 - �ż�����
	0043 - �ż�����
	1098 - �ŵ���ȣ
	0666 - ��������*/
	strOutputFidList = "8,9,30,31,32,33,6,40,41,42,43,1098,666";

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
// Function      : FX���� ��Ʈ ���� ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedBtnReqChartNext()
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
	strMarketCode = _T("F"); //FX����

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

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1003")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MIN))->GetCheck()) //��
	{
		CString strMin;
		strMin.Format(_T("%d"), _ttoi(strChartCnt) * 60);

		//9119 : �����ڵ�( 30: 30��, 60: 1��, 600: 10��, 3600: 60��, 60*N: N�� )
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strMin);

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1006")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_DAY))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1008")); //GID

	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_WEEK))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "W");				//��(W), ��(M)

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1009")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MON))->GetCheck()) //��
	{

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "M");				//��(W), ��(M)

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1010")); //GID
	}

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 3. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	0008 - �ð�
	0009 - ����
	0030 - �ŵ��ð�
	0031 - �ŵ���
	0032 - �ŵ�����
	0033 - �ŵ�����
	0006 - ���ϴ���ȣ(�����ʵ�� : �ż� ��ȣ)
	0040 - �ż��ð�
	0041 - �ż���
	0042 - �ż�����
	0043 - �ż�����
	1098 - �ŵ���ȣ
	0666 - ��������*/
	strOutputFidList = "8,9,30,31,32,33,6,40,41,42,43,1098,666";

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

void CFxMarginSiseDlg::OnBnClickedOk()
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
void CFxMarginSiseDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
void CFxMarginSiseDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
	* FX���� ���� ����Ʈ(������) ��ȸ ������ ���� ó��
	****************************************/
	if (m_nRqIdCodeList == nRequestId)
	{
		CString strCode;			//�����ڵ�
		CString strStandardCode;	//ǥ���ڵ�
		CString strCodeName;		//�ѱ������
		CString strPrice;			//���ذ�

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

		CString arrItemValue[17];

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			arrItemValue[0] = m_CommAgent.GetFidOutputData(nRequestId, "2609", i);		//HTS CODE
			arrItemValue[1] = m_CommAgent.GetFidOutputData(nRequestId, "1171", i);		//��ȭ 1
			arrItemValue[2] = m_CommAgent.GetFidOutputData(nRequestId, "1268", i);		//��ȭ 2
			arrItemValue[3] = m_CommAgent.GetFidOutputData(nRequestId, "2617", i);		//Quote Mode
			arrItemValue[4] = m_CommAgent.GetFidOutputData(nRequestId, "2456", i);		//���ݼҼ���
			arrItemValue[5] = m_CommAgent.GetFidOutputData(nRequestId, "2618", i);		//���ݼҼ�������
			arrItemValue[6] = m_CommAgent.GetFidOutputData(nRequestId, "2619", i);		//���Ҽ���
			arrItemValue[7] = m_CommAgent.GetFidOutputData(nRequestId, "2620", i);		//���Ҽ�������
			arrItemValue[8] = m_CommAgent.GetFidOutputData(nRequestId, "2621", i);		//�������ڵ�
			arrItemValue[9] = m_CommAgent.GetFidOutputData(nRequestId, "2622", i);		//PL�����ȭ
			arrItemValue[10] = m_CommAgent.GetFidOutputData(nRequestId, "2623", i);		//PL�����
			arrItemValue[11] = m_CommAgent.GetFidOutputData(nRequestId, "306", i);		//Pair ID FCM_CD
			arrItemValue[12] = m_CommAgent.GetFidOutputData(nRequestId, "3", i);		//FX ��ǰ��
			arrItemValue[13] = m_CommAgent.GetFidOutputData(nRequestId, "1222", i);		//���� ������
			arrItemValue[14] = m_CommAgent.GetFidOutputData(nRequestId, "1223", i);		//�ŵ� ������
			arrItemValue[15] = m_CommAgent.GetFidOutputData(nRequestId, "1220", i);		//FDM ���� ������
			arrItemValue[16] = m_CommAgent.GetFidOutputData(nRequestId, "1221", i);		//FDM �ŵ� ������

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listCode.InsertItem(&lvItem);

			//����Ʈ ��Ʈ�ѿ� �� �Է�
			for (int col = 0; col < 17; col++)
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
		m_nRqIdCodeList = 0;	//FX���� ���� ����Ʈ(������) ��ȸ Request ID
	}
	/***************************************
	* FX���� ���簡 ��ȸ ������ ���� ó��
	****************************************/
	else if (m_nRqIdCurPrice == nRequestId)
	{
		/*--------------------------------------
		FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
		---------------------------------------*/
		CString strSellPrice = m_CommAgent.GetFidOutputData(nRequestId, "29", 0);		//�ŵ�(29)
		CString strBuyPrice = m_CommAgent.GetFidOutputData(nRequestId, "39", 0);		//�ż�(39)
		CString strSpread = m_CommAgent.GetFidOutputData(nRequestId, "666", 0);			//��������(666)
		CString strPipCost = m_CommAgent.GetFidOutputData(nRequestId, "2468", 0);		//PIP ��ġ(2468)
		CString strHighPrice = m_CommAgent.GetFidOutputData(nRequestId, "14", 0);		//��(14)
		CString strLowPrice = m_CommAgent.GetFidOutputData(nRequestId, "15", 0);		//����(15)
		CString strSellInst = m_CommAgent.GetFidOutputData(nRequestId, "1220", 0);		//����(S)(1220)
		CString strBuyInst = m_CommAgent.GetFidOutputData(nRequestId, "1221", 0);		//����(B)(1221)

		GetDlgItem(IDC_CUR_SELL)->SetWindowText(strSellPrice);
		GetDlgItem(IDC_CUR_BUY)->SetWindowText(strBuyPrice);
		GetDlgItem(IDC_SPREAD)->SetWindowText(strSpread);
		GetDlgItem(IDC_PIP_COST)->SetWindowText(strPipCost);
		GetDlgItem(IDC_HIGH_PRICE)->SetWindowText(strHighPrice);
		GetDlgItem(IDC_LOW_PRICE)->SetWindowText(strLowPrice);
		GetDlgItem(IDC_SELL_INST)->SetWindowText(strSellInst);
		GetDlgItem(IDC_BUY_INST)->SetWindowText(strBuyInst);

		/*--------------------------------------
		������ ü��(���簡) �ǽð����Ű�� �ǽð��� ����Ѵ�.
		�ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		---------------------------------------*/
		if (!m_strCurPriceRealKey.IsEmpty())
		{
			CString strRealName;
			strRealName = _T("V00");

			m_CommAgent.RegisterReal(strRealName, m_strCurPriceRealKey); //�ǽð� ���
		}

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdCurPrice = 0;	//FX���� ���簡 ��ȸ Request ID
	}
	/***************************************
	* FX���� �ð��뺰ü�� ��ȸ ������ ���� ó��
	****************************************/
	else if (m_nRqIdTick == nRequestId)
	{
		CString strTime;		//��ýð�
		CString strSellPrice;	//�ŵ�
		CString strBuyPrice;	//�ż�
		CString strSpread;		//��������
		CString strPipCost;		//PIP��ġ

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
			//��ýð�(8), �ŵ�(29), �ż�(39), ��������(666), PIP��ġ(2468)
			strTime			= m_CommAgent.GetFidOutputData(nRequestId, "8", i);		//��ýð�
			strSellPrice	= m_CommAgent.GetFidOutputData(nRequestId, "29", i);	//�ŵ�
			strBuyPrice		= m_CommAgent.GetFidOutputData(nRequestId, "39", i);	//�ż�
			strSpread		= m_CommAgent.GetFidOutputData(nRequestId, "666", i);	//��������
			strPipCost		= m_CommAgent.GetFidOutputData(nRequestId, "2468", i);	//PIP��ġ

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listTick.InsertItem(&lvItem);

			m_listTick.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strTime);		//��ýð�
			m_listTick.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strSellPrice);	//�ŵ�
			m_listTick.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strBuyPrice);	//�ż�
			m_listTick.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strSpread);		//��������
			m_listTick.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strPipCost);		//PIP��ġ
		}

		m_listTick.EnsureVisible(nViewScrollPos, FALSE);
		m_listTick.SetRedraw(TRUE);

		/*--------------------------------------
		����ü�� �ǽð��� ����Ѵ�.
		�ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		---------------------------------------*/
		if (!m_strTickRealKey.IsEmpty() && m_strTickNextRqKey.IsEmpty())
		{
			CString strRealName;
			strRealName = _T("V00");

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
		m_nRqIdTick = 0;	//FX���� �ð��뺰ü�� ��ȸ Request ID

	}
	/***************************************
	* FX���� ��Ʈ ��ȸ ������ ���� ó��
	****************************************/
	else if (m_nRqIdChart == nRequestId)
	{
		CString arrItem[13];

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

		CCommRecvData fidCommRecvData;
		int nVecRowCnt = 0;	//������ �Ǽ�(��)
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
			FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			arrItem[0] = fidCommRecvData.GetItem(i, 0);	//�ð�
			arrItem[1] = fidCommRecvData.GetItem(i, 1);	//����
			arrItem[2] = fidCommRecvData.GetItem(i, 2);	//�ŵ��ð�
			arrItem[3] = fidCommRecvData.GetItem(i, 3);	//�ŵ���
			arrItem[4] = fidCommRecvData.GetItem(i, 4);	//�ŵ�����
			arrItem[5] = fidCommRecvData.GetItem(i, 5);	//�ŵ�����
			arrItem[6] = fidCommRecvData.GetItem(i, 6);	//���ϴ���ȣ(�����ʵ�� : �ż� ��ȣ)
			arrItem[7] = fidCommRecvData.GetItem(i, 7);	//�ż��ð�
			arrItem[8] = fidCommRecvData.GetItem(i, 8);	//�ż���
			arrItem[9] = fidCommRecvData.GetItem(i, 9);	//�ż�����
			arrItem[10] = fidCommRecvData.GetItem(i, 10);	//�ż�����
			arrItem[11] = fidCommRecvData.GetItem(i, 11);	//�ŵ���ȣ
			arrItem[12] = fidCommRecvData.GetItem(i, 12);	//��������

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listChart.InsertItem(&lvItem);

			//����Ʈ ��Ʈ�ѿ� �׸� ����Ÿ �Է�
			for (int col = 0; col < 13; col++)
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
			arrItem[0] = m_CommAgent.GetFidOutputData(nRequestId, "8", i);	//�ð�
			arrItem[1] = m_CommAgent.GetFidOutputData(nRequestId, "9", i);	//����
			arrItem[2] = m_CommAgent.GetFidOutputData(nRequestId, "30", i);	//�ŵ��ð�
			arrItem[3] = m_CommAgent.GetFidOutputData(nRequestId, "31", i);	//�ŵ���
			arrItem[4] = m_CommAgent.GetFidOutputData(nRequestId, "32", i);	//�ŵ�����
			arrItem[5] = m_CommAgent.GetFidOutputData(nRequestId, "33", i);	//�ŵ�����
			arrItem[6] = m_CommAgent.GetFidOutputData(nRequestId, "6", i);	//���ϴ���ȣ(�����ʵ�� : �ż� ��ȣ)
			arrItem[7] = m_CommAgent.GetFidOutputData(nRequestId, "40", i);	//�ż��ð�
			arrItem[8] = m_CommAgent.GetFidOutputData(nRequestId, "41", i);	//�ż���
			arrItem[9] = m_CommAgent.GetFidOutputData(nRequestId, "42", i);	//�ż�����
			arrItem[10] = m_CommAgent.GetFidOutputData(nRequestId, "43", i);	//�ż�����
			arrItem[11] = m_CommAgent.GetFidOutputData(nRequestId, "1098", i);	//�ŵ���ȣ
			arrItem[12] = m_CommAgent.GetFidOutputData(nRequestId, "666", i);	//��������

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listChart.InsertItem(&lvItem);

			//����Ʈ ��Ʈ�ѿ� �׸� ����Ÿ �Է�
			for (int col = 0; col < 13; col++)
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
		m_nRqIdChart = 0;	//FX���� ���� ����Ʈ(������) ��ȸ Request ID

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
void CFxMarginSiseDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/* ���� : OnGetRealData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
	�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/

	/***************************************
	* FX���� ü��(���簡) �ǽð� ������ ����
	****************************************/
	if (!_tcscmp(strRealName, "V00"))
	{
		CCommRecvData realCommRecvData;
		int nItemCnt = 0;		//�׸� �Ǽ�

		/*--------------------------------------
		�����۸����� ���ŵ� �ǽð� �����͸� �׸񺰷� ������.
		---------------------------------------*/
#if 1
		//FID ��ȸ���� ������ �޸𸮸� ���´�.(C++������ ��� ����)
		if (m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData) == TRUE)
			nItemCnt = realCommRecvData.GetColCnt();		//�׸� �Ǽ�

		CString strSCRN_INDC_PRDT_CD	= realCommRecvData.GetItem(0, 0);	//FX ����(HTS)
		CString strQUOTE_IDX			= realCommRecvData.GetItem(0, 1);	//Quote ����
		CString strFCM_CD				= realCommRecvData.GetItem(0, 2);	//FCM Code
		CString strFCM_DT				= realCommRecvData.GetItem(0, 3);	//FCM Quote ��
		CString strFCM_TM				= realCommRecvData.GetItem(0, 4);	//FCM Quote �ð�
		CString strSPOT_RATE			= realCommRecvData.GetItem(0, 5);	//Spot rate
		CString strDH_RATE_BUY			= realCommRecvData.GetItem(0, 6);	//Buy
		CString strDH_RATE_SELL			= realCommRecvData.GetItem(0, 8);	//Sell
		CString strDH_RATE_HIGH			= realCommRecvData.GetItem(0, 10);	//High
		CString strDH_RATE_LOW			= realCommRecvData.GetItem(0, 11);	//Low
		CString strDH_SPRD				= realCommRecvData.GetItem(0, 12);	//Spread
		CString strDH_PIP_BUY			= realCommRecvData.GetItem(0, 14);	//PIP Cost Buy
		CString strDH_PIP_SELL			= realCommRecvData.GetItem(0, 15);	//PIP Cost Sell
		CString strDH_PIP_MID			= realCommRecvData.GetItem(0, 16);	//PIP Cost Mid
		CString strDH_BUY_IR			= realCommRecvData.GetItem(0, 17);	//Buy IR
		CString strDH_SELL_IR			= realCommRecvData.GetItem(0, 18);	//Sell IR
		CString strDH_BUY_OPEN			= realCommRecvData.GetItem(0, 19);	//Buy Open
		CString strDH_BUY_HIGH			= realCommRecvData.GetItem(0, 20);	//Buy High
		CString strDH_BUY_LOW			= realCommRecvData.GetItem(0, 21);	//Buy Low
		CString strDH_SELL_OPEN			= realCommRecvData.GetItem(0, 22);	//Sell Open
		CString strDH_SELL_HIGH			= realCommRecvData.GetItem(0, 23);	//Sell High
		CString strDH_SELL_LOW			= realCommRecvData.GetItem(0, 24);	//Sell Low
#else
		CString strSCRN_INDC_PRDT_CD = m_CommAgent.GetRealOutputData(strRealName, "SCRN_INDC_PRDT_CD");		//FX ����(HTS)
		CString strQUOTE_IDX = m_CommAgent.GetRealOutputData(strRealName, "QUOTE_IDX");		//Quote ����
		CString strFCM_CD = m_CommAgent.GetRealOutputData(strRealName, "FCM_CD");		//FCM Code
		CString strFCM_DT = m_CommAgent.GetRealOutputData(strRealName, "FCM_DT");		//FCM Quote ��
		CString strFCM_TM = m_CommAgent.GetRealOutputData(strRealName, "FCM_TM");		//FCM Quote �ð�
		CString strSPOT_RATE = m_CommAgent.GetRealOutputData(strRealName, "SPOT_RATE");		//Spot rate
		CString strDH_RATE_BUY = m_CommAgent.GetRealOutputData(strRealName, "DH_RATE_BUY");		//Buy
		CString strDH_RATE_SELL = m_CommAgent.GetRealOutputData(strRealName, "DH_RATE_SELL");		//Sell
		CString strDH_RATE_HIGH = m_CommAgent.GetRealOutputData(strRealName, "DH_RATE_HIGH");		//High
		CString strDH_RATE_LOW = m_CommAgent.GetRealOutputData(strRealName, "DH_RATE_LOW");		//Low
		CString strDH_SPRD = m_CommAgent.GetRealOutputData(strRealName, "DH_SPRD");		//Spread
		CString strDH_PIP_BUY = m_CommAgent.GetRealOutputData(strRealName, "DH_PIP_BUY");		//PIP Cost Buy
		CString strDH_PIP_SELL = m_CommAgent.GetRealOutputData(strRealName, "DH_PIP_SELL");		//PIP Cost Sell
		CString strDH_PIP_MID = m_CommAgent.GetRealOutputData(strRealName, "DH_PIP_MID");		//PIP Cost Mid
		CString strDH_BUY_IR = m_CommAgent.GetRealOutputData(strRealName, "DH_BUY_IR");		//Buy IR
		CString strDH_SELL_IR = m_CommAgent.GetRealOutputData(strRealName, "DH_SELL_IR");		//Sell IR
		CString strDH_BUY_OPEN = m_CommAgent.GetRealOutputData(strRealName, "DH_BUY_OPEN");		//Buy Open
		CString strDH_BUY_HIGH = m_CommAgent.GetRealOutputData(strRealName, "DH_BUY_HIGH");		//Buy High
		CString strDH_BUY_LOW = m_CommAgent.GetRealOutputData(strRealName, "DH_BUY_LOW");		//Buy Low
		CString strDH_SELL_OPEN = m_CommAgent.GetRealOutputData(strRealName, "DH_SELL_OPEN");		//Sell Open
		CString strDH_SELL_HIGH = m_CommAgent.GetRealOutputData(strRealName, "DH_SELL_HIGH");		//Sell High
		CString strDH_SELL_LOW = m_CommAgent.GetRealOutputData(strRealName, "DH_SELL_LOW");		//Sell Low
#endif
		strSCRN_INDC_PRDT_CD.Trim();		strQUOTE_IDX.Trim();		strFCM_CD.Trim();
		strFCM_DT.Trim();					strFCM_TM.Trim();			strSPOT_RATE.Trim();
		strDH_RATE_BUY.Trim();				strDH_RATE_SELL.Trim();		strDH_RATE_HIGH.Trim();
		strDH_RATE_LOW.Trim();				strDH_SPRD.Trim();			strDH_PIP_BUY.Trim();
		strDH_PIP_SELL.Trim();				strDH_PIP_MID.Trim();		strDH_BUY_IR.Trim();
		strDH_SELL_IR.Trim();				strDH_BUY_OPEN.Trim();		strDH_BUY_HIGH.Trim();
		strDH_BUY_LOW.Trim();				strDH_SELL_OPEN.Trim();		strDH_SELL_HIGH.Trim();
		strDH_SELL_LOW.Trim();

		/*--------------------------------------
		��ȸ ������ ����� FX���� ���簡 �ǽð�Ű�� �������� ��
		---------------------------------------*/
		if (m_strCurPriceRealKey == strRealKey)
		{
			GetDlgItem(IDC_CUR_SELL)->SetWindowText(strDH_RATE_SELL);
			GetDlgItem(IDC_CUR_BUY)->SetWindowText(strDH_RATE_BUY);
			GetDlgItem(IDC_SPREAD)->SetWindowText(strDH_SPRD);
			GetDlgItem(IDC_PIP_COST)->SetWindowText(strDH_PIP_MID);
			GetDlgItem(IDC_HIGH_PRICE)->SetWindowText(strDH_RATE_HIGH);
			GetDlgItem(IDC_LOW_PRICE)->SetWindowText(strDH_RATE_LOW);
			GetDlgItem(IDC_SELL_INST)->SetWindowText(strDH_SELL_IR);
			GetDlgItem(IDC_BUY_INST)->SetWindowText(strDH_BUY_IR);
		}

		/*--------------------------------------
		��ȸ ������ ����� FX���� �ð��뺰 ü�� �ǽð�Ű�� �������� ��
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

			m_listTick.SetItemText(0, 0, (LPTSTR)(LPCTSTR)strFCM_TM);			//��ýð�
			m_listTick.SetItemText(0, 1, (LPTSTR)(LPCTSTR)strDH_RATE_SELL);		//�ŵ�
			m_listTick.SetItemText(0, 2, (LPTSTR)(LPCTSTR)strDH_RATE_BUY);		//�ż�
			m_listTick.SetItemText(0, 3, (LPTSTR)(LPCTSTR)strDH_SPRD);			//��������
			m_listTick.SetItemText(0, 4, (LPTSTR)(LPCTSTR)strDH_PIP_MID);		//PIP��ġ

			m_listTick.SetRedraw(TRUE);

		}//End of if

	}//End of if
}

//*******************************************************************
// Function Name : OnAgentEventHandler
// Function      : 
// Param         : long nEventType, long nParam, LPCTSTR strParam
// Return        : void 
// Create        : 2016/11/25
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnAgentEventHandler(long nEventType, long nParam, LPCTSTR strParam)
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
