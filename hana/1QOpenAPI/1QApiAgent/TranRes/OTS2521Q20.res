BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2521Q20, TR_NAME=전략트레이딩사용계좌리스트, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS2521Q20_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=USR_ID, TYPE=string, SIZE=20, CAPTION=사용자ID;
			 INDEX=1, ITEM=STGY_DCD, TYPE=string, SIZE=1, CAPTION=전략구분코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS2521Q20_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=INQ_CNT, TYPE=string, SIZE=19, CAPTION=조회건수;
		END_OUTPUT0_ITEM

		REC_NAME=OTS2521Q20_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=종합계좌번호;
			 INDEX=1, ITEM=ACNT_NM, TYPE=string, SIZE=192, CAPTION=계좌명;
			 INDEX=2, ITEM=STGY_DCD, TYPE=string, SIZE=1, CAPTION=전략구분코드;
			 INDEX=3, ITEM=DCD_NM, TYPE=string, SIZE=40, CAPTION=구분코드명;
			 INDEX=4, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=5, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strUSR_ID;		//사용자ID
CString strSTGY_DCD;		//전략구분코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2521Q20", "OTS2521Q20_in", "USR_ID", strUSR_ID);		//사용자ID
m_CommAgent.SetTranInputData(nRequestId, "OTS2521Q20", "OTS2521Q20_in", "STGY_DCD", strSTGY_DCD);		//전략구분코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strINQ_CNT = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out", "INQ_CNT", 0);		//조회건수
CString strCANO = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out_sub01", "CANO", nRow);		//종합계좌번호
CString strACNT_NM = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out_sub01", "ACNT_NM", nRow);		//계좌명
CString strSTGY_DCD = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out_sub01", "STGY_DCD", nRow);		//전략구분코드
CString strDCD_NM = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out_sub01", "DCD_NM", nRow);		//구분코드명
CString strCTNO = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out_sub01", "CTNO", nRow);		//종합계좌대체번호
CString strAPNO = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out_sub01", "APNO", nRow);		//계좌상품번호
