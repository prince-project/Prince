BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5921Q41, TR_NAME=�ֹ���Ȳ�ؿ�ON��ü, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5921Q41_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5921Q41_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=���հ��¹�ȣ;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=ODRV_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ��ֹ���ȣ;
			 INDEX=3, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=4, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ����ֹ���ȣ;
			 INDEX=5, ITEM=ODRV_MO_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ����ֹ���ȣ;
			 INDEX=6, ITEM=ORDR_GRUP_NO, TYPE=string, SIZE=16, CAPTION=�ֹ��׷��ȣ;
			 INDEX=7, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=8, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=9, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=����;
			 INDEX=10, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ��ŵ��ż������ڵ�;
			 INDEX=11, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ��ֹ�����;
			 INDEX=12, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=13, ITEM=RVSE_QNT, TYPE=string, SIZE=19, CAPTION=��������;
			 INDEX=14, ITEM=CNCL_QNT, TYPE=string, SIZE=19, CAPTION=��Ҽ���;
			 INDEX=15, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=ü�����;
			 INDEX=16, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ��ܿ�����;
			 INDEX=17, ITEM=ODRV_PRC_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ����ݱ����ڵ�;
			 INDEX=18, ITEM=CNCS_CND_DCD, TYPE=string, SIZE=1, CAPTION=ü�����Ǳ����ڵ�;
			 INDEX=19, ITEM=STLS_APPN_PRC, TYPE=string, SIZE=24, CAPTION=��ž�ν���������;
			 INDEX=20, ITEM=AVR_CNCS_PRC, TYPE=string, SIZE=24, CAPTION=���ü�ᰡ��;
			 INDEX=21, ITEM=CNCS_RT, TYPE=string, SIZE=17, CAPTION=ü����;
			 INDEX=22, ITEM=ODRV_NOW_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ����簡��;
			 INDEX=23, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ü�����ڵ�;
			 INDEX=24, ITEM=ODRV_ORDR_TP_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ��ֹ����������ڵ�;
			 INDEX=25, ITEM=ORDR_STTS_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ����±����ڵ�;
			 INDEX=26, ITEM=FCM_ODNO, TYPE=string, SIZE=60, CAPTION=FCM�ֹ���ȣ;
			 INDEX=27, ITEM=HND_EMPNO, TYPE=string, SIZE=7, CAPTION=���ۻ����ȣ;
			 INDEX=28, ITEM=ATHZ_IP_ADDR, TYPE=string, SIZE=39, CAPTION=����IP�ּ�;
			 INDEX=29, ITEM=EXCG_ACPT_TM, TYPE=string, SIZE=6, CAPTION=�ŷ��������ð�;
			 INDEX=30, ITEM=EXCG_CNCS_TM, TYPE=string, SIZE=6, CAPTION=�ŷ���ü��ð�;
			 INDEX=31, ITEM=ORDR_TM, TYPE=string, SIZE=6, CAPTION=�ֹ��ð�;
			 INDEX=32, ITEM=CNCS_TM, TYPE=string, SIZE=6, CAPTION=ü��ð�;
			 INDEX=33, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=��ȭ�ڵ�;
			 INDEX=34, ITEM=PRC_DCPN_BLW_LNG, TYPE=string, SIZE=6, CAPTION=���ݼҼ������ϱ���;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5921Q41", "OTS5921Q41_in_sub01", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5921Q41", "OTS5921Q41_in_sub01", "APNO", strAPNO);		//���»�ǰ��ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCANO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
CString strCTNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CTNO", nRow);		//���հ��´�ü��ȣ
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_ODNO", nRow);		//�ؿ��Ļ��ֹ���ȣ
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
CString strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_OR_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
CString strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_MO_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
CString strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ORDR_GRUP_NO", nRow);		//�ֹ��׷��ȣ
CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ORDR_DT", nRow);		//�ֹ�����
CString strAPNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "APNO", nRow);		//���»�ǰ��ȣ
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CUST_NM", nRow);		//����
CString strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//�ؿ��Ļ��ŵ��ż������ڵ�
CString strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_ORDR_PRC", nRow);		//�ؿ��Ļ��ֹ�����
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
CString strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "RVSE_QNT", nRow);		//��������
CString strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CNCL_QNT", nRow);		//��Ҽ���
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CNCS_QNT", nRow);		//ü�����
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
CString strODRV_PRC_DCD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_PRC_DCD", nRow);		//�ؿ��Ļ����ݱ����ڵ�
CString strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CNCS_CND_DCD", nRow);		//ü�����Ǳ����ڵ�
CString strSTLS_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "STLS_APPN_PRC", nRow);		//��ž�ν���������
CString strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "AVR_CNCS_PRC", nRow);		//���ü�ᰡ��
CString strCNCS_RT = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CNCS_RT", nRow);		//ü����
CString strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_NOW_PRC", nRow);		//�ؿ��Ļ����簡��
CString strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "COMM_MDIA_DCD", nRow);		//��Ÿ�ü�����ڵ�
CString strODRV_ORDR_TP_DCD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ODRV_ORDR_TP_DCD", nRow);		//�ؿ��Ļ��ֹ����������ڵ�
CString strORDR_STTS_DCD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ORDR_STTS_DCD", nRow);		//�ֹ����±����ڵ�
CString strFCM_ODNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "FCM_ODNO", nRow);		//FCM�ֹ���ȣ
CString strHND_EMPNO = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "HND_EMPNO", nRow);		//���ۻ����ȣ
CString strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ATHZ_IP_ADDR", nRow);		//����IP�ּ�
CString strEXCG_ACPT_TM = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "EXCG_ACPT_TM", nRow);		//�ŷ��������ð�
CString strEXCG_CNCS_TM = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "EXCG_CNCS_TM", nRow);		//�ŷ���ü��ð�
CString strORDR_TM = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "ORDR_TM", nRow);		//�ֹ��ð�
CString strCNCS_TM = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CNCS_TM", nRow);		//ü��ð�
CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
CString strPRC_DCPN_BLW_LNG = m_CommAgent.GetTranOutputData("OTS5921Q41", "OTS5921Q41_out_sub01", "PRC_DCPN_BLW_LNG", nRow);		//���ݼҼ������ϱ���
