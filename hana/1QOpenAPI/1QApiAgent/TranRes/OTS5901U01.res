BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5901U01, TR_NAME=�ؿܼ����Ϲ��ֹ�, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5901U01_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=4, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
			 INDEX=5, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=�������Ǳ����ڵ�;
			 INDEX=6, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ��ֹ�����;
			 INDEX=7, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=8, ITEM=STLS_APPN_PRC, TYPE=string, SIZE=24, CAPTION=��ž�ν���������;
			 INDEX=9, ITEM=ORDR_HND_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ����۱����ڵ�;
			 INDEX=10, ITEM=ORDR_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ������ڵ�;
			 INDEX=11, ITEM=ETC_ORDR_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ֹ������ڵ�;
			 INDEX=12, ITEM=CNCS_CND_DCD, TYPE=string, SIZE=1, CAPTION=ü�����Ǳ����ڵ�;
			 INDEX=13, ITEM=CLR_PST_NO, TYPE=string, SIZE=16, CAPTION=û�������ǹ�ȣ;
			 INDEX=14, ITEM=ORDR_EXPR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ���������;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5901U01_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=ODRV_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ��ֹ���ȣ;
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
CString strPRDT_CD;		//��ǰ�ڵ�
CString strSELL_BUY_DCD;		//�ŵ��ż������ڵ�
CString strPRC_CND_DCD;		//�������Ǳ����ڵ�
CString strODRV_ORDR_PRC;		//�ؿ��Ļ��ֹ�����
CString strORDR_QNT;		//�ֹ�����
CString strSTLS_APPN_PRC;		//��ž�ν���������
CString strORDR_HND_DCD;		//�ֹ����۱����ڵ�
CString strORDR_DCD;		//�ֹ������ڵ�
CString strETC_ORDR_DCD;		//��Ÿ�ֹ������ڵ�
CString strCNCS_CND_DCD;		//ü�����Ǳ����ڵ�
CString strCLR_PST_NO;		//û�������ǹ�ȣ
CString strORDR_EXPR_DT;		//�ֹ���������

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//�ŵ��ż������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "PRC_CND_DCD", strPRC_CND_DCD);		//�������Ǳ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "ODRV_ORDR_PRC", strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "STLS_APPN_PRC", strSTLS_APPN_PRC);		//��ž�ν���������
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "ORDR_HND_DCD", strORDR_HND_DCD);		//�ֹ����۱����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "ORDR_DCD", strORDR_DCD);		//�ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "ETC_ORDR_DCD", strETC_ORDR_DCD);		//��Ÿ�ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "CNCS_CND_DCD", strCNCS_CND_DCD);		//ü�����Ǳ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "CLR_PST_NO", strCLR_PST_NO);		//û�������ǹ�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U01", "OTS5901U01_in", "ORDR_EXPR_DT", strORDR_EXPR_DT);		//�ֹ���������




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5901U01", "OTS5901U01_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
