BEGIN_TRAN_LAYOUT

	TR_CODE=OTS4201Q22, TR_NAME=해외주식온라인주문주식잔고API, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS4201Q22_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=3, ITEM=FEE_DVSN, TYPE=string, SIZE=1, CAPTION=수수료구분;
			 INDEX=4, ITEM=BLN_DCD, TYPE=string, SIZE=1, CAPTION=잔고구분코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS4201Q22_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=OSTK_INV_INF_MKT_DCD, TYPE=string, SIZE=2, CAPTION=해외주식투자정보시장구분코드;
			 INDEX=1, ITEM=OSTK_MKT_CD, TYPE=string, SIZE=2, CAPTION=해외주식시장코드;
			 INDEX=2, ITEM=OSTK_MKT_NM, TYPE=string, SIZE=100, CAPTION=해외주식시장명;
			 INDEX=3, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=통화코드;
			 INDEX=4, ITEM=OVRS_SMBL_CD, TYPE=string, SIZE=12, CAPTION=해외상징코드;
			 INDEX=5, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=상품명;
			 INDEX=6, ITEM=CNB_BLN_QNT, TYPE=string, SIZE=26, CAPTION=체결기준잔고수량;
			 INDEX=7, ITEM=SELL_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=매도가능수량;
			 INDEX=8, ITEM=OSTK_BUY_AMT, TYPE=string, SIZE=24, CAPTION=해외주식매수금액;
			 INDEX=9, ITEM=OSTK_BUY_PRC, TYPE=string, SIZE=24, CAPTION=해외주식매수가격;
			 INDEX=10, ITEM=OSTK_CLPR, TYPE=string, SIZE=24, CAPTION=해외주식종가;
			 INDEX=11, ITEM=OSTK_FRCR_EVL_AMT, TYPE=string, SIZE=24, CAPTION=해외주식외화평가금액;
			 INDEX=12, ITEM=TRDE_UN_QNT, TYPE=string, SIZE=19, CAPTION=매매단위수량;
			 INDEX=13, ITEM=LOAN_SN, TYPE=string, SIZE=11, CAPTION=대출일련번호;
			 INDEX=14, ITEM=LOAN_DT, TYPE=string, SIZE=8, CAPTION=대출일자;
			 INDEX=15, ITEM=LOAN_AMT, TYPE=string, SIZE=19, CAPTION=대출금액;
			 INDEX=16, ITEM=BLN_DCD, TYPE=string, SIZE=1, CAPTION=잔고구분코드;
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
CString strFEE_DVSN;		//수수료구분
CString strBLN_DCD;		//잔고구분코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q22", "OTS4201Q22_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q22", "OTS4201Q22_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q22", "OTS4201Q22_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q22", "OTS4201Q22_in", "FEE_DVSN", strFEE_DVSN);		//수수료구분
m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q22", "OTS4201Q22_in", "BLN_DCD", strBLN_DCD);		//잔고구분코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strOSTK_INV_INF_MKT_DCD = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_INV_INF_MKT_DCD", nRow);		//해외주식투자정보시장구분코드
CString strOSTK_MKT_CD = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_MKT_CD", nRow);		//해외주식시장코드
CString strOSTK_MKT_NM = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_MKT_NM", nRow);		//해외주식시장명
CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "CRRY_CD", nRow);		//통화코드
CString strOVRS_SMBL_CD = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OVRS_SMBL_CD", nRow);		//해외상징코드
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "PRDT_NM", nRow);		//상품명
CString strCNB_BLN_QNT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "CNB_BLN_QNT", nRow);		//체결기준잔고수량
CString strSELL_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "SELL_PSBL_QNT", nRow);		//매도가능수량
CString strOSTK_BUY_AMT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_BUY_AMT", nRow);		//해외주식매수금액
CString strOSTK_BUY_PRC = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_BUY_PRC", nRow);		//해외주식매수가격
CString strOSTK_CLPR = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_CLPR", nRow);		//해외주식종가
CString strOSTK_FRCR_EVL_AMT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_FRCR_EVL_AMT", nRow);		//해외주식외화평가금액
CString strTRDE_UN_QNT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "TRDE_UN_QNT", nRow);		//매매단위수량
CString strLOAN_SN = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "LOAN_SN", nRow);		//대출일련번호
CString strLOAN_DT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "LOAN_DT", nRow);		//대출일자
CString strLOAN_AMT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "LOAN_AMT", nRow);		//대출금액
CString strBLN_DCD = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "BLN_DCD", nRow);		//잔고구분코드
