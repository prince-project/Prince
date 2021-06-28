/*----------------------------------------*
| 프로그램명 : 하나금융투자 Open API 예제
| 버      전 : v 
| 배포  일자 :
| 기      타 :
*----------------------------------------*/

#pragma once
#include "hfcommagent.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"

// CStockOrdDlg 대화 상자입니다.
class CStockOrdDlg : public CDialog
{
public:
	CStockOrdDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STOCK_ORD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();

private:
	//호가 배경색 브러쉬
	CBrush m_brushSellBack;			//매수 배경색 브러쉬
	CBrush m_brushBuyBack;			//매도 배경색 브러쉬

	BOOL m_bCommConnect;			//통신연결 상태(TRUE:연결, FALSE:끊김)
	CString m_strLoginID;			//로그인 ID
	CString m_strLoginPwd;			//로그인 비밀번호
	CString m_strCertPwd;			//공인인증 비밀번호

	//Requet ID(조회 고유키)
	int m_nRqIdAccNoList;				//계좌조회 Request ID
	int m_nRqIdFDemoAccNoList;			//해외모의 계좌조회 Request ID
	
	int m_nRqIdSellOrd;					//매도주문 Request ID
	int m_nRqIdBuyOrd;					//매수주문 Request ID
	int m_nRqIdChangeOrd;				//정정주문 Request ID
	int m_nRqIdCancelOrd;				//취소주문 Request ID

	int m_nRqIdNonExecList;				//미체결내역 Request ID
	int m_nRqIdExecList;				//주문체결내역 Request ID
	int m_nRqIdCodeList;				//종목 Request ID
	
	int m_nSeverType;	//0-리얼, 1-국내모의, 2-해외무의

	//실시간 등록키(종목코드)
	CString m_strOrdRealKey;		//리얼등록키

	//연속조회키
	CString m_strCodeListNextRqKey;	//종목 연속키
	CString m_strListNonExecNextRqKey;	//주문미체결 연속키
	CString m_strListExecNextRqKey;	//주문체결 연속키

private:
	//계좌목록
	void InitListAccNo();
	//실시간 주문메시지
	void InitListReal();
	//주문미체결 
	void InitListNonExec();
	//주문체결 
	void InitListExec();
	//종목리스트
	void InitListCode();
public:
	/****************************************************
	 * Control
	 ****************************************************/
	CHFCommAgent m_CommAgent;	//API Agent control
	CEdit m_editUserID;			//로그인ID
	CEdit m_editPwd;			//로그인 비밀번호
	CEdit m_editAuthPwd;		//공인인증서 비밀번호
	CListCtrl m_listAccNo;
	CListCtrl m_listNonExec;	//주문미체결 리스트컨트롤
	CListCtrl m_listExec;		//주문체결 리스트컨트롤
	CListCtrl m_listCode;		//종목 리스트컨트롤
	CListCtrl m_listReal;		//실시간 주문메시지 리스트컨트롤
	CComboBox m_cmdOrdType;		//주문구분
	CDateTimeCtrl m_dateTimeNonExec;	//일자
	CDateTimeCtrl m_dateTimeExec;	//일자

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
	afx_msg void OnNMDblclkListCode(NMHDR *pNMHDR, LRESULT *pResult);
	/****************************************************
	* 로그인/로그아웃
	****************************************************/
	afx_msg void OnBnClickedLogin();			//로그인
	afx_msg void OnBnClickedLogout();			//로그아웃

	/****************************************************
	* 대화창 종료
	****************************************************/
	afx_msg void OnBnClickedOk();

	/****************************************************
	 * 계좌목록조회
	 ****************************************************/
	afx_msg void OnBnClickedBtnReqAccno();
	afx_msg void OnBnClickedBtnLoadUserAcc(); //보유계좌를 읽어들인다.

	void RequestAccList();		//계좌목록 조회
	void RequestFDemoAccList();	//모의 계좌목록 조회

	CStringArray m_arrAccNo;		//계좌목록
	CStringArray m_arrAccAPNO;		//종합계좌대체번호목록
	CString GetAccAPNO(CString strAccNo); //종합계좌대체번호 얻어오는 함수

	/****************************************************
	 * 주문 전송
	 ****************************************************/
	afx_msg void OnBnClickedBtnSell();		//매도주문
	afx_msg void OnBnClickedBtnBuy();		//매수주문
	afx_msg void OnBnClickedBtnChange();	//정정주문
	afx_msg void OnBnClickedBtnCancel();	//취소주문

	BOOL SendSellBuyOrder(CString strDealingSide, int nRqId);	//매수/매도 주문 전송

	/****************************************************
	 * 예수금/주문체결/잔고 조회
	 ****************************************************/
	
	//마스터 조회
	afx_msg void OnBnClickedBtnReqMaster();

	//주문미체결 최초 조회
	afx_msg void OnBnClickedBtnReqNonExecList();
	//주문체결 최초 조회
	afx_msg void OnBnClickedBtnReqExecList();

	//접속서버 라디오
	afx_msg void OnRdoSelectServer(UINT nID);

	DECLARE_EVENTSINK_MAP()

	/****************************************************
	* API Agent Event Handler
	****************************************************/
	//조회 Tran데이터 수신 이벤트
	void OnGetTranData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength);

	//Fid조회 데이터 수신 이벤트
	void OnGetFidData(LONG nRequestId, LPCTSTR pBlock, long nBlockLength);

	//실시간 데이터 수신 이벤트
	void OnGetRealData(LPCTSTR strRealName, LPCTSTR strRealKey, LPCTSTR pBlock, long nBlockLength);

	//에이전트 이벤트 핸들러
	void OnAgentEventHandler(long nEventType, long nParam, LPCTSTR strParam);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
