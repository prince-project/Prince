BEGIN_FUNCTION_MAP
	REAL_TYPE=230, REAL_NAME=FB0, DESCRIPTION=EUREX 미니코스피 200 선물 체결;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SHRN_ISCD, TYPE=string, SIZE=9, KEY=1, CAPTION=종목 코드, FID=0;
			 INDEX=1, ITEM=BSOP_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=실시간일자, FID=0;
			 INDEX=2, ITEM=BSOP_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=체결 시간, FID=0;
			 INDEX=3, ITEM=PRPR, TYPE=string, SIZE=11, KEY=0, CAPTION=현재가, FID=0;
			 INDEX=4, ITEM=PRPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRPR]색참조(+상승, -하락), FID=0;
			 INDEX=5, ITEM=PRDY_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=전일 대비 부호, FID=0;
			 INDEX=6, ITEM=PRDY_VRSS, TYPE=string, SIZE=11, KEY=0, CAPTION=전일 대비, FID=0;
			 INDEX=7, ITEM=PRDY_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRDY_VRSS]색참조(+상승, -하락), FID=0;
			 INDEX=8, ITEM=PRDY_CTRT, TYPE=string, SIZE=10, KEY=0, CAPTION=전일 대비율, FID=0;
			 INDEX=9, ITEM=PRDY_CTRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRDY_CTRT]색참조(+상승, -하락), FID=0;
			 INDEX=10, ITEM=CNTG_VOL, TYPE=string, SIZE=12, KEY=0, CAPTION=체결량, FID=0;
			 INDEX=11, ITEM=CNTG_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[CNTG_VOL]색참조(+상승, -하락), FID=0;
			 INDEX=12, ITEM=ACML_VOL, TYPE=string, SIZE=13, KEY=0, CAPTION=누적 거래량, FID=0;
			 INDEX=13, ITEM=ACML_TR_PBMN, TYPE=string, SIZE=13, KEY=0, CAPTION=누적 거래 대금, FID=0;
			 INDEX=14, ITEM=OPRC, TYPE=string, SIZE=11, KEY=0, CAPTION=시가, FID=0;
			 INDEX=15, ITEM=OPRC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPRC]색참조(+상승, -하락), FID=0;
			 INDEX=16, ITEM=HGPR, TYPE=string, SIZE=11, KEY=0, CAPTION=고가, FID=0;
			 INDEX=17, ITEM=HGPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[HGPR]색참조(+상승, -하락), FID=0;
			 INDEX=18, ITEM=LWPR, TYPE=string, SIZE=11, KEY=0, CAPTION=저가, FID=0;
			 INDEX=19, ITEM=LWPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LWPR]색참조(+상승, -하락), FID=0;
			 INDEX=20, ITEM=OPRC_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=시가 시간, FID=0;
			 INDEX=21, ITEM=OPRC_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=시가 대비 부호, FID=0;
			 INDEX=22, ITEM=OPRC_VRSS, TYPE=string, SIZE=11, KEY=0, CAPTION=시가 대비, FID=0;
			 INDEX=23, ITEM=OPRC_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPRC_VRSS]색참조(+상승, -하락), FID=0;
			 INDEX=24, ITEM=HGPR_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=고가 시간, FID=0;
			 INDEX=25, ITEM=HGPR_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=고가 대비 부호, FID=0;
			 INDEX=26, ITEM=HGPR_VRSS, TYPE=string, SIZE=11, KEY=0, CAPTION=고가 대비, FID=0;
			 INDEX=27, ITEM=HGPR_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[HGPR_VRSS]색참조(+상승, -하락), FID=0;
			 INDEX=28, ITEM=LWPR_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=저가 시간, FID=0;
			 INDEX=29, ITEM=LWPR_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=저가 대비 부호, FID=0;
			 INDEX=30, ITEM=LWPR_VRSS, TYPE=string, SIZE=11, KEY=0, CAPTION=저가 대비, FID=0;
			 INDEX=31, ITEM=LWPR_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LWPR_VRSS]색참조(+상승, -하락), FID=0;
			 INDEX=32, ITEM=NMSC_FCTN_STPL_PRC, TYPE=string, SIZE=10, KEY=0, CAPTION=근월물 의제 약정가, FID=0;
			 INDEX=33, ITEM=FMSC_FCTN_STPL_PRC, TYPE=string, SIZE=10, KEY=0, CAPTION=원월물 의제 약정가, FID=0;
			 INDEX=34, ITEM=SPEAD_PRC, TYPE=string, SIZE=9, KEY=0, CAPTION=스프레드, FID=0;
			 INDEX=35, ITEM=OTST_STPL_QTY, TYPE=string, SIZE=13, KEY=0, CAPTION=미결제 약정 수량, FID=0;
			 INDEX=36, ITEM=OTST_STPL_QTY_ICDC, TYPE=string, SIZE=14, KEY=0, CAPTION=미결제 약정 수량 증감, FID=0;
			 INDEX=37, ITEM=OTST_STPL_QTY_ICDC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OTST_STPL_QTY_ICDC]색참조(+상승, -하락), FID=0;
			 INDEX=38, ITEM=OTST_STPL_QTY_REF_IC, TYPE=string, SIZE=14, KEY=0, CAPTION=미결제 약정 직전 수량 증감, FID=0;
			 INDEX=39, ITEM=OTST_STPL_QTY_REF_IC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OTST_STPL_QTY_REF_IC]색참조(+상승, -하락), FID=0;
			 INDEX=40, ITEM=THPR, TYPE=string, SIZE=10, KEY=0, CAPTION=이론가, FID=0;
			 INDEX=41, ITEM=THPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[THPR]색참조(+상승, -하락), FID=0;
			 INDEX=42, ITEM=MRKT_BASIS, TYPE=string, SIZE=10, KEY=0, CAPTION=시장 BASIS, FID=0;
			 INDEX=43, ITEM=MRKT_BASIS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[MRKT_BASIS]색참조(+상승, -하락), FID=0;
			 INDEX=44, ITEM=THER_BASIS, TYPE=string, SIZE=10, KEY=0, CAPTION=이론 BASIS, FID=0;
			 INDEX=45, ITEM=THER_BASIS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[THER_BASIS]색참조(+상승, -하락), FID=0;
			 INDEX=46, ITEM=ESDG, TYPE=string, SIZE=10, KEY=0, CAPTION=괴리도, FID=0;
			 INDEX=47, ITEM=ESDG_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ESDG]색참조(+상승, -하락), FID=0;
			 INDEX=48, ITEM=DPRT, TYPE=string, SIZE=10, KEY=0, CAPTION=괴리율, FID=0;
			 INDEX=49, ITEM=DPRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[DPRT]색참조(+상승, -하락), FID=0;
			 INDEX=50, ITEM=SHNU_RATE, TYPE=string, SIZE=10, KEY=0, CAPTION=매수비율, FID=0;
			 INDEX=51, ITEM=SHNU_RATE_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[SHNU_RATE]색참조(+상승, -하락), FID=0;
			 INDEX=52, ITEM=CTTR, TYPE=string, SIZE=10, KEY=0, CAPTION=체결강도, FID=0;
			 INDEX=53, ITEM=CTTR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[CTTR]색참조(+상승, -하락), FID=0;
			 INDEX=54, ITEM=ASKP1, TYPE=string, SIZE=11, KEY=0, CAPTION=매도호가1, FID=0;
			 INDEX=55, ITEM=ASKP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP1]색참조(+상승, -하락), FID=0;
			 INDEX=56, ITEM=BIDP1, TYPE=string, SIZE=11, KEY=0, CAPTION=매수호가1, FID=0;
			 INDEX=57, ITEM=BIDP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP1]색참조(+상승, -하락), FID=0;
			 INDEX=58, ITEM=ASKP_RSQN1, TYPE=string, SIZE=13, KEY=0, CAPTION=매도호가 잔량, FID=0;
			 INDEX=59, ITEM=BIDP_RSQN1, TYPE=string, SIZE=13, KEY=0, CAPTION=매수호가 잔량, FID=0;
			 INDEX=60, ITEM=SELN_CNTG_CSNU, TYPE=string, SIZE=5, KEY=0, CAPTION=매도 체결 건수, FID=0;
			 INDEX=61, ITEM=SHNU_CNTG_CSNU, TYPE=string, SIZE=5, KEY=0, CAPTION=매수 체결 건수, FID=0;
			 INDEX=62, ITEM=NTBY_CNTG_CSNU, TYPE=string, SIZE=6, KEY=0, CAPTION=순매수 체결 건수, FID=0;
			 INDEX=63, ITEM=NTBY_CNTG_CSNU_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NTBY_CNTG_CSNU]색참조(+상승, -하락), FID=0;
			 INDEX=64, ITEM=SELN_CNTG_SMTN, TYPE=string, SIZE=13, KEY=0, CAPTION=매도 체결 합계, FID=0;
			 INDEX=65, ITEM=SHNU_CNTG_SMTN, TYPE=string, SIZE=13, KEY=0, CAPTION=매수 체결 합계, FID=0;
			 INDEX=66, ITEM=TOTAL_ASKP_RSQN, TYPE=string, SIZE=13, KEY=0, CAPTION=총 매도호가 잔량, FID=0;
			 INDEX=67, ITEM=TOTAL_BIDP_RSQN, TYPE=string, SIZE=13, KEY=0, CAPTION=총 매수호가 잔량, FID=0;
			 INDEX=68, ITEM=PRDY_VRSS_VOL_RATE, TYPE=string, SIZE=10, KEY=0, CAPTION=전일 대비 거래량 비율, FID=0;
			 INDEX=69, ITEM=PRDY_VRSS_VOL_RATE_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRDY_VRSS_VOL_RATE]색참조(+상승, -하락), FID=0;
			 INDEX=70, ITEM=UNAS_PRC, TYPE=string, SIZE=13, KEY=0, CAPTION=기초자산 가격, FID=0;
			 INDEX=71, ITEM=UNAS_PRC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[UNAS_PRC]색참조(+상승, -하락), FID=0;
			 INDEX=72, ITEM=UNAS_PRDY_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=기초자산 전일대비구분, FID=0;
			 INDEX=73, ITEM=UNAS_PRDY_VRSS, TYPE=string, SIZE=13, KEY=0, CAPTION=기초자산 전일 대비, FID=0;
			 INDEX=74, ITEM=UNAS_PRDY_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[UNAS_PRDY_VRSS]색참조(+상승, -하락), FID=0;
			 INDEX=75, ITEM=UNAS_PRDY_CTRT, TYPE=string, SIZE=10, KEY=0, CAPTION=기초자산 전일 대비율, FID=0;
			 INDEX=76, ITEM=UNAS_PRDY_CTRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[UNAS_PRDY_CTRT]색참조(+상승, -하락), FID=0;
			 INDEX=77, ITEM=CNTG_PRGS, TYPE=string, SIZE=10, KEY=0, CAPTION=체결틱추이, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strSHRN_ISCD = m_CommAgent.GetRealOutputData("FB0", "SHRN_ISCD");		//종목 코드
