#pragma once


// CHFClientSampleDlg ��ȭ �����Դϴ�.

class CHFClientSampleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHFClientSampleDlg)

public:
	CHFClientSampleDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CHFClientSampleDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CLIENT_SAMPLE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

private:
// 	CStockSiseDlg* m_pStockSiseDlg;				//�ֽ� �ü� ��ȭâ
// 	CIndexFutSiseDlg* m_pIndexFutSiseDlg;		//�������� �ü� ��ȭâ
// 	CIndexOptSiseDlg* m_pIndexOptSiseDlg;		//�����ɼ� �ü� ��ȭâ
// 	CForeignFutSiseDlg* m_pForeignFutSiseDlg;	//�ؿܼ��� �ü� ��ȭâ
// 	CFxMarginSiseDlg* m_pFxMarginSiseDlg;		//FX���� �ü� ��ȭâ

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
