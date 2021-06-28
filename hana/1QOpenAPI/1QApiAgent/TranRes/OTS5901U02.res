BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5901U02, TR_NAME=해외선물정정주문, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5901U02_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생원주문번호;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=3, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=4, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=5, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=가격조건구분코드;
			 INDEX=6, ITEM=ODRV_RVSE_PRC, TYPE=string, SIZE=24, CAPTION=해외파생정정가격;
			 INDEX=7, ITEM=RVSE_QNT, TYPE=string, SIZE=19, CAPTION=정정수량;
			 INDEX=8, ITEM=STLS_APPN_PRC, TYPE=string, SIZE=24, CAPTION=스탑로스지정가격;
			 INDEX=9, ITEM=RMN_QNT_YN, TYPE=string, SIZE=1, CAPTION=잔여수량여부;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5901U02_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=ODRV_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생주문번호;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strODRV_OR_ODNO;		//해외파생원주문번호
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strPWD;		//비밀번호
CString strPRDT_CD;		//상품코드
CString strPRC_CND_DCD;		//가격조건구분코드
CString strODRV_RVSE_PRC;		//해외파생정정가격
CString strRVSE_QNT;		//정정수량
CString strSTLS_APPN_PRC;		//스탑로스지정가격
CString strRMN_QNT_YN;		//잔여수량여부

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//해외파생원주문번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "PRDT_CD", strPRDT_CD);		//상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "PRC_CND_DCD", strPRC_CND_DCD);		//가격조건구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "ODRV_RVSE_PRC", strODRV_RVSE_PRC);		//해외파생정정가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "RVSE_QNT", strRVSE_QNT);		//정정수량
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "STLS_APPN_PRC", strSTLS_APPN_PRC);		//스탑로스지정가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "RMN_QNT_YN", strRMN_QNT_YN);		//잔여수량여부




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5901U02", "OTS5901U02_out", "ODRV_ODNO", 0);		//해외파생주문번호
