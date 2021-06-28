BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5901U02, TR_NAME=�ؿܼ��������ֹ�, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5901U02_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ����ֹ���ȣ;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=3, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=4, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=5, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=�������Ǳ����ڵ�;
			 INDEX=6, ITEM=ODRV_RVSE_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ���������;
			 INDEX=7, ITEM=RVSE_QNT, TYPE=string, SIZE=19, CAPTION=��������;
			 INDEX=8, ITEM=STLS_APPN_PRC, TYPE=string, SIZE=24, CAPTION=��ž�ν���������;
			 INDEX=9, ITEM=RMN_QNT_YN, TYPE=string, SIZE=1, CAPTION=�ܿ���������;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5901U02_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strPRC_CND_DCD;		//�������Ǳ����ڵ�
CString strODRV_RVSE_PRC;		//�ؿ��Ļ���������
CString strRVSE_QNT;		//��������
CString strSTLS_APPN_PRC;		//��ž�ν���������
CString strRMN_QNT_YN;		//�ܿ���������

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "ODRV_OR_ODNO", strODRV_OR_ODNO);		//�ؿ��Ļ����ֹ���ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "PRC_CND_DCD", strPRC_CND_DCD);		//�������Ǳ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "ODRV_RVSE_PRC", strODRV_RVSE_PRC);		//�ؿ��Ļ���������
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "RVSE_QNT", strRVSE_QNT);		//��������
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "STLS_APPN_PRC", strSTLS_APPN_PRC);		//��ž�ν���������
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U02", "OTS5901U02_in", "RMN_QNT_YN", strRMN_QNT_YN);		//�ܿ���������




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5901U02", "OTS5901U02_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
