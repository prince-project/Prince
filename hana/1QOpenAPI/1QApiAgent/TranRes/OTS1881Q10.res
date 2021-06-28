BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1881Q10, TR_NAME=�����ֹ����ɱݼ�����ȸ�Ϲݽſ�, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1881Q10_in, INOUT=0, ARRAY=0, ARRINFO=;
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
		REC_NAME=OTS1881Q10_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=WMY_GRD_NM, TYPE=string, SIZE=40, CAPTION=���űݵ�޸�;
			 INDEX=1, ITEM=ITM_WMY_RT, TYPE=string, SIZE=4, CAPTION=�������ű���;
			 INDEX=2, ITEM=GB_ITM_CRDT_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=B�������ſ��ֹ����ɱݾ�;
			 INDEX=3, ITEM=GC_ITM_CRDT_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=C�������ſ��ֹ����ɱݾ�;
			 INDEX=4, ITEM=GB_ITM_CRDT_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=B�������ſ��ֹ����ɼ���;
			 INDEX=5, ITEM=GC_ITM_CRDT_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=C�������ſ��ֹ����ɼ���;
			 INDEX=6, ITEM=CRDT_INCL_MINM_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=�ſ������ּҰ��ɱݾ�;
			 INDEX=7, ITEM=CRDT_INCL_MINM_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=�ſ������ּҰ��ɼ���;
			 INDEX=8, ITEM=MINM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=�ּ��ֹ����ɱݾ�;
			 INDEX=9, ITEM=ORDR_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=�ֹ���������;
			 INDEX=10, ITEM=ORDR_PSBL_SBST_AMT, TYPE=string, SIZE=19, CAPTION=�ֹ����ɴ��ݾ�;
			 INDEX=11, ITEM=BFDT_RETRD_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=������ŸŰ�������;
			 INDEX=12, ITEM=TDAY_RETRD_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=������ŸŰ�������;
			 INDEX=13, ITEM=BFDT_RETRD_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=������ŸŰ��ɱݾ�;
			 INDEX=14, ITEM=TDAY_RETRD_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=������ŸŰ��ɱݾ�;
			 INDEX=15, ITEM=ADIT_MRTG_CSH, TYPE=string, SIZE=19, CAPTION=�߰��㺸����;
			 INDEX=16, ITEM=MRTG_CSH, TYPE=string, SIZE=19, CAPTION=�㺸����;
			 INDEX=17, ITEM=DPST_ASST_AMT, TYPE=string, SIZE=19, CAPTION=��Ź�ڻ�ݾ�;
			 INDEX=18, ITEM=CRDT_RMN_LMT_AMT, TYPE=string, SIZE=19, CAPTION=�ſ��ܿ��ѵ��ݾ�;
			 INDEX=19, ITEM=DACA, TYPE=string, SIZE=19, CAPTION=������;
			 INDEX=20, ITEM=SBST_PRC_STDR_SBST_AMT, TYPE=string, SIZE=19, CAPTION=��밡�ݱ��ش��ݾ�;
			 INDEX=21, ITEM=CSH_WMY, TYPE=string, SIZE=19, CAPTION=�������ű�;
			 INDEX=22, ITEM=SBST_PRC_STDR_SBST_WMY, TYPE=string, SIZE=19, CAPTION=��밡�ݱ��ش�����ű�;
			 INDEX=23, ITEM=MXM_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=�ִ��ֹ����ɼ���;
			 INDEX=24, ITEM=MXM_ORDR_PSBL_AMT, TYPE=string, SIZE=20, CAPTION=�ִ��ֹ����ɱݾ�;
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

m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q10", "OTS1881Q10_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q10", "OTS1881Q10_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q10", "OTS1881Q10_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q10", "OTS1881Q10_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q10", "OTS1881Q10_in", "ORDR_NMPR_DCD", strORDR_NMPR_DCD);		//�ֹ�ȣ�������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q10", "OTS1881Q10_in", "HPE_PRC", strHPE_PRC);		//�������
m_CommAgent.SetTranInputData(nRequestId, "OTS1881Q10", "OTS1881Q10_in", "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//��Ÿ�ü�����ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strWMY_GRD_NM = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "WMY_GRD_NM", 0);		//���űݵ�޸�
CString strITM_WMY_RT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "ITM_WMY_RT", 0);		//�������ű���
CString strGB_ITM_CRDT_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "GB_ITM_CRDT_ORDR_PSBL_AMT", 0);		//B�������ſ��ֹ����ɱݾ�
CString strGC_ITM_CRDT_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "GC_ITM_CRDT_ORDR_PSBL_AMT", 0);		//C�������ſ��ֹ����ɱݾ�
CString strGB_ITM_CRDT_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "GB_ITM_CRDT_ORDR_PSBL_QNT", 0);		//B�������ſ��ֹ����ɼ���
CString strGC_ITM_CRDT_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "GC_ITM_CRDT_ORDR_PSBL_QNT", 0);		//C�������ſ��ֹ����ɼ���
CString strCRDT_INCL_MINM_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "CRDT_INCL_MINM_PSBL_AMT", 0);		//�ſ������ּҰ��ɱݾ�
CString strCRDT_INCL_MINM_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "CRDT_INCL_MINM_PSBL_QNT", 0);		//�ſ������ּҰ��ɼ���
CString strMINM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "MINM_ORDR_PSBL_AMT", 0);		//�ּ��ֹ����ɱݾ�
CString strORDR_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "ORDR_PSBL_CSH", 0);		//�ֹ���������
CString strORDR_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "ORDR_PSBL_SBST_AMT", 0);		//�ֹ����ɴ��ݾ�
CString strBFDT_RETRD_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "BFDT_RETRD_PSBL_CSH", 0);		//������ŸŰ�������
CString strTDAY_RETRD_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "TDAY_RETRD_PSBL_CSH", 0);		//������ŸŰ�������
CString strBFDT_RETRD_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "BFDT_RETRD_PSBL_AMT", 0);		//������ŸŰ��ɱݾ�
CString strTDAY_RETRD_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "TDAY_RETRD_PSBL_AMT", 0);		//������ŸŰ��ɱݾ�
CString strADIT_MRTG_CSH = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "ADIT_MRTG_CSH", 0);		//�߰��㺸����
CString strMRTG_CSH = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "MRTG_CSH", 0);		//�㺸����
CString strDPST_ASST_AMT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "DPST_ASST_AMT", 0);		//��Ź�ڻ�ݾ�
CString strCRDT_RMN_LMT_AMT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "CRDT_RMN_LMT_AMT", 0);		//�ſ��ܿ��ѵ��ݾ�
CString strDACA = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "DACA", 0);		//������
CString strSBST_PRC_STDR_SBST_AMT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "SBST_PRC_STDR_SBST_AMT", 0);		//��밡�ݱ��ش��ݾ�
CString strCSH_WMY = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "CSH_WMY", 0);		//�������ű�
CString strSBST_PRC_STDR_SBST_WMY = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "SBST_PRC_STDR_SBST_WMY", 0);		//��밡�ݱ��ش�����ű�
CString strMXM_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "MXM_ORDR_PSBL_QNT", 0);		//�ִ��ֹ����ɼ���
CString strMXM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1881Q10", "OTS1881Q10_out", "MXM_ORDR_PSBL_AMT", 0);		//�ִ��ֹ����ɱݾ�
