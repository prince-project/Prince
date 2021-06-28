BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5914Q51, TR_NAME=FX마진예탁금조회모의투자, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5914Q51_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=INQ_DT, TYPE=string, SIZE=8, CAPTION=조회일자;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=3, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=계좌비밀번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5914Q51_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=통화코드;
			 INDEX=1, ITEM=BFDT_CSH_BLCE_CTNS, TYPE=string, SIZE=30, CAPTION=전일현금잔액내용;
			 INDEX=2, ITEM=ODRV_IPP_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생입출금액내용;
			 INDEX=3, ITEM=FX_FEE_CTNS, TYPE=string, SIZE=30, CAPTION=FX수수료내용;
			 INDEX=4, ITEM=ROVR_INTR_CTNS, TYPE=string, SIZE=30, CAPTION=롤오버이자내용;
			 INDEX=5, ITEM=THDT_DPSA_CTNS, TYPE=string, SIZE=30, CAPTION=당일예탁금내용;
			 INDEX=6, ITEM=ODRV_CLR_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생청산금액내용;
			 INDEX=7, ITEM=USTL_EVL_PFLS_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=미결제평가손익금액내용;
			 INDEX=8, ITEM=ODRV_EVL_DPST_TOT_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생평가예탁총금액내용;
			 INDEX=9, ITEM=ODRV_CSGN_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생위탁증거금내용;
			 INDEX=10, ITEM=ODRV_ADIT_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생추가증거금내용;
			 INDEX=11, ITEM=ODRV_RCVB_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생미수금액내용;
			 INDEX=12, ITEM=ODRV_ORDR_PSBL_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생주문가능금액내용;
			 INDEX=13, ITEM=ODRV_WDRW_PSBL_AMT_CTNS, TYPE=string, SIZE=20, CAPTION=해외파생인출가능금액내용;
			 INDEX=14, ITEM=ODRV_MNTN_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=해외파생유지증거금내용;
			 INDEX=15, ITEM=RSK_RT_CTNS, TYPE=string, SIZE=30, CAPTION=위험율내용;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strINQ_DT;		//조회일자
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strACNT_PWD;		//계좌비밀번호

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5914Q51", "OTS5914Q51_in", "INQ_DT", strINQ_DT);		//조회일자
m_CommAgent.SetTranInputData(nRequestId, "OTS5914Q51", "OTS5914Q51_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5914Q51", "OTS5914Q51_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5914Q51", "OTS5914Q51_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "CRRY_CD", nRow);		//통화코드
CString strBFDT_CSH_BLCE_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "BFDT_CSH_BLCE_CTNS", nRow);		//전일현금잔액내용
CString strODRV_IPP_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_IPP_AMT_CTNS", nRow);		//해외파생입출금액내용
CString strFX_FEE_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "FX_FEE_CTNS", nRow);		//FX수수료내용
CString strROVR_INTR_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ROVR_INTR_CTNS", nRow);		//롤오버이자내용
CString strTHDT_DPSA_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "THDT_DPSA_CTNS", nRow);		//당일예탁금내용
CString strODRV_CLR_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_CLR_AMT_CTNS", nRow);		//해외파생청산금액내용
CString strUSTL_EVL_PFLS_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "USTL_EVL_PFLS_AMT_CTNS", nRow);		//미결제평가손익금액내용
CString strODRV_EVL_DPST_TOT_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_EVL_DPST_TOT_AMT_CTNS", nRow);		//해외파생평가예탁총금액내용
CString strODRV_CSGN_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_CSGN_WMY_CTNS", nRow);		//해외파생위탁증거금내용
CString strODRV_ADIT_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_ADIT_WMY_CTNS", nRow);		//해외파생추가증거금내용
CString strODRV_RCVB_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_RCVB_AMT_CTNS", nRow);		//해외파생미수금액내용
CString strODRV_ORDR_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_ORDR_PSBL_AMT_CTNS", nRow);		//해외파생주문가능금액내용
CString strODRV_WDRW_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_WDRW_PSBL_AMT_CTNS", nRow);		//해외파생인출가능금액내용
CString strODRV_MNTN_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_MNTN_WMY_CTNS", nRow);		//해외파생유지증거금내용
CString strRSK_RT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "RSK_RT_CTNS", nRow);		//위험율내용
