BEGIN_FUNCTION_MAP
	REAL_TYPE=131, REAL_NAME=V00, DESCRIPTION=FX마진 호가;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SCRN_INDC_PRDT_CD, TYPE=string, SIZE=32, KEY=1, CAPTION=FX 종목(HTS), FID=0;
			 INDEX=1, ITEM=QUOTE_IDX, TYPE=string, SIZE=10, KEY=0, CAPTION=Quote 순번, FID=0;
			 INDEX=2, ITEM=FCM_CD, TYPE=string, SIZE=10, KEY=0, CAPTION=FCM Code, FID=0;
			 INDEX=3, ITEM=FCM_DT, TYPE=string, SIZE=8, KEY=0, CAPTION=FCM Quote 일, FID=0;
			 INDEX=4, ITEM=FCM_TM, TYPE=string, SIZE=8, KEY=0, CAPTION=FCM Quote 시간, FID=0;
			 INDEX=5, ITEM=SPOT_RATE, TYPE=string, SIZE=13, KEY=0, CAPTION=Spot rate, FID=0;
			 INDEX=6, ITEM=DH_RATE_BUY, TYPE=string, SIZE=13, KEY=0, CAPTION=Buy, FID=0;
			 INDEX=7, ITEM=DH_RATE_BUY_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[DH_RATE_BUY]색참조(+상승, -하락), FID=0;
			 INDEX=8, ITEM=DH_RATE_SELL, TYPE=string, SIZE=13, KEY=0, CAPTION=Sell, FID=0;
			 INDEX=9, ITEM=DH_RATE_SELL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[DH_RATE_SELL]색참조(+상승, -하락), FID=0;
			 INDEX=10, ITEM=DH_RATE_HIGH, TYPE=string, SIZE=13, KEY=0, CAPTION=High, FID=0;
			 INDEX=11, ITEM=DH_RATE_LOW, TYPE=string, SIZE=13, KEY=0, CAPTION=Low, FID=0;
			 INDEX=12, ITEM=DH_SPRD, TYPE=string, SIZE=13, KEY=0, CAPTION=Spread, FID=0;
			 INDEX=13, ITEM=DH_SPRD_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[DH_SPRD]색참조(+상승, -하락), FID=0;
			 INDEX=14, ITEM=DH_PIP_BUY, TYPE=string, SIZE=13, KEY=0, CAPTION=PIP Cost Buy, FID=0;
			 INDEX=15, ITEM=DH_PIP_SELL, TYPE=string, SIZE=13, KEY=0, CAPTION=PIP Cost Sell, FID=0;
			 INDEX=16, ITEM=DH_PIP_MID, TYPE=string, SIZE=13, KEY=0, CAPTION=PIP Cost Mid, FID=0;
			 INDEX=17, ITEM=DH_BUY_IR, TYPE=string, SIZE=13, KEY=0, CAPTION=Buy IR, FID=1220;
			 INDEX=18, ITEM=DH_SELL_IR, TYPE=string, SIZE=13, KEY=0, CAPTION=Sell IR, FID=1221;
			 INDEX=19, ITEM=DH_BUY_OPEN, TYPE=string, SIZE=13, KEY=0, CAPTION=Buy Open, FID=0;
			 INDEX=20, ITEM=DH_BUY_HIGH, TYPE=string, SIZE=13, KEY=0, CAPTION=Buy High, FID=0;
			 INDEX=21, ITEM=DH_BUY_LOW, TYPE=string, SIZE=13, KEY=0, CAPTION=Buy Low, FID=0;
			 INDEX=22, ITEM=DH_SELL_OPEN, TYPE=string, SIZE=13, KEY=0, CAPTION=Sell Open, FID=0;
			 INDEX=23, ITEM=DH_SELL_HIGH, TYPE=string, SIZE=13, KEY=0, CAPTION=Sell High, FID=0;
			 INDEX=24, ITEM=DH_SELL_LOW, TYPE=string, SIZE=13, KEY=0, CAPTION=Sell Low, FID=0;
			 INDEX=25, ITEM=DH_SPRD_UPDN, TYPE=string, SIZE=1, KEY=0, CAPTION=SPRD UP/DOWN, FID=2466;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strSCRN_INDC_PRDT_CD = m_CommAgent.GetRealOutputData("V00", "SCRN_INDC_PRDT_CD");		//FX 종목(HTS)
CString strQUOTE_IDX = m_CommAgent.GetRealOutputData("V00", "QUOTE_IDX");		//Quote 순번
CString strFCM_CD = m_CommAgent.GetRealOutputData("V00", "FCM_CD");		//FCM Code
CString strFCM_DT = m_CommAgent.GetRealOutputData("V00", "FCM_DT");		//FCM Quote 일
CString strFCM_TM = m_CommAgent.GetRealOutputData("V00", "FCM_TM");		//FCM Quote 시간
CString strSPOT_RATE = m_CommAgent.GetRealOutputData("V00", "SPOT_RATE");		//Spot rate
CString strDH_RATE_BUY = m_CommAgent.GetRealOutputData("V00", "DH_RATE_BUY");		//Buy
CString strDH_RATE_BUY_CLR = m_CommAgent.GetRealOutputData("V00", "DH_RATE_BUY_CLR");		//[DH_RATE_BUY]색참조(+상승, -하락)
CString strDH_RATE_SELL = m_CommAgent.GetRealOutputData("V00", "DH_RATE_SELL");		//Sell
CString strDH_RATE_SELL_CLR = m_CommAgent.GetRealOutputData("V00", "DH_RATE_SELL_CLR");		//[DH_RATE_SELL]색참조(+상승, -하락)
CString strDH_RATE_HIGH = m_CommAgent.GetRealOutputData("V00", "DH_RATE_HIGH");		//High
CString strDH_RATE_LOW = m_CommAgent.GetRealOutputData("V00", "DH_RATE_LOW");		//Low
CString strDH_SPRD = m_CommAgent.GetRealOutputData("V00", "DH_SPRD");		//Spread
CString strDH_SPRD_CLR = m_CommAgent.GetRealOutputData("V00", "DH_SPRD_CLR");		//[DH_SPRD]색참조(+상승, -하락)
CString strDH_PIP_BUY = m_CommAgent.GetRealOutputData("V00", "DH_PIP_BUY");		//PIP Cost Buy
CString strDH_PIP_SELL = m_CommAgent.GetRealOutputData("V00", "DH_PIP_SELL");		//PIP Cost Sell
CString strDH_PIP_MID = m_CommAgent.GetRealOutputData("V00", "DH_PIP_MID");		//PIP Cost Mid
CString strDH_BUY_IR = m_CommAgent.GetRealOutputData("V00", "DH_BUY_IR");		//Buy IR
CString strDH_SELL_IR = m_CommAgent.GetRealOutputData("V00", "DH_SELL_IR");		//Sell IR
CString strDH_BUY_OPEN = m_CommAgent.GetRealOutputData("V00", "DH_BUY_OPEN");		//Buy Open
CString strDH_BUY_HIGH = m_CommAgent.GetRealOutputData("V00", "DH_BUY_HIGH");		//Buy High
CString strDH_BUY_LOW = m_CommAgent.GetRealOutputData("V00", "DH_BUY_LOW");		//Buy Low
CString strDH_SELL_OPEN = m_CommAgent.GetRealOutputData("V00", "DH_SELL_OPEN");		//Sell Open
CString strDH_SELL_HIGH = m_CommAgent.GetRealOutputData("V00", "DH_SELL_HIGH");		//Sell High
CString strDH_SELL_LOW = m_CommAgent.GetRealOutputData("V00", "DH_SELL_LOW");		//Sell Low
CString strDH_SPRD_UPDN = m_CommAgent.GetRealOutputData("V00", "DH_SPRD_UPDN");		//SPRD UP/DOWN




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strSCRN_INDC_PRDT_CD = realCommRecvData.GetItem(0, 0);		//FX 종목(HTS)
CString strQUOTE_IDX = realCommRecvData.GetItem(0, 1);		//Quote 순번
CString strFCM_CD = realCommRecvData.GetItem(0, 2);		//FCM Code
CString strFCM_DT = realCommRecvData.GetItem(0, 3);		//FCM Quote 일
CString strFCM_TM = realCommRecvData.GetItem(0, 4);		//FCM Quote 시간
CString strSPOT_RATE = realCommRecvData.GetItem(0, 5);		//Spot rate
CString strDH_RATE_BUY = realCommRecvData.GetItem(0, 6);		//Buy
CString strDH_RATE_BUY_CLR = realCommRecvData.GetItem(0, 7);		//[DH_RATE_BUY]색참조(+상승, -하락)
CString strDH_RATE_SELL = realCommRecvData.GetItem(0, 8);		//Sell
CString strDH_RATE_SELL_CLR = realCommRecvData.GetItem(0, 9);		//[DH_RATE_SELL]색참조(+상승, -하락)
CString strDH_RATE_HIGH = realCommRecvData.GetItem(0, 10);		//High
CString strDH_RATE_LOW = realCommRecvData.GetItem(0, 11);		//Low
CString strDH_SPRD = realCommRecvData.GetItem(0, 12);		//Spread
CString strDH_SPRD_CLR = realCommRecvData.GetItem(0, 13);		//[DH_SPRD]색참조(+상승, -하락)
CString strDH_PIP_BUY = realCommRecvData.GetItem(0, 14);		//PIP Cost Buy
CString strDH_PIP_SELL = realCommRecvData.GetItem(0, 15);		//PIP Cost Sell
CString strDH_PIP_MID = realCommRecvData.GetItem(0, 16);		//PIP Cost Mid
CString strDH_BUY_IR = realCommRecvData.GetItem(0, 17);		//Buy IR
CString strDH_SELL_IR = realCommRecvData.GetItem(0, 18);		//Sell IR
CString strDH_BUY_OPEN = realCommRecvData.GetItem(0, 19);		//Buy Open
CString strDH_BUY_HIGH = realCommRecvData.GetItem(0, 20);		//Buy High
CString strDH_BUY_LOW = realCommRecvData.GetItem(0, 21);		//Buy Low
CString strDH_SELL_OPEN = realCommRecvData.GetItem(0, 22);		//Sell Open
CString strDH_SELL_HIGH = realCommRecvData.GetItem(0, 23);		//Sell High
CString strDH_SELL_LOW = realCommRecvData.GetItem(0, 24);		//Sell Low
CString strDH_SPRD_UPDN = realCommRecvData.GetItem(0, 25);		//SPRD UP/DOWN
