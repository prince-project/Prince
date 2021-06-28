// HFClientSampleDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "HFCommClient.h"
#include "HFClientSampleDlg.h"
#include "afxdialogex.h"

#include "StockSiseDlg.h"			//주식 시세 대화창
#include "IndexFutSiseDlg.h"		//지수선물 시세 대화창
#include "IndexOptSiseDlg.h"		//지수옵션 시세 대화창
#include "ForeignFutSiseDlg.h"		//해외선물 시세 대화창
#include "FxMarginSiseDlg.h"		//FX마진 시세 대화창
#include "EurexFutSiseDlg.h"		//야간선물(Eurex) 시세 대화창
#include "EurexOptSiseDlg.h"		//야간옵션(Eurext) 시세 대화창
#include "IndexWeeklyOptSiseDlg.h"	//위클리시세

#include "FFutOptOrdDlg.h"			//해외선물주문
#include "IndexFutOptOrdDlg.h"		//국내지수주문
#include "EurexFutOptOrdDlg.h"		//야간(Eurex)주문
#include "FxMarginOrdDlg.h"			//FX마진주문
#include "IndexIndustrySiseDlg.h"	//업종시세
#include "StockOrdDlg.h"			//주식주문

// CHFClientSampleDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHFClientSampleDlg, CDialogEx)

CHFClientSampleDlg::CHFClientSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHFClientSampleDlg::IDD, pParent)
{
// 	m_pIndexFutSiseDlg = NULL;
// 	m_pStockSiseDlg = NULL;
// 	m_pIndexOptSiseDlg = NULL;
// 	m_pForeignFutSiseDlg = NULL;
// 	m_pFxMarginSiseDlg = NULL;
}

CHFClientSampleDlg::~CHFClientSampleDlg()
{
}

void CHFClientSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHFClientSampleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_INDEX_FUT_SISE, &CHFClientSampleDlg::OnBnClickedBtnIndexFutSise)
	ON_MESSAGE(UM_CHILD_CLOSE, &CHFClientSampleDlg::OnCloseChildDlg)
	ON_BN_CLICKED(IDC_BTN_STOCK_SISE, &CHFClientSampleDlg::OnBnClickedBtnStockSise)
	ON_BN_CLICKED(IDC_BTN_INDEX_OPT_SISE, &CHFClientSampleDlg::OnBnClickedBtnIndexOptSise)
	ON_BN_CLICKED(IDC_BTN_FOREIGN_FUT_SISE, &CHFClientSampleDlg::OnBnClickedBtnForeignFutSise)
	ON_BN_CLICKED(IDC_BTN_FX_MARGIN_SISE, &CHFClientSampleDlg::OnBnClickedBtnFxMarginSise)
	ON_BN_CLICKED(IDC_BTN_CME_FUT_SISE, &CHFClientSampleDlg::OnBnClickedBtnCmeFutSise)
	ON_BN_CLICKED(IDC_BTN_EUREX_OPT_SISE, &CHFClientSampleDlg::OnBnClickedBtnEurexOptSise)
	ON_BN_CLICKED(IDC_BTN_FFORD, &CHFClientSampleDlg::OnBnClickedBtnFford)
	ON_BN_CLICKED(IDC_BTN_INDEXFORD, &CHFClientSampleDlg::OnBnClickedBtnIndexford)
	ON_BN_CLICKED(IDC_BTN_CMEEUFORD, &CHFClientSampleDlg::OnBnClickedBtnCmeeuford)
	ON_BN_CLICKED(IDC_BTN_FXORD, &CHFClientSampleDlg::OnBnClickedBtnFxord)
	ON_BN_CLICKED(IDC_BTN_WEEKLY_SISE, &CHFClientSampleDlg::OnBnClickedBtnWeeklySise)
	ON_BN_CLICKED(IDC_BTN_INDUSTRY_INDEX_SISE2, &CHFClientSampleDlg::OnBnClickedBtnIndustryIndexSise2)
	ON_BN_CLICKED(IDC_BTN_STKORD, &CHFClientSampleDlg::OnBnClickedBtnStkord)
END_MESSAGE_MAP()


// CHFClientSampleDlg 메시지 처리기입니다.

