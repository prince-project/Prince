BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2850Q17, TR_NAME=계좌예탁금세부내역, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS2850Q17_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS2850Q17_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=OPMK_DPST_TOT_AMT, TYPE=string, SIZE=19, CAPTION=개장예탁총금액;
			 INDEX=1, ITEM=OPMK_DPST_CSH, TYPE=string, SIZE=19, CAPTION=개장예탁현금;
			 INDEX=2, ITEM=OPMK_DPST_SBST_AMT, TYPE=string, SIZE=19, CAPTION=개장예탁대용금액;
			 INDEX=3, ITEM=FTR_EXCAL_DEB_AMT, TYPE=string, SIZE=19, CAPTION=선물정산차금금액;
			 INDEX=4, ITEM=OPT_STL_DEB_AMT, TYPE=string, SIZE=19, CAPTION=옵션결제차금금액;
			 INDEX=5, ITEM=FEE_SMM_AMT, TYPE=string, SIZE=19, CAPTION=수수료합계금액;
			 INDEX=6, ITEM=RNDR_SMM, TYPE=string, SIZE=19, CAPTION=입출금합계;
			 INDEX=7, ITEM=EVL_DPST_TOT_AMT, TYPE=string, SIZE=19, CAPTION=평가예탁총금액;
			 INDEX=8, ITEM=FTR_RLZ_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=선물실현손익금액;
			 INDEX=9, ITEM=OPT_RLZ_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=옵션실현손익금액;
			 INDEX=10, ITEM=FTR_FEE, TYPE=string, SIZE=19, CAPTION=선물수수료;
			 INDEX=11, ITEM=RCTM_AMT, TYPE=string, SIZE=19, CAPTION=입금금액;
			 INDEX=12, ITEM=EVL_DPST_CSH, TYPE=string, SIZE=19, CAPTION=평가예탁현금;
			 INDEX=13, ITEM=FTR_EVL_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=선물평가손익금액;
			 INDEX=14, ITEM=OPT_EVL_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=옵션평가손익금액;
			 INDEX=15, ITEM=OPT_FEE, TYPE=string, SIZE=19, CAPTION=옵션수수료;
			 INDEX=16, ITEM=DRWG_AMT, TYPE=string, SIZE=19, CAPTION=출금금액;
			 INDEX=17, ITEM=STL_DPST_TOT_AMT, TYPE=string, SIZE=19, CAPTION=결제예탁총금액;
			 INDEX=18, ITEM=DPST_TOT_AMT, TYPE=string, SIZE=19, CAPTION=예탁총금액;
			 INDEX=19, ITEM=CSGN_WMY_TOT_AMT, TYPE=string, SIZE=19, CAPTION=위탁증거금총금액;
			 INDEX=20, ITEM=ADIT_WMY_TOT_AMT, TYPE=string, SIZE=19, CAPTION=추가증거금총금액;
			 INDEX=21, ITEM=ORDR_PSBL_TOT_AMT, TYPE=string, SIZE=19, CAPTION=주문가능총금액;
			 INDEX=22, ITEM=WDRW_PSBL_TOT_AMT, TYPE=string, SIZE=19, CAPTION=인출가능총금액;
			 INDEX=23, ITEM=DPST_CSH, TYPE=string, SIZE=19, CAPTION=예탁현금;
			 INDEX=24, ITEM=CSGN_WMY_CSH, TYPE=string, SIZE=19, CAPTION=위탁증거금현금;
			 INDEX=25, ITEM=ADIT_WMY_CSH, TYPE=string, SIZE=19, CAPTION=추가증거금현금;
			 INDEX=26, ITEM=ORDR_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=주문가능현금;
			 INDEX=27, ITEM=WDRW_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=인출가능현금;
			 INDEX=28, ITEM=DPST_SBST_AMT, TYPE=string, SIZE=19, CAPTION=예탁대용금액;
			 INDEX=29, ITEM=WMY_SBST_AMT, TYPE=string, SIZE=19, CAPTION=증거금대용금액;
			 INDEX=30, ITEM=ADIT_WMY_SBST_AMT, TYPE=string, SIZE=19, CAPTION=추가증거금대용금액;
			 INDEX=31, ITEM=ORDR_PSBL_SBST_AMT, TYPE=string, SIZE=19, CAPTION=주문가능대용금액;
			 INDEX=32, ITEM=WDRW_PSBL_SBST_AMT, TYPE=string, SIZE=19, CAPTION=인출가능대용금액;
			 INDEX=33, ITEM=FTR_USTL_TOT_QNT, TYPE=string, SIZE=19, CAPTION=선물미결제총수량;
			 INDEX=34, ITEM=OPT_USTL_TOT_QNT, TYPE=string, SIZE=19, CAPTION=옵션미결제총수량;
			 INDEX=35, ITEM=FTR_CTRC_TOT_AMT, TYPE=string, SIZE=19, CAPTION=선물약정총금액;
			 INDEX=36, ITEM=OPT_CTRC_TOT_AMT, TYPE=string, SIZE=19, CAPTION=옵션약정총금액;
			 INDEX=37, ITEM=FTR_TR_TOT_QNT, TYPE=string, SIZE=19, CAPTION=선물거래총수량;
			 INDEX=38, ITEM=OPT_TR_TOT_QNT, TYPE=string, SIZE=19, CAPTION=옵션거래총수량;
			 INDEX=39, ITEM=FTR_SELL_USTL_QNT, TYPE=string, SIZE=19, CAPTION=선물매도미결제수량;
			 INDEX=40, ITEM=OPT_SELL_USTL_QNT, TYPE=string, SIZE=19, CAPTION=옵션매도미결제수량;
			 INDEX=41, ITEM=FTR_SELL_CTRC_AMT, TYPE=string, SIZE=19, CAPTION=선물매도약정금액;
			 INDEX=42, ITEM=OPT_SELL_CTRC_AMT, TYPE=string, SIZE=19, CAPTION=옵션매도약정금액;
			 INDEX=43, ITEM=FTR_SELL_TR_QNT, TYPE=string, SIZE=19, CAPTION=선물매도거래수량;
			 INDEX=44, ITEM=OPT_SELL_TR_QNT, TYPE=string, SIZE=19, CAPTION=옵션매도거래수량;
			 INDEX=45, ITEM=FTR_BUY_USTL_QNT, TYPE=string, SIZE=19, CAPTION=선물매수미결제수량;
			 INDEX=46, ITEM=OPT_BUY_USTL_QNT, TYPE=string, SIZE=19, CAPTION=옵션매수미결제수량;
			 INDEX=47, ITEM=FTR_BUY_CTRC_AMT, TYPE=string, SIZE=19, CAPTION=선물매수약정금액;
			 INDEX=48, ITEM=OPT_BUY_CTRC_AMT, TYPE=string, SIZE=19, CAPTION=옵션매수약정금액;
			 INDEX=49, ITEM=FTR_BUY_TR_QNT, TYPE=string, SIZE=19, CAPTION=선물매수거래수량;
			 INDEX=50, ITEM=OPT_BUY_TR_QNT, TYPE=string, SIZE=19, CAPTION=옵션매수거래수량;
			 INDEX=51, ITEM=NOW_TOT_WMY_RT, TYPE=string, SIZE=17, CAPTION=현재총증거금율;
			 INDEX=52, ITEM=CSH_WMY_RT, TYPE=string, SIZE=17, CAPTION=현금증거금율;
			 INDEX=53, ITEM=MNTN_WMY, TYPE=string, SIZE=19, CAPTION=유지증거금;
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

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q17", "OTS2850Q17_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q17", "OTS2850Q17_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q17", "OTS2850Q17_in", "PWD", strPWD);		//비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strOPMK_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPMK_DPST_TOT_AMT", 0);		//개장예탁총금액
CString strOPMK_DPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPMK_DPST_CSH", 0);		//개장예탁현금
CString strOPMK_DPST_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPMK_DPST_SBST_AMT", 0);		//개장예탁대용금액
CString strFTR_EXCAL_DEB_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_EXCAL_DEB_AMT", 0);		//선물정산차금금액
CString strOPT_STL_DEB_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_STL_DEB_AMT", 0);		//옵션결제차금금액
CString strFEE_SMM_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FEE_SMM_AMT", 0);		//수수료합계금액
CString strRNDR_SMM = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "RNDR_SMM", 0);		//입출금합계
CString strEVL_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "EVL_DPST_TOT_AMT", 0);		//평가예탁총금액
CString strFTR_RLZ_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_RLZ_PFLS_AMT", 0);		//선물실현손익금액
CString strOPT_RLZ_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_RLZ_PFLS_AMT", 0);		//옵션실현손익금액
CString strFTR_FEE = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_FEE", 0);		//선물수수료
CString strRCTM_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "RCTM_AMT", 0);		//입금금액
CString strEVL_DPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "EVL_DPST_CSH", 0);		//평가예탁현금
CString strFTR_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_EVL_PFLS_AMT", 0);		//선물평가손익금액
CString strOPT_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_EVL_PFLS_AMT", 0);		//옵션평가손익금액
CString strOPT_FEE = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_FEE", 0);		//옵션수수료
CString strDRWG_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DRWG_AMT", 0);		//출금금액
CString strSTL_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "STL_DPST_TOT_AMT", 0);		//결제예탁총금액
CString strDPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DPST_TOT_AMT", 0);		//예탁총금액
CString strCSGN_WMY_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "CSGN_WMY_TOT_AMT", 0);		//위탁증거금총금액
CString strADIT_WMY_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ADIT_WMY_TOT_AMT", 0);		//추가증거금총금액
CString strORDR_PSBL_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ORDR_PSBL_TOT_AMT", 0);		//주문가능총금액
CString strWDRW_PSBL_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WDRW_PSBL_TOT_AMT", 0);		//인출가능총금액
CString strDPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DPST_CSH", 0);		//예탁현금
CString strCSGN_WMY_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "CSGN_WMY_CSH", 0);		//위탁증거금현금
CString strADIT_WMY_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ADIT_WMY_CSH", 0);		//추가증거금현금
CString strORDR_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ORDR_PSBL_CSH", 0);		//주문가능현금
CString strWDRW_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WDRW_PSBL_CSH", 0);		//인출가능현금
CString strDPST_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DPST_SBST_AMT", 0);		//예탁대용금액
CString strWMY_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WMY_SBST_AMT", 0);		//증거금대용금액
CString strADIT_WMY_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ADIT_WMY_SBST_AMT", 0);		//추가증거금대용금액
CString strORDR_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ORDR_PSBL_SBST_AMT", 0);		//주문가능대용금액
CString strWDRW_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WDRW_PSBL_SBST_AMT", 0);		//인출가능대용금액
CString strFTR_USTL_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_USTL_TOT_QNT", 0);		//선물미결제총수량
CString strOPT_USTL_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_USTL_TOT_QNT", 0);		//옵션미결제총수량
CString strFTR_CTRC_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_CTRC_TOT_AMT", 0);		//선물약정총금액
CString strOPT_CTRC_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_CTRC_TOT_AMT", 0);		//옵션약정총금액
CString strFTR_TR_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_TR_TOT_QNT", 0);		//선물거래총수량
CString strOPT_TR_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_TR_TOT_QNT", 0);		//옵션거래총수량
CString strFTR_SELL_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_SELL_USTL_QNT", 0);		//선물매도미결제수량
CString strOPT_SELL_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_SELL_USTL_QNT", 0);		//옵션매도미결제수량
CString strFTR_SELL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_SELL_CTRC_AMT", 0);		//선물매도약정금액
CString strOPT_SELL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_SELL_CTRC_AMT", 0);		//옵션매도약정금액
CString strFTR_SELL_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_SELL_TR_QNT", 0);		//선물매도거래수량
CString strOPT_SELL_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_SELL_TR_QNT", 0);		//옵션매도거래수량
CString strFTR_BUY_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_BUY_USTL_QNT", 0);		//선물매수미결제수량
CString strOPT_BUY_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_BUY_USTL_QNT", 0);		//옵션매수미결제수량
CString strFTR_BUY_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_BUY_CTRC_AMT", 0);		//선물매수약정금액
CString strOPT_BUY_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_BUY_CTRC_AMT", 0);		//옵션매수약정금액
CString strFTR_BUY_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_BUY_TR_QNT", 0);		//선물매수거래수량
CString strOPT_BUY_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_BUY_TR_QNT", 0);		//옵션매수거래수량
CString strNOW_TOT_WMY_RT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "NOW_TOT_WMY_RT", 0);		//현재총증거금율
CString strCSH_WMY_RT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "CSH_WMY_RT", 0);		//현금증거금율
CString strMNTN_WMY = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "MNTN_WMY", 0);		//유지증거금
