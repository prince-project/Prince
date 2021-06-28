BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7701Q01, TR_NAME=API용CFD주문가능수량조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS7701Q01_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
			 INDEX=3, ITEM=CFD_NMPR_TP_DCD, TYPE=string, SIZE=1, CAPTION=CFD호가유형구분코드;
			 INDEX=4, ITEM=CFD_ORDR_UNPR, TYPE=string, SIZE=20, CAPTION=CFD주문단가;
			 INDEX=5, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS7701Q01_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_ORDR_PSBL_AMT, TYPE=string, SIZE=23, CAPTION=CFD주문가능금액;
			 INDEX=1, ITEM=CFD_BUY_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFD매수주문가능수량;
			 INDEX=2, ITEM=CFD_SELL_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFD매도주문가능수량;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strCFD_PRDT_CD;		//CFD상품코드
CString strCFD_NMPR_TP_DCD;		//CFD호가유형구분코드
CString strCFD_ORDR_UNPR;		//CFD주문단가
CString strPWD;		//비밀번호

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q01", "OTS7701Q01_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q01", "OTS7701Q01_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q01", "OTS7701Q01_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q01", "OTS7701Q01_in", "CFD_NMPR_TP_DCD", strCFD_NMPR_TP_DCD);		//CFD호가유형구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q01", "OTS7701Q01_in", "CFD_ORDR_UNPR", strCFD_ORDR_UNPR);		//CFD주문단가
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q01", "OTS7701Q01_in", "PWD", strPWD);		//비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strCFD_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS7701Q01", "OTS7701Q01_out", "CFD_ORDR_PSBL_AMT", 0);		//CFD주문가능금액
CString strCFD_BUY_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7701Q01", "OTS7701Q01_out", "CFD_BUY_ORDR_PSBL_QNT", 0);		//CFD매수주문가능수량
CString strCFD_SELL_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7701Q01", "OTS7701Q01_out", "CFD_SELL_ORDR_PSBL_QNT", 0);		//CFD매도주문가능수량
