BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5901U33, TR_NAME=FX��������ֹ�, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5901U33_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ����ֹ���ȣ;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=3, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=4, ITEM=FDM_UNQ_NO, TYPE=string, SIZE=3, CAPTION=�����Ͽ콺������ȣ;
			 INDEX=5, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=6, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=7, ITEM=ORDR_DRCN_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ����ⱸ���ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5901U33_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strFDM_UNQ_NO;		//�����Ͽ콺������ȣ
CString strPRDT_CD;		//��ǰ�ڵ�
CString strORDR_QNT;		//�ֹ�����
CString strORDR_DRCN_DCD;		//�ֹ����ⱸ���ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//�����Ͽ콺������ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U33", "OTS5901U33_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//�ֹ����ⱸ���ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5901U33", "OTS5901U33_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
