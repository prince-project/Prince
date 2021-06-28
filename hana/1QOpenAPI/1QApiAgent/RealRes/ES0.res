BEGIN_FUNCTION_MAP
	REAL_TYPE=212, REAL_NAME=ES0, DESCRIPTION=해외주식체결통보;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=sMrktGroup, TYPE=string, SIZE=2, KEY=0, CAPTION=시장그룹, FID=0;
			 INDEX=1, ITEM=sDataType, TYPE=string, SIZE=2, KEY=0, CAPTION=데이터구분, FID=0;
			 INDEX=2, ITEM=sComCode, TYPE=string, SIZE=3, KEY=0, CAPTION=매체 구분, FID=0;
			 INDEX=3, ITEM=sUserID, TYPE=string, SIZE=20, KEY=1, CAPTION=사용자 ID, FID=0;
			 INDEX=4, ITEM=sCtno, TYPE=string, SIZE=9, KEY=0, CAPTION=계좌대체번호, FID=0;
			 INDEX=5, ITEM=sAcctNo, TYPE=string, SIZE=11, KEY=0, CAPTION=계좌번호, FID=0;
			 INDEX=6, ITEM=sAcctName, TYPE=string, SIZE=50, KEY=0, CAPTION=계좌명, FID=0;
			 INDEX=7, ITEM=sProcTime, TYPE=string, SIZE=6, KEY=0, CAPTION=접수시간, FID=0;
			 INDEX=8, ITEM=sOrdDt, TYPE=string, SIZE=8, KEY=0, CAPTION=주문일자, FID=0;
			 INDEX=9, ITEM=sOrdNo, TYPE=string, SIZE=10, KEY=0, CAPTION=주문번호, FID=0;
			 INDEX=10, ITEM=sOrgOrdNo, TYPE=string, SIZE=10, KEY=0, CAPTION=원주문번호, FID=0;
			 INDEX=11, ITEM=sItemCode, TYPE=string, SIZE=12, KEY=0, CAPTION=단축종목코드, FID=0;
			 INDEX=12, ITEM=sItemName, TYPE=string, SIZE=30, KEY=0, CAPTION=종목명, FID=0;
			 INDEX=13, ITEM=sBidCode, TYPE=string, SIZE=1, KEY=0, CAPTION=매도매수구분, FID=0;
			 INDEX=14, ITEM=sBidCodeName, TYPE=string, SIZE=10, KEY=0, CAPTION=매도매수구분명, FID=0;
			 INDEX=15, ITEM=sModType, TYPE=string, SIZE=1, KEY=0, CAPTION=정정취소구분, FID=0;
			 INDEX=16, ITEM=sOrdQty, TYPE=string, SIZE=10, KEY=0, CAPTION=주문수량, FID=0;
			 INDEX=17, ITEM=sOrdPrice, TYPE=string, SIZE=10, KEY=0, CAPTION=주문가격, FID=0;
			 INDEX=18, ITEM=sTotContQty, TYPE=string, SIZE=10, KEY=0, CAPTION=총체결수량, FID=0;
			 INDEX=19, ITEM=sAvgContPrice, TYPE=string, SIZE=10, KEY=0, CAPTION=평균체결가격, FID=0;
			 INDEX=20, ITEM=sUnContQty, TYPE=string, SIZE=10, KEY=0, CAPTION=미체결수량, FID=0;
			 INDEX=21, ITEM=sContAmt, TYPE=string, SIZE=15, KEY=0, CAPTION=체결금액, FID=0;
			 INDEX=22, ITEM=sCreditType, TYPE=string, SIZE=2, KEY=0, CAPTION=신용구분, FID=0;
			 INDEX=23, ITEM=sCreditLoanDate, TYPE=string, SIZE=8, KEY=0, CAPTION=신용대출일, FID=0;
			 INDEX=24, ITEM=sCreditSn, TYPE=string, SIZE=8, KEY=0, CAPTION=대출일련번호, FID=0;
			 INDEX=25, ITEM=sOrdStatName, TYPE=string, SIZE=20, KEY=0, CAPTION=주문상태, FID=0;
			 INDEX=26, ITEM=sOrdTpName, TYPE=string, SIZE=10, KEY=0, CAPTION=주문구분명, FID=0;
			 INDEX=27, ITEM=sOrdTime, TYPE=string, SIZE=8, KEY=0, CAPTION=주문시각, FID=0;
			 INDEX=28, ITEM=sCntrTime, TYPE=string, SIZE=8, KEY=0, CAPTION=체결시각, FID=0;
			 INDEX=29, ITEM=sLocOrdTime, TYPE=string, SIZE=8, KEY=0, CAPTION=현지주문시각, FID=0;
			 INDEX=30, ITEM=sLocCntrTime, TYPE=string, SIZE=8, KEY=0, CAPTION=현지체결시각, FID=0;
			 INDEX=31, ITEM=sOrdPriceTp, TYPE=string, SIZE=1, KEY=0, CAPTION=주문유형, FID=0;
			 INDEX=32, ITEM=sOrdPriceTpName, TYPE=string, SIZE=10, KEY=0, CAPTION=주문유형명, FID=0;
			 INDEX=33, ITEM=sOrdCond, TYPE=string, SIZE=1, KEY=0, CAPTION=주문조건, FID=0;
			 INDEX=34, ITEM=sOrdCondName, TYPE=string, SIZE=10, KEY=0, CAPTION=주문조건명, FID=0;
			 INDEX=35, ITEM=sInvInfMktDcd, TYPE=string, SIZE=2, KEY=0, CAPTION=해외주식시장구분코드, FID=0;
			 INDEX=36, ITEM=sOsMrktCd, TYPE=string, SIZE=2, KEY=0, CAPTION=해외시장코드, FID=0;
			 INDEX=37, ITEM=sOsMrktName, TYPE=string, SIZE=20, KEY=0, CAPTION=해외시장명, FID=0;
			 INDEX=38, ITEM=sCurrency, TYPE=string, SIZE=3, KEY=0, CAPTION=거래통화, FID=0;
			 INDEX=39, ITEM=sOrdMediaName, TYPE=string, SIZE=20, KEY=0, CAPTION=주문매체명, FID=0;
			 INDEX=40, ITEM=sOrdMembName, TYPE=string, SIZE=20, KEY=0, CAPTION=주문자명, FID=0;
			 INDEX=41, ITEM=sContQty, TYPE=string, SIZE=10, KEY=0, CAPTION=체결수량, FID=0;
			 INDEX=42, ITEM=sContPrice, TYPE=string, SIZE=10, KEY=0, CAPTION=체결가격, FID=0;
			 INDEX=43, ITEM=sFiller, TYPE=string, SIZE=114, KEY=0, CAPTION=Reservation Area, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strsMrktGroup = m_CommAgent.GetRealOutputData("ES0", "sMrktGroup");		//시장그룹
CString strsDataType = m_CommAgent.GetRealOutputData("ES0", "sDataType");		//데이터구분
CString strsComCode = m_CommAgent.GetRealOutputData("ES0", "sComCode");		//매체 구분
CString strsUserID = m_CommAgent.GetRealOutputData("ES0", "sUserID");		//사용자 ID
CString strsCtno = m_CommAgent.GetRealOutputData("ES0", "sCtno");		//계좌대체번호
CString strsAcctNo = m_CommAgent.GetRealOutputData("ES0", "sAcctNo");		//계좌번호
CString strsAcctName = m_CommAgent.GetRealOutputData("ES0", "sAcctName");		//계좌명
CString strsProcTime = m_CommAgent.GetRealOutputData("ES0", "sProcTime");		//접수시간
CString strsOrdDt = m_CommAgent.GetRealOutputData("ES0", "sOrdDt");		//주문일자
CString strsOrdNo = m_CommAgent.GetRealOutputData("ES0", "sOrdNo");		//주문번호
CString strsOrgOrdNo = m_CommAgent.GetRealOutputData("ES0", "sOrgOrdNo");		//원주문번호
CString strsItemCode = m_CommAgent.GetRealOutputData("ES0", "sItemCode");		//단축종목코드
CString strsItemName = m_CommAgent.GetRealOutputData("ES0", "sItemName");		//종목명
CString strsBidCode = m_CommAgent.GetRealOutputData("ES0", "sBidCode");		//매도매수구분
CString strsBidCodeName = m_CommAgent.GetRealOutputData("ES0", "sBidCodeName");		//매도매수구분명
CString strsModType = m_CommAgent.GetRealOutputData("ES0", "sModType");		//정정취소구분
CString strsOrdQty = m_CommAgent.GetRealOutputData("ES0", "sOrdQty");		//주문수량
CString strsOrdPrice = m_CommAgent.GetRealOutputData("ES0", "sOrdPrice");		//주문가격
CString strsTotContQty = m_CommAgent.GetRealOutputData("ES0", "sTotContQty");		//총체결수량
CString strsAvgContPrice = m_CommAgent.GetRealOutputData("ES0", "sAvgContPrice");		//평균체결가격
CString strsUnContQty = m_CommAgent.GetRealOutputData("ES0", "sUnContQty");		//미체결수량
CString strsContAmt = m_CommAgent.GetRealOutputData("ES0", "sContAmt");		//체결금액
CString strsCreditType = m_CommAgent.GetRealOutputData("ES0", "sCreditType");		//신용구분
CString strsCreditLoanDate = m_CommAgent.GetRealOutputData("ES0", "sCreditLoanDate");		//신용대출일
CString strsCreditSn = m_CommAgent.GetRealOutputData("ES0", "sCreditSn");		//대출일련번호
CString strsOrdStatName = m_CommAgent.GetRealOutputData("ES0", "sOrdStatName");		//주문상태
CString strsOrdTpName = m_CommAgent.GetRealOutputData("ES0", "sOrdTpName");		//주문구분명
CString strsOrdTime = m_CommAgent.GetRealOutputData("ES0", "sOrdTime");		//주문시각
CString strsCntrTime = m_CommAgent.GetRealOutputData("ES0", "sCntrTime");		//체결시각
CString strsLocOrdTime = m_CommAgent.GetRealOutputData("ES0", "sLocOrdTime");		//현지주문시각
CString strsLocCntrTime = m_CommAgent.GetRealOutputData("ES0", "sLocCntrTime");		//현지체결시각
CString strsOrdPriceTp = m_CommAgent.GetRealOutputData("ES0", "sOrdPriceTp");		//주문유형
CString strsOrdPriceTpName = m_CommAgent.GetRealOutputData("ES0", "sOrdPriceTpName");		//주문유형명
CString strsOrdCond = m_CommAgent.GetRealOutputData("ES0", "sOrdCond");		//주문조건
CString strsOrdCondName = m_CommAgent.GetRealOutputData("ES0", "sOrdCondName");		//주문조건명
CString strsInvInfMktDcd = m_CommAgent.GetRealOutputData("ES0", "sInvInfMktDcd");		//해외주식시장구분코드
CString strsOsMrktCd = m_CommAgent.GetRealOutputData("ES0", "sOsMrktCd");		//해외시장코드
CString strsOsMrktName = m_CommAgent.GetRealOutputData("ES0", "sOsMrktName");		//해외시장명
CString strsCurrency = m_CommAgent.GetRealOutputData("ES0", "sCurrency");		//거래통화
CString strsOrdMediaName = m_CommAgent.GetRealOutputData("ES0", "sOrdMediaName");		//주문매체명
CString strsOrdMembName = m_CommAgent.GetRealOutputData("ES0", "sOrdMembName");		//주문자명
CString strsContQty = m_CommAgent.GetRealOutputData("ES0", "sContQty");		//체결수량
CString strsContPrice = m_CommAgent.GetRealOutputData("ES0", "sContPrice");		//체결가격
CString strsFiller = m_CommAgent.GetRealOutputData("ES0", "sFiller");		//Reservation Area




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strsMrktGroup = realCommRecvData.GetItem(0, 0);		//시장그룹
CString strsDataType = realCommRecvData.GetItem(0, 1);		//데이터구분
CString strsComCode = realCommRecvData.GetItem(0, 2);		//매체 구분
CString strsUserID = realCommRecvData.GetItem(0, 3);		//사용자 ID
CString strsCtno = realCommRecvData.GetItem(0, 4);		//계좌대체번호
CString strsAcctNo = realCommRecvData.GetItem(0, 5);		//계좌번호
CString strsAcctName = realCommRecvData.GetItem(0, 6);		//계좌명
CString strsProcTime = realCommRecvData.GetItem(0, 7);		//접수시간
CString strsOrdDt = realCommRecvData.GetItem(0, 8);		//주문일자
CString strsOrdNo = realCommRecvData.GetItem(0, 9);		//주문번호
CString strsOrgOrdNo = realCommRecvData.GetItem(0, 10);		//원주문번호
CString strsItemCode = realCommRecvData.GetItem(0, 11);		//단축종목코드
CString strsItemName = realCommRecvData.GetItem(0, 12);		//종목명
CString strsBidCode = realCommRecvData.GetItem(0, 13);		//매도매수구분
CString strsBidCodeName = realCommRecvData.GetItem(0, 14);		//매도매수구분명
CString strsModType = realCommRecvData.GetItem(0, 15);		//정정취소구분
CString strsOrdQty = realCommRecvData.GetItem(0, 16);		//주문수량
CString strsOrdPrice = realCommRecvData.GetItem(0, 17);		//주문가격
CString strsTotContQty = realCommRecvData.GetItem(0, 18);		//총체결수량
CString strsAvgContPrice = realCommRecvData.GetItem(0, 19);		//평균체결가격
CString strsUnContQty = realCommRecvData.GetItem(0, 20);		//미체결수량
CString strsContAmt = realCommRecvData.GetItem(0, 21);		//체결금액
CString strsCreditType = realCommRecvData.GetItem(0, 22);		//신용구분
CString strsCreditLoanDate = realCommRecvData.GetItem(0, 23);		//신용대출일
CString strsCreditSn = realCommRecvData.GetItem(0, 24);		//대출일련번호
CString strsOrdStatName = realCommRecvData.GetItem(0, 25);		//주문상태
CString strsOrdTpName = realCommRecvData.GetItem(0, 26);		//주문구분명
CString strsOrdTime = realCommRecvData.GetItem(0, 27);		//주문시각
CString strsCntrTime = realCommRecvData.GetItem(0, 28);		//체결시각
CString strsLocOrdTime = realCommRecvData.GetItem(0, 29);		//현지주문시각
CString strsLocCntrTime = realCommRecvData.GetItem(0, 30);		//현지체결시각
CString strsOrdPriceTp = realCommRecvData.GetItem(0, 31);		//주문유형
CString strsOrdPriceTpName = realCommRecvData.GetItem(0, 32);		//주문유형명
CString strsOrdCond = realCommRecvData.GetItem(0, 33);		//주문조건
CString strsOrdCondName = realCommRecvData.GetItem(0, 34);		//주문조건명
CString strsInvInfMktDcd = realCommRecvData.GetItem(0, 35);		//해외주식시장구분코드
CString strsOsMrktCd = realCommRecvData.GetItem(0, 36);		//해외시장코드
CString strsOsMrktName = realCommRecvData.GetItem(0, 37);		//해외시장명
CString strsCurrency = realCommRecvData.GetItem(0, 38);		//거래통화
CString strsOrdMediaName = realCommRecvData.GetItem(0, 39);		//주문매체명
CString strsOrdMembName = realCommRecvData.GetItem(0, 40);		//주문자명
CString strsContQty = realCommRecvData.GetItem(0, 41);		//체결수량
CString strsContPrice = realCommRecvData.GetItem(0, 42);		//체결가격
CString strsFiller = realCommRecvData.GetItem(0, 43);		//Reservation Area
