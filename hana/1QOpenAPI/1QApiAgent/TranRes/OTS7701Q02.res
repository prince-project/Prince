BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7701Q02, TR_NAME=API��CFDû�갡�ɼ�����ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7701Q02_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
			 INDEX=3, ITEM=CFD_TRDE_DCD, TYPE=string, SIZE=1, CAPTION=CFD�Ÿű����ڵ�;
			 INDEX=4, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7701Q02_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_CLR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFDû�갡�ɼ���;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strCFD_PRDT_CD;		//CFD��ǰ�ڵ�
CString strCFD_TRDE_DCD;		//CFD�Ÿű����ڵ�
CString strPWD;		//��й�ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q02", "OTS7701Q02_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q02", "OTS7701Q02_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q02", "OTS7701Q02_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q02", "OTS7701Q02_in", "CFD_TRDE_DCD", strCFD_TRDE_DCD);		//CFD�Ÿű����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q02", "OTS7701Q02_in", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strCFD_CLR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7701Q02", "OTS7701Q02_out", "CFD_CLR_PSBL_QNT", 0);		//CFDû�갡�ɼ���
