BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1201Q00, TR_NAME=주문체결내역체결단가별, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS1201Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=3, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=주문일자;
			 INDEX=4, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=5, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=주문일련번호;
			 INDEX=6, ITEM=CNCS_DVSN, TYPE=string, SIZE=1, CAPTION=체결구분;
			 INDEX=7, ITEM=INQ_ORD_DVSN, TYPE=string, SIZE=1, CAPTION=조회순서구분;
			 INDEX=8, ITEM=PRDT_DVSN, TYPE=string, SIZE=1, CAPTION=상품구분;
			 INDEX=9, ITEM=MKT_TR_DCD, TYPE=string, SIZE=2, CAPTION=시장거래구분코드;
			 INDEX=10, ITEM=CRDT_TR_DCD, TYPE=string, SIZE=2, CAPTION=신용거래구분코드;
			 INDEX=11, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=통신매체구분코드;
			 INDEX=12, ITEM=ORDR_PRCS_STTS_DCD, TYPE=string, SIZE=1, CAPTION=주문처리상태구분코드;
			 INDEX=13, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=매도매수구분코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS1201Q00_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=관리부점코드;
			 INDEX=1, ITEM=SELL_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=매도체결수량;
			 INDEX=2, ITEM=SELL_CNCS_AMT, TYPE=string, SIZE=19, CAPTION=매도체결금액;
			 INDEX=3, ITEM=BUY_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=매수체결수량;
			 INDEX=4, ITEM=BUY_CNCS_AMT, TYPE=string, SIZE=19, CAPTION=매수체결금액;
		END_OUTPUT0_ITEM

		REC_NAME=OTS1201Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=주문일련번호;
			 INDEX=1, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=원주문일련번호;
			 INDEX=2, ITEM=ORDR_RVSE_CNCL_DVSN_NM, TYPE=string, SIZE=40, CAPTION=주문정정취소구분명;
			 INDEX=3, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=4, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=단축상품코드;
			 INDEX=5, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=상품명;
			 INDEX=6, ITEM=ORDR_DCD_NM, TYPE=string, SIZE=40, CAPTION=주문구분코드명;
			 INDEX=7, ITEM=NMPR_DVSN_NM, TYPE=string, SIZE=80, CAPTION=호가구분명;
			 INDEX=8, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=9, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=체결수량;
			 INDEX=10, ITEM=ORDR_UNPR, TYPE=string, SIZE=19, CAPTION=주문단가;
			 INDEX=11, ITEM=ITG_BOND_ORDR_UNPR, TYPE=string, SIZE=17, CAPTION=장내채권주문단가;
			 INDEX=12, ITEM=CNCS_UNPR, TYPE=string, SIZE=19, CAPTION=체결단가;
			 INDEX=13, ITEM=ITG_BOND_CNCS_UNPR, TYPE=string, SIZE=17, CAPTION=장내채권체결단가;
			 INDEX=14, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=주문잔여수량;
			 INDEX=15, ITEM=CNCS_QNT_SMM, TYPE=string, SIZE=19, CAPTION=체결수량합계;
			 INDEX=16, ITEM=ORDR_MDIA_NM, TYPE=string, SIZE=50, CAPTION=주문매체명;
			 INDEX=17, ITEM=ORDR_PRCS_STTS_DCD, TYPE=string, SIZE=1, CAPTION=주문처리상태구분코드;
			 INDEX=18, ITEM=ORDR_TM, TYPE=string, SIZE=6, CAPTION=주문시각;
			 INDEX=19, ITEM=LOAN_DT, TYPE=string, SIZE=8, CAPTION=대출일자;
			 INDEX=20, ITEM=LOAN_SN, TYPE=string, SIZE=11, CAPTION=대출일련번호;
			 INDEX=21, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=주문일자;
			 INDEX=22, ITEM=CNCS_DT, TYPE=string, SIZE=8, CAPTION=체결일자;
			 INDEX=23, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=관리부점코드;
			 INDEX=24, ITEM=SCTS_DCD, TYPE=string, SIZE=2, CAPTION=유가증권구분코드;
			 INDEX=25, ITEM=TRDE_STL_DE_DCD, TYPE=string, SIZE=1, CAPTION=매매결제일구분코드;
			 INDEX=26, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=매도매수구분코드;
			 INDEX=27, ITEM=ORDR_PRCS_STTS_DVSN_NM, TYPE=string, SIZE=40, CAPTION=주문처리상태구분명;
			 INDEX=28, ITEM=CRDT_TR_DCD, TYPE=string, SIZE=2, CAPTION=신용거래구분코드;
			 INDEX=29, ITEM=ORDR_KND_DCD, TYPE=string, SIZE=2, CAPTION=주문종류구분코드;
			 INDEX=30, ITEM=CSGN_TRDE_DCD, TYPE=string, SIZE=2, CAPTION=위탁매매구분코드;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strPWD;		//비밀번호
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strORDR_DT;		//주문일자
CString strPRDT_CD;		//상품코드
CString strORDR_SN;		//주문일련번호
CString strCNCS_DVSN;		//체결구분
CString strINQ_ORD_DVSN;		//조회순서구분
CString strPRDT_DVSN;		//상품구분
CString strMKT_TR_DCD;		//시장거래구분코드
CString strCRDT_TR_DCD;		//신용거래구분코드
CString strCOMM_MDIA_DCD;		//통신매체구분코드
CString strORDR_PRCS_STTS_DCD;		//주문처리상태구분코드
CString strSELL_BUY_DCD;		//매도매수구분코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "ORDR_DT", strORDR_DT);		//주문일자
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "PRDT_CD", strPRDT_CD);		//상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "ORDR_SN", strORDR_SN);		//주문일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "CNCS_DVSN", strCNCS_DVSN);		//체결구분
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "INQ_ORD_DVSN", strINQ_ORD_DVSN);		//조회순서구분
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "PRDT_DVSN", strPRDT_DVSN);		//상품구분
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "MKT_TR_DCD", strMKT_TR_DCD);		//시장거래구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "CRDT_TR_DCD", strCRDT_TR_DCD);		//신용거래구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//통신매체구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "ORDR_PRCS_STTS_DCD", strORDR_PRCS_STTS_DCD);		//주문처리상태구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//매도매수구분코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strMNGM_BDCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out", "MNGM_BDCD", 0);		//관리부점코드
CString strSELL_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out", "SELL_CNCS_QNT", 0);		//매도체결수량
CString strSELL_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out", "SELL_CNCS_AMT", 0);		//매도체결금액
CString strBUY_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out", "BUY_CNCS_QNT", 0);		//매수체결수량
CString strBUY_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out", "BUY_CNCS_AMT", 0);		//매수체결금액
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_SN", nRow);		//주문일련번호
CString strOR_ORDR_SN = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "OR_ORDR_SN", nRow);		//원주문일련번호
CString strORDR_RVSE_CNCL_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_RVSE_CNCL_DVSN_NM", nRow);		//주문정정취소구분명
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "PRDT_CD", nRow);		//상품코드
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "SHTN_PRDT_CD", nRow);		//단축상품코드
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "PRDT_NM", nRow);		//상품명
CString strORDR_DCD_NM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_DCD_NM", nRow);		//주문구분코드명
CString strNMPR_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "NMPR_DVSN_NM", nRow);		//호가구분명
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_QNT", nRow);		//주문수량
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "CNCS_QNT", nRow);		//체결수량
CString strORDR_UNPR = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_UNPR", nRow);		//주문단가
CString strITG_BOND_ORDR_UNPR = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ITG_BOND_ORDR_UNPR", nRow);		//장내채권주문단가
CString strCNCS_UNPR = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "CNCS_UNPR", nRow);		//체결단가
CString strITG_BOND_CNCS_UNPR = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ITG_BOND_CNCS_UNPR", nRow);		//장내채권체결단가
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_RMN_QNT", nRow);		//주문잔여수량
CString strCNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "CNCS_QNT_SMM", nRow);		//체결수량합계
CString strORDR_MDIA_NM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_MDIA_NM", nRow);		//주문매체명
CString strORDR_PRCS_STTS_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_PRCS_STTS_DCD", nRow);		//주문처리상태구분코드
CString strORDR_TM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_TM", nRow);		//주문시각
CString strLOAN_DT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "LOAN_DT", nRow);		//대출일자
CString strLOAN_SN = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "LOAN_SN", nRow);		//대출일련번호
CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_DT", nRow);		//주문일자
CString strCNCS_DT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "CNCS_DT", nRow);		//체결일자
CString strMNGM_BDCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "MNGM_BDCD", nRow);		//관리부점코드
CString strSCTS_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "SCTS_DCD", nRow);		//유가증권구분코드
CString strTRDE_STL_DE_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "TRDE_STL_DE_DCD", nRow);		//매매결제일구분코드
CString strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "SELL_BUY_DCD", nRow);		//매도매수구분코드
CString strORDR_PRCS_STTS_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_PRCS_STTS_DVSN_NM", nRow);		//주문처리상태구분명
CString strCRDT_TR_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "CRDT_TR_DCD", nRow);		//신용거래구분코드
CString strORDR_KND_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_KND_DCD", nRow);		//주문종류구분코드
CString strCSGN_TRDE_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "CSGN_TRDE_DCD", nRow);		//위탁매매구분코드
