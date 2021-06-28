BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7101U41, TR_NAME=CFDû���ֹ�ó��API, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7101U41_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=���º�й�ȣ;
			 INDEX=3, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
			 INDEX=4, ITEM=CFD_TRDE_DCD, TYPE=string, SIZE=1, CAPTION=CFD�Ÿű����ڵ�;
			 INDEX=5, ITEM=CFD_NMPR_TP_DCD, TYPE=string, SIZE=1, CAPTION=CFDȣ�����������ڵ�;
			 INDEX=6, ITEM=CFD_CVRG_DCD, TYPE=string, SIZE=1, CAPTION=CFD�ݴ�Ÿű����ڵ�;
			 INDEX=7, ITEM=CFD_ORDR_QNT, TYPE=string, SIZE=19, CAPTION=CFD�ֹ�����;
			 INDEX=8, ITEM=CFD_ORDR_UNPR, TYPE=string, SIZE=20, CAPTION=CFD�ֹ��ܰ�;
			 INDEX=9, ITEM=EXCG_CD, TYPE=string, SIZE=10, CAPTION=�ŷ����ڵ�;
			 INDEX=10, ITEM=CFD_BRKR_CD, TYPE=string, SIZE=20, CAPTION=CFD���Ŀ�ڵ�;
			 INDEX=11, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ü�����ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7101U41_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strCFD_PRDT_CD;		//CFD��ǰ�ڵ�
CString strCFD_TRDE_DCD;		//CFD�Ÿű����ڵ�
CString strCFD_NMPR_TP_DCD;		//CFDȣ�����������ڵ�
CString strCFD_CVRG_DCD;		//CFD�ݴ�Ÿű����ڵ�
CString strCFD_ORDR_QNT;		//CFD�ֹ�����
CString strCFD_ORDR_UNPR;		//CFD�ֹ��ܰ�
CString strEXCG_CD;		//�ŷ����ڵ�
CString strCFD_BRKR_CD;		//CFD���Ŀ�ڵ�
CString strCOMM_MDIA_DCD;		//��Ÿ�ü�����ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7101U41", "OTS7101U41_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U41", "OTS7101U41_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U41", "OTS7101U41_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U41", "OTS7101U41_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U41", "OTS7101U41_in", "CFD_TRDE_DCD", strCFD_TRDE_DCD);		//CFD�Ÿű����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U41", "OTS7101U41_in", "CFD_NMPR_TP_DCD", strCFD_NMPR_TP_DCD);		//CFDȣ�����������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U41", "OTS7101U41_in", "CFD_CVRG_DCD", strCFD_CVRG_DCD);		//CFD�ݴ�Ÿű����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U41", "OTS7101U41_in", "CFD_ORDR_QNT", strCFD_ORDR_QNT);		//CFD�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U41", "OTS7101U41_in", "CFD_ORDR_UNPR", strCFD_ORDR_UNPR);		//CFD�ֹ��ܰ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U41", "OTS7101U41_in", "EXCG_CD", strEXCG_CD);		//�ŷ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U41", "OTS7101U41_in", "CFD_BRKR_CD", strCFD_BRKR_CD);		//CFD���Ŀ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7101U41", "OTS7101U41_in", "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//��Ÿ�ü�����ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strCFD_ODNO = m_CommAgent.GetTranOutputData("OTS7101U41", "OTS7101U41_out", "CFD_ODNO", 0);		//CFD�ֹ���ȣ
