BEGIN_FUNCTION_MAP
	REAL_TYPE=21, REAL_NAME=S01, DESCRIPTION=주식호가;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SHRN_ISCD, TYPE=string, SIZE=9, KEY=1, CAPTION=종목코드, FID=0;
			 INDEX=1, ITEM=BSOP_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=호가시간, FID=0;
			 INDEX=2, ITEM=HOUR_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=시간구분, FID=0;
			 INDEX=3, ITEM=ASKP1, TYPE=string, SIZE=12, KEY=0, CAPTION=1매도호가, FID=29;
			 INDEX=4, ITEM=ASKP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP1]색참조(+상승, -하락), FID=0;
			 INDEX=5, ITEM=ASKP2, TYPE=string, SIZE=12, KEY=0, CAPTION=2매도호가, FID=30;
			 INDEX=6, ITEM=ASKP2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP2]색참조(+상승, -하락), FID=0;
			 INDEX=7, ITEM=ASKP3, TYPE=string, SIZE=12, KEY=0, CAPTION=3매도호가, FID=31;
			 INDEX=8, ITEM=ASKP3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP3]색참조(+상승, -하락), FID=0;
			 INDEX=9, ITEM=ASKP4, TYPE=string, SIZE=12, KEY=0, CAPTION=4매도호가, FID=32;
			 INDEX=10, ITEM=ASKP4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP4]색참조(+상승, -하락), FID=0;
			 INDEX=11, ITEM=ASKP5, TYPE=string, SIZE=12, KEY=0, CAPTION=5매도호가, FID=33;
			 INDEX=12, ITEM=ASKP5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP5]색참조(+상승, -하락), FID=0;
			 INDEX=13, ITEM=ASKP6, TYPE=string, SIZE=12, KEY=0, CAPTION=6매도호가, FID=34;
			 INDEX=14, ITEM=ASKP6_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP6]색참조(+상승, -하락), FID=0;
			 INDEX=15, ITEM=ASKP7, TYPE=string, SIZE=12, KEY=0, CAPTION=7매도호가, FID=35;
			 INDEX=16, ITEM=ASKP7_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP7]색참조(+상승, -하락), FID=0;
			 INDEX=17, ITEM=ASKP8, TYPE=string, SIZE=12, KEY=0, CAPTION=8매도호가, FID=36;
			 INDEX=18, ITEM=ASKP8_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP8]색참조(+상승, -하락), FID=0;
			 INDEX=19, ITEM=ASKP9, TYPE=string, SIZE=12, KEY=0, CAPTION=9매도호가, FID=37;
			 INDEX=20, ITEM=ASKP9_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP9]색참조(+상승, -하락), FID=0;
			 INDEX=21, ITEM=ASKP10, TYPE=string, SIZE=12, KEY=0, CAPTION=10매도호가, FID=38;
			 INDEX=22, ITEM=ASKP10_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP10]색참조(+상승, -하락), FID=0;
			 INDEX=23, ITEM=BIDP1, TYPE=string, SIZE=12, KEY=0, CAPTION=1매수호가, FID=39;
			 INDEX=24, ITEM=BIDP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP1]색참조(+상승, -하락), FID=0;
			 INDEX=25, ITEM=BIDP2, TYPE=string, SIZE=12, KEY=0, CAPTION=2매수호가, FID=40;
			 INDEX=26, ITEM=BIDP2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP2]색참조(+상승, -하락), FID=0;
			 INDEX=27, ITEM=BIDP3, TYPE=string, SIZE=12, KEY=0, CAPTION=3매수호가, FID=41;
			 INDEX=28, ITEM=BIDP3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP3]색참조(+상승, -하락), FID=0;
			 INDEX=29, ITEM=BIDP4, TYPE=string, SIZE=12, KEY=0, CAPTION=4매수호가, FID=42;
			 INDEX=30, ITEM=BIDP4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP4]색참조(+상승, -하락), FID=0;
			 INDEX=31, ITEM=BIDP5, TYPE=string, SIZE=12, KEY=0, CAPTION=5매수호가, FID=43;
			 INDEX=32, ITEM=BIDP5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP5]색참조(+상승, -하락), FID=0;
			 INDEX=33, ITEM=BIDP6, TYPE=string, SIZE=12, KEY=0, CAPTION=6매수호가, FID=44;
			 INDEX=34, ITEM=BIDP6_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP6]색참조(+상승, -하락), FID=0;
			 INDEX=35, ITEM=BIDP7, TYPE=string, SIZE=12, KEY=0, CAPTION=7매수호가, FID=45;
			 INDEX=36, ITEM=BIDP7_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP7]색참조(+상승, -하락), FID=0;
			 INDEX=37, ITEM=BIDP8, TYPE=string, SIZE=12, KEY=0, CAPTION=8매수호가, FID=46;
			 INDEX=38, ITEM=BIDP8_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP8]색참조(+상승, -하락), FID=0;
			 INDEX=39, ITEM=BIDP9, TYPE=string, SIZE=12, KEY=0, CAPTION=9매수호가, FID=47;
			 INDEX=40, ITEM=BIDP9_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP9]색참조(+상승, -하락), FID=0;
			 INDEX=41, ITEM=BIDP10, TYPE=string, SIZE=12, KEY=0, CAPTION=10매수호가, FID=48;
			 INDEX=42, ITEM=BIDP10_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP10]색참조(+상승, -하락), FID=0;
			 INDEX=43, ITEM=ASKP_RSQN1, TYPE=string, SIZE=18, KEY=0, CAPTION=1매도호가잔량, FID=63;
			 INDEX=44, ITEM=ASKP_RSQN2, TYPE=string, SIZE=18, KEY=0, CAPTION=2매도호가잔량, FID=64;
			 INDEX=45, ITEM=ASKP_RSQN3, TYPE=string, SIZE=18, KEY=0, CAPTION=3매도호가잔량, FID=65;
			 INDEX=46, ITEM=ASKP_RSQN4, TYPE=string, SIZE=18, KEY=0, CAPTION=4매도호가잔량, FID=66;
			 INDEX=47, ITEM=ASKP_RSQN5, TYPE=string, SIZE=18, KEY=0, CAPTION=5매도호가잔량, FID=67;
			 INDEX=48, ITEM=ASKP_RSQN6, TYPE=string, SIZE=18, KEY=0, CAPTION=6매도호가잔량, FID=68;
			 INDEX=49, ITEM=ASKP_RSQN7, TYPE=string, SIZE=18, KEY=0, CAPTION=7매도호가잔량, FID=69;
			 INDEX=50, ITEM=ASKP_RSQN8, TYPE=string, SIZE=18, KEY=0, CAPTION=8매도호가잔량, FID=70;
			 INDEX=51, ITEM=ASKP_RSQN9, TYPE=string, SIZE=18, KEY=0, CAPTION=9매도호가잔량, FID=71;
			 INDEX=52, ITEM=ASKP_RSQN10, TYPE=string, SIZE=18, KEY=0, CAPTION=10매도호가잔량, FID=72;
			 INDEX=53, ITEM=BIDP_RSQN1, TYPE=string, SIZE=18, KEY=0, CAPTION=1매수호가잔량, FID=73;
			 INDEX=54, ITEM=BIDP_RSQN2, TYPE=string, SIZE=18, KEY=0, CAPTION=2매수호가잔량, FID=74;
			 INDEX=55, ITEM=BIDP_RSQN3, TYPE=string, SIZE=18, KEY=0, CAPTION=3매수호가잔량, FID=75;
			 INDEX=56, ITEM=BIDP_RSQN4, TYPE=string, SIZE=18, KEY=0, CAPTION=4매수호가잔량, FID=76;
			 INDEX=57, ITEM=BIDP_RSQN5, TYPE=string, SIZE=18, KEY=0, CAPTION=5매수호가잔량, FID=77;
			 INDEX=58, ITEM=BIDP_RSQN6, TYPE=string, SIZE=18, KEY=0, CAPTION=6매수호가잔량, FID=78;
			 INDEX=59, ITEM=BIDP_RSQN7, TYPE=string, SIZE=18, KEY=0, CAPTION=7매수호가잔량, FID=79;
			 INDEX=60, ITEM=BIDP_RSQN8, TYPE=string, SIZE=18, KEY=0, CAPTION=8매수호가잔량, FID=80;
			 INDEX=61, ITEM=BIDP_RSQN9, TYPE=string, SIZE=18, KEY=0, CAPTION=9매수호가잔량, FID=81;
			 INDEX=62, ITEM=BIDP_RSQN10, TYPE=string, SIZE=18, KEY=0, CAPTION=10매수호가잔량, FID=82;
			 INDEX=63, ITEM=ASKP_RSQN_ICDC1, TYPE=string, SIZE=12, KEY=0, CAPTION=1매도호가잔량증감, FID=151;
			 INDEX=64, ITEM=ASKP_RSQN_ICDC1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP_RSQN_ICDC1]색참조(+상승, -하락), FID=0;
			 INDEX=65, ITEM=ASKP_RSQN_ICDC2, TYPE=string, SIZE=12, KEY=0, CAPTION=2매도호가잔량증감, FID=152;
			 INDEX=66, ITEM=ASKP_RSQN_ICDC2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP_RSQN_ICDC2]색참조(+상승, -하락), FID=0;
			 INDEX=67, ITEM=ASKP_RSQN_ICDC3, TYPE=string, SIZE=12, KEY=0, CAPTION=3매도호가잔량증감, FID=153;
			 INDEX=68, ITEM=ASKP_RSQN_ICDC3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP_RSQN_ICDC3]색참조(+상승, -하락), FID=0;
			 INDEX=69, ITEM=ASKP_RSQN_ICDC4, TYPE=string, SIZE=12, KEY=0, CAPTION=4매도호가잔량증감, FID=154;
			 INDEX=70, ITEM=ASKP_RSQN_ICDC4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP_RSQN_ICDC4]색참조(+상승, -하락), FID=0;
			 INDEX=71, ITEM=ASKP_RSQN_ICDC5, TYPE=string, SIZE=12, KEY=0, CAPTION=5매도호가잔량증감, FID=155;
			 INDEX=72, ITEM=ASKP_RSQN_ICDC5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP_RSQN_ICDC5]색참조(+상승, -하락), FID=0;
			 INDEX=73, ITEM=ASKP_RSQN_ICDC6, TYPE=string, SIZE=12, KEY=0, CAPTION=6매도호가잔량증감, FID=156;
			 INDEX=74, ITEM=ASKP_RSQN_ICDC6_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP_RSQN_ICDC6]색참조(+상승, -하락), FID=0;
			 INDEX=75, ITEM=ASKP_RSQN_ICDC7, TYPE=string, SIZE=12, KEY=0, CAPTION=7매도호가잔량증감, FID=157;
			 INDEX=76, ITEM=ASKP_RSQN_ICDC7_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP_RSQN_ICDC7]색참조(+상승, -하락), FID=0;
			 INDEX=77, ITEM=ASKP_RSQN_ICDC8, TYPE=string, SIZE=12, KEY=0, CAPTION=8매도호가잔량증감, FID=158;
			 INDEX=78, ITEM=ASKP_RSQN_ICDC8_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP_RSQN_ICDC8]색참조(+상승, -하락), FID=0;
			 INDEX=79, ITEM=ASKP_RSQN_ICDC9, TYPE=string, SIZE=12, KEY=0, CAPTION=9매도호가잔량증감, FID=159;
			 INDEX=80, ITEM=ASKP_RSQN_ICDC9_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP_RSQN_ICDC9]색참조(+상승, -하락), FID=0;
			 INDEX=81, ITEM=ASKP_RSQN_ICDC10, TYPE=string, SIZE=12, KEY=0, CAPTION=10매도호가잔량증감, FID=160;
			 INDEX=82, ITEM=ASKP_RSQN_ICDC10_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP_RSQN_ICDC10]색참조(+상승, -하락), FID=0;
			 INDEX=83, ITEM=BIDP_RSQN_ICDC1, TYPE=string, SIZE=12, KEY=0, CAPTION=1매수호가 잔량 증감, FID=161;
			 INDEX=84, ITEM=BIDP_RSQN_ICDC1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP_RSQN_ICDC1]색참조(+상승, -하락), FID=0;
			 INDEX=85, ITEM=BIDP_RSQN_ICDC2, TYPE=string, SIZE=12, KEY=0, CAPTION=2매수호가 잔량 증감, FID=162;
			 INDEX=86, ITEM=BIDP_RSQN_ICDC2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP_RSQN_ICDC2]색참조(+상승, -하락), FID=0;
			 INDEX=87, ITEM=BIDP_RSQN_ICDC3, TYPE=string, SIZE=12, KEY=0, CAPTION=3매수호가 잔량 증감, FID=163;
			 INDEX=88, ITEM=BIDP_RSQN_ICDC3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP_RSQN_ICDC3]색참조(+상승, -하락), FID=0;
			 INDEX=89, ITEM=BIDP_RSQN_ICDC4, TYPE=string, SIZE=12, KEY=0, CAPTION=4매수호가 잔량 증감, FID=164;
			 INDEX=90, ITEM=BIDP_RSQN_ICDC4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP_RSQN_ICDC4]색참조(+상승, -하락), FID=0;
			 INDEX=91, ITEM=BIDP_RSQN_ICDC5, TYPE=string, SIZE=12, KEY=0, CAPTION=5매수호가 잔량 증감, FID=165;
			 INDEX=92, ITEM=BIDP_RSQN_ICDC5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP_RSQN_ICDC5]색참조(+상승, -하락), FID=0;
			 INDEX=93, ITEM=BIDP_RSQN_ICDC6, TYPE=string, SIZE=12, KEY=0, CAPTION=6매수호가 잔량 증감, FID=166;
			 INDEX=94, ITEM=BIDP_RSQN_ICDC6_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP_RSQN_ICDC6]색참조(+상승, -하락), FID=0;
			 INDEX=95, ITEM=BIDP_RSQN_ICDC7, TYPE=string, SIZE=12, KEY=0, CAPTION=7매수호가 잔량 증감, FID=167;
			 INDEX=96, ITEM=BIDP_RSQN_ICDC7_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP_RSQN_ICDC7]색참조(+상승, -하락), FID=0;
			 INDEX=97, ITEM=BIDP_RSQN_ICDC8, TYPE=string, SIZE=12, KEY=0, CAPTION=8매수호가 잔량 증감, FID=168;
			 INDEX=98, ITEM=BIDP_RSQN_ICDC8_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP_RSQN_ICDC8]색참조(+상승, -하락), FID=0;
			 INDEX=99, ITEM=BIDP_RSQN_ICDC9, TYPE=string, SIZE=12, KEY=0, CAPTION=9매수호가 잔량 증감, FID=169;
			 INDEX=100, ITEM=BIDP_RSQN_ICDC9_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP_RSQN_ICDC9]색참조(+상승, -하락), FID=0;
			 INDEX=101, ITEM=BIDP_RSQN_ICDC10, TYPE=string, SIZE=12, KEY=0, CAPTION=10매수호가 잔량 증감, FID=170;
			 INDEX=102, ITEM=BIDP_RSQN_ICDC10_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP_RSQN_ICDC10]색참조(+상승, -하락), FID=0;
			 INDEX=103, ITEM=TOTAL_ASKP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=총매도호가잔량, FID=171;
			 INDEX=104, ITEM=TOTAL_BIDP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=총매수호가잔량, FID=172;
			 INDEX=105, ITEM=TOTAL_ASKP_RSQN_ICDC, TYPE=string, SIZE=12, KEY=0, CAPTION=총매도호가잔량증감, FID=278;
			 INDEX=106, ITEM=TOTAL_ASKP_RSQN_ICDC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[TOTAL_ASKP_RSQN_ICDC]색참조(+상승, -하락), FID=0;
			 INDEX=107, ITEM=TOTAL_BIDP_RSQN_ICDC, TYPE=string, SIZE=12, KEY=0, CAPTION=총매수호가잔량증감, FID=279;
			 INDEX=108, ITEM=TOTAL_BIDP_RSQN_ICDC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[TOTAL_BIDP_RSQN_ICDC]색참조(+상승, -하락), FID=0;
			 INDEX=109, ITEM=OVTM_TOTAL_ASKP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=시간외총매도호가잔량, FID=797;
			 INDEX=110, ITEM=OVTM_TOTAL_BIDP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=시간외총매수호가잔량, FID=798;
			 INDEX=111, ITEM=ANTC_CNPR, TYPE=string, SIZE=12, KEY=0, CAPTION=예상체결가, FID=185;
			 INDEX=112, ITEM=ANTC_CNPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ANTC_CNPR]색참조(+상승, -하락), FID=0;
			 INDEX=113, ITEM=ANTC_CNQN, TYPE=string, SIZE=18, KEY=0, CAPTION=예상체결량, FID=189;
			 INDEX=114, ITEM=ACML_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=누적거래량, FID=11;
			 INDEX=115, ITEM=COMP_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=경쟁대량 방향구분, FID=0;
			 INDEX=116, ITEM=CNCC_ASPR_CLS_CODE, TYPE=string, SIZE=2, KEY=0, CAPTION=동시호가구분코드, FID=0;
			 INDEX=117, ITEM=LP_ASKP_RSQN1, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매도호가 잔량1, FID=0;
			 INDEX=118, ITEM=LP_ASKP_RSQN2, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매도호가 잔량2, FID=0;
			 INDEX=119, ITEM=LP_ASKP_RSQN3, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매도호가 잔량3, FID=0;
			 INDEX=120, ITEM=LP_ASKP_RSQN4, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매도호가 잔량4, FID=0;
			 INDEX=121, ITEM=LP_ASKP_RSQN5, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매도호가 잔량5, FID=0;
			 INDEX=122, ITEM=LP_ASKP_RSQN6, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매도호가 잔량6, FID=0;
			 INDEX=123, ITEM=LP_ASKP_RSQN7, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매도호가 잔량7, FID=0;
			 INDEX=124, ITEM=LP_ASKP_RSQN8, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매도호가 잔량8, FID=0;
			 INDEX=125, ITEM=LP_ASKP_RSQN9, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매도호가 잔량9, FID=0;
			 INDEX=126, ITEM=LP_ASKP_RSQN10, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매도호가 잔량10, FID=0;
			 INDEX=127, ITEM=LP_BIDP_RSQN1, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매수호가 잔량1, FID=0;
			 INDEX=128, ITEM=LP_BIDP_RSQN2, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매수호가 잔량2, FID=0;
			 INDEX=129, ITEM=LP_BIDP_RSQN3, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매수호가 잔량3, FID=0;
			 INDEX=130, ITEM=LP_BIDP_RSQN4, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매수호가 잔량4, FID=0;
			 INDEX=131, ITEM=LP_BIDP_RSQN5, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매수호가 잔량5, FID=0;
			 INDEX=132, ITEM=LP_BIDP_RSQN6, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매수호가 잔량6, FID=0;
			 INDEX=133, ITEM=LP_BIDP_RSQN7, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매수호가 잔량7, FID=0;
			 INDEX=134, ITEM=LP_BIDP_RSQN8, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매수호가 잔량8, FID=0;
			 INDEX=135, ITEM=LP_BIDP_RSQN9, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매수호가 잔량9, FID=0;
			 INDEX=136, ITEM=LP_BIDP_RSQN10, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 매수호가 잔량10, FID=0;
			 INDEX=137, ITEM=LP_ASKP_RSQN_ICDC1, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매도호가 잔량 증감1, FID=0;
			 INDEX=138, ITEM=LP_ASKP_RSQN_ICDC1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_ASKP_RSQN_ICDC1]색참조(+상승, -하락), FID=0;
			 INDEX=139, ITEM=LP_ASKP_RSQN_ICDC2, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매도호가 잔량 증감2, FID=0;
			 INDEX=140, ITEM=LP_ASKP_RSQN_ICDC2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_ASKP_RSQN_ICDC2]색참조(+상승, -하락), FID=0;
			 INDEX=141, ITEM=LP_ASKP_RSQN_ICDC3, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매도호가 잔량 증감3, FID=0;
			 INDEX=142, ITEM=LP_ASKP_RSQN_ICDC3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_ASKP_RSQN_ICDC3]색참조(+상승, -하락), FID=0;
			 INDEX=143, ITEM=LP_ASKP_RSQN_ICDC4, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매도호가 잔량 증감4, FID=0;
			 INDEX=144, ITEM=LP_ASKP_RSQN_ICDC4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_ASKP_RSQN_ICDC4]색참조(+상승, -하락), FID=0;
			 INDEX=145, ITEM=LP_ASKP_RSQN_ICDC5, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매도호가 잔량 증감5, FID=0;
			 INDEX=146, ITEM=LP_ASKP_RSQN_ICDC5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_ASKP_RSQN_ICDC5]색참조(+상승, -하락), FID=0;
			 INDEX=147, ITEM=LP_ASKP_RSQN_ICDC6, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매도호가 잔량 증감6, FID=0;
			 INDEX=148, ITEM=LP_ASKP_RSQN_ICDC6_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_ASKP_RSQN_ICDC6]색참조(+상승, -하락), FID=0;
			 INDEX=149, ITEM=LP_ASKP_RSQN_ICDC7, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매도호가 잔량 증감7, FID=0;
			 INDEX=150, ITEM=LP_ASKP_RSQN_ICDC7_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_ASKP_RSQN_ICDC7]색참조(+상승, -하락), FID=0;
			 INDEX=151, ITEM=LP_ASKP_RSQN_ICDC8, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매도호가 잔량 증감8, FID=0;
			 INDEX=152, ITEM=LP_ASKP_RSQN_ICDC8_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_ASKP_RSQN_ICDC8]색참조(+상승, -하락), FID=0;
			 INDEX=153, ITEM=LP_ASKP_RSQN_ICDC9, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매도호가 잔량 증감9, FID=0;
			 INDEX=154, ITEM=LP_ASKP_RSQN_ICDC9_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_ASKP_RSQN_ICDC9]색참조(+상승, -하락), FID=0;
			 INDEX=155, ITEM=LP_ASKP_RSQN_ICDC10, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매도호가 잔량 증감10, FID=0;
			 INDEX=156, ITEM=LP_ASKP_RSQN_ICDC10_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_ASKP_RSQN_ICDC10]색참조(+상승, -하락), FID=0;
			 INDEX=157, ITEM=LP_BIDP_RSQN_ICDC1, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매수호가 잔량 증감1, FID=0;
			 INDEX=158, ITEM=LP_BIDP_RSQN_ICDC1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_BIDP_RSQN_ICDC1]색참조(+상승, -하락), FID=0;
			 INDEX=159, ITEM=LP_BIDP_RSQN_ICDC2, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매수호가 잔량 증감2, FID=0;
			 INDEX=160, ITEM=LP_BIDP_RSQN_ICDC2_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_BIDP_RSQN_ICDC2]색참조(+상승, -하락), FID=0;
			 INDEX=161, ITEM=LP_BIDP_RSQN_ICDC3, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매수호가 잔량 증감3, FID=0;
			 INDEX=162, ITEM=LP_BIDP_RSQN_ICDC3_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_BIDP_RSQN_ICDC3]색참조(+상승, -하락), FID=0;
			 INDEX=163, ITEM=LP_BIDP_RSQN_ICDC4, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매수호가 잔량 증감4, FID=0;
			 INDEX=164, ITEM=LP_BIDP_RSQN_ICDC4_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_BIDP_RSQN_ICDC4]색참조(+상승, -하락), FID=0;
			 INDEX=165, ITEM=LP_BIDP_RSQN_ICDC5, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매수호가 잔량 증감5, FID=0;
			 INDEX=166, ITEM=LP_BIDP_RSQN_ICDC5_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_BIDP_RSQN_ICDC5]색참조(+상승, -하락), FID=0;
			 INDEX=167, ITEM=LP_BIDP_RSQN_ICDC6, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매수호가 잔량 증감6, FID=0;
			 INDEX=168, ITEM=LP_BIDP_RSQN_ICDC6_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_BIDP_RSQN_ICDC6]색참조(+상승, -하락), FID=0;
			 INDEX=169, ITEM=LP_BIDP_RSQN_ICDC7, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매수호가 잔량 증감7, FID=0;
			 INDEX=170, ITEM=LP_BIDP_RSQN_ICDC7_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_BIDP_RSQN_ICDC7]색참조(+상승, -하락), FID=0;
			 INDEX=171, ITEM=LP_BIDP_RSQN_ICDC8, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매수호가 잔량 증감8, FID=0;
			 INDEX=172, ITEM=LP_BIDP_RSQN_ICDC8_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_BIDP_RSQN_ICDC8]색참조(+상승, -하락), FID=0;
			 INDEX=173, ITEM=LP_BIDP_RSQN_ICDC9, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매수호가 잔량 증감9, FID=0;
			 INDEX=174, ITEM=LP_BIDP_RSQN_ICDC9_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_BIDP_RSQN_ICDC9]색참조(+상승, -하락), FID=0;
			 INDEX=175, ITEM=LP_BIDP_RSQN_ICDC10, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 매수호가 잔량 증감10, FID=0;
			 INDEX=176, ITEM=LP_BIDP_RSQN_ICDC10_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_BIDP_RSQN_ICDC10]색참조(+상승, -하락), FID=0;
			 INDEX=177, ITEM=LP_TOTAL_ASKP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 총 매도호가 잔량, FID=0;
			 INDEX=178, ITEM=LP_TOTAL_BIDP_RSQN, TYPE=string, SIZE=18, KEY=0, CAPTION=LP 총 매수호가 잔량, FID=0;
			 INDEX=179, ITEM=LP_TOTAL_ASKP_RSQN_ICDC, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 총 매도호가 잔량 증감, FID=0;
			 INDEX=180, ITEM=LP_TOTAL_ASKP_RSQN_ICDC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_TOTAL_ASKP_RSQN_ICDC]색참조(+상승, -하락), FID=0;
			 INDEX=181, ITEM=LP_TOTAL_BIDP_RSQN_ICDC, TYPE=string, SIZE=12, KEY=0, CAPTION=LP 총 매수호가 잔량 증감, FID=0;
			 INDEX=182, ITEM=LP_TOTAL_BIDP_RSQN_ICDC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LP_TOTAL_BIDP_RSQN_ICDC]색참조(+상승, -하락), FID=0;
			 INDEX=183, ITEM=NEW_MKOP_CLS_CODE, TYPE=string, SIZE=2, KEY=0, CAPTION=신 장운영 구분 코드, FID=0;
			 INDEX=184, ITEM=ANTC_ISS_YN, TYPE=string, SIZE=1, KEY=0, CAPTION=예상 활성 여부, FID=0;
			 INDEX=185, ITEM=OVTM_TOTAL_ASKP_ICDC, TYPE=string, SIZE=12, KEY=0, CAPTION=시간외 총 매도호가 잔량 증감, FID=0;
			 INDEX=186, ITEM=OVTM_TOTAL_ASKP_ICDC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OVTM_TOTAL_ASKP_ICDC]색참조(+상승, -하락), FID=0;
			 INDEX=187, ITEM=OVTM_TOTAL_BIDP_ICDC, TYPE=string, SIZE=12, KEY=0, CAPTION=시간외 총 매수호가 잔량 증감, FID=0;
			 INDEX=188, ITEM=OVTM_TOTAL_BIDP_ICDC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OVTM_TOTAL_BIDP_ICDC]색참조(+상승, -하락), FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strSHRN_ISCD = m_CommAgent.GetRealOutputData("S01", "SHRN_ISCD");		//종목코드
