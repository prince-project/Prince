BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7701Q06, TR_NAME=API��CFD������Ʈ����ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7701Q06_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
			 INDEX=1, ITEM=CFD_TRDE_DCD, TYPE=string, SIZE=1, CAPTION=CFD�Ÿű����ڵ�;
			 INDEX=2, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=3, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7701Q06_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_WMY_RT, TYPE=string, SIZE=20, CAPTION=CFD���ű���;
			 INDEX=1, ITEM=CFD_ROVR_INTR_RT, TYPE=string, SIZE=20, CAPTION=CFD�ѿ���������;
			 INDEX=2, ITEM=CFD_SSS_FEE_RT, TYPE=string, SIZE=20, CAPTION=CFD���ŵ���������;
			 INDEX=3, ITEM=CFD_SELL_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFD�ŵ����ɼ���;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strCFD_PRDT_CD;		//CFD��ǰ�ڵ�
CString strCFD_TRDE_DCD;		//CFD�Ÿű����ڵ�
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q06", "OTS7701Q06_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q06", "OTS7701Q06_in", "CFD_TRDE_DCD", strCFD_TRDE_DCD);		//CFD�Ÿű����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q06", "OTS7701Q06_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q06", "OTS7701Q06_in", "APNO", strAPNO);		//���»�ǰ��ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strCFD_WMY_RT = m_CommAgent.GetTranOutputData("OTS7701Q06", "OTS7701Q06_out", "CFD_WMY_RT", 0);		//CFD���ű���
CString strCFD_ROVR_INTR_RT = m_CommAgent.GetTranOutputData("OTS7701Q06", "OTS7701Q06_out", "CFD_ROVR_INTR_RT", 0);		//CFD�ѿ���������
CString strCFD_SSS_FEE_RT = m_CommAgent.GetTranOutputData("OTS7701Q06", "OTS7701Q06_out", "CFD_SSS_FEE_RT", 0);		//CFD���ŵ���������
CString strCFD_SELL_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7701Q06", "OTS7701Q06_out", "CFD_SELL_PSBL_QNT", 0);		//CFD�ŵ����ɼ���
