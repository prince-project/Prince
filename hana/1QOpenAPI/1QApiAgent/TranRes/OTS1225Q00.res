BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1225Q00, TR_NAME=계좌별당일매매손익, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS1225Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=종합계좌대체번호;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=계좌상품번호;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=비밀번호;
			 INDEX=3, ITEM=TRDE_DT, TYPE=string, SIZE=8, CAPTION=매매일자;
			 INDEX=4, ITEM=FEE_RT, TYPE=string, SIZE=17, CAPTION=수수료율;
			 INDEX=5, ITEM=TRDE_CT_INCL_YN, TYPE=string, SIZE=1, CAPTION=매매비용포함여부;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS1225Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=단축상품코드;
			 INDEX=1, ITEM=PRDT_ABBR_NM, TYPE=string, SIZE=300, CAPTION=상품약어명;
			 INDEX=2, ITEM=ITM_WMY_GRD_DCD, TYPE=string, SIZE=1, CAPTION=종목증거금등급구분코드;
			 INDEX=3, ITEM=INQ_BLN_DVSN_NM, TYPE=string, SIZE=30, CAPTION=조회잔고구분명;
			 INDEX=4, ITEM=LOAN_DT, TYPE=string, SIZE=8, CAPTION=대출일자;
			 INDEX=5, ITEM=EXP_DT, TYPE=string, SIZE=8, CAPTION=만기일자;
			 INDEX=6, ITEM=SELL_QNT, TYPE=string, SIZE=19, CAPTION=매도수량;
			 INDEX=7, ITEM=BUY_QNT, TYPE=string, SIZE=19, CAPTION=매수수량;
			 INDEX=8, ITEM=SELL_AVR_UNPR, TYPE=string, SIZE=17, CAPTION=매도평균단가;
			 INDEX=9, ITEM=BUY_AVR_UNPR, TYPE=string, SIZE=19, CAPTION=매수평균단가;
			 INDEX=10, ITEM=BUY_AMT, TYPE=string, SIZE=19, CAPTION=매수금액;
			 INDEX=11, ITEM=SELL_AMT, TYPE=string, SIZE=19, CAPTION=매도금액;
			 INDEX=12, ITEM=PV, TYPE=string, SIZE=19, CAPTION=현재가;
			 INDEX=13, ITEM=PFLS_AMT, TYPE=string, SIZE=19, CAPTION=손익금액;
			 INDEX=14, ITEM=PFLS_RT, TYPE=string, SIZE=20, CAPTION=손익율;
			 INDEX=15, ITEM=THDT_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=당일손익금액;
			 INDEX=16, ITEM=THDT_PFLS_RT, TYPE=string, SIZE=19, CAPTION=당일손익율;
			 INDEX=17, ITEM=RMN_QNT, TYPE=string, SIZE=19, CAPTION=잔여수량;
			 INDEX=18, ITEM=EVL_AMT, TYPE=string, SIZE=19, CAPTION=평가금액;
			 INDEX=19, ITEM=PCHS_AMT, TYPE=string, SIZE=19, CAPTION=매입금액;
			 INDEX=20, ITEM=FEE, TYPE=string, SIZE=19, CAPTION=수수료;
			 INDEX=21, ITEM=WHIT, TYPE=string, SIZE=19, CAPTION=제세금;
			 INDEX=22, ITEM=STL_BLN_QNT, TYPE=string, SIZE=19, CAPTION=결제잔고수량;
			 INDEX=23, ITEM=CNCS_BLN_QNT, TYPE=string, SIZE=19, CAPTION=체결잔고수량;
			 INDEX=24, ITEM=THDT_RMN_PFLS, TYPE=string, SIZE=19, CAPTION=당일잔여손익;
			 INDEX=25, ITEM=SELL_EXCAL_UNPR, TYPE=string, SIZE=19, CAPTION=매도정산단가;
			 INDEX=26, ITEM=BUY_EXCAL_UNPR, TYPE=string, SIZE=19, CAPTION=매수정산단가;
			 INDEX=27, ITEM=CRDT_AMT, TYPE=string, SIZE=19, CAPTION=신용금액;
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
CString strTRDE_DT;		//매매일자
CString strFEE_RT;		//수수료율
CString strTRDE_CT_INCL_YN;		//매매비용포함여부

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q00", "OTS1225Q00_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q00", "OTS1225Q00_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q00", "OTS1225Q00_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q00", "OTS1225Q00_in", "TRDE_DT", strTRDE_DT);		//매매일자
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q00", "OTS1225Q00_in", "FEE_RT", strFEE_RT);		//수수료율
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q00", "OTS1225Q00_in", "TRDE_CT_INCL_YN", strTRDE_CT_INCL_YN);		//매매비용포함여부




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "SHTN_PRDT_CD", nRow);		//단축상품코드
CString strPRDT_ABBR_NM = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "PRDT_ABBR_NM", nRow);		//상품약어명
CString strITM_WMY_GRD_DCD = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "ITM_WMY_GRD_DCD", nRow);		//종목증거금등급구분코드
CString strINQ_BLN_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "INQ_BLN_DVSN_NM", nRow);		//조회잔고구분명
CString strLOAN_DT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "LOAN_DT", nRow);		//대출일자
CString strEXP_DT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "EXP_DT", nRow);		//만기일자
CString strSELL_QNT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "SELL_QNT", nRow);		//매도수량
CString strBUY_QNT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "BUY_QNT", nRow);		//매수수량
CString strSELL_AVR_UNPR = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "SELL_AVR_UNPR", nRow);		//매도평균단가
CString strBUY_AVR_UNPR = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "BUY_AVR_UNPR", nRow);		//매수평균단가
CString strBUY_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "BUY_AMT", nRow);		//매수금액
CString strSELL_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "SELL_AMT", nRow);		//매도금액
CString strPV = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "PV", nRow);		//현재가
CString strPFLS_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "PFLS_AMT", nRow);		//손익금액
CString strPFLS_RT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "PFLS_RT", nRow);		//손익율
CString strTHDT_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "THDT_PFLS_AMT", nRow);		//당일손익금액
CString strTHDT_PFLS_RT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "THDT_PFLS_RT", nRow);		//당일손익율
CString strRMN_QNT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "RMN_QNT", nRow);		//잔여수량
CString strEVL_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "EVL_AMT", nRow);		//평가금액
CString strPCHS_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "PCHS_AMT", nRow);		//매입금액
CString strFEE = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "FEE", nRow);		//수수료
CString strWHIT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "WHIT", nRow);		//제세금
CString strSTL_BLN_QNT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "STL_BLN_QNT", nRow);		//결제잔고수량
CString strCNCS_BLN_QNT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "CNCS_BLN_QNT", nRow);		//체결잔고수량
CString strTHDT_RMN_PFLS = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "THDT_RMN_PFLS", nRow);		//당일잔여손익
CString strSELL_EXCAL_UNPR = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "SELL_EXCAL_UNPR", nRow);		//매도정산단가
CString strBUY_EXCAL_UNPR = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "BUY_EXCAL_UNPR", nRow);		//매수정산단가
CString strCRDT_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "CRDT_AMT", nRow);		//신용금액
