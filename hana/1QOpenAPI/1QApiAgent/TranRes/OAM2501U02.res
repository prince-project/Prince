BEGIN_TRAN_LAYOUT

	TR_CODE=OAM2501U02, TR_NAME=비밀번호확인C, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OAM2501U02_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=3, ITEM=PWD_GNRL_PRCS_DVSN1, TYPE=string, SIZE=1, CAPTION=비밀번호일반처리구분1;
			 INDEX=4, ITEM=PWD_GNRL_PRCS_DVSN2, TYPE=string, SIZE=1, CAPTION=비밀번호일반처리구분2;
			 INDEX=5, ITEM=PWD_GNRL_PRCS_DVSN3, TYPE=string, SIZE=1, CAPTION=비밀번호일반처리구분3;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OAM2501U02_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=PRCS_PSBL_YN, TYPE=string, SIZE=1, CAPTION=처리가능여부;
			 INDEX=1, ITEM=ERR_ID, TYPE=string, SIZE=10, CAPTION=오류ID;
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
CString strPWD_GNRL_PRCS_DVSN1;		//비밀번호일반처리구분1
CString strPWD_GNRL_PRCS_DVSN2;		//비밀번호일반처리구분2
CString strPWD_GNRL_PRCS_DVSN3;		//비밀번호일반처리구분3

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OAM2501U02", "OAM2501U02_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U02", "OAM2501U02_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U02", "OAM2501U02_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U02", "OAM2501U02_in", "PWD_GNRL_PRCS_DVSN1", strPWD_GNRL_PRCS_DVSN1);		//비밀번호일반처리구분1
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U02", "OAM2501U02_in", "PWD_GNRL_PRCS_DVSN2", strPWD_GNRL_PRCS_DVSN2);		//비밀번호일반처리구분2
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U02", "OAM2501U02_in", "PWD_GNRL_PRCS_DVSN3", strPWD_GNRL_PRCS_DVSN3);		//비밀번호일반처리구분3




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strPRCS_PSBL_YN = m_CommAgent.GetTranOutputData("OAM2501U02", "OAM2501U02_out", "PRCS_PSBL_YN", 0);		//처리가능여부
CString strERR_ID = m_CommAgent.GetTranOutputData("OAM2501U02", "OAM2501U02_out", "ERR_ID", 0);		//오류ID
