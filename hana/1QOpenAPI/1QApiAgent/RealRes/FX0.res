BEGIN_FUNCTION_MAP
	REAL_TYPE=218, REAL_NAME=FX0, DESCRIPTION=FX마진주문확인 및 체결통보;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=rltm_dpch_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=실시간통보구분코드, FID=0;
			 INDEX=1, ITEM=usr_id, TYPE=string, SIZE=20, KEY=1, CAPTION=사용자ID, FID=0;
			 INDEX=2, ITEM=rltm_dpch_prcs_dcd, TYPE=string, SIZE=2, KEY=0, CAPTION=실시간통보처리구분코드, FID=0;
			 INDEX=3, ITEM=cano, TYPE=string, SIZE=8, KEY=0, CAPTION=종합계좌번호, FID=0;
			 INDEX=4, ITEM=fdm_unq_no, TYPE=string, SIZE=3, KEY=0, CAPTION=딜링하우스고유번호, FID=0;
			 INDEX=5, ITEM=prdt_cd, TYPE=string, SIZE=32, KEY=0, CAPTION=상품코드, FID=0;
			 INDEX=6, ITEM=odrv_ordr_tp_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=해외파생주문유형구분코드, FID=0;
			 INDEX=7, ITEM=ordr_stts_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=주문상태구분코드, FID=0;
			 INDEX=8, ITEM=odrv_odno, TYPE=string, SIZE=16, KEY=0, CAPTION=해외파생주문번호, FID=0;
			 INDEX=9, ITEM=odrv_or_odno, TYPE=string, SIZE=16, KEY=0, CAPTION=해외파생원주문번호, FID=0;
			 INDEX=10, ITEM=ordr_dt, TYPE=string, SIZE=8, KEY=0, CAPTION=주문일자, FID=0;
			 INDEX=11, ITEM=apno, TYPE=string, SIZE=3, KEY=0, CAPTION=계좌상품번호, FID=0;
			 INDEX=12, ITEM=cust_nm, TYPE=string, SIZE=50, KEY=0, CAPTION=고객명, FID=0;
			 INDEX=13, ITEM=odrv_sell_buy_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=해외파생매도매수구분코드, FID=0;
			 INDEX=14, ITEM=odrv_ordr_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=해외파생주문가격내용, FID=0;
			 INDEX=15, ITEM=ordr_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=주문수량내용, FID=0;
			 INDEX=16, ITEM=odrv_prc_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=해외파생가격구분코드, FID=0;
			 INDEX=17, ITEM=cncs_cnd_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=체결조건구분코드, FID=0;
			 INDEX=18, ITEM=odrv_ctrt_un_amt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=해외파생계약단위금액내용, FID=0;
			 INDEX=19, ITEM=fx_ordr_tot_amt_ctns, TYPE=string, SIZE=30, KEY=0, CAPTION=FX주문총금액내용, FID=0;
			 INDEX=20, ITEM=comm_mdia_dcd, TYPE=string, SIZE=3, KEY=0, CAPTION=통신매체구분코드, FID=0;
			 INDEX=21, ITEM=excg_acpt_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=거래소접수시각, FID=0;
			 INDEX=22, ITEM=excg_cncs_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=거래소체결시각, FID=0;
			 INDEX=23, ITEM=ordr_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=주문시각, FID=0;
			 INDEX=24, ITEM=cncs_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=체결시각, FID=0;
			 INDEX=25, ITEM=cncs_dt, TYPE=string, SIZE=8, KEY=0, CAPTION=체결일자, FID=0;
			 INDEX=26, ITEM=odrv_cncs_no, TYPE=string, SIZE=8, KEY=0, CAPTION=해외파생체결번호, FID=0;
			 INDEX=27, ITEM=cncs_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=체결수량내용, FID=0;
			 INDEX=28, ITEM=odrv_cncs_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=해외파생체결가격내용, FID=0;
			 INDEX=29, ITEM=odrv_cncs_amt_ctns, TYPE=string, SIZE=30, KEY=0, CAPTION=해외파생체결금액내용, FID=0;
			 INDEX=30, ITEM=trsl_odrv_cncs_amt_char, TYPE=string, SIZE=30, KEY=0, CAPTION=환산해외파생체결금액문자, FID=0;
			 INDEX=31, ITEM=crry_cd, TYPE=string, SIZE=3, KEY=0, CAPTION=통화코드, FID=0;
			 INDEX=32, ITEM=sq1_stls_yn, TYPE=string, SIZE=1, KEY=0, CAPTION=1차스탑로스여부, FID=0;
			 INDEX=33, ITEM=sq1_apmpr_yn, TYPE=string, SIZE=1, KEY=0, CAPTION=1차지정가여부, FID=0;
			 INDEX=34, ITEM=sq1_stls_prc_char, TYPE=string, SIZE=20, KEY=0, CAPTION=1차스탑로스가격문자, FID=0;
			 INDEX=35, ITEM=sq1_appn_prc_char, TYPE=string, SIZE=20, KEY=0, CAPTION=1차지정가격문자, FID=0;
			 INDEX=36, ITEM=sq1_chas_stls_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=1차추적손절매가격내용, FID=0;
			 INDEX=37, ITEM=sq2_stls_yn, TYPE=string, SIZE=1, KEY=0, CAPTION=2차스탑로스여부, FID=0;
			 INDEX=38, ITEM=sq2_apmpr_yn, TYPE=string, SIZE=1, KEY=0, CAPTION=2차지정가여부, FID=0;
			 INDEX=39, ITEM=sq2_stls_prc_char, TYPE=string, SIZE=20, KEY=0, CAPTION=2차스탑로스가격문자, FID=0;
			 INDEX=40, ITEM=sq2_appn_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=2차지정가격내용, FID=0;
			 INDEX=41, ITEM=sq2_chas_stls_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=2차추적손절매가격내용, FID=0;
			 INDEX=42, ITEM=trde_prc_dfrn_ctns, TYPE=string, SIZE=50, KEY=0, CAPTION=매매가격차이내용, FID=0;
			 INDEX=43, ITEM=ctno, TYPE=string, SIZE=9, KEY=0, CAPTION=종합계좌대체번호, FID=0;
			 INDEX=44, ITEM=filler_100, TYPE=string, SIZE=100, KEY=0, CAPTION=필러_100, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strrltm_dpch_dcd = m_CommAgent.GetRealOutputData("FX0", "rltm_dpch_dcd");		//실시간통보구분코드
CString strusr_id = m_CommAgent.GetRealOutputData("FX0", "usr_id");		//사용자ID
CString strrltm_dpch_prcs_dcd = m_CommAgent.GetRealOutputData("FX0", "rltm_dpch_prcs_dcd");		//실시간통보처리구분코드
CString strcano = m_CommAgent.GetRealOutputData("FX0", "cano");		//종합계좌번호
CString strfdm_unq_no = m_CommAgent.GetRealOutputData("FX0", "fdm_unq_no");		//딜링하우스고유번호
CString strprdt_cd = m_CommAgent.GetRealOutputData("FX0", "prdt_cd");		//상품코드
CString strodrv_ordr_tp_dcd = m_CommAgent.GetRealOutputData("FX0", "odrv_ordr_tp_dcd");		//해외파생주문유형구분코드
CString strordr_stts_dcd = m_CommAgent.GetRealOutputData("FX0", "ordr_stts_dcd");		//주문상태구분코드
CString strodrv_odno = m_CommAgent.GetRealOutputData("FX0", "odrv_odno");		//해외파생주문번호
CString strodrv_or_odno = m_CommAgent.GetRealOutputData("FX0", "odrv_or_odno");		//해외파생원주문번호
CString strordr_dt = m_CommAgent.GetRealOutputData("FX0", "ordr_dt");		//주문일자
CString strapno = m_CommAgent.GetRealOutputData("FX0", "apno");		//계좌상품번호
CString strcust_nm = m_CommAgent.GetRealOutputData("FX0", "cust_nm");		//고객명
CString strodrv_sell_buy_dcd = m_CommAgent.GetRealOutputData("FX0", "odrv_sell_buy_dcd");		//해외파생매도매수구분코드
CString strodrv_ordr_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "odrv_ordr_prc_ctns");		//해외파생주문가격내용
CString strordr_qnt_ctns = m_CommAgent.GetRealOutputData("FX0", "ordr_qnt_ctns");		//주문수량내용
CString strodrv_prc_dcd = m_CommAgent.GetRealOutputData("FX0", "odrv_prc_dcd");		//해외파생가격구분코드
CString strcncs_cnd_dcd = m_CommAgent.GetRealOutputData("FX0", "cncs_cnd_dcd");		//체결조건구분코드
CString strodrv_ctrt_un_amt_ctns = m_CommAgent.GetRealOutputData("FX0", "odrv_ctrt_un_amt_ctns");		//해외파생계약단위금액내용
CString strfx_ordr_tot_amt_ctns = m_CommAgent.GetRealOutputData("FX0", "fx_ordr_tot_amt_ctns");		//FX주문총금액내용
CString strcomm_mdia_dcd = m_CommAgent.GetRealOutputData("FX0", "comm_mdia_dcd");		//통신매체구분코드
CString strexcg_acpt_tm = m_CommAgent.GetRealOutputData("FX0", "excg_acpt_tm");		//거래소접수시각
CString strexcg_cncs_tm = m_CommAgent.GetRealOutputData("FX0", "excg_cncs_tm");		//거래소체결시각
CString strordr_tm = m_CommAgent.GetRealOutputData("FX0", "ordr_tm");		//주문시각
CString strcncs_tm = m_CommAgent.GetRealOutputData("FX0", "cncs_tm");		//체결시각
CString strcncs_dt = m_CommAgent.GetRealOutputData("FX0", "cncs_dt");		//체결일자
CString strodrv_cncs_no = m_CommAgent.GetRealOutputData("FX0", "odrv_cncs_no");		//해외파생체결번호
CString strcncs_qnt_ctns = m_CommAgent.GetRealOutputData("FX0", "cncs_qnt_ctns");		//체결수량내용
CString strodrv_cncs_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "odrv_cncs_prc_ctns");		//해외파생체결가격내용
CString strodrv_cncs_amt_ctns = m_CommAgent.GetRealOutputData("FX0", "odrv_cncs_amt_ctns");		//해외파생체결금액내용
CString strtrsl_odrv_cncs_amt_char = m_CommAgent.GetRealOutputData("FX0", "trsl_odrv_cncs_amt_char");		//환산해외파생체결금액문자
CString strcrry_cd = m_CommAgent.GetRealOutputData("FX0", "crry_cd");		//통화코드
CString strsq1_stls_yn = m_CommAgent.GetRealOutputData("FX0", "sq1_stls_yn");		//1차스탑로스여부
CString strsq1_apmpr_yn = m_CommAgent.GetRealOutputData("FX0", "sq1_apmpr_yn");		//1차지정가여부
CString strsq1_stls_prc_char = m_CommAgent.GetRealOutputData("FX0", "sq1_stls_prc_char");		//1차스탑로스가격문자
CString strsq1_appn_prc_char = m_CommAgent.GetRealOutputData("FX0", "sq1_appn_prc_char");		//1차지정가격문자
CString strsq1_chas_stls_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "sq1_chas_stls_prc_ctns");		//1차추적손절매가격내용
CString strsq2_stls_yn = m_CommAgent.GetRealOutputData("FX0", "sq2_stls_yn");		//2차스탑로스여부
CString strsq2_apmpr_yn = m_CommAgent.GetRealOutputData("FX0", "sq2_apmpr_yn");		//2차지정가여부
CString strsq2_stls_prc_char = m_CommAgent.GetRealOutputData("FX0", "sq2_stls_prc_char");		//2차스탑로스가격문자
CString strsq2_appn_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "sq2_appn_prc_ctns");		//2차지정가격내용
CString strsq2_chas_stls_prc_ctns = m_CommAgent.GetRealOutputData("FX0", "sq2_chas_stls_prc_ctns");		//2차추적손절매가격내용
CString strtrde_prc_dfrn_ctns = m_CommAgent.GetRealOutputData("FX0", "trde_prc_dfrn_ctns");		//매매가격차이내용
CString strctno = m_CommAgent.GetRealOutputData("FX0", "ctno");		//종합계좌대체번호
CString strfiller_100 = m_CommAgent.GetRealOutputData("FX0", "filler_100");		//필러_100




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strrltm_dpch_dcd = realCommRecvData.GetItem(0, 0);		//실시간통보구분코드
CString strusr_id = realCommRecvData.GetItem(0, 1);		//사용자ID
CString strrltm_dpch_prcs_dcd = realCommRecvData.GetItem(0, 2);		//실시간통보처리구분코드
CString strcano = realCommRecvData.GetItem(0, 3);		//종합계좌번호
CString strfdm_unq_no = realCommRecvData.GetItem(0, 4);		//딜링하우스고유번호
CString strprdt_cd = realCommRecvData.GetItem(0, 5);		//상품코드
CString strodrv_ordr_tp_dcd = realCommRecvData.GetItem(0, 6);		//해외파생주문유형구분코드
CString strordr_stts_dcd = realCommRecvData.GetItem(0, 7);		//주문상태구분코드
CString strodrv_odno = realCommRecvData.GetItem(0, 8);		//해외파생주문번호
CString strodrv_or_odno = realCommRecvData.GetItem(0, 9);		//해외파생원주문번호
CString strordr_dt = realCommRecvData.GetItem(0, 10);		//주문일자
CString strapno = realCommRecvData.GetItem(0, 11);		//계좌상품번호
CString strcust_nm = realCommRecvData.GetItem(0, 12);		//고객명
CString strodrv_sell_buy_dcd = realCommRecvData.GetItem(0, 13);		//해외파생매도매수구분코드
CString strodrv_ordr_prc_ctns = realCommRecvData.GetItem(0, 14);		//해외파생주문가격내용
CString strordr_qnt_ctns = realCommRecvData.GetItem(0, 15);		//주문수량내용
CString strodrv_prc_dcd = realCommRecvData.GetItem(0, 16);		//해외파생가격구분코드
CString strcncs_cnd_dcd = realCommRecvData.GetItem(0, 17);		//체결조건구분코드
CString strodrv_ctrt_un_amt_ctns = realCommRecvData.GetItem(0, 18);		//해외파생계약단위금액내용
CString strfx_ordr_tot_amt_ctns = realCommRecvData.GetItem(0, 19);		//FX주문총금액내용
CString strcomm_mdia_dcd = realCommRecvData.GetItem(0, 20);		//통신매체구분코드
CString strexcg_acpt_tm = realCommRecvData.GetItem(0, 21);		//거래소접수시각
CString strexcg_cncs_tm = realCommRecvData.GetItem(0, 22);		//거래소체결시각
CString strordr_tm = realCommRecvData.GetItem(0, 23);		//주문시각
CString strcncs_tm = realCommRecvData.GetItem(0, 24);		//체결시각
CString strcncs_dt = realCommRecvData.GetItem(0, 25);		//체결일자
CString strodrv_cncs_no = realCommRecvData.GetItem(0, 26);		//해외파생체결번호
CString strcncs_qnt_ctns = realCommRecvData.GetItem(0, 27);		//체결수량내용
CString strodrv_cncs_prc_ctns = realCommRecvData.GetItem(0, 28);		//해외파생체결가격내용
CString strodrv_cncs_amt_ctns = realCommRecvData.GetItem(0, 29);		//해외파생체결금액내용
CString strtrsl_odrv_cncs_amt_char = realCommRecvData.GetItem(0, 30);		//환산해외파생체결금액문자
CString strcrry_cd = realCommRecvData.GetItem(0, 31);		//통화코드
CString strsq1_stls_yn = realCommRecvData.GetItem(0, 32);		//1차스탑로스여부
CString strsq1_apmpr_yn = realCommRecvData.GetItem(0, 33);		//1차지정가여부
CString strsq1_stls_prc_char = realCommRecvData.GetItem(0, 34);		//1차스탑로스가격문자
CString strsq1_appn_prc_char = realCommRecvData.GetItem(0, 35);		//1차지정가격문자
CString strsq1_chas_stls_prc_ctns = realCommRecvData.GetItem(0, 36);		//1차추적손절매가격내용
CString strsq2_stls_yn = realCommRecvData.GetItem(0, 37);		//2차스탑로스여부
CString strsq2_apmpr_yn = realCommRecvData.GetItem(0, 38);		//2차지정가여부
CString strsq2_stls_prc_char = realCommRecvData.GetItem(0, 39);		//2차스탑로스가격문자
CString strsq2_appn_prc_ctns = realCommRecvData.GetItem(0, 40);		//2차지정가격내용
CString strsq2_chas_stls_prc_ctns = realCommRecvData.GetItem(0, 41);		//2차추적손절매가격내용
CString strtrde_prc_dfrn_ctns = realCommRecvData.GetItem(0, 42);		//매매가격차이내용
CString strctno = realCommRecvData.GetItem(0, 43);		//종합계좌대체번호
CString strfiller_100 = realCommRecvData.GetItem(0, 44);		//필러_100
