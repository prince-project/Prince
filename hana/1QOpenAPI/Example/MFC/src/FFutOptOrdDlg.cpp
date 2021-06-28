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
#include "FFutOptOrdDlg.h"

#define ID_SECOND_TIMER		100	//1초 간격 타이머

#define SELL_BK_COLOR		RGB(206, 232, 255)	//매도 배경색
#define BUY_BK_COLOR		RGB(251, 221, 255)	//매수 배경색

//통신 구조체 헤더

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern void NumericString(CString& strValue, BOOL bNotDisplayZero = FALSE);

static char* g_szPriceCond[] = { "1", "2", "3"}; //1:지정가, 2:시장가, 3:STOPMARKET

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

// CFFutOptOrdDlg 대화 상자
CFFutOptOrdDlg::CFFutOptOrdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFFutOptOrdDlg::IDD, pParent)
{
	m_bCommConnect		= FALSE;

	m_nRqIdAccNoList		= 0;	//계좌조회 Request ID
	m_nRqIdFDemoAccNoList	= 0;	//해외모의 계좌조회 Request ID

	m_nRqIdSellOrd			= 0;	//매도주문 Request ID
	m_nRqIdBuyOrd			= 0;	//매수주문 Request ID
	m_nRqIdChangeOrd		= 0;	//정정주문 Request ID
	m_nRqIdCancelOrd		= 0;	//취소주문 Request ID

	m_nRqIdNonExecList		= 0;		//미체결내역 Request ID
	m_nRqIdExecList			= 0;	//주문체결내역 Request ID
	m_nRqIdDepositList		= 0;	//예수금내역 Request ID

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_nSeverType			= 0;	//0-리얼, 1-국내모의, 2-해외무의

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFFutOptOrdDlg::DoDataExchange(CDataExchange* pDX)
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
}

BEGIN_MESSAGE_MAP(CFFutOptOrdDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_LOGIN, &CFFutOptOrdDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_LOGOUT, &CFFutOptOrdDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDOK, &CFFutOptOrdDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELL, &CFFutOptOrdDlg::OnBnClickedBtnSell)
	ON_BN_CLICKED(IDC_BTN_BUY, &CFFutOptOrdDlg::OnBnClickedBtnBuy)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CFFutOptOrdDlg::OnBnClickedBtnChange)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CFFutOptOrdDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST, &CFFutOptOrdDlg::OnBnClickedBtnReqExecList)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST_NEXT, &CFFutOptOrdDlg::OnBnClickedBtnReqExecListNext)
	ON_BN_CLICKED(IDC_BTN_REQ_ACCNO, &CFFutOptOrdDlg::OnBnClickedBtnReqAccno)
	ON_BN_CLICKED(IDC_BTN_REQ_DEPOSIT, &CFFutOptOrdDlg::OnBnClickedBtnReqDeposit)
	ON_BN_CLICKED(IDC_BTN_REQ_DEPOSIT_NEXT, &CFFutOptOrdDlg::OnBnClickedBtnReqDepositNext)
	ON_BN_CLICKED(IDC_BTN_REQ_NON_EXEC_LIST, &CFFutOptOrdDlg::OnBnClickedBtnReqNonExecList)
	ON_BN_CLICKED(IDC_BTN_REQ_NON_EXEC_LIST_NEXT, &CFFutOptOrdDlg::OnBnClickedBtnReqNonExecListNext)
	ON_BN_CLICKED(IDC_BTN_REQ_BALANCE, &CFFutOptOrdDlg::OnBnClickedBtnReqBalance)
	ON_BN_CLICKED(IDC_BTN_REQ_BALANCE_NEXT, &CFFutOptOrdDlg::OnBnClickedBtnReqBalanceNext)
	ON_BN_CLICKED(IDC_BTN_LOAD_USER_ACC, &CFFutOptOrdDlg::OnBnClickedBtnLoadUserAcc)
	ON_COMMAND_RANGE(IDC_CON_REAL, IDC_CON_F_DEMO, &CFFutOptOrdDlg::OnRdoSelectServer)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCNO, &CFFutOptOrdDlg::OnNMDblclkListAccNo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NON_EXE, &CFFutOptOrdDlg::OnNMDblclkListNonExec)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BALANCE, &CFFutOptOrdDlg::OnNMDblclkListBalance)

	ON_BN_CLICKED(IDC_BTN_ACCINFO, &CFFutOptOrdDlg::OnBnClickedBtnAccinfo)
	ON_BN_CLICKED(IDC_BUTTON2, &CFFutOptOrdDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

// agent로부터 이벤트 수신 함수를 정의한다.
BEGIN_EVENTSINK_MAP(CFFutOptOrdDlg, CDialog)
	ON_EVENT(CFFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 1, CFFutOptOrdDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CFFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 2, CFFutOptOrdDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CFFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 3, CFFutOptOrdDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
	ON_EVENT(CFFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 4, CFFutOptOrdDlg::OnAgentEventHandler, VTS_I4 VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

// CFFutOptOrdDlg 메시지 처리기
void CFFutOptOrdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
void CFFutOptOrdDlg::OnPaint()
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
HCURSOR CFFutOptOrdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CFFutOptOrdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CFFutOptOrdDlg::OnNMDblclkListAccNo(NMHDR *pNMHDR, LRESULT *pResult)
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

void CFFutOptOrdDlg::OnNMDblclkListNonExec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	/*TCHAR *strTitle[] = { 0_T("영업일자"), 1_T("종합계좌번호"), 2_T("주문번호"), 3_T("상품코드"),
		4_T("원주문번호"), 5_T("모주문번호"), 6_T("주문그룹번호"), 7_T("주문일자"),
		8_T("고객명"), 9_T("매도매수구분코드"), 10_T("주문가격"), 11_T("주문수량"),
		12_T("정정수량"), 13_T("취소수량"), 14_T("체결수량"), 15_T("잔여수량"),
		_T("가격조건구분코드"), _T("체결조건구분코드"), _T("1차지정가격"), _T("평균체결가격"),
		_T("체결율"), _T("현재가격"), _T("매체구분코드"), _T("주문구분코드"),
		_T("주문상태구분코드"), _T("FCM주문번호"), _T("사용자ID"), _T("공인IP주소"),
		_T("접수시각"), _T("체결시각"), _T("현지접수시각"), _T("현지체결시각"), _T("통화코드") };*/

	CString strOrdNo = m_listNonExec.GetItemText(nSelectRow, 2);
	CString strSymbol = m_listNonExec.GetItemText(nSelectRow, 3);
	CString strOrdPrice = m_listNonExec.GetItemText(nSelectRow, 10);
	CString strOrdSu = m_listNonExec.GetItemText(nSelectRow, 11);

	GetDlgItem(IDC_EDIT_ORG_NO)->SetWindowText(strOrdNo);
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);
	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);
}

void CFFutOptOrdDlg::OnNMDblclkListBalance(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	/*
		TCHAR *strTitle[] = { 0_T("종합계좌번호"), 1_T("대체종합계좌번호"), 2_T("계좌상품번호"), 3_T("고객명"),
		4_T("상품코드"), 5_T("상품명"), 6_T("매도매수구분코드"), 7_T("미결제약정수량"),
		8_T("매매평균단가"), 9_T("청산가능수량"), 10_T("주문잔여수량"), 11_T("현재가격"),
		12_T("전일대비"), 13_T("전일대비율"), 14_T("평가금액"), 15_T("평가손익금액"),
		16_T("손익율"), 17_T("미결제약정금액"), 18_T("환산승수"), 19_T("선물옵션구분코드"),
		20_T("통화코드"), 21_T("관리부점코드"), 22_T("관리지점명"), 23_T("관리사원번호"),
		24_T("관리자명"), 25_T("가격소수점이하길이"), 26_T("표시가격"), 27_T("영업일자") };*/

	CString strSymbol = m_listBalance.GetItemText(nSelectRow, 4);
	CString strOrdPrice = m_listBalance.GetItemText(nSelectRow, 8);
	CString strOrdSu = m_listBalance.GetItemText(nSelectRow, 7);

	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);
	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);
}

void CFFutOptOrdDlg::OnDestroy()
{
	//모든 실시간등록을 해제한다.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();
	
	CDialog::OnDestroy();
}

void CFFutOptOrdDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CFFutOptOrdDlg::OnTimer(UINT_PTR nIDEvent)
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
void CFFutOptOrdDlg::OnRdoSelectServer(UINT nID)
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
void CFFutOptOrdDlg::OnBnClickedBtnAccinfo()
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
BOOL CFFutOptOrdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CString strTitle;
	strTitle.Format("%s-[해외선물주문](%s)", PROGRAM_NAME, VERSION_INFO);
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
void CFFutOptOrdDlg::InitListAccNo()
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
void CFFutOptOrdDlg::InitListReal()
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
void CFFutOptOrdDlg::InitListNonExec()
{
	CRect rc;
	m_listNonExec.GetClientRect(rc);
	m_listNonExec.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("영업일자"), _T("종합계좌번호"), _T("주문번호"), _T("상품코드"),
		_T("원주문번호"), _T("모주문번호"), _T("주문그룹번호"), _T("주문일자"),
		_T("고객명"), _T("매도매수구분코드"), _T("주문가격"), _T("주문수량"),
		_T("정정수량"), _T("취소수량"), _T("체결수량"), _T("잔여수량"),
		_T("가격조건구분코드"), _T("체결조건구분코드"), _T("1차지정가격"), _T("평균체결가격"),
		_T("체결율"), _T("현재가격"), _T("매체구분코드"), _T("주문구분코드"),
		_T("주문상태구분코드"), _T("FCM주문번호"), _T("사용자ID"), _T("공인IP주소"),
		_T("접수시각"), _T("체결시각"), _T("현지접수시각"), _T("현지체결시각"), _T("통화코드") };

	int i;
	for (i = 0; i < 33; i++)
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
void CFFutOptOrdDlg::InitListExec()
{
	CRect rc;
	m_listExec.GetClientRect(rc);
	m_listExec.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("종합계좌번호"), _T("주문번호"), _T("상품코드"), _T("원주문번호"), _T("모주문번호"),
		_T("주문그룹번호"), _T("주문일자"), _T("계좌상품코드"), _T("고객명"), _T("매도매수구분코드"),
		_T("주문가격"), _T("주문수량"), _T("정정수량"), _T("취소수량"), _T("체결수량"), _T("잔여수량"),
		_T("가격조건구분코드"), _T("체결조건구분코드"), _T("1차지정가격"), _T("평균체결가격"),
		_T("체결율"), _T("현재가격"), _T("매체구분코드"), _T("주문구분코드"), _T("주문상태구분코드"),
		_T("FCM주문번호"), _T("사용자ID"), _T("공인IP주소"), _T("접수시각"), _T("체결시각"), _T("현지접수시각"),
		_T("체결상세일시"), _T("통화코드") };

	int i;
	for (i = 0; i < 33; i++)
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
void CFFutOptOrdDlg::InitListDeposit()
{
	CRect rc;
	m_listDeposit.GetClientRect(rc);
	m_listDeposit.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("통화코드"), _T("기준환율"), _T("전일현금"), _T("현금입금"),
						_T("현금출금"), _T("청산손익"), _T("옵션매도"), _T("옵션매수"),
						_T("수수료"), _T("당일현금"), _T("평가손익"), _T("평가예탁"),
						_T("옵션평가"), _T("총계정자산"), _T("개시증거금"), _T("주문증거금"),
						_T("유지증거금"), _T("증거금부족"), _T("인출가능"), _T("환전가능"),
						_T("주문가능"), _T("추가증거금"), _T("미수연체이자") };

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
void CFFutOptOrdDlg::InitListBalance()
{
	CRect rc;
	m_listBalance.GetClientRect(rc);
	m_listBalance.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("종합계좌번호"), _T("대체종합계좌번호"), _T("계좌상품번호"), _T("고객명"),
		_T("상품코드"), _T("상품명"), _T("매도매수구분코드"), _T("미결제약정수량"),
		_T("매매평균단가"), _T("청산가능수량"), _T("주문잔여수량"), _T("현재가격"),
		_T("전일대비"), _T("전일대비율"), _T("평가금액"), _T("평가손익금액"),
		_T("손익율"), _T("미결제약정금액"), _T("환산승수"), _T("선물옵션구분코드"),
		_T("통화코드"), _T("관리부점코드"), _T("관리지점명"), _T("관리사원번호"),
		_T("관리자명"), _T("가격소수점이하길이"), _T("표시가격"), _T("영업일자") };

	int i;
	for (i = 0; i < 28; i++)
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
void CFFutOptOrdDlg::OnBnClickedLogin()
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
	//체결 실시간 통보
	m_CommAgent.RegisterReal("EF1", m_strLoginID);
	//미체결 실시간 통보
	m_CommAgent.RegisterReal("EF4", m_strLoginID);
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : 로그아웃
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFFutOptOrdDlg::OnBnClickedLogout()
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
void CFFutOptOrdDlg::OnBnClickedOk()
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
void CFFutOptOrdDlg::OnBnClickedBtnReqAccno()
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
void CFFutOptOrdDlg::OnBnClickedBtnLoadUserAcc()
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
CString CFFutOptOrdDlg::GetAccAPNO(CString strAccNo)
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
void CFFutOptOrdDlg::RequestAccList()
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
void CFFutOptOrdDlg::RequestFDemoAccList()
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
BOOL CFFutOptOrdDlg::SendSellBuyOrder(CString strDealingSide, int nRqId)
{
	CString strTrCode = "OTS5901U01";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5901U01_in";		//입력 레코드명(리소스파일 참고)

	//[1] Request ID생성
	
	CString strCTNO;			//대체종합계좌번호
	CString strAPNO;			//계좌상품번호
	CString strPWD;				//비밀번호
	CString strPRDT_CD;			//상품코드
	CString strSELL_BUY_DCD;	//매도매수구분코드
	CString strPRC_CND_DCD;		//가격조건구분코드
	CString strODRV_ORDR_PRC;	//해외파생주문가격
	CString strORDR_QNT;		//주문수량
	CString strSTLS_APPN_PRC;	//스탑로스지정가격
	CString strORDR_HND_DCD;	//주문조작구분코드
	CString strORDR_DCD;		//주문구분코드
	CString strETC_ORDR_DCD;	//기타주문구분코드
	CString strCNCS_CND_DCD;	//체결조건구분코드
	CString strCLR_PST_NO;		//청산포지션번호
	CString strORDR_EXPR_DT;	//주문만료일자

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//계좌상품번호
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//비밀번호
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//계좌비밀번호는 단방향 암호화를 해야된다.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//상품코드

	strSELL_BUY_DCD = strDealingSide;								//매도매수구분코드(S:매도, B:매수)

	if (m_cmdOrdType.GetCurSel() >= 0)
		strPRC_CND_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];		//가격조건구분코드

	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strODRV_ORDR_PRC);	//해외파생주문가격
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);		//주문수량
	GetDlgItem(IDC_EDIT_STOP_PRC)->GetWindowText(strSTLS_APPN_PRC); //스탑로스지정가격

	strORDR_HND_DCD	= "C";					//주문조작구분코드(C:일반주문, M:반대매매, F:강제청산, D:FND반대매매)
	strORDR_DCD		= "O";					//주문구분코드
	strCNCS_CND_DCD	= "1";					//체결조건구분코드(1:FAS(DAY), 6:GTD)

	//[2] Tran조회 입력값을 입력한다.
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "CTNO", strCTNO);						//대체종합계좌번호
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "APNO", strAPNO);						//계좌상품번호
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "PWD", strPWD);						//비밀번호
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);				//상품코드
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);		//매도매수구분코드
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "PRC_CND_DCD", strPRC_CND_DCD);		//가격조건구분코드
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ODRV_ORDR_PRC", strODRV_ORDR_PRC);	//해외파생주문가격
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);				//주문수량

	if (strPRC_CND_DCD == "3")
		m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "STLS_APPN_PRC", strSTLS_APPN_PRC);	//스탑로스지정가격

	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_HND_DCD", strORDR_HND_DCD);		//주문조작구분코드
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_DCD", strORDR_DCD);				//주문구분코드
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ETC_ORDR_DCD", strETC_ORDR_DCD);		//기타주문구분코드
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "CNCS_CND_DCD", strCNCS_CND_DCD);		//체결조건구분코드
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "CLR_PST_NO", strCLR_PST_NO);			//청산포지션번호
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_EXPR_DT", strORDR_EXPR_DT);		//주문만료일자

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
void CFFutOptOrdDlg::OnBnClickedBtnSell()
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
void CFFutOptOrdDlg::OnBnClickedBtnBuy()
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
void CFFutOptOrdDlg::OnBnClickedBtnChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5901U02";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5901U02_in";	//입력 레코드명(리소스파일 참고)
	
	//[1] Request ID생성
	m_nRqIdChangeOrd = m_CommAgent.CreateRequestID();

	//[2] Tran조회 입력값을 입력한다.
	CString strODRV_OR_ODNO;		//해외파생원주문번호
	CString strCTNO;		//대체종합계좌번호
	CString strAPNO;		//계좌상품번호
	CString strPWD;		//비밀번호
	CString strPRDT_CD;		//상품코드
	CString strPRC_CND_DCD;		//가격조건구분코드
	CString strODRV_RVSE_PRC;		//해외파생정정가격
	CString strRVSE_QNT;		//정정수량
	CString strSTLS_APPN_PRC;		//스탑로스지정가격
	CString strRMN_QNT_YN;		//잔여수량여부

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//계좌상품번호
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//비밀번호
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//계좌비밀번호는 단방향 암호화를 해야된다.
	
	//해외파생원주문번호
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strODRV_OR_ODNO);
	
	//상품코드
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);
	
	//가격조건구분코드
	strPRC_CND_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];

	//해외파생정정가격
	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strODRV_RVSE_PRC);

	//정정수량
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strRVSE_QNT);

	//스탑로스지정가격
	GetDlgItem(IDC_EDIT_STOP_PRC)->GetWindowText(strSTLS_APPN_PRC);

	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ODRV_OR_ODNO", strODRV_OR_ODNO);	//해외파생원주문번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "CTNO", strCTNO);				//대체종합계좌번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "APNO", strAPNO);				//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PWD", strPWD);					//비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PRC_CND_DCD", strPRC_CND_DCD);		//가격조건구분코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ODRV_RVSE_PRC", strODRV_RVSE_PRC);		//해외파생정정가격
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "RVSE_QNT", strRVSE_QNT);		//정정수량
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "STLS_APPN_PRC", strSTLS_APPN_PRC);		//스탑로스지정가격
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "RMN_QNT_YN", strRMN_QNT_YN);		//잔여수량여부

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
void CFFutOptOrdDlg::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5901U03";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5901U03_in";	//입력 레코드명(리소스파일 참고)

	//[1] Request ID생성
	m_nRqIdCancelOrd = m_CommAgent.CreateRequestID();

	//[2] Tran조회 입력값을 입력한다.
	
	CString strCTNO;		//대체종합계좌번호
	CString strAPNO;		//계좌상품번호
	CString strPWD;		//비밀번호
	CString strODRV_OR_ODNO;		//해외파생원주문번호
	CString strPRDT_CD;		//상품코드
	CString strCNCL_QNT;		//취소수량

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//대체종합계좌번호
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);			//비밀번호
	strPWD = m_CommAgent.GetEncrpyt(strPWD);						//계좌비밀번호는 단방향 암호화를 해야된다.

	//해외파생원주문번호
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strODRV_OR_ODNO);

	//상품코드
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//취소수량
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strCNCL_QNT);

	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, "OTS5901U03_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//해외파생원주문번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, "OTS5901U03_in", "CTNO", strCTNO);		//대체종합계좌번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, "OTS5901U03_in", "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, "OTS5901U03_in", "PWD", strPWD);		//비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, "OTS5901U03_in", "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, "OTS5901U03_in", "CNCL_QNT", strCNCL_QNT);		//취소수량

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
void CFFutOptOrdDlg::OnBnClickedBtnReqDeposit()
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

	CString strTrCode = "OTS5943Q01";				//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5943Q01_in";			//입력 레코드명(리소스파일 참고)

	/*-------------------------------*
	 [1] Request ID생성
	*-------------------------------*/
	m_nRqIdDepositList = m_CommAgent.CreateRequestID();

	CString strBSN_DT;			//영업일자
	CString strCTNO;			//대체종합계좌번호
	CString strAPNO;			//계좌상품번호
	CString strPWD;				//비밀번호(단방향 암호화를 한다.)

	//조회일자
	m_dateTime1.GetWindowText(strBSN_DT);
	strBSN_DT.Remove('-');
	
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
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "BSN_DT", strBSN_DT);	//영업일자
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "CTNO", strCTNO);		//대체종합계좌번호
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "PWD", strPWD);		//비밀번호

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
void CFFutOptOrdDlg::OnBnClickedBtnReqDepositNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5943Q01";				//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5943Q01_in";			//입력 레코드명(리소스파일 참고)

	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdDepositList = m_CommAgent.CreateRequestID();

	CString strBSN_DT;		//영업일자
	CString strCTNO;		//대체종합계좌번호
	CString strAPNO;		//계좌상품번호
	CString strPWD;			//비밀번호

	//조회일자
	m_dateTime1.GetWindowText(strBSN_DT);
	strBSN_DT.Remove('-');

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
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "BSN_DT", strBSN_DT);	//영업일자
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "CTNO", strCTNO);		//대체종합계좌번호
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "PWD", strPWD);		//비밀번호

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
void CFFutOptOrdDlg::OnBnClickedBtnReqNonExecList()
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

	CString strTrCode = "OTS5911Q41";				//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5911Q41_in_sub01";	//입력 레코드명(리소스파일 참고)

	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdNonExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] 입력 건수를 입력한다.
	*-------------------------------*/
	/*	REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
	ARRAY 가 '0'보다 크면 입력이 복수건이다.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdNonExecList, strTrCode, strInRecName, nInputCnt);
	
	CString strAccNo;	//종합계좌번호
	CString strCTNO;	//계좌대체번호
	CString strPrdt;	//계좌상품번호
	CString strPWD;		//계좌비밀번호

	//[3] Tran조회 입력값을 입력한다.
	for (int i = 0; i < nInputCnt; i++)
	{
		//계좌대체번호를 얻어온다.
		GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
		
		//계좌상품번호
		GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strPrdt);

		strCTNO = GetAccAPNO(strAccNo + strPrdt);	//종합계좌대체번호

		//계좌비밀번호
		GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
		strPWD = m_CommAgent.GetEncrpyt(strPWD);

		//대체종합계좌번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdNonExecList, strTrCode, strInRecName, "CTNO", strCTNO, i);

		//계좌상품번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdNonExecList, strTrCode, strInRecName, "APNO", strPrdt, i);

		//계좌비밀번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdNonExecList, strTrCode, strInRecName, "PWD", strPWD, i);

	}

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
void CFFutOptOrdDlg::OnBnClickedBtnReqNonExecListNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5911Q41";				//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5911Q41_in_sub01";	//입력 레코드명(리소스파일 참고)

	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdNonExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] 입력 건수를 입력한다.
	*-------------------------------*/
	/*	REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
	ARRAY 가 '0'보다 크면 입력이 복수건이다.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdNonExecList, strTrCode, strInRecName, nInputCnt);

	CString strAccNo;
	CString strCTNO;
	CString strPrdt;
	CString strPWD;

	//[3] Tran조회 입력값을 입력한다.
	for (int i = 0; i < nInputCnt; i++)
	{
		//계좌대체번호를 얻어온다.
		GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
		
		//계좌상품번호
		GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strPrdt);
		strCTNO = GetAccAPNO(strAccNo + strPrdt);	//종합계좌대체번호

		//계좌비밀번호
		GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
		strPWD = m_CommAgent.GetEncrpyt(strPWD);

		//대체종합계좌번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdNonExecList, strTrCode, strInRecName, "CTNO", strCTNO, i);

		//계좌상품번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdNonExecList, strTrCode, strInRecName, "APNO", strPrdt, i);

		//계좌비밀번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdNonExecList, strTrCode, strInRecName, "PWD", strPWD, i);
	}

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
void CFFutOptOrdDlg::OnBnClickedBtnReqExecList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_listExec.DeleteAllItems();
	m_strListExecNextRqKey.Empty(); //연속키를 초기화시킨다.

	CString strTrCode = "OTS5911Q52";				//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5911Q52_in_sub01";	//입력 레코드명(리소스파일 참고)
	
	/*-------------------------------*
		[1] Request ID생성
	 *-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
		[2] 입력 건수를 입력한다.
	 *-------------------------------*/
	/*	REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		ARRAY 가 '0'보다 크면 입력이 복수건이다.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdExecList, strTrCode, strInRecName, nInputCnt);

	CString strAccNo;
	CString strCTNO;
	CString strPrdt;
	CString strPWD;

	//[3] Tran조회 입력값을 입력한다.
	for (int i = 0; i < nInputCnt; i++)
	{
		//계좌대체번호를 얻어온다.
		GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
		
		//계좌상품번호
		GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strPrdt);
		strCTNO = GetAccAPNO(strAccNo + strPrdt);	//종합계좌대체번호

		//계좌비밀번호
		GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
		strPWD = m_CommAgent.GetEncrpyt(strPWD);

		//대체종합계좌번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO, i);

		//계좌상품번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strPrdt, i);

		//계좌비밀번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD, i);
	}

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
void CFFutOptOrdDlg::OnBnClickedBtnReqExecListNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5911Q52";				//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS5911Q52_in_sub01";	//입력 레코드명(리소스파일 참고)

	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] 입력 건수를 입력한다.
	*-------------------------------*/
	/*	REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		ARRAY 가 '0'보다 크면 입력이 복수건이다.	*/
	int nInputCnt = 1;
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdExecList, strTrCode, strInRecName, nInputCnt);

	CString strAccNo;
	CString strCTNO;
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
		m_CommAgent.SetTranInputArrayData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO, i);

		//계좌상품번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strPrdt, i);

		//계좌비밀번호
		m_CommAgent.SetTranInputArrayData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD, i);
	}

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
void CFFutOptOrdDlg::OnBnClickedBtnReqBalance()
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

	CString strTrCode = "OTS5919Q41";				//Tran코드(리소스파일 참고)
	CString strInRecName1 = "OTS5919Q41_in";	//입력 레코드명(리소스파일 참고)
	CString strInRecName2 = "OTS5919Q41_in_sub01";	//입력 레코드명(리소스파일 참고)

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
	m_CommAgent.SetTranInputArrayCnt(m_nRqIdBalanceList, strTrCode, strInRecName2, 1);

	CString strAccNo;
	CString strPrdt;
	CString strPWD;

	//[3] Tran조회 입력값을 입력한다.
	for (int i = 0; i < 3; i++)
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
void CFFutOptOrdDlg::OnBnClickedBtnReqBalanceNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS5919Q41";				//Tran코드(리소스파일 참고)
	CString strInRecName1 = "OTS5919Q41_in";	//입력 레코드명(리소스파일 참고)
	CString strInRecName2 = "OTS5919Q41_in_sub01";	//입력 레코드명(리소스파일 참고)

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
void CFFutOptOrdDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
		CString strBSN_DT, strCANO, strODRV_ODNO, strPRDT_CD, strODRV_OR_ODNO, strODRV_MO_ODNO, strORDR_GRUP_NO;
		CString strORDR_DT, strCUST_NM, strSELL_BUY_DCD, strODRV_ORDR_PRC, strORDR_QNT, strRVSE_QNT, strCNCL_QNT;
		CString strCNCS_QNT, strRMN_QNT, strPRC_CND_DCD, strCNCS_CND_DCD, strSQ1_APPN_PRC, strAVR_CNCS_PRC, strCNCS_RT;
		CString strNOW_PRC, strMDIA_DCD, strORDR_DCD, strORDR_STTS_DCD, strFCM_ODNO, strUSER_ID, strATHZ_IP_ADDR;
		CString strACPT_TM, strCNCS_TM, strACPL_ACPT_TM, strACPL_CNCS_TM, strCRRY_CD;

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

		strOutRecName = "OTS5911Q41_out_sub01";

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, strOutRecName);
		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strBSN_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "BSN_DT", nRow);		//영업일자
			strCANO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CANO", nRow);		//종합계좌번호
			strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_ODNO", nRow);		//해외파생주문번호
			strPRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRDT_CD", nRow);		//상품코드
			strODRV_OR_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_OR_ODNO", nRow);		//해외파생원주문번호
			strODRV_MO_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_MO_ODNO", nRow);		//해외파생모주문번호
			strORDR_GRUP_NO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_GRUP_NO", nRow);		//주문그룹번호
			strORDR_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DT", nRow);		//주문일자
			strCUST_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CUST_NM", nRow);		//고객명
			strSELL_BUY_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SELL_BUY_DCD", nRow);		//매도매수구분코드
			strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_ORDR_PRC", nRow);		//해외파생주문가격
			strORDR_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_QNT", nRow);		//주문수량
			strRVSE_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "RVSE_QNT", nRow);		//정정수량
			strCNCL_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCL_QNT", nRow);		//취소수량
			strCNCS_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT", nRow);		//체결수량
			strRMN_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "RMN_QNT", nRow);		//잔여수량
			strPRC_CND_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRC_CND_DCD", nRow);		//가격조건구분코드
			strCNCS_CND_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_CND_DCD", nRow);		//체결조건구분코드
			strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SQ1_APPN_PRC", nRow);		//1차지정가격
			strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "AVR_CNCS_PRC", nRow);		//평균체결가격
			strCNCS_RT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_RT", nRow);		//체결율
			strNOW_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "NOW_PRC", nRow);		//현재가격
			strMDIA_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "MDIA_DCD", nRow);		//매체구분코드
			strORDR_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DCD", nRow);		//주문구분코드
			strORDR_STTS_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_STTS_DCD", nRow);		//주문상태구분코드
			strFCM_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "FCM_ODNO", nRow);		//FCM주문번호
			strUSER_ID = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "USER_ID", nRow);		//사용자ID
			strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ATHZ_IP_ADDR", nRow);		//공인IP주소
			strACPT_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ACPT_TM", nRow);		//접수시각
			strCNCS_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_TM", nRow);		//체결시각
			strACPL_ACPT_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ACPL_ACPT_TM", nRow);		//현지접수시각
			strACPL_CNCS_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ACPL_CNCS_TM", nRow);		//현지체결시각
			strCRRY_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CRRY_CD", nRow);		//통화코드

			strBSN_DT.Trim();		//영업일자
			strCANO.Trim();		//종합계좌번호
			strODRV_ODNO.Trim();		//해외파생주문번호
			strPRDT_CD.Trim();		//상품코드
			strODRV_OR_ODNO.Trim();		//해외파생원주문번호
			strODRV_MO_ODNO.Trim();		//해외파생모주문번호
			strORDR_GRUP_NO.Trim();		//주문그룹번호
			strORDR_DT.Trim();		//주문일자
			strCUST_NM.Trim();		//고객명
			strSELL_BUY_DCD.Trim();		//매도매수구분코드
			NumericString(strODRV_ORDR_PRC);		//해외파생주문가격
			NumericString(strORDR_QNT);		//주문수량
			NumericString(strRVSE_QNT);		//정정수량
			NumericString(strCNCL_QNT);		//취소수량
			NumericString(strCNCS_QNT);		//체결수량
			NumericString(strRMN_QNT);		//잔여수량
			strPRC_CND_DCD.Trim();		//가격조건구분코드
			strCNCS_CND_DCD.Trim();		//체결조건구분코드
			NumericString(strSQ1_APPN_PRC);		//1차지정가격
			NumericString(strAVR_CNCS_PRC);		//평균체결가격
			NumericString(strCNCS_RT);		//체결율
			NumericString(strNOW_PRC);		//현재가격
			strMDIA_DCD.Trim();		//매체구분코드
			strORDR_DCD.Trim();		//주문구분코드
			strORDR_STTS_DCD.Trim();		//주문상태구분코드
			strFCM_ODNO.Trim();		//FCM주문번호
			strUSER_ID.Trim();		//사용자ID
			strATHZ_IP_ADDR.Trim();		//공인IP주소
			strACPT_TM.Trim();		//접수시각
			strCNCS_TM.Trim();		//체결시각
			strACPL_ACPT_TM.Trim();		//현지접수시각
			strACPL_CNCS_TM.Trim();		//현지체결시각
			strCRRY_CD.Trim();		//통화코드

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listNonExec.InsertItem(&lvItem);

			m_listNonExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strBSN_DT);		//영업일자
			m_listNonExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strCANO);		//종합계좌번호
			m_listNonExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strODRV_ODNO);		//해외파생주문번호
			m_listNonExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strPRDT_CD);		//상품코드
			m_listNonExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strODRV_OR_ODNO);		//해외파생원주문번호
			m_listNonExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strODRV_MO_ODNO);		//해외파생모주문번호
			m_listNonExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strORDR_GRUP_NO);		//주문그룹번호
			m_listNonExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strORDR_DT);		//주문일자
			m_listNonExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strCUST_NM);		//고객명
			m_listNonExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strSELL_BUY_DCD);		//매도매수구분코드
			m_listNonExec.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strODRV_ORDR_PRC);		//해외파생주문가격
			m_listNonExec.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strORDR_QNT);		//주문수량
			m_listNonExec.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strRVSE_QNT);		//정정수량
			m_listNonExec.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strCNCL_QNT);		//취소수량
			m_listNonExec.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strCNCS_QNT);		//체결수량
			m_listNonExec.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strRMN_QNT);		//잔여수량
			m_listNonExec.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strPRC_CND_DCD);		//가격조건구분코드
			m_listNonExec.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strCNCS_CND_DCD);		//체결조건구분코드
			m_listNonExec.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strSQ1_APPN_PRC);		//1차지정가격
			m_listNonExec.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strAVR_CNCS_PRC);		//평균체결가격
			m_listNonExec.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strCNCS_RT);		//체결율
			m_listNonExec.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strNOW_PRC);		//현재가격
			m_listNonExec.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strMDIA_DCD);		//매체구분코드
			m_listNonExec.SetItemText(nListIndex, 23, (LPTSTR)(LPCTSTR)strORDR_DCD);		//주문구분코드
			m_listNonExec.SetItemText(nListIndex, 24, (LPTSTR)(LPCTSTR)strORDR_STTS_DCD);		//주문상태구분코드
			m_listNonExec.SetItemText(nListIndex, 25, (LPTSTR)(LPCTSTR)strFCM_ODNO);		//FCM주문번호
			m_listNonExec.SetItemText(nListIndex, 26, (LPTSTR)(LPCTSTR)strUSER_ID);		//사용자ID
			m_listNonExec.SetItemText(nListIndex, 27, (LPTSTR)(LPCTSTR)strATHZ_IP_ADDR);		//공인IP주소
			m_listNonExec.SetItemText(nListIndex, 28, (LPTSTR)(LPCTSTR)strACPT_TM);		//접수시각
			m_listNonExec.SetItemText(nListIndex, 29, (LPTSTR)(LPCTSTR)strCNCS_TM);		//체결시각
			m_listNonExec.SetItemText(nListIndex, 30, (LPTSTR)(LPCTSTR)strACPL_ACPT_TM);		//현지접수시각
			m_listNonExec.SetItemText(nListIndex, 31, (LPTSTR)(LPCTSTR)strACPL_CNCS_TM);		//현지체결시각
			m_listNonExec.SetItemText(nListIndex, 32, (LPTSTR)(LPCTSTR)strCRRY_CD);		//통화코드

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
		CString strCANO, strODRV_ODNO, strPRDT_CD, strODRV_OR_ODNO, strODRV_MO_ODNO, strORDR_GRUP_NO;
		CString strORDR_DT, strACNT_PRDT_CD, strCUST_NM, strSELL_BUY_DCD, strODRV_ORDR_PRC, strORDR_QNT,strRVSE_QNT;
		CString strCNCL_QNT, strCNCS_QNT, strRMN_QNT, strPRC_CND_DCD, strCNCS_CND_DCD, strSQ1_APPN_PRC, strAVR_CNCS_PRC;
		CString strCNCS_RT, strNOW_PRC, strMDIA_DCD, strORDR_DCD, strORDR_STTS_DCD, strFCM_ODNO, strUSER_ID;
		CString strATHZ_IP_ADDR, strACPT_TM, strCNCS_TM, strACPL_ACPT_TM, strCNCS_DETL_DTM, strCRRY_CD;

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

		strOutRecName = "OTS5911Q52_out_sub01";

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, strOutRecName);
		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strCANO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CANO", nRow);		//종합계좌번호
			strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_ODNO", nRow);		//해외파생주문번호
			strPRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRDT_CD", nRow);		//상품코드
			strODRV_OR_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_OR_ODNO", nRow);		//해외파생원주문번호
			strODRV_MO_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_MO_ODNO", nRow);		//해외파생모주문번호
			strORDR_GRUP_NO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_GRUP_NO", nRow);		//주문그룹번호
			strORDR_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DT", nRow);		//주문일자
			strACNT_PRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ACNT_PRDT_CD", nRow);		//계좌상품코드
			strCUST_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CUST_NM", nRow);		//고객명
			strSELL_BUY_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SELL_BUY_DCD", nRow);		//매도매수구분코드
			strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ODRV_ORDR_PRC", nRow);		//해외파생주문가격
			strORDR_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_QNT", nRow);		//주문수량
			strRVSE_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "RVSE_QNT", nRow);		//정정수량
			strCNCL_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCL_QNT", nRow);		//취소수량
			strCNCS_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT", nRow);		//체결수량
			strRMN_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "RMN_QNT", nRow);		//잔여수량
			strPRC_CND_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRC_CND_DCD", nRow);		//가격조건구분코드
			strCNCS_CND_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_CND_DCD", nRow);		//체결조건구분코드
			strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SQ1_APPN_PRC", nRow);		//1차지정가격
			strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "AVR_CNCS_PRC", nRow);		//평균체결가격
			strCNCS_RT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_RT", nRow);		//체결율
			strNOW_PRC = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "NOW_PRC", nRow);		//현재가격
			strMDIA_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "MDIA_DCD", nRow);		//매체구분코드
			strORDR_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DCD", nRow);		//주문구분코드
			strORDR_STTS_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_STTS_DCD", nRow);		//주문상태구분코드
			strFCM_ODNO = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "FCM_ODNO", nRow);		//FCM주문번호
			strUSER_ID = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "USER_ID", nRow);		//사용자ID
			strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ATHZ_IP_ADDR", nRow);		//공인IP주소
			strACPT_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ACPT_TM", nRow);		//접수시각
			strCNCS_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_TM", nRow);		//체결시각
			strACPL_ACPT_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ACPL_ACPT_TM", nRow);		//현지접수시각
			strCNCS_DETL_DTM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_DETL_DTM", nRow);		//체결상세일시
			strCRRY_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CRRY_CD", nRow);		//통화코드

			strCANO.Trim();		//종합계좌번호
			strODRV_ODNO.Trim();		//해외파생주문번호
			strPRDT_CD.Trim();		//상품코드
			strODRV_OR_ODNO.Trim();		//해외파생원주문번호
			strODRV_MO_ODNO.Trim();		//해외파생모주문번호
			strORDR_GRUP_NO.Trim();		//주문그룹번호
			strORDR_DT.Trim();		//주문일자
			strACNT_PRDT_CD.Trim();		//계좌상품코드
			strCUST_NM.Trim();		//고객명
			strSELL_BUY_DCD.Trim();		//매도매수구분코드
			NumericString(strODRV_ORDR_PRC);		//해외파생주문가격
			NumericString(strORDR_QNT);		//주문수량
			NumericString(strRVSE_QNT);		//정정수량
			NumericString(strCNCL_QNT);		//취소수량
			NumericString(strCNCS_QNT);		//체결수량
			NumericString(strRMN_QNT);		//잔여수량
			strPRC_CND_DCD.Trim();		//가격조건구분코드
			strCNCS_CND_DCD.Trim();		//체결조건구분코드
			NumericString(strSQ1_APPN_PRC);		//1차지정가격
			NumericString(strAVR_CNCS_PRC);		//평균체결가격
			NumericString(strCNCS_RT);		//체결율
			NumericString(strNOW_PRC);		//현재가격
			strMDIA_DCD.Trim();		//매체구분코드
			strORDR_DCD.Trim();		//주문구분코드
			strORDR_STTS_DCD.Trim();		//주문상태구분코드
			strFCM_ODNO.Trim();		//FCM주문번호
			strUSER_ID.Trim();		//사용자ID
			strATHZ_IP_ADDR.Trim();		//공인IP주소
			strACPT_TM.Trim();		//접수시각
			strCNCS_TM.Trim();		//체결시각
			strACPL_ACPT_TM.Trim();		//현지접수시각
			strCNCS_DETL_DTM.Trim();		//체결상세일시
			strCRRY_CD.Trim();		//통화코드

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listExec.InsertItem(&lvItem);

			m_listExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strCANO);		//종합계좌번호
			m_listExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strODRV_ODNO);		//해외파생주문번호
			m_listExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strPRDT_CD);		//상품코드
			m_listExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strODRV_OR_ODNO);		//해외파생원주문번호
			m_listExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strODRV_MO_ODNO);		//해외파생모주문번호
			m_listExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strORDR_GRUP_NO);		//주문그룹번호
			m_listExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strORDR_DT);		//주문일자
			m_listExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strACNT_PRDT_CD);		//계좌상품코드
			m_listExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strCUST_NM);		//고객명
			m_listExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strSELL_BUY_DCD);		//매도매수구분코드
			m_listExec.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strODRV_ORDR_PRC);		//해외파생주문가격
			m_listExec.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strORDR_QNT);		//주문수량
			m_listExec.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strRVSE_QNT);		//정정수량
			m_listExec.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strCNCL_QNT);		//취소수량
			m_listExec.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strCNCS_QNT);		//체결수량
			m_listExec.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strRMN_QNT);		//잔여수량
			m_listExec.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strPRC_CND_DCD);		//가격조건구분코드
			m_listExec.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strCNCS_CND_DCD);		//체결조건구분코드
			m_listExec.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strSQ1_APPN_PRC);		//1차지정가격
			m_listExec.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strAVR_CNCS_PRC);		//평균체결가격
			m_listExec.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strCNCS_RT);		//체결율
			m_listExec.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strNOW_PRC);		//현재가격
			m_listExec.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strMDIA_DCD);		//매체구분코드
			m_listExec.SetItemText(nListIndex, 23, (LPTSTR)(LPCTSTR)strORDR_DCD);		//주문구분코드
			m_listExec.SetItemText(nListIndex, 24, (LPTSTR)(LPCTSTR)strORDR_STTS_DCD);		//주문상태구분코드
			m_listExec.SetItemText(nListIndex, 25, (LPTSTR)(LPCTSTR)strFCM_ODNO);		//FCM주문번호
			m_listExec.SetItemText(nListIndex, 26, (LPTSTR)(LPCTSTR)strUSER_ID);		//사용자ID
			m_listExec.SetItemText(nListIndex, 27, (LPTSTR)(LPCTSTR)strATHZ_IP_ADDR);		//공인IP주소
			m_listExec.SetItemText(nListIndex, 28, (LPTSTR)(LPCTSTR)strACPT_TM);		//접수시각
			m_listExec.SetItemText(nListIndex, 29, (LPTSTR)(LPCTSTR)strCNCS_TM);		//체결시각
			m_listExec.SetItemText(nListIndex, 30, (LPTSTR)(LPCTSTR)strACPL_ACPT_TM);		//현지접수시각
			m_listExec.SetItemText(nListIndex, 31, (LPTSTR)(LPCTSTR)strCNCS_DETL_DTM);		//체결상세일시
			m_listExec.SetItemText(nListIndex, 32, (LPTSTR)(LPCTSTR)strCRRY_CD);		//통화코드
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
		m_nRqIdFDemoAccNoList = 0;	//해외선물데모계좌리스트
	}
	//예수금 조회
	else if (m_nRqIdDepositList == nRequestId)
	{
		CString strCRRY_CD, strODRV_STDR_EXRT_CTNS, strBFDT_CSH_BLCE_CTNS, strODRV_CSH_RCTM_AMT_CTNS;
		CString strODRV_CSH_DRWG_AMT_CTNS, strODRV_CLR_PFLS_AMT_CTNS, strODRV_OPT_SELL_AMT_CTNS;
		CString strODRV_OPT_BUY_AMT_CTNS, strODRV_FEE_CTNS, strTHDT_CSH_BLCE_CTNS, strODRV_EVL_PFLS_AMT_CTNS;
		CString strEVL_DPST_AMT_CTNS, strODRV_OPT_EVL_AMT_CTNS, strTOT_ACC_ASST_VALU_AMT_CTNS;
		CString strOPNG_WMY_CTNS, strODRV_ORDR_WMY_CTNS, strODRV_MNTN_WMY_CTNS, strWMY_LACK_AMT_CTNS, strODRV_WDRW_PSBL_AMT_CTNS;
		CString strECHM_PSBL_AMT_CTNS, strODRV_ORDR_PSBL_AMT_CTNS, strODRV_ADIT_WMY_CTNS, strRCVB_OVDU_INTR_CTNS;

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

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OTS5943Q01_out_sub01");

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strCRRY_CD = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "CRRY_CD", nRow);		//통화코드
			strODRV_STDR_EXRT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_STDR_EXRT_CTNS", nRow);			//해외파생기준환율내용
			strBFDT_CSH_BLCE_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "BFDT_CSH_BLCE_CTNS", nRow);			// 전일현금잔액내용
			strODRV_CSH_RCTM_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "BFDT_CSH_BLCE_CTNS", nRow);		//해외파생현금입금금액내용
			strODRV_CSH_DRWG_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_CSH_DRWG_AMT_CTNS", nRow);		//해외파생현금출금금액내용
			strODRV_CLR_PFLS_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_CLR_PFLS_AMT_CTNS", nRow);		//해외파생청산손익금액내용
			strODRV_OPT_SELL_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_OPT_SELL_AMT_CTNS", nRow);		//해외파생옵션매도금액내용
			strODRV_OPT_BUY_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_OPT_BUY_AMT_CTNS", nRow);		//해외파생옵션매수금액내용
			strODRV_FEE_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_FEE_CTNS", nRow);				//해외파생수수료내용
			strTHDT_CSH_BLCE_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "THDT_CSH_BLCE_CTNS", nRow);			//당일현금잔액내용
			strODRV_EVL_PFLS_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_EVL_PFLS_AMT_CTNS", nRow);		//해외파생평가손익금액내용
			strEVL_DPST_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "EVL_DPST_AMT_CTNS", nRow);			//평가예탁금액내용
			strODRV_OPT_EVL_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_OPT_EVL_AMT_CTNS", nRow);		//해외파생옵션평가금액내용
			strTOT_ACC_ASST_VALU_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "TOT_ACC_ASST_VALU_AMT_CTNS", nRow);	//총계정자산가치금액내용
			strOPNG_WMY_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "OPNG_WMY_CTNS", nRow);				//개시증거금내용
			strODRV_ORDR_WMY_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_ORDR_WMY_CTNS", nRow);			//해외파생주문증거금내용
			strODRV_MNTN_WMY_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_MNTN_WMY_CTNS", nRow);			//해외파생유지증거금내용
			strWMY_LACK_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "WMY_LACK_AMT_CTNS", nRow);			//증거금부족금액내용
			strODRV_WDRW_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_WDRW_PSBL_AMT_CTNS", nRow);		//해외파생인출가능금액내용
			strECHM_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ECHM_PSBL_AMT_CTNS", nRow);			//환전가능금액내용
			strODRV_ORDR_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_ORDR_PSBL_AMT_CTNS", nRow);		//해외파생주문가능금액내용
			strODRV_ADIT_WMY_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_ADIT_WMY_CTNS", nRow);			//해외파생추가증거금내용
			strRCVB_OVDU_INTR_CTNS = m_CommAgent.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "RCVB_OVDU_INTR_CTNS", nRow);			//미수연체이자내용

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listDeposit.InsertItem(&lvItem);

			strCRRY_CD.Trim();
			NumericString(strODRV_STDR_EXRT_CTNS);
			NumericString(strBFDT_CSH_BLCE_CTNS);
			NumericString(strODRV_CSH_RCTM_AMT_CTNS);
			NumericString(strODRV_CSH_DRWG_AMT_CTNS);
			NumericString(strODRV_CLR_PFLS_AMT_CTNS);
			NumericString(strODRV_OPT_SELL_AMT_CTNS);
			NumericString(strODRV_OPT_BUY_AMT_CTNS);
			NumericString(strODRV_FEE_CTNS);
			NumericString(strTHDT_CSH_BLCE_CTNS);
			NumericString(strODRV_EVL_PFLS_AMT_CTNS);
			NumericString(strEVL_DPST_AMT_CTNS);
			NumericString(strODRV_OPT_EVL_AMT_CTNS);
			NumericString(strTOT_ACC_ASST_VALU_AMT_CTNS);
			NumericString(strOPNG_WMY_CTNS);
			NumericString(strODRV_ORDR_WMY_CTNS);
			NumericString(strODRV_MNTN_WMY_CTNS);
			NumericString(strWMY_LACK_AMT_CTNS);
			NumericString(strODRV_WDRW_PSBL_AMT_CTNS);
			NumericString(strECHM_PSBL_AMT_CTNS);
			NumericString(strODRV_ORDR_PSBL_AMT_CTNS);
			NumericString(strODRV_ADIT_WMY_CTNS);
			NumericString(strRCVB_OVDU_INTR_CTNS);

			m_listDeposit.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strCRRY_CD);
			m_listDeposit.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strODRV_STDR_EXRT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strBFDT_CSH_BLCE_CTNS);
			m_listDeposit.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strODRV_CSH_RCTM_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strODRV_CSH_DRWG_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strODRV_CLR_PFLS_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strODRV_OPT_SELL_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strODRV_OPT_BUY_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strODRV_FEE_CTNS);
			m_listDeposit.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strTHDT_CSH_BLCE_CTNS);
			m_listDeposit.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strODRV_EVL_PFLS_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strEVL_DPST_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strODRV_OPT_EVL_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strTOT_ACC_ASST_VALU_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strOPNG_WMY_CTNS);
			m_listDeposit.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strODRV_ORDR_WMY_CTNS);
			m_listDeposit.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strODRV_MNTN_WMY_CTNS);
			m_listDeposit.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strWMY_LACK_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strODRV_WDRW_PSBL_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strECHM_PSBL_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strODRV_ORDR_PSBL_AMT_CTNS);
			m_listDeposit.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strODRV_ADIT_WMY_CTNS);
			m_listDeposit.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strRCVB_OVDU_INTR_CTNS);

			nListIndex++;
		}

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
		CString strCANO, strCTNO, strAPNO, strCUST_NM, strPRDT_CD, strPRDT_NM, strODRV_SELL_BUY_DCD;
		CString strUSTL_CTRC_QNT, strTRDE_AVR_UNPR, strCLR_PSBL_QNT, strORDR_RMN_QNT, strODRV_NOW_PRC;
		CString strODRV_BFDT_PRPT, strODRV_BFDT_PRPT_RT, strODRV_EVL_AMT, strODRV_EVL_PFLS_AMT;
		CString strODRV_PFLS_RT, strUSTL_CTRC_AMT, strTRSL_MLT, strODRV_FTOP_DCD, strCRRY_CD;
		CString strMNGM_BDCD, strMNGM_BR_NM, strMNGM_EMPNO, strMNGR_NM, strPRC_DCPN_BLW_LNG;
		CString strINDC_PRC, strBSN_DT;

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

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OTS5919Q41_out_sub01");

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strCANO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CANO", nRow);		//종합계좌번호
			strCTNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CTNO", nRow);		//대체종합계좌번호
			strAPNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "APNO", nRow);		//계좌상품번호
			strCUST_NM = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CUST_NM", nRow);		//고객명
			strPRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "PRDT_CD", nRow);		//상품코드
			strPRDT_NM = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "PRDT_NM", nRow);		//상품명
			strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//해외파생매도매수구분코드
			strUSTL_CTRC_QNT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "USTL_CTRC_QNT", nRow);		//미결제약정수량
			strTRDE_AVR_UNPR = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "TRDE_AVR_UNPR", nRow);		//매매평균단가
			strCLR_PSBL_QNT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CLR_PSBL_QNT", nRow);		//청산가능수량
			strORDR_RMN_QNT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ORDR_RMN_QNT", nRow);		//주문잔여수량
			strODRV_NOW_PRC = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_NOW_PRC", nRow);		//해외파생현재가격
			strODRV_BFDT_PRPT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_BFDT_PRPT", nRow);		//해외파생전일대비
			strODRV_BFDT_PRPT_RT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_BFDT_PRPT_RT", nRow);		//해외파생전일대비율
			strODRV_EVL_AMT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_EVL_AMT", nRow);		//해외파생평가금액
			strODRV_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_EVL_PFLS_AMT", nRow);		//해외파생평가손익금액
			strODRV_PFLS_RT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_PFLS_RT", nRow);		//해외파생손익율
			strUSTL_CTRC_AMT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "USTL_CTRC_AMT", nRow);		//미결제약정금액
			strTRSL_MLT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "TRSL_MLT", nRow);		//환산승수
			strODRV_FTOP_DCD = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_FTOP_DCD", nRow);		//해외파생선물옵션구분코드
			strCRRY_CD = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CRRY_CD", nRow);		//통화코드
			strMNGM_BDCD = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "MNGM_BDCD", nRow);		//관리부점코드
			strMNGM_BR_NM = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "MNGM_BR_NM", nRow);		//관리지점명
			strMNGM_EMPNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "MNGM_EMPNO", nRow);		//관리사원번호
			strMNGR_NM = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "MNGR_NM", nRow);		//관리자명
			strPRC_DCPN_BLW_LNG = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "PRC_DCPN_BLW_LNG", nRow);		//가격소수점이하길이
			strINDC_PRC = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "INDC_PRC", nRow);		//표시가격
			strBSN_DT = m_CommAgent.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "BSN_DT", nRow);		//영업일자


			strCANO.Trim();
			strCTNO.Trim();
			strAPNO.Trim();
			strCUST_NM.Trim();
			strPRDT_CD.Trim();
			strPRDT_NM.Trim();
			strODRV_SELL_BUY_DCD.Trim();
			NumericString(strUSTL_CTRC_QNT);		//미결제약정수량
			NumericString(strTRDE_AVR_UNPR);		//매매평균단가
			NumericString(strCLR_PSBL_QNT);		//청산가능수량
			NumericString(strORDR_RMN_QNT);		//주문잔여수량
			NumericString(strODRV_NOW_PRC);		//해외파생현재가격
			NumericString(strODRV_BFDT_PRPT);		//해외파생전일대비
			NumericString(strODRV_BFDT_PRPT_RT);		//해외파생전일대비율
			NumericString(strODRV_EVL_AMT);		//해외파생평가금액
			NumericString(strODRV_EVL_PFLS_AMT);		//해외파생평가손익금액
			NumericString(strODRV_PFLS_RT);		//해외파생손익율
			NumericString(strUSTL_CTRC_AMT);		//미결제약정금액
			NumericString(strTRSL_MLT);		//환산승수
			strODRV_FTOP_DCD.Trim();		//해외파생선물옵션구분코드
			strCRRY_CD.Trim();		//통화코드
			strMNGM_BDCD.Trim();		//관리부점코드
			strMNGM_BR_NM.Trim();		//관리지점명
			strMNGM_EMPNO.Trim();		//관리사원번호
			strMNGR_NM.Trim();		//관리자명
			NumericString(strPRC_DCPN_BLW_LNG);		//가격소수점이하길이
			NumericString(strINDC_PRC);		//표시가격
			strBSN_DT.Trim();		//영업일자

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listBalance.InsertItem(&lvItem);

			m_listBalance.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strCANO);		//종합계좌번호
			m_listBalance.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strCTNO);		//대체종합계좌번호
			m_listBalance.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strAPNO);		//계좌상품번호
			m_listBalance.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strCUST_NM);		//고객명
			m_listBalance.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strPRDT_CD);		//상품코드
			m_listBalance.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strPRDT_NM);		//상품명
			m_listBalance.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드
			m_listBalance.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strUSTL_CTRC_QNT);		//미결제약정수량
			m_listBalance.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strTRDE_AVR_UNPR);		//매매평균단가
			m_listBalance.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strCLR_PSBL_QNT);		//청산가능수량
			m_listBalance.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strORDR_RMN_QNT);		//주문잔여수량
			m_listBalance.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strODRV_NOW_PRC);		//해외파생현재가격
			m_listBalance.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strODRV_BFDT_PRPT);		//해외파생전일대비
			m_listBalance.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strODRV_BFDT_PRPT_RT);		//해외파생전일대비율
			m_listBalance.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strODRV_EVL_AMT);		//해외파생평가금액
			m_listBalance.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strODRV_EVL_PFLS_AMT);		//해외파생평가손익금액
			m_listBalance.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strODRV_PFLS_RT);		//해외파생손익율
			m_listBalance.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strUSTL_CTRC_AMT);		//미결제약정금액
			m_listBalance.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strTRSL_MLT);		//환산승수
			m_listBalance.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strODRV_FTOP_DCD);		//해외파생선물옵션구분코드
			m_listBalance.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strCRRY_CD);		//통화코드
			m_listBalance.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strMNGM_BDCD);		//관리부점코드
			m_listBalance.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strMNGM_BR_NM);		//관리지점명
			m_listBalance.SetItemText(nListIndex, 23, (LPTSTR)(LPCTSTR)strMNGM_EMPNO);		//관리사원번호
			m_listBalance.SetItemText(nListIndex, 24, (LPTSTR)(LPCTSTR)strMNGR_NM);		//관리자명
			m_listBalance.SetItemText(nListIndex, 25, (LPTSTR)(LPCTSTR)strPRC_DCPN_BLW_LNG);		//가격소수점이하길이
			m_listBalance.SetItemText(nListIndex, 26, (LPTSTR)(LPCTSTR)strINDC_PRC);		//표시가격
			m_listBalance.SetItemText(nListIndex, 27, (LPTSTR)(LPCTSTR)strBSN_DT);		//영업일자

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
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U01_out", "ODRV_ODNO", 0);		//해외파생주문번호
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
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U01_out", "ODRV_ODNO", 0);		//해외파생주문번호
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
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U02_out", "ODRV_ODNO", 0);		//해외파생주문번호
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
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5901U03_out", "ODRV_ODNO", 0);		//해외파생주문번호
		strODRV_ODNO.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdCancelOrd = 0;
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
void CFFutOptOrdDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
void CFFutOptOrdDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/*	주의 : OnGetRealData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
		이벤트 콜백함수 종료 후에는 유효하지 않습니다.*/
	CString strRealMessage;

	/***************************************
	 * 해외선물체결확인
	 ****************************************/
	if (!_tcscmp(strRealName, "EF1"))
	{
		/*--------------------------------------
		 아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
		 ---------------------------------------*/
		CString strrltm_dpch_dcd	= m_CommAgent.GetRealOutputData(strRealName, "rltm_dpch_dcd");		//실시간통보구분코드
		CString strusr_id	= m_CommAgent.GetRealOutputData(strRealName, "usr_id");		//사용자ID
		CString strrltm_dpch_prcs_dcd = m_CommAgent.GetRealOutputData(strRealName, "rltm_dpch_prcs_dcd");		//실시간통보처리구분코드
		CString strcano = m_CommAgent.GetRealOutputData(strRealName, "cano");		//종합계좌번호
		CString strctno = m_CommAgent.GetRealOutputData(strRealName, "ctno");		//대체종합계좌번호
		CString strapno = m_CommAgent.GetRealOutputData(strRealName, "apno");		//계좌상품번호
		CString strprdt_cd = m_CommAgent.GetRealOutputData(strRealName, "prdt_cd");		//상품코드
		CString strodrv_ordr_tp_dcd = m_CommAgent.GetRealOutputData(strRealName, "odrv_ordr_tp_dcd");		//해외파생주문유형구분코드
		CString strordr_stts_dcd = m_CommAgent.GetRealOutputData(strRealName, "ordr_stts_dcd");		//주문상태구분코드
		CString strodrv_odno = m_CommAgent.GetRealOutputData(strRealName, "odrv_odno");		//해외파생주문번호
		CString strodrv_or_odno = m_CommAgent.GetRealOutputData(strRealName, "odrv_or_odno");		//해외파생원주문번호
		CString strordr_dt = m_CommAgent.GetRealOutputData(strRealName, "ordr_dt");		//주문일자
		CString strcust_nm = m_CommAgent.GetRealOutputData(strRealName, "cust_nm");		//고객명
		CString strodrv_sell_buy_dcd = m_CommAgent.GetRealOutputData(strRealName, "odrv_sell_buy_dcd");		//해외파생매도매수구분코드
		CString strodrv_ordr_prc_ctns = m_CommAgent.GetRealOutputData(strRealName, "odrv_ordr_prc_ctns");		//해외파생주문가격내용
		CString strordr_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "ordr_qnt_ctns");		//주문수량내용
		CString strodrv_prc_dcd = m_CommAgent.GetRealOutputData(strRealName, "odrv_prc_dcd");		//해외파생가격구분코드
		CString strcncs_cnd_dcd = m_CommAgent.GetRealOutputData(strRealName, "cncs_cnd_dcd");		//체결조건구분코드
		CString strcnd_prc_ctns = m_CommAgent.GetRealOutputData(strRealName, "cnd_prc_ctns");		//조건가격내용
		CString strcomm_mdia_dcd = m_CommAgent.GetRealOutputData(strRealName, "comm_mdia_dcd");		//통신매체구분코드
		CString stracpt_tm = m_CommAgent.GetRealOutputData(strRealName, "acpt_tm");		//접수시각
		CString strexcg_cncs_tm = m_CommAgent.GetRealOutputData(strRealName, "excg_cncs_tm");		//거래소체결시각
		CString stracpl_acpt_tm = m_CommAgent.GetRealOutputData(strRealName, "acpl_acpt_tm");		//현지접수시각
		CString strcncs_tm = m_CommAgent.GetRealOutputData(strRealName, "cncs_tm");		//체결시각
		CString strcncs_dt = m_CommAgent.GetRealOutputData(strRealName, "cncs_dt");		//체결일자
		CString strodrv_cncs_no = m_CommAgent.GetRealOutputData(strRealName, "odrv_cncs_no");		//해외파생체결번호
		CString strcncs_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "cncs_qnt_ctns");		//체결수량내용
		CString strodrv_cncs_prc_ctns = m_CommAgent.GetRealOutputData(strRealName, "odrv_cncs_prc_ctns");		//해외파생체결가격내용
		CString strodrv_cncs_amt_ctns = m_CommAgent.GetRealOutputData(strRealName, "odrv_cncs_amt_ctns");		//해외파생체결금액내용
		CString strcrry_cd = m_CommAgent.GetRealOutputData(strRealName, "crry_cd");		//통화코드
		CString strordr_rmn_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "ordr_rmn_qnt_ctns");		//주문잔여수량내용
		CString stracnt_dcd = m_CommAgent.GetRealOutputData(strRealName, "acnt_dcd");		//계좌구분코드
		CString strentr_clr_dcd = m_CommAgent.GetRealOutputData(strRealName, "entr_clr_dcd");		//진입청산구분코드
		CString strclr_pst_no = m_CommAgent.GetRealOutputData(strRealName, "clr_pst_no");		//청산포지션번호

		strrltm_dpch_dcd.Trim();
		strusr_id.Trim();
		strrltm_dpch_prcs_dcd.Trim();
		strcano.Trim();
		strctno.Trim();
		strapno.Trim();
		strprdt_cd.Trim();
		strodrv_ordr_tp_dcd.Trim();
		strordr_stts_dcd.Trim();
		strodrv_odno.Trim();
		strodrv_or_odno.Trim();
		strordr_dt.Trim();
		strcust_nm.Trim();
		strodrv_sell_buy_dcd.Trim();
		strodrv_ordr_prc_ctns.Trim();
		strordr_qnt_ctns.Trim();
		strodrv_prc_dcd.Trim();
		strcncs_cnd_dcd.Trim();
		strcnd_prc_ctns.Trim();
		strcomm_mdia_dcd.Trim();
		stracpt_tm.Trim();
		strexcg_cncs_tm.Trim();
		stracpl_acpt_tm.Trim();
		strcncs_tm.Trim();
		strcncs_dt.Trim();
		strodrv_cncs_no.Trim();
		strcncs_qnt_ctns.Trim();
		strodrv_cncs_prc_ctns.Trim();
		strodrv_cncs_amt_ctns.Trim();
		strcrry_cd.Trim();
		strordr_rmn_qnt_ctns.Trim();
		stracnt_dcd.Trim();
		strentr_clr_dcd.Trim();
		strclr_pst_no.Trim();

		/*--------------------------------------
		조회 시점에 등록한 주식 현재가 실시간키와 동일한지 비교
		---------------------------------------*/
		if (m_strLoginID == strRealKey)
		{
			strRealMessage.Format("[%s][계좌:%s][상품:%s][체결:%s]", strRealName, strcano, strprdt_cd, strcncs_qnt_ctns);
		}//End of if

	}
	/***************************************
	* 해외선물미체결
	****************************************/
	else if (!_tcscmp(strRealName, "EF4"))
	{
		CString strrltm_dpch_dcd = m_CommAgent.GetRealOutputData(strRealName, "rltm_dpch_dcd");		//실시간통보구분코드
		CString strusr_id = m_CommAgent.GetRealOutputData(strRealName, "usr_id");		//사용자ID
		CString strrltm_dpch_prcs_dcd = m_CommAgent.GetRealOutputData(strRealName, "rltm_dpch_prcs_dcd");		//실시간통보처리구분코드
		CString strcano = m_CommAgent.GetRealOutputData(strRealName, "cano");		//종합계좌번호
		CString strctno = m_CommAgent.GetRealOutputData(strRealName, "ctno");		//대체종합계좌번호
		CString strapno = m_CommAgent.GetRealOutputData(strRealName, "apno");		//계좌상품번호
		CString strodrv_odno = m_CommAgent.GetRealOutputData(strRealName, "odrv_odno");		//해외파생주문번호
		CString strprdt_cd = m_CommAgent.GetRealOutputData(strRealName, "prdt_cd");		//상품코드
		CString strodrv_or_odno = m_CommAgent.GetRealOutputData(strRealName, "odrv_or_odno");		//해외파생원주문번호
		CString strodrv_mo_odno = m_CommAgent.GetRealOutputData(strRealName, "odrv_mo_odno");		//해외파생모주문번호
		CString strordr_grup_no = m_CommAgent.GetRealOutputData(strRealName, "ordr_grup_no");		//주문그룹번호
		CString strordr_dt = m_CommAgent.GetRealOutputData(strRealName, "ordr_dt");		//주문일자
		CString strcust_nm = m_CommAgent.GetRealOutputData(strRealName, "cust_nm");		//고객명
		CString strodrv_sell_buy_dcd = m_CommAgent.GetRealOutputData(strRealName, "odrv_sell_buy_dcd");		//해외파생매도매수구분코드
		CString strodrv_ordr_prc_ctns = m_CommAgent.GetRealOutputData(strRealName, "odrv_ordr_prc_ctns");		//해외파생주문가격내용
		CString strordr_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "ordr_qnt_ctns");		//주문수량내용
		CString strrvse_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "rvse_qnt_ctns");		//정정수량내용
		CString strcncl_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "cncl_qnt_ctns");		//취소수량내용
		CString strcncs_qnt_smm_ctns = m_CommAgent.GetRealOutputData(strRealName, "cncs_qnt_smm_ctns");		//체결수량합계내용
		CString strordr_rmn_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "ordr_rmn_qnt_ctns");		//주문잔여수량내용
		CString strodrv_prc_dcd = m_CommAgent.GetRealOutputData(strRealName, "odrv_prc_dcd");		//해외파생가격구분코드
		CString strcncs_cnd_dcd = m_CommAgent.GetRealOutputData(strRealName, "cncs_cnd_dcd");		//체결조건구분코드
		CString strcnd_prc_ctns = m_CommAgent.GetRealOutputData(strRealName, "cnd_prc_ctns");		//조건가격내용
		CString stravr_cncs_prc_ctns = m_CommAgent.GetRealOutputData(strRealName, "avr_cncs_prc_ctns");		//평균체결가격내용
		CString strodrv_pv_ctns = m_CommAgent.GetRealOutputData(strRealName, "odrv_pv_ctns");		//해외파생현재가내용
		CString strcncs_rt_ctns = m_CommAgent.GetRealOutputData(strRealName, "cncs_rt_ctns");		//체결율내용
		CString strcomm_mdia_dcd = m_CommAgent.GetRealOutputData(strRealName, "comm_mdia_dcd");		//통신매체구분코드
		CString strodrv_ordr_tp_dcd = m_CommAgent.GetRealOutputData(strRealName, "odrv_ordr_tp_dcd");		//해외파생주문유형구분코드
		CString strordr_stts_dcd = m_CommAgent.GetRealOutputData(strRealName, "ordr_stts_dcd");		//주문상태구분코드
		CString strfcm_odno = m_CommAgent.GetRealOutputData(strRealName, "fcm_odno");		//FCM주문번호
		CString strathz_ip_addr = m_CommAgent.GetRealOutputData(strRealName, "athz_ip_addr");		//공인IP주소
		CString stracpt_tm = m_CommAgent.GetRealOutputData(strRealName, "acpt_tm");		//접수시각
		CString strexcg_cncs_tm = m_CommAgent.GetRealOutputData(strRealName, "excg_cncs_tm");		//거래소체결시각
		CString stracpl_acpt_tm = m_CommAgent.GetRealOutputData(strRealName, "acpl_acpt_tm");		//현지접수시각
		CString strcncs_tm = m_CommAgent.GetRealOutputData(strRealName, "cncs_tm");		//체결시각
		CString strcrry_cd = m_CommAgent.GetRealOutputData(strRealName, "crry_cd");		//통화코드
		CString strcncs_qnt_ctns = m_CommAgent.GetRealOutputData(strRealName, "cncs_qnt_ctns");		//체결수량내용
		CString strordr_expr_dt = m_CommAgent.GetRealOutputData(strRealName, "ordr_expr_dt");		//주문만료일자
		CString stracnt_dcd = m_CommAgent.GetRealOutputData(strRealName, "acnt_dcd");		//계좌구분코드
		CString strentr_clr_dcd = m_CommAgent.GetRealOutputData(strRealName, "entr_clr_dcd");		//진입청산구분코드
		CString strclr_pst_no = m_CommAgent.GetRealOutputData(strRealName, "clr_pst_no");		//청산포지션번호
		
		strrltm_dpch_dcd.Trim();
		strusr_id.Trim();
		strrltm_dpch_prcs_dcd.Trim();
		strcano.Trim();
		strctno.Trim();
		strapno.Trim();
		strodrv_odno.Trim();
		strprdt_cd.Trim();
		strodrv_or_odno.Trim();
		strodrv_mo_odno.Trim();
		strordr_grup_no.Trim();
		strordr_dt.Trim();
		strcust_nm.Trim();
		strodrv_sell_buy_dcd.Trim();
		strodrv_ordr_prc_ctns.Trim();
		strordr_qnt_ctns.Trim();
		strrvse_qnt_ctns.Trim();
		strcncl_qnt_ctns.Trim();
		strcncs_qnt_smm_ctns.Trim();
		strordr_rmn_qnt_ctns.Trim();
		strodrv_prc_dcd.Trim();
		strcncs_cnd_dcd.Trim();
		strcnd_prc_ctns.Trim();
		stravr_cncs_prc_ctns.Trim();
		strodrv_pv_ctns.Trim();
		strcncs_rt_ctns.Trim();
		strcomm_mdia_dcd.Trim();
		strodrv_ordr_tp_dcd.Trim();
		strordr_stts_dcd.Trim();
		strfcm_odno.Trim();
		strathz_ip_addr.Trim();
		stracpt_tm.Trim();
		strexcg_cncs_tm.Trim();
		stracpl_acpt_tm.Trim();
		strcncs_tm.Trim();
		strcrry_cd.Trim();
		strcncs_qnt_ctns.Trim();
		strordr_expr_dt.Trim();
		stracnt_dcd.Trim();
		strentr_clr_dcd.Trim();
		strclr_pst_no.Trim();

		/*--------------------------------------
		조회 시점에 등록한 주식 현재가 실시간키와 동일한지 비교
		---------------------------------------*/
		if (m_strLoginID == strRealKey)
		{
			strRealMessage.Format("[%s][주문상태:%s][계좌:%s][상품:%s][주문수:%s][정정수:%s][취소수:%s]",
								  strRealName, strordr_stts_dcd, strcano, strprdt_cd, strordr_qnt_ctns, strrvse_qnt_ctns, strcncl_qnt_ctns);
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
void CFFutOptOrdDlg::OnAgentEventHandler(long nEventType, long nParam, LPCTSTR strParam)
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

void CFFutOptOrdDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (int i = 0; i < 100; i++)
	{
		OnBnClickedBtnReqDeposit();
	}
}
