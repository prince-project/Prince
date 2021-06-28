BEGIN_FUNCTION_MAP
	REAL_TYPE=133, REAL_NAME=V11, DESCRIPTION=해외선물 호가;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=PRDT_CD, TYPE=string, SIZE=15, KEY=1, CAPTION=종목코드(내부), FID=0;
			 INDEX=1, ITEM=QUOTE_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=호가일자, FID=0;
			 INDEX=2, ITEM=QUOTE_TIME, TYPE=string, SIZE=6, KEY=0, CAPTION=호가시간, FID=0;
			 INDEX=3, ITEM=KQUOTE_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=한국호가일자, FID=0;
			 INDEX=4, ITEM=KQUOTE_TIME, TYPE=string, SIZE=6, KEY=0, CAPTION=한국호가시간, FID=0;
			 INDEX=5, ITEM=RPT_SEQ, TYPE=string, SIZE=8, KEY=0, CAPTION=seq, FID=0;
			 INDEX=6, ITEM=TRADE_SESSION_ID, TYPE=string, SIZE=1, KEY=0, CAPTION=장구분, FID=0;
			 INDEX=7, ITEM=BEST_BID1, TYPE=string, SIZE=20, KEY=0, CAPTION=매수1호가, FID=0;
			 INDEX=8, ITEM=BEST_BID1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BEST_BID1]색참조(+상승, -하락), FID=0;
			 INDEX=9, ITEM=BEST_BSIZ1, TYPE=string, SIZE=12, KEY=0, CAPTION=매수1호가수량, FID=0;
			 INDEX=10, ITEM=BEST_BCNT1, TYPE=string, SIZE=7, KEY=0, CAPTION=매수1호가건수, FID=0;
			 INDEX=11, ITEM=BEST_BID2, TYPE=string, SIZE=20, KEY=0, CAPTION=매수2호가, FID=0;
			 INDEX=12, ITEM=BEST_BID2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BEST_BID2]색참조(+상승, -하락), FID=0;
			 INDEX=13, ITEM=BEST_BSIZ2, TYPE=string, SIZE=12, KEY=0, CAPTION=매수2호가수량, FID=0;
			 INDEX=14, ITEM=BEST_BCNT2, TYPE=string, SIZE=7, KEY=0, CAPTION=메수2호가건수, FID=0;
			 INDEX=15, ITEM=BEST_BID3, TYPE=string, SIZE=20, KEY=0, CAPTION=매수3호가, FID=0;
			 INDEX=16, ITEM=BEST_BID3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BEST_BID3]색참조(+상승, -하락), FID=0;
			 INDEX=17, ITEM=BEST_BSIZ3, TYPE=string, SIZE=12, KEY=0, CAPTION=매수3호가수량, FID=0;
			 INDEX=18, ITEM=BEST_BCNT3, TYPE=string, SIZE=7, KEY=0, CAPTION=매수3호가건수, FID=0;
			 INDEX=19, ITEM=BEST_BID4, TYPE=string, SIZE=20, KEY=0, CAPTION=매수4호가, FID=0;
			 INDEX=20, ITEM=BEST_BID4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BEST_BID4]색참조(+상승, -하락), FID=0;
			 INDEX=21, ITEM=BEST_BSIZ4, TYPE=string, SIZE=12, KEY=0, CAPTION=매수4호가수량, FID=0;
			 INDEX=22, ITEM=BEST_BCNT4, TYPE=string, SIZE=7, KEY=0, CAPTION=매수4호가건수, FID=0;
			 INDEX=23, ITEM=BEST_BID5, TYPE=string, SIZE=20, KEY=0, CAPTION=매수5호가, FID=0;
			 INDEX=24, ITEM=BEST_BID5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BEST_BID5]색참조(+상승, -하락), FID=0;
			 INDEX=25, ITEM=BEST_BSIZ5, TYPE=string, SIZE=12, KEY=0, CAPTION=매수5호가수량, FID=0;
			 INDEX=26, ITEM=BEST_BCNT5, TYPE=string, SIZE=7, KEY=0, CAPTION=매수5호가건수, FID=0;
			 INDEX=27, ITEM=BIDSIZE, TYPE=string, SIZE=15, KEY=0, CAPTION=매수총호가수량, FID=0;
			 INDEX=28, ITEM=BIDCNT, TYPE=string, SIZE=10, KEY=0, CAPTION=매수 전체건수, FID=0;
			 INDEX=29, ITEM=BEST_ASK1, TYPE=string, SIZE=20, KEY=0, CAPTION=매도1호가, FID=0;
			 INDEX=30, ITEM=BEST_ASK1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BEST_ASK1]색참조(+상승, -하락), FID=0;
			 INDEX=31, ITEM=BEST_ASIZ1, TYPE=string, SIZE=12, KEY=0, CAPTION=매도1호가수량, FID=0;
			 INDEX=32, ITEM=BEST_ACNT1, TYPE=string, SIZE=7, KEY=0, CAPTION=매도1호가건수, FID=0;
			 INDEX=33, ITEM=BEST_ASK2, TYPE=string, SIZE=20, KEY=0, CAPTION=매도2호가, FID=0;
			 INDEX=34, ITEM=BEST_ASK2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BEST_ASK2]색참조(+상승, -하락), FID=0;
			 INDEX=35, ITEM=BEST_ASIZ2, TYPE=string, SIZE=12, KEY=0, CAPTION=매도2호가수량, FID=0;
			 INDEX=36, ITEM=BEST_ACNT2, TYPE=string, SIZE=7, KEY=0, CAPTION=매도2호가건수, FID=0;
			 INDEX=37, ITEM=BEST_ASK3, TYPE=string, SIZE=20, KEY=0, CAPTION=매도3호가, FID=0;
			 INDEX=38, ITEM=BEST_ASK3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BEST_ASK3]색참조(+상승, -하락), FID=0;
			 INDEX=39, ITEM=BEST_ASIZ3, TYPE=string, SIZE=12, KEY=0, CAPTION=매도3호가수량, FID=0;
			 INDEX=40, ITEM=BEST_ACNT3, TYPE=string, SIZE=7, KEY=0, CAPTION=매도3호가건수, FID=0;
			 INDEX=41, ITEM=BEST_ASK4, TYPE=string, SIZE=20, KEY=0, CAPTION=매도4호가, FID=0;
			 INDEX=42, ITEM=BEST_ASK4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BEST_ASK4]색참조(+상승, -하락), FID=0;
			 INDEX=43, ITEM=BEST_ASIZ4, TYPE=string, SIZE=12, KEY=0, CAPTION=매도4호가수량, FID=0;
			 INDEX=44, ITEM=BEST_ACNT4, TYPE=string, SIZE=7, KEY=0, CAPTION=매도4호가건수, FID=0;
			 INDEX=45, ITEM=BEST_ASK5, TYPE=string, SIZE=20, KEY=0, CAPTION=매도5호가, FID=0;
			 INDEX=46, ITEM=BEST_ASK5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BEST_ASK5]색참조(+상승, -하락), FID=0;
			 INDEX=47, ITEM=BEST_ASIZ5, TYPE=string, SIZE=12, KEY=0, CAPTION=매도5호가수량, FID=0;
			 INDEX=48, ITEM=BEST_ACNT5, TYPE=string, SIZE=7, KEY=0, CAPTION=매도5호가건수, FID=0;
			 INDEX=49, ITEM=ASKSIZE, TYPE=string, SIZE=15, KEY=0, CAPTION=매도총호가수량, FID=0;
			 INDEX=50, ITEM=ASKCNT, TYPE=string, SIZE=10, KEY=0, CAPTION=매도 전체건수, FID=0;
			 INDEX=51, ITEM=BID_ASK_SIZE_DIFF, TYPE=string, SIZE=15, KEY=0, CAPTION=매수매도 수량차, FID=0;
			 INDEX=52, ITEM=BEST_BSIZ_ICDC1, TYPE=string, SIZE=20, KEY=0, CAPTION=매수1호가수량 증감, FID=0;
			 INDEX=53, ITEM=BEST_BSIZ_ICDC2, TYPE=string, SIZE=20, KEY=0, CAPTION=매수2호가수량 증감, FID=0;
			 INDEX=54, ITEM=BEST_BSIZ_ICDC3, TYPE=string, SIZE=20, KEY=0, CAPTION=매수3호가수량 증감, FID=0;
			 INDEX=55, ITEM=BEST_BSIZ_ICDC4, TYPE=string, SIZE=20, KEY=0, CAPTION=매수4호가수량 증감, FID=0;
			 INDEX=56, ITEM=BEST_BSIZ_ICDC5, TYPE=string, SIZE=20, KEY=0, CAPTION=매수5호가수량 증감, FID=0;
			 INDEX=57, ITEM=BIDSIZE_ICDC, TYPE=string, SIZE=20, KEY=0, CAPTION=매수총호가수량 증감, FID=0;
			 INDEX=58, ITEM=BEST_ASIZ_ICDC1, TYPE=string, SIZE=20, KEY=0, CAPTION=매도1호가수량 증감, FID=0;
			 INDEX=59, ITEM=BEST_ASIZ_ICDC2, TYPE=string, SIZE=20, KEY=0, CAPTION=매도2호가수량 증감, FID=0;
			 INDEX=60, ITEM=BEST_ASIZ_ICDC3, TYPE=string, SIZE=20, KEY=0, CAPTION=매도3호가수량 증감, FID=0;
			 INDEX=61, ITEM=BEST_ASIZ_ICDC4, TYPE=string, SIZE=20, KEY=0, CAPTION=매도4호가수량 증감, FID=0;
			 INDEX=62, ITEM=BEST_ASIZ_ICDC5, TYPE=string, SIZE=20, KEY=0, CAPTION=매도5호가수량 증감, FID=0;
			 INDEX=63, ITEM=ASKSIZE_ICDC, TYPE=string, SIZE=20, KEY=0, CAPTION=매도총호가수량 증감, FID=0;
			 INDEX=64, ITEM=DATETIME, TYPE=string, SIZE=14, KEY=0, CAPTION=수신시간, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strPRDT_CD = m_CommAgent.GetRealOutputData("V11", "PRDT_CD");		//종목코드(내부)
