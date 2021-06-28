BEGIN_FUNCTION_MAP
	REAL_TYPE=69, REAL_NAME=O91, DESCRIPTION=미니지수옵션 호가;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SHRN_ISCD, TYPE=string, SIZE=9, KEY=1, CAPTION=종목코드, FID=0;
			 INDEX=1, ITEM=BSOP_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=호가시간, FID=0;
			 INDEX=2, ITEM=ASKP1, TYPE=string, SIZE=18, KEY=0, CAPTION=1매도호가, FID=0;
			 INDEX=3, ITEM=ASKP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP1]색참조(+상승, -하락), FID=0;
			 INDEX=4, ITEM=ASKP2, TYPE=string, SIZE=18, KEY=0, CAPTION=2매도호가, FID=0;
			 INDEX=5, ITEM=ASKP2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP2]색참조(+상승, -하락), FID=0;
			 INDEX=6, ITEM=ASKP3, TYPE=string, SIZE=18, KEY=0, CAPTION=3매도호가, FID=0;
			 INDEX=7, ITEM=ASKP3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP3]색참조(+상승, -하락), FID=0;
			 INDEX=8, ITEM=ASKP4, TYPE=string, SIZE=18, KEY=0, CAPTION=4매도호가, FID=0;
			 INDEX=9, ITEM=ASKP4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP4]색참조(+상승, -하락), FID=0;
			 INDEX=10, ITEM=ASKP5, TYPE=string, SIZE=18, KEY=0, CAPTION=5매도호가, FID=0;
			 INDEX=11, ITEM=ASKP5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP5]색참조(+상승, -하락), FID=0;
			 INDEX=12, ITEM=BIDP1, TYPE=string, SIZE=18, KEY=0, CAPTION=1매수호가, FID=0;
			 INDEX=13, ITEM=BIDP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP1]색참조(+상승, -하락), FID=0;
			 INDEX=14, ITEM=BIDP2, TYPE=string, SIZE=18, KEY=0, CAPTION=2매수호가, FID=0;
			 INDEX=15, ITEM=BIDP2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP2]색참조(+상승, -하락), FID=0;
			 INDEX=16, ITEM=BIDP3, TYPE=string, SIZE=18, KEY=0, CAPTION=3매수호가, FID=0;
			 INDEX=17, ITEM=BIDP3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP3]색참조(+상승, -하락), FID=0;
			 INDEX=18, ITEM=BIDP4, TYPE=string, SIZE=18, KEY=0, CAPTION=4매수호가, FID=0;
			 INDEX=19, ITEM=BIDP4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP4]색참조(+상승, -하락), FID=0;
			 INDEX=20, ITEM=BIDP5, TYPE=string, SIZE=18, KEY=0, CAPTION=5매수호가, FID=0;
			 INDEX=21, ITEM=BIDP5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP5]색참조(+상승, -하락), FID=0;
			 INDEX=22, ITEM=ASKP_CSNU1, TYPE=string, SIZE=12, KEY=0, CAPTION=1매도호가 건수, FID=0;
			 INDEX=23, ITEM=ASKP_CSNU2, TYPE=string, SIZE=12, KEY=0, CAPTION=2매도호가 건수, FID=0;
			 INDEX=24, ITEM=ASKP_CSNU3, TYPE=string, SIZE=12, KEY=0, CAPTION=3매도호가 건수, FID=0;
			 INDEX=25, ITEM=ASKP_CSNU4, TYPE=string, SIZE=12, KEY=0, CAPTION=4매도호가 건수, FID=0;
			 INDEX=26, ITEM=ASKP_CSNU5, TYPE=string, SIZE=12, KEY=0, CAPTION=5매도호가 건수, FID=0;
			 INDEX=27, ITEM=BIDP_CSNU1, TYPE=string, SIZE=12, KEY=0, CAPTION=1매수호가 건수, FID=0;
			 INDEX=28, ITEM=BIDP_CSNU2, TYPE=string, SIZE=12, KEY=0, CAPTION=2매수호가 건수, FID=0;
			 INDEX=29, ITEM=BIDP_CSNU3, TYPE=string, SIZE=12, KEY=0, CAPTION=3매수호가 건수, FID=0;
			 INDEX=30, ITEM=BIDP_CSNU4, TYPE=string, SIZE=12, KEY=0, CAPTION=4매수호가 건수, FID=0;
			 INDEX=31, ITEM=BIDP_CSNU5, TYPE=string, SIZE=12, KEY=0, CAPTION=5매수호가 건수, FID=0;
			 INDEX=32, ITEM=ASKP_RSQN1, TYPE=string, SIZE=18, KEY=0, CAPTION=1매도호가 잔량, FID=0;
			 INDEX=33, ITEM=ASKP_RSQN2, TYPE=string, SIZE=18, KEY=0, CAPTION=2매도호가 잔량, FID=0;
			 INDEX=34, ITEM=ASKP_RSQN3, TYPE=string, SIZE=18, KEY=0, CAPTION=3매도호가 잔량, FID=0;
			 INDEX=35, ITEM=ASKP_RSQN4, TYPE=string, SIZE=18, KEY=0, CAPTION=4매도호가 잔량, FID=0;
			 INDEX=36, ITEM=ASKP_RSQN5, TYPE=string, SIZE=18, KEY=0, CAPTION=5매도호가 잔량, FID=0;
			 INDEX=37, ITEM=BIDP_RSQN1, TYPE=string, SIZE=18, KEY=0, CAPTION=1매수호가 잔량, FID=0;
			 INDEX=38, ITEM=BIDP_RSQN2, TYPE=string, SIZE=18, KEY=0, CAPTION=2매수호가 잔량, FID=0;
			 INDEX=39, ITEM=BIDP_RSQN3, TYPE=string, SIZE=18, KEY=0, CAPTION=3매수호가 잔량, FID=0;
			 INDEX=40, ITEM=BIDP_RSQN4, TYPE=string, SIZE=18, KEY=0, CAPTION=4매수호가 잔량, FID=0;
			 INDEX=41, ITEM=BIDP_RSQN5, TYPE=string, SIZE=18, KEY=0, CAPTION=5매수호가 잔량, FID=0;
			 INDEX=42, ITEM=TOTAL_ASKP_CSNU, TYPE=string, SIZE=12, KEY=0, CAPTION=총 매도호가 건수, FID=0;
			 INDEX=43, ITEM=TOTAL_BIDP_CSNU, TYPE=string, SIZE=12, KEY=0, CAPTION=총 매수호가 건수, FID=0;
			 INDEX=44, ITEM=TOTAL_ASKP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=총 매도호가 잔량, FID=0;
			 INDEX=45, ITEM=TOTAL_BIDP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=총 매수호가 잔량, FID=0;
			 INDEX=46, ITEM=ANTC_CNPR, TYPE=string, SIZE=18, KEY=0, CAPTION=예상 체결 가격, FID=0;
			 INDEX=47, ITEM=ANTC_CNPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ANTC_CNPR]색참조(+상승, -하락), FID=0;
			 INDEX=48, ITEM=ANTC_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=예상구분코드, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strSHRN_ISCD = m_CommAgent.GetRealOutputData("O91", "SHRN_ISCD");		//종목코드
