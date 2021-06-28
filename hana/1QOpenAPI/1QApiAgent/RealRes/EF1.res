BEGIN_FUNCTION_MAP
	REAL_TYPE=214, REAL_NAME=EF1, DESCRIPTION=해외선물체결확인;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=rltm_dpch_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=실시간통보구분코드, FID=0;
			 INDEX=1, ITEM=usr_id, TYPE=string, SIZE=20, KEY=1, CAPTION=사용자ID, FID=0;
			 INDEX=2, ITEM=rltm_dpch_prcs_dcd, TYPE=string, SIZE=2, KEY=0, CAPTION=실시간통보처리구분코드, FID=0;
			 INDEX=3, ITEM=cano, TYPE=string, SIZE=8, KEY=0, CAPTION=종합계좌번호, FID=0;
			 INDEX=4, ITEM=ctno, TYPE=string, SIZE=9, KEY=0, CAPTION=종합계좌대체번호, FID=0;
			 INDEX=5, ITEM=apno, TYPE=string, SIZE=3, KEY=0, CAPTION=계좌상품번호, FID=0;
			 INDEX=6, ITEM=prdt_cd, TYPE=string, SIZE=32, KEY=0, CAPTION=상품코드, FID=0;
			 INDEX=7, ITEM=odrv_ordr_tp_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=해외파생주문유형구분코드, FID=0;
			 INDEX=8, ITEM=ordr_stts_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=주문상태구분코드, FID=0;
			 INDEX=9, ITEM=odrv_odno, TYPE=string, SIZE=16, KEY=0, CAPTION=해외파생주문번호, FID=0;
			 INDEX=10, ITEM=odrv_or_odno, TYPE=string, SIZE=16, KEY=0, CAPTION=해외파생원주문번호, FID=0;
			 INDEX=11, ITEM=ordr_dt, TYPE=string, SIZE=8, KEY=0, CAPTION=주문일자, FID=0;
			 INDEX=12, ITEM=cust_nm, TYPE=string, SIZE=50, KEY=0, CAPTION=고객명, FID=0;
			 INDEX=13, ITEM=odrv_sell_buy_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=해외파생매도매수구분코드, FID=0;
			 INDEX=14, ITEM=odrv_ordr_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=해외파생주문가격내용, FID=0;
			 INDEX=15, ITEM=ordr_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=주문수량내용, FID=0;
			 INDEX=16, ITEM=odrv_prc_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=해외파생가격구분코드, FID=0;
			 INDEX=17, ITEM=cncs_cnd_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=체결조건구분코드, FID=0;
			 INDEX=18, ITEM=cnd_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=조건가격내용, FID=0;
			 INDEX=19, ITEM=comm_mdia_dcd, TYPE=string, SIZE=3, KEY=0, CAPTION=통신매체구분코드, FID=0;
			 INDEX=20, ITEM=acpt_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=접수시각, FID=0;
			 INDEX=21, ITEM=excg_cncs_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=거래소체결시각, FID=0;
			 INDEX=22, ITEM=acpl_acpt_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=현지접수시각, FID=0;
			 INDEX=23, ITEM=cncs_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=체결시각, FID=0;
			 INDEX=24, ITEM=cncs_dt, TYPE=string, SIZE=8, KEY=0, CAPTION=체결일자, FID=0;
			 INDEX=25, ITEM=odrv_cncs_no, TYPE=string, SIZE=8, KEY=0, CAPTION=해외파생체결번호, FID=0;
			 INDEX=26, ITEM=cncs_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=체결수량내용, FID=0;
			 INDEX=27, ITEM=odrv_cncs_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=해외파생체결가격내용, FID=0;
			 INDEX=28, ITEM=odrv_cncs_amt_ctns, TYPE=string, SIZE=30, KEY=0, CAPTION=해외파생체결금액내용, FID=0;
			 INDEX=29, ITEM=crry_cd, TYPE=string, SIZE=3, KEY=0, CAPTION=통화코드, FID=0;
			 INDEX=30, ITEM=ordr_rmn_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=주문잔여수량내용, FID=0;
			 INDEX=31, ITEM=acnt_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=계좌구분코드, FID=0;
			 INDEX=32, ITEM=entr_clr_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=진입청산구분코드, FID=0;
			 INDEX=33, ITEM=clr_pst_no, TYPE=string, SIZE=16, KEY=0, CAPTION=청산포지션번호, FID=0;
			 INDEX=34, ITEM=pst_no, TYPE=string, SIZE=16, KEY=0, CAPTION=포지션번호, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strrltm_dpch_dcd = m_CommAgent.GetRealOutputData("EF1", "rltm_dpch_dcd");		//실시간통보구분코드
CString strusr_id = m_CommAgent.GetRealOutputData("EF1", "usr_id");		//사용자ID
CString strrltm_dpch_prcs_dcd = m_CommAgent.GetRealOutputData("EF1", "rltm_dpch_prcs_dcd");		//실시간통보처리구분코드
CString strcano = m_CommAgent.GetRealOutputData("EF1", "cano");		//종합계좌번호
CString strctno = m_CommAgent.GetRealOutputData("EF1", "ctno");		//종합계좌대체번호
CString strapno = m_CommAgent.GetRealOutputData("EF1", "apno");		//계좌상품번호
CString strprdt_cd = m_CommAgent.GetRealOutputData("EF1", "prdt_cd");		//상품코드
CString strodrv_ordr_tp_dcd = m_CommAgent.GetRealOutputData("EF1", "odrv_ordr_tp_dcd");		//해외파생주문유형구분코드
CString strordr_stts_dcd = m_CommAgent.GetRealOutputData("EF1", "ordr_stts_dcd");		//주문상태구분코드
CString strodrv_odno = m_CommAgent.GetRealOutputData("EF1", "odrv_odno");		//해외파생주문번호
CString strodrv_or_odno = m_CommAgent.GetRealOutputData("EF1", "odrv_or_odno");		//해외파생원주문번호
CString strordr_dt = m_CommAgent.GetRealOutputData("EF1", "ordr_dt");		//주문일자
CString strcust_nm = m_CommAgent.GetRealOutputData("EF1", "cust_nm");		//고객명
CString strodrv_sell_buy_dcd = m_CommAgent.GetRealOutputData("EF1", "odrv_sell_buy_dcd");		//해외파생매도매수구분코드
CString strodrv_ordr_prc_ctns = m_CommAgent.GetRealOutputData("EF1", "odrv_ordr_prc_ctns");		//해외파생주문가격내용
CString strordr_qnt_ctns = m_CommAgent.GetRealOutputData("EF1", "ordr_qnt_ctns");		//주문수량내용
CString strodrv_prc_dcd = m_CommAgent.GetRealOutputData("EF1", "odrv_prc_dcd");		//해외파생가격구분코드
CString strcncs_cnd_dcd = m_CommAgent.GetRealOutputData("EF1", "cncs_cnd_dcd");		//체결조건구분코드
CString strcnd_prc_ctns = m_CommAgent.GetRealOutputData("EF1", "cnd_prc_ctns");		//조건가격내용
CString strcomm_mdia_dcd = m_CommAgent.GetRealOutputData("EF1", "comm_mdia_dcd");		//통신매체구분코드
CString stracpt_tm = m_CommAgent.GetRealOutputData("EF1", "acpt_tm");		//접수시각
CString strexcg_cncs_tm = m_CommAgent.GetRealOutputData("EF1", "excg_cncs_tm");		//거래소체결시각
CString stracpl_acpt_tm = m_CommAgent.GetRealOutputData("EF1", "acpl_acpt_tm");		//현지접수시각
CString strcncs_tm = m_CommAgent.GetRealOutputData("EF1", "cncs_tm");		//체결시각
CString strcncs_dt = m_CommAgent.GetRealOutputData("EF1", "cncs_dt");		//체결일자
CString strodrv_cncs_no = m_CommAgent.GetRealOutputData("EF1", "odrv_cncs_no");		//해외파생체결번호
CString strcncs_qnt_ctns = m_CommAgent.GetRealOutputData("EF1", "cncs_qnt_ctns");		//체결수량내용
CString strodrv_cncs_prc_ctns = m_CommAgent.GetRealOutputData("EF1", "odrv_cncs_prc_ctns");		//해외파생체결가격내용
CString strodrv_cncs_amt_ctns = m_CommAgent.GetRealOutputData("EF1", "odrv_cncs_amt_ctns");		//해외파생체결금액내용
CString strcrry_cd = m_CommAgent.GetRealOutputData("EF1", "crry_cd");		//통화코드
CString strordr_rmn_qnt_ctns = m_CommAgent.GetRealOutputData("EF1", "ordr_rmn_qnt_ctns");		//주문잔여수량내용
CString stracnt_dcd = m_CommAgent.GetRealOutputData("EF1", "acnt_dcd");		//계좌구분코드
CString strentr_clr_dcd = m_CommAgent.GetRealOutputData("EF1", "entr_clr_dcd");		//진입청산구분코드
CString strclr_pst_no = m_CommAgent.GetRealOutputData("EF1", "clr_pst_no");		//청산포지션번호
CString strpst_no = m_CommAgent.GetRealOutputData("EF1", "pst_no");		//포지션번호




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
CString strprdt_cd = realCommRecvData.GetItem(0, 6);		//상품코드
CString strodrv_ordr_tp_dcd = realCommRecvData.GetItem(0, 7);		//해외파생주문유형구분코드
CString strordr_stts_dcd = realCommRecvData.GetItem(0, 8);		//주문상태구분코드
CString strodrv_odno = realCommRecvData.GetItem(0, 9);		//해외파생주문번호
CString strodrv_or_odno = realCommRecvData.GetItem(0, 10);		//해외파생원주문번호
CString strordr_dt = realCommRecvData.GetItem(0, 11);		//주문일자
CString strcust_nm = realCommRecvData.GetItem(0, 12);		//고객명
CString strodrv_sell_buy_dcd = realCommRecvData.GetItem(0, 13);		//해외파생매도매수구분코드
CString strodrv_ordr_prc_ctns = realCommRecvData.GetItem(0, 14);		//해외파생주문가격내용
CString strordr_qnt_ctns = realCommRecvData.GetItem(0, 15);		//주문수량내용
CString strodrv_prc_dcd = realCommRecvData.GetItem(0, 16);		//해외파생가격구분코드
CString strcncs_cnd_dcd = realCommRecvData.GetItem(0, 17);		//체결조건구분코드
CString strcnd_prc_ctns = realCommRecvData.GetItem(0, 18);		//조건가격내용
CString strcomm_mdia_dcd = realCommRecvData.GetItem(0, 19);		//통신매체구분코드
CString stracpt_tm = realCommRecvData.GetItem(0, 20);		//접수시각
CString strexcg_cncs_tm = realCommRecvData.GetItem(0, 21);		//거래소체결시각
CString stracpl_acpt_tm = realCommRecvData.GetItem(0, 22);		//현지접수시각
CString strcncs_tm = realCommRecvData.GetItem(0, 23);		//체결시각
CString strcncs_dt = realCommRecvData.GetItem(0, 24);		//체결일자
CString strodrv_cncs_no = realCommRecvData.GetItem(0, 25);		//해외파생체결번호
CString strcncs_qnt_ctns = realCommRecvData.GetItem(0, 26);		//체결수량내용
CString strodrv_cncs_prc_ctns = realCommRecvData.GetItem(0, 27);		//해외파생체결가격내용
CString strodrv_cncs_amt_ctns = realCommRecvData.GetItem(0, 28);		//해외파생체결금액내용
CString strcrry_cd = realCommRecvData.GetItem(0, 29);		//통화코드
CString strordr_rmn_qnt_ctns = realCommRecvData.GetItem(0, 30);		//주문잔여수량내용
CString stracnt_dcd = realCommRecvData.GetItem(0, 31);		//계좌구분코드
CString strentr_clr_dcd = realCommRecvData.GetItem(0, 32);		//진입청산구분코드
CString strclr_pst_no = realCommRecvData.GetItem(0, 33);		//청산포지션번호
CString strpst_no = realCommRecvData.GetItem(0, 34);		//포지션번호
