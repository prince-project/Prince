BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5914Q51, TR_NAME=FX������Ź����ȸ��������, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5914Q51_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=INQ_DT, TYPE=string, SIZE=8, CAPTION=��ȸ����;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=3, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=���º�й�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5914Q51_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=��ȭ�ڵ�;
			 INDEX=1, ITEM=BFDT_CSH_BLCE_CTNS, TYPE=string, SIZE=30, CAPTION=���������ܾ׳���;
			 INDEX=2, ITEM=ODRV_IPP_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ�����ݾ׳���;
			 INDEX=3, ITEM=FX_FEE_CTNS, TYPE=string, SIZE=30, CAPTION=FX�����᳻��;
			 INDEX=4, ITEM=ROVR_INTR_CTNS, TYPE=string, SIZE=30, CAPTION=�ѿ������ڳ���;
			 INDEX=5, ITEM=THDT_DPSA_CTNS, TYPE=string, SIZE=30, CAPTION=���Ͽ�Ź�ݳ���;
			 INDEX=6, ITEM=ODRV_CLR_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ�û��ݾ׳���;
			 INDEX=7, ITEM=USTL_EVL_PFLS_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�̰����򰡼��ͱݾ׳���;
			 INDEX=8, ITEM=ODRV_EVL_DPST_TOT_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��򰡿�Ź�ѱݾ׳���;
			 INDEX=9, ITEM=ODRV_CSGN_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ���Ź���űݳ���;
			 INDEX=10, ITEM=ODRV_ADIT_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��߰����űݳ���;
			 INDEX=11, ITEM=ODRV_RCVB_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��̼��ݾ׳���;
			 INDEX=12, ITEM=ODRV_ORDR_PSBL_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��ֹ����ɱݾ׳���;
			 INDEX=13, ITEM=ODRV_WDRW_PSBL_AMT_CTNS, TYPE=string, SIZE=20, CAPTION=�ؿ��Ļ����Ⱑ�ɱݾ׳���;
			 INDEX=14, ITEM=ODRV_MNTN_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��������űݳ���;
			 INDEX=15, ITEM=RSK_RT_CTNS, TYPE=string, SIZE=30, CAPTION=����������;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strINQ_DT;		//��ȸ����
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strACNT_PWD;		//���º�й�ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5914Q51", "OTS5914Q51_in", "INQ_DT", strINQ_DT);		//��ȸ����
m_CommAgent.SetTranInputData(nRequestId, "OTS5914Q51", "OTS5914Q51_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5914Q51", "OTS5914Q51_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5914Q51", "OTS5914Q51_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
CString strBFDT_CSH_BLCE_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "BFDT_CSH_BLCE_CTNS", nRow);		//���������ܾ׳���
CString strODRV_IPP_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_IPP_AMT_CTNS", nRow);		//�ؿ��Ļ�����ݾ׳���
CString strFX_FEE_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "FX_FEE_CTNS", nRow);		//FX�����᳻��
CString strROVR_INTR_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ROVR_INTR_CTNS", nRow);		//�ѿ������ڳ���
CString strTHDT_DPSA_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "THDT_DPSA_CTNS", nRow);		//���Ͽ�Ź�ݳ���
CString strODRV_CLR_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_CLR_AMT_CTNS", nRow);		//�ؿ��Ļ�û��ݾ׳���
CString strUSTL_EVL_PFLS_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "USTL_EVL_PFLS_AMT_CTNS", nRow);		//�̰����򰡼��ͱݾ׳���
CString strODRV_EVL_DPST_TOT_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_EVL_DPST_TOT_AMT_CTNS", nRow);		//�ؿ��Ļ��򰡿�Ź�ѱݾ׳���
CString strODRV_CSGN_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_CSGN_WMY_CTNS", nRow);		//�ؿ��Ļ���Ź���űݳ���
CString strODRV_ADIT_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_ADIT_WMY_CTNS", nRow);		//�ؿ��Ļ��߰����űݳ���
CString strODRV_RCVB_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_RCVB_AMT_CTNS", nRow);		//�ؿ��Ļ��̼��ݾ׳���
CString strODRV_ORDR_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_ORDR_PSBL_AMT_CTNS", nRow);		//�ؿ��Ļ��ֹ����ɱݾ׳���
CString strODRV_WDRW_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_WDRW_PSBL_AMT_CTNS", nRow);		//�ؿ��Ļ����Ⱑ�ɱݾ׳���
CString strODRV_MNTN_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "ODRV_MNTN_WMY_CTNS", nRow);		//�ؿ��Ļ��������űݳ���
CString strRSK_RT_CTNS = m_CommAgent.GetTranOutputData("OTS5914Q51", "OTS5914Q51_out_sub01", "RSK_RT_CTNS", nRow);		//����������
