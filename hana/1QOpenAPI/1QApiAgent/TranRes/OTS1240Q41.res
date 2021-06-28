BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1240Q41, TR_NAME=OFS체결단가별주문체결내역조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS1240Q41_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=3, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=주문일자;
			 INDEX=4, ITEM=INQ_END_DT, TYPE=string, SIZE=8, CAPTION=조회종료일자;
			 INDEX=5, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=6, ITEM=SCTS_DVSN, TYPE=string, SIZE=1, CAPTION=유가증권구분;
			 INDEX=7, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=매도매수구분코드;
			 INDEX=8, ITEM=INP_MKT_DCD, TYPE=string, SIZE=1, CAPTION=입력시장구분코드;
			 INDEX=9, ITEM=ORDR_STTS_CD, TYPE=string, SIZE=2, CAPTION=주문상태코드;
			 INDEX=10, ITEM=CRDT_DCD, TYPE=string, SIZE=2, CAPTION=신용구분코드;
			 INDEX=11, ITEM=COMM_MDIA_DVSN, TYPE=string, SIZE=2, CAPTION=통신매체구분;
			 INDEX=12, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=주문일련번호;
			 INDEX=13, ITEM=ORDR_ORD, TYPE=string, SIZE=1, CAPTION=주문순서;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS1240Q41_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=SELL_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=매도체결수량;
			 INDEX=1, ITEM=SELL_CNCS_AMT, TYPE=string, SIZE=19, CAPTION=매도체결금액;
			 INDEX=2, ITEM=BUY_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=매수체결수량;
			 INDEX=3, ITEM=BUY_CNCS_AMT, TYPE=string, SIZE=19, CAPTION=매수체결금액;
			 INDEX=4, ITEM=CSGN_ACNT_NM, TYPE=string, SIZE=80, CAPTION=위탁계좌명;
		END_OUTPUT0_ITEM

		REC_NAME=OTS1240Q41_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=주문일련번호;
			 INDEX=1, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=원주문일련번호;
			 INDEX=2, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=3, ITEM=SELL_BUY_DCD_NM, TYPE=string, SIZE=40, CAPTION=매도매수구분코드명;
			 INDEX=4, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=5, ITEM=ITG_BOND_ORDR_UNPR, TYPE=string, SIZE=17, CAPTION=장내채권주문단가;
			 INDEX=6, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=주문잔여수량;
			 INDEX=7, ITEM=COMM_MDIA_DCD_NM, TYPE=string, SIZE=24, CAPTION=통신매체구분코드명;
			 INDEX=8, ITEM=ORDR_TM, TYPE=string, SIZE=6, CAPTION=주문시각;
			 INDEX=9, ITEM=RVSE_CNCL_DVSN_NM, TYPE=string, SIZE=40, CAPTION=정정취소구분명;
			 INDEX=10, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=상품명;
			 INDEX=11, ITEM=NMPR_DVSN_NM, TYPE=string, SIZE=80, CAPTION=호가구분명;
			 INDEX=12, ITEM=SMM_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=합계체결수량;
			 INDEX=13, ITEM=ITG_BOND_CNCS_UNPR, TYPE=string, SIZE=17, CAPTION=장내채권체결단가;
			 INDEX=14, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=체결수량;
			 INDEX=15, ITEM=PRCS_STTS_NM, TYPE=string, SIZE=20, CAPTION=처리상태명;
			 INDEX=16, ITEM=LOAN_SN, TYPE=string, SIZE=11, CAPTION=대출일련번호;
			 INDEX=17, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=주문일자;
			 INDEX=18, ITEM=BDCD, TYPE=string, SIZE=5, CAPTION=부점코드;
			 INDEX=19, ITEM=SCTS_DCD, TYPE=string, SIZE=2, CAPTION=유가증권구분코드;
			 INDEX=20, ITEM=TRDE_STL_DE_DCD, TYPE=string, SIZE=1, CAPTION=매매결제일구분코드;
			 INDEX=21, ITEM=DETL_PRCS_DVSN, TYPE=string, SIZE=1, CAPTION=상세처리구분;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strPWD;		//비밀번호
CString strORDR_DT;		//주문일자
CString strINQ_END_DT;		//조회종료일자
CString strPRDT_CD;		//상품코드
CString strSCTS_DVSN;		//유가증권구분
CString strSELL_BUY_DCD;		//매도매수구분코드
CString strINP_MKT_DCD;		//입력시장구분코드
CString strORDR_STTS_CD;		//주문상태코드
CString strCRDT_DCD;		//신용구분코드
CString strCOMM_MDIA_DVSN;		//통신매체구분
CString strORDR_SN;		//주문일련번호
CString strORDR_ORD;		//주문순서

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "ORDR_DT", strORDR_DT);		//주문일자
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "INQ_END_DT", strINQ_END_DT);		//조회종료일자
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "PRDT_CD", strPRDT_CD);		//상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "SCTS_DVSN", strSCTS_DVSN);		//유가증권구분
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//매도매수구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "INP_MKT_DCD", strINP_MKT_DCD);		//입력시장구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "ORDR_STTS_CD", strORDR_STTS_CD);		//주문상태코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "CRDT_DCD", strCRDT_DCD);		//신용구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "COMM_MDIA_DVSN", strCOMM_MDIA_DVSN);		//통신매체구분
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "ORDR_SN", strORDR_SN);		//주문일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "ORDR_ORD", strORDR_ORD);		//주문순서




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strSELL_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out", "SELL_CNCS_QNT", 0);		//매도체결수량
CString strSELL_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out", "SELL_CNCS_AMT", 0);		//매도체결금액
CString strBUY_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out", "BUY_CNCS_QNT", 0);		//매수체결수량
CString strBUY_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out", "BUY_CNCS_AMT", 0);		//매수체결금액
CString strCSGN_ACNT_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out", "CSGN_ACNT_NM", 0);		//위탁계좌명
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ORDR_SN", nRow);		//주문일련번호
CString strOR_ORDR_SN = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "OR_ORDR_SN", nRow);		//원주문일련번호
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "PRDT_CD", nRow);		//상품코드
CString strSELL_BUY_DCD_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "SELL_BUY_DCD_NM", nRow);		//매도매수구분코드명
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ORDR_QNT", nRow);		//주문수량
CString strITG_BOND_ORDR_UNPR = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ITG_BOND_ORDR_UNPR", nRow);		//장내채권주문단가
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ORDR_RMN_QNT", nRow);		//주문잔여수량
CString strCOMM_MDIA_DCD_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "COMM_MDIA_DCD_NM", nRow);		//통신매체구분코드명
CString strORDR_TM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ORDR_TM", nRow);		//주문시각
CString strRVSE_CNCL_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "RVSE_CNCL_DVSN_NM", nRow);		//정정취소구분명
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "PRDT_NM", nRow);		//상품명
CString strNMPR_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "NMPR_DVSN_NM", nRow);		//호가구분명
CString strSMM_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "SMM_CNCS_QNT", nRow);		//합계체결수량
CString strITG_BOND_CNCS_UNPR = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ITG_BOND_CNCS_UNPR", nRow);		//장내채권체결단가
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "CNCS_QNT", nRow);		//체결수량
CString strPRCS_STTS_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "PRCS_STTS_NM", nRow);		//처리상태명
CString strLOAN_SN = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "LOAN_SN", nRow);		//대출일련번호
CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ORDR_DT", nRow);		//주문일자
CString strBDCD = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "BDCD", nRow);		//부점코드
CString strSCTS_DCD = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "SCTS_DCD", nRow);		//유가증권구분코드
CString strTRDE_STL_DE_DCD = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "TRDE_STL_DE_DCD", nRow);		//매매결제일구분코드
CString strDETL_PRCS_DVSN = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "DETL_PRCS_DVSN", nRow);		//상세처리구분