CString strBSOP_DATE = m_CommAgent.GetRealOutputData("FB0", "BSOP_DATE");		//실시간일자
CString strBSOP_HOUR = m_CommAgent.GetRealOutputData("FB0", "BSOP_HOUR");		//체결 시간
CString strPRPR = m_CommAgent.GetRealOutputData("FB0", "PRPR");		//현재가
CString strPRPR_CLR = m_CommAgent.GetRealOutputData("FB0", "PRPR_CLR");		//[PRPR]색참조(+상승, -하락)
CString strPRDY_VRSS_SIGN = m_CommAgent.GetRealOutputData("FB0", "PRDY_VRSS_SIGN");		//전일 대비 부호
CString strPRDY_VRSS = m_CommAgent.GetRealOutputData("FB0", "PRDY_VRSS");		//전일 대비
CString strPRDY_VRSS_CLR = m_CommAgent.GetRealOutputData("FB0", "PRDY_VRSS_CLR");		//[PRDY_VRSS]색참조(+상승, -하락)
CString strPRDY_CTRT = m_CommAgent.GetRealOutputData("FB0", "PRDY_CTRT");		//전일 대비율
CString strPRDY_CTRT_CLR = m_CommAgent.GetRealOutputData("FB0", "PRDY_CTRT_CLR");		//[PRDY_CTRT]색참조(+상승, -하락)
CString strCNTG_VOL = m_CommAgent.GetRealOutputData("FB0", "CNTG_VOL");		//체결량
CString strCNTG_VOL_CLR = m_CommAgent.GetRealOutputData("FB0", "CNTG_VOL_CLR");		//[CNTG_VOL]색참조(+상승, -하락)
CString strACML_VOL = m_CommAgent.GetRealOutputData("FB0", "ACML_VOL");		//누적 거래량
CString strACML_TR_PBMN = m_CommAgent.GetRealOutputData("FB0", "ACML_TR_PBMN");		//누적 거래 대금
CString strOPRC = m_CommAgent.GetRealOutputData("FB0", "OPRC");		//시가
CString strOPRC_CLR = m_CommAgent.GetRealOutputData("FB0", "OPRC_CLR");		//[OPRC]색참조(+상승, -하락)
CString strHGPR = m_CommAgent.GetRealOutputData("FB0", "HGPR");		//고가
CString strHGPR_CLR = m_CommAgent.GetRealOutputData("FB0", "HGPR_CLR");		//[HGPR]색참조(+상승, -하락)
CString strLWPR = m_CommAgent.GetRealOutputData("FB0", "LWPR");		//저가
CString strLWPR_CLR = m_CommAgent.GetRealOutputData("FB0", "LWPR_CLR");		//[LWPR]색참조(+상승, -하락)
CString strOPRC_HOUR = m_CommAgent.GetRealOutputData("FB0", "OPRC_HOUR");		//시가 시간
CString strOPRC_VRSS_SIGN = m_CommAgent.GetRealOutputData("FB0", "OPRC_VRSS_SIGN");		//시가 대비 부호
CString strOPRC_VRSS = m_CommAgent.GetRealOutputData("FB0", "OPRC_VRSS");		//시가 대비
CString strOPRC_VRSS_CLR = m_CommAgent.GetRealOutputData("FB0", "OPRC_VRSS_CLR");		//[OPRC_VRSS]색참조(+상승, -하락)
CString strHGPR_HOUR = m_CommAgent.GetRealOutputData("FB0", "HGPR_HOUR");		//고가 시간
CString strHGPR_VRSS_SIGN = m_CommAgent.GetRealOutputData("FB0", "HGPR_VRSS_SIGN");		//고가 대비 부호
CString strHGPR_VRSS = m_CommAgent.GetRealOutputData("FB0", "HGPR_VRSS");		//고가 대비
CString strHGPR_VRSS_CLR = m_CommAgent.GetRealOutputData("FB0", "HGPR_VRSS_CLR");		//[HGPR_VRSS]색참조(+상승, -하락)
CString strLWPR_HOUR = m_CommAgent.GetRealOutputData("FB0", "LWPR_HOUR");		//저가 시간
CString strLWPR_VRSS_SIGN = m_CommAgent.GetRealOutputData("FB0", "LWPR_VRSS_SIGN");		//저가 대비 부호
CString strLWPR_VRSS = m_CommAgent.GetRealOutputData("FB0", "LWPR_VRSS");		//저가 대비
CString strLWPR_VRSS_CLR = m_CommAgent.GetRealOutputData("FB0", "LWPR_VRSS_CLR");		//[LWPR_VRSS]색참조(+상승, -하락)
CString strNMSC_FCTN_STPL_PRC = m_CommAgent.GetRealOutputData("FB0", "NMSC_FCTN_STPL_PRC");		//근월물 의제 약정가
CString strFMSC_FCTN_STPL_PRC = m_CommAgent.GetRealOutputData("FB0", "FMSC_FCTN_STPL_PRC");		//원월물 의제 약정가
CString strSPEAD_PRC = m_CommAgent.GetRealOutputData("FB0", "SPEAD_PRC");		//스프레드
CString strOTST_STPL_QTY = m_CommAgent.GetRealOutputData("FB0", "OTST_STPL_QTY");		//미결제 약정 수량
CString strOTST_STPL_QTY_ICDC = m_CommAgent.GetRealOutputData("FB0", "OTST_STPL_QTY_ICDC");		//미결제 약정 수량 증감
CString strOTST_STPL_QTY_ICDC_CLR = m_CommAgent.GetRealOutputData("FB0", "OTST_STPL_QTY_ICDC_CLR");		//[OTST_STPL_QTY_ICDC]색참조(+상승, -하락)
CString strOTST_STPL_QTY_REF_IC = m_CommAgent.GetRealOutputData("FB0", "OTST_STPL_QTY_REF_IC");		//미결제 약정 직전 수량 증감
CString strOTST_STPL_QTY_REF_IC_CLR = m_CommAgent.GetRealOutputData("FB0", "OTST_STPL_QTY_REF_IC_CLR");		//[OTST_STPL_QTY_REF_IC]색참조(+상승, -하락)
CString strTHPR = m_CommAgent.GetRealOutputData("FB0", "THPR");		//이론가
CString strTHPR_CLR = m_CommAgent.GetRealOutputData("FB0", "THPR_CLR");		//[THPR]색참조(+상승, -하락)
CString strMRKT_BASIS = m_CommAgent.GetRealOutputData("FB0", "MRKT_BASIS");		//시장 BASIS
CString strMRKT_BASIS_CLR = m_CommAgent.GetRealOutputData("FB0", "MRKT_BASIS_CLR");		//[MRKT_BASIS]색참조(+상승, -하락)
CString strTHER_BASIS = m_CommAgent.GetRealOutputData("FB0", "THER_BASIS");		//이론 BASIS
CString strTHER_BASIS_CLR = m_CommAgent.GetRealOutputData("FB0", "THER_BASIS_CLR");		//[THER_BASIS]색참조(+상승, -하락)
CString strESDG = m_CommAgent.GetRealOutputData("FB0", "ESDG");		//괴리도
CString strESDG_CLR = m_CommAgent.GetRealOutputData("FB0", "ESDG_CLR");		//[ESDG]색참조(+상승, -하락)
CString strDPRT = m_CommAgent.GetRealOutputData("FB0", "DPRT");		//괴리율
CString strDPRT_CLR = m_CommAgent.GetRealOutputData("FB0", "DPRT_CLR");		//[DPRT]색참조(+상승, -하락)
CString strSHNU_RATE = m_CommAgent.GetRealOutputData("FB0", "SHNU_RATE");		//매수비율
CString strSHNU_RATE_CLR = m_CommAgent.GetRealOutputData("FB0", "SHNU_RATE_CLR");		//[SHNU_RATE]색참조(+상승, -하락)
CString strCTTR = m_CommAgent.GetRealOutputData("FB0", "CTTR");		//체결강도
CString strCTTR_CLR = m_CommAgent.GetRealOutputData("FB0", "CTTR_CLR");		//[CTTR]색참조(+상승, -하락)
CString strASKP1 = m_CommAgent.GetRealOutputData("FB0", "ASKP1");		//매도호가1
CString strASKP1_CLR = m_CommAgent.GetRealOutputData("FB0", "ASKP1_CLR");		//[ASKP1]색참조(+상승, -하락)
CString strBIDP1 = m_CommAgent.GetRealOutputData("FB0", "BIDP1");		//매수호가1
CString strBIDP1_CLR = m_CommAgent.GetRealOutputData("FB0", "BIDP1_CLR");		//[BIDP1]색참조(+상승, -하락)
CString strASKP_RSQN1 = m_CommAgent.GetRealOutputData("FB0", "ASKP_RSQN1");		//매도호가 잔량
CString strBIDP_RSQN1 = m_CommAgent.GetRealOutputData("FB0", "BIDP_RSQN1");		//매수호가 잔량
CString strSELN_CNTG_CSNU = m_CommAgent.GetRealOutputData("FB0", "SELN_CNTG_CSNU");		//매도 체결 건수
CString strSHNU_CNTG_CSNU = m_CommAgent.GetRealOutputData("FB0", "SHNU_CNTG_CSNU");		//매수 체결 건수
CString strNTBY_CNTG_CSNU = m_CommAgent.GetRealOutputData("FB0", "NTBY_CNTG_CSNU");		//순매수 체결 건수
CString strNTBY_CNTG_CSNU_CLR = m_CommAgent.GetRealOutputData("FB0", "NTBY_CNTG_CSNU_CLR");		//[NTBY_CNTG_CSNU]색참조(+상승, -하락)
CString strSELN_CNTG_SMTN = m_CommAgent.GetRealOutputData("FB0", "SELN_CNTG_SMTN");		//매도 체결 합계
CString strSHNU_CNTG_SMTN = m_CommAgent.GetRealOutputData("FB0", "SHNU_CNTG_SMTN");		//매수 체결 합계
CString strTOTAL_ASKP_RSQN = m_CommAgent.GetRealOutputData("FB0", "TOTAL_ASKP_RSQN");		//총 매도호가 잔량
CString strTOTAL_BIDP_RSQN = m_CommAgent.GetRealOutputData("FB0", "TOTAL_BIDP_RSQN");		//총 매수호가 잔량
CString strPRDY_VRSS_VOL_RATE = m_CommAgent.GetRealOutputData("FB0", "PRDY_VRSS_VOL_RATE");		//전일 대비 거래량 비율
CString strPRDY_VRSS_VOL_RATE_CLR = m_CommAgent.GetRealOutputData("FB0", "PRDY_VRSS_VOL_RATE_CLR");		//[PRDY_VRSS_VOL_RATE]색참조(+상승, -하락)
CString strUNAS_PRC = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRC");		//기초자산 가격
CString strUNAS_PRC_CLR = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRC_CLR");		//[UNAS_PRC]색참조(+상승, -하락)
CString strUNAS_PRDY_VRSS_SIGN = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRDY_VRSS_SIGN");		//기초자산 전일대비구분
CString strUNAS_PRDY_VRSS = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRDY_VRSS");		//기초자산 전일 대비
CString strUNAS_PRDY_VRSS_CLR = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRDY_VRSS_CLR");		//[UNAS_PRDY_VRSS]색참조(+상승, -하락)
CString strUNAS_PRDY_CTRT = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRDY_CTRT");		//기초자산 전일 대비율
CString strUNAS_PRDY_CTRT_CLR = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRDY_CTRT_CLR");		//[UNAS_PRDY_CTRT]색참조(+상승, -하락)
CString strCNTG_PRGS = m_CommAgent.GetRealOutputData("FB0", "CNTG_PRGS");		//체결틱추이




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
CString strCNTG_VOL = realCommRecvData.GetItem(0, 10);		//체결량
CString strCNTG_VOL_CLR = realCommRecvData.GetItem(0, 11);		//[CNTG_VOL]색참조(+상승, -하락)
CString strACML_VOL = realCommRecvData.GetItem(0, 12);		//누적 거래량
CString strACML_TR_PBMN = realCommRecvData.GetItem(0, 13);		//누적 거래 대금
CString strOPRC = realCommRecvData.GetItem(0, 14);		//시가
CString strOPRC_CLR = realCommRecvData.GetItem(0, 15);		//[OPRC]색참조(+상승, -하락)
CString strHGPR = realCommRecvData.GetItem(0, 16);		//고가
CString strHGPR_CLR = realCommRecvData.GetItem(0, 17);		//[HGPR]색참조(+상승, -하락)
CString strLWPR = realCommRecvData.GetItem(0, 18);		//저가
CString strLWPR_CLR = realCommRecvData.GetItem(0, 19);		//[LWPR]색참조(+상승, -하락)
CString strOPRC_HOUR = realCommRecvData.GetItem(0, 20);		//시가 시간
CString strOPRC_VRSS_SIGN = realCommRecvData.GetItem(0, 21);		//시가 대비 부호
CString strOPRC_VRSS = realCommRecvData.GetItem(0, 22);		//시가 대비
CString strOPRC_VRSS_CLR = realCommRecvData.GetItem(0, 23);		//[OPRC_VRSS]색참조(+상승, -하락)
CString strHGPR_HOUR = realCommRecvData.GetItem(0, 24);		//고가 시간
CString strHGPR_VRSS_SIGN = realCommRecvData.GetItem(0, 25);		//고가 대비 부호
CString strHGPR_VRSS = realCommRecvData.GetItem(0, 26);		//고가 대비
CString strHGPR_VRSS_CLR = realCommRecvData.GetItem(0, 27);		//[HGPR_VRSS]색참조(+상승, -하락)
CString strLWPR_HOUR = realCommRecvData.GetItem(0, 28);		//저가 시간
CString strLWPR_VRSS_SIGN = realCommRecvData.GetItem(0, 29);		//저가 대비 부호
CString strLWPR_VRSS = realCommRecvData.GetItem(0, 30);		//저가 대비
CString strLWPR_VRSS_CLR = realCommRecvData.GetItem(0, 31);		//[LWPR_VRSS]색참조(+상승, -하락)
CString strNMSC_FCTN_STPL_PRC = realCommRecvData.GetItem(0, 32);		//근월물 의제 약정가
CString strFMSC_FCTN_STPL_PRC = realCommRecvData.GetItem(0, 33);		//원월물 의제 약정가
CString strSPEAD_PRC = realCommRecvData.GetItem(0, 34);		//스프레드
CString strOTST_STPL_QTY = realCommRecvData.GetItem(0, 35);		//미결제 약정 수량
CString strOTST_STPL_QTY_ICDC = realCommRecvData.GetItem(0, 36);		//미결제 약정 수량 증감
CString strOTST_STPL_QTY_ICDC_CLR = realCommRecvData.GetItem(0, 37);		//[OTST_STPL_QTY_ICDC]색참조(+상승, -하락)
CString strOTST_STPL_QTY_REF_IC = realCommRecvData.GetItem(0, 38);		//미결제 약정 직전 수량 증감
CString strOTST_STPL_QTY_REF_IC_CLR = realCommRecvData.GetItem(0, 39);		//[OTST_STPL_QTY_REF_IC]색참조(+상승, -하락)
CString strTHPR = realCommRecvData.GetItem(0, 40);		//이론가
CString strTHPR_CLR = realCommRecvData.GetItem(0, 41);		//[THPR]색참조(+상승, -하락)
CString strMRKT_BASIS = realCommRecvData.GetItem(0, 42);		//시장 BASIS
CString strMRKT_BASIS_CLR = realCommRecvData.GetItem(0, 43);		//[MRKT_BASIS]색참조(+상승, -하락)
CString strTHER_BASIS = realCommRecvData.GetItem(0, 44);		//이론 BASIS
CString strTHER_BASIS_CLR = realCommRecvData.GetItem(0, 45);		//[THER_BASIS]색참조(+상승, -하락)
CString strESDG = realCommRecvData.GetItem(0, 46);		//괴리도
CString strESDG_CLR = realCommRecvData.GetItem(0, 47);		//[ESDG]색참조(+상승, -하락)
CString strDPRT = realCommRecvData.GetItem(0, 48);		//괴리율
CString strDPRT_CLR = realCommRecvData.GetItem(0, 49);		//[DPRT]색참조(+상승, -하락)
CString strSHNU_RATE = realCommRecvData.GetItem(0, 50);		//매수비율
CString strSHNU_RATE_CLR = realCommRecvData.GetItem(0, 51);		//[SHNU_RATE]색참조(+상승, -하락)
CString strCTTR = realCommRecvData.GetItem(0, 52);		//체결강도
CString strCTTR_CLR = realCommRecvData.GetItem(0, 53);		//[CTTR]색참조(+상승, -하락)
CString strASKP1 = realCommRecvData.GetItem(0, 54);		//매도호가1
CString strASKP1_CLR = realCommRecvData.GetItem(0, 55);		//[ASKP1]색참조(+상승, -하락)
CString strBIDP1 = realCommRecvData.GetItem(0, 56);		//매수호가1
CString strBIDP1_CLR = realCommRecvData.GetItem(0, 57);		//[BIDP1]색참조(+상승, -하락)
CString strASKP_RSQN1 = realCommRecvData.GetItem(0, 58);		//매도호가 잔량
CString strBIDP_RSQN1 = realCommRecvData.GetItem(0, 59);		//매수호가 잔량
CString strSELN_CNTG_CSNU = realCommRecvData.GetItem(0, 60);		//매도 체결 건수
CString strSHNU_CNTG_CSNU = realCommRecvData.GetItem(0, 61);		//매수 체결 건수
CString strNTBY_CNTG_CSNU = realCommRecvData.GetItem(0, 62);		//순매수 체결 건수
CString strNTBY_CNTG_CSNU_CLR = realCommRecvData.GetItem(0, 63);		//[NTBY_CNTG_CSNU]색참조(+상승, -하락)
CString strSELN_CNTG_SMTN = realCommRecvData.GetItem(0, 64);		//매도 체결 합계
CString strSHNU_CNTG_SMTN = realCommRecvData.GetItem(0, 65);		//매수 체결 합계
CString strTOTAL_ASKP_RSQN = realCommRecvData.GetItem(0, 66);		//총 매도호가 잔량
CString strTOTAL_BIDP_RSQN = realCommRecvData.GetItem(0, 67);		//총 매수호가 잔량
CString strPRDY_VRSS_VOL_RATE = realCommRecvData.GetItem(0, 68);		//전일 대비 거래량 비율
CString strPRDY_VRSS_VOL_RATE_CLR = realCommRecvData.GetItem(0, 69);		//[PRDY_VRSS_VOL_RATE]색참조(+상승, -하락)
CString strUNAS_PRC = realCommRecvData.GetItem(0, 70);		//기초자산 가격
CString strUNAS_PRC_CLR = realCommRecvData.GetItem(0, 71);		//[UNAS_PRC]색참조(+상승, -하락)
CString strUNAS_PRDY_VRSS_SIGN = realCommRecvData.GetItem(0, 72);		//기초자산 전일대비구분
CString strUNAS_PRDY_VRSS = realCommRecvData.GetItem(0, 73);		//기초자산 전일 대비
CString strUNAS_PRDY_VRSS_CLR = realCommRecvData.GetItem(0, 74);		//[UNAS_PRDY_VRSS]색참조(+상승, -하락)
CString strUNAS_PRDY_CTRT = realCommRecvData.GetItem(0, 75);		//기초자산 전일 대비율
CString strUNAS_PRDY_CTRT_CLR = realCommRecvData.GetItem(0, 76);		//[UNAS_PRDY_CTRT]색참조(+상승, -하락)
CString strCNTG_PRGS = realCommRecvData.GetItem(0, 77);		//체결틱추이
