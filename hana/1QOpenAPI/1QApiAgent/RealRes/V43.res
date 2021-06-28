BEGIN_FUNCTION_MAP
	REAL_TYPE=167, REAL_NAME=V43, DESCRIPTION=�̵��ϸ� FX ü��;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SYMBOL, TYPE=string, SIZE=16, KEY=1, CAPTION=�����ڵ�, FID=1;
			 INDEX=1, ITEM=XYMD, TYPE=string, SIZE=8, KEY=0, CAPTION=�ŷ�����(��������), FID=9;
			 INDEX=2, ITEM=XHMS, TYPE=string, SIZE=6, KEY=0, CAPTION=�ŷ��ð�(�����ð�), FID=8;
			 INDEX=3, ITEM=KYMD, TYPE=string, SIZE=8, KEY=0, CAPTION=�ŷ�����(�ѱ�����), FID=1173;
			 INDEX=4, ITEM=KHMS, TYPE=string, SIZE=6, KEY=0, CAPTION=�ŷ��ð�(�ѱ��ð�), FID=1174;
			 INDEX=5, ITEM=OPEN, TYPE=string, SIZE=18, KEY=0, CAPTION=�ð�, FID=13;
			 INDEX=6, ITEM=OPEN_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPEN]������(+���, -�϶�), FID=0;
			 INDEX=7, ITEM=HIGH, TYPE=string, SIZE=18, KEY=0, CAPTION=��, FID=14;
			 INDEX=8, ITEM=HIGH_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[HIGH]������(+���, -�϶�), FID=0;
			 INDEX=9, ITEM=LOW, TYPE=string, SIZE=18, KEY=0, CAPTION=����, FID=15;
			 INDEX=10, ITEM=LOW_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LOW]������(+���, -�϶�), FID=0;
			 INDEX=11, ITEM=LAST, TYPE=string, SIZE=18, KEY=0, CAPTION=���簡, FID=4;
			 INDEX=12, ITEM=LAST_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LAST]������(+���, -�϶�), FID=0;
			 INDEX=13, ITEM=SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=����ȣ, FID=6;
			 INDEX=14, ITEM=DIFF, TYPE=string, SIZE=18, KEY=0, CAPTION=���ϴ��, FID=5;
			 INDEX=15, ITEM=DIFF_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[DIFF]������(+���, -�϶�), FID=0;
			 INDEX=16, ITEM=RATE, TYPE=string, SIZE=18, KEY=0, CAPTION=�����, FID=7;
			 INDEX=17, ITEM=RATE_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[RATE]������(+���, -�϶�), FID=0;
			 INDEX=18, ITEM=MSGA, TYPE=string, SIZE=18, KEY=0, CAPTION=�ż�ȣ��, FID=39;
			 INDEX=19, ITEM=MSGA_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[MSGA]������(+���, -�϶�), FID=0;
			 INDEX=20, ITEM=STIM, TYPE=string, SIZE=6, KEY=0, CAPTION=�ż�ȣ���ð�, FID=0;
			 INDEX=21, ITEM=MDGA, TYPE=string, SIZE=18, KEY=0, CAPTION=�ŵ�ȣ��, FID=29;
			 INDEX=22, ITEM=MDGA_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[MDGA]������(+���, -�϶�), FID=0;
			 INDEX=23, ITEM=DTIM, TYPE=string, SIZE=6, KEY=0, CAPTION=�ŵ�ȣ���ð�, FID=0;
			 INDEX=24, ITEM=BANK, TYPE=string, SIZE=4, KEY=0, CAPTION=Contributor code, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 ���� ���Ǹ� ���� GetRealOutputData �޼ҵ� MFC �ҽ� ���ø�
 **********************************************/
CString strSYMBOL = m_CommAgent.GetRealOutputData("V43", "SYMBOL");		//�����ڵ�
CString strXYMD = m_CommAgent.GetRealOutputData("V43", "XYMD");		//�ŷ�����(��������)
CString strXHMS = m_CommAgent.GetRealOutputData("V43", "XHMS");		//�ŷ��ð�(�����ð�)
CString strKYMD = m_CommAgent.GetRealOutputData("V43", "KYMD");		//�ŷ�����(�ѱ�����)
CString strKHMS = m_CommAgent.GetRealOutputData("V43", "KHMS");		//�ŷ��ð�(�ѱ��ð�)
CString strOPEN = m_CommAgent.GetRealOutputData("V43", "OPEN");		//�ð�
CString strOPEN_CLR = m_CommAgent.GetRealOutputData("V43", "OPEN_CLR");		//[OPEN]������(+���, -�϶�)
CString strHIGH = m_CommAgent.GetRealOutputData("V43", "HIGH");		//��
CString strHIGH_CLR = m_CommAgent.GetRealOutputData("V43", "HIGH_CLR");		//[HIGH]������(+���, -�϶�)
CString strLOW = m_CommAgent.GetRealOutputData("V43", "LOW");		//����
CString strLOW_CLR = m_CommAgent.GetRealOutputData("V43", "LOW_CLR");		//[LOW]������(+���, -�϶�)
CString strLAST = m_CommAgent.GetRealOutputData("V43", "LAST");		//���簡
CString strLAST_CLR = m_CommAgent.GetRealOutputData("V43", "LAST_CLR");		//[LAST]������(+���, -�϶�)
CString strSIGN = m_CommAgent.GetRealOutputData("V43", "SIGN");		//����ȣ
CString strDIFF = m_CommAgent.GetRealOutputData("V43", "DIFF");		//���ϴ��
CString strDIFF_CLR = m_CommAgent.GetRealOutputData("V43", "DIFF_CLR");		//[DIFF]������(+���, -�϶�)
CString strRATE = m_CommAgent.GetRealOutputData("V43", "RATE");		//�����
CString strRATE_CLR = m_CommAgent.GetRealOutputData("V43", "RATE_CLR");		//[RATE]������(+���, -�϶�)
CString strMSGA = m_CommAgent.GetRealOutputData("V43", "MSGA");		//�ż�ȣ��
CString strMSGA_CLR = m_CommAgent.GetRealOutputData("V43", "MSGA_CLR");		//[MSGA]������(+���, -�϶�)
CString strSTIM = m_CommAgent.GetRealOutputData("V43", "STIM");		//�ż�ȣ���ð�
CString strMDGA = m_CommAgent.GetRealOutputData("V43", "MDGA");		//�ŵ�ȣ��
CString strMDGA_CLR = m_CommAgent.GetRealOutputData("V43", "MDGA_CLR");		//[MDGA]������(+���, -�϶�)
CString strDTIM = m_CommAgent.GetRealOutputData("V43", "DTIM");		//�ŵ�ȣ���ð�
CString strBANK = m_CommAgent.GetRealOutputData("V43", "BANK");		//Contributor code




/**********************************************
 ���� ���Ǹ� ���� �޸� �ε��� ���� �ҽ� ���ø�(C++������ ��� ����)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strSYMBOL = realCommRecvData.GetItem(0, 0);		//�����ڵ�
CString strXYMD = realCommRecvData.GetItem(0, 1);		//�ŷ�����(��������)
CString strXHMS = realCommRecvData.GetItem(0, 2);		//�ŷ��ð�(�����ð�)
CString strKYMD = realCommRecvData.GetItem(0, 3);		//�ŷ�����(�ѱ�����)
CString strKHMS = realCommRecvData.GetItem(0, 4);		//�ŷ��ð�(�ѱ��ð�)
CString strOPEN = realCommRecvData.GetItem(0, 5);		//�ð�
CString strOPEN_CLR = realCommRecvData.GetItem(0, 6);		//[OPEN]������(+���, -�϶�)
CString strHIGH = realCommRecvData.GetItem(0, 7);		//��
CString strHIGH_CLR = realCommRecvData.GetItem(0, 8);		//[HIGH]������(+���, -�϶�)
CString strLOW = realCommRecvData.GetItem(0, 9);		//����
CString strLOW_CLR = realCommRecvData.GetItem(0, 10);		//[LOW]������(+���, -�϶�)
CString strLAST = realCommRecvData.GetItem(0, 11);		//���簡
CString strLAST_CLR = realCommRecvData.GetItem(0, 12);		//[LAST]������(+���, -�϶�)
CString strSIGN = realCommRecvData.GetItem(0, 13);		//����ȣ
CString strDIFF = realCommRecvData.GetItem(0, 14);		//���ϴ��
CString strDIFF_CLR = realCommRecvData.GetItem(0, 15);		//[DIFF]������(+���, -�϶�)
CString strRATE = realCommRecvData.GetItem(0, 16);		//�����
CString strRATE_CLR = realCommRecvData.GetItem(0, 17);		//[RATE]������(+���, -�϶�)
CString strMSGA = realCommRecvData.GetItem(0, 18);		//�ż�ȣ��
CString strMSGA_CLR = realCommRecvData.GetItem(0, 19);		//[MSGA]������(+���, -�϶�)
CString strSTIM = realCommRecvData.GetItem(0, 20);		//�ż�ȣ���ð�
CString strMDGA = realCommRecvData.GetItem(0, 21);		//�ŵ�ȣ��
CString strMDGA_CLR = realCommRecvData.GetItem(0, 22);		//[MDGA]������(+���, -�϶�)
CString strDTIM = realCommRecvData.GetItem(0, 23);		//�ŵ�ȣ���ð�
CString strBANK = realCommRecvData.GetItem(0, 24);		//Contributor code
