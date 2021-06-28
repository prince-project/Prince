/*----------------------------------------*
| 프로그램명 : 하나금융투자 Open API 예제
| 버      전 : v 
| 배포  일자 :
| 기      타 :
*----------------------------------------*/
// IndexFutSiseDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "HFCommClient.h"
#include "FxMarginOrdDlg.h"

#define ID_SECOND_TIMER		100	//1초 간격 타이머

#define SELL_BK_COLOR		RGB(206, 232, 255)	//매도 배경색
#define BUY_BK_COLOR		RGB(251, 221, 255)	//매수 배경색

//통신 구조체 헤더

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern void NumericString(CString& strValue, BOOL bNotDisplayZero = FALSE);

static char* g_szPriceCond[] = { "2", "1", "3"}; //1:시장가, 2:지정가, 3:역지정가

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

// CFxMarginOrdDlg 대화 상자
CFxMarginOrdDlg::CFxMarginOrdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFxMarginOrdDlg::IDD, pParent)
{
	m_bCommConnect		= FALSE;

	m_nRqIdAccNoList		= 0;	//계좌조회 Request ID
	m_nRqIdFDemoAccNoList	= 0;	//해외모의 계좌조회 Request ID

	m_nRqIdSellOrd			= 0;	//매도주문 Request ID
	m_nRqIdBuyOrd			= 0;	//매수주문 Request ID
	m_nRqIdChangeOrd		= 0;	//정정주문 Request ID
	m_nRqIdCancelOrd		= 0;	//취소주문 Request ID

	m_nRqIdNonExecList		= 0;	//미체결내역 Request ID
	m_nRqIdExecList			= 0;	//주문체결내역 Request ID
	m_nRqIdDepositList		= 0;	//예수금내역 Request ID

	m_nRqIdCloseOrd			= 0;	//청산주문 Request ID
	m_nRqIdModSLOrd			= 0;	//SL정정주문 Request ID
	m_nRqIdCanSLOrd			= 0;	//SL취소주문 Request ID

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_nSeverType			= 0;	//0-리얼, 1-국내모의, 2-해외무의

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

// agent로부터 이벤트 수신 함수를 정의한다.
BEGIN_EVENTSINK_MAP(CFxMarginOrdDlg, CDialog)
	ON_EVENT(CFxMarginOrdDlg, IDC_HFCOMMAGENTCTRL1, 1, CFxMarginOrdDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CFxMarginOrdDlg, IDC_HFCOMMAGENTCTRL1, 2, CFxMarginOrdDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CFxMarginOrdDlg, IDC_HFCOMMAGENTCTRL1, 3, CFxMarginOrdDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
	ON_EVENT(CFxMarginOrdDlg, IDC_HFCOMMAGENTCTRL1, 4, CFxMarginOrdDlg::OnAgentEventHandler, VTS_I4 VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

// CFxMarginOrdDlg 메시지 처리기
void CFxMarginOrdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
void CFxMarginOrdDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFxMarginOrdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CFxMarginOrdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

	//호가 배경색칠
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	//TCHAR *strTitle[] = { _T("계좌번호"), _T("대체번호"), _T("계좌상품번호"), _T("계좌명"), _T("계좌특정"), _T("은행연계여부") };

	CString strAccNo = m_listAccNo.GetItemText(nSelectRow, 0);
	CString strPrdtNo = m_listAccNo.GetItemText(nSelectRow, 2);

	GetDlgItem(IDC_EDIT_ACCNO)->SetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->SetWindowText(strPrdtNo);
}

void CFxMarginOrdDlg::OnNMDblclkListNonExec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

	static char* g_szPriceCond[] = { "2", "1", "3" }; //1:시장가, 2:지정가, 3:역지정가
	for (int i = 0; i < 3; i++)
	{
		if (strOrderType == g_szPriceCond[i])
			m_cmdOrdType.SetCurSel(i);
	}
}

void CFxMarginOrdDlg::OnNMDblclkListBalance(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	//모든 실시간등록을 해제한다.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();
	
	CDialog::OnDestroy();
}

void CFxMarginOrdDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CFxMarginOrdDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
	case ID_SECOND_TIMER:
	{
		BOOL bConnectState = m_CommAgent.CommGetConnectState();

		if (bConnectState)
			GetDlgItem(IDC_COMM_STATUS)->SetWindowText(_T("연결됨"));
		else
			GetDlgItem(IDC_COMM_STATUS)->SetWindowText(_T("접속 끊김"));

		m_bCommConnect = bConnectState;

		BOOL bLoginState = m_CommAgent.GetLoginState();
		if (bLoginState)
			GetDlgItem(IDC_LOGIN_STATE)->SetWindowText(_T("로그인"));
		else
			GetDlgItem(IDC_LOGIN_STATE)->SetWindowText(_T("로그아웃"));

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
// Comment       : 접속서버를 설정한다.
//******************************************************************
void CFxMarginOrdDlg::OnRdoSelectServer(UINT nID)
{
	m_nSeverType = nID - IDC_CON_REAL;

	/*----------------------------------
	  접속서버를 설정한다.(0 - 리얼, 1 - 국내모의, 2 - 해외모의)
	 *----------------------------------*/
	m_CommAgent.SetLoginMode(0, m_nSeverType);
}

//*******************************************************************
// Function Name : OnBnClickedBtnAccinfo
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 주문대리인 등록여부
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedBtnAccinfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strAccNo;
	CString strAPNO;

	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//계좌상품번호
	
	CString strReturn = m_CommAgent.GetAccInfo(198, strAccNo + strAPNO);

	::AfxMessageBox(strReturn);
}


//*******************************************************************
// Function Name : OnInitDialog
// Function      : 다이얼로그 초기화
// Param         : 
// Return        : BOOL 
// Create        : 
// Comment       : 
//******************************************************************
BOOL CFxMarginOrdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CString strTitle;
	strTitle.Format("%s-[FX마진주문](%s)", PROGRAM_NAME, VERSION_INFO);
	SetWindowText(strTitle);
	
	/**********************************
	 * Open API Agent 컨트롤 윈도우를 생성한다.
	 **********************************/
	BOOL bRtn = m_CommAgent.Create(_T("HFCOMMAGENT.HFCommAgentCtrl.1"), NULL, WS_CHILD, CRect(0, 0, 0, 0), this, IDC_HFCOMMAGENTCTRL1);
	if (!bRtn)
	{
		::AfxMessageBox("Open API Agent 컨트롤 윈도우 생성을 실패했습니다!");
		return FALSE;
	}

	/**********************************
	 * 1초 간격 타이머
	 **********************************/
	SetTimer(ID_SECOND_TIMER, 1000, NULL);

	/**********************************
	* 리스트 컨트롤 초기화
	**********************************/
	InitListAccNo();	//계좌목록
	InitListReal();		//실시간 주문메시지
	InitListNonExec();	//주문미체결
	InitListExec();		//주문체결
	InitListDeposit();	//예수금
	InitListBalance();	//잔고

	/**********************************
	 * HFCommAgent.dll(API Agent DLL파일 위치의 경로)
	 **********************************/
	CString strApidAgentModulePath = m_CommAgent.GetApiAgentModulePath();
	GetDlgItem(IDC_API_AGENT_PATH)->SetWindowText(strApidAgentModulePath);

	/**********************************
	 * 접속서버 선택
	 **********************************/
	m_nSeverType = m_CommAgent.GetLoginMode(0);
	switch (m_nSeverType)
	{
		case 1: //국내모의서버
			((CButton*)GetDlgItem(IDC_CON_DEMO))->SetCheck(1);
		break;
		case 2: //해외모의서버
			((CButton*)GetDlgItem(IDC_CON_F_DEMO))->SetCheck(1);
		break;
		default: //실거래서버
			((CButton*)GetDlgItem(IDC_CON_REAL))->SetCheck(1);
		break;
	}//End of switch

	((CButton*)GetDlgItem(IDC_RADIO_EX1))->SetCheck(1);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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
	TCHAR *strTitle[] = { _T("계좌번호"), _T("대체번호"), _T("계좌상품번호"), _T("계좌명"), _T("계좌특정"), _T("은행연계여부")};

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
	TCHAR *strTitle[] = {_T("메시지")};

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
	TCHAR *strTitle[] = { _T("딜링하우스고유번"),
		_T("계좌번호"),
		_T("대체번호"),
		_T("주문번호"),
		_T("딜링하우스고유번호"),
		_T("상품코드"),
		_T("원주문번호"),
		_T("모주문번호"),
		_T("주문그룹번호"),
		_T("주문일자"),
		_T("계좌상품번호"),
		_T("고객명"),
		_T("매매구분코드"),
		_T("주문가격"),
		_T("주문수량"),
		_T("정정수량"),
		_T("취소수량"),
		_T("체결수량"),
		_T("주문잔여수량"),
		_T("계약단위금액"),
		_T("FX주문총금액"),
		_T("FX잔여총금액"),
		_T("가격조건구분코드"),
		_T("체결조건구분코드"),
		_T("1차스탑로스여부"),
		_T("1차지정가여부"),
		_T("1차스탑로스가격"),
		_T("1차지정가격"),
		_T("1차추적손절매가격"),
		_T("2차스탑로스여부"),
		_T("2차지정가여부"),
		_T("2차스탑로스가격"),
		_T("2차지정가격"),
		_T("2차추적손절매가격"),
		_T("평균체결가격"),
		_T("체결율"),
		_T("현재가격"),
		_T("통신매체구분코드"),
		_T("주문유형구분코드"),
		_T("주문상태구분코드"),
		_T("FCM주문번호"),
		_T("사용자ID"),
		_T("공인IP주소"),
		_T("거래소접수시각"),
		_T("거래소체결시각"),
		_T("주문시각"),
		_T("체결시각"),
		_T("통화코드"),
		_T("가격소수점이하길이"),
		_T("매매가격차이내용") };

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
	TCHAR *strTitle[] = { _T("딜링하우스고유번"),
		_T("계좌번호"),
		_T("대체번호"),
		_T("주문번호"),
		_T("딜링하우스고유번호"),
		_T("상품코드"),
		_T("원주문번호"),
		_T("모주문번호"),
		_T("주문그룹번호"),
		_T("주문일자"),
		_T("계좌상품번호"),
		_T("고객명"),
		_T("매매구분코드"),
		_T("주문가격"),
		_T("주문수량"),
		_T("정정수량"),
		_T("취소수량"),
		_T("체결수량"),
		_T("주문잔여수량"),
		_T("계약단위금액"),
		_T("FX주문총금액"),
		_T("FX잔여총금액"),
		_T("가격조건구분코드"),
		_T("체결조건구분코드"),
		_T("1차스탑로스여부"),
		_T("1차지정가여부"),
		_T("1차스탑로스가격"),
		_T("1차지정가격"),
		_T("1차추적손절매가격"),
		_T("2차스탑로스여부"),
		_T("2차지정가여부"),
		_T("2차스탑로스가격"),
		_T("2차지정가격"),
		_T("2차추적손절매가격"),
		_T("평균체결가격"),
		_T("체결율"),
		_T("현재가격"),
		_T("통신매체구분코드"),
		_T("주문유형구분코드"),
		_T("주문상태구분코드"),
		_T("FCM주문번호"),
		_T("사용자ID"),
		_T("공인IP주소"),
		_T("거래소접수시각"),
		_T("거래소체결시각"),
		_T("주문시각"),
		_T("체결시각"),
		_T("통화코드"),
		_T("가격소수점이하길이"),
		_T("매매가격차이내용") };

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
// Comment       : 예수금
//******************************************************************
void CFxMarginOrdDlg::InitListDeposit()
{
	CRect rc;
	m_listDeposit.GetClientRect(rc);
	m_listDeposit.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("통화"), _T("전일현금잔액"), _T("입출금액"), _T("FX수수료"), _T("롤오버이자"),
		_T("당일예탁금"), _T("청산금액"), _T("미결제평가손익"), _T("평가예탁"),
		_T("위탁증거금"), _T("추가증거금"), _T("미수금액"), _T("주문가능금액"), _T("인출가능금액"), _T("유지증거금"), _T("위험율") };

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
	TCHAR *strTitle[] = { _T("포지션번호"),
		_T("대체번호"),
		_T("계좌번호"),
		_T("계좌상품번호"),
		_T("체결일자"),
		_T("관리부점"),
		_T("위탁자기구분"),
		_T("딜링하우스번호"),
		_T("상품"),
		_T("호가고유번호"),
		_T("매도매수구분"),
		_T("체결가격"),
		_T("최초체결수량"),
		_T("청산수량"),
		_T("체결취소거래수량"),
		_T("미결제약정수량"),
		_T("미결제약정금액2"),
		_T("미결제약정금액3"),
		_T("체결PIP가치금액"),
		_T("약정금액"),
		_T("미결제약정금액"),
		_T("교차환율"),
		_T("정산가격"),
		_T("평가손익금액"),
		_T("PIP가치금액"),
		_T("환산평가손익금액"),
		_T("정산교차환율"),
		_T("온라인거래여부"),
		_T("체결번호"),
		_T("보유포지션여부"),
		_T("사용여부"),
		_T("주문번호"),
		_T("원주문번호"),
		_T("모주문번호"),
		_T("주문그룹번호"),
		_T("주문일자"),
		_T("고객명"),
		_T("주문가격"),
		_T("시장가격적용설정금액"),
		_T("주문수량"),
		_T("정정수량"),
		_T("취소수량"),
		_T("체결수량"),
		_T("주문잔여수량"),
		_T("가격조건구분"),
		_T("체결조건구분"),
		_T("1차스탑로스여부"),
		_T("1차지정가여부"),
		_T("1차구분여부"),
		_T("1차스탑로스가격"),
		_T("1차지정가격"),
		_T("1차추적손절매가격"),
		_T("계약단위금액"),
		_T("주문방향구분"),
		_T("평균체결가격"),
		_T("현재가격"),
		_T("상품2")	};

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
// Function      : 로그인
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedLogin()
{
	//로그인 ID
	m_editUserID.GetWindowText(m_strLoginID);

	//로그인 비밀번호
	m_editPwd.GetWindowText(m_strLoginPwd);

	//공인인증 비밀번호
	m_editAuthPwd.GetWindowText(m_strCertPwd);

	if (m_strLoginID.IsEmpty() || m_strLoginPwd.IsEmpty())
	{
		::AfxMessageBox("ID, 비번은 필수 입력입니다.");
		return;
	}

	/**********************************
	* 강제 접속 IP 셋팅
	**********************************/
	CString strIpAddress;
	GetDlgItem(IDC_EDIT_IP)->GetWindowText(strIpAddress);
	m_CommAgent.SetConnectIPList(strIpAddress);

	if (!m_bCommConnect)
	{
		/**********************************
		 * 통신모듈 초기화 및 통신 연결
		 **********************************/
		if (m_CommAgent.CommInit() < 0)
			::AfxMessageBox(m_CommAgent.GetLastErrMsg());
	}

	//연결상태(TRUE : 연결, FALSE : 끊김)
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}
	
	/**********************************
	* 로그인을 요청한다.
	**********************************/
	if (m_CommAgent.CommLogin(m_strLoginID, m_strLoginPwd, m_strCertPwd) == 0)
	{
		//로그인 실패
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());

		m_CommAgent.CommTerminate(TRUE);
	}

	/**********************************
	 * 로그인이 완료되면 주문 실시간을 등록한다.
	 * 주문 실시간 통보는 사용자ID가 등록키가 된다.
	 **********************************/
	//미체결/체결 실시간 통보
	m_CommAgent.RegisterReal("FX0", m_strLoginID);
	
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : 로그아웃
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedLogout()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	/**********************************
	* 로그아웃한다.
	**********************************/
	m_CommAgent.CommLogout(m_strLoginID);

	//모든 실시간등록을 해제한다.
	m_CommAgent.AllUnRegisterReal();

	/**********************************
	 * 통신연결을 끊는다.
	 **********************************/
	m_CommAgent.CommTerminate(TRUE);

	//연결상태(TRUE : 연결, FALSE : 끊김)
	m_bCommConnect = m_CommAgent.CommGetConnectState();
}

//*******************************************************************
// Function Name : OnBnClickedOk
// Function      : 대화창 종료
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	switch (m_nSeverType)
	{
		case 0 : //실거래
			RequestAccList();
		break;
		case 1 : //국내모의
			OnBnClickedBtnLoadUserAcc();
		break;
		case 2 : //해외모의
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_listAccNo.DeleteAllItems();

	//보유계좌 수를 반환한다.
	int nAccCnt = m_CommAgent.GetUserAccCnt();
	CString strAccNoPrtd; //종합계좌번호(8) + 상품번호(3)
	CString strAccNo;	//계좌번호
	CString strAPNO;	//계좌대체번호
	CString strPrdtNo;	//계좌상품번호

	m_listAccNo.SetRedraw(FALSE);
	int nListIndex = 0;

	for (int i = 0; i < nAccCnt; i++)
	{
		//종합계좌번호(8) + 상품번호(3)
		strAccNoPrtd = m_CommAgent.GetUserAccNo(i);

		if(strAccNoPrtd.IsEmpty()) continue;

		//앞에 8자리는 종합계좌번호
		strAccNo = strAccNoPrtd.Mid(0, 8);
		//뒤에 3자리는 계좌상품번호
		strPrdtNo = strAccNoPrtd.Mid(8, 3);

		strAPNO = GetAccAPNO(strAccNo + strPrdtNo);	//종합계좌대체번호
		
		if (!strPrdtNo.IsEmpty())
		{
			LV_ITEM	lvItem;
			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listAccNo.InsertItem(&lvItem);

			m_listAccNo.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strAccNo);		//종합계좌번호
			m_listAccNo.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strAPNO);		//대체종합계좌번호
			m_listAccNo.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strPrdtNo);		//계좌상품번호
			m_listAccNo.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)"");		//계좌명
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
// Comment       : 모의접속일 때 종합계좌대체번호 얻어오는 함수
//******************************************************************
CString CFxMarginOrdDlg::GetAccAPNO(CString strAccNo)
{
	CString strAPNO;

	//0-리얼, 1-국내모의, 2-해외모의
	switch (m_nSeverType)
	{
		case 0:	//리얼
		case 1:	//국내모의
		{
			strAPNO = m_CommAgent.GetAccInfo(0, strAccNo);
		}
		break;
		case 2:	//해외모의
		{
			strAccNo.Trim();

			if (strAccNo.GetLength() > 8)
				strAccNo = strAccNo.Mid(0, 8);

			//모의일 때는 모의용 계좌조회 Tran으로 가져온 대체번호를 사용한다.
			int nAccCnt = m_arrAccNo.GetSize();			//계좌목록
			int nApnoCnt = m_arrAccAPNO.GetSize();		//종합계좌대체번호목록

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
// Comment       : 계좌목록 조회
//******************************************************************
void CFxMarginOrdDlg::RequestAccList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	m_listAccNo.DeleteAllItems();

	CString strTrCode = "HHTACCNM01";	//Tran코드(리소스파일 참고)
	CString strInRecName1 = "InRec1";	//입력 레코드명(리소스파일 참고)
	CString strInRecName2 = "InRec2";	//입력 레코드명(리소스파일 참고)

	//InRec1 입력
	CString strfunc;		//기능구분코드(Q:Query,U:UPDATE,M:Upate and Query)
	CString strusid;		//사용자아이디
	CString strerrc;		//에러코드
	CString stremsg;		//에러메시지
	CString strnrec;		//입력건수

	//InRec2 입력
	CString straccn;		//계좌번호
	CString strsub_accn;	//대체계좌번호
	CString stracnm;		//계좌명
	CString strachk;		//계좌특성(00:기본계좌,01: 화면상에 보이지 않는계좌)
	CString strpwch;		//은행연계계좌여부

	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdAccNoList = m_CommAgent.CreateRequestID();

	strfunc = "Q";			//기능구분코드(Q:Query,U:UPDATE,M:Upate and Query)
	strusid = m_strLoginID;	//사용자아이디
	strnrec = "1";			//입력건수

	/*InRec1 레코드는 단건 입력이다.*/
	m_CommAgent.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "func", strfunc); //기능구분코드
	m_CommAgent.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "usid", strusid); //사용자아이디
	m_CommAgent.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "errc", strerrc); //에러코드
	m_CommAgent.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "emsg", stremsg); //에러메시지
	m_CommAgent.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "nrec", strnrec); //입력건수

	/*InRec2 레코드는 복수건 입력이다.*/
	/*	REC_NAME=InRec2, INOUT=0, ARRAY=3, ARRINFO=InRec1.nrec;
	ARRAY 가 '0'보다 크면 입력이 복수건이다.	*/
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdAccNoList, strTrCode, strInRecName2, _ttoi(strnrec));

	for (int i = 0; i < _ttoi(strnrec); i++)
	{
		m_CommAgent.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "accn", straccn, i);			//계좌번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "sub_accn", strsub_accn, i);	//대체계좌번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "acnm", stracnm, i);			//계좌명
		m_CommAgent.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "achk", strachk, i);			//계좌특성
		m_CommAgent.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "pwch", strpwch, i);			//은행연계계좌여부
	}//End of for

	CString strBenefitAcc = "N";		//수익증권계좌 구분
	CString strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호

	//[4] 서버에 Tran조회 요청한다.
	if (m_CommAgent.RequestTran(m_nRqIdAccNoList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : RequestDemoAccList
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 해외모의 계좌목록 조회
//******************************************************************
void CFxMarginOrdDlg::RequestFDemoAccList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	m_listAccNo.DeleteAllItems();

	CString strTrCode = "OTS5991Q03";	//Tran코드(리소스파일 참고)
	CString strInRecName1 = "OTS5991Q03_in";	//입력 레코드명(리소스파일 참고)
	
	CString strUSR_ID = m_strLoginID;		//사용자ID

	/*-------------------------------*
		[1] Request ID생성
	 *-------------------------------*/
	m_nRqIdFDemoAccNoList = m_CommAgent.CreateRequestID();
	m_CommAgent.SetTranInputData(m_nRqIdFDemoAccNoList, strTrCode, strInRecName1, "USR_ID", strUSR_ID);		//사용자ID

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "1";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호

	/*-------------------------------*
		[2] 서버에 Tran조회 요청한다.
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
// Comment       : 매수/매도 주문 전송
//******************************************************************
BOOL CFxMarginOrdDlg::SendSellBuyOrder(CString strDealingSide, int nRqId, CString strOrderKind /*= _T("")*/)
{
	CString strTrCode = "OTS5901U31";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5901U31_in";		//입력 레코드명(리소스파일 참고)

	//[1] Request ID생성
	CString strCTNO;		//종합계좌대체번호
	CString strAPNO;		//계좌상품번호
	CString strPWD;			//비밀번호
	CString strFDM_UNQ_NO;	//딜링하우스고유번호
	CString strPRDT_CD;		//상품코드
	CString strNMPR_UNQ_NO;	//호가고유번호
	CString strENTR_CLR_DCD;//진입청산구분코드
	CString strPST_NO;		//포지션번호
	CString strODRV_SELL_BUY_DCD;		//해외파생매도매수구분코드
	CString strPRC_CND_DCD;		//가격조건구분코드
	CString strODRV_ORDR_PRC;		//해외파생주문가격
	CString strORDR_QNT;		//주문수량
	CString strSQ1_STLS_YN;		//1차스탑로스여부
	CString strSQ1_APMPR_YN;		//1차지정가여부
	CString strSQ1_STLS_PRC;		//1차스탑로스가격
	CString strSQ1_APPN_PRC;		//1차지정가격
	CString strSQ1_CHAS_STLS_PRC;		//1차추적손절매가격
	CString strSQ2_STLS_YN;		//2차스탑로스여부
	CString strSQ2_APMPR_YN;		//2차지정가여부
	CString strSQ2_STLS_PRC;		//2차스탑로스가격
	CString strSQ2_APPN_PRC;		//2차지정가격
	CString strSQ2_CHAS_STLS_PRC;		//2차추적손절매가격
	CString strORDR_DRCN_DCD;		//주문방향구분코드
	CString strORDR_SRC_DCD;		//주문원천구분코드
	CString strTRDE_PRC_DFRN_CTNS;		//매매가격차이내용

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//계좌상품번호
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//비밀번호
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//계좌비밀번호는 단방향 암호화를 해야된다.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//상품코드

	//딜링하우스고유번호
	GetDlgItem(IDC_EDIT_SYMBOL_HOUSE)->GetWindowText(strFDM_UNQ_NO);
	
	//상품코드
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//호가고유번호
	strNMPR_UNQ_NO = _T("0");

	//주문수량
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	//1차스탑로스가격(STOP)
	GetDlgItem(IDC_EDIT_STOP_PRC)->GetWindowText(strSQ1_STLS_PRC);
	//1차스탑로스여부(STOP)
	if (_ttof(strSQ1_STLS_PRC))
		strSQ1_STLS_YN = _T("Y");
	else
		strSQ1_STLS_YN = _T("N");

	//1차지정가격(LIMIT)
	GetDlgItem(IDC_EDIT_LIMIT_PRC)->GetWindowText(strSQ1_APPN_PRC);
	//1차지정가여부(LIMIT)
	if (_ttof(strSQ1_APPN_PRC))
		strSQ1_APMPR_YN = _T("Y");
	else
		strSQ1_APMPR_YN = _T("N");

	//1차추적손절매가격(T.Stop)
	GetDlgItem(IDC_EDIT_T_STOP_PRC)->GetWindowText(strSQ1_CHAS_STLS_PRC);
	//2차스탑로스여부
	if (_ttof(strSQ1_CHAS_STLS_PRC))
		strSQ2_STLS_YN = _T("Y");
	else
		strSQ2_STLS_YN = _T("N");

	strSQ2_STLS_PRC = _T("0");		//2차스탑로스가격(사용안함)
	strSQ2_APPN_PRC = _T("0");		//2차지정가격(사용안함)
	strSQ2_APMPR_YN = _T("N");		//2차지정가여부(사용안함)
	strSQ2_CHAS_STLS_PRC = _T("0");		//2차추적손절매가격(사용안함)

	//주문방향구분코드(N-일반주문, W-대기주문 (일반주문만 사용))
	strORDR_DRCN_DCD = _T("N");

	//주문원천구분코드(C-일반주문)
	strORDR_SRC_DCD = _T("C");

	//매매가격차이내용(사용안함)
	strTRDE_PRC_DFRN_CTNS.Empty();
	
	//청산주문, SL주문
	if (!strOrderKind.CompareNoCase(_T("CloseOrder")) ||
		!strOrderKind.CompareNoCase(_T("SLOrder")))
	{

		/***************************************************
		* ***** 주의 *****
		* 청산주문은(반대매매 청산 포함) Stop, Limit을 취소 후에
		* 가능합니다.
		***************************************************/

		//진입청산구분코드(C - 청산, O - 신규)
		strENTR_CLR_DCD = _T("C");

		//포지션번호(청산주문 필요)
		GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strPST_NO);

		//청산은 신규주문의 반대 매매구분으로 주문을 낸다.
		if (!strDealingSide.CompareNoCase(_T("S")))
			strODRV_SELL_BUY_DCD = _T("B");
		else
			strODRV_SELL_BUY_DCD = _T("S");

		strPRC_CND_DCD = _T("2"); //청산주문은 주문유형을 시장가로 한다.

		CString strSLOrderNo;
		GetDlgItem(IDC_ORDER_NO)->GetWindowText(strSLOrderNo);
		strSLOrderNo.Trim();

		//SL주문이면 주문구분을 변경한다.
		if (!strOrderKind.CompareNoCase(_T("SLOrder")))
		{
			//T.S
			if (!strSQ2_STLS_YN.CompareNoCase(_T("Y")))
			{
				strPRC_CND_DCD = _T("6");
			}
			//Stop 또는 Limit
			else if (!strSQ1_STLS_YN.CompareNoCase(_T("Y")) ||
					 !strSQ1_APMPR_YN.CompareNoCase(_T("Y")))
			{
				strPRC_CND_DCD = _T("4");
			}
			//OCO 주문
			else if (!strSQ1_STLS_YN.CompareNoCase(_T("Y")) &&
					 !strSQ1_APMPR_YN.CompareNoCase(_T("Y")))
			{
				strPRC_CND_DCD = _T("5");
			}
		}
	}
	else
	{
		//진입청산구분코드(C - 청산, O - 신규)
		strENTR_CLR_DCD = _T("O");

		//해외파생매도매수구분코드(S-매도, B-매수)
		strODRV_SELL_BUY_DCD = strDealingSide;

		//가격조건구분코드
		if (m_cmdOrdType.GetCurSel() >= 0)
			strPRC_CND_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];		//가격조건구분코드
	}

	//해외파생주문가격
	if (strPRC_CND_DCD == _T("1") || strPRC_CND_DCD == _T("3"))	//지정가, 역지정가(STOP)
		GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strODRV_ORDR_PRC);
	else //시장가
		strODRV_ORDR_PRC = _T("0");

	//[2] Tran조회 입력값을 입력한다.
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "PWD", strPWD);		//비밀번호
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//딜링하우스고유번호
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "NMPR_UNQ_NO", strNMPR_UNQ_NO);		//호가고유번호
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "ENTR_CLR_DCD", strENTR_CLR_DCD);		//진입청산구분코드
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "PST_NO", strPST_NO);		//포지션번호
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "PRC_CND_DCD", strPRC_CND_DCD);		//가격조건구분코드
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "ODRV_ORDR_PRC", strODRV_ORDR_PRC);		//해외파생주문가격
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "ORDR_QNT", strORDR_QNT);		//주문수량
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ1_STLS_YN", strSQ1_STLS_YN);		//1차스탑로스여부
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ1_APMPR_YN", strSQ1_APMPR_YN);		//1차지정가여부
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ1_STLS_PRC", strSQ1_STLS_PRC);		//1차스탑로스가격
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ1_APPN_PRC", strSQ1_APPN_PRC);		//1차지정가격
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ1_CHAS_STLS_PRC", strSQ1_CHAS_STLS_PRC);		//1차추적손절매가격
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ2_STLS_YN", strSQ2_STLS_YN);		//2차스탑로스여부
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ2_APMPR_YN", strSQ2_APMPR_YN);		//2차지정가여부
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ2_STLS_PRC", strSQ2_STLS_PRC);		//2차스탑로스가격
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ2_APPN_PRC", strSQ2_APPN_PRC);		//2차지정가격
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "SQ2_CHAS_STLS_PRC", strSQ2_CHAS_STLS_PRC);		//2차추적손절매가격
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//주문방향구분코드
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "ORDR_SRC_DCD", strORDR_SRC_DCD);		//주문원천구분코드
	m_CommAgent.SetTranInputData(nRqId, "OTS5901U31", "OTS5901U31_in", "TRDE_PRC_DFRN_CTNS", strTRDE_PRC_DFRN_CTNS);		//매매가격차이내용

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[3] 서버에 Tran조회 요청한다.
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
// Comment       : 매도주문
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedBtnSell()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nRqIdSellOrd = m_CommAgent.CreateRequestID();
	SendSellBuyOrder("S", m_nRqIdSellOrd);	//매도주문 전송
}

//*******************************************************************
// Function Name : OnBnClickedBtnBuy
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 매수주문
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedBtnBuy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nRqIdBuyOrd = m_CommAgent.CreateRequestID();
	SendSellBuyOrder("B", m_nRqIdBuyOrd);	//매도주문 전송
}

//*******************************************************************
// Function Name : OnBnClickedBtnChange
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 정정주문
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedBtnChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5901U32";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5901U32_in";	//입력 레코드명(리소스파일 참고)
	
	//[1] Request ID생성
	m_nRqIdChangeOrd = m_CommAgent.CreateRequestID();

	//[2] Tran조회 입력값을 입력한다.
	CString strODRV_OR_ODNO;		//해외파생원주문번호
	CString strCTNO;		//종합계좌대체번호
	CString strAPNO;		//계좌상품번호
	CString strPWD;		//비밀번호
	CString strODRV_SELL_BUY_DCD;		//해외파생매도매수구분코드
	CString strFDM_UNQ_NO;		//딜링하우스고유번호
	CString strPRDT_CD;		//상품코드
	CString strNMPR_UNQ_NO;		//호가고유번호
	CString strCNCS_CND_DCD;		//체결조건구분코드
	CString strORDR_EXPR_DT;		//주문만료일자
	CString strPRC_CND_DCD;		//가격조건구분코드
	CString strODRV_ORDR_PRC;		//해외파생주문가격
	CString strORDR_QNT;		//주문수량
	CString strSQ1_STLS_YN;		//1차스탑로스여부
	CString strSQ1_APMPR_YN;		//1차지정가여부
	CString strSQ1_STLS_PRC;		//1차스탑로스가격
	CString strSQ1_APPN_PRC;		//1차지정가격
	CString strSQ1_CHAS_STLS_PRC;		//1차추적손절매가격
	CString strSQ2_STLS_YN;		//2차스탑로스여부
	CString strSQ2_STLS_PRC;		//2차스탑로스가격
	CString strSQ2_APMPR_YN;		//2차지정가여부
	CString strSQ2_APPN_PRC;		//2차지정가격
	CString strSQ2_CHAS_STLS_PRC;		//2차추적손절매가격
	CString strORDR_DRCN_DCD;		//주문방향구분코드
	CString strTRDE_PRC_DFRN_CTNS;		//매매가격차이내용

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//계좌상품번호
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//비밀번호
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//계좌비밀번호는 단방향 암호화를 해야된다.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//상품코드

	//해외파생원주문번호
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strODRV_OR_ODNO);

	//딜링하우스고유번호
	GetDlgItem(IDC_EDIT_SYMBOL_HOUSE)->GetWindowText(strFDM_UNQ_NO);

	//상품코드
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//호가고유번호
	strNMPR_UNQ_NO = _T("0");

	//해외파생매도매수구분코드
	if (m_cmdOrdType.GetCurSel() >= 0)
		strODRV_SELL_BUY_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];		//가격조건구분코드

	//주문수량
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	//1차스탑로스가격(STOP)
	GetDlgItem(IDC_EDIT_STOP_PRC)->GetWindowText(strSQ1_STLS_PRC);
	//1차스탑로스여부(STOP)
	if (_ttof(strSQ1_STLS_PRC))
		strSQ1_STLS_YN = _T("Y");
	else
		strSQ1_STLS_YN = _T("N");

	//1차지정가격(LIMIT)
	GetDlgItem(IDC_EDIT_LIMIT_PRC)->GetWindowText(strSQ1_APPN_PRC);
	//1차지정가여부(LIMIT)
	if (_ttof(strSQ1_APPN_PRC))
		strSQ1_APMPR_YN = _T("Y");
	else
		strSQ1_APMPR_YN = _T("N");

	//1차추적손절매가격(T.Stop)
	GetDlgItem(IDC_EDIT_T_STOP_PRC)->GetWindowText(strSQ1_CHAS_STLS_PRC);
	//2차스탑로스여부
	if (_ttof(strSQ1_CHAS_STLS_PRC))
		strSQ2_STLS_YN = _T("Y");
	else
		strSQ2_STLS_YN = _T("N");

	strSQ2_STLS_PRC = _T("0");		//2차스탑로스가격(사용안함)
	strSQ2_APPN_PRC = _T("0");		//2차지정가격(사용안함)
	strSQ2_APMPR_YN = _T("N");		//2차지정가여부(사용안함)
	strSQ2_CHAS_STLS_PRC = _T("0");		//2차추적손절매가격(사용안함)

	//주문방향구분코드(N-일반주문, W-대기주문 (일반주문만 사용))
	strORDR_DRCN_DCD = _T("N");

	//매매가격차이내용(사용안함)
	strTRDE_PRC_DFRN_CTNS.Empty();

	//가격조건구분코드
	if (m_cmdOrdType.GetCurSel() >= 0)
		strPRC_CND_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];

	//해외파생주문가격
	if (strPRC_CND_DCD == _T("1") || strPRC_CND_DCD == _T("3"))	//지정가, 역지정가(STOP)
		GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strODRV_ORDR_PRC);
	else //시장가
		strODRV_ORDR_PRC = _T("0");

	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//해외파생원주문번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "PWD", strPWD);		//비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//딜링하우스고유번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "NMPR_UNQ_NO", strNMPR_UNQ_NO);		//호가고유번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "CNCS_CND_DCD", strCNCS_CND_DCD);		//체결조건구분코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "ORDR_EXPR_DT", strORDR_EXPR_DT);		//주문만료일자
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "PRC_CND_DCD", strPRC_CND_DCD);		//가격조건구분코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "ODRV_ORDR_PRC", strODRV_ORDR_PRC);		//해외파생주문가격
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "ORDR_QNT", strORDR_QNT);		//주문수량
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_STLS_YN", strSQ1_STLS_YN);		//1차스탑로스여부
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_APMPR_YN", strSQ1_APMPR_YN);		//1차지정가여부
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_STLS_PRC", strSQ1_STLS_PRC);		//1차스탑로스가격
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_APPN_PRC", strSQ1_APPN_PRC);		//1차지정가격
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_CHAS_STLS_PRC", strSQ1_CHAS_STLS_PRC);		//1차추적손절매가격
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_STLS_YN", strSQ2_STLS_YN);		//2차스탑로스여부
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_STLS_PRC", strSQ2_STLS_PRC);		//2차스탑로스가격
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_APMPR_YN", strSQ2_APMPR_YN);		//2차지정가여부
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_APPN_PRC", strSQ2_APPN_PRC);		//2차지정가격
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_CHAS_STLS_PRC", strSQ2_CHAS_STLS_PRC);		//2차추적손절매가격
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//주문방향구분코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, "OTS5901U32", "OTS5901U32_in", "TRDE_PRC_DFRN_CTNS", strTRDE_PRC_DFRN_CTNS);		//매매가격차이내용

	CString strBenefitAcc = "N";		//수익증권계좌 구분
	CString strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[3] 서버에 Tran조회 요청한다.
	if (m_CommAgent.RequestTran(m_nRqIdChangeOrd, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", nRequestDataCnt) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnCancel
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 취소주문
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5901U33";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5901U33_in";	//입력 레코드명(리소스파일 참고)

	//[1] Request ID생성
	m_nRqIdCancelOrd = m_CommAgent.CreateRequestID();

	//[2] Tran조회 입력값을 입력한다.
	CString strODRV_OR_ODNO;		//해외파생원주문번호
	CString strCTNO;		//종합계좌대체번호
	CString strAPNO;		//계좌상품번호
	CString strPWD;		//비밀번호
	CString strFDM_UNQ_NO;		//딜링하우스고유번호
	CString strPRDT_CD;		//상품코드
	CString strORDR_QNT;		//주문수량
	CString strORDR_DRCN_DCD;		//주문방향구분코드

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//계좌상품번호
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//비밀번호
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//계좌비밀번호는 단방향 암호화를 해야된다.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//상품코드

	//해외파생원주문번호
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strODRV_OR_ODNO);

	//딜링하우스고유번호
	GetDlgItem(IDC_EDIT_SYMBOL_HOUSE)->GetWindowText(strFDM_UNQ_NO);

	//상품코드
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//주문수량
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	
	//주문방향구분코드(N-일반주문, W-대기주문 (일반주문만 사용))
	strORDR_DRCN_DCD = _T("N");

	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//해외파생원주문번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "PWD", strPWD);		//비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//딜링하우스고유번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "ORDR_QNT", strORDR_QNT);		//주문수량
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, "OTS5901U33", "OTS5901U33_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//주문방향구분코드

	CString strBenefitAcc = "N";		//수익증권계좌 구분
	CString strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[3] 서버에 Tran조회 요청한다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_listDeposit.DeleteAllItems();
	m_strListDepositNextRqKey.Empty();				//연속키를 초기화시킨다.

	CString strTrCode = "OTS5914Q51";				//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5914Q51_in";			//입력 레코드명(리소스파일 참고)

	/*-------------------------------*
	 [1] Request ID생성
	*-------------------------------*/
	m_nRqIdDepositList = m_CommAgent.CreateRequestID();

	CString strINQ_DT;			//영업일자
	CString strCTNO;			//대체종합계좌번호
	CString strAPNO;			//계좌상품번호
	CString strPWD;				//비밀번호(단방향 암호화를 한다.)

	//조회일자
	m_dateTime1.GetWindowText(strINQ_DT);
	strINQ_DT.Remove('-');
	
	//계좌번호
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	
	//계좌상품번호
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);
	strCTNO = GetAccAPNO(strCTNO + strAPNO);	//종합계좌대체번호

	//계좌비번
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD); //암호화한다.


	/*-------------------------------*
	 [2] Tran조회 입력값을 입력한다.
	 *-------------------------------*/
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "INQ_DT", strINQ_DT);	//영업일자
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "CTNO", strCTNO);		//대체종합계좌번호
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "ACNT_PWD", strPWD);		//비밀번호

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "1";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	/*-------------------------------*
	 [3] 서버에 Tran조회 요청한다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5914Q51";				//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5914Q51_in";			//입력 레코드명(리소스파일 참고)

	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdDepositList = m_CommAgent.CreateRequestID();

	CString strINQ_DT;		//영업일자
	CString strCTNO;		//대체종합계좌번호
	CString strAPNO;		//계좌상품번호
	CString strPWD;			//비밀번호

	//조회일자
	m_dateTime1.GetWindowText(strINQ_DT);
	strINQ_DT.Remove('-');

	//계좌번호
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);

	//계좌상품번호
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);
	strCTNO = GetAccAPNO(strCTNO + strAPNO);	//종합계좌대체번호

	//계좌비번
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD); //암호화한다.

	/*-------------------------------*
	[2] Tran조회 입력값을 입력한다.
	*-------------------------------*/
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "INQ_DT", strINQ_DT);	//영업일자
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "CTNO", strCTNO);		//대체종합계좌번호
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "ACNT_PWD", strPWD);		//비밀번호

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "3";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	/*-------------------------------*
	[3] 서버에 Tran조회 요청한다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_listNonExec.DeleteAllItems();
	m_strListNonExecNextRqKey.Empty(); //연속키를 초기화시킨다.

	CString strTrCode = "OTS5913Q53";				//Tran코드(리소스파일 참고)
	
	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdNonExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] 입력 건수를 입력한다.
	*-------------------------------*/
	CString strAccNo;
	CString strINQ_STRT_DT;		//조회시작일자
	CString strINQ_END_DT;		//조회종료일자
	CString strSORT_MTH;		//정렬방법
	CString strCTNO;			//종합계좌대체번호
	CString strAPNO;			//계좌상품번호
	CString strPRDT_CD;			//상품코드
	CString strACNT_PWD;		//계좌비밀번호
	CString strINQ_DVSN;		//조회구분

	//조회시작일자
	m_dateTimeN1.GetWindowText(strINQ_STRT_DT);
	strINQ_STRT_DT.Remove('-');

	//조회종료일자
	m_dateTimeN2.GetWindowText(strINQ_END_DT);
	strINQ_END_DT.Remove('-');

	//정렬방법(1-역순, 2 정순)
	strSORT_MTH = _T("1");

	// 조회구분 0:전체(미체결+거부), 1:미체결
	if(((CButton*)GetDlgItem(IDC_RADIO_EX1))->GetCheck())
		strINQ_DVSN = "1";	//미체결만 조회
	else
		strINQ_DVSN = "0"; //미체결 + 거부 조회


	//계좌대체번호를 얻어온다.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);

	//계좌상품번호
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);
	
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호

	//계좌비밀번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);

	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "INQ_STRT_DT", strINQ_STRT_DT);		//조회시작일자
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "INQ_END_DT", strINQ_END_DT);		//조회종료일자
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "SORT_MTH", strSORT_MTH);		//정렬방법
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "INQ_DVSN", strINQ_DVSN);		//조회구분

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "1";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[4] 서버에 Tran조회 요청한다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	CString strTrCode = "OTS5913Q53";				//Tran코드(리소스파일 참고)
	
	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdNonExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] 입력 건수를 입력한다.
	*-------------------------------*/
	CString strAccNo;
	CString strINQ_STRT_DT;		//조회시작일자
	CString strINQ_END_DT;		//조회종료일자
	CString strSORT_MTH;		//정렬방법
	CString strCTNO;			//종합계좌대체번호
	CString strAPNO;			//계좌상품번호
	CString strPRDT_CD;			//상품코드
	CString strACNT_PWD;		//계좌비밀번호
	CString strINQ_DVSN;		//조회구분

	//조회시작일자
	m_dateTimeN1.GetWindowText(strINQ_STRT_DT);
	strINQ_STRT_DT.Remove('-');

	//조회종료일자
	m_dateTimeN2.GetWindowText(strINQ_END_DT);
	strINQ_END_DT.Remove('-');

	//정렬방법(1-역순, 2 정순)
	strSORT_MTH = _T("1");

	// 조회구분 0:전체(미체결+거부), 1:미체결
	if (((CButton*)GetDlgItem(IDC_RADIO_EX1))->GetCheck())
		strINQ_DVSN = "1";	//미체결만 조회
	else
		strINQ_DVSN = "0"; //미체결 + 거부 조회

	//계좌대체번호를 얻어온다.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);

	//계좌상품번호
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호

	//계좌비밀번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);

	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "INQ_STRT_DT", strINQ_STRT_DT);		//조회시작일자
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "INQ_END_DT", strINQ_END_DT);		//조회종료일자
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "SORT_MTH", strSORT_MTH);		//정렬방법
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, "OTS5913Q53", "OTS5913Q53_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "3";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[4] 서버에 Tran조회 요청한다.
	if(m_CommAgent.RequestTran(m_nRqIdNonExecList, strTrCode, strBenefitAcc, strPreNext, m_strListNonExecNextRqKey, strScreenNo, "Q", nRequestDataCnt) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}


