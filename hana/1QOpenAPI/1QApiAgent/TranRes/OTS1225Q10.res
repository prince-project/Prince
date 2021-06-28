BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1225Q10, TR_NAME=���º����ϸŸż����հ�, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1225Q10_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=TRDE_DT, TYPE=string, SIZE=8, CAPTION=�Ÿ�����;
			 INDEX=4, ITEM=FEE_RT, TYPE=string, SIZE=17, CAPTION=��������;
			 INDEX=5, ITEM=TRDE_CT_INCL_YN, TYPE=string, SIZE=1, CAPTION=�Ÿź�����Կ���;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1225Q10_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=BUY_AMT, TYPE=string, SIZE=19, CAPTION=�ż��ݾ�;
			 INDEX=1, ITEM=SELL_AMT, TYPE=string, SIZE=19, CAPTION=�ŵ��ݾ�;
			 INDEX=2, ITEM=EXCAL_AMT, TYPE=string, SIZE=19, CAPTION=����ݾ�;
			 INDEX=3, ITEM=TRDE_CT_AMT, TYPE=string, SIZE=18, CAPTION=�Ÿź��ݾ�;
			 INDEX=4, ITEM=PFLS_AMT, TYPE=string, SIZE=19, CAPTION=���ͱݾ�;
			 INDEX=5, ITEM=PFLS_RT, TYPE=string, SIZE=20, CAPTION=������;
			 INDEX=6, ITEM=DACA, TYPE=string, SIZE=19, CAPTION=������;
			 INDEX=7, ITEM=NDY_PRSM_DACA, TYPE=string, SIZE=19, CAPTION=��������������;
			 INDEX=8, ITEM=NX_NDY_PRSM_DACA, TYPE=string, SIZE=19, CAPTION=����������������;
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
CString strTRDE_DT;		//�Ÿ�����
CString strFEE_RT;		//��������
CString strTRDE_CT_INCL_YN;		//�Ÿź�����Կ���

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q10", "OTS1225Q10_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q10", "OTS1225Q10_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q10", "OTS1225Q10_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q10", "OTS1225Q10_in", "TRDE_DT", strTRDE_DT);		//�Ÿ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q10", "OTS1225Q10_in", "FEE_RT", strFEE_RT);		//��������
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q10", "OTS1225Q10_in", "TRDE_CT_INCL_YN", strTRDE_CT_INCL_YN);		//�Ÿź�����Կ���




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strBUY_AMT = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "BUY_AMT", 0);		//�ż��ݾ�
CString strSELL_AMT = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "SELL_AMT", 0);		//�ŵ��ݾ�
CString strEXCAL_AMT = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "EXCAL_AMT", 0);		//����ݾ�
CString strTRDE_CT_AMT = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "TRDE_CT_AMT", 0);		//�Ÿź��ݾ�
CString strPFLS_AMT = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "PFLS_AMT", 0);		//���ͱݾ�
CString strPFLS_RT = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "PFLS_RT", 0);		//������
CString strDACA = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "DACA", 0);		//������
CString strNDY_PRSM_DACA = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "NDY_PRSM_DACA", 0);		//��������������
CString strNX_NDY_PRSM_DACA = m_CommAgent.GetTranOutputData("OTS1225Q10", "OTS1225Q10_out", "NX_NDY_PRSM_DACA", 0);		//����������������
