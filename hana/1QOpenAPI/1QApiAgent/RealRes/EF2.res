BEGIN_FUNCTION_MAP
	REAL_TYPE=215, REAL_NAME=EF2, DESCRIPTION=해외선물미결제;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=rltm_dpch_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=실시간통보구분코드, FID=0;
			 INDEX=1, ITEM=usr_id, TYPE=string, SIZE=20, KEY=1, CAPTION=사용자ID, FID=0;
			 INDEX=2, ITEM=rltm_dpch_prcs_dcd, TYPE=string, SIZE=2, KEY=0, CAPTION=실시간통보처리구분코드, FID=0;
			 INDEX=3, ITEM=cano, TYPE=string, SIZE=8, KEY=0, CAPTION=종합계좌번호, FID=0;
			 INDEX=4, ITEM=ctno, TYPE=string, SIZE=9, KEY=0, CAPTION=종합계좌대체번호, FID=0;
			 INDEX=5, ITEM=apno, TYPE=string, SIZE=3, KEY=0, CAPTION=계좌상품번호, FID=0;
			 INDEX=6, ITEM=cust_nm, TYPE=string, SIZE=50, KEY=0, CAPTION=고객명, FID=0;
			 INDEX=7, ITEM=prdt_cd, TYPE=string, SIZE=32, KEY=0, CAPTION=상품코드, FID=0;
			 INDEX=8, ITEM=prdt_nm, TYPE=string, SIZE=50, KEY=0, CAPTION=상품명, FID=0;
			 INDEX=9, ITEM=odrv_sell_buy_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=해외파생매도매수구분코드, FID=0;
			 INDEX=10, ITEM=ustl_ctrc_qnt_ctns, TYPE=string, SIZE=30, KEY=0, CAPTION=미결제약정수량내용, FID=0;
			 INDEX=11, ITEM=avr_cncs_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=평균체결가격내용, FID=0;
			 INDEX=12, ITEM=clr_psbl_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=청산가능수량내용, FID=0;
			 INDEX=13, ITEM=ncnc_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=미체결수량내용, FID=0;
			 INDEX=14, ITEM=odrv_pv_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=해외파생현재가내용, FID=0;
			 INDEX=15, ITEM=bfdt_prpt_mark, TYPE=string, SIZE=1, KEY=0, CAPTION=전일대비부호, FID=0;
			 INDEX=16, ITEM=bfdt_prpt_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=전일대비가격내용, FID=0;
			 INDEX=17, ITEM=bfdt_prpt_prc_rto_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=전일대비가격비율내용, FID=0;
			 INDEX=18, ITEM=odrv_evl_amt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=해외파생평가금액내용, FID=0;
			 INDEX=19, ITEM=evl_pfls_amt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=평가손익금액내용, FID=0;
			 INDEX=20, ITEM=pfls_rt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=손익율내용, FID=0;
			 INDEX=21, ITEM=pchs_amt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=매입금액내용, FID=0;
			 INDEX=22, ITEM=mlt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=승수내용, FID=0;
			 INDEX=23, ITEM=itm_dvsn, TYPE=string, SIZE=1, KEY=0, CAPTION=종목구분, FID=0;
			 INDEX=24, ITEM=crry_cd, TYPE=string, SIZE=3, KEY=0, CAPTION=통화코드, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strrltm_dpch_dcd = m_CommAgent.GetRealOutputData("EF2", "rltm_dpch_dcd");		//실시간통보구분코드
CString strusr_id = m_CommAgent.GetRealOutputData("EF2", "usr_id");		//사용자ID
CString strrltm_dpch_prcs_dcd = m_CommAgent.GetRealOutputData("EF2", "rltm_dpch_prcs_dcd");		//실시간통보처리구분코드
CString strcano = m_CommAgent.GetRealOutputData("EF2", "cano");		//종합계좌번호
CString strctno = m_CommAgent.GetRealOutputData("EF2", "ctno");		//종합계좌대체번호
CString strapno = m_CommAgent.GetRealOutputData("EF2", "apno");		//계좌상품번호
CString strcust_nm = m_CommAgent.GetRealOutputData("EF2", "cust_nm");		//고객명
CString strprdt_cd = m_CommAgent.GetRealOutputData("EF2", "prdt_cd");		//상품코드
CString strprdt_nm = m_CommAgent.GetRealOutputData("EF2", "prdt_nm");		//상품명
CString strodrv_sell_buy_dcd = m_CommAgent.GetRealOutputData("EF2", "odrv_sell_buy_dcd");		//해외파생매도매수구분코드
CString strustl_ctrc_qnt_ctns = m_CommAgent.GetRealOutputData("EF2", "ustl_ctrc_qnt_ctns");		//미결제약정수량내용
CString stravr_cncs_prc_ctns = m_CommAgent.GetRealOutputData("EF2", "avr_cncs_prc_ctns");		//평균체결가격내용
CString strclr_psbl_qnt_ctns = m_CommAgent.GetRealOutputData("EF2", "clr_psbl_qnt_ctns");		//청산가능수량내용
CString strncnc_qnt_ctns = m_CommAgent.GetRealOutputData("EF2", "ncnc_qnt_ctns");		//미체결수량내용
CString strodrv_pv_ctns = m_CommAgent.GetRealOutputData("EF2", "odrv_pv_ctns");		//해외파생현재가내용
CString strbfdt_prpt_mark = m_CommAgent.GetRealOutputData("EF2", "bfdt_prpt_mark");		//전일대비부호
CString strbfdt_prpt_prc_ctns = m_CommAgent.GetRealOutputData("EF2", "bfdt_prpt_prc_ctns");		//전일대비가격내용
CString strbfdt_prpt_prc_rto_ctns = m_CommAgent.GetRealOutputData("EF2", "bfdt_prpt_prc_rto_ctns");		//전일대비가격비율내용
CString strodrv_evl_amt_ctns = m_CommAgent.GetRealOutputData("EF2", "odrv_evl_amt_ctns");		//해외파생평가금액내용
CString strevl_pfls_amt_ctns = m_CommAgent.GetRealOutputData("EF2", "evl_pfls_amt_ctns");		//평가손익금액내용
CString strpfls_rt_ctns = m_CommAgent.GetRealOutputData("EF2", "pfls_rt_ctns");		//손익율내용
CString strpchs_amt_ctns = m_CommAgent.GetRealOutputData("EF2", "pchs_amt_ctns");		//매입금액내용
CString strmlt_ctns = m_CommAgent.GetRealOutputData("EF2", "mlt_ctns");		//승수내용
CString stritm_dvsn = m_CommAgent.GetRealOutputData("EF2", "itm_dvsn");		//종목구분
CString strcrry_cd = m_CommAgent.GetRealOutputData("EF2", "crry_cd");		//통화코드




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strrltm_dpch_dcd = realCommRecvData.GetItem(0, 0);		//실시간통보구분코드
CString strusr_id = realCommRecvData.GetItem(0, 1);		//사용자ID
CString strrltm_dpch_prcs_dcd = realCommRecvData.GetItem(0, 2);		//실시간통보처리구분코드
CString strcano = realCommRecvData.GetItem(0, 3);		//종합계좌번호
CString strctno = realCommRecvData.GetItem(0, 4);		//종합계좌대체번호
CString strapno = realCommRecvData.GetItem(0, 5);		//계좌상품번호
CString strcust_nm = realCommRecvData.GetItem(0, 6);		//고객명
CString strprdt_cd = realCommRecvData.GetItem(0, 7);		//상품코드
CString strprdt_nm = realCommRecvData.GetItem(0, 8);		//상품명
CString strodrv_sell_buy_dcd = realCommRecvData.GetItem(0, 9);		//해외파생매도매수구분코드
CString strustl_ctrc_qnt_ctns = realCommRecvData.GetItem(0, 10);		//미결제약정수량내용
CString stravr_cncs_prc_ctns = realCommRecvData.GetItem(0, 11);		//평균체결가격내용
CString strclr_psbl_qnt_ctns = realCommRecvData.GetItem(0, 12);		//청산가능수량내용
CString strncnc_qnt_ctns = realCommRecvData.GetItem(0, 13);		//미체결수량내용
CString strodrv_pv_ctns = realCommRecvData.GetItem(0, 14);		//해외파생현재가내용
CString strbfdt_prpt_mark = realCommRecvData.GetItem(0, 15);		//전일대비부호
CString strbfdt_prpt_prc_ctns = realCommRecvData.GetItem(0, 16);		//전일대비가격내용
CString strbfdt_prpt_prc_rto_ctns = realCommRecvData.GetItem(0, 17);		//전일대비가격비율내용
CString strodrv_evl_amt_ctns = realCommRecvData.GetItem(0, 18);		//해외파생평가금액내용
CString strevl_pfls_amt_ctns = realCommRecvData.GetItem(0, 19);		//평가손익금액내용
CString strpfls_rt_ctns = realCommRecvData.GetItem(0, 20);		//손익율내용
CString strpchs_amt_ctns = realCommRecvData.GetItem(0, 21);		//매입금액내용
CString strmlt_ctns = realCommRecvData.GetItem(0, 22);		//승수내용
CString stritm_dvsn = realCommRecvData.GetItem(0, 23);		//종목구분
CString strcrry_cd = realCommRecvData.GetItem(0, 24);		//통화코드
