BEGIN_FUNCTION_MAP
	REAL_TYPE=211, REAL_NAME=IF0, DESCRIPTION=국내선물옵션체결통보;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=sDataType, TYPE=string, SIZE=2, KEY=0, CAPTION=데이터구분, FID=0;
			 INDEX=1, ITEM=sProcTime, TYPE=string, SIZE=6, KEY=0, CAPTION=처리시간, FID=0;
			 INDEX=2, ITEM=sComCode, TYPE=string, SIZE=3, KEY=0, CAPTION=매체구분, FID=0;
			 INDEX=3, ITEM=sUserID, TYPE=string, SIZE=20, KEY=1, CAPTION=사용자ID, FID=0;
			 INDEX=4, ITEM=sCtno, TYPE=string, SIZE=9, KEY=0, CAPTION=계좌대체번호, FID=0;
			 INDEX=5, ITEM=sAcctNo, TYPE=string, SIZE=11, KEY=0, CAPTION=계좌번호, FID=0;
			 INDEX=6, ITEM=sAcctName, TYPE=string, SIZE=50, KEY=0, CAPTION=계좌명, FID=0;
			 INDEX=7, ITEM=sBidCode, TYPE=string, SIZE=1, KEY=0, CAPTION=주문구분, FID=0;
			 INDEX=8, ITEM=sModType, TYPE=string, SIZE=1, KEY=0, CAPTION=정정취소구분, FID=0;
			 INDEX=9, ITEM=sItemCode, TYPE=string, SIZE=12, KEY=0, CAPTION=단축종목코드, FID=0;
			 INDEX=10, ITEM=sItemName, TYPE=string, SIZE=50, KEY=0, CAPTION=종목명, FID=0;
			 INDEX=11, ITEM=sOrdVol, TYPE=string, SIZE=10, KEY=0, CAPTION=주문수량, FID=0;
			 INDEX=12, ITEM=sOrdPrice, TYPE=string, SIZE=11, KEY=0, CAPTION=주문가격, FID=0;
			 INDEX=13, ITEM=sHogaType, TYPE=string, SIZE=2, KEY=0, CAPTION=호가구분, FID=0;
			 INDEX=14, ITEM=sOrderCon, TYPE=string, SIZE=2, KEY=0, CAPTION=주문조건, FID=0;
			 INDEX=15, ITEM=sBrnNo, TYPE=string, SIZE=5, KEY=0, CAPTION=지점번호, FID=0;
			 INDEX=16, ITEM=sOrdNo, TYPE=string, SIZE=10, KEY=0, CAPTION=주문번호, FID=0;
			 INDEX=17, ITEM=sOrgOrdNo, TYPE=string, SIZE=10, KEY=0, CAPTION=원주문번호, FID=0;
			 INDEX=18, ITEM=sContVol, TYPE=string, SIZE=10, KEY=0, CAPTION=체결수량, FID=0;
			 INDEX=19, ITEM=sContPrice, TYPE=string, SIZE=11, KEY=0, CAPTION=체결가격, FID=0;
			 INDEX=20, ITEM=sRejectCode, TYPE=string, SIZE=4, KEY=0, CAPTION=거부사유코드, FID=0;
			 INDEX=21, ITEM=sRejectReason, TYPE=string, SIZE=40, KEY=0, CAPTION=거부사유, FID=0;
			 INDEX=22, ITEM=sUnContVol, TYPE=string, SIZE=10, KEY=0, CAPTION=미체결수량, FID=0;
			 INDEX=23, ITEM=sFotsTradeUnit, TYPE=string, SIZE=16, KEY=0, CAPTION=거래승수, FID=0;
			 INDEX=24, ITEM=sChegNo, TYPE=string, SIZE=10, KEY=0, CAPTION=체결번호, FID=0;
			 INDEX=25, ITEM=sFstPrc, TYPE=string, SIZE=11, KEY=0, CAPTION=근월물 체결가격(스프레드), FID=0;
			 INDEX=26, ITEM=sSndPrc, TYPE=string, SIZE=11, KEY=0, CAPTION=원월물 체결가격(스프레드), FID=0;
			 INDEX=27, ITEM=sWrapNo, TYPE=string, SIZE=10, KEY=0, CAPTION=Wrap주문번호, FID=0;
			 INDEX=28, ITEM=sGroupNo, TYPE=string, SIZE=5, KEY=0, CAPTION=그룹번호, FID=0;
			 INDEX=29, ITEM=sSeqNo, TYPE=string, SIZE=8, KEY=0, CAPTION=바스켓시퀀스, FID=0;
			 INDEX=30, ITEM=sFee, TYPE=string, SIZE=8, KEY=0, CAPTION=수수료, FID=0;
			 INDEX=31, ITEM=sFiller, TYPE=string, SIZE=31, KEY=0, CAPTION=Filler, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strsDataType = m_CommAgent.GetRealOutputData("IF0", "sDataType");		//데이터구분
CString strsProcTime = m_CommAgent.GetRealOutputData("IF0", "sProcTime");		//처리시간
CString strsComCode = m_CommAgent.GetRealOutputData("IF0", "sComCode");		//매체구분
CString strsUserID = m_CommAgent.GetRealOutputData("IF0", "sUserID");		//사용자ID
CString strsCtno = m_CommAgent.GetRealOutputData("IF0", "sCtno");		//계좌대체번호
CString strsAcctNo = m_CommAgent.GetRealOutputData("IF0", "sAcctNo");		//계좌번호
CString strsAcctName = m_CommAgent.GetRealOutputData("IF0", "sAcctName");		//계좌명
CString strsBidCode = m_CommAgent.GetRealOutputData("IF0", "sBidCode");		//주문구분
CString strsModType = m_CommAgent.GetRealOutputData("IF0", "sModType");		//정정취소구분
CString strsItemCode = m_CommAgent.GetRealOutputData("IF0", "sItemCode");		//단축종목코드
CString strsItemName = m_CommAgent.GetRealOutputData("IF0", "sItemName");		//종목명
CString strsOrdVol = m_CommAgent.GetRealOutputData("IF0", "sOrdVol");		//주문수량
CString strsOrdPrice = m_CommAgent.GetRealOutputData("IF0", "sOrdPrice");		//주문가격
CString strsHogaType = m_CommAgent.GetRealOutputData("IF0", "sHogaType");		//호가구분
CString strsOrderCon = m_CommAgent.GetRealOutputData("IF0", "sOrderCon");		//주문조건
CString strsBrnNo = m_CommAgent.GetRealOutputData("IF0", "sBrnNo");		//지점번호
CString strsOrdNo = m_CommAgent.GetRealOutputData("IF0", "sOrdNo");		//주문번호
CString strsOrgOrdNo = m_CommAgent.GetRealOutputData("IF0", "sOrgOrdNo");		//원주문번호
CString strsContVol = m_CommAgent.GetRealOutputData("IF0", "sContVol");		//체결수량
CString strsContPrice = m_CommAgent.GetRealOutputData("IF0", "sContPrice");		//체결가격
CString strsRejectCode = m_CommAgent.GetRealOutputData("IF0", "sRejectCode");		//거부사유코드
CString strsRejectReason = m_CommAgent.GetRealOutputData("IF0", "sRejectReason");		//거부사유
CString strsUnContVol = m_CommAgent.GetRealOutputData("IF0", "sUnContVol");		//미체결수량
CString strsFotsTradeUnit = m_CommAgent.GetRealOutputData("IF0", "sFotsTradeUnit");		//거래승수
CString strsChegNo = m_CommAgent.GetRealOutputData("IF0", "sChegNo");		//체결번호
CString strsFstPrc = m_CommAgent.GetRealOutputData("IF0", "sFstPrc");		//근월물 체결가격(스프레드)
CString strsSndPrc = m_CommAgent.GetRealOutputData("IF0", "sSndPrc");		//원월물 체결가격(스프레드)
CString strsWrapNo = m_CommAgent.GetRealOutputData("IF0", "sWrapNo");		//Wrap주문번호
CString strsGroupNo = m_CommAgent.GetRealOutputData("IF0", "sGroupNo");		//그룹번호
CString strsSeqNo = m_CommAgent.GetRealOutputData("IF0", "sSeqNo");		//바스켓시퀀스
CString strsFee = m_CommAgent.GetRealOutputData("IF0", "sFee");		//수수료
CString strsFiller = m_CommAgent.GetRealOutputData("IF0", "sFiller");		//Filler




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strsDataType = realCommRecvData.GetItem(0, 0);		//데이터구분
CString strsProcTime = realCommRecvData.GetItem(0, 1);		//처리시간
CString strsComCode = realCommRecvData.GetItem(0, 2);		//매체구분
CString strsUserID = realCommRecvData.GetItem(0, 3);		//사용자ID
CString strsCtno = realCommRecvData.GetItem(0, 4);		//계좌대체번호
CString strsAcctNo = realCommRecvData.GetItem(0, 5);		//계좌번호
CString strsAcctName = realCommRecvData.GetItem(0, 6);		//계좌명
CString strsBidCode = realCommRecvData.GetItem(0, 7);		//주문구분
CString strsModType = realCommRecvData.GetItem(0, 8);		//정정취소구분
CString strsItemCode = realCommRecvData.GetItem(0, 9);		//단축종목코드
CString strsItemName = realCommRecvData.GetItem(0, 10);		//종목명
CString strsOrdVol = realCommRecvData.GetItem(0, 11);		//주문수량
CString strsOrdPrice = realCommRecvData.GetItem(0, 12);		//주문가격
CString strsHogaType = realCommRecvData.GetItem(0, 13);		//호가구분
CString strsOrderCon = realCommRecvData.GetItem(0, 14);		//주문조건
CString strsBrnNo = realCommRecvData.GetItem(0, 15);		//지점번호
CString strsOrdNo = realCommRecvData.GetItem(0, 16);		//주문번호
CString strsOrgOrdNo = realCommRecvData.GetItem(0, 17);		//원주문번호
CString strsContVol = realCommRecvData.GetItem(0, 18);		//체결수량
CString strsContPrice = realCommRecvData.GetItem(0, 19);		//체결가격
CString strsRejectCode = realCommRecvData.GetItem(0, 20);		//거부사유코드
CString strsRejectReason = realCommRecvData.GetItem(0, 21);		//거부사유
CString strsUnContVol = realCommRecvData.GetItem(0, 22);		//미체결수량
CString strsFotsTradeUnit = realCommRecvData.GetItem(0, 23);		//거래승수
CString strsChegNo = realCommRecvData.GetItem(0, 24);		//체결번호
CString strsFstPrc = realCommRecvData.GetItem(0, 25);		//근월물 체결가격(스프레드)
CString strsSndPrc = realCommRecvData.GetItem(0, 26);		//원월물 체결가격(스프레드)
CString strsWrapNo = realCommRecvData.GetItem(0, 27);		//Wrap주문번호
CString strsGroupNo = realCommRecvData.GetItem(0, 28);		//그룹번호
CString strsSeqNo = realCommRecvData.GetItem(0, 29);		//바스켓시퀀스
CString strsFee = realCommRecvData.GetItem(0, 30);		//수수료
CString strsFiller = realCommRecvData.GetItem(0, 31);		//Filler
