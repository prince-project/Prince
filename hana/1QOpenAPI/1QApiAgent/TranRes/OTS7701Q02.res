BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7701Q02, TR_NAME=API용CFD청산가능수량조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS7701Q02_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
			 INDEX=3, ITEM=CFD_TRDE_DCD, TYPE=string, SIZE=1, CAPTION=CFD매매구분코드;
			 INDEX=4, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS7701Q02_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_CLR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFD청산가능수량;
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
CString strCFD_TRDE_DCD;		//CFD매매구분코드
CString strPWD;		//비밀번호

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q02", "OTS7701Q02_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q02", "OTS7701Q02_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q02", "OTS7701Q02_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q02", "OTS7701Q02_in", "CFD_TRDE_DCD", strCFD_TRDE_DCD);		//CFD매매구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q02", "OTS7701Q02_in", "PWD", strPWD);		//비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strCFD_CLR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7701Q02", "OTS7701Q02_out", "CFD_CLR_PSBL_QNT", 0);		//CFD청산가능수량