CString strQUOTE_DATE = m_CommAgent.GetRealOutputData("V11", "QUOTE_DATE");		//호가일자
CString strQUOTE_TIME = m_CommAgent.GetRealOutputData("V11", "QUOTE_TIME");		//호가시간
CString strKQUOTE_DATE = m_CommAgent.GetRealOutputData("V11", "KQUOTE_DATE");		//한국호가일자
CString strKQUOTE_TIME = m_CommAgent.GetRealOutputData("V11", "KQUOTE_TIME");		//한국호가시간
CString strRPT_SEQ = m_CommAgent.GetRealOutputData("V11", "RPT_SEQ");		//seq
CString strTRADE_SESSION_ID = m_CommAgent.GetRealOutputData("V11", "TRADE_SESSION_ID");		//장구분
CString strBEST_BID1 = m_CommAgent.GetRealOutputData("V11", "BEST_BID1");		//매수1호가
CString strBEST_BID1_CLR = m_CommAgent.GetRealOutputData("V11", "BEST_BID1_CLR");		//[BEST_BID1]색참조(+상승, -하락)
CString strBEST_BSIZ1 = m_CommAgent.GetRealOutputData("V11", "BEST_BSIZ1");		//매수1호가수량
CString strBEST_BCNT1 = m_CommAgent.GetRealOutputData("V11", "BEST_BCNT1");		//매수1호가건수
CString strBEST_BID2 = m_CommAgent.GetRealOutputData("V11", "BEST_BID2");		//매수2호가
CString strBEST_BID2_CLR = m_CommAgent.GetRealOutputData("V11", "BEST_BID2_CLR");		//[BEST_BID2]색참조(+상승, -하락)
CString strBEST_BSIZ2 = m_CommAgent.GetRealOutputData("V11", "BEST_BSIZ2");		//매수2호가수량
CString strBEST_BCNT2 = m_CommAgent.GetRealOutputData("V11", "BEST_BCNT2");		//메수2호가건수
CString strBEST_BID3 = m_CommAgent.GetRealOutputData("V11", "BEST_BID3");		//매수3호가
CString strBEST_BID3_CLR = m_CommAgent.GetRealOutputData("V11", "BEST_BID3_CLR");		//[BEST_BID3]색참조(+상승, -하락)
CString strBEST_BSIZ3 = m_CommAgent.GetRealOutputData("V11", "BEST_BSIZ3");		//매수3호가수량
CString strBEST_BCNT3 = m_CommAgent.GetRealOutputData("V11", "BEST_BCNT3");		//매수3호가건수
CString strBEST_BID4 = m_CommAgent.GetRealOutputData("V11", "BEST_BID4");		//매수4호가
CString strBEST_BID4_CLR = m_CommAgent.GetRealOutputData("V11", "BEST_BID4_CLR");		//[BEST_BID4]색참조(+상승, -하락)
CString strBEST_BSIZ4 = m_CommAgent.GetRealOutputData("V11", "BEST_BSIZ4");		//매수4호가수량
CString strBEST_BCNT4 = m_CommAgent.GetRealOutputData("V11", "BEST_BCNT4");		//매수4호가건수
CString strBEST_BID5 = m_CommAgent.GetRealOutputData("V11", "BEST_BID5");		//매수5호가
CString strBEST_BID5_CLR = m_CommAgent.GetRealOutputData("V11", "BEST_BID5_CLR");		//[BEST_BID5]색참조(+상승, -하락)
CString strBEST_BSIZ5 = m_CommAgent.GetRealOutputData("V11", "BEST_BSIZ5");		//매수5호가수량
CString strBEST_BCNT5 = m_CommAgent.GetRealOutputData("V11", "BEST_BCNT5");		//매수5호가건수
CString strBIDSIZE = m_CommAgent.GetRealOutputData("V11", "BIDSIZE");		//매수총호가수량
CString strBIDCNT = m_CommAgent.GetRealOutputData("V11", "BIDCNT");		//매수 전체건수
CString strBEST_ASK1 = m_CommAgent.GetRealOutputData("V11", "BEST_ASK1");		//매도1호가
CString strBEST_ASK1_CLR = m_CommAgent.GetRealOutputData("V11", "BEST_ASK1_CLR");		//[BEST_ASK1]색참조(+상승, -하락)
CString strBEST_ASIZ1 = m_CommAgent.GetRealOutputData("V11", "BEST_ASIZ1");		//매도1호가수량
CString strBEST_ACNT1 = m_CommAgent.GetRealOutputData("V11", "BEST_ACNT1");		//매도1호가건수
CString strBEST_ASK2 = m_CommAgent.GetRealOutputData("V11", "BEST_ASK2");		//매도2호가
CString strBEST_ASK2_CLR = m_CommAgent.GetRealOutputData("V11", "BEST_ASK2_CLR");		//[BEST_ASK2]색참조(+상승, -하락)
CString strBEST_ASIZ2 = m_CommAgent.GetRealOutputData("V11", "BEST_ASIZ2");		//매도2호가수량
CString strBEST_ACNT2 = m_CommAgent.GetRealOutputData("V11", "BEST_ACNT2");		//매도2호가건수
CString strBEST_ASK3 = m_CommAgent.GetRealOutputData("V11", "BEST_ASK3");		//매도3호가
CString strBEST_ASK3_CLR = m_CommAgent.GetRealOutputData("V11", "BEST_ASK3_CLR");		//[BEST_ASK3]색참조(+상승, -하락)
CString strBEST_ASIZ3 = m_CommAgent.GetRealOutputData("V11", "BEST_ASIZ3");		//매도3호가수량
CString strBEST_ACNT3 = m_CommAgent.GetRealOutputData("V11", "BEST_ACNT3");		//매도3호가건수
CString strBEST_ASK4 = m_CommAgent.GetRealOutputData("V11", "BEST_ASK4");		//매도4호가
CString strBEST_ASK4_CLR = m_CommAgent.GetRealOutputData("V11", "BEST_ASK4_CLR");		//[BEST_ASK4]색참조(+상승, -하락)
CString strBEST_ASIZ4 = m_CommAgent.GetRealOutputData("V11", "BEST_ASIZ4");		//매도4호가수량
CString strBEST_ACNT4 = m_CommAgent.GetRealOutputData("V11", "BEST_ACNT4");		//매도4호가건수
CString strBEST_ASK5 = m_CommAgent.GetRealOutputData("V11", "BEST_ASK5");		//매도5호가
CString strBEST_ASK5_CLR = m_CommAgent.GetRealOutputData("V11", "BEST_ASK5_CLR");		//[BEST_ASK5]색참조(+상승, -하락)
CString strBEST_ASIZ5 = m_CommAgent.GetRealOutputData("V11", "BEST_ASIZ5");		//매도5호가수량
CString strBEST_ACNT5 = m_CommAgent.GetRealOutputData("V11", "BEST_ACNT5");		//매도5호가건수
CString strASKSIZE = m_CommAgent.GetRealOutputData("V11", "ASKSIZE");		//매도총호가수량
CString strASKCNT = m_CommAgent.GetRealOutputData("V11", "ASKCNT");		//매도 전체건수
CString strBID_ASK_SIZE_DIFF = m_CommAgent.GetRealOutputData("V11", "BID_ASK_SIZE_DIFF");		//매수매도 수량차
CString strBEST_BSIZ_ICDC1 = m_CommAgent.GetRealOutputData("V11", "BEST_BSIZ_ICDC1");		//매수1호가수량 증감
CString strBEST_BSIZ_ICDC2 = m_CommAgent.GetRealOutputData("V11", "BEST_BSIZ_ICDC2");		//매수2호가수량 증감
CString strBEST_BSIZ_ICDC3 = m_CommAgent.GetRealOutputData("V11", "BEST_BSIZ_ICDC3");		//매수3호가수량 증감
CString strBEST_BSIZ_ICDC4 = m_CommAgent.GetRealOutputData("V11", "BEST_BSIZ_ICDC4");		//매수4호가수량 증감
CString strBEST_BSIZ_ICDC5 = m_CommAgent.GetRealOutputData("V11", "BEST_BSIZ_ICDC5");		//매수5호가수량 증감
CString strBIDSIZE_ICDC = m_CommAgent.GetRealOutputData("V11", "BIDSIZE_ICDC");		//매수총호가수량 증감
CString strBEST_ASIZ_ICDC1 = m_CommAgent.GetRealOutputData("V11", "BEST_ASIZ_ICDC1");		//매도1호가수량 증감
CString strBEST_ASIZ_ICDC2 = m_CommAgent.GetRealOutputData("V11", "BEST_ASIZ_ICDC2");		//매도2호가수량 증감
CString strBEST_ASIZ_ICDC3 = m_CommAgent.GetRealOutputData("V11", "BEST_ASIZ_ICDC3");		//매도3호가수량 증감
CString strBEST_ASIZ_ICDC4 = m_CommAgent.GetRealOutputData("V11", "BEST_ASIZ_ICDC4");		//매도4호가수량 증감
CString strBEST_ASIZ_ICDC5 = m_CommAgent.GetRealOutputData("V11", "BEST_ASIZ_ICDC5");		//매도5호가수량 증감
CString strASKSIZE_ICDC = m_CommAgent.GetRealOutputData("V11", "ASKSIZE_ICDC");		//매도총호가수량 증감
CString strDATETIME = m_CommAgent.GetRealOutputData("V11", "DATETIME");		//수신시간




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strPRDT_CD = realCommRecvData.GetItem(0, 0);		//종목코드(내부)
CString strQUOTE_DATE = realCommRecvData.GetItem(0, 1);		//호가일자
CString strQUOTE_TIME = realCommRecvData.GetItem(0, 2);		//호가시간
CString strKQUOTE_DATE = realCommRecvData.GetItem(0, 3);		//한국호가일자
CString strKQUOTE_TIME = realCommRecvData.GetItem(0, 4);		//한국호가시간
CString strRPT_SEQ = realCommRecvData.GetItem(0, 5);		//seq
CString strTRADE_SESSION_ID = realCommRecvData.GetItem(0, 6);		//장구분
CString strBEST_BID1 = realCommRecvData.GetItem(0, 7);		//매수1호가
CString strBEST_BID1_CLR = realCommRecvData.GetItem(0, 8);		//[BEST_BID1]색참조(+상승, -하락)
CString strBEST_BSIZ1 = realCommRecvData.GetItem(0, 9);		//매수1호가수량
CString strBEST_BCNT1 = realCommRecvData.GetItem(0, 10);		//매수1호가건수
CString strBEST_BID2 = realCommRecvData.GetItem(0, 11);		//매수2호가
CString strBEST_BID2_CLR = realCommRecvData.GetItem(0, 12);		//[BEST_BID2]색참조(+상승, -하락)
CString strBEST_BSIZ2 = realCommRecvData.GetItem(0, 13);		//매수2호가수량
CString strBEST_BCNT2 = realCommRecvData.GetItem(0, 14);		//메수2호가건수
CString strBEST_BID3 = realCommRecvData.GetItem(0, 15);		//매수3호가
CString strBEST_BID3_CLR = realCommRecvData.GetItem(0, 16);		//[BEST_BID3]색참조(+상승, -하락)
CString strBEST_BSIZ3 = realCommRecvData.GetItem(0, 17);		//매수3호가수량
CString strBEST_BCNT3 = realCommRecvData.GetItem(0, 18);		//매수3호가건수
CString strBEST_BID4 = realCommRecvData.GetItem(0, 19);		//매수4호가
CString strBEST_BID4_CLR = realCommRecvData.GetItem(0, 20);		//[BEST_BID4]색참조(+상승, -하락)
CString strBEST_BSIZ4 = realCommRecvData.GetItem(0, 21);		//매수4호가수량
CString strBEST_BCNT4 = realCommRecvData.GetItem(0, 22);		//매수4호가건수
CString strBEST_BID5 = realCommRecvData.GetItem(0, 23);		//매수5호가
CString strBEST_BID5_CLR = realCommRecvData.GetItem(0, 24);		//[BEST_BID5]색참조(+상승, -하락)
CString strBEST_BSIZ5 = realCommRecvData.GetItem(0, 25);		//매수5호가수량
CString strBEST_BCNT5 = realCommRecvData.GetItem(0, 26);		//매수5호가건수
CString strBIDSIZE = realCommRecvData.GetItem(0, 27);		//매수총호가수량
CString strBIDCNT = realCommRecvData.GetItem(0, 28);		//매수 전체건수
CString strBEST_ASK1 = realCommRecvData.GetItem(0, 29);		//매도1호가
CString strBEST_ASK1_CLR = realCommRecvData.GetItem(0, 30);		//[BEST_ASK1]색참조(+상승, -하락)
CString strBEST_ASIZ1 = realCommRecvData.GetItem(0, 31);		//매도1호가수량
CString strBEST_ACNT1 = realCommRecvData.GetItem(0, 32);		//매도1호가건수
CString strBEST_ASK2 = realCommRecvData.GetItem(0, 33);		//매도2호가
CString strBEST_ASK2_CLR = realCommRecvData.GetItem(0, 34);		//[BEST_ASK2]색참조(+상승, -하락)
CString strBEST_ASIZ2 = realCommRecvData.GetItem(0, 35);		//매도2호가수량
CString strBEST_ACNT2 = realCommRecvData.GetItem(0, 36);		//매도2호가건수
CString strBEST_ASK3 = realCommRecvData.GetItem(0, 37);		//매도3호가
CString strBEST_ASK3_CLR = realCommRecvData.GetItem(0, 38);		//[BEST_ASK3]색참조(+상승, -하락)
CString strBEST_ASIZ3 = realCommRecvData.GetItem(0, 39);		//매도3호가수량
CString strBEST_ACNT3 = realCommRecvData.GetItem(0, 40);		//매도3호가건수
CString strBEST_ASK4 = realCommRecvData.GetItem(0, 41);		//매도4호가
CString strBEST_ASK4_CLR = realCommRecvData.GetItem(0, 42);		//[BEST_ASK4]색참조(+상승, -하락)
CString strBEST_ASIZ4 = realCommRecvData.GetItem(0, 43);		//매도4호가수량
CString strBEST_ACNT4 = realCommRecvData.GetItem(0, 44);		//매도4호가건수
CString strBEST_ASK5 = realCommRecvData.GetItem(0, 45);		//매도5호가
CString strBEST_ASK5_CLR = realCommRecvData.GetItem(0, 46);		//[BEST_ASK5]색참조(+상승, -하락)
CString strBEST_ASIZ5 = realCommRecvData.GetItem(0, 47);		//매도5호가수량
CString strBEST_ACNT5 = realCommRecvData.GetItem(0, 48);		//매도5호가건수
CString strASKSIZE = realCommRecvData.GetItem(0, 49);		//매도총호가수량
CString strASKCNT = realCommRecvData.GetItem(0, 50);		//매도 전체건수
CString strBID_ASK_SIZE_DIFF = realCommRecvData.GetItem(0, 51);		//매수매도 수량차
CString strBEST_BSIZ_ICDC1 = realCommRecvData.GetItem(0, 52);		//매수1호가수량 증감
CString strBEST_BSIZ_ICDC2 = realCommRecvData.GetItem(0, 53);		//매수2호가수량 증감
CString strBEST_BSIZ_ICDC3 = realCommRecvData.GetItem(0, 54);		//매수3호가수량 증감
CString strBEST_BSIZ_ICDC4 = realCommRecvData.GetItem(0, 55);		//매수4호가수량 증감
CString strBEST_BSIZ_ICDC5 = realCommRecvData.GetItem(0, 56);		//매수5호가수량 증감
CString strBIDSIZE_ICDC = realCommRecvData.GetItem(0, 57);		//매수총호가수량 증감
CString strBEST_ASIZ_ICDC1 = realCommRecvData.GetItem(0, 58);		//매도1호가수량 증감
CString strBEST_ASIZ_ICDC2 = realCommRecvData.GetItem(0, 59);		//매도2호가수량 증감
CString strBEST_ASIZ_ICDC3 = realCommRecvData.GetItem(0, 60);		//매도3호가수량 증감
CString strBEST_ASIZ_ICDC4 = realCommRecvData.GetItem(0, 61);		//매도4호가수량 증감
CString strBEST_ASIZ_ICDC5 = realCommRecvData.GetItem(0, 62);		//매도5호가수량 증감
CString strASKSIZE_ICDC = realCommRecvData.GetItem(0, 63);		//매도총호가수량 증감
CString strDATETIME = realCommRecvData.GetItem(0, 64);		//수신시간
