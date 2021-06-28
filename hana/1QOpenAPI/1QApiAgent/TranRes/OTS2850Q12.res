BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2850Q12, TR_NAME=체결건별주문체결내역조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS2850Q12_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=3, ITEM=CNCS_DCD, TYPE=string, SIZE=2, CAPTION=체결구분코드;
			 INDEX=4, ITEM=STRT_ORDR_SN, TYPE=string, SIZE=11, CAPTION=시작주문일련번호;
			 INDEX=5, ITEM=INQ_DVSN, TYPE=string, SIZE=1, CAPTION=조회구분;
			 INDEX=6, ITEM=INQ_STDR_DT, TYPE=string, SIZE=8, CAPTION=조회기준일자;
			 INDEX=7, ITEM=DRVS_ITM_DVSN, TYPE=string, SIZE=1, CAPTION=파생상품종목구분;
			 INDEX=8, ITEM=FTOP_DCD, TYPE=string, SIZE=1, CAPTION=선물옵션구분코드;
			 INDEX=9, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=매도매수구분코드;
			 INDEX=10, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS2850Q12_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=FTR_SELL_ORDR_QNT_SMM, TYPE=string, SIZE=19, CAPTION=선물매도주문수량합계;
			 INDEX=1, ITEM=FTR_BUY_ORDR_QNT_SMM, TYPE=string, SIZE=19, CAPTION=선물매수주문수량합계;
			 INDEX=2, ITEM=IDX_CLPT_SELL_ORDR_QNT_SMM, TYPE=string, SIZE=19, CAPTION=지수콜옵션매도주문수량합계;
			 INDEX=3, ITEM=IDX_PTPT_SELL_ORDR_QNT_SMM, TYPE=string, SIZE=19, CAPTION=지수풋옵션매도주문수량합계;
			 INDEX=4, ITEM=IDX_CLPT_BUY_ORDR_QNT_SMM, TYPE=string, SIZE=19, CAPTION=지수콜옵션매수주문수량합계;
			 INDEX=5, ITEM=IDX_PTPT_BUY_ORDR_QNT_SMM, TYPE=string, SIZE=19, CAPTION=지수풋옵션매수주문수량합계;
			 INDEX=6, ITEM=FTR_SELL_CNCS_QNT_SMM, TYPE=string, SIZE=19, CAPTION=선물매도체결수량합계;
			 INDEX=7, ITEM=FTR_BUY_CNCS_QNT_SMM, TYPE=string, SIZE=19, CAPTION=선물매수체결수량합계;
			 INDEX=8, ITEM=IDX_CLPT_SELL_CNCS_QNT_SMM, TYPE=string, SIZE=19, CAPTION=지수콜옵션매도체결수량합계;
			 INDEX=9, ITEM=IDX_PTPT_SELL_CNCS_QNT_SMM, TYPE=string, SIZE=19, CAPTION=지수풋옵션매도체결수량합계;
			 INDEX=10, ITEM=IDX_CLPT_BUY_CNCS_QNT_SMM, TYPE=string, SIZE=19, CAPTION=지수콜옵션매수체결수량합계;
			 INDEX=11, ITEM=IDX_PTPT_BUY_CNCS_QNT_SMM, TYPE=string, SIZE=20, CAPTION=지수풋옵션매수체결수량합계;
		END_OUTPUT0_ITEM

		REC_NAME=OTS2850Q12_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=관리부점코드;
			 INDEX=1, ITEM=MNGM_BD_NM, TYPE=string, SIZE=40, CAPTION=관리부점명;
			 INDEX=2, ITEM=MO_ORDR_SN, TYPE=string, SIZE=11, CAPTION=모주문일련번호;
			 INDEX=3, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=주문일련번호;
			 INDEX=4, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=원주문일련번호;
			 INDEX=5, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=6, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=상품명;
			 INDEX=7, ITEM=DRVS_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=파생상품호가구분코드;
			 INDEX=8, ITEM=DRVS_NMPR_DVSN_NM, TYPE=string, SIZE=50, CAPTION=파생상품호가구분명;
			 INDEX=9, ITEM=ORDR_PRC_CTNS, TYPE=string, SIZE=40, CAPTION=주문가격내용;
			 INDEX=10, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=11, ITEM=CNCS_DVSN_NM, TYPE=string, SIZE=50, CAPTION=체결구분명;
			 INDEX=12, ITEM=CNCS_PRC_CTNS, TYPE=string, SIZE=30, CAPTION=체결가격내용;
			 INDEX=13, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=체결수량;
			 INDEX=14, ITEM=CNCS_DTMD, TYPE=string, SIZE=9, CAPTION=체결상세시각;
			 INDEX=15, ITEM=NCNC_QNT, TYPE=string, SIZE=19, CAPTION=미체결수량;
			 INDEX=16, ITEM=DRVS_NMPR_ACPT_DCD, TYPE=string, SIZE=2, CAPTION=파생상품호가접수구분코드;
			 INDEX=17, ITEM=DRVS_NMPR_ACPT_DVSN_NM, TYPE=string, SIZE=50, CAPTION=파생상품호가접수구분명;
			 INDEX=18, ITEM=HND_DETL_DTM, TYPE=string, SIZE=17, CAPTION=조작상세일시;
			 INDEX=19, ITEM=KRX_MSG_NO, TYPE=string, SIZE=12, CAPTION=한국거래소메시지번호;
			 INDEX=20, ITEM=CNCS_SN, TYPE=string, SIZE=11, CAPTION=체결일련번호;
			 INDEX=21, ITEM=XTNL_ISTT_RJCT_RSN_CD, TYPE=string, SIZE=5, CAPTION=외부기관거부사유코드;
			 INDEX=22, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=통신매체구분코드;
			 INDEX=23, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=매도매수구분코드;
			 INDEX=24, ITEM=SELL_BUY_DVSN_NM, TYPE=string, SIZE=40, CAPTION=매도매수구분명;
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
CString strCNCS_DCD;		//체결구분코드
CString strSTRT_ORDR_SN;		//시작주문일련번호
CString strINQ_DVSN;		//조회구분
CString strINQ_STDR_DT;		//조회기준일자
CString strDRVS_ITM_DVSN;		//파생상품종목구분
CString strFTOP_DCD;		//선물옵션구분코드
CString strSELL_BUY_DCD;		//매도매수구분코드
CString strPRDT_CD;		//상품코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "CNCS_DCD", strCNCS_DCD);		//체결구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "STRT_ORDR_SN", strSTRT_ORDR_SN);		//시작주문일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "INQ_DVSN", strINQ_DVSN);		//조회구분
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "INQ_STDR_DT", strINQ_STDR_DT);		//조회기준일자
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "DRVS_ITM_DVSN", strDRVS_ITM_DVSN);		//파생상품종목구분
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "FTOP_DCD", strFTOP_DCD);		//선물옵션구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//매도매수구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "PRDT_CD", strPRDT_CD);		//상품코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strFTR_SELL_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_SELL_ORDR_QNT_SMM", 0);		//선물매도주문수량합계
CString strFTR_BUY_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_BUY_ORDR_QNT_SMM", 0);		//선물매수주문수량합계
CString strIDX_CLPT_SELL_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_SELL_ORDR_QNT_SMM", 0);		//지수콜옵션매도주문수량합계
CString strIDX_PTPT_SELL_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_SELL_ORDR_QNT_SMM", 0);		//지수풋옵션매도주문수량합계
CString strIDX_CLPT_BUY_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_BUY_ORDR_QNT_SMM", 0);		//지수콜옵션매수주문수량합계
CString strIDX_PTPT_BUY_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_BUY_ORDR_QNT_SMM", 0);		//지수풋옵션매수주문수량합계
CString strFTR_SELL_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_SELL_CNCS_QNT_SMM", 0);		//선물매도체결수량합계
CString strFTR_BUY_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_BUY_CNCS_QNT_SMM", 0);		//선물매수체결수량합계
CString strIDX_CLPT_SELL_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_SELL_CNCS_QNT_SMM", 0);		//지수콜옵션매도체결수량합계
CString strIDX_PTPT_SELL_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_SELL_CNCS_QNT_SMM", 0);		//지수풋옵션매도체결수량합계
CString strIDX_CLPT_BUY_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_BUY_CNCS_QNT_SMM", 0);		//지수콜옵션매수체결수량합계
CString strIDX_PTPT_BUY_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_BUY_CNCS_QNT_SMM", 0);		//지수풋옵션매수체결수량합계
CString strMNGM_BDCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "MNGM_BDCD", nRow);		//관리부점코드
CString strMNGM_BD_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "MNGM_BD_NM", nRow);		//관리부점명
CString strMO_ORDR_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "MO_ORDR_SN", nRow);		//모주문일련번호
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "ORDR_SN", nRow);		//주문일련번호
CString strOR_ORDR_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "OR_ORDR_SN", nRow);		//원주문일련번호
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "PRDT_CD", nRow);		//상품코드
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "PRDT_NM", nRow);		//상품명
CString strDRVS_NMPR_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_DCD", nRow);		//파생상품호가구분코드
CString strDRVS_NMPR_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_DVSN_NM", nRow);		//파생상품호가구분명
CString strORDR_PRC_CTNS = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "ORDR_PRC_CTNS", nRow);		//주문가격내용
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "ORDR_QNT", nRow);		//주문수량
CString strCNCS_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_DVSN_NM", nRow);		//체결구분명
CString strCNCS_PRC_CTNS = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_PRC_CTNS", nRow);		//체결가격내용
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_QNT", nRow);		//체결수량
CString strCNCS_DTMD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_DTMD", nRow);		//체결상세시각
CString strNCNC_QNT = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "NCNC_QNT", nRow);		//미체결수량
CString strDRVS_NMPR_ACPT_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_ACPT_DCD", nRow);		//파생상품호가접수구분코드
CString strDRVS_NMPR_ACPT_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_ACPT_DVSN_NM", nRow);		//파생상품호가접수구분명
CString strHND_DETL_DTM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "HND_DETL_DTM", nRow);		//조작상세일시
CString strKRX_MSG_NO = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "KRX_MSG_NO", nRow);		//한국거래소메시지번호
CString strCNCS_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_SN", nRow);		//체결일련번호
CString strXTNL_ISTT_RJCT_RSN_CD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "XTNL_ISTT_RJCT_RSN_CD", nRow);		//외부기관거부사유코드
CString strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "COMM_MDIA_DCD", nRow);		//통신매체구분코드
CString strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "SELL_BUY_DCD", nRow);		//매도매수구분코드
CString strSELL_BUY_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//매도매수구분명
