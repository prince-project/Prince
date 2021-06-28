BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5991Q03, TR_NAME=모의투자고객계좌조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5991Q03_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=USR_ID, TYPE=string, SIZE=20, CAPTION=사용자ID;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5991Q03_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=종합계좌번호;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=3, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=고객명;
			 INDEX=4, ITEM=RMS_ACNT_YN, TYPE=string, SIZE=1, CAPTION=RMS계좌여부;
			 INDEX=5, ITEM=ACNT_STTS_DCD, TYPE=string, SIZE=1, CAPTION=계좌상태구분코드;
			 INDEX=6, ITEM=WRAP_OPER_ACNT_DCD, TYPE=string, SIZE=1, CAPTION=WRAP운영계좌구분코드;
			 INDEX=7, ITEM=USE_MDIA_DCD, TYPE=string, SIZE=1, CAPTION=사용매체구분코드;
			 INDEX=8, ITEM=ACNT_PRDT_CD, TYPE=string, SIZE=2, CAPTION=계좌상품코드;
			 INDEX=9, ITEM=GSPT_BSNM_YN, TYPE=string, SIZE=1, CAPTION=금현물사업자여부;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strUSR_ID;		//사용자ID

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5991Q03", "OTS5991Q03_in", "USR_ID", strUSR_ID);		//사용자ID




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCTNO = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "CTNO", nRow);		//종합계좌대체번호
CString strCANO = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "CANO", nRow);		//종합계좌번호
CString strAPNO = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "APNO", nRow);		//계좌상품번호
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "CUST_NM", nRow);		//고객명
CString strRMS_ACNT_YN = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "RMS_ACNT_YN", nRow);		//RMS계좌여부
CString strACNT_STTS_DCD = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "ACNT_STTS_DCD", nRow);		//계좌상태구분코드
CString strWRAP_OPER_ACNT_DCD = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "WRAP_OPER_ACNT_DCD", nRow);		//WRAP운영계좌구분코드
CString strUSE_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "USE_MDIA_DCD", nRow);		//사용매체구분코드
CString strACNT_PRDT_CD = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "ACNT_PRDT_CD", nRow);		//계좌상품코드
CString strGSPT_BSNM_YN = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "GSPT_BSNM_YN", nRow);		//금현물사업자여부
