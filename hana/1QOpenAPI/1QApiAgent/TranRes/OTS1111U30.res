BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1111U30, TR_NAME=국내현물장내주식주문정정, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS1111U30_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=주문일자;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=3, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=관리부점코드;
			 INDEX=4, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=원주문일련번호;
			 INDEX=5, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=계좌비밀번호;
			 INDEX=6, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=7, ITEM=NMPR_DCD, TYPE=string, SIZE=2, CAPTION=호가구분코드;
			 INDEX=8, ITEM=ORDR_CND_DCD, TYPE=string, SIZE=2, CAPTION=주문조건구분코드;
			 INDEX=9, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=10, ITEM=ORDR_UNPR, TYPE=string, SIZE=19, CAPTION=주문단가;
			 INDEX=11, ITEM=EMR_ORDR_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=비상주문매체구분코드;
			 INDEX=12, ITEM=GRUP_ODNO, TYPE=string, SIZE=13, CAPTION=그룹주문번호;
			 INDEX=13, ITEM=BSK_ORDR_SN, TYPE=string, SIZE=11, CAPTION=바스켓주문일련번호;
			 INDEX=14, ITEM=MTS_KEY, TYPE=string, SIZE=7, CAPTION=MTS키;
			 INDEX=15, ITEM=HTS_ORDR_PSBL_MDIA_YN, TYPE=string, SIZE=1, CAPTION=HTS주문가능매체여부;
			 INDEX=16, ITEM=NMPR_PROP_XCP_YN, TYPE=string, SIZE=1, CAPTION=호가적정성예외여부;
			 INDEX=17, ITEM=ORDR_ANGT_ORDR_DCD, TYPE=string, SIZE=1, CAPTION=주문대리인주문구분코드;
			 INDEX=18, ITEM=BOND_ORDR_OR_UN_DCD, TYPE=string, SIZE=1, CAPTION=채권주문원단위구분코드;
			 INDEX=19, ITEM=PRT_ALL_DCD, TYPE=string, SIZE=1, CAPTION=일부전체구분코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS1111U30_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strMNGM_BDCD;		//관리부점코드
CString strOR_ORDR_SN;		//원주문일련번호
CString strACNT_PWD;		//계좌비밀번호
CString strPRDT_CD;		//상품코드
CString strNMPR_DCD;		//호가구분코드
CString strORDR_CND_DCD;		//주문조건구분코드
CString strORDR_QNT;		//주문수량
CString strORDR_UNPR;		//주문단가
CString strEMR_ORDR_MDIA_DCD;		//비상주문매체구분코드
CString strGRUP_ODNO;		//그룹주문번호
CString strBSK_ORDR_SN;		//바스켓주문일련번호
CString strMTS_KEY;		//MTS키
CString strHTS_ORDR_PSBL_MDIA_YN;		//HTS주문가능매체여부
CString strNMPR_PROP_XCP_YN;		//호가적정성예외여부
CString strORDR_ANGT_ORDR_DCD;		//주문대리인주문구분코드
CString strBOND_ORDR_OR_UN_DCD;		//채권주문원단위구분코드
CString strPRT_ALL_DCD;		//일부전체구분코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "ORDR_DT", strORDR_DT);		//주문일자
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "MNGM_BDCD", strMNGM_BDCD);		//관리부점코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "OR_ORDR_SN", strOR_ORDR_SN);		//원주문일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "PRDT_CD", strPRDT_CD);		//상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "NMPR_DCD", strNMPR_DCD);		//호가구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "ORDR_CND_DCD", strORDR_CND_DCD);		//주문조건구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "ORDR_QNT", strORDR_QNT);		//주문수량
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "ORDR_UNPR", strORDR_UNPR);		//주문단가
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//비상주문매체구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "GRUP_ODNO", strGRUP_ODNO);		//그룹주문번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "BSK_ORDR_SN", strBSK_ORDR_SN);		//바스켓주문일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "MTS_KEY", strMTS_KEY);		//MTS키
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "HTS_ORDR_PSBL_MDIA_YN", strHTS_ORDR_PSBL_MDIA_YN);		//HTS주문가능매체여부
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "NMPR_PROP_XCP_YN", strNMPR_PROP_XCP_YN);		//호가적정성예외여부
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//주문대리인주문구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "BOND_ORDR_OR_UN_DCD", strBOND_ORDR_OR_UN_DCD);		//채권주문원단위구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "PRT_ALL_DCD", strPRT_ALL_DCD);		//일부전체구분코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS1111U30", "OTS1111U30_out", "ORDR_SN", 0);		//주문일련번호
CString strMSG_CD = m_CommAgent.GetTranOutputData("OTS1111U30", "OTS1111U30_out", "MSG_CD", 0);		//메시지코드
CString strMSG_CTNS = m_CommAgent.GetTranOutputData("OTS1111U30", "OTS1111U30_out", "MSG_CTNS", 0);		//메시지내용
