BEGIN_FUNCTION_MAP
	REAL_TYPE=20, REAL_NAME=S00, DESCRIPTION=주식체결;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SHRN_ISCD, TYPE=string, SIZE=9, KEY=1, CAPTION=종목코드, FID=0;
			 INDEX=1, ITEM=BSOP_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=실시간일자, FID=0;
			 INDEX=2, ITEM=STCK_CNTG_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=체결시간, FID=0;
			 INDEX=3, ITEM=HOUR_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=시간구분코드, FID=0;
			 INDEX=4, ITEM=ANTC_NMIX_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=예상지수구분코드, FID=0;
			 INDEX=5, ITEM=STCK_PRPR, TYPE=string, SIZE=12, KEY=0, CAPTION=현재가, FID=4;
			 INDEX=6, ITEM=STCK_PRPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[STCK_PRPR]색참조(+상승, -하락), FID=0;
			 INDEX=7, ITEM=PRDY_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=전일대비부호, FID=6;
			 INDEX=8, ITEM=PRDY_VRSS, TYPE=string, SIZE=12, KEY=0, CAPTION=전일대비, FID=5;
			 INDEX=9, ITEM=PRDY_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRDY_VRSS]색참조(+상승, -하락), FID=0;
			 INDEX=10, ITEM=PRDY_CTRT, TYPE=string, SIZE=18, KEY=0, CAPTION=전일대비율, FID=7;
			 INDEX=11, ITEM=PRDY_CTRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRDY_CTRT]색참조(+상승, -하락), FID=0;
			 INDEX=12, ITEM=STCK_OPRC, TYPE=string, SIZE=12, KEY=0, CAPTION=시가, FID=13;
			 INDEX=13, ITEM=STCK_OPRC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[STCK_OPRC]색참조(+상승, -하락), FID=0;
			 INDEX=14, ITEM=STCK_HGPR, TYPE=string, SIZE=12, KEY=0, CAPTION=고가, FID=14;
			 INDEX=15, ITEM=STCK_HGPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[STCK_HGPR]색참조(+상승, -하락), FID=0;
			 INDEX=16, ITEM=STCK_LWPR, TYPE=string, SIZE=12, KEY=0, CAPTION=저가, FID=15;
			 INDEX=17, ITEM=STCK_LWPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[STCK_LWPR]색참조(+상승, -하락), FID=0;
			 INDEX=18, ITEM=STCK_SDPR, TYPE=string, SIZE=12, KEY=0, CAPTION=기준가, FID=16;
			 INDEX=19, ITEM=STCK_MXPR, TYPE=string, SIZE=12, KEY=0, CAPTION=상한가, FID=17;
			 INDEX=20, ITEM=STCK_MXPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[STCK_MXPR]색참조(+상승, -하락), FID=0;
			 INDEX=21, ITEM=STCK_LLAM, TYPE=string, SIZE=12, KEY=0, CAPTION=하한가, FID=18;
			 INDEX=22, ITEM=STCK_LLAM_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[STCK_LLAM]색참조(+상승, -하락), FID=0;
			 INDEX=23, ITEM=CNTG_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=체결구분코드, FID=0;
			 INDEX=24, ITEM=CNTG_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=체결거래량, FID=83;
			 INDEX=25, ITEM=CNTG_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[CNTG_VOL]색참조(+상승, -하락), FID=0;
			 INDEX=26, ITEM=ACML_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=누적거래량, FID=11;
			 INDEX=27, ITEM=ACML_TR_PBMN, TYPE=string, SIZE=18, KEY=0, CAPTION=누적거래대금, FID=12;
			 INDEX=28, ITEM=ASKP1, TYPE=string, SIZE=12, KEY=0, CAPTION=매도호가, FID=29;
			 INDEX=29, ITEM=ASKP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP1]색참조(+상승, -하락), FID=0;
			 INDEX=30, ITEM=BIDP1, TYPE=string, SIZE=12, KEY=0, CAPTION=매수호가, FID=39;
			 INDEX=31, ITEM=BIDP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP1]색참조(+상승, -하락), FID=0;
			 INDEX=32, ITEM=ASKP_RSQN1, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가잔량, FID=63;
			 INDEX=33, ITEM=BIDP_RSQN1, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가잔량, FID=73;
			 INDEX=34, ITEM=TOTAL_ASKP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=총매도호가잔량, FID=171;
			 INDEX=35, ITEM=TOTAL_BIDP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=총매수호가잔량, FID=172;
			 INDEX=36, ITEM=TRHT_YN, TYPE=string, SIZE=1, KEY=0, CAPTION=거래정지 여부, FID=0;
			 INDEX=37, ITEM=MANG_ISSU_YN, TYPE=string, SIZE=1, KEY=0, CAPTION=관리종목 여부, FID=0;
			 INDEX=38, ITEM=PRST_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=우선주 구분 코드, FID=0;
			 INDEX=39, ITEM=WARN_YN, TYPE=string, SIZE=1, KEY=0, CAPTION=투자주의 여부, FID=0;
			 INDEX=40, ITEM=NEW_MKOP_CLS_CODE, TYPE=string, SIZE=2, KEY=0, CAPTION=신장운영구분코드, FID=879;
			 INDEX=41, ITEM=RGBF_CNTG_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=직전체결구분코드, FID=0;
			 INDEX=42, ITEM=RLTV, TYPE=string, SIZE=18, KEY=0, CAPTION=체결강도, FID=0;
			 INDEX=43, ITEM=RLTV_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RLTV]색참조(+상승, -하락), FID=0;
			 INDEX=44, ITEM=SELN_CNTG_CSNU, TYPE=string, SIZE=12, KEY=0, CAPTION=매도체결건수, FID=0;
			 INDEX=45, ITEM=SHNU_CNTG_CSNU, TYPE=string, SIZE=12, KEY=0, CAPTION=매수체결건수, FID=0;
			 INDEX=46, ITEM=WGHN_AVRG_PRPR, TYPE=string, SIZE=12, KEY=0, CAPTION=가중평균가격, FID=0;
			 INDEX=47, ITEM=SELN_CNTG_SMTN, TYPE=string, SIZE=18, KEY=0, CAPTION=매도체결합계, FID=0;
			 INDEX=48, ITEM=SHNU_CNTG_SMTN, TYPE=string, SIZE=18, KEY=0, CAPTION=매수체결합계, FID=0;
			 INDEX=49, ITEM=CNTG_PRGS, TYPE=string, SIZE=10, KEY=0, CAPTION=체결틱추이, FID=0;
			 INDEX=50, ITEM=RGBF_ANTC_SDPR, TYPE=string, SIZE=12, KEY=0, CAPTION=직전예상기준가(현재가), FID=0;
			 INDEX=51, ITEM=RGBF_ANTC_SDPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RGBF_ANTC_SDPR]색참조(+상승, -하락), FID=0;
			 INDEX=52, ITEM=RGBF_ANTC_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=직전예상부호, FID=0;
			 INDEX=53, ITEM=RGBF_ANTC_VRSS, TYPE=string, SIZE=12, KEY=0, CAPTION=직전예상대비, FID=0;
			 INDEX=54, ITEM=RGBF_ANTC_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RGBF_ANTC_VRSS]색참조(+상승, -하락), FID=0;
			 INDEX=55, ITEM=RGBF_ANTC_CTRT, TYPE=string, SIZE=18, KEY=0, CAPTION=직전예상대비율, FID=0;
			 INDEX=56, ITEM=RGBF_ANTC_CTRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RGBF_ANTC_CTRT]색참조(+상승, -하락), FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strSHRN_ISCD = m_CommAgent.GetRealOutputData("S00", "SHRN_ISCD");		//종목코드
