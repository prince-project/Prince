BEGIN_FUNCTION_MAP
	REAL_TYPE=217, REAL_NAME=EF4, DESCRIPTION=해외선물미체결;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=rltm_dpch_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=실시간통보구분코드, FID=0;
			 INDEX=1, ITEM=usr_id, TYPE=string, SIZE=20, KEY=1, CAPTION=사용자ID, FID=0;
			 INDEX=2, ITEM=rltm_dpch_prcs_dcd, TYPE=string, SIZE=2, KEY=0, CAPTION=실시간통보처리구분코드, FID=0;
			 INDEX=3, ITEM=cano, TYPE=string, SIZE=8, KEY=0, CAPTION=종합계좌번호, FID=0;
			 INDEX=4, ITEM=ctno, TYPE=string, SIZE=9, KEY=0, CAPTION=종합계좌대체번호, FID=0;
			 INDEX=5, ITEM=apno, TYPE=string, SIZE=3, KEY=0, CAPTION=계좌상품번호, FID=0;
			 INDEX=6, ITEM=odrv_odno, TYPE=string, SIZE=16, KEY=0, CAPTION=해외파생주문번호, FID=0;
			 INDEX=7, ITEM=prdt_cd, TYPE=string, SIZE=32, KEY=0, CAPTION=상품코드, FID=0;
			 INDEX=8, ITEM=odrv_or_odno, TYPE=string, SIZE=16, KEY=0, CAPTION=해외파생원주문번호, FID=0;
			 INDEX=9, ITEM=odrv_mo_odno, TYPE=string, SIZE=16, KEY=0, CAPTION=해외파생모주문번호, FID=0;
			 INDEX=10, ITEM=ordr_grup_no, TYPE=string, SIZE=16, KEY=0, CAPTION=주문그룹번호, FID=0;
			 INDEX=11, ITEM=ordr_dt, TYPE=string, SIZE=8, KEY=0, CAPTION=주문일자, FID=0;
			 INDEX=12, ITEM=cust_nm, TYPE=string, SIZE=50, KEY=0, CAPTION=고객명, FID=0;
			 INDEX=13, ITEM=odrv_sell_buy_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=해외파생매도매수구분코드, FID=0;
			 INDEX=14, ITEM=odrv_ordr_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=해외파생주문가격내용, FID=0;
			 INDEX=15, ITEM=ordr_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=주문수량내용, FID=0;
			 INDEX=16, ITEM=rvse_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=정정수량내용, FID=0;
			 INDEX=17, ITEM=cncl_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=취소수량내용, FID=0;
			 INDEX=18, ITEM=cncs_qnt_smm_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=체결수량합계내용, FID=0;
			 INDEX=19, ITEM=ordr_rmn_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=주문잔여수량내용, FID=0;
			 INDEX=20, ITEM=odrv_prc_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=해외파생가격구분코드, FID=0;
			 INDEX=21, ITEM=cncs_cnd_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=체결조건구분코드, FID=0;
			 INDEX=22, ITEM=cnd_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=조건가격내용, FID=0;
			 INDEX=23, ITEM=avr_cncs_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=평균체결가격내용, FID=0;
			 INDEX=24, ITEM=odrv_pv_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=해외파생현재가내용, FID=0;
			 INDEX=25, ITEM=cncs_rt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=체결율내용, FID=0;
			 INDEX=26, ITEM=comm_mdia_dcd, TYPE=string, SIZE=3, KEY=0, CAPTION=통신매체구분코드, FID=0;
			 INDEX=27, ITEM=odrv_ordr_tp_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=해외파생주문유형구분코드, FID=0;
			 INDEX=28, ITEM=ordr_stts_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=주문상태구분코드, FID=0;
			 INDEX=29, ITEM=fcm_odno, TYPE=string, SIZE=60, KEY=0, CAPTION=FCM주문번호, FID=0;
			 INDEX=30, ITEM=athz_ip_addr, TYPE=string, SIZE=39, KEY=0, CAPTION=공인IP주소, FID=0;
			 INDEX=31, ITEM=acpt_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=접수시각, FID=0;
			 INDEX=32, ITEM=excg_cncs_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=거래소체결시각, FID=0;
			 INDEX=33, ITEM=acpl_acpt_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=현지접수시각, FID=0;
			 INDEX=34, ITEM=cncs_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=체결시각, FID=0;
			 INDEX=35, ITEM=crry_cd, TYPE=string, SIZE=3, KEY=0, CAPTION=통화코드, FID=0;
			 INDEX=36, ITEM=cncs_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=체결수량내용, FID=0;
			 INDEX=37, ITEM=ordr_expr_dt, TYPE=string, SIZE=8, KEY=0, CAPTION=주문만료일자, FID=0;
			 INDEX=38, ITEM=acnt_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=계좌구분코드, FID=0;
			 INDEX=39, ITEM=entr_clr_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=진입청산구분코드, FID=0;
			 INDEX=40, ITEM=clr_pst_no, TYPE=string, SIZE=16, KEY=0, CAPTION=청산포지션번호, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strrltm_dpch_dcd = m_CommAgent.GetRealOutputData("EF4", "rltm_dpch_dcd");		//실시간통보구분코드
CString strusr_id = m_CommAgent.GetRealOutputData("EF4", "usr_id");		//사용자ID
CString strrltm_dpch_prcs_dcd = m_CommAgent.GetRealOutputData("EF4", "rltm_dpch_prcs_dcd");		//실시간통보처리구분코드
CString strcano = m_CommAgent.GetRealOutputData("EF4", "cano");		//종합계좌번호
CString strctno = m_CommAgent.GetRealOutputData("EF4", "ctno");		//종합계좌대체번호
CString strapno = m_CommAgent.GetRealOutputData("EF4", "apno");		//계좌상품번호
CString strodrv_odno = m_CommAgent.GetRealOutputData("EF4", "odrv_odno");		//해외파생주문번호
CString strprdt_cd = m_CommAgent.GetRealOutputData("EF4", "prdt_cd");		//상품코드
CString strodrv_or_odno = m_CommAgent.GetRealOutputData("EF4", "odrv_or_odno");		//해외파생원주문번호
CString strodrv_mo_odno = m_CommAgent.GetRealOutputData("EF4", "odrv_mo_odno");		//해외파생모주문번호
CString strordr_grup_no = m_CommAgent.GetRealOutputData("EF4", "ordr_grup_no");		//주문그룹번호
CString strordr_dt = m_CommAgent.GetRealOutputData("EF4", "ordr_dt");		//주문일자
CString strcust_nm = m_CommAgent.GetRealOutputData("EF4", "cust_nm");		//고객명
CString strodrv_sell_buy_dcd = m_CommAgent.GetRealOutputData("EF4", "odrv_sell_buy_dcd");		//해외파생매도매수구분코드
CString strodrv_ordr_prc_ctns = m_CommAgent.GetRealOutputData("EF4", "odrv_ordr_prc_ctns");		//해외파생주문가격내용
CString strordr_qnt_ctns = m_CommAgent.GetRealOutputData("EF4", "ordr_qnt_ctns");		//주문수량내용
CString strrvse_qnt_ctns = m_CommAgent.GetRealOutputData("EF4", "rvse_qnt_ctns");		//정정수량내용
CString strcncl_qnt_ctns = m_CommAgent.GetRealOutputData("EF4", "cncl_qnt_ctns");		//취소수량내용
CString strcncs_qnt_smm_ctns = m_CommAgent.GetRealOutputData("EF4", "cncs_qnt_smm_ctns");		//체결수량합계내용
CString strordr_rmn_qnt_ctns = m_CommAgent.GetRealOutputData("EF4", "ordr_rmn_qnt_ctns");		//주문잔여수량내용
CString strodrv_prc_dcd = m_CommAgent.GetRealOutputData("EF4", "odrv_prc_dcd");		//해외파생가격구분코드
CString strcncs_cnd_dcd = m_CommAgent.GetRealOutputData("EF4", "cncs_cnd_dcd");		//체결조건구분코드
CString strcnd_prc_ctns = m_CommAgent.GetRealOutputData("EF4", "cnd_prc_ctns");		//조건가격내용
CString stravr_cncs_prc_ctns = m_CommAgent.GetRealOutputData("EF4", "avr_cncs_prc_ctns");		//평균체결가격내용
CString strodrv_pv_ctns = m_CommAgent.GetRealOutputData("EF4", "odrv_pv_ctns");		//해외파생현재가내용
CString strcncs_rt_ctns = m_CommAgent.GetRealOutputData("EF4", "cncs_rt_ctns");		//체결율내용
CString strcomm_mdia_dcd = m_CommAgent.GetRealOutputData("EF4", "comm_mdia_dcd");		//통신매체구분코드
CString strodrv_ordr_tp_dcd = m_CommAgent.GetRealOutputData("EF4", "odrv_ordr_tp_dcd");		//해외파생주문유형구분코드
CString strordr_stts_dcd = m_CommAgent.GetRealOutputData("EF4", "ordr_stts_dcd");		//주문상태구분코드
CString strfcm_odno = m_CommAgent.GetRealOutputData("EF4", "fcm_odno");		//FCM주문번호
CString strathz_ip_addr = m_CommAgent.GetRealOutputData("EF4", "athz_ip_addr");		//공인IP주소
CString stracpt_tm = m_CommAgent.GetRealOutputData("EF4", "acpt_tm");		//접수시각
CString strexcg_cncs_tm = m_CommAgent.GetRealOutputData("EF4", "excg_cncs_tm");		//거래소체결시각
CString stracpl_acpt_tm = m_CommAgent.GetRealOutputData("EF4", "acpl_acpt_tm");		//현지접수시각
CString strcncs_tm = m_CommAgent.GetRealOutputData("EF4", "cncs_tm");		//체결시각
CString strcrry_cd = m_CommAgent.GetRealOutputData("EF4", "crry_cd");		//통화코드
CString strcncs_qnt_ctns = m_CommAgent.GetRealOutputData("EF4", "cncs_qnt_ctns");		//체결수량내용
CString strordr_expr_dt = m_CommAgent.GetRealOutputData("EF4", "ordr_expr_dt");		//주문만료일자
CString stracnt_dcd = m_CommAgent.GetRealOutputData("EF4", "acnt_dcd");		//계좌구분코드
CString strentr_clr_dcd = m_CommAgent.GetRealOutputData("EF4", "entr_clr_dcd");		//진입청산구분코드
CString strclr_pst_no = m_CommAgent.GetRealOutputData("EF4", "clr_pst_no");		//청산포지션번호




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
CString strodrv_odno = realCommRecvData.GetItem(0, 6);		//해외파생주문번호
CString strprdt_cd = realCommRecvData.GetItem(0, 7);		//상품코드
CString strodrv_or_odno = realCommRecvData.GetItem(0, 8);		//해외파생원주문번호
CString strodrv_mo_odno = realCommRecvData.GetItem(0, 9);		//해외파생모주문번호
CString strordr_grup_no = realCommRecvData.GetItem(0, 10);		//주문그룹번호
CString strordr_dt = realCommRecvData.GetItem(0, 11);		//주문일자
CString strcust_nm = realCommRecvData.GetItem(0, 12);		//고객명
CString strodrv_sell_buy_dcd = realCommRecvData.GetItem(0, 13);		//해외파생매도매수구분코드
CString strodrv_ordr_prc_ctns = realCommRecvData.GetItem(0, 14);		//해외파생주문가격내용
CString strordr_qnt_ctns = realCommRecvData.GetItem(0, 15);		//주문수량내용
CString strrvse_qnt_ctns = realCommRecvData.GetItem(0, 16);		//정정수량내용
CString strcncl_qnt_ctns = realCommRecvData.GetItem(0, 17);		//취소수량내용
CString strcncs_qnt_smm_ctns = realCommRecvData.GetItem(0, 18);		//체결수량합계내용
CString strordr_rmn_qnt_ctns = realCommRecvData.GetItem(0, 19);		//주문잔여수량내용
CString strodrv_prc_dcd = realCommRecvData.GetItem(0, 20);		//해외파생가격구분코드
CString strcncs_cnd_dcd = realCommRecvData.GetItem(0, 21);		//체결조건구분코드
CString strcnd_prc_ctns = realCommRecvData.GetItem(0, 22);		//조건가격내용
CString stravr_cncs_prc_ctns = realCommRecvData.GetItem(0, 23);		//평균체결가격내용
CString strodrv_pv_ctns = realCommRecvData.GetItem(0, 24);		//해외파생현재가내용
CString strcncs_rt_ctns = realCommRecvData.GetItem(0, 25);		//체결율내용
CString strcomm_mdia_dcd = realCommRecvData.GetItem(0, 26);		//통신매체구분코드
CString strodrv_ordr_tp_dcd = realCommRecvData.GetItem(0, 27);		//해외파생주문유형구분코드
CString strordr_stts_dcd = realCommRecvData.GetItem(0, 28);		//주문상태구분코드
CString strfcm_odno = realCommRecvData.GetItem(0, 29);		//FCM주문번호
CString strathz_ip_addr = realCommRecvData.GetItem(0, 30);		//공인IP주소
CString stracpt_tm = realCommRecvData.GetItem(0, 31);		//접수시각
CString strexcg_cncs_tm = realCommRecvData.GetItem(0, 32);		//거래소체결시각
CString stracpl_acpt_tm = realCommRecvData.GetItem(0, 33);		//현지접수시각
CString strcncs_tm = realCommRecvData.GetItem(0, 34);		//체결시각
CString strcrry_cd = realCommRecvData.GetItem(0, 35);		//통화코드
CString strcncs_qnt_ctns = realCommRecvData.GetItem(0, 36);		//체결수량내용
CString strordr_expr_dt = realCommRecvData.GetItem(0, 37);		//주문만료일자
CString stracnt_dcd = realCommRecvData.GetItem(0, 38);		//계좌구분코드
CString strentr_clr_dcd = realCommRecvData.GetItem(0, 39);		//진입청산구분코드
CString strclr_pst_no = realCommRecvData.GetItem(0, 40);		//청산포지션번호
