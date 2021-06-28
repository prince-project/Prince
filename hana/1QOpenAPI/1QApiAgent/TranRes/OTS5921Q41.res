BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5921Q41, TR_NAME=주문현황해외ON전체, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5921Q41_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5921Q41_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=종합계좌번호;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=2, ITEM=ODRV_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생주문번호;
			 INDEX=3, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=4, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생원주문번호;
			 INDEX=5, ITEM=ODRV_MO_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생모주문번호;
			 INDEX=6, ITEM=ORDR_GRUP_NO, TYPE=string, SIZE=16, CAPTION=주문그룹번호;
			 INDEX=7, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=주문일자;
			 INDEX=8, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=9, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=고객명;
			 INDEX=10, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=해외파생매도매수구분코드;
			 INDEX=11, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=해외파생주문가격;
			 INDEX=12, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=13, ITEM=RVSE_QNT, TYPE=string, SIZE=19, CAPTION=정정수량;
			 INDEX=14, ITEM=CNCL_QNT, TYPE=string, SIZE=19, CAPTION=취소수량;
			 INDEX=15, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=체결수량;
			 INDEX=16, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=주문잔여수량;
			 INDEX=17, ITEM=ODRV_PRC_DCD, TYPE=string, SIZE=1, CAPTION=해외파생가격구분코드;
			 INDEX=18, ITEM=CNCS_CND_DCD, TYPE=string, SIZE=1, CAPTION=체결조건구분코드;
			 INDEX=19, ITEM=STLS_APPN_PRC, TYPE=string, SIZE=24, CAPTION=스탑로스지정가격;
			 INDEX=20, ITEM=AVR_CNCS_PRC, TYPE=string, SIZE=24, CAPTION=평균체결가격;
			 INDEX=21, ITEM=CNCS_RT, TYPE=string, SIZE=17, CAPTION=체결율;
			 INDEX=22, ITEM=ODRV_NOW_PRC, TYPE=string, SIZE=24, CAPTION=해외파생현재가격;
			 INDEX=23, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=통신매체구분코드;
			 INDEX=24, ITEM=ODRV_ORDR_TP_DCD, TYPE=string, SIZE=1, CAPTION=해외파생주문유형구분코드;
			 INDEX=25, ITEM=ORDR_STTS_DCD, TYPE=string, SIZE=1, CAPTION=주문상태구분코드;
			 INDEX=26, ITEM=FCM_ODNO, TYPE=string, SIZE=60, CAPTION=FCM주문번호;
			 INDEX=27, ITEM=HND_EMPNO, TYPE=string, SIZE=7, CAPTION=조작사원번호;
			 INDEX=28, ITEM=ATHZ_IP_ADDR, TYPE=string, SIZE=39, CAPTION=공인IP주소;
			 INDEX=29, ITEM=EXCG_ACPT_TM, TYPE=string, SIZE=6, CAPTION=거래소접수시각;
			 INDEX=30, ITEM=EXCG_CNCS_TM, TYPE=string, SIZE=6, CAPTION=거래소체결시각;
			 INDEX=31, ITEM=ORDR_TM, TYPE=string, SIZE=6, CAPTION=주문시각;
			 INDEX=32, ITEM=CNCS_TM, TYPE=string, SIZE=6, CAPTION=체결시각;
			 INDEX=33, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=통화코드;
			 INDEX=34, ITEM=PRC_DCPN_BLW_LNG, TYPE=string, SIZE=6, CAPTION=가격소수점이하길이;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5921Q41", "OTS5921Q41_in_sub01", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5921Q41", "OTS5921Q41_in_sub01", "APNO", strAPNO);		//계좌상품번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCANO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CANO", nRow);		//종합계좌번호
CString strCTNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CTNO", nRow);		//종합계좌대체번호
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_ODNO", nRow);		//해외파생주문번호
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "PRDT_CD", nRow);		//상품코드
CString strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_OR_ODNO", nRow);		//해외파생원주문번호
CString strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_MO_ODNO", nRow);		//해외파생모주문번호
CString strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ORDR_GRUP_NO", nRow);		//주문그룹번호
CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ORDR_DT", nRow);		//주문일자
CString strAPNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "APNO", nRow);		//계좌상품번호
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CUST_NM", nRow);		//고객명
CString strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//해외파생매도매수구분코드
CString strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_ORDR_PRC", nRow);		//해외파생주문가격
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ORDR_QNT", nRow);		//주문수량
CString strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "RVSE_QNT", nRow);		//정정수량
CString strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CNCL_QNT", nRow);		//취소수량
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CNCS_QNT", nRow);		//체결수량
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ORDR_RMN_QNT", nRow);		//주문잔여수량
CString strODRV_PRC_DCD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_PRC_DCD", nRow);		//해외파생가격구분코드
CString strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CNCS_CND_DCD", nRow);		//체결조건구분코드
CString strSTLS_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "STLS_APPN_PRC", nRow);		//스탑로스지정가격
CString strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "AVR_CNCS_PRC", nRow);		//평균체결가격
CString strCNCS_RT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CNCS_RT", nRow);		//체결율
CString strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_NOW_PRC", nRow);		//해외파생현재가격
CString strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "COMM_MDIA_DCD", nRow);		//통신매체구분코드
CString strODRV_ORDR_TP_DCD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_ORDR_TP_DCD", nRow);		//해외파생주문유형구분코드
CString strORDR_STTS_DCD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ORDR_STTS_DCD", nRow);		//주문상태구분코드
CString strFCM_ODNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "FCM_ODNO", nRow);		//FCM주문번호
CString strHND_EMPNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "HND_EMPNO", nRow);		//조작사원번호
CString strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ATHZ_IP_ADDR", nRow);		//공인IP주소
CString strEXCG_ACPT_TM = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "EXCG_ACPT_TM", nRow);		//거래소접수시각
CString strEXCG_CNCS_TM = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "EXCG_CNCS_TM", nRow);		//거래소체결시각
CString strORDR_TM = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ORDR_TM", nRow);		//주문시각
CString strCNCS_TM = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CNCS_TM", nRow);		//체결시각
CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CRRY_CD", nRow);		//통화코드
CString strPRC_DCPN_BLW_LNG = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "PRC_DCPN_BLW_LNG", nRow);		//가격소수점이하길이
