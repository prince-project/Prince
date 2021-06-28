/*----------------------------------------*
| ���α׷��� : �ϳ��������� Open API ����
| ��      �� : 0.0.1
| ����  ���� :
| ��      Ÿ : 
*----------------------------------------*/

// HFCommClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "HFCommClient.h"
#include "HFCommClientDlg.h"

#define ID_SECOND_TIMER		100	//1�� ���� Ÿ�̸�

#define SELL_BK_COLOR		RGB(206, 232, 255)	//�ŵ� ����
#define BUY_BK_COLOR		RGB(251, 221, 255)	//�ż� ����

//��� ����ü ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

// CHFCommClientDlg ��ȭ ����
CHFCommClientDlg::CHFCommClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHFCommClientDlg::IDD, pParent)
{
	m_bCommConnect	= FALSE;
	m_nRqIdHoga		= 0;
	m_nRqIdCurPrice	= 0;
	m_nRqIdTick		= 0;

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHFCommClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	/*DDX_Control(pDX, IDC_HFCOMMAGENTCTRL1, m_CommAgent);*/
	DDX_Control(pDX, IDC_EDIT_ID, m_editUserID);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDC_EDIT_AUTH_PWD, m_editAuthPwd);
	DDX_Text(pDX, IDC_EDIT_ID, m_strLoginID);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strLoginPwd);
	DDX_Text(pDX, IDC_EDIT_AUTH_PWD, m_strCertPwd);
	DDX_Control(pDX, IDC_CHECK_DEMO, m_checkDemo);
	DDX_Control(pDX, IDC_EDIT_SYMBOL, m_editSymbol);
	DDX_Control(pDX, IDC_EDIT_SYMBOL_PRICE, m_editSymbolPrice);
	DDX_Control(pDX, IDC_LIST_TICK, m_listTick);
	DDX_Control(pDX, IDC_EDIT_SYMBOL_TICK, m_editSymbolTick);
	DDX_Control(pDX, IDC_LIST_SYMBOL, m_listCode);
}

BEGIN_MESSAGE_MAP(CHFCommClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_LOGIN, &CHFCommClientDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_LOGOUT, &CHFCommClientDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_INITCOMM, &CHFCommClientDlg::OnBnClickedInitcomm)
	ON_BN_CLICKED(IDC_TERMINATE, &CHFCommClientDlg::OnBnClickedTerminate)
	ON_BN_CLICKED(IDC_BTN_REQ_HOGA, &CHFCommClientDlg::OnBnClickedBtnReqHoga)
	ON_BN_CLICKED(IDC_BTN_REQ_PRICE, &CHFCommClientDlg::OnBnClickedBtnReqPrice)
	ON_BN_CLICKED(IDC_BTN_REQ_TICK, &CHFCommClientDlg::OnBnClickedBtnReqTick)
	ON_BN_CLICKED(IDC_BTN_REQ_TICK_NEXT, &CHFCommClientDlg::OnBnClickedBtnReqTickNext)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE_LIST, &CHFCommClientDlg::OnBnClickedBtnReqCodeList)
	ON_BN_CLICKED(IDC_BTN_REQ_CODE_LIST_NEXT, &CHFCommClientDlg::OnBnClickedBtnReqCodeListNext)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SYMBOL, &CHFCommClientDlg::OnNMDblclkListSymbol)
END_MESSAGE_MAP()

// agent�κ��� �̺�Ʈ ���� �Լ��� �����Ѵ�.
BEGIN_EVENTSINK_MAP(CHFCommClientDlg, CDialog)
	ON_EVENT(CHFCommClientDlg, IDC_HFCOMMAGENTCTRL1, 1, CHFCommClientDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CHFCommClientDlg, IDC_HFCOMMAGENTCTRL1, 2, CHFCommClientDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CHFCommClientDlg, IDC_HFCOMMAGENTCTRL1, 3, CHFCommClientDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
END_EVENTSINK_MAP()

// CHFCommClientDlg �޽��� ó����

void CHFCommClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CHFCommClientDlg::OnPaint()
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
HCURSOR CHFCommClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CHFCommClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CHFCommClientDlg::OnDestroy()
{
	//��� �ǽð������ �����Ѵ�.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();

	CDialog::OnDestroy();
}

void CHFCommClientDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();
	CDialog::OnClose();
}

void CHFCommClientDlg::OnTimer(UINT_PTR nIDEvent)
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

			BOOL bLoginState = m_CommAgent.GetLoginState();
			if (bLoginState)
				GetDlgItem(IDC_LOGIN_STATE)->SetWindowText(_T("�α���"));
			else
				GetDlgItem(IDC_LOGIN_STATE)->SetWindowText(_T("�α׾ƿ�"));

		}
		break;
	}//End of switch

	CDialog::OnTimer(nIDEvent);
}

void CHFCommClientDlg::OnNMDblclkListSymbol(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;

	CString strSymbol		= m_listCode.GetItemText(nSelectRow, 0); //�����ڵ�
	CString strStandardCode	= m_listCode.GetItemText(nSelectRow, 1); //ǥ�������ڵ�
	CString strSymbolName	= m_listCode.GetItemText(nSelectRow, 2); //�ѱ������
	CString strPrice		= m_listCode.GetItemText(nSelectRow, 3); //���ذ�

	if (strSymbol.IsEmpty())
		return;

	//�����ڵ带 �Է��Ѵ�.
	m_editSymbol.SetWindowText(strSymbol);		//5�ܰ�ȣ�� �����ڵ�(�ɺ�)
	m_editSymbolPrice.SetWindowText(strSymbol);	//���簡 �����ڵ�(�ɺ�)
	m_editSymbolTick.SetWindowText(strSymbol);	//�ð��뺰ü�� �����ڵ�(�ɺ�)

	GetDlgItem(IDC_SYMBOL_NAME)->SetWindowText(strSymbolName);		//5�ܰ�ȣ�� �����
	GetDlgItem(IDC_SYMBOL_NAME_PRICE)->SetWindowText(strSymbolName);//���簡 �����
	GetDlgItem(IDC_SYMBOL_NAME_TICK)->SetWindowText(strSymbolName);	//�ð��뺰ü�� �����

	//�Էµ� �����ڵ�� ����ȸ ��û�� �Ѵ�.
	OnBnClickedBtnReqPrice();	//�������� ���簡 ��ȸ
	OnBnClickedBtnReqHoga();	//�������� 5�ܰ�ȣ�� ��ȸ
	OnBnClickedBtnReqTick();	//�������� �ð��뺰ü�� ��ȸ
}

//*******************************************************************
// Function Name : OnInitDialog
// Function      : ���̾�α� �ʱ�ȭ
// Param         : 
// Return        : BOOL 
// Create        : 
// Comment       : 
//******************************************************************
BOOL CHFCommClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CString strTitle;
	strTitle.Format("%s-[�������� �ü�](%s)", PROGRAM_NAME, VERSION_INFO);
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
	 * �������� �ð��뺰ü�ᰡ ����Ʈ ��Ʈ�� �ʱ�ȭ
	 **********************************/
	InitListTick();

	/**********************************
	 * �������� ���� ����Ʈ ��Ʈ�� �ʱ�ȭ
	 **********************************/
	InitListCode();

	/**********************************
	 * HFCommAgent.dll(API Agent DLL���� ��ġ�� ���)
	 **********************************/
	CString strApidAgentModulePath = m_CommAgent.GetApiAgentModulePath();
	GetDlgItem(IDC_API_AGENT_PATH)->SetWindowText(strApidAgentModulePath);

	/**********************************
	 * ��ȸTr, �ǽð� ��� I/O ���� ���ҽ� ���� �ε�
	 **********************************/
	if (!m_CommAgent.LoadTranResource(strApidAgentModulePath + "/OAM4109Q01.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());

	//��������ü�� �ǽð� I/O ���� ���ҽ� ����
	if (!m_CommAgent.LoadRealResource(strApidAgentModulePath + "/F00.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());

	//��������ȣ�� �ǽð� I/O ���� ���ҽ� ����
	if (!m_CommAgent.LoadRealResource(strApidAgentModulePath + "/F01.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

//*******************************************************************
// Function Name : InitListTick
// Function      : �������� �ð��뺰ü�� ����Ʈ ��Ʈ�� �ʱ�ȭ
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CHFCommClientDlg::InitListTick()
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
// Function      : �������� ���� ����Ʈ ��Ʈ�� �ʱ�ȭ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFCommClientDlg::InitListCode()
{
	CRect rc;
	m_listCode.GetClientRect(rc);
	m_listCode.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int arrWidth[4] = { 0x00 };
	int nWidth = rc.Width() - ::GetSystemMetrics(SM_CYHSCROLL);

	arrWidth[0] = (int)(nWidth * 0.2);
	arrWidth[1] = (int)(nWidth * 0.3);
	arrWidth[2] = (int)(nWidth * 0.3);
	arrWidth[3] = (int)(nWidth * 0.2);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("�����ڵ�"), _T("ǥ���ڵ�"), _T("�����"), _T("���ذ�") };

	int i;
	for (i = 0; i < 4; i++)
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
// Function Name : GetDiffSign
// Function      : ����ȣ
// Param         : CString strSignCode
// Return        : CString 
// Create        :
// Comment       : 
//******************************************************************
CString CHFCommClientDlg::GetDiffSign(CString strSignCode)
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
void CHFCommClientDlg::SetHogaData(CString* arrSellHoga, CString* arrBuyHoga, CString* arrSellRemain,
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
void CHFCommClientDlg::OnBnClickedInitcomm()
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
void CHFCommClientDlg::OnBnClickedTerminate()
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
void CHFCommClientDlg::OnBnClickedLogin()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("��� ������ ������ϴ�!");
		return;
	}

	//�α��� ID
	m_editUserID.GetWindowText(m_strLoginID);

	//�α��� ��й�ȣ
	m_editPwd.GetWindowText(m_strLoginPwd);

	//�������� ��й�ȣ
	m_editAuthPwd.GetWindowText(m_strCertPwd);

	/**********************************
	 * �α����� ��û�Ѵ�.
	 **********************************/
	if (m_CommAgent.CommLogin(m_strLoginID, m_strLoginPwd, m_strCertPwd) == 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : �α׾ƿ�
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFCommClientDlg::OnBnClickedLogout()
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
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqCodeList
// Function      : �������� ���� ����Ʈ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFCommClientDlg::OnBnClickedBtnReqCodeList()
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

	//�������� ���� ����Ʈ(������) ��Ʈ�� ������ �ʱ�ȭ
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
	strMarketCode = _T("F");	//��������

	/**********************************
	* 3. �����ȸ ��û �Էµ�����
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("1499"));		//GID

	//�������� �������� ����׸��.
	CString strOutputFidList;

	/**********************************
	* 4. �����ȸ �������� ���� �׸� ����.
	**********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	�����ڵ�(1), ǥ���߸��ڵ�(2), �ѱ������(3), ���ذ�(16) */
	strOutputFidList = "1,2,3,16";

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
// Function      : �������� ���� ����Ʈ ���� ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFCommClientDlg::OnBnClickedBtnReqCodeListNext()
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
	strMarketCode = _T("F"); //��������

	/**********************************
	 * 2. �����ȸ ��û �Էµ�����
	 **********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9002"), strSymBol);		//����ɺ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//���屸���ڵ�
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("1001"));		//GID

	//�����ȸ �������� ���� ������ �׸�(FID)
	CString strOutputFidList;

	/**********************************
	 * 3. �����ȸ �������� ���� �׸� ����.
	 **********************************/
	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]
	�����ڵ�(1), ǥ���߸��ڵ�(2), �ѱ������(3), ���ذ�(16) */
	strOutputFidList = "1,2,3,16";

	CString strScreenNo;
	strScreenNo = "9999";

	CString strPreNext = "3"; //���� ������ ��ȸ

	/**********************************
	 * 4. ������ �����ȸ ��û�Ѵ�.
	 **********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, m_strTickNextRqKey, strScreenNo, 0);
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
void CHFCommClientDlg::OnBnClickedBtnReqPrice()
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
	 * 2. ������ ��ϵ� ��������ü��(���簡) �ǽð���� ����.
	 **********************************/
	if (!m_strCurPriceRealKey.IsEmpty())
	{
		CString strRealName;
		strRealName = _T("F00"); //��������ü�� Real name

		m_CommAgent.UnRegisterReal(strRealName, m_strCurPriceRealKey);
		m_strCurPriceRealKey.Empty();
	}

	CString strMarketCode;		//���屸��
	strMarketCode = _T("F");	//��������
	
	//��������ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
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
// Function      : ��������ȣ�� ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFCommClientDlg::OnBnClickedBtnReqHoga()
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
		strRealName = _T("F01");

		m_CommAgent.UnRegisterReal(strRealName, m_strHogaRealKey);
		m_strHogaRealKey.Empty();
	}

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("F");

	//����ȣ�� �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
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
	CString strSellHoga		= _T("29,30,31,32,33");	//�ŵ� 1~5 ȣ��(FID)
	CString strSellRemain	= _T("63,64,65,66,67"); //�ŵ� 1~5 ȣ���ܷ�(FID)
	CString strBuyHoga		= _T("39,40,41,42,43");	//�ż� 1~5 ȣ��(FID)
	CString strBuyRemain	= _T("73,74,75,76,77"); //�ż� 1~5 ȣ�� �ܷ�(FID)

	/* [ �����ȸ �������� ���� ������ �׸�(FID) ]*/
	CString strOutputFidList = strSellHoga + "," + strSellRemain + "," + strBuyHoga + "," + strBuyRemain;

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
// Function      : �������� �ð��뺰ü�� ������ ��ȸ(���Ӱŷ� �����Ͱ� �ִ� ���)
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFCommClientDlg::OnBnClickedBtnReqTick()
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

	//�������� �ð��뺰ü�� ����Ʈ ��Ʈ�� ������ �ʱ�ȭ
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
	 * 3. ������ ��ϵ� ��������ü��(���簡) �ǽð���� ����.
	 **********************************/
	if (!m_strTickRealKey.IsEmpty())
	{
		CString strRealName;
		strRealName = _T("F00");

		m_CommAgent.UnRegisterReal(strRealName, m_strTickRealKey);
		m_strTickRealKey.Empty();
	}

	CString strMarketCode;		//���屸���ڵ�
	strMarketCode = _T("F");

	//��������ü��(���簡) �ǽð� ���Ű�� ����� ����Ű(�����ڵ�)
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
// Function      : �������� �ð��뺰ü�� ���� ������ ��ȸ
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFCommClientDlg::OnBnClickedBtnReqTickNext()
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
	strMarketCode = _T("F"); //��������

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
// Function Name : OnGetTranData
// Function      : Tran ��ȸ���� �̺�Ʈ
// Param         :	LONG nRequestId, ��ȸID
//					LPCTSTR pBlock, ��ȸ���� ������ ��
//					long nBlockLength ��ȸ���� ������ �� ũ��
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFCommClientDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
{
	/* ���� : OnGetTranData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
	�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/

	/*	0 : ������ȸ �̻��,		1 : ���� ������ ����,	2 : ���� ������ ����
		3 : ����/���� ������ ����	*/
	CString strPreNext			= m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::PrevNextCode);

	//������ȸŰ
	CString strPreNextContext	= m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::PrevNextKey);

	//��ȸ���� �޽����ڵ�
	CString strMsgCode			= m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::MsgCode);

	//��ȸ���� �޽���
	CString strMsg				= m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::Msg);

	//��ȸ���� �ΰ��޽����ڵ�
	CString strSubMsgCode		= m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::SubMsgCode);

	//��ȸ���� �ΰ��޽���
	CString strSubMsg			= m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::SubMsg);

	CString strErrMsg = m_CommAgent.GetLastErrMsg();

#if 0
	CString strTemp;
	CString strData;
	m_edOutput.SetWindowText(_T(""));
	strData.Format("RQID		: %d\r\n", nRequestId);
	strTemp.Format("TR CODE		: %s\r\n", strTrCode);
	strData += strTemp;

	//����������������ȸ
	if (!_tcscmp("OAM4109Q01", strTrCode))
	{
		ReceiveTr_OAM4109Q01(nRequestId, strPreNext, strMsgCode, strMsg);
	}
	
	m_strTrPreNext = strPreNext;

	strTemp.Format("������������	: %s\r\n", strPreNext);
	strData += strTemp;
	strTemp.Format("�����ڵ�		: %s\r\n", strMsgCode);
	strData += strTemp;
	strTemp.Format("�޼���			: %s\r\n", strMsg);
	strData += strTemp;
	strTemp.Format("�����޼���		: %s\r\n", strSubMsg);
	strData += strTemp;
	strTemp.Format("���� ����Ÿ		:\r\n");
	strData += strTemp;
// 	strTemp = CString(sData, nDataLength);
// 	strData += strTemp;

#if 0
	// ����/���� ��ư Ȱ��ȭ ó��
	if (m_strTrPreNext == "1" || m_strTrPreNext == "3")
		GetDlgItem(IDC_RQTEST_PRE)->EnableWindow(TRUE);

	if (m_strTrPreNext == "2" || m_strTrPreNext == "3")
		GetDlgItem(IDC_RQTEST_NEXT)->EnableWindow(TRUE);

	if (m_strTrPreNext != "1" && m_strTrPreNext != "2" && m_strTrPreNext != "3")
	{
		GetDlgItem(IDC_RQTEST_PRE)->EnableWindow(FALSE);
		GetDlgItem(IDC_RQTEST_NEXT)->EnableWindow(FALSE);
	}
