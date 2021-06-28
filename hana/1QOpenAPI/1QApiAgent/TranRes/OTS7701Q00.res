BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7701Q00, TR_NAME=API용CFD주문거래가능종목목록조, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=OTS7701Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=EXCG_CD, TYPE=string, SIZE=10, CAPTION=거래소코드;
			 INDEX=1, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
		END_INPUT0_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OTS7701Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=EXCG_CD, TYPE=string, SIZE=10, CAPTION=거래소코드;
			 INDEX=1, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD상품코드;
			 INDEX=2, ITEM=CFD_WMY_RT, TYPE=string, SIZE=20, CAPTION=CFD증거금율;
			 INDEX=3, ITEM=CFD_BUY_PSBL_YN, TYPE=string, SIZE=1, CAPTION=CFD매수가능여부;
			 INDEX=4, ITEM=CFD_SELL_PSBL_YN, TYPE=string, SIZE=1, CAPTION=CFD매도가능여부;
			 INDEX=5, ITEM=CFD_BUY_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFD매수가능수량;
			 INDEX=6, ITEM=CFD_SELL_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFD매도가능수량;
			 INDEX=7, ITEM=CFD_ITNT_STN_NTN_CD, TYPE=string, SIZE=2, CAPTION=CFD국제표준국가코드;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strEXCG_CD;		//거래소코드
CString strCFD_PRDT_CD;		//CFD상품코드

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q00", "OTS7701Q00_in", "EXCG_CD", strEXCG_CD);		//거래소코드
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q00", "OTS7701Q00_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD상품코드




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strEXCG_CD = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "EXCG_CD", nRow);		//거래소코드
CString strCFD_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_PRDT_CD", nRow);		//CFD상품코드
CString strCFD_WMY_RT = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_WMY_RT", nRow);		//CFD증거금율
CString strCFD_BUY_PSBL_YN = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_BUY_PSBL_YN", nRow);		//CFD매수가능여부
CString strCFD_SELL_PSBL_YN = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_SELL_PSBL_YN", nRow);		//CFD매도가능여부
CString strCFD_BUY_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_BUY_PSBL_QNT", nRow);		//CFD매수가능수량
CString strCFD_SELL_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_SELL_PSBL_QNT", nRow);		//CFD매도가능수량
CString strCFD_ITNT_STN_NTN_CD = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_ITNT_STN_NTN_CD", nRow);		//CFD국제표준국가코드