LRESULT CHFClientSampleDlg::OnCloseChildDlg(WPARAM wParam, LPARAM lParam)
{
// 	if ((void*)m_pIndexFutSiseDlg == (void*)lParam)
// 	{
// 		if (::IsWindow(m_pIndexFutSiseDlg->GetSafeHwnd()))
// 			m_pIndexFutSiseDlg->DestroyWindow();
// 
// 		delete m_pIndexFutSiseDlg;
// 		m_pIndexFutSiseDlg = NULL;
// 	}
// 	else if ((void*)m_pStockSiseDlg == (void*)lParam)
// 	{
// 		if (::IsWindow(m_pStockSiseDlg->GetSafeHwnd()))
// 			m_pStockSiseDlg->DestroyWindow();
// 
// 		delete m_pStockSiseDlg;
// 		m_pStockSiseDlg = NULL;
// 	}
// 	else if ((void*)m_pIndexOptSiseDlg == (void*)lParam)
// 	{
// 		if (::IsWindow(m_pIndexOptSiseDlg->GetSafeHwnd()))
// 			m_pIndexOptSiseDlg->DestroyWindow();
// 
// 		delete m_pIndexOptSiseDlg;
// 		m_pIndexOptSiseDlg = NULL;
// 	}
// 	else if ((void*)m_pForeignFutSiseDlg == (void*)lParam)
// 	{
// 		if (::IsWindow(m_pForeignFutSiseDlg->GetSafeHwnd()))
// 			m_pForeignFutSiseDlg->DestroyWindow();
// 
// 		delete m_pForeignFutSiseDlg;
// 		m_pForeignFutSiseDlg = NULL;
// 	}
// 	else if ((void*)m_pFxMarginSiseDlg == (void*)lParam)
// 	{
// 		if (::IsWindow(m_pFxMarginSiseDlg->GetSafeHwnd()))
// 			m_pFxMarginSiseDlg->DestroyWindow();
// 
// 		delete m_pFxMarginSiseDlg;
// 		m_pFxMarginSiseDlg = NULL;
// 	}
	
	return 0L;
}

BOOL CHFClientSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString strTitle;
	strTitle.Format("%s (%s)", PROGRAM_NAME, VERSION_INFO);
	SetWindowText(strTitle);

	CString strApiAgentPath;
	strApiAgentPath.Format("%s\\HFCommAgent.dll", theApp.m_sAppPath);

	CFileFind find;
	BOOL bExist = find.FindFile(strApiAgentPath);
	find.Close();

	//예제 기본 폴더에 있는지 파일을 찾아본다.
	if (!bExist)
	{
		strApiAgentPath.Format("%s\\..\\..\\..\\1QApiAgent\\HFCommAgent.dll", theApp.m_sAppPath);
		bExist = find.FindFile(strApiAgentPath);
		find.Close();
	}

	/*********************************
	* 예제 프로그램과 동일한 위치에 OpenAPI 에이젠트 컨트롤(HFCommAgent.dll)
	* 모듈이 있을 경우 레지스트리에 자동 등록처리를 한다.
	*********************************/
	if (bExist)
	{
		theApp.RegisterOCX(strApiAgentPath);
	}
	else
		::AfxMessageBox("HFCommAgent.dll 파일을 찾지 못했습니다.");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//*******************************************************************
// Function Name : OnBnClickedBtnStockSise
// Function      : 주식 시세 예제 대화창을 실행한다.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnStockSise()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
// 	if (m_pStockSiseDlg)
// 	{
// 		m_pStockSiseDlg->SetFocus();
// 		return;
// 	}
// 
// 	m_pStockSiseDlg = new CStockSiseDlg(this);
// 	m_pStockSiseDlg->Create(IDD_STOCK_SISE_DLG, this);
// 	m_pStockSiseDlg->ShowWindow(SW_SHOW);

	CStockSiseDlg dlg(this);
	dlg.DoModal();
}


