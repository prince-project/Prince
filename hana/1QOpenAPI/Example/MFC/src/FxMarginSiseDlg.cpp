/*----------------------------------------*
| 프로그램명 : 하나금융투자 Open API 예제
| 버      전 : v 
| 배포  일자 :
| 기      타 :
*----------------------------------------*/
// FxMarginSiseDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "HFCommClient.h"
#include "FxMarginSiseDlg.h"

#define ID_SECOND_TIMER		100	//1초 간격 타이머

#define SELL_BK_COLOR		RGB(206, 232, 255)	//매도 배경색
#define BUY_BK_COLOR		RGB(251, 221, 255)	//매수 배경색

//통신 구조체 헤더

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

// CFxMarginSiseDlg 대화 상자
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

	m_nSeverType = 0;	//0-리얼, 1-국내모의, 2-해외무의
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

// agent로부터 이벤트 수신 함수를 정의한다.
BEGIN_EVENTSINK_MAP(CFxMarginSiseDlg, CDialog)
	ON_EVENT(CFxMarginSiseDlg, IDC_HFCOMMAGENTCTRL1, 1, CFxMarginSiseDlg::OnGetTranData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CFxMarginSiseDlg, IDC_HFCOMMAGENTCTRL1, 2, CFxMarginSiseDlg::OnGetFidData, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CFxMarginSiseDlg, IDC_HFCOMMAGENTCTRL1, 3, CFxMarginSiseDlg::OnGetRealData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
	ON_EVENT(CFxMarginSiseDlg, IDC_HFCOMMAGENTCTRL1, 4, CFxMarginSiseDlg::OnAgentEventHandler, VTS_I4 VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

// CFxMarginSiseDlg 메시지 처리기

void CFxMarginSiseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
void CFxMarginSiseDlg::OnPaint()
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

void CFxMarginSiseDlg::OnRdoSelectServer(UINT nID)
{
	m_nSeverType = nID - IDC_CON_REAL;

	/*----------------------------------
	접속서버를 설정한다.(0 - 리얼, 1 - 국내모의, 2 - 해외모의)
	*----------------------------------*/
	m_CommAgent.SetLoginMode(0, m_nSeverType);
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFxMarginSiseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CFxMarginSiseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CFxMarginSiseDlg::OnDestroy()
{
	//모든 실시간등록을 해제한다.
	m_CommAgent.AllUnRegisterReal();

	m_brushSellBack.DeleteObject();
	m_brushBuyBack.DeleteObject();

	CDialog::OnDestroy();
}

void CFxMarginSiseDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_CommAgent.CommTerminate(TRUE);
	m_bCommConnect = m_CommAgent.CommGetConnectState();

	m_pParentWnd->PostMessage(UM_CHILD_CLOSE, (WPARAM)0, (LPARAM)this);

	CDialog::OnClose();
}

void CFxMarginSiseDlg::OnTimer(UINT_PTR nIDEvent)
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

void CFxMarginSiseDlg::OnNMDblclkListSymbol(NMHDR *pNMHDR, LRESULT *pResult)
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
	m_editSymbolPrice.SetWindowText(strSymbol);	//현재가 종목코드(심볼)
	m_editSymbolTick.SetWindowText(strSymbol);	//시간대별체결 종목코드(심볼)
	m_editSymbolChart.SetWindowText(strSymbol);	//차트 종목코드(심볼)

	GetDlgItem(IDC_SYMBOL_NAME_PRICE)->SetWindowText(strSymbolName);//현재가 종목명
	GetDlgItem(IDC_SYMBOL_NAME_TICK)->SetWindowText(strSymbolName);	//시간대별체결 종목명
	GetDlgItem(IDC_SYMBOL_NAME_CHART)->SetWindowText(strSymbolName);//차트 데이터 종목명

	//입력된 종목코드로 재조회 요청을 한다.
	OnBnClickedBtnReqPrice();	//FX마진 현재가 조회
	OnBnClickedBtnReqTick();	//FX마진 시간대별체결 조회
	OnBnClickedBtnReqChart();	//FX마진 차트데이터 조회
}

void CFxMarginSiseDlg::OnRadioChartTerm(UINT nID)
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
BOOL CFxMarginSiseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CString strTitle;
	strTitle.Format("%s-[FX마진 시세](%s)", PROGRAM_NAME, VERSION_INFO);
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
	* FX마진 시간대별체결가 리스트 컨트롤 초기화
	**********************************/
	InitListTick();

	/**********************************
	* FX마진 종목 리스트 컨트롤 초기화
	**********************************/
	InitListCode();

	/**********************************
	* FX마진 차트 리스트 컨트롤 초기화
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
	//FX마진체결 실시간 I/O 정보 리소스 파일
	if (!m_CommAgent.LoadRealResource(strApidAgentModulePath + "/RealRes/V00.res"))
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
#endif

	//차트 FX마진 라디오 틱으로 선택
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
// Function      : FX마진 시간대별체결 리스트 컨트롤 초기화
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
	TCHAR *strTitle[] = { _T("고시시각"), _T("매도"), _T("매수"), _T("스프레드"), _T("PIP가치") };

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
// Function      : FX마진 종목 리스트 컨트롤 초기화
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
	TCHAR *strTitle[] = { _T("HTS CODE"), _T("1171 - 통화 1"), _T("통화 2"), _T("Quote Mode"),
		_T("가격소수점"), _T("가격소수점보정"), _T("고객소수점"), _T("고객소수점보정"), _T("딜링룸코드"),
		_T("PL계산통화"), _T("PL계산방법"), _T("Pair ID FCM_CD"), _T("FX 상품명"), _T("매입 이자율"),
		_T("매도 이자율"), _T("FDM 매입 이자율"), _T("FDM 매도 이자율") };


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
	TCHAR *strTitle[] = { _T("시간"), _T("일자"), _T("매도시가"), _T("매도고가"), _T("매도저가"),
		_T("매도종가"), _T("대비부호"), _T("매수시가"), _T("매수고가"), _T("매수저가"), _T("매수종가"),
		_T("매도부호"), _T("스프레드") };

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
// Function      : 대비부호
// Param         : CString strSignCode
// Return        : CString 
// Create        :
// Comment       : 
//******************************************************************
CString CFxMarginSiseDlg::GetDiffSign(CString strSignCode)
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
// Function Name : OnBnClickedInitcomm
// Function      : 통신모듈 초기화 및 통신 연결
// Param         : 
// Return        : void 
// Create        :
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedInitcomm()
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
void CFxMarginSiseDlg::OnBnClickedTerminate()
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
void CFxMarginSiseDlg::OnBnClickedLogin()
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
void CFxMarginSiseDlg::OnBnClickedLogout()
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
// Function      : FX마진 종목 리스트 조회
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedBtnReqCodeList()
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

	//FX마진 종목 리스트(마스터) 컨트롤 데이터 초기화
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
	strMarketCode = _T("FX");	//FX마진

	/**********************************
	* 3. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("4199"));		//GID

	//서버에서 내려받을 출력항목들.
	CString strOutputFidList;

	/**********************************
	* 4. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	2609 - HTS CODE
	1171 - 통화 1
	1268 - 통화 2
	2617 - Quote Mode
	2456 - 가격소수점
	2618 - 가격소수점보정
	2619 - 고객소수점
	2620 - 고객소수점보정
	2621 - 딜링룸코드
	2622 - PL계산통화
	2623 - PL계산방법
	0306 - Pair ID FCM_CD
	0003 - FX 상품명
	1222 - 매입 이자율
	1223 - 매도 이자율
	1220 - FDM 매입 이자율
	1221 - FDM 매도 이자율
 */
	strOutputFidList = "2609,1171,1268,2617,2456,2618,2619,2620,2621,2622,"
						"2623,306,3,1222,1223,1220,1221";

	CString strScreenNo;
	strScreenNo = "9999";

	//연속조회 옵션 : '0':미사용, '1'사용, '2' : 이전 데이터 조회, '3' : 다음 데이터 조회
	CString strPreNext = "1";

	/**********************************
	* 5. 서버에 통신조회 요청한다.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, "", strScreenNo, 0);
	if (nReturn < 0)
		::AfxMessageBox(m_CommAgent.GetLastErrMsg());
}

//*******************************************************************
// Function Name : OnBnClickedBtnReqCodeListNext
// Function      : FX마진 종목 리스트 다음 조회
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedBtnReqCodeListNext()
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

	CString strSymBol;			//종목심볼코드
	CString strMarketCode;		//시장구분코드

	m_editSymbolTick.GetWindowText(strSymBol); //종목코드
	strMarketCode = _T("FX"); //FX마진

	/**********************************
	* 2. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdCodeList, _T("GID"), _T("4199"));		//GID

	//통신조회 응답으로 받을 데이터 항목(FID)
	CString strOutputFidList;

	/**********************************
	* 3. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	2609 - HTS CODE
	1171 - 통화 1
	1268 - 통화 2
	2617 - Quote Mode
	2456 - 가격소수점
	2618 - 가격소수점보정
	2619 - 고객소수점
	2620 - 고객소수점보정
	2621 - 딜링룸코드
	2622 - PL계산통화
	2623 - PL계산방법
	0306 - Pair ID FCM_CD
	0003 - FX 상품명
	1222 - 매입 이자율
	1223 - 매도 이자율
	1220 - FDM 매입 이자율
	1221 - FDM 매도 이자율
	*/
	strOutputFidList = "2609,1171,1268,2617,2456,2618,2619,2620,2621,2622,"
		"2623,306,3,1222,1223,1220,1221";


	CString strScreenNo;
	strScreenNo = "9999";

	CString strPreNext = "3"; //다음 데이터 조회

	/**********************************
	* 4. 서버에 통신조회 요청한다.
	**********************************/
	int nReturn = m_CommAgent.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, m_strCodeListNextRqKey, strScreenNo, 0);
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
void CFxMarginSiseDlg::OnBnClickedBtnReqPrice()
{
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
	* 2. 이전에 등록된 FX마진체결(현재가) 실시간등록 해제.
	**********************************/
	if (!m_strCurPriceRealKey.IsEmpty())
	{
		CString strRealName;
		strRealName = _T("V00"); //FX마진체결 Real name

		m_CommAgent.UnRegisterReal(strRealName, m_strCurPriceRealKey);
		m_strCurPriceRealKey.Empty();
	}

	CString strMarketCode;		//시장구분
	strMarketCode = _T("FX");	//FX마진

	//FX마진체결(현재가) 실시간 등록키로 사용할 리얼키(종목코드)
	m_strCurPriceRealKey = strSymBol;

	/**********************************
	* 3. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdCurPrice, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdCurPrice, _T("9002"), strSymBol);		//종목코드
	m_CommAgent.SetFidInputData(m_nRqIdCurPrice, _T("GID"), _T("1000"));		//GID

	//통신조회 응답으로 받을 데이터 항목(FID)
	CString strOutputFidList;

	/**********************************
	* 4. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	매도(29), 매수(39), 스프레드(666), PIP 가치(2468), 고가(14), 저가(15), 이자(S)(1220), 이지(B)(1221)*/
	strOutputFidList = "29,39,666,2468,14,15,1220,1221";

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
// Function Name : OnBnClickedBtnReqTick
// Function      : FX마진 시간대별체결 데이터 조회(연속거래 데이터가 있는 경우)
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedBtnReqTick()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
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

	//FX마진 시간대별체결 리스트 컨트롤 데이터 초기화
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
	* 3. 이전에 등록된 FX마진체결(현재가) 실시간등록 해제.
	**********************************/
	if (!m_strTickRealKey.IsEmpty())
	{
		CString strRealName;
		strRealName = _T("V00");

		m_CommAgent.UnRegisterReal(strRealName, m_strTickRealKey);
		m_strTickRealKey.Empty();
	}

	CString strMarketCode;		//시장구분코드
	strMarketCode = _T("FX");

	//FX마진체결(현재가) 실시간 등록키로 사용할 리얼키(종목코드)
	m_strTickRealKey = strSymBol;

	/**********************************
	 * 4. 통신조회 요청 입력데이터
	 **********************************/
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9002"), strSymBol);		//종목심볼
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9018"), "1");				//입력구간구분
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9119"), "");				//입력분틱
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("GID"), _T("1003"));		//GID

	//서버에서 내려받을 출력항목들.
	CString strOutputFidList;

	/**********************************
	 * 5. 통신조회 응답으로 받을 항목 설정.
	 **********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	고시시각(8), 매도(29), 매수(39), 스프레드(666), PIP가치(2468)*/
	strOutputFidList = "8,29,39,666,2468";

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
// Function      : FX마진 시간대별체결 다음 데이터 조회
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedBtnReqTickNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
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

	CString strMarketCode;		//시장구분코드
	strMarketCode = _T("F"); //FX마진

	/**********************************
	* 2. 통신조회 요청 입력데이터
	**********************************/
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9001"), strMarketCode);	//시장구분코드
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9002"), strSymBol);		//종목심볼
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9018"), "1");				//입력구간구분
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("9119"), "");				//입력분틱
	m_CommAgent.SetFidInputData(m_nRqIdTick, _T("GID"), _T("1003"));		//GID

	//통신조회 응답으로 받을 데이터 항목(FID)
	CString strOutputFidList;

	/**********************************
	* 3. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	고시시각(8), 매도(29), 매수(39), 스프레드(666), PIP가치(2468)*/
	strOutputFidList = "8,29,39,666,2468";

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
// Function      : FX마진 차트 데이터 조회
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedBtnReqChart()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
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

	//FX마진 시간대별체결 리스트 컨트롤 데이터 초기화
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

	CString strMarketCode;		//시장구분코드
	strMarketCode = _T("FX");

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
		if (_ttoi(strChartCnt) > 0)
		{
			nRecvCnt = _ttoi(strChartCnt);
			m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strChartCnt);	//9119 : 틱 건수
		}

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1003")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MIN))->GetCheck()) //분
	{
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
	0008 - 시간
	0009 - 일자
	0030 - 매도시가
	0031 - 매도고가
	0032 - 매도저가
	0033 - 매도종가
	0006 - 전일대비부호(실제필드명 : 매수 부호)
	0040 - 매수시가
	0041 - 매수고가
	0042 - 매수저가
	0043 - 매수종가
	1098 - 매도부호
	0666 - 스프레드*/
	strOutputFidList = "8,9,30,31,32,33,6,40,41,42,43,1098,666";

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
// Function      : FX마진 차트 다음 데이터 조회
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CFxMarginSiseDlg::OnBnClickedBtnReqChartNext()
{
	if (!m_bCommConnect)
	{
		::AfxMessageBox("통신 접속이 끊겼습니다!");
		return;
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

	CString strMarketCode;		//시장구분코드
	strMarketCode = _T("F"); //FX마진

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
	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9034"), strFromDate);	//시작일
	m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9035"), strToDate);	//종료일

	if (((CButton*)GetDlgItem(IDC_RADIO_TICK))->GetCheck()) //틱
	{
		if (_ttoi(strChartCnt) > 0)
		{
			nRecvCnt = _ttoi(strChartCnt);
			m_CommAgent.SetFidInputData(m_nRqIdChart, _T("9119"), strChartCnt);	//9119 : 틱 건수
		}

		m_CommAgent.SetFidInputData(m_nRqIdChart, _T("GID"), _T("1003")); //GID
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_MIN))->GetCheck()) //분
	{
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

	//통신조회 응답으로 받을 데이터 항목(FID)
	CString strOutputFidList;

	/**********************************
	* 3. 통신조회 응답으로 받을 항목 설정.
	**********************************/
	/* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	0008 - 시간
	0009 - 일자
	0030 - 매도시가
	0031 - 매도고가
	0032 - 매도저가
	0033 - 매도종가
	0006 - 전일대비부호(실제필드명 : 매수 부호)
	0040 - 매수시가
	0041 - 매수고가
	0042 - 매수저가
	0043 - 매수종가
	1098 - 매도부호
	0666 - 스프레드*/
	strOutputFidList = "8,9,30,31,32,33,6,40,41,42,43,1098,666";

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

void CFxMarginSiseDlg::OnBnClickedOk()
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
void CFxMarginSiseDlg::OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
void CFxMarginSiseDlg::OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength)
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
	* FX마진 종목 리스트(마스터) 조회 데이터 수신 처리
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

		CString arrItemValue[17];

		for (int i = 0; i < nDataCnt; i++, nListIndex++)
		{
			/*--------------------------------------
			FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
			---------------------------------------*/
			arrItemValue[0] = m_CommAgent.GetFidOutputData(nRequestId, "2609", i);		//HTS CODE
			arrItemValue[1] = m_CommAgent.GetFidOutputData(nRequestId, "1171", i);		//통화 1
			arrItemValue[2] = m_CommAgent.GetFidOutputData(nRequestId, "1268", i);		//통화 2
			arrItemValue[3] = m_CommAgent.GetFidOutputData(nRequestId, "2617", i);		//Quote Mode
			arrItemValue[4] = m_CommAgent.GetFidOutputData(nRequestId, "2456", i);		//가격소수점
			arrItemValue[5] = m_CommAgent.GetFidOutputData(nRequestId, "2618", i);		//가격소수점보정
			arrItemValue[6] = m_CommAgent.GetFidOutputData(nRequestId, "2619", i);		//고객소수점
			arrItemValue[7] = m_CommAgent.GetFidOutputData(nRequestId, "2620", i);		//고객소수점보정
			arrItemValue[8] = m_CommAgent.GetFidOutputData(nRequestId, "2621", i);		//딜링룸코드
			arrItemValue[9] = m_CommAgent.GetFidOutputData(nRequestId, "2622", i);		//PL계산통화
			arrItemValue[10] = m_CommAgent.GetFidOutputData(nRequestId, "2623", i);		//PL계산방법
			arrItemValue[11] = m_CommAgent.GetFidOutputData(nRequestId, "306", i);		//Pair ID FCM_CD
			arrItemValue[12] = m_CommAgent.GetFidOutputData(nRequestId, "3", i);		//FX 상품명
			arrItemValue[13] = m_CommAgent.GetFidOutputData(nRequestId, "1222", i);		//매입 이자율
			arrItemValue[14] = m_CommAgent.GetFidOutputData(nRequestId, "1223", i);		//매도 이자율
			arrItemValue[15] = m_CommAgent.GetFidOutputData(nRequestId, "1220", i);		//FDM 매입 이자율
			arrItemValue[16] = m_CommAgent.GetFidOutputData(nRequestId, "1221", i);		//FDM 매도 이자율

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listCode.InsertItem(&lvItem);

			//리스트 컨트롤에 값 입력
			for (int col = 0; col < 17; col++)
				m_listCode.SetItemText(nListIndex, col, (LPTSTR)(LPCTSTR)arrItemValue[col]);
			
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
		m_nRqIdCodeList = 0;	//FX마진 종목 리스트(마스터) 조회 Request ID
	}
	/***************************************
	* FX마진 현재가 조회 데이터 수신 처리
	****************************************/
	else if (m_nRqIdCurPrice == nRequestId)
	{
		/*--------------------------------------
		FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
		---------------------------------------*/
		CString strSellPrice = m_CommAgent.GetFidOutputData(nRequestId, "29", 0);		//매도(29)
		CString strBuyPrice = m_CommAgent.GetFidOutputData(nRequestId, "39", 0);		//매수(39)
		CString strSpread = m_CommAgent.GetFidOutputData(nRequestId, "666", 0);			//스프레드(666)
		CString strPipCost = m_CommAgent.GetFidOutputData(nRequestId, "2468", 0);		//PIP 가치(2468)
		CString strHighPrice = m_CommAgent.GetFidOutputData(nRequestId, "14", 0);		//고가(14)
		CString strLowPrice = m_CommAgent.GetFidOutputData(nRequestId, "15", 0);		//저가(15)
		CString strSellInst = m_CommAgent.GetFidOutputData(nRequestId, "1220", 0);		//이자(S)(1220)
		CString strBuyInst = m_CommAgent.GetFidOutputData(nRequestId, "1221", 0);		//이지(B)(1221)

		GetDlgItem(IDC_CUR_SELL)->SetWindowText(strSellPrice);
		GetDlgItem(IDC_CUR_BUY)->SetWindowText(strBuyPrice);
		GetDlgItem(IDC_SPREAD)->SetWindowText(strSpread);
		GetDlgItem(IDC_PIP_COST)->SetWindowText(strPipCost);
		GetDlgItem(IDC_HIGH_PRICE)->SetWindowText(strHighPrice);
		GetDlgItem(IDC_LOW_PRICE)->SetWindowText(strLowPrice);
		GetDlgItem(IDC_SELL_INST)->SetWindowText(strSellInst);
		GetDlgItem(IDC_BUY_INST)->SetWindowText(strBuyInst);

		/*--------------------------------------
		지선물 체결(현재가) 실시간등록키로 실시간을 등록한다.
		실시간 등록은 첫 조회 시 한번만 한다.
		---------------------------------------*/
		if (!m_strCurPriceRealKey.IsEmpty())
		{
			CString strRealName;
			strRealName = _T("V00");

			m_CommAgent.RegisterReal(strRealName, m_strCurPriceRealKey); //실시간 등록
		}

		/*--------------------------------------
		반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		---------------------------------------*/
		m_nRqIdCurPrice = 0;	//FX마진 현재가 조회 Request ID
	}
	/***************************************
	* FX마진 시간대별체결 조회 데이터 수신 처리
	****************************************/
	else if (m_nRqIdTick == nRequestId)
	{
		CString strTime;		//고시시간
		CString strSellPrice;	//매도
		CString strBuyPrice;	//매수
		CString strSpread;		//스프레드
		CString strPipCost;		//PIP가치

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
			//고시시각(8), 매도(29), 매수(39), 스프레드(666), PIP가치(2468)
			strTime			= m_CommAgent.GetFidOutputData(nRequestId, "8", i);		//고시시간
			strSellPrice	= m_CommAgent.GetFidOutputData(nRequestId, "29", i);	//매도
			strBuyPrice		= m_CommAgent.GetFidOutputData(nRequestId, "39", i);	//매수
			strSpread		= m_CommAgent.GetFidOutputData(nRequestId, "666", i);	//스프레드
			strPipCost		= m_CommAgent.GetFidOutputData(nRequestId, "2468", i);	//PIP가치

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listTick.InsertItem(&lvItem);

			m_listTick.SetItemText(nListIndex, 0, (LPTSTR)(LPCTSTR)strTime);		//고시시간
			m_listTick.SetItemText(nListIndex, 1, (LPTSTR)(LPCTSTR)strSellPrice);	//매도
			m_listTick.SetItemText(nListIndex, 2, (LPTSTR)(LPCTSTR)strBuyPrice);	//매수
			m_listTick.SetItemText(nListIndex, 3, (LPTSTR)(LPCTSTR)strSpread);		//스프레드
			m_listTick.SetItemText(nListIndex, 4, (LPTSTR)(LPCTSTR)strPipCost);		//PIP가치
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
			strRealName = _T("V00");

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
		m_nRqIdTick = 0;	//FX마진 시간대별체결 조회 Request ID

	}
	/***************************************
	* FX마진 차트 조회 데이터 수신 처리
	****************************************/
	else if (m_nRqIdChart == nRequestId)
	{
		CString arrItem[13];

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
			arrItem[0] = fidCommRecvData.GetItem(i, 0);	//시간
			arrItem[1] = fidCommRecvData.GetItem(i, 1);	//일자
			arrItem[2] = fidCommRecvData.GetItem(i, 2);	//매도시가
			arrItem[3] = fidCommRecvData.GetItem(i, 3);	//매도고가
			arrItem[4] = fidCommRecvData.GetItem(i, 4);	//매도저가
			arrItem[5] = fidCommRecvData.GetItem(i, 5);	//매도종가
			arrItem[6] = fidCommRecvData.GetItem(i, 6);	//전일대비부호(실제필드명 : 매수 부호)
			arrItem[7] = fidCommRecvData.GetItem(i, 7);	//매수시가
			arrItem[8] = fidCommRecvData.GetItem(i, 8);	//매수고가
			arrItem[9] = fidCommRecvData.GetItem(i, 9);	//매수저가
			arrItem[10] = fidCommRecvData.GetItem(i, 10);	//매수종가
			arrItem[11] = fidCommRecvData.GetItem(i, 11);	//매도부호
			arrItem[12] = fidCommRecvData.GetItem(i, 12);	//스프레드

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listChart.InsertItem(&lvItem);

			//리스트 컨트롤에 항목별 데이타 입력
			for (int col = 0; col < 13; col++)
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
			arrItem[0] = m_CommAgent.GetFidOutputData(nRequestId, "8", i);	//시간
			arrItem[1] = m_CommAgent.GetFidOutputData(nRequestId, "9", i);	//일자
			arrItem[2] = m_CommAgent.GetFidOutputData(nRequestId, "30", i);	//매도시가
			arrItem[3] = m_CommAgent.GetFidOutputData(nRequestId, "31", i);	//매도고가
			arrItem[4] = m_CommAgent.GetFidOutputData(nRequestId, "32", i);	//매도저가
			arrItem[5] = m_CommAgent.GetFidOutputData(nRequestId, "33", i);	//매도종가
			arrItem[6] = m_CommAgent.GetFidOutputData(nRequestId, "6", i);	//전일대비부호(실제필드명 : 매수 부호)
			arrItem[7] = m_CommAgent.GetFidOutputData(nRequestId, "40", i);	//매수시가
			arrItem[8] = m_CommAgent.GetFidOutputData(nRequestId, "41", i);	//매수고가
			arrItem[9] = m_CommAgent.GetFidOutputData(nRequestId, "42", i);	//매수저가
			arrItem[10] = m_CommAgent.GetFidOutputData(nRequestId, "43", i);	//매수종가
			arrItem[11] = m_CommAgent.GetFidOutputData(nRequestId, "1098", i);	//매도부호
			arrItem[12] = m_CommAgent.GetFidOutputData(nRequestId, "666", i);	//스프레드

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = (LPTSTR)(LPCSTR)_T("");
			lvItem.iItem = nListIndex;

			m_listChart.InsertItem(&lvItem);

			//리스트 컨트롤에 항목별 데이타 입력
			for (int col = 0; col < 13; col++)
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
		m_nRqIdChart = 0;	//FX마진 종목 리스트(마스터) 조회 Request ID

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
void CFxMarginSiseDlg::OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength)
{
	/* 주의 : OnGetRealData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
	이벤트 콜백함수 종료 후에는 유효하지 않습니다.*/

	/***************************************
	* FX마진 체결(현재가) 실시간 데이터 수신
	****************************************/
	if (!_tcscmp(strRealName, "V00"))
	{
		CCommRecvData realCommRecvData;
		int nItemCnt = 0;		//항목 건수

		/*--------------------------------------
		아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
		---------------------------------------*/
#if 1
		//FID 조회응답 데이터 메모리를 얻어온다.(C++에서만 사용 가능)
		if (m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData) == TRUE)
			nItemCnt = realCommRecvData.GetColCnt();		//항목 건수

		CString strSCRN_INDC_PRDT_CD	= realCommRecvData.GetItem(0, 0);	//FX 종목(HTS)
		CString strQUOTE_IDX			= realCommRecvData.GetItem(0, 1);	//Quote 순번
		CString strFCM_CD				= realCommRecvData.GetItem(0, 2);	//FCM Code
		CString strFCM_DT				= realCommRecvData.GetItem(0, 3);	//FCM Quote 일
		CString strFCM_TM				= realCommRecvData.GetItem(0, 4);	//FCM Quote 시간
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
		CString strSCRN_INDC_PRDT_CD = m_CommAgent.GetRealOutputData(strRealName, "SCRN_INDC_PRDT_CD");		//FX 종목(HTS)
		CString strQUOTE_IDX = m_CommAgent.GetRealOutputData(strRealName, "QUOTE_IDX");		//Quote 순번
		CString strFCM_CD = m_CommAgent.GetRealOutputData(strRealName, "FCM_CD");		//FCM Code
		CString strFCM_DT = m_CommAgent.GetRealOutputData(strRealName, "FCM_DT");		//FCM Quote 일
		CString strFCM_TM = m_CommAgent.GetRealOutputData(strRealName, "FCM_TM");		//FCM Quote 시간
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
		조회 시점에 등록한 FX마진 현재가 실시간키와 동일한지 비교
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
		조회 시점에 등록한 FX마진 시간대별 체결 실시간키와 동일한지 비교
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

			m_listTick.SetItemText(0, 0, (LPTSTR)(LPCTSTR)strFCM_TM);			//고시시간
			m_listTick.SetItemText(0, 1, (LPTSTR)(LPCTSTR)strDH_RATE_SELL);		//매도
			m_listTick.SetItemText(0, 2, (LPTSTR)(LPCTSTR)strDH_RATE_BUY);		//매수
			m_listTick.SetItemText(0, 3, (LPTSTR)(LPCTSTR)strDH_SPRD);			//스프레드
			m_listTick.SetItemText(0, 4, (LPTSTR)(LPCTSTR)strDH_PIP_MID);		//PIP가치

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