#endif

	m_editExtInfo.SetWindowText(strData);
#endif
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
void CHFCommClientDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
{
	/* ���� : OnGetFidData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
	�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/

	/*	0 : ������ȸ �̻��,		1 : ���� ������ ����,	2 : ���� ������ ����
		3 : ����/���� ������ ����	*/
	CString strPreNext			= m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::PrevNextCode);

	//������ȸŰ
	CString strPreNextContext	= m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::PrevNextKey);

	//��ȸ���� �޽����ڵ�
	CString strMsgCode			= m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::MsgCode);

	//��ȸ���� �޽���
	CString strMsg				= m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::Msg);

	CString strErrMsg = m_CommAgent.GetLastErrMsg();

	//FID ��ȸ���� ������ �ε��� ���ߺ���(C++������ ��� ����)
	//FID��ȸ ������ �Էµ� ���FID ������ �ε��̵ȴ�.
	CCommRecvData fidCommRecvData;
	m_CommAgent.GetCommFidDataBlock((long)&fidCommRecvData);

	int nVecRowCnt = fidCommRecvData.GetRowCnt();
	int nVecColCnt = fidCommRecvData.GetRowCnt();

	/***************************************
	 * �������� ���� ����Ʈ(������) ��ȸ ������ ���� ó��
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
		if (!m_strCodeListNextRqKey.IsEmpty())
		{
			nListIndex = m_listCode.GetItemCount() - 1;
		}

		int nDataCnt = m_CommAgent.GetFidOutputRowCnt(nRequestId);

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			  FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			 ---------------------------------------*/
			strCode			= m_CommAgent.GetFidOutputData(nRequestId, "1", i);	//�����ڵ�
			strStandardCode	= m_CommAgent.GetFidOutputData(nRequestId, "2", i);	//ǥ���ڵ�
			strCodeName		= m_CommAgent.GetFidOutputData(nRequestId, "3", i);	//�ѱ������
			strPrice		= m_CommAgent.GetFidOutputData(nRequestId, "16", i);//���ذ�

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listCode.InsertItem(&lvItem);

			m_listCode.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strCode);		//�����ڵ�
			m_listCode.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strStandardCode);//ü�ᰡ
			m_listCode.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strCodeName);	//���
			m_listCode.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strPrice);		//���

		}//End of for

		m_listCode.EnsureVisible(nListIndex, FALSE);
		m_listCode.SetRedraw(TRUE);
		
		/*--------------------------------------
		  ������ȸŰ�� ������ ���´�.
		 ---------------------------------------*/
		m_strCodeListNextRqKey = strPreNextContext;

		/*--------------------------------------
		  ������ȸŰ�� �����ϸ� '����'��ư�� Ȱ��ȭ ��Ų��.
		 ---------------------------------------*/
		if (!m_strCodeListNextRqKey.IsEmpty())
			GetDlgItem(IDC_BTN_REQ_CODE_LIST_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_CODE_LIST_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		  �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdCodeList = 0;	//�������� ���� ����Ʈ(������) ��ȸ Request ID
	}
	/***************************************
	 * �������� 5�ܰ�ȣ�� ��ȸ ������ ���� ó��
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
		arrSellHoga[0]	= m_CommAgent.GetFidOutputData(nRequestId, "29", 0);	//�ŵ� 1ȣ��
		arrSellHoga[1]	= m_CommAgent.GetFidOutputData(nRequestId, "30", 0);	//�ŵ� 2ȣ��
		arrSellHoga[2]	= m_CommAgent.GetFidOutputData(nRequestId, "31", 0);	//�ŵ� 3ȣ��
		arrSellHoga[3]	= m_CommAgent.GetFidOutputData(nRequestId, "32", 0);	//�ŵ� 4ȣ��
		arrSellHoga[4]	= m_CommAgent.GetFidOutputData(nRequestId, "33", 0);	//�ŵ� 5ȣ��
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
		  ��������ȣ�� �ǽð�Ű�� �ǽð��� ����Ѵ�.
		  �ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		 ---------------------------------------*/
		if (!m_strHogaRealKey.IsEmpty())
		{
			CString strRealName;
			strRealName = _T("F01");
			
			m_CommAgent.RegisterReal(strRealName, m_strHogaRealKey); //�ǽð� ���
		}

		/*--------------------------------------
		  �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdHoga = 0;	//�������� 5�ܰ�ȣ�� ��ȸ Request ID
	}
	/***************************************
	 * �������� ���簡 ��ȸ ������ ���� ó��
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
			strRealName = _T("F00");

			m_CommAgent.RegisterReal(strRealName, m_strCurPriceRealKey); //�ǽð� ���
		}

		/*--------------------------------------
		  �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdCurPrice = 0;	//�������� ���簡 ��ȸ Request ID
	}
	/***************************************
	 * �������� �ð��뺰ü�� ��ȸ ������ ���� ó��
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
		if (!m_strTickNextRqKey.IsEmpty())
		{
			nListIndex = m_listTick.GetItemCount() - 1;
		}

		int nDataCnt = m_CommAgent.GetFidOutputRowCnt(nRequestId);

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			  FID ��ȣ�� ��ȸ�� ���� �����͸� �׸񺰷� ������.
			 ---------------------------------------*/
			strTime		= m_CommAgent.GetFidOutputData(nRequestId, "8", i);	//�ð�
			strPrice	= m_CommAgent.GetFidOutputData(nRequestId, "4", i);	//ü�ᰡ
			strDiff		= m_CommAgent.GetFidOutputData(nRequestId, "5", i);	//���
			strDiffRate	= m_CommAgent.GetFidOutputData(nRequestId, "7", i);	//���
			strVolume	= m_CommAgent.GetFidOutputData(nRequestId, "83", i);//ü�ᷮ
			
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

		m_listTick.EnsureVisible(nListIndex, FALSE);
		m_listTick.SetRedraw(TRUE);

		/*--------------------------------------
		  ����ü�� �ǽð��� ����Ѵ�.
		  �ǽð� ����� ù ��ȸ �� �ѹ��� �Ѵ�.
		 ---------------------------------------*/
		if (!m_strTickRealKey.IsEmpty() && m_strTickNextRqKey.IsEmpty())
		{
			CString strRealName;
			strRealName = _T("F00");

			m_CommAgent.RegisterReal(strRealName, m_strTickRealKey); //�ǽð� ���
		}

		/*--------------------------------------
		  ������ȸŰ�� ������ ���´�.
		 ---------------------------------------*/
		m_strTickNextRqKey = strPreNextContext;

		/*--------------------------------------
		  ������ȸŰ�� �����ϸ� '����'��ư�� Ȱ��ȭ ��Ų��.
		 ---------------------------------------*/
		if (!m_strTickNextRqKey.IsEmpty())
			GetDlgItem(IDC_BTN_REQ_TICK_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_TICK_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		  �ݵ�� ����� ���� RQ ID�� 0���� �ʱ�ȭ�Ѵ�.
		 ---------------------------------------*/
		m_nRqIdTick = 0;	//�������� �ð��뺰ü�� ��ȸ Request ID

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
void CHFCommClientDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/* ���� : OnGetRealData �̺�Ʈ���� ���� �Ǵ� �Լ��� ���� ���� ��� �ֹ߼�����
	�̺�Ʈ �ݹ��Լ� ���� �Ŀ��� ��ȿ���� �ʽ��ϴ�.*/

	/***************************************
	 * �������� ȣ�� �ǽð� ������ ����
	 ****************************************/
	if (!_tcscmp(strRealName, "F01"))
	{
		/*--------------------------------------
		  ��ȸ ������ ����� �������� ȣ�� �ǽð�Ű�� �������� ��
		 ---------------------------------------*/
		if (m_strHogaRealKey == strRealKey)
		{
			CString arrSellHoga[5];
			CString arrBuyHoga[5];

			CString arrSellRemain[5];
			CString arrBuyRemain[5];

			CString arrSellCnt[5];
			CString arrBuyCnt[5];

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

			SetHogaData(arrSellHoga, arrBuyHoga, arrSellRemain, arrBuyRemain, arrSellCnt, arrBuyCnt);
		}//End of if
	}
	/***************************************
	 * �������� ü��(���簡) �ǽð� ������ ����
	 ****************************************/
	else if (!_tcscmp(strRealName, "F00"))
	{
		/*--------------------------------------
		  �����۸����� ���ŵ� �ǽð� �����͸� �׸񺰷� ������.
		 ---------------------------------------*/
		CString strCurPrice		= m_CommAgent.GetRealOutputData(strRealName, "PRPR");			//���簡
		CString strDiffSign		= m_CommAgent.GetRealOutputData(strRealName, "PRDY_VRSS_SIGN");	//��ȣ
		CString strDiff			= m_CommAgent.GetRealOutputData(strRealName, "PRDY_VRSS");		//���ϴ��
		CString strDiffRate		= m_CommAgent.GetRealOutputData(strRealName, "PRDY_CTRT");		//�����
		CString strVolume		= m_CommAgent.GetRealOutputData(strRealName, "ACML_VOL");		//�ŷ���

		CString strOpenPrice	= m_CommAgent.GetRealOutputData(strRealName, "OPRC");			//�ð�
		CString strHighPrice	= m_CommAgent.GetRealOutputData(strRealName, "HGPR");			//��
		CString strLowPrice		= m_CommAgent.GetRealOutputData(strRealName, "LWPR");			//����
		
		CString strTime			= m_CommAgent.GetRealOutputData(strRealName, "BSOP_HOUR");		//ü��ð�
		CString strExecVolume	= m_CommAgent.GetRealOutputData(strRealName, "CNTG_VOL");		//ü�ᷮ

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
		  ��ȸ ������ ����� �������� ���簡 �ǽð�Ű�� �������� ��
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
		  ��ȸ ������ ����� �������� �ð��뺰 ü�� �ǽð�Ű�� �������� ��
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
