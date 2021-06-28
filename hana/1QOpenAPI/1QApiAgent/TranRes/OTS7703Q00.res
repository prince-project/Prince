BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7703Q00, TR_NAME=API용CFD주문체결목록조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS7703Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=관리부점코드;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=3, ITEM=SCTN_STRT_DT, TYPE=string, SIZE=8, CAPTION=구간시작일자;
			 INDEX=4, ITEM=SCTN_END_DT, TYPE=string, SIZE=8, CAPTION=구간종료일자;
			 INDEX=5, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
			 INDEX=6, ITEM=CFD_ODNO, TYPE=string, SIZE=11, CAPTION=CFD주문번호;
			 INDEX=7, ITEM=CFD_TRDE_DCD, TYPE=string, SIZE=1, CAPTION=CFD매매구분코드;
			 INDEX=8, ITEM=INQ_KND_DCD, TYPE=string, SIZE=1, CAPTION=조회종류구분코드;
			 INDEX=9, ITEM=INQ_ORD_DCD, TYPE=string, SIZE=1, CAPTION=조회순서구분코드;
			 INDEX=10, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS7703Q00_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_BUY_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=CFD매수체결수량;
			 INDEX=1, ITEM=CFD_BUY_CNCS_AMT, TYPE=string, SIZE=23, CAPTION=CFD매수체결금액;
			 INDEX=2, ITEM=CFD_SELL_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=CFD매도체결수량;
			 INDEX=3, ITEM=CFD_SELL_CNCS_AMT, TYPE=string, SIZE=23, CAPTION=CFD매도체결금액;
		END_OUTPUT0_ITEM

		REC_NAME=OTS7703Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=CFD_ORDR_DT, TYPE=string, SIZE=8, CAPTION=CFD주문일자;
			 INDEX=1, ITEM=CFD_OR_ODNO, TYPE=string, SIZE=11, CAPTION=CFD원주문번호;
			 INDEX=2, ITEM=CFD_ODNO, TYPE=string, SIZE=11, CAPTION=CFD주문번호;
			 INDEX=3, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=종합계좌번호;
			 INDEX=4, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=고객명;
			 INDEX=5, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=단축상품코드;
			 INDEX=6, ITEM=CFD_PRDT_NM, TYPE=string, SIZE=100, CAPTION=CFD상품명;
			 INDEX=7, ITEM=CFD_TRDE_DCD_NM, TYPE=string, SIZE=10, CAPTION=CFD매매구분코드명;
			 INDEX=8, ITEM=CFD_RVSE_CNCL_DCD_NM, TYPE=string, SIZE=10, CAPTION=CFD정정취소구분코드명;
			 INDEX=9, ITEM=CFD_ORDR_QNT, TYPE=string, SIZE=19, CAPTION=CFD주문수량;
			 INDEX=10, ITEM=CFD_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=CFD체결수량;
			 INDEX=11, ITEM=CFD_CNCL_QNT, TYPE=string, SIZE=19, CAPTION=CFD취소수량;
			 INDEX=12, ITEM=CFD_RVSE_QNT, TYPE=string, SIZE=19, CAPTION=CFD정정수량;
			 INDEX=13, ITEM=CFD_ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=CFD주문잔여수량;
			 INDEX=14, ITEM=CFD_ORDR_UNPR, TYPE=string, SIZE=20, CAPTION=CFD주문단가;
			 INDEX=15, ITEM=CFD_CNCS_UNPR, TYPE=string, SIZE=20, CAPTION=CFD체결단가;
			 INDEX=16, ITEM=CFD_ORDR_DTM, TYPE=string, SIZE=17, CAPTION=CFD주문일시;
			 INDEX=17, ITEM=CFD_CNCS_DTM, TYPE=string, SIZE=17, CAPTION=CFD체결일시;
			 INDEX=18, ITEM=CFD_ORDR_STTS_CD_NM, TYPE=string, SIZE=10, CAPTION=CFD주문상태코드명;
			 INDEX=19, ITEM=USR_NM, TYPE=string, SIZE=128, CAPTION=사용자명;
			 INDEX=20, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=통신매체구분코드;
			 INDEX=21, ITEM=ATHZ_IP_ADDR, TYPE=string, SIZE=39, CAPTION=공인IP주소;
			 INDEX=22, ITEM=MAC_ADDR, TYPE=string, SIZE=12, CAPTION=MAC주소;
			 INDEX=23, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
			 INDEX=24, ITEM=CFD_NMPR_TP_DCD_NM, TYPE=string, SIZE=20, CAPTION=CFD호가유형구분코드명;
			 INDEX=25, ITEM=CFD_ORDR_TP_DCD_NM, TYPE=string, SIZE=10, CAPTION=CFD주문유형구분코드명;
			 INDEX=26, ITEM=CFD_FEE, TYPE=string, SIZE=23, CAPTION=CFD수수료;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strMNGM_BDCD;		//관리부점코드
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strSCTN_STRT_DT;		//구간시작일자
CString strSCTN_END_DT;		//구간종료일자
CString strCFD_PRDT_CD;		//CFD상품코드
CString strCFD_ODNO;		//CFD주문번호
CString strCFD_TRDE_DCD;		//CFD매매구분코드
CString strINQ_KND_DCD;		//조회종류구분코드
CString strINQ_ORD_DCD;		//조회순서구분코드
CString strPWD;		//비밀번호

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "MNGM_BDCD", strMNGM_BDCD);		//관리부점코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "SCTN_STRT_DT", strSCTN_STRT_DT);		//구간시작일자
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "SCTN_END_DT", strSCTN_END_DT);		//구간종료일자
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "CFD_ODNO", strCFD_ODNO);		//CFD주문번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "CFD_TRDE_DCD", strCFD_TRDE_DCD);		//CFD매매구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "INQ_KND_DCD", strINQ_KND_DCD);		//조회종류구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "INQ_ORD_DCD", strINQ_ORD_DCD);		//조회순서구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "PWD", strPWD);		//비밀번호




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCFD_BUY_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out", "CFD_BUY_CNCS_QNT", 0);		//CFD매수체결수량
CString strCFD_BUY_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out", "CFD_BUY_CNCS_AMT", 0);		//CFD매수체결금액
CString strCFD_SELL_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out", "CFD_SELL_CNCS_QNT", 0);		//CFD매도체결수량
CString strCFD_SELL_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out", "CFD_SELL_CNCS_AMT", 0);		//CFD매도체결금액
CString strCFD_ORDR_DT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_DT", nRow);		//CFD주문일자
CString strCFD_OR_ODNO = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_OR_ODNO", nRow);		//CFD원주문번호
CString strCFD_ODNO = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ODNO", nRow);		//CFD주문번호
CString strCANO = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CANO", nRow);		//종합계좌번호
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CUST_NM", nRow);		//고객명
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "SHTN_PRDT_CD", nRow);		//단축상품코드
CString strCFD_PRDT_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_PRDT_NM", nRow);		//CFD상품명
CString strCFD_TRDE_DCD_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_TRDE_DCD_NM", nRow);		//CFD매매구분코드명
CString strCFD_RVSE_CNCL_DCD_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_RVSE_CNCL_DCD_NM", nRow);		//CFD정정취소구분코드명
CString strCFD_ORDR_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_QNT", nRow);		//CFD주문수량
CString strCFD_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_CNCS_QNT", nRow);		//CFD체결수량
CString strCFD_CNCL_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_CNCL_QNT", nRow);		//CFD취소수량
CString strCFD_RVSE_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_RVSE_QNT", nRow);		//CFD정정수량
CString strCFD_ORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_RMN_QNT", nRow);		//CFD주문잔여수량
CString strCFD_ORDR_UNPR = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_UNPR", nRow);		//CFD주문단가
CString strCFD_CNCS_UNPR = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_CNCS_UNPR", nRow);		//CFD체결단가
CString strCFD_ORDR_DTM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_DTM", nRow);		//CFD주문일시
CString strCFD_CNCS_DTM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_CNCS_DTM", nRow);		//CFD체결일시
CString strCFD_ORDR_STTS_CD_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_STTS_CD_NM", nRow);		//CFD주문상태코드명
CString strUSR_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "USR_NM", nRow);		//사용자명
CString strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "COMM_MDIA_DCD", nRow);		//통신매체구분코드
CString strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "ATHZ_IP_ADDR", nRow);		//공인IP주소
CString strMAC_ADDR = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "MAC_ADDR", nRow);		//MAC주소
CString strCFD_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_PRDT_CD", nRow);		//CFD상품코드
CString strCFD_NMPR_TP_DCD_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_NMPR_TP_DCD_NM", nRow);		//CFD호가유형구분코드명
CString strCFD_ORDR_TP_DCD_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_TP_DCD_NM", nRow);		//CFD주문유형구분코드명
CString strCFD_FEE = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_FEE", nRow);		//CFD수수료
