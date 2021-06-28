BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5901U03, TR_NAME=�ؿܼ�������ֹ�, SERVER=A, ENCODE=0, COMPRESS=0, CERT=1;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5901U03_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ����ֹ���ȣ;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=3, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=4, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=5, ITEM=CNCL_QNT, TYPE=string, SIZE=19, CAPTION=��Ҽ���;
			 INDEX=6, ITEM=ODRV_RMN_QNT_DVSN, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ��ܿ���������;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5901U03_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=ODRV_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ��ֹ���ȣ;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strODRV_OR_ODNO;		//�ؿ��Ļ����ֹ���ȣ
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strPWD;		//��й�ȣ
CString strPRDT_CD;		//��ǰ�ڵ�
CString strCNCL_QNT;		//��Ҽ���
CString strODRV_RMN_QNT_DVSN;		//�ؿ��Ļ��ܿ���������

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5901U03", "OTS5901U03_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U03", "OTS5901U03_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U03", "OTS5901U03_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U03", "OTS5901U03_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U03", "OTS5901U03_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U03", "OTS5901U03_in", "CNCL_QNT", strCNCL_QNT);		//��Ҽ���
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U03", "OTS5901U03_in", "ODRV_RMN_QNT_DVSN", strODRV_RMN_QNT_DVSN);		//�ؿ��Ļ��ܿ���������




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5901U03", "OTS5901U03_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
