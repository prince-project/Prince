BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5913Q53, TR_NAME=FX마진미체결내역조회모의투자, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5913Q53_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=INQ_STRT_DT, TYPE=string, SIZE=8, CAPTION=조회시작일자;
			 INDEX=1, ITEM=INQ_END_DT, TYPE=string, SIZE=8, CAPTION=조회종료일자;
			 INDEX=2, ITEM=SORT_MTH, TYPE=string, SIZE=1, CAPTION=정렬방법;
			 INDEX=3, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=4, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=5, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=6, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=계좌비밀번호;
			 INDEX=7, ITEM=INQ_DVSN, TYPE=string, SIZE=1, CAPTION=조회구분;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5913Q53_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=FDM_UNQ_NO_PRDT_CD, TYPE=string, SIZE=35, CAPTION=딜링하우스고유번호상품코드;
			 INDEX=1, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=종합계좌번호;
			 INDEX=2, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=3, ITEM=ODRV_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생주문번호;
			 INDEX=4, ITEM=FDM_UNQ_NO, TYPE=string, SIZE=3, CAPTION=딜링하우스고유번호;
			 INDEX=5, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=6, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생원주문번호;
			 INDEX=7, ITEM=ODRV_MO_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생모주문번호;
			 INDEX=8, ITEM=ORDR_GRUP_NO, TYPE=string, SIZE=16, CAPTION=주문그룹번호;
			 INDEX=9, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=주문일자;
			 INDEX=10, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=11, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=고객명;
			 INDEX=12, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=해외파생매도매수구분코드;
			 INDEX=13, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=해외파생주문가격;
			 INDEX=14, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=15, ITEM=RVSE_QNT, TYPE=string, SIZE=19, CAPTION=정정수량;
			 INDEX=16, ITEM=CNCL_QNT, TYPE=string, SIZE=19, CAPTION=취소수량;
			 INDEX=17, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=체결수량;
			 INDEX=18, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=주문잔여수량;
			 INDEX=19, ITEM=CTRT_UN_AMT, TYPE=string, SIZE=24, CAPTION=계약단위금액;
			 INDEX=20, ITEM=FX_ORDR_TOT_AMT, TYPE=string, SIZE=24, CAPTION=FX주문총금액;
			 INDEX=21, ITEM=FX_RMN_TOT_AMT, TYPE=string, SIZE=24, CAPTION=FX잔여총금액;
			 INDEX=22, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=가격조건구분코드;
			 INDEX=23, ITEM=CNCS_CND_DCD, TYPE=string, SIZE=1, CAPTION=체결조건구분코드;
			 INDEX=24, ITEM=SQ1_STLS_YN, TYPE=string, SIZE=1, CAPTION=1차스탑로스여부;
			 INDEX=25, ITEM=SQ1_APMPR_YN, TYPE=string, SIZE=1, CAPTION=1차지정가여부;
			 INDEX=26, ITEM=SQ1_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1차스탑로스가격;
			 INDEX=27, ITEM=SQ1_APPN_PRC, TYPE=string, SIZE=24, CAPTION=1차지정가격;
			 INDEX=28, ITEM=SQ1_CHAS_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1차추적손절매가격;
			 INDEX=29, ITEM=SQ2_STLS_YN, TYPE=string, SIZE=1, CAPTION=2차스탑로스여부;
			 INDEX=30, ITEM=SQ2_APMPR_YN, TYPE=string, SIZE=1, CAPTION=2차지정가여부;
			 INDEX=31, ITEM=SQ2_STLS_PRC, TYPE=string, SIZE=24, CAPTION=2차스탑로스가격;
			 INDEX=32, ITEM=SQ2_APPN_PRC, TYPE=string, SIZE=24, CAPTION=2차지정가격;
			 INDEX=33, ITEM=SQ2_CHAS_STLS_PRC, TYPE=string, SIZE=24, CAPTION=2차추적손절매가격;
			 INDEX=34, ITEM=AVR_CNCS_PRC, TYPE=string, SIZE=24, CAPTION=평균체결가격;
			 INDEX=35, ITEM=CNCS_RT, TYPE=string, SIZE=17, CAPTION=체결율;
			 INDEX=36, ITEM=ODRV_NOW_PRC, TYPE=string, SIZE=24, CAPTION=해외파생현재가격;
			 INDEX=37, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=통신매체구분코드;
			 INDEX=38, ITEM=ODRV_ORDR_TP_DCD, TYPE=string, SIZE=1, CAPTION=해외파생주문유형구분코드;
			 INDEX=39, ITEM=ORDR_STTS_DCD, TYPE=string, SIZE=1, CAPTION=주문상태구분코드;
			 INDEX=40, ITEM=FCM_ODNO, TYPE=string, SIZE=60, CAPTION=FCM주문번호;
			 INDEX=41, ITEM=USR_ID, TYPE=string, SIZE=20, CAPTION=사용자ID;
			 INDEX=42, ITEM=ATHZ_IP_ADDR, TYPE=string, SIZE=39, CAPTION=공인IP주소;
			 INDEX=43, ITEM=EXCG_ACPT_TM, TYPE=string, SIZE=6, CAPTION=거래소접수시각;
			 INDEX=44, ITEM=EXCG_CNCS_TM, TYPE=string, SIZE=6, CAPTION=거래소체결시각;
			 INDEX=45, ITEM=ORDR_TM, TYPE=string, SIZE=6, CAPTION=주문시각;
			 INDEX=46, ITEM=CNCS_TM, TYPE=string, SIZE=6, CAPTION=체결시각;
			 INDEX=47, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=통화코드;
			 INDEX=48, ITEM=PRC_DCPN_BLW_LNG, TYPE=string, SIZE=6, CAPTION=가격소수점이하길이;
			 INDEX=49, ITEM=TRDE_PRC_DFRN_CTNS, TYPE=string, SIZE=50, CAPTION=매매가격차이내용;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strINQ_STRT_DT;		//조회시작일자
CString strINQ_END_DT;		//조회종료일자
CString strSORT_MTH;		//정렬방법
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strPRDT_CD;		//상품코드
CString strACNT_PWD;		//계좌비밀번호
CString strINQ_DVSN;		//조회구분

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "INQ_STRT_DT", strINQ_STRT_DT);		//조회시작일자
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "INQ_END_DT", strINQ_END_DT);		//조회종료일자
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "SORT_MTH", strSORT_MTH);		//정렬방법
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "PRDT_CD", strPRDT_CD);		//상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "INQ_DVSN", strINQ_DVSN);		//조회구분




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strFDM_UNQ_NO_PRDT_CD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FDM_UNQ_NO_PRDT_CD", nRow);		//딜링하우스고유번호상품코드
CString strCANO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CANO", nRow);		//종합계좌번호
CString strCTNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CTNO", nRow);		//종합계좌대체번호
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_ODNO", nRow);		//해외파생주문번호
CString strFDM_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FDM_UNQ_NO", nRow);		//딜링하우스고유번호
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "PRDT_CD", nRow);		//상품코드
CString strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_OR_ODNO", nRow);		//해외파생원주문번호
CString strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_MO_ODNO", nRow);		//해외파생모주문번호
CString strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_GRUP_NO", nRow);		//주문그룹번호
CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_DT", nRow);		//주문일자
CString strAPNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "APNO", nRow);		//계좌상품번호
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CUST_NM", nRow);		//고객명
CString strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//해외파생매도매수구분코드
CString strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_ORDR_PRC", nRow);		//해외파생주문가격
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_QNT", nRow);		//주문수량
CString strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "RVSE_QNT", nRow);		//정정수량
CString strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCL_QNT", nRow);		//취소수량
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_QNT", nRow);		//체결수량
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_RMN_QNT", nRow);		//주문잔여수량
CString strCTRT_UN_AMT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CTRT_UN_AMT", nRow);		//계약단위금액
CString strFX_ORDR_TOT_AMT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FX_ORDR_TOT_AMT", nRow);		//FX주문총금액
CString strFX_RMN_TOT_AMT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FX_RMN_TOT_AMT", nRow);		//FX잔여총금액
CString strPRC_CND_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "PRC_CND_DCD", nRow);		//가격조건구분코드
CString strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_CND_DCD", nRow);		//체결조건구분코드
CString strSQ1_STLS_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_STLS_YN", nRow);		//1차스탑로스여부
CString strSQ1_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_APMPR_YN", nRow);		//1차지정가여부
CString strSQ1_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_STLS_PRC", nRow);		//1차스탑로스가격
CString strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_APPN_PRC", nRow);		//1차지정가격
CString strSQ1_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_CHAS_STLS_PRC", nRow);		//1차추적손절매가격
CString strSQ2_STLS_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_STLS_YN", nRow);		//2차스탑로스여부
CString strSQ2_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_APMPR_YN", nRow);		//2차지정가여부
CString strSQ2_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_STLS_PRC", nRow);		//2차스탑로스가격
CString strSQ2_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_APPN_PRC", nRow);		//2차지정가격
CString strSQ2_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_CHAS_STLS_PRC", nRow);		//2차추적손절매가격
CString strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "AVR_CNCS_PRC", nRow);		//평균체결가격
CString strCNCS_RT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_RT", nRow);		//체결율
CString strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_NOW_PRC", nRow);		//해외파생현재가격
CString strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "COMM_MDIA_DCD", nRow);		//통신매체구분코드
CString strODRV_ORDR_TP_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_ORDR_TP_DCD", nRow);		//해외파생주문유형구분코드
CString strORDR_STTS_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_STTS_DCD", nRow);		//주문상태구분코드
CString strFCM_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FCM_ODNO", nRow);		//FCM주문번호
CString strUSR_ID = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "USR_ID", nRow);		//사용자ID
CString strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ATHZ_IP_ADDR", nRow);		//공인IP주소
CString strEXCG_ACPT_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "EXCG_ACPT_TM", nRow);		//거래소접수시각
CString strEXCG_CNCS_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "EXCG_CNCS_TM", nRow);		//거래소체결시각
CString strORDR_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_TM", nRow);		//주문시각
CString strCNCS_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_TM", nRow);		//체결시각
CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CRRY_CD", nRow);		//통화코드
CString strPRC_DCPN_BLW_LNG = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "PRC_DCPN_BLW_LNG", nRow);		//가격소수점이하길이
CString strTRDE_PRC_DFRN_CTNS = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "TRDE_PRC_DFRN_CTNS", nRow);		//매매가격차이내용
