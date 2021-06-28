BEGIN_TRAN_LAYOUT

	TR_CODE=OTS4201Q21, TR_NAME=해외주식온라인주문외화잔고API, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS4201Q21_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS4201Q21_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=통화코드;
			 INDEX=1, ITEM=FRCR_BLN_AMT, TYPE=string, SIZE=26, CAPTION=외화잔고금액;
			 INDEX=2, ITEM=FRCR_PRSM_DACA, TYPE=string, SIZE=26, CAPTION=외화추정예수금;
			 INDEX=3, ITEM=OSTK_ORDR_PSBL_AMT, TYPE=string, SIZE=26, CAPTION=해외주식주문가능금액;
			 INDEX=4, ITEM=FRCR_DRWG_PSBL_AMT, TYPE=string, SIZE=26, CAPTION=외화출금가능금액;
			 INDEX=5, ITEM=OSTK_ORDR_WMY, TYPE=string, SIZE=24, CAPTION=해외주식주문증거금;
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

m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q21", "OTS4201Q21_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q21", "OTS4201Q21_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q21", "OTS4201Q21_in", "PWD", strPWD);		//비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS4201Q21", "OTS4201Q21_out_sub01", "CRRY_CD", nRow);		//통화코드
CString strFRCR_BLN_AMT = m_CommAgent.GetTranOutputData("OTS4201Q21", "OTS4201Q21_out_sub01", "FRCR_BLN_AMT", nRow);		//외화잔고금액
CString strFRCR_PRSM_DACA = m_CommAgent.GetTranOutputData("OTS4201Q21", "OTS4201Q21_out_sub01", "FRCR_PRSM_DACA", nRow);		//외화추정예수금
CString strOSTK_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS4201Q21", "OTS4201Q21_out_sub01", "OSTK_ORDR_PSBL_AMT", nRow);		//해외주식주문가능금액
CString strFRCR_DRWG_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS4201Q21", "OTS4201Q21_out_sub01", "FRCR_DRWG_PSBL_AMT", nRow);		//외화출금가능금액
CString strOSTK_ORDR_WMY = m_CommAgent.GetTranOutputData("OTS4201Q21", "OTS4201Q21_out_sub01", "OSTK_ORDR_WMY", nRow);		//해외주식주문증거금