//*******************************************************************
// Function Name : OnBnClickedBtnReqExecList
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 주문체결내역조회
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedBtnReqExecList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_listExec.DeleteAllItems();
	m_strListExecNextRqKey.Empty(); //연속키를 초기화시킨다.

	CString strTrCode = "OTS5913Q52";				//Tran코드(리소스파일 참고)
	
	/*-------------------------------*
		[1] Request ID생성
	 *-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
		[2] 입력 건수를 입력한다.
	 *-------------------------------*/
	CString strAccNo;
	CString strINQ_STRT_DT;		//조회시작일자
	CString strINQ_END_DT;		//조회종료일자
	CString strSORT_MTH;		//정렬방법
	CString strCTNO;		//종합계좌대체번호
	CString strAPNO;		//계좌상품번호
	CString strPRDT_CD;		//상품코드
	CString strACNT_PWD;		//계좌비밀번호

	//[3] Tran조회 입력값을 입력한다.

	//조회시작일자
	m_dateTimeE1.GetWindowText(strINQ_STRT_DT);
	strINQ_STRT_DT.Remove('-');

	//조회종료일자
	m_dateTimeE2.GetWindowText(strINQ_END_DT);
	strINQ_END_DT.Remove('-');

	//정렬방법
	strSORT_MTH = _T("0");

	//계좌대체번호를 얻어온다.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);

	//계좌상품번호
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호

	//계좌비밀번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);

	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "INQ_STRT_DT", strINQ_STRT_DT);		//조회시작일자
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "INQ_END_DT", strINQ_END_DT);		//조회종료일자
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "SORT_MTH", strSORT_MTH);		//정렬방법
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "1";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[4] 서버에 Tran조회 요청한다.
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
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5913Q52";				//Tran코드(리소스파일 참고)

	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] 입력 건수를 입력한다.
	*-------------------------------*/
	CString strAccNo;
	CString strINQ_STRT_DT;		//조회시작일자
	CString strINQ_END_DT;		//조회종료일자
	CString strSORT_MTH;		//정렬방법
	CString strCTNO;		//종합계좌대체번호
	CString strAPNO;		//계좌상품번호
	CString strPRDT_CD;		//상품코드
	CString strACNT_PWD;		//계좌비밀번호

	//[3] Tran조회 입력값을 입력한다.

	//조회시작일자
	m_dateTimeE1.GetWindowText(strINQ_STRT_DT);
	strINQ_STRT_DT.Remove('-');

	//조회종료일자
	m_dateTimeE2.GetWindowText(strINQ_END_DT);
	strINQ_END_DT.Remove('-');

	//정렬방법
	strSORT_MTH = _T("0");

	//계좌대체번호를 얻어온다.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);

	//계좌상품번호
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호

	//계좌비밀번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);

	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "INQ_STRT_DT", strINQ_STRT_DT);		//조회시작일자
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "INQ_END_DT", strINQ_END_DT);		//조회종료일자
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "SORT_MTH", strSORT_MTH);		//정렬방법
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdExecList, "OTS5913Q52", "OTS5913Q52_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "3";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[4] 서버에 Tran조회 요청한다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_listBalance.DeleteAllItems();
	m_strListBalanceNextRqKey.Empty(); //연속키를 초기화시킨다.

	CString strTrCode = "OTS5919Q51";				//Tran코드(리소스파일 참고)
	CString strInRecName1 = "OTS5919Q51_in";	//입력 레코드명(리소스파일 참고)
	CString strInRecName2 = "OTS5919Q51_in_sub01";	//입력 레코드명(리소스파일 참고)

	CString strODRV_SELL_BUY_DCD;	//해외파생매도매수구분코드(0:전체, B:매수, S:매도)
	CString strCTNO;				//대체종합계좌번호
	CString strAPNO;				//계좌상품번호
	
	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdBalanceList = m_CommAgent.CreateRequestID();

	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드

	/*-------------------------------*
	[2] 입력 건수를 입력한다.
	*-------------------------------*/
	/*	REC_NAME=OTS5919Q51_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
	ARRAY 가 '0'보다 크면 입력이 복수건이다.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdBalanceList, strTrCode, strInRecName2, 1);

	CString strAccNo;
	CString strPrdt;
	CString strPWD;

	//[3] Tran조회 입력값을 입력한다.
	for (int i = 0; i < nInputCnt; i++)
	{
		//계좌대체번호를 얻어온다.
		GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
		
		//계좌상품번호
		GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strPrdt);
		strCTNO = GetAccAPNO(strAccNo + strPrdt); //종합계좌대체번호 조회

		//계좌비밀번호
		GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
		strPWD = m_CommAgent.GetEncrpyt(strPWD);

		//대체종합계좌번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "CTNO", strCTNO, i);

		//계좌상품번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "APNO", strPrdt, i);

		//계좌비밀번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "PWD", strPWD, i);
	}

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "1";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[4] 서버에 Tran조회 요청한다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5919Q51";				//Tran코드(리소스파일 참고)
	CString strInRecName1 = "OTS5919Q51_in";	//입력 레코드명(리소스파일 참고)
	CString strInRecName2 = "OTS5919Q51_in_sub01";	//입력 레코드명(리소스파일 참고)

	CString strODRV_SELL_BUY_DCD = "0";	//해외파생매도매수구분코드(0:전체, B:매수, S:매도)
	CString strCTNO;				//대체종합계좌번호
	CString strAPNO;				//계좌상품번호

	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdBalanceList = m_CommAgent.CreateRequestID();

	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드

	/*-------------------------------*
	[2] 입력 건수를 입력한다.
	*-------------------------------*/
	/*	REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
	ARRAY 가 '0'보다 크면 입력이 복수건이다.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdBalanceList, strTrCode, strInRecName2, nInputCnt);
	
	CString strAccNo;
	CString strPrdt;
	CString strPWD;

	//[3] Tran조회 입력값을 입력한다.
	for (int i = 0; i < nInputCnt; i++)
	{
		//계좌대체번호를 얻어온다.
		GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
		
		//계좌상품번호
		GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strPrdt);
		strCTNO = GetAccAPNO(strAccNo + strPrdt); //종합계좌대체번호 조회

		//계좌비밀번호
		GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
		strPWD = m_CommAgent.GetEncrpyt(strPWD);

		//대체종합계좌번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "CTNO", strCTNO, i);

		//계좌상품번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "APNO", strPrdt, i);

		//계좌비밀번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "PWD", strPWD, i);
	}

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "3";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[4] 서버에 Tran조회 요청한다.
	if(m_CommAgent.RequestTran(m_nRqIdBalanceList, strTrCode, strBenefitAcc, strPreNext, m_strListBalanceNextRqKey, strScreenNo, "Q", 0) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}


//*******************************************************************
// Function Name : OnGetTranData
// Function      : Tran 조회응답 이벤트
// Param         :	LONG nRequestId, 조회ID
//					LPCTSTR pBlock, 조회응답 데이터 블럭
//					long nBlockLength 조회응답 데이터 블럭 크기
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginOrdDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
{
	/* 주의 : OnGetTranData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
	이벤트 콜백함수 종료 후에는 유효하지 않습니다.*/

	CString strTrCode = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::TranCode);

	/*	0 : 연속조회 미사용,		1 : 이전 데이터 있음,	2 : 다음 데이터 있음
		3 : 이전/다음 데이터 있음	*/
	CString strPreNext = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::PrevNextCode);

	//연속조회키
	CString strPreNextContext = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::PrevNextKey);

	//조회응답 메시지코드
	CString strMsgCode = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::MsgCode);

	//조회응답 메시지
	CString strMsg = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::Msg);

	//조회응답 부가메시지코드
	CString strSubMsgCode = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::SubMsgCode);

	//조회응답 부가메시지
	CString strSubMsg = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::SubMsg);

	//에러여부( "1" : 에러, "0" : 정상)
	CString strIsError = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::Error);

	CString strErrMsg = m_CommAgent.GetLastErrMsg();

	CString strOutRecName;
	int nRowCnt = 0;

	/*---------------------------------------------
		통신 메시지
	 ---------------------------------------------*/
	if (!strErrMsg.IsEmpty())
		GetDlgItem(IDC_TRAN_MSG)->SetWindowText(strErrMsg);
	else
		GetDlgItem(IDC_TRAN_MSG)->SetWindowText(strMsg);

	//주문미체결내역
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
		다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		붙여 삽입한다.
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
			strFDM_UNQ_NO_PRDT_CD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FDM_UNQ_NO_PRDT_CD", nRow);		//딜링하우스고유번호상품코드
			strCANO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CANO", nRow);		//종합계좌번호
			strCTNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CTNO", nRow);		//종합계좌대체번호
			strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_ODNO", nRow);		//해외파생주문번호
			strFDM_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FDM_UNQ_NO", nRow);		//딜링하우스고유번호
			strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "PRDT_CD", nRow);		//상품코드
			strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_OR_ODNO", nRow);		//해외파생원주문번호
			strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_MO_ODNO", nRow);		//해외파생모주문번호
			strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_GRUP_NO", nRow);		//주문그룹번호
			strORDR_DT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_DT", nRow);		//주문일자
			strAPNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "APNO", nRow);		//계좌상품번호
			strCUST_NM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CUST_NM", nRow);		//고객명
			strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//해외파생매도매수구분코드
			strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_ORDR_PRC", nRow);		//해외파생주문가격
			strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_QNT", nRow);		//주문수량
			strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "RVSE_QNT", nRow);		//정정수량
			strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCL_QNT", nRow);		//취소수량
			strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_QNT", nRow);		//체결수량
			strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_RMN_QNT", nRow);		//주문잔여수량
			strCTRT_UN_AMT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CTRT_UN_AMT", nRow);		//계약단위금액
			strFX_ORDR_TOT_AMT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FX_ORDR_TOT_AMT", nRow);		//FX주문총금액
			strFX_RMN_TOT_AMT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FX_RMN_TOT_AMT", nRow);		//FX잔여총금액
			strPRC_CND_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "PRC_CND_DCD", nRow);		//가격조건구분코드
			strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_CND_DCD", nRow);		//체결조건구분코드
			strSQ1_STLS_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_STLS_YN", nRow);		//1차스탑로스여부
			strSQ1_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_APMPR_YN", nRow);		//1차지정가여부
			strSQ1_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_STLS_PRC", nRow);		//1차스탑로스가격
			strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_APPN_PRC", nRow);		//1차지정가격
			strSQ1_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_CHAS_STLS_PRC", nRow);		//1차추적손절매가격
			strSQ2_STLS_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_STLS_YN", nRow);		//2차스탑로스여부
			strSQ2_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_APMPR_YN", nRow);		//2차지정가여부
			strSQ2_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_STLS_PRC", nRow);		//2차스탑로스가격
			strSQ2_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_APPN_PRC", nRow);		//2차지정가격
			strSQ2_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_CHAS_STLS_PRC", nRow);		//2차추적손절매가격
			strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "AVR_CNCS_PRC", nRow);		//평균체결가격
			strCNCS_RT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_RT", nRow);		//체결율
			strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_NOW_PRC", nRow);		//해외파생현재가격
			strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "COMM_MDIA_DCD", nRow);		//통신매체구분코드
			strODRV_ORDR_TP_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_ORDR_TP_DCD", nRow);		//해외파생주문유형구분코드
			strORDR_STTS_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_STTS_DCD", nRow);		//주문상태구분코드
			strFCM_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FCM_ODNO", nRow);		//FCM주문번호
			strUSR_ID = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "USR_ID", nRow);		//사용자ID
			strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ATHZ_IP_ADDR", nRow);		//공인IP주소
			strEXCG_ACPT_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "EXCG_ACPT_TM", nRow);		//거래소접수시각
			strEXCG_CNCS_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "EXCG_CNCS_TM", nRow);		//거래소체결시각
			strORDR_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_TM", nRow);		//주문시각
			strCNCS_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_TM", nRow);		//체결시각
			strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CRRY_CD", nRow);		//통화코드
			strPRC_DCPN_BLW_LNG = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "PRC_DCPN_BLW_LNG", nRow);		//가격소수점이하길이
			strTRDE_PRC_DFRN_CTNS = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "TRDE_PRC_DFRN_CTNS", nRow);		//매매가격차이내용

			strFDM_UNQ_NO_PRDT_CD.Trim();		//딜링하우스고유번호상품코드
			strCANO.Trim();		//종합계좌번호
			strCTNO.Trim();		//종합계좌대체번호
			strODRV_ODNO.Trim();		//해외파생주문번호
			strFDM_UNQ_NO.Trim();		//딜링하우스고유번호
			strPRDT_CD.Trim();		//상품코드
			strODRV_OR_ODNO.Trim();		//해외파생원주문번호
			strODRV_MO_ODNO.Trim();		//해외파생모주문번호
			strORDR_GRUP_NO.Trim();		//주문그룹번호
			strORDR_DT.Trim();		//주문일자
			strAPNO.Trim();		//계좌상품번호
			strCUST_NM.Trim();		//고객명
			strODRV_SELL_BUY_DCD.Trim();		//해외파생매도매수구분코드
			NumericString(strODRV_ORDR_PRC);		//해외파생주문가격
			NumericString(strORDR_QNT);		//주문수량
			NumericString(strRVSE_QNT);		//정정수량
			NumericString(strCNCL_QNT);		//취소수량
			NumericString(strCNCS_QNT);		//체결수량
			NumericString(strORDR_RMN_QNT);		//주문잔여수량
			NumericString(strCTRT_UN_AMT);		//계약단위금액
			NumericString(strFX_ORDR_TOT_AMT);		//FX주문총금액
			NumericString(strFX_RMN_TOT_AMT);		//FX잔여총금액
			strPRC_CND_DCD.Trim();		//가격조건구분코드
			strCNCS_CND_DCD.Trim();		//체결조건구분코드
			strSQ1_STLS_YN.Trim();		//1차스탑로스여부
			strSQ1_APMPR_YN.Trim();		//1차지정가여부
			NumericString(strSQ1_STLS_PRC);		//1차스탑로스가격
			NumericString(strSQ1_APPN_PRC);		//1차지정가격
			NumericString(strSQ1_CHAS_STLS_PRC);		//1차추적손절매가격
			strSQ2_STLS_YN.Trim();		//2차스탑로스여부
			strSQ2_APMPR_YN.Trim();		//2차지정가여부
			strSQ2_STLS_PRC.Trim();		//2차스탑로스가격
			strSQ2_APPN_PRC.Trim();		//2차지정가격
			NumericString(strSQ2_CHAS_STLS_PRC);		//2차추적손절매가격
			NumericString(strAVR_CNCS_PRC);		//평균체결가격
			NumericString(strCNCS_RT);		//체결율
			NumericString(strODRV_NOW_PRC);		//해외파생현재가격
			strCOMM_MDIA_DCD.Trim();		//통신매체구분코드
			strODRV_ORDR_TP_DCD.Trim();		//해외파생주문유형구분코드
			strORDR_STTS_DCD.Trim();		//주문상태구분코드
			strFCM_ODNO.Trim();		//FCM주문번호
			strUSR_ID.Trim();		//사용자ID
			strATHZ_IP_ADDR.Trim();		//공인IP주소
			strEXCG_ACPT_TM.Trim();		//거래소접수시각
			strEXCG_CNCS_TM.Trim();		//거래소체결시각
			strORDR_TM.Trim();		//주문시각
			strCNCS_TM.Trim();		//체결시각
			strCRRY_CD.Trim();		//통화코드
			strPRC_DCPN_BLW_LNG.Trim();		//가격소수점이하길이
			strTRDE_PRC_DFRN_CTNS.Trim();		//매매가격차이내용

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listNonExec.InsertItem(&lvItem);

			m_listNonExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strFDM_UNQ_NO_PRDT_CD);		//딜링하우스고유번호상품코드
			m_listNonExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strCANO);		//종합계좌번호
			m_listNonExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strCTNO);		//종합계좌대체번호
			m_listNonExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strODRV_ODNO);		//해외파생주문번호
			m_listNonExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strFDM_UNQ_NO);		//딜링하우스고유번호
			m_listNonExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strPRDT_CD);		//상품코드
			m_listNonExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strODRV_OR_ODNO);		//해외파생원주문번호
			m_listNonExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strODRV_MO_ODNO);		//해외파생모주문번호
			m_listNonExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strORDR_GRUP_NO);		//주문그룹번호
			m_listNonExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strORDR_DT);		//주문일자
			m_listNonExec.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strAPNO);		//계좌상품번호
			m_listNonExec.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strCUST_NM);		//고객명
			m_listNonExec.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드
			m_listNonExec.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strODRV_ORDR_PRC);		//해외파생주문가격
			m_listNonExec.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strORDR_QNT);		//주문수량
			m_listNonExec.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strRVSE_QNT);		//정정수량
			m_listNonExec.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strCNCL_QNT);		//취소수량
			m_listNonExec.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strCNCS_QNT);		//체결수량
			m_listNonExec.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strORDR_RMN_QNT);		//주문잔여수량
			m_listNonExec.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strCTRT_UN_AMT);		//계약단위금액
			m_listNonExec.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strFX_ORDR_TOT_AMT);		//FX주문총금액
			m_listNonExec.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strFX_RMN_TOT_AMT);		//FX잔여총금액
			m_listNonExec.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strPRC_CND_DCD);		//가격조건구분코드
			m_listNonExec.SetItemText(nListIndex, 23, (LPTSTR)(LPCTSTR)strCNCS_CND_DCD);		//체결조건구분코드
			m_listNonExec.SetItemText(nListIndex, 24, (LPTSTR)(LPCTSTR)strSQ1_STLS_YN);		//1차스탑로스여부
			m_listNonExec.SetItemText(nListIndex, 25, (LPTSTR)(LPCTSTR)strSQ1_APMPR_YN);		//1차지정가여부
			m_listNonExec.SetItemText(nListIndex, 26, (LPTSTR)(LPCTSTR)strSQ1_STLS_PRC);		//1차스탑로스가격
			m_listNonExec.SetItemText(nListIndex, 27, (LPTSTR)(LPCTSTR)strSQ1_APPN_PRC);		//1차지정가격
			m_listNonExec.SetItemText(nListIndex, 28, (LPTSTR)(LPCTSTR)strSQ1_CHAS_STLS_PRC);		//1차추적손절매가격
			m_listNonExec.SetItemText(nListIndex, 29, (LPTSTR)(LPCTSTR)strSQ2_STLS_YN);		//2차스탑로스여부
			m_listNonExec.SetItemText(nListIndex, 30, (LPTSTR)(LPCTSTR)strSQ2_APMPR_YN);		//2차지정가여부
			m_listNonExec.SetItemText(nListIndex, 31, (LPTSTR)(LPCTSTR)strSQ2_STLS_PRC);		//2차스탑로스가격
			m_listNonExec.SetItemText(nListIndex, 32, (LPTSTR)(LPCTSTR)strSQ2_APPN_PRC);		//2차지정가격
			m_listNonExec.SetItemText(nListIndex, 33, (LPTSTR)(LPCTSTR)strSQ2_CHAS_STLS_PRC);		//2차추적손절매가격
			m_listNonExec.SetItemText(nListIndex, 34, (LPTSTR)(LPCTSTR)strAVR_CNCS_PRC);		//평균체결가격
			m_listNonExec.SetItemText(nListIndex, 35, (LPTSTR)(LPCTSTR)strCNCS_RT);		//체결율
			m_listNonExec.SetItemText(nListIndex, 36, (LPTSTR)(LPCTSTR)strODRV_NOW_PRC);		//해외파생현재가격
			m_listNonExec.SetItemText(nListIndex, 37, (LPTSTR)(LPCTSTR)strCOMM_MDIA_DCD);		//통신매체구분코드
			m_listNonExec.SetItemText(nListIndex, 38, (LPTSTR)(LPCTSTR)strODRV_ORDR_TP_DCD);		//해외파생주문유형구분코드
			m_listNonExec.SetItemText(nListIndex, 39, (LPTSTR)(LPCTSTR)strORDR_STTS_DCD);		//주문상태구분코드
			m_listNonExec.SetItemText(nListIndex, 40, (LPTSTR)(LPCTSTR)strFCM_ODNO);		//FCM주문번호
			m_listNonExec.SetItemText(nListIndex, 41, (LPTSTR)(LPCTSTR)strUSR_ID);		//사용자ID
			m_listNonExec.SetItemText(nListIndex, 42, (LPTSTR)(LPCTSTR)strATHZ_IP_ADDR);		//공인IP주소
			m_listNonExec.SetItemText(nListIndex, 43, (LPTSTR)(LPCTSTR)strEXCG_ACPT_TM);		//거래소접수시각
			m_listNonExec.SetItemText(nListIndex, 44, (LPTSTR)(LPCTSTR)strEXCG_CNCS_TM);		//거래소체결시각
			m_listNonExec.SetItemText(nListIndex, 45, (LPTSTR)(LPCTSTR)strORDR_TM);		//주문시각
			m_listNonExec.SetItemText(nListIndex, 46, (LPTSTR)(LPCTSTR)strCNCS_TM);		//체결시각
			m_listNonExec.SetItemText(nListIndex, 47, (LPTSTR)(LPCTSTR)strCRRY_CD);		//통화코드
			m_listNonExec.SetItemText(nListIndex, 48, (LPTSTR)(LPCTSTR)strPRC_DCPN_BLW_LNG);		//가격소수점이하길이
			m_listNonExec.SetItemText(nListIndex, 49, (LPTSTR)(LPCTSTR)strTRDE_PRC_DFRN_CTNS);		//매매가격차이내용

			nListIndex++;

		}//End of for

		m_listNonExec.EnsureVisible(nViewScrollPos, FALSE);
		m_listNonExec.SetRedraw(TRUE);

		/*--------------------------------------
		연속조회키를 저장해 놓는다.
		---------------------------------------*/
		m_strListNonExecNextRqKey = strPreNextContext;

		/*--------------------------------------
		연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_NON_EXEC_LIST_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_NON_EXEC_LIST_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdNonExecList = 0;	//주문체결조회 Rq ID

	}
	//주문체결내역 조회
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
		다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		붙여 삽입한다.
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
			strFDM_UNQ_NO_PRDT_CD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "FDM_UNQ_NO_PRDT_CD", nRow);		//딜링하우스고유번호상품코드
			strCANO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CANO", nRow);		//종합계좌번호
			strCTNO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CTNO", nRow);		//종합계좌대체번호
			strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_ODNO", nRow);		//해외파생주문번호
			strFDM_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "FDM_UNQ_NO", nRow);		//딜링하우스고유번호
			strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "PRDT_CD", nRow);		//상품코드
			strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_OR_ODNO", nRow);		//해외파생원주문번호
			strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_MO_ODNO", nRow);		//해외파생모주문번호
			strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ORDR_GRUP_NO", nRow);		//주문그룹번호
			strORDR_DT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ORDR_DT", nRow);		//주문일자
			strAPNO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "APNO", nRow);		//계좌상품번호
			strCUST_NM = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CUST_NM", nRow);		//고객명
			strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//해외파생매도매수구분코드
			strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_ORDR_PRC", nRow);		//해외파생주문가격
			strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ORDR_QNT", nRow);		//주문수량
			strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "RVSE_QNT", nRow);		//정정수량
			strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CNCL_QNT", nRow);		//취소수량
			strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CNCS_QNT", nRow);		//체결수량
			strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ORDR_RMN_QNT", nRow);		//주문잔여수량
			strCTRT_UN_AMT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CTRT_UN_AMT", nRow);		//계약단위금액
			strFX_ORDR_TOT_AMT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "FX_ORDR_TOT_AMT", nRow);		//FX주문총금액
			strFX_RMN_TOT_AMT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "FX_RMN_TOT_AMT", nRow);		//FX잔여총금액
			strPRC_CND_DCD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "PRC_CND_DCD", nRow);		//가격조건구분코드
			strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CNCS_CND_DCD", nRow);		//체결조건구분코드
			strSQ1_STLS_YN = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ1_STLS_YN", nRow);		//1차스탑로스여부
			strSQ1_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ1_APMPR_YN", nRow);		//1차지정가여부
			strSQ1_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ1_STLS_PRC", nRow);		//1차스탑로스가격
			strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ1_APPN_PRC", nRow);		//1차지정가격
			strSQ1_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ1_CHAS_STLS_PRC", nRow);		//1차추적손절매가격
			strSQ2_STLS_YN = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ2_STLS_YN", nRow);		//2차스탑로스여부
			strSQ2_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ2_APMPR_YN", nRow);		//2차지정가여부
			strSQ2_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ2_STLS_PRC", nRow);		//2차스탑로스가격
			strSQ2_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ2_APPN_PRC", nRow);		//2차지정가격
			strSQ2_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "SQ2_CHAS_STLS_PRC", nRow);		//2차추적손절매가격
			strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "AVR_CNCS_PRC", nRow);		//평균체결가격
			strCNCS_RT = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CNCS_RT", nRow);		//체결율
			strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_NOW_PRC", nRow);		//해외파생현재가격
			strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "COMM_MDIA_DCD", nRow);		//통신매체구분코드
			strODRV_ORDR_TP_DCD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ODRV_ORDR_TP_DCD", nRow);		//해외파생주문유형구분코드
			strORDR_STTS_DCD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ORDR_STTS_DCD", nRow);		//주문상태구분코드
			strFCM_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "FCM_ODNO", nRow);		//FCM주문번호
			strUSR_ID = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "USR_ID", nRow);		//사용자ID
			strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ATHZ_IP_ADDR", nRow);		//공인IP주소
			strEXCG_ACPT_TM = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "EXCG_ACPT_TM", nRow);		//거래소접수시각
			strEXCG_CNCS_TM = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "EXCG_CNCS_TM", nRow);		//거래소체결시각
			strORDR_TM = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "ORDR_TM", nRow);		//주문시각
			strCNCS_TM = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CNCS_TM", nRow);		//체결시각
			strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "CRRY_CD", nRow);		//통화코드
			strPRC_DCPN_BLW_LNG = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "PRC_DCPN_BLW_LNG", nRow);		//가격소수점이하길이
			strTRDE_PRC_DFRN_CTNS = m_CommAgent.GetTranOutputData("OTS5913Q52", "OTS5913Q52_out_sub01", "TRDE_PRC_DFRN_CTNS", nRow);		//매매가격차이내용

			strFDM_UNQ_NO_PRDT_CD.Trim();		//딜링하우스고유번호상품코드
			strCANO.Trim();		//종합계좌번호
			strCTNO.Trim();		//종합계좌대체번호
			strODRV_ODNO.Trim();		//해외파생주문번호
			strFDM_UNQ_NO.Trim();		//딜링하우스고유번호
			strPRDT_CD.Trim();		//상품코드
			strODRV_OR_ODNO.Trim();		//해외파생원주문번호
			strODRV_MO_ODNO.Trim();		//해외파생모주문번호
			strORDR_GRUP_NO.Trim();		//주문그룹번호
			strORDR_DT.Trim();		//주문일자
			strAPNO.Trim();		//계좌상품번호
			strCUST_NM.Trim();		//고객명
			strODRV_SELL_BUY_DCD.Trim();		//해외파생매도매수구분코드
			NumericString(strODRV_ORDR_PRC);		//해외파생주문가격
			NumericString(strORDR_QNT);		//주문수량
			NumericString(strRVSE_QNT);		//정정수량
			NumericString(strCNCL_QNT);		//취소수량
			NumericString(strCNCS_QNT);		//체결수량
			NumericString(strORDR_RMN_QNT);		//주문잔여수량
			NumericString(strCTRT_UN_AMT);		//계약단위금액
			NumericString(strFX_ORDR_TOT_AMT);		//FX주문총금액
			NumericString(strFX_RMN_TOT_AMT);		//FX잔여총금액
			strPRC_CND_DCD.Trim();		//가격조건구분코드
			strCNCS_CND_DCD.Trim();		//체결조건구분코드
			strSQ1_STLS_YN.Trim();		//1차스탑로스여부
			strSQ1_APMPR_YN.Trim();		//1차지정가여부
			NumericString(strSQ1_STLS_PRC);		//1차스탑로스가격
			NumericString(strSQ1_APPN_PRC);		//1차지정가격
			NumericString(strSQ1_CHAS_STLS_PRC);		//1차추적손절매가격
			strSQ2_STLS_YN.Trim();		//2차스탑로스여부
			strSQ2_APMPR_YN.Trim();		//2차지정가여부
			strSQ2_STLS_PRC.Trim();		//2차스탑로스가격
			strSQ2_APPN_PRC.Trim();		//2차지정가격
			NumericString(strSQ2_CHAS_STLS_PRC);		//2차추적손절매가격
			NumericString(strAVR_CNCS_PRC);		//평균체결가격
			NumericString(strCNCS_RT);		//체결율
			NumericString(strODRV_NOW_PRC);		//해외파생현재가격
			strCOMM_MDIA_DCD.Trim();		//통신매체구분코드
			strODRV_ORDR_TP_DCD.Trim();		//해외파생주문유형구분코드
			strORDR_STTS_DCD.Trim();		//주문상태구분코드
			strFCM_ODNO.Trim();		//FCM주문번호
			strUSR_ID.Trim();		//사용자ID
			strATHZ_IP_ADDR.Trim();		//공인IP주소
			strEXCG_ACPT_TM.Trim();		//거래소접수시각
			strEXCG_CNCS_TM.Trim();		//거래소체결시각
			strORDR_TM.Trim();		//주문시각
			strCNCS_TM.Trim();		//체결시각
			strCRRY_CD.Trim();		//통화코드
			strPRC_DCPN_BLW_LNG.Trim();		//가격소수점이하길이
			strTRDE_PRC_DFRN_CTNS.Trim();		//매매가격차이내용

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listExec.InsertItem(&lvItem);

			m_listExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strFDM_UNQ_NO_PRDT_CD);		//딜링하우스고유번호상품코드
			m_listExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strCANO);		//종합계좌번호
			m_listExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strCTNO);		//종합계좌대체번호
			m_listExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strODRV_ODNO);		//해외파생주문번호
			m_listExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strFDM_UNQ_NO);		//딜링하우스고유번호
			m_listExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strPRDT_CD);		//상품코드
			m_listExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strODRV_OR_ODNO);		//해외파생원주문번호
			m_listExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strODRV_MO_ODNO);		//해외파생모주문번호
			m_listExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strORDR_GRUP_NO);		//주문그룹번호
			m_listExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strORDR_DT);		//주문일자
			m_listExec.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strAPNO);		//계좌상품번호
			m_listExec.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strCUST_NM);		//고객명
			m_listExec.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드
			m_listExec.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strODRV_ORDR_PRC);		//해외파생주문가격
			m_listExec.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strORDR_QNT);		//주문수량
			m_listExec.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strRVSE_QNT);		//정정수량
			m_listExec.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strCNCL_QNT);		//취소수량
			m_listExec.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strCNCS_QNT);		//체결수량
			m_listExec.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strORDR_RMN_QNT);		//주문잔여수량
			m_listExec.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strCTRT_UN_AMT);		//계약단위금액
			m_listExec.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strFX_ORDR_TOT_AMT);		//FX주문총금액
			m_listExec.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strFX_RMN_TOT_AMT);		//FX잔여총금액
			m_listExec.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strPRC_CND_DCD);		//가격조건구분코드
			m_listExec.SetItemText(nListIndex, 23, (LPTSTR)(LPCTSTR)strCNCS_CND_DCD);		//체결조건구분코드
			m_listExec.SetItemText(nListIndex, 24, (LPTSTR)(LPCTSTR)strSQ1_STLS_YN);		//1차스탑로스여부
			m_listExec.SetItemText(nListIndex, 25, (LPTSTR)(LPCTSTR)strSQ1_APMPR_YN);		//1차지정가여부
			m_listExec.SetItemText(nListIndex, 26, (LPTSTR)(LPCTSTR)strSQ1_STLS_PRC);		//1차스탑로스가격
			m_listExec.SetItemText(nListIndex, 27, (LPTSTR)(LPCTSTR)strSQ1_APPN_PRC);		//1차지정가격
			m_listExec.SetItemText(nListIndex, 28, (LPTSTR)(LPCTSTR)strSQ1_CHAS_STLS_PRC);		//1차추적손절매가격
			m_listExec.SetItemText(nListIndex, 29, (LPTSTR)(LPCTSTR)strSQ2_STLS_YN);		//2차스탑로스여부
			m_listExec.SetItemText(nListIndex, 30, (LPTSTR)(LPCTSTR)strSQ2_APMPR_YN);		//2차지정가여부
			m_listExec.SetItemText(nListIndex, 31, (LPTSTR)(LPCTSTR)strSQ2_STLS_PRC);		//2차스탑로스가격
			m_listExec.SetItemText(nListIndex, 32, (LPTSTR)(LPCTSTR)strSQ2_APPN_PRC);		//2차지정가격
			m_listExec.SetItemText(nListIndex, 33, (LPTSTR)(LPCTSTR)strSQ2_CHAS_STLS_PRC);		//2차추적손절매가격
			m_listExec.SetItemText(nListIndex, 34, (LPTSTR)(LPCTSTR)strAVR_CNCS_PRC);		//평균체결가격
			m_listExec.SetItemText(nListIndex, 35, (LPTSTR)(LPCTSTR)strCNCS_RT);		//체결율
			m_listExec.SetItemText(nListIndex, 36, (LPTSTR)(LPCTSTR)strODRV_NOW_PRC);		//해외파생현재가격
			m_listExec.SetItemText(nListIndex, 37, (LPTSTR)(LPCTSTR)strCOMM_MDIA_DCD);		//통신매체구분코드
			m_listExec.SetItemText(nListIndex, 38, (LPTSTR)(LPCTSTR)strODRV_ORDR_TP_DCD);		//해외파생주문유형구분코드
			m_listExec.SetItemText(nListIndex, 39, (LPTSTR)(LPCTSTR)strORDR_STTS_DCD);		//주문상태구분코드
			m_listExec.SetItemText(nListIndex, 40, (LPTSTR)(LPCTSTR)strFCM_ODNO);		//FCM주문번호
			m_listExec.SetItemText(nListIndex, 41, (LPTSTR)(LPCTSTR)strUSR_ID);		//사용자ID
			m_listExec.SetItemText(nListIndex, 42, (LPTSTR)(LPCTSTR)strATHZ_IP_ADDR);		//공인IP주소
			m_listExec.SetItemText(nListIndex, 43, (LPTSTR)(LPCTSTR)strEXCG_ACPT_TM);		//거래소접수시각
			m_listExec.SetItemText(nListIndex, 44, (LPTSTR)(LPCTSTR)strEXCG_CNCS_TM);		//거래소체결시각
			m_listExec.SetItemText(nListIndex, 45, (LPTSTR)(LPCTSTR)strORDR_TM);		//주문시각
			m_listExec.SetItemText(nListIndex, 46, (LPTSTR)(LPCTSTR)strCNCS_TM);		//체결시각
			m_listExec.SetItemText(nListIndex, 47, (LPTSTR)(LPCTSTR)strCRRY_CD);		//통화코드
			m_listExec.SetItemText(nListIndex, 48, (LPTSTR)(LPCTSTR)strPRC_DCPN_BLW_LNG);		//가격소수점이하길이
			m_listExec.SetItemText(nListIndex, 49, (LPTSTR)(LPCTSTR)strTRDE_PRC_DFRN_CTNS);		//매매가격차이내용
		}//End of for

		m_listExec.EnsureVisible(nViewScrollPos, FALSE);
		m_listExec.SetRedraw(TRUE);
		
		/*--------------------------------------
		연속조회키를 저장해 놓는다.
		---------------------------------------*/
		m_strListExecNextRqKey = strPreNextContext;

		/*--------------------------------------
		연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_EXEC_LIST_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_EXEC_LIST_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdExecList = 0;	//주문체결조회 Rq ID

	}
	//계좌목록 조회
	else if (m_nRqIdAccNoList == nRequestId)
	{
		CString strfunc, strusid, strerrc, stremsg, strnrec, straccn, strsub_accn;
		CString stracnm, strachk, strpwch;

		strfunc = m_CommAgent.GetTranOutputData(strTrCode, "OutRec1", "func", 0);		//기능구분코드
		strusid = m_CommAgent.GetTranOutputData(strTrCode, "OutRec1", "usid", 0);		//사용자아이디
		strerrc = m_CommAgent.GetTranOutputData(strTrCode, "OutRec1", "errc", 0);		//에러코드
		stremsg = m_CommAgent.GetTranOutputData(strTrCode, "OutRec1", "emsg", 0);		//에러메시지
		strnrec = m_CommAgent.GetTranOutputData(strTrCode, "OutRec1", "nrec", 0);		//출력건수
		
		m_listAccNo.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OutRec2");

		CString strAccNo;
		CString strPrdt;

		m_arrAccNo.RemoveAll();		//종합계좌번호
		m_arrAccAPNO.RemoveAll();	//종합계좌대체번호

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			straccn = m_CommAgent.GetTranOutputData(strTrCode, "OutRec2", "accn", nRow);		//계좌번호
			strsub_accn = m_CommAgent.GetTranOutputData(strTrCode, "OutRec2", "sub_accn", nRow);		//대체계좌번호
			stracnm = m_CommAgent.GetTranOutputData(strTrCode, "OutRec2", "acnm", nRow);		//계좌명
			strachk = m_CommAgent.GetTranOutputData(strTrCode, "OutRec2", "achk", nRow);		//계좌특성
			strpwch = m_CommAgent.GetTranOutputData(strTrCode, "OutRec2", "pwch", nRow);		//은행연계계좌여부

			straccn.Trim();
			strsub_accn.Trim();
			stracnm.Trim();
			strachk.Trim();
			strpwch.Trim();

			strAccNo = straccn.Mid(0, 8);
			strPrdt = straccn.Mid(8, 3);

			m_arrAccNo.Add(strAccNo);		//종합계좌번호
			m_arrAccAPNO.Add(strsub_accn);	//종합계좌대체번호

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
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdAccNoList = 0;	//계좌목록
	}
	//계좌목록 조회
	else if (m_nRqIdFDemoAccNoList == nRequestId)
	{
		CString strCTNO;		//종합계좌대체번호
		CString strCANO;		//종합계좌번호
		CString strAPNO;		//계좌상품번호
		CString strCUST_NM;		//고객명

		m_listAccNo.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OTS5991Q03_out_sub01");

		m_arrAccNo.RemoveAll();			//계좌목록
		m_arrAccAPNO.RemoveAll();		//종합계좌대체번호목록

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strCTNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CTNO", nRow);		//고객명
			strCANO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CANO", nRow);		//종합계좌번호
			strAPNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "APNO", nRow);		//계좌상품번호
			strCUST_NM = m_CommAgent.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CUST_NM", nRow);		//고객명

			strCTNO.Trim();
			strCANO.Trim();
			strAPNO.Trim();
			strCUST_NM.Trim();

			m_arrAccNo.Add(strCANO);		//종합계좌번호
			m_arrAccAPNO.Add(strCTNO);		//종합계좌대체번호

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
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdFDemoAccNoList = 0;	//데모계좌리스트
	}
	//예수금 조회
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
		다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		붙여 삽입한다.
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
			strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "CRRY_CD", nRow);		//통화코드
			strBFDT_CSH_BLCE_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "BFDT_CSH_BLCE_CTNS", nRow);		//전일현금잔액내용
			strODRV_IPP_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_IPP_AMT_CTNS", nRow);		//해외파생입출금액내용
			strFX_FEE_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "FX_FEE_CTNS", nRow);		//FX수수료내용
			strROVR_INTR_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ROVR_INTR_CTNS", nRow);		//롤오버이자내용
			strTHDT_DPSA_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "THDT_DPSA_CTNS", nRow);		//당일예탁금내용
			strODRV_CLR_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_CLR_AMT_CTNS", nRow);		//해외파생청산금액내용
			strUSTL_EVL_PFLS_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "USTL_EVL_PFLS_AMT_CTNS", nRow);		//미결제평가손익금액내용
			strODRV_EVL_DPST_TOT_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_EVL_DPST_TOT_AMT_CTNS", nRow);		//해외파생평가예탁총금액내용
			strODRV_CSGN_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_CSGN_WMY_CTNS", nRow);		//해외파생위탁증거금내용
			strODRV_ADIT_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_ADIT_WMY_CTNS", nRow);		//해외파생추가증거금내용
			strODRV_RCVB_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_RCVB_AMT_CTNS", nRow);		//해외파생미수금액내용
			strODRV_ORDR_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_ORDR_PSBL_AMT_CTNS", nRow);		//해외파생주문가능금액내용
			strODRV_WDRW_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_WDRW_PSBL_AMT_CTNS", nRow);		//해외파생인출가능금액내용
			strODRV_MNTN_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_MNTN_WMY_CTNS", nRow);		//해외파생유지증거금내용
			strRSK_RT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "RSK_RT_CTNS", nRow);		//위험율내용

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
		연속조회키를 저장해 놓는다.
		---------------------------------------*/
		m_strListDepositNextRqKey = strPreNextContext;

		/*--------------------------------------
		연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_DEPOSIT_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_DEPOSIT_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdDepositList = 0;	//예수금

	}//End of if
	//잔고 조회
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
		다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		붙여 삽입한다.
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
			strPST_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PST_NO", nRow);		//포지션번호
			strCTNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CTNO", nRow);		//종합계좌대체번호
			strCANO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CANO", nRow);		//종합계좌번호
			strAPNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "APNO", nRow);		//계좌상품번호
			strCNCS_DT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_DT", nRow);		//체결일자
			strMNGM_BDCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "MNGM_BDCD", nRow);		//관리부점코드
			strODRV_CSGN_SLF_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CSGN_SLF_DCD", nRow);		//해외파생위탁자기구분코드
			strFDM_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "FDM_UNQ_NO", nRow);		//딜링하우스고유번호
			strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PRDT_CD", nRow);		//상품코드
			strNMPR_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "NMPR_UNQ_NO", nRow);		//호가고유번호
			strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//해외파생매도매수구분코드
			strODRV_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CNCS_PRC", nRow);		//해외파생체결가격
			strFRS_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "FRS_CNCS_QNT", nRow);		//최초체결수량
			strCLR_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CLR_QNT", nRow);		//청산수량
			strCNCS_CNCL_TR_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_CNCL_TR_QNT", nRow);		//체결취소거래수량
			strUSTL_CTRC_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_QNT", nRow);		//미결제약정수량
			strUSTL_CTRC_AMT2 = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_AMT2", nRow);		//미결제약정금액2
			strUSTL_CTRC_AMT3 = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_AMT3", nRow);		//미결제약정금액3
			strCNCS_PIP_VALU_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_PIP_VALU_AMT", nRow);		//체결PIP가치금액
			strODRV_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CTRC_AMT", nRow);		//해외파생약정금액
			strUSTL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_AMT", nRow);		//미결제약정금액
			strCRSS_EXRT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CRSS_EXRT", nRow);		//교차환율
			strODRV_EXCAL_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_EXCAL_PRC", nRow);		//해외파생정산가격
			strODRV_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_EVL_PFLS_AMT", nRow);		//해외파생평가손익금액
			strPIP_VALU_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PIP_VALU_AMT", nRow);		//PIP가치금액
			strTRSL_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "TRSL_EVL_PFLS_AMT", nRow);		//환산평가손익금액
			strEXCAL_CRSS_EXRT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "EXCAL_CRSS_EXRT", nRow);		//정산교차환율
			strONL_TR_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ONL_TR_YN", nRow);		//온라인거래여부
			strODRV_CNCS_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CNCS_NO", nRow);		//해외파생체결번호
			strHOLD_PST_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "HOLD_PST_YN", nRow);		//보유포지션여부
			strUSE_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USE_YN", nRow);		//사용여부
			strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_ODNO", nRow);		//해외파생주문번호
			strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_OR_ODNO", nRow);		//해외파생원주문번호
			strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_MO_ODNO", nRow);		//해외파생모주문번호
			strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_GRUP_NO", nRow);		//주문그룹번호
			strORDR_DT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_DT", nRow);		//주문일자
			strCUST_NM = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CUST_NM", nRow);		//고객명
			strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_ORDR_PRC", nRow);		//해외파생주문가격
			strMKT_PRC_APLY_STUP_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "MKT_PRC_APLY_STUP_AMT", nRow);		//시장가격적용설정금액
			strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_QNT", nRow);		//주문수량
			strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "RVSE_QNT", nRow);		//정정수량
			strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCL_QNT", nRow);		//취소수량
			strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_QNT", nRow);		//체결수량
			strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_RMN_QNT", nRow);		//주문잔여수량
			strPRC_CND_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PRC_CND_DCD", nRow);		//가격조건구분코드
			strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_CND_DCD", nRow);		//체결조건구분코드
			strSQ1_STLS_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_STLS_YN", nRow);		//1차스탑로스여부
			strSQ1_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_APMPR_YN", nRow);		//1차지정가여부
			strSQ1_DVSN_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_DVSN_YN", nRow);		//1차구분여부
			strSQ1_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_STLS_PRC", nRow);		//1차스탑로스가격
			strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_APPN_PRC", nRow);		//1차지정가격
			strSQ1_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_CHAS_STLS_PRC", nRow);		//1차추적손절매가격
			strCTRT_UN_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CTRT_UN_AMT", nRow);		//계약단위금액
			strORDR_DRCN_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_DRCN_DCD", nRow);		//주문방향구분코드
			strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "AVR_CNCS_PRC", nRow);		//평균체결가격
			strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_NOW_PRC", nRow);		//해외파생현재가격
			strPRDT_CD2 = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PRDT_CD2", nRow);		//상품코드2

			strPST_NO.Trim();		//포지션번호
			strCTNO.Trim();		//종합계좌대체번호
			strCANO.Trim();		//종합계좌번호
			strAPNO.Trim();		//계좌상품번호
			strCNCS_DT.Trim();		//체결일자
			strMNGM_BDCD.Trim();		//관리부점코드
			strODRV_CSGN_SLF_DCD.Trim();		//해외파생위탁자기구분코드
			strFDM_UNQ_NO.Trim();		//딜링하우스고유번호
			strPRDT_CD.Trim();		//상품코드
			strNMPR_UNQ_NO.Trim();		//호가고유번호
			strODRV_SELL_BUY_DCD.Trim();		//해외파생매도매수구분코드
			NumericString(strODRV_CNCS_PRC);		//해외파생체결가격
			NumericString(strFRS_CNCS_QNT);		//최초체결수량
			NumericString(strCLR_QNT);		//청산수량
			NumericString(strCNCS_CNCL_TR_QNT);		//체결취소거래수량
			NumericString(strUSTL_CTRC_QNT);		//미결제약정수량
			NumericString(strUSTL_CTRC_AMT2);		//미결제약정금액2
			NumericString(strUSTL_CTRC_AMT3);		//미결제약정금액3
			NumericString(strCNCS_PIP_VALU_AMT);		//체결PIP가치금액
			NumericString(strODRV_CTRC_AMT);		//해외파생약정금액
			NumericString(strUSTL_CTRC_AMT);		//미결제약정금액
			NumericString(strCRSS_EXRT);		//교차환율
			NumericString(strODRV_EXCAL_PRC);		//해외파생정산가격
			NumericString(strODRV_EVL_PFLS_AMT);		//해외파생평가손익금액
			NumericString(strPIP_VALU_AMT);		//PIP가치금액
			NumericString(strTRSL_EVL_PFLS_AMT);		//환산평가손익금액
			NumericString(strEXCAL_CRSS_EXRT);		//정산교차환율
			strONL_TR_YN.Trim();		//온라인거래여부
			strODRV_CNCS_NO.Trim();		//해외파생체결번호
			strHOLD_PST_YN.Trim();		//보유포지션여부
			strUSE_YN.Trim();		//사용여부
			strODRV_ODNO.Trim();		//해외파생주문번호
			strODRV_OR_ODNO.Trim();		//해외파생원주문번호
			strODRV_MO_ODNO.Trim();		//해외파생모주문번호
			strORDR_GRUP_NO.Trim();		//주문그룹번호
			strORDR_DT.Trim();		//주문일자
			strCUST_NM.Trim();		//고객명
			NumericString(strODRV_ORDR_PRC);		//해외파생주문가격
			NumericString(strMKT_PRC_APLY_STUP_AMT);		//시장가격적용설정금액
			NumericString(strORDR_QNT);		//주문수량
			NumericString(strRVSE_QNT);		//정정수량
			NumericString(strCNCL_QNT);		//취소수량
			NumericString(strCNCS_QNT);		//체결수량
			NumericString(strORDR_RMN_QNT);		//주문잔여수량
			strPRC_CND_DCD.Trim();		//가격조건구분코드
			strCNCS_CND_DCD.Trim();		//체결조건구분코드
			strSQ1_STLS_YN.Trim();		//1차스탑로스여부
			strSQ1_APMPR_YN.Trim();		//1차지정가여부
			strSQ1_DVSN_YN.Trim();		//1차구분여부
			NumericString(strSQ1_STLS_PRC);		//1차스탑로스가격
			NumericString(strSQ1_APPN_PRC);		//1차지정가격
			NumericString(strSQ1_CHAS_STLS_PRC);		//1차추적손절매가격
			NumericString(strCTRT_UN_AMT);		//계약단위금액
			strORDR_DRCN_DCD.Trim();		//주문방향구분코드
			NumericString(strAVR_CNCS_PRC);		//평균체결가격
			NumericString(strODRV_NOW_PRC);		//해외파생현재가격
			strPRDT_CD2.Trim();		//상품코드2

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listBalance.InsertItem(&lvItem);

			m_listBalance.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strPST_NO);		//포지션번호
			m_listBalance.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strCTNO);		//종합계좌대체번호
			m_listBalance.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strCANO);		//종합계좌번호
			m_listBalance.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strAPNO);		//계좌상품번호
			m_listBalance.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strCNCS_DT);		//체결일자
			m_listBalance.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strMNGM_BDCD);		//관리부점코드
			m_listBalance.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strODRV_CSGN_SLF_DCD);		//해외파생위탁자기구분코드
			m_listBalance.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strFDM_UNQ_NO);		//딜링하우스고유번호
			m_listBalance.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strPRDT_CD);		//상품코드
			m_listBalance.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strNMPR_UNQ_NO);		//호가고유번호
			m_listBalance.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드
			m_listBalance.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strODRV_CNCS_PRC);		//해외파생체결가격
			m_listBalance.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strFRS_CNCS_QNT);		//최초체결수량
			m_listBalance.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strCLR_QNT);		//청산수량
			m_listBalance.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strCNCS_CNCL_TR_QNT);		//체결취소거래수량
			m_listBalance.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strUSTL_CTRC_QNT);		//미결제약정수량
			m_listBalance.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strUSTL_CTRC_AMT2);		//미결제약정금액2
			m_listBalance.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strUSTL_CTRC_AMT3);		//미결제약정금액3
			m_listBalance.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strCNCS_PIP_VALU_AMT);		//체결PIP가치금액
			m_listBalance.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strODRV_CTRC_AMT);		//해외파생약정금액
			m_listBalance.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strUSTL_CTRC_AMT);		//미결제약정금액
			m_listBalance.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strCRSS_EXRT);		//교차환율
			m_listBalance.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strODRV_EXCAL_PRC);		//해외파생정산가격
			m_listBalance.SetItemText(nListIndex, 23, (LPTSTR)(LPCTSTR)strODRV_EVL_PFLS_AMT);		//해외파생평가손익금액
			m_listBalance.SetItemText(nListIndex, 24, (LPTSTR)(LPCTSTR)strPIP_VALU_AMT);		//PIP가치금액
			m_listBalance.SetItemText(nListIndex, 25, (LPTSTR)(LPCTSTR)strTRSL_EVL_PFLS_AMT);		//환산평가손익금액
			m_listBalance.SetItemText(nListIndex, 26, (LPTSTR)(LPCTSTR)strEXCAL_CRSS_EXRT);		//정산교차환율
			m_listBalance.SetItemText(nListIndex, 27, (LPTSTR)(LPCTSTR)strONL_TR_YN);		//온라인거래여부
			m_listBalance.SetItemText(nListIndex, 28, (LPTSTR)(LPCTSTR)strODRV_CNCS_NO);		//해외파생체결번호
			m_listBalance.SetItemText(nListIndex, 29, (LPTSTR)(LPCTSTR)strHOLD_PST_YN);		//보유포지션여부
			m_listBalance.SetItemText(nListIndex, 30, (LPTSTR)(LPCTSTR)strUSE_YN);			//사용여부
			m_listBalance.SetItemText(nListIndex, 31, (LPTSTR)(LPCTSTR)strODRV_ODNO);		//해외파생주문번호
			m_listBalance.SetItemText(nListIndex, 32, (LPTSTR)(LPCTSTR)strODRV_OR_ODNO);		//해외파생원주문번호
			m_listBalance.SetItemText(nListIndex, 33, (LPTSTR)(LPCTSTR)strODRV_MO_ODNO);		//해외파생모주문번호
			m_listBalance.SetItemText(nListIndex, 34, (LPTSTR)(LPCTSTR)strORDR_GRUP_NO);		//주문그룹번호
			m_listBalance.SetItemText(nListIndex, 35, (LPTSTR)(LPCTSTR)strORDR_DT);				//주문일자
			m_listBalance.SetItemText(nListIndex, 36, (LPTSTR)(LPCTSTR)strCUST_NM);				//고객명
			m_listBalance.SetItemText(nListIndex, 37, (LPTSTR)(LPCTSTR)strODRV_ORDR_PRC);		//해외파생주문가격
			m_listBalance.SetItemText(nListIndex, 38, (LPTSTR)(LPCTSTR)strMKT_PRC_APLY_STUP_AMT);		//시장가격적용설정금액
			m_listBalance.SetItemText(nListIndex, 39, (LPTSTR)(LPCTSTR)strORDR_QNT);			//주문수량
			m_listBalance.SetItemText(nListIndex, 40, (LPTSTR)(LPCTSTR)strRVSE_QNT);			//정정수량
			m_listBalance.SetItemText(nListIndex, 41, (LPTSTR)(LPCTSTR)strCNCL_QNT);			//취소수량
			m_listBalance.SetItemText(nListIndex, 42, (LPTSTR)(LPCTSTR)strCNCS_QNT);			//체결수량
			m_listBalance.SetItemText(nListIndex, 43, (LPTSTR)(LPCTSTR)strORDR_RMN_QNT);		//주문잔여수량
			m_listBalance.SetItemText(nListIndex, 44, (LPTSTR)(LPCTSTR)strPRC_CND_DCD);			//가격조건구분코드
			m_listBalance.SetItemText(nListIndex, 45, (LPTSTR)(LPCTSTR)strCNCS_CND_DCD);		//체결조건구분코드
			m_listBalance.SetItemText(nListIndex, 46, (LPTSTR)(LPCTSTR)strSQ1_STLS_YN);			//1차스탑로스여부
			m_listBalance.SetItemText(nListIndex, 47, (LPTSTR)(LPCTSTR)strSQ1_APMPR_YN);		//1차지정가여부
			m_listBalance.SetItemText(nListIndex, 48, (LPTSTR)(LPCTSTR)strSQ1_DVSN_YN);			//1차구분여부
			m_listBalance.SetItemText(nListIndex, 49, (LPTSTR)(LPCTSTR)strSQ1_STLS_PRC);		//1차스탑로스가격
			m_listBalance.SetItemText(nListIndex, 50, (LPTSTR)(LPCTSTR)strSQ1_APPN_PRC);		//1차지정가격
			m_listBalance.SetItemText(nListIndex, 51, (LPTSTR)(LPCTSTR)strSQ1_CHAS_STLS_PRC);	//1차추적손절매가격
			m_listBalance.SetItemText(nListIndex, 52, (LPTSTR)(LPCTSTR)strCTRT_UN_AMT);			//계약단위금액
			m_listBalance.SetItemText(nListIndex, 53, (LPTSTR)(LPCTSTR)strORDR_DRCN_DCD);		//주문방향구분코드
			m_listBalance.SetItemText(nListIndex, 54, (LPTSTR)(LPCTSTR)strAVR_CNCS_PRC);		//평균체결가격
			m_listBalance.SetItemText(nListIndex, 55, (LPTSTR)(LPCTSTR)strODRV_NOW_PRC);		//해외파생현재가격
			m_listBalance.SetItemText(nListIndex, 56, (LPTSTR)(LPCTSTR)strPRDT_CD2);			//상품코드2

			nListIndex++;
		}

		m_listBalance.EnsureVisible(0, FALSE);
		m_listBalance.SetRedraw(TRUE);

		/*--------------------------------------
		연속조회키를 저장해 놓는다.
		---------------------------------------*/
		m_strListBalanceNextRqKey = strPreNextContext;

		/*--------------------------------------
		연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_BALANCE_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_BALANCE_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdBalanceList = 0;	//주문체결조회 Rq ID

	}
	//매도주문 Request ID
	else if (m_nRqIdSellOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U31_out", "ODRV_ODNO", 0);		//해외파생주문번호
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		 반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		 ---------------------------------------*/
		m_nRqIdSellOrd = 0;
	}
	//매수주문 Request ID
	else if (m_nRqIdBuyOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U31_out", "ODRV_ODNO", 0);		//해외파생주문번호
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		 반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		 ---------------------------------------*/
		m_nRqIdBuyOrd = 0;
	}
	//정정주문 Request ID
	else if (m_nRqIdChangeOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U32_out", "ODRV_ODNO", 0);		//해외파생주문번호
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		 반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		 ---------------------------------------*/
		m_nRqIdChangeOrd = 0;
	}
	//취소주문 Request ID
	else if (m_nRqIdCancelOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U33_out", "ODRV_ODNO", 0);		//해외파생주문번호
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		 반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		 ---------------------------------------*/
		m_nRqIdCancelOrd = 0;
	}
	//청산주문 Request ID
	else if (m_nRqIdCloseOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U31_out", "ODRV_ODNO", 0);		//해외파생주문번호
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		 반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		 ---------------------------------------*/
		m_nRqIdCloseOrd = 0;
	}
	//SL정정주문 Request ID
	else if (m_nRqIdModSLOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U31_out", "ODRV_ODNO", 0);		//해외파생주문번호
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		 반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		 ---------------------------------------*/
		m_nRqIdModSLOrd = 0;
	}
	//SL취소주문 Request ID
	else if (m_nRqIdCanSLOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U33_out", "ODRV_ODNO", 0);		//해외파생주문번호
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		 반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		 ---------------------------------------*/
		m_nRqIdCanSLOrd = 0;
	}

	if (!strErrMsg.IsEmpty())
		::AfxMessageBox(strErrMsg);
}

//*******************************************************************
// Function Name : OnGetFidData
// Function      : FID 조회응답 이벤트
// Param         :	LONG nRequestId, 조회ID
//					LPCTSTR pBlock, 조회응답 데이터 블럭
//					long nBlockLength 조회응답 데이터 블럭 크기
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginOrdDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
{
	/* 주의 : OnGetFidData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
	이벤트 콜백함수 종료 후에는 유효하지 않습니다.*/

	/*	0 : 연속조회 미사용,		1 : 이전 데이터 있음,	2 : 다음 데이터 있음
		3 : 이전/다음 데이터 있음	*/
	CString strPreNext = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::PrevNextCode);

	//연속조회키
	CString strPreNextContext = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::PrevNextKey);

	//조회응답 메시지코드
	CString strMsgCode = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::MsgCode);

	//조회응답 메시지
	CString strMsg = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::Msg);

	//에러여부( "1" : 에러, "0" : 정상)
	CString strIsError = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::Error);

	CString strErrMsg = m_CommAgent.GetLastErrMsg();
	
	if (!strErrMsg.IsEmpty())
		::AfxMessageBox(strErrMsg);
}

//*******************************************************************
// Function Name : OnGetRealData
// Function      : 실시간 데이터를 수신한다.
// Param         :	LPCTSTR strRealName : 실시간 코드명
//					LPCTSTR strRealKey : 실시간 등록키
//					LPCTSTR pBlock, 조회응답 데이터 블럭
//					long nBlockLength 조회응답 데이터 블럭 크기
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginOrdDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/*	주의 : OnGetRealData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
		이벤트 콜백함수 종료 후에는 유효하지 않습니다.*/
	CString strRealMessage;

	/***************************************
	 * 미체결/체결확인
	 ****************************************/
	if (!_tcscmp(strRealName, "FX0"))
	{
		/*--------------------------------------
		 아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
		 ---------------------------------------*/
		CString strrltm_dpch_dcd = m_CommAgent.GetRealOutputData("FX0", "rltm_dpch_dcd");		//실시간통보구분코드
		CString strusr_id = m_CommAgent.GetRealOutputData("FX0", "usr_id");		//사용자ID
		CString strrltm_dpch_prcs_dcd = m_CommAgent.GetRealOutputData("FX0", "rltm_dpch_prcs_dcd");		//실시간통보처리구분코드
		CString strcano = m_CommAgent.GetRealOutputData("FX0", "cano");		//종합계좌번호
		CString strfdm_unq_no = m_CommAgent.GetRealOutputData("FX0", "fdm_unq_no");		//딜링하우스고유번호
		CString strprdt_cd = m_CommAgent.GetRealOutputData("FX0", "prdt_cd");		//상품코드
		CString strodrv_ordr_tp_dcd = m_CommAgent.GetRealOutputData("FX0", "odrv_ordr_tp_dcd");		//해외파생주문유형구분코드
		CString strordr_stts_dcd = m_CommAgent.GetRealOutputData("FX0", "ordr_stts_dcd");		//주문상태구분코드
		CString strodrv_odno = m_CommAgent.GetRealOutputData("FX0", "odrv_odno");		//해외파생주문번호
		CString strodrv_or_odno = m_CommAgent.GetRealOutputData("FX0", "odrv_or_odno");		//해외파생원주문번호
		CString strordr_dt = m_CommAgent.GetRealOutputData("FX0", "ordr_dt");		//주문일자
		CString strapno = m_CommAgent.GetRealOutputData("FX0", "apno");		//계좌상품번호
		CString strcust_nm = m_CommAgent.GetRealOutputData("FX0", "cust_nm");		//고객명
		CString strodrv_sell_buy_dcd = m_CommAgent.GetRealOutputData("FX0", "odrv_sell_buy_dcd");		//해외파생매도매수구분코드
		CString strodrv_ordr_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "odrv_ordr_prc_ctns");		//해외파생주문가격내용
		CString strordr_qnt_ctns = m_CommAgent.GetRealOutputData("FX0", "ordr_qnt_ctns");		//주문수량내용
		CString strodrv_prc_dcd = m_CommAgent.GetRealOutputData("FX0", "odrv_prc_dcd");		//해외파생가격구분코드
		CString strcncs_cnd_dcd = m_CommAgent.GetRealOutputData("FX0", "cncs_cnd_dcd");		//체결조건구분코드
		CString strodrv_ctrt_un_amt_ctns = m_CommAgent.GetRealOutputData("FX0", "odrv_ctrt_un_amt_ctns");		//해외파생계약단위금액내용
		CString strfx_ordr_tot_amt_ctns = m_CommAgent.GetRealOutputData("FX0", "fx_ordr_tot_amt_ctns");		//FX주문총금액내용
		CString strcomm_mdia_dcd = m_CommAgent.GetRealOutputData("FX0", "comm_mdia_dcd");		//통신매체구분코드
		CString strexcg_acpt_tm = m_CommAgent.GetRealOutputData("FX0", "excg_acpt_tm");		//거래소접수시각
		CString strexcg_cncs_tm = m_CommAgent.GetRealOutputData("FX0", "excg_cncs_tm");		//거래소체결시각
		CString strordr_tm = m_CommAgent.GetRealOutputData("FX0", "ordr_tm");		//주문시각
		CString strcncs_tm = m_CommAgent.GetRealOutputData("FX0", "cncs_tm");		//체결시각
		CString strcncs_dt = m_CommAgent.GetRealOutputData("FX0", "cncs_dt");		//체결일자
		CString strodrv_cncs_no = m_CommAgent.GetRealOutputData("FX0", "odrv_cncs_no");		//해외파생체결번호
		CString strcncs_qnt_ctns = m_CommAgent.GetRealOutputData("FX0", "cncs_qnt_ctns");		//체결수량내용
		CString strodrv_cncs_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "odrv_cncs_prc_ctns");		//해외파생체결가격내용
		CString strodrv_cncs_amt_ctns = m_CommAgent.GetRealOutputData("FX0", "odrv_cncs_amt_ctns");		//해외파생체결금액내용
		CString strtrsl_odrv_cncs_amt_char = m_CommAgent.GetRealOutputData("FX0", "trsl_odrv_cncs_amt_char");		//환산해외파생체결금액문자
		CString strcrry_cd = m_CommAgent.GetRealOutputData("FX0", "crry_cd");		//통화코드
		CString strsq1_stls_yn = m_CommAgent.GetRealOutputData("FX0", "sq1_stls_yn");		//1차스탑로스여부
		CString strsq1_apmpr_yn = m_CommAgent.GetRealOutputData("FX0", "sq1_apmpr_yn");		//1차지정가여부
		CString strsq1_stls_prc_char = m_CommAgent.GetRealOutputData("FX0", "sq1_stls_prc_char");		//1차스탑로스가격문자
		CString strsq1_appn_prc_char = m_CommAgent.GetRealOutputData("FX0", "sq1_appn_prc_char");		//1차지정가격문자
		CString strsq1_chas_stls_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "sq1_chas_stls_prc_ctns");		//1차추적손절매가격내용
		CString strsq2_stls_yn = m_CommAgent.GetRealOutputData("FX0", "sq2_stls_yn");		//2차스탑로스여부
		CString strsq2_apmpr_yn = m_CommAgent.GetRealOutputData("FX0", "sq2_apmpr_yn");		//2차지정가여부
		CString strsq2_stls_prc_char = m_CommAgent.GetRealOutputData("FX0", "sq2_stls_prc_char");		//2차스탑로스가격문자
		CString strsq2_appn_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "sq2_appn_prc_ctns");		//2차지정가격내용
		CString strsq2_chas_stls_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "sq2_chas_stls_prc_ctns");		//2차추적손절매가격내용
		CString strtrde_prc_dfrn_ctns = m_CommAgent.GetRealOutputData("FX0", "trde_prc_dfrn_ctns");		//매매가격차이내용
		CString strctno = m_CommAgent.GetRealOutputData("FX0", "ctno");		//종합계좌대체번호
		CString strfiller_100 = m_CommAgent.GetRealOutputData("FX0", "filler_100");		//필러_100

		strrltm_dpch_dcd.Trim();  //실시간통보구분코드
		strusr_id.Trim(); //사용자ID
		strrltm_dpch_prcs_dcd.Trim(); //실시간통보처리구분코드
		strcano.Trim(); //종합계좌번호
		strfdm_unq_no.Trim(); //딜링하우스고유번호
		strprdt_cd.Trim();  //상품코드
		strodrv_ordr_tp_dcd.Trim(); //해외파생주문유형구분코드
		strordr_stts_dcd.Trim();  //주문상태구분코드
		strodrv_odno.Trim();  //해외파생주문번호
		strodrv_or_odno.Trim(); //해외파생원주문번호
		strordr_dt.Trim();  //주문일자
		strapno.Trim(); //계좌상품번호
		strcust_nm.Trim();  //고객명
		strodrv_sell_buy_dcd.Trim();  //해외파생매도매수구분코드
		strodrv_ordr_prc_ctns.Trim(); //해외파생주문가격내용
		strordr_qnt_ctns.Trim();  //주문수량내용
		strodrv_prc_dcd.Trim(); //해외파생가격구분코드
		strcncs_cnd_dcd.Trim(); //체결조건구분코드
		strodrv_ctrt_un_amt_ctns.Trim();  //해외파생계약단위금액내용
		strfx_ordr_tot_amt_ctns.Trim(); //FX주문총금액내용
		strcomm_mdia_dcd.Trim();  //통신매체구분코드
		strexcg_acpt_tm.Trim(); //거래소접수시각
		strexcg_cncs_tm.Trim(); //거래소체결시각
		strordr_tm.Trim();  //주문시각
		strcncs_tm.Trim();  //체결시각
		strcncs_dt.Trim();  //체결일자
		strodrv_cncs_no.Trim(); //해외파생체결번호
		strcncs_qnt_ctns.Trim();  //체결수량내용
		strodrv_cncs_prc_ctns.Trim(); //해외파생체결가격내용
		strodrv_cncs_amt_ctns.Trim(); //해외파생체결금액내용
		strtrsl_odrv_cncs_amt_char.Trim();  //환산해외파생체결금액문자
		strcrry_cd.Trim();  //통화코드
		strsq1_stls_yn.Trim();  //1차스탑로스여부
		strsq1_apmpr_yn.Trim(); //1차지정가여부
		strsq1_stls_prc_char.Trim();  //1차스탑로스가격문자
		strsq1_appn_prc_char.Trim();  //1차지정가격문자
		strsq1_chas_stls_prc_ctns.Trim(); //1차추적손절매가격내용
		strsq2_stls_yn.Trim();  //2차스탑로스여부
		strsq2_apmpr_yn.Trim(); //2차지정가여부
		strsq2_stls_prc_char.Trim();  //2차스탑로스가격문자
		strsq2_appn_prc_ctns.Trim();  //2차지정가격내용
		strsq2_chas_stls_prc_ctns.Trim(); //2차추적손절매가격내용
		strtrde_prc_dfrn_ctns.Trim(); //매매가격차이내용
		strctno.Trim(); //종합계좌대체번호
		strfiller_100.Trim(); //필러_100

		/*--------------------------------------
		조회 시점에 등록한 주식 현재가 실시간키와 동일한지 비교
		---------------------------------------*/
		if (m_strLoginID == strRealKey)
		{
			strRealMessage.Format("[%s][계좌:%s][상품:%s][미체결/체결:%s]", strRealName, strcano, strprdt_cd, strordr_qnt_ctns);
		}//End of if

	}//End of if

	if (!strRealMessage.IsEmpty())
	{
		m_listReal.SetRedraw(FALSE);
		int nListRowCnt = m_listReal.GetItemCount();

		//데이터 500건이 넘으면 100건만 남기고 지운다.
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
		m_listReal.SetItemText(0, 0, (LPTSTR)(LPCTSTR)strRealMessage);			//메시지
		m_listReal.SetRedraw(TRUE);
	}
}

