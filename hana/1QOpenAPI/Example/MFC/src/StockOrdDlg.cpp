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
#include "StockOrdDlg.h"

#define ID_SECOND_TIMER		100	//1초 간격 타이머

#define SELL_BK_COLOR		RGB(206, 232, 255)	//매도 배경색
#define BUY_BK_COLOR		RGB(251, 221, 255)	//매수 배경색

//통신 구조체 헤더

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern void NumericString(CString& strValue, BOOL bNotDisplayZero = FALSE);

static char* g_szPriceCond[] = { "00", "03", "05", "06", "07"}; //00:지정가, 03:시장가, 05:조건부지정가, 06:최유리지정가, 07:최우선지정가

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

// CStockOrdDlg 대화 상자
CStockOrdDlg::CStockOrdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStockOrdDlg::IDD, pParent)
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
	m_nRqIdCodeList		= 0;	//예수금내역 Request ID

	m_brushSellBack.CreateSolidBrush(SELL_BK_COLOR);
	m_brushBuyBack.CreateSolidBrush(BUY_BK_COLOR);

	m_nSeverType			= 0;	//0-리얼, 1-국내모의, 2-해외무의

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

// agent로부터 이벤트 수신 함수를 정의한다.
BEGIN_EVENTSINK_MAP(CStockOrdDlg, CDialog)
	ON_EVENT(CStockOrdDlg, IDC_HFCOMMAGENTCTRL1, 1, CStockOrdDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CStockOrdDlg, IDC_HFCOMMAGENTCTRL1, 2, CStockOrdDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CStockOrdDlg, IDC_HFCOMMAGENTCTRL1, 3, CStockOrdDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
	ON_EVENT(CStockOrdDlg, IDC_HFCOMMAGENTCTRL1, 4, CStockOrdDlg::OnAgentEventHandler, VTS_I4 VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

// CStockOrdDlg 메시지 처리기
void CStockOrdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
void CStockOrdDlg::OnPaint()
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
HCURSOR CStockOrdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CStockOrdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CStockOrdDlg::OnNMDblclkListAccNo(NMHDR *pNMHDR, LRESULT *pResult)
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

void CStockOrdDlg::OnNMDblclkListNonExec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
// 	TCHAR *strTitle[] = { _T("주문일련번호"), _T("원주문번호"), _T("표준코드"), _T("단축코드"), _T("종목명"),
// 		_T("주문구분"), _T("호가구분명"), _T("주문수량"), _T("체결수량"), _T("주문단가") };

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;
	
	CString strCode = m_listCode.GetItemText(nSelectRow, 1);
	CString strPrice = m_listCode.GetItemText(nSelectRow, 18);

	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->SetWindowText(strCode);
	GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText(strPrice);
}


void CStockOrdDlg::OnDestroy()
{
	//모든 실시간등록을 해제한다.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();
	
	CDialog::OnDestroy();
}

void CStockOrdDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CStockOrdDlg::OnTimer(UINT_PTR nIDEvent)
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
void CStockOrdDlg::OnRdoSelectServer(UINT nID)
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
BOOL CStockOrdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CString strTitle;
	strTitle.Format("%s-[주식주문](%s)", PROGRAM_NAME, VERSION_INFO);
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
	InitListCode();		//주식마스터
	m_cmdOrdType.SetCurSel(0);

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
void CStockOrdDlg::InitListAccNo()
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
void CStockOrdDlg::InitListReal()
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
void CStockOrdDlg::InitListNonExec()
{
	CRect rc;
	m_listNonExec.GetClientRect(rc);
	m_listNonExec.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LV_COLUMN lvcolumn;
	TCHAR *strTitle[] = { _T("주문일련번호"),_T("원주문번호"), _T("표준코드"), _T("단축코드"), _T("종목명"),
		_T("주문구분"), _T("호가구분명"), _T("주문수량"), _T("체결수량"), _T("주문단가") };


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
	TCHAR *strTitle[] = { _T("주문일련번호"), _T("원주문번호"), _T("표준코드"), _T("단축코드"), _T("종목명"),
		_T("주문구분"), _T("호가구분명"), _T("주문수량"), _T("체결수량"), _T("주문단가") };


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
// Function      : 로그인
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockOrdDlg::OnBnClickedLogin()
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
	m_CommAgent.RegisterReal("IS0", m_strLoginID);
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : 로그아웃
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CStockOrdDlg::OnBnClickedLogout()
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
void CStockOrdDlg::OnBnClickedOk()
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
void CStockOrdDlg::OnBnClickedBtnReqAccno()
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
void CStockOrdDlg::OnBnClickedBtnLoadUserAcc()
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
CString CStockOrdDlg::GetAccAPNO(CString strAccNo)
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
void CStockOrdDlg::RequestAccList()
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
void CStockOrdDlg::RequestFDemoAccList()
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
BOOL CStockOrdDlg::SendSellBuyOrder(CString strDealingSide, int nRequestId)
{
	CString strTrCode = "OTS1111U10";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS1111U10_in";		//입력 레코드명(리소스파일 참고)
	if (strDealingSide == "B")
	{
		strTrCode = "OTS1111U20";
		strInRecName = "OTS1111U20_in";
	}

	CString strORDR_DT;		//주문일자
	CString strCTNO;		//종합계좌대체번호
	CString strAPNO;		//계좌상품번호
	CString strACNT_PWD;		//계좌비밀번호
	CString strPRDT_CD;		//상품코드
	CString strSPTX_DCD = "1";		//분리과세구분코드
	CString strLOAN_SN = "0";		//대출일련번호
	CString strCRDT_TR_DCD = "00";		//신용거래구분코드
	CString strSSS_NMPR_DCD = "00";		//공매도호가구분코드
	CString strFTS_ORDR_DCD = "00";		//선물대용주문구분코드
	CString strNMPR_DCD = "00";		//호가구분코드
	CString strORDR_CND_DCD = "00";		//주문조건구분코드
	CString strRSVN_ORDR_DCD = "0";		//예약주문구분코드
	CString strCVRG_PRCS_DCD = "00";		//반대매매처리구분코드
	CString strORDR_QNT;		//주문수량
	CString strORDR_UNPR;		//주문단가
	CString strEMR_ORDR_MDIA_DCD = "000";		//비상주문매체구분코드
	CString strWRAP_ORDR_KND_DCD = "00";		//WRAP주문종류구분코드
	CString strORDR_ANGT_ORDR_DCD = "0";		//주문대리인주문구분코드
	CString strPRTR_PANC_DCD = "00";		//프로그램매매공시구분코드
	CString strHTRD_NEGO_NO = "00";		//대량매매협상번호
	CString strSMLN_YN = "N";		//시뮬레이션여부

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//계좌상품번호
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);			//비밀번호
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);						//계좌비밀번호는 단방향 암호화를 해야된다.
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);		//상품코드

	if (m_cmdOrdType.GetCurSel() >= 0)
		strNMPR_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];		//가격조건구분코드

	if (strNMPR_DCD == "03")
		GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText("");

	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strORDR_UNPR);	//주문가격
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);		//주문수량


	//[2] Tran조회 입력값을 입력한다.
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "ORDR_DT", strORDR_DT);		//주문일자
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "SPTX_DCD", strSPTX_DCD);		//분리과세구분코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "LOAN_SN", strLOAN_SN);		//대출일련번호
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "CRDT_TR_DCD", strCRDT_TR_DCD);		//신용거래구분코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "SSS_NMPR_DCD", strSSS_NMPR_DCD);		//공매도호가구분코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "FTS_ORDR_DCD", strFTS_ORDR_DCD);		//선물대용주문구분코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "NMPR_DCD", strNMPR_DCD);		//호가구분코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "ORDR_CND_DCD", strORDR_CND_DCD);		//주문조건구분코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "RSVN_ORDR_DCD", strRSVN_ORDR_DCD);		//예약주문구분코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "CVRG_PRCS_DCD", strCVRG_PRCS_DCD);		//반대매매처리구분코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);		//주문수량
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "ORDR_UNPR", strORDR_UNPR);		//주문단가
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//비상주문매체구분코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "WRAP_ORDR_KND_DCD", strWRAP_ORDR_KND_DCD);		//WRAP주문종류구분코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//주문대리인주문구분코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "PRTR_PANC_DCD", strPRTR_PANC_DCD);		//프로그램매매공시구분코드
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "HTRD_NEGO_NO", strHTRD_NEGO_NO);		//대량매매협상번호
	m_CommAgent.SetTranInputData(nRequestId, strTrCode, strInRecName, "SMLN_YN", strSMLN_YN);		//시뮬레이션여부

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[3] 서버에 Tran조회 요청한다.
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
// Comment       : 매도주문
//******************************************************************
void CStockOrdDlg::OnBnClickedBtnSell()
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
void CStockOrdDlg::OnBnClickedBtnBuy()
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
void CStockOrdDlg::OnBnClickedBtnChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS1111U30";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS1111U30_in";	//입력 레코드명(리소스파일 참고)
	
	//[1] Request ID생성
	m_nRqIdChangeOrd = m_CommAgent.CreateRequestID();

	//[2] Tran조회 입력값을 입력한다.
	CString strORDR_DT;		//주문일자
	CString strCTNO;		//종합계좌대체번호
	CString strAPNO;		//계좌상품번호
	CString strMNGM_BDCD;		//관리부점코드
	CString strOR_ORDR_SN;		//원주문일련번호
	CString strACNT_PWD;		//계좌비밀번호
	CString strPRDT_CD;		//상품코드
	CString strNMPR_DCD;		//호가구분코드
	CString strORDR_CND_DCD;		//주문조건구분코드
	CString strORDR_QNT;		//주문수량
	CString strORDR_UNPR;		//주문단가
	CString strEMR_ORDR_MDIA_DCD;		//비상주문매체구분코드
	CString strGRUP_ODNO;		//그룹주문번호
	CString strBSK_ORDR_SN;		//바스켓주문일련번호
	CString strMTS_KEY;		//MTS키
	CString strHTS_ORDR_PSBL_MDIA_YN;		//HTS주문가능매체여부
	CString strNMPR_PROP_XCP_YN;		//호가적정성예외여부
	CString strORDR_ANGT_ORDR_DCD;		//주문대리인주문구분코드
	CString strBOND_ORDR_OR_UN_DCD;		//채권주문원단위구분코드
	CString strPRT_ALL_DCD;		//일부전체

	CString strAccNo;
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//계좌상품번호
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);			//비밀번호
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);						//계좌비밀번호는 단방향 암호화를 해야된다.
	
	//원주문번호
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strOR_ORDR_SN);
	
	//상품코드
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);
	
	//가격조건구분코드
	if (m_cmdOrdType.GetCurSel() >= 0)
		strNMPR_DCD = g_szPriceCond[m_cmdOrdType.GetCurSel()];

	if (strNMPR_DCD == "03")
		GetDlgItem(IDC_EDIT_ORD_PRC)->SetWindowText("");
	//정정가격
	GetDlgItem(IDC_EDIT_ORD_PRC)->GetWindowText(strORDR_UNPR);

	//정정수량
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	strEMR_ORDR_MDIA_DCD = "000";
	strGRUP_ODNO = "0";
	strBOND_ORDR_OR_UN_DCD = "2";
	strPRT_ALL_DCD = "2";

	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_DT", strORDR_DT);		//주문일자
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "MNGM_BDCD", strMNGM_BDCD);		//관리부점코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "OR_ORDR_SN", strOR_ORDR_SN);		//원주문일련번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "NMPR_DCD", strNMPR_DCD);		//호가구분코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_CND_DCD", strORDR_CND_DCD);		//주문조건구분코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);		//주문수량
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_UNPR", strORDR_UNPR);		//주문단가
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//비상주문매체구분코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "GRUP_ODNO", strGRUP_ODNO);		//그룹주문번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "BSK_ORDR_SN", strBSK_ORDR_SN);		//바스켓주문일련번호
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "MTS_KEY", strMTS_KEY);		//MTS키
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "HTS_ORDR_PSBL_MDIA_YN", strHTS_ORDR_PSBL_MDIA_YN);		//HTS주문가능매체여부
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "NMPR_PROP_XCP_YN", strNMPR_PROP_XCP_YN);		//호가적정성예외여부
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//주문대리인주문구분코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "BOND_ORDR_OR_UN_DCD", strBOND_ORDR_OR_UN_DCD);		//채권주문원단위구분코드
	m_CommAgent.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PRT_ALL_DCD", strPRT_ALL_DCD);		//일부전체

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
void CStockOrdDlg::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTrCode = "OTS1111U40";			//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS1111U40_in";	//입력 레코드명(리소스파일 참고)

	//[1] Request ID생성
	m_nRqIdCancelOrd = m_CommAgent.CreateRequestID();

	//[2] Tran조회 입력값을 입력한다.	
	CString strORDR_DT;		//주문일자
	CString strCTNO;		//종합계좌대체번호
	CString strAPNO;		//계좌상품번호
	CString strMNGM_BDCD;		//관리부점코드
	CString strOR_ORDR_SN;		//원주문일련번호
	CString strACNT_PWD;		//계좌비밀번호
	CString strPRDT_CD;		//상품코드
	CString strORDR_QNT;		//주문수량
	CString strEMR_ORDR_MDIA_DCD;		//비상주문매체구분코드
	CString strGRUP_ODNO;		//그룹주문번호
	CString strBSK_ORDR_SN;		//바스켓주문일련번호
	CString strMTS_KEY;		//MTS키
	CString strHTS_ORDR_PSBL_MDIA_YN;		//HTS주문가능매체여부
	CString strNMPR_PROP_XCP_YN;		//호가적정성예외여부
	CString strORDR_ANGT_ORDR_DCD;		//주문대리인주문구분코드
	CString strBOND_ORDR_OR_UN_DCD;		//채권주문원단위구분코드
	CString strPRT_ALL_DCD;		//일부전체구분코드
	CString strAccNo;

	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strAccNo);
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);				//대체종합계좌번호
	strCTNO = GetAccAPNO(strAccNo + strAPNO);	//종합계좌대체번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strACNT_PWD);			//비밀번호
	strACNT_PWD = m_CommAgent.GetEncrpyt(strACNT_PWD);						//계좌비밀번호는 단방향 암호화를 해야된다.

	//원주문번호
	GetDlgItem(IDC_EDIT_ORG_NO)->GetWindowText(strOR_ORDR_SN);

	//상품코드
	GetDlgItem(IDC_EDIT_SYMBOL_ORD)->GetWindowText(strPRDT_CD);

	//취소수량
	GetDlgItem(IDC_EDIT_ORD_VOL)->GetWindowText(strORDR_QNT);

	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ORDR_DT", strORDR_DT);		//주문일자
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "MNGM_BDCD", strMNGM_BDCD);		//관리부점코드
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "OR_ORDR_SN", strOR_ORDR_SN);		//원주문일련번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);		//주문수량
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//비상주문매체구분코드
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "GRUP_ODNO", strGRUP_ODNO);		//그룹주문번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "BSK_ORDR_SN", strBSK_ORDR_SN);		//바스켓주문일련번호
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "MTS_KEY", strMTS_KEY);		//MTS키
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "HTS_ORDR_PSBL_MDIA_YN", strHTS_ORDR_PSBL_MDIA_YN);		//HTS주문가능매체여부
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "NMPR_PROP_XCP_YN", strNMPR_PROP_XCP_YN);		//호가적정성예외여부
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//주문대리인주문구분코드
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "BOND_ORDR_OR_UN_DCD", strBOND_ORDR_OR_UN_DCD);		//채권주문원단위구분코드
	m_CommAgent.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "PRT_ALL_DCD", strPRT_ALL_DCD);		//일부전체구분코드
	
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
void CStockOrdDlg::OnBnClickedBtnReqMaster()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	/**********************************
	* 1. 연속조회키 초기화
	**********************************/
	m_strCodeListNextRqKey.Empty();

	//주식 종목 리스트(마스터) 컨트롤 데이터 초기화
	m_listCode.DeleteAllItems();

	/**********************************
	* 2. 통신조회 Request ID를 생성한다.
	**********************************/
	m_nRqIdCodeList = m_CommAgent.CreateRequestID();

	if (m_nRqIdCodeList == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	CString strMarketCode;		//시장구분코드
	strMarketCode = _T("J");	//주식

	/**********************************
	* 3. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("1199"));		//GID

	//서버에서 내려받을 출력항목들.
	CString strOutputFidList;

	/**********************************
	* 4. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	/* [주식 종목리스트(마스터) FID 번호]
	0001 : 단축코드
	0002 : 표준종목코드
	0003 : 한글종목명
	0827 : 시장구분(1: KOSPI, 4 : KOSDAQ, A : ETN)
	1893 : 증권그룹구분코드
	2574 : 시가총액 규모 구분코드
	제외종목 : 0
	코스피 1: 대형주, 2: 중형주, 3: 소형주
	코스닥 4: KOSDAQ100 5:KOSDAQmid300 6:KOSDAQsmall
	1993 : 지수 업종 대분류 코드
	1994 : 지수 업종 중분류 코드
	1995 : 지수 업종 소분류 코드
	2604 : 제조업 구분코드(Y : 해당 N : 비해당) = > mnin_cls_code
	2605 : 배당지수 종목여부(Y, N) = > dvdn_nmix_issu_yn
	2606 : 지배구조우수구분(Y, N) = > sprn_strr_sprr_yn
	1257 : KOSPI200 구분
	0:업종미분류 1:건설 2:중공업 3:철강소재
	4:에너지화학 5:정보통신 6:금융 7:필수소비재
	8:자유소비재 9:산업재  A:건강관리
	1998 : KOSPI100, 50 구분 (1:KOSPI100, 2:KOSPI50)
	2607 : 벤처기업 여부 Y, N = > sprn_strr_nmix_issu_yn
	1996 : KRX100 종목여부
	0225 : 결산월
	0053 : 주식액면가
	0016 : 주식기준가
	0056 : 자본금
	0055 : 상장주수
	2067 : 배당수익율
	0684 : 신용잔고비율
	1253 : 거래정지여부(N : 정상, Y : 거래정지)
	1254 : 정리매매여부(N : 정상, Y : 정리매매)
	1258 : 관리종목여부(N : 정상, Y : 관리종목)
	1251 : 시장경고구분코드(00:정상 01:주의 02:경고 03:위험)
	2608 : 시장경고예고구분코드 Y, N = > mrkt_alrm_risk_adnt_yn
	1252 : 불성실공시지정 여부 Y, N
	1992 : 우회상장구분 Y, N
	1256 : 락구분코드
	00:해당없음     01:권리락     02:배당락
	03:분배락       04:권배락     05:중간배당락
	06:권리중간배당락  99:기타
	0222 : 당사 신용 비율
	2129 : 고위험종목 구분값 1 : 해당 0 : 비해당
	2148 : Equity Rating정보 A, B, C, D, F 비산출 X
	0019 : 시가총액(억)
	0021 : 외국인보유비율
	1896 : 우선주 구분 코드(0:보통주, 그외 : 우선주)
	0:해당없음(보통주)
	1:구형우선주
	2:신형우선주
	9:종류주권
	ST에만 해당 */
	strOutputFidList = "1,2,3,827,1893,2574,1993,1994,1995,2604,2605,"
		"2606,1257,1998,2607,1996,225,53,16,56,55,2067,"
		"684,1253,1254,1258,1251,2608,1252,1992,1256,"
		"222,2129,2148,19,21,1896";
	CString strScreenNo;
	strScreenNo = "9999";

	//연속조회 옵션 : '0':미사용, '1'사용, '2' : 이전 데이터 조회, '3' : 다음 데이터 조회
	CString strPreNext = "1";

	/**********************************
	* 5. 서버에 통신조회 요청한다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_listNonExec.DeleteAllItems();
	m_strListNonExecNextRqKey.Empty(); //연속키를 초기화시킨다.

	CString strTrCode = "OTS1201Q00";				//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS1201Q00_in";	//입력 레코드명(리소스파일 참고)

	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdNonExecList = m_CommAgent.CreateRequestID();
	

	CString strPWD;		//비밀번호
	CString strCTNO;		//종합계좌대체번호
	CString strAPNO;		//계좌상품번호
	CString strORDR_DT;		//주문일자
	CString strPRDT_CD = "";		//상품코드
	CString strORDR_SN = "999999999";		//주문일련번호
	CString strCNCS_DVSN = "2";		//체결구분
	CString strINQ_ORD_DVSN = "3";		//조회순서구분
	CString strPRDT_DVSN = "0";		//상품구분
	CString strMKT_TR_DCD = "0";		//시장거래구분코드
	CString strCRDT_TR_DCD = "0";		//신용거래구분코드
	CString strCOMM_MDIA_DCD = "000";		//통신매체구분코드
	CString strORDR_PRCS_STTS_DCD = "0";		//주문처리상태구분코드
	CString strSELL_BUY_DCD = "0";		//매도매수

	m_dateTimeNonExec.GetWindowText(strORDR_DT);
	strORDR_DT.Remove('-');
	//[3] Tran조회 입력값을 입력한다.
	//계좌대체번호를 얻어온다.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);

	//계좌상품번호
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO);	//종합계좌대체번호

	//계좌비밀번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD);

	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "PWD", strPWD);		//비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "CTNO", strCTNO);		//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "ORDR_DT", strORDR_DT);		//주문일자
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "ORDR_SN", strORDR_SN);		//주문일련번호
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "CNCS_DVSN", strCNCS_DVSN);		//체결구분
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "INQ_ORD_DVSN", strINQ_ORD_DVSN);		//조회순서구분
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "PRDT_DVSN", strPRDT_DVSN);		//상품구분
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "MKT_TR_DCD", strMKT_TR_DCD);		//시장거래구분코드
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "CRDT_TR_DCD", strCRDT_TR_DCD);		//신용거래구분코드
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//통신매체구분코드
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "ORDR_PRCS_STTS_DCD", strORDR_PRCS_STTS_DCD);		//주문처리상태구분코드
	m_CommAgent.SetTranInputData(m_nRqIdNonExecList, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);		//매도매수구분코드

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "1";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[4] 서버에 Tran조회 요청한다.
	if(m_CommAgent.RequestTran(m_nRqIdNonExecList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
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
void CStockOrdDlg::OnBnClickedBtnReqExecList()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_listExec.DeleteAllItems();
	m_strListExecNextRqKey.Empty(); //연속키를 초기화시킨다.

	CString strTrCode = "OTS1201Q00";				//Tran코드(리소스파일 참고)
	CString strInRecName = "OTS1201Q00_in";	//입력 레코드명(리소스파일 참고)

	/*-------------------------------*
	[1] Request ID생성
	*-------------------------------*/
	m_nRqIdExecList = m_CommAgent.CreateRequestID();

	CString strPWD;		//비밀번호
	CString strCTNO;		//종합계좌대체번호
	CString strAPNO;		//계좌상품번호
	CString strORDR_DT;		//주문일자
	CString strPRDT_CD = "";		//상품코드
	CString strORDR_SN = "999999999";		//주문일련번호
	CString strCNCS_DVSN = "0";		//체결구분
	CString strINQ_ORD_DVSN = "3";		//조회순서구분
	CString strPRDT_DVSN = "0";		//상품구분
	CString strMKT_TR_DCD = "0";		//시장거래구분코드
	CString strCRDT_TR_DCD = "0";		//신용거래구분코드
	CString strCOMM_MDIA_DCD = "000";		//통신매체구분코드
	CString strORDR_PRCS_STTS_DCD = "0";		//주문처리상태구분코드
	CString strSELL_BUY_DCD = "0";		//매도매수

	m_dateTimeExec.GetWindowText(strORDR_DT);
	strORDR_DT.Remove('-');
	//[3] Tran조회 입력값을 입력한다.
	//계좌대체번호를 얻어온다.
	GetDlgItem(IDC_EDIT_ACCNO)->GetWindowText(strCTNO);

	//계좌상품번호
	GetDlgItem(IDC_EDIT_APNO)->GetWindowText(strAPNO);

	strCTNO = GetAccAPNO(strCTNO + strAPNO);	//종합계좌대체번호

	//계좌비밀번호
	GetDlgItem(IDC_EDIT_ACC_PWD)->GetWindowText(strPWD);
	strPWD = m_CommAgent.GetEncrpyt(strPWD);

	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD);		//비밀번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO);	//종합계좌대체번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strAPNO);		//계좌상품번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_DT", strORDR_DT);		//주문일자
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);		//상품코드
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_SN", strORDR_SN);		//주문일련번호
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CNCS_DVSN", strCNCS_DVSN);		//체결구분
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_ORD_DVSN", strINQ_ORD_DVSN);		//조회순서구분
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PRDT_DVSN", strPRDT_DVSN);		//상품구분
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "MKT_TR_DCD", strMKT_TR_DCD);		//시장거래구분코드
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CRDT_TR_DCD", strCRDT_TR_DCD);		//신용거래구분코드
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//통신매체구분코드
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_PRCS_STTS_DCD", strORDR_PRCS_STTS_DCD);		//주문처리상태구분코드
	m_CommAgent.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);		//매도매수구분코드

	CString strBenefitAcc = "N";	//수익증권계좌 구분
	CString strPreNext = "1";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	CString strScreenNo = "9999";	//화면번호
	int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	//[4] 서버에 Tran조회 요청한다.
	if (m_CommAgent.RequestTran(m_nRqIdExecList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
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
void CStockOrdDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
		CString strMNGM_BDCD, strSELL_CNCS_QNT, strSELL_CNCS_AMT, strBUY_CNCS_QNT, strBUY_CNCS_AMT, strORDR_SN;
		CString strOR_ORDR_SN, strORDR_RVSE_CNCL_DVSN_NM, strPRDT_CD, strSHTN_PRDT_CD, strPRDT_NM, strORDR_DCD_NM, strNMPR_DVSN_NM, strORDR_QNT, strCNCS_QNT;
		CString strORDR_UNPR, strITG_BOND_ORDR_UNPR, strCNCS_UNPR, strITG_BOND_CNCS_UNPR, strORDR_RMN_QNT, strCNCS_QNT_SMM, strORDR_MDIA_NM, strORDR_PRCS_STTS_DCD;
		CString strORDR_TM, strLOAN_DT, strLOAN_SN, strORDR_DT, strCNCS_DT, strSCTS_DCD, strTRDE_STL_DE_DCD, strSELL_BUY_DCD, strORDR_PRCS_STTS_DVSN_NM;
		CString strCRDT_TR_DCD, strORDR_KND_DCD, strCSGN_TRDE_DCD;

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

		strOutRecName = "OTS1201Q00_out_sub01";

		nRowCnt = m_CommAgent.GetTranOutputRowCnt(strTrCode, strOutRecName);
		for (int nRow = 0; nRow < nRowCnt; nRow++)
		{
			strORDR_SN = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_SN", nRow);		//주문일련번호
			strOR_ORDR_SN = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "OR_ORDR_SN", nRow);		//원주문일련번호
			strORDR_RVSE_CNCL_DVSN_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_RVSE_CNCL_DVSN_NM", nRow);		//주문정정취소구분명
			strPRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRDT_CD", nRow);		//상품코드
			strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SHTN_PRDT_CD", nRow);		//단축상품코드
			strPRDT_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRDT_NM", nRow);		//상품명
			strORDR_DCD_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DCD_NM", nRow);		//주문구분코드명
			strNMPR_DVSN_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "NMPR_DVSN_NM", nRow);		//호가구분명
			strORDR_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_QNT", nRow);		//주문수량
			strCNCS_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT", nRow);		//체결수량
			strORDR_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_UNPR", nRow);		//주문단가
			strITG_BOND_ORDR_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ITG_BOND_ORDR_UNPR", nRow);		//장내채권주문단가
			strCNCS_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_UNPR", nRow);		//체결단가
			strITG_BOND_CNCS_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ITG_BOND_CNCS_UNPR", nRow);		//장내채권체결단가
			strORDR_RMN_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_RMN_QNT", nRow);		//주문잔여수량
			strCNCS_QNT_SMM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT_SMM", nRow);		//체결수량합계
			strORDR_MDIA_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_MDIA_NM", nRow);		//주문매체명
			strORDR_PRCS_STTS_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_PRCS_STTS_DCD", nRow);		//주문처리상태구분코드
			strORDR_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_TM", nRow);		//주문시각
			strLOAN_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "LOAN_DT", nRow);		//대출일자
			strLOAN_SN = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "LOAN_SN", nRow);		//대출일련번호
			strORDR_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DT", nRow);		//주문일자
			strCNCS_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_DT", nRow);		//체결일자
			strMNGM_BDCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "MNGM_BDCD", nRow);		//관리부점코드
			strSCTS_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SCTS_DCD", nRow);		//유가증권구분코드
			strTRDE_STL_DE_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "TRDE_STL_DE_DCD", nRow);		//매매결제일구분코드
			strSELL_BUY_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SELL_BUY_DCD", nRow);		//매도매수구분코드
			strORDR_PRCS_STTS_DVSN_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_PRCS_STTS_DVSN_NM", nRow);		//주문처리상태구분
			strCRDT_TR_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CRDT_TR_DCD", nRow);		//신용거래구분코드
			strORDR_KND_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_KND_DCD", nRow);		//주문종류구분코드
			strCSGN_TRDE_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CSGN_TRDE_DCD", nRow);		//위탁매매구분코드

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
			
			m_listNonExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strORDR_SN);			//주문일련번호
			m_listNonExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strOR_ORDR_SN);		//원주문번호
			m_listNonExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strPRDT_CD);			//상품코드
			m_listNonExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strSHTN_PRDT_CD);		//단축코드
			m_listNonExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strPRDT_NM);			//종목명
			m_listNonExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strORDR_DCD_NM);		//주문구분코드
			m_listNonExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strNMPR_DVSN_NM);		//호가구분명
			m_listNonExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strORDR_QNT);			//주문수량
			m_listNonExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strCNCS_QNT);			//체결수량
			m_listNonExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strORDR_UNPR);		//주문단가
		}

		m_listNonExec.EnsureVisible(nViewScrollPos, FALSE);
		m_listNonExec.SetRedraw(TRUE);

		/*--------------------------------------
		연속조회키를 저장해 놓는다.
		---------------------------------------*/
		m_strListNonExecNextRqKey = strPreNextContext;

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdNonExecList = 0;	//주문체결조회 Rq ID

	}
	//주문체결내역 조회
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
		다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		붙여 삽입한다.
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
			strORDR_SN = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_SN", nRow);		//주문일련번호
			strOR_ORDR_SN = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "OR_ORDR_SN", nRow);		//원주문일련번호
			strORDR_RVSE_CNCL_DVSN_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_RVSE_CNCL_DVSN_NM", nRow);		//주문정정취소구분명
			strPRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRDT_CD", nRow);		//상품코드
			strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SHTN_PRDT_CD", nRow);		//단축상품코드
			strPRDT_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "PRDT_NM", nRow);		//상품명
			strORDR_DCD_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DCD_NM", nRow);		//주문구분코드명
			strNMPR_DVSN_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "NMPR_DVSN_NM", nRow);		//호가구분명
			strORDR_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_QNT", nRow);		//주문수량
			strCNCS_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT", nRow);		//체결수량
			strORDR_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_UNPR", nRow);		//주문단가
			strITG_BOND_ORDR_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ITG_BOND_ORDR_UNPR", nRow);		//장내채권주문단가
			strCNCS_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_UNPR", nRow);		//체결단가
			strITG_BOND_CNCS_UNPR = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ITG_BOND_CNCS_UNPR", nRow);		//장내채권체결단가
			strORDR_RMN_QNT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_RMN_QNT", nRow);		//주문잔여수량
			strCNCS_QNT_SMM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT_SMM", nRow);		//체결수량합계
			strORDR_MDIA_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_MDIA_NM", nRow);		//주문매체명
			strORDR_PRCS_STTS_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_PRCS_STTS_DCD", nRow);		//주문처리상태구분코드
			strORDR_TM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_TM", nRow);		//주문시각
			strLOAN_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "LOAN_DT", nRow);		//대출일자
			strLOAN_SN = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "LOAN_SN", nRow);		//대출일련번호
			strORDR_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DT", nRow);		//주문일자
			strCNCS_DT = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CNCS_DT", nRow);		//체결일자
			strMNGM_BDCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "MNGM_BDCD", nRow);		//관리부점코드
			strSCTS_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SCTS_DCD", nRow);		//유가증권구분코드
			strTRDE_STL_DE_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "TRDE_STL_DE_DCD", nRow);		//매매결제일구분코드
			strSELL_BUY_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "SELL_BUY_DCD", nRow);		//매도매수구분코드
			strORDR_PRCS_STTS_DVSN_NM = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_PRCS_STTS_DVSN_NM", nRow);		//주문처리상태구분
			strCRDT_TR_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CRDT_TR_DCD", nRow);		//신용거래구분코드
			strORDR_KND_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "ORDR_KND_DCD", nRow);		//주문종류구분코드
			strCSGN_TRDE_DCD = m_CommAgent.GetTranOutputData(strTrCode, strOutRecName, "CSGN_TRDE_DCD", nRow);		//위탁매매구분코드

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

			m_listExec.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strORDR_SN);			//주문일련번호
			m_listExec.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strOR_ORDR_SN);		//원주문번호
			m_listExec.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strPRDT_CD);			//상품코드
			m_listExec.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strSHTN_PRDT_CD);		//단축코드
			m_listExec.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strPRDT_NM);			//종목명
			m_listExec.SetItemText(nListIndex, 5, (LPTSTR)(LPCTSTR)strORDR_DCD_NM);		//주문구분코드
			m_listExec.SetItemText(nListIndex, 6, (LPTSTR)(LPCTSTR)strNMPR_DVSN_NM);		//호가구분명
			m_listExec.SetItemText(nListIndex, 7, (LPTSTR)(LPCTSTR)strORDR_QNT);			//주문수량
			m_listExec.SetItemText(nListIndex, 8, (LPTSTR)(LPCTSTR)strCNCS_QNT);			//체결수량
			m_listExec.SetItemText(nListIndex, 9, (LPTSTR)(LPCTSTR)strORDR_UNPR);		//주문단가
		}

		m_listExec.EnsureVisible(nViewScrollPos, FALSE);
		m_listExec.SetRedraw(TRUE);
		
		/*--------------------------------------
		연속조회키를 저장해 놓는다.
		---------------------------------------*/
		m_strListExecNextRqKey = strPreNextContext;

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
	//매도주문 Request ID
	else if (m_nRqIdSellOrd == nRequestId)
	{
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS1111U10_out", "ORDR_SN", 0);		//주문번호
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
		CString strODRV_ODNO = m_CommAgent.GetTranOutputData(strTrCode, "OTS1111U20_out", "ORDR_SN", 0);		//주문번호
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
		CString strORDR_SN = m_CommAgent.GetTranOutputData(strTrCode, "OTS1111U30_out", "ORDR_SN", 0);		//주문일련번호
		strORDR_SN.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strORDR_SN);

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdChangeOrd = 0;
	}
	//취소주문 Request ID
	else if (m_nRqIdCancelOrd == nRequestId)
	{
		CString strORDR_SN = m_CommAgent.GetTranOutputData(strTrCode, "OTS1111U40_out", "ORDR_SN", 0);		//주문일
		strORDR_SN.Trim();

		GetDlgItem(IDC_ORDER_NO)->SetWindowText(strORDR_SN);

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
void CStockOrdDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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

	/***************************************
	* 주식 종목 리스트(마스터) 조회 데이터 수신 처리
	****************************************/
	if (m_nRqIdCodeList == nRequestId)
	{
		CString arrItem[37];			//종목리스트

		m_listCode.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;
		int nViewScrollPos = 0;

		/*--------------------------------------
		다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		붙여 삽입한다.
		---------------------------------------*/
		if (!m_strCodeListNextRqKey.IsEmpty())
		{
			nListIndex = m_listCode.GetItemCount();
			nViewScrollPos = nListIndex;
		}


		/***************************************
		* 수신데이터를 직접 추출한다.(C++에서만 사용 가능)
		* 종목리스트, 차트 데이터 같은 대량의 데이터 처리 시
		* 에이전트 컨트롤의 GetFidOutputData 함수 호출보다 빠른 성능을 보인다.
		****************************************/

		/*[FID조회 시점에 입력된 출력FID 데이터 블럭이 만들어진다.]
		단축코드(FID:1), 표준중목코드(FID:2), 한글종목명(FID:3), 기준가(FID:16)
		strOutputFidList = "1,2,3,16";	*/
		CCommRecvData fidCommRecvData;
		int nVecRowCnt = 0;		//데이터 건수(행)
		int nVecColCnt = 0;	//데이터 항목 건수(열)

		//FID 조회응답 데이터 메모리를 얻어온다.(C++에서만 사용 가능)
		if (m_CommAgent.GetCommFidDataBlock((long)&fidCommRecvData) == TRUE)
		{
			nVecRowCnt = fidCommRecvData.GetRowCnt();	//데이터 건수(행)
			nVecColCnt = fidCommRecvData.GetColCnt();	//데이터 항목 건수(열)
		}

		int nDataCnt = nVecRowCnt;

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			인덱스로 조회된 수신 데이터를 항목별로 빼낸다.
			---------------------------------------*/
			arrItem[0] = fidCommRecvData.GetItem(i, 0);	//0001 : 단축코드
			arrItem[1] = fidCommRecvData.GetItem(i, 1);	//0002 : 표준종목코드
			arrItem[2] = fidCommRecvData.GetItem(i, 2);	//0003 : 한글종목명
			arrItem[3] = fidCommRecvData.GetItem(i, 3);	//0827 : 시장구분(1: KOSPI, 4 : KOSDAQ, A : ETN)
			arrItem[4] = fidCommRecvData.GetItem(i, 4);	//1893 : 증권그룹구분코드
			arrItem[5] = fidCommRecvData.GetItem(i, 5);	//2574 : 시가총액 규모 구분코드
			arrItem[6] = fidCommRecvData.GetItem(i, 6);	//1993 : 지수 업종 대분류 코드
			arrItem[7] = fidCommRecvData.GetItem(i, 7);	//1994 : 지수 업종 중분류 코드
			arrItem[8] = fidCommRecvData.GetItem(i, 8);	//1995 : 지수 업종 소분류 코드
			arrItem[9] = fidCommRecvData.GetItem(i, 9);	//2604 : 제조업 구분코드(Y : 해당 N : 비해당) = > mnin_cls_code
			arrItem[10] = fidCommRecvData.GetItem(i, 10);	//2605 : 배당지수 종목여부(Y, N) = > dvdn_nmix_issu_yn
			arrItem[11] = fidCommRecvData.GetItem(i, 11);	//2606 : 지배구조우수구분(Y, N) = > sprn_strr_sprr_yn
			arrItem[12] = fidCommRecvData.GetItem(i, 12);	//1257 : KOSPI200 구분
			arrItem[13] = fidCommRecvData.GetItem(i, 13);	//1998 : KOSPI100, 50 구분(1:KOSPI100, 2 : KOSPI50)
			arrItem[14] = fidCommRecvData.GetItem(i, 14);	//2607 : 벤처기업 여부 Y, N = > sprn_strr_nmix_issu_yn
			arrItem[15] = fidCommRecvData.GetItem(i, 15);	//1996 : KRX100 종목여부
			arrItem[16] = fidCommRecvData.GetItem(i, 16);	//0225 : 결산월
			arrItem[17] = fidCommRecvData.GetItem(i, 17);	//0053 : 주식액면가
			arrItem[18] = fidCommRecvData.GetItem(i, 18);	//0016 : 주식기준가
			arrItem[19] = fidCommRecvData.GetItem(i, 19);	//0056 : 자본금
			arrItem[20] = fidCommRecvData.GetItem(i, 20);	//0055 : 상장주수
			arrItem[21] = fidCommRecvData.GetItem(i, 21);	//2067 : 배당수익율
			arrItem[22] = fidCommRecvData.GetItem(i, 22);	//0684 : 신용잔고비율
			arrItem[23] = fidCommRecvData.GetItem(i, 23);	//1253 : 거래정지여부(N : 정상, Y : 거래정지)
			arrItem[24] = fidCommRecvData.GetItem(i, 24);	//1254 : 정리매매여부(N : 정상, Y : 정리매매)
			arrItem[25] = fidCommRecvData.GetItem(i, 25);	//1258 : 관리종목여부(N : 정상, Y : 관리종목)
			arrItem[26] = fidCommRecvData.GetItem(i, 26);	//1251 : 시장경고구분코드(00:정상 01 : 주의 02 : 경고 03 : 위험)
			arrItem[27] = fidCommRecvData.GetItem(i, 27);	//2608 : 시장경고예고구분코드 Y, N = > mrkt_alrm_risk_adnt_yn
			arrItem[28] = fidCommRecvData.GetItem(i, 28);	//1252 : 불성실공시지정 여부 Y, N
			arrItem[29] = fidCommRecvData.GetItem(i, 29);	//1992 : 우회상장구분 Y, N
			arrItem[30] = fidCommRecvData.GetItem(i, 30);	//1256 : 락구분코드
			arrItem[31] = fidCommRecvData.GetItem(i, 31);	//0222 : 당사 신용 비율
			arrItem[32] = fidCommRecvData.GetItem(i, 32);	//2129 : 고위험종목 구분값 1 : 해당 0 : 비해당
			arrItem[33] = fidCommRecvData.GetItem(i, 33);	//2148 : Equity Rating정보 A, B, C, D, F 비산출 X
			arrItem[34] = fidCommRecvData.GetItem(i, 34);	//0019 : 시가총액(억)
			arrItem[35] = fidCommRecvData.GetItem(i, 35);	//0021 : 외국인보유비율
			arrItem[36] = fidCommRecvData.GetItem(i, 36);	//1896 : 우선주 구분 코드(0:보통주, 그외 : 우선주)

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listCode.InsertItem(&lvItem);

			//리스트 컨트롤에 항목별 데이타 입력
			for (int col = 0; col < 37; col++)
			{
				m_listCode.SetItemText(nListIndex, col, (LPTSTR)(LPCTSTR)arrItem[col]);
			}

		}//End of for
		m_listCode.EnsureVisible(nViewScrollPos, FALSE);
		m_listCode.SetRedraw(TRUE);

		/*--------------------------------------
		연속조회키를 저장해 놓는다.
		---------------------------------------*/
		m_strCodeListNextRqKey = strPreNextContext;

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdCodeList = 0;	//주식 종목 리스트(마스터) 조회 Request ID

	}
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
void CStockOrdDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/*	주의 : OnGetRealData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
		이벤트 콜백함수 종료 후에는 유효하지 않습니다.*/
	CString strRealMessage;

	/***************************************
	 체결확인
	 ****************************************/
	if (!_tcscmp(strRealName, "IS0"))
	{
		/*--------------------------------------
		 아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
		 ---------------------------------------*/		
		CString strsDataType = m_CommAgent.GetRealOutputData("IS0", "sDataType");		//데이터구분
		CString strsProcTime = m_CommAgent.GetRealOutputData("IS0", "sProcTime");		//처리시간
		CString strsComCode = m_CommAgent.GetRealOutputData("IS0", "sComCode");		//매체구분
		CString strsUserID = m_CommAgent.GetRealOutputData("IS0", "sUserID");		//사용자ID
		CString strsCtno = m_CommAgent.GetRealOutputData("IS0", "sCtno");		//계좌대체번호
		CString strsAcctNo = m_CommAgent.GetRealOutputData("IS0", "sAcctNo");		//계좌번호
		CString strsAcctName = m_CommAgent.GetRealOutputData("IS0", "sAcctName");		//계좌명
		CString strsBidCode = m_CommAgent.GetRealOutputData("IS0", "sBidCode");		//주문구분
		CString strsModType = m_CommAgent.GetRealOutputData("IS0", "sModType");		//정정취소구분
		CString strsBidDetail = m_CommAgent.GetRealOutputData("IS0", "sBidDetail");		//주문상세구분
		CString strsItemCode = m_CommAgent.GetRealOutputData("IS0", "sItemCode");		//단축종목코드
		CString strsItemName = m_CommAgent.GetRealOutputData("IS0", "sItemName");		//종목명
		CString strsOrdVol = m_CommAgent.GetRealOutputData("IS0", "sOrdVol");		//주문수량
		CString strsOrdPrice = m_CommAgent.GetRealOutputData("IS0", "sOrdPrice");		//주문가격
		CString strsHogaType = m_CommAgent.GetRealOutputData("IS0", "sHogaType");		//호가구분
		CString strsOrderCon = m_CommAgent.GetRealOutputData("IS0", "sOrderCon");		//주문조건
		CString strsBrnNo = m_CommAgent.GetRealOutputData("IS0", "sBrnNo");		//지점번호
		CString strsOrdNo = m_CommAgent.GetRealOutputData("IS0", "sOrdNo");		//주문번호
		CString strsOrgOrdNo = m_CommAgent.GetRealOutputData("IS0", "sOrgOrdNo");		//원주문번호
		CString strsContVol = m_CommAgent.GetRealOutputData("IS0", "sContVol");		//체결수량
		CString strsContPrice = m_CommAgent.GetRealOutputData("IS0", "sContPrice");		//체결가격
		CString strsOrderModName = m_CommAgent.GetRealOutputData("IS0", "sOrderModName");		//주문정정취소구분명
		CString strsOrderStatName = m_CommAgent.GetRealOutputData("IS0", "sOrderStatName");		//주문처리상태구분명
		CString strsOrderTypeName = m_CommAgent.GetRealOutputData("IS0", "sOrderTypeName");		//주문구분코드명
		CString strsRejectCode = m_CommAgent.GetRealOutputData("IS0", "sRejectCode");		//거부사유코드
		CString strsRejectReason = m_CommAgent.GetRealOutputData("IS0", "sRejectReason");		//거부사유
		CString strsUnContVol = m_CommAgent.GetRealOutputData("IS0", "sUnContVol");		//미체결수량
		CString strsCreditType = m_CommAgent.GetRealOutputData("IS0", "sCreditType");		//신용구분
		CString strsCreditLoanDate = m_CommAgent.GetRealOutputData("IS0", "sCreditLoanDate");		//신용대출일
		CString strsCreditSn = m_CommAgent.GetRealOutputData("IS0", "sCreditSn");		//대출일련번호
		CString strsCreditPayment = m_CommAgent.GetRealOutputData("IS0", "sCreditPayment");		//신용금/대출상환금
		CString strsWrapNo = m_CommAgent.GetRealOutputData("IS0", "sWrapNo");		//Wrap주문번호
		CString strsGroupNo = m_CommAgent.GetRealOutputData("IS0", "sGroupNo");		//그룹번호
		CString strsSeqNo = m_CommAgent.GetRealOutputData("IS0", "sSeqNo");		//바스켓시퀀스
		CString strsBndlOrdrGrupSn = m_CommAgent.GetRealOutputData("IS0", "sBndlOrdrGrupSn");		//일괄주문그룹일련번호
		CString strsOrdrKndDcd = m_CommAgent.GetRealOutputData("IS0", "sOrdrKndDcd");		//주문종류구분코드
		CString strsFiller = m_CommAgent.GetRealOutputData("IS0", "sFiller");		//Filler


		/*--------------------------------------
		조회 시점에 등록한 주식 현재가 실시간키와 동일한지 비교
		---------------------------------------*/
		if (m_strLoginID == strRealKey)
		{
			strRealMessage.Format("[%s][계좌:%s][상품:%s][체결:%s]", strRealName, strsAcctNo, strsItemCode, strsContVol);
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

//*******************************************************************
// Function Name : OnAgentEventHandler
// Function      : 
// Param         : long nEventType, long nParam, LPCTSTR strParam
// Return        : void 
// Create        : 2016/11/10
// Comment       : 에이전트 이벤트 핸들러
//******************************************************************
void CStockOrdDlg::OnAgentEventHandler(long nEventType, long nParam, LPCTSTR strParam)
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
	TCHAR *strTitle[] = { _T("단축코드"), _T("표준코드"), _T("종목명"), _T("시장구분"),
		_T("증권코드"), _T("시가총코드"), _T("대분류"), _T("중분류"),
		_T("소분류"), _T("제조업"), _T("배당지수"), _T("지배구조"),
		_T("KSP200"), _T("KSP100"), _T("벤처기업"), _T("KRX100"),
		_T("결산월"), _T("액면가"), _T("기준가"), _T("자본금"),
		_T("상장주수"), _T("배당수익"), _T("신용잔고"), _T("거래정지"),
		_T("정리매매"), _T("관리종목"), _T("시장경고"), _T("시장경고"),
		_T("불성실"), _T("우회상장"), _T("락구분"), _T("당사신용"),
		_T("고위험"), _T("EQ Rating"), _T("시가총"), _T("외국인"),
		_T("우선주") };

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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN )
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