CString strBSOP_HOUR = m_CommAgent.GetRealOutputData("O91", "BSOP_HOUR");		//호가시간
CString strASKP1 = m_CommAgent.GetRealOutputData("O91", "ASKP1");		//1매도호가
CString strASKP1_CLR = m_CommAgent.GetRealOutputData("O91", "ASKP1_CLR");		//[ASKP1]색참조(+상승, -하락)
CString strASKP2 = m_CommAgent.GetRealOutputData("O91", "ASKP2");		//2매도호가
CString strASKP2_CLR = m_CommAgent.GetRealOutputData("O91", "ASKP2_CLR");		//[ASKP2]색참조(+상승, -하락)
CString strASKP3 = m_CommAgent.GetRealOutputData("O91", "ASKP3");		//3매도호가
CString strASKP3_CLR = m_CommAgent.GetRealOutputData("O91", "ASKP3_CLR");		//[ASKP3]색참조(+상승, -하락)
CString strASKP4 = m_CommAgent.GetRealOutputData("O91", "ASKP4");		//4매도호가
CString strASKP4_CLR = m_CommAgent.GetRealOutputData("O91", "ASKP4_CLR");		//[ASKP4]색참조(+상승, -하락)
CString strASKP5 = m_CommAgent.GetRealOutputData("O91", "ASKP5");		//5매도호가
CString strASKP5_CLR = m_CommAgent.GetRealOutputData("O91", "ASKP5_CLR");		//[ASKP5]색참조(+상승, -하락)
CString strBIDP1 = m_CommAgent.GetRealOutputData("O91", "BIDP1");		//1매수호가
CString strBIDP1_CLR = m_CommAgent.GetRealOutputData("O91", "BIDP1_CLR");		//[BIDP1]색참조(+상승, -하락)
CString strBIDP2 = m_CommAgent.GetRealOutputData("O91", "BIDP2");		//2매수호가
CString strBIDP2_CLR = m_CommAgent.GetRealOutputData("O91", "BIDP2_CLR");		//[BIDP2]색참조(+상승, -하락)
CString strBIDP3 = m_CommAgent.GetRealOutputData("O91", "BIDP3");		//3매수호가
CString strBIDP3_CLR = m_CommAgent.GetRealOutputData("O91", "BIDP3_CLR");		//[BIDP3]색참조(+상승, -하락)
CString strBIDP4 = m_CommAgent.GetRealOutputData("O91", "BIDP4");		//4매수호가
CString strBIDP4_CLR = m_CommAgent.GetRealOutputData("O91", "BIDP4_CLR");		//[BIDP4]색참조(+상승, -하락)
CString strBIDP5 = m_CommAgent.GetRealOutputData("O91", "BIDP5");		//5매수호가
CString strBIDP5_CLR = m_CommAgent.GetRealOutputData("O91", "BIDP5_CLR");		//[BIDP5]색참조(+상승, -하락)
CString strASKP_CSNU1 = m_CommAgent.GetRealOutputData("O91", "ASKP_CSNU1");		//1매도호가 건수
CString strASKP_CSNU2 = m_CommAgent.GetRealOutputData("O91", "ASKP_CSNU2");		//2매도호가 건수
CString strASKP_CSNU3 = m_CommAgent.GetRealOutputData("O91", "ASKP_CSNU3");		//3매도호가 건수
CString strASKP_CSNU4 = m_CommAgent.GetRealOutputData("O91", "ASKP_CSNU4");		//4매도호가 건수
CString strASKP_CSNU5 = m_CommAgent.GetRealOutputData("O91", "ASKP_CSNU5");		//5매도호가 건수
CString strBIDP_CSNU1 = m_CommAgent.GetRealOutputData("O91", "BIDP_CSNU1");		//1매수호가 건수
CString strBIDP_CSNU2 = m_CommAgent.GetRealOutputData("O91", "BIDP_CSNU2");		//2매수호가 건수
CString strBIDP_CSNU3 = m_CommAgent.GetRealOutputData("O91", "BIDP_CSNU3");		//3매수호가 건수
CString strBIDP_CSNU4 = m_CommAgent.GetRealOutputData("O91", "BIDP_CSNU4");		//4매수호가 건수
CString strBIDP_CSNU5 = m_CommAgent.GetRealOutputData("O91", "BIDP_CSNU5");		//5매수호가 건수
CString strASKP_RSQN1 = m_CommAgent.GetRealOutputData("O91", "ASKP_RSQN1");		//1매도호가 잔량
CString strASKP_RSQN2 = m_CommAgent.GetRealOutputData("O91", "ASKP_RSQN2");		//2매도호가 잔량
CString strASKP_RSQN3 = m_CommAgent.GetRealOutputData("O91", "ASKP_RSQN3");		//3매도호가 잔량
CString strASKP_RSQN4 = m_CommAgent.GetRealOutputData("O91", "ASKP_RSQN4");		//4매도호가 잔량
CString strASKP_RSQN5 = m_CommAgent.GetRealOutputData("O91", "ASKP_RSQN5");		//5매도호가 잔량
CString strBIDP_RSQN1 = m_CommAgent.GetRealOutputData("O91", "BIDP_RSQN1");		//1매수호가 잔량
CString strBIDP_RSQN2 = m_CommAgent.GetRealOutputData("O91", "BIDP_RSQN2");		//2매수호가 잔량
CString strBIDP_RSQN3 = m_CommAgent.GetRealOutputData("O91", "BIDP_RSQN3");		//3매수호가 잔량
CString strBIDP_RSQN4 = m_CommAgent.GetRealOutputData("O91", "BIDP_RSQN4");		//4매수호가 잔량
CString strBIDP_RSQN5 = m_CommAgent.GetRealOutputData("O91", "BIDP_RSQN5");		//5매수호가 잔량
CString strTOTAL_ASKP_CSNU = m_CommAgent.GetRealOutputData("O91", "TOTAL_ASKP_CSNU");		//총 매도호가 건수
CString strTOTAL_BIDP_CSNU = m_CommAgent.GetRealOutputData("O91", "TOTAL_BIDP_CSNU");		//총 매수호가 건수
CString strTOTAL_ASKP_RSQN = m_CommAgent.GetRealOutputData("O91", "TOTAL_ASKP_RSQN");		//총 매도호가 잔량
CString strTOTAL_BIDP_RSQN = m_CommAgent.GetRealOutputData("O91", "TOTAL_BIDP_RSQN");		//총 매수호가 잔량
CString strANTC_CNPR = m_CommAgent.GetRealOutputData("O91", "ANTC_CNPR");		//예상 체결 가격
CString strANTC_CNPR_CLR = m_CommAgent.GetRealOutputData("O91", "ANTC_CNPR_CLR");		//[ANTC_CNPR]색참조(+상승, -하락)
CString strANTC_CLS_CODE = m_CommAgent.GetRealOutputData("O91", "ANTC_CLS_CODE");		//예상구분코드




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
CString strBIDP1 = realCommRecvData.GetItem(0, 12);		//1매수호가
CString strBIDP1_CLR = realCommRecvData.GetItem(0, 13);		//[BIDP1]색참조(+상승, -하락)
CString strBIDP2 = realCommRecvData.GetItem(0, 14);		//2매수호가
CString strBIDP2_CLR = realCommRecvData.GetItem(0, 15);		//[BIDP2]색참조(+상승, -하락)
CString strBIDP3 = realCommRecvData.GetItem(0, 16);		//3매수호가
CString strBIDP3_CLR = realCommRecvData.GetItem(0, 17);		//[BIDP3]색참조(+상승, -하락)
CString strBIDP4 = realCommRecvData.GetItem(0, 18);		//4매수호가
CString strBIDP4_CLR = realCommRecvData.GetItem(0, 19);		//[BIDP4]색참조(+상승, -하락)
CString strBIDP5 = realCommRecvData.GetItem(0, 20);		//5매수호가
CString strBIDP5_CLR = realCommRecvData.GetItem(0, 21);		//[BIDP5]색참조(+상승, -하락)
CString strASKP_CSNU1 = realCommRecvData.GetItem(0, 22);		//1매도호가 건수
CString strASKP_CSNU2 = realCommRecvData.GetItem(0, 23);		//2매도호가 건수
CString strASKP_CSNU3 = realCommRecvData.GetItem(0, 24);		//3매도호가 건수
CString strASKP_CSNU4 = realCommRecvData.GetItem(0, 25);		//4매도호가 건수
CString strASKP_CSNU5 = realCommRecvData.GetItem(0, 26);		//5매도호가 건수
CString strBIDP_CSNU1 = realCommRecvData.GetItem(0, 27);		//1매수호가 건수
CString strBIDP_CSNU2 = realCommRecvData.GetItem(0, 28);		//2매수호가 건수
CString strBIDP_CSNU3 = realCommRecvData.GetItem(0, 29);		//3매수호가 건수
CString strBIDP_CSNU4 = realCommRecvData.GetItem(0, 30);		//4매수호가 건수
CString strBIDP_CSNU5 = realCommRecvData.GetItem(0, 31);		//5매수호가 건수
CString strASKP_RSQN1 = realCommRecvData.GetItem(0, 32);		//1매도호가 잔량
CString strASKP_RSQN2 = realCommRecvData.GetItem(0, 33);		//2매도호가 잔량
CString strASKP_RSQN3 = realCommRecvData.GetItem(0, 34);		//3매도호가 잔량
CString strASKP_RSQN4 = realCommRecvData.GetItem(0, 35);		//4매도호가 잔량
CString strASKP_RSQN5 = realCommRecvData.GetItem(0, 36);		//5매도호가 잔량
CString strBIDP_RSQN1 = realCommRecvData.GetItem(0, 37);		//1매수호가 잔량
CString strBIDP_RSQN2 = realCommRecvData.GetItem(0, 38);		//2매수호가 잔량
CString strBIDP_RSQN3 = realCommRecvData.GetItem(0, 39);		//3매수호가 잔량
CString strBIDP_RSQN4 = realCommRecvData.GetItem(0, 40);		//4매수호가 잔량
CString strBIDP_RSQN5 = realCommRecvData.GetItem(0, 41);		//5매수호가 잔량
CString strTOTAL_ASKP_CSNU = realCommRecvData.GetItem(0, 42);		//총 매도호가 건수
CString strTOTAL_BIDP_CSNU = realCommRecvData.GetItem(0, 43);		//총 매수호가 건수
CString strTOTAL_ASKP_RSQN = realCommRecvData.GetItem(0, 44);		//총 매도호가 잔량
CString strTOTAL_BIDP_RSQN = realCommRecvData.GetItem(0, 45);		//총 매수호가 잔량
CString strANTC_CNPR = realCommRecvData.GetItem(0, 46);		//예상 체결 가격
CString strANTC_CNPR_CLR = realCommRecvData.GetItem(0, 47);		//[ANTC_CNPR]색참조(+상승, -하락)
CString strANTC_CLS_CODE = realCommRecvData.GetItem(0, 48);		//예상구분코드
