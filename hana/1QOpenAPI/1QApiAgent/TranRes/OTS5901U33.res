BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5901U33, TR_NAME=FX마진취소주문, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5901U33_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생원주문번호;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=3, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=4, ITEM=FDM_UNQ_NO, TYPE=string, SIZE=3, CAPTION=딜링하우스고유번호;
			 INDEX=5, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=6, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=7, ITEM=ORDR_DRCN_DCD, TYPE=string, SIZE=1, CAPTION=주문방향구분코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5901U33_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strFDM_UNQ_NO;		//딜링하우스고유번호
CString strPRDT_CD;		//상품코드
CString strORDR_QNT;		//주문수량
CString strORDR_DRCN_DCD;		//주문방향구분코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//해외파생원주문번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//딜링하우스고유번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "PRDT_CD", strPRDT_CD);		//상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "ORDR_QNT", strORDR_QNT);		//주문수량
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//주문방향구분코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5901U33", "OTS5901U33_out", "ODRV_ODNO", 0);		//해외파생주문번호
