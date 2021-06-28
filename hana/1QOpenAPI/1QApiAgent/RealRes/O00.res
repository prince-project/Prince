BEGIN_FUNCTION_MAP
	REAL_TYPE=34, REAL_NAME=O00, DESCRIPTION=지수옵션체결;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SHRN_ISCD, TYPE=string, SIZE=9, KEY=1, CAPTION=종목 코드, FID=1;
			 INDEX=1, ITEM=BSOP_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=실시간일자, FID=9;
			 INDEX=2, ITEM=BSOP_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=체결 시간, FID=8;
			 INDEX=3, ITEM=PRPR, TYPE=string, SIZE=18, KEY=0, CAPTION=현재가, FID=4;
			 INDEX=4, ITEM=PRPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRPR]색참조(+상승, -하락), FID=0;
			 INDEX=5, ITEM=PRDY_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=전일 대비 부호, FID=6;
			 INDEX=6, ITEM=PRDY_VRSS, TYPE=string, SIZE=18, KEY=0, CAPTION=전일 대비, FID=5;
			 INDEX=7, ITEM=PRDY_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRDY_VRSS]색참조(+상승, -하락), FID=0;
			 INDEX=8, ITEM=PRDY_CTRT, TYPE=string, SIZE=18, KEY=0, CAPTION=전일 대비율, FID=7;
			 INDEX=9, ITEM=PRDY_CTRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRDY_CTRT]색참조(+상승, -하락), FID=0;
			 INDEX=10, ITEM=CNTG_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=체결 거래량, FID=83;
			 INDEX=11, ITEM=CNTG_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[CNTG_VOL]색참조(+상승, -하락), FID=0;
			 INDEX=12, ITEM=CNTG_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=체결 구분 코드, FID=0;
			 INDEX=13, ITEM=ACML_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=누적 거래량, FID=11;
			 INDEX=14, ITEM=ACML_TR_PBMN, TYPE=string, SIZE=18, KEY=0, CAPTION=누적 거래 대금, FID=12;
			 INDEX=15, ITEM=OPRC, TYPE=string, SIZE=18, KEY=0, CAPTION=시가, FID=13;
			 INDEX=16, ITEM=OPRC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPRC]색참조(+상승, -하락), FID=0;
			 INDEX=17, ITEM=HGPR, TYPE=string, SIZE=18, KEY=0, CAPTION=고가, FID=14;
			 INDEX=18, ITEM=HGPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[HGPR]색참조(+상승, -하락), FID=0;
			 INDEX=19, ITEM=LWPR, TYPE=string, SIZE=18, KEY=0, CAPTION=저가, FID=15;
			 INDEX=20, ITEM=LWPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LWPR]색참조(+상승, -하락), FID=0;
			 INDEX=21, ITEM=ASKP1, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가1, FID=29;
			 INDEX=22, ITEM=ASKP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP1]색참조(+상승, -하락), FID=0;
			 INDEX=23, ITEM=BIDP1, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가1, FID=39;
			 INDEX=24, ITEM=BIDP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP1]색참조(+상승, -하락), FID=0;
			 INDEX=25, ITEM=OTST_STPL_QTY, TYPE=string, SIZE=18, KEY=0, CAPTION=미결제 약정 수량, FID=125;
			 INDEX=26, ITEM=DELTA, TYPE=string, SIZE=18, KEY=0, CAPTION=델타, FID=301;
			 INDEX=27, ITEM=GAMA, TYPE=string, SIZE=18, KEY=0, CAPTION=감마, FID=302;
			 INDEX=28, ITEM=VEGA, TYPE=string, SIZE=18, KEY=0, CAPTION=베가, FID=304;
			 INDEX=29, ITEM=THETA, TYPE=string, SIZE=18, KEY=0, CAPTION=세타, FID=303;
			 INDEX=30, ITEM=RHO, TYPE=string, SIZE=18, KEY=0, CAPTION=로, FID=305;
			 INDEX=31, ITEM=THPR, TYPE=string, SIZE=18, KEY=0, CAPTION=이론가, FID=264;
			 INDEX=32, ITEM=INTS_VLTL_PRPR, TYPE=string, SIZE=18, KEY=0, CAPTION=내재변동성_현재가, FID=0;
			 INDEX=33, ITEM=INTS_VLTL_ASKP, TYPE=string, SIZE=18, KEY=0, CAPTION=내재변동성_매도호가, FID=0;
			 INDEX=34, ITEM=INTS_VLTL_BIDP, TYPE=string, SIZE=18, KEY=0, CAPTION=내재변동성_매수호가, FID=0;
			 INDEX=35, ITEM=OTST_STPL_QTY_ICDC, TYPE=string, SIZE=12, KEY=0, CAPTION=미결제 약정 수량 증감, FID=0;
			 INDEX=36, ITEM=OTST_STPL_QTY_ICDC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OTST_STPL_QTY_ICDC]색참조(+상승, -하락), FID=0;
			 INDEX=37, ITEM=DYNMC_UPLMTPRC, TYPE=string, SIZE=18, KEY=0, CAPTION=실시간상한가, FID=2300;
			 INDEX=38, ITEM=DYNMC_LWLMTPRC, TYPE=string, SIZE=18, KEY=0, CAPTION=실시간하한, FID=2301;
			 INDEX=39, ITEM=ANTC_NMIX_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=예상지수구분코드, FID=0;
			 INDEX=40, ITEM=OTST_STPL_QTY_REF_IC, TYPE=string, SIZE=12, KEY=0, CAPTION=미결제약정수량직전증감, FID=0;
			 INDEX=41, ITEM=OTST_STPL_QTY_REF_IC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OTST_STPL_QTY_REF_IC]색참조(+상승, -하락), FID=0;
			 INDEX=42, ITEM=INTS_WRTH, TYPE=string, SIZE=18, KEY=0, CAPTION=내재가치, FID=500;
			 INDEX=43, ITEM=TIME_WRTH, TYPE=string, SIZE=18, KEY=0, CAPTION=시간가치, FID=803;
			 INDEX=44, ITEM=ESDG, TYPE=string, SIZE=10, KEY=0, CAPTION=괴리도, FID=271;
			 INDEX=45, ITEM=ESDG_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ESDG]색참조(+상승, -하락), FID=0;
			 INDEX=46, ITEM=DPRT, TYPE=string, SIZE=10, KEY=0, CAPTION=괴리율, FID=265;
			 INDEX=47, ITEM=DPRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[DPRT]색참조(+상승, -하락), FID=0;
			 INDEX=48, ITEM=CNTG_PRGS, TYPE=string, SIZE=10, KEY=0, CAPTION=체결틱추이, FID=2655;
			 INDEX=49, ITEM=ASPR_RAISE_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=호가상향부호, FID=0;
			 INDEX=50, ITEM=RGBF_ANTC_SDPR, TYPE=string, SIZE=18, KEY=0, CAPTION=전예상기준가, FID=0;
			 INDEX=51, ITEM=RGBF_ANTC_SDPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RGBF_ANTC_SDPR]색참조(+상승, -하락), FID=0;
			 INDEX=52, ITEM=RGBF_ANTC_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=직전예상대비부호, FID=2928;
			 INDEX=53, ITEM=RGBF_ANTC_VRSS, TYPE=string, SIZE=18, KEY=0, CAPTION=직전예상대비, FID=2926;
			 INDEX=54, ITEM=RGBF_ANTC_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RGBF_ANTC_VRSS]색참조(+상승, -하락), FID=0;
			 INDEX=55, ITEM=RGBF_ANTC_CTRT, TYPE=string, SIZE=18, KEY=0, CAPTION=직전예상대비율, FID=2627;
			 INDEX=56, ITEM=RGBF_ANTC_CTRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RGBF_ANTC_CTRT]색참조(+상승, -하락), FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strSHRN_ISCD = m_CommAgent.GetRealOutputData("O00", "SHRN_ISCD");		//종목 코드
