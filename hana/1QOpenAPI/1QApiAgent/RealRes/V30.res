BEGIN_FUNCTION_MAP
	REAL_TYPE=144, REAL_NAME=V30, DESCRIPTION=�ؿ��ֽ� ü��;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SYMBOL, TYPE=string, SIZE=18, KEY=1, CAPTION=�����ڵ�, FID=2730;
			 INDEX=1, ITEM=BUSIDATE, TYPE=string, SIZE=8, KEY=0, CAPTION=������������, FID=0;
			 INDEX=2, ITEM=LOCDATE, TYPE=string, SIZE=8, KEY=0, CAPTION=��������, FID=9;
			 INDEX=3, ITEM=LOCTIME, TYPE=string, SIZE=6, KEY=0, CAPTION=�����ð�, FID=8;
			 INDEX=4, ITEM=KORDATE, TYPE=string, SIZE=8, KEY=0, CAPTION=�ѱ�����, FID=1173;
			 INDEX=5, ITEM=KORTIME, TYPE=string, SIZE=6, KEY=0, CAPTION=�ѱ��ð�, FID=1174;
			 INDEX=6, ITEM=OPEN, TYPE=string, SIZE=20, KEY=0, CAPTION=�ð�, FID=13;
			 INDEX=7, ITEM=OPEN_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPEN]������(+���, -�϶�), FID=0;
			 INDEX=8, ITEM=HIGH, TYPE=string, SIZE=20, KEY=0, CAPTION=��, FID=14;
			 INDEX=9, ITEM=HIGH_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[HIGH]������(+���, -�϶�), FID=0;
			 INDEX=10, ITEM=LOW, TYPE=string, SIZE=20, KEY=0, CAPTION=����, FID=15;
			 INDEX=11, ITEM=LOW_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LOW]������(+���, -�϶�), FID=0;
			 INDEX=12, ITEM=LAST, TYPE=string, SIZE=20, KEY=0, CAPTION=���簡, FID=4;
			 INDEX=13, ITEM=LAST_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LAST]������(+���, -�϶�), FID=0;
			 INDEX=14, ITEM=SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=����ȣ, FID=6;
			 INDEX=15, ITEM=DIFF, TYPE=string, SIZE=20, KEY=0, CAPTION=���ϴ��, FID=5;
			 INDEX=16, ITEM=DIFF_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[DIFF]������(+���, -�϶�), FID=0;
			 INDEX=17, ITEM=RATE, TYPE=string, SIZE=20, KEY=0, CAPTION=�����, FID=7;
			 INDEX=18, ITEM=RATE_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RATE]������(+���, -�϶�), FID=0;
			 INDEX=19, ITEM=BID, TYPE=string, SIZE=20, KEY=0, CAPTION=�ż�ȣ��, FID=39;
			 INDEX=20, ITEM=BID_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BID]������(+���, -�϶�), FID=0;
			 INDEX=21, ITEM=BIDSIZE, TYPE=string, SIZE=12, KEY=0, CAPTION=�ż��ܷ�, FID=73;
			 INDEX=22, ITEM=ASK, TYPE=string, SIZE=20, KEY=0, CAPTION=�ŵ�ȣ��, FID=29;
			 INDEX=23, ITEM=ASK_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASK]������(+���, -�϶�), FID=0;
			 INDEX=24, ITEM=ASKSIZE, TYPE=string, SIZE=12, KEY=0, CAPTION=�ŵ��ܷ�, FID=63;
			 INDEX=25, ITEM=EXEVOL, TYPE=string, SIZE=12, KEY=0, CAPTION=ü�ᷮ, FID=83;
			 INDEX=26, ITEM=EXEVOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[EXEVOL]������(+���, -�϶�), FID=0;
			 INDEX=27, ITEM=VOLUME, TYPE=string, SIZE=18, KEY=0, CAPTION=�����ŷ���, FID=11;
			 INDEX=28, ITEM=AMOUNT, TYPE=string, SIZE=18, KEY=0, CAPTION=�����ŷ����, FID=0;
			 INDEX=29, ITEM=SESSION_ID, TYPE=string, SIZE=1, KEY=0, CAPTION=�屸��, FID=0;
			 INDEX=30, ITEM=BID_EXEVOL_SUM, TYPE=string, SIZE=18, KEY=0, CAPTION=�ż�����ü�ᷮ, FID=0;
			 INDEX=31, ITEM=ASK_EXEVOL_SUM, TYPE=string, SIZE=18, KEY=0, CAPTION=�ŵ�����ü�ᷮ, FID=0;
			 INDEX=32, ITEM=RLTV, TYPE=string, SIZE=18, KEY=0, CAPTION=ü�ᰭ��, FID=0;
			 INDEX=33, ITEM=RLTV_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RLTV]������(+���, -�϶�), FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 ���� ���Ǹ� ���� GetRealOutputData �޼ҵ� MFC �ҽ� ���ø�
 **********************************************/
