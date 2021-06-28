BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5901U31, TR_NAME=FX�����Ϲ��ֹ�, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5901U31_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=FDM_UNQ_NO, TYPE=string, SIZE=3, CAPTION=�����Ͽ콺������ȣ;
			 INDEX=4, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=5, ITEM=NMPR_UNQ_NO, TYPE=string, SIZE=11, CAPTION=ȣ��������ȣ;
			 INDEX=6, ITEM=ENTR_CLR_DCD, TYPE=string, SIZE=1, CAPTION=����û�걸���ڵ�;
			 INDEX=7, ITEM=PST_NO, TYPE=string, SIZE=16, CAPTION=�����ǹ�ȣ;
			 INDEX=8, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ��ŵ��ż������ڵ�;
			 INDEX=9, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=�������Ǳ����ڵ�;
			 INDEX=10, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ��ֹ�����;
			 INDEX=11, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=12, ITEM=SQ1_STLS_YN, TYPE=string, SIZE=1, CAPTION=1����ž�ν�����;
			 INDEX=13, ITEM=SQ1_APMPR_YN, TYPE=string, SIZE=1, CAPTION=1������������;
			 INDEX=14, ITEM=SQ1_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1����ž�ν�����;
			 INDEX=15, ITEM=SQ1_APPN_PRC, TYPE=string, SIZE=24, CAPTION=1����������;
			 INDEX=16, ITEM=SQ1_CHAS_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1�����������Ű���;
			 INDEX=17, ITEM=SQ2_STLS_YN, TYPE=string, SIZE=1, CAPTION=2����ž�ν�����;
			 INDEX=18, ITEM=SQ2_APMPR_YN, TYPE=string, SIZE=1, CAPTION=2������������;
			 INDEX=19, ITEM=SQ2_STLS_PRC, TYPE=string, SIZE=24, CAPTION=2����ž�ν�����;
			 INDEX=20, ITEM=SQ2_APPN_PRC, TYPE=string, SIZE=24, CAPTION=2����������;
			 INDEX=21, ITEM=SQ2_CHAS_STLS_PRC, TYPE=string, SIZE=24, CAPTION=2�����������Ű���;
			 INDEX=22, ITEM=ORDR_DRCN_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ����ⱸ���ڵ�;
			 INDEX=23, ITEM=ORDR_SRC_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ���õ�����ڵ�;
			 INDEX=24, ITEM=TRDE_PRC_DFRN_CTNS, TYPE=string, SIZE=50, CAPTION=�ŸŰ������̳���;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5901U31_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strFDM_UNQ_NO;		//�����Ͽ콺������ȣ
CString strPRDT_CD;		//��ǰ�ڵ�
CString strNMPR_UNQ_NO;		//ȣ��������ȣ
CString strENTR_CLR_DCD;		//����û�걸���ڵ�
CString strPST_NO;		//�����ǹ�ȣ
CString strODRV_SELL_BUY_DCD;		//�ؿ��Ļ��ŵ��ż������ڵ�
CString strPRC_CND_DCD;		//�������Ǳ����ڵ�
CString strODRV_ORDR_PRC;		//�ؿ��Ļ��ֹ�����
CString strORDR_QNT;		//�ֹ�����
CString strSQ1_STLS_YN;		//1����ž�ν�����
CString strSQ1_APMPR_YN;		//1������������
CString strSQ1_STLS_PRC;		//1����ž�ν�����
CString strSQ1_APPN_PRC;		//1����������
CString strSQ1_CHAS_STLS_PRC;		//1�����������Ű���
CString strSQ2_STLS_YN;		//2����ž�ν�����
CString strSQ2_APMPR_YN;		//2������������
CString strSQ2_STLS_PRC;		//2����ž�ν�����
CString strSQ2_APPN_PRC;		//2����������
CString strSQ2_CHAS_STLS_PRC;		//2�����������Ű���
CString strORDR_DRCN_DCD;		//�ֹ����ⱸ���ڵ�
CString strORDR_SRC_DCD;		//�ֹ���õ�����ڵ�
CString strTRDE_PRC_DFRN_CTNS;		//�ŸŰ������̳���

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "FDM_UNQ_NO", strFDM_UNQ_NO);		//�����Ͽ콺������ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "NMPR_UNQ_NO", strNMPR_UNQ_NO);		//ȣ��������ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "ENTR_CLR_DCD", strENTR_CLR_DCD);		//����û�걸���ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "PST_NO", strPST_NO);		//�����ǹ�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//�ؿ��Ļ��ŵ��ż������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "PRC_CND_DCD", strPRC_CND_DCD);		//�������Ǳ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "ODRV_ORDR_PRC", strODRV_ORDR_PRC);		//�ؿ��Ļ��ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ1_STLS_YN", strSQ1_STLS_YN);		//1����ž�ν�����
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ1_APMPR_YN", strSQ1_APMPR_YN);		//1������������
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ1_STLS_PRC", strSQ1_STLS_PRC);		//1����ž�ν�����
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ1_APPN_PRC", strSQ1_APPN_PRC);		//1����������
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ1_CHAS_STLS_PRC", strSQ1_CHAS_STLS_PRC);		//1�����������Ű���
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ2_STLS_YN", strSQ2_STLS_YN);		//2����ž�ν�����
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ2_APMPR_YN", strSQ2_APMPR_YN);		//2������������
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ2_STLS_PRC", strSQ2_STLS_PRC);		//2����ž�ν�����
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ2_APPN_PRC", strSQ2_APPN_PRC);		//2����������
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "SQ2_CHAS_STLS_PRC", strSQ2_CHAS_STLS_PRC);		//2�����������Ű���
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "ORDR_DRCN_DCD", strORDR_DRCN_DCD);		//�ֹ����ⱸ���ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "ORDR_SRC_DCD", strORDR_SRC_DCD);		//�ֹ���õ�����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5901U31", "OTS5901U31_in", "TRDE_PRC_DFRN_CTNS", strTRDE_PRC_DFRN_CTNS);		//�ŸŰ������̳���




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5901U31", "OTS5901U31_out", "ODRV_ODNO", 0);		//�ؿ��Ļ��ֹ���ȣ
