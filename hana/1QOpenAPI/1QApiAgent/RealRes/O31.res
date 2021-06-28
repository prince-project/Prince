BEGIN_FUNCTION_MAP
	REAL_TYPE=55, REAL_NAME=O31, DESCRIPTION=EUREX 옵션 호가;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SHRN_ISCD, TYPE=string, SIZE=9, KEY=1, CAPTION=종목 코드, FID=0;
			 INDEX=1, ITEM=BSOP_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=호가 시간, FID=0;
			 INDEX=2, ITEM=ASKP1, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가1, FID=0;
			 INDEX=3, ITEM=ASKP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP1]색참조(+상승, -하락), FID=0;
			 INDEX=4, ITEM=ASKP2, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가2, FID=0;
			 INDEX=5, ITEM=ASKP2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP2]색참조(+상승, -하락), FID=0;
			 INDEX=6, ITEM=ASKP3, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가3, FID=0;
			 INDEX=7, ITEM=ASKP3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP3]색참조(+상승, -하락), FID=0;
			 INDEX=8, ITEM=ASKP4, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가4, FID=0;
			 INDEX=9, ITEM=ASKP4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP4]색참조(+상승, -하락), FID=0;
			 INDEX=10, ITEM=ASKP5, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가5, FID=0;
			 INDEX=11, ITEM=ASKP5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP5]색참조(+상승, -하락), FID=0;
			 INDEX=12, ITEM=BIDP1, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가1, FID=0;
			 INDEX=13, ITEM=BIDP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP1]색참조(+상승, -하락), FID=0;
			 INDEX=14, ITEM=BIDP2, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가2, FID=0;
			 INDEX=15, ITEM=BIDP2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP2]색참조(+상승, -하락), FID=0;
			 INDEX=16, ITEM=BIDP3, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가3, FID=0;
			 INDEX=17, ITEM=BIDP3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP3]색참조(+상승, -하락), FID=0;
			 INDEX=18, ITEM=BIDP4, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가4, FID=0;
			 INDEX=19, ITEM=BIDP4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP4]색참조(+상승, -하락), FID=0;
			 INDEX=20, ITEM=BIDP5, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가5, FID=0;
			 INDEX=21, ITEM=BIDP5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP5]색참조(+상승, -하락), FID=0;
			 INDEX=22, ITEM=ASKP_CSNU1, TYPE=string, SIZE=12, KEY=0, CAPTION=매도호가 건수1, FID=0;
			 INDEX=23, ITEM=ASKP_CSNU2, TYPE=string, SIZE=12, KEY=0, CAPTION=매도호가 건수2, FID=0;
			 INDEX=24, ITEM=ASKP_CSNU3, TYPE=string, SIZE=12, KEY=0, CAPTION=매도호가 건수3, FID=0;
			 INDEX=25, ITEM=ASKP_CSNU4, TYPE=string, SIZE=12, KEY=0, CAPTION=매도호가 건수4, FID=0;
			 INDEX=26, ITEM=ASKP_CSNU5, TYPE=string, SIZE=12, KEY=0, CAPTION=매도호가 건수5, FID=0;
			 INDEX=27, ITEM=BIDP_CSNU1, TYPE=string, SIZE=12, KEY=0, CAPTION=매수호가 건수1, FID=0;
			 INDEX=28, ITEM=BIDP_CSNU2, TYPE=string, SIZE=12, KEY=0, CAPTION=매수호가 건수2, FID=0;
			 INDEX=29, ITEM=BIDP_CSNU3, TYPE=string, SIZE=12, KEY=0, CAPTION=매수호가 건수3, FID=0;
			 INDEX=30, ITEM=BIDP_CSNU4, TYPE=string, SIZE=12, KEY=0, CAPTION=매수호가 건수4, FID=0;
			 INDEX=31, ITEM=BIDP_CSNU5, TYPE=string, SIZE=12, KEY=0, CAPTION=매수호가 건수5, FID=0;
			 INDEX=32, ITEM=ASKP_RSQN1, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가 잔량1, FID=0;
			 INDEX=33, ITEM=ASKP_RSQN2, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가 잔량2, FID=0;
			 INDEX=34, ITEM=ASKP_RSQN3, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가 잔량3, FID=0;
			 INDEX=35, ITEM=ASKP_RSQN4, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가 잔량4, FID=0;
			 INDEX=36, ITEM=ASKP_RSQN5, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가 잔량5, FID=0;
			 INDEX=37, ITEM=BIDP_RSQN1, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가 잔량1, FID=0;
			 INDEX=38, ITEM=BIDP_RSQN2, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가 잔량2, FID=0;
			 INDEX=39, ITEM=BIDP_RSQN3, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가 잔량3, FID=0;
			 INDEX=40, ITEM=BIDP_RSQN4, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가 잔량4, FID=0;
			 INDEX=41, ITEM=BIDP_RSQN5, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가 잔량5, FID=0;
			 INDEX=42, ITEM=TOTAL_ASKP_CSNU, TYPE=string, SIZE=12, KEY=0, CAPTION=총 매도호가 건수, FID=0;
			 INDEX=43, ITEM=TOTAL_BIDP_CSNU, TYPE=string, SIZE=12, KEY=0, CAPTION=총 매수호가 건수, FID=0;
			 INDEX=44, ITEM=TOTAL_ASKP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=총 매도호가 잔량, FID=0;
			 INDEX=45, ITEM=TOTAL_BIDP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=총 매수호가 잔량, FID=0;
			 INDEX=46, ITEM=ANTC_CNPR, TYPE=string, SIZE=18, KEY=0, CAPTION=예상 체결가, FID=0;
			 INDEX=47, ITEM=ANTC_CNPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ANTC_CNPR]색참조(+상승, -하락), FID=0;
			 INDEX=48, ITEM=ANTC_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=예상 구분 코드, FID=0;
			 INDEX=49, ITEM=ANTC_ISS_YN, TYPE=string, SIZE=1, KEY=0, CAPTION=예상활성여부, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strSHRN_ISCD = m_CommAgent.GetRealOutputData("O31", "SHRN_ISCD");		//종목 코드
CString strBSOP_HOUR = m_CommAgent.GetRealOutputData("O31", "BSOP_HOUR");		//호가 시간
CString strASKP1 = m_CommAgent.GetRealOutputData("O31", "ASKP1");		//매도호가1
CString strASKP1_CLR = m_CommAgent.GetRealOutputData("O31", "ASKP1_CLR");		//[ASKP1]색참조(+상승, -하락)
CString strASKP2 = m_CommAgent.GetRealOutputData("O31", "ASKP2");		//매도호가2
CString strASKP2_CLR = m_CommAgent.GetRealOutputData("O31", "ASKP2_CLR");		//[ASKP2]색참조(+상승, -하락)
CString strASKP3 = m_CommAgent.GetRealOutputData("O31", "ASKP3");		//매도호가3
CString strASKP3_CLR = m_CommAgent.GetRealOutputData("O31", "ASKP3_CLR");		//[ASKP3]색참조(+상승, -하락)
CString strASKP4 = m_CommAgent.GetRealOutputData("O31", "ASKP4");		//매도호가4
CString strASKP4_CLR = m_CommAgent.GetRealOutputData("O31", "ASKP4_CLR");		//[ASKP4]색참조(+상승, -하락)
CString strASKP5 = m_CommAgent.GetRealOutputData("O31", "ASKP5");		//매도호가5
CString strASKP5_CLR = m_CommAgent.GetRealOutputData("O31", "ASKP5_CLR");		//[ASKP5]색참조(+상승, -하락)
CString strBIDP1 = m_CommAgent.GetRealOutputData("O31", "BIDP1");		//매수호가1
CString strBIDP1_CLR = m_CommAgent.GetRealOutputData("O31", "BIDP1_CLR");		//[BIDP1]색참조(+상승, -하락)
CString strBIDP2 = m_CommAgent.GetRealOutputData("O31", "BIDP2");		//매수호가2
CString strBIDP2_CLR = m_CommAgent.GetRealOutputData("O31", "BIDP2_CLR");		//[BIDP2]색참조(+상승, -하락)
CString strBIDP3 = m_CommAgent.GetRealOutputData("O31", "BIDP3");		//매수호가3
CString strBIDP3_CLR = m_CommAgent.GetRealOutputData("O31", "BIDP3_CLR");		//[BIDP3]색참조(+상승, -하락)
CString strBIDP4 = m_CommAgent.GetRealOutputData("O31", "BIDP4");		//매수호가4
CString strBIDP4_CLR = m_CommAgent.GetRealOutputData("O31", "BIDP4_CLR");		//[BIDP4]색참조(+상승, -하락)
CString strBIDP5 = m_CommAgent.GetRealOutputData("O31", "BIDP5");		//매수호가5
CString strBIDP5_CLR = m_CommAgent.GetRealOutputData("O31", "BIDP5_CLR");		//[BIDP5]색참조(+상승, -하락)
CString strASKP_CSNU1 = m_CommAgent.GetRealOutputData("O31", "ASKP_CSNU1");		//매도호가 건수1
CString strASKP_CSNU2 = m_CommAgent.GetRealOutputData("O31", "ASKP_CSNU2");		//매도호가 건수2
CString strASKP_CSNU3 = m_CommAgent.GetRealOutputData("O31", "ASKP_CSNU3");		//매도호가 건수3
CString strASKP_CSNU4 = m_CommAgent.GetRealOutputData("O31", "ASKP_CSNU4");		//매도호가 건수4
CString strASKP_CSNU5 = m_CommAgent.GetRealOutputData("O31", "ASKP_CSNU5");		//매도호가 건수5
CString strBIDP_CSNU1 = m_CommAgent.GetRealOutputData("O31", "BIDP_CSNU1");		//매수호가 건수1
CString strBIDP_CSNU2 = m_CommAgent.GetRealOutputData("O31", "BIDP_CSNU2");		//매수호가 건수2
CString strBIDP_CSNU3 = m_CommAgent.GetRealOutputData("O31", "BIDP_CSNU3");		//매수호가 건수3
CString strBIDP_CSNU4 = m_CommAgent.GetRealOutputData("O31", "BIDP_CSNU4");		//매수호가 건수4
CString strBIDP_CSNU5 = m_CommAgent.GetRealOutputData("O31", "BIDP_CSNU5");		//매수호가 건수5
CString strASKP_RSQN1 = m_CommAgent.GetRealOutputData("O31", "ASKP_RSQN1");		//매도호가 잔량1
CString strASKP_RSQN2 = m_CommAgent.GetRealOutputData("O31", "ASKP_RSQN2");		//매도호가 잔량2
CString strASKP_RSQN3 = m_CommAgent.GetRealOutputData("O31", "ASKP_RSQN3");		//매도호가 잔량3
CString strASKP_RSQN4 = m_CommAgent.GetRealOutputData("O31", "ASKP_RSQN4");		//매도호가 잔량4
CString strASKP_RSQN5 = m_CommAgent.GetRealOutputData("O31", "ASKP_RSQN5");		//매도호가 잔량5
CString strBIDP_RSQN1 = m_CommAgent.GetRealOutputData("O31", "BIDP_RSQN1");		//매수호가 잔량1
CString strBIDP_RSQN2 = m_CommAgent.GetRealOutputData("O31", "BIDP_RSQN2");		//매수호가 잔량2
CString strBIDP_RSQN3 = m_CommAgent.GetRealOutputData("O31", "BIDP_RSQN3");		//매수호가 잔량3
CString strBIDP_RSQN4 = m_CommAgent.GetRealOutputData("O31", "BIDP_RSQN4");		//매수호가 잔량4
CString strBIDP_RSQN5 = m_CommAgent.GetRealOutputData("O31", "BIDP_RSQN5");		//매수호가 잔량5
CString strTOTAL_ASKP_CSNU = m_CommAgent.GetRealOutputData("O31", "TOTAL_ASKP_CSNU");		//총 매도호가 건수
CString strTOTAL_BIDP_CSNU = m_CommAgent.GetRealOutputData("O31", "TOTAL_BIDP_CSNU");		//총 매수호가 건수
CString strTOTAL_ASKP_RSQN = m_CommAgent.GetRealOutputData("O31", "TOTAL_ASKP_RSQN");		//총 매도호가 잔량
CString strTOTAL_BIDP_RSQN = m_CommAgent.GetRealOutputData("O31", "TOTAL_BIDP_RSQN");		//총 매수호가 잔량
CString strANTC_CNPR = m_CommAgent.GetRealOutputData("O31", "ANTC_CNPR");		//예상 체결가
CString strANTC_CNPR_CLR = m_CommAgent.GetRealOutputData("O31", "ANTC_CNPR_CLR");		//[ANTC_CNPR]색참조(+상승, -하락)
CString strANTC_CLS_CODE = m_CommAgent.GetRealOutputData("O31", "ANTC_CLS_CODE");		//예상 구분 코드
CString strANTC_ISS_YN = m_CommAgent.GetRealOutputData("O31", "ANTC_ISS_YN");		//예상활성여부




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strSHRN_ISCD = realCommRecvData.GetItem(0, 0);		//종목 코드
CString strBSOP_HOUR = realCommRecvData.GetItem(0, 1);		//호가 시간
CString strASKP1 = realCommRecvData.GetItem(0, 2);		//매도호가1
CString strASKP1_CLR = realCommRecvData.GetItem(0, 3);		//[ASKP1]색참조(+상승, -하락)
CString strASKP2 = realCommRecvData.GetItem(0, 4);		//매도호가2
CString strASKP2_CLR = realCommRecvData.GetItem(0, 5);		//[ASKP2]색참조(+상승, -하락)
CString strASKP3 = realCommRecvData.GetItem(0, 6);		//매도호가3
CString strASKP3_CLR = realCommRecvData.GetItem(0, 7);		//[ASKP3]색참조(+상승, -하락)
CString strASKP4 = realCommRecvData.GetItem(0, 8);		//매도호가4
CString strASKP4_CLR = realCommRecvData.GetItem(0, 9);		//[ASKP4]색참조(+상승, -하락)
CString strASKP5 = realCommRecvData.GetItem(0, 10);		//매도호가5
CString strASKP5_CLR = realCommRecvData.GetItem(0, 11);		//[ASKP5]색참조(+상승, -하락)
CString strBIDP1 = realCommRecvData.GetItem(0, 12);		//매수호가1
CString strBIDP1_CLR = realCommRecvData.GetItem(0, 13);		//[BIDP1]색참조(+상승, -하락)
CString strBIDP2 = realCommRecvData.GetItem(0, 14);		//매수호가2
CString strBIDP2_CLR = realCommRecvData.GetItem(0, 15);		//[BIDP2]색참조(+상승, -하락)
CString strBIDP3 = realCommRecvData.GetItem(0, 16);		//매수호가3
CString strBIDP3_CLR = realCommRecvData.GetItem(0, 17);		//[BIDP3]색참조(+상승, -하락)
CString strBIDP4 = realCommRecvData.GetItem(0, 18);		//매수호가4
CString strBIDP4_CLR = realCommRecvData.GetItem(0, 19);		//[BIDP4]색참조(+상승, -하락)
CString strBIDP5 = realCommRecvData.GetItem(0, 20);		//매수호가5
CString strBIDP5_CLR = realCommRecvData.GetItem(0, 21);		//[BIDP5]색참조(+상승, -하락)
CString strASKP_CSNU1 = realCommRecvData.GetItem(0, 22);		//매도호가 건수1
CString strASKP_CSNU2 = realCommRecvData.GetItem(0, 23);		//매도호가 건수2
CString strASKP_CSNU3 = realCommRecvData.GetItem(0, 24);		//매도호가 건수3
CString strASKP_CSNU4 = realCommRecvData.GetItem(0, 25);		//매도호가 건수4
CString strASKP_CSNU5 = realCommRecvData.GetItem(0, 26);		//매도호가 건수5
CString strBIDP_CSNU1 = realCommRecvData.GetItem(0, 27);		//매수호가 건수1
CString strBIDP_CSNU2 = realCommRecvData.GetItem(0, 28);		//매수호가 건수2
CString strBIDP_CSNU3 = realCommRecvData.GetItem(0, 29);		//매수호가 건수3
CString strBIDP_CSNU4 = realCommRecvData.GetItem(0, 30);		//매수호가 건수4
CString strBIDP_CSNU5 = realCommRecvData.GetItem(0, 31);		//매수호가 건수5
CString strASKP_RSQN1 = realCommRecvData.GetItem(0, 32);		//매도호가 잔량1
CString strASKP_RSQN2 = realCommRecvData.GetItem(0, 33);		//매도호가 잔량2
CString strASKP_RSQN3 = realCommRecvData.GetItem(0, 34);		//매도호가 잔량3
CString strASKP_RSQN4 = realCommRecvData.GetItem(0, 35);		//매도호가 잔량4
CString strASKP_RSQN5 = realCommRecvData.GetItem(0, 36);		//매도호가 잔량5
CString strBIDP_RSQN1 = realCommRecvData.GetItem(0, 37);		//매수호가 잔량1
CString strBIDP_RSQN2 = realCommRecvData.GetItem(0, 38);		//매수호가 잔량2
CString strBIDP_RSQN3 = realCommRecvData.GetItem(0, 39);		//매수호가 잔량3
CString strBIDP_RSQN4 = realCommRecvData.GetItem(0, 40);		//매수호가 잔량4
CString strBIDP_RSQN5 = realCommRecvData.GetItem(0, 41);		//매수호가 잔량5
CString strTOTAL_ASKP_CSNU = realCommRecvData.GetItem(0, 42);		//총 매도호가 건수
CString strTOTAL_BIDP_CSNU = realCommRecvData.GetItem(0, 43);		//총 매수호가 건수
CString strTOTAL_ASKP_RSQN = realCommRecvData.GetItem(0, 44);		//총 매도호가 잔량
CString strTOTAL_BIDP_RSQN = realCommRecvData.GetItem(0, 45);		//총 매수호가 잔량
CString strANTC_CNPR = realCommRecvData.GetItem(0, 46);		//예상 체결가
CString strANTC_CNPR_CLR = realCommRecvData.GetItem(0, 47);		//[ANTC_CNPR]색참조(+상승, -하락)
CString strANTC_CLS_CODE = realCommRecvData.GetItem(0, 48);		//예상 구분 코드
CString strANTC_ISS_YN = realCommRecvData.GetItem(0, 49);		//예상활성여부
