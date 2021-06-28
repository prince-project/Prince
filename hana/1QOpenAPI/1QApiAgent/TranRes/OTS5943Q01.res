BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5943Q01, TR_NAME=해외온라인통화별계좌잔고조회1, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5943Q01_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=BSN_DT, TYPE=string, SIZE=8, CAPTION=영업일자;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=3, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5943Q01_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=통화코드;
			 INDEX=1, ITEM=ODRV_STDR_EXRT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생기준환율내용;
			 INDEX=2, ITEM=BFDT_CSH_BLCE_CTNS, TYPE=string, SIZE=30, CAPTION=전일현금잔액내용;
			 INDEX=3, ITEM=ODRV_CSH_RCTM_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생현금입금금액내용;
			 INDEX=4, ITEM=ODRV_CSH_DRWG_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생현금출금금액내용;
			 INDEX=5, ITEM=ODRV_CLR_PFLS_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생청산손익금액내용;
			 INDEX=6, ITEM=ODRV_OPT_SELL_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생옵션매도금액내용;
			 INDEX=7, ITEM=ODRV_OPT_BUY_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생옵션매수금액내용;
			 INDEX=8, ITEM=ODRV_FEE_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생수수료내용;
			 INDEX=9, ITEM=THDT_CSH_BLCE_CTNS, TYPE=string, SIZE=30, CAPTION=당일현금잔액내용;
			 INDEX=10, ITEM=ODRV_EVL_PFLS_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생평가손익금액내용;
			 INDEX=11, ITEM=EVL_DPST_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=평가예탁금액내용;
			 INDEX=12, ITEM=ODRV_OPT_EVL_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생옵션평가금액내용;
			 INDEX=13, ITEM=TOT_ACC_ASST_VALU_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=총계정자산가치금액내용;
			 INDEX=14, ITEM=OPNG_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=개시증거금내용;
			 INDEX=15, ITEM=ODRV_ORDR_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생주문증거금내용;
			 INDEX=16, ITEM=ODRV_MNTN_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생유지증거금내용;
			 INDEX=17, ITEM=WMY_LACK_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=증거금부족금액내용;
			 INDEX=18, ITEM=ODRV_WDRW_PSBL_AMT_CTNS, TYPE=string, SIZE=20, CAPTION=해외파생인출가능금액내용;
			 INDEX=19, ITEM=ECHM_PSBL_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=환전가능금액내용;
			 INDEX=20, ITEM=ODRV_ORDR_PSBL_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생주문가능금액내용;
			 INDEX=21, ITEM=ODRV_ADIT_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생추가증거금내용;
			 INDEX=22, ITEM=RCVB_OVDU_INTR_CTNS, TYPE=string, SIZE=30, CAPTION=미수연체이자내용;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strBSN_DT;		//영업일자
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strPWD;		//비밀번호

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5943Q01", "OTS5943Q01_in", "BSN_DT", strBSN_DT);		//영업일자
m_CommAgent.SetTranInputData(nRequestId, "OTS5943Q01", "OTS5943Q01_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5943Q01", "OTS5943Q01_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5943Q01", "OTS5943Q01_in", "PWD", strPWD);		//비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "CRRY_CD", nRow);		//통화코드
CString strODRV_STDR_EXRT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_STDR_EXRT_CTNS", nRow);		//해외파생기준환율내용
CString strBFDT_CSH_BLCE_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "BFDT_CSH_BLCE_CTNS", nRow);		//전일현금잔액내용
CString strODRV_CSH_RCTM_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_CSH_RCTM_AMT_CTNS", nRow);		//해외파생현금입금금액내용
CString strODRV_CSH_DRWG_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_CSH_DRWG_AMT_CTNS", nRow);		//해외파생현금출금금액내용
CString strODRV_CLR_PFLS_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_CLR_PFLS_AMT_CTNS", nRow);		//해외파생청산손익금액내용
CString strODRV_OPT_SELL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_OPT_SELL_AMT_CTNS", nRow);		//해외파생옵션매도금액내용
CString strODRV_OPT_BUY_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_OPT_BUY_AMT_CTNS", nRow);		//해외파생옵션매수금액내용
CString strODRV_FEE_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_FEE_CTNS", nRow);		//해외파생수수료내용
CString strTHDT_CSH_BLCE_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "THDT_CSH_BLCE_CTNS", nRow);		//당일현금잔액내용
CString strODRV_EVL_PFLS_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_EVL_PFLS_AMT_CTNS", nRow);		//해외파생평가손익금액내용
CString strEVL_DPST_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "EVL_DPST_AMT_CTNS", nRow);		//평가예탁금액내용
CString strODRV_OPT_EVL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_OPT_EVL_AMT_CTNS", nRow);		//해외파생옵션평가금액내용
CString strTOT_ACC_ASST_VALU_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "TOT_ACC_ASST_VALU_AMT_CTNS", nRow);		//총계정자산가치금액내용
CString strOPNG_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "OPNG_WMY_CTNS", nRow);		//개시증거금내용
CString strODRV_ORDR_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_ORDR_WMY_CTNS", nRow);		//해외파생주문증거금내용
CString strODRV_MNTN_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_MNTN_WMY_CTNS", nRow);		//해외파생유지증거금내용
CString strWMY_LACK_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "WMY_LACK_AMT_CTNS", nRow);		//증거금부족금액내용
CString strODRV_WDRW_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_WDRW_PSBL_AMT_CTNS", nRow);		//해외파생인출가능금액내용
CString strECHM_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ECHM_PSBL_AMT_CTNS", nRow);		//환전가능금액내용
CString strODRV_ORDR_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_ORDR_PSBL_AMT_CTNS", nRow);		//해외파생주문가능금액내용
CString strODRV_ADIT_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_ADIT_WMY_CTNS", nRow);		//해외파생추가증거금내용
CString strRCVB_OVDU_INTR_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "RCVB_OVDU_INTR_CTNS", nRow);		//미수연체이자내용