CString strBSOP_DATE = m_CommAgent.GetRealOutputData("O00", "BSOP_DATE");		//실시간일자
CString strBSOP_HOUR = m_CommAgent.GetRealOutputData("O00", "BSOP_HOUR");		//체결 시간
CString strPRPR = m_CommAgent.GetRealOutputData("O00", "PRPR");		//현재가
CString strPRPR_CLR = m_CommAgent.GetRealOutputData("O00", "PRPR_CLR");		//[PRPR]색참조(+상승, -하락)
CString strPRDY_VRSS_SIGN = m_CommAgent.GetRealOutputData("O00", "PRDY_VRSS_SIGN");		//전일 대비 부호
CString strPRDY_VRSS = m_CommAgent.GetRealOutputData("O00", "PRDY_VRSS");		//전일 대비
CString strPRDY_VRSS_CLR = m_CommAgent.GetRealOutputData("O00", "PRDY_VRSS_CLR");		//[PRDY_VRSS]색참조(+상승, -하락)
CString strPRDY_CTRT = m_CommAgent.GetRealOutputData("O00", "PRDY_CTRT");		//전일 대비율
CString strPRDY_CTRT_CLR = m_CommAgent.GetRealOutputData("O00", "PRDY_CTRT_CLR");		//[PRDY_CTRT]색참조(+상승, -하락)
CString strCNTG_VOL = m_CommAgent.GetRealOutputData("O00", "CNTG_VOL");		//체결 거래량
CString strCNTG_VOL_CLR = m_CommAgent.GetRealOutputData("O00", "CNTG_VOL_CLR");		//[CNTG_VOL]색참조(+상승, -하락)
CString strCNTG_CLS_CODE = m_CommAgent.GetRealOutputData("O00", "CNTG_CLS_CODE");		//체결 구분 코드
CString strACML_VOL = m_CommAgent.GetRealOutputData("O00", "ACML_VOL");		//누적 거래량
CString strACML_TR_PBMN = m_CommAgent.GetRealOutputData("O00", "ACML_TR_PBMN");		//누적 거래 대금
CString strOPRC = m_CommAgent.GetRealOutputData("O00", "OPRC");		//시가
CString strOPRC_CLR = m_CommAgent.GetRealOutputData("O00", "OPRC_CLR");		//[OPRC]색참조(+상승, -하락)
CString strHGPR = m_CommAgent.GetRealOutputData("O00", "HGPR");		//고가
CString strHGPR_CLR = m_CommAgent.GetRealOutputData("O00", "HGPR_CLR");		//[HGPR]색참조(+상승, -하락)
CString strLWPR = m_CommAgent.GetRealOutputData("O00", "LWPR");		//저가
CString strLWPR_CLR = m_CommAgent.GetRealOutputData("O00", "LWPR_CLR");		//[LWPR]색참조(+상승, -하락)
CString strASKP1 = m_CommAgent.GetRealOutputData("O00", "ASKP1");		//매도호가1
CString strASKP1_CLR = m_CommAgent.GetRealOutputData("O00", "ASKP1_CLR");		//[ASKP1]색참조(+상승, -하락)
CString strBIDP1 = m_CommAgent.GetRealOutputData("O00", "BIDP1");		//매수호가1
CString strBIDP1_CLR = m_CommAgent.GetRealOutputData("O00", "BIDP1_CLR");		//[BIDP1]색참조(+상승, -하락)
CString strOTST_STPL_QTY = m_CommAgent.GetRealOutputData("O00", "OTST_STPL_QTY");		//미결제 약정 수량
CString strDELTA = m_CommAgent.GetRealOutputData("O00", "DELTA");		//델타
CString strGAMA = m_CommAgent.GetRealOutputData("O00", "GAMA");		//감마
CString strVEGA = m_CommAgent.GetRealOutputData("O00", "VEGA");		//베가
CString strTHETA = m_CommAgent.GetRealOutputData("O00", "THETA");		//세타
CString strRHO = m_CommAgent.GetRealOutputData("O00", "RHO");		//로
CString strTHPR = m_CommAgent.GetRealOutputData("O00", "THPR");		//이론가
CString strINTS_VLTL_PRPR = m_CommAgent.GetRealOutputData("O00", "INTS_VLTL_PRPR");		//내재변동성_현재가
CString strINTS_VLTL_ASKP = m_CommAgent.GetRealOutputData("O00", "INTS_VLTL_ASKP");		//내재변동성_매도호가
CString strINTS_VLTL_BIDP = m_CommAgent.GetRealOutputData("O00", "INTS_VLTL_BIDP");		//내재변동성_매수호가
CString strOTST_STPL_QTY_ICDC = m_CommAgent.GetRealOutputData("O00", "OTST_STPL_QTY_ICDC");		//미결제 약정 수량 증감
CString strOTST_STPL_QTY_ICDC_CLR = m_CommAgent.GetRealOutputData("O00", "OTST_STPL_QTY_ICDC_CLR");		//[OTST_STPL_QTY_ICDC]색참조(+상승, -하락)
CString strDYNMC_UPLMTPRC = m_CommAgent.GetRealOutputData("O00", "DYNMC_UPLMTPRC");		//실시간상한가
CString strDYNMC_LWLMTPRC = m_CommAgent.GetRealOutputData("O00", "DYNMC_LWLMTPRC");		//실시간하한
CString strANTC_NMIX_CLS_CODE = m_CommAgent.GetRealOutputData("O00", "ANTC_NMIX_CLS_CODE");		//예상지수구분코드
CString strOTST_STPL_QTY_REF_IC = m_CommAgent.GetRealOutputData("O00", "OTST_STPL_QTY_REF_IC");		//미결제약정수량직전증감
CString strOTST_STPL_QTY_REF_IC_CLR = m_CommAgent.GetRealOutputData("O00", "OTST_STPL_QTY_REF_IC_CLR");		//[OTST_STPL_QTY_REF_IC]색참조(+상승, -하락)
CString strINTS_WRTH = m_CommAgent.GetRealOutputData("O00", "INTS_WRTH");		//내재가치
CString strTIME_WRTH = m_CommAgent.GetRealOutputData("O00", "TIME_WRTH");		//시간가치
CString strESDG = m_CommAgent.GetRealOutputData("O00", "ESDG");		//괴리도
CString strESDG_CLR = m_CommAgent.GetRealOutputData("O00", "ESDG_CLR");		//[ESDG]색참조(+상승, -하락)
CString strDPRT = m_CommAgent.GetRealOutputData("O00", "DPRT");		//괴리율
CString strDPRT_CLR = m_CommAgent.GetRealOutputData("O00", "DPRT_CLR");		//[DPRT]색참조(+상승, -하락)
CString strCNTG_PRGS = m_CommAgent.GetRealOutputData("O00", "CNTG_PRGS");		//체결틱추이
CString strASPR_RAISE_SIGN = m_CommAgent.GetRealOutputData("O00", "ASPR_RAISE_SIGN");		//호가상향부호
CString strRGBF_ANTC_SDPR = m_CommAgent.GetRealOutputData("O00", "RGBF_ANTC_SDPR");		//전예상기준가
CString strRGBF_ANTC_SDPR_CLR = m_CommAgent.GetRealOutputData("O00", "RGBF_ANTC_SDPR_CLR");		//[RGBF_ANTC_SDPR]색참조(+상승, -하락)
CString strRGBF_ANTC_VRSS_SIGN = m_CommAgent.GetRealOutputData("O00", "RGBF_ANTC_VRSS_SIGN");		//직전예상대비부호
CString strRGBF_ANTC_VRSS = m_CommAgent.GetRealOutputData("O00", "RGBF_ANTC_VRSS");		//직전예상대비
CString strRGBF_ANTC_VRSS_CLR = m_CommAgent.GetRealOutputData("O00", "RGBF_ANTC_VRSS_CLR");		//[RGBF_ANTC_VRSS]색참조(+상승, -하락)
CString strRGBF_ANTC_CTRT = m_CommAgent.GetRealOutputData("O00", "RGBF_ANTC_CTRT");		//직전예상대비율
CString strRGBF_ANTC_CTRT_CLR = m_CommAgent.GetRealOutputData("O00", "RGBF_ANTC_CTRT_CLR");		//[RGBF_ANTC_CTRT]색참조(+상승, -하락)




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strSHRN_ISCD = realCommRecvData.GetItem(0, 0);		//종목 코드
CString strBSOP_DATE = realCommRecvData.GetItem(0, 1);		//실시간일자
CString strBSOP_HOUR = realCommRecvData.GetItem(0, 2);		//체결 시간
CString strPRPR = realCommRecvData.GetItem(0, 3);		//현재가
CString strPRPR_CLR = realCommRecvData.GetItem(0, 4);		//[PRPR]색참조(+상승, -하락)
CString strPRDY_VRSS_SIGN = realCommRecvData.GetItem(0, 5);		//전일 대비 부호
CString strPRDY_VRSS = realCommRecvData.GetItem(0, 6);		//전일 대비
CString strPRDY_VRSS_CLR = realCommRecvData.GetItem(0, 7);		//[PRDY_VRSS]색참조(+상승, -하락)
CString strPRDY_CTRT = realCommRecvData.GetItem(0, 8);		//전일 대비율
CString strPRDY_CTRT_CLR = realCommRecvData.GetItem(0, 9);		//[PRDY_CTRT]색참조(+상승, -하락)
CString strCNTG_VOL = realCommRecvData.GetItem(0, 10);		//체결 거래량
CString strCNTG_VOL_CLR = realCommRecvData.GetItem(0, 11);		//[CNTG_VOL]색참조(+상승, -하락)
CString strCNTG_CLS_CODE = realCommRecvData.GetItem(0, 12);		//체결 구분 코드
CString strACML_VOL = realCommRecvData.GetItem(0, 13);		//누적 거래량
CString strACML_TR_PBMN = realCommRecvData.GetItem(0, 14);		//누적 거래 대금
CString strOPRC = realCommRecvData.GetItem(0, 15);		//시가
CString strOPRC_CLR = realCommRecvData.GetItem(0, 16);		//[OPRC]색참조(+상승, -하락)
CString strHGPR = realCommRecvData.GetItem(0, 17);		//고가
CString strHGPR_CLR = realCommRecvData.GetItem(0, 18);		//[HGPR]색참조(+상승, -하락)
CString strLWPR = realCommRecvData.GetItem(0, 19);		//저가
CString strLWPR_CLR = realCommRecvData.GetItem(0, 20);		//[LWPR]색참조(+상승, -하락)
CString strASKP1 = realCommRecvData.GetItem(0, 21);		//매도호가1
CString strASKP1_CLR = realCommRecvData.GetItem(0, 22);		//[ASKP1]색참조(+상승, -하락)
CString strBIDP1 = realCommRecvData.GetItem(0, 23);		//매수호가1
CString strBIDP1_CLR = realCommRecvData.GetItem(0, 24);		//[BIDP1]색참조(+상승, -하락)
CString strOTST_STPL_QTY = realCommRecvData.GetItem(0, 25);		//미결제 약정 수량
CString strDELTA = realCommRecvData.GetItem(0, 26);		//델타
CString strGAMA = realCommRecvData.GetItem(0, 27);		//감마
CString strVEGA = realCommRecvData.GetItem(0, 28);		//베가
CString strTHETA = realCommRecvData.GetItem(0, 29);		//세타
CString strRHO = realCommRecvData.GetItem(0, 30);		//로
CString strTHPR = realCommRecvData.GetItem(0, 31);		//이론가
CString strINTS_VLTL_PRPR = realCommRecvData.GetItem(0, 32);		//내재변동성_현재가
CString strINTS_VLTL_ASKP = realCommRecvData.GetItem(0, 33);		//내재변동성_매도호가
CString strINTS_VLTL_BIDP = realCommRecvData.GetItem(0, 34);		//내재변동성_매수호가
CString strOTST_STPL_QTY_ICDC = realCommRecvData.GetItem(0, 35);		//미결제 약정 수량 증감
CString strOTST_STPL_QTY_ICDC_CLR = realCommRecvData.GetItem(0, 36);		//[OTST_STPL_QTY_ICDC]색참조(+상승, -하락)
CString strDYNMC_UPLMTPRC = realCommRecvData.GetItem(0, 37);		//실시간상한가
CString strDYNMC_LWLMTPRC = realCommRecvData.GetItem(0, 38);		//실시간하한
CString strANTC_NMIX_CLS_CODE = realCommRecvData.GetItem(0, 39);		//예상지수구분코드
CString strOTST_STPL_QTY_REF_IC = realCommRecvData.GetItem(0, 40);		//미결제약정수량직전증감
CString strOTST_STPL_QTY_REF_IC_CLR = realCommRecvData.GetItem(0, 41);		//[OTST_STPL_QTY_REF_IC]색참조(+상승, -하락)
CString strINTS_WRTH = realCommRecvData.GetItem(0, 42);		//내재가치
CString strTIME_WRTH = realCommRecvData.GetItem(0, 43);		//시간가치
CString strESDG = realCommRecvData.GetItem(0, 44);		//괴리도
CString strESDG_CLR = realCommRecvData.GetItem(0, 45);		//[ESDG]색참조(+상승, -하락)
CString strDPRT = realCommRecvData.GetItem(0, 46);		//괴리율
CString strDPRT_CLR = realCommRecvData.GetItem(0, 47);		//[DPRT]색참조(+상승, -하락)
CString strCNTG_PRGS = realCommRecvData.GetItem(0, 48);		//체결틱추이
CString strASPR_RAISE_SIGN = realCommRecvData.GetItem(0, 49);		//호가상향부호
CString strRGBF_ANTC_SDPR = realCommRecvData.GetItem(0, 50);		//전예상기준가
CString strRGBF_ANTC_SDPR_CLR = realCommRecvData.GetItem(0, 51);		//[RGBF_ANTC_SDPR]색참조(+상승, -하락)
CString strRGBF_ANTC_VRSS_SIGN = realCommRecvData.GetItem(0, 52);		//직전예상대비부호
CString strRGBF_ANTC_VRSS = realCommRecvData.GetItem(0, 53);		//직전예상대비
CString strRGBF_ANTC_VRSS_CLR = realCommRecvData.GetItem(0, 54);		//[RGBF_ANTC_VRSS]색참조(+상승, -하락)
CString strRGBF_ANTC_CTRT = realCommRecvData.GetItem(0, 55);		//직전예상대비율
CString strRGBF_ANTC_CTRT_CLR = realCommRecvData.GetItem(0, 56);		//[RGBF_ANTC_CTRT]색참조(+상승, -하락)