//*******************************************************************
// Function Name : OnAgentEventHandler
// Function      : 
// Param         : long nEventType, long nParam, LPCTSTR strParam
// Return        : void 
// Create        : 2016/11/10
// Comment       : 에이전트 이벤트 핸들러
//******************************************************************
void CFxMarginOrdDlg::OnAgentEventHandler(long nEventType, long nParam, LPCTSTR strParam)
{
	CString strEventMsg;

	switch (nEventType)
	{
		case CommEvent::Connecting:			// 연결중
		{
			strEventMsg = "[통신 이벤트] 통신 연결중";
			::AfxMessageBox(strEventMsg);
		}
		break;
		case CommEvent::Connected:			// 연결 완료
		{
			strEventMsg = "[통신 이벤트] 통신 연결 완료";
			::AfxMessageBox(strEventMsg);
		}
		break;
		case CommEvent::Closed:			// 소켓 단절 상태
		case CommEvent::Closing:			// 소켓 단절 중
		case CommEvent::ReconnectRequest:	// 재접속 요청
		{
			strEventMsg = "[통신 이벤트] 소켓이 단절되었습니다.";
			::AfxMessageBox(strEventMsg);
		}
		break;
		case CommEvent::ConnectFail:		// 소켓 연결 실패
		{
			strEventMsg = "[통신 이벤트] 통신연결 실패.";
			::AfxMessageBox(strEventMsg);
		}
		break;
		//서버 공지 메시지
		case CommEvent::NotifyMultiLogin:	// 다중접속 알림 메시지
		{
			strEventMsg.Format("[복수로그인 이벤트] %s", strParam);
			::AfxMessageBox(strEventMsg);

			//nParam 값이 1 이면 연결을 해제하라는 메시지이다.
			//실제로 해제할지는 API 사용자가 알아서 코딩한다.
			if (nParam == 1)
			{
				strEventMsg.Format("[복수로그인 이벤트] 다중 접속으로 인한 연결 해제");
				::AfxMessageBox(strEventMsg);
			}
		}
		break;
		case CommEvent::NotifyEmergency:	// 긴급공지 메시지
		{
			strEventMsg.Format("[긴급공지 이벤트] %s", strParam);
			::AfxMessageBox(strEventMsg);
		}
		break;
		case CommEvent::PopUpMsg:			// 팝업메시지
		{
			strEventMsg.Format("[팝업 이벤트] %s", strParam);
			::AfxMessageBox(strEventMsg);
		}
		break;

	}//End of switch
}


