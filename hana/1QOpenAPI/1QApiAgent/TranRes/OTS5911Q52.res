BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5911Q52, TR_NAME=ü�ὺũ���ؿ�ONü�᳻����ȸ��, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5911Q52_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=���հ��¹�ȣ;
			 INDEX=1, ITEM=ODRV_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ��ֹ���ȣ;
			 INDEX=2, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=3, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ����ֹ���ȣ;
			 INDEX=4, ITEM=ODRV_MO_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ����ֹ���ȣ;
			 INDEX=5, ITEM=ORDR_GRUP_NO, TYPE=string, SIZE=16, CAPTION=�ֹ��׷��ȣ;
			 INDEX=6, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=7, ITEM=ACNT_PRDT_CD, TYPE=string, SIZE=2, CAPTION=���»�ǰ�ڵ�;
			 INDEX=8, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=����;
			 INDEX=9, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
			 INDEX=10, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ��ֹ�����;
			 INDEX=11, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=12, ITEM=RVSE_QNT, TYPE=string, SIZE=19, CAPTION=��������;
			 INDEX=13, ITEM=CNCL_QNT, TYPE=string, SIZE=19, CAPTION=��Ҽ���;
			 INDEX=14, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=ü�����;
			 INDEX=15, ITEM=RMN_QNT, TYPE=string, SIZE=19, CAPTION=�ܿ�����;
			 INDEX=16, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=�������Ǳ����ڵ�;
			 INDEX=17, ITEM=CNCS_CND_DCD, TYPE=string, SIZE=1, CAPTION=ü�����Ǳ����ڵ�;
			 INDEX=18, ITEM=SQ1_APPN_PRC, TYPE=string, SIZE=24, CAPTION=1����������;
			 INDEX=19, ITEM=AVR_CNCS_PRC, TYPE=string, SIZE=24, CAPTION=���ü�ᰡ��;
			 INDEX=20, ITEM=CNCS_RT, TYPE=string, SIZE=17, CAPTION=ü����;
			 INDEX=21, ITEM=NOW_PRC, TYPE=string, SIZE=22, CAPTION=���簡��;
			 INDEX=22, ITEM=MDIA_DCD, TYPE=string, SIZE=2, CAPTION=��ü�����ڵ�;
			 INDEX=23, ITEM=ORDR_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ������ڵ�;
			 INDEX=24, ITEM=ORDR_STTS_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ����±����ڵ�;
			 INDEX=25, ITEM=FCM_ODNO, TYPE=string, SIZE=60, CAPTION=FCM�ֹ���ȣ;
			 INDEX=26, ITEM=USER_ID, TYPE=string, SIZE=7, CAPTION=�����ID;
			 INDEX=27, ITEM=ATHZ_IP_ADDR, TYPE=string, SIZE=39, CAPTION=����IP�ּ�;
			 INDEX=28, ITEM=ACPT_TM, TYPE=string, SIZE=6, CAPTION=�����ð�;
			 INDEX=29, ITEM=CNCS_TM, TYPE=string, SIZE=6, CAPTION=ü��ð�;
			 INDEX=30, ITEM=ACPL_ACPT_TM, TYPE=string, SIZE=6, CAPTION=���������ð�;
			 INDEX=31, ITEM=CNCS_DETL_DTM, TYPE=string, SIZE=17, CAPTION=ü����Ͻ�;
			 INDEX=32, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=��ȭ�ڵ�;
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

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5911Q52", "OTS5911Q52_in_sub01", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5911Q52", "OTS5911Q52_in_sub01", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5911Q52", "OTS5911Q52_in_sub01", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCANO = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ODRV_ODNO", nRow);		//�ؿ��Ļ��ֹ���ȣ
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
CString strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ODRV_OR_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
CString strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ODRV_MO_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
CString strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ORDR_GRUP_NO", nRow);		//�ֹ��׷��ȣ
CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ORDR_DT", nRow);		//�ֹ�����
CString strACNT_PRDT_CD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ACNT_PRDT_CD", nRow);		//���»�ǰ�ڵ�
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CUST_NM", nRow);		//����
CString strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "SELL_BUY_DCD", nRow);		//�ŵ��ż������ڵ�
CString strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ODRV_ORDR_PRC", nRow);		//�ؿ��Ļ��ֹ�����
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
CString strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "RVSE_QNT", nRow);		//��������
CString strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CNCL_QNT", nRow);		//��Ҽ���
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CNCS_QNT", nRow);		//ü�����
CString strRMN_QNT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "RMN_QNT", nRow);		//�ܿ�����
CString strPRC_CND_DCD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "PRC_CND_DCD", nRow);		//�������Ǳ����ڵ�
CString strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CNCS_CND_DCD", nRow);		//ü�����Ǳ����ڵ�
CString strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "SQ1_APPN_PRC", nRow);		//1����������
CString strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "AVR_CNCS_PRC", nRow);		//���ü�ᰡ��
CString strCNCS_RT = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CNCS_RT", nRow);		//ü����
CString strNOW_PRC = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "NOW_PRC", nRow);		//���簡��
CString strMDIA_DCD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "MDIA_DCD", nRow);		//��ü�����ڵ�
CString strORDR_DCD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ORDR_DCD", nRow);		//�ֹ������ڵ�
CString strORDR_STTS_DCD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ORDR_STTS_DCD", nRow);		//�ֹ����±����ڵ�
CString strFCM_ODNO = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "FCM_ODNO", nRow);		//FCM�ֹ���ȣ
CString strUSER_ID = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "USER_ID", nRow);		//�����ID
CString strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ATHZ_IP_ADDR", nRow);		//����IP�ּ�
CString strACPT_TM = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ACPT_TM", nRow);		//�����ð�
CString strCNCS_TM = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CNCS_TM", nRow);		//ü��ð�
CString strACPL_ACPT_TM = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "ACPL_ACPT_TM", nRow);		//���������ð�
CString strCNCS_DETL_DTM = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CNCS_DETL_DTM", nRow);		//ü����Ͻ�
CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5911Q52", "OTS5911Q52_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
