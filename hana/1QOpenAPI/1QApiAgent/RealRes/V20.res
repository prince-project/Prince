BEGIN_FUNCTION_MAP
	REAL_TYPE=138, REAL_NAME=V20, DESCRIPTION=�ؿܿɼ� ü��;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=QTTN_PRDT_CD, TYPE=string, SIZE=32, KEY=1, CAPTION=�����ڵ�(����), FID=0;
			 INDEX=1, ITEM=CURRENT_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=��������, �ŷ�����, FID=0;
			 INDEX=2, ITEM=TRADE_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=����, FID=0;
			 INDEX=3, ITEM=TRADE_TIME, TYPE=string, SIZE=6, KEY=0, CAPTION=�ð�, FID=0;
			 INDEX=4, ITEM=KTRADE_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=�ѱ�����, FID=0;
			 INDEX=5, ITEM=KTRADE_TIME, TYPE=string, SIZE=6, KEY=0, CAPTION=�ѱ��ð�, FID=0;
			 INDEX=6, ITEM=RPT_SEQ, TYPE=string, SIZE=8, KEY=0, CAPTION=seq, FID=0;
			 INDEX=7, ITEM=GLOBEX_TP, TYPE=string, SIZE=1, KEY=0, CAPTION=�����屸��, FID=0;
			 INDEX=8, ITEM=TRDPRC_1, TYPE=string, SIZE=20, KEY=0, CAPTION=���簡, FID=0;
			 INDEX=9, ITEM=TRDPRC_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[TRDPRC_1]������(+���, -�϶�), FID=0;
			 INDEX=10, ITEM=NETCHNG_CLS, TYPE=string, SIZE=1, KEY=0, CAPTION=���ϴ�񱸺�, FID=0;
			 INDEX=11, ITEM=NETCHNG_1, TYPE=string, SIZE=20, KEY=0, CAPTION=���ϴ��, FID=0;
			 INDEX=12, ITEM=NETCHNG_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NETCHNG_1]������(+���, -�϶�), FID=0;
			 INDEX=13, ITEM=PCTCHNG_1, TYPE=string, SIZE=6, KEY=0, CAPTION=���ϴ����, FID=0;
			 INDEX=14, ITEM=PCTCHNG_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PCTCHNG_1]������(+���, -�϶�), FID=0;
			 INDEX=15, ITEM=TRDVOL_1, TYPE=string, SIZE=12, KEY=0, CAPTION=ü�����, FID=0;
			 INDEX=16, ITEM=TRDVOL_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[TRDVOL_1]������(+���, -�϶�), FID=0;
			 INDEX=17, ITEM=ACVOL_1, TYPE=string, SIZE=12, KEY=0, CAPTION=����ü�����, FID=0;
			 INDEX=18, ITEM=OPEN_PRC, TYPE=string, SIZE=20, KEY=0, CAPTION=�ð�, FID=0;
			 INDEX=19, ITEM=OPEN_PRC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPEN_PRC]������(+���, -�϶�), FID=0;
			 INDEX=20, ITEM=HIGH_1, TYPE=string, SIZE=20, KEY=0, CAPTION=��, FID=0;
			 INDEX=21, ITEM=HIGH_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[HIGH_1]������(+���, -�϶�), FID=0;
			 INDEX=22, ITEM=LOW_1, TYPE=string, SIZE=20, KEY=0, CAPTION=����, FID=0;
			 INDEX=23, ITEM=LOW_1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LOW_1]������(+���, -�϶�), FID=0;
			 INDEX=24, ITEM=OPEN_TIME, TYPE=string, SIZE=6, KEY=0, CAPTION=�ð��ð�, FID=0;
			 INDEX=25, ITEM=HIGH_TIME, TYPE=string, SIZE=6, KEY=0, CAPTION=���ð�, FID=0;
			 INDEX=26, ITEM=LOW_TIME, TYPE=string, SIZE=6, KEY=0, CAPTION=�����ð�, FID=0;
			 INDEX=27, ITEM=BID_EXEC_SUM, TYPE=string, SIZE=15, KEY=0, CAPTION=���� ����ü�����(�ż�����), FID=0;
			 INDEX=28, ITEM=ASK_EXEC_SUM, TYPE=string, SIZE=15, KEY=0, CAPTION=���� ����ü�����(�ŵ�����), FID=0;
			 INDEX=29, ITEM=BOH_EXEC_SUM, TYPE=string, SIZE=15, KEY=0, CAPTION=���� ����ü�����(����), FID=0;
			 INDEX=30, ITEM=EX_BEST_BID1, TYPE=string, SIZE=20, KEY=0, CAPTION=ü��� �ż� 1ȣ��(�ŷ���), FID=0;
			 INDEX=31, ITEM=EX_BEST_BID1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[EX_BEST_BID1]������(+���, -�϶�), FID=0;
			 INDEX=32, ITEM=EX_BEST_ASK1, TYPE=string, SIZE=20, KEY=0, CAPTION=ü��� �ŵ� 1ȣ��(�ŷ���), FID=0;
			 INDEX=33, ITEM=EX_BEST_ASK1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[EX_BEST_ASK1]������(+���, -�϶�), FID=0;
			 INDEX=34, ITEM=EX_BEST_BSIZ1, TYPE=string, SIZE=12, KEY=0, CAPTION=ü��� �ż� 1����(�ŷ���), FID=0;
			 INDEX=35, ITEM=EX_BEST_ASIZ1, TYPE=string, SIZE=12, KEY=0, CAPTION=ü��� �ŵ� 1����(�ŷ���), FID=0;
			 INDEX=36, ITEM=OPENINTEREST, TYPE=string, SIZE=12, KEY=0, CAPTION=�̰�����, FID=0;
			 INDEX=37, ITEM=OP_NETCHNG_1, TYPE=string, SIZE=12, KEY=0, CAPTION=��ü�ᷮ���, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 ���� ���Ǹ� ���� GetRealOutputData �޼ҵ� MFC �ҽ� ���ø�
 **********************************************/
