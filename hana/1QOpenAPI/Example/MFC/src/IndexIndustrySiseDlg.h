/*----------------------------------------*
| ���α׷��� : �ϳ��������� Open API ����
| ��      �� : v 
| ����  ���� :
| ��      Ÿ :
*----------------------------------------*/

#pragma once
#include "hfcommagent.h"
#include "afxwin.h"
#include "afxcmn.h"

// CIndexIndustrySiseDlg ��ȭ �����Դϴ�.

class CIndexIndustrySiseDlg : public CDialog
{
public:
	CIndexIndustrySiseDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SISE_INDUSTRY_INDEX_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();

private:
	//ȣ�� ���� �귯��
	CBrush m_brushSellBack;			//�ż� ���� �귯��
	CBrush m_brushBuyBack;			//�ŵ� ���� �귯��

	BOOL m_bCommConnect;			//��ſ��� ����(TRUE:����, FALSE:����)
	CString m_strLoginID;			//�α��� ID
	CString m_strLoginPwd;			//�α��� ��й�ȣ
	CString m_strCertPwd;			//�������� ��й�ȣ

	//Requet ID(��ȸ ����Ű)
	int m_nRqIdHoga;				//�������� 5�ܰ�ȣ�� ��ȸ Request ID
	int m_nRqIdCurPrice;			//�������� ���簡 ��ȸ Request ID
	int m_nRqIdTick;				//�������� �ð��뺰ü�� ��ȸ Request ID
	int m_nRqIdCodeList;			//�������� ���� ����Ʈ(������) ��ȸ Request ID
	int m_nRqIdChart;				//�������� ��Ʈ ������ ��ȸ Request ID

	int m_nSeverType;	//0-����, 1-��������, 2-�ؿܹ���

	//�ǽð� ���Ű(�����ڵ�)
	CString m_strHogaRealKey;		//�������� 5�ܰ�ȣ�� �ǽð� ���Ű
	CString m_strCurPriceRealKey;	//�������� ���簡 �ǽð� ���Ű
	CString m_strTickRealKey;		//�������� �ð��뺰ü�� �ǽð� ���Ű

	//������ȸŰ
	CString m_strTickNextRqKey;		//�������� �ð��뺰ü�� ������ȸŰ(���� ��ȸ)
	CString m_strCodeListNextRqKey;	//�������� ���� ����Ʈ(������) ������ȸŰ(���� ��ȸ)
	CString m_strChartNextRqKey;	//�������� ��Ʈ ������ ������ȸŰ(���� ��ȸ)
	
private:
	//�������� �ð��뺰ü�� ����Ʈ ��Ʈ�� �ʱ�ȭ
	void InitListTick();

	//�������� ���� ����Ʈ ��Ʈ�� �ʱ�ȭ
	void InitListCode();

	//�������� ��Ʈ ����Ʈ ��Ʈ�� �ʱ�ȭ
	void InitListChart();

	//����ȣ
	CString GetDiffSign(CString strSignCode);

	//�������� 5�ܰ�ȣ�� ��ȸ/�ǽð� ������ ��Ʈ�� �Է�
	void SetHogaData(CString* arrSellHoga, CString* arrBuyHoga, CString* arrSellRemain,
		CString* arrBuyRemain, CString* arrSellCnt, CString* arrBuyCnt);

public:
	/****************************************************
	* Control
	****************************************************/
	CHFCommAgent m_CommAgent;	//API Agent control
	CEdit m_editUserID;			//�α���ID
	CEdit m_editPwd;			//�α��� ��й�ȣ
	CEdit m_editAuthPwd;		//���������� ��й�ȣ

	CEdit m_editSymbolPrice;	//�������� ���簡 �����ڵ�
	CEdit m_editSymbol;			//�������� 5�ܰ�ȣ�� �����ڵ�
	CEdit m_editSymbolTick;		//�������� �ð��뺰ü�� �����ڵ�
	CListCtrl m_listTick;		//�������� �ð��뺰ü�� ����Ʈ
	CListCtrl m_listCode;		//�������� ���� ����Ʈ

	CEdit m_editSymbolChart;		//��Ʈ �����ڵ�
	CButton m_chkAutoReqChart;		//��Ʈ �ڵ� ���� ��ȸ üũ�ڽ�
	CListCtrl m_listChart;			//��Ʈ ����Ʈ
	CEdit m_editChartCnt;			//��Ʈ ��ȸ ������ ��ȸ �Ǽ�
	CDateTimeCtrl m_dateTimeFrom;	//��Ʈ ��ȸ ���� ����
	CDateTimeCtrl m_dateTimeTo;		//��Ʈ ��ȸ ���� ����

	UINT m_uIdxSelectedIndustry;	//���õ� ������ Index

	DECLARE_MESSAGE_MAP()

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMDblclkListSymbol(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRadioChartTerm(UINT nID);

	/****************************************************
	* ���� �ʱ�ȭ �� ����/����
	****************************************************/
	afx_msg void OnBnClickedInitcomm();			//��� ����
	afx_msg void OnBnClickedTerminate();		//��ſ��� ����

	/****************************************************
	* �α���/�α׾ƿ�
	****************************************************/
	afx_msg void OnBnClickedLogin();			//�α���
	afx_msg void OnBnClickedLogout();			//�α׾ƿ�

	/****************************************************
	* ���� ����Ʈ(������) ��ȸ
	****************************************************/
	afx_msg void OnBnClickedBtnReqCodeList();	//���� ����Ʈ ��ȸ
	afx_msg void OnBnClickedBtnReqCodeListNext();//���� ����Ʈ ���� ��ȸ

	/****************************************************
	* �������� ���簡 ��ȸ
	****************************************************/
	afx_msg void OnBnClickedBtnReqPrice();		//�������� ���簡 ��ȸ

	/****************************************************
	* �������� 5�ܰ�ȣ�� ��ȸ
	****************************************************/
	afx_msg void OnBnClickedBtnReqHoga();		//�������� 5�ܰ�ȣ�� ��ȸ

	/****************************************************
	* �������� �ð��뺰ü�� ��ȸ
	****************************************************/
	afx_msg void OnBnClickedBtnReqTick();		//�������� �ð��뺰ü�� ��ȸ
	afx_msg void OnBnClickedBtnReqTickNext();	//�������� �ð��뺰ü�� ���� ��ȸ
	
	/****************************************************
	* �������� ��Ʈ ������ ��ȸ
	****************************************************/
	afx_msg void OnBnClickedBtnReqChart();		//�������� ��Ʈ ������ ��ȸ
	afx_msg void OnBnClickedBtnReqChartNext();	//�������� ��Ʈ ���� ������ ��ȸ

	//��ȭâ ����
	afx_msg void OnBnClickedOk();

	//���Ӽ��� ����
	afx_msg void OnRdoSelectServer(UINT nID);

	afx_msg void OnSelectRadioIndustry(UINT nID);

	DECLARE_EVENTSINK_MAP()

	/****************************************************
	* API Agent Event Handler
	****************************************************/
	//��ȸ Tran������ ���� �̺�Ʈ
	void OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength);

	//Fid��ȸ ������ ���� �̺�Ʈ
	void OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength);

	//�ǽð� ������ ���� �̺�Ʈ
	void OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength);
};