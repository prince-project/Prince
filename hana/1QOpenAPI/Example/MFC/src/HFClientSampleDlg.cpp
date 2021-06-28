// HFClientSampleDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "HFCommClient.h"
#include "HFClientSampleDlg.h"
#include "afxdialogex.h"

#include "StockSiseDlg.h"			//�ֽ� �ü� ��ȭâ
#include "IndexFutSiseDlg.h"		//�������� �ü� ��ȭâ
#include "IndexOptSiseDlg.h"		//�����ɼ� �ü� ��ȭâ
#include "ForeignFutSiseDlg.h"		//�ؿܼ��� �ü� ��ȭâ
#include "FxMarginSiseDlg.h"		//FX���� �ü� ��ȭâ
#include "EurexFutSiseDlg.h"		//�߰�����(Eurex) �ü� ��ȭâ
#include "EurexOptSiseDlg.h"		//�߰��ɼ�(Eurext) �ü� ��ȭâ
#include "IndexWeeklyOptSiseDlg.h"	//��Ŭ���ü�

#include "FFutOptOrdDlg.h"			//�ؿܼ����ֹ�
#include "IndexFutOptOrdDlg.h"		//���������ֹ�
#include "EurexFutOptOrdDlg.h"		//�߰�(Eurex)�ֹ�
#include "FxMarginOrdDlg.h"			//FX�����ֹ�
#include "IndexIndustrySiseDlg.h"	//�����ü�
#include "StockOrdDlg.h"			//�ֽ��ֹ�

// CHFClientSampleDlg ��ȭ �����Դϴ�.

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


// CHFClientSampleDlg �޽��� ó�����Դϴ�.

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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CString strTitle;
	strTitle.Format("%s (%s)", PROGRAM_NAME, VERSION_INFO);
	SetWindowText(strTitle);

	CString strApiAgentPath;
	strApiAgentPath.Format("%s\\HFCommAgent.dll", theApp.m_sAppPath);

	CFileFind find;
	BOOL bExist = find.FindFile(strApiAgentPath);
	find.Close();

	//���� �⺻ ������ �ִ��� ������ ã�ƺ���.
	if (!bExist)
	{
		strApiAgentPath.Format("%s\\..\\..\\..\\1QApiAgent\\HFCommAgent.dll", theApp.m_sAppPath);
		bExist = find.FindFile(strApiAgentPath);
		find.Close();
	}

	/*********************************
	* ���� ���α׷��� ������ ��ġ�� OpenAPI ������Ʈ ��Ʈ��(HFCommAgent.dll)
	* ����� ���� ��� ������Ʈ���� �ڵ� ���ó���� �Ѵ�.
	*********************************/
	if (bExist)
	{
		theApp.RegisterOCX(strApiAgentPath);
	}
	else
		::AfxMessageBox("HFCommAgent.dll ������ ã�� ���߽��ϴ�.");

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

//*******************************************************************
// Function Name : OnBnClickedBtnStockSise
// Function      : �ֽ� �ü� ���� ��ȭâ�� �����Ѵ�.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnStockSise()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
// Function      : �������� �ü� ���� ��ȭâ�� �����Ѵ�.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnIndexFutSise()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
// Function      : �����ɼ� �ü� ���� ��ȭâ�� �����Ѵ�.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnIndexOptSise()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
// Function      : �ؿܼ��� �ü� ���� ��ȭâ�� �����Ѵ�.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnForeignFutSise()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
// Function      : FX���� �ü� ���� ��ȭâ�� �����Ѵ�.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnFxMarginSise()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
// Function      : �߰�����(Eurex) �ü� ���� ��ȭâ�� �����Ѵ�.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnCmeFutSise()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CEurexFutSiseDlg dlg(this);
	dlg.DoModal();
}


//*******************************************************************
// Function Name : OnBnClickedBtnEurexOptSise
// Function      : �߰��ɼ�(Eurex) �ü� ���� ��ȭâ�� �����Ѵ�.
// Param         : 
// Return        : void 
// Create        : 
// Comment       : 
//******************************************************************
void CHFClientSampleDlg::OnBnClickedBtnEurexOptSise()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFFutOptOrdDlg dlg(this);
	dlg.DoModal();
}


void CHFClientSampleDlg::OnBnClickedBtnIndexford()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CIndexFutOptOrdDlg dlg(this);
	dlg.DoModal();
}


void CHFClientSampleDlg::OnBnClickedBtnCmeeuford()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CEurexFutOptOrdDlg dlg(this);
	dlg.DoModal();
}


void CHFClientSampleDlg::OnBnClickedBtnFxord()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFxMarginOrdDlg dlg(this);
	dlg.DoModal();
}


void CHFClientSampleDlg::OnBnClickedBtnWeeklySise()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CStockOrdDlg dlg(this);
	dlg.DoModal();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
