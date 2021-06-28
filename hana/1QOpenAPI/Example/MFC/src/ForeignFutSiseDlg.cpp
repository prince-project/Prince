/*----------------------------------------*
| ���α׷��� : �ϳ��������� Open API ����
| ��      �� : v 
| ����  ���� :
| ��      Ÿ :
*----------------------------------------*/
// ForeignFutSiseDlg.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "HFCommClient.h"
#include "ForeignFutSiseDlg.h"

#define ID_SECOND_TIMER		100	//1�� ���� Ÿ�̸�

#define SELL_BK_COLOR		RGB(206, 232, 255)	//�ŵ� ����
#define BUY_BK_COLOR		RGB(251, 221, 255)	//�ż� ����

//��� ����ü ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

// CForeignFutSiseDlg ��ȭ ����
CForeignFutSiseDlg::CForeignFutSiseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CForeignFutSiseDlg::IDD, pParent)
{
	m_bCommConnect = FALSE;
	m_nRqIdHoga = 0;
	m_nRqIdCurPrice = 0;
	m_nRqIdTick = 0;
	m_nRqIdCodeList = 0;
	m_nRqIdCodeList2 = 0;
	m_nRqIdChart = 0;

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nSeverType = 0;	//0-����, 1-��������, 2-�ؿܹ���
}

void CForeignFutSiseDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_LIST_SYMBOL2, m_listCode2);
	DDX_Control(pDX, IDC_EDIT_SYMBOL_CHART, m_editSymbolChart);
	DDX_Control(pDX, IDC_CHK_AUTO_REQ_CHART, m_chkAutoReqChart);
	DDX_Control(pDX, IDC_LIST_CHART, m_listChart);
	DDX_Control(pDX, IDC_EDIT_CHART_CNT, m_editChartCnt);
	DDX_Control(pDX, IDC_DATETIME_FROM, m_dateTimeFrom);
	DDX_Control(pDX, IDC_DATETIME_TO, m_dateTimeTo);
}

BEGIN_MESSAGE_MAP(CForeignFutSiseDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_LOGIN, &CForeignFutSiseDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_LOGOUT, &CForeignFutSiseDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_INITCOMM, &CForeignFutSiseDlg::OnBnClickedInitcomm)
	ON_BN_CLICKED(IDC_TERMINATE, &CForeignFutSiseDlg::OnBnClickedTerminate)
	ON_BN_CLICKED(IDC_BTN_REQ_HOGA, &CForeignFutSiseDlg::OnBnClickedBtnReqHoga)
	ON_BN_CLICKED(IDC_BTN_REQ_PRICE, &CForeignFutSiseDlg::OnBnClickedBtnReqPrice)
	ON_BN_CLICKED(IDC_BTN_REQ_TICK, &CForeignFutSiseDlg::OnBnClickedBtnReqTick)
	ON_BN_CLICKED(IDC_BTN_REQ_TICK_NEXT, &CForeignFutSiseDlg::OnBnClickedBtnReqTickNext)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE_LIST, &CForeignFutSiseDlg::OnBnClickedBtnReqCodeList)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE_LIST_NEXT, &CForeignFutSiseDlg::OnBnClickedBtnReqCodeListNext)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SYMBOL, &CForeignFutSiseDlg::OnNMDblclkListSymbol)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SYMBOL2, &CForeignFutSiseDlg::OnNMDblclkListSymbol2)
	ON_BN_CLICKED(IDOK, &CForeignFutSiseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_REQ_CHART, &CForeignFutSiseDlg::OnBnClickedBtnReqChart)
	ON_BN_CLICKED(IDC_BTN_REQ_CHART_NEXT, &CForeignFutSiseDlg::OnBnClickedBtnReqChartNext)
	ON_COMMAND_RANGE(IDC_RADIO_TICK, IDC_RADIO_MON, &CForeignFutSiseDlg::OnRadioChartTerm)
	ON_COMMAND_RANGE(IDC_CON_REAL, IDC_CON_F_DEMO, &CForeignFutSiseDlg::OnRdoSelectServer)
	ON_BN_CLICKED(IDC_BUTTON_REAL, &CForeignFutSiseDlg::OnBnClickedButtonReal)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE_LIST2, &CForeignFutSiseDlg::OnBnClickedBtnReqCodeList2)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE_LIST_NEXT2, &CForeignFutSiseDlg::OnBnClickedBtnReqCodeListNext2)
END_MESSAGE_MAP()

// agent�κ��� �̺�Ʈ ���� �Լ��� �����Ѵ�.
BEGIN_EVENTSINK_MAP(CForeignFutSiseDlg, CDialog)
	ON_EVENT(CForeignFutSiseDlg, IDC_HFCOMMAGENTCTRL1, 1, CForeignFutSiseDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CForeignFutSiseDlg, IDC_HFCOMMAGENTCTRL1, 2, CForeignFutSiseDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CForeignFutSiseDlg, IDC_HFCOMMAGENTCTRL1, 3, CForeignFutSiseDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
END_EVENTSINK_MAP()

// CForeignFutSiseDlg �޽��� ó����

void CForeignFutSiseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CForeignFutSiseDlg::OnPaint()
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
HCURSOR CForeignFutSiseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CForeignFutSiseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CForeignFutSiseDlg::OnDestroy()
{
	//��� �ǽð������ �����Ѵ�.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();

	CDialog::OnDestroy();
}

void CForeignFutSiseDlg::OnRdoSelectServer(UINT nID)
{
	m_nSeverType = nID - IDC_CON_REAL;

	/*----------------------------------
	���Ӽ����� �����Ѵ�.(0 - ����, 1 - ��������, 2 - �ؿܸ���)
	*----------------------------------*/
	m_CommAgent.SetLoginMode(0, m_nSeverType);
}


void CForeignFutSiseDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CForeignFutSiseDlg::OnTimer(UINT_PTR nIDEvent)
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

void CForeignFutSiseDlg::OnNMDblclkListSymbol(NMHDR *pNMHDR, LRESULT *pResult)
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

	((CButton*)GetDlgItem(IDC_RAD_QRY1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RAD_QRY3))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RAD_QRY5))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RAD_QRY7))->SetCheck(1);

	((CButton*)GetDlgItem(IDC_RAD_QRY2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RAD_QRY4))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RAD_QRY6))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RAD_QRY8))->SetCheck(0);

	//�Էµ� �����ڵ�� ����ȸ ��û�� �Ѵ�.
	OnBnClickedBtnReqPrice();	//�ؿܼ��� ���簡 ��ȸ
	OnBnClickedBtnReqHoga();	//�ؿܼ��� 5�ܰ�ȣ�� ��ȸ
	OnBnClickedBtnReqTick();	//�ؿܼ��� �ð��뺰ü�� ��ȸ
	OnBnClickedBtnReqChart();	//�ؿܼ��� ��Ʈ������ ��ȸ
}

void CForeignFutSiseDlg::OnNMDblclkListSymbol2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;

	CString strSymbol = m_listCode2.GetItemText(nSelectRow, 0); //�����ڵ�
	CString strStandardCode = m_listCode2.GetItemText(nSelectRow, 1); //ǥ�������ڵ�
	CString strSymbolName = m_listCode2.GetItemText(nSelectRow, 2); //�ѱ������
	CString strPrice = m_listCode2.GetItemText(nSelectRow, 3); //���ذ�

	if (strSymbol.IsEmpty())
		return;

	//�����ڵ带 �Է��Ѵ�.
	m_editSymbol.SetWindowText(strStandardCode);		//5�ܰ�ȣ�� �����ڵ�(�ɺ�)
	m_editSymbolPrice.SetWindowText(strStandardCode);	//���簡 �����ڵ�(�ɺ�)
	m_editSymbolTick.SetWindowText(strStandardCode);	//�ð��뺰ü�� �����ڵ�(�ɺ�)
	m_editSymbolChart.SetWindowText(strStandardCode);	//��Ʈ �����ڵ�(�ɺ�)

	GetDlgItem(IDC_SYMBOL_NAME)->SetWindowText(strSymbolName);		//5�ܰ�ȣ�� �����
	GetDlgItem(IDC_SYMBOL_NAME_PRICE)->SetWindowText(strSymbolName);//���簡 �����
	GetDlgItem(IDC_SYMBOL_NAME_TICK)->SetWindowText(strSymbolName);	//�ð��뺰ü�� �����
	GetDlgItem(IDC_SYMBOL_NAME_CHART)->SetWindowText(strSymbolName);//��Ʈ ������ �����

	((CButton*)GetDlgItem(IDC_RAD_QRY1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RAD_QRY3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RAD_QRY5))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RAD_QRY7))->SetCheck(0);

	((CButton*)GetDlgItem(IDC_RAD_QRY2))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RAD_QRY4))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RAD_QRY6))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RAD_QRY8))->SetCheck(1);

	//�Էµ� �����ڵ�� ����ȸ ��û�� �Ѵ�.
	OnBnClickedBtnReqPrice();	//�ؿܼ��� ���簡 ��ȸ
	OnBnClickedBtnReqHoga();	//�ؿܼ��� 5�ܰ�ȣ�� ��ȸ
	OnBnClickedBtnReqTick();	//�ؿܼ��� �ð��뺰ü�� ��ȸ
	OnBnClickedBtnReqChart();	//�ؿܼ��� ��Ʈ������ ��ȸ
}

void CForeignFutSiseDlg::OnRadioChartTerm(UINT nID)
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
BOOL CForeignFutSiseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CString strTitle;
	strTitle.Format("%s-[�ؿܼ��� �ü�](%s)", PROGRAM_NAME, VERSION_INFO);
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
	* �ؿܼ��� �ð��뺰ü�ᰡ ����Ʈ ��Ʈ�� �ʱ�ȭ
	**********************************/
	InitListTick();

	/**********************************
	* �ؿܼ��� ���� ����Ʈ ��Ʈ�� �ʱ�ȭ
	**********************************/
	InitListCode();

	/**********************************
	* �ؿܼ��� ��Ʈ ����Ʈ ��Ʈ�� �ʱ�ȭ
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
	//�ǽýð� ��� ���ҽ������� �����ڰ� ���� ��θ� ���� �ε����� ������
	//HFCommAgent.dll������ ��ġ�� RealRes �������� �ڵ����� �ε��Ѵ�.
	//�ؿܼ���ü�� �ǽð� I/O ���� ���ҽ� ����
	if (!m_CommAgent.LoadRealResource(strApidAgentModulePath + "/RealRes/V10.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());

	//�ؿܼ���ȣ�� �ǽð� I/O ���� ���ҽ� ����
	if (!m_CommAgent.LoadRealResource(strApidAgentModulePath + "/RealRes/V11.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
#endif
	//��Ʈ �ؿܼ��� ���� ƽ���� ����
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
// Function      : �ؿܼ��� �ð��뺰ü�� ����Ʈ ��Ʈ�� �ʱ�ȭ
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::InitListTick()
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
// Function      : �ؿܼ��� ���� ����Ʈ ��Ʈ�� �ʱ�ȭ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::InitListCode()
{
	m_listCode.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int arrWidth[39] = { 0x00 };
	
	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("�����ڵ�"), _T("�ü������ڵ�"), _T("�ؿ��Ļ���ǰ��"), _T("ǰ���ڵ�"),
		_T("�ؿ��Ļ�ǰ���"), _T("��簡��"), _T("�����ڵ�"), _T("�ŷ����ڵ�"), _T("ǰ���������и�"),
		_T("���ݼҼ�������"), _T("����"), _T("TickSize"), _T("�ּҰ��ݺ����ݾ�"), _T("ȯ��¼�"),
		_T("������"), _T("��Ź���ű�"), _T("�������ű�"), _T("��������"), _T("�����ŷ���(LTD)"),
		_T("��������"), _T("������"), _T("������ȭ"), _T("ǥ����ȭ"), _T("�ٿ�������"),
		_T("�����ϼ�"), _T("Active Flag"), _T("���ذ�"), _T("��������"), _T("���ϰŷ���"),
		_T("�ŷ����� ����"), _T("���۽ð�"), _T("����ð�"), _T("����۽ð�(�ѱ�)"),
		_T("������ð�(�ѱ�)"), _T("�����ŷ���"), _T("��������, �ŷ�����"), _T("�����İ�"),
		_T("����������"), _T("���ΰŷ���") };

	int i;
	CDC* pDC = GetDC();
	CSize size;

	for (i = 0; i < 39; i++)
	{
		size = pDC->GetTextExtent(strTitle[i]);
		arrWidth[i] = size.cx;
	}

	for (i = 0; i < 39; i++)
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

	//�ɼ����� ����Ʈ
	m_listCode2.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	for (i = 0; i < 39; i++)
	{
		size = pDC->GetTextExtent(strTitle[i]);
		arrWidth[i] = size.cx;
	}

	for (i = 0; i < 39; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		if (i == 0)
			lvcolumn.fmt = LVCFMT_CENTER;
		else
			lvcolumn.fmt = LVCFMT_LEFT;

		lvcolumn.pszText = strTitle[i];

		lvcolumn.iSubItem = i;
		lvcolumn.cx = arrWidth[i];
		m_listCode2.InsertColumn(i, &lvcolumn);
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
void CForeignFutSiseDlg::InitListChart()
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
CString CForeignFutSiseDlg::GetDiffSign(CString strSignCode)
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
void CForeignFutSiseDlg::SetHogaData(CString* arrSellHoga, CString* arrBuyHoga, CString* arrSellRemain,
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
void CForeignFutSiseDlg::OnBnClickedInitcomm()
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
void CForeignFutSiseDlg::OnBnClickedTerminate()
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
void CForeignFutSiseDlg::OnBnClickedLogin()
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
void CForeignFutSiseDlg::OnBnClickedLogout()
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
// Function      : �ؿܼ��� ���� ����Ʈ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqCodeList()
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

	//�ؿܼ��� ���� ����Ʈ(������) ��Ʈ�� ������ �ʱ�ȭ
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
	strMarketCode = _T("FF");	//�ؿܼ���

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("3299"));		//GID

	//�������� �������� ����׸��.
	CString strOutputFidList;

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	0001 : �����ڵ�(����)
	0002 : �ü������ڵ�
	0003 : �ؿ��Ļ���ǰ��
	1448 : ǰ���ڵ�
	2083 : �ؿ��Ļ�ǰ���
	0661 : ��簡��
	1170 : �����ڵ�
	1987 : �ŷ����ڵ�
	2467 : ǰ���������и�
	2456 : ���ݼҼ�������
	2457 : ����
	2295 : Tick Size
	1396 : �ּҰ��ݺ����ݾ�
	1773 : ȯ��¼�
	1772 : ������, ���ũ��
	1731 : ��Ź���ű�
	2460 : �������ű�
	0226 : ��������
	0132 : �����ŷ���(LTD)
	0981 : ��������(Expire Date)
	1203 : ������(Expire Month/Year)
	1268 : ������ȭ(�ŷ���ȭ?)
	1171 : ǥ����ȭ
	2459 : �ٿ�������
	0133 : �����ϼ�
	1759 : Active Flag
	0016 : ���ذ�
	0010 : ��������
	0028 : ���ϰŷ���
	1762 : �ŷ����� ����
	1870 : ���۽ð�
	1871 : ����ð�
	2486 : ����۽ð�(�ѱ�)
	2487 : ������ð�(�ѱ�)
	0815 : �����ŷ���
	0009 : ��������, �ŷ�����
	0128 : �����İ�
	0129 : ����������
	2596 : ���ΰŷ����ڵ�*/
	strOutputFidList =	"1,2,3,1448,2083,661,1170,1987,2467,2456,2457,2295,1396,"
						"1773,1772,1731,2460,226,132,981,1203,1268,1171,"
						"2459,133,1759,16,10,28,1762,1870,1871,2486,2487,"
						"815,9,128,129, 2596";

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
// Function      : �ؿܼ��� ���� ����Ʈ ���� ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqCodeListNext()
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
	strMarketCode = _T("FF"); //�ؿܼ���

	/**********************************
	* 2. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("3299"));		//GID

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 3. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	0001 : �����ڵ�(����)
	0002 : �ü������ڵ�
	0003 : �ؿ��Ļ���ǰ��
	1448 : ǰ���ڵ�
	2083 : �ؿ��Ļ�ǰ���
	0661 : ��簡��
	1170 : �����ڵ�
	1987 : �ŷ����ڵ�
	2467 : ǰ���������и�
	2456 : ���ݼҼ�������
	2457 : ����
	2295 : Tick Size
	1396 : �ּҰ��ݺ����ݾ�
	1773 : ȯ��¼�
	1772 : ������, ���ũ��
	1731 : ��Ź���ű�
	2460 : �������ű�
	0226 : ��������
	0132 : �����ŷ���(LTD)
	0981 : ��������(Expire Date)
	1203 : ������(Expire Month/Year)
	1268 : ������ȭ(�ŷ���ȭ?)
	1171 : ǥ����ȭ
	2459 : �ٿ�������
	0133 : �����ϼ�
	1759 : Active Flag
	0016 : ���ذ�
	0010 : ��������
	0028 : ���ϰŷ���
	1762 : �ŷ����� ����
	1870 : ���۽ð�
	1871 : ����ð�
	2486 : ����۽ð�(�ѱ�)
	2487 : ������ð�(�ѱ�)
	0815 : �����ŷ���
	0009 : ��������, �ŷ�����
	0128 : �����İ�
	0129 : ����������
	2596 : ���ΰŷ����ڵ�*/
	strOutputFidList =	"1,2,3,1448,2083,661,1170,1987,2467,2456,2457,2295,1396,"
						"1773,1772,1731,2460,226,132,981,1203,1268,1171,"
						"2459,133,1759,16,10,28,1762,1870,1871,2486,2487,"
						"815,9,128,129,2596";

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
void CForeignFutSiseDlg::OnBnClickedBtnReqPrice()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strMarketCode;		//���屸��
	CString strRealName;

	if (((CButton*)GetDlgItem(IDC_RAD_QRY5))->GetCheck())
	{
		strMarketCode = _T("FF");	//�ؿܼ���
		strRealName = _T("V10"); //�ؿܼ���ü�� Real name
	}
	else
	{
		strMarketCode = _T("FO");	//�ؿܿɼ�
		strRealName = _T("V20"); //�ؿܿɼ�ü�� Real name
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
	* 2. ������ ��ϵ� �ؿܼ���ü��(���簡) �ǽð���� ����.
	**********************************/
	if (!m_strCurPriceRealKey.IsEmpty())
	{
		m_CommAgent.UnRegisterReal(strRealName, m_strCurPriceRealKey);
		m_strCurPriceRealKey.Empty();
	}

	//�ؿܼ���ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
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
// Function      : �ؿܼ���ȣ�� ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqHoga()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strMarketCode;		//���屸���ڵ�
	CString strRealName;

	if (((CButton*)GetDlgItem(IDC_RAD_QRY1))->GetCheck())
	{
		strMarketCode = _T("FF");	//�ؿܼ���
		strRealName = _T("V11"); //�ؿܼ���ü�� Real name
	}
	else
	{
		strMarketCode = _T("FO");	//�ؿܿɼ�
		strRealName = _T("V21"); //�ؿܿɼ�ü�� Real name
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
	* 2. ������ ��ϵ� �ؿ�ȣ�� �ǽð���� ����
	**********************************/
	if (!m_strHogaRealKey.IsEmpty())
	{
		m_CommAgent.UnRegisterReal(strRealName, m_strHogaRealKey);
		m_strHogaRealKey.Empty();
	}

	//�ؿ�ȣ�� �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
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
// Function      : �ؿܼ��� �ð��뺰ü�� ������ ��ȸ(���Ӱŷ� �����Ͱ� �ִ� ���)
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqTick()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strMarketCode;		//���屸���ڵ�
	CString strRealName;

	if (((CButton*)GetDlgItem(IDC_RAD_QRY3))->GetCheck())
	{
		strMarketCode = _T("FF");	//�ؿܼ���
		strRealName = _T("V10"); //�ؿܼ���ü�� Real name
	}
	else
	{
		strMarketCode = _T("FO");	//�ؿܿɼ�
		strRealName = _T("V20"); //�ؿܿɼ�ü�� Real name
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

	//�ؿܼ��� �ð��뺰ü�� ����Ʈ ��Ʈ�� ������ �ʱ�ȭ
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
	* 3. ������ ��ϵ� �ؿܼ���ü��(���簡) �ǽð���� ����.
	**********************************/
	if (!m_strTickRealKey.IsEmpty())
	{
		m_CommAgent.UnRegisterReal(strRealName, m_strTickRealKey);
		m_strTickRealKey.Empty();
	}

	//�ؿܼ���ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
	m_strTickRealKey = strSymBol;

	/**********************************
	* 4. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9002"), strSymBol);		//����ɺ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("GID"), _T("1003"));		//GID

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
// Function      : �ؿܼ��� �ð��뺰ü�� ���� ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqTickNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strMarketCode;		//���屸���ڵ�
	
	if (((CButton*)GetDlgItem(IDC_RAD_QRY3))->GetCheck())
	{
		strMarketCode = _T("FF");	//�ؿܼ���
	}
	else
	{
		strMarketCode = _T("FO");	//�ؿܿɼ�
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

	/**********************************
	* 2. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9002"), strSymBol);		//����ɺ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("GID"), _T("1003"));		//GID

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
// Function      : �ؿܼ��� ��Ʈ ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqChart()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strMarketCode;		//���屸���ڵ�

	if (((CButton*)GetDlgItem(IDC_RAD_QRY7))->GetCheck())
	{
		strMarketCode = _T("FF");	//�ؿܼ���
	}
	else
	{
		strMarketCode = _T("FO");	//�ؿܿɼ�
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

	//�ؿܼ��� �ð��뺰ü�� ����Ʈ ��Ʈ�� ������ �ʱ�ȭ
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
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);		//������

		if (_ttoi(strChartCnt) > 0)
		{
			nRecvCnt = _ttoi(strChartCnt);
			m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strChartCnt);	//9119 : ƽ �Ǽ�
		}

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1003")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MIN))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);		//������

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
	����(9), �ð�(8), ����(4), �ð�(13), ��(14), ����(15), ü�ᷮ(83), �ŷ���(11) */
	/*strOutputFidList = "9,8,4,13,14,15,83,11";*/
	//1173,1174 �ѱ� ����/�ð�
	strOutputFidList = "1173,1174,4,13,14,15,83,11";

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
// Function      : �ؿܼ��� ��Ʈ ���� ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqChartNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	CString strMarketCode;		//���屸���ڵ�

	if (((CButton*)GetDlgItem(IDC_RAD_QRY7))->GetCheck())
	{
		strMarketCode = _T("FF");	//�ؿܼ���
	}
	else
	{
		strMarketCode = _T("FO");	//�ؿܿɼ�
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

	if (((CButton*)GetDlgItem(IDC_RADIO_TICK))->GetCheck()) //ƽ
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);	//������

		if (_ttoi(strChartCnt) > 0)
		{
			nRecvCnt = _ttoi(strChartCnt);
			m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strChartCnt);	//9119 : ƽ �Ǽ�
		}

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1003")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MIN))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);	//������

		CString strMin;
		strMin.Format(_T("%d"), _ttoi(strChartCnt) * 60);

		//9119 : �����ڵ�( 30: 30��, 60: 1��, 600: 10��, 3600: 60��, 60*N: N�� )
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strMin);

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1006")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_DAY))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);	//������
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);	//������

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1008")); //GID

	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_WEEK))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);	//������
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);	//������

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "W");				//��(W), ��(M)

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1009")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MON))->GetCheck()) //��
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);	//������
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);	//������

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "M");				//��(W), ��(M)

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1010")); //GID
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