//*******************************************************************
// Function Name : OnBnClickedBtnIndexFutSise
// Function      : 지수선물 시세 예제 대화창을 실행한다.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnIndexFutSise()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
// 	if (m_pIndexFutSiseDlg)
// 	{
// 		m_pIndexFutSiseDlg->SetFocus();
// 		return;
// 	}
// 
// 	m_pIndexFutSiseDlg = new CIndexFutSiseDlg(this);
// 	m_pIndexFutSiseDlg->Create(IDD_INDEX_FUT_SISE_DLG, this);
// 	m_pIndexFutSiseDlg->ShowWindow(SW_SHOW);

	CIndexFutSiseDlg dlg(this);
	dlg.DoModal();
}

//*******************************************************************
// Function Name : OnBnClickedBtnIndexOptSise
// Function      : 지수옵션 시세 예제 대화창을 실행한다.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnIndexOptSise()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
// 	if (m_pIndexOptSiseDlg)
// 	{
// 		m_pIndexOptSiseDlg->SetFocus();
// 		return;
// 	}
// 
// 	m_pIndexOptSiseDlg = new CIndexOptSiseDlg(this);
// 	m_pIndexOptSiseDlg->Create(IDD_INDEX_OPT_SISE_DLG, this);
// 	m_pIndexOptSiseDlg->ShowWindow(SW_SHOW);
	CIndexOptSiseDlg dlg(this);
	dlg.DoModal();
}


//*******************************************************************
// Function Name : OnBnClickedBtnForeignFutSise
// Function      : 해외선물 시세 예제 대화창을 실행한다.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnForeignFutSise()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
// 	if (m_pForeignFutSiseDlg)
// 	{
// 		m_pForeignFutSiseDlg->SetFocus();
// 		return;
// 	}
// 
// 	m_pForeignFutSiseDlg = new CForeignFutSiseDlg(this);
// 	m_pForeignFutSiseDlg->Create(IDD_FOREIGN_FUT_SISE_DLG, this);
// 	m_pForeignFutSiseDlg->ShowWindow(SW_SHOW);
	CForeignFutSiseDlg dlg(this);
	dlg.DoModal();
}


//*******************************************************************
// Function Name : OnBnClickedBtnFxMarginSise
// Function      : FX마진 시세 예제 대화창을 실행한다.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnFxMarginSise()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
// 	if (m_pFxMarginSiseDlg)
// 	{
// 		m_pFxMarginSiseDlg->SetFocus();
// 		return;
// 	}
// 
// 	m_pFxMarginSiseDlg = new CFxMarginSiseDlg(this);
// 	m_pFxMarginSiseDlg->Create(IDD_FX_SISE_DLG, this);
// 	m_pFxMarginSiseDlg->ShowWindow(SW_SHOW);

	CFxMarginSiseDlg dlg(this);
	dlg.DoModal();
}


//*******************************************************************
// Function Name : OnBnClickedBtnCmeFutSise
// Function      : 야간선물(Eurex) 시세 예제 대화창을 실행한다.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnCmeFutSise()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CEurexFutSiseDlg dlg(this);
	dlg.DoModal();
}


//*******************************************************************
// Function Name : OnBnClickedBtnEurexOptSise
// Function      : 야간옵션(Eurex) 시세 예제 대화창을 실행한다.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnEurexOptSise()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CEurexOptSiseDlg dlg(this);
	dlg.DoModal();
}

//*******************************************************************
// Function Name : OnBnClickedBtnFford
// Function      : 
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnFford()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFFutOptOrdDlg dlg(this);
	dlg.DoModal();
}


void CHFClientSampleDlg::OnBnClickedBtnIndexford()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CIndexFutOptOrdDlg dlg(this);
	dlg.DoModal();
}


void CHFClientSampleDlg::OnBnClickedBtnCmeeuford()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CEurexFutOptOrdDlg dlg(this);
	dlg.DoModal();
}


void CHFClientSampleDlg::OnBnClickedBtnFxord()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFxMarginOrdDlg dlg(this);
	dlg.DoModal();
}


void CHFClientSampleDlg::OnBnClickedBtnWeeklySise()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CWeeklyIndexOptSiseDlg dlg(this);
	dlg.DoModal();
}


void CHFClientSampleDlg::OnBnClickedBtnIndustryIndexSise2()
{
	CIndexIndustrySiseDlg dlg(this);
	dlg.DoModal();
}


void CHFClientSampleDlg::OnBnClickedBtnStkord()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CStockOrdDlg dlg(this);
	dlg.DoModal();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
