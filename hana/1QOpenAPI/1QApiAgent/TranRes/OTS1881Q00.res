BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1881Q00, TR_NAME=계좌주문가능금수량조회현금매수, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS1881Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=계좌비밀번호;
			 INDEX=3, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=상품코드;
			 INDEX=4, ITEM=ORDR_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=주문호가구분코드;
			 INDEX=5, ITEM=HPE_PRC, TYPE=string, SIZE=19, CAPTION=희망가격;
			 INDEX=6, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=통신매체구분코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS1881Q00_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=WMY_GRD_NM, TYPE=string, SIZE=40, CAPTION=증거금등급명;
			 INDEX=1, ITEM=ITM_WMY_RT, TYPE=string, SIZE=4, CAPTION=종목증거금율;
			 INDEX=2, ITEM=GA_ITM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=A등급종목주문가능금액;
			 INDEX=3, ITEM=GB_ITM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=B등급종목주문가능금액;
			 INDEX=4, ITEM=GC_ITM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=C등급종목주문가능금액;
			 INDEX=5, ITEM=GE_ITM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=E등급종목주문가능금액;
			 INDEX=6, ITEM=GA_ITM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=A등급종목주문가능수량;
			 INDEX=7, ITEM=GB_ITM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=B등급종목주문가능수량;
			 INDEX=8, ITEM=GC_ITM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=C등급종목주문가능수량;
			 INDEX=9, ITEM=GE_ITM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=E등급종목주문가능수량;
			 INDEX=10, ITEM=MINM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=최소주문가능금액;
			 INDEX=11, ITEM=MINM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=최소주문가능수량;
			 INDEX=12, ITEM=ORDR_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=주문가능현금;
			 INDEX=13, ITEM=ORDR_PSBL_SBST_AMT, TYPE=string, SIZE=19, CAPTION=주문가능대용금액;
			 INDEX=14, ITEM=BFDT_RETRD_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=전일재매매가능현금;
			 INDEX=15, ITEM=TDAY_RETRD_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=금일재매매가능현금;
			 INDEX=16, ITEM=BFDT_RETRD_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=전일재매매가능금액;
			 INDEX=17, ITEM=TDAY_RETRD_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=금일재매매가능금액;
			 INDEX=18, ITEM=ADIT_MRTG_CSH, TYPE=string, SIZE=19, CAPTION=추가담보현금;
			 INDEX=19, ITEM=MRTG_CSH, TYPE=string, SIZE=19, CAPTION=담보현금;
			 INDEX=20, ITEM=DACA, TYPE=string, SIZE=19, CAPTION=예수금;
			 INDEX=21, ITEM=SBST_PRC_STDR_SBST_AMT, TYPE=string, SIZE=19, CAPTION=대용가격기준대용금액;
			 INDEX=22, ITEM=CSH_WMY, TYPE=string, SIZE=19, CAPTION=현금증거금;
			 INDEX=23, ITEM=SBST_PRC_STDR_SBST_WMY, TYPE=string, SIZE=19, CAPTION=대용가격기준대용증거금;
			 INDEX=24, ITEM=MXM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=최대주문가능수량;
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
CString strPRDT_CD;		//상품코드
CString strORDR_NMPR_DCD;		//주문호가구분코드
CString strHPE_PRC;		//희망가격
CString strCOMM_MDIA_DCD;		//통신매체구분코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "PRDT_CD", strPRDT_CD);		//상품코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "ORDR_NMPR_DCD", strORDR_NMPR_DCD);		//주문호가구분코드
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "HPE_PRC", strHPE_PRC);		//희망가격
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//통신매체구분코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strWMY_GRD_NM = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "WMY_GRD_NM", 0);		//증거금등급명
CString strITM_WMY_RT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "ITM_WMY_RT", 0);		//종목증거금율
CString strGA_ITM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GA_ITM_ORDR_PSBL_AMT", 0);		//A등급종목주문가능금액
CString strGB_ITM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GB_ITM_ORDR_PSBL_AMT", 0);		//B등급종목주문가능금액
CString strGC_ITM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GC_ITM_ORDR_PSBL_AMT", 0);		//C등급종목주문가능금액
CString strGE_ITM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GE_ITM_ORDR_PSBL_AMT", 0);		//E등급종목주문가능금액
CString strGA_ITM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GA_ITM_ORDR_PSBL_QNT", 0);		//A등급종목주문가능수량
CString strGB_ITM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GB_ITM_ORDR_PSBL_QNT", 0);		//B등급종목주문가능수량
CString strGC_ITM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GC_ITM_ORDR_PSBL_QNT", 0);		//C등급종목주문가능수량
CString strGE_ITM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GE_ITM_ORDR_PSBL_QNT", 0);		//E등급종목주문가능수량
CString strMINM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "MINM_ORDR_PSBL_AMT", 0);		//최소주문가능금액
CString strMINM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "MINM_ORDR_PSBL_QNT", 0);		//최소주문가능수량
CString strORDR_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "ORDR_PSBL_CSH", 0);		//주문가능현금
CString strORDR_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "ORDR_PSBL_SBST_AMT", 0);		//주문가능대용금액
CString strBFDT_RETRD_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "BFDT_RETRD_PSBL_CSH", 0);		//전일재매매가능현금
CString strTDAY_RETRD_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "TDAY_RETRD_PSBL_CSH", 0);		//금일재매매가능현금
CString strBFDT_RETRD_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "BFDT_RETRD_PSBL_AMT", 0);		//전일재매매가능금액
CString strTDAY_RETRD_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "TDAY_RETRD_PSBL_AMT", 0);		//금일재매매가능금액
CString strADIT_MRTG_CSH = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "ADIT_MRTG_CSH", 0);		//추가담보현금
CString strMRTG_CSH = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "MRTG_CSH", 0);		//담보현금
CString strDACA = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "DACA", 0);		//예수금
CString strSBST_PRC_STDR_SBST_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "SBST_PRC_STDR_SBST_AMT", 0);		//대용가격기준대용금액
CString strCSH_WMY = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "CSH_WMY", 0);		//현금증거금
CString strSBST_PRC_STDR_SBST_WMY = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "SBST_PRC_STDR_SBST_WMY", 0);		//대용가격기준대용증거금
CString strMXM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "MXM_ORDR_PSBL_QNT", 0);		//최대주문가능수량
