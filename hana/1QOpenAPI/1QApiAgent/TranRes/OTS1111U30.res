BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1111U30, TR_NAME=���������峻�ֽ��ֹ�����, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1111U30_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=3, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=���������ڵ�;
			 INDEX=4, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=���ֹ��Ϸù�ȣ;
			 INDEX=5, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=���º�й�ȣ;
			 INDEX=6, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=7, ITEM=NMPR_DCD, TYPE=string, SIZE=2, CAPTION=ȣ�������ڵ�;
			 INDEX=8, ITEM=ORDR_CND_DCD, TYPE=string, SIZE=2, CAPTION=�ֹ����Ǳ����ڵ�;
			 INDEX=9, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=10, ITEM=ORDR_UNPR, TYPE=string, SIZE=19, CAPTION=�ֹ��ܰ�;
			 INDEX=11, ITEM=EMR_ORDR_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=����ֹ���ü�����ڵ�;
			 INDEX=12, ITEM=GRUP_ODNO, TYPE=string, SIZE=13, CAPTION=�׷��ֹ���ȣ;
			 INDEX=13, ITEM=BSK_ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ٽ����ֹ��Ϸù�ȣ;
			 INDEX=14, ITEM=MTS_KEY, TYPE=string, SIZE=7, CAPTION=MTSŰ;
			 INDEX=15, ITEM=HTS_ORDR_PSBL_MDIA_YN, TYPE=string, SIZE=1, CAPTION=HTS�ֹ����ɸ�ü����;
			 INDEX=16, ITEM=NMPR_PROP_XCP_YN, TYPE=string, SIZE=1, CAPTION=ȣ�����������ܿ���;
			 INDEX=17, ITEM=ORDR_ANGT_ORDR_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ��븮���ֹ������ڵ�;
			 INDEX=18, ITEM=BOND_ORDR_OR_UN_DCD, TYPE=string, SIZE=1, CAPTION=ä���ֹ������������ڵ�;
			 INDEX=19, ITEM=PRT_ALL_DCD, TYPE=string, SIZE=1, CAPTION=�Ϻ���ü�����ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1111U30_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ֹ��Ϸù�ȣ;
			 INDEX=1, ITEM=MSG_CD, TYPE=string, SIZE=6, CAPTION=�޽����ڵ�;
			 INDEX=2, ITEM=MSG_CTNS, TYPE=string, SIZE=500, CAPTION=�޽�������;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strORDR_DT;		//�ֹ�����
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strMNGM_BDCD;		//���������ڵ�
CString strOR_ORDR_SN;		//���ֹ��Ϸù�ȣ
CString strACNT_PWD;		//���º�й�ȣ
CString strPRDT_CD;		//��ǰ�ڵ�
CString strNMPR_DCD;		//ȣ�������ڵ�
CString strORDR_CND_DCD;		//�ֹ����Ǳ����ڵ�
CString strORDR_QNT;		//�ֹ�����
CString strORDR_UNPR;		//�ֹ��ܰ�
CString strEMR_ORDR_MDIA_DCD;		//����ֹ���ü�����ڵ�
CString strGRUP_ODNO;		//�׷��ֹ���ȣ
CString strBSK_ORDR_SN;		//�ٽ����ֹ��Ϸù�ȣ
CString strMTS_KEY;		//MTSŰ
CString strHTS_ORDR_PSBL_MDIA_YN;		//HTS�ֹ����ɸ�ü����
CString strNMPR_PROP_XCP_YN;		//ȣ�����������ܿ���
CString strORDR_ANGT_ORDR_DCD;		//�ֹ��븮���ֹ������ڵ�
CString strBOND_ORDR_OR_UN_DCD;		//ä���ֹ������������ڵ�
CString strPRT_ALL_DCD;		//�Ϻ���ü�����ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "ORDR_DT", strORDR_DT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "MNGM_BDCD", strMNGM_BDCD);		//���������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "OR_ORDR_SN", strOR_ORDR_SN);		//���ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "NMPR_DCD", strNMPR_DCD);		//ȣ�������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "ORDR_CND_DCD", strORDR_CND_DCD);		//�ֹ����Ǳ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "ORDR_UNPR", strORDR_UNPR);		//�ֹ��ܰ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//����ֹ���ü�����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "GRUP_ODNO", strGRUP_ODNO);		//�׷��ֹ���ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "BSK_ORDR_SN", strBSK_ORDR_SN);		//�ٽ����ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "MTS_KEY", strMTS_KEY);		//MTSŰ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "HTS_ORDR_PSBL_MDIA_YN", strHTS_ORDR_PSBL_MDIA_YN);		//HTS�ֹ����ɸ�ü����
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "NMPR_PROP_XCP_YN", strNMPR_PROP_XCP_YN);		//ȣ�����������ܿ���
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//�ֹ��븮���ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "BOND_ORDR_OR_UN_DCD", strBOND_ORDR_OR_UN_DCD);		//ä���ֹ������������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U30", "OTS1111U30_in", "PRT_ALL_DCD", strPRT_ALL_DCD);		//�Ϻ���ü�����ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS1111U30", "OTS1111U30_out", "ORDR_SN", 0);		//�ֹ��Ϸù�ȣ
CString strMSG_CD = m_CommAgent.GetTranOutputData("OTS1111U30", "OTS1111U30_out", "MSG_CD", 0);		//�޽����ڵ�
CString strMSG_CTNS = m_CommAgent.GetTranOutputData("OTS1111U30", "OTS1111U30_out", "MSG_CTNS", 0);		//�޽�������
