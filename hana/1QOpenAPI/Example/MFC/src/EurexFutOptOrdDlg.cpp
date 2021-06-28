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
#include "EurexFutOptOrdDlg.h"

#define ID_SECOND_TIMER		100	//1초 간격 타이머

#define SELL_BK_COLOR		RGB(206, 232, 255)	//매도 배경색
#define BUY_BK_COLOR		RGB(251, 221, 255)	//매수 배경색

//통신 구조체 헤더

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern void NumericString(CString& strValue, BOOL bNotDisplayZero = FALSE);

static char* g_szOrderType[] = { "01", "03" }; //호가구분 : 01:지정가, 03:시장가
static char g_cPriceCont[3] = { ' ' , 'I', 'F' };	//주문조건 : 없음, IOC, FOK

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

// CEurexFutOptOrdDlg 대화 상자
CEurexFutOptOrdDlg::CEurexFutOptOrdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEurexFutOptOrdDlg::IDD, pParent)
{
	m_bCommConnect		= FALSE;

	m_nRqIdAccNoList		= 0;	//계좌조회 Request ID
	m_nRqIdFDemoAccNoList	= 0;	//해외모의 계좌조회 Request ID

	m_nRqIdSellOrd			= 0;	//매도주문 Request ID
	m_nRqIdBuyOrd			= 0;	//매수주문 Request ID
	m_nRqIdChangeOrd		= 0;	//정정주문 Request ID
	m_nRqIdCancelOrd		= 0;	//취소주문 Request ID

	m_nRqIdExecList			= 0;	//주문체결(미체결)내역 Request ID
	m_nRqIdDepositList		= 0;	//예수금내역 Request ID

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_nSeverType			= 0;	//0-리얼, 1-국내모의, 2-해외무의

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEurexFutOptOrdDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_CMB_ORD_COND, m_cmbOrdCond);
	DDX_Control(pDX, IDC_DATETIME2, m_dateTime2);
	DDX_Control(pDX, IDC_DATETIME3, m_dateTime3);
}

BEGIN_MESSAGE_MAP(CEurexFutOptOrdDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_LOGIN, &CEurexFutOptOrdDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_LOGOUT, &CEurexFutOptOrdDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDOK, &CEurexFutOptOrdDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELL, &CEurexFutOptOrdDlg::OnBnClickedBtnSell)
	ON_BN_CLICKED(IDC_BTN_BUY, &CEurexFutOptOrdDlg::OnBnClickedBtnBuy)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CEurexFutOptOrdDlg::OnBnClickedBtnChange)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CEurexFutOptOrdDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST, &CEurexFutOptOrdDlg::OnBnClickedBtnReqExecList)
	ON_BN_CLICKED(IDC_BTN_REQ_EXEC_LIST_NEXT, &CEurexFutOptOrdDlg::OnBnClickedBtnReqExecListNext)
	ON_BN_CLICKED(IDC_BTN_REQ_ACCNO, &CEurexFutOptOrdDlg::OnBnClickedBtnReqAccno)
	ON_BN_CLICKED(IDC_BTN_REQ_DEPOSIT, &CEurexFutOptOrdDlg::OnBnClickedBtnReqDeposit)
	ON_BN_CLICKED(IDC_BTN_REQ_BALANCE, &CEurexFutOptOrdDlg::OnBnClickedBtnReqBalance)
	ON_BN_CLICKED(IDC_BTN_LOAD_USER_ACC, &CEurexFutOptOrdDlg::OnBnClickedBtnLoadUserAcc)
	ON_COMMAND_RANGE(IDC_CON_REAL, IDC_CON_F_DEMO, &CEurexFutOptOrdDlg::OnRdoSelectServer)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCNO, &CEurexFutOptOrdDlg::OnNMDblclkListAccNo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ORD, &CEurexFutOptOrdDlg::OnNMDblclkListExec)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BALANCE, &CEurexFutOptOrdDlg::OnNMDblclkListBalance)

	ON_BN_CLICKED(IDC_BUTTON_TEST, &CEurexFutOptOrdDlg::OnBnClickedButtonTest)
END_MESSAGE_MAP()

// agent로부터 이벤트 수신 함수를 정의한다.
BEGIN_EVENTSINK_MAP(CEurexFutOptOrdDlg, CDialog)
	ON_EVENT(CEurexFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 1, CEurexFutOptOrdDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CEurexFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 2, CEurexFutOptOrdDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CEurexFutOptOrdDlg, IDC_HFCOMMAGENTCTRL1, 3, CEurexFutOptOrdDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
END_EVENTSINK_MAP()

// CEurexFutOptOrdDlg 메시지 처리기
void CEurexFutOptOrdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
void CEurexFutOptOrdDlg::OnPaint()
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
HCURSOR CEurexFutOptOrdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CEurexFutOptOrdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CEurexFutOptOrdDlg::OnNMDblclkListAccNo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	
	CString strAccNo = m_listAccNo.GetItemText(nSelectRow, 0);
	CString strPrdtNo = m_listAccNo.GetItemText(nSelectRow, 2);

	GetDlgItem(IDC_EDIT_ACCNO)->SetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->SetWindowText(strPrdtNo);
}

void CEurexFutOptOrdDlg::OnNMDblclkListExec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;

	CString strOrdOrg = m_listExec.GetItemText(nSelectRow, 4);
	CString strSymbol = m_listExec.GetItemText(nSelectRow, 5);
	CString strOrdPrice = m_listExec.GetItemText(nSelectRow, 9);
	CString strOrdSu = m_listExec.GetItemText(nSelectRow, 10);

	GetDlgItem(IDC_EDIT_ORG_NO)->SetWindowText(strOrdOrg);
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);
	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);
}

void CEurexFutOptOrdDlg::OnNMDblclkListBalance(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	
	CString strSymbol = m_listBalance.GetItemText(nSelectRow, 0);
	CString strOrdPrice = m_listBalance.GetItemText(nSelectRow, 6);
	CString strOrdSu = m_listBalance.GetItemText(nSelectRow, 10);
	
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strSymbol);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strOrdPrice);
	GetDlgItem(IDC_EDIT_ORD_VOL)->SetWindowText(strOrdSu);
}

void CEurexFutOptOrdDlg::OnDestroy()
{
	//모든 실시간등록을 해제한다.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();
	
	CDialog::OnDestroy();
}

void CEurexFutOptOrdDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CEurexFutOptOrdDlg::OnTimer(UINT_PTR nIDEvent)
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
void CEurexFutOptOrdDlg::OnRdoSelectServer(UINT nID)
{
	m_nSeverType = nID - IDC_CON_REAL;

	/*----------------------------------
	  접속서버를 설정한다.(0 - 리얼, 1 - 국내모의, 2 - 해외모의)
	 *----------------------------------*/
	m_CommAgent.SetLoginMode(0, m_nSeverType);
}

//*******************************************************************
// Function Name : OnInitDialog
// Function      : 다이얼로그 초기화
// Param         : 
// Return        : BOOL 
// Create        : 
// Comment       : 
//******************************************************************
BOOL CEurexFutOptOrdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CString strTitle;
	strTitle.Format("%s-[야간선옵 주문](%s)", PROGRAM_NAME, VERSION_INFO);
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
	InitListExec();		//주문체결
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

	((CButton*)GetDlgItem(IDC_CHK_AllQty))->SetCheck(1);

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
void CEurexFutOptOrdDlg::InitListAccNo()
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
void CEurexFutOptOrdDlg::InitListReal()
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
// Function Name : InitListExec
// Function      : 
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CEurexFutOptOrdDlg::InitListExec()
{
	CRect rc;
	m_listExec.GetClientRect(rc);
	m_listExec.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("관리부점코드"), _T("관리부점명"), _T("모주문일련번호"), _T("주문일련번호"),
		_T("원주문일련번호"), _T("상품코드"), _T("상품명"), _T("파생상품호가구분코드"), _T("파생상품호가구분명"),
		_T("주문가격내용"), _T("주문수량"), _T("체결구분명"), _T("체결가격내용"), _T("체결수량"),
		_T("체결상세시각"), _T("미체결수량"), _T("파생상품호가접수구분코드"), _T("파생상품호가접수구분명"),
		_T("조작상세일시"), _T("한국거래소메시지번호"), _T("체결일련번호"), _T("외부기관거부사유코드"), _T("통신매체구분코드") };

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
void CEurexFutOptOrdDlg::InitListBalance()
{
	CRect rc;
	m_listBalance.GetClientRect(rc);
	m_listBalance.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("상품코드"), _T("상품명"), _T("매매구분코드"), _T("매매구분명"),
						_T("미결제약정수량"), _T("평균가격"), _T("현재가격"), _T("평가금액"), _T("평가손익금액"),
						_T("손익율"), _T("청산가능수량"), _T("매입장부금액") };

	int i;
	for (i = 0; i < 12; i++)
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
void CEurexFutOptOrdDlg::OnBnClickedLogin()
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
	//주문확인/체결/미체결(정정/취소) 실시간 통보
	m_CommAgent.RegisterReal("EF5", m_strLoginID);
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : 로그아웃
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CEurexFutOptOrdDlg::OnBnClickedLogout()
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
void CEurexFutOptOrdDlg::OnBnClickedOk()
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
void CEurexFutOptOrdDlg::OnBnClickedBtnReqAccno()
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
void CEurexFutOptOrdDlg::OnBnClickedBtnLoadUserAcc()
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

		strAPNO = GetAccAPNO(strAccNo + strPrdtNo); //종합계좌대체번호 얻어오기

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
CString CEurexFutOptOrdDlg::GetAccAPNO(CString strAccNo)
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
void CEurexFutOptOrdDlg::RequestAccList()
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
void CEurexFutOptOrdDlg::RequestFDemoAccList()
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
// Param         : CString strDealSide
// Return        : void 
// Create        : 
// Comment       : 매수/매도 주문 전송
//******************************************************************
BOOL CEurexFutOptOrdDlg::SendSellBuyOrder(CString strDealSide, int nRqId)
{
	CString strInRecName;
	CString strTrCode;
	
	//입력항목 변수들
	CString strCTNO;					//대체종합계좌번호
	CString strAPNO;					//계좌상품번호
	CString strACNT_PWD;				//비밀번호
	CString strSELL_BUY_DCD;			//상품코드
	CString strPRDT_CD;					//매도매수구분코드
	CString strDRVS_NMPR_DCD;			//가격조건구분코드
	CString strORDR_PRC;				//주문가격
	CString strORDR_QNT;				//주문수량
	CString strPWD_CNFM_YN("Y");		//비밀번호확인여부
	CString strCVRG_YN("N");			//반대매매여부
	CString strDRVS_ORDR_CND_DCD;		//주문조건(' ' : 없음, 'I' : IOC, 'F' : FOK)
	CString strDFRT_HDGE_DCD("00");		//차익헷지구분코드

	strTrCode = "OTS2850U30";

	if (strDealSide == "S") //매도
		strSELL_BUY_DCD = "1";
	else if (strDealSide == "B") //매수
		strSELL_BUY_DCD = "2";

	strInRecName.Format("%s_in", strTrCode);		//입력 레코드명(리소스파일 참고)

	CString strAccNo;
	CString strAccPwd;

	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//계좌상품번호

	strCTNO = GetAccAPNO(strAccNo + strAPNO); //종합계좌대체번호 얻어오기

	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strAccPwd);			//비밀번호
	strACNT_PWD = m_CommAgent.GetEncrpyt(strAccPwd);				//계좌비밀번호는 단방향 암호화를 해야된다.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//상품코드

	if (m_cmdOrdType.GetCurSel() >= 0)
		strDRVS_NMPR_DCD = g_szOrderType[m_cmdOrdType.GetCurSel()];	//파생상품호가구분코드

	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strORDR_PRC);		//주문가격
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);		//주문수량

	if(m_cmbOrdCond.GetCurSel() >= 0)
		strDRVS_ORDR_CND_DCD.Format("%c", g_cPriceCont[m_cmbOrdCond.GetCurSel()]);//주문조건(' ' : 없음, 'I' : IOC, 'F' : FOK)

	//[2] Tran조회 입력값을 입력한다.
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "CTNO", strCTNO);					//대체종합계좌번호
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "APNO", strAPNO);					//계좌상품번호
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);			//비밀번호
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);	//상품코드
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);			//매도매수구분코드
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "DRVS_NMPR_DCD", strDRVS_NMPR_DCD);//가격조건구분코드
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_PRC", strORDR_PRC);			//주문가격
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);			//주문수량
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "PWD_CNFM_YN", strPWD_CNFM_YN);	//비밀번호확인여부
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "CVRG_YN", strCVRG_YN);			//반대매매여부
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "DRVS_ORDR_CND_DCD", strDRVS_ORDR_CND_DCD);	//주문조건(' ' : 없음, 'I' : IOC, 'F' : FOK)
	m_CommAgent.SetTranInputData(nRqId, strTrCode, strInRecName, "DFRT_HDGE_DCD", strDFRT_HDGE_DCD);	//차익헷지구분코드
	

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	
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
void CEurexFutOptOrdDlg::OnBnClickedBtnSell()
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
void CEurexFutOptOrdDlg::OnBnClickedBtnBuy()
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
void CEurexFutOptOrdDlg::OnBnClickedBtnChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS2850U32";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS2850U32_in";	//입력 레코드명(리소스파일 참고)
	
	//[1] Request ID생성
	m_nRqIdChangeOrd = m_CommAgent.CreateRequestID();

	//[2] Tran조회 입력값을 입력한다.
	CString strCTNO;				//종합계좌대체번호
	CString strAPNO;				//계좌상품번호
	CString strACNT_PWD;			//계좌비밀번호
	CString strOR_ORDR_SN;			//원주문일련번호
	CString strDRVS_NMPR_DCD;		//파생상품호가구분코드
	CString strORDR_PRC;			//주문가격
	CString strORDR_QNT;			//주문수량
	CString strALL_YN;				//전체여부
	CString strDRVS_ORDR_CND_DCD;	//파생상품주문조건구분코드
	CString strPWD_CNFM_YN("Y");	//비밀번호확인여부
	CString strCVRG_YN("N");		//반대매매여부
	CString strDFRT_HDGE_DCD("00");	//차익헷지구분코드
	
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//계좌상품번호

	strCTNO = GetAccAPNO(strCTNO + strAPNO);						//종합계좌대체번호 얻어오기

	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);		//비밀번호
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);				//계좌비밀번호는 단방향 암호화를 해야된다.

	//원주문번호
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strOR_ORDR_SN);

	//가격조건구분코드
	if (m_cmdOrdType.GetCurSel() >= 0)
		strDRVS_NMPR_DCD = g_szOrderType[m_cmdOrdType.GetCurSel()];

	//정정가격
	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strORDR_PRC);

	//정정수량
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	//전체여부
	if (((CButton*)GetDlgItem(IDC_CHK_AllQty))->GetCheck() == 1)
		strALL_YN = "Y";
	else
		strALL_YN = "N";

	//주문조건(' ' : 없음, 'I' : IOC, 'F' : FOK)
	if (m_cmbOrdCond.GetCurSel() >= 0)
		strDRVS_ORDR_CND_DCD.Format("%c", g_cPriceCont[m_cmbOrdCond.GetCurSel()]);

	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "CTNO", strCTNO);					//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "APNO", strAPNO);					//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);			//계좌비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "OR_ORDR_SN", strOR_ORDR_SN);		//원주문일련번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "DRVS_NMPR_DCD", strDRVS_NMPR_DCD);	//파생상품호가구분코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_PRC", strORDR_PRC);			//주문가격
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);			//주문수량
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ALL_YN", strALL_YN);				//전체여부
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "DRVS_ORDR_CND_DCD", strDRVS_ORDR_CND_DCD);	//파생상품주문조건구분코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PWD_CNFM_YN", strPWD_CNFM_YN);		//비밀번호확인여부
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "CVRG_YN", strCVRG_YN);				//반대매매여부
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "DFRT_HDGE_DCD", strDFRT_HDGE_DCD);	//차익헷지구분코드

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	
	//[3] 서버에 Tran조회 요청한다.
	if (m_CommAgent.RequestTran(m_nRqIdChangeOrd, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", 0) < 0)
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
void CEurexFutOptOrdDlg::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS2850U33";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS2850U33_in ";	//입력 레코드명(리소스파일 참고)

	//[1] Request ID생성
	m_nRqIdCancelOrd = m_CommAgent.CreateRequestID();

	//[2] Tran조회 입력값을 입력한다.
	CString strCTNO;			//종합계좌대체번호
	CString strAPNO;			//계좌상품번호
	CString strACNT_PWD;		//계좌비밀번호
	CString strOR_ORDR_SN;		//원주문일련번호
	CString strORDR_QNT;		//주문수량
	CString strORDR_PRC;		//주문가격
	CString strALL_YN;			//전체여부
	CString strPWD_CNFM_YN("Y");//비밀번호확인여부
	CString strDFRT_HDGE_DCD("00");	//차익헷지구분코드

	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//대체종합계좌번호

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //종합계좌대체번호 얻어오기

	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);		//비밀번호
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);				//계좌비밀번호는 단방향 암호화를 해야된다.

	//원주문번호
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strOR_ORDR_SN);

	//취소수량
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	//주문가격
	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strORDR_PRC);

	//전체여부
	if (((CButton*)GetDlgItem(IDC_CHK_AllQty))->GetCheck() == 1)
		strALL_YN = "Y";
	else
		strALL_YN = "N";

	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "APNO", strAPNO);				//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "OR_ORDR_SN", strOR_ORDR_SN);	//원주문일련번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);		//주문수량
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ORDR_PRC", strORDR_PRC);			//주문가격
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ALL_YN", strALL_YN);			//전체여부
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "PWD_CNFM_YN", strPWD_CNFM_YN);	//비밀번호확인여부
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "DFRT_HDGE_DCD", strDFRT_HDGE_DCD);	//차익헷지구분코드

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	
	//[3] 서버에 Tran조회 요청한다.
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
void CEurexFutOptOrdDlg::OnBnClickedBtnReqDeposit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}
	
	GetDlgItem(IDC_EDIT_DEPOSIT)->SetWindowText("");

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS2850Q17";				//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS2850Q17_in";			//입력 레코드명(리소스파일 참고)

	/*-------------------------------*
	 [1] Request ID생성
	*-------------------------------*/
	m_nRqIdDepositList = m_CommAgent.CreateRequestID();

	CString strCTNO;			//종합계좌대체번호
	CString strAPNO;			//계좌상품번호
	CString strPWD;				//비밀번호
	CString strINQ_DT;			//조회일자
	
	//계좌번호
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	
	//계좌상품번호
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //종합계좌대체번호 얻어오기

	//계좌비번
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD); //암호화한다.


	/*-------------------------------*
	 [2] Tran조회 입력값을 입력한다.
	 *-------------------------------*/
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "CTNO", strCTNO);			//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "APNO", strAPNO);			//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "PWD", strPWD);			//비밀번호

	CString strBenefitAcc	= "N";		//수익증권계좌 구분
	CString strPreNext		= "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo		= "9999";	//화면번호


	/*-------------------------------*
	 [3] 서버에 Tran조회 요청한다.
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
// Comment       : 주문체결내역조회
//******************************************************************
void CEurexFutOptOrdDlg::OnBnClickedBtnReqExecList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_listExec.DeleteAllItems();
	m_strListExecNextRqKey.Empty(); //연속키를 초기화시킨다.

	CString strTrCode = "OTS2850Q12";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS2850Q12_in";		//입력 레코드명(리소스파일 참고)
	
	/*-------------------------------*
		[1] Request ID생성
	 *-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
		[2] Tran조회 입력값을 입력한다.
	 *-------------------------------*/
	CString strCTNO;				//종합계좌대체번호
	CString strAPNO;				//계좌상품번호
	CString strPWD;					//비밀번호
	CString strORDR_STRT_SN("0");	//주문시작일련번호
	CString strINQ_STDR_DT;			//조회일자
	CString strCNCS_DCD("0");		//체결구분코드(0: 전체, 1: 체결, 2: 미체결)
	CString strINQ_DVSN("1");		//정렬구분코드(1: 역순, 그외 값은 정순)
	CString strFTOP_DCD("0");		//선물옵션구분코드(0: 전체, 1: 선물, 2: 옵션)
	CString strSELL_BUY_DCD("0");	//매수도매도(0:전체, 1:매도, 2:매수)
	CString strPRDT_CD;				//상품코드(값이 없으면 전종목)

	//계좌대체번호를 얻어온다.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	
	//계좌상품번호
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //종합계좌대체번호 얻어오기

	//계좌비밀번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD);

	//조회일자
	m_dateTime3.GetWindowText(strINQ_STDR_DT);
	strINQ_STDR_DT.Remove('-');

	//체결미체결구분코드(0: 전체, 1: 체결, 2: 미체결)
	if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT1))->GetCheck())
		strCNCS_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT2))->GetCheck())
		strCNCS_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT3))->GetCheck())
		strCNCS_DCD = "2";

	//정렬구분코드(1: 역순, 2 : 정순)
	if (((CButton*)GetDlgItem(IDC_RD_EXE_SORT1))->GetCheck())
		strINQ_DVSN = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_SORT2))->GetCheck())
		strINQ_DVSN = "2";

	//선물옵션구분(0:전체, 1:선물, 2:옵션)
	if (((CButton*)GetDlgItem(IDC_RD_FO_OPT1))->GetCheck())
		strFTOP_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_FO_OPT2))->GetCheck())
		strFTOP_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_FO_OPT3))->GetCheck())
		strFTOP_DCD = "2";

	//매수도매도(0:전체, 1:매도, 2:매수)
	if (((CButton*)GetDlgItem(IDC_RD_SB1))->GetCheck())
		strSELL_BUY_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_SB2))->GetCheck())
		strSELL_BUY_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_SB3))->GetCheck())
		strSELL_BUY_DCD = "2";

	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO);					//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strAPNO);					//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD);						//비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_STRT_SN", strORDR_STRT_SN);	//주문시작일련번호(필수입력아님)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_STDR_DT", strINQ_STDR_DT);		//조회일자
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CNCS_DCD", strCNCS_DCD);			//체결미체결구분코드(0: 전체, 1: 체결, 2: 미체결)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_DVSN", strINQ_DVSN);			//정렬구분코드(1: 역순, 2 : 정순)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "FTOP_DCD", strFTOP_DCD);			//선물옵션구분코드
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);	//매수매도구분
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);				//상품코드
	
	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "1";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[4] 서버에 Tran조회 요청한다.
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
void CEurexFutOptOrdDlg::OnBnClickedBtnReqExecListNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS2850Q12";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS2850Q12_in";		//입력 레코드명(리소스파일 참고)

	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	/*-------------------------------*
	[2] Tran조회 입력값을 입력한다.
	*-------------------------------*/
	CString strCTNO;				//종합계좌대체번호
	CString strAPNO;				//계좌상품번호
	CString strPWD;					//비밀번호
	CString strORDR_STRT_SN("0");	//주문시작일련번호
	CString strINQ_STDR_DT;			//조회일자
	CString strCNCS_DCD("0");		//체결구분코드(0: 전체, 1: 체결, 2: 미체결)
	CString strINQ_DVSN("1");		//정렬구분코드(1: 역순, 그외 값은 정순)
	CString strFTOP_DCD("0");		//선물옵션구분코드(0: 전체, 1: 선물, 2: 옵션)
	CString strSELL_BUY_DCD("0");	//매수도매도(0:전체, 1:매도, 2:매수)
	CString strPRDT_CD;				//상품코드(값이 없으면 전종목)

	//계좌대체번호를 얻어온다.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);

	//계좌상품번호
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //종합계좌대체번호 얻어오기

	//계좌비밀번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD);

	//조회일자
	m_dateTime3.GetWindowText(strINQ_STDR_DT);
	strINQ_STDR_DT.Remove('-');

	//체결미체결구분코드(0: 전체, 1: 체결, 2: 미체결)
	if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT1))->GetCheck())
		strCNCS_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT2))->GetCheck())
		strCNCS_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_OPT3))->GetCheck())
		strCNCS_DCD = "2";

	//정렬구분코드(1: 역순, 2 : 정순)
	if (((CButton*)GetDlgItem(IDC_RD_EXE_SORT1))->GetCheck())
		strINQ_DVSN = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_EXE_SORT2))->GetCheck())
		strINQ_DVSN = "2";

	//선물옵션구분(0:전체, 1:선물, 2:옵션)
	if (((CButton*)GetDlgItem(IDC_RD_FO_OPT1))->GetCheck())
		strFTOP_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_FO_OPT2))->GetCheck())
		strFTOP_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_FO_OPT3))->GetCheck())
		strFTOP_DCD = "2";

	//매수도매도(0:전체, 1:매도, 2:매수)
	if (((CButton*)GetDlgItem(IDC_RD_SB1))->GetCheck())
		strSELL_BUY_DCD = "0";
	else if (((CButton*)GetDlgItem(IDC_RD_SB2))->GetCheck())
		strSELL_BUY_DCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_SB3))->GetCheck())
		strSELL_BUY_DCD = "2";

	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO);					//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strAPNO);					//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD);						//비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_STRT_SN", strORDR_STRT_SN);	//주문시작일련번호(필수입력아님)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_STDR_DT", strINQ_STDR_DT);		//조회일자
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CNCS_DCD", strCNCS_DCD);			//체결미체결구분코드(0: 전체, 1: 체결, 2: 미체결)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_DVSN", strINQ_DVSN);			//정렬구분코드(1: 역순, 2 : 정순)
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "FTOP_DCD", strFTOP_DCD);			//선물옵션구분코드
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);	//매수매도구분
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);				//상품코드

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "3";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.)

	//[4] 서버에 Tran조회 요청한다.
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
void CEurexFutOptOrdDlg::OnBnClickedBtnReqBalance()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_listBalance.DeleteAllItems();

	CString strTrCode = "OTS2850Q18";			//Tran코드(리소스파일 참고)
	CString strInRecName1 = "OTS2850Q18_in";	//입력 레코드명(리소스파일 참고)

	CString strCTNO;			//대체종합계좌번호
	CString strAPNO;			//계좌상품번호
	CString strPWD;				//비밀번호
	CString strINQ_DT;			//조회일자
	CString strDCD("1");		//조회구분(1:정산전, 2:정산후 -  (1:전체 2:최종거래일이 당영업일이 아닌경우))

	//계좌대체번호를 얻어온다.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);
	
	//계좌상품번호
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO); //종합계좌대체번호 얻어오기

	//계좌비밀번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD);

	m_dateTime2.GetWindowText(strINQ_DT);
	strINQ_DT.Remove('-');

	//조회구분(1:정산전, 2:정산후 -  (1:전체 2:최종거래일이 당영업일이 아닌경우))
	if (((CButton*)GetDlgItem(IDC_RD_BAL_OPT1))->GetCheck())
		strDCD = "1";
	else if (((CButton*)GetDlgItem(IDC_RD_BAL_OPT2))->GetCheck())
		strDCD = "2";


	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdBalanceList = m_CommAgent.CreateRequestID();

	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "CTNO", strCTNO);			//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "APNO", strAPNO);			//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "PWD", strPWD);				//비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "INQ_DT", strINQ_DT);		//조회일자
	m_CommAgent.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "DCD", strDCD);			//조회구분

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[4] 서버에 Tran조회 요청한다.
	if (m_CommAgent.RequestTran(m_nRqIdBalanceList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", nRequestDataCnt) < 0)
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
void CEurexFutOptOrdDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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

	//에러메시지
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

	//주문체결내역 조회
	if (nRequestId == m_nRqIdExecList)
	{
		/*-------------------------
		  OTS2850Q80_out 단건 출력
		 --------------------------*/
		CString strFTR_SELL_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_SELL_ORDR_QNT_SMM", 0);		//선물매도주문수량합계
		CString strFTR_BUY_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_BUY_ORDR_QNT_SMM", 0);		//선물매수주문수량합계
		CString strIDX_CLPT_SELL_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_SELL_ORDR_QNT_SMM", 0);		//지수콜옵션매도주문수량합계
		CString strIDX_PTPT_SELL_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_SELL_ORDR_QNT_SMM", 0);		//지수풋옵션매도주문수량합계
		CString strIDX_CLPT_BUY_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_BUY_ORDR_QNT_SMM", 0);		//지수콜옵션매수주문수량합계
		CString strIDX_PTPT_BUY_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_BUY_ORDR_QNT_SMM", 0);		//지수풋옵션매수주문수량합계
		CString strFTR_SELL_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_SELL_CNCS_QNT_SMM", 0);		//선물매도체결수량합계
		CString strFTR_BUY_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_BUY_CNCS_QNT_SMM", 0);		//선물매수체결수량합계
		CString strIDX_CLPT_SELL_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_SELL_CNCS_QNT_SMM", 0);		//지수콜옵션매도체결수량합계
		CString strIDX_PTPT_SELL_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_SELL_CNCS_QNT_SMM", 0);		//지수풋옵션매도체결수량합계
		CString strIDX_CLPT_BUY_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_BUY_CNCS_QNT_SMM", 0);		//지수콜옵션매수체결수량합계
		CString strIDX_PTPT_BUY_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_BUY_CNCS_QNT_SMM", 0);		//지수풋옵션매수체결수량합계
		
		NumericString(strFTR_SELL_ORDR_QNT_SMM);		//선물매도주문수량합계
		NumericString(strFTR_BUY_ORDR_QNT_SMM);			//선물매수주문수량합계
		NumericString(strIDX_CLPT_SELL_ORDR_QNT_SMM);	//지수콜옵션매도주문수량합계
		NumericString(strIDX_PTPT_SELL_ORDR_QNT_SMM);	//지수풋옵션매도주문수량합계
		NumericString(strIDX_CLPT_BUY_ORDR_QNT_SMM);	//지수콜옵션매수주문수량합계
		NumericString(strIDX_PTPT_BUY_ORDR_QNT_SMM);	//지수풋옵션매수주문수량합계
		NumericString(strFTR_SELL_CNCS_QNT_SMM);		//선물매도체결수량합계
		NumericString(strFTR_BUY_CNCS_QNT_SMM);			//선물매수체결수량합계
		NumericString(strIDX_CLPT_SELL_CNCS_QNT_SMM);	//지수콜옵션매도체결수량합계
		NumericString(strIDX_PTPT_SELL_CNCS_QNT_SMM);	//지수풋옵션매도체결수량합계
		NumericString(strIDX_CLPT_BUY_CNCS_QNT_SMM);	//지수콜옵션매수체결수량합계
		NumericString(strIDX_PTPT_BUY_CNCS_QNT_SMM);	//지수풋옵션매수체결수량합계


		/*-------------------------
		 OTS2850Q80_out_sub01 복수건 출력
		 --------------------------*/
		CString strMNGM_BDCD, strMNGM_BD_NM, strMO_ORDR_SN, strORDR_SN, strOR_ORDR_SN, strPRDT_CD;
		CString strPRDT_NM, strDRVS_NMPR_DCD, strDRVS_NMPR_DVSN_NM, strORDR_PRC_CTNS, strORDR_QNT;
		CString strCNCS_DVSN_NM, strCNCS_PRC_CTNS, strCNCS_QNT, strCNCS_DTMD, strNCNC_QNT, strDRVS_NMPR_ACPT_DCD;
		CString strDRVS_NMPR_ACPT_DVSN_NM, strHND_DETL_DTM, strKRX_MSG_NO, strCNCS_SN, strXTNL_ISTT_RJCT_RSN_CD;
		CString strCOMM_MDIA_DCD;

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

		strOutRecName = "OTS2850Q12_out_sub01";

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, strOutRecName);
		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strMNGM_BDCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "MNGM_BDCD", nRow);		//관리부점코드
			strMNGM_BD_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "MNGM_BD_NM", nRow);		//관리부점명
			strMO_ORDR_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "MO_ORDR_SN", nRow);		//모주문일련번호
			strORDR_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "ORDR_SN", nRow);		//주문일련번호
			strOR_ORDR_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "OR_ORDR_SN", nRow);		//원주문일련번호
			strPRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "PRDT_CD", nRow);		//상품코드
			strPRDT_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "PRDT_NM", nRow);		//상품명
			strDRVS_NMPR_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_DCD", nRow);		//파생상품호가구분코드
			strDRVS_NMPR_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_DVSN_NM", nRow);		//파생상품호가구분명
			strORDR_PRC_CTNS = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "ORDR_PRC_CTNS", nRow);		//주문가격내용
			strORDR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "ORDR_QNT", nRow);		//주문수량
			strCNCS_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_DVSN_NM", nRow);		//체결구분명
			strCNCS_PRC_CTNS = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_PRC_CTNS", nRow);		//체결가격내용
			strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_QNT", nRow);		//체결수량
			strCNCS_DTMD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_DTMD", nRow);		//체결상세시각
			strNCNC_QNT = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "NCNC_QNT", nRow);		//미체결수량
			strDRVS_NMPR_ACPT_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_ACPT_DCD", nRow);		//파생상품호가접수구분코드
			strDRVS_NMPR_ACPT_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_ACPT_DVSN_NM", nRow);		//파생상품호가접수구분명
			strHND_DETL_DTM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "HND_DETL_DTM", nRow);		//조작상세일시
			strKRX_MSG_NO = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "KRX_MSG_NO", nRow);		//한국거래소메시지번호
			strCNCS_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_SN", nRow);		//체결일련번호
			strXTNL_ISTT_RJCT_RSN_CD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "XTNL_ISTT_RJCT_RSN_CD", nRow);		//외부기관거부사유코드
			strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "COMM_MDIA_DCD", nRow);		//통신매체구분코드

			strMNGM_BDCD.Trim();				//관리부점코드
			strMNGM_BD_NM.Trim();				//관리부점명
			NumericString(strMO_ORDR_SN);		//모주문일련번호
			NumericString(strORDR_SN);			//주문일련번호
			NumericString(strOR_ORDR_SN);		//원주문일련번호
			strPRDT_CD.Trim();					//상품코드
			strPRDT_NM.Trim();					//상품명
			strDRVS_NMPR_DCD.Trim();			//파생상품호가구분코드
			strDRVS_NMPR_DVSN_NM.Trim();		//파생상품호가구분명
			NumericString(strORDR_PRC_CTNS);	//주문가격내용
			NumericString(strORDR_QNT);			//주문수량
			strCNCS_DVSN_NM.Trim();				//체결구분명
			NumericString(strCNCS_PRC_CTNS);	//체결가격내용
			NumericString(strCNCS_QNT);			//체결수량
			strCNCS_DTMD.Trim();				//체결상세시각
			NumericString(strNCNC_QNT);			//미체결수량
			strDRVS_NMPR_ACPT_DCD.Trim();		//파생상품호가접수구분코드
			strDRVS_NMPR_ACPT_DVSN_NM.Trim();	//파생상품호가접수구분명
			strHND_DETL_DTM.Trim();				//조작상세일시
			strKRX_MSG_NO.Trim();				//한국거래소메시지번호
			NumericString(strCNCS_SN);			//체결일련번호
			strXTNL_ISTT_RJCT_RSN_CD.Trim();	//외부기관거부사유코드
			strCOMM_MDIA_DCD.Trim();			//통신매체구분코드

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listExec.InsertItem(&lvItem);

			m_listExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strMNGM_BDCD);		//관리부점코드
			m_listExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strMNGM_BD_NM);		//관리부점명
			m_listExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strMO_ORDR_SN);		//모주문일련번호
			m_listExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strORDR_SN);			//주문일련번호
			m_listExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strOR_ORDR_SN);		//원주문일련번호
			m_listExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strPRDT_CD);			//상품코드
			m_listExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strPRDT_NM);			//상품명
			m_listExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strDRVS_NMPR_DCD);		//파생상품호가구분코드
			m_listExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strDRVS_NMPR_DVSN_NM);	//파생상품호가구분명
			m_listExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strORDR_PRC_CTNS);		//주문가격내용
			m_listExec.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strORDR_QNT);		//주문수량
			m_listExec.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strCNCS_DVSN_NM);	//체결구분명
			m_listExec.SetItemText(nListIndex, 12, (LPTSTR)(LPCTSTR)strCNCS_PRC_CTNS);	//체결가격내용
			m_listExec.SetItemText(nListIndex, 13, (LPTSTR)(LPCTSTR)strCNCS_QNT);		//체결수량
			m_listExec.SetItemText(nListIndex, 14, (LPTSTR)(LPCTSTR)strCNCS_DTMD);		//체결상세시각
			m_listExec.SetItemText(nListIndex, 15, (LPTSTR)(LPCTSTR)strNCNC_QNT);		//미체결수량
			m_listExec.SetItemText(nListIndex, 16, (LPTSTR)(LPCTSTR)strDRVS_NMPR_ACPT_DCD);		//파생상품호가접수구분코드
			m_listExec.SetItemText(nListIndex, 17, (LPTSTR)(LPCTSTR)strDRVS_NMPR_ACPT_DVSN_NM);	//파생상품호가접수구분명
			m_listExec.SetItemText(nListIndex, 18, (LPTSTR)(LPCTSTR)strHND_DETL_DTM);	//조작상세일시
			m_listExec.SetItemText(nListIndex, 19, (LPTSTR)(LPCTSTR)strKRX_MSG_NO);		//한국거래소메시지번호
			m_listExec.SetItemText(nListIndex, 20, (LPTSTR)(LPCTSTR)strCNCS_SN);		//체결일련번호
			m_listExec.SetItemText(nListIndex, 21, (LPTSTR)(LPCTSTR)strXTNL_ISTT_RJCT_RSN_CD);	//외부기관거부사유코드
			m_listExec.SetItemText(nListIndex, 22, (LPTSTR)(LPCTSTR)strCOMM_MDIA_DCD);	//통신매체구분코드

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
			strCTNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CTNO", nRow);		//종합계좌대체번호
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
	//예수금(예탁금) 조회
	else if (m_nRqIdDepositList == nRequestId)
	{
		CString strOPMK_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPMK_DPST_TOT_AMT", 0);		//개장예탁총금액
		CString strOPMK_DPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPMK_DPST_CSH", 0);		//개장예탁현금
		CString strOPMK_DPST_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPMK_DPST_SBST_AMT", 0);		//개장예탁대용금액
		CString strFTR_EXCAL_DEB_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_EXCAL_DEB_AMT", 0);		//선물정산차금금액
		CString strOPT_STL_DEB_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_STL_DEB_AMT", 0);		//옵션결제차금금액
		CString strFEE_SMM_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FEE_SMM_AMT", 0);		//수수료합계금액
		CString strRNDR_SMM = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "RNDR_SMM", 0);		//입출금합계
		CString strEVL_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "EVL_DPST_TOT_AMT", 0);		//평가예탁총금액
		CString strFTR_RLZ_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_RLZ_PFLS_AMT", 0);		//선물실현손익금액
		CString strOPT_RLZ_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_RLZ_PFLS_AMT", 0);		//옵션실현손익금액
		CString strFTR_FEE = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_FEE", 0);		//선물수수료
		CString strRCTM_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "RCTM_AMT", 0);		//입금금액
		CString strEVL_DPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "EVL_DPST_CSH", 0);		//평가예탁현금
		CString strFTR_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_EVL_PFLS_AMT", 0);		//선물평가손익금액
		CString strOPT_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_EVL_PFLS_AMT", 0);		//옵션평가손익금액
		CString strOPT_FEE = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_FEE", 0);		//옵션수수료
		CString strDRWG_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DRWG_AMT", 0);		//출금금액
		CString strSTL_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "STL_DPST_TOT_AMT", 0);		//결제예탁총금액
		CString strDPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DPST_TOT_AMT", 0);		//예탁총금액
		CString strCSGN_WMY_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "CSGN_WMY_TOT_AMT", 0);		//위탁증거금총금액
		CString strADIT_WMY_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ADIT_WMY_TOT_AMT", 0);		//추가증거금총금액
		CString strORDR_PSBL_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ORDR_PSBL_TOT_AMT", 0);		//주문가능총금액
		CString strWDRW_PSBL_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WDRW_PSBL_TOT_AMT", 0);		//인출가능총금액
		CString strDPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DPST_CSH", 0);		//예탁현금
		CString strCSGN_WMY_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "CSGN_WMY_CSH", 0);		//위탁증거금현금
		CString strADIT_WMY_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ADIT_WMY_CSH", 0);		//추가증거금현금
		CString strORDR_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ORDR_PSBL_CSH", 0);		//주문가능현금
		CString strWDRW_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WDRW_PSBL_CSH", 0);		//인출가능현금
		CString strDPST_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DPST_SBST_AMT", 0);		//예탁대용금액
		CString strWMY_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WMY_SBST_AMT", 0);		//증거금대용금액
		CString strADIT_WMY_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ADIT_WMY_SBST_AMT", 0);		//추가증거금대용금액
		CString strORDR_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ORDR_PSBL_SBST_AMT", 0);		//주문가능대용금액
		CString strWDRW_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WDRW_PSBL_SBST_AMT", 0);		//인출가능대용금액
		CString strFTR_USTL_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_USTL_TOT_QNT", 0);		//선물미결제총수량
		CString strOPT_USTL_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_USTL_TOT_QNT", 0);		//옵션미결제총수량
		CString strFTR_CTRC_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_CTRC_TOT_AMT", 0);		//선물약정총금액
		CString strOPT_CTRC_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_CTRC_TOT_AMT", 0);		//옵션약정총금액
		CString strFTR_TR_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_TR_TOT_QNT", 0);		//선물거래총수량
		CString strOPT_TR_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_TR_TOT_QNT", 0);		//옵션거래총수량
		CString strFTR_SELL_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_SELL_USTL_QNT", 0);		//선물매도미결제수량
		CString strOPT_SELL_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_SELL_USTL_QNT", 0);		//옵션매도미결제수량
		CString strFTR_SELL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_SELL_CTRC_AMT", 0);		//선물매도약정금액
		CString strOPT_SELL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_SELL_CTRC_AMT", 0);		//옵션매도약정금액
		CString strFTR_SELL_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_SELL_TR_QNT", 0);		//선물매도거래수량
		CString strOPT_SELL_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_SELL_TR_QNT", 0);		//옵션매도거래수량
		CString strFTR_BUY_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_BUY_USTL_QNT", 0);		//선물매수미결제수량
		CString strOPT_BUY_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_BUY_USTL_QNT", 0);		//옵션매수미결제수량
		CString strFTR_BUY_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_BUY_CTRC_AMT", 0);		//선물매수약정금액
		CString strOPT_BUY_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_BUY_CTRC_AMT", 0);		//옵션매수약정금액
		CString strFTR_BUY_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_BUY_TR_QNT", 0);		//선물매수거래수량
		CString strOPT_BUY_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_BUY_TR_QNT", 0);		//옵션매수거래수량
		CString strNOW_TOT_WMY_RT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "NOW_TOT_WMY_RT", 0);		//현재총증거금율
		CString strCSH_WMY_RT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "CSH_WMY_RT", 0);		//현금증거금율
		CString strMNTN_WMY = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "MNTN_WMY", 0);		//유지증거금

		NumericString(strOPMK_DPST_TOT_AMT);
		NumericString(strOPMK_DPST_CSH);
		NumericString(strOPMK_DPST_SBST_AMT);
		NumericString(strFTR_EXCAL_DEB_AMT);
		NumericString(strOPT_STL_DEB_AMT);
		NumericString(strFEE_SMM_AMT);
		NumericString(strRNDR_SMM);
		NumericString(strEVL_DPST_TOT_AMT);
		NumericString(strFTR_RLZ_PFLS_AMT);
		NumericString(strOPT_RLZ_PFLS_AMT);
		NumericString(strFTR_FEE);
		NumericString(strRCTM_AMT);
		NumericString(strEVL_DPST_CSH);
		NumericString(strFTR_EVL_PFLS_AMT);
		NumericString(strOPT_EVL_PFLS_AMT);
		NumericString(strOPT_FEE);
		NumericString(strDRWG_AMT);
		NumericString(strSTL_DPST_TOT_AMT);
		NumericString(strDPST_TOT_AMT);
		NumericString(strCSGN_WMY_TOT_AMT);
		NumericString(strADIT_WMY_TOT_AMT);
		NumericString(strORDR_PSBL_TOT_AMT);
		NumericString(strWDRW_PSBL_TOT_AMT);
		NumericString(strDPST_CSH);
		NumericString(strCSGN_WMY_CSH);
		NumericString(strADIT_WMY_CSH);
		NumericString(strORDR_PSBL_CSH);
		NumericString(strWDRW_PSBL_CSH);
		NumericString(strDPST_SBST_AMT);
		NumericString(strWMY_SBST_AMT);
		NumericString(strADIT_WMY_SBST_AMT);
		NumericString(strORDR_PSBL_SBST_AMT);
		NumericString(strWDRW_PSBL_SBST_AMT);
		NumericString(strFTR_USTL_TOT_QNT);
		NumericString(strOPT_USTL_TOT_QNT);
		NumericString(strFTR_CTRC_TOT_AMT);
		NumericString(strOPT_CTRC_TOT_AMT);
		NumericString(strFTR_TR_TOT_QNT);
		NumericString(strOPT_TR_TOT_QNT);
		NumericString(strFTR_SELL_USTL_QNT);
		NumericString(strOPT_SELL_USTL_QNT);
		NumericString(strFTR_SELL_CTRC_AMT);
		NumericString(strOPT_SELL_CTRC_AMT);
		NumericString(strFTR_SELL_TR_QNT);
		NumericString(strOPT_SELL_TR_QNT);
		NumericString(strFTR_BUY_USTL_QNT);
		NumericString(strOPT_BUY_USTL_QNT);
		NumericString(strFTR_BUY_CTRC_AMT);
		NumericString(strOPT_BUY_CTRC_AMT);
		NumericString(strFTR_BUY_TR_QNT);
		NumericString(strOPT_BUY_TR_QNT);
		NumericString(strNOW_TOT_WMY_RT);
		NumericString(strCSH_WMY_RT);
		NumericString(strMNTN_WMY);

		CString strOutString;
		strOutString = "개장예탁현금(" + strOPMK_DPST_CSH + "),\t\t\t개장예탁대용금액(" + strOPMK_DPST_SBST_AMT + ")\r\n" +
			"선물정산차금금액(" + strFTR_EXCAL_DEB_AMT + "),\t\t\t옵션결제차금금액(" + strOPT_STL_DEB_AMT + ")\r\n" +
			"수수료합계금액(" + strFEE_SMM_AMT + "),\t\t\t입출금합계(" + strRNDR_SMM + ")\r\n" +
			"평가예탁총금액(" + strEVL_DPST_TOT_AMT + "),\t\t\t선물실현손익금액(" + strFTR_RLZ_PFLS_AMT + ")\r\n" +
			"옵션실현손익금액(" + strOPT_RLZ_PFLS_AMT + "),\t\t\t선물수수료(" + strFTR_FEE + ")\r\n" +
			"입금금액(" + strRCTM_AMT + "),\t\t\t평가예탁현금(" + strEVL_DPST_CSH + ")\r\n" +
			"선물평가손익금액(" + strFTR_EVL_PFLS_AMT + "),\t\t\t옵션평가손익금액(" + strOPT_EVL_PFLS_AMT + ")\r\n" +
			"옵션수수료(" + strOPT_FEE + "),\t\t\t출금금액(" + strDRWG_AMT + ")\r\n" +
			"결제예탁총금액(" + strSTL_DPST_TOT_AMT + "),\t\t\t예탁총금액(" + strDPST_TOT_AMT + ")\r\n" +
			"위탁증거금총금액(" + strCSGN_WMY_TOT_AMT + "),\t\t\t추가증거금총금액(" + strADIT_WMY_TOT_AMT + ")\r\n" +
			"주문가능총금액(" + strORDR_PSBL_TOT_AMT + "),\t\t\t인출가능총금액(" + strWDRW_PSBL_TOT_AMT + ")\r\n" +
			"예탁현금(" + strDPST_CSH + "),\t\t\t위탁증거금현금(" + strCSGN_WMY_CSH + ")\r\n" +
			"추가증거금현금(" + strADIT_WMY_CSH + "),\t\t\t주문가능현금(" + strORDR_PSBL_CSH + ")\r\n" +
			"인출가능현금(" + strWDRW_PSBL_CSH + "),\t\t\t예탁대용금액(" + strDPST_SBST_AMT + ")\r\n" +
			"증거금대용금액(" + strWMY_SBST_AMT + "),\t\t\t추가증거금대용금액(" + strADIT_WMY_SBST_AMT + ")\r\n" +
			"주문가능대용금액(" + strORDR_PSBL_SBST_AMT + "),\t\t\t인출가능대용금액(" + strWDRW_PSBL_SBST_AMT + ")\r\n" +
			"선물미결제총수량(" + strFTR_USTL_TOT_QNT + "),\t\t\t옵션미결제총수량(" + strOPT_USTL_TOT_QNT + ")\r\n" +
			"선물약정총금액(" + strFTR_CTRC_TOT_AMT + "),\t\t\t옵션약정총금액(" + strOPT_CTRC_TOT_AMT + ")\r\n" +
			"선물거래총수량(" + strFTR_TR_TOT_QNT + "),\t\t\t옵션거래총수량(" + strOPT_TR_TOT_QNT + ")\r\n" +
			"선물매도미결제수량(" + strFTR_SELL_USTL_QNT + "),\t\t\t옵션매도미결제수량(" + strOPT_SELL_USTL_QNT + ")\r\n" +
			"선물매도약정금액(" + strFTR_SELL_CTRC_AMT + "),\t\t\t옵션매도약정금액(" + strOPT_SELL_CTRC_AMT + ")\r\n" +
			"선물매도거래수량(" + strFTR_SELL_TR_QNT + "),\t\t\t옵션매도거래수량(" + strOPT_SELL_TR_QNT + ")\r\n" +
			"선물매수미결제수량(" + strFTR_BUY_USTL_QNT + "),\t\t\t옵션매수미결제수량(" + strOPT_BUY_USTL_QNT + ")\r\n" +
			"선물매수약정금액(" + strFTR_BUY_CTRC_AMT + "),\t\t\t옵션매수약정금액(" + strOPT_BUY_CTRC_AMT + ")\r\n" +
			"선물매수거래수량(" + strFTR_BUY_TR_QNT + "),\t\t\t옵션매수거래수량(" + strOPT_BUY_TR_QNT + ")\r\n" +
			"현재총증거금율(" + strNOW_TOT_WMY_RT + "),\t\t\t현금증거금율(" + strCSH_WMY_RT + ")\r\n" +
			"유지증거금(" + strMNTN_WMY + ")";

		GetDlgItem(IDC_EDIT_DEPOSIT)->SetWindowText(strOutString);


		/*--------------------------------------
		  반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		 ---------------------------------------*/
		m_nRqIdDepositList = 0;	//예수금

	}
	//잔고 조회
	else if (m_nRqIdBalanceList == nRequestId)
	{
		CString strPRDT_CD;				//상품코드
		CString strPRDT_NM;				//상품명
		CString strSELL_BUY_DCD;		//매도매수구분코드
		CString strSELL_BUY_DVSN_NM;	//매도매수구분명
		CString strUSTL_CTRC_QNT;		//미결제약정수량
		CString strAVR_PRC;				//평균가격
		CString strNOW_PRC;				//현재가격
		CString strEVL_AMT;				//평가금액
		CString strEVL_PFLS_AMT;		//평가손익금액
		CString strPFLS_RT;				//손익율
		CString strCLR_PSBL_QNT;		//청산가능수량
		CString strPCHS_ACBK_AMT;		//매입장부금액

		m_listBalance.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;

		/*--------------------------------------
		  다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		  붙여 삽입한다.
		 ---------------------------------------*/
		int nViewScrollPos = 0;

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, "OTS2850Q18_out_sub01");

		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strPRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "PRDT_CD", nRow);		//상품코드
			strPRDT_NM = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "PRDT_NM", nRow);		//상품명
			strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "SELL_BUY_DCD", nRow);		//매도매수구분코드
			strSELL_BUY_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//매도매수구분명
			strUSTL_CTRC_QNT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "USTL_CTRC_QNT", nRow);		//미결제약정수량
			strAVR_PRC = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "AVR_PRC", nRow);		//평균가격
			strNOW_PRC = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "NOW_PRC", nRow);		//현재가격
			strEVL_AMT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "EVL_AMT", nRow);		//평가금액
			strEVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "EVL_PFLS_AMT", nRow);		//평가손익금액
			strPFLS_RT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "PFLS_RT", nRow);		//손익율
			strCLR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "CLR_PSBL_QNT", nRow);		//청산가능수량
			strPCHS_ACBK_AMT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "PCHS_ACBK_AMT", nRow);		//매입장부금액

			strPRDT_CD.Trim();
			strPRDT_NM.Trim();
			strSELL_BUY_DVSN_NM.Trim();
			strSELL_BUY_DCD.Trim();
			NumericString(strUSTL_CTRC_QNT);
			NumericString(strAVR_PRC);
			NumericString(strNOW_PRC);
			NumericString(strEVL_AMT);
			NumericString(strEVL_PFLS_AMT);
			NumericString(strPFLS_RT);
			NumericString(strCLR_PSBL_QNT);
			NumericString(strPCHS_ACBK_AMT);

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listBalance.InsertItem(&lvItem);

			m_listBalance.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strPRDT_CD);				//상품코드
			m_listBalance.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strPRDT_NM);				//상품명
			m_listBalance.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strSELL_BUY_DCD);			//매도매수구분코드
			m_listBalance.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strSELL_BUY_DVSN_NM);		//매도매수구분명
			m_listBalance.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strUSTL_CTRC_QNT);		//미결제약정수량
			m_listBalance.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strAVR_PRC);				//평균가격
			m_listBalance.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strNOW_PRC);				//현재가격
			m_listBalance.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strEVL_AMT);				//평가금액
			m_listBalance.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strEVL_PFLS_AMT);			//평가손익금액
			m_listBalance.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strPFLS_RT);				//손익율
			m_listBalance.SetItemText(nListIndex, 10, (LPTSTR)(LPCTSTR)strCLR_PSBL_QNT);		//청산가능수량
			m_listBalance.SetItemText(nListIndex, 11, (LPTSTR)(LPCTSTR)strPCHS_ACBK_AMT);		//매입장부금액

			nListIndex++;
		}

		m_listBalance.EnsureVisible(0, FALSE);
		m_listBalance.SetRedraw(TRUE);

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
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS2100U10_out", "ORDR_SN", 0);		//주문번호
		NumericString(strODRV_ODNO, TRUE);

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		  반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		 ---------------------------------------*/
		m_nRqIdSellOrd = 0;
	}
	//매수주문 Request ID
	else if (m_nRqIdBuyOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS2100U20_out", "ORDR_SN", 0);		//주문번호
		NumericString(strODRV_ODNO, TRUE);

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		  반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		 ---------------------------------------*/
		m_nRqIdBuyOrd = 0;
	}
	//정정주문 Request ID
	else if (m_nRqIdChangeOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS2100U30_out", "ORDR_SN", 0);		//주문번호
		NumericString(strODRV_ODNO, TRUE);

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strODRV_ODNO);

		/*--------------------------------------
		  반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		 ---------------------------------------*/
		m_nRqIdChangeOrd = 0;
	}
	//취소주문 Request ID
	else if (m_nRqIdCancelOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS2100U40_out", "ORDR_SN", 0);		//주문번호
		NumericString(strODRV_ODNO, TRUE);

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
void CEurexFutOptOrdDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
void CEurexFutOptOrdDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/*	주의 : OnGetRealData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
		이벤트 콜백함수 종료 후에는 유효하지 않습니다.*/
	CString strRealMessage;
	CString strTemp;

	/***************************************
	 * 지수선물옵션 주문확인/체결/미체결(정정/취소) 실시간 통보
	 ****************************************/
	if (!_tcscmp(strRealName, "EF5"))
	{
		/*--------------------------------------
		 아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
		 ---------------------------------------*/
		CString strsDataType = m_CommAgent.GetRealOutputData("EF5", "sDataType");		//데이터구분
		CString strsProcTime = m_CommAgent.GetRealOutputData("EF5", "sProcTime");		//처리시간
		CString strsComCode = m_CommAgent.GetRealOutputData("EF5", "sComCode");		//매체구분
		CString strsUserID = m_CommAgent.GetRealOutputData("EF5", "sUserID");		//사용자ID
		CString strsCtno = m_CommAgent.GetRealOutputData("EF5", "sCtno");		//계좌대체번호
		CString strsAcctNo = m_CommAgent.GetRealOutputData("EF5", "sAcctNo");		//계좌번호
		CString strsAcctName = m_CommAgent.GetRealOutputData("EF5", "sAcctName");		//계좌명
		CString strsBidCode = m_CommAgent.GetRealOutputData("EF5", "sBidCode");		//주문구분
		CString strsModType = m_CommAgent.GetRealOutputData("EF5", "sModType");		//정정취소구분
		CString strsItemCode = m_CommAgent.GetRealOutputData("EF5", "sItemCode");		//단축종목코드
		CString strsItemName = m_CommAgent.GetRealOutputData("EF5", "sItemName");		//종목명
		CString strsOrdVol = m_CommAgent.GetRealOutputData("EF5", "sOrdVol");		//주문수량
		CString strsOrdPrice = m_CommAgent.GetRealOutputData("EF5", "sOrdPrice");		//주문가격
		CString strsHogaType = m_CommAgent.GetRealOutputData("EF5", "sHogaType");		//호가구분
		CString strsOrderCon = m_CommAgent.GetRealOutputData("EF5", "sOrderCon");		//주문조건
		CString strsBrnNo = m_CommAgent.GetRealOutputData("EF5", "sBrnNo");		//지점번호
		CString strsOrdNo = m_CommAgent.GetRealOutputData("EF5", "sOrdNo");		//주문번호
		CString strsOrgOrdNo = m_CommAgent.GetRealOutputData("EF5", "sOrgOrdNo");		//원주문번호
		CString strsContVol = m_CommAgent.GetRealOutputData("EF5", "sContVol");		//체결수량
		CString strsContPrice = m_CommAgent.GetRealOutputData("EF5", "sContPrice");		//체결가격
		CString strsRejectCode = m_CommAgent.GetRealOutputData("EF5", "sRejectCode");		//거부사유코드
		CString strsRejectReason = m_CommAgent.GetRealOutputData("EF5", "sRejectReason");		//거부사유
		CString strsUnContVol = m_CommAgent.GetRealOutputData("EF5", "sUnContVol");		//미체결수량
		CString strsFotsTradeUnit = m_CommAgent.GetRealOutputData("EF5", "sFotsTradeUnit");		//거래승수
		CString strsChegNo = m_CommAgent.GetRealOutputData("EF5", "sChegNo");		//체결번호
		CString strsFstPrc = m_CommAgent.GetRealOutputData("EF5", "sFstPrc");		//근월물 체결가격(스프레드)
		CString strsSndPrc = m_CommAgent.GetRealOutputData("EF5", "sSndPrc");		//원월물 체결가격(스프레드)
		CString strsWrapNo = m_CommAgent.GetRealOutputData("EF5", "sWrapNo");		//Wrap주문번호
		CString strsGroupNo = m_CommAgent.GetRealOutputData("EF5", "sGroupNo");		//그룹번호
		CString strsSeqNo = m_CommAgent.GetRealOutputData("EF5", "sSeqNo");		//바스켓시퀀스
		CString strsFee = m_CommAgent.GetRealOutputData("EF5", "sFee");		//수수료
		CString strsDvrsExcgDcd = m_CommAgent.GetRealOutputData("EF5", "sDvrsExcgDcd");		//파생상품거래소구분코드
		CString strsFiller = m_CommAgent.GetRealOutputData("EF5", "sFiller");		//Filler

		strsAcctNo.Trim();
		strsItemName.Trim();

		NumericString(strsUnContVol);		//미체결수량
		NumericString(strsContVol);			//체결수량

		//01:체결, 02 : 정정확인, 03 : 취소확인, 04 : 거부, 21 : 접수, 29 : 접수오류(01~21 거래소응답, 29 FEP응답)
		switch (_ttoi(strsDataType))
		{
			case 1:		//체결
			strTemp = "체결";
			break;
			case 2:		//정정확인
			strTemp = "정정확인";
			break;
			case 3:		//취소확인
			strTemp = "취소확인";
			break;
			case 4:		//거부
			strTemp = "거부";
			break;
			case 21:	//접수
			strTemp = "접수";
			break;
			case 29:	//접수오류
			strTemp = "접수오류";
			break;
		}//End of switch

		/*--------------------------------------
		조회 시점에 등록한 주식 현재가 실시간키와 동일한지 비교
		---------------------------------------*/
		if (m_strLoginID == strRealKey)
		{
			strRealMessage.Format("[%s][상태:%s][계좌:%s][상품:%s][미체결:%s][확인/체결:%s]", strRealName, strTemp, strsAcctNo, strsItemName, strsUnContVol, strsContVol);
		}//End of if

	}

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


void CEurexFutOptOrdDlg::OnBnClickedButtonTest()
{
	CString strAccNo, strAPNO;
	CString strAccPwd;

	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);		//계좌상품번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strAccPwd);	//비밀번호

	CString strCTNO = GetAccAPNO(strAccNo + strAPNO);		//종합계좌대체번호 얻어오기
	CString strACNT_PWD = m_CommAgent.GetEncrpyt(strAccPwd);//계좌비밀번호는 단방향 암호화를 해야된다.

	int nRequestId = m_CommAgent.CreateRequestID();

	m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "CTNO", strCTNO);			//종합계좌대체번호
	m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "APNO", strAPNO);			//계좌상품번호
	m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "PWD", strAccPwd);			//비밀번호
	m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "INQ_DVSN", _T("1"));		//조회구분
	m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "TRDE_CT_INCL_YN", _T("N"));//매매비용포함여부

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "DAPI";	//화면번호

	if (m_CommAgent.RequestTran(nRequestId, "OTS1841Q00", strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}
