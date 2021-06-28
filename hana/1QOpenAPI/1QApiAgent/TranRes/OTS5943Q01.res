BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5943Q01, TR_NAME=�ؿܿ¶�����ȭ�������ܰ���ȸ1, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5943Q01_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=BSN_DT, TYPE=string, SIZE=8, CAPTION=��������;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=3, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5943Q01_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=��ȭ�ڵ�;
			 INDEX=1, ITEM=ODRV_STDR_EXRT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ�����ȯ������;
			 INDEX=2, ITEM=BFDT_CSH_BLCE_CTNS, TYPE=string, SIZE=30, CAPTION=���������ܾ׳���;
			 INDEX=3, ITEM=ODRV_CSH_RCTM_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ������Աݱݾ׳���;
			 INDEX=4, ITEM=ODRV_CSH_DRWG_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ�������ݱݾ׳���;
			 INDEX=5, ITEM=ODRV_CLR_PFLS_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ�û����ͱݾ׳���;
			 INDEX=6, ITEM=ODRV_OPT_SELL_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��ɼǸŵ��ݾ׳���;
			 INDEX=7, ITEM=ODRV_OPT_BUY_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��ɼǸż��ݾ׳���;
			 INDEX=8, ITEM=ODRV_FEE_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ������᳻��;
			 INDEX=9, ITEM=THDT_CSH_BLCE_CTNS, TYPE=string, SIZE=30, CAPTION=���������ܾ׳���;
			 INDEX=10, ITEM=ODRV_EVL_PFLS_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��򰡼��ͱݾ׳���;
			 INDEX=11, ITEM=EVL_DPST_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�򰡿�Ź�ݾ׳���;
			 INDEX=12, ITEM=ODRV_OPT_EVL_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��ɼ��򰡱ݾ׳���;
			 INDEX=13, ITEM=TOT_ACC_ASST_VALU_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�Ѱ����ڻ갡ġ�ݾ׳���;
			 INDEX=14, ITEM=OPNG_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=�������űݳ���;
			 INDEX=15, ITEM=ODRV_ORDR_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��ֹ����űݳ���;
			 INDEX=16, ITEM=ODRV_MNTN_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��������űݳ���;
			 INDEX=17, ITEM=WMY_LACK_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=���űݺ����ݾ׳���;
			 INDEX=18, ITEM=ODRV_WDRW_PSBL_AMT_CTNS, TYPE=string, SIZE=20, CAPTION=�ؿ��Ļ����Ⱑ�ɱݾ׳���;
			 INDEX=19, ITEM=ECHM_PSBL_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=ȯ�����ɱݾ׳���;
			 INDEX=20, ITEM=ODRV_ORDR_PSBL_AMT_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��ֹ����ɱݾ׳���;
			 INDEX=21, ITEM=ODRV_ADIT_WMY_CTNS, TYPE=string, SIZE=30, CAPTION=�ؿ��Ļ��߰����űݳ���;
			 INDEX=22, ITEM=RCVB_OVDU_INTR_CTNS, TYPE=string, SIZE=30, CAPTION=�̼���ü���ڳ���;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strBSN_DT;		//��������
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strPWD;		//��й�ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5943Q01", "OTS5943Q01_in", "BSN_DT", strBSN_DT);		//��������
m_CommAgent.SetTranInputData(nRequestId, "OTS5943Q01", "OTS5943Q01_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5943Q01", "OTS5943Q01_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5943Q01", "OTS5943Q01_in", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
CString strODRV_STDR_EXRT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_STDR_EXRT_CTNS", nRow);		//�ؿ��Ļ�����ȯ������
CString strBFDT_CSH_BLCE_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "BFDT_CSH_BLCE_CTNS", nRow);		//���������ܾ׳���
CString strODRV_CSH_RCTM_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_CSH_RCTM_AMT_CTNS", nRow);		//�ؿ��Ļ������Աݱݾ׳���
CString strODRV_CSH_DRWG_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_CSH_DRWG_AMT_CTNS", nRow);		//�ؿ��Ļ�������ݱݾ׳���
CString strODRV_CLR_PFLS_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_CLR_PFLS_AMT_CTNS", nRow);		//�ؿ��Ļ�û����ͱݾ׳���
CString strODRV_OPT_SELL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_OPT_SELL_AMT_CTNS", nRow);		//�ؿ��Ļ��ɼǸŵ��ݾ׳���
CString strODRV_OPT_BUY_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_OPT_BUY_AMT_CTNS", nRow);		//�ؿ��Ļ��ɼǸż��ݾ׳���
CString strODRV_FEE_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_FEE_CTNS", nRow);		//�ؿ��Ļ������᳻��
CString strTHDT_CSH_BLCE_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "THDT_CSH_BLCE_CTNS", nRow);		//���������ܾ׳���
CString strODRV_EVL_PFLS_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_EVL_PFLS_AMT_CTNS", nRow);		//�ؿ��Ļ��򰡼��ͱݾ׳���
CString strEVL_DPST_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "EVL_DPST_AMT_CTNS", nRow);		//�򰡿�Ź�ݾ׳���
CString strODRV_OPT_EVL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_OPT_EVL_AMT_CTNS", nRow);		//�ؿ��Ļ��ɼ��򰡱ݾ׳���
CString strTOT_ACC_ASST_VALU_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "TOT_ACC_ASST_VALU_AMT_CTNS", nRow);		//�Ѱ����ڻ갡ġ�ݾ׳���
CString strOPNG_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "OPNG_WMY_CTNS", nRow);		//�������űݳ���
CString strODRV_ORDR_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_ORDR_WMY_CTNS", nRow);		//�ؿ��Ļ��ֹ����űݳ���
CString strODRV_MNTN_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_MNTN_WMY_CTNS", nRow);		//�ؿ��Ļ��������űݳ���
CString strWMY_LACK_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "WMY_LACK_AMT_CTNS", nRow);		//���űݺ����ݾ׳���
CString strODRV_WDRW_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_WDRW_PSBL_AMT_CTNS", nRow);		//�ؿ��Ļ����Ⱑ�ɱݾ׳���
CString strECHM_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ECHM_PSBL_AMT_CTNS", nRow);		//ȯ�����ɱݾ׳���
CString strODRV_ORDR_PSBL_AMT_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_ORDR_PSBL_AMT_CTNS", nRow);		//�ؿ��Ļ��ֹ����ɱݾ׳���
CString strODRV_ADIT_WMY_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "ODRV_ADIT_WMY_CTNS", nRow);		//�ؿ��Ļ��߰����űݳ���
CString strRCVB_OVDU_INTR_CTNS = m_CommAgent.GetTranOutputData("OTS5943Q01", "OTS5943Q01_out_sub01", "RCVB_OVDU_INTR_CTNS", nRow);		//�̼���ü���ڳ���
