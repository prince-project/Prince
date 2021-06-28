BEGIN_TRAN_LAYOUT

	TR_CODE=OAM2501U03, TR_NAME=비밀번호확인퇴직연금용, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OAM2501U03_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=INQ_DVSN, TYPE=string, SIZE=1, CAPTION=조회구분;
			 INDEX=1, ITEM=CUST_RNM_CNFM_NO, TYPE=string, SIZE=32, CAPTION=고객실명확인번호;
			 INDEX=2, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=3, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OAM2501U03_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=PRCS_PSBL_YN, TYPE=string, SIZE=1, CAPTION=처리가능여부;
			 INDEX=1, ITEM=CUST_RNM_CNFM_NO, TYPE=string, SIZE=32, CAPTION=고객실명확인번호;
			 INDEX=2, ITEM=HDS_CUST_DVSN, TYPE=string, SIZE=1, CAPTION=하나대투증권고객구분;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strINQ_DVSN;		//조회구분
CString strCUST_RNM_CNFM_NO;		//고객실명확인번호
CString strCTNO;		//종합계좌대체번호
CString strPWD;		//비밀번호

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OAM2501U03", "OAM2501U03_in", "INQ_DVSN", strINQ_DVSN);		//조회구분
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U03", "OAM2501U03_in", "CUST_RNM_CNFM_NO", strCUST_RNM_CNFM_NO);		//고객실명확인번호
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U03", "OAM2501U03_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U03", "OAM2501U03_in", "PWD", strPWD);		//비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strPRCS_PSBL_YN = m_CommAgent.GetTranOutputData("OAM2501U03", "OAM2501U03_out", "PRCS_PSBL_YN", 0);		//처리가능여부
CString strCUST_RNM_CNFM_NO = m_CommAgent.GetTranOutputData("OAM2501U03", "OAM2501U03_out", "CUST_RNM_CNFM_NO", 0);		//고객실명확인번호
CString strHDS_CUST_DVSN = m_CommAgent.GetTranOutputData("OAM2501U03", "OAM2501U03_out", "HDS_CUST_DVSN", 0);		//하나대투증권고객구분
