BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2850U33, TR_NAME=�߰������ɼ�����ֹ�, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2850U33_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=���º�й�ȣ;
			 INDEX=3, ITEM=ORDR_BDCD, TYPE=string, SIZE=5, CAPTION=�ֹ������ڵ�;
			 INDEX=4, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=���ֹ��Ϸù�ȣ;
			 INDEX=5, ITEM=DRVS_EXCG_DCD, TYPE=string, SIZE=2, CAPTION=�Ļ���ǰ�ŷ��ұ����ڵ�;
			 INDEX=6, ITEM=ORDR_PRC, TYPE=string, SIZE=20, CAPTION=�ֹ�����;
			 INDEX=7, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=8, ITEM=ALL_YN, TYPE=string, SIZE=1, CAPTION=��ü����;
			 INDEX=9, ITEM=EMR_ORDR_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=����ֹ���ü�����ڵ�;
			 INDEX=10, ITEM=DFRT_HDGE_DCD, TYPE=string, SIZE=2, CAPTION=�������������ڵ�;
			 INDEX=11, ITEM=GRUP_ORDR_YN, TYPE=string, SIZE=1, CAPTION=�׷��ֹ�����;
			 INDEX=12, ITEM=ORDR_GRUP_NM, TYPE=string, SIZE=100, CAPTION=�ֹ��׷��;
			 INDEX=13, ITEM=PWD_CNFM_YN, TYPE=string, SIZE=1, CAPTION=��й�ȣȮ�ο���;
			 INDEX=14, ITEM=ETC_ORDR_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ֹ������ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2850U33_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ֹ��Ϸù�ȣ;
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
CString strORDR_BDCD;		//�ֹ������ڵ�
CString strOR_ORDR_SN;		//���ֹ��Ϸù�ȣ
CString strDRVS_EXCG_DCD;		//�Ļ���ǰ�ŷ��ұ����ڵ�
CString strORDR_PRC;		//�ֹ�����
CString strORDR_QNT;		//�ֹ�����
CString strALL_YN;		//��ü����
CString strEMR_ORDR_MDIA_DCD;		//����ֹ���ü�����ڵ�
CString strDFRT_HDGE_DCD;		//�������������ڵ�
CString strGRUP_ORDR_YN;		//�׷��ֹ�����
CString strORDR_GRUP_NM;		//�ֹ��׷��
CString strPWD_CNFM_YN;		//��й�ȣȮ�ο���
CString strETC_ORDR_DCD;		//��Ÿ�ֹ������ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "ORDR_BDCD", strORDR_BDCD);		//�ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "OR_ORDR_SN", strOR_ORDR_SN);		//���ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "DRVS_EXCG_DCD", strDRVS_EXCG_DCD);		//�Ļ���ǰ�ŷ��ұ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "ORDR_PRC", strORDR_PRC);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "ALL_YN", strALL_YN);		//��ü����
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//����ֹ���ü�����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "DFRT_HDGE_DCD", strDFRT_HDGE_DCD);		//�������������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "GRUP_ORDR_YN", strGRUP_ORDR_YN);		//�׷��ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "ORDR_GRUP_NM", strORDR_GRUP_NM);		//�ֹ��׷��
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "PWD_CNFM_YN", strPWD_CNFM_YN);		//��й�ȣȮ�ο���
m_CommAgent.SetTranInputData(nRequestId, "OTS2850U33", "OTS2850U33_in", "ETC_ORDR_DCD", strETC_ORDR_DCD);		//��Ÿ�ֹ������ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS2850U33", "OTS2850U33_out", "ORDR_SN", 0);		//�ֹ��Ϸù�ȣ
