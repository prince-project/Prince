BEGIN_TRAN_LAYOUT

	TR_CODE=OAM2501U03, TR_NAME=��й�ȣȮ���������ݿ�, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OAM2501U03_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=INQ_DVSN, TYPE=string, SIZE=1, CAPTION=��ȸ����;
			 INDEX=1, ITEM=CUST_RNM_CNFM_NO, TYPE=string, SIZE=32, CAPTION=���Ǹ�Ȯ�ι�ȣ;
			 INDEX=2, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=3, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OAM2501U03_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=PRCS_PSBL_YN, TYPE=string, SIZE=1, CAPTION=ó�����ɿ���;
			 INDEX=1, ITEM=CUST_RNM_CNFM_NO, TYPE=string, SIZE=32, CAPTION=���Ǹ�Ȯ�ι�ȣ;
			 INDEX=2, ITEM=HDS_CUST_DVSN, TYPE=string, SIZE=1, CAPTION=�ϳ��������ǰ�����;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strINQ_DVSN;		//��ȸ����
CString strCUST_RNM_CNFM_NO;		//���Ǹ�Ȯ�ι�ȣ
CString strCTNO;		//���հ��´�ü��ȣ
CString strPWD;		//��й�ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OAM2501U03", "OAM2501U03_in", "INQ_DVSN", strINQ_DVSN);		//��ȸ����
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U03", "OAM2501U03_in", "CUST_RNM_CNFM_NO", strCUST_RNM_CNFM_NO);		//���Ǹ�Ȯ�ι�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U03", "OAM2501U03_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U03", "OAM2501U03_in", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strPRCS_PSBL_YN = m_CommAgent.GetTranOutputData("OAM2501U03", "OAM2501U03_out", "PRCS_PSBL_YN", 0);		//ó�����ɿ���
CString strCUST_RNM_CNFM_NO = m_CommAgent.GetTranOutputData("OAM2501U03", "OAM2501U03_out", "CUST_RNM_CNFM_NO", 0);		//���Ǹ�Ȯ�ι�ȣ
CString strHDS_CUST_DVSN = m_CommAgent.GetTranOutputData("OAM2501U03", "OAM2501U03_out", "HDS_CUST_DVSN", 0);		//�ϳ��������ǰ�����
