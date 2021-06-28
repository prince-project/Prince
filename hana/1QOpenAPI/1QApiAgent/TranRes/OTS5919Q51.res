BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5919Q51, TR_NAME=미결제약정현황FX마진계좌그룹별, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5919Q51_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=해외파생매도매수구분코드;
		END_INPUT0_ITEM

		REC_NAME=OTS5919Q51_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		BEGIN_INPUT1_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT1_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5919Q51_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=PST_NO, TYPE=string, SIZE=16, CAPTION=포지션번호;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=2, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=종합계좌번호;
			 INDEX=3, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=4, ITEM=CNCS_DT, TYPE=string, SIZE=8, CAPTION=체결일자;
			 INDEX=5, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=관리부점코드;
			 INDEX=6, ITEM=ODRV_CSGN_SLF_DCD, TYPE=string, SIZE=1, CAPTION=해외파생위탁자기구분코드;
			 INDEX=7, ITEM=FDM_UNQ_NO, TYPE=string, SIZE=3, CAPTION=딜링하우스고유번호;
			 INDEX=8, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=9, ITEM=NMPR_UNQ_NO, TYPE=string, SIZE=11, CAPTION=호가고유번호;
			 INDEX=10, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=해외파생매도매수구분코드;
			 INDEX=11, ITEM=ODRV_CNCS_PRC, TYPE=string, SIZE=24, CAPTION=해외파생체결가격;
			 INDEX=12, ITEM=FRS_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=최초체결수량;
			 INDEX=13, ITEM=CLR_QNT, TYPE=string, SIZE=19, CAPTION=청산수량;
			 INDEX=14, ITEM=CNCS_CNCL_TR_QNT, TYPE=string, SIZE=19, CAPTION=체결취소거래수량;
			 INDEX=15, ITEM=USTL_CTRC_QNT, TYPE=string, SIZE=19, CAPTION=미결제약정수량;
			 INDEX=16, ITEM=USTL_CTRC_AMT2, TYPE=string, SIZE=24, CAPTION=미결제약정금액2;
			 INDEX=17, ITEM=USTL_CTRC_AMT3, TYPE=string, SIZE=24, CAPTION=미결제약정금액3;
			 INDEX=18, ITEM=CNCS_PIP_VALU_AMT, TYPE=string, SIZE=24, CAPTION=체결PIP가치금액;
			 INDEX=19, ITEM=ODRV_CTRC_AMT, TYPE=string, SIZE=24, CAPTION=해외파생약정금액;
			 INDEX=20, ITEM=USTL_CTRC_AMT, TYPE=string, SIZE=24, CAPTION=미결제약정금액;
			 INDEX=21, ITEM=CRSS_EXRT, TYPE=string, SIZE=23, CAPTION=교차환율;
			 INDEX=22, ITEM=ODRV_EXCAL_PRC, TYPE=string, SIZE=24, CAPTION=해외파생정산가격;
			 INDEX=23, ITEM=ODRV_EVL_PFLS_AMT, TYPE=string, SIZE=24, CAPTION=해외파생평가손익금액;
			 INDEX=24, ITEM=PIP_VALU_AMT, TYPE=string, SIZE=24, CAPTION=PIP가치금액;
			 INDEX=25, ITEM=TRSL_EVL_PFLS_AMT, TYPE=string, SIZE=24, CAPTION=환산평가손익금액;
			 INDEX=26, ITEM=EXCAL_CRSS_EXRT, TYPE=string, SIZE=23, CAPTION=정산교차환율;
			 INDEX=27, ITEM=ONL_TR_YN, TYPE=string, SIZE=1, CAPTION=온라인거래여부;
			 INDEX=28, ITEM=ODRV_CNCS_NO, TYPE=string, SIZE=8, CAPTION=해외파생체결번호;
			 INDEX=29, ITEM=HOLD_PST_YN, TYPE=string, SIZE=1, CAPTION=보유포지션여부;
			 INDEX=30, ITEM=USE_YN, TYPE=string, SIZE=1, CAPTION=사용여부;
			 INDEX=31, ITEM=ODRV_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생주문번호;
			 INDEX=32, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생원주문번호;
			 INDEX=33, ITEM=ODRV_MO_ODNO, TYPE=string, SIZE=16, CAPTION=해외파생모주문번호;
			 INDEX=34, ITEM=ORDR_GRUP_NO, TYPE=string, SIZE=16, CAPTION=주문그룹번호;
			 INDEX=35, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=주문일자;
			 INDEX=36, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=고객명;
			 INDEX=37, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=해외파생주문가격;
			 INDEX=38, ITEM=MKT_PRC_APLY_STUP_AMT, TYPE=string, SIZE=26, CAPTION=시장가격적용설정금액;
			 INDEX=39, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=40, ITEM=RVSE_QNT, TYPE=string, SIZE=19, CAPTION=정정수량;
			 INDEX=41, ITEM=CNCL_QNT, TYPE=string, SIZE=19, CAPTION=취소수량;
			 INDEX=42, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=체결수량;
			 INDEX=43, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=주문잔여수량;
			 INDEX=44, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=가격조건구분코드;
			 INDEX=45, ITEM=CNCS_CND_DCD, TYPE=string, SIZE=1, CAPTION=체결조건구분코드;
			 INDEX=46, ITEM=SQ1_STLS_YN, TYPE=string, SIZE=1, CAPTION=1차스탑로스여부;
			 INDEX=47, ITEM=SQ1_APMPR_YN, TYPE=string, SIZE=1, CAPTION=1차지정가여부;
			 INDEX=48, ITEM=SQ1_DVSN_YN, TYPE=string, SIZE=1, CAPTION=1차구분여부;
			 INDEX=49, ITEM=SQ1_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1차스탑로스가격;
			 INDEX=50, ITEM=SQ1_APPN_PRC, TYPE=string, SIZE=24, CAPTION=1차지정가격;
			 INDEX=51, ITEM=SQ1_CHAS_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1차추적손절매가격;
			 INDEX=52, ITEM=CTRT_UN_AMT, TYPE=string, SIZE=24, CAPTION=계약단위금액;
			 INDEX=53, ITEM=ORDR_DRCN_DCD, TYPE=string, SIZE=1, CAPTION=주문방향구분코드;
			 INDEX=54, ITEM=AVR_CNCS_PRC, TYPE=string, SIZE=24, CAPTION=평균체결가격;
			 INDEX=55, ITEM=ODRV_NOW_PRC, TYPE=string, SIZE=24, CAPTION=해외파생현재가격;
			 INDEX=56, ITEM=PRDT_CD2, TYPE=string, SIZE=32, CAPTION=상품코드2;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strODRV_SELL_BUY_DCD;		//해외파생매도매수구분코드
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strPWD;		//비밀번호

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q51", "OTS5919Q51_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q51", "OTS5919Q51_in_sub01", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q51", "OTS5919Q51_in_sub01", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q51", "OTS5919Q51_in_sub01", "PWD", strPWD);		//비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strPST_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PST_NO", nRow);		//포지션번호
CString strCTNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CTNO", nRow);		//종합계좌대체번호
CString strCANO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CANO", nRow);		//종합계좌번호
CString strAPNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "APNO", nRow);		//계좌상품번호
CString strCNCS_DT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_DT", nRow);		//체결일자
CString strMNGM_BDCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "MNGM_BDCD", nRow);		//관리부점코드
CString strODRV_CSGN_SLF_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CSGN_SLF_DCD", nRow);		//해외파생위탁자기구분코드
CString strFDM_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "FDM_UNQ_NO", nRow);		//딜링하우스고유번호
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PRDT_CD", nRow);		//상품코드
CString strNMPR_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "NMPR_UNQ_NO", nRow);		//호가고유번호
CString strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//해외파생매도매수구분코드
CString strODRV_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CNCS_PRC", nRow);		//해외파생체결가격
CString strFRS_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "FRS_CNCS_QNT", nRow);		//최초체결수량
CString strCLR_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CLR_QNT", nRow);		//청산수량
CString strCNCS_CNCL_TR_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_CNCL_TR_QNT", nRow);		//체결취소거래수량
CString strUSTL_CTRC_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_QNT", nRow);		//미결제약정수량
CString strUSTL_CTRC_AMT2 = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_AMT2", nRow);		//미결제약정금액2
CString strUSTL_CTRC_AMT3 = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_AMT3", nRow);		//미결제약정금액3
CString strCNCS_PIP_VALU_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_PIP_VALU_AMT", nRow);		//체결PIP가치금액
CString strODRV_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CTRC_AMT", nRow);		//해외파생약정금액
CString strUSTL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_AMT", nRow);		//미결제약정금액
CString strCRSS_EXRT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CRSS_EXRT", nRow);		//교차환율
CString strODRV_EXCAL_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_EXCAL_PRC", nRow);		//해외파생정산가격
CString strODRV_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_EVL_PFLS_AMT", nRow);		//해외파생평가손익금액
CString strPIP_VALU_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PIP_VALU_AMT", nRow);		//PIP가치금액
CString strTRSL_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "TRSL_EVL_PFLS_AMT", nRow);		//환산평가손익금액
CString strEXCAL_CRSS_EXRT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "EXCAL_CRSS_EXRT", nRow);		//정산교차환율
CString strONL_TR_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ONL_TR_YN", nRow);		//온라인거래여부
CString strODRV_CNCS_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CNCS_NO", nRow);		//해외파생체결번호
CString strHOLD_PST_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "HOLD_PST_YN", nRow);		//보유포지션여부
CString strUSE_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USE_YN", nRow);		//사용여부
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_ODNO", nRow);		//해외파생주문번호
CString strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_OR_ODNO", nRow);		//해외파생원주문번호
CString strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_MO_ODNO", nRow);		//해외파생모주문번호
CString strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_GRUP_NO", nRow);		//주문그룹번호
CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_DT", nRow);		//주문일자
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CUST_NM", nRow);		//고객명
CString strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_ORDR_PRC", nRow);		//해외파생주문가격
CString strMKT_PRC_APLY_STUP_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "MKT_PRC_APLY_STUP_AMT", nRow);		//시장가격적용설정금액
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_QNT", nRow);		//주문수량
CString strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "RVSE_QNT", nRow);		//정정수량
CString strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCL_QNT", nRow);		//취소수량
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_QNT", nRow);		//체결수량
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_RMN_QNT", nRow);		//주문잔여수량
CString strPRC_CND_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PRC_CND_DCD", nRow);		//가격조건구분코드
CString strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_CND_DCD", nRow);		//체결조건구분코드
CString strSQ1_STLS_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_STLS_YN", nRow);		//1차스탑로스여부
CString strSQ1_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_APMPR_YN", nRow);		//1차지정가여부
CString strSQ1_DVSN_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_DVSN_YN", nRow);		//1차구분여부
CString strSQ1_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_STLS_PRC", nRow);		//1차스탑로스가격
CString strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_APPN_PRC", nRow);		//1차지정가격
CString strSQ1_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_CHAS_STLS_PRC", nRow);		//1차추적손절매가격
CString strCTRT_UN_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CTRT_UN_AMT", nRow);		//계약단위금액
CString strORDR_DRCN_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_DRCN_DCD", nRow);		//주문방향구분코드
CString strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "AVR_CNCS_PRC", nRow);		//평균체결가격
CString strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_NOW_PRC", nRow);		//해외파생현재가격
CString strPRDT_CD2 = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PRDT_CD2", nRow);		//상품코드2
