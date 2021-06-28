BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7101U31, TR_NAME=CFD취소주문처리API, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS7101U31_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=계좌비밀번호;
			 INDEX=3, ITEM=CFD_ODNO, TYPE=string, SIZE=11, CAPTION=CFD주문번호;
			 INDEX=4, ITEM=CFD_CVRG_DCD, TYPE=string, SIZE=1, CAPTION=CFD반대매매구분코드;
			 INDEX=5, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=통신매체구분코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS7101U31_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_ODNO, TYPE=string, SIZE=11, CAPTION=CFD주문번호;
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
CString strCFD_ODNO;		//CFD주문번호
CString strCFD_CVRG_DCD;		//CFD반대매매구분코드
CString strCOMM_MDIA_DCD;		//통신매체구분코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7101U31", "OTS7101U31_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U31", "OTS7101U31_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U31", "OTS7101U31_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U31", "OTS7101U31_in", "CFD_ODNO", strCFD_ODNO);		//CFD주문번호
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U31", "OTS7101U31_in", "CFD_CVRG_DCD", strCFD_CVRG_DCD);		//CFD반대매매구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U31", "OTS7101U31_in", "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//통신매체구분코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strCFD_ODNO = m_CommAgent.GetTranOutputData("OTS7101U31", "OTS7101U31_out", "CFD_ODNO", 0);		//CFD주문번호
