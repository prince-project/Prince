BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5901U32, TR_NAME=FX마진정정주문, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5901U32_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생원주문번호;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=3, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=4, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=해외파생매도매수구분코드;
			 INDEX=5, ITEM=FDM_UNQ_NO, TYPE=string, SIZE=3, CAPTION=딜링하우스고유번호;
			 INDEX=6, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=7, ITEM=NMPR_UNQ_NO, TYPE=string, SIZE=11, CAPTION=호가고유번호;
			 INDEX=8, ITEM=CNCS_CND_DCD, TYPE=string, SIZE=1, CAPTION=체결조건구분코드;
			 INDEX=9, ITEM=ORDR_EXPR_DT, TYPE=string, SIZE=8, CAPTION=주문만료일자;
			 INDEX=10, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=가격조건구분코드;
			 INDEX=11, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=해외파생주문가격;
			 INDEX=12, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=13, ITEM=SQ1_STLS_YN, TYPE=string, SIZE=1, CAPTION=1차스탑로스여부;
			 INDEX=14, ITEM=SQ1_APMPR_YN, TYPE=string, SIZE=1, CAPTION=1차지정가여부;
			 INDEX=15, ITEM=SQ1_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1차스탑로스가격;
			 INDEX=16, ITEM=SQ1_APPN_PRC, TYPE=string, SIZE=24, CAPTION=1차지정가격;
			 INDEX=17, ITEM=SQ1_CHAS_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1차추적손절매가격;
			 INDEX=18, ITEM=SQ2_STLS_YN, TYPE=string, SIZE=1, CAPTION=2차스탑로스여부;
			 INDEX=19, ITEM=SQ2_STLS_PRC, TYPE=string, SIZE=24, CAPTION=2차스탑로스가격;
			 INDEX=20, ITEM=SQ2_APMPR_YN, TYPE=string, SIZE=1, CAPTION=2차지정가여부;
			 INDEX=21, ITEM=SQ2_APPN_PRC, TYPE=string, SIZE=24, CAPTION=2차지정가격;
			 INDEX=22, ITEM=SQ2_CHAS_STLS_PRC, TYPE=string, SIZE=24, CAPTION=2차추적손절매가격;
			 INDEX=23, ITEM=ORDR_DRCN_DCD, TYPE=string, SIZE=1, CAPTION=주문방향구분코드;
			 INDEX=24, ITEM=TRDE_PRC_DFRN_CTNS, TYPE=string, SIZE=50, CAPTION=매매가격차이내용;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5901U32_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strODRV_SELL_BUY_DCD;		//해외파생매도매수구분코드
CString strFDM_UNQ_NO;		//딜링하우스고유번호
CString strPRDT_CD;		//상품코드
CString strNMPR_UNQ_NO;		//호가고유번호
CString strCNCS_CND_DCD;		//체결조건구분코드
CString strORDR_EXPR_DT;		//주문만료일자
CString strPRC_CND_DCD;		//가격조건구분코드
CString strODRV_ORDR_PRC;		//해외파생주문가격
CString strORDR_QNT;		//주문수량
CString strSQ1_STLS_YN;		//1차스탑로스여부
CString strSQ1_APMPR_YN;		//1차지정가여부
CString strSQ1_STLS_PRC;		//1차스탑로스가격
CString strSQ1_APPN_PRC;		//1차지정가격
CString strSQ1_CHAS_STLS_PRC;		//1차추적손절매가격
CString strSQ2_STLS_YN;		//2차스탑로스여부
CString strSQ2_STLS_PRC;		//2차스탑로스가격
CString strSQ2_APMPR_YN;		//2차지정가여부
CString strSQ2_APPN_PRC;		//2차지정가격
CString strSQ2_CHAS_STLS_PRC;		//2차추적손절매가격
CString strORDR_DRCN_DCD;		//주문방향구분코드
CString strTRDE_PRC_DFRN_CTNS;		//매매가격차이내용

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//해외파생원주문번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//딜링하우스고유번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "PRDT_CD", strPRDT_CD);		//상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "NMPR_UNQ_NO", strNMPR_UNQ_NO);		//호가고유번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "CNCS_CND_DCD", strCNCS_CND_DCD);		//체결조건구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "ORDR_EXPR_DT", strORDR_EXPR_DT);		//주문만료일자
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "PRC_CND_DCD", strPRC_CND_DCD);		//가격조건구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "ODRV_ORDR_PRC", strODRV_ORDR_PRC);		//해외파생주문가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "ORDR_QNT", strORDR_QNT);		//주문수량
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "SQ1_STLS_YN", strSQ1_STLS_YN);		//1차스탑로스여부
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "SQ1_APMPR_YN", strSQ1_APMPR_YN);		//1차지정가여부
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "SQ1_STLS_PRC", strSQ1_STLS_PRC);		//1차스탑로스가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "SQ1_APPN_PRC", strSQ1_APPN_PRC);		//1차지정가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "SQ1_CHAS_STLS_PRC", strSQ1_CHAS_STLS_PRC);		//1차추적손절매가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "SQ2_STLS_YN", strSQ2_STLS_YN);		//2차스탑로스여부
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "SQ2_STLS_PRC", strSQ2_STLS_PRC);		//2차스탑로스가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "SQ2_APMPR_YN", strSQ2_APMPR_YN);		//2차지정가여부
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "SQ2_APPN_PRC", strSQ2_APPN_PRC);		//2차지정가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "SQ2_CHAS_STLS_PRC", strSQ2_CHAS_STLS_PRC);		//2차추적손절매가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//주문방향구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U32", "OTS5901U32_in", "TRDE_PRC_DFRN_CTNS", strTRDE_PRC_DFRN_CTNS);		//매매가격차이내용




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5901U32", "OTS5901U32_out", "ODRV_ODNO", 0);		//해외파생주문번호
