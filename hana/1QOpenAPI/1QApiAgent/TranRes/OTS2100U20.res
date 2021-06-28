BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2100U20, TR_NAME=선물옵션종합매수주문, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS2100U20_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=계좌비밀번호;
			 INDEX=3, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=매도매수구분코드;
			 INDEX=4, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=5, ITEM=DRVS_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=파생상품호가구분코드;
			 INDEX=6, ITEM=ORDR_PRC, TYPE=string, SIZE=20, CAPTION=주문가격;
			 INDEX=7, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=주문수량;
			 INDEX=8, ITEM=EMR_ORDR_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=비상주문매체구분코드;
			 INDEX=9, ITEM=DFRT_HDGE_DCD, TYPE=string, SIZE=2, CAPTION=차익헷지구분코드;
			 INDEX=10, ITEM=GRUP_ORDR_YN, TYPE=string, SIZE=1, CAPTION=그룹주문여부;
			 INDEX=11, ITEM=ORDR_GRUP_NM, TYPE=string, SIZE=100, CAPTION=주문그룹명;
			 INDEX=12, ITEM=BNDL_ORDR_GRUP_NO, TYPE=string, SIZE=7, CAPTION=일괄주문그룹번호;
			 INDEX=13, ITEM=DRVS_WRAP_ORDR_DCD, TYPE=string, SIZE=2, CAPTION=파생상품WRAP주문구분코드;
			 INDEX=14, ITEM=RCMD_ORTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=추천운용상품코드;
			 INDEX=15, ITEM=BSK_TRDE_ORDR_SN, TYPE=string, SIZE=11, CAPTION=바스켓매매주문일련번호;
			 INDEX=16, ITEM=DRVS_ORDR_CND_DCD, TYPE=string, SIZE=1, CAPTION=파생상품주문조건구분코드;
			 INDEX=17, ITEM=PWD_CNFM_YN, TYPE=string, SIZE=1, CAPTION=비밀번호확인여부;
			 INDEX=18, ITEM=CVRG_YN, TYPE=string, SIZE=1, CAPTION=반대매매여부;
			 INDEX=19, ITEM=MDIA_ORDR_SN, TYPE=string, SIZE=11, CAPTION=매체주문일련번호;
			 INDEX=20, ITEM=ADIT_WMY_BNDL_ORDR_YN, TYPE=string, SIZE=1, CAPTION=추가증거금일괄주문여부;
			 INDEX=21, ITEM=WRN_ORDR_CNFM_YN, TYPE=string, SIZE=1, CAPTION=경고주문확인여부;
			 INDEX=22, ITEM=ETC_ORDR_DCD, TYPE=string, SIZE=3, CAPTION=기타주문구분코드;
			 INDEX=23, ITEM=ORDR_ANGT_ORDR_DCD, TYPE=string, SIZE=1, CAPTION=주문대리인주문구분코드;
			 INDEX=24, ITEM=ORDR_RPRC_YN, TYPE=string, SIZE=1, CAPTION=주문재처리여부;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS2100U20_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strSELL_BUY_DCD;		//매도매수구분코드
CString strPRDT_CD;		//상품코드
CString strDRVS_NMPR_DCD;		//파생상품호가구분코드
CString strORDR_PRC;		//주문가격
CString strORDR_QNT;		//주문수량
CString strEMR_ORDR_MDIA_DCD;		//비상주문매체구분코드
CString strDFRT_HDGE_DCD;		//차익헷지구분코드
CString strGRUP_ORDR_YN;		//그룹주문여부
CString strORDR_GRUP_NM;		//주문그룹명
CString strBNDL_ORDR_GRUP_NO;		//일괄주문그룹번호
CString strDRVS_WRAP_ORDR_DCD;		//파생상품WRAP주문구분코드
CString strRCMD_ORTN_PRDT_CD;		//추천운용상품코드
CString strBSK_TRDE_ORDR_SN;		//바스켓매매주문일련번호
CString strDRVS_ORDR_CND_DCD;		//파생상품주문조건구분코드
CString strPWD_CNFM_YN;		//비밀번호확인여부
CString strCVRG_YN;		//반대매매여부
CString strMDIA_ORDR_SN;		//매체주문일련번호
CString strADIT_WMY_BNDL_ORDR_YN;		//추가증거금일괄주문여부
CString strWRN_ORDR_CNFM_YN;		//경고주문확인여부
CString strETC_ORDR_DCD;		//기타주문구분코드
CString strORDR_ANGT_ORDR_DCD;		//주문대리인주문구분코드
CString strORDR_RPRC_YN;		//주문재처리여부

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//매도매수구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "PRDT_CD", strPRDT_CD);		//상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "DRVS_NMPR_DCD", strDRVS_NMPR_DCD);		//파생상품호가구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ORDR_PRC", strORDR_PRC);		//주문가격
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ORDR_QNT", strORDR_QNT);		//주문수량
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//비상주문매체구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "DFRT_HDGE_DCD", strDFRT_HDGE_DCD);		//차익헷지구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "GRUP_ORDR_YN", strGRUP_ORDR_YN);		//그룹주문여부
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ORDR_GRUP_NM", strORDR_GRUP_NM);		//주문그룹명
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "BNDL_ORDR_GRUP_NO", strBNDL_ORDR_GRUP_NO);		//일괄주문그룹번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "DRVS_WRAP_ORDR_DCD", strDRVS_WRAP_ORDR_DCD);		//파생상품WRAP주문구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "RCMD_ORTN_PRDT_CD", strRCMD_ORTN_PRDT_CD);		//추천운용상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "BSK_TRDE_ORDR_SN", strBSK_TRDE_ORDR_SN);		//바스켓매매주문일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "DRVS_ORDR_CND_DCD", strDRVS_ORDR_CND_DCD);		//파생상품주문조건구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "PWD_CNFM_YN", strPWD_CNFM_YN);		//비밀번호확인여부
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "CVRG_YN", strCVRG_YN);		//반대매매여부
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "MDIA_ORDR_SN", strMDIA_ORDR_SN);		//매체주문일련번호
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ADIT_WMY_BNDL_ORDR_YN", strADIT_WMY_BNDL_ORDR_YN);		//추가증거금일괄주문여부
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "WRN_ORDR_CNFM_YN", strWRN_ORDR_CNFM_YN);		//경고주문확인여부
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ETC_ORDR_DCD", strETC_ORDR_DCD);		//기타주문구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//주문대리인주문구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ORDR_RPRC_YN", strORDR_RPRC_YN);		//주문재처리여부




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS2100U20", "OTS2100U20_out", "ORDR_SN", 0);		//주문일련번호
