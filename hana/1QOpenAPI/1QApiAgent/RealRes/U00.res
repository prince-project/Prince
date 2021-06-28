BEGIN_FUNCTION_MAP
	REAL_TYPE=28, REAL_NAME=U00, DESCRIPTION=업종지수체결;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=BSTP_CLS_CODE, TYPE=string, SIZE=3, KEY=1, CAPTION=업종 구분 코드, FID=0;
			 INDEX=1, ITEM=ANTC_NMIX_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=예상지수 구분코드, FID=0;
			 INDEX=2, ITEM=BSOP_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=실시간일자, FID=9;
			 INDEX=3, ITEM=BSOP_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=시간, FID=8;
			 INDEX=4, ITEM=PRPR_NMIX, TYPE=string, SIZE=18, KEY=0, CAPTION=지수, FID=4;
			 INDEX=5, ITEM=PRPR_NMIX_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRPR_NMIX]색참조(+상승, -하락), FID=0;
			 INDEX=6, ITEM=PRDY_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=전일 대비 부호, FID=6;
			 INDEX=7, ITEM=BSTP_NMIX_PRDY_VRSS, TYPE=string, SIZE=18, KEY=0, CAPTION=전일 대비, FID=5;
			 INDEX=8, ITEM=BSTP_NMIX_PRDY_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BSTP_NMIX_PRDY_VRSS]색참조(+상승, -하락), FID=0;
			 INDEX=9, ITEM=PRDY_CTRT, TYPE=string, SIZE=18, KEY=0, CAPTION=등락율, FID=7;
			 INDEX=10, ITEM=PRDY_CTRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRDY_CTRT]색참조(+상승, -하락), FID=0;
			 INDEX=11, ITEM=ACML_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=누적 거래량, FID=11;
			 INDEX=12, ITEM=ACML_TR_PBMN, TYPE=string, SIZE=18, KEY=0, CAPTION=누적 거래 대금, FID=12;
			 INDEX=13, ITEM=OPRC_NMIX, TYPE=string, SIZE=18, KEY=0, CAPTION=시가, FID=13;
			 INDEX=14, ITEM=OPRC_NMIX_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPRC_NMIX]색참조(+상승, -하락), FID=0;
			 INDEX=15, ITEM=NMIX_HGPR, TYPE=string, SIZE=18, KEY=0, CAPTION=고가, FID=14;
			 INDEX=16, ITEM=NMIX_HGPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NMIX_HGPR]색참조(+상승, -하락), FID=0;
			 INDEX=17, ITEM=NMIX_LWPR, TYPE=string, SIZE=18, KEY=0, CAPTION=저가, FID=15;
			 INDEX=18, ITEM=NMIX_LWPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NMIX_LWPR]색참조(+상승, -하락), FID=0;
			 INDEX=19, ITEM=CNTG_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=체결 거래량, FID=83;
			 INDEX=20, ITEM=CNTG_PRGS, TYPE=string, SIZE=10, KEY=0, CAPTION=체결틱추이, FID=2655;
			 INDEX=21, ITEM=ANTC_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=예상지수구분코드, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strBSTP_CLS_CODE = m_CommAgent.GetRealOutputData("U00", "BSTP_CLS_CODE");		//업종 구분 코드
CString strANTC_NMIX_CLS_CODE = m_CommAgent.GetRealOutputData("U00", "ANTC_NMIX_CLS_CODE");		//예상지수 구분코드
CString strBSOP_DATE = m_CommAgent.GetRealOutputData("U00", "BSOP_DATE");		//실시간일자
CString strBSOP_HOUR = m_CommAgent.GetRealOutputData("U00", "BSOP_HOUR");		//시간
CString strPRPR_NMIX = m_CommAgent.GetRealOutputData("U00", "PRPR_NMIX");		//지수
CString strPRPR_NMIX_CLR = m_CommAgent.GetRealOutputData("U00", "PRPR_NMIX_CLR");		//[PRPR_NMIX]색참조(+상승, -하락)
CString strPRDY_VRSS_SIGN = m_CommAgent.GetRealOutputData("U00", "PRDY_VRSS_SIGN");		//전일 대비 부호
CString strBSTP_NMIX_PRDY_VRSS = m_CommAgent.GetRealOutputData("U00", "BSTP_NMIX_PRDY_VRSS");		//전일 대비
CString strBSTP_NMIX_PRDY_VRSS_CLR = m_CommAgent.GetRealOutputData("U00", "BSTP_NMIX_PRDY_VRSS_CLR");		//[BSTP_NMIX_PRDY_VRSS]색참조(+상승, -하락)
CString strPRDY_CTRT = m_CommAgent.GetRealOutputData("U00", "PRDY_CTRT");		//등락율
CString strPRDY_CTRT_CLR = m_CommAgent.GetRealOutputData("U00", "PRDY_CTRT_CLR");		//[PRDY_CTRT]색참조(+상승, -하락)
CString strACML_VOL = m_CommAgent.GetRealOutputData("U00", "ACML_VOL");		//누적 거래량
CString strACML_TR_PBMN = m_CommAgent.GetRealOutputData("U00", "ACML_TR_PBMN");		//누적 거래 대금
CString strOPRC_NMIX = m_CommAgent.GetRealOutputData("U00", "OPRC_NMIX");		//시가
CString strOPRC_NMIX_CLR = m_CommAgent.GetRealOutputData("U00", "OPRC_NMIX_CLR");		//[OPRC_NMIX]색참조(+상승, -하락)
CString strNMIX_HGPR = m_CommAgent.GetRealOutputData("U00", "NMIX_HGPR");		//고가
CString strNMIX_HGPR_CLR = m_CommAgent.GetRealOutputData("U00", "NMIX_HGPR_CLR");		//[NMIX_HGPR]색참조(+상승, -하락)
CString strNMIX_LWPR = m_CommAgent.GetRealOutputData("U00", "NMIX_LWPR");		//저가
CString strNMIX_LWPR_CLR = m_CommAgent.GetRealOutputData("U00", "NMIX_LWPR_CLR");		//[NMIX_LWPR]색참조(+상승, -하락)
CString strCNTG_VOL = m_CommAgent.GetRealOutputData("U00", "CNTG_VOL");		//체결 거래량
CString strCNTG_PRGS = m_CommAgent.GetRealOutputData("U00", "CNTG_PRGS");		//체결틱추이
CString strANTC_CLS_CODE = m_CommAgent.GetRealOutputData("U00", "ANTC_CLS_CODE");		//예상지수구분코드




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strBSTP_CLS_CODE = realCommRecvData.GetItem(0, 0);		//업종 구분 코드
CString strANTC_NMIX_CLS_CODE = realCommRecvData.GetItem(0, 1);		//예상지수 구분코드
CString strBSOP_DATE = realCommRecvData.GetItem(0, 2);		//실시간일자
CString strBSOP_HOUR = realCommRecvData.GetItem(0, 3);		//시간
CString strPRPR_NMIX = realCommRecvData.GetItem(0, 4);		//지수
CString strPRPR_NMIX_CLR = realCommRecvData.GetItem(0, 5);		//[PRPR_NMIX]색참조(+상승, -하락)
CString strPRDY_VRSS_SIGN = realCommRecvData.GetItem(0, 6);		//전일 대비 부호
CString strBSTP_NMIX_PRDY_VRSS = realCommRecvData.GetItem(0, 7);		//전일 대비
CString strBSTP_NMIX_PRDY_VRSS_CLR = realCommRecvData.GetItem(0, 8);		//[BSTP_NMIX_PRDY_VRSS]색참조(+상승, -하락)
CString strPRDY_CTRT = realCommRecvData.GetItem(0, 9);		//등락율
CString strPRDY_CTRT_CLR = realCommRecvData.GetItem(0, 10);		//[PRDY_CTRT]색참조(+상승, -하락)
CString strACML_VOL = realCommRecvData.GetItem(0, 11);		//누적 거래량
CString strACML_TR_PBMN = realCommRecvData.GetItem(0, 12);		//누적 거래 대금
CString strOPRC_NMIX = realCommRecvData.GetItem(0, 13);		//시가
CString strOPRC_NMIX_CLR = realCommRecvData.GetItem(0, 14);		//[OPRC_NMIX]색참조(+상승, -하락)
CString strNMIX_HGPR = realCommRecvData.GetItem(0, 15);		//고가
CString strNMIX_HGPR_CLR = realCommRecvData.GetItem(0, 16);		//[NMIX_HGPR]색참조(+상승, -하락)
CString strNMIX_LWPR = realCommRecvData.GetItem(0, 17);		//저가
CString strNMIX_LWPR_CLR = realCommRecvData.GetItem(0, 18);		//[NMIX_LWPR]색참조(+상승, -하락)
CString strCNTG_VOL = realCommRecvData.GetItem(0, 19);		//체결 거래량
CString strCNTG_PRGS = realCommRecvData.GetItem(0, 20);		//체결틱추이
CString strANTC_CLS_CODE = realCommRecvData.GetItem(0, 21);		//예상지수구분코드
