BEGIN_TRAN_LAYOUT

	TR_CODE=OAM2501U02, TR_NAME=��й�ȣȮ��C, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OAM2501U02_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=PWD_GNRL_PRCS_DVSN1, TYPE=string, SIZE=1, CAPTION=��й�ȣ�Ϲ�ó������1;
			 INDEX=4, ITEM=PWD_GNRL_PRCS_DVSN2, TYPE=string, SIZE=1, CAPTION=��й�ȣ�Ϲ�ó������2;
			 INDEX=5, ITEM=PWD_GNRL_PRCS_DVSN3, TYPE=string, SIZE=1, CAPTION=��й�ȣ�Ϲ�ó������3;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OAM2501U02_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=PRCS_PSBL_YN, TYPE=string, SIZE=1, CAPTION=ó�����ɿ���;
			 INDEX=1, ITEM=ERR_ID, TYPE=string, SIZE=10, CAPTION=����ID;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strPWD;		//��й�ȣ
CString strPWD_GNRL_PRCS_DVSN1;		//��й�ȣ�Ϲ�ó������1
CString strPWD_GNRL_PRCS_DVSN2;		//��й�ȣ�Ϲ�ó������2
CString strPWD_GNRL_PRCS_DVSN3;		//��й�ȣ�Ϲ�ó������3

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OAM2501U02", "OAM2501U02_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U02", "OAM2501U02_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U02", "OAM2501U02_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U02", "OAM2501U02_in", "PWD_GNRL_PRCS_DVSN1", strPWD_GNRL_PRCS_DVSN1);		//��й�ȣ�Ϲ�ó������1
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U02", "OAM2501U02_in", "PWD_GNRL_PRCS_DVSN2", strPWD_GNRL_PRCS_DVSN2);		//��й�ȣ�Ϲ�ó������2
m_CommAgent.SetTranInputData(nRequestId, "OAM2501U02", "OAM2501U02_in", "PWD_GNRL_PRCS_DVSN3", strPWD_GNRL_PRCS_DVSN3);		//��й�ȣ�Ϲ�ó������3




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strPRCS_PSBL_YN = m_CommAgent.GetTranOutputData("OAM2501U02", "OAM2501U02_out", "PRCS_PSBL_YN", 0);		//ó�����ɿ���
CString strERR_ID = m_CommAgent.GetTranOutputData("OAM2501U02", "OAM2501U02_out", "ERR_ID", 0);		//����ID
