BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1225Q10, TR_NAME=계좌별당일매매손익합계, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS1225Q10_in, INOUT=0, ARRAY=0, ARRINFO=;
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
		REC_NAME=OTS1225Q10_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=BUY_AMT, TYPE=string, SIZE=19, CAPTION=매수금액;
			 INDEX=1, ITEM=SELL_AMT, TYPE=string, SIZE=19, CAPTION=매도금액;
			 INDEX=2, ITEM=EXCAL_AMT, TYPE=string, SIZE=19, CAPTION=정산금액;
			 INDEX=3, ITEM=TRDE_CT_AMT, TYPE=string, SIZE=18, CAPTION=매매비용금액;
			 INDEX=4, ITEM=PFLS_AMT, TYPE=string, SIZE=19, CAPTION=손익금액;
			 INDEX=5, ITEM=PFLS_RT, TYPE=string, SIZE=20, CAPTION=손익율;
			 INDEX=6, ITEM=DACA, TYPE=string, SIZE=19, CAPTION=예수금;
			 INDEX=7, ITEM=NDY_PRSM_DACA, TYPE=string, SIZE=19, CAPTION=익일추정예수금;
			 INDEX=8, ITEM=NX_NDY_PRSM_DACA, TYPE=string, SIZE=19, CAPTION=익익일추정예수금;
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

m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q10", "OTS1225Q10_in", "CTNO", strCTNO);		//종합계좌대체번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q10", "OTS1225Q10_in", "APNO", strAPNO);		//계좌상품번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q10", "OTS1225Q10_in", "PWD", strPWD);		//비밀번호
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q10", "OTS1225Q10_in", "TRDE_DT", strTRDE_DT);		//매매일자
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q10", "OTS1225Q10_in", "FEE_RT", strFEE_RT);		//수수료율
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q10", "OTS1225Q10_in", "TRDE_CT_INCL_YN", strTRDE_CT_INCL_YN);		//매매비용포함여부




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
CString strBUY_AMT = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "BUY_AMT", 0);		//매수금액
CString strSELL_AMT = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "SELL_AMT", 0);		//매도금액
CString strEXCAL_AMT = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "EXCAL_AMT", 0);		//정산금액
CString strTRDE_CT_AMT = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "TRDE_CT_AMT", 0);		//매매비용금액
CString strPFLS_AMT = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "PFLS_AMT", 0);		//손익금액
CString strPFLS_RT = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "PFLS_RT", 0);		//손익율
CString strDACA = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "DACA", 0);		//예수금
CString strNDY_PRSM_DACA = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "NDY_PRSM_DACA", 0);		//익일추정예수금
CString strNX_NDY_PRSM_DACA = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "NX_NDY_PRSM_DACA", 0);		//익익일추정예수금