CString strSYMBOL = m_CommAgent.GetRealOutputData("V30", "SYMBOL");		//�����ڵ�
CString strBUSIDATE = m_CommAgent.GetRealOutputData("V30", "BUSIDATE");		//������������
CString strLOCDATE = m_CommAgent.GetRealOutputData("V30", "LOCDATE");		//��������
CString strLOCTIME = m_CommAgent.GetRealOutputData("V30", "LOCTIME");		//�����ð�
CString strKORDATE = m_CommAgent.GetRealOutputData("V30", "KORDATE");		//�ѱ�����
CString strKORTIME = m_CommAgent.GetRealOutputData("V30", "KORTIME");		//�ѱ��ð�
CString strOPEN = m_CommAgent.GetRealOutputData("V30", "OPEN");		//�ð�
CString strOPEN_CLR = m_CommAgent.GetRealOutputData("V30", "OPEN_CLR");		//[OPEN]������(+���, -�϶�)
CString strHIGH = m_CommAgent.GetRealOutputData("V30", "HIGH");		//��
CString strHIGH_CLR = m_CommAgent.GetRealOutputData("V30", "HIGH_CLR");		//[HIGH]������(+���, -�϶�)
CString strLOW = m_CommAgent.GetRealOutputData("V30", "LOW");		//����
CString strLOW_CLR = m_CommAgent.GetRealOutputData("V30", "LOW_CLR");		//[LOW]������(+���, -�϶�)
CString strLAST = m_CommAgent.GetRealOutputData("V30", "LAST");		//���簡
CString strLAST_CLR = m_CommAgent.GetRealOutputData("V30", "LAST_CLR");		//[LAST]������(+���, -�϶�)
CString strSIGN = m_CommAgent.GetRealOutputData("V30", "SIGN");		//����ȣ
CString strDIFF = m_CommAgent.GetRealOutputData("V30", "DIFF");		//���ϴ��
CString strDIFF_CLR = m_CommAgent.GetRealOutputData("V30", "DIFF_CLR");		//[DIFF]������(+���, -�϶�)
CString strRATE = m_CommAgent.GetRealOutputData("V30", "RATE");		//�����
CString strRATE_CLR = m_CommAgent.GetRealOutputData("V30", "RATE_CLR");		//[RATE]������(+���, -�϶�)
CString strBID = m_CommAgent.GetRealOutputData("V30", "BID");		//�ż�ȣ��
CString strBID_CLR = m_CommAgent.GetRealOutputData("V30", "BID_CLR");		//[BID]������(+���, -�϶�)
CString strBIDSIZE = m_CommAgent.GetRealOutputData("V30", "BIDSIZE");		//�ż��ܷ�
CString strASK = m_CommAgent.GetRealOutputData("V30", "ASK");		//�ŵ�ȣ��
CString strASK_CLR = m_CommAgent.GetRealOutputData("V30", "ASK_CLR");		//[ASK]������(+���, -�϶�)
CString strASKSIZE = m_CommAgent.GetRealOutputData("V30", "ASKSIZE");		//�ŵ��ܷ�
CString strEXEVOL = m_CommAgent.GetRealOutputData("V30", "EXEVOL");		//ü�ᷮ
CString strEXEVOL_CLR = m_CommAgent.GetRealOutputData("V30", "EXEVOL_CLR");		//[EXEVOL]������(+���, -�϶�)
CString strVOLUME = m_CommAgent.GetRealOutputData("V30", "VOLUME");		//�����ŷ���
CString strAMOUNT = m_CommAgent.GetRealOutputData("V30", "AMOUNT");		//�����ŷ����
CString strSESSION_ID = m_CommAgent.GetRealOutputData("V30", "SESSION_ID");		//�屸��
CString strBID_EXEVOL_SUM = m_CommAgent.GetRealOutputData("V30", "BID_EXEVOL_SUM");		//�ż�����ü�ᷮ
CString strASK_EXEVOL_SUM = m_CommAgent.GetRealOutputData("V30", "ASK_EXEVOL_SUM");		//�ŵ�����ü�ᷮ
CString strRLTV = m_CommAgent.GetRealOutputData("V30", "RLTV");		//ü�ᰭ��
CString strRLTV_CLR = m_CommAgent.GetRealOutputData("V30", "RLTV_CLR");		//[RLTV]������(+���, -�϶�)




