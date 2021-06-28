BEGIN_FUNCTION_MAP
	REAL_TYPE=167, REAL_NAME=V43, DESCRIPTION=이데일리 FX 체결;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SYMBOL, TYPE=string, SIZE=16, KEY=1, CAPTION=종목코드, FID=1;
			 INDEX=1, ITEM=XYMD, TYPE=string, SIZE=8, KEY=0, CAPTION=거래일자(현지일자), FID=9;
			 INDEX=2, ITEM=XHMS, TYPE=string, SIZE=6, KEY=0, CAPTION=거래시간(현지시간), FID=8;
			 INDEX=3, ITEM=KYMD, TYPE=string, SIZE=8, KEY=0, CAPTION=거래일자(한국일자), FID=1173;
			 INDEX=4, ITEM=KHMS, TYPE=string, SIZE=6, KEY=0, CAPTION=거래시간(한국시간), FID=1174;
			 INDEX=5, ITEM=OPEN, TYPE=string, SIZE=18, KEY=0, CAPTION=시가, FID=13;
			 INDEX=6, ITEM=OPEN_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPEN]색참조(+상승, -하락), FID=0;
			 INDEX=7, ITEM=HIGH, TYPE=string, SIZE=18, KEY=0, CAPTION=고가, FID=14;
			 INDEX=8, ITEM=HIGH_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[HIGH]색참조(+상승, -하락), FID=0;
			 INDEX=9, ITEM=LOW, TYPE=string, SIZE=18, KEY=0, CAPTION=저가, FID=15;
			 INDEX=10, ITEM=LOW_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LOW]색참조(+상승, -하락), FID=0;
			 INDEX=11, ITEM=LAST, TYPE=string, SIZE=18, KEY=0, CAPTION=현재가, FID=4;
			 INDEX=12, ITEM=LAST_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LAST]색참조(+상승, -하락), FID=0;
			 INDEX=13, ITEM=SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=대비부호, FID=6;
			 INDEX=14, ITEM=DIFF, TYPE=string, SIZE=18, KEY=0, CAPTION=전일대비, FID=5;
			 INDEX=15, ITEM=DIFF_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[DIFF]색참조(+상승, -하락), FID=0;
			 INDEX=16, ITEM=RATE, TYPE=string, SIZE=18, KEY=0, CAPTION=등락율, FID=7;
			 INDEX=17, ITEM=RATE_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RATE]색참조(+상승, -하락), FID=0;
			 INDEX=18, ITEM=MSGA, TYPE=string, SIZE=18, KEY=0, CAPTION=매수호가, FID=39;
			 INDEX=19, ITEM=MSGA_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[MSGA]색참조(+상승, -하락), FID=0;
			 INDEX=20, ITEM=STIM, TYPE=string, SIZE=6, KEY=0, CAPTION=매수호가시간, FID=0;
			 INDEX=21, ITEM=MDGA, TYPE=string, SIZE=18, KEY=0, CAPTION=매도호가, FID=29;
			 INDEX=22, ITEM=MDGA_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[MDGA]색참조(+상승, -하락), FID=0;
			 INDEX=23, ITEM=DTIM, TYPE=string, SIZE=6, KEY=0, CAPTION=매도호가시간, FID=0;
			 INDEX=24, ITEM=BANK, TYPE=string, SIZE=4, KEY=0, CAPTION=Contributor code, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strSYMBOL = m_CommAgent.GetRealOutputData("V43", "SYMBOL");		//종목코드
