BEGIN_TRAN_LAYOUT

	TR_CODE=OAM5760Q50, TR_NAME=파생시세신청여부조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OAM5760Q50_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=API_USE_YN, TYPE=string, SIZE=1, CAPTION=API사용여부;
			 INDEX=1, ITEM=USR_ID, TYPE=string, SIZE=20, CAPTION=사용자ID;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OAM5760Q50_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=EXCG_CD, TYPE=string, SIZE=10, CAPTION=거래소코드;
			 INDEX=1, ITEM=QTTN_INQ_RQS_YN, TYPE=string, SIZE=1, CAPTION=시세조회신청여부;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strAPI_USE_YN;		//API사용여부
CString strUSR_ID;		//사용자ID

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OAM5760Q50", "OAM5760Q50_in", "API_USE_YN", strAPI_USE_YN);		//API사용여부
m_CommAgent.SetTranInputData(nRequestId, "OAM5760Q50", "OAM5760Q50_in", "USR_ID", strUSR_ID);		//사용자ID




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strEXCG_CD = m_CommAgent.GetTranOutputData("OAM5760Q50", "OAM5760Q50_out_sub01", "EXCG_CD", nRow);		//거래소코드
CString strQTTN_INQ_RQS_YN = m_CommAgent.GetTranOutputData("OAM5760Q50", "OAM5760Q50_out_sub01", "QTTN_INQ_RQS_YN", nRow);		//시세조회신청여부
