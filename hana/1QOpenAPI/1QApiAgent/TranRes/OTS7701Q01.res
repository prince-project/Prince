BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7701Q01, TR_NAME=API��CFD�ֹ����ɼ�����ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7701Q01_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
			 INDEX=3, ITEM=CFD_NMPR_TP_DCD, TYPE=string, SIZE=1, CAPTION=CFDȣ�����������ڵ�;
			 INDEX=4, ITEM=CFD_ORDR_UNPR, TYPE=string, SIZE=20, CAPTION=CFD�ֹ��ܰ�;
			 INDEX=5, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7701Q01_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_ORDR_PSBL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�ֹ����ɱݾ�;
			 INDEX=1, ITEM=CFD_BUY_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFD�ż��ֹ����ɼ���;
			 INDEX=2, ITEM=CFD_SELL_ORDR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFD�ŵ��ֹ����ɼ���;
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
CString strCFD_NMPR_TP_DCD;		//CFDȣ�����������ڵ�
CString strCFD_ORDR_UNPR;		//CFD�ֹ��ܰ�
CString strPWD;		//��й�ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q01", "OTS7701Q01_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q01", "OTS7701Q01_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q01", "OTS7701Q01_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q01", "OTS7701Q01_in", "CFD_NMPR_TP_DCD", strCFD_NMPR_TP_DCD);		//CFDȣ�����������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q01", "OTS7701Q01_in", "CFD_ORDR_UNPR", strCFD_ORDR_UNPR);		//CFD�ֹ��ܰ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q01", "OTS7701Q01_in", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strCFD_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS7701Q01", "OTS7701Q01_out", "CFD_ORDR_PSBL_AMT", 0);		//CFD�ֹ����ɱݾ�
CString strCFD_BUY_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7701Q01", "OTS7701Q01_out", "CFD_BUY_ORDR_PSBL_QNT", 0);		//CFD�ż��ֹ����ɼ���
CString strCFD_SELL_ORDR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7701Q01", "OTS7701Q01_out", "CFD_SELL_ORDR_PSBL_QNT", 0);		//CFD�ŵ��ֹ����ɼ���
