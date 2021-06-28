BEGIN_FUNCTION_MAP
	REAL_TYPE=138, REAL_NAME=V20, DESCRIPTION=해외옵션 체결;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=QTTN_PRDT_CD, TYPE=string, SIZE=32, KEY=1, CAPTION=종목코드(내부), FID=0;
			 INDEX=1, ITEM=CURRENT_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=현영업일, 거래일자, FID=0;
			 INDEX=2, ITEM=TRADE_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=일자, FID=0;
			 INDEX=3, ITEM=TRADE_TIME, TYPE=string, SIZE=6, KEY=0, CAPTION=시간, FID=0;
			 INDEX=4, ITEM=KTRADE_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=한국일자, FID=0;
			 INDEX=5, ITEM=KTRADE_TIME, TYPE=string, SIZE=6, KEY=0, CAPTION=한국시간, FID=0;
			 INDEX=6, ITEM=RPT_SEQ, TYPE=string, SIZE=8, KEY=0, CAPTION=seq, FID=0;
			 INDEX=7, ITEM=GLOBEX_TP, TYPE=string, SIZE=1, KEY=0, CAPTION=전산장구분, FID=0;
			 INDEX=8, ITEM=TRDPRC_1, TYPE=string, SIZE=20, KEY=0, CAPTION=현재가, FID=0;
			 INDEX=9, ITEM=TRDPRC_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[TRDPRC_1]색참조(+상승, -하락), FID=0;
			 INDEX=10, ITEM=NETCHNG_CLS, TYPE=string, SIZE=1, KEY=0, CAPTION=전일대비구분, FID=0;
			 INDEX=11, ITEM=NETCHNG_1, TYPE=string, SIZE=20, KEY=0, CAPTION=전일대비, FID=0;
			 INDEX=12, ITEM=NETCHNG_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NETCHNG_1]색참조(+상승, -하락), FID=0;
			 INDEX=13, ITEM=PCTCHNG_1, TYPE=string, SIZE=6, KEY=0, CAPTION=전일대비율, FID=0;
			 INDEX=14, ITEM=PCTCHNG_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PCTCHNG_1]색참조(+상승, -하락), FID=0;
			 INDEX=15, ITEM=TRDVOL_1, TYPE=string, SIZE=12, KEY=0, CAPTION=체결수량, FID=0;
			 INDEX=16, ITEM=TRDVOL_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[TRDVOL_1]색참조(+상승, -하락), FID=0;
			 INDEX=17, ITEM=ACVOL_1, TYPE=string, SIZE=12, KEY=0, CAPTION=누적체결수량, FID=0;
			 INDEX=18, ITEM=OPEN_PRC, TYPE=string, SIZE=20, KEY=0, CAPTION=시가, FID=0;
			 INDEX=19, ITEM=OPEN_PRC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPEN_PRC]색참조(+상승, -하락), FID=0;
			 INDEX=20, ITEM=HIGH_1, TYPE=string, SIZE=20, KEY=0, CAPTION=고가, FID=0;
			 INDEX=21, ITEM=HIGH_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[HIGH_1]색참조(+상승, -하락), FID=0;
			 INDEX=22, ITEM=LOW_1, TYPE=string, SIZE=20, KEY=0, CAPTION=저가, FID=0;
			 INDEX=23, ITEM=LOW_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LOW_1]색참조(+상승, -하락), FID=0;
			 INDEX=24, ITEM=OPEN_TIME, TYPE=string, SIZE=6, KEY=0, CAPTION=시가시간, FID=0;
			 INDEX=25, ITEM=HIGH_TIME, TYPE=string, SIZE=6, KEY=0, CAPTION=고가시간, FID=0;
			 INDEX=26, ITEM=LOW_TIME, TYPE=string, SIZE=6, KEY=0, CAPTION=저가시간, FID=0;
			 INDEX=27, ITEM=BID_EXEC_SUM, TYPE=string, SIZE=15, KEY=0, CAPTION=당일 누적체결수량(매수성향), FID=0;
			 INDEX=28, ITEM=ASK_EXEC_SUM, TYPE=string, SIZE=15, KEY=0, CAPTION=당일 누적체결수량(매도성향), FID=0;
			 INDEX=29, ITEM=BOH_EXEC_SUM, TYPE=string, SIZE=15, KEY=0, CAPTION=당일 누적체결수량(보합), FID=0;
			 INDEX=30, ITEM=EX_BEST_BID1, TYPE=string, SIZE=20, KEY=0, CAPTION=체결시 매수 1호가(거래소), FID=0;
			 INDEX=31, ITEM=EX_BEST_BID1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[EX_BEST_BID1]색참조(+상승, -하락), FID=0;
			 INDEX=32, ITEM=EX_BEST_ASK1, TYPE=string, SIZE=20, KEY=0, CAPTION=체결시 매도 1호가(거래소), FID=0;
			 INDEX=33, ITEM=EX_BEST_ASK1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[EX_BEST_ASK1]색참조(+상승, -하락), FID=0;
			 INDEX=34, ITEM=EX_BEST_BSIZ1, TYPE=string, SIZE=12, KEY=0, CAPTION=체결시 매수 1수량(거래소), FID=0;
			 INDEX=35, ITEM=EX_BEST_ASIZ1, TYPE=string, SIZE=12, KEY=0, CAPTION=체결시 매도 1수량(거래소), FID=0;
			 INDEX=36, ITEM=OPENINTEREST, TYPE=string, SIZE=12, KEY=0, CAPTION=미결제량, FID=0;
			 INDEX=37, ITEM=OP_NETCHNG_1, TYPE=string, SIZE=12, KEY=0, CAPTION=미체결량대비, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strQTTN_PRDT_CD = m_CommAgent.GetRealOutputData("V20", "QTTN_PRDT_CD");		//종목코드(내부)
CString strCURRENT_DATE = m_CommAgent.GetRealOutputData("V20", "CURRENT_DATE");		//현영업일, 거래일자
CString strTRADE_DATE = m_CommAgent.GetRealOutputData("V20", "TRADE_DATE");		//일자
CString strTRADE_TIME = m_CommAgent.GetRealOutputData("V20", "TRADE_TIME");		//시간
CString strKTRADE_DATE = m_CommAgent.GetRealOutputData("V20", "KTRADE_DATE");		//한국일자
CString strKTRADE_TIME = m_CommAgent.GetRealOutputData("V20", "KTRADE_TIME");		//한국시간
CString strRPT_SEQ = m_CommAgent.GetRealOutputData("V20", "RPT_SEQ");		//seq
CString strGLOBEX_TP = m_CommAgent.GetRealOutputData("V20", "GLOBEX_TP");		//전산장구분
CString strTRDPRC_1 = m_CommAgent.GetRealOutputData("V20", "TRDPRC_1");		//현재가
CString strTRDPRC_1_CLR = m_CommAgent.GetRealOutputData("V20", "TRDPRC_1_CLR");		//[TRDPRC_1]색참조(+상승, -하락)
CString strNETCHNG_CLS = m_CommAgent.GetRealOutputData("V20", "NETCHNG_CLS");		//전일대비구분
CString strNETCHNG_1 = m_CommAgent.GetRealOutputData("V20", "NETCHNG_1");		//전일대비
CString strNETCHNG_1_CLR = m_CommAgent.GetRealOutputData("V20", "NETCHNG_1_CLR");		//[NETCHNG_1]색참조(+상승, -하락)
CString strPCTCHNG_1 = m_CommAgent.GetRealOutputData("V20", "PCTCHNG_1");		//전일대비율
CString strPCTCHNG_1_CLR = m_CommAgent.GetRealOutputData("V20", "PCTCHNG_1_CLR");		//[PCTCHNG_1]색참조(+상승, -하락)
CString strTRDVOL_1 = m_CommAgent.GetRealOutputData("V20", "TRDVOL_1");		//체결수량
CString strTRDVOL_1_CLR = m_CommAgent.GetRealOutputData("V20", "TRDVOL_1_CLR");		//[TRDVOL_1]색참조(+상승, -하락)
CString strACVOL_1 = m_CommAgent.GetRealOutputData("V20", "ACVOL_1");		//누적체결수량
CString strOPEN_PRC = m_CommAgent.GetRealOutputData("V20", "OPEN_PRC");		//시가
CString strOPEN_PRC_CLR = m_CommAgent.GetRealOutputData("V20", "OPEN_PRC_CLR");		//[OPEN_PRC]색참조(+상승, -하락)
CString strHIGH_1 = m_CommAgent.GetRealOutputData("V20", "HIGH_1");		//고가
CString strHIGH_1_CLR = m_CommAgent.GetRealOutputData("V20", "HIGH_1_CLR");		//[HIGH_1]색참조(+상승, -하락)
CString strLOW_1 = m_CommAgent.GetRealOutputData("V20", "LOW_1");		//저가
CString strLOW_1_CLR = m_CommAgent.GetRealOutputData("V20", "LOW_1_CLR");		//[LOW_1]색참조(+상승, -하락)
CString strOPEN_TIME = m_CommAgent.GetRealOutputData("V20", "OPEN_TIME");		//시가시간
CString strHIGH_TIME = m_CommAgent.GetRealOutputData("V20", "HIGH_TIME");		//고가시간
CString strLOW_TIME = m_CommAgent.GetRealOutputData("V20", "LOW_TIME");		//저가시간
CString strBID_EXEC_SUM = m_CommAgent.GetRealOutputData("V20", "BID_EXEC_SUM");		//당일 누적체결수량(매수성향)
CString strASK_EXEC_SUM = m_CommAgent.GetRealOutputData("V20", "ASK_EXEC_SUM");		//당일 누적체결수량(매도성향)
CString strBOH_EXEC_SUM = m_CommAgent.GetRealOutputData("V20", "BOH_EXEC_SUM");		//당일 누적체결수량(보합)
CString strEX_BEST_BID1 = m_CommAgent.GetRealOutputData("V20", "EX_BEST_BID1");		//체결시 매수 1호가(거래소)
CString strEX_BEST_BID1_CLR = m_CommAgent.GetRealOutputData("V20", "EX_BEST_BID1_CLR");		//[EX_BEST_BID1]색참조(+상승, -하락)
CString strEX_BEST_ASK1 = m_CommAgent.GetRealOutputData("V20", "EX_BEST_ASK1");		//체결시 매도 1호가(거래소)
CString strEX_BEST_ASK1_CLR = m_CommAgent.GetRealOutputData("V20", "EX_BEST_ASK1_CLR");		//[EX_BEST_ASK1]색참조(+상승, -하락)
CString strEX_BEST_BSIZ1 = m_CommAgent.GetRealOutputData("V20", "EX_BEST_BSIZ1");		//체결시 매수 1수량(거래소)
CString strEX_BEST_ASIZ1 = m_CommAgent.GetRealOutputData("V20", "EX_BEST_ASIZ1");		//체결시 매도 1수량(거래소)
CString strOPENINTEREST = m_CommAgent.GetRealOutputData("V20", "OPENINTEREST");		//미결제량
CString strOP_NETCHNG_1 = m_CommAgent.GetRealOutputData("V20", "OP_NETCHNG_1");		//미체결량대비




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strQTTN_PRDT_CD = realCommRecvData.GetItem(0, 0);		//종목코드(내부)
CString strCURRENT_DATE = realCommRecvData.GetItem(0, 1);		//현영업일, 거래일자
CString strTRADE_DATE = realCommRecvData.GetItem(0, 2);		//일자
CString strTRADE_TIME = realCommRecvData.GetItem(0, 3);		//시간
CString strKTRADE_DATE = realCommRecvData.GetItem(0, 4);		//한국일자
CString strKTRADE_TIME = realCommRecvData.GetItem(0, 5);		//한국시간
CString strRPT_SEQ = realCommRecvData.GetItem(0, 6);		//seq
CString strGLOBEX_TP = realCommRecvData.GetItem(0, 7);		//전산장구분
CString strTRDPRC_1 = realCommRecvData.GetItem(0, 8);		//현재가
CString strTRDPRC_1_CLR = realCommRecvData.GetItem(0, 9);		//[TRDPRC_1]색참조(+상승, -하락)
CString strNETCHNG_CLS = realCommRecvData.GetItem(0, 10);		//전일대비구분
CString strNETCHNG_1 = realCommRecvData.GetItem(0, 11);		//전일대비
CString strNETCHNG_1_CLR = realCommRecvData.GetItem(0, 12);		//[NETCHNG_1]색참조(+상승, -하락)
CString strPCTCHNG_1 = realCommRecvData.GetItem(0, 13);		//전일대비율
CString strPCTCHNG_1_CLR = realCommRecvData.GetItem(0, 14);		//[PCTCHNG_1]색참조(+상승, -하락)
CString strTRDVOL_1 = realCommRecvData.GetItem(0, 15);		//체결수량
CString strTRDVOL_1_CLR = realCommRecvData.GetItem(0, 16);		//[TRDVOL_1]색참조(+상승, -하락)
CString strACVOL_1 = realCommRecvData.GetItem(0, 17);		//누적체결수량
CString strOPEN_PRC = realCommRecvData.GetItem(0, 18);		//시가
CString strOPEN_PRC_CLR = realCommRecvData.GetItem(0, 19);		//[OPEN_PRC]색참조(+상승, -하락)
CString strHIGH_1 = realCommRecvData.GetItem(0, 20);		//고가
CString strHIGH_1_CLR = realCommRecvData.GetItem(0, 21);		//[HIGH_1]색참조(+상승, -하락)
CString strLOW_1 = realCommRecvData.GetItem(0, 22);		//저가
CString strLOW_1_CLR = realCommRecvData.GetItem(0, 23);		//[LOW_1]색참조(+상승, -하락)
CString strOPEN_TIME = realCommRecvData.GetItem(0, 24);		//시가시간
CString strHIGH_TIME = realCommRecvData.GetItem(0, 25);		//고가시간
CString strLOW_TIME = realCommRecvData.GetItem(0, 26);		//저가시간
CString strBID_EXEC_SUM = realCommRecvData.GetItem(0, 27);		//당일 누적체결수량(매수성향)
CString strASK_EXEC_SUM = realCommRecvData.GetItem(0, 28);		//당일 누적체결수량(매도성향)
CString strBOH_EXEC_SUM = realCommRecvData.GetItem(0, 29);		//당일 누적체결수량(보합)
CString strEX_BEST_BID1 = realCommRecvData.GetItem(0, 30);		//체결시 매수 1호가(거래소)
CString strEX_BEST_BID1_CLR = realCommRecvData.GetItem(0, 31);		//[EX_BEST_BID1]색참조(+상승, -하락)
CString strEX_BEST_ASK1 = realCommRecvData.GetItem(0, 32);		//체결시 매도 1호가(거래소)
CString strEX_BEST_ASK1_CLR = realCommRecvData.GetItem(0, 33);		//[EX_BEST_ASK1]색참조(+상승, -하락)
CString strEX_BEST_BSIZ1 = realCommRecvData.GetItem(0, 34);		//체결시 매수 1수량(거래소)
CString strEX_BEST_ASIZ1 = realCommRecvData.GetItem(0, 35);		//체결시 매도 1수량(거래소)
CString strOPENINTEREST = realCommRecvData.GetItem(0, 36);		//미결제량
CString strOP_NETCHNG_1 = realCommRecvData.GetItem(0, 37);		//미체결량대비
