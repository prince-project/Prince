BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1841Q00, TR_NAME=HTS전용잔고평가조회1, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS1841Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=3, ITEM=INQ_DVSN, TYPE=string, SIZE=1, CAPTION=조회구분;
			 INDEX=4, ITEM=TRDE_CT_INCL_YN, TYPE=string, SIZE=1, CAPTION=매매비용포함여부;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS1841Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=DACA, TYPE=string, SIZE=19, CAPTION=예수금;
			 INDEX=1, ITEM=NDY_PRSM_DACA, TYPE=string, SIZE=19, CAPTION=익일추정예수금;
			 INDEX=2, ITEM=NX_NDY_PRSM_DACA, TYPE=string, SIZE=19, CAPTION=익익일추정예수금;
			 INDEX=3, ITEM=SBST_AMT, TYPE=string, SIZE=19, CAPTION=대용금액;
			 INDEX=4, ITEM=NDY_PRSM_SBST_AMT, TYPE=string, SIZE=19, CAPTION=익일추정대용금액;
			 INDEX=5, ITEM=NX_NDY_PRSM_SBST_AMT, TYPE=string, SIZE=19, CAPTION=익익일추정대용금액;
			 INDEX=6, ITEM=BFDT_SELL_EXCAL_AMT, TYPE=string, SIZE=19, CAPTION=전일매도정산금액;
			 INDEX=7, ITEM=BFDT_BUY_EXCAL_AMT, TYPE=string, SIZE=19, CAPTION=전일매수정산금액;
			 INDEX=8, ITEM=TDAY_SELL_EXCAL_AMT, TYPE=string, SIZE=19, CAPTION=금일매도정산금액;
			 INDEX=9, ITEM=TDAY_BUY_EXCAL_AMT, TYPE=string, SIZE=19, CAPTION=금일매수정산금액;
			 INDEX=10, ITEM=CRDT_AMT, TYPE=string, SIZE=19, CAPTION=신용금액;
			 INDEX=11, ITEM=MRTG_RTO, TYPE=string, SIZE=17, CAPTION=담보비율;
			 INDEX=12, ITEM=RQRM_MRTG_AMT, TYPE=string, SIZE=19, CAPTION=소요담보금액;
			 INDEX=13, ITEM=MRTG_LACK_AMT, TYPE=string, SIZE=19, CAPTION=담보부족금액;
			 INDEX=14, ITEM=MXM_ORDR_PSBL_AMT, TYPE=string, SIZE=20, CAPTION=최대주문가능금액;
			 INDEX=15, ITEM=MINM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=최소주문가능금액;
			 INDEX=16, ITEM=CRDT_MXM_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=신용최대가능금액;
			 INDEX=17, ITEM=ORDR_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=주문가능현금;
			 INDEX=18, ITEM=ORDR_PSBL_SBST_AMT, TYPE=string, SIZE=19, CAPTION=주문가능대용금액;
			 INDEX=19, ITEM=DRWG_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=출금가능금액;
			 INDEX=20, ITEM=NDY_DRWG_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=익일출금가능금액;
			 INDEX=21, ITEM=ACNT_EVL_AMT, TYPE=string, SIZE=19, CAPTION=계좌평가금액;
			 INDEX=22, ITEM=PCHS_TOT_AMT, TYPE=string, SIZE=19, CAPTION=매입총금액;
			 INDEX=23, ITEM=SCTS_EVL_AMT, TYPE=string, SIZE=19, CAPTION=유가증권평가금액;
			 INDEX=24, ITEM=PFLS_AMT, TYPE=string, SIZE=19, CAPTION=손익금액;
			 INDEX=25, ITEM=EVL_PFLS_RT, TYPE=string, SIZE=17, CAPTION=평가손익율;
		END_OUTPUT0_ITEM

		REC_NAME=OTS1841Q00_out_sub02, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=단축상품코드;
			 INDEX=1, ITEM=PRDT_ABBR_NM, TYPE=string, SIZE=300, CAPTION=상품약어명;
			 INDEX=2, ITEM=ITM_WMY_GRD_DCD, TYPE=string, SIZE=1, CAPTION=종목증거금등급구분코드;
			 INDEX=3, ITEM=INQ_BLN_DVSN_NM, TYPE=string, SIZE=30, CAPTION=조회잔고구분명;
			 INDEX=4, ITEM=LOAN_DT, TYPE=string, SIZE=8, CAPTION=대출일자;
			 INDEX=5, ITEM=EXP_DT, TYPE=string, SIZE=8, CAPTION=만기일자;
			 INDEX=6, ITEM=LOAN_SN, TYPE=string, SIZE=11, CAPTION=대출일련번호;
			 INDEX=7, ITEM=STL_BLN_QNT, TYPE=string, SIZE=19, CAPTION=결제잔고수량;
			 INDEX=8, ITEM=CNCS_BLN_QNT, TYPE=string, SIZE=19, CAPTION=체결잔고수량;
			 INDEX=9, ITEM=SELL_QNT, TYPE=string, SIZE=19, CAPTION=매도수량;
			 INDEX=10, ITEM=BUY_QNT, TYPE=string, SIZE=19, CAPTION=매수수량;
			 INDEX=11, ITEM=SELL_AVR_UNPR, TYPE=string, SIZE=17, CAPTION=매도평균단가;
			 INDEX=12, ITEM=BUY_AVR_UNPR, TYPE=string, SIZE=19, CAPTION=매수평균단가;
			 INDEX=13, ITEM=SELL_AMT, TYPE=string, SIZE=19, CAPTION=매도금액;
			 INDEX=14, ITEM=BUY_AMT, TYPE=string, SIZE=19, CAPTION=매수금액;
			 INDEX=15, ITEM=PV, TYPE=string, SIZE=19, CAPTION=현재가;
			 INDEX=16, ITEM=PFLS_AMT, TYPE=string, SIZE=19, CAPTION=손익금액;
			 INDEX=17, ITEM=PFLS_RT, TYPE=string, SIZE=20, CAPTION=손익율;
			 INDEX=18, ITEM=THDT_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=당일손익금액;
			 INDEX=19, ITEM=THDT_PFLS_RT, TYPE=string, SIZE=19, CAPTION=당일손익율;
			 INDEX=20, ITEM=RMN_QNT, TYPE=string, SIZE=19, CAPTION=잔여수량;
			 INDEX=21, ITEM=EVL_AMT, TYPE=string, SIZE=19, CAPTION=평가금액;
			 INDEX=22, ITEM=CRDT_AMT, TYPE=string, SIZE=19, CAPTION=신용금액;
			 INDEX=23, ITEM=CRDT_INTR_AMT, TYPE=string, SIZE=19, CAPTION=신용이자금액;
			 INDEX=24, ITEM=PCHS_AMT, TYPE=string, SIZE=19, CAPTION=매입금액;
			 INDEX=25, ITEM=FEE, TYPE=string, SIZE=19, CAPTION=수수료;
			 INDEX=26, ITEM=WHIT, TYPE=string, SIZE=19, CAPTION=제세금;
			 INDEX=27, ITEM=SELL_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=매도가능수량;
			 INDEX=28, ITEM=INQ_BLN_DCD, TYPE=string, SIZE=2, CAPTION=조회잔고구분코드;
			 INDEX=29, ITEM=FLC_RT, TYPE=string, SIZE=17, CAPTION=등락율;
			 INDEX=30, ITEM=MARK_DCD, TYPE=string, SIZE=1, CAPTION=부호구분코드;
			 INDEX=31, ITEM=PRPT, TYPE=string, SIZE=17, CAPTION=대비;
			 INDEX=32, ITEM=PCHS_UNPR, TYPE=string, SIZE=23, CAPTION=매입단가;
			 INDEX=33, ITEM=SELL_PFLS_AMT, TYPE=string, SIZE=24, CAPTION=매도손익금액;
			 INDEX=34, ITEM=SFGV, TYPE=string, SIZE=17, CAPTION=비중;
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
CString strINQ_DVSN;		//조회구분
CString strTRDE_CT_INCL_YN;		//매매비용포함여부

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "INQ_DVSN", strINQ_DVSN);		//조회구분
m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "TRDE_CT_INCL_YN", strTRDE_CT_INCL_YN);		//매매비용포함여부




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strDACA = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "DACA", nRow);		//예수금
CString strNDY_PRSM_DACA = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "NDY_PRSM_DACA", nRow);		//익일추정예수금
CString strNX_NDY_PRSM_DACA = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "NX_NDY_PRSM_DACA", nRow);		//익익일추정예수금
CString strSBST_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "SBST_AMT", nRow);		//대용금액
CString strNDY_PRSM_SBST_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "NDY_PRSM_SBST_AMT", nRow);		//익일추정대용금액
CString strNX_NDY_PRSM_SBST_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "NX_NDY_PRSM_SBST_AMT", nRow);		//익익일추정대용금액
CString strBFDT_SELL_EXCAL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "BFDT_SELL_EXCAL_AMT", nRow);		//전일매도정산금액
CString strBFDT_BUY_EXCAL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "BFDT_BUY_EXCAL_AMT", nRow);		//전일매수정산금액
CString strTDAY_SELL_EXCAL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "TDAY_SELL_EXCAL_AMT", nRow);		//금일매도정산금액
CString strTDAY_BUY_EXCAL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "TDAY_BUY_EXCAL_AMT", nRow);		//금일매수정산금액
CString strCRDT_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "CRDT_AMT", nRow);		//신용금액
CString strMRTG_RTO = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "MRTG_RTO", nRow);		//담보비율
CString strRQRM_MRTG_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "RQRM_MRTG_AMT", nRow);		//소요담보금액
CString strMRTG_LACK_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "MRTG_LACK_AMT", nRow);		//담보부족금액
CString strMXM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "MXM_ORDR_PSBL_AMT", nRow);		//최대주문가능금액
CString strMINM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "MINM_ORDR_PSBL_AMT", nRow);		//최소주문가능금액
CString strCRDT_MXM_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "CRDT_MXM_PSBL_AMT", nRow);		//신용최대가능금액
CString strORDR_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "ORDR_PSBL_CSH", nRow);		//주문가능현금
CString strORDR_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "ORDR_PSBL_SBST_AMT", nRow);		//주문가능대용금액
CString strDRWG_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "DRWG_PSBL_AMT", nRow);		//출금가능금액
CString strNDY_DRWG_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "NDY_DRWG_PSBL_AMT", nRow);		//익일출금가능금액
CString strACNT_EVL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "ACNT_EVL_AMT", nRow);		//계좌평가금액
CString strPCHS_TOT_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "PCHS_TOT_AMT", nRow);		//매입총금액
CString strSCTS_EVL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "SCTS_EVL_AMT", nRow);		//유가증권평가금액
CString strPFLS_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "PFLS_AMT", nRow);		//손익금액
CString strEVL_PFLS_RT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "EVL_PFLS_RT", nRow);		//평가손익율
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SHTN_PRDT_CD", nRow);		//단축상품코드
CString strPRDT_ABBR_NM = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PRDT_ABBR_NM", nRow);		//상품약어명
CString strITM_WMY_GRD_DCD = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "ITM_WMY_GRD_DCD", nRow);		//종목증거금등급구분코드
CString strINQ_BLN_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "INQ_BLN_DVSN_NM", nRow);		//조회잔고구분명
CString strLOAN_DT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "LOAN_DT", nRow);		//대출일자
CString strEXP_DT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "EXP_DT", nRow);		//만기일자
CString strLOAN_SN = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "LOAN_SN", nRow);		//대출일련번호
CString strSTL_BLN_QNT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "STL_BLN_QNT", nRow);		//결제잔고수량
CString strCNCS_BLN_QNT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "CNCS_BLN_QNT", nRow);		//체결잔고수량
CString strSELL_QNT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SELL_QNT", nRow);		//매도수량
CString strBUY_QNT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "BUY_QNT", nRow);		//매수수량
CString strSELL_AVR_UNPR = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SELL_AVR_UNPR", nRow);		//매도평균단가
CString strBUY_AVR_UNPR = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "BUY_AVR_UNPR", nRow);		//매수평균단가
CString strSELL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SELL_AMT", nRow);		//매도금액
CString strBUY_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "BUY_AMT", nRow);		//매수금액
CString strPV = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PV", nRow);		//현재가
CString strPFLS_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PFLS_AMT", nRow);		//손익금액
CString strPFLS_RT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PFLS_RT", nRow);		//손익율
CString strTHDT_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "THDT_PFLS_AMT", nRow);		//당일손익금액
CString strTHDT_PFLS_RT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "THDT_PFLS_RT", nRow);		//당일손익율
CString strRMN_QNT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "RMN_QNT", nRow);		//잔여수량
CString strEVL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "EVL_AMT", nRow);		//평가금액
CString strCRDT_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "CRDT_AMT", nRow);		//신용금액
CString strCRDT_INTR_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "CRDT_INTR_AMT", nRow);		//신용이자금액
CString strPCHS_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PCHS_AMT", nRow);		//매입금액
CString strFEE = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "FEE", nRow);		//수수료
CString strWHIT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "WHIT", nRow);		//제세금
CString strSELL_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SELL_PSBL_QNT", nRow);		//매도가능수량
CString strINQ_BLN_DCD = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "INQ_BLN_DCD", nRow);		//조회잔고구분코드
CString strFLC_RT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "FLC_RT", nRow);		//등락율
CString strMARK_DCD = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "MARK_DCD", nRow);		//부호구분코드
CString strPRPT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PRPT", nRow);		//대비
CString strPCHS_UNPR = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PCHS_UNPR", nRow);		//매입단가
CString strSELL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SELL_PFLS_AMT", nRow);		//매도손익금액
CString strSFGV = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SFGV", nRow);		//비중
