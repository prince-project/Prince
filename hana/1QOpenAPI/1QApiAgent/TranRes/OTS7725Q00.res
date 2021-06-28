BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7725Q00, TR_NAME=API용CFD청산내역목록조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS7725Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=관리부점코드;
			 INDEX=1, ITEM=CFD_BRKR_CD, TYPE=string, SIZE=20, CAPTION=CFD브로커코드;
			 INDEX=2, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=3, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=4, ITEM=SCTN_STRT_DT, TYPE=string, SIZE=8, CAPTION=구간시작일자;
			 INDEX=5, ITEM=SCTN_END_DT, TYPE=string, SIZE=8, CAPTION=구간종료일자;
			 INDEX=6, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
			 INDEX=7, ITEM=CFD_BRKR_TRDE_DCD, TYPE=string, SIZE=1, CAPTION=CFD브로커매매구분코드;
			 INDEX=8, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS7725Q00_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_BYCL_PRNA, TYPE=string, SIZE=23, CAPTION=CFD매수청산원금;
			 INDEX=1, ITEM=CFD_BYCL_AMT, TYPE=string, SIZE=23, CAPTION=CFD매수청산금액;
			 INDEX=2, ITEM=CFD_BYCL_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD매수청산손익금액;
			 INDEX=3, ITEM=CFD_BUY_FEE, TYPE=string, SIZE=23, CAPTION=CFD매수수수료;
			 INDEX=4, ITEM=CFD_BUY_NIAL_AMT, TYPE=string, SIZE=23, CAPTION=CFD매수순손익금액;
			 INDEX=5, ITEM=CFD_SLCL_PRNA, TYPE=string, SIZE=23, CAPTION=CFD매도청산원금;
			 INDEX=6, ITEM=CFD_SLCL_AMT, TYPE=string, SIZE=23, CAPTION=CFD매도청산금액;
			 INDEX=7, ITEM=CFD_SLCL_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD매도청산손익금액;
			 INDEX=8, ITEM=CFD_SELL_FEE, TYPE=string, SIZE=23, CAPTION=CFD매도수수료;
			 INDEX=9, ITEM=CFD_SELL_NIAL_AMT, TYPE=string, SIZE=23, CAPTION=CFD매도순손익금액;
		END_OUTPUT0_ITEM

		REC_NAME=OTS7725Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=CFD_CVRG_DT, TYPE=string, SIZE=8, CAPTION=CFD반대매매일자;
			 INDEX=1, ITEM=BD_NM, TYPE=string, SIZE=80, CAPTION=부점명;
			 INDEX=2, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=종합계좌번호;
			 INDEX=3, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=고객명;
			 INDEX=4, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=단축상품코드;
			 INDEX=5, ITEM=CFD_PRDT_NM, TYPE=string, SIZE=100, CAPTION=CFD상품명;
			 INDEX=6, ITEM=CFD_BRKR_TRDE_DCD_NM, TYPE=string, SIZE=10, CAPTION=CFD브로커매매구분코드명;
			 INDEX=7, ITEM=CFD_CLR_QNT, TYPE=string, SIZE=19, CAPTION=CFD청산수량;
			 INDEX=8, ITEM=CFD_ACBK_DT, TYPE=string, SIZE=8, CAPTION=CFD장부일자;
			 INDEX=9, ITEM=CFD_ACBK_UNPR, TYPE=string, SIZE=20, CAPTION=CFD장부단가;
			 INDEX=10, ITEM=CFD_CLR_UNPR, TYPE=string, SIZE=20, CAPTION=CFD청산단가;
			 INDEX=11, ITEM=CFD_CLR_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD청산손익금액;
			 INDEX=12, ITEM=CFD_FEE, TYPE=string, SIZE=23, CAPTION=CFD수수료;
			 INDEX=13, ITEM=CFD_PUR_CLR_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD순수청산손익금액;
			 INDEX=14, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strMNGM_BDCD;		//관리부점코드
CString strCFD_BRKR_CD;		//CFD브로커코드
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strSCTN_STRT_DT;		//구간시작일자
CString strSCTN_END_DT;		//구간종료일자
CString strCFD_PRDT_CD;		//CFD상품코드
CString strCFD_BRKR_TRDE_DCD;		//CFD브로커매매구분코드
CString strPWD;		//비밀번호

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "MNGM_BDCD", strMNGM_BDCD);		//관리부점코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "CFD_BRKR_CD", strCFD_BRKR_CD);		//CFD브로커코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "SCTN_STRT_DT", strSCTN_STRT_DT);		//구간시작일자
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "SCTN_END_DT", strSCTN_END_DT);		//구간종료일자
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "CFD_BRKR_TRDE_DCD", strCFD_BRKR_TRDE_DCD);		//CFD브로커매매구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "PWD", strPWD);		//비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCFD_BYCL_PRNA = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_BYCL_PRNA", 0);		//CFD매수청산원금
CString strCFD_BYCL_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_BYCL_AMT", 0);		//CFD매수청산금액
CString strCFD_BYCL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_BYCL_PFLS_AMT", 0);		//CFD매수청산손익금액
CString strCFD_BUY_FEE = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_BUY_FEE", 0);		//CFD매수수수료
CString strCFD_BUY_NIAL_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_BUY_NIAL_AMT", 0);		//CFD매수순손익금액
CString strCFD_SLCL_PRNA = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_SLCL_PRNA", 0);		//CFD매도청산원금
CString strCFD_SLCL_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_SLCL_AMT", 0);		//CFD매도청산금액
CString strCFD_SLCL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_SLCL_PFLS_AMT", 0);		//CFD매도청산손익금액
CString strCFD_SELL_FEE = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_SELL_FEE", 0);		//CFD매도수수료
CString strCFD_SELL_NIAL_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_SELL_NIAL_AMT", 0);		//CFD매도순손익금액
CString strCFD_CVRG_DT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_CVRG_DT", nRow);		//CFD반대매매일자
CString strBD_NM = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "BD_NM", nRow);		//부점명
CString strCANO = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CANO", nRow);		//종합계좌번호
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CUST_NM", nRow);		//고객명
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "SHTN_PRDT_CD", nRow);		//단축상품코드
CString strCFD_PRDT_NM = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_PRDT_NM", nRow);		//CFD상품명
CString strCFD_BRKR_TRDE_DCD_NM = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_BRKR_TRDE_DCD_NM", nRow);		//CFD브로커매매구분코드명
CString strCFD_CLR_QNT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_CLR_QNT", nRow);		//CFD청산수량
CString strCFD_ACBK_DT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_ACBK_DT", nRow);		//CFD장부일자
CString strCFD_ACBK_UNPR = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_ACBK_UNPR", nRow);		//CFD장부단가
CString strCFD_CLR_UNPR = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_CLR_UNPR", nRow);		//CFD청산단가
CString strCFD_CLR_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_CLR_PFLS_AMT", nRow);		//CFD청산손익금액
CString strCFD_FEE = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_FEE", nRow);		//CFD수수료
CString strCFD_PUR_CLR_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_PUR_CLR_PFLS_AMT", nRow);		//CFD순수청산손익금액
CString strCFD_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_PRDT_CD", nRow);		//CFD상품코드
