BEGIN_FUNCTION_MAP
	REAL_TYPE=144, REAL_NAME=V30, DESCRIPTION=해외주식 체결;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SYMBOL, TYPE=string, SIZE=18, KEY=1, CAPTION=종목코드, FID=2730;
			 INDEX=1, ITEM=BUSIDATE, TYPE=string, SIZE=8, KEY=0, CAPTION=현지영업일자, FID=0;
			 INDEX=2, ITEM=LOCDATE, TYPE=string, SIZE=8, KEY=0, CAPTION=현지일자, FID=9;
			 INDEX=3, ITEM=LOCTIME, TYPE=string, SIZE=6, KEY=0, CAPTION=현지시간, FID=8;
			 INDEX=4, ITEM=KORDATE, TYPE=string, SIZE=8, KEY=0, CAPTION=한국일자, FID=1173;
			 INDEX=5, ITEM=KORTIME, TYPE=string, SIZE=6, KEY=0, CAPTION=한국시간, FID=1174;
			 INDEX=6, ITEM=OPEN, TYPE=string, SIZE=20, KEY=0, CAPTION=시가, FID=13;
			 INDEX=7, ITEM=OPEN_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPEN]색참조(+상승, -하락), FID=0;
			 INDEX=8, ITEM=HIGH, TYPE=string, SIZE=20, KEY=0, CAPTION=고가, FID=14;
			 INDEX=9, ITEM=HIGH_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[HIGH]색참조(+상승, -하락), FID=0;
			 INDEX=10, ITEM=LOW, TYPE=string, SIZE=20, KEY=0, CAPTION=저가, FID=15;
			 INDEX=11, ITEM=LOW_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LOW]색참조(+상승, -하락), FID=0;
			 INDEX=12, ITEM=LAST, TYPE=string, SIZE=20, KEY=0, CAPTION=현재가, FID=4;
			 INDEX=13, ITEM=LAST_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LAST]색참조(+상승, -하락), FID=0;
			 INDEX=14, ITEM=SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=대비부호, FID=6;
			 INDEX=15, ITEM=DIFF, TYPE=string, SIZE=20, KEY=0, CAPTION=전일대비, FID=5;
			 INDEX=16, ITEM=DIFF_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[DIFF]색참조(+상승, -하락), FID=0;
			 INDEX=17, ITEM=RATE, TYPE=string, SIZE=20, KEY=0, CAPTION=등락율, FID=7;
			 INDEX=18, ITEM=RATE_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RATE]색참조(+상승, -하락), FID=0;
			 INDEX=19, ITEM=BID, TYPE=string, SIZE=20, KEY=0, CAPTION=매수호가, FID=39;
			 INDEX=20, ITEM=BID_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BID]색참조(+상승, -하락), FID=0;
			 INDEX=21, ITEM=BIDSIZE, TYPE=string, SIZE=12, KEY=0, CAPTION=매수잔량, FID=73;
			 INDEX=22, ITEM=ASK, TYPE=string, SIZE=20, KEY=0, CAPTION=매도호가, FID=29;
			 INDEX=23, ITEM=ASK_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASK]색참조(+상승, -하락), FID=0;
			 INDEX=24, ITEM=ASKSIZE, TYPE=string, SIZE=12, KEY=0, CAPTION=매도잔량, FID=63;
			 INDEX=25, ITEM=EXEVOL, TYPE=string, SIZE=12, KEY=0, CAPTION=체결량, FID=83;
			 INDEX=26, ITEM=EXEVOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[EXEVOL]색참조(+상승, -하락), FID=0;
			 INDEX=27, ITEM=VOLUME, TYPE=string, SIZE=18, KEY=0, CAPTION=누적거래량, FID=11;
			 INDEX=28, ITEM=AMOUNT, TYPE=string, SIZE=18, KEY=0, CAPTION=누적거래대금, FID=0;
			 INDEX=29, ITEM=SESSION_ID, TYPE=string, SIZE=1, KEY=0, CAPTION=장구분, FID=0;
			 INDEX=30, ITEM=BID_EXEVOL_SUM, TYPE=string, SIZE=18, KEY=0, CAPTION=매수누적체결량, FID=0;
			 INDEX=31, ITEM=ASK_EXEVOL_SUM, TYPE=string, SIZE=18, KEY=0, CAPTION=매도누적체결량, FID=0;
			 INDEX=32, ITEM=RLTV, TYPE=string, SIZE=18, KEY=0, CAPTION=체결강도, FID=0;
			 INDEX=33, ITEM=RLTV_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RLTV]색참조(+상승, -하락), FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strSYMBOL = m_CommAgent.GetRealOutputData("V30", "SYMBOL");		//종목코드
CString strBUSIDATE = m_CommAgent.GetRealOutputData("V30", "BUSIDATE");		//현지영업일자
CString strLOCDATE = m_CommAgent.GetRealOutputData("V30", "LOCDATE");		//현지일자
CString strLOCTIME = m_CommAgent.GetRealOutputData("V30", "LOCTIME");		//현지시간
CString strKORDATE = m_CommAgent.GetRealOutputData("V30", "KORDATE");		//한국일자
CString strKORTIME = m_CommAgent.GetRealOutputData("V30", "KORTIME");		//한국시간
CString strOPEN = m_CommAgent.GetRealOutputData("V30", "OPEN");		//시가
CString strOPEN_CLR = m_CommAgent.GetRealOutputData("V30", "OPEN_CLR");		//[OPEN]색참조(+상승, -하락)
CString strHIGH = m_CommAgent.GetRealOutputData("V30", "HIGH");		//고가
CString strHIGH_CLR = m_CommAgent.GetRealOutputData("V30", "HIGH_CLR");		//[HIGH]색참조(+상승, -하락)
CString strLOW = m_CommAgent.GetRealOutputData("V30", "LOW");		//저가
CString strLOW_CLR = m_CommAgent.GetRealOutputData("V30", "LOW_CLR");		//[LOW]색참조(+상승, -하락)
CString strLAST = m_CommAgent.GetRealOutputData("V30", "LAST");		//현재가
CString strLAST_CLR = m_CommAgent.GetRealOutputData("V30", "LAST_CLR");		//[LAST]색참조(+상승, -하락)
CString strSIGN = m_CommAgent.GetRealOutputData("V30", "SIGN");		//대비부호
CString strDIFF = m_CommAgent.GetRealOutputData("V30", "DIFF");		//전일대비
CString strDIFF_CLR = m_CommAgent.GetRealOutputData("V30", "DIFF_CLR");		//[DIFF]색참조(+상승, -하락)
CString strRATE = m_CommAgent.GetRealOutputData("V30", "RATE");		//등락율
CString strRATE_CLR = m_CommAgent.GetRealOutputData("V30", "RATE_CLR");		//[RATE]색참조(+상승, -하락)
CString strBID = m_CommAgent.GetRealOutputData("V30", "BID");		//매수호가
CString strBID_CLR = m_CommAgent.GetRealOutputData("V30", "BID_CLR");		//[BID]색참조(+상승, -하락)
CString strBIDSIZE = m_CommAgent.GetRealOutputData("V30", "BIDSIZE");		//매수잔량
CString strASK = m_CommAgent.GetRealOutputData("V30", "ASK");		//매도호가
CString strASK_CLR = m_CommAgent.GetRealOutputData("V30", "ASK_CLR");		//[ASK]색참조(+상승, -하락)
CString strASKSIZE = m_CommAgent.GetRealOutputData("V30", "ASKSIZE");		//매도잔량
CString strEXEVOL = m_CommAgent.GetRealOutputData("V30", "EXEVOL");		//체결량
CString strEXEVOL_CLR = m_CommAgent.GetRealOutputData("V30", "EXEVOL_CLR");		//[EXEVOL]색참조(+상승, -하락)
CString strVOLUME = m_CommAgent.GetRealOutputData("V30", "VOLUME");		//누적거래량
CString strAMOUNT = m_CommAgent.GetRealOutputData("V30", "AMOUNT");		//누적거래대금
CString strSESSION_ID = m_CommAgent.GetRealOutputData("V30", "SESSION_ID");		//장구분
CString strBID_EXEVOL_SUM = m_CommAgent.GetRealOutputData("V30", "BID_EXEVOL_SUM");		//매수누적체결량
CString strASK_EXEVOL_SUM = m_CommAgent.GetRealOutputData("V30", "ASK_EXEVOL_SUM");		//매도누적체결량
CString strRLTV = m_CommAgent.GetRealOutputData("V30", "RLTV");		//체결강도
CString strRLTV_CLR = m_CommAgent.GetRealOutputData("V30", "RLTV_CLR");		//[RLTV]색참조(+상승, -하락)




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strSYMBOL = realCommRecvData.GetItem(0, 0);		//종목코드
CString strBUSIDATE = realCommRecvData.GetItem(0, 1);		//현지영업일자
CString strLOCDATE = realCommRecvData.GetItem(0, 2);		//현지일자
CString strLOCTIME = realCommRecvData.GetItem(0, 3);		//현지시간
CString strKORDATE = realCommRecvData.GetItem(0, 4);		//한국일자
CString strKORTIME = realCommRecvData.GetItem(0, 5);		//한국시간
CString strOPEN = realCommRecvData.GetItem(0, 6);		//시가
CString strOPEN_CLR = realCommRecvData.GetItem(0, 7);		//[OPEN]색참조(+상승, -하락)
CString strHIGH = realCommRecvData.GetItem(0, 8);		//고가
CString strHIGH_CLR = realCommRecvData.GetItem(0, 9);		//[HIGH]색참조(+상승, -하락)
CString strLOW = realCommRecvData.GetItem(0, 10);		//저가
CString strLOW_CLR = realCommRecvData.GetItem(0, 11);		//[LOW]색참조(+상승, -하락)
CString strLAST = realCommRecvData.GetItem(0, 12);		//현재가
CString strLAST_CLR = realCommRecvData.GetItem(0, 13);		//[LAST]색참조(+상승, -하락)
CString strSIGN = realCommRecvData.GetItem(0, 14);		//대비부호
CString strDIFF = realCommRecvData.GetItem(0, 15);		//전일대비
CString strDIFF_CLR = realCommRecvData.GetItem(0, 16);		//[DIFF]색참조(+상승, -하락)
CString strRATE = realCommRecvData.GetItem(0, 17);		//등락율
CString strRATE_CLR = realCommRecvData.GetItem(0, 18);		//[RATE]색참조(+상승, -하락)
CString strBID = realCommRecvData.GetItem(0, 19);		//매수호가
CString strBID_CLR = realCommRecvData.GetItem(0, 20);		//[BID]색참조(+상승, -하락)
CString strBIDSIZE = realCommRecvData.GetItem(0, 21);		//매수잔량
CString strASK = realCommRecvData.GetItem(0, 22);		//매도호가
CString strASK_CLR = realCommRecvData.GetItem(0, 23);		//[ASK]색참조(+상승, -하락)
CString strASKSIZE = realCommRecvData.GetItem(0, 24);		//매도잔량
CString strEXEVOL = realCommRecvData.GetItem(0, 25);		//체결량
CString strEXEVOL_CLR = realCommRecvData.GetItem(0, 26);		//[EXEVOL]색참조(+상승, -하락)
CString strVOLUME = realCommRecvData.GetItem(0, 27);		//누적거래량
CString strAMOUNT = realCommRecvData.GetItem(0, 28);		//누적거래대금
CString strSESSION_ID = realCommRecvData.GetItem(0, 29);		//장구분
CString strBID_EXEVOL_SUM = realCommRecvData.GetItem(0, 30);		//매수누적체결량
CString strASK_EXEVOL_SUM = realCommRecvData.GetItem(0, 31);		//매도누적체결량
CString strRLTV = realCommRecvData.GetItem(0, 32);		//체결강도
CString strRLTV_CLR = realCommRecvData.GetItem(0, 33);		//[RLTV]색참조(+상승, -하락)