CString strQTTN_PRDT_CD = m_CommAgent.GetRealOutputData("V20", "QTTN_PRDT_CD");		//�����ڵ�(����)
CString strCURRENT_DATE = m_CommAgent.GetRealOutputData("V20", "CURRENT_DATE");		//��������, �ŷ�����
CString strTRADE_DATE = m_CommAgent.GetRealOutputData("V20", "TRADE_DATE");		//����
CString strTRADE_TIME = m_CommAgent.GetRealOutputData("V20", "TRADE_TIME");		//�ð�
CString strKTRADE_DATE = m_CommAgent.GetRealOutputData("V20", "KTRADE_DATE");		//�ѱ�����
CString strKTRADE_TIME = m_CommAgent.GetRealOutputData("V20", "KTRADE_TIME");		//�ѱ��ð�
CString strRPT_SEQ = m_CommAgent.GetRealOutputData("V20", "RPT_SEQ");		//seq
CString strGLOBEX_TP = m_CommAgent.GetRealOutputData("V20", "GLOBEX_TP");		//�����屸��
CString strTRDPRC_1 = m_CommAgent.GetRealOutputData("V20", "TRDPRC_1");		//���簡
CString strTRDPRC_1_CLR = m_CommAgent.GetRealOutputData("V20", "TRDPRC_1_CLR");		//[TRDPRC_1]������(+���, -�϶�)
CString strNETCHNG_CLS = m_CommAgent.GetRealOutputData("V20", "NETCHNG_CLS");		//���ϴ�񱸺�
CString strNETCHNG_1 = m_CommAgent.GetRealOutputData("V20", "NETCHNG_1");		//���ϴ��
CString strNETCHNG_1_CLR = m_CommAgent.GetRealOutputData("V20", "NETCHNG_1_CLR");		//[NETCHNG_1]������(+���, -�϶�)
CString strPCTCHNG_1 = m_CommAgent.GetRealOutputData("V20", "PCTCHNG_1");		//���ϴ����
CString strPCTCHNG_1_CLR = m_CommAgent.GetRealOutputData("V20", "PCTCHNG_1_CLR");		//[PCTCHNG_1]������(+���, -�϶�)
CString strTRDVOL_1 = m_CommAgent.GetRealOutputData("V20", "TRDVOL_1");		//ü�����
CString strTRDVOL_1_CLR = m_CommAgent.GetRealOutputData("V20", "TRDVOL_1_CLR");		//[TRDVOL_1]������(+���, -�϶�)
CString strACVOL_1 = m_CommAgent.GetRealOutputData("V20", "ACVOL_1");		//����ü�����
CString strOPEN_PRC = m_CommAgent.GetRealOutputData("V20", "OPEN_PRC");		//�ð�
CString strOPEN_PRC_CLR = m_CommAgent.GetRealOutputData("V20", "OPEN_PRC_CLR");		//[OPEN_PRC]������(+���, -�϶�)
CString strHIGH_1 = m_CommAgent.GetRealOutputData("V20", "HIGH_1");		//��
CString strHIGH_1_CLR = m_CommAgent.GetRealOutputData("V20", "HIGH_1_CLR");		//[HIGH_1]������(+���, -�϶�)
CString strLOW_1 = m_CommAgent.GetRealOutputData("V20", "LOW_1");		//����
CString strLOW_1_CLR = m_CommAgent.GetRealOutputData("V20", "LOW_1_CLR");		//[LOW_1]������(+���, -�϶�)
CString strOPEN_TIME = m_CommAgent.GetRealOutputData("V20", "OPEN_TIME");		//�ð��ð�
CString strHIGH_TIME = m_CommAgent.GetRealOutputData("V20", "HIGH_TIME");		//���ð�
CString strLOW_TIME = m_CommAgent.GetRealOutputData("V20", "LOW_TIME");		//�����ð�
CString strBID_EXEC_SUM = m_CommAgent.GetRealOutputData("V20", "BID_EXEC_SUM");		//���� ����ü�����(�ż�����)
CString strASK_EXEC_SUM = m_CommAgent.GetRealOutputData("V20", "ASK_EXEC_SUM");		//���� ����ü�����(�ŵ�����)
CString strBOH_EXEC_SUM = m_CommAgent.GetRealOutputData("V20", "BOH_EXEC_SUM");		//���� ����ü�����(����)
CString strEX_BEST_BID1 = m_CommAgent.GetRealOutputData("V20", "EX_BEST_BID1");		//ü��� �ż� 1ȣ��(�ŷ���)
CString strEX_BEST_BID1_CLR = m_CommAgent.GetRealOutputData("V20", "EX_BEST_BID1_CLR");		//[EX_BEST_BID1]������(+���, -�϶�)
CString strEX_BEST_ASK1 = m_CommAgent.GetRealOutputData("V20", "EX_BEST_ASK1");		//ü��� �ŵ� 1ȣ��(�ŷ���)
CString strEX_BEST_ASK1_CLR = m_CommAgent.GetRealOutputData("V20", "EX_BEST_ASK1_CLR");		//[EX_BEST_ASK1]������(+���, -�϶�)
CString strEX_BEST_BSIZ1 = m_CommAgent.GetRealOutputData("V20", "EX_BEST_BSIZ1");		//ü��� �ż� 1����(�ŷ���)
CString strEX_BEST_ASIZ1 = m_CommAgent.GetRealOutputData("V20", "EX_BEST_ASIZ1");		//ü��� �ŵ� 1����(�ŷ���)
CString strOPENINTEREST = m_CommAgent.GetRealOutputData("V20", "OPENINTEREST");		//�̰�����
CString strOP_NETCHNG_1 = m_CommAgent.GetRealOutputData("V20", "OP_NETCHNG_1");		//��ü�ᷮ���




/**********************************************
 ���� ���Ǹ� ���� �޸� �ε��� ���� �ҽ� ���ø�(C++������ ��� ����)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strQTTN_PRDT_CD = realCommRecvData.GetItem(0, 0);		//�����ڵ�(����)
CString strCURRENT_DATE = realCommRecvData.GetItem(0, 1);		//��������, �ŷ�����
CString strTRADE_DATE = realCommRecvData.GetItem(0, 2);		//����
CString strTRADE_TIME = realCommRecvData.GetItem(0, 3);		//�ð�
CString strKTRADE_DATE = realCommRecvData.GetItem(0, 4);		//�ѱ�����
CString strKTRADE_TIME = realCommRecvData.GetItem(0, 5);		//�ѱ��ð�
CString strRPT_SEQ = realCommRecvData.GetItem(0, 6);		//seq
CString strGLOBEX_TP = realCommRecvData.GetItem(0, 7);		//�����屸��
CString strTRDPRC_1 = realCommRecvData.GetItem(0, 8);		//���簡
CString strTRDPRC_1_CLR = realCommRecvData.GetItem(0, 9);		//[TRDPRC_1]������(+���, -�϶�)
CString strNETCHNG_CLS = realCommRecvData.GetItem(0, 10);		//���ϴ�񱸺�
CString strNETCHNG_1 = realCommRecvData.GetItem(0, 11);		//���ϴ��
CString strNETCHNG_1_CLR = realCommRecvData.GetItem(0, 12);		//[NETCHNG_1]������(+���, -�϶�)
CString strPCTCHNG_1 = realCommRecvData.GetItem(0, 13);		//���ϴ����
CString strPCTCHNG_1_CLR = realCommRecvData.GetItem(0, 14);		//[PCTCHNG_1]������(+���, -�϶�)
CString strTRDVOL_1 = realCommRecvData.GetItem(0, 15);		//ü�����
CString strTRDVOL_1_CLR = realCommRecvData.GetItem(0, 16);		//[TRDVOL_1]������(+���, -�϶�)
CString strACVOL_1 = realCommRecvData.GetItem(0, 17);		//����ü�����
CString strOPEN_PRC = realCommRecvData.GetItem(0, 18);		//�ð�
CString strOPEN_PRC_CLR = realCommRecvData.GetItem(0, 19);		//[OPEN_PRC]������(+���, -�϶�)
CString strHIGH_1 = realCommRecvData.GetItem(0, 20);		//��
CString strHIGH_1_CLR = realCommRecvData.GetItem(0, 21);		//[HIGH_1]������(+���, -�϶�)
CString strLOW_1 = realCommRecvData.GetItem(0, 22);		//����
CString strLOW_1_CLR = realCommRecvData.GetItem(0, 23);		//[LOW_1]������(+���, -�϶�)
CString strOPEN_TIME = realCommRecvData.GetItem(0, 24);		//�ð��ð�
CString strHIGH_TIME = realCommRecvData.GetItem(0, 25);		//���ð�
CString strLOW_TIME = realCommRecvData.GetItem(0, 26);		//�����ð�
CString strBID_EXEC_SUM = realCommRecvData.GetItem(0, 27);		//���� ����ü�����(�ż�����)
CString strASK_EXEC_SUM = realCommRecvData.GetItem(0, 28);		//���� ����ü�����(�ŵ�����)
CString strBOH_EXEC_SUM = realCommRecvData.GetItem(0, 29);		//���� ����ü�����(����)
CString strEX_BEST_BID1 = realCommRecvData.GetItem(0, 30);		//ü��� �ż� 1ȣ��(�ŷ���)
CString strEX_BEST_BID1_CLR = realCommRecvData.GetItem(0, 31);		//[EX_BEST_BID1]������(+���, -�϶�)
CString strEX_BEST_ASK1 = realCommRecvData.GetItem(0, 32);		//ü��� �ŵ� 1ȣ��(�ŷ���)
CString strEX_BEST_ASK1_CLR = realCommRecvData.GetItem(0, 33);		//[EX_BEST_ASK1]������(+���, -�϶�)
CString strEX_BEST_BSIZ1 = realCommRecvData.GetItem(0, 34);		//ü��� �ż� 1����(�ŷ���)
CString strEX_BEST_ASIZ1 = realCommRecvData.GetItem(0, 35);		//ü��� �ŵ� 1����(�ŷ���)
CString strOPENINTEREST = realCommRecvData.GetItem(0, 36);		//�̰�����
CString strOP_NETCHNG_1 = realCommRecvData.GetItem(0, 37);		//��ü�ᷮ���
