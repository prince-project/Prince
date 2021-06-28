BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7701Q06, TR_NAME=API용CFD종목컨트롤조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS7701Q06_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
			 INDEX=1, ITEM=CFD_TRDE_DCD, TYPE=string, SIZE=1, CAPTION=CFD매매구분코드;
			 INDEX=2, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=3, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS7701Q06_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_WMY_RT, TYPE=string, SIZE=20, CAPTION=CFD증거금율;
			 INDEX=1, ITEM=CFD_ROVR_INTR_RT, TYPE=string, SIZE=20, CAPTION=CFD롤오버이자율;
			 INDEX=2, ITEM=CFD_SSS_FEE_RT, TYPE=string, SIZE=20, CAPTION=CFD공매도수수료율;
			 INDEX=3, ITEM=CFD_SELL_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFD매도가능수량;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strCFD_PRDT_CD;		//CFD상품코드
CString strCFD_TRDE_DCD;		//CFD매매구분코드
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q06", "OTS7701Q06_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q06", "OTS7701Q06_in", "CFD_TRDE_DCD", strCFD_TRDE_DCD);		//CFD매매구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q06", "OTS7701Q06_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q06", "OTS7701Q06_in", "APNO", strAPNO);		//계좌상품번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strCFD_WMY_RT = m_CommAgent.GetTranOutputData("OTS7701Q06", "OTS7701Q06_out", "CFD_WMY_RT", 0);		//CFD증거금율
CString strCFD_ROVR_INTR_RT = m_CommAgent.GetTranOutputData("OTS7701Q06", "OTS7701Q06_out", "CFD_ROVR_INTR_RT", 0);		//CFD롤오버이자율
CString strCFD_SSS_FEE_RT = m_CommAgent.GetTranOutputData("OTS7701Q06", "OTS7701Q06_out", "CFD_SSS_FEE_RT", 0);		//CFD공매도수수료율
CString strCFD_SELL_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7701Q06", "OTS7701Q06_out", "CFD_SELL_PSBL_QNT", 0);		//CFD매도가능수량
