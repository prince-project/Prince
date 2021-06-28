BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7101U31, TR_NAME=CFD����ֹ�ó��API, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7101U31_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=���º�й�ȣ;
			 INDEX=3, ITEM=CFD_ODNO, TYPE=string, SIZE=11, CAPTION=CFD�ֹ���ȣ;
			 INDEX=4, ITEM=CFD_CVRG_DCD, TYPE=string, SIZE=1, CAPTION=CFD�ݴ�Ÿű����ڵ�;
			 INDEX=5, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ü�����ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7101U31_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_ODNO, TYPE=string, SIZE=11, CAPTION=CFD�ֹ���ȣ;
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
CString strCFD_ODNO;		//CFD�ֹ���ȣ
CString strCFD_CVRG_DCD;		//CFD�ݴ�Ÿű����ڵ�
CString strCOMM_MDIA_DCD;		//��Ÿ�ü�����ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7101U31", "OTS7101U31_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U31", "OTS7101U31_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U31", "OTS7101U31_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U31", "OTS7101U31_in", "CFD_ODNO", strCFD_ODNO);		//CFD�ֹ���ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U31", "OTS7101U31_in", "CFD_CVRG_DCD", strCFD_CVRG_DCD);		//CFD�ݴ�Ÿű����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U31", "OTS7101U31_in", "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//��Ÿ�ü�����ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strCFD_ODNO = m_CommAgent.GetTranOutputData("OTS7101U31", "OTS7101U31_out", "CFD_ODNO", 0);		//CFD�ֹ���ȣ
