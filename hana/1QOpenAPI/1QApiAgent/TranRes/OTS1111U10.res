BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1111U10, TR_NAME=국내현물장내주식주문매도, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS1111U10_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=주문일자;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=3, ITEM=FTS_CTNO, TYPE=string, SIZE=9, CAPTION=선물대용종합계좌대체번호;
			 INDEX=4, ITEM=FTS_APNO, TYPE=string, SIZE=3, CAPTION=선물대용계좌상품번호;
			 INDEX=5, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=계좌비밀번호;
			 INDEX=6, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=7, ITEM=BUY_DT, TYPE=string, SIZE=8, CAPTION=매수일자;
			 INDEX=8, ITEM=SPTX_DCD, TYPE=string, SIZE=1, CAPTION=분리과세구분코드;
			 INDEX=9, ITEM=LOAN_SN, TYPE=string, SIZE=11, CAPTION=대출일련번호;
			 INDEX=10, ITEM=CRDT_TR_DCD, TYPE=string, SIZE=2, CAPTION=신용거래구분코드;
			 INDEX=11, ITEM=ALMN_RDMP_DCD, TYPE=string, SIZE=1, CAPTION=전액상환구분코드;
			 INDEX=12, ITEM=SSS_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=공매도호가구분코드;
			 INDEX=13, ITEM=FTS_ORDR_DCD, TYPE=string, SIZE=2, CAPTION=선물대용주문구분코드;
			 INDEX=14, ITEM=NMPR_DCD, TYPE=string, SIZE=2, CAPTION=호가구분코드;
			 INDEX=15, ITEM=ORDR_CND_DCD, TYPE=string, SIZE=2, CAPTION=주문조건구분코드;
			 INDEX=16, ITEM=RSVN_ORDR_DCD, TYPE=string, SIZE=1, CAPTION=예약주문구분코드;
			 INDEX=17, ITEM=CVRG_PRCS_DCD, TYPE=string, SIZE=2, CAPTION=반대매매처리구분코드;
			 INDEX=18, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=19, ITEM=ORDR_UNPR, TYPE=string, SIZE=19, CAPTION=주문단가;
			 INDEX=20, ITEM=EMR_ORDR_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=비상주문매체구분코드;
			 INDEX=21, ITEM=RSV_ORDR_SN, TYPE=string, SIZE=11, CAPTION=예비주문일련번호;
			 INDEX=22, ITEM=FIX_ODNO, TYPE=string, SIZE=40, CAPTION=FIX주문번호;
			 INDEX=23, ITEM=WRAP_ORDR_KND_DCD, TYPE=string, SIZE=2, CAPTION=WRAP주문종류구분코드;
			 INDEX=24, ITEM=RCMD_ORTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=추천운용상품코드;
			 INDEX=25, ITEM=GRUP_ODNO, TYPE=string, SIZE=13, CAPTION=그룹주문번호;
			 INDEX=26, ITEM=BSK_ORDR_SN, TYPE=string, SIZE=11, CAPTION=바스켓주문일련번호;
			 INDEX=27, ITEM=ORDR_ANGT_ORDR_DCD, TYPE=string, SIZE=1, CAPTION=주문대리인주문구분코드;
			 INDEX=28, ITEM=MTS_KEY, TYPE=string, SIZE=7, CAPTION=MTS키;
			 INDEX=29, ITEM=HTS_ORDR_PSBL_MDIA_YN, TYPE=string, SIZE=1, CAPTION=HTS주문가능매체여부;
			 INDEX=30, ITEM=NMPR_PROP_XCP_YN, TYPE=string, SIZE=1, CAPTION=호가적정성예외여부;
			 INDEX=31, ITEM=BNDL_SELL_ORDR_YN, TYPE=string, SIZE=1, CAPTION=일괄매도주문여부;
			 INDEX=32, ITEM=AGCP_OPPS_SELL_DCD, TYPE=string, SIZE=1, CAPTION=대행사반대매도구분코드;
			 INDEX=33, ITEM=PGM_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=프로그램호가구분코드;
			 INDEX=34, ITEM=PRTR_PANC_DCD, TYPE=string, SIZE=2, CAPTION=프로그램매매공시구분코드;
			 INDEX=35, ITEM=HTRD_NEGO_NO, TYPE=string, SIZE=7, CAPTION=대량매매협상번호;
			 INDEX=36, ITEM=HTRD_SRV_NO, TYPE=string, SIZE=7, CAPTION=대량매매서버번호;
			 INDEX=37, ITEM=HTRD_USR_NO, TYPE=string, SIZE=20, CAPTION=대량매매사용자번호;
			 INDEX=38, ITEM=BOND_ORDR_OR_UN_DCD, TYPE=string, SIZE=1, CAPTION=채권주문원단위구분코드;
			 INDEX=39, ITEM=SMLN_YN, TYPE=string, SIZE=1, CAPTION=시뮬레이션여부;
			 INDEX=40, ITEM=LOAN_DT, TYPE=string, SIZE=8, CAPTION=대출일자;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS1111U10_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=주문일련번호;
			 INDEX=1, ITEM=MSG_CD, TYPE=string, SIZE=6, CAPTION=메시지코드;
			 INDEX=2, ITEM=MSG_CTNS, TYPE=string, SIZE=500, CAPTION=메시지내용;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strORDR_DT;		//주문일자
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strFTS_CTNO;		//선물대용종합계좌대체번호
CString strFTS_APNO;		//선물대용계좌상품번호
CString strACNT_PWD;		//계좌비밀번호
CString strPRDT_CD;		//상품코드
CString strBUY_DT;		//매수일자
CString strSPTX_DCD;		//분리과세구분코드
CString strLOAN_SN;		//대출일련번호
CString strCRDT_TR_DCD;		//신용거래구분코드
CString strALMN_RDMP_DCD;		//전액상환구분코드
CString strSSS_NMPR_DCD;		//공매도호가구분코드
CString strFTS_ORDR_DCD;		//선물대용주문구분코드
CString strNMPR_DCD;		//호가구분코드
CString strORDR_CND_DCD;		//주문조건구분코드
CString strRSVN_ORDR_DCD;		//예약주문구분코드
CString strCVRG_PRCS_DCD;		//반대매매처리구분코드
CString strORDR_QNT;		//주문수량
CString strORDR_UNPR;		//주문단가
CString strEMR_ORDR_MDIA_DCD;		//비상주문매체구분코드
CString strRSV_ORDR_SN;		//예비주문일련번호
CString strFIX_ODNO;		//FIX주문번호
CString strWRAP_ORDR_KND_DCD;		//WRAP주문종류구분코드
CString strRCMD_ORTN_PRDT_CD;		//추천운용상품코드
CString strGRUP_ODNO;		//그룹주문번호
CString strBSK_ORDR_SN;		//바스켓주문일련번호
CString strORDR_ANGT_ORDR_DCD;		//주문대리인주문구분코드
CString strMTS_KEY;		//MTS키
CString strHTS_ORDR_PSBL_MDIA_YN;		//HTS주문가능매체여부
CString strNMPR_PROP_XCP_YN;		//호가적정성예외여부
CString strBNDL_SELL_ORDR_YN;		//일괄매도주문여부
CString strAGCP_OPPS_SELL_DCD;		//대행사반대매도구분코드
CString strPGM_NMPR_DCD;		//프로그램호가구분코드
CString strPRTR_PANC_DCD;		//프로그램매매공시구분코드
CString strHTRD_NEGO_NO;		//대량매매협상번호
CString strHTRD_SRV_NO;		//대량매매서버번호
CString strHTRD_USR_NO;		//대량매매사용자번호
CString strBOND_ORDR_OR_UN_DCD;		//채권주문원단위구분코드
CString strSMLN_YN;		//시뮬레이션여부
CString strLOAN_DT;		//대출일자

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ORDR_DT", strORDR_DT);		//주문일자
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "FTS_CTNO", strFTS_CTNO);		//선물대용종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "FTS_APNO", strFTS_APNO);		//선물대용계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "PRDT_CD", strPRDT_CD);		//상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "BUY_DT", strBUY_DT);		//매수일자
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "SPTX_DCD", strSPTX_DCD);		//분리과세구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "LOAN_SN", strLOAN_SN);		//대출일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "CRDT_TR_DCD", strCRDT_TR_DCD);		//신용거래구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ALMN_RDMP_DCD", strALMN_RDMP_DCD);		//전액상환구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "SSS_NMPR_DCD", strSSS_NMPR_DCD);		//공매도호가구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "FTS_ORDR_DCD", strFTS_ORDR_DCD);		//선물대용주문구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "NMPR_DCD", strNMPR_DCD);		//호가구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ORDR_CND_DCD", strORDR_CND_DCD);		//주문조건구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "RSVN_ORDR_DCD", strRSVN_ORDR_DCD);		//예약주문구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "CVRG_PRCS_DCD", strCVRG_PRCS_DCD);		//반대매매처리구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ORDR_QNT", strORDR_QNT);		//주문수량
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ORDR_UNPR", strORDR_UNPR);		//주문단가
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//비상주문매체구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "RSV_ORDR_SN", strRSV_ORDR_SN);		//예비주문일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "FIX_ODNO", strFIX_ODNO);		//FIX주문번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "WRAP_ORDR_KND_DCD", strWRAP_ORDR_KND_DCD);		//WRAP주문종류구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "RCMD_ORTN_PRDT_CD", strRCMD_ORTN_PRDT_CD);		//추천운용상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "GRUP_ODNO", strGRUP_ODNO);		//그룹주문번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "BSK_ORDR_SN", strBSK_ORDR_SN);		//바스켓주문일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//주문대리인주문구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "MTS_KEY", strMTS_KEY);		//MTS키
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "HTS_ORDR_PSBL_MDIA_YN", strHTS_ORDR_PSBL_MDIA_YN);		//HTS주문가능매체여부
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "NMPR_PROP_XCP_YN", strNMPR_PROP_XCP_YN);		//호가적정성예외여부
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "BNDL_SELL_ORDR_YN", strBNDL_SELL_ORDR_YN);		//일괄매도주문여부
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "AGCP_OPPS_SELL_DCD", strAGCP_OPPS_SELL_DCD);		//대행사반대매도구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "PGM_NMPR_DCD", strPGM_NMPR_DCD);		//프로그램호가구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "PRTR_PANC_DCD", strPRTR_PANC_DCD);		//프로그램매매공시구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "HTRD_NEGO_NO", strHTRD_NEGO_NO);		//대량매매협상번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "HTRD_SRV_NO", strHTRD_SRV_NO);		//대량매매서버번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "HTRD_USR_NO", strHTRD_USR_NO);		//대량매매사용자번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "BOND_ORDR_OR_UN_DCD", strBOND_ORDR_OR_UN_DCD);		//채권주문원단위구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "SMLN_YN", strSMLN_YN);		//시뮬레이션여부
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "LOAN_DT", strLOAN_DT);		//대출일자




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS1111U10", "OTS1111U10_out", "ORDR_SN", 0);		//주문일련번호
CString strMSG_CD = m_CommAgent.GetTranOutputData("OTS1111U10", "OTS1111U10_out", "MSG_CD", 0);		//메시지코드
CString strMSG_CTNS = m_CommAgent.GetTranOutputData("OTS1111U10", "OTS1111U10_out", "MSG_CTNS", 0);		//메시지내용
