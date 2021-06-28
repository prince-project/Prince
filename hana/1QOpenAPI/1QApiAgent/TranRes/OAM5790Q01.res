BEGIN_TRAN_LAYOUT

	TR_CODE=OAM5790Q01, TR_NAME=해외주식실시간시세조회, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OAM5790Q01_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=USR_ID, TYPE=string, SIZE=20, CAPTION=사용자ID;
			 INDEX=1, ITEM=INQ_DVSN, TYPE=string, SIZE=1, CAPTION=조회구분;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OAM5790Q01_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=OSTK_RLTM_QTTN_STL_DCD, TYPE=string, SIZE=1, CAPTION=해외주식실시간시세결제구분코드;
		END_OUTPUT0_ITEM

		REC_NAME=OAM5790Q01_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=QTTN_INQ_RQS_YN, TYPE=string, SIZE=1, CAPTION=시세조회신청여부;
			 INDEX=1, ITEM=OSTK_QTTN_DVSN_NM, TYPE=string, SIZE=20, CAPTION=해외주식시세구분명;
			 INDEX=2, ITEM=OVRS_EXCG_DSCM_NO, TYPE=string, SIZE=4, CAPTION=해외거래소식별번호;
			 INDEX=3, ITEM=OSTK_MKT_CD, TYPE=string, SIZE=2, CAPTION=해외주식시장코드;
			 INDEX=4, ITEM=PMNT_CRRY_CD, TYPE=string, SIZE=3, CAPTION=납부통화코드;
			 INDEX=5, ITEM=MM_USE_CHGE, TYPE=string, SIZE=11, CAPTION=월사용요금;
			 INDEX=6, ITEM=STDR_EXRT, TYPE=string, SIZE=17, CAPTION=기준환율;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strUSR_ID;		//사용자ID
CString strINQ_DVSN;		//조회구분

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OAM5790Q01", "OAM5790Q01_in", "USR_ID", strUSR_ID);		//사용자ID
m_CommAgent.SetTranInputData(nRequestId, "OAM5790Q01", "OAM5790Q01_in", "INQ_DVSN", strINQ_DVSN);		//조회구분




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCTNO = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out", "CTNO", 0);		//종합계좌대체번호
CString strAPNO = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out", "APNO", 0);		//계좌상품번호
CString strOSTK_RLTM_QTTN_STL_DCD = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out", "OSTK_RLTM_QTTN_STL_DCD", 0);		//해외주식실시간시세결제구분코드
CString strQTTN_INQ_RQS_YN = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "QTTN_INQ_RQS_YN", nRow);		//시세조회신청여부
CString strOSTK_QTTN_DVSN_NM = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "OSTK_QTTN_DVSN_NM", nRow);		//해외주식시세구분명
CString strOVRS_EXCG_DSCM_NO = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "OVRS_EXCG_DSCM_NO", nRow);		//해외거래소식별번호
CString strOSTK_MKT_CD = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "OSTK_MKT_CD", nRow);		//해외주식시장코드
CString strPMNT_CRRY_CD = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "PMNT_CRRY_CD", nRow);		//납부통화코드
CString strMM_USE_CHGE = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "MM_USE_CHGE", nRow);		//월사용요금
CString strSTDR_EXRT = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "STDR_EXRT", nRow);		//기준환율
