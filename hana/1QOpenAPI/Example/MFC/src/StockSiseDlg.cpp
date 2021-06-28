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
#include "StockSiseDlg.h"

#define ID_SECOND_TIMER		100	//1�� ���� Ÿ�̸�

#define SELL_BK_COLOR		RGB(206, 232, 255)	//�ŵ� ����
#define BUY_BK_COLOR		RGB(251, 221, 255)	//�ż� ����

//��� ����ü ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

// CStockSiseDlg ��ȭ ����
CStockSiseDlg::CStockSiseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStockSiseDlg::IDD, pParent)
{
	m_bCommConnect = FALSE;
	m_nRqIdHoga = 0;
	m_nRqIdCurPrice = 0;
	m_nRqIdTick = 0;
	m_nRqIdCodeList = 0;
	m_nRqIdChart = 0;
	m_nRqIdPortfolio = 0;
	m_nRqIdCurRate = 0;
	m_nRqIdKospi = 0;
	m_nRqIdMem = 0;
	m_nSeverType = 0;

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nSeverType = 0;	//0-����, 1-��������, 2-�ؿܹ���
}

void CStockSiseDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_CHK_AUTO_REQ, m_chkAutoReq);
	DDX_Control(pDX, IDC_EDIT_SYMBOL_CHART, m_editSymbolChart);
	DDX_Control(pDX, IDC_CHK_AUTO_REQ_CHART, m_chkAutoReqChart);
	DDX_Control(pDX, IDC_LIST_CHART, m_listChart);
	DDX_Control(pDX, IDC_EDIT_CHART_CNT, m_editChartCnt);
	DDX_Control(pDX, IDC_DATETIME_FROM, m_dateTimeFrom);
	DDX_Control(pDX, IDC_DATETIME_TO, m_dateTimeTo);
	DDX_Control(pDX, IDC_LIST_PORTFOLIO, m_listPortfolio);
}

BEGIN_MESSAGE_MAP(CStockSiseDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_LOGIN, &CStockSiseDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_LOGOUT, &CStockSiseDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_INITCOMM, &CStockSiseDlg::OnBnClickedInitcomm)
	ON_BN_CLICKED(IDC_TERMINATE, &CStockSiseDlg::OnBnClickedTerminate)
	ON_BN_CLICKED(IDC_BTN_REQ_HOGA, &CStockSiseDlg::OnBnClickedBtnReqHoga)
	ON_BN_CLICKED(IDC_BTN_REQ_PRICE, &CStockSiseDlg::OnBnClickedBtnReqPrice)
	ON_BN_CLICKED(IDC_BTN_REQ_TICK, &CStockSiseDlg::OnBnClickedBtnReqTick)
	ON_BN_CLICKED(IDC_BTN_REQ_TICK_NEXT, &CStockSiseDlg::OnBnClickedBtnReqTickNext)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE_LIST, &CStockSiseDlg::OnBnClickedBtnReqCodeList)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE_LIST_NEXT, &CStockSiseDlg::OnBnClickedBtnReqCodeListNext)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SYMBOL, &CStockSiseDlg::OnNMDblclkListSymbol)
	ON_BN_CLICKED(IDOK, &CStockSiseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_REQ_CHART, &CStockSiseDlg::OnBnClickedBtnReqChart)
	ON_BN_CLICKED(IDC_BTN_REQ_CHART_NEXT, &CStockSiseDlg::OnBnClickedBtnReqChartNext)
	ON_COMMAND_RANGE(IDC_RADIO_TICK, IDC_RADIO_MON, &CStockSiseDlg::OnRadioChartTerm)
	ON_BN_CLICKED(IDC_BTN_REQ_PORTFOLIO, &CStockSiseDlg::OnBnClickedBtnReqPortfolio)
	ON_COMMAND_RANGE(IDC_CON_REAL, IDC_CON_F_DEMO, &CStockSiseDlg::OnRdoSelectServer)
	ON_BN_CLICKED(IDC_BTN_REQ_CUR_RATE, &CStockSiseDlg::OnBnClickedBtnReqCurRate)
	ON_BN_CLICKED(IDC_BTN_REQ_KOSPI, &CStockSiseDlg::OnBnClickedBtnReqKospi)
	ON_BN_CLICKED(IDC_BTN_REQ_MEM, &CStockSiseDlg::OnBnClickedBtnReqMem)
	ON_BN_CLICKED(IDC_BTN_MEM_RANK, &CStockSiseDlg::OnBnClickedBtnMemRank)
END_MESSAGE_MAP()

