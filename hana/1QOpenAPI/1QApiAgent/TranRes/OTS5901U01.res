BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5901U01, TR_NAME=해외선물일반주문, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5901U01_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=3, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=4, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=매도매수구분코드;
			 INDEX=5, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=가격조건구분코드;
			 INDEX=6, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=해외파생주문가격;
			 INDEX=7, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=8, ITEM=STLS_APPN_PRC, TYPE=string, SIZE=24, CAPTION=스탑로스지정가격;
			 INDEX=9, ITEM=ORDR_HND_DCD, TYPE=string, SIZE=1, CAPTION=주문조작구분코드;
			 INDEX=10, ITEM=ORDR_DCD, TYPE=string, SIZE=1, CAPTION=주문구분코드;
			 INDEX=11, ITEM=ETC_ORDR_DCD, TYPE=string, SIZE=3, CAPTION=기타주문구분코드;
			 INDEX=12, ITEM=CNCS_CND_DCD, TYPE=string, SIZE=1, CAPTION=체결조건구분코드;
			 INDEX=13, ITEM=CLR_PST_NO, TYPE=string, SIZE=16, CAPTION=청산포지션번호;
			 INDEX=14, ITEM=ORDR_EXPR_DT, TYPE=string, SIZE=8, CAPTION=주문만료일자;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5901U01_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=ODRV_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생주문번호;
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
CString strPRDT_CD;		//상품코드
CString strSELL_BUY_DCD;		//매도매수구분코드
CString strPRC_CND_DCD;		//가격조건구분코드
CString strODRV_ORDR_PRC;		//해외파생주문가격
CString strORDR_QNT;		//주문수량
CString strSTLS_APPN_PRC;		//스탑로스지정가격
CString strORDR_HND_DCD;		//주문조작구분코드
CString strORDR_DCD;		//주문구분코드
CString strETC_ORDR_DCD;		//기타주문구분코드
CString strCNCS_CND_DCD;		//체결조건구분코드
CString strCLR_PST_NO;		//청산포지션번호
CString strORDR_EXPR_DT;		//주문만료일자

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "PRDT_CD", strPRDT_CD);		//상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//매도매수구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "PRC_CND_DCD", strPRC_CND_DCD);		//가격조건구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "ODRV_ORDR_PRC", strODRV_ORDR_PRC);		//해외파생주문가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "ORDR_QNT", strORDR_QNT);		//주문수량
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "STLS_APPN_PRC", strSTLS_APPN_PRC);		//스탑로스지정가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "ORDR_HND_DCD", strORDR_HND_DCD);		//주문조작구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "ORDR_DCD", strORDR_DCD);		//주문구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "ETC_ORDR_DCD", strETC_ORDR_DCD);		//기타주문구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "CNCS_CND_DCD", strCNCS_CND_DCD);		//체결조건구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "CLR_PST_NO", strCLR_PST_NO);		//청산포지션번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "ORDR_EXPR_DT", strORDR_EXPR_DT);		//주문만료일자




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5901U01", "OTS5901U01_out", "ODRV_ODNO", 0);		//해외파생주문번호