/**********************************************
 ���� ���Ǹ� ���� �޸� �ε��� ���� �ҽ� ���ø�(C++������ ��� ����)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strSYMBOL = realCommRecvData.GetItem(0, 0);		//�����ڵ�
CString strBUSIDATE = realCommRecvData.GetItem(0, 1);		//������������
CString strLOCDATE = realCommRecvData.GetItem(0, 2);		//��������
CString strLOCTIME = realCommRecvData.GetItem(0, 3);		//�����ð�
CString strKORDATE = realCommRecvData.GetItem(0, 4);		//�ѱ�����
CString strKORTIME = realCommRecvData.GetItem(0, 5);		//�ѱ��ð�
CString strOPEN = realCommRecvData.GetItem(0, 6);		//�ð�
CString strOPEN_CLR = realCommRecvData.GetItem(0, 7);		//[OPEN]������(+���, -�϶�)
CString strHIGH = realCommRecvData.GetItem(0, 8);		//��
CString strHIGH_CLR = realCommRecvData.GetItem(0, 9);		//[HIGH]������(+���, -�϶�)
CString strLOW = realCommRecvData.GetItem(0, 10);		//����
CString strLOW_CLR = realCommRecvData.GetItem(0, 11);		//[LOW]������(+���, -�϶�)
CString strLAST = realCommRecvData.GetItem(0, 12);		//���簡
CString strLAST_CLR = realCommRecvData.GetItem(0, 13);		//[LAST]������(+���, -�϶�)
CString strSIGN = realCommRecvData.GetItem(0, 14);		//����ȣ
CString strDIFF = realCommRecvData.GetItem(0, 15);		//���ϴ��
CString strDIFF_CLR = realCommRecvData.GetItem(0, 16);		//[DIFF]������(+���, -�϶�)
CString strRATE = realCommRecvData.GetItem(0, 17);		//�����
CString strRATE_CLR = realCommRecvData.GetItem(0, 18);		//[RATE]������(+���, -�϶�)
CString strBID = realCommRecvData.GetItem(0, 19);		//�ż�ȣ��
CString strBID_CLR = realCommRecvData.GetItem(0, 20);		//[BID]������(+���, -�϶�)
CString strBIDSIZE = realCommRecvData.GetItem(0, 21);		//�ż��ܷ�
CString strASK = realCommRecvData.GetItem(0, 22);		//�ŵ�ȣ��
CString strASK_CLR = realCommRecvData.GetItem(0, 23);		//[ASK]������(+���, -�϶�)
CString strASKSIZE = realCommRecvData.GetItem(0, 24);		//�ŵ��ܷ�
CString strEXEVOL = realCommRecvData.GetItem(0, 25);		//ü�ᷮ
CString strEXEVOL_CLR = realCommRecvData.GetItem(0, 26);		//[EXEVOL]������(+���, -�϶�)
CString strVOLUME = realCommRecvData.GetItem(0, 27);		//�����ŷ���
CString strAMOUNT = realCommRecvData.GetItem(0, 28);		//�����ŷ����
CString strSESSION_ID = realCommRecvData.GetItem(0, 29);		//�屸��
CString strBID_EXEVOL_SUM = realCommRecvData.GetItem(0, 30);		//�ż�����ü�ᷮ
CString strASK_EXEVOL_SUM = realCommRecvData.GetItem(0, 31);		//�ŵ�����ü�ᷮ
CString strRLTV = realCommRecvData.GetItem(0, 32);		//ü�ᰭ��
CString strRLTV_CLR = realCommRecvData.GetItem(0, 33);		//[RLTV]������(+���, -�϶�)