// agent�κ��� �̺�Ʈ ���� �Լ��� �����Ѵ�.
BEGIN_EVENTSINK_MAP(CStockSiseDlg, CDialog)
	ON_EVENT(CStockSiseDlg, IDC_HFCOMMAGENTCTRL1, 1, CStockSiseDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CStockSiseDlg, IDC_HFCOMMAGENTCTRL1, 2, CStockSiseDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CStockSiseDlg, IDC_HFCOMMAGENTCTRL1, 3, CStockSiseDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
	ON_EVENT(CStockSiseDlg, IDC_HFCOMMAGENTCTRL1, 4, CStockSiseDlg::OnAgentEventHandler, VTS_I4 VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

// CStockSiseDlg �޽��� ó����
void CStockSiseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CStockSiseDlg::OnPaint()
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
HCURSOR CStockSiseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CStockSiseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CStockSiseDlg::OnDestroy()
{
	//��� �ǽð������ �����Ѵ�.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();
	
	CDialog::OnDestroy();
}

void CStockSiseDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

//*******************************************************************
// Function Name : OnRdoSelectServer
// Function      : 
// Param         : UINT nID
// Return        : void 
// Create        : 
// Comment       : ���Ӽ����� �����Ѵ�.
//******************************************************************
void CStockSiseDlg::OnRdoSelectServer(UINT nID)
{
	m_nSeverType = nID - IDC_CON_REAL;

	/*----------------------------------
	���Ӽ����� �����Ѵ�.(0 - ����, 1 - ��������, 2 - �ؿܸ���)
	*----------------------------------*/
	m_CommAgent.SetLoginMode(0, m_nSeverType);
}

void CStockSiseDlg::OnTimer(UINT_PTR nIDEvent)
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

void CStockSiseDlg::OnNMDblclkListSymbol(NMHDR *pNMHDR, LRESULT *pResult)
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
	OnBnClickedBtnReqPrice();		//�ֽ� ���簡 ��ȸ
	OnBnClickedBtnReqHoga();		//�ֽ� 5�ܰ�ȣ�� ��ȸ
	OnBnClickedBtnReqTick();		//�ֽ� �ð��뺰ü�� ��ȸ
	OnBnClickedBtnReqChart();		//�ֽ� ��Ʈ������ ��ȸ
	OnBnClickedBtnReqPortfolio();	//�ֽ� ���������� ��ȸ
}

void CStockSiseDlg::OnRadioChartTerm(UINT nID)
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
BOOL CStockSiseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CString strTitle;
	strTitle.Format("%s-[�ֽĽü�](%s)", PROGRAM_NAME, VERSION_INFO);
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
	* �ֽ� �ð��뺰ü�ᰡ ����Ʈ ��Ʈ�� �ʱ�ȭ
	**********************************/
	InitListTick();

	/**********************************
	* �ֽ� ���� ����Ʈ ��Ʈ�� �ʱ�ȭ
	**********************************/
	InitListCode();

	/**********************************
	 * �ֽ� ��Ʈ ����Ʈ ��Ʈ�� �ʱ�ȭ
	 **********************************/
	InitListChart();

	/**********************************
	* �ֽ� ���������� ����Ʈ ��Ʈ�� �ʱ�ȭ
	**********************************/
	InitListPortfolio();

	//����������(Portfolio) �����ڵ� �Է�
	GetDlgItem(IDC_EDIT_PORT_VALUE1)->SetWindowText("000660");
	GetDlgItem(IDC_EDIT_PORT_VALUE2)->SetWindowText("005930");
	GetDlgItem(IDC_EDIT_PORT_VALUE3)->SetWindowText("000815");
	GetDlgItem(IDC_EDIT_PORT_VALUE4)->SetWindowText("000880");
	GetDlgItem(IDC_EDIT_PORT_VALUE5)->SetWindowText("000210");

	//���屸�� �ڵ�
	GetDlgItem(IDC_EDIT_MARKET_CODE1)->SetWindowText("J");
	GetDlgItem(IDC_EDIT_MARKET_CODE2)->SetWindowText("J");
	GetDlgItem(IDC_EDIT_MARKET_CODE3)->SetWindowText("J");
	GetDlgItem(IDC_EDIT_MARKET_CODE4)->SetWindowText("J");
	GetDlgItem(IDC_EDIT_MARKET_CODE5)->SetWindowText("J");

	//����������(Portfolio) ��� FID ��ȣ
	GetDlgItem(IDC_EDIT_PORT_OUT_FID1)->SetWindowText("3"); //�ѱ������
	GetDlgItem(IDC_EDIT_PORT_OUT_FID2)->SetWindowText("4"); //���簡
	GetDlgItem(IDC_EDIT_PORT_OUT_FID3)->SetWindowText("5"); //���ϴ��
	GetDlgItem(IDC_EDIT_PORT_OUT_FID4)->SetWindowText("6"); //���ϴ���ȣ
	GetDlgItem(IDC_EDIT_PORT_OUT_FID5)->SetWindowText("7"); //���ϴ����

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
	//�ֽ�ü�� �ǽð� Block ���� ���ҽ� ����
	if (!m_CommAgent.LoadRealResource(strApidAgentModulePath + "/RealRes/S00.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());

	//�ֽ�ȣ�� �ǽð� Block ���� ���ҽ� ����
	if (!m_CommAgent.LoadRealResource(strApidAgentModulePath + "/RealRes/S01.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
#endif

	//��Ʈ �ֽ� ���� ƽ���� ����
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
// Function      : �ֽ� �ð��뺰ü�� ����Ʈ ��Ʈ�� �ʱ�ȭ
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CStockSiseDlg::InitListTick()
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
// Function      : �ֽ� ���� ����Ʈ ��Ʈ�� �ʱ�ȭ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::InitListCode()
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
						80};

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

//*******************************************************************
// Function Name : InitListChart
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::InitListChart()
{
	CRect rc;
	m_listChart.GetClientRect(rc);
	m_listChart.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int arrWidth[8] = { 60, 60, 70, 70, 70, 70, 80, 80};

	int nWidth = rc.Width() - ::GetSystemMetrics(SM_CYHSCROLL);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("����"), _T("�ð�"), _T("����"), _T("�ð�"), _T("��"), _T("����"), _T("ü�ᷮ"), _T("�ŷ���")};

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
// Function Name : InitListPortfolio
// Function      : �ֽ� ���������� ����Ʈ ��Ʈ�� �ʱ�ȭ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::InitListPortfolio()
{
	m_listPortfolio.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int arrWidth[5] = { 85, 85, 85, 85, 85 };
	
	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("FID-3"), _T("FID-4"), _T("FID-5"), _T("FID-6"), _T("FID-7")};

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
		m_listPortfolio.InsertColumn(i, &lvcolumn);
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
CString CStockSiseDlg::GetDiffSign(CString strSignCode)
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
void CStockSiseDlg::SetHogaData(CString* arrSellHoga, CString* arrBuyHoga, CString* arrSellRemain,
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
void CStockSiseDlg::OnBnClickedInitcomm()
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
void CStockSiseDlg::OnBnClickedTerminate()
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
void CStockSiseDlg::OnBnClickedLogin()
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

	m_CommAgent.SetOffAgentMessageBox(1);

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
		OnBnClickedBtnReqCodeList();
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : �α׾ƿ�
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedLogout()
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
// Function      : �ֽ� ���� ����Ʈ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedBtnReqCodeList()
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
	strOutputFidList =	"1,2,3,827,1893,2574,1993,1994,1995,2604,2605,"
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
// Function Name : OnBnClickedBtnReqCodeListNext
// Function      : �ֽ� ���� ����Ʈ ���� ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedBtnReqCodeListNext()
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
	strMarketCode = _T("J"); //�ֽ�

	/**********************************
	* 2. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("1199"));		//GID

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 3. �����ȸ �������� ���� �׸� ����.
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
	strOutputFidList =	"1,2,3,827,1893,2574,1993,1994,1995,2604,2605,"
						"2606,1257,1998,2607,1996,225,53,16,56,55,2067,"
						"684,1253,1254,1258,1251,2608,1252,1992,1256,"
						"222,2129,2148,19,21,1896";

	CString strScreenNo;
	strScreenNo = "9999";

	CString strPreNext = "3"; //���� ������ ��ȸ

	/**********************************
	* 4. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, m_strCodeListNextRqKey, strScreenNo, 3000);
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
void CStockSiseDlg::OnBnClickedBtnReqPrice()
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
	* 2. ������ ��ϵ� �ֽ�ü��(���簡) �ǽð���� ����.
	**********************************/
	if (!m_strCurPriceRealKey.IsEmpty())
	{
		CString strRealName;
		strRealName = _T("S00"); //�ֽ�ü�� Real name

		m_CommAgent.UnRegisterReal(strRealName, m_strCurPriceRealKey);
		m_strCurPriceRealKey.Empty();
	}

	CString strMarketCode;		//���屸��
	strMarketCode = _T("J");	//�ֽ�

	//�ֽ�ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
	m_strCurPriceRealKey = strSymBol;

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCurPrice, _T("9002"), strSymBol);		//�����ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCurPrice, _T("9001"), strMarketCode);	//���屸���ڵ�
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
// Function      : �ֽ�ȣ�� ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedBtnReqHoga()
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
	* 2. ������ ��ϵ� �ֽ�ȣ�� �ǽð���� ����
	**********************************/
	if (!m_strHogaRealKey.IsEmpty())
	{
		CString strRealName;
		strRealName = _T("S01");

		m_CommAgent.UnRegisterReal(strRealName, m_strHogaRealKey);
		m_strHogaRealKey.Empty();
	}

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("J");

	//�ֽ�ȣ�� �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
	m_strHogaRealKey = strSymBol;

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdHoga, _T("9002"), strSymBol);		//�����ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdHoga, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdHoga, _T("GID"), _T("1000"));		//GID

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	CString strSellHoga = _T("29,30,31,32,33");	//�ŵ� 1~5 ȣ��(FID)
	CString strSellRemain = _T("63,64,65,66,67"); //�ŵ� 1~5 ȣ���ܷ�(FID)
	CString strBuyHoga = _T("39,40,41,42,43");	//�ż� 1~5 ȣ��(FID)
	CString strBuyRemain = _T("73,74,75,76,77"); //�ż� 1~5 ȣ�� �ܷ�(FID)
	CString strSellCnt = _T("151,152,153,154,155"); //�ŵ� 1~5 ȣ������(FID)
	CString strBuyCnt = _T("161,162,163,164,165"); //�ż� 1~5 ȣ������(FID)

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
// Function      : �ֽ� �ð��뺰ü�� ������ ��ȸ(���Ӱŷ� �����Ͱ� �ִ� ���)
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedBtnReqTick()
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

	//�ֽ� �ð��뺰ü�� ����Ʈ ��Ʈ�� ������ �ʱ�ȭ
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
	* 3. ������ ��ϵ� �ֽ�ü��(���簡) �ǽð���� ����.
	**********************************/
	if (!m_strTickRealKey.IsEmpty())
	{
		CString strRealName;
		strRealName = _T("S00");

		m_CommAgent.UnRegisterReal(strRealName, m_strTickRealKey);
		m_strTickRealKey.Empty();
	}

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("J");

	//�ֽ�ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
	m_strTickRealKey = strSymBol;

	/**********************************
	* 4. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9002"), strSymBol);		//����ɺ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9001"), strMarketCode);	//���屸���ڵ�
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
// Function      : �ֽ� �ð��뺰ü�� ���� ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedBtnReqTickNext()
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
	strMarketCode = _T("J"); //�ֽ�

	/**********************************
	* 2. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9002"), strSymBol);		//����ɺ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9001"), strMarketCode);	//���屸���ڵ�
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
// Function      : �ֽ� ��Ʈ ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedBtnReqChart()
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

	//�ֽ� �ð��뺰ü�� ����Ʈ ��Ʈ�� ������ �ʱ�ȭ
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
	strMarketCode = _T("J");
	
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
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9008"), _T("4"));	//�ð������ڵ�(4:����)

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
// Function      : �ֽ� ��Ʈ ���� ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedBtnReqChartNext()
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
	strMarketCode = _T("J"); //�ֽ�

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
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9008"), _T("4"));	//�ð������ڵ�(4:����)

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

//*******************************************************************
// Function Name : OnBnClickedBtnReqPortfolio
// Function      : ����������(Portfolio) ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedBtnReqPortfolio()
{
	m_listPortfolio.DeleteAllItems();

	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strSymbolCode1, strSymbolCode2, strSymbolCode3;
	CString strSymbolCode4, strSymbolCode5;

	GetDlgItem(IDC_EDIT_PORT_VALUE1)->GetWindowText(strSymbolCode1);
	GetDlgItem(IDC_EDIT_PORT_VALUE2)->GetWindowText(strSymbolCode2);
	GetDlgItem(IDC_EDIT_PORT_VALUE3)->GetWindowText(strSymbolCode3);
	GetDlgItem(IDC_EDIT_PORT_VALUE4)->GetWindowText(strSymbolCode4);
	GetDlgItem(IDC_EDIT_PORT_VALUE5)->GetWindowText(strSymbolCode5);

	CString strMarketCode1, strMarketCode2, strMarketCode3;
	CString strMarketCode4, strMarketCode5;

	GetDlgItem(IDC_EDIT_MARKET_CODE1)->GetWindowText(strMarketCode1);
	GetDlgItem(IDC_EDIT_MARKET_CODE2)->GetWindowText(strMarketCode2);
	GetDlgItem(IDC_EDIT_MARKET_CODE3)->GetWindowText(strMarketCode3);
	GetDlgItem(IDC_EDIT_MARKET_CODE4)->GetWindowText(strMarketCode4);
	GetDlgItem(IDC_EDIT_MARKET_CODE5)->GetWindowText(strMarketCode5);

	CString strOutFid1, strOutFid2, strOutFid3;
	CString strOutFid4, strOutFid5;

	GetDlgItem(IDC_EDIT_PORT_OUT_FID1)->GetWindowText(strOutFid1);
	GetDlgItem(IDC_EDIT_PORT_OUT_FID2)->GetWindowText(strOutFid2);
	GetDlgItem(IDC_EDIT_PORT_OUT_FID3)->GetWindowText(strOutFid3);
	GetDlgItem(IDC_EDIT_PORT_OUT_FID4)->GetWindowText(strOutFid4);
	GetDlgItem(IDC_EDIT_PORT_OUT_FID5)->GetWindowText(strOutFid5);
	
	//Requst ID�� �����Ѵ�.
	m_nRqIdPortfolio = m_CommAgent.CreateRequestID();

	//����������(Portfolio) �����ڵ带 �Է��Ѵ�.
	m_CommAgent.SetPortfolioFidInputData(m_nRqIdPortfolio, strSymbolCode1, strMarketCode1);
	m_CommAgent.SetPortfolioFidInputData(m_nRqIdPortfolio, strSymbolCode2, strMarketCode2);
	m_CommAgent.SetPortfolioFidInputData(m_nRqIdPortfolio, strSymbolCode3, strMarketCode3);
	m_CommAgent.SetPortfolioFidInputData(m_nRqIdPortfolio, strSymbolCode4, strMarketCode4);
	m_CommAgent.SetPortfolioFidInputData(m_nRqIdPortfolio, strSymbolCode5, strMarketCode5);
	m_CommAgent.SetFidInputData(m_nRqIdPortfolio, _T("GID"), _T("5000"));		//GID(����������)

	CString strOutFidList;

	//�������� ������� �������� FID�׸��� �Է��Ѵ�.
	strOutFidList.Format("%s,%s,%s,%s,%s", strOutFid1, strOutFid2, strOutFid3, strOutFid4, strOutFid5);

	CString strPreNext;
	CString strScreenNo = "9999";

	//��ȸ ��û
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdPortfolio, strOutFidList, strPreNext, "", strScreenNo, 5);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqCurRate
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : ȯ����ȸ
//******************************************************************
void CStockSiseDlg::OnBnClickedBtnReqCurRate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	/**********************************
	* 1. �����ȸ Request ID�� �����Ѵ�.
	**********************************/
	m_nRqIdCurRate = m_CommAgent.CreateRequestID();
	if (m_nRqIdCurRate == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	// 	/**********************************
	// 	* 2. ������ ��ϵ� �ֽ�ü��(���簡) �ǽð���� ����.
	// 	**********************************/
	// 	if (!m_strCurPriceRealKey.IsEmpty())
	// 	{
	// 		CString strRealName;
	// 		strRealName = _T("S00"); //�ֽ�ü�� Real name
	// 
	// 		m_CommAgent.UnRegisterReal(strRealName, m_strCurPriceRealKey);
	// 		m_strCurPriceRealKey.Empty();
	// 	}

	//�ֽ�ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
	//	m_strCurPriceRealKey = strSymBol;

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetPortfolioFidInputData(m_nRqIdCurRate, "USDJPYCOMP", "EX"); //�Ϻ� ��/�޷�
	m_CommAgent.SetPortfolioFidInputData(m_nRqIdCurRate, "USDKRWSMBS", "EX"); //��/�޷�
	m_CommAgent.SetPortfolioFidInputData(m_nRqIdCurRate, "USDCNYCOMP", "EX"); //�߱� ����/�޷�
	m_CommAgent.SetPortfolioFidInputData(m_nRqIdCurRate, "USDEURCOMP", "EX"); //����/�޷�
	m_CommAgent.SetPortfolioFidInputData(m_nRqIdCurRate, "USDHKDCOMP", "EX"); //ȫ�� �޷�/�޷�
	m_CommAgent.SetPortfolioFidInputData(m_nRqIdCurRate, "USDGBPCOMP", "EX"); //���� �Ŀ��/�޷�
	m_CommAgent.SetPortfolioFidInputData(m_nRqIdCurRate, "USDTWDCOMP", "EX"); //�븸 ���޷�/�޷�

	m_CommAgent.SetFidInputData(m_nRqIdCurRate, _T("GID"), _T("5000"));  //GID(����������)

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	//�������� ������� �������� FID�׸��� �Է��Ѵ�.
	//3(ȯ����),4(���簡),7(�����)
	strOutputFidList = "3,4,7";

	CString strScreenNo;
	strScreenNo = "9999";

	/**********************************
	* 5. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFid(m_nRqIdCurRate, strOutputFidList, strScreenNo);

	//�ǽð� ���ҽ������� V43.res�̴�.
	//��ȸ ������ ���� �Ŀ� �ǽð� ����ϸ� �ȴ�. ����Ű�� ȯ�������ڵ带 �ִ´�.
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqKospi
// Function      : 
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedBtnReqKospi()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	/**********************************
	* 1. �����ȸ Request ID�� �����Ѵ�.
	**********************************/
	m_nRqIdKospi = m_CommAgent.CreateRequestID();
	if (m_nRqIdKospi == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	// 	/**********************************
	// 	* 2. ������ ��ϵ� �ֽ�ü��(���簡) �ǽð���� ����.
	// 	**********************************/
	// 	if (!m_strCurPriceRealKey.IsEmpty())
	// 	{
	// 		CString strRealName;
	// 		strRealName = _T("S00"); //�ֽ�ü�� Real name
	// 
	// 		m_CommAgent.UnRegisterReal(strRealName, m_strCurPriceRealKey);
	// 		m_strCurPriceRealKey.Empty();
	// 	}

	//�ֽ�ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
	//	m_strCurPriceRealKey = strSymBol;

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdKospi, "9002", "001");	//001(KOSPI ����) / 101(KOSPI 200) / 201(KOSDAQ ����)
	m_CommAgent.SetFidInputData(m_nRqIdKospi, "9001", "U");		//����
	
	m_CommAgent.SetFidInputData(m_nRqIdKospi, _T("GID"), _T("1000"));  //GID

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	//�������� ������� �������� FID�׸��� �Է��Ѵ�.
	//9 ����, 4 ���簡, 6 ���ϴ���ȣ, 5 ���ϴ��, 7 ���ϴ����, 13 �ð�,
	//14 ��, 15 ����, 11 �����ŷ���, 12 �����ŷ����
	strOutputFidList = "9,4,6,5,7,13,14,15,11,12";

	CString strScreenNo;
	strScreenNo = "9999";

	/**********************************
	* 5. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFid(m_nRqIdKospi, strOutputFidList, strScreenNo);

	//�ǽð� ���ҽ������� V43.res�̴�.
	//��ȸ ������ ���� �Ŀ� �ǽð� ����ϸ� �ȴ�. ����Ű�� ȯ�������ڵ带 �ִ´�.

	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}


//*******************************************************************
// Function Name : OnBnClickedBtnReqMem
// Function      : 
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedBtnReqMem()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	/**********************************
	* 1. �����ȸ Request ID�� �����Ѵ�.
	**********************************/
	m_nRqIdMem = m_CommAgent.CreateRequestID();
	if (m_nRqIdMem == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	// 	/**********************************
	// 	* 2. ������ ��ϵ� �ֽ�ü��(���簡) �ǽð���� ����.
	// 	**********************************/
	// 	if (!m_strCurPriceRealKey.IsEmpty())
	// 	{
	// 		CString strRealName;
	// 		strRealName = _T("S00"); //�ֽ�ü�� Real name
	// 
	// 		m_CommAgent.UnRegisterReal(strRealName, m_strCurPriceRealKey);
	// 		m_strCurPriceRealKey.Empty();
	// 	}

	//�ֽ�ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
	//	m_strCurPriceRealKey = strSymBol;

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdMem, _T("9117"), "000"); //�Է�ȸ���������ڵ�(000: ��ü)
	m_CommAgent.SetFidInputData(m_nRqIdMem, _T("9034"), "20161205"); //�Է³�¥1(��ȸ������)
	m_CommAgent.SetFidInputData(m_nRqIdMem, _T("9035"), "20161209"); //�Է³�¥2(��ȸ��������)
	m_CommAgent.SetFidInputData(m_nRqIdMem, _T("9027"), "107"); //�Է¼������ı����ڵ�1(107:���űݾ�, 108:���ŵ��ݾ�, 26:���ż���, 27:���ż���)
	m_CommAgent.SetFidInputData(m_nRqIdMem, _T("GID"), "2112");

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	//�������� ������� �������� FID�׸��� �Է��Ѵ�.
	/* �����(2639), �����ڵ�(1), ���ż��ݾ�(377), ���ŵ��ݾ�(407), �ż��ݾ�(406),�ŵ��ݾ�(405),���ż���(404),�ż���(403),�ŵ���(402),���ŵ���(874),
	����(4),����ȣ(6),���(5),�����(7),�ŷ���(11) */
	//�ݾ� �Ǵ� ���� �� ���ϴ� �������� ���FID�׸��� �����.
	strOutputFidList = "2639,1,377,406,405,4,6,5,7,11"; //���ż��ݾ����� ��ȸ �� ����׸��
	//strOutputFidList = "2639,1,407,406,405,4,6,5,7,11"; //���ŵ��ݾ����� ��ȸ �� ����׸��
	//strOutputFidList = "2639,1,404,403,402,4,6,5,7,11"; //���ż��������� ��ȸ �� ����׸��
	//strOutputFidList = "2639,1,874,403,402,4,6,5,7,11"; //���ŵ��������� ��ȸ �� ����׸��

	CString strScreenNo;
	strScreenNo = "9999";

	/**********************************
	* 5. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	//������ȸ �ɼ� : '0':�̻��, '1'���, '2' : ���� ������ ��ȸ, '3' : ���� ������ ��ȸ
	CString strPreNext = "1";

	/**********************************
	* 6. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdMem, strOutputFidList, strPreNext, "", strScreenNo, 9999);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());

	//��ȸ ������ ���� �Ŀ� �ǽð� ����ϸ� �ȴ�. ����Ű�� ȯ�������ڵ带 �ִ´�.
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnMemRank
// Function      : 
// Param         : 
// Return        : void 
// Create        : ������, 2017/01/05
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedBtnMemRank()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}

//*******************************************************************
// Function Name : OnBnClickedOk
// Function      : ��ȭâ ����
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockSiseDlg::OnBnClickedOk()
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
void CStockSiseDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
void CStockSiseDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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


#if 1	/***************************************
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

#else	/***************************************
		 * ������Ʈ ��Ʈ���� ���� �׸� ����Ÿ�� ������.
		 ****************************************/
		int nDataCnt = m_CommAgent.GetFidOutputRowCnt(nRequestId);

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			arrItem[0] = m_CommAgent.GetFidOutputData(nRequestId, "1", i);	//0001 : �����ڵ�
			arrItem[1] = m_CommAgent.GetFidOutputData(nRequestId, "2", i);	//0002 : ǥ�������ڵ�
			arrItem[2] = m_CommAgent.GetFidOutputData(nRequestId, "3", i);	//0003 : �ѱ������
			arrItem[3] = m_CommAgent.GetFidOutputData(nRequestId, "827", i);	//0827 : ���屸��(1: KOSPI, 4 : KOSDAQ, A : ETN)
			arrItem[4] = m_CommAgent.GetFidOutputData(nRequestId, "1893", i);	//1893 : ���Ǳ׷챸���ڵ�
			arrItem[5] = m_CommAgent.GetFidOutputData(nRequestId, "2574", i);	//2574 : �ð��Ѿ� �Ը� �����ڵ�
			arrItem[6] = m_CommAgent.GetFidOutputData(nRequestId, "1993", i);	//1993 : ���� ���� ��з� �ڵ�
			arrItem[7] = m_CommAgent.GetFidOutputData(nRequestId, "1994", i);	//1994 : ���� ���� �ߺз� �ڵ�
			arrItem[8] = m_CommAgent.GetFidOutputData(nRequestId, "1995", i);	//1995 : ���� ���� �Һз� �ڵ�
			arrItem[9] = m_CommAgent.GetFidOutputData(nRequestId, "2604", i);	//2604 : ������ �����ڵ�(Y : �ش� N : ���ش�) = > mnin_cls_code
			arrItem[10] = m_CommAgent.GetFidOutputData(nRequestId, "2606", i);	//2605 : ������� ���񿩺�(Y, N) = > dvdn_nmix_issu_yn
			arrItem[11] = m_CommAgent.GetFidOutputData(nRequestId, "1257", i);	//2606 : ���豸���������(Y, N) = > sprn_strr_sprr_yn
			arrItem[12] = m_CommAgent.GetFidOutputData(nRequestId, "1257", i);	//1257 : KOSPI200 ����
			arrItem[13] = m_CommAgent.GetFidOutputData(nRequestId, "1998", i);	//1998 : KOSPI100, 50 ����(1:KOSPI100, 2 : KOSPI50)
			arrItem[14] = m_CommAgent.GetFidOutputData(nRequestId, "2607", i);	//2607 : ��ó��� ���� Y, N = > sprn_strr_nmix_issu_yn
			arrItem[15] = m_CommAgent.GetFidOutputData(nRequestId, "1996", i);	//1996 : KRX100 ���񿩺�
			arrItem[16] = m_CommAgent.GetFidOutputData(nRequestId, "225", i);	//0225 : ����
			arrItem[17] = m_CommAgent.GetFidOutputData(nRequestId, "53", i);	//0053 : �ֽľ׸鰡
			arrItem[18] = m_CommAgent.GetFidOutputData(nRequestId, "16", i);	//0016 : �ֽı��ذ�
			arrItem[19] = m_CommAgent.GetFidOutputData(nRequestId, "56", i);	//0056 : �ں���
			arrItem[20] = m_CommAgent.GetFidOutputData(nRequestId, "55", i);	//0055 : �����ּ�
			arrItem[21] = m_CommAgent.GetFidOutputData(nRequestId, "2067", i);	//2067 : ��������
			arrItem[22] = m_CommAgent.GetFidOutputData(nRequestId, "684", i);	//0684 : �ſ��ܰ����
			arrItem[23] = m_CommAgent.GetFidOutputData(nRequestId, "1253", i);	//1253 : �ŷ���������(N : ����, Y : �ŷ�����)
			arrItem[24] = m_CommAgent.GetFidOutputData(nRequestId, "1254", i);	//1254 : �����Ÿſ���(N : ����, Y : �����Ÿ�)
			arrItem[25] = m_CommAgent.GetFidOutputData(nRequestId, "1258", i);	//1258 : �������񿩺�(N : ����, Y : ��������)
			arrItem[26] = m_CommAgent.GetFidOutputData(nRequestId, "1251", i);	//1251 : ���������ڵ�(00:���� 01 : ���� 02 : ��� 03 : ����)
			arrItem[27] = m_CommAgent.GetFidOutputData(nRequestId, "2608", i);	//2608 : �����������ڵ� Y, N = > mrkt_alrm_risk_adnt_yn
			arrItem[28] = m_CommAgent.GetFidOutputData(nRequestId, "1252", i);	//1252 : �Ҽ��ǰ������� ���� Y, N
			arrItem[29] = m_CommAgent.GetFidOutputData(nRequestId, "1992", i);	//1992 : ��ȸ���屸�� Y, N
			arrItem[30] = m_CommAgent.GetFidOutputData(nRequestId, "1256", i);	//1256 : �������ڵ�
			arrItem[31] = m_CommAgent.GetFidOutputData(nRequestId, "222", i);	//0222 : ��� �ſ� ����
			arrItem[32] = m_CommAgent.GetFidOutputData(nRequestId, "2129", i);	//2129 : ���������� ���а� 1 : �ش� 0 : ���ش�
			arrItem[33] = m_CommAgent.GetFidOutputData(nRequestId, "2148", i);	//2148 : Equity Rating���� A, B, C, D, F ����� X
			arrItem[34] = m_CommAgent.GetFidOutputData(nRequestId, "19", i);	//0019 : �ð��Ѿ�(��)
			arrItem[35] = m_CommAgent.GetFidOutputData(nRequestId, "21", i);	//0021 : �ܱ��κ�������
			arrItem[36] = m_CommAgent.GetFidOutputData(nRequestId, "1896", i);	//1896 : �켱�� ���� �ڵ�(0:������, �׿� : �켱��)

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
#endif

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
		m_nRqIdCodeList = 0;	//�ֽ� ���� ����Ʈ(������) ��ȸ Request ID

		/*--------------------------------------
		�ڵ� ���� ��ȸ
		---------------------------------------*/
		if (m_chkAutoReq.GetCheck() == 1 &&
			GetDlgItem(IDC_BTN_REQ_CODE_LIST_NEXT)->IsWindowEnabled())
		{
			OnBnClickedBtnReqCodeListNext();
		}
	}
	/***************************************
	* �ֽ� 5�ܰ�ȣ�� ��ȸ ������ ���� ó��
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
		arrSellHoga[0] = m_CommAgent.GetFidOutputData(nRequestId, "29", 0);		//�ŵ� 1ȣ��
		arrSellHoga[1] = m_CommAgent.GetFidOutputData(nRequestId, "30", 0);		//�ŵ� 2ȣ��
		arrSellHoga[2] = m_CommAgent.GetFidOutputData(nRequestId, "31", 0);		//�ŵ� 3ȣ��
		arrSellHoga[3] = m_CommAgent.GetFidOutputData(nRequestId, "32", 0);		//�ŵ� 4ȣ��
		arrSellHoga[4] = m_CommAgent.GetFidOutputData(nRequestId, "33", 0);		//�ŵ� 5ȣ��

		arrSellRemain[0] = m_CommAgent.GetFidOutputData(nRequestId, "63", 0);	//�ŵ� 1ȣ���ܷ�
		arrSellRemain[1] = m_CommAgent.GetFidOutputData(nRequestId, "64", 0);	//�ŵ� 2ȣ���ܷ�
		arrSellRemain[2] = m_CommAgent.GetFidOutputData(nRequestId, "65", 0);	//�ŵ� 3ȣ���ܷ�
		arrSellRemain[3] = m_CommAgent.GetFidOutputData(nRequestId, "66", 0);	//�ŵ� 4ȣ���ܷ�
		arrSellRemain[4] = m_CommAgent.GetFidOutputData(nRequestId, "67", 0);	//�ŵ� 5ȣ���ܷ�

		arrSellCnt[0] = m_CommAgent.GetFidOutputData(nRequestId, "151", 0);		//�ŵ� 1ȣ������
		arrSellCnt[1] = m_CommAgent.GetFidOutputData(nRequestId, "152", 0);		//�ŵ� 2ȣ������
		arrSellCnt[2] = m_CommAgent.GetFidOutputData(nRequestId, "153", 0);		//�ŵ� 3ȣ������
		arrSellCnt[3] = m_CommAgent.GetFidOutputData(nRequestId, "154", 0);		//�ŵ� 4ȣ������
		arrSellCnt[4] = m_CommAgent.GetFidOutputData(nRequestId, "155", 0);		//�ŵ� 5ȣ������

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

		arrBuyCnt[0] = m_CommAgent.GetFidOutputData(nRequestId, "161", 0);		//�ż� 1ȣ������
		arrBuyCnt[1] = m_CommAgent.GetFidOutputData(nRequestId, "162", 0);		//�ż� 2ȣ������
		arrBuyCnt[2] = m_CommAgent.GetFidOutputData(nRequestId, "163", 0);		//�ż� 3ȣ������
		arrBuyCnt[3] = m_CommAgent.GetFidOutputData(nRequestId, "164", 0);		//�ż� 4ȣ������
		arrBuyCnt[4] = m_CommAgent.GetFidOutputData(nRequestId, "165", 0);		//�ż� 5ȣ������

		/*--------------------------------------
		��ȸ�� ���� �����͸� ȭ�� ��Ʈ�ѿ� ǥ���Ѵ�.
		---------------------------------------*/
		SetHogaData(arrSellHoga, arrBuyHoga, arrSellRemain, arrBuyRemain, arrSellCnt, arrBuyCnt);

		/*--------------------------------------
		�ֽ�ȣ�� �ǽð�Ű�� �ǽð��� ����Ѵ�.
		�ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		---------------------------------------*/
		if (!m_strHogaRealKey.IsEmpty())
		{
			CString strRealName;
			strRealName = _T("S01");

			m_CommAgent.RegisterReal(strRealName, m_strHogaRealKey); //�ǽð� ���
		}

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdHoga = 0;	//�ֽ� 5�ܰ�ȣ�� ��ȸ Request ID
	}
	/***************************************
	* �ֽ� ���簡 ��ȸ ������ ���� ó��
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
		�ֽ� ü��(���簡) �ǽð����Ű�� �ǽð��� ����Ѵ�.
		�ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		---------------------------------------*/
		if (!m_strCurPriceRealKey.IsEmpty())
		{
			CString strRealName;
			strRealName = _T("S00");

			m_CommAgent.RegisterReal(strRealName, m_strCurPriceRealKey); //�ǽð� ���
		}

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdCurPrice = 0;	//�ֽ� ���簡 ��ȸ Request ID
	}
	/***************************************
	* �ֽ� �ð��뺰ü�� ��ȸ ������ ���� ó��
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
			strTime = m_CommAgent.GetFidOutputData(nRequestId, "8", i);		//�ð�
			strPrice = m_CommAgent.GetFidOutputData(nRequestId, "4", i);	//ü�ᰡ
			strDiff = m_CommAgent.GetFidOutputData(nRequestId, "5", i);		//���
			strDiffRate = m_CommAgent.GetFidOutputData(nRequestId, "7", i);	//���
			strVolume = m_CommAgent.GetFidOutputData(nRequestId, "83", i);	//ü�ᷮ

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
		�ֽ�ü�� �ǽð��� ����Ѵ�.
		�ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		---------------------------------------*/
		if (!m_strTickRealKey.IsEmpty() && m_strTickNextRqKey.IsEmpty())
		{
			CString strRealName;
			strRealName = _T("S00");

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
		m_nRqIdTick = 0;	//�ֽ� �ð��뺰ü�� ��ȸ Request ID

	}
	/***************************************
	 * �ֽ� ��Ʈ ��ȸ ������ ���� ó��
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
			arrItem[0] = fidCommRecvData.GetItem(i, 0);	//0009 : ����
			arrItem[1] = fidCommRecvData.GetItem(i, 1);	//0008 : �ð�
			arrItem[2] = fidCommRecvData.GetItem(i, 2);	//0004 : ����
			arrItem[3] = fidCommRecvData.GetItem(i, 3);	//0013 : �ð�
			arrItem[4] = fidCommRecvData.GetItem(i, 4);	//0014 : ��
			arrItem[5] = fidCommRecvData.GetItem(i, 5);	//0015 : ����
			arrItem[6] = fidCommRecvData.GetItem(i, 6);	//0083 : ü�ᷮ
			arrItem[7] = fidCommRecvData.GetItem(i, 7);	//0011 : �ŷ���

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
		* ������Ʈ ��Ʈ���� ���� �׸� ����Ÿ�� ������.
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
		m_nRqIdChart = 0;	//�ֽ� ���� ����Ʈ(������) ��ȸ Request ID

		/*--------------------------------------
		�ڵ� ���� ��ȸ
		---------------------------------------*/
		if (m_chkAutoReqChart.GetCheck() == 1 &&
			GetDlgItem(IDC_BTN_REQ_CHART_NEXT)->IsWindowEnabled())
		{
			OnBnClickedBtnReqChartNext();
		}
	}
	/***************************************
	* �ֽ� ����������(Portfolio) ��ȸ
	****************************************/
	else if (m_nRqIdPortfolio == nRequestId)
	{
		CString strName;
		CString strPrice;
		CString strDiff;
		CString strDiffSign;
		CString strDiffRate;

		m_listPortfolio.SetRedraw(FALSE);
		LV_ITEM	lvItem;

		int nListIndex = 0;
		int nDataCnt = m_CommAgent.GetFidOutputRowCnt(nRequestId);

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			strName = m_CommAgent.GetFidOutputData(nRequestId, "3", i);			//�ѱ������
			strPrice = m_CommAgent.GetFidOutputData(nRequestId, "4", i);		//���簡
			strDiff = m_CommAgent.GetFidOutputData(nRequestId, "5", i);			//���ϴ��
			strDiffSign = m_CommAgent.GetFidOutputData(nRequestId, "6", i);		//���ϴ���ȣ
			strDiffRate = m_CommAgent.GetFidOutputData(nRequestId, "7", i);		//���ϴ����

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listPortfolio.InsertItem(&lvItem);

			m_listPortfolio.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strName);
			m_listPortfolio.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strPrice);
			m_listPortfolio.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strDiff);
			m_listPortfolio.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strDiffSign);
			m_listPortfolio.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strDiffRate);
		}

		m_listPortfolio.SetRedraw(TRUE);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdPortfolio = 0;	//Request ID

	}
	/***************************************
	* ȯ������ ��ȸ
	****************************************/
	else if (m_nRqIdCurRate == nRequestId)
	{
		//3(ȯ����),4(���簡),7(�����)
		CString strCurrencyName;
		CString strPrice;
		CString strDiffRate;

		int nDataCnt = m_CommAgent.GetFidOutputRowCnt(nRequestId);

		for (int i = 0; i < nDataCnt; i++)
		{
			/*--------------------------------------
			FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			strCurrencyName = m_CommAgent.GetFidOutputData(nRequestId, "3", i);	//ȯ����
			strPrice = m_CommAgent.GetFidOutputData(nRequestId, "4", i);		//���簡
			strDiffRate = m_CommAgent.GetFidOutputData(nRequestId, "7", i);		//�����
		}

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdCurRate = 0;	//Request ID

	}
	else if (m_nRqIdKospi == nRequestId)
	{
		//9 ����, 4 ���簡, 6 ���ϴ���ȣ, 5 ���ϴ��, 7 ���ϴ����, 13 �ð�,
		//14 ��, 15 ����, 11 �����ŷ���, 12 �����ŷ����
		//strOutputFidList = "9,4,6,5,7,13,14,15,11,12";
		CString strDate;
		CString strPrice;
		CString strDiffSign;
		CString strDiff;
		CString strDiffRate;
		CString strOpenPrice;
		CString strHighPrice;
		CString strLowPrice;
		CString strVolume;
		CString strAmount;

		/*--------------------------------------
		FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
		---------------------------------------*/
		strDate = m_CommAgent.GetFidOutputData(nRequestId, "9", 0);			//����
		strPrice = m_CommAgent.GetFidOutputData(nRequestId, "4", 0);		//���簡
		strDiffSign = m_CommAgent.GetFidOutputData(nRequestId, "6", 0);		//���ϴ���ȣ
		strDiff = m_CommAgent.GetFidOutputData(nRequestId, "5", 0);			//���ϴ��
		strDiffRate = m_CommAgent.GetFidOutputData(nRequestId, "7", 0);		//���ϴ����
		strOpenPrice = m_CommAgent.GetFidOutputData(nRequestId, "13", 0);	//�ð�
		strHighPrice = m_CommAgent.GetFidOutputData(nRequestId, "14", 0);	//��
		strLowPrice = m_CommAgent.GetFidOutputData(nRequestId, "15", 0);	//����
		strVolume = m_CommAgent.GetFidOutputData(nRequestId, "11", 0);		//�����ŷ���
		strAmount = m_CommAgent.GetFidOutputData(nRequestId, "12", 0);		//�����ŷ����

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdKospi = 0;	//Request ID
	}
	else if (m_nRqIdMem == nRequestId)
	{
		/* �����(2639), �����ڵ�(1), ���ż��ݾ�(377), ���ŵ��ݾ�(407), �ż��ݾ�(406),�ŵ��ݾ�(405),���ż���(404),�ż���(403),�ŵ���(402),���ŵ���(874),
		����(4),����ȣ(6),���(5),�����(7),�ŷ���(11)
		strOutputFidList = "2639,1,377,406,405,4,6,5,7,11"; //���ż��ݾ����� ��ȸ �� ����׸��
		strOutputFidList = "2639,1,407,406,405,4,6,5,7,11"; //���ŵ��ݾ����� ��ȸ �� ����׸��
		strOutputFidList = "2639,1,404,403,402,4,6,5,7,11"; //���ż��������� ��ȸ �� ����׸��
		strOutputFidList = "2639,1,874,403,402,4,6,5,7,11"; //���ŵ��������� ��ȸ �� ����׸�� */
		int nDataCnt = m_CommAgent.GetFidOutputRowCnt(nRequestId);
		m_nRqIdMem = 0;
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
void CStockSiseDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/* ���� : OnGetRealData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
	�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/

	/***************************************
	* �ֽ� ȣ�� �ǽð� ������ ����
	****************************************/
	if (!_tcscmp(strRealName, "S01"))
	{
		/*--------------------------------------
		��ȸ ������ ����� �ֽ� ȣ�� �ǽð�Ű�� �������� ��
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

			//S01.res ������  INDEX�ʵ� ��ȣ�� �ε����� ����Ѵ�.
			arrSellHoga[0] = realCommRecvData.GetItem(0, 3);		//�ŵ�1ȣ��
			arrSellHoga[1] = realCommRecvData.GetItem(0, 5);		//�ŵ�2ȣ��
			arrSellHoga[2] = realCommRecvData.GetItem(0, 7);		//�ŵ�3ȣ��
			arrSellHoga[3] = realCommRecvData.GetItem(0, 9);		//�ŵ�4ȣ��
			arrSellHoga[4] = realCommRecvData.GetItem(0, 11);	//�ŵ�5ȣ��
			
			arrSellRemain[0] = realCommRecvData.GetItem(0, 43);	//�ŵ�1ȣ���ܷ�
			arrSellRemain[1] = realCommRecvData.GetItem(0, 44);	//�ŵ�2ȣ���ܷ�
			arrSellRemain[2] = realCommRecvData.GetItem(0, 45);	//�ŵ�3ȣ���ܷ�
			arrSellRemain[3] = realCommRecvData.GetItem(0, 46);	//�ŵ�4ȣ���ܷ�
			arrSellRemain[4] = realCommRecvData.GetItem(0, 47);	//�ŵ�5ȣ���ܷ�
			
			arrSellCnt[0] = realCommRecvData.GetItem(0, 63);		//�ŵ�1ȣ���ܷ�����
			arrSellCnt[1] = realCommRecvData.GetItem(0, 65);		//�ŵ�2ȣ���ܷ�����
			arrSellCnt[2] = realCommRecvData.GetItem(0, 67);		//�ŵ�3ȣ���ܷ�����
			arrSellCnt[3] = realCommRecvData.GetItem(0, 69);		//�ŵ�4ȣ���ܷ�����
			arrSellCnt[4] = realCommRecvData.GetItem(0, 71);		//�ŵ�5ȣ���ܷ�����

			arrBuyHoga[0] = realCommRecvData.GetItem(0, 23);		//�ż�1ȣ��
			arrBuyHoga[1] = realCommRecvData.GetItem(0, 25);		//�ż�2ȣ��
			arrBuyHoga[2] = realCommRecvData.GetItem(0, 27);		//�ż�3ȣ��
			arrBuyHoga[3] = realCommRecvData.GetItem(0, 29);		//�ż�4ȣ��
			arrBuyHoga[4] = realCommRecvData.GetItem(0, 31);		//�ż�5ȣ��
			
			arrBuyRemain[0] = realCommRecvData.GetItem(0, 53);	//�ż�1ȣ���ܷ�
			arrBuyRemain[1] = realCommRecvData.GetItem(0, 54);	//�ż�2ȣ���ܷ�
			arrBuyRemain[2] = realCommRecvData.GetItem(0, 55);	//�ż�3ȣ���ܷ�
			arrBuyRemain[3] = realCommRecvData.GetItem(0, 56);	//�ż�4ȣ���ܷ�
			arrBuyRemain[4] = realCommRecvData.GetItem(0, 57);	//�ż�5ȣ���ܷ�
			
			arrBuyCnt[0] = realCommRecvData.GetItem(0, 83);		//�ż�1ȣ���ܷ�����
			arrBuyCnt[1] = realCommRecvData.GetItem(0, 85);		//�ż�2ȣ���ܷ�����
			arrBuyCnt[2] = realCommRecvData.GetItem(0, 87);		//�ż�3ȣ���ܷ�����
			arrBuyCnt[3] = realCommRecvData.GetItem(0, 89);		//�ż�4ȣ���ܷ�����
			arrBuyCnt[4] = realCommRecvData.GetItem(0, 91);		//�ż�5ȣ���ܷ�����

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
			//�ŵ� 1~5ȣ�� �ܷ�����
			arrSellCnt[0] = m_CommAgent.GetRealOutputData(strRealName, "LP_ASKP_RSQN_ICDC1");
			arrSellCnt[1] = m_CommAgent.GetRealOutputData(strRealName, "LP_ASKP_RSQN_ICDC2");
			arrSellCnt[2] = m_CommAgent.GetRealOutputData(strRealName, "LP_ASKP_RSQN_ICDC3");
			arrSellCnt[3] = m_CommAgent.GetRealOutputData(strRealName, "LP_ASKP_RSQN_ICDC4");
			arrSellCnt[4] = m_CommAgent.GetRealOutputData(strRealName, "LP_ASKP_RSQN_ICDC5");

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
			//�ż� 1~5ȣ�� �ܷ�����
			arrBuyCnt[0] = m_CommAgent.GetRealOutputData(strRealName, "LP_BIDP_RSQN_ICDC1");
			arrBuyCnt[1] = m_CommAgent.GetRealOutputData(strRealName, "LP_BIDP_RSQN_ICDC2");
			arrBuyCnt[2] = m_CommAgent.GetRealOutputData(strRealName, "LP_BIDP_RSQN_ICDC3");
			arrBuyCnt[3] = m_CommAgent.GetRealOutputData(strRealName, "LP_BIDP_RSQN_ICDC4");
			arrBuyCnt[4] = m_CommAgent.GetRealOutputData(strRealName, "LP_BIDP_RSQN_ICDC5");
#endif
			SetHogaData(arrSellHoga, arrBuyHoga, arrSellRemain, arrBuyRemain, arrSellCnt, arrBuyCnt);

		}//End of if
	}
	/***************************************
	* �ֽ� ü��(���簡) �ǽð� ������ ����
	****************************************/
	else if (!_tcscmp(strRealName, "S00"))
	{
		/*--------------------------------------
		�����۸����� ���ŵ� �ǽð� �����͸� �׸񺰷� ������.
		---------------------------------------*/
		CString strCurPrice	= m_CommAgent.GetRealOutputData(strRealName, "STCK_PRPR");		//���簡
		CString strDiffSign	= m_CommAgent.GetRealOutputData(strRealName, "PRDY_VRSS_SIGN");	//��ȣ
		CString strDiff	= m_CommAgent.GetRealOutputData(strRealName, "PRDY_VRSS");			//���ϴ��
		CString strDiffRate = m_CommAgent.GetRealOutputData(strRealName, "PRDY_CTRT");		//�����
		CString strVolume = m_CommAgent.GetRealOutputData(strRealName, "ACML_VOL");			//�ŷ���

		CString strOpenPrice = m_CommAgent.GetRealOutputData(strRealName, "STCK_OPRC");		//�ð�
		CString strHighPrice = m_CommAgent.GetRealOutputData(strRealName, "STCK_HGPR");		//��
		CString strLowPrice = m_CommAgent.GetRealOutputData(strRealName, "STCK_LWPR");		//����

		CString strTime = m_CommAgent.GetRealOutputData(strRealName, "STCK_CNTG_HOUR");		//ü��ð�
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
		��ȸ ������ ����� �ֽ� ���簡 �ǽð�Ű�� �������� ��
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
		��ȸ ������ ����� �ֽ� �ð��뺰 ü�� �ǽð�Ű�� �������� ��
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



//*******************************************************************
// Function Name : OnAgentEventHandler
// Function      : 
// Param         : long nEventType, long nParam, LPCTSTR strParam
// Return        : void 
// Create        : 2016/11/10
// Comment       : ������Ʈ �̺�Ʈ �ڵ鷯
//******************************************************************
void CStockSiseDlg::OnAgentEventHandler(long nEventType, long nParam, LPCTSTR strParam)
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
