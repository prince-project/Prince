BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5911Q52, TR_NAME=체결스크린해외ON체결내역조회시, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5911Q52_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=종합계좌번호;
			 INDEX=1, ITEM=ODRV_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생주문번호;
			 INDEX=2, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=3, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생원주문번호;
			 INDEX=4, ITEM=ODRV_MO_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생모주문번호;
			 INDEX=5, ITEM=ORDR_GRUP_NO, TYPE=string, SIZE=16, CAPTION=주문그룹번호;
			 INDEX=6, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=주문일자;
			 INDEX=7, ITEM=ACNT_PRDT_CD, TYPE=string, SIZE=2, CAPTION=계좌상품코드;
			 INDEX=8, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=고객명;
			 INDEX=9, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=매도매수구분코드;
			 INDEX=10, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=해외파생주문가격;
			 INDEX=11, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=12, ITEM=RVSE_QNT, TYPE=string, SIZE=19, CAPTION=정정수량;
			 INDEX=13, ITEM=CNCL_QNT, TYPE=string, SIZE=19, CAPTION=취소수량;
			 INDEX=14, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=체결수량;
			 INDEX=15, ITEM=RMN_QNT, TYPE=string, SIZE=19, CAPTION=잔여수량;
			 INDEX=16, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=가격조건구분코드;
			 INDEX=17, ITEM=CNCS_CND_DCD, TYPE=string, SIZE=1, CAPTION=체결조건구분코드;
			 INDEX=18, ITEM=SQ1_APPN_PRC, TYPE=string, SIZE=24, CAPTION=1차지정가격;
			 INDEX=19, ITEM=AVR_CNCS_PRC, TYPE=string, SIZE=24, CAPTION=평균체결가격;
			 INDEX=20, ITEM=CNCS_RT, TYPE=string, SIZE=17, CAPTION=체결율;
			 INDEX=21, ITEM=NOW_PRC, TYPE=string, SIZE=22, CAPTION=현재가격;
			 INDEX=22, ITEM=MDIA_DCD, TYPE=string, SIZE=2, CAPTION=매체구분코드;
			 INDEX=23, ITEM=ORDR_DCD, TYPE=string, SIZE=1, CAPTION=주문구분코드;
			 INDEX=24, ITEM=ORDR_STTS_DCD, TYPE=string, SIZE=1, CAPTION=주문상태구분코드;
			 INDEX=25, ITEM=FCM_ODNO, TYPE=string, SIZE=60, CAPTION=FCM주문번호;
			 INDEX=26, ITEM=USER_ID, TYPE=string, SIZE=7, CAPTION=사용자ID;
			 INDEX=27, ITEM=ATHZ_IP_ADDR, TYPE=string, SIZE=39, CAPTION=공인IP주소;
			 INDEX=28, ITEM=ACPT_TM, TYPE=string, SIZE=6, CAPTION=접수시각;
			 INDEX=29, ITEM=CNCS_TM, TYPE=string, SIZE=6, CAPTION=체결시각;
			 INDEX=30, ITEM=ACPL_ACPT_TM, TYPE=string, SIZE=6, CAPTION=현지접수시각;
			 INDEX=31, ITEM=CNCS_DETL_DTM, TYPE=string, SIZE=17, CAPTION=체결상세일시;
			 INDEX=32, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=통화코드;
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

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5911Q52", "OTS5911Q52_in_sub01", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5911Q52", "OTS5911Q52_in_sub01", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5911Q52", "OTS5911Q52_in_sub01", "PWD", strPWD);		//비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCANO = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CANO", nRow);		//종합계좌번호
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ODRV_ODNO", nRow);		//해외파생주문번호
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "PRDT_CD", nRow);		//상품코드
CString strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ODRV_OR_ODNO", nRow);		//해외파생원주문번호
CString strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ODRV_MO_ODNO", nRow);		//해외파생모주문번호
CString strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ORDR_GRUP_NO", nRow);		//주문그룹번호
CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ORDR_DT", nRow);		//주문일자
CString strACNT_PRDT_CD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ACNT_PRDT_CD", nRow);		//계좌상품코드
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CUST_NM", nRow);		//고객명
CString strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "SELL_BUY_DCD", nRow);		//매도매수구분코드
CString strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ODRV_ORDR_PRC", nRow);		//해외파생주문가격
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ORDR_QNT", nRow);		//주문수량
CString strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "RVSE_QNT", nRow);		//정정수량
CString strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CNCL_QNT", nRow);		//취소수량
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CNCS_QNT", nRow);		//체결수량
CString strRMN_QNT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "RMN_QNT", nRow);		//잔여수량
CString strPRC_CND_DCD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "PRC_CND_DCD", nRow);		//가격조건구분코드
CString strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CNCS_CND_DCD", nRow);		//체결조건구분코드
CString strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "SQ1_APPN_PRC", nRow);		//1차지정가격
CString strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "AVR_CNCS_PRC", nRow);		//평균체결가격
CString strCNCS_RT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CNCS_RT", nRow);		//체결율
CString strNOW_PRC = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "NOW_PRC", nRow);		//현재가격
CString strMDIA_DCD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "MDIA_DCD", nRow);		//매체구분코드
CString strORDR_DCD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ORDR_DCD", nRow);		//주문구분코드
CString strORDR_STTS_DCD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ORDR_STTS_DCD", nRow);		//주문상태구분코드
CString strFCM_ODNO = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "FCM_ODNO", nRow);		//FCM주문번호
CString strUSER_ID = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "USER_ID", nRow);		//사용자ID
CString strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ATHZ_IP_ADDR", nRow);		//공인IP주소
CString strACPT_TM = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ACPT_TM", nRow);		//접수시각
CString strCNCS_TM = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CNCS_TM", nRow);		//체결시각
CString strACPL_ACPT_TM = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ACPL_ACPT_TM", nRow);		//현지접수시각
CString strCNCS_DETL_DTM = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CNCS_DETL_DTM", nRow);		//체결상세일시
CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CRRY_CD", nRow);		//통화코드