void CForeignFutSiseDlg::OnBnClickedOk()
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
void CForeignFutSiseDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
void CForeignFutSiseDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
	* �ؿܼ��� ���� ����Ʈ(������) ��ȸ ������ ���� ó��
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
		CString arrItemValue[39];

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			arrItemValue[0] = m_CommAgent.GetFidOutputData(nRequestId, "1", i);			//�����ڵ�(����)
			
			if (m_CommAgent.VerifyRequestCode(arrItemValue[0]))
				continue;
			
			arrItemValue[1] = m_CommAgent.GetFidOutputData(nRequestId, "2", i);			//�ü������ڵ�
			arrItemValue[2] = m_CommAgent.GetFidOutputData(nRequestId, "3", i);			//�ؿ��Ļ���ǰ��
			arrItemValue[3] = m_CommAgent.GetFidOutputData(nRequestId, "1448", i);		//ǰ���ڵ�
			arrItemValue[4] = m_CommAgent.GetFidOutputData(nRequestId, "2083", i);		//�ؿ��Ļ�ǰ���
			arrItemValue[5] = m_CommAgent.GetFidOutputData(nRequestId, "661", i);		//��簡��
			arrItemValue[6] = m_CommAgent.GetFidOutputData(nRequestId, "1170", i);		//�����ڵ�
			arrItemValue[7] = m_CommAgent.GetFidOutputData(nRequestId, "1987", i);		//�ŷ����ڵ�
			arrItemValue[8] = m_CommAgent.GetFidOutputData(nRequestId, "2467", i);		//ǰ���������и�
			arrItemValue[9] = m_CommAgent.GetFidOutputData(nRequestId, "2456", i);		//���ݼҼ�������
			arrItemValue[10] = m_CommAgent.GetFidOutputData(nRequestId, "2457", i);		//����
			arrItemValue[11] = m_CommAgent.GetFidOutputData(nRequestId, "2295", i);		//Tick Size
			arrItemValue[12] = m_CommAgent.GetFidOutputData(nRequestId, "1396", i);		//�ּҰ��ݺ����ݾ�
			arrItemValue[13] = m_CommAgent.GetFidOutputData(nRequestId, "1773", i);		//ȯ��¼�
			arrItemValue[14] = m_CommAgent.GetFidOutputData(nRequestId, "1772", i);		//������, ���ũ��
			arrItemValue[15] = m_CommAgent.GetFidOutputData(nRequestId, "1731", i);		//��Ź���ű�
			arrItemValue[16] = m_CommAgent.GetFidOutputData(nRequestId, "2460", i);		//�������ű�
			arrItemValue[17] = m_CommAgent.GetFidOutputData(nRequestId, "226", i);		//��������
			arrItemValue[18] = m_CommAgent.GetFidOutputData(nRequestId, "132", i);		//�����ŷ���(LTD)
			arrItemValue[19] = m_CommAgent.GetFidOutputData(nRequestId, "981", i);		//��������(Expire Date)
			arrItemValue[20] = m_CommAgent.GetFidOutputData(nRequestId, "1203", i);		//������(Expire Month / Year)
			arrItemValue[21] = m_CommAgent.GetFidOutputData(nRequestId, "1268", i);		//������ȭ(�ŷ���ȭ ? )
			arrItemValue[22] = m_CommAgent.GetFidOutputData(nRequestId, "1171", i);		//ǥ����ȭ
			arrItemValue[23] = m_CommAgent.GetFidOutputData(nRequestId, "2459", i);		//�ٿ�������
			arrItemValue[24] = m_CommAgent.GetFidOutputData(nRequestId, "133", i);		//�����ϼ�
			arrItemValue[25] = m_CommAgent.GetFidOutputData(nRequestId, "1759", i);		//Active Flag
			arrItemValue[26] = m_CommAgent.GetFidOutputData(nRequestId, "16", i);		//���ذ�
			arrItemValue[27] = m_CommAgent.GetFidOutputData(nRequestId, "10", i);		//��������
			arrItemValue[28] = m_CommAgent.GetFidOutputData(nRequestId, "28", i);		//���ϰŷ���
			arrItemValue[29] = m_CommAgent.GetFidOutputData(nRequestId, "1762", i);		//�ŷ����� ����
			arrItemValue[30] = m_CommAgent.GetFidOutputData(nRequestId, "1870", i);		//���۽ð�
			arrItemValue[31] = m_CommAgent.GetFidOutputData(nRequestId, "1871", i);		//����ð�
			arrItemValue[32] = m_CommAgent.GetFidOutputData(nRequestId, "2486", i);		//����۽ð�(�ѱ�)
			arrItemValue[33] = m_CommAgent.GetFidOutputData(nRequestId, "2487", i);		//������ð�(�ѱ�)
			arrItemValue[34] = m_CommAgent.GetFidOutputData(nRequestId, "815", i);		//�����ŷ���
			arrItemValue[35] = m_CommAgent.GetFidOutputData(nRequestId, "9", i);			//��������, �ŷ�����
			arrItemValue[36] = m_CommAgent.GetFidOutputData(nRequestId, "128", i);		//�����İ�
			arrItemValue[37] = m_CommAgent.GetFidOutputData(nRequestId, "129", i);		//����������
			arrItemValue[38] = m_CommAgent.GetFidOutputData(nRequestId, "2596", i);		//���ΰŷ����ڵ�

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listCode.InsertItem(&lvItem);

			//����Ʈ ��Ʈ�ѿ� �׸� ���� �Է��Ѵ�.
			for (int col = 0; col < 39; col++)
			{
				m_listCode.SetItemText(nListIndex, col, (LPTSTR)(LPCTSTR)arrItemValue[col]);
			}


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
		m_nRqIdCodeList = 0;	//�ؿܼ��� ���� ����Ʈ(������) ��ȸ Request ID
	}
	/***************************************
	* �ؿܿɼ� ���� ����Ʈ(������) ��ȸ ������ ���� ó��
	****************************************/
	else if (m_nRqIdCodeList2 == nRequestId)
	{
		CString strCode;			//�����ڵ�
		CString strStandardCode;	//ǥ���ڵ�
		CString strCodeName;		//�ѱ������
		CString strPrice;			//���ذ�

		m_listCode2.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;

		/*--------------------------------------
		���� ��ȸ ������ �����̸� ������ ���� ����Ÿ �ڿ�
		�ٿ� �����Ѵ�.
		---------------------------------------*/
		int nViewScrollPos = 0;
		if (!m_strCodeListNextRqKey2.IsEmpty())
		{
			nListIndex = m_listCode2.GetItemCount();
			nViewScrollPos = nListIndex;
		}

		int nDataCnt = m_CommAgent.GetFidOutputRowCnt(nRequestId);
		CString arrItemValue[39];

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			arrItemValue[0] = m_CommAgent.GetFidOutputData(nRequestId, "1", i);			//�����ڵ�(����)
			arrItemValue[1] = m_CommAgent.GetFidOutputData(nRequestId, "2", i);			//�ü������ڵ�
			arrItemValue[2] = m_CommAgent.GetFidOutputData(nRequestId, "3", i);			//�ؿ��Ļ���ǰ��
			arrItemValue[3] = m_CommAgent.GetFidOutputData(nRequestId, "1448", i);		//ǰ���ڵ�
			arrItemValue[4] = m_CommAgent.GetFidOutputData(nRequestId, "2083", i);		//�ؿ��Ļ�ǰ���
			arrItemValue[5] = m_CommAgent.GetFidOutputData(nRequestId, "661", i);		//��簡��
			arrItemValue[6] = m_CommAgent.GetFidOutputData(nRequestId, "1170", i);		//�����ڵ�
			arrItemValue[7] = m_CommAgent.GetFidOutputData(nRequestId, "1987", i);		//�ŷ����ڵ�
			arrItemValue[8] = m_CommAgent.GetFidOutputData(nRequestId, "2467", i);		//ǰ���������и�
			arrItemValue[9] = m_CommAgent.GetFidOutputData(nRequestId, "2456", i);		//���ݼҼ�������
			arrItemValue[10] = m_CommAgent.GetFidOutputData(nRequestId, "2457", i);		//����
			arrItemValue[11] = m_CommAgent.GetFidOutputData(nRequestId, "2295", i);		//Tick Size
			arrItemValue[12] = m_CommAgent.GetFidOutputData(nRequestId, "1396", i);		//�ּҰ��ݺ����ݾ�
			arrItemValue[13] = m_CommAgent.GetFidOutputData(nRequestId, "1773", i);		//ȯ��¼�
			arrItemValue[14] = m_CommAgent.GetFidOutputData(nRequestId, "1772", i);		//������, ���ũ��
			arrItemValue[15] = m_CommAgent.GetFidOutputData(nRequestId, "1731", i);		//��Ź���ű�
			arrItemValue[16] = m_CommAgent.GetFidOutputData(nRequestId, "2460", i);		//�������ű�
			arrItemValue[17] = m_CommAgent.GetFidOutputData(nRequestId, "226", i);		//��������
			arrItemValue[18] = m_CommAgent.GetFidOutputData(nRequestId, "132", i);		//�����ŷ���(LTD)
			arrItemValue[19] = m_CommAgent.GetFidOutputData(nRequestId, "981", i);		//��������(Expire Date)
			arrItemValue[20] = m_CommAgent.GetFidOutputData(nRequestId, "1203", i);		//������(Expire Month / Year)
			arrItemValue[21] = m_CommAgent.GetFidOutputData(nRequestId, "1268", i);		//������ȭ(�ŷ���ȭ ? )
			arrItemValue[22] = m_CommAgent.GetFidOutputData(nRequestId, "1171", i);		//ǥ����ȭ
			arrItemValue[23] = m_CommAgent.GetFidOutputData(nRequestId, "2459", i);		//�ٿ�������
			arrItemValue[24] = m_CommAgent.GetFidOutputData(nRequestId, "133", i);		//�����ϼ�
			arrItemValue[25] = m_CommAgent.GetFidOutputData(nRequestId, "1759", i);		//Active Flag
			arrItemValue[26] = m_CommAgent.GetFidOutputData(nRequestId, "16", i);		//���ذ�
			arrItemValue[27] = m_CommAgent.GetFidOutputData(nRequestId, "10", i);		//��������
			arrItemValue[28] = m_CommAgent.GetFidOutputData(nRequestId, "28", i);		//���ϰŷ���
			arrItemValue[29] = m_CommAgent.GetFidOutputData(nRequestId, "1762", i);		//�ŷ����� ����
			arrItemValue[30] = m_CommAgent.GetFidOutputData(nRequestId, "1870", i);		//���۽ð�
			arrItemValue[31] = m_CommAgent.GetFidOutputData(nRequestId, "1871", i);		//����ð�
			arrItemValue[32] = m_CommAgent.GetFidOutputData(nRequestId, "2486", i);		//����۽ð�(�ѱ�)
			arrItemValue[33] = m_CommAgent.GetFidOutputData(nRequestId, "2487", i);		//������ð�(�ѱ�)
			arrItemValue[34] = m_CommAgent.GetFidOutputData(nRequestId, "815", i);		//�����ŷ���
			arrItemValue[35] = m_CommAgent.GetFidOutputData(nRequestId, "9", i);			//��������, �ŷ�����
			arrItemValue[36] = m_CommAgent.GetFidOutputData(nRequestId, "128", i);		//�����İ�
			arrItemValue[37] = m_CommAgent.GetFidOutputData(nRequestId, "129", i);		//����������
			arrItemValue[38] = m_CommAgent.GetFidOutputData(nRequestId, "2596", i);		//���ΰŷ����ڵ�

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listCode2.InsertItem(&lvItem);

			//����Ʈ ��Ʈ�ѿ� �׸� ���� �Է��Ѵ�.
			for (int col = 0; col < 39; col++)
			{
				m_listCode2.SetItemText(nListIndex, col, (LPTSTR)(LPCTSTR)arrItemValue[col]);
			}


		}//End of for

		m_listCode2.EnsureVisible(nViewScrollPos, FALSE);
		m_listCode2.SetRedraw(TRUE);

		/*--------------------------------------
		������ȸŰ�� ������ ���´�.
		---------------------------------------*/
		m_strCodeListNextRqKey2 = strPreNextContext;

		/*--------------------------------------
		������ȸŰ�� '2', '3'�̸� '����'��ư�� Ȱ��ȭ ��Ų��.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_CODE_LIST_NEXT2)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_CODE_LIST_NEXT2)->EnableWindow(FALSE);

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdCodeList2 = 0;	//�ؿܼ��� ���� ����Ʈ(������) ��ȸ Request ID
	}
	/***************************************
	* �ؿܼ��� 5�ܰ�ȣ�� ��ȸ ������ ���� ó��
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
		�ؿܼ���ȣ�� �ǽð�Ű�� �ǽð��� ����Ѵ�.
		�ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		---------------------------------------*/
		if (!m_strHogaRealKey.IsEmpty())
		{
			CString strRealName;

			if (((CButton*)GetDlgItem(IDC_RAD_QRY1))->GetCheck())
			{
				strRealName = _T("V11"); //�ؿܼ���ü�� Real name
			}
			else
			{
				strRealName = _T("V21"); //�ؿܿɼ�ü�� Real name
			}

			m_CommAgent.RegisterReal(strRealName, m_strHogaRealKey); //�ǽð� ���
		}

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdHoga = 0;	//�ؿܼ��� 5�ܰ�ȣ�� ��ȸ Request ID
	}
	/***************************************
	* �ؿܼ��� ���簡 ��ȸ ������ ���� ó��
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
		������ ü��(���簡) �ǽð����Ű�� �ǽð��� ����Ѵ�.
		�ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		---------------------------------------*/
		if (!m_strCurPriceRealKey.IsEmpty())
		{
			CString strRealName;

			if (((CButton*)GetDlgItem(IDC_RAD_QRY5))->GetCheck())
			{
				strRealName = _T("V10"); //�ؿܼ���ü�� Real name
			}
			else
			{
				strRealName = _T("V20"); //�ؿܿɼ�ü�� Real name
			}

			m_CommAgent.RegisterReal(strRealName, m_strCurPriceRealKey); //�ǽð� ���
		}

		/*--------------------------------------
		�ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		---------------------------------------*/
		m_nRqIdCurPrice = 0;	//�ؿܼ��� ���簡 ��ȸ Request ID
	}
	/***************************************
	* �ؿܼ��� �ð��뺰ü�� ��ȸ ������ ���� ó��
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
		����ü�� �ǽð��� ����Ѵ�.
		�ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		---------------------------------------*/
		if (!m_strTickRealKey.IsEmpty() && m_strTickNextRqKey.IsEmpty())
		{
			CString strRealName;

			if (((CButton*)GetDlgItem(IDC_RAD_QRY3))->GetCheck())
			{
				strRealName = _T("V10"); //�ؿܼ���ü�� Real name
			}
			else
			{
				strRealName = _T("V20"); //�ؿܿɼ�ü�� Real name
			}

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
		m_nRqIdTick = 0;	//�ؿܼ��� �ð��뺰ü�� ��ȸ Request ID

	}
	/***************************************
	* �ؿܼ��� ��Ʈ ��ȸ ������ ���� ó��
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
		m_nRqIdChart = 0;	//�ؿܼ��� ���� ����Ʈ(������) ��ȸ Request ID

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
void CForeignFutSiseDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/* ���� : OnGetRealData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
	�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/

	/***************************************
	* �ؿܼ��� ȣ�� �ǽð� ������ ����
	****************************************/
	if (!_tcscmp(strRealName, "V11") ||
		!_tcscmp(strRealName, "V21"))
	{
		/*--------------------------------------
		��ȸ ������ ����� �ؿܼ��� ȣ�� �ǽð�Ű�� �������� ��
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
			arrSellHoga[0] = realCommRecvData.GetItem(0, 29);		//�ŵ�1ȣ��
			arrSellHoga[1] = realCommRecvData.GetItem(0, 33);		//�ŵ�2ȣ��
			arrSellHoga[2] = realCommRecvData.GetItem(0, 37);		//�ŵ�3ȣ��
			arrSellHoga[3] = realCommRecvData.GetItem(0, 41);		//�ŵ�4ȣ��
			arrSellHoga[4] = realCommRecvData.GetItem(0, 45);	//�ŵ�5ȣ��SEQ��

			arrSellRemain[0] = realCommRecvData.GetItem(0, 31);	//�ŵ�1ȣ���ܷ�
			arrSellRemain[1] = realCommRecvData.GetItem(0, 35);	//�ŵ�2ȣ���ܷ�
			arrSellRemain[2] = realCommRecvData.GetItem(0, 39);	//�ŵ�3ȣ���ܷ�
			arrSellRemain[3] = realCommRecvData.GetItem(0, 43);	//�ŵ�4ȣ���ܷ�
			arrSellRemain[4] = realCommRecvData.GetItem(0, 47);	//�ŵ�5ȣ���ܷ�

			arrSellCnt[0] = realCommRecvData.GetItem(0, 32);		//�ŵ�1ȣ���Ǽ�
			arrSellCnt[1] = realCommRecvData.GetItem(0, 36);		//�ŵ�2ȣ���Ǽ�
			arrSellCnt[2] = realCommRecvData.GetItem(0, 40);		//�ŵ�3ȣ���Ǽ�
			arrSellCnt[3] = realCommRecvData.GetItem(0, 44);		//�ŵ�4ȣ���Ǽ�
			arrSellCnt[4] = realCommRecvData.GetItem(0, 48);		//�ŵ�5ȣ���Ǽ�

			arrBuyHoga[0] = realCommRecvData.GetItem(0, 7);		//�ż�1ȣ��
			arrBuyHoga[1] = realCommRecvData.GetItem(0, 11);		//�ż�2ȣ��
			arrBuyHoga[2] = realCommRecvData.GetItem(0, 15);		//�ż�3ȣ��
			arrBuyHoga[3] = realCommRecvData.GetItem(0, 19);		//�ż�4ȣ��
			arrBuyHoga[4] = realCommRecvData.GetItem(0, 23);		//�ż�5ȣ��

			arrBuyRemain[0] = realCommRecvData.GetItem(0, 9);	//�ż�1ȣ���ܷ�
			arrBuyRemain[1] = realCommRecvData.GetItem(0, 13);	//�ż�2ȣ���ܷ�
			arrBuyRemain[2] = realCommRecvData.GetItem(0, 17);	//�ż�3ȣ���ܷ�
			arrBuyRemain[3] = realCommRecvData.GetItem(0, 21);	//�ż�4ȣ���ܷ�
			arrBuyRemain[4] = realCommRecvData.GetItem(0, 25);	//�ż�5ȣ���ܷ�

			arrBuyCnt[0] = realCommRecvData.GetItem(0, 10);		//�ż�1ȣ���Ǽ�
			arrBuyCnt[1] = realCommRecvData.GetItem(0, 14);		//�ż�2ȣ���Ǽ�
			arrBuyCnt[2] = realCommRecvData.GetItem(0, 18);		//�ż�3ȣ���Ǽ�
			arrBuyCnt[3] = realCommRecvData.GetItem(0, 22);		//�ż�4ȣ���Ǽ�
			arrBuyCnt[4] = realCommRecvData.GetItem(0, 26);		//�ż�5ȣ���Ǽ�

#else		/*--------------------------------------
			������Ʈ ��Ʈ���� GetRealOutputData �Լ��� �����ۺ� �����͸� ������.
			---------------------------------------*/
			/*--------------------------------------
			�����۸����� ���ŵ� �ǽð� �����͸� �׸񺰷� ������.
			---------------------------------------*/
			//�ŵ� 1~5ȣ��
			arrSellHoga[0] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASK1");
			arrSellHoga[1] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASK2");
			arrSellHoga[2] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASK3");
			arrSellHoga[3] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASK4");
			arrSellHoga[4] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASK5");
			//�ŵ� 1~5ȣ���ܷ�
			arrSellRemain[0] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASIZ1");
			arrSellRemain[1] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASIZ2");
			arrSellRemain[2] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASIZ3");
			arrSellRemain[3] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASIZ4");
			arrSellRemain[4] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASIZ5");
			//�ŵ� 1~5ȣ���Ǽ�
			arrSellCnt[0] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ACNT1");
			arrSellCnt[1] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ACNT2");
			arrSellCnt[2] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ACNT3");
			arrSellCnt[3] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ACNT4");
			arrSellCnt[4] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ACNT5");

			//�ż� 1~5ȣ��
			arrBuyHoga[0] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BID1");
			arrBuyHoga[1] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BID2");
			arrBuyHoga[2] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BID3");
			arrBuyHoga[3] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BID4");
			arrBuyHoga[4] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BID5");
			//�ż� 1~5ȣ���ܷ�
			arrBuyRemain[0] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BSIZ1");
			arrBuyRemain[1] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BSIZ2");
			arrBuyRemain[2] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BSIZ3");
			arrBuyRemain[3] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BSIZ4");
			arrBuyRemain[4] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BSIZ5");
			//�ż� 1~5ȣ���Ǽ�
			arrBuyCnt[0] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BCNT1");
			arrBuyCnt[1] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BCNT2");
			arrBuyCnt[2] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BCNT3");
			arrBuyCnt[3] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BCNT4");
			arrBuyCnt[4] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BCNT5");
#endif
			SetHogaData(arrSellHoga, arrBuyHoga, arrSellRemain, arrBuyRemain, arrSellCnt, arrBuyCnt);
		}//End of if
	}
	/***************************************
	* �ؿܼ��� ü��(���簡) �ǽð� ������ ����
	****************************************/
	else if (!_tcscmp(strRealName, "V10") ||
			!_tcscmp(strRealName, "V20"))
	{
		/*--------------------------------------
		�����۸����� ���ŵ� �ǽð� �����͸� �׸񺰷� ������.
		---------------------------------------*/
		CString strCurPrice = m_CommAgent.GetRealOutputData(strRealName, "TRDPRC_1");		//���簡
		CString strDiffSign = m_CommAgent.GetRealOutputData(strRealName, "NETCHNG_CLS");	//��ȣ
		CString strDiff = m_CommAgent.GetRealOutputData(strRealName, "NETCHNG_1");			//���ϴ��
		CString strDiffRate = m_CommAgent.GetRealOutputData(strRealName, "PCTCHNG_1");		//�����
		CString strVolume = m_CommAgent.GetRealOutputData(strRealName, "ACVOL_1");			//�ŷ���

		CString strOpenPrice = m_CommAgent.GetRealOutputData(strRealName, "OPEN_PRC");		//�ð�
		CString strHighPrice = m_CommAgent.GetRealOutputData(strRealName, "HIGH_1");		//��
		CString strLowPrice = m_CommAgent.GetRealOutputData(strRealName, "LOW_1");			//����

		CString strTime = m_CommAgent.GetRealOutputData(strRealName, "TRADE_TIME");			//ü��ð�
		CString strExecVolume = m_CommAgent.GetRealOutputData(strRealName, "TRDVOL_1");		//ü�ᷮ

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
		��ȸ ������ ����� �ؿܼ��� ���簡 �ǽð�Ű�� �������� ��
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
		��ȸ ������ ����� �ؿܼ��� �ð��뺰 ü�� �ǽð�Ű�� �������� ��
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
// Function Name : OnBnClickedButtonReal
// Function      : 
// Param         : 
// Return        : void 
// Create        : 2019/07/08
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedButtonReal()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	CString strRealName;

	if (((CButton*)GetDlgItem(IDC_RAD_QRY5))->GetCheck())
	{
		strRealName = _T("V10"); //�ؿܼ���ü�� Real name
	}
	else
	{
		strRealName = _T("V20"); //�ؿܿɼ�ü�� Real name
	}

	if(m_CommAgent.RegisterReal(strRealName, strSymBol) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqCodeList2
// Function      : 
// Param         : 
// Return        : void 
// Create        : , 2019/09/11
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqCodeList2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	/**********************************
	* 1. ������ȸŰ �ʱ�ȭ
	**********************************/
	m_strCodeListNextRqKey2.Empty();

	//�ؿܼ��� ���� ����Ʈ(������) ��Ʈ�� ������ �ʱ�ȭ
	m_listCode2.DeleteAllItems();

	/**********************************
	* 2. �����ȸ Request ID�� �����Ѵ�.
	**********************************/
	m_nRqIdCodeList2 = m_CommAgent.CreateRequestID();

	if (m_nRqIdCodeList2 == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("FO");	//�ؿܼ���

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList2, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList2, _T("GID"), _T("4499"));		//GID

	//�������� �������� ����׸��.
	CString strOutputFidList;

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	0001 : �����ڵ�(����)
	0002 : �ü������ڵ�
	0003 : �ؿ��Ļ���ǰ��
	1448 : ǰ���ڵ�
	2083 : �ؿ��Ļ�ǰ���
	0661 : ��簡��
	1170 : �����ڵ�
	1987 : �ŷ����ڵ�
	2467 : ǰ���������и�
	2456 : ���ݼҼ�������
	2457 : ����
	2295 : Tick Size
	1396 : �ּҰ��ݺ����ݾ�
	1773 : ȯ��¼�
	1772 : ������, ���ũ��
	1731 : ��Ź���ű�
	2460 : �������ű�
	0226 : ��������
	0132 : �����ŷ���(LTD)
	0981 : ��������(Expire Date)
	1203 : ������(Expire Month/Year)
	1268 : ������ȭ(�ŷ���ȭ?)
	1171 : ǥ����ȭ
	2459 : �ٿ�������
	0133 : �����ϼ�
	1759 : Active Flag
	0016 : ���ذ�
	0010 : ��������
	0028 : ���ϰŷ���
	1762 : �ŷ����� ����
	1870 : ���۽ð�
	1871 : ����ð�
	2486 : ����۽ð�(�ѱ�)
	2487 : ������ð�(�ѱ�)
	0815 : �����ŷ���
	0009 : ��������, �ŷ�����
	0128 : �����İ�
	0129 : ����������
	2596 : ���ΰŷ����ڵ�*/
	strOutputFidList = "1,2,3,1448,2083,661,1170,1987,2467,2456,2457,2295,1396,"
		"1773,1772,1731,2460,226,132,981,1203,1268,1171,"
		"2459,133,1759,16,10,28,1762,1870,1871,2486,2487,"
		"815,9,128,129, 2596";

	CString strScreenNo;
	strScreenNo = "9999";

	//������ȸ �ɼ� : '0':�̻��, '1'���, '2' : ���� ������ ��ȸ, '3' : ���� ������ ��ȸ
	CString strPreNext = "1";

	/**********************************
	* 5. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList2, strOutputFidList, strPreNext, "", strScreenNo, 1000);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}


//*******************************************************************
// Function Name : OnBnClickedBtnReqCodeListNext2
// Function      : 
// Param         : 
// Return        : void 
// Create        : , 2019/09/11
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqCodeListNext2()
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
	m_nRqIdCodeList2 = m_CommAgent.CreateRequestID();
	if (m_nRqIdCodeList2 == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("FO"); //�ؿܿɼ�

	/**********************************
	* 2. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList2, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList2, _T("GID"), _T("4499"));		//GID

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	* 3. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	0001 : �����ڵ�(����)
	0002 : �ü������ڵ�
	0003 : �ؿ��Ļ���ǰ��
	1448 : ǰ���ڵ�
	2083 : �ؿ��Ļ�ǰ���
	0661 : ��簡��
	1170 : �����ڵ�
	1987 : �ŷ����ڵ�
	2467 : ǰ���������и�
	2456 : ���ݼҼ�������
	2457 : ����
	2295 : Tick Size
	1396 : �ּҰ��ݺ����ݾ�
	1773 : ȯ��¼�
	1772 : ������, ���ũ��
	1731 : ��Ź���ű�
	2460 : �������ű�
	0226 : ��������
	0132 : �����ŷ���(LTD)
	0981 : ��������(Expire Date)
	1203 : ������(Expire Month/Year)
	1268 : ������ȭ(�ŷ���ȭ?)
	1171 : ǥ����ȭ
	2459 : �ٿ�������
	0133 : �����ϼ�
	1759 : Active Flag
	0016 : ���ذ�
	0010 : ��������
	0028 : ���ϰŷ���
	1762 : �ŷ����� ����
	1870 : ���۽ð�
	1871 : ����ð�
	2486 : ����۽ð�(�ѱ�)
	2487 : ������ð�(�ѱ�)
	0815 : �����ŷ���
	0009 : ��������, �ŷ�����
	0128 : �����İ�
	0129 : ����������
	2596 : ���ΰŷ����ڵ�*/
	strOutputFidList = "1,2,3,1448,2083,661,1170,1987,2467,2456,2457,2295,1396,"
		"1773,1772,1731,2460,226,132,981,1203,1268,1171,"
		"2459,133,1759,16,10,28,1762,1870,1871,2486,2487,"
		"815,9,128,129,2596";

	CString strScreenNo;
	strScreenNo = "9999";

	CString strPreNext = "3"; //���� ������ ��ȸ

	/**********************************
	* 4. ������ �����ȸ ��û�Ѵ�.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList2, strOutputFidList, strPreNext, m_strCodeListNextRqKey2, strScreenNo, 1000);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}