CString strBSOP_HOUR = m_CommAgent.GetRealOutputData("S01", "BSOP_HOUR");		//호가시간
CString strHOUR_CLS_CODE = m_CommAgent.GetRealOutputData("S01", "HOUR_CLS_CODE");		//시간구분
CString strASKP1 = m_CommAgent.GetRealOutputData("S01", "ASKP1");		//1매도호가
CString strASKP1_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP1_CLR");		//[ASKP1]색참조(+상승, -하락)
CString strASKP2 = m_CommAgent.GetRealOutputData("S01", "ASKP2");		//2매도호가
CString strASKP2_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP2_CLR");		//[ASKP2]색참조(+상승, -하락)
CString strASKP3 = m_CommAgent.GetRealOutputData("S01", "ASKP3");		//3매도호가
CString strASKP3_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP3_CLR");		//[ASKP3]색참조(+상승, -하락)
CString strASKP4 = m_CommAgent.GetRealOutputData("S01", "ASKP4");		//4매도호가
CString strASKP4_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP4_CLR");		//[ASKP4]색참조(+상승, -하락)
CString strASKP5 = m_CommAgent.GetRealOutputData("S01", "ASKP5");		//5매도호가
CString strASKP5_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP5_CLR");		//[ASKP5]색참조(+상승, -하락)
CString strASKP6 = m_CommAgent.GetRealOutputData("S01", "ASKP6");		//6매도호가
CString strASKP6_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP6_CLR");		//[ASKP6]색참조(+상승, -하락)
CString strASKP7 = m_CommAgent.GetRealOutputData("S01", "ASKP7");		//7매도호가
CString strASKP7_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP7_CLR");		//[ASKP7]색참조(+상승, -하락)
CString strASKP8 = m_CommAgent.GetRealOutputData("S01", "ASKP8");		//8매도호가
CString strASKP8_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP8_CLR");		//[ASKP8]색참조(+상승, -하락)
CString strASKP9 = m_CommAgent.GetRealOutputData("S01", "ASKP9");		//9매도호가
CString strASKP9_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP9_CLR");		//[ASKP9]색참조(+상승, -하락)
CString strASKP10 = m_CommAgent.GetRealOutputData("S01", "ASKP10");		//10매도호가
CString strASKP10_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP10_CLR");		//[ASKP10]색참조(+상승, -하락)
CString strBIDP1 = m_CommAgent.GetRealOutputData("S01", "BIDP1");		//1매수호가
CString strBIDP1_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP1_CLR");		//[BIDP1]색참조(+상승, -하락)
CString strBIDP2 = m_CommAgent.GetRealOutputData("S01", "BIDP2");		//2매수호가
CString strBIDP2_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP2_CLR");		//[BIDP2]색참조(+상승, -하락)
CString strBIDP3 = m_CommAgent.GetRealOutputData("S01", "BIDP3");		//3매수호가
CString strBIDP3_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP3_CLR");		//[BIDP3]색참조(+상승, -하락)
CString strBIDP4 = m_CommAgent.GetRealOutputData("S01", "BIDP4");		//4매수호가
CString strBIDP4_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP4_CLR");		//[BIDP4]색참조(+상승, -하락)
CString strBIDP5 = m_CommAgent.GetRealOutputData("S01", "BIDP5");		//5매수호가
CString strBIDP5_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP5_CLR");		//[BIDP5]색참조(+상승, -하락)
CString strBIDP6 = m_CommAgent.GetRealOutputData("S01", "BIDP6");		//6매수호가
CString strBIDP6_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP6_CLR");		//[BIDP6]색참조(+상승, -하락)
CString strBIDP7 = m_CommAgent.GetRealOutputData("S01", "BIDP7");		//7매수호가
CString strBIDP7_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP7_CLR");		//[BIDP7]색참조(+상승, -하락)
CString strBIDP8 = m_CommAgent.GetRealOutputData("S01", "BIDP8");		//8매수호가
CString strBIDP8_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP8_CLR");		//[BIDP8]색참조(+상승, -하락)
CString strBIDP9 = m_CommAgent.GetRealOutputData("S01", "BIDP9");		//9매수호가
CString strBIDP9_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP9_CLR");		//[BIDP9]색참조(+상승, -하락)
CString strBIDP10 = m_CommAgent.GetRealOutputData("S01", "BIDP10");		//10매수호가
CString strBIDP10_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP10_CLR");		//[BIDP10]색참조(+상승, -하락)
CString strASKP_RSQN1 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN1");		//1매도호가잔량
CString strASKP_RSQN2 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN2");		//2매도호가잔량
CString strASKP_RSQN3 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN3");		//3매도호가잔량
CString strASKP_RSQN4 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN4");		//4매도호가잔량
CString strASKP_RSQN5 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN5");		//5매도호가잔량
CString strASKP_RSQN6 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN6");		//6매도호가잔량
CString strASKP_RSQN7 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN7");		//7매도호가잔량
CString strASKP_RSQN8 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN8");		//8매도호가잔량
CString strASKP_RSQN9 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN9");		//9매도호가잔량
CString strASKP_RSQN10 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN10");		//10매도호가잔량
CString strBIDP_RSQN1 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN1");		//1매수호가잔량
CString strBIDP_RSQN2 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN2");		//2매수호가잔량
CString strBIDP_RSQN3 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN3");		//3매수호가잔량
CString strBIDP_RSQN4 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN4");		//4매수호가잔량
CString strBIDP_RSQN5 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN5");		//5매수호가잔량
CString strBIDP_RSQN6 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN6");		//6매수호가잔량
CString strBIDP_RSQN7 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN7");		//7매수호가잔량
CString strBIDP_RSQN8 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN8");		//8매수호가잔량
CString strBIDP_RSQN9 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN9");		//9매수호가잔량
CString strBIDP_RSQN10 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN10");		//10매수호가잔량
CString strASKP_RSQN_ICDC1 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC1");		//1매도호가잔량증감
CString strASKP_RSQN_ICDC1_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC1_CLR");		//[ASKP_RSQN_ICDC1]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC2 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC2");		//2매도호가잔량증감
CString strASKP_RSQN_ICDC2_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC2_CLR");		//[ASKP_RSQN_ICDC2]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC3 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC3");		//3매도호가잔량증감
CString strASKP_RSQN_ICDC3_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC3_CLR");		//[ASKP_RSQN_ICDC3]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC4 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC4");		//4매도호가잔량증감
CString strASKP_RSQN_ICDC4_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC4_CLR");		//[ASKP_RSQN_ICDC4]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC5 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC5");		//5매도호가잔량증감
CString strASKP_RSQN_ICDC5_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC5_CLR");		//[ASKP_RSQN_ICDC5]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC6 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC6");		//6매도호가잔량증감
CString strASKP_RSQN_ICDC6_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC6_CLR");		//[ASKP_RSQN_ICDC6]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC7 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC7");		//7매도호가잔량증감
CString strASKP_RSQN_ICDC7_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC7_CLR");		//[ASKP_RSQN_ICDC7]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC8 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC8");		//8매도호가잔량증감
CString strASKP_RSQN_ICDC8_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC8_CLR");		//[ASKP_RSQN_ICDC8]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC9 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC9");		//9매도호가잔량증감
CString strASKP_RSQN_ICDC9_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC9_CLR");		//[ASKP_RSQN_ICDC9]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC10 = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC10");		//10매도호가잔량증감
CString strASKP_RSQN_ICDC10_CLR = m_CommAgent.GetRealOutputData("S01", "ASKP_RSQN_ICDC10_CLR");		//[ASKP_RSQN_ICDC10]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC1 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC1");		//1매수호가 잔량 증감
CString strBIDP_RSQN_ICDC1_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC1_CLR");		//[BIDP_RSQN_ICDC1]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC2 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC2");		//2매수호가 잔량 증감
CString strBIDP_RSQN_ICDC2_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC2_CLR");		//[BIDP_RSQN_ICDC2]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC3 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC3");		//3매수호가 잔량 증감
CString strBIDP_RSQN_ICDC3_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC3_CLR");		//[BIDP_RSQN_ICDC3]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC4 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC4");		//4매수호가 잔량 증감
CString strBIDP_RSQN_ICDC4_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC4_CLR");		//[BIDP_RSQN_ICDC4]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC5 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC5");		//5매수호가 잔량 증감
CString strBIDP_RSQN_ICDC5_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC5_CLR");		//[BIDP_RSQN_ICDC5]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC6 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC6");		//6매수호가 잔량 증감
CString strBIDP_RSQN_ICDC6_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC6_CLR");		//[BIDP_RSQN_ICDC6]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC7 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC7");		//7매수호가 잔량 증감
CString strBIDP_RSQN_ICDC7_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC7_CLR");		//[BIDP_RSQN_ICDC7]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC8 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC8");		//8매수호가 잔량 증감
CString strBIDP_RSQN_ICDC8_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC8_CLR");		//[BIDP_RSQN_ICDC8]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC9 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC9");		//9매수호가 잔량 증감
CString strBIDP_RSQN_ICDC9_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC9_CLR");		//[BIDP_RSQN_ICDC9]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC10 = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC10");		//10매수호가 잔량 증감
CString strBIDP_RSQN_ICDC10_CLR = m_CommAgent.GetRealOutputData("S01", "BIDP_RSQN_ICDC10_CLR");		//[BIDP_RSQN_ICDC10]색참조(+상승, -하락)
CString strTOTAL_ASKP_RSQN = m_CommAgent.GetRealOutputData("S01", "TOTAL_ASKP_RSQN");		//총매도호가잔량
CString strTOTAL_BIDP_RSQN = m_CommAgent.GetRealOutputData("S01", "TOTAL_BIDP_RSQN");		//총매수호가잔량
CString strTOTAL_ASKP_RSQN_ICDC = m_CommAgent.GetRealOutputData("S01", "TOTAL_ASKP_RSQN_ICDC");		//총매도호가잔량증감
CString strTOTAL_ASKP_RSQN_ICDC_CLR = m_CommAgent.GetRealOutputData("S01", "TOTAL_ASKP_RSQN_ICDC_CLR");		//[TOTAL_ASKP_RSQN_ICDC]색참조(+상승, -하락)
CString strTOTAL_BIDP_RSQN_ICDC = m_CommAgent.GetRealOutputData("S01", "TOTAL_BIDP_RSQN_ICDC");		//총매수호가잔량증감
CString strTOTAL_BIDP_RSQN_ICDC_CLR = m_CommAgent.GetRealOutputData("S01", "TOTAL_BIDP_RSQN_ICDC_CLR");		//[TOTAL_BIDP_RSQN_ICDC]색참조(+상승, -하락)
CString strOVTM_TOTAL_ASKP_RSQN = m_CommAgent.GetRealOutputData("S01", "OVTM_TOTAL_ASKP_RSQN");		//시간외총매도호가잔량
CString strOVTM_TOTAL_BIDP_RSQN = m_CommAgent.GetRealOutputData("S01", "OVTM_TOTAL_BIDP_RSQN");		//시간외총매수호가잔량
CString strANTC_CNPR = m_CommAgent.GetRealOutputData("S01", "ANTC_CNPR");		//예상체결가
CString strANTC_CNPR_CLR = m_CommAgent.GetRealOutputData("S01", "ANTC_CNPR_CLR");		//[ANTC_CNPR]색참조(+상승, -하락)
CString strANTC_CNQN = m_CommAgent.GetRealOutputData("S01", "ANTC_CNQN");		//예상체결량
CString strACML_VOL = m_CommAgent.GetRealOutputData("S01", "ACML_VOL");		//누적거래량
CString strCOMP_CLS_CODE = m_CommAgent.GetRealOutputData("S01", "COMP_CLS_CODE");		//경쟁대량 방향구분
CString strCNCC_ASPR_CLS_CODE = m_CommAgent.GetRealOutputData("S01", "CNCC_ASPR_CLS_CODE");		//동시호가구분코드
CString strLP_ASKP_RSQN1 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN1");		//LP 매도호가 잔량1
CString strLP_ASKP_RSQN2 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN2");		//LP 매도호가 잔량2
CString strLP_ASKP_RSQN3 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN3");		//LP 매도호가 잔량3
CString strLP_ASKP_RSQN4 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN4");		//LP 매도호가 잔량4
CString strLP_ASKP_RSQN5 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN5");		//LP 매도호가 잔량5
CString strLP_ASKP_RSQN6 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN6");		//LP 매도호가 잔량6
CString strLP_ASKP_RSQN7 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN7");		//LP 매도호가 잔량7
CString strLP_ASKP_RSQN8 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN8");		//LP 매도호가 잔량8
CString strLP_ASKP_RSQN9 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN9");		//LP 매도호가 잔량9
CString strLP_ASKP_RSQN10 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN10");		//LP 매도호가 잔량10
CString strLP_BIDP_RSQN1 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN1");		//LP 매수호가 잔량1
CString strLP_BIDP_RSQN2 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN2");		//LP 매수호가 잔량2
CString strLP_BIDP_RSQN3 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN3");		//LP 매수호가 잔량3
CString strLP_BIDP_RSQN4 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN4");		//LP 매수호가 잔량4
CString strLP_BIDP_RSQN5 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN5");		//LP 매수호가 잔량5
CString strLP_BIDP_RSQN6 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN6");		//LP 매수호가 잔량6
CString strLP_BIDP_RSQN7 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN7");		//LP 매수호가 잔량7
CString strLP_BIDP_RSQN8 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN8");		//LP 매수호가 잔량8
CString strLP_BIDP_RSQN9 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN9");		//LP 매수호가 잔량9
CString strLP_BIDP_RSQN10 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN10");		//LP 매수호가 잔량10
CString strLP_ASKP_RSQN_ICDC1 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC1");		//LP 매도호가 잔량 증감1
CString strLP_ASKP_RSQN_ICDC1_CLR = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC1_CLR");		//[LP_ASKP_RSQN_ICDC1]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC2 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC2");		//LP 매도호가 잔량 증감2
CString strLP_ASKP_RSQN_ICDC2_CLR = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC2_CLR");		//[LP_ASKP_RSQN_ICDC2]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC3 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC3");		//LP 매도호가 잔량 증감3
CString strLP_ASKP_RSQN_ICDC3_CLR = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC3_CLR");		//[LP_ASKP_RSQN_ICDC3]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC4 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC4");		//LP 매도호가 잔량 증감4
CString strLP_ASKP_RSQN_ICDC4_CLR = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC4_CLR");		//[LP_ASKP_RSQN_ICDC4]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC5 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC5");		//LP 매도호가 잔량 증감5
CString strLP_ASKP_RSQN_ICDC5_CLR = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC5_CLR");		//[LP_ASKP_RSQN_ICDC5]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC6 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC6");		//LP 매도호가 잔량 증감6
CString strLP_ASKP_RSQN_ICDC6_CLR = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC6_CLR");		//[LP_ASKP_RSQN_ICDC6]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC7 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC7");		//LP 매도호가 잔량 증감7
CString strLP_ASKP_RSQN_ICDC7_CLR = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC7_CLR");		//[LP_ASKP_RSQN_ICDC7]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC8 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC8");		//LP 매도호가 잔량 증감8
CString strLP_ASKP_RSQN_ICDC8_CLR = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC8_CLR");		//[LP_ASKP_RSQN_ICDC8]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC9 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC9");		//LP 매도호가 잔량 증감9
CString strLP_ASKP_RSQN_ICDC9_CLR = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC9_CLR");		//[LP_ASKP_RSQN_ICDC9]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC10 = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC10");		//LP 매도호가 잔량 증감10
CString strLP_ASKP_RSQN_ICDC10_CLR = m_CommAgent.GetRealOutputData("S01", "LP_ASKP_RSQN_ICDC10_CLR");		//[LP_ASKP_RSQN_ICDC10]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC1 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC1");		//LP 매수호가 잔량 증감1
CString strLP_BIDP_RSQN_ICDC1_CLR = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC1_CLR");		//[LP_BIDP_RSQN_ICDC1]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC2 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC2");		//LP 매수호가 잔량 증감2
CString strLP_BIDP_RSQN_ICDC2_CLR = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC2_CLR");		//[LP_BIDP_RSQN_ICDC2]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC3 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC3");		//LP 매수호가 잔량 증감3
CString strLP_BIDP_RSQN_ICDC3_CLR = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC3_CLR");		//[LP_BIDP_RSQN_ICDC3]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC4 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC4");		//LP 매수호가 잔량 증감4
CString strLP_BIDP_RSQN_ICDC4_CLR = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC4_CLR");		//[LP_BIDP_RSQN_ICDC4]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC5 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC5");		//LP 매수호가 잔량 증감5
CString strLP_BIDP_RSQN_ICDC5_CLR = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC5_CLR");		//[LP_BIDP_RSQN_ICDC5]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC6 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC6");		//LP 매수호가 잔량 증감6
CString strLP_BIDP_RSQN_ICDC6_CLR = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC6_CLR");		//[LP_BIDP_RSQN_ICDC6]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC7 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC7");		//LP 매수호가 잔량 증감7
CString strLP_BIDP_RSQN_ICDC7_CLR = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC7_CLR");		//[LP_BIDP_RSQN_ICDC7]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC8 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC8");		//LP 매수호가 잔량 증감8
CString strLP_BIDP_RSQN_ICDC8_CLR = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC8_CLR");		//[LP_BIDP_RSQN_ICDC8]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC9 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC9");		//LP 매수호가 잔량 증감9
CString strLP_BIDP_RSQN_ICDC9_CLR = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC9_CLR");		//[LP_BIDP_RSQN_ICDC9]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC10 = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC10");		//LP 매수호가 잔량 증감10
CString strLP_BIDP_RSQN_ICDC10_CLR = m_CommAgent.GetRealOutputData("S01", "LP_BIDP_RSQN_ICDC10_CLR");		//[LP_BIDP_RSQN_ICDC10]색참조(+상승, -하락)
CString strLP_TOTAL_ASKP_RSQN = m_CommAgent.GetRealOutputData("S01", "LP_TOTAL_ASKP_RSQN");		//LP 총 매도호가 잔량
CString strLP_TOTAL_BIDP_RSQN = m_CommAgent.GetRealOutputData("S01", "LP_TOTAL_BIDP_RSQN");		//LP 총 매수호가 잔량
CString strLP_TOTAL_ASKP_RSQN_ICDC = m_CommAgent.GetRealOutputData("S01", "LP_TOTAL_ASKP_RSQN_ICDC");		//LP 총 매도호가 잔량 증감
CString strLP_TOTAL_ASKP_RSQN_ICDC_CLR = m_CommAgent.GetRealOutputData("S01", "LP_TOTAL_ASKP_RSQN_ICDC_CLR");		//[LP_TOTAL_ASKP_RSQN_ICDC]색참조(+상승, -하락)
CString strLP_TOTAL_BIDP_RSQN_ICDC = m_CommAgent.GetRealOutputData("S01", "LP_TOTAL_BIDP_RSQN_ICDC");		//LP 총 매수호가 잔량 증감
CString strLP_TOTAL_BIDP_RSQN_ICDC_CLR = m_CommAgent.GetRealOutputData("S01", "LP_TOTAL_BIDP_RSQN_ICDC_CLR");		//[LP_TOTAL_BIDP_RSQN_ICDC]색참조(+상승, -하락)
CString strNEW_MKOP_CLS_CODE = m_CommAgent.GetRealOutputData("S01", "NEW_MKOP_CLS_CODE");		//신 장운영 구분 코드
CString strANTC_ISS_YN = m_CommAgent.GetRealOutputData("S01", "ANTC_ISS_YN");		//예상 활성 여부
CString strOVTM_TOTAL_ASKP_ICDC = m_CommAgent.GetRealOutputData("S01", "OVTM_TOTAL_ASKP_ICDC");		//시간외 총 매도호가 잔량 증감
CString strOVTM_TOTAL_ASKP_ICDC_CLR = m_CommAgent.GetRealOutputData("S01", "OVTM_TOTAL_ASKP_ICDC_CLR");		//[OVTM_TOTAL_ASKP_ICDC]색참조(+상승, -하락)
CString strOVTM_TOTAL_BIDP_ICDC = m_CommAgent.GetRealOutputData("S01", "OVTM_TOTAL_BIDP_ICDC");		//시간외 총 매수호가 잔량 증감
CString strOVTM_TOTAL_BIDP_ICDC_CLR = m_CommAgent.GetRealOutputData("S01", "OVTM_TOTAL_BIDP_ICDC_CLR");		//[OVTM_TOTAL_BIDP_ICDC]색참조(+상승, -하락)




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strSHRN_ISCD = realCommRecvData.GetItem(0, 0);		//종목코드
CString strBSOP_HOUR = realCommRecvData.GetItem(0, 1);		//호가시간
CString strHOUR_CLS_CODE = realCommRecvData.GetItem(0, 2);		//시간구분
CString strASKP1 = realCommRecvData.GetItem(0, 3);		//1매도호가
CString strASKP1_CLR = realCommRecvData.GetItem(0, 4);		//[ASKP1]색참조(+상승, -하락)
CString strASKP2 = realCommRecvData.GetItem(0, 5);		//2매도호가
CString strASKP2_CLR = realCommRecvData.GetItem(0, 6);		//[ASKP2]색참조(+상승, -하락)
CString strASKP3 = realCommRecvData.GetItem(0, 7);		//3매도호가
CString strASKP3_CLR = realCommRecvData.GetItem(0, 8);		//[ASKP3]색참조(+상승, -하락)
CString strASKP4 = realCommRecvData.GetItem(0, 9);		//4매도호가
CString strASKP4_CLR = realCommRecvData.GetItem(0, 10);		//[ASKP4]색참조(+상승, -하락)
CString strASKP5 = realCommRecvData.GetItem(0, 11);		//5매도호가
CString strASKP5_CLR = realCommRecvData.GetItem(0, 12);		//[ASKP5]색참조(+상승, -하락)
CString strASKP6 = realCommRecvData.GetItem(0, 13);		//6매도호가
CString strASKP6_CLR = realCommRecvData.GetItem(0, 14);		//[ASKP6]색참조(+상승, -하락)
CString strASKP7 = realCommRecvData.GetItem(0, 15);		//7매도호가
CString strASKP7_CLR = realCommRecvData.GetItem(0, 16);		//[ASKP7]색참조(+상승, -하락)
CString strASKP8 = realCommRecvData.GetItem(0, 17);		//8매도호가
CString strASKP8_CLR = realCommRecvData.GetItem(0, 18);		//[ASKP8]색참조(+상승, -하락)
CString strASKP9 = realCommRecvData.GetItem(0, 19);		//9매도호가
CString strASKP9_CLR = realCommRecvData.GetItem(0, 20);		//[ASKP9]색참조(+상승, -하락)
CString strASKP10 = realCommRecvData.GetItem(0, 21);		//10매도호가
CString strASKP10_CLR = realCommRecvData.GetItem(0, 22);		//[ASKP10]색참조(+상승, -하락)
CString strBIDP1 = realCommRecvData.GetItem(0, 23);		//1매수호가
CString strBIDP1_CLR = realCommRecvData.GetItem(0, 24);		//[BIDP1]색참조(+상승, -하락)
CString strBIDP2 = realCommRecvData.GetItem(0, 25);		//2매수호가
CString strBIDP2_CLR = realCommRecvData.GetItem(0, 26);		//[BIDP2]색참조(+상승, -하락)
CString strBIDP3 = realCommRecvData.GetItem(0, 27);		//3매수호가
CString strBIDP3_CLR = realCommRecvData.GetItem(0, 28);		//[BIDP3]색참조(+상승, -하락)
CString strBIDP4 = realCommRecvData.GetItem(0, 29);		//4매수호가
CString strBIDP4_CLR = realCommRecvData.GetItem(0, 30);		//[BIDP4]색참조(+상승, -하락)
CString strBIDP5 = realCommRecvData.GetItem(0, 31);		//5매수호가
CString strBIDP5_CLR = realCommRecvData.GetItem(0, 32);		//[BIDP5]색참조(+상승, -하락)
CString strBIDP6 = realCommRecvData.GetItem(0, 33);		//6매수호가
CString strBIDP6_CLR = realCommRecvData.GetItem(0, 34);		//[BIDP6]색참조(+상승, -하락)
CString strBIDP7 = realCommRecvData.GetItem(0, 35);		//7매수호가
CString strBIDP7_CLR = realCommRecvData.GetItem(0, 36);		//[BIDP7]색참조(+상승, -하락)
CString strBIDP8 = realCommRecvData.GetItem(0, 37);		//8매수호가
CString strBIDP8_CLR = realCommRecvData.GetItem(0, 38);		//[BIDP8]색참조(+상승, -하락)
CString strBIDP9 = realCommRecvData.GetItem(0, 39);		//9매수호가
CString strBIDP9_CLR = realCommRecvData.GetItem(0, 40);		//[BIDP9]색참조(+상승, -하락)
CString strBIDP10 = realCommRecvData.GetItem(0, 41);		//10매수호가
CString strBIDP10_CLR = realCommRecvData.GetItem(0, 42);		//[BIDP10]색참조(+상승, -하락)
CString strASKP_RSQN1 = realCommRecvData.GetItem(0, 43);		//1매도호가잔량
CString strASKP_RSQN2 = realCommRecvData.GetItem(0, 44);		//2매도호가잔량
CString strASKP_RSQN3 = realCommRecvData.GetItem(0, 45);		//3매도호가잔량
CString strASKP_RSQN4 = realCommRecvData.GetItem(0, 46);		//4매도호가잔량
CString strASKP_RSQN5 = realCommRecvData.GetItem(0, 47);		//5매도호가잔량
CString strASKP_RSQN6 = realCommRecvData.GetItem(0, 48);		//6매도호가잔량
CString strASKP_RSQN7 = realCommRecvData.GetItem(0, 49);		//7매도호가잔량
CString strASKP_RSQN8 = realCommRecvData.GetItem(0, 50);		//8매도호가잔량
CString strASKP_RSQN9 = realCommRecvData.GetItem(0, 51);		//9매도호가잔량
CString strASKP_RSQN10 = realCommRecvData.GetItem(0, 52);		//10매도호가잔량
CString strBIDP_RSQN1 = realCommRecvData.GetItem(0, 53);		//1매수호가잔량
CString strBIDP_RSQN2 = realCommRecvData.GetItem(0, 54);		//2매수호가잔량
CString strBIDP_RSQN3 = realCommRecvData.GetItem(0, 55);		//3매수호가잔량
CString strBIDP_RSQN4 = realCommRecvData.GetItem(0, 56);		//4매수호가잔량
CString strBIDP_RSQN5 = realCommRecvData.GetItem(0, 57);		//5매수호가잔량
CString strBIDP_RSQN6 = realCommRecvData.GetItem(0, 58);		//6매수호가잔량
CString strBIDP_RSQN7 = realCommRecvData.GetItem(0, 59);		//7매수호가잔량
CString strBIDP_RSQN8 = realCommRecvData.GetItem(0, 60);		//8매수호가잔량
CString strBIDP_RSQN9 = realCommRecvData.GetItem(0, 61);		//9매수호가잔량
CString strBIDP_RSQN10 = realCommRecvData.GetItem(0, 62);		//10매수호가잔량
CString strASKP_RSQN_ICDC1 = realCommRecvData.GetItem(0, 63);		//1매도호가잔량증감
CString strASKP_RSQN_ICDC1_CLR = realCommRecvData.GetItem(0, 64);		//[ASKP_RSQN_ICDC1]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC2 = realCommRecvData.GetItem(0, 65);		//2매도호가잔량증감
CString strASKP_RSQN_ICDC2_CLR = realCommRecvData.GetItem(0, 66);		//[ASKP_RSQN_ICDC2]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC3 = realCommRecvData.GetItem(0, 67);		//3매도호가잔량증감
CString strASKP_RSQN_ICDC3_CLR = realCommRecvData.GetItem(0, 68);		//[ASKP_RSQN_ICDC3]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC4 = realCommRecvData.GetItem(0, 69);		//4매도호가잔량증감
CString strASKP_RSQN_ICDC4_CLR = realCommRecvData.GetItem(0, 70);		//[ASKP_RSQN_ICDC4]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC5 = realCommRecvData.GetItem(0, 71);		//5매도호가잔량증감
CString strASKP_RSQN_ICDC5_CLR = realCommRecvData.GetItem(0, 72);		//[ASKP_RSQN_ICDC5]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC6 = realCommRecvData.GetItem(0, 73);		//6매도호가잔량증감
CString strASKP_RSQN_ICDC6_CLR = realCommRecvData.GetItem(0, 74);		//[ASKP_RSQN_ICDC6]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC7 = realCommRecvData.GetItem(0, 75);		//7매도호가잔량증감
CString strASKP_RSQN_ICDC7_CLR = realCommRecvData.GetItem(0, 76);		//[ASKP_RSQN_ICDC7]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC8 = realCommRecvData.GetItem(0, 77);		//8매도호가잔량증감
CString strASKP_RSQN_ICDC8_CLR = realCommRecvData.GetItem(0, 78);		//[ASKP_RSQN_ICDC8]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC9 = realCommRecvData.GetItem(0, 79);		//9매도호가잔량증감
CString strASKP_RSQN_ICDC9_CLR = realCommRecvData.GetItem(0, 80);		//[ASKP_RSQN_ICDC9]색참조(+상승, -하락)
CString strASKP_RSQN_ICDC10 = realCommRecvData.GetItem(0, 81);		//10매도호가잔량증감
CString strASKP_RSQN_ICDC10_CLR = realCommRecvData.GetItem(0, 82);		//[ASKP_RSQN_ICDC10]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC1 = realCommRecvData.GetItem(0, 83);		//1매수호가 잔량 증감
CString strBIDP_RSQN_ICDC1_CLR = realCommRecvData.GetItem(0, 84);		//[BIDP_RSQN_ICDC1]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC2 = realCommRecvData.GetItem(0, 85);		//2매수호가 잔량 증감
CString strBIDP_RSQN_ICDC2_CLR = realCommRecvData.GetItem(0, 86);		//[BIDP_RSQN_ICDC2]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC3 = realCommRecvData.GetItem(0, 87);		//3매수호가 잔량 증감
CString strBIDP_RSQN_ICDC3_CLR = realCommRecvData.GetItem(0, 88);		//[BIDP_RSQN_ICDC3]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC4 = realCommRecvData.GetItem(0, 89);		//4매수호가 잔량 증감
CString strBIDP_RSQN_ICDC4_CLR = realCommRecvData.GetItem(0, 90);		//[BIDP_RSQN_ICDC4]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC5 = realCommRecvData.GetItem(0, 91);		//5매수호가 잔량 증감
CString strBIDP_RSQN_ICDC5_CLR = realCommRecvData.GetItem(0, 92);		//[BIDP_RSQN_ICDC5]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC6 = realCommRecvData.GetItem(0, 93);		//6매수호가 잔량 증감
CString strBIDP_RSQN_ICDC6_CLR = realCommRecvData.GetItem(0, 94);		//[BIDP_RSQN_ICDC6]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC7 = realCommRecvData.GetItem(0, 95);		//7매수호가 잔량 증감
CString strBIDP_RSQN_ICDC7_CLR = realCommRecvData.GetItem(0, 96);		//[BIDP_RSQN_ICDC7]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC8 = realCommRecvData.GetItem(0, 97);		//8매수호가 잔량 증감
CString strBIDP_RSQN_ICDC8_CLR = realCommRecvData.GetItem(0, 98);		//[BIDP_RSQN_ICDC8]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC9 = realCommRecvData.GetItem(0, 99);		//9매수호가 잔량 증감
CString strBIDP_RSQN_ICDC9_CLR = realCommRecvData.GetItem(0, 100);		//[BIDP_RSQN_ICDC9]색참조(+상승, -하락)
CString strBIDP_RSQN_ICDC10 = realCommRecvData.GetItem(0, 101);		//10매수호가 잔량 증감
CString strBIDP_RSQN_ICDC10_CLR = realCommRecvData.GetItem(0, 102);		//[BIDP_RSQN_ICDC10]색참조(+상승, -하락)
CString strTOTAL_ASKP_RSQN = realCommRecvData.GetItem(0, 103);		//총매도호가잔량
CString strTOTAL_BIDP_RSQN = realCommRecvData.GetItem(0, 104);		//총매수호가잔량
CString strTOTAL_ASKP_RSQN_ICDC = realCommRecvData.GetItem(0, 105);		//총매도호가잔량증감
CString strTOTAL_ASKP_RSQN_ICDC_CLR = realCommRecvData.GetItem(0, 106);		//[TOTAL_ASKP_RSQN_ICDC]색참조(+상승, -하락)
CString strTOTAL_BIDP_RSQN_ICDC = realCommRecvData.GetItem(0, 107);		//총매수호가잔량증감
CString strTOTAL_BIDP_RSQN_ICDC_CLR = realCommRecvData.GetItem(0, 108);		//[TOTAL_BIDP_RSQN_ICDC]색참조(+상승, -하락)
CString strOVTM_TOTAL_ASKP_RSQN = realCommRecvData.GetItem(0, 109);		//시간외총매도호가잔량
CString strOVTM_TOTAL_BIDP_RSQN = realCommRecvData.GetItem(0, 110);		//시간외총매수호가잔량
CString strANTC_CNPR = realCommRecvData.GetItem(0, 111);		//예상체결가
CString strANTC_CNPR_CLR = realCommRecvData.GetItem(0, 112);		//[ANTC_CNPR]색참조(+상승, -하락)
CString strANTC_CNQN = realCommRecvData.GetItem(0, 113);		//예상체결량
CString strACML_VOL = realCommRecvData.GetItem(0, 114);		//누적거래량
CString strCOMP_CLS_CODE = realCommRecvData.GetItem(0, 115);		//경쟁대량 방향구분
CString strCNCC_ASPR_CLS_CODE = realCommRecvData.GetItem(0, 116);		//동시호가구분코드
CString strLP_ASKP_RSQN1 = realCommRecvData.GetItem(0, 117);		//LP 매도호가 잔량1
CString strLP_ASKP_RSQN2 = realCommRecvData.GetItem(0, 118);		//LP 매도호가 잔량2
CString strLP_ASKP_RSQN3 = realCommRecvData.GetItem(0, 119);		//LP 매도호가 잔량3
CString strLP_ASKP_RSQN4 = realCommRecvData.GetItem(0, 120);		//LP 매도호가 잔량4
CString strLP_ASKP_RSQN5 = realCommRecvData.GetItem(0, 121);		//LP 매도호가 잔량5
CString strLP_ASKP_RSQN6 = realCommRecvData.GetItem(0, 122);		//LP 매도호가 잔량6
CString strLP_ASKP_RSQN7 = realCommRecvData.GetItem(0, 123);		//LP 매도호가 잔량7
CString strLP_ASKP_RSQN8 = realCommRecvData.GetItem(0, 124);		//LP 매도호가 잔량8
CString strLP_ASKP_RSQN9 = realCommRecvData.GetItem(0, 125);		//LP 매도호가 잔량9
CString strLP_ASKP_RSQN10 = realCommRecvData.GetItem(0, 126);		//LP 매도호가 잔량10
CString strLP_BIDP_RSQN1 = realCommRecvData.GetItem(0, 127);		//LP 매수호가 잔량1
CString strLP_BIDP_RSQN2 = realCommRecvData.GetItem(0, 128);		//LP 매수호가 잔량2
CString strLP_BIDP_RSQN3 = realCommRecvData.GetItem(0, 129);		//LP 매수호가 잔량3
CString strLP_BIDP_RSQN4 = realCommRecvData.GetItem(0, 130);		//LP 매수호가 잔량4
CString strLP_BIDP_RSQN5 = realCommRecvData.GetItem(0, 131);		//LP 매수호가 잔량5
CString strLP_BIDP_RSQN6 = realCommRecvData.GetItem(0, 132);		//LP 매수호가 잔량6
CString strLP_BIDP_RSQN7 = realCommRecvData.GetItem(0, 133);		//LP 매수호가 잔량7
CString strLP_BIDP_RSQN8 = realCommRecvData.GetItem(0, 134);		//LP 매수호가 잔량8
CString strLP_BIDP_RSQN9 = realCommRecvData.GetItem(0, 135);		//LP 매수호가 잔량9
CString strLP_BIDP_RSQN10 = realCommRecvData.GetItem(0, 136);		//LP 매수호가 잔량10
CString strLP_ASKP_RSQN_ICDC1 = realCommRecvData.GetItem(0, 137);		//LP 매도호가 잔량 증감1
CString strLP_ASKP_RSQN_ICDC1_CLR = realCommRecvData.GetItem(0, 138);		//[LP_ASKP_RSQN_ICDC1]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC2 = realCommRecvData.GetItem(0, 139);		//LP 매도호가 잔량 증감2
CString strLP_ASKP_RSQN_ICDC2_CLR = realCommRecvData.GetItem(0, 140);		//[LP_ASKP_RSQN_ICDC2]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC3 = realCommRecvData.GetItem(0, 141);		//LP 매도호가 잔량 증감3
CString strLP_ASKP_RSQN_ICDC3_CLR = realCommRecvData.GetItem(0, 142);		//[LP_ASKP_RSQN_ICDC3]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC4 = realCommRecvData.GetItem(0, 143);		//LP 매도호가 잔량 증감4
CString strLP_ASKP_RSQN_ICDC4_CLR = realCommRecvData.GetItem(0, 144);		//[LP_ASKP_RSQN_ICDC4]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC5 = realCommRecvData.GetItem(0, 145);		//LP 매도호가 잔량 증감5
CString strLP_ASKP_RSQN_ICDC5_CLR = realCommRecvData.GetItem(0, 146);		//[LP_ASKP_RSQN_ICDC5]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC6 = realCommRecvData.GetItem(0, 147);		//LP 매도호가 잔량 증감6
CString strLP_ASKP_RSQN_ICDC6_CLR = realCommRecvData.GetItem(0, 148);		//[LP_ASKP_RSQN_ICDC6]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC7 = realCommRecvData.GetItem(0, 149);		//LP 매도호가 잔량 증감7
CString strLP_ASKP_RSQN_ICDC7_CLR = realCommRecvData.GetItem(0, 150);		//[LP_ASKP_RSQN_ICDC7]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC8 = realCommRecvData.GetItem(0, 151);		//LP 매도호가 잔량 증감8
CString strLP_ASKP_RSQN_ICDC8_CLR = realCommRecvData.GetItem(0, 152);		//[LP_ASKP_RSQN_ICDC8]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC9 = realCommRecvData.GetItem(0, 153);		//LP 매도호가 잔량 증감9
CString strLP_ASKP_RSQN_ICDC9_CLR = realCommRecvData.GetItem(0, 154);		//[LP_ASKP_RSQN_ICDC9]색참조(+상승, -하락)
CString strLP_ASKP_RSQN_ICDC10 = realCommRecvData.GetItem(0, 155);		//LP 매도호가 잔량 증감10
CString strLP_ASKP_RSQN_ICDC10_CLR = realCommRecvData.GetItem(0, 156);		//[LP_ASKP_RSQN_ICDC10]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC1 = realCommRecvData.GetItem(0, 157);		//LP 매수호가 잔량 증감1
CString strLP_BIDP_RSQN_ICDC1_CLR = realCommRecvData.GetItem(0, 158);		//[LP_BIDP_RSQN_ICDC1]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC2 = realCommRecvData.GetItem(0, 159);		//LP 매수호가 잔량 증감2
CString strLP_BIDP_RSQN_ICDC2_CLR = realCommRecvData.GetItem(0, 160);		//[LP_BIDP_RSQN_ICDC2]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC3 = realCommRecvData.GetItem(0, 161);		//LP 매수호가 잔량 증감3
CString strLP_BIDP_RSQN_ICDC3_CLR = realCommRecvData.GetItem(0, 162);		//[LP_BIDP_RSQN_ICDC3]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC4 = realCommRecvData.GetItem(0, 163);		//LP 매수호가 잔량 증감4
CString strLP_BIDP_RSQN_ICDC4_CLR = realCommRecvData.GetItem(0, 164);		//[LP_BIDP_RSQN_ICDC4]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC5 = realCommRecvData.GetItem(0, 165);		//LP 매수호가 잔량 증감5
CString strLP_BIDP_RSQN_ICDC5_CLR = realCommRecvData.GetItem(0, 166);		//[LP_BIDP_RSQN_ICDC5]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC6 = realCommRecvData.GetItem(0, 167);		//LP 매수호가 잔량 증감6
CString strLP_BIDP_RSQN_ICDC6_CLR = realCommRecvData.GetItem(0, 168);		//[LP_BIDP_RSQN_ICDC6]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC7 = realCommRecvData.GetItem(0, 169);		//LP 매수호가 잔량 증감7
CString strLP_BIDP_RSQN_ICDC7_CLR = realCommRecvData.GetItem(0, 170);		//[LP_BIDP_RSQN_ICDC7]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC8 = realCommRecvData.GetItem(0, 171);		//LP 매수호가 잔량 증감8
CString strLP_BIDP_RSQN_ICDC8_CLR = realCommRecvData.GetItem(0, 172);		//[LP_BIDP_RSQN_ICDC8]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC9 = realCommRecvData.GetItem(0, 173);		//LP 매수호가 잔량 증감9
CString strLP_BIDP_RSQN_ICDC9_CLR = realCommRecvData.GetItem(0, 174);		//[LP_BIDP_RSQN_ICDC9]색참조(+상승, -하락)
CString strLP_BIDP_RSQN_ICDC10 = realCommRecvData.GetItem(0, 175);		//LP 매수호가 잔량 증감10
CString strLP_BIDP_RSQN_ICDC10_CLR = realCommRecvData.GetItem(0, 176);		//[LP_BIDP_RSQN_ICDC10]색참조(+상승, -하락)
CString strLP_TOTAL_ASKP_RSQN = realCommRecvData.GetItem(0, 177);		//LP 총 매도호가 잔량
CString strLP_TOTAL_BIDP_RSQN = realCommRecvData.GetItem(0, 178);		//LP 총 매수호가 잔량
CString strLP_TOTAL_ASKP_RSQN_ICDC = realCommRecvData.GetItem(0, 179);		//LP 총 매도호가 잔량 증감
CString strLP_TOTAL_ASKP_RSQN_ICDC_CLR = realCommRecvData.GetItem(0, 180);		//[LP_TOTAL_ASKP_RSQN_ICDC]색참조(+상승, -하락)
CString strLP_TOTAL_BIDP_RSQN_ICDC = realCommRecvData.GetItem(0, 181);		//LP 총 매수호가 잔량 증감
CString strLP_TOTAL_BIDP_RSQN_ICDC_CLR = realCommRecvData.GetItem(0, 182);		//[LP_TOTAL_BIDP_RSQN_ICDC]색참조(+상승, -하락)
CString strNEW_MKOP_CLS_CODE = realCommRecvData.GetItem(0, 183);		//신 장운영 구분 코드
CString strANTC_ISS_YN = realCommRecvData.GetItem(0, 184);		//예상 활성 여부
CString strOVTM_TOTAL_ASKP_ICDC = realCommRecvData.GetItem(0, 185);		//시간외 총 매도호가 잔량 증감
CString strOVTM_TOTAL_ASKP_ICDC_CLR = realCommRecvData.GetItem(0, 186);		//[OVTM_TOTAL_ASKP_ICDC]색참조(+상승, -하락)
CString strOVTM_TOTAL_BIDP_ICDC = realCommRecvData.GetItem(0, 187);		//시간외 총 매수호가 잔량 증감
CString strOVTM_TOTAL_BIDP_ICDC_CLR = realCommRecvData.GetItem(0, 188);		//[OVTM_TOTAL_BIDP_ICDC]색참조(+상승, -하락)
