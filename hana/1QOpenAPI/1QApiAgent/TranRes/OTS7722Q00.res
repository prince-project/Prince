BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7722Q00, TR_NAME=API용CFD미결제잔고목록조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS7722Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=CFD_STDR_DT, TYPE=string, SIZE=8, CAPTION=CFD기준일자;
			 INDEX=3, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS7722Q00_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_BFDT_DPST_AMT, TYPE=string, SIZE=23, CAPTION=CFD전일예탁금액;
			 INDEX=1, ITEM=CFD_RNDR_AMT, TYPE=string, SIZE=23, CAPTION=CFD입출금금액;
			 INDEX=2, ITEM=CFD_STL_AMT, TYPE=string, SIZE=23, CAPTION=CFD결제금액;
			 INDEX=3, ITEM=CFD_DPST_AMT, TYPE=string, SIZE=23, CAPTION=CFD예탁금액;
			 INDEX=4, ITEM=CFD_ORDR_PSBL_AMT, TYPE=string, SIZE=23, CAPTION=CFD주문가능금액;
			 INDEX=5, ITEM=CFD_DRWG_PSBL_AMT, TYPE=string, SIZE=23, CAPTION=CFD출금가능금액;
			 INDEX=6, ITEM=CFD_CLR_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD청산손익금액;
			 INDEX=7, ITEM=CFD_FEE, TYPE=string, SIZE=23, CAPTION=CFD수수료;
			 INDEX=8, ITEM=CFD_FNN_CT_AMT, TYPE=string, SIZE=23, CAPTION=CFD금융비용금액;
			 INDEX=9, ITEM=CFD_CSGN_WMY, TYPE=string, SIZE=23, CAPTION=CFD위탁증거금;
			 INDEX=10, ITEM=CFD_EVL_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD평가손익금액;
			 INDEX=11, ITEM=CFD_ACNT_EVL_AMT, TYPE=string, SIZE=23, CAPTION=CFD계좌평가금액;
			 INDEX=12, ITEM=CFD_ADIT_WMY, TYPE=string, SIZE=23, CAPTION=CFD추가증거금;
			 INDEX=13, ITEM=CFD_WMY_RTO, TYPE=string, SIZE=20, CAPTION=CFD증거금비율;
			 INDEX=14, ITEM=CFD_RST_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD리셋손익금액;
		END_OUTPUT0_ITEM

		REC_NAME=OTS7722Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=단축상품코드;
			 INDEX=1, ITEM=CFD_PRDT_NM, TYPE=string, SIZE=100, CAPTION=CFD상품명;
			 INDEX=2, ITEM=CFD_TRDE_DCD_NM, TYPE=string, SIZE=10, CAPTION=CFD매매구분코드명;
			 INDEX=3, ITEM=CFD_ACBK_QNT, TYPE=string, SIZE=19, CAPTION=CFD장부수량;
			 INDEX=4, ITEM=CFD_ACBK_UNPR, TYPE=string, SIZE=20, CAPTION=CFD장부단가;
			 INDEX=5, ITEM=CFD_PV, TYPE=string, SIZE=20, CAPTION=CFD현재가;
			 INDEX=6, ITEM=CFD_EVL_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD평가손익금액;
			 INDEX=7, ITEM=ERN_RT, TYPE=string, SIZE=17, CAPTION=수익율;
			 INDEX=8, ITEM=CFD_CLR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFD청산가능수량;
			 INDEX=9, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
			 INDEX=10, ITEM=CFD_BRKR_CD, TYPE=string, SIZE=20, CAPTION=CFD브로커코드;
			 INDEX=11, ITEM=CFD_ACBK_AMT, TYPE=string, SIZE=23, CAPTION=CFD장부금액;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strCFD_STDR_DT;		//CFD기준일자
CString strPWD;		//비밀번호

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7722Q00", "OTS7722Q00_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7722Q00", "OTS7722Q00_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7722Q00", "OTS7722Q00_in", "CFD_STDR_DT", strCFD_STDR_DT);		//CFD기준일자
m_CommAgent.SetTranInputData(nRequestId, "OTS7722Q00", "OTS7722Q00_in", "PWD", strPWD);		//비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCFD_BFDT_DPST_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_BFDT_DPST_AMT", 0);		//CFD전일예탁금액
CString strCFD_RNDR_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_RNDR_AMT", 0);		//CFD입출금금액
CString strCFD_STL_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_STL_AMT", 0);		//CFD결제금액
CString strCFD_DPST_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_DPST_AMT", 0);		//CFD예탁금액
CString strCFD_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_ORDR_PSBL_AMT", 0);		//CFD주문가능금액
CString strCFD_DRWG_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_DRWG_PSBL_AMT", 0);		//CFD출금가능금액
CString strCFD_CLR_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_CLR_PFLS_AMT", 0);		//CFD청산손익금액
CString strCFD_FEE = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_FEE", 0);		//CFD수수료
CString strCFD_FNN_CT_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_FNN_CT_AMT", 0);		//CFD금융비용금액
CString strCFD_CSGN_WMY = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_CSGN_WMY", 0);		//CFD위탁증거금
CString strCFD_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_EVL_PFLS_AMT", 0);		//CFD평가손익금액
CString strCFD_ACNT_EVL_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_ACNT_EVL_AMT", 0);		//CFD계좌평가금액
CString strCFD_ADIT_WMY = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_ADIT_WMY", 0);		//CFD추가증거금
CString strCFD_WMY_RTO = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_WMY_RTO", 0);		//CFD증거금비율
CString strCFD_RST_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_RST_PFLS_AMT", 0);		//CFD리셋손익금액
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "SHTN_PRDT_CD", nRow);		//단축상품코드
CString strCFD_PRDT_NM = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_PRDT_NM", nRow);		//CFD상품명
CString strCFD_TRDE_DCD_NM = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_TRDE_DCD_NM", nRow);		//CFD매매구분코드명
CString strCFD_ACBK_QNT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_ACBK_QNT", nRow);		//CFD장부수량
CString strCFD_ACBK_UNPR = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_ACBK_UNPR", nRow);		//CFD장부단가
CString strCFD_PV = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_PV", nRow);		//CFD현재가
CString strCFD_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_EVL_PFLS_AMT", nRow);		//CFD평가손익금액
CString strERN_RT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "ERN_RT", nRow);		//수익율
CString strCFD_CLR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_CLR_PSBL_QNT", nRow);		//CFD청산가능수량
CString strCFD_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_PRDT_CD", nRow);		//CFD상품코드
CString strCFD_BRKR_CD = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_BRKR_CD", nRow);		//CFD브로커코드
CString strCFD_ACBK_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_ACBK_AMT", nRow);		//CFD장부금액
