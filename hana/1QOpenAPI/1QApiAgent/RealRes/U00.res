BEGIN_FUNCTION_MAP
	REAL_TYPE=28, REAL_NAME=U00, DESCRIPTION=��������ü��;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=BSTP_CLS_CODE, TYPE=string, SIZE=3, KEY=1, CAPTION=���� ���� �ڵ�, FID=0;
			 INDEX=1, ITEM=ANTC_NMIX_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=�������� �����ڵ�, FID=0;
			 INDEX=2, ITEM=BSOP_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=�ǽð�����, FID=9;
			 INDEX=3, ITEM=BSOP_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=�ð�, FID=8;
			 INDEX=4, ITEM=PRPR_NMIX, TYPE=string, SIZE=18, KEY=0, CAPTION=����, FID=4;
			 INDEX=5, ITEM=PRPR_NMIX_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRPR_NMIX]������(+���, -�϶�), FID=0;
			 INDEX=6, ITEM=PRDY_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=���� ��� ��ȣ, FID=6;
			 INDEX=7, ITEM=BSTP_NMIX_PRDY_VRSS, TYPE=string, SIZE=18, KEY=0, CAPTION=���� ���, FID=5;
			 INDEX=8, ITEM=BSTP_NMIX_PRDY_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BSTP_NMIX_PRDY_VRSS]������(+���, -�϶�), FID=0;
			 INDEX=9, ITEM=PRDY_CTRT, TYPE=string, SIZE=18, KEY=0, CAPTION=�����, FID=7;
			 INDEX=10, ITEM=PRDY_CTRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRDY_CTRT]������(+���, -�϶�), FID=0;
			 INDEX=11, ITEM=ACML_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=���� �ŷ���, FID=11;
			 INDEX=12, ITEM=ACML_TR_PBMN, TYPE=string, SIZE=18, KEY=0, CAPTION=���� �ŷ� ���, FID=12;
			 INDEX=13, ITEM=OPRC_NMIX, TYPE=string, SIZE=18, KEY=0, CAPTION=�ð�, FID=13;
			 INDEX=14, ITEM=OPRC_NMIX_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPRC_NMIX]������(+���, -�϶�), FID=0;
			 INDEX=15, ITEM=NMIX_HGPR, TYPE=string, SIZE=18, KEY=0, CAPTION=��, FID=14;
			 INDEX=16, ITEM=NMIX_HGPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NMIX_HGPR]������(+���, -�϶�), FID=0;
			 INDEX=17, ITEM=NMIX_LWPR, TYPE=string, SIZE=18, KEY=0, CAPTION=����, FID=15;
			 INDEX=18, ITEM=NMIX_LWPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NMIX_LWPR]������(+���, -�϶�), FID=0;
			 INDEX=19, ITEM=CNTG_VOL, TYPE=string, SIZE=18, KEY=0, CAPTION=ü�� �ŷ���, FID=83;
			 INDEX=20, ITEM=CNTG_PRGS, TYPE=string, SIZE=10, KEY=0, CAPTION=ü��ƽ����, FID=2655;
			 INDEX=21, ITEM=ANTC_CLS_CODE, TYPE=string, SIZE=1, KEY=0, CAPTION=�������������ڵ�, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 ���� ���Ǹ� ���� GetRealOutputData �޼ҵ� MFC �ҽ� ���ø�
 **********************************************/
CString strBSTP_CLS_CODE = m_CommAgent.GetRealOutputData("U00", "BSTP_CLS_CODE");		//���� ���� �ڵ�
CString strANTC_NMIX_CLS_CODE = m_CommAgent.GetRealOutputData("U00", "ANTC_NMIX_CLS_CODE");		//�������� �����ڵ�
CString strBSOP_DATE = m_CommAgent.GetRealOutputData("U00", "BSOP_DATE");		//�ǽð�����
CString strBSOP_HOUR = m_CommAgent.GetRealOutputData("U00", "BSOP_HOUR");		//�ð�
CString strPRPR_NMIX = m_CommAgent.GetRealOutputData("U00", "PRPR_NMIX");		//����
CString strPRPR_NMIX_CLR = m_CommAgent.GetRealOutputData("U00", "PRPR_NMIX_CLR");		//[PRPR_NMIX]������(+���, -�϶�)
CString strPRDY_VRSS_SIGN = m_CommAgent.GetRealOutputData("U00", "PRDY_VRSS_SIGN");		//���� ��� ��ȣ
CString strBSTP_NMIX_PRDY_VRSS = m_CommAgent.GetRealOutputData("U00", "BSTP_NMIX_PRDY_VRSS");		//���� ���
CString strBSTP_NMIX_PRDY_VRSS_CLR = m_CommAgent.GetRealOutputData("U00", "BSTP_NMIX_PRDY_VRSS_CLR");		//[BSTP_NMIX_PRDY_VRSS]������(+���, -�϶�)
CString strPRDY_CTRT = m_CommAgent.GetRealOutputData("U00", "PRDY_CTRT");		//�����
CString strPRDY_CTRT_CLR = m_CommAgent.GetRealOutputData("U00", "PRDY_CTRT_CLR");		//[PRDY_CTRT]������(+���, -�϶�)
CString strACML_VOL = m_CommAgent.GetRealOutputData("U00", "ACML_VOL");		//���� �ŷ���
CString strACML_TR_PBMN = m_CommAgent.GetRealOutputData("U00", "ACML_TR_PBMN");		//���� �ŷ� ���
CString strOPRC_NMIX = m_CommAgent.GetRealOutputData("U00", "OPRC_NMIX");		//�ð�
CString strOPRC_NMIX_CLR = m_CommAgent.GetRealOutputData("U00", "OPRC_NMIX_CLR");		//[OPRC_NMIX]������(+���, -�϶�)
CString strNMIX_HGPR = m_CommAgent.GetRealOutputData("U00", "NMIX_HGPR");		//��
CString strNMIX_HGPR_CLR = m_CommAgent.GetRealOutputData("U00", "NMIX_HGPR_CLR");		//[NMIX_HGPR]������(+���, -�϶�)
CString strNMIX_LWPR = m_CommAgent.GetRealOutputData("U00", "NMIX_LWPR");		//����
CString strNMIX_LWPR_CLR = m_CommAgent.GetRealOutputData("U00", "NMIX_LWPR_CLR");		//[NMIX_LWPR]������(+���, -�϶�)
CString strCNTG_VOL = m_CommAgent.GetRealOutputData("U00", "CNTG_VOL");		//ü�� �ŷ���
CString strCNTG_PRGS = m_CommAgent.GetRealOutputData("U00", "CNTG_PRGS");		//ü��ƽ����
CString strANTC_CLS_CODE = m_CommAgent.GetRealOutputData("U00", "ANTC_CLS_CODE");		//�������������ڵ�




/**********************************************
 ���� ���Ǹ� ���� �޸� �ε��� ���� �ҽ� ���ø�(C++������ ��� ����)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strBSTP_CLS_CODE = realCommRecvData.GetItem(0, 0);		//���� ���� �ڵ�
CString strANTC_NMIX_CLS_CODE = realCommRecvData.GetItem(0, 1);		//�������� �����ڵ�
CString strBSOP_DATE = realCommRecvData.GetItem(0, 2);		//�ǽð�����
CString strBSOP_HOUR = realCommRecvData.GetItem(0, 3);		//�ð�
CString strPRPR_NMIX = realCommRecvData.GetItem(0, 4);		//����
CString strPRPR_NMIX_CLR = realCommRecvData.GetItem(0, 5);		//[PRPR_NMIX]������(+���, -�϶�)
CString strPRDY_VRSS_SIGN = realCommRecvData.GetItem(0, 6);		//���� ��� ��ȣ
CString strBSTP_NMIX_PRDY_VRSS = realCommRecvData.GetItem(0, 7);		//���� ���
CString strBSTP_NMIX_PRDY_VRSS_CLR = realCommRecvData.GetItem(0, 8);		//[BSTP_NMIX_PRDY_VRSS]������(+���, -�϶�)
CString strPRDY_CTRT = realCommRecvData.GetItem(0, 9);		//�����
CString strPRDY_CTRT_CLR = realCommRecvData.GetItem(0, 10);		//[PRDY_CTRT]������(+���, -�϶�)
CString strACML_VOL = realCommRecvData.GetItem(0, 11);		//���� �ŷ���
CString strACML_TR_PBMN = realCommRecvData.GetItem(0, 12);		//���� �ŷ� ���
CString strOPRC_NMIX = realCommRecvData.GetItem(0, 13);		//�ð�
CString strOPRC_NMIX_CLR = realCommRecvData.GetItem(0, 14);		//[OPRC_NMIX]������(+���, -�϶�)
CString strNMIX_HGPR = realCommRecvData.GetItem(0, 15);		//��
CString strNMIX_HGPR_CLR = realCommRecvData.GetItem(0, 16);		//[NMIX_HGPR]������(+���, -�϶�)
CString strNMIX_LWPR = realCommRecvData.GetItem(0, 17);		//����
CString strNMIX_LWPR_CLR = realCommRecvData.GetItem(0, 18);		//[NMIX_LWPR]������(+���, -�϶�)
CString strCNTG_VOL = realCommRecvData.GetItem(0, 19);		//ü�� �ŷ���
CString strCNTG_PRGS = realCommRecvData.GetItem(0, 20);		//ü��ƽ����
CString strANTC_CLS_CODE = realCommRecvData.GetItem(0, 21);		//�������������ڵ�
