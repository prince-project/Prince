BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7101U11, TR_NAME=CFD신규주문처리API, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS7101U11_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=계좌비밀번호;
			 INDEX=3, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
			 INDEX=4, ITEM=CFD_TRDE_DCD, TYPE=string, SIZE=1, CAPTION=CFD매매구분코드;
			 INDEX=5, ITEM=CFD_NMPR_TP_DCD, TYPE=string, SIZE=1, CAPTION=CFD호가유형구분코드;
			 INDEX=6, ITEM=CFD_ORDR_QNT, TYPE=string, SIZE=19, CAPTION=CFD주문수량;
			 INDEX=7, ITEM=CFD_ORDR_UNPR, TYPE=string, SIZE=20, CAPTION=CFD주문단가;
			 INDEX=8, ITEM=EXCG_CD, TYPE=string, SIZE=10, CAPTION=거래소코드;
			 INDEX=9, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=통신매체구분코드;
			 INDEX=10, ITEM=CFD_USR_DFNT_CD, TYPE=string, SIZE=1, CAPTION=CFD사용자정의코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS7101U11_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_ODNO, TYPE=string, SIZE=11, CAPTION=CFD주문번호;
			 INDEX=1, ITEM=MSG_CTNS, TYPE=string, SIZE=500, CAPTION=메시지내용;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strCTNO;		//종합계좌대체번호
CString strAPNO;		//계좌상품번호
CString strACNT_PWD;		//계좌비밀번호
CString strCFD_PRDT_CD;		//CFD상품코드
CString strCFD_TRDE_DCD;		//CFD매매구분코드
CString strCFD_NMPR_TP_DCD;		//CFD호가유형구분코드
CString strCFD_ORDR_QNT;		//CFD주문수량
CString strCFD_ORDR_UNPR;		//CFD주문단가
CString strEXCG_CD;		//거래소코드
CString strCOMM_MDIA_DCD;		//통신매체구분코드
CString strCFD_USR_DFNT_CD;		//CFD사용자정의코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7101U11", "OTS7101U11_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U11", "OTS7101U11_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U11", "OTS7101U11_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U11", "OTS7101U11_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U11", "OTS7101U11_in", "CFD_TRDE_DCD", strCFD_TRDE_DCD);		//CFD매매구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U11", "OTS7101U11_in", "CFD_NMPR_TP_DCD", strCFD_NMPR_TP_DCD);		//CFD호가유형구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U11", "OTS7101U11_in", "CFD_ORDR_QNT", strCFD_ORDR_QNT);		//CFD주문수량
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U11", "OTS7101U11_in", "CFD_ORDR_UNPR", strCFD_ORDR_UNPR);		//CFD주문단가
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U11", "OTS7101U11_in", "EXCG_CD", strEXCG_CD);		//거래소코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U11", "OTS7101U11_in", "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//통신매체구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U11", "OTS7101U11_in", "CFD_USR_DFNT_CD", strCFD_USR_DFNT_CD);		//CFD사용자정의코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strCFD_ODNO = m_CommAgent.GetTranOutputData("OTS7101U11", "OTS7101U11_out", "CFD_ODNO", 0);		//CFD주문번호
CString strMSG_CTNS = m_CommAgent.GetTranOutputData("OTS7101U11", "OTS7101U11_out", "MSG_CTNS", 0);		//메시지내용
