BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2100U30, TR_NAME=선물옵션종합정정주문, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS2100U30_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=계좌비밀번호;
			 INDEX=3, ITEM=ORDR_BDCD, TYPE=string, SIZE=5, CAPTION=주문부점코드;
			 INDEX=4, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=원주문일련번호;
			 INDEX=5, ITEM=DRVS_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=파생상품호가구분코드;
			 INDEX=6, ITEM=ORDR_PRC, TYPE=string, SIZE=20, CAPTION=주문가격;
			 INDEX=7, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=8, ITEM=ALL_YN, TYPE=string, SIZE=1, CAPTION=전체여부;
			 INDEX=9, ITEM=EMR_ORDR_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=비상주문매체구분코드;
			 INDEX=10, ITEM=DFRT_HDGE_DCD, TYPE=string, SIZE=2, CAPTION=차익헷지구분코드;
			 INDEX=11, ITEM=GRUP_ORDR_YN, TYPE=string, SIZE=1, CAPTION=그룹주문여부;
			 INDEX=12, ITEM=ORDR_GRUP_NM, TYPE=string, SIZE=100, CAPTION=주문그룹명;
			 INDEX=13, ITEM=DRVS_ORDR_CND_DCD, TYPE=string, SIZE=1, CAPTION=파생상품주문조건구분코드;
			 INDEX=14, ITEM=PWD_CNFM_YN, TYPE=string, SIZE=1, CAPTION=비밀번호확인여부;
			 INDEX=15, ITEM=CVRG_YN, TYPE=string, SIZE=1, CAPTION=반대매매여부;
			 INDEX=16, ITEM=MDIA_ORDR_SN, TYPE=string, SIZE=11, CAPTION=매체주문일련번호;
			 INDEX=17, ITEM=WRN_ORDR_CNFM_YN, TYPE=string, SIZE=1, CAPTION=경고주문확인여부;
			 INDEX=18, ITEM=ETC_ORDR_DCD, TYPE=string, SIZE=3, CAPTION=기타주문구분코드;
			 INDEX=19, ITEM=ORDR_RPRC_YN, TYPE=string, SIZE=1, CAPTION=주문재처리여부;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS2100U30_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=주문일련번호;
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
CString strORDR_BDCD;		//주문부점코드
CString strOR_ORDR_SN;		//원주문일련번호
CString strDRVS_NMPR_DCD;		//파생상품호가구분코드
CString strORDR_PRC;		//주문가격
CString strORDR_QNT;		//주문수량
CString strALL_YN;		//전체여부
CString strEMR_ORDR_MDIA_DCD;		//비상주문매체구분코드
CString strDFRT_HDGE_DCD;		//차익헷지구분코드
CString strGRUP_ORDR_YN;		//그룹주문여부
CString strORDR_GRUP_NM;		//주문그룹명
CString strDRVS_ORDR_CND_DCD;		//파생상품주문조건구분코드
CString strPWD_CNFM_YN;		//비밀번호확인여부
CString strCVRG_YN;		//반대매매여부
CString strMDIA_ORDR_SN;		//매체주문일련번호
CString strWRN_ORDR_CNFM_YN;		//경고주문확인여부
CString strETC_ORDR_DCD;		//기타주문구분코드
CString strORDR_RPRC_YN;		//주문재처리여부

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "ORDR_BDCD", strORDR_BDCD);		//주문부점코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "OR_ORDR_SN", strOR_ORDR_SN);		//원주문일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "DRVS_NMPR_DCD", strDRVS_NMPR_DCD);		//파생상품호가구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "ORDR_PRC", strORDR_PRC);		//주문가격
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "ORDR_QNT", strORDR_QNT);		//주문수량
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "ALL_YN", strALL_YN);		//전체여부
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//비상주문매체구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "DFRT_HDGE_DCD", strDFRT_HDGE_DCD);		//차익헷지구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "GRUP_ORDR_YN", strGRUP_ORDR_YN);		//그룹주문여부
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "ORDR_GRUP_NM", strORDR_GRUP_NM);		//주문그룹명
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "DRVS_ORDR_CND_DCD", strDRVS_ORDR_CND_DCD);		//파생상품주문조건구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "PWD_CNFM_YN", strPWD_CNFM_YN);		//비밀번호확인여부
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "CVRG_YN", strCVRG_YN);		//반대매매여부
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "MDIA_ORDR_SN", strMDIA_ORDR_SN);		//매체주문일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "WRN_ORDR_CNFM_YN", strWRN_ORDR_CNFM_YN);		//경고주문확인여부
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "ETC_ORDR_DCD", strETC_ORDR_DCD);		//기타주문구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U30", "OTS2100U30_in", "ORDR_RPRC_YN", strORDR_RPRC_YN);		//주문재처리여부




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS2100U30", "OTS2100U30_out", "ORDR_SN", 0);		//주문일련번호