void CFxMarginOrdDlg::OnBnClickedRadioEx1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnBnClickedBtnReqNonExecList();
}


void CFxMarginOrdDlg::OnBnClickedRadioEx2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnBnClickedBtnReqNonExecList();
}


//*******************************************************************
// Function Name : OnBnClickedBtnClose
// Function      : 
// Param         : 
// Return        : void 
// Create        : 변윤식, 2017/07/31
// Comment       : 청산주문
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedBtnClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
// Create        : 변윤식, 2017/07/31
// Comment       : S&L정정
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedBtnModsl()
{
	/***************************************************
	 * ***** 주의 *****
	 * 거래소에 따라 Stop과 Limit은 동시 OCO 주문 불가
	 ***************************************************/

	//[1] Request ID생성
	m_nRqIdModSLOrd = m_CommAgent.CreateRequestID();

	//해외파생원주문번호
	CString strODRV_OR_ODNO;		//해외파생원주문번호
	CString strODRV_SELL_BUY_DCD;		//해외파생매도매수구분코드

	GetDlgItem(IDC_ORDER_NO)->GetWindowText(strODRV_OR_ODNO);
	strODRV_OR_ODNO.Trim();

	/***************************************************
	 * SL주문이 처음이면 신규주문Tr로  SL주문을 낸다.
	 * 기존 SL주문이 있으면 정정주문Tr로 SL주문을 낸다.
	 ***************************************************/
	if (strODRV_OR_ODNO.IsEmpty())
	{
		GetDlgItem(IDC_POS_SELLBUY)->GetWindowText(strODRV_SELL_BUY_DCD);
		SendSellBuyOrder(strODRV_SELL_BUY_DCD, m_nRqIdModSLOrd, _T("SLOrder"));

		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5901U32";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5901U32_in";	//입력 레코드명(리소스파일 참고)

	

	//[2] Tran조회 입력값을 입력한다.
	CString strCTNO;		//종합계좌대체번호
	CString strAPNO;		//계좌상품번호
	CString strPWD;		//비밀번호
	CString strFDM_UNQ_NO;		//딜링하우스고유번호
	CString strPRDT_CD;		//상품코드
	CString strNMPR_UNQ_NO;		//호가고유번호
	CString strCNCS_CND_DCD;		//체결조건구분코드
	CString strORDR_EXPR_DT;		//주문만료일자
	CString strPRC_CND_DCD;		//가격조건구분코드
	CString strODRV_ORDR_PRC;		//해외파생주문가격
	CString strORDR_QNT;		//주문수량
	CString strSQ1_STLS_YN;		//1차스탑로스여부
	CString strSQ1_APMPR_YN;		//1차지정가여부
	CString strSQ1_STLS_PRC;		//1차스탑로스가격
	CString strSQ1_APPN_PRC;		//1차지정가격
	CString strSQ1_CHAS_STLS_PRC;		//1차추적손절매가격
	CString strSQ2_STLS_YN;		//2차스탑로스여부
	CString strSQ2_STLS_PRC;		//2차스탑로스가격
	CString strSQ2_APMPR_YN;		//2차지정가여부
	CString strSQ2_APPN_PRC;		//2차지정가격
	CString strSQ2_CHAS_STLS_PRC;		//2차추적손절매가격
	CString strORDR_DRCN_DCD;		//주문방향구분코드
	CString strTRDE_PRC_DFRN_CTNS;		//매매가격차이내용

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//계좌상품번호
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//비밀번호
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//계좌비밀번호는 단방향 암호화를 해야된다.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//상품코드
	
	//딜링하우스고유번호
	GetDlgItem(IDC_EDIT_SYMBOL_HOUSE)->GetWindowText(strFDM_UNQ_NO);

	//상품코드
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//호가고유번호
	strNMPR_UNQ_NO = _T("0");

	//해외파생매도매수구분코드
	strODRV_SELL_BUY_DCD = _T("6");

	//주문수량
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	//1차스탑로스가격(STOP)
	GetDlgItem(IDC_EDIT_STOP_PRC)->GetWindowText(strSQ1_STLS_PRC);
	//1차스탑로스여부(STOP)
	if (_ttof(strSQ1_STLS_PRC))
		strSQ1_STLS_YN = _T("Y");
	else
		strSQ1_STLS_YN = _T("N");

	//1차지정가격(LIMIT)
	GetDlgItem(IDC_EDIT_LIMIT_PRC)->GetWindowText(strSQ1_APPN_PRC);
	//1차지정가여부(LIMIT)
	if (_ttof(strSQ1_APPN_PRC))
		strSQ1_APMPR_YN = _T("Y");
	else
		strSQ1_APMPR_YN = _T("N");

	//1차추적손절매가격(T.Stop)
	GetDlgItem(IDC_EDIT_T_STOP_PRC)->GetWindowText(strSQ1_CHAS_STLS_PRC);
	//2차스탑로스여부
	if (_ttof(strSQ1_CHAS_STLS_PRC))
		strSQ2_STLS_YN = _T("Y");
	else
		strSQ2_STLS_YN = _T("N");

	strSQ2_STLS_PRC = _T("0");		//2차스탑로스가격(사용안함)
	strSQ2_APPN_PRC = _T("0");		//2차지정가격(사용안함)
	strSQ2_APMPR_YN = _T("N");		//2차지정가여부(사용안함)
	strSQ2_CHAS_STLS_PRC = _T("0");		//2차추적손절매가격(사용안함)

	//주문방향구분코드(N-일반주문, W-대기주문 (일반주문만 사용))
	strORDR_DRCN_DCD = _T("N");

	//매매가격차이내용(사용안함)
	strTRDE_PRC_DFRN_CTNS.Empty();

	//T.S
	if (!strSQ2_STLS_YN.CompareNoCase(_T("Y")))
	{
		strPRC_CND_DCD = _T("6");
	}
	//Stop 또는 Limit
	else if (!strSQ1_STLS_YN.CompareNoCase(_T("Y")) ||
			 !strSQ1_APMPR_YN.CompareNoCase(_T("Y")))
	{
		strPRC_CND_DCD = _T("4");
	}
	//OCO 주문
	else if (!strSQ1_STLS_YN.CompareNoCase(_T("Y")) &&
			 !strSQ1_APMPR_YN.CompareNoCase(_T("Y")))
	{
		strPRC_CND_DCD = _T("5");
	}
	
	//해외파생주문가격
	if (strPRC_CND_DCD == _T("1") || strPRC_CND_DCD == _T("3"))	//지정가, 역지정가(STOP)
		GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strODRV_ORDR_PRC);
	else //시장가
		strODRV_ORDR_PRC = _T("0");

	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//해외파생원주문번호
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "PWD", strPWD);		//비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//딜링하우스고유번호
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "NMPR_UNQ_NO", strNMPR_UNQ_NO);		//호가고유번호
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "CNCS_CND_DCD", strCNCS_CND_DCD);		//체결조건구분코드
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "ORDR_EXPR_DT", strORDR_EXPR_DT);		//주문만료일자
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "PRC_CND_DCD", strPRC_CND_DCD);		//가격조건구분코드
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "ODRV_ORDR_PRC", strODRV_ORDR_PRC);		//해외파생주문가격
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "ORDR_QNT", strORDR_QNT);		//주문수량
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_STLS_YN", strSQ1_STLS_YN);		//1차스탑로스여부
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_APMPR_YN", strSQ1_APMPR_YN);		//1차지정가여부
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_STLS_PRC", strSQ1_STLS_PRC);		//1차스탑로스가격
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_APPN_PRC", strSQ1_APPN_PRC);		//1차지정가격
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ1_CHAS_STLS_PRC", strSQ1_CHAS_STLS_PRC);		//1차추적손절매가격
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_STLS_YN", strSQ2_STLS_YN);		//2차스탑로스여부
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_STLS_PRC", strSQ2_STLS_PRC);		//2차스탑로스가격
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_APMPR_YN", strSQ2_APMPR_YN);		//2차지정가여부
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_APPN_PRC", strSQ2_APPN_PRC);		//2차지정가격
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "SQ2_CHAS_STLS_PRC", strSQ2_CHAS_STLS_PRC);		//2차추적손절매가격
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//주문방향구분코드
	m_CommAgent.SetTranInputData(m_nRqIdModSLOrd, "OTS5901U32", "OTS5901U32_in", "TRDE_PRC_DFRN_CTNS", strTRDE_PRC_DFRN_CTNS);		//매매가격차이내용

	CString strBenefitAcc = "N";		//수익증권계좌 구분
	CString strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[3] 서버에 Tran조회 요청한다.
	if (m_CommAgent.RequestTran(m_nRqIdModSLOrd, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", nRequestDataCnt) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}


//*******************************************************************
// Function Name : OnBnClickedBtnCalsl
// Function      : 
// Param         : 
// Return        : void 
// Create        : 변윤식, 2017/07/31
// Comment       : S&L취소
//******************************************************************
void CFxMarginOrdDlg::OnBnClickedBtnCalsl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5901U33";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5901U33_in";	//입력 레코드명(리소스파일 참고)

	//[1] Request ID생성
	m_nRqIdCanSLOrd = m_CommAgent.CreateRequestID();

	//[2] Tran조회 입력값을 입력한다.
	CString strODRV_OR_ODNO;		//해외파생원주문번호
	CString strCTNO;		//종합계좌대체번호
	CString strAPNO;		//계좌상품번호
	CString strPWD;		//비밀번호
	CString strFDM_UNQ_NO;		//딜링하우스고유번호
	CString strPRDT_CD;		//상품코드
	CString strORDR_QNT;		//주문수량
	CString strORDR_DRCN_DCD;		//주문방향구분코드

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//계좌상품번호
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//비밀번호
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//계좌비밀번호는 단방향 암호화를 해야된다.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//상품코드

	//해외파생원주문번호
	GetDlgItem(IDC_ORDER_NO)->GetWindowText(strODRV_OR_ODNO);

	//딜링하우스고유번호
	GetDlgItem(IDC_EDIT_SYMBOL_HOUSE)->GetWindowText(strFDM_UNQ_NO);

	//상품코드
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//주문수량
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	//주문방향구분코드(N-일반주문, W-대기주문 (일반주문만 사용))
	strORDR_DRCN_DCD = _T("N");

	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//해외파생원주문번호
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "PWD", strPWD);		//비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//딜링하우스고유번호
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "ORDR_QNT", strORDR_QNT);		//주문수량
	m_CommAgent.SetTranInputData(m_nRqIdCanSLOrd, "OTS5901U33", "OTS5901U33_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//주문방향구분코드

	CString strBenefitAcc = "N";		//수익증권계좌 구분
	CString strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.)

	//[3] 서버에 Tran조회 요청한다.
	if (m_CommAgent.RequestTran(m_nRqIdCanSLOrd, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", nRequestDataCnt) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}
