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
#include "afxdtctl.h"

// CFxMarginOrdDlg ��ȭ �����Դϴ�.
class CFxMarginOrdDlg : public CDialog
{
public:
	CFxMarginOrdDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FX_ORD_DLG};

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
	int m_nRqIdAccNoList;				//������ȸ Request ID
	int m_nRqIdFDemoAccNoList;			//�ؿܸ��� ������ȸ Request ID
	
	int m_nRqIdSellOrd;					//�ŵ��ֹ� Request ID
	int m_nRqIdBuyOrd;					//�ż��ֹ� Request ID
	int m_nRqIdChangeOrd;				//�����ֹ� Request ID
	int m_nRqIdCancelOrd;				//����ֹ� Request ID

	int m_nRqIdCloseOrd;				//û���ֹ� Request ID
	int m_nRqIdModSLOrd;				//SL�����ֹ� Request ID
	int m_nRqIdCanSLOrd;				//SL����ֹ� Request ID

	int m_nRqIdNonExecList;				//��ü�᳻�� Request ID
	int m_nRqIdExecList;				//�ֹ�ü�᳻�� Request ID
	int m_nRqIdDepositList;				//�����ݳ��� Request ID
	int m_nRqIdBalanceList;				//�ܰ� Request ID
	
	int m_nSeverType;	//0-����, 1-��������, 2-�ؿܹ���

	//�ǽð� ���Ű(�����ڵ�)
	CString m_strOrdRealKey;		//������Ű

	//������ȸŰ
	CString m_strListDepositNextRqKey;	//������ ����Ű
	CString m_strListNonExecNextRqKey;	//�ֹ���ü�� ����Ű
	CString m_strListExecNextRqKey;	//�ֹ�ü�� ����Ű
	CString m_strListBalanceNextRqKey;	//�ܰ� ����Ű

private:
	//���¸��
	void InitListAccNo();

	//�ǽð� �ֹ��޽���
	void InitListReal();

	//�ֹ���ü�� 
	void InitListNonExec();

	//�ֹ�ü�� 
	void InitListExec();

	//������
	void InitListDeposit();

	//�ܰ�
	void InitListBalance();

public:
	/****************************************************
	 * Control
	 ****************************************************/
	CHFCommAgent m_CommAgent;	//API Agent control
	CEdit m_editUserID;			//�α���ID
	CEdit m_editPwd;			//�α��� ��й�ȣ
	CEdit m_editAuthPwd;		//���������� ��й�ȣ
	CListCtrl m_listAccNo;
	CListCtrl m_listNonExec;	//�ֹ���ü�� ����Ʈ��Ʈ��
	CListCtrl m_listExec;		//�ֹ�ü�� ����Ʈ��Ʈ��
	CListCtrl m_listDeposit;	//������ ����Ʈ��Ʈ��
	CListCtrl m_listBalance;	//�ܰ� ����Ʈ��Ʈ��
	CListCtrl m_listReal;		//�ǽð� �ֹ��޽��� ����Ʈ��Ʈ��
	CComboBox m_cmdOrdType;		//�ֹ�����(L-Limit, S-Stop)
	CDateTimeCtrl m_dateTime1;	//����

	DECLARE_MESSAGE_MAP()

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnNMDblclkListAccNo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListNonExec(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListBalance(NMHDR *pNMHDR, LRESULT *pResult);

	/****************************************************
	* �α���/�α׾ƿ�
	****************************************************/
	afx_msg void OnBnClickedLogin();			//�α���
	afx_msg void OnBnClickedLogout();			//�α׾ƿ�

	/****************************************************
	* ��ȭâ ����
	****************************************************/
	afx_msg void OnBnClickedOk();

	/****************************************************
	 * ���¸����ȸ
	 ****************************************************/
	afx_msg void OnBnClickedBtnReqAccno();
	afx_msg void OnBnClickedBtnLoadUserAcc(); //�������¸� �о���δ�.

	void RequestAccList();		//���¸�� ��ȸ
	void RequestFDemoAccList();	//�ؿܸ��� ���¸�� ��ȸ

	CStringArray m_arrAccNo;		//���¸��
	CStringArray m_arrAccAPNO;		//���հ��´�ü��ȣ���
	CString GetAccAPNO(CString strAccNo); //���հ��´�ü��ȣ ������ �Լ�

	/****************************************************
	 * �ֹ� ����
	 ****************************************************/
	afx_msg void OnBnClickedBtnSell();		//�ŵ��ֹ�
	afx_msg void OnBnClickedBtnBuy();		//�ż��ֹ�
	afx_msg void OnBnClickedBtnChange();	//�����ֹ�
	afx_msg void OnBnClickedBtnCancel();	//����ֹ�

	BOOL SendSellBuyOrder(CString strDealingSide, int nRqId, CString strOrderKind = _T(""));	//�ż�/�ŵ� �ֹ� ����

	/****************************************************
	 * ������/�ֹ�ü��/�ܰ� ��ȸ
	 ****************************************************/
	
	//������ ���� ��ȸ
	afx_msg void OnBnClickedBtnReqDeposit(); 
	//������ ���� ��ȸ
	afx_msg void OnBnClickedBtnReqDepositNext();

	//�ֹ���ü�� ���� ��ȸ
	afx_msg void OnBnClickedBtnReqNonExecList();
	//�ֹ���ü�� ���� ��ȸ
	afx_msg void OnBnClickedBtnReqNonExecListNext();

	//�ֹ�ü�� ���� ��ȸ
	afx_msg void OnBnClickedBtnReqExecList();
	//�ֹ�ü�� ���� ��ȸ
	afx_msg void OnBnClickedBtnReqExecListNext();

	//�ܰ� ���� ��ȸ
	afx_msg void OnBnClickedBtnReqBalance();
	//�ܰ� ���� ��ȸ
	afx_msg void OnBnClickedBtnReqBalanceNext();

	//���Ӽ��� ����
	afx_msg void OnRdoSelectServer(UINT nID);

	//�ֹ��븮�� ��Ͽ��θ� ���´�.
	afx_msg void OnBnClickedBtnAccinfo();

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

	//������Ʈ �̺�Ʈ �ڵ鷯
	void OnAgentEventHandler(long nEventType, long nParam, LPCTSTR strParam);
	CDateTimeCtrl m_dateTimeN1;
	CDateTimeCtrl m_dateTimeN2;
	CDateTimeCtrl m_dateTimeE1;
	CDateTimeCtrl m_dateTimeE2;
	afx_msg void OnBnClickedRadioEx1();
	afx_msg void OnBnClickedRadioEx2();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnModsl();
	afx_msg void OnBnClickedBtnCalsl();
};
