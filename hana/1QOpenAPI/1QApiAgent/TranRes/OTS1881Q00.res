BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1881Q00, TR_NAME=�����ֹ����ɱݼ�����ȸ���ݸż�, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1881Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=���º�й�ȣ;
			 INDEX=3, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=4, ITEM=ORDR_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=�ֹ�ȣ�������ڵ�;
			 INDEX=5, ITEM=HPE_PRC, TYPE=string, SIZE=19, CAPTION=�������;
			 INDEX=6, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ü�����ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1881Q00_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=WMY_GRD_NM, TYPE=string, SIZE=40, CAPTION=���űݵ�޸�;
			 INDEX=1, ITEM=ITM_WMY_RT, TYPE=string, SIZE=4, CAPTION=�������ű���;
			 INDEX=2, ITEM=GA_ITM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=A��������ֹ����ɱݾ�;
			 INDEX=3, ITEM=GB_ITM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=B��������ֹ����ɱݾ�;
			 INDEX=4, ITEM=GC_ITM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=C��������ֹ����ɱݾ�;
			 INDEX=5, ITEM=GE_ITM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=E��������ֹ����ɱݾ�;
			 INDEX=6, ITEM=GA_ITM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=A��������ֹ����ɼ���;
			 INDEX=7, ITEM=GB_ITM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=B��������ֹ����ɼ���;
			 INDEX=8, ITEM=GC_ITM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=C��������ֹ����ɼ���;
			 INDEX=9, ITEM=GE_ITM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=E��������ֹ����ɼ���;
			 INDEX=10, ITEM=MINM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=�ּ��ֹ����ɱݾ�;
			 INDEX=11, ITEM=MINM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=�ּ��ֹ����ɼ���;
			 INDEX=12, ITEM=ORDR_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=�ֹ���������;
			 INDEX=13, ITEM=ORDR_PSBL_SBST_AMT, TYPE=string, SIZE=19, CAPTION=�ֹ����ɴ��ݾ�;
			 INDEX=14, ITEM=BFDT_RETRD_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=������ŸŰ�������;
			 INDEX=15, ITEM=TDAY_RETRD_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=������ŸŰ�������;
			 INDEX=16, ITEM=BFDT_RETRD_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=������ŸŰ��ɱݾ�;
			 INDEX=17, ITEM=TDAY_RETRD_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=������ŸŰ��ɱݾ�;
			 INDEX=18, ITEM=ADIT_MRTG_CSH, TYPE=string, SIZE=19, CAPTION=�߰��㺸����;
			 INDEX=19, ITEM=MRTG_CSH, TYPE=string, SIZE=19, CAPTION=�㺸����;
			 INDEX=20, ITEM=DACA, TYPE=string, SIZE=19, CAPTION=������;
			 INDEX=21, ITEM=SBST_PRC_STDR_SBST_AMT, TYPE=string, SIZE=19, CAPTION=��밡�ݱ��ش��ݾ�;
			 INDEX=22, ITEM=CSH_WMY, TYPE=string, SIZE=19, CAPTION=�������ű�;
			 INDEX=23, ITEM=SBST_PRC_STDR_SBST_WMY, TYPE=string, SIZE=19, CAPTION=��밡�ݱ��ش�����ű�;
			 INDEX=24, ITEM=MXM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=�ִ��ֹ����ɼ���;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strACNT_PWD;		//���º�й�ȣ
CString strPRDT_CD;		//��ǰ�ڵ�
CString strORDR_NMPR_DCD;		//�ֹ�ȣ�������ڵ�
CString strHPE_PRC;		//�������
CString strCOMM_MDIA_DCD;		//��Ÿ�ü�����ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "ORDR_NMPR_DCD", strORDR_NMPR_DCD);		//�ֹ�ȣ�������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "HPE_PRC", strHPE_PRC);		//�������
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q00", "OTS1881Q00_in", "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//��Ÿ�ü�����ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strWMY_GRD_NM = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "WMY_GRD_NM", 0);		//���űݵ�޸�
CString strITM_WMY_RT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "ITM_WMY_RT", 0);		//�������ű���
CString strGA_ITM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GA_ITM_ORDR_PSBL_AMT", 0);		//A��������ֹ����ɱݾ�
CString strGB_ITM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GB_ITM_ORDR_PSBL_AMT", 0);		//B��������ֹ����ɱݾ�
CString strGC_ITM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GC_ITM_ORDR_PSBL_AMT", 0);		//C��������ֹ����ɱݾ�
CString strGE_ITM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GE_ITM_ORDR_PSBL_AMT", 0);		//E��������ֹ����ɱݾ�
CString strGA_ITM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GA_ITM_ORDR_PSBL_QNT", 0);		//A��������ֹ����ɼ���
CString strGB_ITM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GB_ITM_ORDR_PSBL_QNT", 0);		//B��������ֹ����ɼ���
CString strGC_ITM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GC_ITM_ORDR_PSBL_QNT", 0);		//C��������ֹ����ɼ���
CString strGE_ITM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "GE_ITM_ORDR_PSBL_QNT", 0);		//E��������ֹ����ɼ���
CString strMINM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "MINM_ORDR_PSBL_AMT", 0);		//�ּ��ֹ����ɱݾ�
CString strMINM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "MINM_ORDR_PSBL_QNT", 0);		//�ּ��ֹ����ɼ���
CString strORDR_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "ORDR_PSBL_CSH", 0);		//�ֹ���������
CString strORDR_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "ORDR_PSBL_SBST_AMT", 0);		//�ֹ����ɴ��ݾ�
CString strBFDT_RETRD_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "BFDT_RETRD_PSBL_CSH", 0);		//������ŸŰ�������
CString strTDAY_RETRD_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "TDAY_RETRD_PSBL_CSH", 0);		//������ŸŰ�������
CString strBFDT_RETRD_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "BFDT_RETRD_PSBL_AMT", 0);		//������ŸŰ��ɱݾ�
CString strTDAY_RETRD_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "TDAY_RETRD_PSBL_AMT", 0);		//������ŸŰ��ɱݾ�
CString strADIT_MRTG_CSH = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "ADIT_MRTG_CSH", 0);		//�߰��㺸����
CString strMRTG_CSH = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "MRTG_CSH", 0);		//�㺸����
CString strDACA = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "DACA", 0);		//������
CString strSBST_PRC_STDR_SBST_AMT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "SBST_PRC_STDR_SBST_AMT", 0);		//��밡�ݱ��ش��ݾ�
CString strCSH_WMY = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "CSH_WMY", 0);		//�������ű�
CString strSBST_PRC_STDR_SBST_WMY = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "SBST_PRC_STDR_SBST_WMY", 0);		//��밡�ݱ��ش�����ű�
CString strMXM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q00", "OTS1881Q00_out", "MXM_ORDR_PSBL_QNT", 0);		//�ִ��ֹ����ɼ���
