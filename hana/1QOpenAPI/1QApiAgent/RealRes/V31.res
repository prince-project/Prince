BEGIN_FUNCTION_MAP
	REAL_TYPE=145, REAL_NAME=V31, DESCRIPTION=해외주식호가;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SYMBOL, TYPE=string, SIZE=18, KEY=1, CAPTION=종목코드, FID=0;
			 INDEX=1, ITEM=LOCDATE, TYPE=string, SIZE=8, KEY=0, CAPTION=현지일자, FID=0;
			 INDEX=2, ITEM=LOCTIME, TYPE=string, SIZE=6, KEY=0, CAPTION=현지시간, FID=0;
			 INDEX=3, ITEM=KORDATE, TYPE=string, SIZE=8, KEY=0, CAPTION=한국일자, FID=0;
			 INDEX=4, ITEM=KORTIME, TYPE=string, SIZE=6, KEY=0, CAPTION=한국시간, FID=0;
			 INDEX=5, ITEM=TOTBIDSIZE, TYPE=string, SIZE=12, KEY=0, CAPTION=매수호가 총잔량, FID=0;
			 INDEX=6, ITEM=TOTASKSIZE, TYPE=string, SIZE=12, KEY=0, CAPTION=매도호가 총잔량, FID=0;
			 INDEX=7, ITEM=TOTBIDCOUNT, TYPE=string, SIZE=12, KEY=0, CAPTION=매도호가 총건수, FID=0;
			 INDEX=8, ITEM=TOTASKCOUNT, TYPE=string, SIZE=12, KEY=0, CAPTION=매수호가 총건수, FID=0;
			 INDEX=9, ITEM=BID_1, TYPE=string, SIZE=20, KEY=0, CAPTION=매수1호가, FID=0;
			 INDEX=10, ITEM=BID_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BID_1]색참조(+상승, -하락), FID=0;
			 INDEX=11, ITEM=ASK_1, TYPE=string, SIZE=20, KEY=0, CAPTION=매도1호가, FID=0;
			 INDEX=12, ITEM=ASK_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASK_1]색참조(+상승, -하락), FID=0;
			 INDEX=13, ITEM=BIDSIZE_1, TYPE=string, SIZE=12, KEY=0, CAPTION=매수1호가잔량, FID=0;
			 INDEX=14, ITEM=ASKSIZE_1, TYPE=string, SIZE=12, KEY=0, CAPTION=매도1호가잔량, FID=0;
			 INDEX=15, ITEM=BIDCOUNT_1, TYPE=string, SIZE=12, KEY=0, CAPTION=매수1호가건수, FID=0;
			 INDEX=16, ITEM=ASKCOUNT_1, TYPE=string, SIZE=12, KEY=0, CAPTION=매도1호가건수, FID=0;
			 INDEX=17, ITEM=BID_2, TYPE=string, SIZE=20, KEY=0, CAPTION=매수2호가, FID=0;
			 INDEX=18, ITEM=BID_2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BID_2]색참조(+상승, -하락), FID=0;
			 INDEX=19, ITEM=ASK_2, TYPE=string, SIZE=20, KEY=0, CAPTION=매도2호가, FID=0;
			 INDEX=20, ITEM=ASK_2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASK_2]색참조(+상승, -하락), FID=0;
			 INDEX=21, ITEM=BIDSIZE_2, TYPE=string, SIZE=12, KEY=0, CAPTION=매수2호가잔량, FID=0;
			 INDEX=22, ITEM=ASKSIZE_2, TYPE=string, SIZE=12, KEY=0, CAPTION=매도2호가잔량, FID=0;
			 INDEX=23, ITEM=BIDCOUNT_2, TYPE=string, SIZE=12, KEY=0, CAPTION=매수2호가건수, FID=0;
			 INDEX=24, ITEM=ASKCOUNT_2, TYPE=string, SIZE=12, KEY=0, CAPTION=매도2호가건수, FID=0;
			 INDEX=25, ITEM=BID_3, TYPE=string, SIZE=20, KEY=0, CAPTION=매수3호가, FID=0;
			 INDEX=26, ITEM=BID_3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BID_3]색참조(+상승, -하락), FID=0;
			 INDEX=27, ITEM=ASK_3, TYPE=string, SIZE=20, KEY=0, CAPTION=매도3호가, FID=0;
			 INDEX=28, ITEM=ASK_3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASK_3]색참조(+상승, -하락), FID=0;
			 INDEX=29, ITEM=BIDSIZE_3, TYPE=string, SIZE=12, KEY=0, CAPTION=매수3호가잔량, FID=0;
			 INDEX=30, ITEM=ASKSIZE_3, TYPE=string, SIZE=12, KEY=0, CAPTION=매도3호가잔량, FID=0;
			 INDEX=31, ITEM=BIDCOUNT_3, TYPE=string, SIZE=12, KEY=0, CAPTION=매수3호가건수, FID=0;
			 INDEX=32, ITEM=ASKCOUNT_3, TYPE=string, SIZE=12, KEY=0, CAPTION=매도3호가건수, FID=0;
			 INDEX=33, ITEM=BID_4, TYPE=string, SIZE=20, KEY=0, CAPTION=매수4호가, FID=0;
			 INDEX=34, ITEM=BID_4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BID_4]색참조(+상승, -하락), FID=0;
			 INDEX=35, ITEM=ASK_4, TYPE=string, SIZE=20, KEY=0, CAPTION=매도4호가, FID=0;
			 INDEX=36, ITEM=ASK_4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASK_4]색참조(+상승, -하락), FID=0;
			 INDEX=37, ITEM=BIDSIZE_4, TYPE=string, SIZE=12, KEY=0, CAPTION=매수4호가잔량, FID=0;
			 INDEX=38, ITEM=ASKSIZE_4, TYPE=string, SIZE=12, KEY=0, CAPTION=매도4호가잔량, FID=0;
			 INDEX=39, ITEM=BIDCOUNT_4, TYPE=string, SIZE=12, KEY=0, CAPTION=매수4호가건수, FID=0;
			 INDEX=40, ITEM=ASKCOUNT_4, TYPE=string, SIZE=12, KEY=0, CAPTION=매도4호가건수, FID=0;
			 INDEX=41, ITEM=BID_5, TYPE=string, SIZE=20, KEY=0, CAPTION=매수5호가, FID=0;
			 INDEX=42, ITEM=BID_5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BID_5]색참조(+상승, -하락), FID=0;
			 INDEX=43, ITEM=ASK_5, TYPE=string, SIZE=20, KEY=0, CAPTION=매도5호가, FID=0;
			 INDEX=44, ITEM=ASK_5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASK_5]색참조(+상승, -하락), FID=0;
			 INDEX=45, ITEM=BIDSIZE_5, TYPE=string, SIZE=12, KEY=0, CAPTION=매수5호가잔량, FID=0;
			 INDEX=46, ITEM=ASKSIZE_5, TYPE=string, SIZE=12, KEY=0, CAPTION=매도5호가잔량, FID=0;
			 INDEX=47, ITEM=BIDCOUNT_5, TYPE=string, SIZE=12, KEY=0, CAPTION=매수5호가건수, FID=0;
			 INDEX=48, ITEM=ASKCOUNT_5, TYPE=string, SIZE=12, KEY=0, CAPTION=매도5호가건수, FID=0;
			 INDEX=49, ITEM=BID_6, TYPE=string, SIZE=20, KEY=0, CAPTION=매수6호가, FID=0;
			 INDEX=50, ITEM=BID_6_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BID_6]색참조(+상승, -하락), FID=0;
			 INDEX=51, ITEM=ASK_6, TYPE=string, SIZE=20, KEY=0, CAPTION=매도6호가, FID=0;
			 INDEX=52, ITEM=ASK_6_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASK_6]색참조(+상승, -하락), FID=0;
			 INDEX=53, ITEM=BIDSIZE_6, TYPE=string, SIZE=12, KEY=0, CAPTION=매수6호가잔량, FID=0;
			 INDEX=54, ITEM=ASKSIZE_6, TYPE=string, SIZE=12, KEY=0, CAPTION=매도6호가잔량, FID=0;
			 INDEX=55, ITEM=BIDCOUNT_6, TYPE=string, SIZE=12, KEY=0, CAPTION=매수6호가건수, FID=0;
			 INDEX=56, ITEM=ASKCOUNT_6, TYPE=string, SIZE=12, KEY=0, CAPTION=매도6호가건수, FID=0;
			 INDEX=57, ITEM=BID_7, TYPE=string, SIZE=20, KEY=0, CAPTION=매수7호가, FID=0;
			 INDEX=58, ITEM=BID_7_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BID_7]색참조(+상승, -하락), FID=0;
			 INDEX=59, ITEM=ASK_7, TYPE=string, SIZE=20, KEY=0, CAPTION=매도7호가, FID=0;
			 INDEX=60, ITEM=ASK_7_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASK_7]색참조(+상승, -하락), FID=0;
			 INDEX=61, ITEM=BIDSIZE_7, TYPE=string, SIZE=12, KEY=0, CAPTION=매수7호가잔량, FID=0;
			 INDEX=62, ITEM=ASKSIZE_7, TYPE=string, SIZE=12, KEY=0, CAPTION=매도7호가잔량, FID=0;
			 INDEX=63, ITEM=BIDCOUNT_7, TYPE=string, SIZE=12, KEY=0, CAPTION=매수7호가건수, FID=0;
			 INDEX=64, ITEM=ASKCOUNT_7, TYPE=string, SIZE=12, KEY=0, CAPTION=매도7호가건수, FID=0;
			 INDEX=65, ITEM=BID_8, TYPE=string, SIZE=20, KEY=0, CAPTION=매수8호가, FID=0;
			 INDEX=66, ITEM=BID_8_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BID_8]색참조(+상승, -하락), FID=0;
			 INDEX=67, ITEM=ASK_8, TYPE=string, SIZE=20, KEY=0, CAPTION=매도8호가, FID=0;
			 INDEX=68, ITEM=ASK_8_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASK_8]색참조(+상승, -하락), FID=0;
			 INDEX=69, ITEM=BIDSIZE_8, TYPE=string, SIZE=12, KEY=0, CAPTION=매수8호가잔량, FID=0;
			 INDEX=70, ITEM=ASKSIZE_8, TYPE=string, SIZE=12, KEY=0, CAPTION=매도8호가잔량, FID=0;
			 INDEX=71, ITEM=BIDCOUNT_8, TYPE=string, SIZE=12, KEY=0, CAPTION=매수8호가건수, FID=0;
			 INDEX=72, ITEM=ASKCOUNT_8, TYPE=string, SIZE=12, KEY=0, CAPTION=매도8호가건수, FID=0;
			 INDEX=73, ITEM=BID_9, TYPE=string, SIZE=20, KEY=0, CAPTION=매수9호가, FID=0;
			 INDEX=74, ITEM=BID_9_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BID_9]색참조(+상승, -하락), FID=0;
			 INDEX=75, ITEM=ASK_9, TYPE=string, SIZE=20, KEY=0, CAPTION=매도9호가, FID=0;
			 INDEX=76, ITEM=ASK_9_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASK_9]색참조(+상승, -하락), FID=0;
			 INDEX=77, ITEM=BIDSIZE_9, TYPE=string, SIZE=12, KEY=0, CAPTION=매수9호가잔량, FID=0;
			 INDEX=78, ITEM=ASKSIZE_9, TYPE=string, SIZE=12, KEY=0, CAPTION=매도9호가잔량, FID=0;
			 INDEX=79, ITEM=BIDCOUNT_9, TYPE=string, SIZE=12, KEY=0, CAPTION=매수9호가건수, FID=0;
			 INDEX=80, ITEM=ASKCOUNT_9, TYPE=string, SIZE=12, KEY=0, CAPTION=매도9호가건수, FID=0;
			 INDEX=81, ITEM=BID_10, TYPE=string, SIZE=20, KEY=0, CAPTION=매수10호가, FID=0;
			 INDEX=82, ITEM=BID_10_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BID_10]색참조(+상승, -하락), FID=0;
			 INDEX=83, ITEM=ASK_10, TYPE=string, SIZE=20, KEY=0, CAPTION=매도10호가, FID=0;
			 INDEX=84, ITEM=ASK_10_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASK_10]색참조(+상승, -하락), FID=0;
			 INDEX=85, ITEM=BIDSIZE_10, TYPE=string, SIZE=12, KEY=0, CAPTION=매수10호가잔량, FID=0;
			 INDEX=86, ITEM=ASKSIZE_10, TYPE=string, SIZE=12, KEY=0, CAPTION=매도10호가잔량, FID=0;
			 INDEX=87, ITEM=BIDCOUNT_10, TYPE=string, SIZE=12, KEY=0, CAPTION=매수10호가건수, FID=0;
			 INDEX=88, ITEM=ASKCOUNT_10, TYPE=string, SIZE=12, KEY=0, CAPTION=매도10호가건수, FID=0;
			 INDEX=89, ITEM=TOTBIDSIZE_ICDC, TYPE=string, SIZE=20, KEY=0, CAPTION=매수호가 총잔량 증감, FID=0;
			 INDEX=90, ITEM=TOTBIDSIZE_ICDC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[TOTBIDSIZE_ICDC]색참조(+상승, -하락), FID=0;
			 INDEX=91, ITEM=TOTASKSIZE_ICDC, TYPE=string, SIZE=20, KEY=0, CAPTION=매도호가 총잔량 증감, FID=0;
			 INDEX=92, ITEM=TOTASKSIZE_ICDC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[TOTASKSIZE_ICDC]색참조(+상승, -하락), FID=0;
			 INDEX=93, ITEM=BIDSIZE_ICDC1, TYPE=string, SIZE=20, KEY=0, CAPTION=매수 1호가잔량 증감, FID=0;
			 INDEX=94, ITEM=BIDSIZE_ICDC1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDSIZE_ICDC1]색참조(+상승, -하락), FID=0;
			 INDEX=95, ITEM=ASKSIZE_ICDC1, TYPE=string, SIZE=20, KEY=0, CAPTION=매도 1호가잔량 증감, FID=0;
			 INDEX=96, ITEM=ASKSIZE_ICDC1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKSIZE_ICDC1]색참조(+상승, -하락), FID=0;
			 INDEX=97, ITEM=BIDSIZE_ICDC2, TYPE=string, SIZE=20, KEY=0, CAPTION=매수 2호가잔량 증감, FID=0;
			 INDEX=98, ITEM=BIDSIZE_ICDC2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDSIZE_ICDC2]색참조(+상승, -하락), FID=0;
			 INDEX=99, ITEM=ASKSIZE_ICDC2, TYPE=string, SIZE=20, KEY=0, CAPTION=매도 2호가잔량 증감, FID=0;
			 INDEX=100, ITEM=ASKSIZE_ICDC2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKSIZE_ICDC2]색참조(+상승, -하락), FID=0;
			 INDEX=101, ITEM=BIDSIZE_ICDC3, TYPE=string, SIZE=20, KEY=0, CAPTION=매수 3호가잔량 증감, FID=0;
			 INDEX=102, ITEM=BIDSIZE_ICDC3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDSIZE_ICDC3]색참조(+상승, -하락), FID=0;
			 INDEX=103, ITEM=ASKSIZE_ICDC3, TYPE=string, SIZE=20, KEY=0, CAPTION=매도 3호가잔량 증감, FID=0;
			 INDEX=104, ITEM=ASKSIZE_ICDC3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKSIZE_ICDC3]색참조(+상승, -하락), FID=0;
			 INDEX=105, ITEM=BIDSIZE_ICDC4, TYPE=string, SIZE=20, KEY=0, CAPTION=매수 4호가잔량 증감, FID=0;
			 INDEX=106, ITEM=BIDSIZE_ICDC4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDSIZE_ICDC4]색참조(+상승, -하락), FID=0;
			 INDEX=107, ITEM=ASKSIZE_ICDC4, TYPE=string, SIZE=20, KEY=0, CAPTION=매도 4호가잔량 증감, FID=0;
			 INDEX=108, ITEM=ASKSIZE_ICDC4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKSIZE_ICDC4]색참조(+상승, -하락), FID=0;
			 INDEX=109, ITEM=BIDSIZE_ICDC5, TYPE=string, SIZE=20, KEY=0, CAPTION=매수 5호가잔량 증감, FID=0;
			 INDEX=110, ITEM=BIDSIZE_ICDC5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDSIZE_ICDC5]색참조(+상승, -하락), FID=0;
			 INDEX=111, ITEM=ASKSIZE_ICDC5, TYPE=string, SIZE=20, KEY=0, CAPTION=매도 5호가잔량 증감, FID=0;
			 INDEX=112, ITEM=ASKSIZE_ICDC5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKSIZE_ICDC5]색참조(+상승, -하락), FID=0;
			 INDEX=113, ITEM=BIDSIZE_ICDC6, TYPE=string, SIZE=20, KEY=0, CAPTION=매수 6호가잔량 증감, FID=0;
			 INDEX=114, ITEM=BIDSIZE_ICDC6_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDSIZE_ICDC6]색참조(+상승, -하락), FID=0;
			 INDEX=115, ITEM=ASKSIZE_ICDC6, TYPE=string, SIZE=20, KEY=0, CAPTION=매도 6호가잔량 증감, FID=0;
			 INDEX=116, ITEM=ASKSIZE_ICDC6_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKSIZE_ICDC6]색참조(+상승, -하락), FID=0;
			 INDEX=117, ITEM=BIDSIZE_ICDC7, TYPE=string, SIZE=20, KEY=0, CAPTION=매수 7호가잔량 증감, FID=0;
			 INDEX=118, ITEM=BIDSIZE_ICDC7_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDSIZE_ICDC7]색참조(+상승, -하락), FID=0;
			 INDEX=119, ITEM=ASKSIZE_ICDC7, TYPE=string, SIZE=20, KEY=0, CAPTION=매도 7호가잔량 증감, FID=0;
			 INDEX=120, ITEM=ASKSIZE_ICDC7_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKSIZE_ICDC7]색참조(+상승, -하락), FID=0;
			 INDEX=121, ITEM=BIDSIZE_ICDC8, TYPE=string, SIZE=20, KEY=0, CAPTION=매수 8호가잔량 증감, FID=0;
			 INDEX=122, ITEM=BIDSIZE_ICDC8_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDSIZE_ICDC8]색참조(+상승, -하락), FID=0;
			 INDEX=123, ITEM=ASKSIZE_ICDC8, TYPE=string, SIZE=20, KEY=0, CAPTION=매도 8호가잔량 증감, FID=0;
			 INDEX=124, ITEM=ASKSIZE_ICDC8_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKSIZE_ICDC8]색참조(+상승, -하락), FID=0;
			 INDEX=125, ITEM=BIDSIZE_ICDC9, TYPE=string, SIZE=20, KEY=0, CAPTION=매수 9호가잔량 증감, FID=0;
			 INDEX=126, ITEM=BIDSIZE_ICDC9_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDSIZE_ICDC9]색참조(+상승, -하락), FID=0;
			 INDEX=127, ITEM=ASKSIZE_ICDC9, TYPE=string, SIZE=20, KEY=0, CAPTION=매도 9호가잔량 증감, FID=0;
			 INDEX=128, ITEM=ASKSIZE_ICDC9_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKSIZE_ICDC9]색참조(+상승, -하락), FID=0;
			 INDEX=129, ITEM=BIDSIZE_ICDC10, TYPE=string, SIZE=20, KEY=0, CAPTION=매수10호가잔량 증감, FID=0;
			 INDEX=130, ITEM=BIDSIZE_ICDC10_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDSIZE_ICDC10]색참조(+상승, -하락), FID=0;
			 INDEX=131, ITEM=ASKSIZE_ICDC10, TYPE=string, SIZE=20, KEY=0, CAPTION=매도10호가잔량 증감, FID=0;
			 INDEX=132, ITEM=ASKSIZE_ICDC10_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKSIZE_ICDC10]색참조(+상승, -하락), FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strSYMBOL = m_CommAgent.GetRealOutputData("V31", "SYMBOL");		//종목코드
CString strLOCDATE = m_CommAgent.GetRealOutputData("V31", "LOCDATE");		//현지일자
CString strLOCTIME = m_CommAgent.GetRealOutputData("V31", "LOCTIME");		//현지시간
CString strKORDATE = m_CommAgent.GetRealOutputData("V31", "KORDATE");		//한국일자
CString strKORTIME = m_CommAgent.GetRealOutputData("V31", "KORTIME");		//한국시간
CString strTOTBIDSIZE = m_CommAgent.GetRealOutputData("V31", "TOTBIDSIZE");		//매수호가 총잔량
CString strTOTASKSIZE = m_CommAgent.GetRealOutputData("V31", "TOTASKSIZE");		//매도호가 총잔량
CString strTOTBIDCOUNT = m_CommAgent.GetRealOutputData("V31", "TOTBIDCOUNT");		//매도호가 총건수
CString strTOTASKCOUNT = m_CommAgent.GetRealOutputData("V31", "TOTASKCOUNT");		//매수호가 총건수
CString strBID_1 = m_CommAgent.GetRealOutputData("V31", "BID_1");		//매수1호가
CString strBID_1_CLR = m_CommAgent.GetRealOutputData("V31", "BID_1_CLR");		//[BID_1]색참조(+상승, -하락)
CString strASK_1 = m_CommAgent.GetRealOutputData("V31", "ASK_1");		//매도1호가
CString strASK_1_CLR = m_CommAgent.GetRealOutputData("V31", "ASK_1_CLR");		//[ASK_1]색참조(+상승, -하락)
CString strBIDSIZE_1 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_1");		//매수1호가잔량
CString strASKSIZE_1 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_1");		//매도1호가잔량
CString strBIDCOUNT_1 = m_CommAgent.GetRealOutputData("V31", "BIDCOUNT_1");		//매수1호가건수
CString strASKCOUNT_1 = m_CommAgent.GetRealOutputData("V31", "ASKCOUNT_1");		//매도1호가건수
CString strBID_2 = m_CommAgent.GetRealOutputData("V31", "BID_2");		//매수2호가
CString strBID_2_CLR = m_CommAgent.GetRealOutputData("V31", "BID_2_CLR");		//[BID_2]색참조(+상승, -하락)
CString strASK_2 = m_CommAgent.GetRealOutputData("V31", "ASK_2");		//매도2호가
CString strASK_2_CLR = m_CommAgent.GetRealOutputData("V31", "ASK_2_CLR");		//[ASK_2]색참조(+상승, -하락)
CString strBIDSIZE_2 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_2");		//매수2호가잔량
CString strASKSIZE_2 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_2");		//매도2호가잔량
CString strBIDCOUNT_2 = m_CommAgent.GetRealOutputData("V31", "BIDCOUNT_2");		//매수2호가건수
CString strASKCOUNT_2 = m_CommAgent.GetRealOutputData("V31", "ASKCOUNT_2");		//매도2호가건수
CString strBID_3 = m_CommAgent.GetRealOutputData("V31", "BID_3");		//매수3호가
CString strBID_3_CLR = m_CommAgent.GetRealOutputData("V31", "BID_3_CLR");		//[BID_3]색참조(+상승, -하락)
CString strASK_3 = m_CommAgent.GetRealOutputData("V31", "ASK_3");		//매도3호가
CString strASK_3_CLR = m_CommAgent.GetRealOutputData("V31", "ASK_3_CLR");		//[ASK_3]색참조(+상승, -하락)
CString strBIDSIZE_3 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_3");		//매수3호가잔량
CString strASKSIZE_3 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_3");		//매도3호가잔량
CString strBIDCOUNT_3 = m_CommAgent.GetRealOutputData("V31", "BIDCOUNT_3");		//매수3호가건수
CString strASKCOUNT_3 = m_CommAgent.GetRealOutputData("V31", "ASKCOUNT_3");		//매도3호가건수
CString strBID_4 = m_CommAgent.GetRealOutputData("V31", "BID_4");		//매수4호가
CString strBID_4_CLR = m_CommAgent.GetRealOutputData("V31", "BID_4_CLR");		//[BID_4]색참조(+상승, -하락)
CString strASK_4 = m_CommAgent.GetRealOutputData("V31", "ASK_4");		//매도4호가
CString strASK_4_CLR = m_CommAgent.GetRealOutputData("V31", "ASK_4_CLR");		//[ASK_4]색참조(+상승, -하락)
CString strBIDSIZE_4 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_4");		//매수4호가잔량
CString strASKSIZE_4 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_4");		//매도4호가잔량
CString strBIDCOUNT_4 = m_CommAgent.GetRealOutputData("V31", "BIDCOUNT_4");		//매수4호가건수
CString strASKCOUNT_4 = m_CommAgent.GetRealOutputData("V31", "ASKCOUNT_4");		//매도4호가건수
CString strBID_5 = m_CommAgent.GetRealOutputData("V31", "BID_5");		//매수5호가
CString strBID_5_CLR = m_CommAgent.GetRealOutputData("V31", "BID_5_CLR");		//[BID_5]색참조(+상승, -하락)
CString strASK_5 = m_CommAgent.GetRealOutputData("V31", "ASK_5");		//매도5호가
CString strASK_5_CLR = m_CommAgent.GetRealOutputData("V31", "ASK_5_CLR");		//[ASK_5]색참조(+상승, -하락)
CString strBIDSIZE_5 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_5");		//매수5호가잔량
CString strASKSIZE_5 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_5");		//매도5호가잔량
CString strBIDCOUNT_5 = m_CommAgent.GetRealOutputData("V31", "BIDCOUNT_5");		//매수5호가건수
CString strASKCOUNT_5 = m_CommAgent.GetRealOutputData("V31", "ASKCOUNT_5");		//매도5호가건수
CString strBID_6 = m_CommAgent.GetRealOutputData("V31", "BID_6");		//매수6호가
CString strBID_6_CLR = m_CommAgent.GetRealOutputData("V31", "BID_6_CLR");		//[BID_6]색참조(+상승, -하락)
CString strASK_6 = m_CommAgent.GetRealOutputData("V31", "ASK_6");		//매도6호가
CString strASK_6_CLR = m_CommAgent.GetRealOutputData("V31", "ASK_6_CLR");		//[ASK_6]색참조(+상승, -하락)
CString strBIDSIZE_6 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_6");		//매수6호가잔량
CString strASKSIZE_6 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_6");		//매도6호가잔량
CString strBIDCOUNT_6 = m_CommAgent.GetRealOutputData("V31", "BIDCOUNT_6");		//매수6호가건수
CString strASKCOUNT_6 = m_CommAgent.GetRealOutputData("V31", "ASKCOUNT_6");		//매도6호가건수
CString strBID_7 = m_CommAgent.GetRealOutputData("V31", "BID_7");		//매수7호가
CString strBID_7_CLR = m_CommAgent.GetRealOutputData("V31", "BID_7_CLR");		//[BID_7]색참조(+상승, -하락)
CString strASK_7 = m_CommAgent.GetRealOutputData("V31", "ASK_7");		//매도7호가
CString strASK_7_CLR = m_CommAgent.GetRealOutputData("V31", "ASK_7_CLR");		//[ASK_7]색참조(+상승, -하락)
CString strBIDSIZE_7 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_7");		//매수7호가잔량
CString strASKSIZE_7 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_7");		//매도7호가잔량
CString strBIDCOUNT_7 = m_CommAgent.GetRealOutputData("V31", "BIDCOUNT_7");		//매수7호가건수
CString strASKCOUNT_7 = m_CommAgent.GetRealOutputData("V31", "ASKCOUNT_7");		//매도7호가건수
CString strBID_8 = m_CommAgent.GetRealOutputData("V31", "BID_8");		//매수8호가
CString strBID_8_CLR = m_CommAgent.GetRealOutputData("V31", "BID_8_CLR");		//[BID_8]색참조(+상승, -하락)
CString strASK_8 = m_CommAgent.GetRealOutputData("V31", "ASK_8");		//매도8호가
CString strASK_8_CLR = m_CommAgent.GetRealOutputData("V31", "ASK_8_CLR");		//[ASK_8]색참조(+상승, -하락)
CString strBIDSIZE_8 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_8");		//매수8호가잔량
CString strASKSIZE_8 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_8");		//매도8호가잔량
CString strBIDCOUNT_8 = m_CommAgent.GetRealOutputData("V31", "BIDCOUNT_8");		//매수8호가건수
CString strASKCOUNT_8 = m_CommAgent.GetRealOutputData("V31", "ASKCOUNT_8");		//매도8호가건수
CString strBID_9 = m_CommAgent.GetRealOutputData("V31", "BID_9");		//매수9호가
CString strBID_9_CLR = m_CommAgent.GetRealOutputData("V31", "BID_9_CLR");		//[BID_9]색참조(+상승, -하락)
CString strASK_9 = m_CommAgent.GetRealOutputData("V31", "ASK_9");		//매도9호가
CString strASK_9_CLR = m_CommAgent.GetRealOutputData("V31", "ASK_9_CLR");		//[ASK_9]색참조(+상승, -하락)
CString strBIDSIZE_9 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_9");		//매수9호가잔량
CString strASKSIZE_9 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_9");		//매도9호가잔량
CString strBIDCOUNT_9 = m_CommAgent.GetRealOutputData("V31", "BIDCOUNT_9");		//매수9호가건수
CString strASKCOUNT_9 = m_CommAgent.GetRealOutputData("V31", "ASKCOUNT_9");		//매도9호가건수
CString strBID_10 = m_CommAgent.GetRealOutputData("V31", "BID_10");		//매수10호가
CString strBID_10_CLR = m_CommAgent.GetRealOutputData("V31", "BID_10_CLR");		//[BID_10]색참조(+상승, -하락)
CString strASK_10 = m_CommAgent.GetRealOutputData("V31", "ASK_10");		//매도10호가
CString strASK_10_CLR = m_CommAgent.GetRealOutputData("V31", "ASK_10_CLR");		//[ASK_10]색참조(+상승, -하락)
CString strBIDSIZE_10 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_10");		//매수10호가잔량
CString strASKSIZE_10 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_10");		//매도10호가잔량
CString strBIDCOUNT_10 = m_CommAgent.GetRealOutputData("V31", "BIDCOUNT_10");		//매수10호가건수
CString strASKCOUNT_10 = m_CommAgent.GetRealOutputData("V31", "ASKCOUNT_10");		//매도10호가건수
CString strTOTBIDSIZE_ICDC = m_CommAgent.GetRealOutputData("V31", "TOTBIDSIZE_ICDC");		//매수호가 총잔량 증감
CString strTOTBIDSIZE_ICDC_CLR = m_CommAgent.GetRealOutputData("V31", "TOTBIDSIZE_ICDC_CLR");		//[TOTBIDSIZE_ICDC]색참조(+상승, -하락)
CString strTOTASKSIZE_ICDC = m_CommAgent.GetRealOutputData("V31", "TOTASKSIZE_ICDC");		//매도호가 총잔량 증감
CString strTOTASKSIZE_ICDC_CLR = m_CommAgent.GetRealOutputData("V31", "TOTASKSIZE_ICDC_CLR");		//[TOTASKSIZE_ICDC]색참조(+상승, -하락)
CString strBIDSIZE_ICDC1 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC1");		//매수 1호가잔량 증감
CString strBIDSIZE_ICDC1_CLR = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC1_CLR");		//[BIDSIZE_ICDC1]색참조(+상승, -하락)
CString strASKSIZE_ICDC1 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC1");		//매도 1호가잔량 증감
CString strASKSIZE_ICDC1_CLR = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC1_CLR");		//[ASKSIZE_ICDC1]색참조(+상승, -하락)
CString strBIDSIZE_ICDC2 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC2");		//매수 2호가잔량 증감
CString strBIDSIZE_ICDC2_CLR = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC2_CLR");		//[BIDSIZE_ICDC2]색참조(+상승, -하락)
CString strASKSIZE_ICDC2 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC2");		//매도 2호가잔량 증감
CString strASKSIZE_ICDC2_CLR = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC2_CLR");		//[ASKSIZE_ICDC2]색참조(+상승, -하락)
CString strBIDSIZE_ICDC3 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC3");		//매수 3호가잔량 증감
CString strBIDSIZE_ICDC3_CLR = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC3_CLR");		//[BIDSIZE_ICDC3]색참조(+상승, -하락)
CString strASKSIZE_ICDC3 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC3");		//매도 3호가잔량 증감
CString strASKSIZE_ICDC3_CLR = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC3_CLR");		//[ASKSIZE_ICDC3]색참조(+상승, -하락)
CString strBIDSIZE_ICDC4 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC4");		//매수 4호가잔량 증감
CString strBIDSIZE_ICDC4_CLR = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC4_CLR");		//[BIDSIZE_ICDC4]색참조(+상승, -하락)
CString strASKSIZE_ICDC4 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC4");		//매도 4호가잔량 증감
CString strASKSIZE_ICDC4_CLR = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC4_CLR");		//[ASKSIZE_ICDC4]색참조(+상승, -하락)
CString strBIDSIZE_ICDC5 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC5");		//매수 5호가잔량 증감
CString strBIDSIZE_ICDC5_CLR = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC5_CLR");		//[BIDSIZE_ICDC5]색참조(+상승, -하락)
CString strASKSIZE_ICDC5 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC5");		//매도 5호가잔량 증감
CString strASKSIZE_ICDC5_CLR = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC5_CLR");		//[ASKSIZE_ICDC5]색참조(+상승, -하락)
CString strBIDSIZE_ICDC6 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC6");		//매수 6호가잔량 증감
CString strBIDSIZE_ICDC6_CLR = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC6_CLR");		//[BIDSIZE_ICDC6]색참조(+상승, -하락)
CString strASKSIZE_ICDC6 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC6");		//매도 6호가잔량 증감
CString strASKSIZE_ICDC6_CLR = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC6_CLR");		//[ASKSIZE_ICDC6]색참조(+상승, -하락)
CString strBIDSIZE_ICDC7 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC7");		//매수 7호가잔량 증감
CString strBIDSIZE_ICDC7_CLR = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC7_CLR");		//[BIDSIZE_ICDC7]색참조(+상승, -하락)
CString strASKSIZE_ICDC7 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC7");		//매도 7호가잔량 증감
CString strASKSIZE_ICDC7_CLR = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC7_CLR");		//[ASKSIZE_ICDC7]색참조(+상승, -하락)
CString strBIDSIZE_ICDC8 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC8");		//매수 8호가잔량 증감
CString strBIDSIZE_ICDC8_CLR = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC8_CLR");		//[BIDSIZE_ICDC8]색참조(+상승, -하락)
CString strASKSIZE_ICDC8 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC8");		//매도 8호가잔량 증감
CString strASKSIZE_ICDC8_CLR = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC8_CLR");		//[ASKSIZE_ICDC8]색참조(+상승, -하락)
CString strBIDSIZE_ICDC9 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC9");		//매수 9호가잔량 증감
CString strBIDSIZE_ICDC9_CLR = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC9_CLR");		//[BIDSIZE_ICDC9]색참조(+상승, -하락)
CString strASKSIZE_ICDC9 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC9");		//매도 9호가잔량 증감
CString strASKSIZE_ICDC9_CLR = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC9_CLR");		//[ASKSIZE_ICDC9]색참조(+상승, -하락)
CString strBIDSIZE_ICDC10 = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC10");		//매수10호가잔량 증감
CString strBIDSIZE_ICDC10_CLR = m_CommAgent.GetRealOutputData("V31", "BIDSIZE_ICDC10_CLR");		//[BIDSIZE_ICDC10]색참조(+상승, -하락)
CString strASKSIZE_ICDC10 = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC10");		//매도10호가잔량 증감
CString strASKSIZE_ICDC10_CLR = m_CommAgent.GetRealOutputData("V31", "ASKSIZE_ICDC10_CLR");		//[ASKSIZE_ICDC10]색참조(+상승, -하락)




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strSYMBOL = realCommRecvData.GetItem(0, 0);		//종목코드
CString strLOCDATE = realCommRecvData.GetItem(0, 1);		//현지일자
CString strLOCTIME = realCommRecvData.GetItem(0, 2);		//현지시간
CString strKORDATE = realCommRecvData.GetItem(0, 3);		//한국일자
CString strKORTIME = realCommRecvData.GetItem(0, 4);		//한국시간
CString strTOTBIDSIZE = realCommRecvData.GetItem(0, 5);		//매수호가 총잔량
CString strTOTASKSIZE = realCommRecvData.GetItem(0, 6);		//매도호가 총잔량
CString strTOTBIDCOUNT = realCommRecvData.GetItem(0, 7);		//매도호가 총건수
CString strTOTASKCOUNT = realCommRecvData.GetItem(0, 8);		//매수호가 총건수
CString strBID_1 = realCommRecvData.GetItem(0, 9);		//매수1호가
CString strBID_1_CLR = realCommRecvData.GetItem(0, 10);		//[BID_1]색참조(+상승, -하락)
CString strASK_1 = realCommRecvData.GetItem(0, 11);		//매도1호가
CString strASK_1_CLR = realCommRecvData.GetItem(0, 12);		//[ASK_1]색참조(+상승, -하락)
CString strBIDSIZE_1 = realCommRecvData.GetItem(0, 13);		//매수1호가잔량
CString strASKSIZE_1 = realCommRecvData.GetItem(0, 14);		//매도1호가잔량
CString strBIDCOUNT_1 = realCommRecvData.GetItem(0, 15);		//매수1호가건수
CString strASKCOUNT_1 = realCommRecvData.GetItem(0, 16);		//매도1호가건수
CString strBID_2 = realCommRecvData.GetItem(0, 17);		//매수2호가
CString strBID_2_CLR = realCommRecvData.GetItem(0, 18);		//[BID_2]색참조(+상승, -하락)
CString strASK_2 = realCommRecvData.GetItem(0, 19);		//매도2호가
CString strASK_2_CLR = realCommRecvData.GetItem(0, 20);		//[ASK_2]색참조(+상승, -하락)
CString strBIDSIZE_2 = realCommRecvData.GetItem(0, 21);		//매수2호가잔량
CString strASKSIZE_2 = realCommRecvData.GetItem(0, 22);		//매도2호가잔량
CString strBIDCOUNT_2 = realCommRecvData.GetItem(0, 23);		//매수2호가건수
CString strASKCOUNT_2 = realCommRecvData.GetItem(0, 24);		//매도2호가건수
CString strBID_3 = realCommRecvData.GetItem(0, 25);		//매수3호가
CString strBID_3_CLR = realCommRecvData.GetItem(0, 26);		//[BID_3]색참조(+상승, -하락)
CString strASK_3 = realCommRecvData.GetItem(0, 27);		//매도3호가
CString strASK_3_CLR = realCommRecvData.GetItem(0, 28);		//[ASK_3]색참조(+상승, -하락)
CString strBIDSIZE_3 = realCommRecvData.GetItem(0, 29);		//매수3호가잔량
CString strASKSIZE_3 = realCommRecvData.GetItem(0, 30);		//매도3호가잔량
CString strBIDCOUNT_3 = realCommRecvData.GetItem(0, 31);		//매수3호가건수
CString strASKCOUNT_3 = realCommRecvData.GetItem(0, 32);		//매도3호가건수
CString strBID_4 = realCommRecvData.GetItem(0, 33);		//매수4호가
CString strBID_4_CLR = realCommRecvData.GetItem(0, 34);		//[BID_4]색참조(+상승, -하락)
CString strASK_4 = realCommRecvData.GetItem(0, 35);		//매도4호가
CString strASK_4_CLR = realCommRecvData.GetItem(0, 36);		//[ASK_4]색참조(+상승, -하락)
CString strBIDSIZE_4 = realCommRecvData.GetItem(0, 37);		//매수4호가잔량
CString strASKSIZE_4 = realCommRecvData.GetItem(0, 38);		//매도4호가잔량
CString strBIDCOUNT_4 = realCommRecvData.GetItem(0, 39);		//매수4호가건수
CString strASKCOUNT_4 = realCommRecvData.GetItem(0, 40);		//매도4호가건수
CString strBID_5 = realCommRecvData.GetItem(0, 41);		//매수5호가
CString strBID_5_CLR = realCommRecvData.GetItem(0, 42);		//[BID_5]색참조(+상승, -하락)
CString strASK_5 = realCommRecvData.GetItem(0, 43);		//매도5호가
CString strASK_5_CLR = realCommRecvData.GetItem(0, 44);		//[ASK_5]색참조(+상승, -하락)
CString strBIDSIZE_5 = realCommRecvData.GetItem(0, 45);		//매수5호가잔량
CString strASKSIZE_5 = realCommRecvData.GetItem(0, 46);		//매도5호가잔량
CString strBIDCOUNT_5 = realCommRecvData.GetItem(0, 47);		//매수5호가건수
CString strASKCOUNT_5 = realCommRecvData.GetItem(0, 48);		//매도5호가건수
CString strBID_6 = realCommRecvData.GetItem(0, 49);		//매수6호가
CString strBID_6_CLR = realCommRecvData.GetItem(0, 50);		//[BID_6]색참조(+상승, -하락)
CString strASK_6 = realCommRecvData.GetItem(0, 51);		//매도6호가
CString strASK_6_CLR = realCommRecvData.GetItem(0, 52);		//[ASK_6]색참조(+상승, -하락)
CString strBIDSIZE_6 = realCommRecvData.GetItem(0, 53);		//매수6호가잔량
CString strASKSIZE_6 = realCommRecvData.GetItem(0, 54);		//매도6호가잔량
CString strBIDCOUNT_6 = realCommRecvData.GetItem(0, 55);		//매수6호가건수
CString strASKCOUNT_6 = realCommRecvData.GetItem(0, 56);		//매도6호가건수
CString strBID_7 = realCommRecvData.GetItem(0, 57);		//매수7호가
CString strBID_7_CLR = realCommRecvData.GetItem(0, 58);		//[BID_7]색참조(+상승, -하락)
CString strASK_7 = realCommRecvData.GetItem(0, 59);		//매도7호가
CString strASK_7_CLR = realCommRecvData.GetItem(0, 60);		//[ASK_7]색참조(+상승, -하락)
CString strBIDSIZE_7 = realCommRecvData.GetItem(0, 61);		//매수7호가잔량
CString strASKSIZE_7 = realCommRecvData.GetItem(0, 62);		//매도7호가잔량
CString strBIDCOUNT_7 = realCommRecvData.GetItem(0, 63);		//매수7호가건수
CString strASKCOUNT_7 = realCommRecvData.GetItem(0, 64);		//매도7호가건수
CString strBID_8 = realCommRecvData.GetItem(0, 65);		//매수8호가
CString strBID_8_CLR = realCommRecvData.GetItem(0, 66);		//[BID_8]색참조(+상승, -하락)
CString strASK_8 = realCommRecvData.GetItem(0, 67);		//매도8호가
CString strASK_8_CLR = realCommRecvData.GetItem(0, 68);		//[ASK_8]색참조(+상승, -하락)
CString strBIDSIZE_8 = realCommRecvData.GetItem(0, 69);		//매수8호가잔량
CString strASKSIZE_8 = realCommRecvData.GetItem(0, 70);		//매도8호가잔량
CString strBIDCOUNT_8 = realCommRecvData.GetItem(0, 71);		//매수8호가건수
CString strASKCOUNT_8 = realCommRecvData.GetItem(0, 72);		//매도8호가건수
CString strBID_9 = realCommRecvData.GetItem(0, 73);		//매수9호가
CString strBID_9_CLR = realCommRecvData.GetItem(0, 74);		//[BID_9]색참조(+상승, -하락)
CString strASK_9 = realCommRecvData.GetItem(0, 75);		//매도9호가
CString strASK_9_CLR = realCommRecvData.GetItem(0, 76);		//[ASK_9]색참조(+상승, -하락)
CString strBIDSIZE_9 = realCommRecvData.GetItem(0, 77);		//매수9호가잔량
CString strASKSIZE_9 = realCommRecvData.GetItem(0, 78);		//매도9호가잔량
CString strBIDCOUNT_9 = realCommRecvData.GetItem(0, 79);		//매수9호가건수
CString strASKCOUNT_9 = realCommRecvData.GetItem(0, 80);		//매도9호가건수
CString strBID_10 = realCommRecvData.GetItem(0, 81);		//매수10호가
CString strBID_10_CLR = realCommRecvData.GetItem(0, 82);		//[BID_10]색참조(+상승, -하락)
CString strASK_10 = realCommRecvData.GetItem(0, 83);		//매도10호가
CString strASK_10_CLR = realCommRecvData.GetItem(0, 84);		//[ASK_10]색참조(+상승, -하락)
CString strBIDSIZE_10 = realCommRecvData.GetItem(0, 85);		//매수10호가잔량
CString strASKSIZE_10 = realCommRecvData.GetItem(0, 86);		//매도10호가잔량
CString strBIDCOUNT_10 = realCommRecvData.GetItem(0, 87);		//매수10호가건수
CString strASKCOUNT_10 = realCommRecvData.GetItem(0, 88);		//매도10호가건수
CString strTOTBIDSIZE_ICDC = realCommRecvData.GetItem(0, 89);		//매수호가 총잔량 증감
CString strTOTBIDSIZE_ICDC_CLR = realCommRecvData.GetItem(0, 90);		//[TOTBIDSIZE_ICDC]색참조(+상승, -하락)
CString strTOTASKSIZE_ICDC = realCommRecvData.GetItem(0, 91);		//매도호가 총잔량 증감
CString strTOTASKSIZE_ICDC_CLR = realCommRecvData.GetItem(0, 92);		//[TOTASKSIZE_ICDC]색참조(+상승, -하락)
CString strBIDSIZE_ICDC1 = realCommRecvData.GetItem(0, 93);		//매수 1호가잔량 증감
CString strBIDSIZE_ICDC1_CLR = realCommRecvData.GetItem(0, 94);		//[BIDSIZE_ICDC1]색참조(+상승, -하락)
CString strASKSIZE_ICDC1 = realCommRecvData.GetItem(0, 95);		//매도 1호가잔량 증감
CString strASKSIZE_ICDC1_CLR = realCommRecvData.GetItem(0, 96);		//[ASKSIZE_ICDC1]색참조(+상승, -하락)
CString strBIDSIZE_ICDC2 = realCommRecvData.GetItem(0, 97);		//매수 2호가잔량 증감
CString strBIDSIZE_ICDC2_CLR = realCommRecvData.GetItem(0, 98);		//[BIDSIZE_ICDC2]색참조(+상승, -하락)
CString strASKSIZE_ICDC2 = realCommRecvData.GetItem(0, 99);		//매도 2호가잔량 증감
CString strASKSIZE_ICDC2_CLR = realCommRecvData.GetItem(0, 100);		//[ASKSIZE_ICDC2]색참조(+상승, -하락)
CString strBIDSIZE_ICDC3 = realCommRecvData.GetItem(0, 101);		//매수 3호가잔량 증감
CString strBIDSIZE_ICDC3_CLR = realCommRecvData.GetItem(0, 102);		//[BIDSIZE_ICDC3]색참조(+상승, -하락)
CString strASKSIZE_ICDC3 = realCommRecvData.GetItem(0, 103);		//매도 3호가잔량 증감
CString strASKSIZE_ICDC3_CLR = realCommRecvData.GetItem(0, 104);		//[ASKSIZE_ICDC3]색참조(+상승, -하락)
CString strBIDSIZE_ICDC4 = realCommRecvData.GetItem(0, 105);		//매수 4호가잔량 증감
CString strBIDSIZE_ICDC4_CLR = realCommRecvData.GetItem(0, 106);		//[BIDSIZE_ICDC4]색참조(+상승, -하락)
CString strASKSIZE_ICDC4 = realCommRecvData.GetItem(0, 107);		//매도 4호가잔량 증감
CString strASKSIZE_ICDC4_CLR = realCommRecvData.GetItem(0, 108);		//[ASKSIZE_ICDC4]색참조(+상승, -하락)
CString strBIDSIZE_ICDC5 = realCommRecvData.GetItem(0, 109);		//매수 5호가잔량 증감
CString strBIDSIZE_ICDC5_CLR = realCommRecvData.GetItem(0, 110);		//[BIDSIZE_ICDC5]색참조(+상승, -하락)
CString strASKSIZE_ICDC5 = realCommRecvData.GetItem(0, 111);		//매도 5호가잔량 증감
CString strASKSIZE_ICDC5_CLR = realCommRecvData.GetItem(0, 112);		//[ASKSIZE_ICDC5]색참조(+상승, -하락)
CString strBIDSIZE_ICDC6 = realCommRecvData.GetItem(0, 113);		//매수 6호가잔량 증감
CString strBIDSIZE_ICDC6_CLR = realCommRecvData.GetItem(0, 114);		//[BIDSIZE_ICDC6]색참조(+상승, -하락)
CString strASKSIZE_ICDC6 = realCommRecvData.GetItem(0, 115);		//매도 6호가잔량 증감
CString strASKSIZE_ICDC6_CLR = realCommRecvData.GetItem(0, 116);		//[ASKSIZE_ICDC6]색참조(+상승, -하락)
CString strBIDSIZE_ICDC7 = realCommRecvData.GetItem(0, 117);		//매수 7호가잔량 증감
CString strBIDSIZE_ICDC7_CLR = realCommRecvData.GetItem(0, 118);		//[BIDSIZE_ICDC7]색참조(+상승, -하락)
CString strASKSIZE_ICDC7 = realCommRecvData.GetItem(0, 119);		//매도 7호가잔량 증감
CString strASKSIZE_ICDC7_CLR = realCommRecvData.GetItem(0, 120);		//[ASKSIZE_ICDC7]색참조(+상승, -하락)
CString strBIDSIZE_ICDC8 = realCommRecvData.GetItem(0, 121);		//매수 8호가잔량 증감
CString strBIDSIZE_ICDC8_CLR = realCommRecvData.GetItem(0, 122);		//[BIDSIZE_ICDC8]색참조(+상승, -하락)
CString strASKSIZE_ICDC8 = realCommRecvData.GetItem(0, 123);		//매도 8호가잔량 증감
CString strASKSIZE_ICDC8_CLR = realCommRecvData.GetItem(0, 124);		//[ASKSIZE_ICDC8]색참조(+상승, -하락)
CString strBIDSIZE_ICDC9 = realCommRecvData.GetItem(0, 125);		//매수 9호가잔량 증감
CString strBIDSIZE_ICDC9_CLR = realCommRecvData.GetItem(0, 126);		//[BIDSIZE_ICDC9]색참조(+상승, -하락)
CString strASKSIZE_ICDC9 = realCommRecvData.GetItem(0, 127);		//매도 9호가잔량 증감
CString strASKSIZE_ICDC9_CLR = realCommRecvData.GetItem(0, 128);		//[ASKSIZE_ICDC9]색참조(+상승, -하락)
CString strBIDSIZE_ICDC10 = realCommRecvData.GetItem(0, 129);		//매수10호가잔량 증감
CString strBIDSIZE_ICDC10_CLR = realCommRecvData.GetItem(0, 130);		//[BIDSIZE_ICDC10]색참조(+상승, -하락)
CString strASKSIZE_ICDC10 = realCommRecvData.GetItem(0, 131);		//매도10호가잔량 증감
CString strASKSIZE_ICDC10_CLR = realCommRecvData.GetItem(0, 132);		//[ASKSIZE_ICDC10]색참조(+상승, -하락)
