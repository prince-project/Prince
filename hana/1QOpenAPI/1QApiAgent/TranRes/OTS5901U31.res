BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5901U31, TR_NAME=FX마진일반주문, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5901U31_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=3, ITEM=FDM_UNQ_NO, TYPE=string, SIZE=3, CAPTION=딜링하우스고유번호;
			 INDEX=4, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=5, ITEM=NMPR_UNQ_NO, TYPE=string, SIZE=11, CAPTION=호가고유번호;
			 INDEX=6, ITEM=ENTR_CLR_DCD, TYPE=string, SIZE=1, CAPTION=진입청산구분코드;
			 INDEX=7, ITEM=PST_NO, TYPE=string, SIZE=16, CAPTION=포지션번호;
			 INDEX=8, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=해외파생매도매수구분코드;
			 INDEX=9, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=가격조건구분코드;
			 INDEX=10, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=해외파생주문가격;
			 INDEX=11, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=12, ITEM=SQ1_STLS_YN, TYPE=string, SIZE=1, CAPTION=1차스탑로스여부;
			 INDEX=13, ITEM=SQ1_APMPR_YN, TYPE=string, SIZE=1, CAPTION=1차지정가여부;
			 INDEX=14, ITEM=SQ1_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1차스탑로스가격;
			 INDEX=15, ITEM=SQ1_APPN_PRC, TYPE=string, SIZE=24, CAPTION=1차지정가격;
			 INDEX=16, ITEM=SQ1_CHAS_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1차추적손절매가격;
			 INDEX=17, ITEM=SQ2_STLS_YN, TYPE=string, SIZE=1, CAPTION=2차스탑로스여부;
			 INDEX=18, ITEM=SQ2_APMPR_YN, TYPE=string, SIZE=1, CAPTION=2차지정가여부;
			 INDEX=19, ITEM=SQ2_STLS_PRC, TYPE=string, SIZE=24, CAPTION=2차스탑로스가격;
			 INDEX=20, ITEM=SQ2_APPN_PRC, TYPE=string, SIZE=24, CAPTION=2차지정가격;
			 INDEX=21, ITEM=SQ2_CHAS_STLS_PRC, TYPE=string, SIZE=24, CAPTION=2차추적손절매가격;
			 INDEX=22, ITEM=ORDR_DRCN_DCD, TYPE=string, SIZE=1, CAPTION=주문방향구분코드;
			 INDEX=23, ITEM=ORDR_SRC_DCD, TYPE=string, SIZE=1, CAPTION=주문원천구분코드;
			 INDEX=24, ITEM=TRDE_PRC_DFRN_CTNS, TYPE=string, SIZE=50, CAPTION=매매가격차이내용;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5901U31_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strFDM_UNQ_NO;		//딜링하우스고유번호
CString strPRDT_CD;		//상품코드
CString strNMPR_UNQ_NO;		//호가고유번호
CString strENTR_CLR_DCD;		//진입청산구분코드
CString strPST_NO;		//포지션번호
CString strODRV_SELL_BUY_DCD;		//해외파생매도매수구분코드
CString strPRC_CND_DCD;		//가격조건구분코드
CString strODRV_ORDR_PRC;		//해외파생주문가격
CString strORDR_QNT;		//주문수량
CString strSQ1_STLS_YN;		//1차스탑로스여부
CString strSQ1_APMPR_YN;		//1차지정가여부
CString strSQ1_STLS_PRC;		//1차스탑로스가격
CString strSQ1_APPN_PRC;		//1차지정가격
CString strSQ1_CHAS_STLS_PRC;		//1차추적손절매가격
CString strSQ2_STLS_YN;		//2차스탑로스여부
CString strSQ2_APMPR_YN;		//2차지정가여부
CString strSQ2_STLS_PRC;		//2차스탑로스가격
CString strSQ2_APPN_PRC;		//2차지정가격
CString strSQ2_CHAS_STLS_PRC;		//2차추적손절매가격
CString strORDR_DRCN_DCD;		//주문방향구분코드
CString strORDR_SRC_DCD;		//주문원천구분코드
CString strTRDE_PRC_DFRN_CTNS;		//매매가격차이내용

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//딜링하우스고유번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "PRDT_CD", strPRDT_CD);		//상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "NMPR_UNQ_NO", strNMPR_UNQ_NO);		//호가고유번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "ENTR_CLR_DCD", strENTR_CLR_DCD);		//진입청산구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "PST_NO", strPST_NO);		//포지션번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "PRC_CND_DCD", strPRC_CND_DCD);		//가격조건구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "ODRV_ORDR_PRC", strODRV_ORDR_PRC);		//해외파생주문가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "ORDR_QNT", strORDR_QNT);		//주문수량
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ1_STLS_YN", strSQ1_STLS_YN);		//1차스탑로스여부
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ1_APMPR_YN", strSQ1_APMPR_YN);		//1차지정가여부
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ1_STLS_PRC", strSQ1_STLS_PRC);		//1차스탑로스가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ1_APPN_PRC", strSQ1_APPN_PRC);		//1차지정가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ1_CHAS_STLS_PRC", strSQ1_CHAS_STLS_PRC);		//1차추적손절매가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ2_STLS_YN", strSQ2_STLS_YN);		//2차스탑로스여부
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ2_APMPR_YN", strSQ2_APMPR_YN);		//2차지정가여부
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ2_STLS_PRC", strSQ2_STLS_PRC);		//2차스탑로스가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ2_APPN_PRC", strSQ2_APPN_PRC);		//2차지정가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ2_CHAS_STLS_PRC", strSQ2_CHAS_STLS_PRC);		//2차추적손절매가격
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//주문방향구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "ORDR_SRC_DCD", strORDR_SRC_DCD);		//주문원천구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "TRDE_PRC_DFRN_CTNS", strTRDE_PRC_DFRN_CTNS);		//매매가격차이내용




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5901U31", "OTS5901U31_out", "ODRV_ODNO", 0);		//해외파생주문번호
