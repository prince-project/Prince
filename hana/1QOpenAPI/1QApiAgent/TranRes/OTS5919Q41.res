BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5919Q41, TR_NAME=미결제약정현황해외ON계좌그룹별, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS5919Q41_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=해외파생매도매수구분코드;
		END_INPUT0_ITEM

		REC_NAME=OTS5919Q41_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		BEGIN_INPUT1_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT1_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS5919Q41_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=종합계좌번호;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=3, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=고객명;
			 INDEX=4, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=5, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=상품명;
			 INDEX=6, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=해외파생매도매수구분코드;
			 INDEX=7, ITEM=USTL_CTRC_QNT, TYPE=string, SIZE=19, CAPTION=미결제약정수량;
			 INDEX=8, ITEM=TRDE_AVR_UNPR, TYPE=string, SIZE=23, CAPTION=매매평균단가;
			 INDEX=9, ITEM=CLR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=청산가능수량;
			 INDEX=10, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=주문잔여수량;
			 INDEX=11, ITEM=ODRV_NOW_PRC, TYPE=string, SIZE=24, CAPTION=해외파생현재가격;
			 INDEX=12, ITEM=ODRV_BFDT_PRPT, TYPE=string, SIZE=24, CAPTION=해외파생전일대비;
			 INDEX=13, ITEM=ODRV_BFDT_PRPT_RT, TYPE=string, SIZE=24, CAPTION=해외파생전일대비율;
			 INDEX=14, ITEM=ODRV_EVL_AMT, TYPE=string, SIZE=24, CAPTION=해외파생평가금액;
			 INDEX=15, ITEM=ODRV_EVL_PFLS_AMT, TYPE=string, SIZE=24, CAPTION=해외파생평가손익금액;
			 INDEX=16, ITEM=ODRV_PFLS_RT, TYPE=string, SIZE=24, CAPTION=해외파생손익율;
			 INDEX=17, ITEM=USTL_CTRC_AMT, TYPE=string, SIZE=24, CAPTION=미결제약정금액;
			 INDEX=18, ITEM=TRSL_MLT, TYPE=string, SIZE=23, CAPTION=환산승수;
			 INDEX=19, ITEM=ODRV_FTOP_DCD, TYPE=string, SIZE=1, CAPTION=해외파생선물옵션구분코드;
			 INDEX=20, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=통화코드;
			 INDEX=21, ITEM=PRC_DCPN_BLW_LNG, TYPE=string, SIZE=6, CAPTION=가격소수점이하길이;
			 INDEX=22, ITEM=INDC_PRC, TYPE=string, SIZE=19, CAPTION=표시가격;
			 INDEX=23, ITEM=BSN_DT, TYPE=string, SIZE=8, CAPTION=영업일자;
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

m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q41", "OTS5919Q41_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//해외파생매도매수구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q41", "OTS5919Q41_in_sub01", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q41", "OTS5919Q41_in_sub01", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q41", "OTS5919Q41_in_sub01", "PWD", strPWD);		//비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCANO = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "CANO", nRow);		//종합계좌번호
CString strCTNO = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "CTNO", nRow);		//종합계좌대체번호
CString strAPNO = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "APNO", nRow);		//계좌상품번호
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "CUST_NM", nRow);		//고객명
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "PRDT_CD", nRow);		//상품코드
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "PRDT_NM", nRow);		//상품명
CString strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//해외파생매도매수구분코드
CString strUSTL_CTRC_QNT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "USTL_CTRC_QNT", nRow);		//미결제약정수량
CString strTRDE_AVR_UNPR = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "TRDE_AVR_UNPR", nRow);		//매매평균단가
CString strCLR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "CLR_PSBL_QNT", nRow);		//청산가능수량
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ORDR_RMN_QNT", nRow);		//주문잔여수량
CString strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_NOW_PRC", nRow);		//해외파생현재가격
CString strODRV_BFDT_PRPT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_BFDT_PRPT", nRow);		//해외파생전일대비
CString strODRV_BFDT_PRPT_RT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_BFDT_PRPT_RT", nRow);		//해외파생전일대비율
CString strODRV_EVL_AMT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_EVL_AMT", nRow);		//해외파생평가금액
CString strODRV_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_EVL_PFLS_AMT", nRow);		//해외파생평가손익금액
CString strODRV_PFLS_RT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_PFLS_RT", nRow);		//해외파생손익율
CString strUSTL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "USTL_CTRC_AMT", nRow);		//미결제약정금액
CString strTRSL_MLT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "TRSL_MLT", nRow);		//환산승수
CString strODRV_FTOP_DCD = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_FTOP_DCD", nRow);		//해외파생선물옵션구분코드
CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "CRRY_CD", nRow);		//통화코드
CString strPRC_DCPN_BLW_LNG = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "PRC_DCPN_BLW_LNG", nRow);		//가격소수점이하길이
CString strINDC_PRC = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "INDC_PRC", nRow);		//표시가격
CString strBSN_DT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "BSN_DT", nRow);		//영업일자
