BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2100U40, TR_NAME=�����ɼ���������ֹ�, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2100U40_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=���º�й�ȣ;
			 INDEX=3, ITEM=ORDR_BDCD, TYPE=string, SIZE=5, CAPTION=�ֹ������ڵ�;
			 INDEX=4, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=���ֹ��Ϸù�ȣ;
			 INDEX=5, ITEM=ORDR_PRC, TYPE=string, SIZE=20, CAPTION=�ֹ�����;
			 INDEX=6, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=7, ITEM=ALL_YN, TYPE=string, SIZE=1, CAPTION=��ü����;
			 INDEX=8, ITEM=EMR_ORDR_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=����ֹ���ü�����ڵ�;
			 INDEX=9, ITEM=DFRT_HDGE_DCD, TYPE=string, SIZE=2, CAPTION=�������������ڵ�;
			 INDEX=10, ITEM=GRUP_ORDR_YN, TYPE=string, SIZE=1, CAPTION=�׷��ֹ�����;
			 INDEX=11, ITEM=ORDR_GRUP_NM, TYPE=string, SIZE=100, CAPTION=�ֹ��׷��;
			 INDEX=12, ITEM=PWD_CNFM_YN, TYPE=string, SIZE=1, CAPTION=��й�ȣȮ�ο���;
			 INDEX=13, ITEM=MDIA_ORDR_SN, TYPE=string, SIZE=11, CAPTION=��ü�ֹ��Ϸù�ȣ;
			 INDEX=14, ITEM=ETC_ORDR_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ֹ������ڵ�;
			 INDEX=15, ITEM=ORDR_RPRC_YN, TYPE=string, SIZE=1, CAPTION=�ֹ���ó������;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2100U40_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strORDR_PRC;		//�ֹ�����
CString strORDR_QNT;		//�ֹ�����
CString strALL_YN;		//��ü����
CString strEMR_ORDR_MDIA_DCD;		//����ֹ���ü�����ڵ�
CString strDFRT_HDGE_DCD;		//�������������ڵ�
CString strGRUP_ORDR_YN;		//�׷��ֹ�����
CString strORDR_GRUP_NM;		//�ֹ��׷��
CString strPWD_CNFM_YN;		//��й�ȣȮ�ο���
CString strMDIA_ORDR_SN;		//��ü�ֹ��Ϸù�ȣ
CString strETC_ORDR_DCD;		//��Ÿ�ֹ������ڵ�
CString strORDR_RPRC_YN;		//�ֹ���ó������

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "ORDR_BDCD", strORDR_BDCD);		//�ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "OR_ORDR_SN", strOR_ORDR_SN);		//���ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "ORDR_PRC", strORDR_PRC);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "ALL_YN", strALL_YN);		//��ü����
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//����ֹ���ü�����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "DFRT_HDGE_DCD", strDFRT_HDGE_DCD);		//�������������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "GRUP_ORDR_YN", strGRUP_ORDR_YN);		//�׷��ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "ORDR_GRUP_NM", strORDR_GRUP_NM);		//�ֹ��׷��
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "PWD_CNFM_YN", strPWD_CNFM_YN);		//��й�ȣȮ�ο���
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "MDIA_ORDR_SN", strMDIA_ORDR_SN);		//��ü�ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "ETC_ORDR_DCD", strETC_ORDR_DCD);		//��Ÿ�ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U40", "OTS2100U40_in", "ORDR_RPRC_YN", strORDR_RPRC_YN);		//�ֹ���ó������




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS2100U40", "OTS2100U40_out", "ORDR_SN", 0);		//�ֹ��Ϸù�ȣ
