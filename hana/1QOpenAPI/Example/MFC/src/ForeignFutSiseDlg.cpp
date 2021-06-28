/*----------------------------------------*
| 프로그램명 : 하나금융투자 Open API 예제
| 버      전 : v 
| 배포  일자 :
| 기      타 :
*----------------------------------------*/
// ForeignFutSiseDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "HFCommClient.h"
#include "ForeignFutSiseDlg.h"

#define ID_SECOND_TIMER		100	//1초 간격 타이머

#define SELL_BK_COLOR		RGB(206, 232, 255)	//매도 배경색
#define BUY_BK_COLOR		RGB(251, 221, 255)	//매수 배경색

//통신 구조체 헤더

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

// CForeignFutSiseDlg 대화 상자
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

	m_nSeverType = 0;	//0-리얼, 1-국내모의, 2-해외무의
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

// agent로부터 이벤트 수신 함수를 정의한다.
BEGIN_EVENTSINK_MAP(CForeignFutSiseDlg, CDialog)
	ON_EVENT(CForeignFutSiseDlg, IDC_HFCOMMAGENTCTRL1, 1, CForeignFutSiseDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CForeignFutSiseDlg, IDC_HFCOMMAGENTCTRL1, 2, CForeignFutSiseDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CForeignFutSiseDlg, IDC_HFCOMMAGENTCTRL1, 3, CForeignFutSiseDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
END_EVENTSINK_MAP()

// CForeignFutSiseDlg 메시지 처리기

void CForeignFutSiseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
void CForeignFutSiseDlg::OnPaint()
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
HCURSOR CForeignFutSiseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CForeignFutSiseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

	//호가 배경색칠
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
	//모든 실시간등록을 해제한다.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();

	CDialog::OnDestroy();
}

void CForeignFutSiseDlg::OnRdoSelectServer(UINT nID)
{
	m_nSeverType = nID - IDC_CON_REAL;

	/*----------------------------------
	접속서버를 설정한다.(0 - 리얼, 1 - 국내모의, 2 - 해외모의)
	*----------------------------------*/
	m_CommAgent.SetLoginMode(0, m_nSeverType);
}


void CForeignFutSiseDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CForeignFutSiseDlg::OnTimer(UINT_PTR nIDEvent)
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

void CForeignFutSiseDlg::OnNMDblclkListSymbol(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;

	CString strSymbol = m_listCode.GetItemText(nSelectRow, 0); //단축코드
	CString strStandardCode = m_listCode.GetItemText(nSelectRow, 1); //표준종목코드
	CString strSymbolName = m_listCode.GetItemText(nSelectRow, 2); //한글종목명
	CString strPrice = m_listCode.GetItemText(nSelectRow, 3); //기준가

	if (strSymbol.IsEmpty())
		return;

	//종목코드를 입력한다.
	m_editSymbol.SetWindowText(strSymbol);		//5단계호가 종목코드(심볼)
	m_editSymbolPrice.SetWindowText(strSymbol);	//현재가 종목코드(심볼)
	m_editSymbolTick.SetWindowText(strSymbol);	//시간대별체결 종목코드(심볼)
	m_editSymbolChart.SetWindowText(strSymbol);	//차트 종목코드(심볼)

	GetDlgItem(IDC_SYMBOL_NAME)->SetWindowText(strSymbolName);		//5단계호가 종목명
	GetDlgItem(IDC_SYMBOL_NAME_PRICE)->SetWindowText(strSymbolName);//현재가 종목명
	GetDlgItem(IDC_SYMBOL_NAME_TICK)->SetWindowText(strSymbolName);	//시간대별체결 종목명
	GetDlgItem(IDC_SYMBOL_NAME_CHART)->SetWindowText(strSymbolName);//차트 데이터 종목명

	((CButton*)GetDlgItem(IDC_RAD_QRY1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RAD_QRY3))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RAD_QRY5))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RAD_QRY7))->SetCheck(1);

	((CButton*)GetDlgItem(IDC_RAD_QRY2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RAD_QRY4))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RAD_QRY6))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RAD_QRY8))->SetCheck(0);

	//입력된 종목코드로 재조회 요청을 한다.
	OnBnClickedBtnReqPrice();	//해외선물 현재가 조회
	OnBnClickedBtnReqHoga();	//해외선물 5단계호가 조회
	OnBnClickedBtnReqTick();	//해외선물 시간대별체결 조회
	OnBnClickedBtnReqChart();	//해외선물 차트데이터 조회
}

void CForeignFutSiseDlg::OnNMDblclkListSymbol2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int nSelectRow = pNMItemActivate->iItem;

	CString strSymbol = m_listCode2.GetItemText(nSelectRow, 0); //단축코드
	CString strStandardCode = m_listCode2.GetItemText(nSelectRow, 1); //표준종목코드
	CString strSymbolName = m_listCode2.GetItemText(nSelectRow, 2); //한글종목명
	CString strPrice = m_listCode2.GetItemText(nSelectRow, 3); //기준가

	if (strSymbol.IsEmpty())
		return;

	//종목코드를 입력한다.
	m_editSymbol.SetWindowText(strStandardCode);		//5단계호가 종목코드(심볼)
	m_editSymbolPrice.SetWindowText(strStandardCode);	//현재가 종목코드(심볼)
	m_editSymbolTick.SetWindowText(strStandardCode);	//시간대별체결 종목코드(심볼)
	m_editSymbolChart.SetWindowText(strStandardCode);	//차트 종목코드(심볼)

	GetDlgItem(IDC_SYMBOL_NAME)->SetWindowText(strSymbolName);		//5단계호가 종목명
	GetDlgItem(IDC_SYMBOL_NAME_PRICE)->SetWindowText(strSymbolName);//현재가 종목명
	GetDlgItem(IDC_SYMBOL_NAME_TICK)->SetWindowText(strSymbolName);	//시간대별체결 종목명
	GetDlgItem(IDC_SYMBOL_NAME_CHART)->SetWindowText(strSymbolName);//차트 데이터 종목명

	((CButton*)GetDlgItem(IDC_RAD_QRY1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RAD_QRY3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RAD_QRY5))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RAD_QRY7))->SetCheck(0);

	((CButton*)GetDlgItem(IDC_RAD_QRY2))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RAD_QRY4))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RAD_QRY6))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RAD_QRY8))->SetCheck(1);

	//입력된 종목코드로 재조회 요청을 한다.
	OnBnClickedBtnReqPrice();	//해외선물 현재가 조회
	OnBnClickedBtnReqHoga();	//해외선물 5단계호가 조회
	OnBnClickedBtnReqTick();	//해외선물 시간대별체결 조회
	OnBnClickedBtnReqChart();	//해외선물 차트데이터 조회
}

void CForeignFutSiseDlg::OnRadioChartTerm(UINT nID)
{
	CString strCaption;

	GetDlgItem(IDC_STATIC_CHART)->SetWindowText(NULL);

	switch (nID)
	{
	case IDC_RADIO_TICK:	//틱
	{
		GetDlgItem(IDC_STATIC_CHART)->SetWindowText(_T("건수"));
	}
	break;
	case IDC_RADIO_MIN:		//분
	{
		GetDlgItem(IDC_STATIC_CHART)->SetWindowText(_T("분"));
	}
	break;
	case IDC_RADIO_DAY:		//일
	{
	}
	break;
	case IDC_RADIO_WEEK:	//주
	{
	}
	break;
	case IDC_RADIO_MON:		//월
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
// Function      : 다이얼로그 초기화
// Param         : 
// Return        : BOOL 
// Create        : 
// Comment       : 
//******************************************************************
BOOL CForeignFutSiseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CString strTitle;
	strTitle.Format("%s-[해외선물 시세](%s)", PROGRAM_NAME, VERSION_INFO);
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
	* 해외선물 시간대별체결가 리스트 컨트롤 초기화
	**********************************/
	InitListTick();

	/**********************************
	* 해외선물 종목 리스트 컨트롤 초기화
	**********************************/
	InitListCode();

	/**********************************
	* 해외선물 차트 리스트 컨트롤 초기화
	**********************************/
	InitListChart();

	/**********************************
	* HFCommAgent.dll(API Agent DLL파일 위치의 경로)
	**********************************/
	CString strApidAgentModulePath = m_CommAgent.GetApiAgentModulePath();
	GetDlgItem(IDC_API_AGENT_PATH)->SetWindowText(strApidAgentModulePath);

	/**********************************
	* 조회Tr, 실시간 통신 I/O 정보 리소스 파일 로드
	**********************************/
	//실시시간 통신 리소스파일은 개발자가 직접 경로를 지정 로드하지 않으면
	//HFCommAgent.dll파일이 위치한 RealRes 폴더에서 자동으로 로드한다.
#if 0
	//실시시간 통신 리소스파일은 개발자가 직접 경로를 지정 로드하지 않으면
	//HFCommAgent.dll파일이 위치한 RealRes 폴더에서 자동으로 로드한다.
	//해외선물체결 실시간 I/O 정보 리소스 파일
	if (!m_CommAgent.LoadRealResource(strApidAgentModulePath + "/RealRes/V10.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());

	//해외선물호가 실시간 I/O 정보 리소스 파일
	if (!m_CommAgent.LoadRealResource(strApidAgentModulePath + "/RealRes/V11.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
#endif
	//차트 해외선물 라디오 틱으로 선택
	((CButton*)GetDlgItem(IDC_RADIO_MIN))->SetCheck(1);
	GetDlgItem(IDC_EDIT_CHART_CNT)->SetWindowText("60");
	GetDlgItem(IDC_STATIC_CHART)->SetWindowText("분");

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
// Function Name : InitListTick
// Function      : 해외선물 시간대별체결 리스트 컨트롤 초기화
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
	TCHAR *strTitle[] = { _T("시간"), _T("체결가"), _T("대비"), _T("등락률"), _T("체결량") };

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
// Function      : 해외선물 종목 리스트 컨트롤 초기화
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
	TCHAR *strTitle[] = { _T("종목코드"), _T("시세종목코드"), _T("해외파생상품명"), _T("품목코드"),
		_T("해외파생품목명"), _T("행사가격"), _T("국가코드"), _T("거래소코드"), _T("품목유형구분명"),
		_T("가격소수점정보"), _T("진법"), _T("TickSize"), _T("최소가격변동금액"), _T("환산승수"),
		_T("계약단위"), _T("위탁증거금"), _T("유지증거금"), _T("상장일자"), _T("최종거래일(LTD)"),
		_T("만기일자"), _T("만기년월"), _T("결제통화"), _T("표시통화"), _T("근월물순서"),
		_T("잔존일수"), _T("Active Flag"), _T("기준가"), _T("전일종가"), _T("전일거래량"),
		_T("거래가능 여부"), _T("시작시간"), _T("종료시간"), _T("장시작시간(한국)"),
		_T("장종료시간(한국)"), _T("직전거래일"), _T("현영업일, 거래일자"), _T("상장후고가"),
		_T("상장후저가"), _T("세부거래소") };

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

	//옵션종목 리스트
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
	TCHAR *strTitle[] = { _T("일자"), _T("시간"), _T("종가"), _T("시가"), _T("고가"), _T("저가"), _T("체결량"), _T("거래량") };

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
// Function      : 대비부호
// Param         : CString strSignCode
// Return        : CString 
// Create        :
// Comment       : 
//******************************************************************
CString CForeignFutSiseDlg::GetDiffSign(CString strSignCode)
{
	if (strSignCode == _T("2"))			// 상승
		return _T("▲");
	else if (strSignCode == _T("1"))	// 상한
		return _T("↑");
	else if (strSignCode == _T("3"))	// 보합
		return _T("-");
	else if (strSignCode == _T("5"))	// 하락
		return _T("▼");
	else if (strSignCode == _T("4"))	// 하한가
		return _T("↓");

	return _T("");
}

//*******************************************************************
// Function Name : SetHogaData
// Function      : 호가데이터 컨트롤 표시
// Param         :	CString* arrSellHoga,	매도 5단계호가
//					CString* arrBuyHoga,	매수 5단계호가
//					CString* arrSellRemain,	매도 5단계호가잔량
//					CString* arrBuyRemain	매수 5단계호가잔량
//					CString* arrSellCnt,
//					CString* arrBuyCnt
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::SetHogaData(CString* arrSellHoga, CString* arrBuyHoga, CString* arrSellRemain,
	CString* arrBuyRemain, CString* arrSellCnt, CString* arrBuyCnt)
{
	//공백문자 제거
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

	//매도호가 컨트롤 입력
	GetDlgItem(IDC_SELL_1)->SetWindowText(arrSellHoga[0]);
	GetDlgItem(IDC_SELL_2)->SetWindowText(arrSellHoga[1]);
	GetDlgItem(IDC_SELL_3)->SetWindowText(arrSellHoga[2]);
	GetDlgItem(IDC_SELL_4)->SetWindowText(arrSellHoga[3]);
	GetDlgItem(IDC_SELL_5)->SetWindowText(arrSellHoga[4]);

	//매도호가잔량 컨트롤 입력
	GetDlgItem(IDC_SELL_REMAIN_1)->SetWindowText(arrSellRemain[0]);
	GetDlgItem(IDC_SELL_REMAIN_2)->SetWindowText(arrSellRemain[1]);
	GetDlgItem(IDC_SELL_REMAIN_3)->SetWindowText(arrSellRemain[2]);
	GetDlgItem(IDC_SELL_REMAIN_4)->SetWindowText(arrSellRemain[3]);
	GetDlgItem(IDC_SELL_REMAIN_5)->SetWindowText(arrSellRemain[4]);

	//매도호가건수 컨트롤 입력
	GetDlgItem(IDC_SELL_CNT1)->SetWindowText(arrSellRemain[0]);
	GetDlgItem(IDC_SELL_CNT2)->SetWindowText(arrSellRemain[1]);
	GetDlgItem(IDC_SELL_CNT3)->SetWindowText(arrSellRemain[2]);
	GetDlgItem(IDC_SELL_CNT4)->SetWindowText(arrSellRemain[3]);
	GetDlgItem(IDC_SELL_CNT5)->SetWindowText(arrSellRemain[4]);

	//매수호가 컨트롤 입력
	GetDlgItem(IDC_BUY_1)->SetWindowText(arrBuyHoga[0]);
	GetDlgItem(IDC_BUY_2)->SetWindowText(arrBuyHoga[1]);
	GetDlgItem(IDC_BUY_3)->SetWindowText(arrBuyHoga[2]);
	GetDlgItem(IDC_BUY_4)->SetWindowText(arrBuyHoga[3]);
	GetDlgItem(IDC_BUY_5)->SetWindowText(arrBuyHoga[4]);

	//매수호가잔량 컨트롤 입력
	GetDlgItem(IDC_BUY_REMAIN_1)->SetWindowText(arrBuyRemain[0]);
	GetDlgItem(IDC_BUY_REMAIN_2)->SetWindowText(arrBuyRemain[1]);
	GetDlgItem(IDC_BUY_REMAIN_3)->SetWindowText(arrBuyRemain[2]);
	GetDlgItem(IDC_BUY_REMAIN_4)->SetWindowText(arrBuyRemain[3]);
	GetDlgItem(IDC_BUY_REMAIN_5)->SetWindowText(arrBuyRemain[4]);

	//매수호가건수 컨트롤 입력
	GetDlgItem(IDC_BUY_CNT1)->SetWindowText(arrSellRemain[0]);
	GetDlgItem(IDC_BUY_CNT2)->SetWindowText(arrSellRemain[1]);
	GetDlgItem(IDC_BUY_CNT3)->SetWindowText(arrSellRemain[2]);
	GetDlgItem(IDC_BUY_CNT4)->SetWindowText(arrSellRemain[3]);
	GetDlgItem(IDC_BUY_CNT5)->SetWindowText(arrSellRemain[4]);
}

//*******************************************************************
// Function Name : OnBnClickedInitcomm
// Function      : 통신모듈 초기화 및 통신 연결
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedInitcomm()
{
	if (m_bCommConnect)
	{
		::AfxMessageBox("이미 통신 접속되었습니다!");
		return;
	}

	//통신모듈 초기화 및 통신 연결
	if (m_CommAgent.CommInit() < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());

	//연결상태(TRUE : 연결, FALSE : 끊김)
	m_bCommConnect = m_CommAgent.CommGetConnectState();
}

//*******************************************************************
// Function Name : OnBnClickedTerminate
// Function      : 통신연결 해제
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedTerminate()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("이미 통신 접속이 끊겼습니다!");
		return;
	}

	//모든 실시간등록을 해제한다.
	m_CommAgent.AllUnRegisterReal();

	//통신연결 해제
	m_CommAgent.CommTerminate(TRUE);

	//연결상태(TRUE : 연결, FALSE : 끊김)
	m_bCommConnect = m_CommAgent.CommGetConnectState();
}

//*******************************************************************
// Function Name : OnBnClickedLogin
// Function      : 로그인
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedLogin()
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
	else
		OnBnClickedBtnReqCodeList(); //종목리스트(마스터) 조회
}

//*******************************************************************
// Function Name : OnBnClickedLogout
// Function      : 로그아웃
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedLogout()
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
// Function Name : OnBnClickedBtnReqCodeList
// Function      : 해외선물 종목 리스트 조회
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqCodeList()
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

	//해외선물 종목 리스트(마스터) 컨트롤 데이터 초기화
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
	strMarketCode = _T("FF");	//해외선물

	/**********************************
	* 3. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("3299"));		//GID

	//서버에서 내려받을 출력항목들.
	CString strOutputFidList;

	/**********************************
	* 4. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	0001 : 종목코드(내부)
	0002 : 시세종목코드
	0003 : 해외파생상품명
	1448 : 품목코드
	2083 : 해외파생품목명
	0661 : 행사가격
	1170 : 국가코드
	1987 : 거래소코드
	2467 : 품목유형구분명
	2456 : 가격소수점정보
	2457 : 진법
	2295 : Tick Size
	1396 : 최소가격변동금액
	1773 : 환산승수
	1772 : 계약단위, 계약크기
	1731 : 위탁증거금
	2460 : 유지증거금
	0226 : 상장일자
	0132 : 최종거래일(LTD)
	0981 : 만기일자(Expire Date)
	1203 : 만기년월(Expire Month/Year)
	1268 : 결제통화(거래통화?)
	1171 : 표시통화
	2459 : 근월물순서
	0133 : 잔존일수
	1759 : Active Flag
	0016 : 기준가
	0010 : 전일종가
	0028 : 전일거래량
	1762 : 거래가능 여부
	1870 : 시작시간
	1871 : 종료시간
	2486 : 장시작시간(한국)
	2487 : 장종료시간(한국)
	0815 : 직전거래일
	0009 : 현영업일, 거래일자
	0128 : 상장후고가
	0129 : 상장후저가
	2596 : 세부거래소코드*/
	strOutputFidList =	"1,2,3,1448,2083,661,1170,1987,2467,2456,2457,2295,1396,"
						"1773,1772,1731,2460,226,132,981,1203,1268,1171,"
						"2459,133,1759,16,10,28,1762,1870,1871,2486,2487,"
						"815,9,128,129, 2596";

	CString strScreenNo;
	strScreenNo = "9999";

	//연속조회 옵션 : '0':미사용, '1'사용, '2' : 이전 데이터 조회, '3' : 다음 데이터 조회
	CString strPreNext = "1";

	/**********************************
	* 5. 서버에 통신조회 요청한다.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, "", strScreenNo, 9999);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqCodeListNext
// Function      : 해외선물 종목 리스트 다음 조회
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqCodeListNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	/**********************************
	* 1. 통신조회 Request ID를 생성한다.
	**********************************/
	m_nRqIdCodeList = m_CommAgent.CreateRequestID();
	if (m_nRqIdCodeList == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	CString strMarketCode;		//시장구분코드
	strMarketCode = _T("FF"); //해외선물

	/**********************************
	* 2. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("3299"));		//GID

	//통신조회 응답으로 받을 데이터 항목(FID)
	CString strOutputFidList;

	/**********************************
	* 3. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	0001 : 종목코드(내부)
	0002 : 시세종목코드
	0003 : 해외파생상품명
	1448 : 품목코드
	2083 : 해외파생품목명
	0661 : 행사가격
	1170 : 국가코드
	1987 : 거래소코드
	2467 : 품목유형구분명
	2456 : 가격소수점정보
	2457 : 진법
	2295 : Tick Size
	1396 : 최소가격변동금액
	1773 : 환산승수
	1772 : 계약단위, 계약크기
	1731 : 위탁증거금
	2460 : 유지증거금
	0226 : 상장일자
	0132 : 최종거래일(LTD)
	0981 : 만기일자(Expire Date)
	1203 : 만기년월(Expire Month/Year)
	1268 : 결제통화(거래통화?)
	1171 : 표시통화
	2459 : 근월물순서
	0133 : 잔존일수
	1759 : Active Flag
	0016 : 기준가
	0010 : 전일종가
	0028 : 전일거래량
	1762 : 거래가능 여부
	1870 : 시작시간
	1871 : 종료시간
	2486 : 장시작시간(한국)
	2487 : 장종료시간(한국)
	0815 : 직전거래일
	0009 : 현영업일, 거래일자
	0128 : 상장후고가
	0129 : 상장후저가
	2596 : 세부거래소코드*/
	strOutputFidList =	"1,2,3,1448,2083,661,1170,1987,2467,2456,2457,2295,1396,"
						"1773,1772,1731,2460,226,132,981,1203,1268,1171,"
						"2459,133,1759,16,10,28,1762,1870,1871,2486,2487,"
						"815,9,128,129,2596";

	CString strScreenNo;
	strScreenNo = "9999";

	CString strPreNext = "3"; //다음 데이터 조회

	/**********************************
	* 4. 서버에 통신조회 요청한다.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, m_strCodeListNextRqKey, strScreenNo, 9999);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqPrice
// Function      : 현재가 조회
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqPrice()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	CString strMarketCode;		//시장구분
	CString strRealName;

	if (((CButton*)GetDlgItem(IDC_RAD_QRY5))->GetCheck())
	{
		strMarketCode = _T("FF");	//해외선물
		strRealName = _T("V10"); //해외선물체결 Real name
	}
	else
	{
		strMarketCode = _T("FO");	//해외옵션
		strRealName = _T("V20"); //해외옵션체결 Real name
	}

	CString strSymBol;			//종목코드
	m_editSymbolPrice.GetWindowText(strSymBol); //종목코드
	strSymBol.Trim();
	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("종목코드 입력은 필수입니다!");
		m_editSymbolPrice.SetFocus();
		return;
	}
	/**********************************
	* 1. 통신조회 Request ID를 생성한다.
	**********************************/
	m_nRqIdCurPrice = m_CommAgent.CreateRequestID();
	if (m_nRqIdCurPrice == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	/**********************************
	* 2. 이전에 등록된 해외선물체결(현재가) 실시간등록 해제.
	**********************************/
	if (!m_strCurPriceRealKey.IsEmpty())
	{
		m_CommAgent.UnRegisterReal(strRealName, m_strCurPriceRealKey);
		m_strCurPriceRealKey.Empty();
	}

	//해외선물체결(현재가) 실시간 등록키로 사용할 리얼키(종목코드)
	m_strCurPriceRealKey = strSymBol;

	/**********************************
	* 3. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCurPrice, _T("9002"), strSymBol);		//종목코드
	m_CommAgent.SetFidInputData(m_nRqIdCurPrice, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdCurPrice, _T("GID"), _T("1000"));		//GID

	//통신조회 응답으로 받을 데이터 항목(FID)
	CString strOutputFidList;

	/**********************************
	* 4. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	현재가(4), 부호(6), 전일대비(5), 대비율(7), 거래량(11)
	전일거래량(28), 시가(13), 고가(14), 저가(15) */
	strOutputFidList = "4,6,5,7,11,28,13,14,15";

	CString strScreenNo;
	strScreenNo = "9999";

	/**********************************
	* 5. 서버에 통신조회 요청한다.
	**********************************/
	int nReturn = m_CommAgent.RequestFid(m_nRqIdCurPrice, strOutputFidList, strScreenNo);

	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqHoga
// Function      : 해외선물호가 조회
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqHoga()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	CString strMarketCode;		//시장구분코드
	CString strRealName;

	if (((CButton*)GetDlgItem(IDC_RAD_QRY1))->GetCheck())
	{
		strMarketCode = _T("FF");	//해외선물
		strRealName = _T("V11"); //해외선물체결 Real name
	}
	else
	{
		strMarketCode = _T("FO");	//해외옵션
		strRealName = _T("V21"); //해외옵션체결 Real name
	}

	CString strSymBol;			//종목코드
	m_editSymbol.GetWindowText(strSymBol);

	strSymBol.Trim();
	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("종목코드 입력은 필수입니다!");
		m_editSymbol.SetFocus();
		return;
	}

	/**********************************
	* 1. 통신조회 Request ID를 생성한다.
	**********************************/
	m_nRqIdHoga = m_CommAgent.CreateRequestID();
	if (m_nRqIdHoga == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	/**********************************
	* 2. 이전에 등록된 해외호가 실시간등록 해제
	**********************************/
	if (!m_strHogaRealKey.IsEmpty())
	{
		m_CommAgent.UnRegisterReal(strRealName, m_strHogaRealKey);
		m_strHogaRealKey.Empty();
	}

	//해외호가 실시간 등록키로 사용할 리얼키(종목코드)
	m_strHogaRealKey = strSymBol;

	/**********************************
	* 3. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdHoga, _T("9002"), strSymBol);		//종목코드
	m_CommAgent.SetFidInputData(m_nRqIdHoga, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdHoga, _T("GID"), _T("1000"));		//GID

	/**********************************
	* 4. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	CString strSellHoga = _T("29,30,31,32,33");	//매도 1~5 호가(FID)
	CString strSellRemain = _T("63,64,65,66,67"); //매도 1~5 호가잔량(FID)
	CString strBuyHoga = _T("39,40,41,42,43");	//매수 1~5 호가(FID)
	CString strBuyRemain = _T("73,74,75,76,77"); //매수 1~5 호가 잔량(FID)
	CString strSellCnt = _T("196,197,198,199,200"); //매도 1~5 호가건수(FID)
	CString strBuyCnt = _T("201,202,203,204,205"); //매수 1~5 호가건수(FID)

	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]*/
	CString strOutputFidList = strSellHoga + "," + strSellRemain + "," + strBuyHoga + "," +
		strBuyRemain + "," + strSellCnt + "," + strBuyCnt;

	CString strScreenNo;
	strScreenNo = "9999";

	/**********************************
	* 5. 서버에 통신조회 요청한다.
	**********************************/
	int nReturn = m_CommAgent.RequestFid(m_nRqIdHoga, strOutputFidList, strScreenNo);

	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqTick
// Function      : 해외선물 시간대별체결 데이터 조회(연속거래 데이터가 있는 경우)
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqTick()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	CString strMarketCode;		//시장구분코드
	CString strRealName;

	if (((CButton*)GetDlgItem(IDC_RAD_QRY3))->GetCheck())
	{
		strMarketCode = _T("FF");	//해외선물
		strRealName = _T("V10"); //해외선물체결 Real name
	}
	else
	{
		strMarketCode = _T("FO");	//해외옵션
		strRealName = _T("V20"); //해외옵션체결 Real name
	}

	CString strSymBol;			//종목심볼코드
	m_editSymbolTick.GetWindowText(strSymBol);
	strSymBol.Trim();

	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("종목코드 입력은 필수입니다!");
		m_editSymbolTick.SetFocus();
		return;
	}

	/**********************************
	* 1. 연속조회키 초기화
	**********************************/
	m_strTickNextRqKey.Empty();

	//해외선물 시간대별체결 리스트 컨트롤 데이터 초기화
	m_listTick.DeleteAllItems();

	/**********************************
	* 2. 통신조회 Request ID를 생성한다.
	**********************************/
	m_nRqIdTick = m_CommAgent.CreateRequestID();

	if (m_nRqIdTick == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	/**********************************
	* 3. 이전에 등록된 해외선물체결(현재가) 실시간등록 해제.
	**********************************/
	if (!m_strTickRealKey.IsEmpty())
	{
		m_CommAgent.UnRegisterReal(strRealName, m_strTickRealKey);
		m_strTickRealKey.Empty();
	}

	//해외선물체결(현재가) 실시간 등록키로 사용할 리얼키(종목코드)
	m_strTickRealKey = strSymBol;

	/**********************************
	* 4. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9002"), strSymBol);		//종목심볼
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("GID"), _T("1003"));		//GID

	//서버에서 내려받을 출력항목들.
	CString strOutputFidList;

	/**********************************
	* 5. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	시간(8), 체결가(4), 대비(5), 등락률(7), 체결량(83) */
	strOutputFidList = "8,4,5,7,83";

	CString strScreenNo;
	strScreenNo = "9999";

	//연속조회 옵션 : '0':미사용, '1'사용, '2' : 이전 데이터 조회, '3' : 다음 데이터 조회
	CString strPreNext = "1";

	/**********************************
	* 6. 서버에 통신조회 요청한다.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdTick, strOutputFidList, strPreNext, "", strScreenNo, 0);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqTickNext
// Function      : 해외선물 시간대별체결 다음 데이터 조회
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqTickNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	CString strMarketCode;		//시장구분코드
	
	if (((CButton*)GetDlgItem(IDC_RAD_QRY3))->GetCheck())
	{
		strMarketCode = _T("FF");	//해외선물
	}
	else
	{
		strMarketCode = _T("FO");	//해외옵션
	}

	CString strSymBol;			//종목심볼코드
	m_editSymbolTick.GetWindowText(strSymBol);
	strSymBol.Trim();

	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("종목코드 입력은 필수입니다!");
		m_editSymbolTick.SetFocus();
		return;
	}


	/**********************************
	* 1. 통신조회 Request ID를 생성한다.
	**********************************/
	m_nRqIdTick = m_CommAgent.CreateRequestID();
	if (m_nRqIdTick == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	/**********************************
	* 2. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9002"), strSymBol);		//종목심볼
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("GID"), _T("1003"));		//GID

	//통신조회 응답으로 받을 데이터 항목(FID)
	CString strOutputFidList;

	/**********************************
	* 3. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	시간(8), 체결가(4), 대비(5), 등락률(7), 체결량(83) */
	strOutputFidList = "8,4,5,7,83";

	CString strScreenNo;
	strScreenNo = "9999";

	CString strPreNext = "3"; //다음 데이터 조회

	/**********************************
	* 4. 서버에 통신조회 요청한다.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdTick, strOutputFidList, strPreNext, m_strTickNextRqKey, strScreenNo, 0);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqChart
// Function      : 해외선물 차트 데이터 조회
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqChart()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	CString strMarketCode;		//시장구분코드

	if (((CButton*)GetDlgItem(IDC_RAD_QRY7))->GetCheck())
	{
		strMarketCode = _T("FF");	//해외선물
	}
	else
	{
		strMarketCode = _T("FO");	//해외옵션
	}

	CString strSymBol;			//종목심볼코드
	m_editSymbolChart.GetWindowText(strSymBol);
	strSymBol.Trim();

	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("종목코드 입력은 필수입니다!");
		m_editSymbolChart.SetFocus();
		return;
	}

	/**********************************
	* 1. 연속조회키 초기화
	**********************************/
	m_strTickNextRqKey.Empty();

	//해외선물 시간대별체결 리스트 컨트롤 데이터 초기화
	m_listChart.DeleteAllItems();

	/**********************************
	* 2. 통신조회 Request ID를 생성한다.
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
	* 3. 통신조회 요청 입력데이터
	**********************************/
	int nRecvCnt = 9999;
	CString strFromDate, strToDate;
	m_dateTimeFrom.GetWindowText(strFromDate);	//조회 시작일
	m_dateTimeTo.GetWindowText(strToDate);		//조회 종료일

	strFromDate.Remove('-'); strToDate.Remove('-');

	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9002"), strSymBol);		//종목심볼
	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);		//시작일
	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);		//종료일

	if (((CButton*)GetDlgItem(IDC_RADIO_TICK))->GetCheck()) //틱
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);		//시작일

		if (_ttoi(strChartCnt) > 0)
		{
			nRecvCnt = _ttoi(strChartCnt);
			m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strChartCnt);	//9119 : 틱 건수
		}

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1003")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MIN))->GetCheck()) //분
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);		//시작일

		CString strMin;
		strMin.Format(_T("%d"), _ttoi(strChartCnt) * 60);

		//9119 : 구분코드( 30: 30초, 60: 1분, 600: 10분, 3600: 60분, 60*N: N분 )
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strMin);
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1006")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_DAY))->GetCheck()) //일
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1008")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_WEEK))->GetCheck()) //주
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "W");				//주(W), 월(M)
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1009")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MON))->GetCheck()) //월
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "M");				//주(W), 월(M)
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1010")); //GID
	}

	//서버에서 내려받을 출력항목들.
	CString strOutputFidList;

	/**********************************
	* 4. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	일자(9), 시간(8), 종가(4), 시가(13), 고가(14), 저가(15), 체결량(83), 거래량(11) */
	/*strOutputFidList = "9,8,4,13,14,15,83,11";*/
	//1173,1174 한국 일자/시간
	strOutputFidList = "1173,1174,4,13,14,15,83,11";

	CString strScreenNo;
	strScreenNo = "9999";

	//연속조회 옵션 : '0':미사용, '1'사용, '2' : 이전 데이터 조회, '3' : 다음 데이터 조회
	CString strPreNext = "1";

	/**********************************
	* 6. 서버에 통신조회 요청한다.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdChart, strOutputFidList, strPreNext, "", strScreenNo, nRecvCnt);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqChartNext
// Function      : 해외선물 차트 다음 데이터 조회
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnBnClickedBtnReqChartNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	CString strMarketCode;		//시장구분코드

	if (((CButton*)GetDlgItem(IDC_RAD_QRY7))->GetCheck())
	{
		strMarketCode = _T("FF");	//해외선물
	}
	else
	{
		strMarketCode = _T("FO");	//해외옵션
	}

	CString strSymBol;			//종목심볼코드
	m_editSymbolChart.GetWindowText(strSymBol);
	strSymBol.Trim();

	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("종목코드 입력은 필수입니다!");
		m_editSymbolChart.SetFocus();
		return;
	}


	/**********************************
	* 1. 통신조회 Request ID를 생성한다.
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
	* 2. 통신조회 요청 입력데이터
	**********************************/
	int nRecvCnt = 9999;
	CString strFromDate, strToDate;
	m_dateTimeFrom.GetWindowText(strFromDate);	//조회 시작일
	m_dateTimeTo.GetWindowText(strToDate);		//조회 종료일
	strFromDate.Remove('-'); strToDate.Remove('-');

	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9002"), strSymBol);		//종목심볼
	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9001"), strMarketCode);	//시장구분코드

	if (((CButton*)GetDlgItem(IDC_RADIO_TICK))->GetCheck()) //틱
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);	//종료일

		if (_ttoi(strChartCnt) > 0)
		{
			nRecvCnt = _ttoi(strChartCnt);
			m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strChartCnt);	//9119 : 틱 건수
		}

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1003")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MIN))->GetCheck()) //분
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);	//종료일

		CString strMin;
		strMin.Format(_T("%d"), _ttoi(strChartCnt) * 60);

		//9119 : 구분코드( 30: 30초, 60: 1분, 600: 10분, 3600: 60분, 60*N: N분 )
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strMin);

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1006")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_DAY))->GetCheck()) //일
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);	//시작일
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);	//종료일

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1008")); //GID

	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_WEEK))->GetCheck()) //주
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);	//시작일
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);	//종료일

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "W");				//주(W), 월(M)

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1009")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MON))->GetCheck()) //월
	{
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);	//시작일
		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);	//종료일

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9011"), "M");				//주(W), 월(M)

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1010")); //GID
	}

	//통신조회 응답으로 받을 데이터 항목(FID)
	CString strOutputFidList;

	/**********************************
	* 3. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	일자(9), 시간(8), 종가(4), 시가(13), 고가(14), 저가(15), 체결량(83), 거래량(11) */
	strOutputFidList = "9,8,4,13,14,15,83,11";

	CString strScreenNo;
	strScreenNo = "9999";

	CString strPreNext = "3"; //다음 데이터 조회

	/**********************************
	* 4. 서버에 통신조회 요청한다.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdChart, strOutputFidList, strPreNext, m_strChartNextRqKey, strScreenNo, nRecvCnt);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

void CForeignFutSiseDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PostMessage(WM_CLOSE);
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
void CForeignFutSiseDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
{
	/* 주의 : OnGetTranData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
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

	//조회응답 부가메시지코드
	CString strSubMsgCode = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::SubMsgCode);

	//조회응답 부가메시지
	CString strSubMsg = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::SubMsg);

	//에러여부( "1" : 에러, "0" : 정상)
	CString strIsError = m_CommAgent.GetCommRecvOptionValue(CommRecvOpt::Error);

	CString strErrMsg = m_CommAgent.GetLastErrMsg();
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
void CForeignFutSiseDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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

	/***************************************
	* 해외선물 종목 리스트(마스터) 조회 데이터 수신 처리
	****************************************/
	if (m_nRqIdCodeList == nRequestId)
	{
		CString strCode;			//단축코드
		CString strStandardCode;	//표준코드
		CString strCodeName;		//한글종목명
		CString strPrice;			//기준가

		m_listCode.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;

		/*--------------------------------------
		다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		붙여 삽입한다.
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
			FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
			---------------------------------------*/
			arrItemValue[0] = m_CommAgent.GetFidOutputData(nRequestId, "1", i);			//종목코드(내부)
			
			if (m_CommAgent.VerifyRequestCode(arrItemValue[0]))
				continue;
			
			arrItemValue[1] = m_CommAgent.GetFidOutputData(nRequestId, "2", i);			//시세종목코드
			arrItemValue[2] = m_CommAgent.GetFidOutputData(nRequestId, "3", i);			//해외파생상품명
			arrItemValue[3] = m_CommAgent.GetFidOutputData(nRequestId, "1448", i);		//품목코드
			arrItemValue[4] = m_CommAgent.GetFidOutputData(nRequestId, "2083", i);		//해외파생품목명
			arrItemValue[5] = m_CommAgent.GetFidOutputData(nRequestId, "661", i);		//행사가격
			arrItemValue[6] = m_CommAgent.GetFidOutputData(nRequestId, "1170", i);		//국가코드
			arrItemValue[7] = m_CommAgent.GetFidOutputData(nRequestId, "1987", i);		//거래소코드
			arrItemValue[8] = m_CommAgent.GetFidOutputData(nRequestId, "2467", i);		//품목유형구분명
			arrItemValue[9] = m_CommAgent.GetFidOutputData(nRequestId, "2456", i);		//가격소수점정보
			arrItemValue[10] = m_CommAgent.GetFidOutputData(nRequestId, "2457", i);		//진법
			arrItemValue[11] = m_CommAgent.GetFidOutputData(nRequestId, "2295", i);		//Tick Size
			arrItemValue[12] = m_CommAgent.GetFidOutputData(nRequestId, "1396", i);		//최소가격변동금액
			arrItemValue[13] = m_CommAgent.GetFidOutputData(nRequestId, "1773", i);		//환산승수
			arrItemValue[14] = m_CommAgent.GetFidOutputData(nRequestId, "1772", i);		//계약단위, 계약크기
			arrItemValue[15] = m_CommAgent.GetFidOutputData(nRequestId, "1731", i);		//위탁증거금
			arrItemValue[16] = m_CommAgent.GetFidOutputData(nRequestId, "2460", i);		//유지증거금
			arrItemValue[17] = m_CommAgent.GetFidOutputData(nRequestId, "226", i);		//상장일자
			arrItemValue[18] = m_CommAgent.GetFidOutputData(nRequestId, "132", i);		//최종거래일(LTD)
			arrItemValue[19] = m_CommAgent.GetFidOutputData(nRequestId, "981", i);		//만기일자(Expire Date)
			arrItemValue[20] = m_CommAgent.GetFidOutputData(nRequestId, "1203", i);		//만기년월(Expire Month / Year)
			arrItemValue[21] = m_CommAgent.GetFidOutputData(nRequestId, "1268", i);		//결제통화(거래통화 ? )
			arrItemValue[22] = m_CommAgent.GetFidOutputData(nRequestId, "1171", i);		//표시통화
			arrItemValue[23] = m_CommAgent.GetFidOutputData(nRequestId, "2459", i);		//근월물순서
			arrItemValue[24] = m_CommAgent.GetFidOutputData(nRequestId, "133", i);		//잔존일수
			arrItemValue[25] = m_CommAgent.GetFidOutputData(nRequestId, "1759", i);		//Active Flag
			arrItemValue[26] = m_CommAgent.GetFidOutputData(nRequestId, "16", i);		//기준가
			arrItemValue[27] = m_CommAgent.GetFidOutputData(nRequestId, "10", i);		//전일종가
			arrItemValue[28] = m_CommAgent.GetFidOutputData(nRequestId, "28", i);		//전일거래량
			arrItemValue[29] = m_CommAgent.GetFidOutputData(nRequestId, "1762", i);		//거래가능 여부
			arrItemValue[30] = m_CommAgent.GetFidOutputData(nRequestId, "1870", i);		//시작시간
			arrItemValue[31] = m_CommAgent.GetFidOutputData(nRequestId, "1871", i);		//종료시간
			arrItemValue[32] = m_CommAgent.GetFidOutputData(nRequestId, "2486", i);		//장시작시간(한국)
			arrItemValue[33] = m_CommAgent.GetFidOutputData(nRequestId, "2487", i);		//장종료시간(한국)
			arrItemValue[34] = m_CommAgent.GetFidOutputData(nRequestId, "815", i);		//직전거래일
			arrItemValue[35] = m_CommAgent.GetFidOutputData(nRequestId, "9", i);			//현영업일, 거래일자
			arrItemValue[36] = m_CommAgent.GetFidOutputData(nRequestId, "128", i);		//상장후고가
			arrItemValue[37] = m_CommAgent.GetFidOutputData(nRequestId, "129", i);		//상장후저가
			arrItemValue[38] = m_CommAgent.GetFidOutputData(nRequestId, "2596", i);		//세부거래소코드

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listCode.InsertItem(&lvItem);

			//리스트 컨트롤에 항목별 값을 입력한다.
			for (int col = 0; col < 39; col++)
			{
				m_listCode.SetItemText(nListIndex, col, (LPTSTR)(LPCTSTR)arrItemValue[col]);
			}


		}//End of for

		m_listCode.EnsureVisible(nViewScrollPos, FALSE);
		m_listCode.SetRedraw(TRUE);

		/*--------------------------------------
		연속조회키를 저장해 놓는다.
		---------------------------------------*/
		m_strCodeListNextRqKey = strPreNextContext;

		/*--------------------------------------
		연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_CODE_LIST_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_CODE_LIST_NEXT)->EnableWindow(FALSE);
		
		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdCodeList = 0;	//해외선물 종목 리스트(마스터) 조회 Request ID
	}
	/***************************************
	* 해외옵션 종목 리스트(마스터) 조회 데이터 수신 처리
	****************************************/
	else if (m_nRqIdCodeList2 == nRequestId)
	{
		CString strCode;			//단축코드
		CString strStandardCode;	//표준코드
		CString strCodeName;		//한글종목명
		CString strPrice;			//기준가

		m_listCode2.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;

		/*--------------------------------------
		다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		붙여 삽입한다.
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
			FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
			---------------------------------------*/
			arrItemValue[0] = m_CommAgent.GetFidOutputData(nRequestId, "1", i);			//종목코드(내부)
			arrItemValue[1] = m_CommAgent.GetFidOutputData(nRequestId, "2", i);			//시세종목코드
			arrItemValue[2] = m_CommAgent.GetFidOutputData(nRequestId, "3", i);			//해외파생상품명
			arrItemValue[3] = m_CommAgent.GetFidOutputData(nRequestId, "1448", i);		//품목코드
			arrItemValue[4] = m_CommAgent.GetFidOutputData(nRequestId, "2083", i);		//해외파생품목명
			arrItemValue[5] = m_CommAgent.GetFidOutputData(nRequestId, "661", i);		//행사가격
			arrItemValue[6] = m_CommAgent.GetFidOutputData(nRequestId, "1170", i);		//국가코드
			arrItemValue[7] = m_CommAgent.GetFidOutputData(nRequestId, "1987", i);		//거래소코드
			arrItemValue[8] = m_CommAgent.GetFidOutputData(nRequestId, "2467", i);		//품목유형구분명
			arrItemValue[9] = m_CommAgent.GetFidOutputData(nRequestId, "2456", i);		//가격소수점정보
			arrItemValue[10] = m_CommAgent.GetFidOutputData(nRequestId, "2457", i);		//진법
			arrItemValue[11] = m_CommAgent.GetFidOutputData(nRequestId, "2295", i);		//Tick Size
			arrItemValue[12] = m_CommAgent.GetFidOutputData(nRequestId, "1396", i);		//최소가격변동금액
			arrItemValue[13] = m_CommAgent.GetFidOutputData(nRequestId, "1773", i);		//환산승수
			arrItemValue[14] = m_CommAgent.GetFidOutputData(nRequestId, "1772", i);		//계약단위, 계약크기
			arrItemValue[15] = m_CommAgent.GetFidOutputData(nRequestId, "1731", i);		//위탁증거금
			arrItemValue[16] = m_CommAgent.GetFidOutputData(nRequestId, "2460", i);		//유지증거금
			arrItemValue[17] = m_CommAgent.GetFidOutputData(nRequestId, "226", i);		//상장일자
			arrItemValue[18] = m_CommAgent.GetFidOutputData(nRequestId, "132", i);		//최종거래일(LTD)
			arrItemValue[19] = m_CommAgent.GetFidOutputData(nRequestId, "981", i);		//만기일자(Expire Date)
			arrItemValue[20] = m_CommAgent.GetFidOutputData(nRequestId, "1203", i);		//만기년월(Expire Month / Year)
			arrItemValue[21] = m_CommAgent.GetFidOutputData(nRequestId, "1268", i);		//결제통화(거래통화 ? )
			arrItemValue[22] = m_CommAgent.GetFidOutputData(nRequestId, "1171", i);		//표시통화
			arrItemValue[23] = m_CommAgent.GetFidOutputData(nRequestId, "2459", i);		//근월물순서
			arrItemValue[24] = m_CommAgent.GetFidOutputData(nRequestId, "133", i);		//잔존일수
			arrItemValue[25] = m_CommAgent.GetFidOutputData(nRequestId, "1759", i);		//Active Flag
			arrItemValue[26] = m_CommAgent.GetFidOutputData(nRequestId, "16", i);		//기준가
			arrItemValue[27] = m_CommAgent.GetFidOutputData(nRequestId, "10", i);		//전일종가
			arrItemValue[28] = m_CommAgent.GetFidOutputData(nRequestId, "28", i);		//전일거래량
			arrItemValue[29] = m_CommAgent.GetFidOutputData(nRequestId, "1762", i);		//거래가능 여부
			arrItemValue[30] = m_CommAgent.GetFidOutputData(nRequestId, "1870", i);		//시작시간
			arrItemValue[31] = m_CommAgent.GetFidOutputData(nRequestId, "1871", i);		//종료시간
			arrItemValue[32] = m_CommAgent.GetFidOutputData(nRequestId, "2486", i);		//장시작시간(한국)
			arrItemValue[33] = m_CommAgent.GetFidOutputData(nRequestId, "2487", i);		//장종료시간(한국)
			arrItemValue[34] = m_CommAgent.GetFidOutputData(nRequestId, "815", i);		//직전거래일
			arrItemValue[35] = m_CommAgent.GetFidOutputData(nRequestId, "9", i);			//현영업일, 거래일자
			arrItemValue[36] = m_CommAgent.GetFidOutputData(nRequestId, "128", i);		//상장후고가
			arrItemValue[37] = m_CommAgent.GetFidOutputData(nRequestId, "129", i);		//상장후저가
			arrItemValue[38] = m_CommAgent.GetFidOutputData(nRequestId, "2596", i);		//세부거래소코드

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listCode2.InsertItem(&lvItem);

			//리스트 컨트롤에 항목별 값을 입력한다.
			for (int col = 0; col < 39; col++)
			{
				m_listCode2.SetItemText(nListIndex, col, (LPTSTR)(LPCTSTR)arrItemValue[col]);
			}


		}//End of for

		m_listCode2.EnsureVisible(nViewScrollPos, FALSE);
		m_listCode2.SetRedraw(TRUE);

		/*--------------------------------------
		연속조회키를 저장해 놓는다.
		---------------------------------------*/
		m_strCodeListNextRqKey2 = strPreNextContext;

		/*--------------------------------------
		연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_CODE_LIST_NEXT2)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_CODE_LIST_NEXT2)->EnableWindow(FALSE);

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdCodeList2 = 0;	//해외선물 종목 리스트(마스터) 조회 Request ID
	}
	/***************************************
	* 해외선물 5단계호가 조회 데이터 수신 처리
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
		FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
		---------------------------------------*/
		//매도호가/잔량
		arrSellHoga[0] = m_CommAgent.GetFidOutputData(nRequestId, "29", 0);	//매도 1호가
		arrSellHoga[1] = m_CommAgent.GetFidOutputData(nRequestId, "30", 0);	//매도 2호가
		arrSellHoga[2] = m_CommAgent.GetFidOutputData(nRequestId, "31", 0);	//매도 3호가
		arrSellHoga[3] = m_CommAgent.GetFidOutputData(nRequestId, "32", 0);	//매도 4호가
		arrSellHoga[4] = m_CommAgent.GetFidOutputData(nRequestId, "33", 0);	//매도 5호가
		arrSellRemain[0] = m_CommAgent.GetFidOutputData(nRequestId, "63", 0);	//매도 1호가잔량
		arrSellRemain[1] = m_CommAgent.GetFidOutputData(nRequestId, "64", 0);	//매도 2호가잔량
		arrSellRemain[2] = m_CommAgent.GetFidOutputData(nRequestId, "65", 0);	//매도 3호가잔량
		arrSellRemain[3] = m_CommAgent.GetFidOutputData(nRequestId, "66", 0);	//매도 4호가잔량
		arrSellRemain[4] = m_CommAgent.GetFidOutputData(nRequestId, "67", 0);	//매도 5호가잔량
		arrSellCnt[0] = m_CommAgent.GetFidOutputData(nRequestId, "196", 0);		//매도 1호가건수
		arrSellCnt[1] = m_CommAgent.GetFidOutputData(nRequestId, "197", 0);		//매도 2호가건수
		arrSellCnt[2] = m_CommAgent.GetFidOutputData(nRequestId, "198", 0);		//매도 3호가건수
		arrSellCnt[3] = m_CommAgent.GetFidOutputData(nRequestId, "199", 0);		//매도 4호가건수
		arrSellCnt[4] = m_CommAgent.GetFidOutputData(nRequestId, "200", 0);		//매도 5호가건수

		//매수호가/잔량
		arrBuyHoga[0] = m_CommAgent.GetFidOutputData(nRequestId, "39", 0);		//매수 1호가
		arrBuyHoga[1] = m_CommAgent.GetFidOutputData(nRequestId, "40", 0);		//매수 2호가
		arrBuyHoga[2] = m_CommAgent.GetFidOutputData(nRequestId, "41", 0);		//매수 3호가
		arrBuyHoga[3] = m_CommAgent.GetFidOutputData(nRequestId, "42", 0);		//매수 4호가
		arrBuyHoga[4] = m_CommAgent.GetFidOutputData(nRequestId, "43", 0);		//매수 5호가
		arrBuyRemain[0] = m_CommAgent.GetFidOutputData(nRequestId, "73", 0);	//매수 1호가잔량
		arrBuyRemain[1] = m_CommAgent.GetFidOutputData(nRequestId, "74", 0);	//매수 2호가잔량
		arrBuyRemain[2] = m_CommAgent.GetFidOutputData(nRequestId, "75", 0);	//매수 3호가잔량
		arrBuyRemain[3] = m_CommAgent.GetFidOutputData(nRequestId, "76", 0);	//매수 4호가잔량
		arrBuyRemain[4] = m_CommAgent.GetFidOutputData(nRequestId, "77", 0);	//매수 5호가잔량
		arrBuyCnt[0] = m_CommAgent.GetFidOutputData(nRequestId, "201", 0);		//매수 1호가건수
		arrBuyCnt[1] = m_CommAgent.GetFidOutputData(nRequestId, "202", 0);		//매수 2호가건수
		arrBuyCnt[2] = m_CommAgent.GetFidOutputData(nRequestId, "203", 0);		//매수 3호가건수
		arrBuyCnt[3] = m_CommAgent.GetFidOutputData(nRequestId, "204", 0);		//매수 4호가건수
		arrBuyCnt[4] = m_CommAgent.GetFidOutputData(nRequestId, "205", 0);		//매수 5호가건수

		/*--------------------------------------
		조회된 수신 데이터를 화면 컨트롤에 표시한다.
		---------------------------------------*/
		SetHogaData(arrSellHoga, arrBuyHoga, arrSellRemain, arrBuyRemain, arrSellCnt, arrBuyCnt);

		/*--------------------------------------
		해외선물호가 실시간키로 실시간을 등록한다.
		실시간 등록은 첫 조회 시 한번만 한다.
		---------------------------------------*/
		if (!m_strHogaRealKey.IsEmpty())
		{
			CString strRealName;

			if (((CButton*)GetDlgItem(IDC_RAD_QRY1))->GetCheck())
			{
				strRealName = _T("V11"); //해외선물체결 Real name
			}
			else
			{
				strRealName = _T("V21"); //해외옵션체결 Real name
			}

			m_CommAgent.RegisterReal(strRealName, m_strHogaRealKey); //실시간 등록
		}

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdHoga = 0;	//해외선물 5단계호가 조회 Request ID
	}
	/***************************************
	* 해외선물 현재가 조회 데이터 수신 처리
	****************************************/
	else if (m_nRqIdCurPrice == nRequestId)
	{
		/*--------------------------------------
		FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
		---------------------------------------*/
		CString strCurPrice = m_CommAgent.GetFidOutputData(nRequestId, "4", 0);		//현재가
		CString strDiffSign = m_CommAgent.GetFidOutputData(nRequestId, "6", 0);		//부호
		CString strDiff = m_CommAgent.GetFidOutputData(nRequestId, "5", 0);			//전일대비
		CString strDiffRate = m_CommAgent.GetFidOutputData(nRequestId, "7", 0);		//대비율
		CString strVolume = m_CommAgent.GetFidOutputData(nRequestId, "11", 0);		//거래량
		CString strPreVolume = m_CommAgent.GetFidOutputData(nRequestId, "28", 0);	//전일거래량
		CString strOpenPrice = m_CommAgent.GetFidOutputData(nRequestId, "13", 0);	//시가
		CString strHighPrice = m_CommAgent.GetFidOutputData(nRequestId, "14", 0);	//고가
		CString strLowPrice = m_CommAgent.GetFidOutputData(nRequestId, "15", 0);	//저가

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
		지선물 체결(현재가) 실시간등록키로 실시간을 등록한다.
		실시간 등록은 첫 조회 시 한번만 한다.
		---------------------------------------*/
		if (!m_strCurPriceRealKey.IsEmpty())
		{
			CString strRealName;

			if (((CButton*)GetDlgItem(IDC_RAD_QRY5))->GetCheck())
			{
				strRealName = _T("V10"); //해외선물체결 Real name
			}
			else
			{
				strRealName = _T("V20"); //해외옵션체결 Real name
			}

			m_CommAgent.RegisterReal(strRealName, m_strCurPriceRealKey); //실시간 등록
		}

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdCurPrice = 0;	//해외선물 현재가 조회 Request ID
	}
	/***************************************
	* 해외선물 시간대별체결 조회 데이터 수신 처리
	****************************************/
	else if (m_nRqIdTick == nRequestId)
	{
		CString strTime;		//시간
		CString strPrice;		//체결가
		CString strDiff;		//대비
		CString strDiffRate;	//등률
		CString strVolume;		//체결량

		m_listTick.SetRedraw(FALSE);
		LV_ITEM	lvItem;

		int nListIndex = 0;

		/*--------------------------------------
		다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		붙여 삽입한다.
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
			FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
			---------------------------------------*/
			strTime = m_CommAgent.GetFidOutputData(nRequestId, "8", i);	//시간
			strPrice = m_CommAgent.GetFidOutputData(nRequestId, "4", i);	//체결가
			strDiff = m_CommAgent.GetFidOutputData(nRequestId, "5", i);	//대비
			strDiffRate = m_CommAgent.GetFidOutputData(nRequestId, "7", i);	//등률
			strVolume = m_CommAgent.GetFidOutputData(nRequestId, "83", i);//체결량

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listTick.InsertItem(&lvItem);

			m_listTick.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strTime);	//시간
			m_listTick.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strPrice);	//체결가
			m_listTick.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strDiff);	//대비
			m_listTick.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strDiffRate);//등률
			m_listTick.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strVolume);	//체결량
		}

		m_listTick.EnsureVisible(nViewScrollPos, FALSE);
		m_listTick.SetRedraw(TRUE);

		/*--------------------------------------
		선물체결 실시간을 등록한다.
		실시간 등록은 첫 조회 시 한번만 한다.
		---------------------------------------*/
		if (!m_strTickRealKey.IsEmpty() && m_strTickNextRqKey.IsEmpty())
		{
			CString strRealName;

			if (((CButton*)GetDlgItem(IDC_RAD_QRY3))->GetCheck())
			{
				strRealName = _T("V10"); //해외선물체결 Real name
			}
			else
			{
				strRealName = _T("V20"); //해외옵션체결 Real name
			}

			m_CommAgent.RegisterReal(strRealName, m_strTickRealKey); //실시간 등록
		}

		/*--------------------------------------
		연속조회키를 저장해 놓는다.
		---------------------------------------*/
		m_strTickNextRqKey = strPreNextContext;

		/*--------------------------------------
		연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_TICK_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_TICK_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdTick = 0;	//해외선물 시간대별체결 조회 Request ID

	}
	/***************************************
	* 해외선물 차트 조회 데이터 수신 처리
	****************************************/
	else if (m_nRqIdChart == nRequestId)
	{
		CString arrItem[8];

		m_listChart.SetRedraw(FALSE);
		LV_ITEM	lvItem;
		int nListIndex = 0;
		int nViewScrollPos = 0;

		/*--------------------------------------
		다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		붙여 삽입한다.
		---------------------------------------*/
		if (!m_strChartNextRqKey.IsEmpty())
		{
			nListIndex = m_listChart.GetItemCount();
			nViewScrollPos = nListIndex;
		}

#if 1	/***************************************
		* 수신데이터를 직접 추출한다.(C++에서만 사용 가능)
		* 종목리스트, 차트 데이터 같은 대량의 데이터 처리 시
		* 에이전트 컨트롤의 GetFidOutputData 함수 호출보다 빠른 성능을 보인다.
		****************************************/

		CCommRecvData fidCommRecvData;
		int nVecRowCnt = 0;	//데이터 건수(행)
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
			FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
			---------------------------------------*/
			arrItem[0] = fidCommRecvData.GetItem(i, 0);	//0009 : 일자
			arrItem[1] = fidCommRecvData.GetItem(i, 1);	//0008 : 시간
			arrItem[2] = fidCommRecvData.GetItem(i, 2);	//0004 : 종가
			arrItem[3] = fidCommRecvData.GetItem(i, 3);	//0013 : 시가
			arrItem[4] = fidCommRecvData.GetItem(i, 4);	//0014 : 고가
			arrItem[5] = fidCommRecvData.GetItem(i, 5);	//0015 : 저가
			arrItem[6] = fidCommRecvData.GetItem(i, 6);	//0083 : 체결량
			arrItem[7] = fidCommRecvData.GetItem(i, 7);	//0011 : 거래량

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listChart.InsertItem(&lvItem);

			//리스트 컨트롤에 항목별 데이타 입력
			for (int col = 0; col < 8; col++)
			{
				m_listChart.SetItemText(nListIndex, col, (LPTSTR)(LPCTSTR)arrItem[col]);
			}

		}//End of for

#else	/***************************************
		* 에이전트 컨트롤을 통해 간적접으로 항목별 데이타를 빼낸다.
		****************************************/
		int nDataCnt = m_CommAgent.GetFidOutputRowCnt(nRequestId);

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
			---------------------------------------*/
			arrItem[0] = m_CommAgent.GetFidOutputData(nRequestId, "9", i);	//0009 : 일자
			arrItem[1] = m_CommAgent.GetFidOutputData(nRequestId, "8", i);	//0008 : 시간
			arrItem[2] = m_CommAgent.GetFidOutputData(nRequestId, "4", i);	//0004 : 종가
			arrItem[3] = m_CommAgent.GetFidOutputData(nRequestId, "13", i);	//0013 : 시가
			arrItem[4] = m_CommAgent.GetFidOutputData(nRequestId, "14", i);	//0014 : 고가
			arrItem[5] = m_CommAgent.GetFidOutputData(nRequestId, "15", i);	//0015 : 저가
			arrItem[6] = m_CommAgent.GetFidOutputData(nRequestId, "83", i);	//0083 : 체결량
			arrItem[7] = m_CommAgent.GetFidOutputData(nRequestId, "11", i);	//0011 : 거래량

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listChart.InsertItem(&lvItem);

			//리스트 컨트롤에 항목별 데이타 입력
			for (int col = 0; col < 8; col++)
			{
				m_listChart.SetItemText(nListIndex, col, (LPTSTR)(LPCTSTR)arrItem[col]);
			}

		}//End of for
#endif

		m_listChart.EnsureVisible(nViewScrollPos, FALSE);
		m_listChart.SetRedraw(TRUE);

		/*--------------------------------------
		연속조회키를 저장해 놓는다.
		---------------------------------------*/
		m_strChartNextRqKey = strPreNextContext;

		/*--------------------------------------
		연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
		---------------------------------------*/
		if (!_tcscmp(strPreNext, _T("2")) || !_tcscmp(strPreNext, _T("3")))
			GetDlgItem(IDC_BTN_REQ_CHART_NEXT)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BTN_REQ_CHART_NEXT)->EnableWindow(FALSE);

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdChart = 0;	//해외선물 종목 리스트(마스터) 조회 Request ID

		/*--------------------------------------
		자동 다음 조회
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
// Function      : 실시간 데이터를 수신한다.
// Param         :	LPCTSTR strRealName : 실시간 코드명
//					LPCTSTR strRealKey : 실시간 등록키
//					LPCTSTR pBlock, 조회응답 데이터 블럭
//					long nBlockLength 조회응답 데이터 블럭 크기
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CForeignFutSiseDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/* 주의 : OnGetRealData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
	이벤트 콜백함수 종료 후에는 유효하지 않습니다.*/

	/***************************************
	* 해외선물 호가 실시간 데이터 수신
	****************************************/
	if (!_tcscmp(strRealName, "V11") ||
		!_tcscmp(strRealName, "V21"))
	{
		/*--------------------------------------
		조회 시점에 등록한 해외선물 호가 실시간키와 동일한지 비교
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
			수신된 실시간 데이터를 직접 빼낸다.(C++에서만 사용 가능)
			대량의 실시간 데이터 처리 시에는 에이전트 컨트롤 GetRealOutputData 함수 호출보다 빠른 성능을 보인다.
			---------------------------------------*/
			CCommRecvData realCommRecvData;
			int nItemCnt = 0;		//항목 건수

			//FID 조회응답 데이터 메모리를 얻어온다.(C++에서만 사용 가능)
			if (m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData) == TRUE)
				nItemCnt = realCommRecvData.GetColCnt();		//항목 건수

			//F01.res 파일의  INDEX필드 번호를 인덱스로 사용한다.
			arrSellHoga[0] = realCommRecvData.GetItem(0, 29);		//매도1호가
			arrSellHoga[1] = realCommRecvData.GetItem(0, 33);		//매도2호가
			arrSellHoga[2] = realCommRecvData.GetItem(0, 37);		//매도3호가
			arrSellHoga[3] = realCommRecvData.GetItem(0, 41);		//매도4호가
			arrSellHoga[4] = realCommRecvData.GetItem(0, 45);	//매도5호가SEQ필

			arrSellRemain[0] = realCommRecvData.GetItem(0, 31);	//매도1호가잔량
			arrSellRemain[1] = realCommRecvData.GetItem(0, 35);	//매도2호가잔량
			arrSellRemain[2] = realCommRecvData.GetItem(0, 39);	//매도3호가잔량
			arrSellRemain[3] = realCommRecvData.GetItem(0, 43);	//매도4호가잔량
			arrSellRemain[4] = realCommRecvData.GetItem(0, 47);	//매도5호가잔량

			arrSellCnt[0] = realCommRecvData.GetItem(0, 32);		//매도1호가건수
			arrSellCnt[1] = realCommRecvData.GetItem(0, 36);		//매도2호가건수
			arrSellCnt[2] = realCommRecvData.GetItem(0, 40);		//매도3호가건수
			arrSellCnt[3] = realCommRecvData.GetItem(0, 44);		//매도4호가건수
			arrSellCnt[4] = realCommRecvData.GetItem(0, 48);		//매도5호가건수

			arrBuyHoga[0] = realCommRecvData.GetItem(0, 7);		//매수1호가
			arrBuyHoga[1] = realCommRecvData.GetItem(0, 11);		//매수2호가
			arrBuyHoga[2] = realCommRecvData.GetItem(0, 15);		//매수3호가
			arrBuyHoga[3] = realCommRecvData.GetItem(0, 19);		//매수4호가
			arrBuyHoga[4] = realCommRecvData.GetItem(0, 23);		//매수5호가

			arrBuyRemain[0] = realCommRecvData.GetItem(0, 9);	//매수1호가잔량
			arrBuyRemain[1] = realCommRecvData.GetItem(0, 13);	//매수2호가잔량
			arrBuyRemain[2] = realCommRecvData.GetItem(0, 17);	//매수3호가잔량
			arrBuyRemain[3] = realCommRecvData.GetItem(0, 21);	//매수4호가잔량
			arrBuyRemain[4] = realCommRecvData.GetItem(0, 25);	//매수5호가잔량

			arrBuyCnt[0] = realCommRecvData.GetItem(0, 10);		//매수1호가건수
			arrBuyCnt[1] = realCommRecvData.GetItem(0, 14);		//매수2호가건수
			arrBuyCnt[2] = realCommRecvData.GetItem(0, 18);		//매수3호가건수
			arrBuyCnt[3] = realCommRecvData.GetItem(0, 22);		//매수4호가건수
			arrBuyCnt[4] = realCommRecvData.GetItem(0, 26);		//매수5호가건수

#else		/*--------------------------------------
			에이전트 컨트롤의 GetRealOutputData 함수로 아이템별 데이터를 빼낸다.
			---------------------------------------*/
			/*--------------------------------------
			아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
			---------------------------------------*/
			//매도 1~5호가
			arrSellHoga[0] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASK1");
			arrSellHoga[1] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASK2");
			arrSellHoga[2] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASK3");
			arrSellHoga[3] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASK4");
			arrSellHoga[4] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASK5");
			//매도 1~5호가잔량
			arrSellRemain[0] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASIZ1");
			arrSellRemain[1] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASIZ2");
			arrSellRemain[2] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASIZ3");
			arrSellRemain[3] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASIZ4");
			arrSellRemain[4] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ASIZ5");
			//매도 1~5호가건수
			arrSellCnt[0] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ACNT1");
			arrSellCnt[1] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ACNT2");
			arrSellCnt[2] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ACNT3");
			arrSellCnt[3] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ACNT4");
			arrSellCnt[4] = m_CommAgent.GetRealOutputData(strRealName, "BEST_ACNT5");

			//매수 1~5호가
			arrBuyHoga[0] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BID1");
			arrBuyHoga[1] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BID2");
			arrBuyHoga[2] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BID3");
			arrBuyHoga[3] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BID4");
			arrBuyHoga[4] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BID5");
			//매수 1~5호가잔량
			arrBuyRemain[0] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BSIZ1");
			arrBuyRemain[1] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BSIZ2");
			arrBuyRemain[2] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BSIZ3");
			arrBuyRemain[3] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BSIZ4");
			arrBuyRemain[4] = m_CommAgent.GetRealOutputData(strRealName, "BEST_BSIZ5");
			//매수 1~5호가건수
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
	* 해외선물 체결(현재가) 실시간 데이터 수신
	****************************************/
	else if (!_tcscmp(strRealName, "V10") ||
			!_tcscmp(strRealName, "V20"))
	{
		/*--------------------------------------
		아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
		---------------------------------------*/
		CString strCurPrice = m_CommAgent.GetRealOutputData(strRealName, "TRDPRC_1");		//현재가
		CString strDiffSign = m_CommAgent.GetRealOutputData(strRealName, "NETCHNG_CLS");	//부호
		CString strDiff = m_CommAgent.GetRealOutputData(strRealName, "NETCHNG_1");			//전일대비
		CString strDiffRate = m_CommAgent.GetRealOutputData(strRealName, "PCTCHNG_1");		//대비율
		CString strVolume = m_CommAgent.GetRealOutputData(strRealName, "ACVOL_1");			//거래량

		CString strOpenPrice = m_CommAgent.GetRealOutputData(strRealName, "OPEN_PRC");		//시가
		CString strHighPrice = m_CommAgent.GetRealOutputData(strRealName, "HIGH_1");		//고가
		CString strLowPrice = m_CommAgent.GetRealOutputData(strRealName, "LOW_1");			//저가

		CString strTime = m_CommAgent.GetRealOutputData(strRealName, "TRADE_TIME");			//체결시간
		CString strExecVolume = m_CommAgent.GetRealOutputData(strRealName, "TRDVOL_1");		//체결량

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
		조회 시점에 등록한 해외선물 현재가 실시간키와 동일한지 비교
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
		조회 시점에 등록한 해외선물 시간대별 체결 실시간키와 동일한지 비교
		---------------------------------------*/
		if (m_strTickRealKey == strRealKey)
		{
			m_listTick.SetRedraw(FALSE);


			int nListRowCnt = m_listTick.GetItemCount();

			//데이터 500건이 넘으면 100건만 남기고 지운다.
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

			m_listTick.SetItemText(0, 0, (LPTSTR)(LPCTSTR)strTime);			//시간
			m_listTick.SetItemText(0, 1, (LPTSTR)(LPCTSTR)strCurPrice);		//체결가
			m_listTick.SetItemText(0, 2, (LPTSTR)(LPCTSTR)strDiff);			//대비
			m_listTick.SetItemText(0, 3, (LPTSTR)(LPCTSTR)strDiffRate);		//등률
			m_listTick.SetItemText(0, 4, (LPTSTR)(LPCTSTR)strExecVolume);	//체결량

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	CString strSymBol;			//종목코드
	m_editSymbolPrice.GetWindowText(strSymBol); //종목코드
	strSymBol.Trim();
	if (strSymBol.IsEmpty())
	{
		::AfxMessageBox("종목코드 입력은 필수입니다!");
		m_editSymbolPrice.SetFocus();
		return;
	}

	CString strRealName;

	if (((CButton*)GetDlgItem(IDC_RAD_QRY5))->GetCheck())
	{
		strRealName = _T("V10"); //해외선물체결 Real name
	}
	else
	{
		strRealName = _T("V20"); //해외옵션체결 Real name
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	/**********************************
	* 1. 연속조회키 초기화
	**********************************/
	m_strCodeListNextRqKey2.Empty();

	//해외선물 종목 리스트(마스터) 컨트롤 데이터 초기화
	m_listCode2.DeleteAllItems();

	/**********************************
	* 2. 통신조회 Request ID를 생성한다.
	**********************************/
	m_nRqIdCodeList2 = m_CommAgent.CreateRequestID();

	if (m_nRqIdCodeList2 == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	CString strMarketCode;		//시장구분코드
	strMarketCode = _T("FO");	//해외선물

	/**********************************
	* 3. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList2, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdCodeList2, _T("GID"), _T("4499"));		//GID

	//서버에서 내려받을 출력항목들.
	CString strOutputFidList;

	/**********************************
	* 4. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	0001 : 종목코드(내부)
	0002 : 시세종목코드
	0003 : 해외파생상품명
	1448 : 품목코드
	2083 : 해외파생품목명
	0661 : 행사가격
	1170 : 국가코드
	1987 : 거래소코드
	2467 : 품목유형구분명
	2456 : 가격소수점정보
	2457 : 진법
	2295 : Tick Size
	1396 : 최소가격변동금액
	1773 : 환산승수
	1772 : 계약단위, 계약크기
	1731 : 위탁증거금
	2460 : 유지증거금
	0226 : 상장일자
	0132 : 최종거래일(LTD)
	0981 : 만기일자(Expire Date)
	1203 : 만기년월(Expire Month/Year)
	1268 : 결제통화(거래통화?)
	1171 : 표시통화
	2459 : 근월물순서
	0133 : 잔존일수
	1759 : Active Flag
	0016 : 기준가
	0010 : 전일종가
	0028 : 전일거래량
	1762 : 거래가능 여부
	1870 : 시작시간
	1871 : 종료시간
	2486 : 장시작시간(한국)
	2487 : 장종료시간(한국)
	0815 : 직전거래일
	0009 : 현영업일, 거래일자
	0128 : 상장후고가
	0129 : 상장후저가
	2596 : 세부거래소코드*/
	strOutputFidList = "1,2,3,1448,2083,661,1170,1987,2467,2456,2457,2295,1396,"
		"1773,1772,1731,2460,226,132,981,1203,1268,1171,"
		"2459,133,1759,16,10,28,1762,1870,1871,2486,2487,"
		"815,9,128,129, 2596";

	CString strScreenNo;
	strScreenNo = "9999";

	//연속조회 옵션 : '0':미사용, '1'사용, '2' : 이전 데이터 조회, '3' : 다음 데이터 조회
	CString strPreNext = "1";

	/**********************************
	* 5. 서버에 통신조회 요청한다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
	}

	/**********************************
	* 1. 통신조회 Request ID를 생성한다.
	**********************************/
	m_nRqIdCodeList2 = m_CommAgent.CreateRequestID();
	if (m_nRqIdCodeList2 == -1)
	{
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
		return;
	}

	CString strMarketCode;		//시장구분코드
	strMarketCode = _T("FO"); //해외옵션

	/**********************************
	* 2. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList2, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdCodeList2, _T("GID"), _T("4499"));		//GID

	//통신조회 응답으로 받을 데이터 항목(FID)
	CString strOutputFidList;

	/**********************************
	* 3. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	0001 : 종목코드(내부)
	0002 : 시세종목코드
	0003 : 해외파생상품명
	1448 : 품목코드
	2083 : 해외파생품목명
	0661 : 행사가격
	1170 : 국가코드
	1987 : 거래소코드
	2467 : 품목유형구분명
	2456 : 가격소수점정보
	2457 : 진법
	2295 : Tick Size
	1396 : 최소가격변동금액
	1773 : 환산승수
	1772 : 계약단위, 계약크기
	1731 : 위탁증거금
	2460 : 유지증거금
	0226 : 상장일자
	0132 : 최종거래일(LTD)
	0981 : 만기일자(Expire Date)
	1203 : 만기년월(Expire Month/Year)
	1268 : 결제통화(거래통화?)
	1171 : 표시통화
	2459 : 근월물순서
	0133 : 잔존일수
	1759 : Active Flag
	0016 : 기준가
	0010 : 전일종가
	0028 : 전일거래량
	1762 : 거래가능 여부
	1870 : 시작시간
	1871 : 종료시간
	2486 : 장시작시간(한국)
	2487 : 장종료시간(한국)
	0815 : 직전거래일
	0009 : 현영업일, 거래일자
	0128 : 상장후고가
	0129 : 상장후저가
	2596 : 세부거래소코드*/
	strOutputFidList = "1,2,3,1448,2083,661,1170,1987,2467,2456,2457,2295,1396,"
		"1773,1772,1731,2460,226,132,981,1203,1268,1171,"
		"2459,133,1759,16,10,28,1762,1870,1871,2486,2487,"
		"815,9,128,129,2596";

	CString strScreenNo;
	strScreenNo = "9999";

	CString strPreNext = "3"; //다음 데이터 조회

	/**********************************
	* 4. 서버에 통신조회 요청한다.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList2, strOutputFidList, strPreNext, m_strCodeListNextRqKey2, strScreenNo, 1000);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}
