BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2850Q81, TR_NAME=예탁금조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS2850Q81_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=3, ITEM=INQ_DT, TYPE=string, SIZE=8, CAPTION=조회일자;
			 INDEX=4, ITEM=INQ_DVSN, TYPE=string, SIZE=1, CAPTION=조회구분;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS2850Q81_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=EVL_DPST_TOT_AMT, TYPE=string, SIZE=19, CAPTION=평가예탁총금액;
			 INDEX=1, ITEM=EVL_DPST_CSH, TYPE=string, SIZE=19, CAPTION=평가예탁현금;
			 INDEX=2, ITEM=DPST_TOT_AMT, TYPE=string, SIZE=19, CAPTION=예탁총금액;
			 INDEX=3, ITEM=DPST_CSH, TYPE=string, SIZE=19, CAPTION=예탁현금;
			 INDEX=4, ITEM=DPST_SBST, TYPE=string, SIZE=19, CAPTION=예탁대용;
			 INDEX=5, ITEM=WDRW_PSBL_TOT_AMT, TYPE=string, SIZE=19, CAPTION=인출가능총금액;
			 INDEX=6, ITEM=WDRW_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=인출가능현금;
			 INDEX=7, ITEM=WDRW_PSBL_SBST_AMT, TYPE=string, SIZE=19, CAPTION=인출가능대용금액;
			 INDEX=8, ITEM=ORDR_PSBL_TOT_AMT, TYPE=string, SIZE=19, CAPTION=주문가능총금액;
			 INDEX=9, ITEM=ORDR_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=주문가능현금;
			 INDEX=10, ITEM=CSGN_WMY_TOT_AMT, TYPE=string, SIZE=19, CAPTION=위탁증거금총금액;
			 INDEX=11, ITEM=CSGN_WMY_CSH, TYPE=string, SIZE=19, CAPTION=위탁증거금현금;
			 INDEX=12, ITEM=MNMG_TOT_AMT, TYPE=string, SIZE=19, CAPTION=유지증거금총금액;
			 INDEX=13, ITEM=MNMG_CSH, TYPE=string, SIZE=19, CAPTION=유지증거금현금;
			 INDEX=14, ITEM=ADIT_WMY_TOT_AMT, TYPE=string, SIZE=19, CAPTION=추가증거금총금액;
			 INDEX=15, ITEM=ADIT_WMY_CSH, TYPE=string, SIZE=19, CAPTION=추가증거금현금;
			 INDEX=16, ITEM=EVL_AMT, TYPE=string, SIZE=19, CAPTION=평가금액;
			 INDEX=17, ITEM=EVL_PFLS, TYPE=string, SIZE=19, CAPTION=평가손익;
			 INDEX=18, ITEM=FEE, TYPE=string, SIZE=19, CAPTION=수수료;
			 INDEX=19, ITEM=RCVA, TYPE=string, SIZE=19, CAPTION=미수금;
			 INDEX=20, ITEM=THDT_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=당일손익금액;
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
CString strINQ_DVSN;		//조회구분

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q81", "OTS2850Q81_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q81", "OTS2850Q81_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q81", "OTS2850Q81_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q81", "OTS2850Q81_in", "INQ_DT", strINQ_DT);		//조회일자
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q81", "OTS2850Q81_in", "INQ_DVSN", strINQ_DVSN);		//조회구분




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strEVL_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "EVL_DPST_TOT_AMT", 0);		//평가예탁총금액
CString strEVL_DPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "EVL_DPST_CSH", 0);		//평가예탁현금
CString strDPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "DPST_TOT_AMT", 0);		//예탁총금액
CString strDPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "DPST_CSH", 0);		//예탁현금
CString strDPST_SBST = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "DPST_SBST", 0);		//예탁대용
CString strWDRW_PSBL_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "WDRW_PSBL_TOT_AMT", 0);		//인출가능총금액
CString strWDRW_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "WDRW_PSBL_CSH", 0);		//인출가능현금
CString strWDRW_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "WDRW_PSBL_SBST_AMT", 0);		//인출가능대용금액
CString strORDR_PSBL_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "ORDR_PSBL_TOT_AMT", 0);		//주문가능총금액
CString strORDR_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "ORDR_PSBL_CSH", 0);		//주문가능현금
CString strCSGN_WMY_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "CSGN_WMY_TOT_AMT", 0);		//위탁증거금총금액
CString strCSGN_WMY_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "CSGN_WMY_CSH", 0);		//위탁증거금현금
CString strMNMG_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "MNMG_TOT_AMT", 0);		//유지증거금총금액
CString strMNMG_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "MNMG_CSH", 0);		//유지증거금현금
CString strADIT_WMY_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "ADIT_WMY_TOT_AMT", 0);		//추가증거금총금액
CString strADIT_WMY_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "ADIT_WMY_CSH", 0);		//추가증거금현금
CString strEVL_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "EVL_AMT", 0);		//평가금액
CString strEVL_PFLS = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "EVL_PFLS", 0);		//평가손익
CString strFEE = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "FEE", 0);		//수수료
CString strRCVA = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "RCVA", 0);		//미수금
CString strTHDT_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "THDT_PFLS_AMT", 0);		//당일손익금액
