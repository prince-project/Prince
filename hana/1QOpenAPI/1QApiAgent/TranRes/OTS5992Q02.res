BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5992Q02, TR_NAME=시그널메이커조회고객API용, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5992Q02_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=USR_ID, TYPE=string, SIZE=20, CAPTION=사용자ID;
			 INDEX=1, ITEM=AFFL_SRVC_DCD, TYPE=string, SIZE=3, CAPTION=제휴서비스구분코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5992Q02_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=종합계좌번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=고객명;
			 INDEX=3, ITEM=AFFL_SRVC_DCD, TYPE=string, SIZE=3, CAPTION=제휴서비스구분코드;
			 INDEX=4, ITEM=SRVC_NM, TYPE=string, SIZE=80, CAPTION=서비스명;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strUSR_ID;		//사용자ID
CString strAFFL_SRVC_DCD;		//제휴서비스구분코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5992Q02", "OTS5992Q02_in", "USR_ID", strUSR_ID);		//사용자ID
m_CommAgent.SetTranInputData(nRequestId, "OTS5992Q02", "OTS5992Q02_in", "AFFL_SRVC_DCD", strAFFL_SRVC_DCD);		//제휴서비스구분코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCANO = m_CommAgent.GetTranOutputData("OTS5992Q02", "OTS5992Q02_out_sub01", "CANO", nRow);		//종합계좌번호
CString strAPNO = m_CommAgent.GetTranOutputData("OTS5992Q02", "OTS5992Q02_out_sub01", "APNO", nRow);		//계좌상품번호
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5992Q02", "OTS5992Q02_out_sub01", "CUST_NM", nRow);		//고객명
CString strAFFL_SRVC_DCD = m_CommAgent.GetTranOutputData("OTS5992Q02", "OTS5992Q02_out_sub01", "AFFL_SRVC_DCD", nRow);		//제휴서비스구분코드
CString strSRVC_NM = m_CommAgent.GetTranOutputData("OTS5992Q02", "OTS5992Q02_out_sub01", "SRVC_NM", nRow);		//서비스명