CString strBSOP_DATE = m_CommAgent.GetRealOutputData("S00", "BSOP_DATE");		//실시간일자
CString strSTCK_CNTG_HOUR = m_CommAgent.GetRealOutputData("S00", "STCK_CNTG_HOUR");		//체결시간
CString strHOUR_CLS_CODE = m_CommAgent.GetRealOutputData("S00", "HOUR_CLS_CODE");		//시간구분코드
CString strANTC_NMIX_CLS_CODE = m_CommAgent.GetRealOutputData("S00", "ANTC_NMIX_CLS_CODE");		//예상지수구분코드
CString strSTCK_PRPR = m_CommAgent.GetRealOutputData("S00", "STCK_PRPR");		//현재가
CString strSTCK_PRPR_CLR = m_CommAgent.GetRealOutputData("S00", "STCK_PRPR_CLR");		//[STCK_PRPR]색참조(+상승, -하락)
CString strPRDY_VRSS_SIGN = m_CommAgent.GetRealOutputData("S00", "PRDY_VRSS_SIGN");		//전일대비부호
CString strPRDY_VRSS = m_CommAgent.GetRealOutputData("S00", "PRDY_VRSS");		//전일대비
CString strPRDY_VRSS_CLR = m_CommAgent.GetRealOutputData("S00", "PRDY_VRSS_CLR");		//[PRDY_VRSS]색참조(+상승, -하락)
CString strPRDY_CTRT = m_CommAgent.GetRealOutputData("S00", "PRDY_CTRT");		//전일대비율
CString strPRDY_CTRT_CLR = m_CommAgent.GetRealOutputData("S00", "PRDY_CTRT_CLR");		//[PRDY_CTRT]색참조(+상승, -하락)
CString strSTCK_OPRC = m_CommAgent.GetRealOutputData("S00", "STCK_OPRC");		//시가
CString strSTCK_OPRC_CLR = m_CommAgent.GetRealOutputData("S00", "STCK_OPRC_CLR");		//[STCK_OPRC]색참조(+상승, -하락)
CString strSTCK_HGPR = m_CommAgent.GetRealOutputData("S00", "STCK_HGPR");		//고가
CString strSTCK_HGPR_CLR = m_CommAgent.GetRealOutputData("S00", "STCK_HGPR_CLR");		//[STCK_HGPR]색참조(+상승, -하락)
CString strSTCK_LWPR = m_CommAgent.GetRealOutputData("S00", "STCK_LWPR");		//저가
CString strSTCK_LWPR_CLR = m_CommAgent.GetRealOutputData("S00", "STCK_LWPR_CLR");		//[STCK_LWPR]색참조(+상승, -하락)
CString strSTCK_SDPR = m_CommAgent.GetRealOutputData("S00", "STCK_SDPR");		//기준가
CString strSTCK_MXPR = m_CommAgent.GetRealOutputData("S00", "STCK_MXPR");		//상한가
CString strSTCK_MXPR_CLR = m_CommAgent.GetRealOutputData("S00", "STCK_MXPR_CLR");		//[STCK_MXPR]색참조(+상승, -하락)
CString strSTCK_LLAM = m_CommAgent.GetRealOutputData("S00", "STCK_LLAM");		//하한가
CString strSTCK_LLAM_CLR = m_CommAgent.GetRealOutputData("S00", "STCK_LLAM_CLR");		//[STCK_LLAM]색참조(+상승, -하락)
CString strCNTG_CLS_CODE = m_CommAgent.GetRealOutputData("S00", "CNTG_CLS_CODE");		//체결구분코드
CString strCNTG_VOL = m_CommAgent.GetRealOutputData("S00", "CNTG_VOL");		//체결거래량
CString strCNTG_VOL_CLR = m_CommAgent.GetRealOutputData("S00", "CNTG_VOL_CLR");		//[CNTG_VOL]색참조(+상승, -하락)
CString strACML_VOL = m_CommAgent.GetRealOutputData("S00", "ACML_VOL");		//누적거래량
CString strACML_TR_PBMN = m_CommAgent.GetRealOutputData("S00", "ACML_TR_PBMN");		//누적거래대금
CString strASKP1 = m_CommAgent.GetRealOutputData("S00", "ASKP1");		//매도호가
CString strASKP1_CLR = m_CommAgent.GetRealOutputData("S00", "ASKP1_CLR");		//[ASKP1]색참조(+상승, -하락)
CString strBIDP1 = m_CommAgent.GetRealOutputData("S00", "BIDP1");		//매수호가
CString strBIDP1_CLR = m_CommAgent.GetRealOutputData("S00", "BIDP1_CLR");		//[BIDP1]색참조(+상승, -하락)
CString strASKP_RSQN1 = m_CommAgent.GetRealOutputData("S00", "ASKP_RSQN1");		//매도호가잔량
CString strBIDP_RSQN1 = m_CommAgent.GetRealOutputData("S00", "BIDP_RSQN1");		//매수호가잔량
CString strTOTAL_ASKP_RSQN = m_CommAgent.GetRealOutputData("S00", "TOTAL_ASKP_RSQN");		//총매도호가잔량
CString strTOTAL_BIDP_RSQN = m_CommAgent.GetRealOutputData("S00", "TOTAL_BIDP_RSQN");		//총매수호가잔량
CString strTRHT_YN = m_CommAgent.GetRealOutputData("S00", "TRHT_YN");		//거래정지 여부
CString strMANG_ISSU_YN = m_CommAgent.GetRealOutputData("S00", "MANG_ISSU_YN");		//관리종목 여부
CString strPRST_CLS_CODE = m_CommAgent.GetRealOutputData("S00", "PRST_CLS_CODE");		//우선주 구분 코드
CString strWARN_YN = m_CommAgent.GetRealOutputData("S00", "WARN_YN");		//투자주의 여부
CString strNEW_MKOP_CLS_CODE = m_CommAgent.GetRealOutputData("S00", "NEW_MKOP_CLS_CODE");		//신장운영구분코드
CString strRGBF_CNTG_CLS_CODE = m_CommAgent.GetRealOutputData("S00", "RGBF_CNTG_CLS_CODE");		//직전체결구분코드
CString strRLTV = m_CommAgent.GetRealOutputData("S00", "RLTV");		//체결강도
CString strRLTV_CLR = m_CommAgent.GetRealOutputData("S00", "RLTV_CLR");		//[RLTV]색참조(+상승, -하락)
CString strSELN_CNTG_CSNU = m_CommAgent.GetRealOutputData("S00", "SELN_CNTG_CSNU");		//매도체결건수
CString strSHNU_CNTG_CSNU = m_CommAgent.GetRealOutputData("S00", "SHNU_CNTG_CSNU");		//매수체결건수
CString strWGHN_AVRG_PRPR = m_CommAgent.GetRealOutputData("S00", "WGHN_AVRG_PRPR");		//가중평균가격
CString strSELN_CNTG_SMTN = m_CommAgent.GetRealOutputData("S00", "SELN_CNTG_SMTN");		//매도체결합계
CString strSHNU_CNTG_SMTN = m_CommAgent.GetRealOutputData("S00", "SHNU_CNTG_SMTN");		//매수체결합계
CString strCNTG_PRGS = m_CommAgent.GetRealOutputData("S00", "CNTG_PRGS");		//체결틱추이
CString strRGBF_ANTC_SDPR = m_CommAgent.GetRealOutputData("S00", "RGBF_ANTC_SDPR");		//직전예상기준가(현재가)
CString strRGBF_ANTC_SDPR_CLR = m_CommAgent.GetRealOutputData("S00", "RGBF_ANTC_SDPR_CLR");		//[RGBF_ANTC_SDPR]색참조(+상승, -하락)
CString strRGBF_ANTC_VRSS_SIGN = m_CommAgent.GetRealOutputData("S00", "RGBF_ANTC_VRSS_SIGN");		//직전예상부호
CString strRGBF_ANTC_VRSS = m_CommAgent.GetRealOutputData("S00", "RGBF_ANTC_VRSS");		//직전예상대비
CString strRGBF_ANTC_VRSS_CLR = m_CommAgent.GetRealOutputData("S00", "RGBF_ANTC_VRSS_CLR");		//[RGBF_ANTC_VRSS]색참조(+상승, -하락)
CString strRGBF_ANTC_CTRT = m_CommAgent.GetRealOutputData("S00", "RGBF_ANTC_CTRT");		//직전예상대비율
CString strRGBF_ANTC_CTRT_CLR = m_CommAgent.GetRealOutputData("S00", "RGBF_ANTC_CTRT_CLR");		//[RGBF_ANTC_CTRT]색참조(+상승, -하락)




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strSHRN_ISCD = realCommRecvData.GetItem(0, 0);		//종목코드
CString strBSOP_DATE = realCommRecvData.GetItem(0, 1);		//실시간일자
CString strSTCK_CNTG_HOUR = realCommRecvData.GetItem(0, 2);		//체결시간
CString strHOUR_CLS_CODE = realCommRecvData.GetItem(0, 3);		//시간구분코드
CString strANTC_NMIX_CLS_CODE = realCommRecvData.GetItem(0, 4);		//예상지수구분코드
CString strSTCK_PRPR = realCommRecvData.GetItem(0, 5);		//현재가
CString strSTCK_PRPR_CLR = realCommRecvData.GetItem(0, 6);		//[STCK_PRPR]색참조(+상승, -하락)
CString strPRDY_VRSS_SIGN = realCommRecvData.GetItem(0, 7);		//전일대비부호
CString strPRDY_VRSS = realCommRecvData.GetItem(0, 8);		//전일대비
CString strPRDY_VRSS_CLR = realCommRecvData.GetItem(0, 9);		//[PRDY_VRSS]색참조(+상승, -하락)
CString strPRDY_CTRT = realCommRecvData.GetItem(0, 10);		//전일대비율
CString strPRDY_CTRT_CLR = realCommRecvData.GetItem(0, 11);		//[PRDY_CTRT]색참조(+상승, -하락)
CString strSTCK_OPRC = realCommRecvData.GetItem(0, 12);		//시가
CString strSTCK_OPRC_CLR = realCommRecvData.GetItem(0, 13);		//[STCK_OPRC]색참조(+상승, -하락)
CString strSTCK_HGPR = realCommRecvData.GetItem(0, 14);		//고가
CString strSTCK_HGPR_CLR = realCommRecvData.GetItem(0, 15);		//[STCK_HGPR]색참조(+상승, -하락)
CString strSTCK_LWPR = realCommRecvData.GetItem(0, 16);		//저가
CString strSTCK_LWPR_CLR = realCommRecvData.GetItem(0, 17);		//[STCK_LWPR]색참조(+상승, -하락)
CString strSTCK_SDPR = realCommRecvData.GetItem(0, 18);		//기준가
CString strSTCK_MXPR = realCommRecvData.GetItem(0, 19);		//상한가
CString strSTCK_MXPR_CLR = realCommRecvData.GetItem(0, 20);		//[STCK_MXPR]색참조(+상승, -하락)
CString strSTCK_LLAM = realCommRecvData.GetItem(0, 21);		//하한가
CString strSTCK_LLAM_CLR = realCommRecvData.GetItem(0, 22);		//[STCK_LLAM]색참조(+상승, -하락)
CString strCNTG_CLS_CODE = realCommRecvData.GetItem(0, 23);		//체결구분코드
CString strCNTG_VOL = realCommRecvData.GetItem(0, 24);		//체결거래량
CString strCNTG_VOL_CLR = realCommRecvData.GetItem(0, 25);		//[CNTG_VOL]색참조(+상승, -하락)
CString strACML_VOL = realCommRecvData.GetItem(0, 26);		//누적거래량
CString strACML_TR_PBMN = realCommRecvData.GetItem(0, 27);		//누적거래대금
CString strASKP1 = realCommRecvData.GetItem(0, 28);		//매도호가
CString strASKP1_CLR = realCommRecvData.GetItem(0, 29);		//[ASKP1]색참조(+상승, -하락)
CString strBIDP1 = realCommRecvData.GetItem(0, 30);		//매수호가
CString strBIDP1_CLR = realCommRecvData.GetItem(0, 31);		//[BIDP1]색참조(+상승, -하락)
CString strASKP_RSQN1 = realCommRecvData.GetItem(0, 32);		//매도호가잔량
CString strBIDP_RSQN1 = realCommRecvData.GetItem(0, 33);		//매수호가잔량
CString strTOTAL_ASKP_RSQN = realCommRecvData.GetItem(0, 34);		//총매도호가잔량
CString strTOTAL_BIDP_RSQN = realCommRecvData.GetItem(0, 35);		//총매수호가잔량
CString strTRHT_YN = realCommRecvData.GetItem(0, 36);		//거래정지 여부
CString strMANG_ISSU_YN = realCommRecvData.GetItem(0, 37);		//관리종목 여부
CString strPRST_CLS_CODE = realCommRecvData.GetItem(0, 38);		//우선주 구분 코드
CString strWARN_YN = realCommRecvData.GetItem(0, 39);		//투자주의 여부
CString strNEW_MKOP_CLS_CODE = realCommRecvData.GetItem(0, 40);		//신장운영구분코드
CString strRGBF_CNTG_CLS_CODE = realCommRecvData.GetItem(0, 41);		//직전체결구분코드
CString strRLTV = realCommRecvData.GetItem(0, 42);		//체결강도
CString strRLTV_CLR = realCommRecvData.GetItem(0, 43);		//[RLTV]색참조(+상승, -하락)
CString strSELN_CNTG_CSNU = realCommRecvData.GetItem(0, 44);		//매도체결건수
CString strSHNU_CNTG_CSNU = realCommRecvData.GetItem(0, 45);		//매수체결건수
CString strWGHN_AVRG_PRPR = realCommRecvData.GetItem(0, 46);		//가중평균가격
CString strSELN_CNTG_SMTN = realCommRecvData.GetItem(0, 47);		//매도체결합계
CString strSHNU_CNTG_SMTN = realCommRecvData.GetItem(0, 48);		//매수체결합계
CString strCNTG_PRGS = realCommRecvData.GetItem(0, 49);		//체결틱추이
CString strRGBF_ANTC_SDPR = realCommRecvData.GetItem(0, 50);		//직전예상기준가(현재가)
CString strRGBF_ANTC_SDPR_CLR = realCommRecvData.GetItem(0, 51);		//[RGBF_ANTC_SDPR]색참조(+상승, -하락)
CString strRGBF_ANTC_VRSS_SIGN = realCommRecvData.GetItem(0, 52);		//직전예상부호
CString strRGBF_ANTC_VRSS = realCommRecvData.GetItem(0, 53);		//직전예상대비
CString strRGBF_ANTC_VRSS_CLR = realCommRecvData.GetItem(0, 54);		//[RGBF_ANTC_VRSS]색참조(+상승, -하락)
CString strRGBF_ANTC_CTRT = realCommRecvData.GetItem(0, 55);		//직전예상대비율
CString strRGBF_ANTC_CTRT_CLR = realCommRecvData.GetItem(0, 56);		//[RGBF_ANTC_CTRT]색참조(+상승, -하락)
