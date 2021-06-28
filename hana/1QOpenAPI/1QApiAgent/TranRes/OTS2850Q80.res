BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2850Q80, TR_NAME=주문체결내역, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS2850Q80_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=3, ITEM=ORDR_STRT_SN, TYPE=string, SIZE=11, CAPTION=주문시작일련번호;
			 INDEX=4, ITEM=INQ_DT, TYPE=string, SIZE=8, CAPTION=조회일자;
			 INDEX=5, ITEM=CNCS_NCNC_DCD, TYPE=string, SIZE=1, CAPTION=체결미체결구분코드;
			 INDEX=6, ITEM=INQ_CHNL_DVSN, TYPE=string, SIZE=1, CAPTION=조회채널구분;
			 INDEX=7, ITEM=SORT_DCD, TYPE=string, SIZE=1, CAPTION=정렬구분코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS2850Q80_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=FTR_SELL_QNT, TYPE=string, SIZE=19, CAPTION=선물매도수량;
			 INDEX=1, ITEM=FTR_BUY_QNT, TYPE=string, SIZE=19, CAPTION=선물매수수량;
			 INDEX=2, ITEM=IDX_CLPT_SELL_QNT, TYPE=string, SIZE=19, CAPTION=지수콜옵션매도수량;
			 INDEX=3, ITEM=IDX_PTPT_SELL_QNT, TYPE=string, SIZE=19, CAPTION=지수풋옵션매도수량;
			 INDEX=4, ITEM=IDX_CLPT_BUY_QNT, TYPE=string, SIZE=19, CAPTION=지수콜옵션매수수량;
			 INDEX=5, ITEM=IDX_PTPT_BUY_QNT, TYPE=string, SIZE=19, CAPTION=지수풋옵션매수수량;
			 INDEX=6, ITEM=KOSPI_FTR_SELL_QNT, TYPE=string, SIZE=19, CAPTION=코스피선물매도수량;
			 INDEX=7, ITEM=KOSPI_FTR_BUY_QNT, TYPE=string, SIZE=19, CAPTION=코스피선물매수수량;
			 INDEX=8, ITEM=STK_FTR_SELL_QNT, TYPE=string, SIZE=19, CAPTION=주식선물매도수량;
			 INDEX=9, ITEM=STK_FTR_BUY_QNT, TYPE=string, SIZE=19, CAPTION=주식선물매수수량;
			 INDEX=10, ITEM=STK_OPT_SELL_QNT, TYPE=string, SIZE=19, CAPTION=주식옵션매도수량;
			 INDEX=11, ITEM=STK_OPT_BUY_QNT, TYPE=string, SIZE=19, CAPTION=주식옵션매수수량;
			 INDEX=12, ITEM=CNCS_FTR_SELL_QNT, TYPE=string, SIZE=19, CAPTION=체결선물매도수량;
			 INDEX=13, ITEM=CNCS_FTR_BUY_QNT, TYPE=string, SIZE=19, CAPTION=체결선물매수수량;
			 INDEX=14, ITEM=CNCS_IDX_CLPT_SELL_QNT, TYPE=string, SIZE=19, CAPTION=체결지수콜옵션매도수량;
			 INDEX=15, ITEM=CNCS_IDX_PTPT_SELL_QNT, TYPE=string, SIZE=19, CAPTION=체결지수풋옵션매도수량;
			 INDEX=16, ITEM=CNCS_IDX_CLPT_BUY_QNT, TYPE=string, SIZE=19, CAPTION=체결지수콜옵션매수수량;
			 INDEX=17, ITEM=CNCS_IDX_PTPT_BUY_QNT, TYPE=string, SIZE=19, CAPTION=체결지수풋옵션매수수량;
			 INDEX=18, ITEM=CNCS_KOSPI_FTR_SELL_QNT, TYPE=string, SIZE=19, CAPTION=체결코스피선물매도수량;
			 INDEX=19, ITEM=CNCS_KOSPI_FTR_BUY_QNT, TYPE=string, SIZE=19, CAPTION=체결코스피선물매수수량;
			 INDEX=20, ITEM=CNCS_STK_FTR_SELL_QNT, TYPE=string, SIZE=19, CAPTION=체결주식선물매도수량;
			 INDEX=21, ITEM=CNCS_STK_FTR_BUY_QNT, TYPE=string, SIZE=19, CAPTION=체결주식선물매수수량;
			 INDEX=22, ITEM=CNCS_STK_OPT_SELL_QNT, TYPE=string, SIZE=19, CAPTION=체결주식옵션매도수량;
			 INDEX=23, ITEM=CNCS_STK_OPT_BUY_QNT, TYPE=string, SIZE=19, CAPTION=체결주식옵션매수수량;
		END_OUTPUT0_ITEM

		REC_NAME=OTS2850Q80_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=ODNO, TYPE=string, SIZE=10, CAPTION=주문번호;
			 INDEX=1, ITEM=OR_ODNO, TYPE=string, SIZE=10, CAPTION=원주문번호;
			 INDEX=2, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=3, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=단축상품코드;
			 INDEX=4, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=상품명;
			 INDEX=5, ITEM=SELL_BUY_DVSN_NM, TYPE=string, SIZE=40, CAPTION=매도매수구분명;
			 INDEX=6, ITEM=DRVS_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=파생상품호가구분코드;
			 INDEX=7, ITEM=NMPR_DCD, TYPE=string, SIZE=2, CAPTION=호가구분코드;
			 INDEX=8, ITEM=ORDR_PRC_AMT, TYPE=string, SIZE=30, CAPTION=주문가격금액;
			 INDEX=9, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=10, ITEM=CNCS_DVSN_NM, TYPE=string, SIZE=50, CAPTION=체결구분명;
			 INDEX=11, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=체결수량;
			 INDEX=12, ITEM=CNCS_PRC_AMT, TYPE=string, SIZE=30, CAPTION=체결가격금액;
			 INDEX=13, ITEM=KOR_CNCS_TM, TYPE=string, SIZE=7, CAPTION=한국체결시간;
			 INDEX=14, ITEM=RVSE_CNCL_CNFM_QNT, TYPE=string, SIZE=19, CAPTION=정정취소확인수량;
			 INDEX=15, ITEM=NCNC_QNT, TYPE=string, SIZE=19, CAPTION=미체결수량;
			 INDEX=16, ITEM=DRVS_NMPR_ACPT_DCD, TYPE=string, SIZE=2, CAPTION=파생상품호가접수구분코드;
			 INDEX=17, ITEM=DRVS_NMPR_ACPT_DVSN_NM, TYPE=string, SIZE=50, CAPTION=파생상품호가접수구분명;
			 INDEX=18, ITEM=EXCG_ACPT_HR, TYPE=string, SIZE=6, CAPTION=거래소접수시간;
			 INDEX=19, ITEM=KRX_MSG_NO, TYPE=string, SIZE=12, CAPTION=한국거래소메시지번호;
			 INDEX=20, ITEM=COMM_MDIA_DCD_NM, TYPE=string, SIZE=24, CAPTION=통신매체구분코드명;
			 INDEX=21, ITEM=XTNL_ISTT_RJCT_RSN_CD, TYPE=string, SIZE=5, CAPTION=외부기관거부사유코드;
			 INDEX=22, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=매도매수구분코드;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strPWD;		//비밀번호
CString strORDR_STRT_SN;		//주문시작일련번호
CString strINQ_DT;		//조회일자
CString strCNCS_NCNC_DCD;		//체결미체결구분코드
CString strINQ_CHNL_DVSN;		//조회채널구분
CString strSORT_DCD;		//정렬구분코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "ORDR_STRT_SN", strORDR_STRT_SN);		//주문시작일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "INQ_DT", strINQ_DT);		//조회일자
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "CNCS_NCNC_DCD", strCNCS_NCNC_DCD);		//체결미체결구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "INQ_CHNL_DVSN", strINQ_CHNL_DVSN);		//조회채널구분
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "SORT_DCD", strSORT_DCD);		//정렬구분코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strFTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "FTR_SELL_QNT", 0);		//선물매도수량
CString strFTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "FTR_BUY_QNT", 0);		//선물매수수량
CString strIDX_CLPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_CLPT_SELL_QNT", 0);		//지수콜옵션매도수량
CString strIDX_PTPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_PTPT_SELL_QNT", 0);		//지수풋옵션매도수량
CString strIDX_CLPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_CLPT_BUY_QNT", 0);		//지수콜옵션매수수량
CString strIDX_PTPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_PTPT_BUY_QNT", 0);		//지수풋옵션매수수량
CString strKOSPI_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "KOSPI_FTR_SELL_QNT", 0);		//코스피선물매도수량
CString strKOSPI_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "KOSPI_FTR_BUY_QNT", 0);		//코스피선물매수수량
CString strSTK_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_FTR_SELL_QNT", 0);		//주식선물매도수량
CString strSTK_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_FTR_BUY_QNT", 0);		//주식선물매수수량
CString strSTK_OPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_OPT_SELL_QNT", 0);		//주식옵션매도수량
CString strSTK_OPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_OPT_BUY_QNT", 0);		//주식옵션매수수량
CString strCNCS_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_FTR_SELL_QNT", 0);		//체결선물매도수량
CString strCNCS_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_FTR_BUY_QNT", 0);		//체결선물매수수량
CString strCNCS_IDX_CLPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_CLPT_SELL_QNT", 0);		//체결지수콜옵션매도수량
CString strCNCS_IDX_PTPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_PTPT_SELL_QNT", 0);		//체결지수풋옵션매도수량
CString strCNCS_IDX_CLPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_CLPT_BUY_QNT", 0);		//체결지수콜옵션매수수량
CString strCNCS_IDX_PTPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_PTPT_BUY_QNT", 0);		//체결지수풋옵션매수수량
CString strCNCS_KOSPI_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_KOSPI_FTR_SELL_QNT", 0);		//체결코스피선물매도수량
CString strCNCS_KOSPI_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_KOSPI_FTR_BUY_QNT", 0);		//체결코스피선물매수수량
CString strCNCS_STK_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_FTR_SELL_QNT", 0);		//체결주식선물매도수량
CString strCNCS_STK_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_FTR_BUY_QNT", 0);		//체결주식선물매수수량
CString strCNCS_STK_OPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_OPT_SELL_QNT", 0);		//체결주식옵션매도수량
CString strCNCS_STK_OPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_OPT_BUY_QNT", 0);		//체결주식옵션매수수량
CString strODNO = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "ODNO", nRow);		//주문번호
CString strOR_ODNO = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "OR_ODNO", nRow);		//원주문번호
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "PRDT_CD", nRow);		//상품코드
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "SHTN_PRDT_CD", nRow);		//단축상품코드
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "PRDT_NM", nRow);		//상품명
CString strSELL_BUY_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//매도매수구분명
CString strDRVS_NMPR_DCD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "DRVS_NMPR_DCD", nRow);		//파생상품호가구분코드
CString strNMPR_DCD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "NMPR_DCD", nRow);		//호가구분코드
CString strORDR_PRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "ORDR_PRC_AMT", nRow);		//주문가격금액
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "ORDR_QNT", nRow);		//주문수량
CString strCNCS_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "CNCS_DVSN_NM", nRow);		//체결구분명
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "CNCS_QNT", nRow);		//체결수량
CString strCNCS_PRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "CNCS_PRC_AMT", nRow);		//체결가격금액
CString strKOR_CNCS_TM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "KOR_CNCS_TM", nRow);		//한국체결시간
CString strRVSE_CNCL_CNFM_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "RVSE_CNCL_CNFM_QNT", nRow);		//정정취소확인수량
CString strNCNC_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "NCNC_QNT", nRow);		//미체결수량
CString strDRVS_NMPR_ACPT_DCD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "DRVS_NMPR_ACPT_DCD", nRow);		//파생상품호가접수구분코드
CString strDRVS_NMPR_ACPT_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "DRVS_NMPR_ACPT_DVSN_NM", nRow);		//파생상품호가접수구분명
CString strEXCG_ACPT_HR = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "EXCG_ACPT_HR", nRow);		//거래소접수시간
CString strKRX_MSG_NO = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "KRX_MSG_NO", nRow);		//한국거래소메시지번호
CString strCOMM_MDIA_DCD_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "COMM_MDIA_DCD_NM", nRow);		//통신매체구분코드명
CString strXTNL_ISTT_RJCT_RSN_CD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "XTNL_ISTT_RJCT_RSN_CD", nRow);		//외부기관거부사유코드
CString strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "SELL_BUY_DCD", nRow);		//매도매수구분코드
