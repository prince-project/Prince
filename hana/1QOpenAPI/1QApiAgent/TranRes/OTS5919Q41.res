BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5919Q41, TR_NAME=�̰���������Ȳ�ؿ�ON���±׷캰, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5919Q41_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ��ŵ��ż������ڵ�;
		END_INPUT0_ITEM

		REC_NAME=OTS5919Q41_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		BEGIN_INPUT1_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT1_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5919Q41_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=���հ��¹�ȣ;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=3, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=����;
			 INDEX=4, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=5, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=��ǰ��;
			 INDEX=6, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ��ŵ��ż������ڵ�;
			 INDEX=7, ITEM=USTL_CTRC_QNT, TYPE=string, SIZE=19, CAPTION=�̰�����������;
			 INDEX=8, ITEM=TRDE_AVR_UNPR, TYPE=string, SIZE=23, CAPTION=�Ÿ���մܰ�;
			 INDEX=9, ITEM=CLR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=û�갡�ɼ���;
			 INDEX=10, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ��ܿ�����;
			 INDEX=11, ITEM=ODRV_NOW_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ����簡��;
			 INDEX=12, ITEM=ODRV_BFDT_PRPT, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ����ϴ��;
			 INDEX=13, ITEM=ODRV_BFDT_PRPT_RT, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ����ϴ����;
			 INDEX=14, ITEM=ODRV_EVL_AMT, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ��򰡱ݾ�;
			 INDEX=15, ITEM=ODRV_EVL_PFLS_AMT, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ��򰡼��ͱݾ�;
			 INDEX=16, ITEM=ODRV_PFLS_RT, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ�������;
			 INDEX=17, ITEM=USTL_CTRC_AMT, TYPE=string, SIZE=24, CAPTION=�̰��������ݾ�;
			 INDEX=18, ITEM=TRSL_MLT, TYPE=string, SIZE=23, CAPTION=ȯ��¼�;
			 INDEX=19, ITEM=ODRV_FTOP_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ������ɼǱ����ڵ�;
			 INDEX=20, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=��ȭ�ڵ�;
			 INDEX=21, ITEM=PRC_DCPN_BLW_LNG, TYPE=string, SIZE=6, CAPTION=���ݼҼ������ϱ���;
			 INDEX=22, ITEM=INDC_PRC, TYPE=string, SIZE=19, CAPTION=ǥ�ð���;
			 INDEX=23, ITEM=BSN_DT, TYPE=string, SIZE=8, CAPTION=��������;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strODRV_SELL_BUY_DCD;		//�ؿ��Ļ��ŵ��ż������ڵ�
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strPWD;		//��й�ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q41", "OTS5919Q41_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//�ؿ��Ļ��ŵ��ż������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q41", "OTS5919Q41_in_sub01", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q41", "OTS5919Q41_in_sub01", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q41", "OTS5919Q41_in_sub01", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCANO = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
CString strCTNO = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "CTNO", nRow);		//���հ��´�ü��ȣ
CString strAPNO = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "APNO", nRow);		//���»�ǰ��ȣ
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "CUST_NM", nRow);		//����
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "PRDT_NM", nRow);		//��ǰ��
CString strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//�ؿ��Ļ��ŵ��ż������ڵ�
CString strUSTL_CTRC_QNT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "USTL_CTRC_QNT", nRow);		//�̰�����������
CString strTRDE_AVR_UNPR = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "TRDE_AVR_UNPR", nRow);		//�Ÿ���մܰ�
CString strCLR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "CLR_PSBL_QNT", nRow);		//û�갡�ɼ���
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
CString strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_NOW_PRC", nRow);		//�ؿ��Ļ����簡��
CString strODRV_BFDT_PRPT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_BFDT_PRPT", nRow);		//�ؿ��Ļ����ϴ��
CString strODRV_BFDT_PRPT_RT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_BFDT_PRPT_RT", nRow);		//�ؿ��Ļ����ϴ����
CString strODRV_EVL_AMT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_EVL_AMT", nRow);		//�ؿ��Ļ��򰡱ݾ�
CString strODRV_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_EVL_PFLS_AMT", nRow);		//�ؿ��Ļ��򰡼��ͱݾ�
CString strODRV_PFLS_RT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_PFLS_RT", nRow);		//�ؿ��Ļ�������
CString strUSTL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "USTL_CTRC_AMT", nRow);		//�̰��������ݾ�
CString strTRSL_MLT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "TRSL_MLT", nRow);		//ȯ��¼�
CString strODRV_FTOP_DCD = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "ODRV_FTOP_DCD", nRow);		//�ؿ��Ļ������ɼǱ����ڵ�
CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
CString strPRC_DCPN_BLW_LNG = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "PRC_DCPN_BLW_LNG", nRow);		//���ݼҼ������ϱ���
CString strINDC_PRC = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "INDC_PRC", nRow);		//ǥ�ð���
CString strBSN_DT = m_CommAgent.GetTranOutputData("OTS5919Q41", "OTS5919Q41_out_sub01", "BSN_DT", nRow);		//��������
