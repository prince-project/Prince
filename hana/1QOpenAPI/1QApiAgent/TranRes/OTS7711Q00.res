BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7711Q00, TR_NAME=API용CFD증거금계산기조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS7711Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
		END_INPUT0_ITEM

		REC_NAME=OTS7711Q00_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		BEGIN_INPUT1_ITEM
			 INDEX=0, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
			 INDEX=1, ITEM=CFD_ORDR_QNT, TYPE=string, SIZE=19, CAPTION=CFD주문수량;
		END_INPUT1_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS7711Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
			 INDEX=1, ITEM=CFD_PRDT_NM, TYPE=string, SIZE=100, CAPTION=CFD상품명;
			 INDEX=2, ITEM=CFD_WMY_RT, TYPE=string, SIZE=20, CAPTION=CFD증거금율;
			 INDEX=3, ITEM=CFD_ORDR_QNT, TYPE=string, SIZE=19, CAPTION=CFD주문수량;
			 INDEX=4, ITEM=CFD_PV, TYPE=string, SIZE=20, CAPTION=CFD현재가;
			 INDEX=5, ITEM=CFD_WMY, TYPE=string, SIZE=23, CAPTION=CFD증거금;
			 INDEX=6, ITEM=PRCS_YN, TYPE=string, SIZE=1, CAPTION=처리여부;
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
CString strCFD_PRDT_CD;		//CFD상품코드
CString strCFD_ORDR_QNT;		//CFD주문수량

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7711Q00", "OTS7711Q00_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7711Q00", "OTS7711Q00_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7711Q00", "OTS7711Q00_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7711Q00", "OTS7711Q00_in_sub01", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7711Q00", "OTS7711Q00_in_sub01", "CFD_ORDR_QNT", strCFD_ORDR_QNT);		//CFD주문수량




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCFD_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "CFD_PRDT_CD", nRow);		//CFD상품코드
CString strCFD_PRDT_NM = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "CFD_PRDT_NM", nRow);		//CFD상품명
CString strCFD_WMY_RT = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "CFD_WMY_RT", nRow);		//CFD증거금율
CString strCFD_ORDR_QNT = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "CFD_ORDR_QNT", nRow);		//CFD주문수량
CString strCFD_PV = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "CFD_PV", nRow);		//CFD현재가
CString strCFD_WMY = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "CFD_WMY", nRow);		//CFD증거금
CString strPRCS_YN = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "PRCS_YN", nRow);		//처리여부
