#pragma once


// CHFClientSampleDlg 대화 상자입니다.

class CHFClientSampleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHFClientSampleDlg)

public:
	CHFClientSampleDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CHFClientSampleDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CLIENT_SAMPLE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

private:
// 	CStockSiseDlg* m_pStockSiseDlg;				//주식 시세 대화창
// 	CIndexFutSiseDlg* m_pIndexFutSiseDlg;		//지수선물 시세 대화창
// 	CIndexOptSiseDlg* m_pIndexOptSiseDlg;		//지수옵션 시세 대화창
// 	CForeignFutSiseDlg* m_pForeignFutSiseDlg;	//해외선물 시세 대화창
// 	CFxMarginSiseDlg* m_pFxMarginSiseDlg;		//FX마진 시세 대화창

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnCloseChildDlg(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedBtnStockSise();
	afx_msg void OnBnClickedBtnIndexFutSise();
	afx_msg void OnBnClickedBtnIndexOptSise();

	afx_msg void OnBnClickedBtnForeignFutSise();
	afx_msg void OnBnClickedBtnFxMarginSise();
	afx_msg void OnBnClickedBtnCmeFutSise();
	afx_msg void OnBnClickedBtnEurexOptSise();
	afx_msg void OnBnClickedBtnFford();
	afx_msg void OnBnClickedBtnIndexford();
	afx_msg void OnBnClickedBtnCmeeuford();
	afx_msg void OnBnClickedBtnFxord();
	afx_msg void OnBnClickedBtnWeeklySise();
	afx_msg void OnBnClickedBtnIndustryIndexSise2();
	afx_msg void OnBnClickedBtnStkord();
};