CString strXYMD = m_CommAgent.GetRealOutputData("V43", "XYMD");		//거래일자(현지일자)
CString strXHMS = m_CommAgent.GetRealOutputData("V43", "XHMS");		//거래시간(현지시간)
CString strKYMD = m_CommAgent.GetRealOutputData("V43", "KYMD");		//거래일자(한국일자)
CString strKHMS = m_CommAgent.GetRealOutputData("V43", "KHMS");		//거래시간(한국시간)
CString strOPEN = m_CommAgent.GetRealOutputData("V43", "OPEN");		//시가
CString strOPEN_CLR = m_CommAgent.GetRealOutputData("V43", "OPEN_CLR");		//[OPEN]색참조(+상승, -하락)
CString strHIGH = m_CommAgent.GetRealOutputData("V43", "HIGH");		//고가
CString strHIGH_CLR = m_CommAgent.GetRealOutputData("V43", "HIGH_CLR");		//[HIGH]색참조(+상승, -하락)
CString strLOW = m_CommAgent.GetRealOutputData("V43", "LOW");		//저가
CString strLOW_CLR = m_CommAgent.GetRealOutputData("V43", "LOW_CLR");		//[LOW]색참조(+상승, -하락)
CString strLAST = m_CommAgent.GetRealOutputData("V43", "LAST");		//현재가
CString strLAST_CLR = m_CommAgent.GetRealOutputData("V43", "LAST_CLR");		//[LAST]색참조(+상승, -하락)
CString strSIGN = m_CommAgent.GetRealOutputData("V43", "SIGN");		//대비부호
CString strDIFF = m_CommAgent.GetRealOutputData("V43", "DIFF");		//전일대비
CString strDIFF_CLR = m_CommAgent.GetRealOutputData("V43", "DIFF_CLR");		//[DIFF]색참조(+상승, -하락)
CString strRATE = m_CommAgent.GetRealOutputData("V43", "RATE");		//등락율
CString strRATE_CLR = m_CommAgent.GetRealOutputData("V43", "RATE_CLR");		//[RATE]색참조(+상승, -하락)
CString strMSGA = m_CommAgent.GetRealOutputData("V43", "MSGA");		//매수호가
CString strMSGA_CLR = m_CommAgent.GetRealOutputData("V43", "MSGA_CLR");		//[MSGA]색참조(+상승, -하락)
CString strSTIM = m_CommAgent.GetRealOutputData("V43", "STIM");		//매수호가시간
CString strMDGA = m_CommAgent.GetRealOutputData("V43", "MDGA");		//매도호가
CString strMDGA_CLR = m_CommAgent.GetRealOutputData("V43", "MDGA_CLR");		//[MDGA]색참조(+상승, -하락)
CString strDTIM = m_CommAgent.GetRealOutputData("V43", "DTIM");		//매도호가시간
CString strBANK = m_CommAgent.GetRealOutputData("V43", "BANK");		//Contributor code




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strSYMBOL = realCommRecvData.GetItem(0, 0);		//종목코드
CString strXYMD = realCommRecvData.GetItem(0, 1);		//거래일자(현지일자)
CString strXHMS = realCommRecvData.GetItem(0, 2);		//거래시간(현지시간)
CString strKYMD = realCommRecvData.GetItem(0, 3);		//거래일자(한국일자)
CString strKHMS = realCommRecvData.GetItem(0, 4);		//거래시간(한국시간)
CString strOPEN = realCommRecvData.GetItem(0, 5);		//시가
CString strOPEN_CLR = realCommRecvData.GetItem(0, 6);		//[OPEN]색참조(+상승, -하락)
CString strHIGH = realCommRecvData.GetItem(0, 7);		//고가
CString strHIGH_CLR = realCommRecvData.GetItem(0, 8);		//[HIGH]색참조(+상승, -하락)
CString strLOW = realCommRecvData.GetItem(0, 9);		//저가
CString strLOW_CLR = realCommRecvData.GetItem(0, 10);		//[LOW]색참조(+상승, -하락)
CString strLAST = realCommRecvData.GetItem(0, 11);		//현재가
CString strLAST_CLR = realCommRecvData.GetItem(0, 12);		//[LAST]색참조(+상승, -하락)
CString strSIGN = realCommRecvData.GetItem(0, 13);		//대비부호
CString strDIFF = realCommRecvData.GetItem(0, 14);		//전일대비
CString strDIFF_CLR = realCommRecvData.GetItem(0, 15);		//[DIFF]색참조(+상승, -하락)
CString strRATE = realCommRecvData.GetItem(0, 16);		//등락율
CString strRATE_CLR = realCommRecvData.GetItem(0, 17);		//[RATE]색참조(+상승, -하락)
CString strMSGA = realCommRecvData.GetItem(0, 18);		//매수호가
CString strMSGA_CLR = realCommRecvData.GetItem(0, 19);		//[MSGA]색참조(+상승, -하락)
CString strSTIM = realCommRecvData.GetItem(0, 20);		//매수호가시간
CString strMDGA = realCommRecvData.GetItem(0, 21);		//매도호가
CString strMDGA_CLR = realCommRecvData.GetItem(0, 22);		//[MDGA]색참조(+상승, -하락)
CString strDTIM = realCommRecvData.GetItem(0, 23);		//매도호가시간
CString strBANK = realCommRecvData.GetItem(0, 24);		//Contributor code
