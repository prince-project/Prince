BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2850Q18, TR_NAME=계좌미결제잔고내역잔고정보조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS2850Q18_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=3, ITEM=INQ_DT, TYPE=string, SIZE=8, CAPTION=조회일자;
			 INDEX=4, ITEM=DCD, TYPE=string, SIZE=1, CAPTION=구분코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS2850Q18_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=1, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=상품명;
			 INDEX=2, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=매도매수구분코드;
			 INDEX=3, ITEM=SELL_BUY_DVSN_NM, TYPE=string, SIZE=40, CAPTION=매도매수구분명;
			 INDEX=4, ITEM=USTL_CTRC_QNT, TYPE=string, SIZE=19, CAPTION=미결제약정수량;
			 INDEX=5, ITEM=AVR_PRC, TYPE=string, SIZE=20, CAPTION=평균가격;
			 INDEX=6, ITEM=NOW_PRC, TYPE=string, SIZE=22, CAPTION=현재가격;
			 INDEX=7, ITEM=EVL_AMT, TYPE=string, SIZE=19, CAPTION=평가금액;
			 INDEX=8, ITEM=EVL_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=평가손익금액;
			 INDEX=9, ITEM=PFLS_RT, TYPE=string, SIZE=20, CAPTION=손익율;
			 INDEX=10, ITEM=CLR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=청산가능수량;
			 INDEX=11, ITEM=PCHS_ACBK_AMT, TYPE=string, SIZE=19, CAPTION=매입장부금액;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strPWD;		//비밀번호
CString strINQ_DT;		//조회일자
CString strDCD;		//구분코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q18", "OTS2850Q18_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q18", "OTS2850Q18_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q18", "OTS2850Q18_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q18", "OTS2850Q18_in", "INQ_DT", strINQ_DT);		//조회일자
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q18", "OTS2850Q18_in", "DCD", strDCD);		//구분코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "PRDT_CD", nRow);		//상품코드
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "PRDT_NM", nRow);		//상품명
CString strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "SELL_BUY_DCD", nRow);		//매도매수구분코드
CString strSELL_BUY_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//매도매수구분명
CString strUSTL_CTRC_QNT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "USTL_CTRC_QNT", nRow);		//미결제약정수량
CString strAVR_PRC = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "AVR_PRC", nRow);		//평균가격
CString strNOW_PRC = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "NOW_PRC", nRow);		//현재가격
CString strEVL_AMT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "EVL_AMT", nRow);		//평가금액
CString strEVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "EVL_PFLS_AMT", nRow);		//평가손익금액
CString strPFLS_RT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "PFLS_RT", nRow);		//손익율
CString strCLR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "CLR_PSBL_QNT", nRow);		//청산가능수량
CString strPCHS_ACBK_AMT = m_CommAgent.GetTranOutputData("OTS2850Q18", "OTS2850Q18_out_sub01", "PCHS_ACBK_AMT", nRow);		//매입장부금액
