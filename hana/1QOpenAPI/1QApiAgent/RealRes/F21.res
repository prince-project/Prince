BEGIN_FUNCTION_MAP
	REAL_TYPE=33, REAL_NAME=F21, DESCRIPTION=주식선물호가;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SHRN_ISCD, TYPE=string, SIZE=9, KEY=1, CAPTION=종목코드, FID=0;
			 INDEX=1, ITEM=BSOP_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=호가시간, FID=0;
			 INDEX=2, ITEM=ASKP1, TYPE=string, SIZE=12, KEY=0, CAPTION=1매도호가, FID=0;
			 INDEX=3, ITEM=ASKP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP1]색참조(+상승, -하락), FID=0;
			 INDEX=4, ITEM=ASKP2, TYPE=string, SIZE=12, KEY=0, CAPTION=2매도호가, FID=0;
			 INDEX=5, ITEM=ASKP2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP2]색참조(+상승, -하락), FID=0;
			 INDEX=6, ITEM=ASKP3, TYPE=string, SIZE=12, KEY=0, CAPTION=3매도호가, FID=0;
			 INDEX=7, ITEM=ASKP3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP3]색참조(+상승, -하락), FID=0;
			 INDEX=8, ITEM=ASKP4, TYPE=string, SIZE=12, KEY=0, CAPTION=4매도호가, FID=0;
			 INDEX=9, ITEM=ASKP4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP4]색참조(+상승, -하락), FID=0;
			 INDEX=10, ITEM=ASKP5, TYPE=string, SIZE=12, KEY=0, CAPTION=5매도호가, FID=0;
			 INDEX=11, ITEM=ASKP5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP5]색참조(+상승, -하락), FID=0;
			 INDEX=12, ITEM=ASKP6, TYPE=string, SIZE=12, KEY=0, CAPTION=6매도호가, FID=0;
			 INDEX=13, ITEM=ASKP6_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP6]색참조(+상승, -하락), FID=0;
			 INDEX=14, ITEM=ASKP7, TYPE=string, SIZE=12, KEY=0, CAPTION=7매도호가, FID=0;
			 INDEX=15, ITEM=ASKP7_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP7]색참조(+상승, -하락), FID=0;
			 INDEX=16, ITEM=ASKP8, TYPE=string, SIZE=12, KEY=0, CAPTION=8매도호가, FID=0;
			 INDEX=17, ITEM=ASKP8_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP8]색참조(+상승, -하락), FID=0;
			 INDEX=18, ITEM=ASKP9, TYPE=string, SIZE=12, KEY=0, CAPTION=9매도호가, FID=0;
			 INDEX=19, ITEM=ASKP9_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP9]색참조(+상승, -하락), FID=0;
			 INDEX=20, ITEM=ASKP10, TYPE=string, SIZE=12, KEY=0, CAPTION=10매도호가, FID=0;
			 INDEX=21, ITEM=ASKP10_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP10]색참조(+상승, -하락), FID=0;
			 INDEX=22, ITEM=BIDP1, TYPE=string, SIZE=12, KEY=0, CAPTION=1매수호가, FID=0;
			 INDEX=23, ITEM=BIDP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP1]색참조(+상승, -하락), FID=0;
			 INDEX=24, ITEM=BIDP2, TYPE=string, SIZE=12, KEY=0, CAPTION=2매수호가, FID=0;
			 INDEX=25, ITEM=BIDP2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP2]색참조(+상승, -하락), FID=0;
			 INDEX=26, ITEM=BIDP3, TYPE=string, SIZE=12, KEY=0, CAPTION=3매수호가, FID=0;
			 INDEX=27, ITEM=BIDP3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP3]색참조(+상승, -하락), FID=0;
			 INDEX=28, ITEM=BIDP4, TYPE=string, SIZE=12, KEY=0, CAPTION=4매수호가, FID=0;
			 INDEX=29, ITEM=BIDP4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP4]색참조(+상승, -하락), FID=0;
			 INDEX=30, ITEM=BIDP5, TYPE=string, SIZE=12, KEY=0, CAPTION=5매수호가, FID=0;
			 INDEX=31, ITEM=BIDP5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP5]색참조(+상승, -하락), FID=0;
			 INDEX=32, ITEM=BIDP6, TYPE=string, SIZE=12, KEY=0, CAPTION=6매수호가, FID=0;
			 INDEX=33, ITEM=BIDP6_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP6]색참조(+상승, -하락), FID=0;
			 INDEX=34, ITEM=BIDP7, TYPE=string, SIZE=12, KEY=0, CAPTION=7매수호가, FID=0;
			 INDEX=35, ITEM=BIDP7_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP7]색참조(+상승, -하락), FID=0;
			 INDEX=36, ITEM=BIDP8, TYPE=string, SIZE=12, KEY=0, CAPTION=8매수호가, FID=0;
			 INDEX=37, ITEM=BIDP8_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP8]색참조(+상승, -하락), FID=0;
			 INDEX=38, ITEM=BIDP9, TYPE=string, SIZE=12, KEY=0, CAPTION=9매수호가, FID=0;
			 INDEX=39, ITEM=BIDP9_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP9]색참조(+상승, -하락), FID=0;
			 INDEX=40, ITEM=BIDP10, TYPE=string, SIZE=12, KEY=0, CAPTION=10매수호가, FID=0;
			 INDEX=41, ITEM=BIDP10_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP10]색참조(+상승, -하락), FID=0;
			 INDEX=42, ITEM=ASKP_RSQN1, TYPE=string, SIZE=18, KEY=0, CAPTION=1매도호가 잔량, FID=0;
			 INDEX=43, ITEM=ASKP_RSQN2, TYPE=string, SIZE=18, KEY=0, CAPTION=2매도호가 잔량, FID=0;
			 INDEX=44, ITEM=ASKP_RSQN3, TYPE=string, SIZE=18, KEY=0, CAPTION=3매도호가 잔량, FID=0;
			 INDEX=45, ITEM=ASKP_RSQN4, TYPE=string, SIZE=18, KEY=0, CAPTION=4매도호가 잔량, FID=0;
			 INDEX=46, ITEM=ASKP_RSQN5, TYPE=string, SIZE=18, KEY=0, CAPTION=5매도호가 잔량, FID=0;
			 INDEX=47, ITEM=ASKP_RSQN6, TYPE=string, SIZE=18, KEY=0, CAPTION=6매도호가 잔량, FID=0;
			 INDEX=48, ITEM=ASKP_RSQN7, TYPE=string, SIZE=18, KEY=0, CAPTION=7매도호가 잔량, FID=0;
			 INDEX=49, ITEM=ASKP_RSQN8, TYPE=string, SIZE=18, KEY=0, CAPTION=8매도호가 잔량, FID=0;
			 INDEX=50, ITEM=ASKP_RSQN9, TYPE=string, SIZE=18, KEY=0, CAPTION=9매도호가 잔량, FID=0;
			 INDEX=51, ITEM=ASKP_RSQN10, TYPE=string, SIZE=18, KEY=0, CAPTION=10매도호가 잔량, FID=0;
			 INDEX=52, ITEM=BIDP_RSQN1, TYPE=string, SIZE=18, KEY=0, CAPTION=1매수호가 잔량, FID=0;
			 INDEX=53, ITEM=BIDP_RSQN2, TYPE=string, SIZE=18, KEY=0, CAPTION=2매수호가 잔량, FID=0;
			 INDEX=54, ITEM=BIDP_RSQN3, TYPE=string, SIZE=18, KEY=0, CAPTION=3매수호가 잔량, FID=0;
			 INDEX=55, ITEM=BIDP_RSQN4, TYPE=string, SIZE=18, KEY=0, CAPTION=4매수호가 잔량, FID=0;
			 INDEX=56, ITEM=BIDP_RSQN5, TYPE=string, SIZE=18, KEY=0, CAPTION=5매수호가 잔량, FID=0;
			 INDEX=57, ITEM=BIDP_RSQN6, TYPE=string, SIZE=18, KEY=0, CAPTION=6매수호가 잔량, FID=0;
			 INDEX=58, ITEM=BIDP_RSQN7, TYPE=string, SIZE=18, KEY=0, CAPTION=7매수호가 잔량, FID=0;
			 INDEX=59, ITEM=BIDP_RSQN8, TYPE=string, SIZE=18, KEY=0, CAPTION=8매수호가 잔량, FID=0;
			 INDEX=60, ITEM=BIDP_RSQN9, TYPE=string, SIZE=18, KEY=0, CAPTION=9매수호가 잔량, FID=0;
			 INDEX=61, ITEM=BIDP_RSQN10, TYPE=string, SIZE=18, KEY=0, CAPTION=10매수호가 잔량, FID=0;
			 INDEX=62, ITEM=ASKP_CSNU1, TYPE=string, SIZE=12, KEY=0, CAPTION=1매도호가 건수, FID=0;
			 INDEX=63, ITEM=ASKP_CSNU2, TYPE=string, SIZE=12, KEY=0, CAPTION=2매도호가 건수, FID=0;
			 INDEX=64, ITEM=ASKP_CSNU3, TYPE=string, SIZE=12, KEY=0, CAPTION=3매도호가 건수, FID=0;
			 INDEX=65, ITEM=ASKP_CSNU4, TYPE=string, SIZE=12, KEY=0, CAPTION=4매도호가 건수, FID=0;
			 INDEX=66, ITEM=ASKP_CSNU5, TYPE=string, SIZE=12, KEY=0, CAPTION=5매도호가 건수, FID=0;
			 INDEX=67, ITEM=ASKP_CSNU6, TYPE=string, SIZE=12, KEY=0, CAPTION=6매도호가 건수, FID=0;
			 INDEX=68, ITEM=ASKP_CSNU7, TYPE=string, SIZE=12, KEY=0, CAPTION=7매도호가 건수, FID=0;
			 INDEX=69, ITEM=ASKP_CSNU8, TYPE=string, SIZE=12, KEY=0, CAPTION=8매도호가 건수, FID=0;
			 INDEX=70, ITEM=ASKP_CSNU9, TYPE=string, SIZE=12, KEY=0, CAPTION=9매도호가 건수, FID=0;
			 INDEX=71, ITEM=ASKP_CSNU10, TYPE=string, SIZE=12, KEY=0, CAPTION=10매도호가 건수, FID=0;
			 INDEX=72, ITEM=BIDP_CSNU1, TYPE=string, SIZE=12, KEY=0, CAPTION=1매수호가 건수, FID=0;
			 INDEX=73, ITEM=BIDP_CSNU2, TYPE=string, SIZE=12, KEY=0, CAPTION=2매수호가 건수, FID=0;
			 INDEX=74, ITEM=BIDP_CSNU3, TYPE=string, SIZE=12, KEY=0, CAPTION=3매수호가 건수, FID=0;
			 INDEX=75, ITEM=BIDP_CSNU4, TYPE=string, SIZE=12, KEY=0, CAPTION=4매수호가 건수, FID=0;
			 INDEX=76, ITEM=BIDP_CSNU5, TYPE=string, SIZE=12, KEY=0, CAPTION=5매수호가 건수, FID=0;
			 INDEX=77, ITEM=BIDP_CSNU6, TYPE=string, SIZE=12, KEY=0, CAPTION=6매수호가 건수, FID=0;
			 INDEX=78, ITEM=BIDP_CSNU7, TYPE=string, SIZE=12, KEY=0, CAPTION=7매수호가 건수, FID=0;
			 INDEX=79, ITEM=BIDP_CSNU8, TYPE=string, SIZE=12, KEY=0, CAPTION=8매수호가 건수, FID=0;
			 INDEX=80, ITEM=BIDP_CSNU9, TYPE=string, SIZE=12, KEY=0, CAPTION=9매수호가 건수, FID=0;
			 INDEX=81, ITEM=BIDP_CSNU10, TYPE=string, SIZE=12, KEY=0, CAPTION=10매수호가 건수, FID=0;
			 INDEX=82, ITEM=TOTAL_ASKP_CSNU, TYPE=string, SIZE=12, KEY=0, CAPTION=총 매도호가 건수, FID=0;
			 INDEX=83, ITEM=TOTAL_BIDP_CSNU, TYPE=string, SIZE=12, KEY=0, CAPTION=총 매수호가 건수, FID=0;
			 INDEX=84, ITEM=TOTAL_ASKP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=총 매도호가 잔량, FID=0;
			 INDEX=85, ITEM=TOTAL_BIDP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=총 매수호가 잔량, FID=0;
			 INDEX=86, ITEM=ANTC_CNPR, TYPE=string, SIZE=12, KEY=0, CAPTION=예상 체결 가격, FID=0;
			 INDEX=87, ITEM=ANTC_CNPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ANTC_CNPR]색참조(+상승, -하락), FID=0;
			 INDEX=88, ITEM=ANTC_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=예상구분코드, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strSHRN_ISCD = m_CommAgent.GetRealOutputData("F21", "SHRN_ISCD");		//종목코드
CString strBSOP_HOUR = m_CommAgent.GetRealOutputData("F21", "BSOP_HOUR");		//호가시간
CString strASKP1 = m_CommAgent.GetRealOutputData("F21", "ASKP1");		//1매도호가
CString strASKP1_CLR = m_CommAgent.GetRealOutputData("F21", "ASKP1_CLR");		//[ASKP1]색참조(+상승, -하락)
CString strASKP2 = m_CommAgent.GetRealOutputData("F21", "ASKP2");		//2매도호가
CString strASKP2_CLR = m_CommAgent.GetRealOutputData("F21", "ASKP2_CLR");		//[ASKP2]색참조(+상승, -하락)
CString strASKP3 = m_CommAgent.GetRealOutputData("F21", "ASKP3");		//3매도호가
CString strASKP3_CLR = m_CommAgent.GetRealOutputData("F21", "ASKP3_CLR");		//[ASKP3]색참조(+상승, -하락)
CString strASKP4 = m_CommAgent.GetRealOutputData("F21", "ASKP4");		//4매도호가
CString strASKP4_CLR = m_CommAgent.GetRealOutputData("F21", "ASKP4_CLR");		//[ASKP4]색참조(+상승, -하락)
CString strASKP5 = m_CommAgent.GetRealOutputData("F21", "ASKP5");		//5매도호가
CString strASKP5_CLR = m_CommAgent.GetRealOutputData("F21", "ASKP5_CLR");		//[ASKP5]색참조(+상승, -하락)
CString strASKP6 = m_CommAgent.GetRealOutputData("F21", "ASKP6");		//6매도호가
CString strASKP6_CLR = m_CommAgent.GetRealOutputData("F21", "ASKP6_CLR");		//[ASKP6]색참조(+상승, -하락)
CString strASKP7 = m_CommAgent.GetRealOutputData("F21", "ASKP7");		//7매도호가
CString strASKP7_CLR = m_CommAgent.GetRealOutputData("F21", "ASKP7_CLR");		//[ASKP7]색참조(+상승, -하락)
CString strASKP8 = m_CommAgent.GetRealOutputData("F21", "ASKP8");		//8매도호가
CString strASKP8_CLR = m_CommAgent.GetRealOutputData("F21", "ASKP8_CLR");		//[ASKP8]색참조(+상승, -하락)
CString strASKP9 = m_CommAgent.GetRealOutputData("F21", "ASKP9");		//9매도호가
CString strASKP9_CLR = m_CommAgent.GetRealOutputData("F21", "ASKP9_CLR");		//[ASKP9]색참조(+상승, -하락)
CString strASKP10 = m_CommAgent.GetRealOutputData("F21", "ASKP10");		//10매도호가
CString strASKP10_CLR = m_CommAgent.GetRealOutputData("F21", "ASKP10_CLR");		//[ASKP10]색참조(+상승, -하락)
CString strBIDP1 = m_CommAgent.GetRealOutputData("F21", "BIDP1");		//1매수호가
CString strBIDP1_CLR = m_CommAgent.GetRealOutputData("F21", "BIDP1_CLR");		//[BIDP1]색참조(+상승, -하락)
CString strBIDP2 = m_CommAgent.GetRealOutputData("F21", "BIDP2");		//2매수호가
CString strBIDP2_CLR = m_CommAgent.GetRealOutputData("F21", "BIDP2_CLR");		//[BIDP2]색참조(+상승, -하락)
CString strBIDP3 = m_CommAgent.GetRealOutputData("F21", "BIDP3");		//3매수호가
CString strBIDP3_CLR = m_CommAgent.GetRealOutputData("F21", "BIDP3_CLR");		//[BIDP3]색참조(+상승, -하락)
CString strBIDP4 = m_CommAgent.GetRealOutputData("F21", "BIDP4");		//4매수호가
CString strBIDP4_CLR = m_CommAgent.GetRealOutputData("F21", "BIDP4_CLR");		//[BIDP4]색참조(+상승, -하락)
CString strBIDP5 = m_CommAgent.GetRealOutputData("F21", "BIDP5");		//5매수호가
CString strBIDP5_CLR = m_CommAgent.GetRealOutputData("F21", "BIDP5_CLR");		//[BIDP5]색참조(+상승, -하락)
CString strBIDP6 = m_CommAgent.GetRealOutputData("F21", "BIDP6");		//6매수호가
CString strBIDP6_CLR = m_CommAgent.GetRealOutputData("F21", "BIDP6_CLR");		//[BIDP6]색참조(+상승, -하락)
CString strBIDP7 = m_CommAgent.GetRealOutputData("F21", "BIDP7");		//7매수호가
CString strBIDP7_CLR = m_CommAgent.GetRealOutputData("F21", "BIDP7_CLR");		//[BIDP7]색참조(+상승, -하락)
CString strBIDP8 = m_CommAgent.GetRealOutputData("F21", "BIDP8");		//8매수호가
CString strBIDP8_CLR = m_CommAgent.GetRealOutputData("F21", "BIDP8_CLR");		//[BIDP8]색참조(+상승, -하락)
CString strBIDP9 = m_CommAgent.GetRealOutputData("F21", "BIDP9");		//9매수호가
CString strBIDP9_CLR = m_CommAgent.GetRealOutputData("F21", "BIDP9_CLR");		//[BIDP9]색참조(+상승, -하락)
CString strBIDP10 = m_CommAgent.GetRealOutputData("F21", "BIDP10");		//10매수호가
CString strBIDP10_CLR = m_CommAgent.GetRealOutputData("F21", "BIDP10_CLR");		//[BIDP10]색참조(+상승, -하락)
CString strASKP_RSQN1 = m_CommAgent.GetRealOutputData("F21", "ASKP_RSQN1");		//1매도호가 잔량
CString strASKP_RSQN2 = m_CommAgent.GetRealOutputData("F21", "ASKP_RSQN2");		//2매도호가 잔량
CString strASKP_RSQN3 = m_CommAgent.GetRealOutputData("F21", "ASKP_RSQN3");		//3매도호가 잔량
CString strASKP_RSQN4 = m_CommAgent.GetRealOutputData("F21", "ASKP_RSQN4");		//4매도호가 잔량
CString strASKP_RSQN5 = m_CommAgent.GetRealOutputData("F21", "ASKP_RSQN5");		//5매도호가 잔량
CString strASKP_RSQN6 = m_CommAgent.GetRealOutputData("F21", "ASKP_RSQN6");		//6매도호가 잔량
CString strASKP_RSQN7 = m_CommAgent.GetRealOutputData("F21", "ASKP_RSQN7");		//7매도호가 잔량
CString strASKP_RSQN8 = m_CommAgent.GetRealOutputData("F21", "ASKP_RSQN8");		//8매도호가 잔량
CString strASKP_RSQN9 = m_CommAgent.GetRealOutputData("F21", "ASKP_RSQN9");		//9매도호가 잔량
CString strASKP_RSQN10 = m_CommAgent.GetRealOutputData("F21", "ASKP_RSQN10");		//10매도호가 잔량
CString strBIDP_RSQN1 = m_CommAgent.GetRealOutputData("F21", "BIDP_RSQN1");		//1매수호가 잔량
CString strBIDP_RSQN2 = m_CommAgent.GetRealOutputData("F21", "BIDP_RSQN2");		//2매수호가 잔량
CString strBIDP_RSQN3 = m_CommAgent.GetRealOutputData("F21", "BIDP_RSQN3");		//3매수호가 잔량
CString strBIDP_RSQN4 = m_CommAgent.GetRealOutputData("F21", "BIDP_RSQN4");		//4매수호가 잔량
CString strBIDP_RSQN5 = m_CommAgent.GetRealOutputData("F21", "BIDP_RSQN5");		//5매수호가 잔량
CString strBIDP_RSQN6 = m_CommAgent.GetRealOutputData("F21", "BIDP_RSQN6");		//6매수호가 잔량
CString strBIDP_RSQN7 = m_CommAgent.GetRealOutputData("F21", "BIDP_RSQN7");		//7매수호가 잔량
CString strBIDP_RSQN8 = m_CommAgent.GetRealOutputData("F21", "BIDP_RSQN8");		//8매수호가 잔량
CString strBIDP_RSQN9 = m_CommAgent.GetRealOutputData("F21", "BIDP_RSQN9");		//9매수호가 잔량
CString strBIDP_RSQN10 = m_CommAgent.GetRealOutputData("F21", "BIDP_RSQN10");		//10매수호가 잔량
CString strASKP_CSNU1 = m_CommAgent.GetRealOutputData("F21", "ASKP_CSNU1");		//1매도호가 건수
CString strASKP_CSNU2 = m_CommAgent.GetRealOutputData("F21", "ASKP_CSNU2");		//2매도호가 건수
CString strASKP_CSNU3 = m_CommAgent.GetRealOutputData("F21", "ASKP_CSNU3");		//3매도호가 건수
CString strASKP_CSNU4 = m_CommAgent.GetRealOutputData("F21", "ASKP_CSNU4");		//4매도호가 건수
CString strASKP_CSNU5 = m_CommAgent.GetRealOutputData("F21", "ASKP_CSNU5");		//5매도호가 건수
CString strASKP_CSNU6 = m_CommAgent.GetRealOutputData("F21", "ASKP_CSNU6");		//6매도호가 건수
CString strASKP_CSNU7 = m_CommAgent.GetRealOutputData("F21", "ASKP_CSNU7");		//7매도호가 건수
CString strASKP_CSNU8 = m_CommAgent.GetRealOutputData("F21", "ASKP_CSNU8");		//8매도호가 건수
CString strASKP_CSNU9 = m_CommAgent.GetRealOutputData("F21", "ASKP_CSNU9");		//9매도호가 건수
CString strASKP_CSNU10 = m_CommAgent.GetRealOutputData("F21", "ASKP_CSNU10");		//10매도호가 건수
CString strBIDP_CSNU1 = m_CommAgent.GetRealOutputData("F21", "BIDP_CSNU1");		//1매수호가 건수
CString strBIDP_CSNU2 = m_CommAgent.GetRealOutputData("F21", "BIDP_CSNU2");		//2매수호가 건수
CString strBIDP_CSNU3 = m_CommAgent.GetRealOutputData("F21", "BIDP_CSNU3");		//3매수호가 건수
CString strBIDP_CSNU4 = m_CommAgent.GetRealOutputData("F21", "BIDP_CSNU4");		//4매수호가 건수
CString strBIDP_CSNU5 = m_CommAgent.GetRealOutputData("F21", "BIDP_CSNU5");		//5매수호가 건수
CString strBIDP_CSNU6 = m_CommAgent.GetRealOutputData("F21", "BIDP_CSNU6");		//6매수호가 건수
CString strBIDP_CSNU7 = m_CommAgent.GetRealOutputData("F21", "BIDP_CSNU7");		//7매수호가 건수
CString strBIDP_CSNU8 = m_CommAgent.GetRealOutputData("F21", "BIDP_CSNU8");		//8매수호가 건수
CString strBIDP_CSNU9 = m_CommAgent.GetRealOutputData("F21", "BIDP_CSNU9");		//9매수호가 건수
CString strBIDP_CSNU10 = m_CommAgent.GetRealOutputData("F21", "BIDP_CSNU10");		//10매수호가 건수
CString strTOTAL_ASKP_CSNU = m_CommAgent.GetRealOutputData("F21", "TOTAL_ASKP_CSNU");		//총 매도호가 건수
CString strTOTAL_BIDP_CSNU = m_CommAgent.GetRealOutputData("F21", "TOTAL_BIDP_CSNU");		//총 매수호가 건수
CString strTOTAL_ASKP_RSQN = m_CommAgent.GetRealOutputData("F21", "TOTAL_ASKP_RSQN");		//총 매도호가 잔량
CString strTOTAL_BIDP_RSQN = m_CommAgent.GetRealOutputData("F21", "TOTAL_BIDP_RSQN");		//총 매수호가 잔량
CString strANTC_CNPR = m_CommAgent.GetRealOutputData("F21", "ANTC_CNPR");		//예상 체결 가격
CString strANTC_CNPR_CLR = m_CommAgent.GetRealOutputData("F21", "ANTC_CNPR_CLR");		//[ANTC_CNPR]색참조(+상승, -하락)
CString strANTC_CLS_CODE = m_CommAgent.GetRealOutputData("F21", "ANTC_CLS_CODE");		//예상구분코드




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strSHRN_ISCD = realCommRecvData.GetItem(0, 0);		//종목코드
CString strBSOP_HOUR = realCommRecvData.GetItem(0, 1);		//호가시간
CString strASKP1 = realCommRecvData.GetItem(0, 2);		//1매도호가
CString strASKP1_CLR = realCommRecvData.GetItem(0, 3);		//[ASKP1]색참조(+상승, -하락)
CString strASKP2 = realCommRecvData.GetItem(0, 4);		//2매도호가
CString strASKP2_CLR = realCommRecvData.GetItem(0, 5);		//[ASKP2]색참조(+상승, -하락)
CString strASKP3 = realCommRecvData.GetItem(0, 6);		//3매도호가
CString strASKP3_CLR = realCommRecvData.GetItem(0, 7);		//[ASKP3]색참조(+상승, -하락)
CString strASKP4 = realCommRecvData.GetItem(0, 8);		//4매도호가
CString strASKP4_CLR = realCommRecvData.GetItem(0, 9);		//[ASKP4]색참조(+상승, -하락)
CString strASKP5 = realCommRecvData.GetItem(0, 10);		//5매도호가
CString strASKP5_CLR = realCommRecvData.GetItem(0, 11);		//[ASKP5]색참조(+상승, -하락)
CString strASKP6 = realCommRecvData.GetItem(0, 12);		//6매도호가
CString strASKP6_CLR = realCommRecvData.GetItem(0, 13);		//[ASKP6]색참조(+상승, -하락)
CString strASKP7 = realCommRecvData.GetItem(0, 14);		//7매도호가
CString strASKP7_CLR = realCommRecvData.GetItem(0, 15);		//[ASKP7]색참조(+상승, -하락)
CString strASKP8 = realCommRecvData.GetItem(0, 16);		//8매도호가
CString strASKP8_CLR = realCommRecvData.GetItem(0, 17);		//[ASKP8]색참조(+상승, -하락)
CString strASKP9 = realCommRecvData.GetItem(0, 18);		//9매도호가
CString strASKP9_CLR = realCommRecvData.GetItem(0, 19);		//[ASKP9]색참조(+상승, -하락)
CString strASKP10 = realCommRecvData.GetItem(0, 20);		//10매도호가
CString strASKP10_CLR = realCommRecvData.GetItem(0, 21);		//[ASKP10]색참조(+상승, -하락)
CString strBIDP1 = realCommRecvData.GetItem(0, 22);		//1매수호가
CString strBIDP1_CLR = realCommRecvData.GetItem(0, 23);		//[BIDP1]색참조(+상승, -하락)
CString strBIDP2 = realCommRecvData.GetItem(0, 24);		//2매수호가
CString strBIDP2_CLR = realCommRecvData.GetItem(0, 25);		//[BIDP2]색참조(+상승, -하락)
CString strBIDP3 = realCommRecvData.GetItem(0, 26);		//3매수호가
CString strBIDP3_CLR = realCommRecvData.GetItem(0, 27);		//[BIDP3]색참조(+상승, -하락)
CString strBIDP4 = realCommRecvData.GetItem(0, 28);		//4매수호가
CString strBIDP4_CLR = realCommRecvData.GetItem(0, 29);		//[BIDP4]색참조(+상승, -하락)
CString strBIDP5 = realCommRecvData.GetItem(0, 30);		//5매수호가
CString strBIDP5_CLR = realCommRecvData.GetItem(0, 31);		//[BIDP5]색참조(+상승, -하락)
CString strBIDP6 = realCommRecvData.GetItem(0, 32);		//6매수호가
CString strBIDP6_CLR = realCommRecvData.GetItem(0, 33);		//[BIDP6]색참조(+상승, -하락)
CString strBIDP7 = realCommRecvData.GetItem(0, 34);		//7매수호가
CString strBIDP7_CLR = realCommRecvData.GetItem(0, 35);		//[BIDP7]색참조(+상승, -하락)
CString strBIDP8 = realCommRecvData.GetItem(0, 36);		//8매수호가
CString strBIDP8_CLR = realCommRecvData.GetItem(0, 37);		//[BIDP8]색참조(+상승, -하락)
CString strBIDP9 = realCommRecvData.GetItem(0, 38);		//9매수호가
CString strBIDP9_CLR = realCommRecvData.GetItem(0, 39);		//[BIDP9]색참조(+상승, -하락)
CString strBIDP10 = realCommRecvData.GetItem(0, 40);		//10매수호가
CString strBIDP10_CLR = realCommRecvData.GetItem(0, 41);		//[BIDP10]색참조(+상승, -하락)
CString strASKP_RSQN1 = realCommRecvData.GetItem(0, 42);		//1매도호가 잔량
CString strASKP_RSQN2 = realCommRecvData.GetItem(0, 43);		//2매도호가 잔량
CString strASKP_RSQN3 = realCommRecvData.GetItem(0, 44);		//3매도호가 잔량
CString strASKP_RSQN4 = realCommRecvData.GetItem(0, 45);		//4매도호가 잔량
CString strASKP_RSQN5 = realCommRecvData.GetItem(0, 46);		//5매도호가 잔량
CString strASKP_RSQN6 = realCommRecvData.GetItem(0, 47);		//6매도호가 잔량
CString strASKP_RSQN7 = realCommRecvData.GetItem(0, 48);		//7매도호가 잔량
CString strASKP_RSQN8 = realCommRecvData.GetItem(0, 49);		//8매도호가 잔량
CString strASKP_RSQN9 = realCommRecvData.GetItem(0, 50);		//9매도호가 잔량
CString strASKP_RSQN10 = realCommRecvData.GetItem(0, 51);		//10매도호가 잔량
CString strBIDP_RSQN1 = realCommRecvData.GetItem(0, 52);		//1매수호가 잔량
CString strBIDP_RSQN2 = realCommRecvData.GetItem(0, 53);		//2매수호가 잔량
CString strBIDP_RSQN3 = realCommRecvData.GetItem(0, 54);		//3매수호가 잔량
CString strBIDP_RSQN4 = realCommRecvData.GetItem(0, 55);		//4매수호가 잔량
CString strBIDP_RSQN5 = realCommRecvData.GetItem(0, 56);		//5매수호가 잔량
CString strBIDP_RSQN6 = realCommRecvData.GetItem(0, 57);		//6매수호가 잔량
CString strBIDP_RSQN7 = realCommRecvData.GetItem(0, 58);		//7매수호가 잔량
CString strBIDP_RSQN8 = realCommRecvData.GetItem(0, 59);		//8매수호가 잔량
CString strBIDP_RSQN9 = realCommRecvData.GetItem(0, 60);		//9매수호가 잔량
CString strBIDP_RSQN10 = realCommRecvData.GetItem(0, 61);		//10매수호가 잔량
CString strASKP_CSNU1 = realCommRecvData.GetItem(0, 62);		//1매도호가 건수
CString strASKP_CSNU2 = realCommRecvData.GetItem(0, 63);		//2매도호가 건수
CString strASKP_CSNU3 = realCommRecvData.GetItem(0, 64);		//3매도호가 건수
CString strASKP_CSNU4 = realCommRecvData.GetItem(0, 65);		//4매도호가 건수
CString strASKP_CSNU5 = realCommRecvData.GetItem(0, 66);		//5매도호가 건수
CString strASKP_CSNU6 = realCommRecvData.GetItem(0, 67);		//6매도호가 건수
CString strASKP_CSNU7 = realCommRecvData.GetItem(0, 68);		//7매도호가 건수
CString strASKP_CSNU8 = realCommRecvData.GetItem(0, 69);		//8매도호가 건수
CString strASKP_CSNU9 = realCommRecvData.GetItem(0, 70);		//9매도호가 건수
CString strASKP_CSNU10 = realCommRecvData.GetItem(0, 71);		//10매도호가 건수
CString strBIDP_CSNU1 = realCommRecvData.GetItem(0, 72);		//1매수호가 건수
CString strBIDP_CSNU2 = realCommRecvData.GetItem(0, 73);		//2매수호가 건수
CString strBIDP_CSNU3 = realCommRecvData.GetItem(0, 74);		//3매수호가 건수
CString strBIDP_CSNU4 = realCommRecvData.GetItem(0, 75);		//4매수호가 건수
CString strBIDP_CSNU5 = realCommRecvData.GetItem(0, 76);		//5매수호가 건수
CString strBIDP_CSNU6 = realCommRecvData.GetItem(0, 77);		//6매수호가 건수
CString strBIDP_CSNU7 = realCommRecvData.GetItem(0, 78);		//7매수호가 건수
CString strBIDP_CSNU8 = realCommRecvData.GetItem(0, 79);		//8매수호가 건수
CString strBIDP_CSNU9 = realCommRecvData.GetItem(0, 80);		//9매수호가 건수
CString strBIDP_CSNU10 = realCommRecvData.GetItem(0, 81);		//10매수호가 건수
CString strTOTAL_ASKP_CSNU = realCommRecvData.GetItem(0, 82);		//총 매도호가 건수
CString strTOTAL_BIDP_CSNU = realCommRecvData.GetItem(0, 83);		//총 매수호가 건수
CString strTOTAL_ASKP_RSQN = realCommRecvData.GetItem(0, 84);		//총 매도호가 잔량
CString strTOTAL_BIDP_RSQN = realCommRecvData.GetItem(0, 85);		//총 매수호가 잔량
CString strANTC_CNPR = realCommRecvData.GetItem(0, 86);		//예상 체결 가격
CString strANTC_CNPR_CLR = realCommRecvData.GetItem(0, 87);		//[ANTC_CNPR]색참조(+상승, -하락)
CString strANTC_CLS_CODE = realCommRecvData.GetItem(0, 88);		//예상구분코드
