/*----------------------------------------*
| 프로그램명 : 하나금융투자 Open API 예제
| 버      전 : 0.0.1
| 배포  일자 :
| 기      타 :
*----------------------------------------*/

// HFCommClientDlg.h : 헤더 파일
//
#pragma once
#include "hfcommagent.h"
#include "afxwin.h"
#include "afxcmn.h"

// CHFCommClientDlg 대화 상자
class CHFCommClientDlg : public CDialog
{
// 생성입니다.
public:
	CHFCommClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HFCOMMCLIENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
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
	int m_nRqIdHoga;				//지수선물 5단계호가 조회 Request ID
	int m_nRqIdCurPrice;			//지수선물 현재가 조회 Request ID
	int m_nRqIdTick;				//지수선물 시간대별체결 조회 Request ID
	int m_nRqIdCodeList;			//지수선물 종목 리스트(마스터) 조회 Request ID

	//실시간 등록키(종목코드)
	CString m_strHogaRealKey;		//지수선물 5단계호가 실시간 등록키
	CString m_strCurPriceRealKey;	//지수선물 현재가 실시간 등록키
	CString m_strTickRealKey;		//지수선물 시간대별체결 실시간 등록키

	//연속조회키
	CString m_strTickNextRqKey;		//지수선물 시간대별체결 연속조회키(다음 조회)
	CString m_strCodeListNextRqKey;	//지수선물 종목 리스트(마스터) 연속조회키(다음 조회)

private:
	//지수선물 시간대별체결 리스트 컨트롤 초기화
	void InitListTick();
	
	//지수선물 종목 리스트 컨트롤 초기화
	void InitListCode();

	//대비부호
	CString GetDiffSign(CString strSignCode);

	//지수선물 5단계호가 조회/실시간 데이터 컨트롤 입력
	void SetHogaData(CString* arrSellHoga, CString* arrBuyHoga, CString* arrSellRemain,
						CString* arrBuyRemain, CString* arrSellCnt, CString* arrBuyCnt);

public:
	/****************************************************
	 * Control
	 ****************************************************/
	CHFCommAgent m_CommAgent;	//API Agent control
	CEdit m_editUserID;			//로그인ID
	CEdit m_editPwd;			//로그인 비밀번호
	CEdit m_editAuthPwd;		//공인인증서 비밀번호
	CButton m_checkDemo;		//모의투자 체크

	CEdit m_editSymbolPrice;	//지수선물 현재가 종목코드
	CEdit m_editSymbol;			//지수선물 5단계호가 종목코드
	CEdit m_editSymbolTick;		//지수선물 시간대별체결 종목코드
	CListCtrl m_listTick;		//지수선물 시간대별체결 리스트
	CListCtrl m_listCode;		//지수선물 종목 리스트

	DECLARE_MESSAGE_MAP()

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMDblclkListSymbol(NMHDR *pNMHDR, LRESULT *pResult);

	/****************************************************
	 * 통모듈 초기화 및 연결/해제
	 ****************************************************/
	afx_msg void OnBnClickedInitcomm();			//통신 연결
	afx_msg void OnBnClickedTerminate();		//통신연결 해제

	/****************************************************
	 * 로그인/로그아웃
	 ****************************************************/
	afx_msg void OnBnClickedLogin();			//로그인
	afx_msg void OnBnClickedLogout();			//로그아웃

	/****************************************************
	 * 종목 리스트(마스터) 조회
	 ****************************************************/
	afx_msg void OnBnClickedBtnReqCodeList();	//종목 리스트 조회
	afx_msg void OnBnClickedBtnReqCodeListNext();//종목 리스트 다음 조회

	/****************************************************
	 * 지수선물 현재가 조회
	 ****************************************************/
	afx_msg void OnBnClickedBtnReqPrice();		//지수선물 현재가 조회

	/****************************************************
	 * 지수선물 5단계호가 조회
	 ****************************************************/
	afx_msg void OnBnClickedBtnReqHoga();		//지수선물 5단계호가 조회

	/****************************************************
	 * 지수선물 시간대별체결 조회
	 ****************************************************/
	afx_msg void OnBnClickedBtnReqTick();		//지수선물 시간대별체결 조회
	afx_msg void OnBnClickedBtnReqTickNext();	//지수선물 시간대별체결 다음 조회

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
};
