BEGIN_TRAN_LAYOUT

	TR_CODE=OTS4296Q23, TR_NAME=해외주식주문체결내역조회API용, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS4296Q23_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=3, ITEM=INQ_STRT_DT, TYPE=string, SIZE=8, CAPTION=조회시작일자;
			 INDEX=4, ITEM=INQ_END_DT, TYPE=string, SIZE=8, CAPTION=조회종료일자;
			 INDEX=5, ITEM=OSTK_MKT_GRUP_CD, TYPE=string, SIZE=2, CAPTION=해외주식시장그룹코드;
			 INDEX=6, ITEM=OVRS_SMBL_CD, TYPE=string, SIZE=12, CAPTION=해외상징코드;
			 INDEX=7, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=매도매수구분코드;
			 INDEX=8, ITEM=CNCS_NCNC_DCD, TYPE=string, SIZE=1, CAPTION=체결미체결구분코드;
			 INDEX=9, ITEM=SORT_DCD, TYPE=string, SIZE=1, CAPTION=정렬구분코드;
			 INDEX=10, ITEM=FTNG_DCD, TYPE=string, SIZE=1, CAPTION=합산구분코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS4296Q23_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=주문일자;
			 INDEX=1, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=주문일련번호;
			 INDEX=2, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=원주문일련번호;
			 INDEX=3, ITEM=OSTK_INV_INF_MKT_DCD, TYPE=string, SIZE=2, CAPTION=해외주식투자정보시장구분코드;
			 INDEX=4, ITEM=OSTK_MKT_CD, TYPE=string, SIZE=2, CAPTION=해외주식시장코드;
			 INDEX=5, ITEM=OSTK_MKT_NM, TYPE=string, SIZE=100, CAPTION=해외주식시장명;
			 INDEX=6, ITEM=OVRS_SMBL_CD, TYPE=string, SIZE=12, CAPTION=해외상징코드;
			 INDEX=7, ITEM=OSTK_SMBL_NM, TYPE=string, SIZE=130, CAPTION=해외주식상징명;
			 INDEX=8, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=매도매수구분코드;
			 INDEX=9, ITEM=SELL_BUY_DVSN_NM, TYPE=string, SIZE=40, CAPTION=매도매수구분명;
			 INDEX=10, ITEM=OSTK_ORDR_DCD, TYPE=string, SIZE=1, CAPTION=해외주식주문구분코드;
			 INDEX=11, ITEM=OSTK_ORDR_DVSN_NM, TYPE=string, SIZE=80, CAPTION=해외주식주문구분명;
			 INDEX=12, ITEM=OSTK_ORDR_PRC_DCD, TYPE=string, SIZE=1, CAPTION=해외주식주문가격구분코드;
			 INDEX=13, ITEM=OSTK_ORDR_PRC_DVSN_NM, TYPE=string, SIZE=20, CAPTION=해외주식주문가격구분명;
			 INDEX=14, ITEM=OSTK_ORDR_CND_DCD, TYPE=string, SIZE=1, CAPTION=해외주식주문조건구분코드;
			 INDEX=15, ITEM=OSTK_ORDR_CND_DVSN_NM, TYPE=string, SIZE=40, CAPTION=해외주식주문조건구분명;
			 INDEX=16, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=17, ITEM=OSTK_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=해외주식주문가격;
			 INDEX=18, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=체결수량;
			 INDEX=19, ITEM=OSTK_CNCS_PRC, TYPE=string, SIZE=24, CAPTION=해외주식체결가격;
			 INDEX=20, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=주문잔여수량;
			 INDEX=21, ITEM=OSTK_CNCS_AMT, TYPE=string, SIZE=24, CAPTION=해외주식체결금액;
			 INDEX=22, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=통화코드;
			 INDEX=23, ITEM=OSTK_ORDR_STTS_DCD, TYPE=string, SIZE=1, CAPTION=해외주식주문상태구분코드;
			 INDEX=24, ITEM=OSTK_ORDR_STTS_NM, TYPE=string, SIZE=80, CAPTION=해외주식주문상태명;
			 INDEX=25, ITEM=ORDR_DTM, TYPE=string, SIZE=14, CAPTION=주문일시;
			 INDEX=26, ITEM=CNCS_DTM, TYPE=string, SIZE=14, CAPTION=체결일시;
			 INDEX=27, ITEM=OSTK_ACPL_ORDR_DTM, TYPE=string, SIZE=14, CAPTION=해외주식현지주문일시;
			 INDEX=28, ITEM=ACPL_CNCS_DTM, TYPE=string, SIZE=14, CAPTION=현지체결일시;
			 INDEX=29, ITEM=ODER_NM, TYPE=string, SIZE=100, CAPTION=주문자명;
			 INDEX=30, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=통신매체구분코드;
			 INDEX=31, ITEM=COMM_MDIA_DVSN_NM, TYPE=string, SIZE=24, CAPTION=통신매체구분명;
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
CString strINQ_STRT_DT;		//조회시작일자
CString strINQ_END_DT;		//조회종료일자
CString strOSTK_MKT_GRUP_CD;		//해외주식시장그룹코드
CString strOVRS_SMBL_CD;		//해외상징코드
CString strSELL_BUY_DCD;		//매도매수구분코드
CString strCNCS_NCNC_DCD;		//체결미체결구분코드
CString strSORT_DCD;		//정렬구분코드
CString strFTNG_DCD;		//합산구분코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "INQ_STRT_DT", strINQ_STRT_DT);		//조회시작일자
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "INQ_END_DT", strINQ_END_DT);		//조회종료일자
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "OSTK_MKT_GRUP_CD", strOSTK_MKT_GRUP_CD);		//해외주식시장그룹코드
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "OVRS_SMBL_CD", strOVRS_SMBL_CD);		//해외상징코드
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//매도매수구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "CNCS_NCNC_DCD", strCNCS_NCNC_DCD);		//체결미체결구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "SORT_DCD", strSORT_DCD);		//정렬구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "FTNG_DCD", strFTNG_DCD);		//합산구분코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ORDR_DT", nRow);		//주문일자
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ORDR_SN", nRow);		//주문일련번호
CString strOR_ORDR_SN = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OR_ORDR_SN", nRow);		//원주문일련번호
CString strOSTK_INV_INF_MKT_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_INV_INF_MKT_DCD", nRow);		//해외주식투자정보시장구분코드
CString strOSTK_MKT_CD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_MKT_CD", nRow);		//해외주식시장코드
CString strOSTK_MKT_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_MKT_NM", nRow);		//해외주식시장명
CString strOVRS_SMBL_CD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OVRS_SMBL_CD", nRow);		//해외상징코드
CString strOSTK_SMBL_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_SMBL_NM", nRow);		//해외주식상징명
CString strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "SELL_BUY_DCD", nRow);		//매도매수구분코드
CString strSELL_BUY_DVSN_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//매도매수구분명
CString strOSTK_ORDR_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_DCD", nRow);		//해외주식주문구분코드
CString strOSTK_ORDR_DVSN_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_DVSN_NM", nRow);		//해외주식주문구분명
CString strOSTK_ORDR_PRC_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_PRC_DCD", nRow);		//해외주식주문가격구분코드
CString strOSTK_ORDR_PRC_DVSN_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_PRC_DVSN_NM", nRow);		//해외주식주문가격구분명
CString strOSTK_ORDR_CND_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_CND_DCD", nRow);		//해외주식주문조건구분코드
CString strOSTK_ORDR_CND_DVSN_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_CND_DVSN_NM", nRow);		//해외주식주문조건구분명
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ORDR_QNT", nRow);		//주문수량
CString strOSTK_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_PRC", nRow);		//해외주식주문가격
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "CNCS_QNT", nRow);		//체결수량
CString strOSTK_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_CNCS_PRC", nRow);		//해외주식체결가격
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ORDR_RMN_QNT", nRow);		//주문잔여수량
CString strOSTK_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_CNCS_AMT", nRow);		//해외주식체결금액
CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "CRRY_CD", nRow);		//통화코드
CString strOSTK_ORDR_STTS_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_STTS_DCD", nRow);		//해외주식주문상태구분코드
CString strOSTK_ORDR_STTS_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_STTS_NM", nRow);		//해외주식주문상태명
CString strORDR_DTM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ORDR_DTM", nRow);		//주문일시
CString strCNCS_DTM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "CNCS_DTM", nRow);		//체결일시
CString strOSTK_ACPL_ORDR_DTM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ACPL_ORDR_DTM", nRow);		//해외주식현지주문일시
CString strACPL_CNCS_DTM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ACPL_CNCS_DTM", nRow);		//현지체결일시
CString strODER_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ODER_NM", nRow);		//주문자명
CString strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "COMM_MDIA_DCD", nRow);		//통신매체구분코드
CString strCOMM_MDIA_DVSN_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "COMM_MDIA_DVSN_NM", nRow);		//통신매체구분명
