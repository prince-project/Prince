BEGIN_FUNCTION_MAP
	REAL_TYPE=113, REAL_NAME=U06, DESCRIPTION=업종프로그램매매;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=MRKT_DIV_CLS_CODE, TYPE=string, SIZE=1, KEY=1, CAPTION=시장 분류 구분 코드, FID=0;
			 INDEX=1, ITEM=BSOP_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=영업 시간, FID=0;
			 INDEX=2, ITEM=BSTP_NMIX, TYPE=string, SIZE=18, KEY=0, CAPTION=지수, FID=0;
			 INDEX=3, ITEM=BSTP_NMIX_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BSTP_NMIX]색참조(+상승, -하락), FID=0;
			 INDEX=4, ITEM=BSTP_NMIX_PRDY_VRSS, TYPE=string, SIZE=18, KEY=0, CAPTION=전일대비, FID=0;
			 INDEX=5, ITEM=BSTP_NMIX_PRDY_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BSTP_NMIX_PRDY_VRSS]색참조(+상승, -하락), FID=0;
			 INDEX=6, ITEM=ARBT_SELN_ENTM_CNQN, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 매도 위탁 체결량, FID=0;
			 INDEX=7, ITEM=ARBT_SELN_ONSL_CNQN, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 매도 자기 체결량, FID=0;
			 INDEX=8, ITEM=ARBT_SHNU_ENTM_CNQN, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 매수 위탁 체결량, FID=0;
			 INDEX=9, ITEM=ARBT_SHNU_ONSL_CNQN, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 매수 자기 체결량, FID=0;
			 INDEX=10, ITEM=NABT_SELN_ENTM_CNQN, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 매도 위탁 체결량, FID=0;
			 INDEX=11, ITEM=NABT_SELN_ONSL_CNQN, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 매도 자기 체결량, FID=0;
			 INDEX=12, ITEM=NABT_SHNU_ENTM_CNQN, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 매수 위탁 체결량, FID=0;
			 INDEX=13, ITEM=NABT_SHNU_ONSL_CNQN, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 매수 자기 체결량, FID=0;
			 INDEX=14, ITEM=ARBT_SEL_ENT_CNT_AMT, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 매도 위탁 체결 금액, FID=0;
			 INDEX=15, ITEM=ARBT_SEL_ONS_CNT_AMT, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 매도 자기 체결 금액, FID=0;
			 INDEX=16, ITEM=ARBT_SHN_ENT_CNT_AMT, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 매수 위탁 체결 금액, FID=0;
			 INDEX=17, ITEM=ARBT_SHN_ONS_CNT_AMT, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 매수 자기 체결 금액, FID=0;
			 INDEX=18, ITEM=NABT_SEL_ENT_CNT_AMT, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 매도 위탁 체결 금액, FID=0;
			 INDEX=19, ITEM=NABT_SEL_ONS_CNT_AMT, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 매도 자기 체결 금액, FID=0;
			 INDEX=20, ITEM=NABT_SHN_ENT_CNT_AMT, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 매수 위탁 체결 금액, FID=0;
			 INDEX=21, ITEM=NABT_SHN_ONS_CNT_AMT, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 매수 자기 체결 금액, FID=0;
			 INDEX=22, ITEM=ARBT_SMTN_SELN_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 매도 거래량, FID=0;
			 INDEX=23, ITEM=ARBT_SMTN_SELN_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 매도 거래대금, FID=0;
			 INDEX=24, ITEM=ARBT_SMTN_SHNU_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 매수 거래량, FID=0;
			 INDEX=25, ITEM=ARBT_SMTN_SHNU_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 매수 거래대금, FID=0;
			 INDEX=26, ITEM=ARBT_SMTN_NTBY_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 순매수 거래량, FID=0;
			 INDEX=27, ITEM=ARBT_SMTN_NTBY_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ARBT_SMTN_NTBY_VOL]색참조(+상승, -하락), FID=0;
			 INDEX=28, ITEM=ARBT_SMTN_NTBY_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 순매수 거래대금, FID=0;
			 INDEX=29, ITEM=ARBT_SMTN_NTBY_TR_PB_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ARBT_SMTN_NTBY_TR_PB]색참조(+상승, -하락), FID=0;
			 INDEX=30, ITEM=NABT_SMTN_SELN_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 매도 거래량, FID=0;
			 INDEX=31, ITEM=NABT_SMTN_SELN_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 매도 거래대금, FID=0;
			 INDEX=32, ITEM=NABT_SMTN_SHNU_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 매수 거래량, FID=0;
			 INDEX=33, ITEM=NABT_SMTN_SHNU_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 매수 거래대금, FID=0;
			 INDEX=34, ITEM=NABT_SMTN_NTBY_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 순매수 거래량, FID=0;
			 INDEX=35, ITEM=NABT_SMTN_NTBY_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NABT_SMTN_NTBY_VOL]색참조(+상승, -하락), FID=0;
			 INDEX=36, ITEM=NABT_SMTN_NTBY_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 순매수 거래대금, FID=0;
			 INDEX=37, ITEM=NABT_SMTN_NTBY_TR_PB_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NABT_SMTN_NTBY_TR_PB]색참조(+상승, -하락), FID=0;
			 INDEX=38, ITEM=WHOL_ENTM_SELN_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 위탁 매도 거래량, FID=0;
			 INDEX=39, ITEM=WHOL_ENTM_SELN_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 위탁 매도 거래대금, FID=0;
			 INDEX=40, ITEM=WHOL_ENTM_SHNU_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 위탁 매수 거래량, FID=0;
			 INDEX=41, ITEM=WHOL_ENTM_SHNU_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 위탁 매수 거래대금, FID=0;
			 INDEX=42, ITEM=WHOL_ENTM_NTBY_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 위탁 순매수 거래량, FID=0;
			 INDEX=43, ITEM=WHOL_ENTM_NTBY_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[WHOL_ENTM_NTBY_VOL]색참조(+상승, -하락), FID=0;
			 INDEX=44, ITEM=WHOL_ENTM_NTBY_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 위탁 순매수 거래대금, FID=0;
			 INDEX=45, ITEM=WHOL_ENTM_NTBY_TR_PB_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[WHOL_ENTM_NTBY_TR_PB]색참조(+상승, -하락), FID=0;
			 INDEX=46, ITEM=WHOL_ONSL_SELN_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 자기 매도 거래량, FID=0;
			 INDEX=47, ITEM=WHOL_ONSL_SELN_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 자기 매도 거래대금, FID=0;
			 INDEX=48, ITEM=WHOL_ONSL_SHNU_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 자기 매수 거래량, FID=0;
			 INDEX=49, ITEM=WHOL_ONSL_SHNU_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 자기 매수 거래대금, FID=0;
			 INDEX=50, ITEM=WHOL_ONSL_NTBY_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 자기 순매수 거래량, FID=0;
			 INDEX=51, ITEM=WHOL_ONSL_NTBY_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[WHOL_ONSL_NTBY_VOL]색참조(+상승, -하락), FID=0;
			 INDEX=52, ITEM=WHOL_ONSL_NTBY_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 자기 순매수 거래대금, FID=0;
			 INDEX=53, ITEM=WHOL_ONSL_NTBY_TR_PB_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[WHOL_ONSL_NTBY_TR_PB]색참조(+상승, -하락), FID=0;
			 INDEX=54, ITEM=WHOL_SELN_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 매도 거래량, FID=0;
			 INDEX=55, ITEM=WHOL_SELN_TR_PBMN, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 매도 거래대금, FID=0;
			 INDEX=56, ITEM=WHOL_SHNU_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 매수 거래량, FID=0;
			 INDEX=57, ITEM=WHOL_SHNU_TR_PBMN, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 매수 거래대금, FID=0;
			 INDEX=58, ITEM=WHOL_NTBY_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 순매수 거래량, FID=0;
			 INDEX=59, ITEM=WHOL_NTBY_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[WHOL_NTBY_VOL]색참조(+상승, -하락), FID=0;
			 INDEX=60, ITEM=WHOL_NTBY_TR_PBMN, TYPE=string, SIZE=18, KEY=0, CAPTION=전체 순매수 거래대금, FID=0;
			 INDEX=61, ITEM=WHOL_NTBY_TR_PBMN_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[WHOL_NTBY_TR_PBMN]색참조(+상승, -하락), FID=0;
			 INDEX=62, ITEM=ARBT_ENTM_NTBY_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 위탁 순매수 거래량, FID=0;
			 INDEX=63, ITEM=ARBT_ENTM_NTBY_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ARBT_ENTM_NTBY_VOL]색참조(+상승, -하락), FID=0;
			 INDEX=64, ITEM=ARBT_ENTM_NTBY_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 위탁 순매수 거래대금, FID=0;
			 INDEX=65, ITEM=ARBT_ENTM_NTBY_TR_PB_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ARBT_ENTM_NTBY_TR_PB]색참조(+상승, -하락), FID=0;
			 INDEX=66, ITEM=ARBT_ONSL_NTBY_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 자기 순매수 거래량, FID=0;
			 INDEX=67, ITEM=ARBT_ONSL_NTBY_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ARBT_ONSL_NTBY_VOL]색참조(+상승, -하락), FID=0;
			 INDEX=68, ITEM=ARBT_ONSL_NTBY_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=차익 자기 순매수 거래대금, FID=0;
			 INDEX=69, ITEM=ARBT_ONSL_NTBY_TR_PB_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ARBT_ONSL_NTBY_TR_PB]색참조(+상승, -하락), FID=0;
			 INDEX=70, ITEM=NABT_ENTM_NTBY_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 위탁 순매수 거래량, FID=0;
			 INDEX=71, ITEM=NABT_ENTM_NTBY_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NABT_ENTM_NTBY_VOL]색참조(+상승, -하락), FID=0;
			 INDEX=72, ITEM=NABT_ENTM_NTBY_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 위탁 순매수 거래대금, FID=0;
			 INDEX=73, ITEM=NABT_ENTM_NTBY_TR_PB_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NABT_ENTM_NTBY_TR_PB]색참조(+상승, -하락), FID=0;
			 INDEX=74, ITEM=NABT_ONSL_NTBY_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 자기 순매수 거래량, FID=0;
			 INDEX=75, ITEM=NABT_ONSL_NTBY_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NABT_ONSL_NTBY_VOL]색참조(+상승, -하락), FID=0;
			 INDEX=76, ITEM=NABT_ONSL_NTBY_TR_PB, TYPE=string, SIZE=18, KEY=0, CAPTION=비차익 자기 순매수 거래대금, FID=0;
			 INDEX=77, ITEM=NABT_ONSL_NTBY_TR_PB_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NABT_ONSL_NTBY_TR_PB]색참조(+상승, -하락), FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strMRKT_DIV_CLS_CODE = m_CommAgent.GetRealOutputData("U06", "MRKT_DIV_CLS_CODE");		//시장 분류 구분 코드
CString strBSOP_HOUR = m_CommAgent.GetRealOutputData("U06", "BSOP_HOUR");		//영업 시간
CString strBSTP_NMIX = m_CommAgent.GetRealOutputData("U06", "BSTP_NMIX");		//지수
CString strBSTP_NMIX_CLR = m_CommAgent.GetRealOutputData("U06", "BSTP_NMIX_CLR");		//[BSTP_NMIX]색참조(+상승, -하락)
CString strBSTP_NMIX_PRDY_VRSS = m_CommAgent.GetRealOutputData("U06", "BSTP_NMIX_PRDY_VRSS");		//전일대비
CString strBSTP_NMIX_PRDY_VRSS_CLR = m_CommAgent.GetRealOutputData("U06", "BSTP_NMIX_PRDY_VRSS_CLR");		//[BSTP_NMIX_PRDY_VRSS]색참조(+상승, -하락)
CString strARBT_SELN_ENTM_CNQN = m_CommAgent.GetRealOutputData("U06", "ARBT_SELN_ENTM_CNQN");		//차익 매도 위탁 체결량
CString strARBT_SELN_ONSL_CNQN = m_CommAgent.GetRealOutputData("U06", "ARBT_SELN_ONSL_CNQN");		//차익 매도 자기 체결량
CString strARBT_SHNU_ENTM_CNQN = m_CommAgent.GetRealOutputData("U06", "ARBT_SHNU_ENTM_CNQN");		//차익 매수 위탁 체결량
CString strARBT_SHNU_ONSL_CNQN = m_CommAgent.GetRealOutputData("U06", "ARBT_SHNU_ONSL_CNQN");		//차익 매수 자기 체결량
CString strNABT_SELN_ENTM_CNQN = m_CommAgent.GetRealOutputData("U06", "NABT_SELN_ENTM_CNQN");		//비차익 매도 위탁 체결량
CString strNABT_SELN_ONSL_CNQN = m_CommAgent.GetRealOutputData("U06", "NABT_SELN_ONSL_CNQN");		//비차익 매도 자기 체결량
CString strNABT_SHNU_ENTM_CNQN = m_CommAgent.GetRealOutputData("U06", "NABT_SHNU_ENTM_CNQN");		//비차익 매수 위탁 체결량
CString strNABT_SHNU_ONSL_CNQN = m_CommAgent.GetRealOutputData("U06", "NABT_SHNU_ONSL_CNQN");		//비차익 매수 자기 체결량
CString strARBT_SEL_ENT_CNT_AMT = m_CommAgent.GetRealOutputData("U06", "ARBT_SEL_ENT_CNT_AMT");		//차익 매도 위탁 체결 금액
CString strARBT_SEL_ONS_CNT_AMT = m_CommAgent.GetRealOutputData("U06", "ARBT_SEL_ONS_CNT_AMT");		//차익 매도 자기 체결 금액
CString strARBT_SHN_ENT_CNT_AMT = m_CommAgent.GetRealOutputData("U06", "ARBT_SHN_ENT_CNT_AMT");		//차익 매수 위탁 체결 금액
CString strARBT_SHN_ONS_CNT_AMT = m_CommAgent.GetRealOutputData("U06", "ARBT_SHN_ONS_CNT_AMT");		//차익 매수 자기 체결 금액
CString strNABT_SEL_ENT_CNT_AMT = m_CommAgent.GetRealOutputData("U06", "NABT_SEL_ENT_CNT_AMT");		//비차익 매도 위탁 체결 금액
CString strNABT_SEL_ONS_CNT_AMT = m_CommAgent.GetRealOutputData("U06", "NABT_SEL_ONS_CNT_AMT");		//비차익 매도 자기 체결 금액
CString strNABT_SHN_ENT_CNT_AMT = m_CommAgent.GetRealOutputData("U06", "NABT_SHN_ENT_CNT_AMT");		//비차익 매수 위탁 체결 금액
CString strNABT_SHN_ONS_CNT_AMT = m_CommAgent.GetRealOutputData("U06", "NABT_SHN_ONS_CNT_AMT");		//비차익 매수 자기 체결 금액
CString strARBT_SMTN_SELN_VOL = m_CommAgent.GetRealOutputData("U06", "ARBT_SMTN_SELN_VOL");		//차익 매도 거래량
CString strARBT_SMTN_SELN_TR_PB = m_CommAgent.GetRealOutputData("U06", "ARBT_SMTN_SELN_TR_PB");		//차익 매도 거래대금
CString strARBT_SMTN_SHNU_VOL = m_CommAgent.GetRealOutputData("U06", "ARBT_SMTN_SHNU_VOL");		//차익 매수 거래량
CString strARBT_SMTN_SHNU_TR_PB = m_CommAgent.GetRealOutputData("U06", "ARBT_SMTN_SHNU_TR_PB");		//차익 매수 거래대금
CString strARBT_SMTN_NTBY_VOL = m_CommAgent.GetRealOutputData("U06", "ARBT_SMTN_NTBY_VOL");		//차익 순매수 거래량
CString strARBT_SMTN_NTBY_VOL_CLR = m_CommAgent.GetRealOutputData("U06", "ARBT_SMTN_NTBY_VOL_CLR");		//[ARBT_SMTN_NTBY_VOL]색참조(+상승, -하락)
CString strARBT_SMTN_NTBY_TR_PB = m_CommAgent.GetRealOutputData("U06", "ARBT_SMTN_NTBY_TR_PB");		//차익 순매수 거래대금
CString strARBT_SMTN_NTBY_TR_PB_CLR = m_CommAgent.GetRealOutputData("U06", "ARBT_SMTN_NTBY_TR_PB_CLR");		//[ARBT_SMTN_NTBY_TR_PB]색참조(+상승, -하락)
CString strNABT_SMTN_SELN_VOL = m_CommAgent.GetRealOutputData("U06", "NABT_SMTN_SELN_VOL");		//비차익 매도 거래량
CString strNABT_SMTN_SELN_TR_PB = m_CommAgent.GetRealOutputData("U06", "NABT_SMTN_SELN_TR_PB");		//비차익 매도 거래대금
CString strNABT_SMTN_SHNU_VOL = m_CommAgent.GetRealOutputData("U06", "NABT_SMTN_SHNU_VOL");		//비차익 매수 거래량
CString strNABT_SMTN_SHNU_TR_PB = m_CommAgent.GetRealOutputData("U06", "NABT_SMTN_SHNU_TR_PB");		//비차익 매수 거래대금
CString strNABT_SMTN_NTBY_VOL = m_CommAgent.GetRealOutputData("U06", "NABT_SMTN_NTBY_VOL");		//비차익 순매수 거래량
CString strNABT_SMTN_NTBY_VOL_CLR = m_CommAgent.GetRealOutputData("U06", "NABT_SMTN_NTBY_VOL_CLR");		//[NABT_SMTN_NTBY_VOL]색참조(+상승, -하락)
CString strNABT_SMTN_NTBY_TR_PB = m_CommAgent.GetRealOutputData("U06", "NABT_SMTN_NTBY_TR_PB");		//비차익 순매수 거래대금
CString strNABT_SMTN_NTBY_TR_PB_CLR = m_CommAgent.GetRealOutputData("U06", "NABT_SMTN_NTBY_TR_PB_CLR");		//[NABT_SMTN_NTBY_TR_PB]색참조(+상승, -하락)
CString strWHOL_ENTM_SELN_VOL = m_CommAgent.GetRealOutputData("U06", "WHOL_ENTM_SELN_VOL");		//전체 위탁 매도 거래량
CString strWHOL_ENTM_SELN_TR_PB = m_CommAgent.GetRealOutputData("U06", "WHOL_ENTM_SELN_TR_PB");		//전체 위탁 매도 거래대금
CString strWHOL_ENTM_SHNU_VOL = m_CommAgent.GetRealOutputData("U06", "WHOL_ENTM_SHNU_VOL");		//전체 위탁 매수 거래량
CString strWHOL_ENTM_SHNU_TR_PB = m_CommAgent.GetRealOutputData("U06", "WHOL_ENTM_SHNU_TR_PB");		//전체 위탁 매수 거래대금
CString strWHOL_ENTM_NTBY_VOL = m_CommAgent.GetRealOutputData("U06", "WHOL_ENTM_NTBY_VOL");		//전체 위탁 순매수 거래량
CString strWHOL_ENTM_NTBY_VOL_CLR = m_CommAgent.GetRealOutputData("U06", "WHOL_ENTM_NTBY_VOL_CLR");		//[WHOL_ENTM_NTBY_VOL]색참조(+상승, -하락)
CString strWHOL_ENTM_NTBY_TR_PB = m_CommAgent.GetRealOutputData("U06", "WHOL_ENTM_NTBY_TR_PB");		//전체 위탁 순매수 거래대금
CString strWHOL_ENTM_NTBY_TR_PB_CLR = m_CommAgent.GetRealOutputData("U06", "WHOL_ENTM_NTBY_TR_PB_CLR");		//[WHOL_ENTM_NTBY_TR_PB]색참조(+상승, -하락)
CString strWHOL_ONSL_SELN_VOL = m_CommAgent.GetRealOutputData("U06", "WHOL_ONSL_SELN_VOL");		//전체 자기 매도 거래량
CString strWHOL_ONSL_SELN_TR_PB = m_CommAgent.GetRealOutputData("U06", "WHOL_ONSL_SELN_TR_PB");		//전체 자기 매도 거래대금
CString strWHOL_ONSL_SHNU_VOL = m_CommAgent.GetRealOutputData("U06", "WHOL_ONSL_SHNU_VOL");		//전체 자기 매수 거래량
CString strWHOL_ONSL_SHNU_TR_PB = m_CommAgent.GetRealOutputData("U06", "WHOL_ONSL_SHNU_TR_PB");		//전체 자기 매수 거래대금
CString strWHOL_ONSL_NTBY_VOL = m_CommAgent.GetRealOutputData("U06", "WHOL_ONSL_NTBY_VOL");		//전체 자기 순매수 거래량
CString strWHOL_ONSL_NTBY_VOL_CLR = m_CommAgent.GetRealOutputData("U06", "WHOL_ONSL_NTBY_VOL_CLR");		//[WHOL_ONSL_NTBY_VOL]색참조(+상승, -하락)
CString strWHOL_ONSL_NTBY_TR_PB = m_CommAgent.GetRealOutputData("U06", "WHOL_ONSL_NTBY_TR_PB");		//전체 자기 순매수 거래대금
CString strWHOL_ONSL_NTBY_TR_PB_CLR = m_CommAgent.GetRealOutputData("U06", "WHOL_ONSL_NTBY_TR_PB_CLR");		//[WHOL_ONSL_NTBY_TR_PB]색참조(+상승, -하락)
CString strWHOL_SELN_VOL = m_CommAgent.GetRealOutputData("U06", "WHOL_SELN_VOL");		//전체 매도 거래량
CString strWHOL_SELN_TR_PBMN = m_CommAgent.GetRealOutputData("U06", "WHOL_SELN_TR_PBMN");		//전체 매도 거래대금
CString strWHOL_SHNU_VOL = m_CommAgent.GetRealOutputData("U06", "WHOL_SHNU_VOL");		//전체 매수 거래량
CString strWHOL_SHNU_TR_PBMN = m_CommAgent.GetRealOutputData("U06", "WHOL_SHNU_TR_PBMN");		//전체 매수 거래대금
CString strWHOL_NTBY_VOL = m_CommAgent.GetRealOutputData("U06", "WHOL_NTBY_VOL");		//전체 순매수 거래량
CString strWHOL_NTBY_VOL_CLR = m_CommAgent.GetRealOutputData("U06", "WHOL_NTBY_VOL_CLR");		//[WHOL_NTBY_VOL]색참조(+상승, -하락)
CString strWHOL_NTBY_TR_PBMN = m_CommAgent.GetRealOutputData("U06", "WHOL_NTBY_TR_PBMN");		//전체 순매수 거래대금
CString strWHOL_NTBY_TR_PBMN_CLR = m_CommAgent.GetRealOutputData("U06", "WHOL_NTBY_TR_PBMN_CLR");		//[WHOL_NTBY_TR_PBMN]색참조(+상승, -하락)
CString strARBT_ENTM_NTBY_VOL = m_CommAgent.GetRealOutputData("U06", "ARBT_ENTM_NTBY_VOL");		//차익 위탁 순매수 거래량
CString strARBT_ENTM_NTBY_VOL_CLR = m_CommAgent.GetRealOutputData("U06", "ARBT_ENTM_NTBY_VOL_CLR");		//[ARBT_ENTM_NTBY_VOL]색참조(+상승, -하락)
CString strARBT_ENTM_NTBY_TR_PB = m_CommAgent.GetRealOutputData("U06", "ARBT_ENTM_NTBY_TR_PB");		//차익 위탁 순매수 거래대금
CString strARBT_ENTM_NTBY_TR_PB_CLR = m_CommAgent.GetRealOutputData("U06", "ARBT_ENTM_NTBY_TR_PB_CLR");		//[ARBT_ENTM_NTBY_TR_PB]색참조(+상승, -하락)
CString strARBT_ONSL_NTBY_VOL = m_CommAgent.GetRealOutputData("U06", "ARBT_ONSL_NTBY_VOL");		//차익 자기 순매수 거래량
CString strARBT_ONSL_NTBY_VOL_CLR = m_CommAgent.GetRealOutputData("U06", "ARBT_ONSL_NTBY_VOL_CLR");		//[ARBT_ONSL_NTBY_VOL]색참조(+상승, -하락)
CString strARBT_ONSL_NTBY_TR_PB = m_CommAgent.GetRealOutputData("U06", "ARBT_ONSL_NTBY_TR_PB");		//차익 자기 순매수 거래대금
CString strARBT_ONSL_NTBY_TR_PB_CLR = m_CommAgent.GetRealOutputData("U06", "ARBT_ONSL_NTBY_TR_PB_CLR");		//[ARBT_ONSL_NTBY_TR_PB]색참조(+상승, -하락)
CString strNABT_ENTM_NTBY_VOL = m_CommAgent.GetRealOutputData("U06", "NABT_ENTM_NTBY_VOL");		//비차익 위탁 순매수 거래량
CString strNABT_ENTM_NTBY_VOL_CLR = m_CommAgent.GetRealOutputData("U06", "NABT_ENTM_NTBY_VOL_CLR");		//[NABT_ENTM_NTBY_VOL]색참조(+상승, -하락)
CString strNABT_ENTM_NTBY_TR_PB = m_CommAgent.GetRealOutputData("U06", "NABT_ENTM_NTBY_TR_PB");		//비차익 위탁 순매수 거래대금
CString strNABT_ENTM_NTBY_TR_PB_CLR = m_CommAgent.GetRealOutputData("U06", "NABT_ENTM_NTBY_TR_PB_CLR");		//[NABT_ENTM_NTBY_TR_PB]색참조(+상승, -하락)
CString strNABT_ONSL_NTBY_VOL = m_CommAgent.GetRealOutputData("U06", "NABT_ONSL_NTBY_VOL");		//비차익 자기 순매수 거래량
CString strNABT_ONSL_NTBY_VOL_CLR = m_CommAgent.GetRealOutputData("U06", "NABT_ONSL_NTBY_VOL_CLR");		//[NABT_ONSL_NTBY_VOL]색참조(+상승, -하락)
CString strNABT_ONSL_NTBY_TR_PB = m_CommAgent.GetRealOutputData("U06", "NABT_ONSL_NTBY_TR_PB");		//비차익 자기 순매수 거래대금
CString strNABT_ONSL_NTBY_TR_PB_CLR = m_CommAgent.GetRealOutputData("U06", "NABT_ONSL_NTBY_TR_PB_CLR");		//[NABT_ONSL_NTBY_TR_PB]색참조(+상승, -하락)




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strMRKT_DIV_CLS_CODE = realCommRecvData.GetItem(0, 0);		//시장 분류 구분 코드
CString strBSOP_HOUR = realCommRecvData.GetItem(0, 1);		//영업 시간
CString strBSTP_NMIX = realCommRecvData.GetItem(0, 2);		//지수
CString strBSTP_NMIX_CLR = realCommRecvData.GetItem(0, 3);		//[BSTP_NMIX]색참조(+상승, -하락)
CString strBSTP_NMIX_PRDY_VRSS = realCommRecvData.GetItem(0, 4);		//전일대비
CString strBSTP_NMIX_PRDY_VRSS_CLR = realCommRecvData.GetItem(0, 5);		//[BSTP_NMIX_PRDY_VRSS]색참조(+상승, -하락)
CString strARBT_SELN_ENTM_CNQN = realCommRecvData.GetItem(0, 6);		//차익 매도 위탁 체결량
CString strARBT_SELN_ONSL_CNQN = realCommRecvData.GetItem(0, 7);		//차익 매도 자기 체결량
CString strARBT_SHNU_ENTM_CNQN = realCommRecvData.GetItem(0, 8);		//차익 매수 위탁 체결량
CString strARBT_SHNU_ONSL_CNQN = realCommRecvData.GetItem(0, 9);		//차익 매수 자기 체결량
CString strNABT_SELN_ENTM_CNQN = realCommRecvData.GetItem(0, 10);		//비차익 매도 위탁 체결량
CString strNABT_SELN_ONSL_CNQN = realCommRecvData.GetItem(0, 11);		//비차익 매도 자기 체결량
CString strNABT_SHNU_ENTM_CNQN = realCommRecvData.GetItem(0, 12);		//비차익 매수 위탁 체결량
CString strNABT_SHNU_ONSL_CNQN = realCommRecvData.GetItem(0, 13);		//비차익 매수 자기 체결량
CString strARBT_SEL_ENT_CNT_AMT = realCommRecvData.GetItem(0, 14);		//차익 매도 위탁 체결 금액
CString strARBT_SEL_ONS_CNT_AMT = realCommRecvData.GetItem(0, 15);		//차익 매도 자기 체결 금액
CString strARBT_SHN_ENT_CNT_AMT = realCommRecvData.GetItem(0, 16);		//차익 매수 위탁 체결 금액
CString strARBT_SHN_ONS_CNT_AMT = realCommRecvData.GetItem(0, 17);		//차익 매수 자기 체결 금액
CString strNABT_SEL_ENT_CNT_AMT = realCommRecvData.GetItem(0, 18);		//비차익 매도 위탁 체결 금액
CString strNABT_SEL_ONS_CNT_AMT = realCommRecvData.GetItem(0, 19);		//비차익 매도 자기 체결 금액
CString strNABT_SHN_ENT_CNT_AMT = realCommRecvData.GetItem(0, 20);		//비차익 매수 위탁 체결 금액
CString strNABT_SHN_ONS_CNT_AMT = realCommRecvData.GetItem(0, 21);		//비차익 매수 자기 체결 금액
CString strARBT_SMTN_SELN_VOL = realCommRecvData.GetItem(0, 22);		//차익 매도 거래량
CString strARBT_SMTN_SELN_TR_PB = realCommRecvData.GetItem(0, 23);		//차익 매도 거래대금
CString strARBT_SMTN_SHNU_VOL = realCommRecvData.GetItem(0, 24);		//차익 매수 거래량
CString strARBT_SMTN_SHNU_TR_PB = realCommRecvData.GetItem(0, 25);		//차익 매수 거래대금
CString strARBT_SMTN_NTBY_VOL = realCommRecvData.GetItem(0, 26);		//차익 순매수 거래량
CString strARBT_SMTN_NTBY_VOL_CLR = realCommRecvData.GetItem(0, 27);		//[ARBT_SMTN_NTBY_VOL]색참조(+상승, -하락)
CString strARBT_SMTN_NTBY_TR_PB = realCommRecvData.GetItem(0, 28);		//차익 순매수 거래대금
CString strARBT_SMTN_NTBY_TR_PB_CLR = realCommRecvData.GetItem(0, 29);		//[ARBT_SMTN_NTBY_TR_PB]색참조(+상승, -하락)
CString strNABT_SMTN_SELN_VOL = realCommRecvData.GetItem(0, 30);		//비차익 매도 거래량
CString strNABT_SMTN_SELN_TR_PB = realCommRecvData.GetItem(0, 31);		//비차익 매도 거래대금
CString strNABT_SMTN_SHNU_VOL = realCommRecvData.GetItem(0, 32);		//비차익 매수 거래량
CString strNABT_SMTN_SHNU_TR_PB = realCommRecvData.GetItem(0, 33);		//비차익 매수 거래대금
CString strNABT_SMTN_NTBY_VOL = realCommRecvData.GetItem(0, 34);		//비차익 순매수 거래량
CString strNABT_SMTN_NTBY_VOL_CLR = realCommRecvData.GetItem(0, 35);		//[NABT_SMTN_NTBY_VOL]색참조(+상승, -하락)
CString strNABT_SMTN_NTBY_TR_PB = realCommRecvData.GetItem(0, 36);		//비차익 순매수 거래대금
CString strNABT_SMTN_NTBY_TR_PB_CLR = realCommRecvData.GetItem(0, 37);		//[NABT_SMTN_NTBY_TR_PB]색참조(+상승, -하락)
CString strWHOL_ENTM_SELN_VOL = realCommRecvData.GetItem(0, 38);		//전체 위탁 매도 거래량
CString strWHOL_ENTM_SELN_TR_PB = realCommRecvData.GetItem(0, 39);		//전체 위탁 매도 거래대금
CString strWHOL_ENTM_SHNU_VOL = realCommRecvData.GetItem(0, 40);		//전체 위탁 매수 거래량
CString strWHOL_ENTM_SHNU_TR_PB = realCommRecvData.GetItem(0, 41);		//전체 위탁 매수 거래대금
CString strWHOL_ENTM_NTBY_VOL = realCommRecvData.GetItem(0, 42);		//전체 위탁 순매수 거래량
CString strWHOL_ENTM_NTBY_VOL_CLR = realCommRecvData.GetItem(0, 43);		//[WHOL_ENTM_NTBY_VOL]색참조(+상승, -하락)
CString strWHOL_ENTM_NTBY_TR_PB = realCommRecvData.GetItem(0, 44);		//전체 위탁 순매수 거래대금
CString strWHOL_ENTM_NTBY_TR_PB_CLR = realCommRecvData.GetItem(0, 45);		//[WHOL_ENTM_NTBY_TR_PB]색참조(+상승, -하락)
CString strWHOL_ONSL_SELN_VOL = realCommRecvData.GetItem(0, 46);		//전체 자기 매도 거래량
CString strWHOL_ONSL_SELN_TR_PB = realCommRecvData.GetItem(0, 47);		//전체 자기 매도 거래대금
CString strWHOL_ONSL_SHNU_VOL = realCommRecvData.GetItem(0, 48);		//전체 자기 매수 거래량
CString strWHOL_ONSL_SHNU_TR_PB = realCommRecvData.GetItem(0, 49);		//전체 자기 매수 거래대금
CString strWHOL_ONSL_NTBY_VOL = realCommRecvData.GetItem(0, 50);		//전체 자기 순매수 거래량
CString strWHOL_ONSL_NTBY_VOL_CLR = realCommRecvData.GetItem(0, 51);		//[WHOL_ONSL_NTBY_VOL]색참조(+상승, -하락)
CString strWHOL_ONSL_NTBY_TR_PB = realCommRecvData.GetItem(0, 52);		//전체 자기 순매수 거래대금
CString strWHOL_ONSL_NTBY_TR_PB_CLR = realCommRecvData.GetItem(0, 53);		//[WHOL_ONSL_NTBY_TR_PB]색참조(+상승, -하락)
CString strWHOL_SELN_VOL = realCommRecvData.GetItem(0, 54);		//전체 매도 거래량
CString strWHOL_SELN_TR_PBMN = realCommRecvData.GetItem(0, 55);		//전체 매도 거래대금
CString strWHOL_SHNU_VOL = realCommRecvData.GetItem(0, 56);		//전체 매수 거래량
CString strWHOL_SHNU_TR_PBMN = realCommRecvData.GetItem(0, 57);		//전체 매수 거래대금
CString strWHOL_NTBY_VOL = realCommRecvData.GetItem(0, 58);		//전체 순매수 거래량
CString strWHOL_NTBY_VOL_CLR = realCommRecvData.GetItem(0, 59);		//[WHOL_NTBY_VOL]색참조(+상승, -하락)
CString strWHOL_NTBY_TR_PBMN = realCommRecvData.GetItem(0, 60);		//전체 순매수 거래대금
CString strWHOL_NTBY_TR_PBMN_CLR = realCommRecvData.GetItem(0, 61);		//[WHOL_NTBY_TR_PBMN]색참조(+상승, -하락)
CString strARBT_ENTM_NTBY_VOL = realCommRecvData.GetItem(0, 62);		//차익 위탁 순매수 거래량
CString strARBT_ENTM_NTBY_VOL_CLR = realCommRecvData.GetItem(0, 63);		//[ARBT_ENTM_NTBY_VOL]색참조(+상승, -하락)
CString strARBT_ENTM_NTBY_TR_PB = realCommRecvData.GetItem(0, 64);		//차익 위탁 순매수 거래대금
CString strARBT_ENTM_NTBY_TR_PB_CLR = realCommRecvData.GetItem(0, 65);		//[ARBT_ENTM_NTBY_TR_PB]색참조(+상승, -하락)
CString strARBT_ONSL_NTBY_VOL = realCommRecvData.GetItem(0, 66);		//차익 자기 순매수 거래량
CString strARBT_ONSL_NTBY_VOL_CLR = realCommRecvData.GetItem(0, 67);		//[ARBT_ONSL_NTBY_VOL]색참조(+상승, -하락)
CString strARBT_ONSL_NTBY_TR_PB = realCommRecvData.GetItem(0, 68);		//차익 자기 순매수 거래대금
CString strARBT_ONSL_NTBY_TR_PB_CLR = realCommRecvData.GetItem(0, 69);		//[ARBT_ONSL_NTBY_TR_PB]색참조(+상승, -하락)
CString strNABT_ENTM_NTBY_VOL = realCommRecvData.GetItem(0, 70);		//비차익 위탁 순매수 거래량
CString strNABT_ENTM_NTBY_VOL_CLR = realCommRecvData.GetItem(0, 71);		//[NABT_ENTM_NTBY_VOL]색참조(+상승, -하락)
CString strNABT_ENTM_NTBY_TR_PB = realCommRecvData.GetItem(0, 72);		//비차익 위탁 순매수 거래대금
CString strNABT_ENTM_NTBY_TR_PB_CLR = realCommRecvData.GetItem(0, 73);		//[NABT_ENTM_NTBY_TR_PB]색참조(+상승, -하락)
CString strNABT_ONSL_NTBY_VOL = realCommRecvData.GetItem(0, 74);		//비차익 자기 순매수 거래량
CString strNABT_ONSL_NTBY_VOL_CLR = realCommRecvData.GetItem(0, 75);		//[NABT_ONSL_NTBY_VOL]색참조(+상승, -하락)
CString strNABT_ONSL_NTBY_TR_PB = realCommRecvData.GetItem(0, 76);		//비차익 자기 순매수 거래대금
CString strNABT_ONSL_NTBY_TR_PB_CLR = realCommRecvData.GetItem(0, 77);		//[NABT_ONSL_NTBY_TR_PB]색참조(+상승, -하락)
