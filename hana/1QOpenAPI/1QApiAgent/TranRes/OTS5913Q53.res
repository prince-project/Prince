BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5913Q53, TR_NAME=FX������ü�᳻����ȸ��������, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5913Q53_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=INQ_STRT_DT, TYPE=string, SIZE=8, CAPTION=��ȸ��������;
			 INDEX=1, ITEM=INQ_END_DT, TYPE=string, SIZE=8, CAPTION=��ȸ��������;
			 INDEX=2, ITEM=SORT_MTH, TYPE=string, SIZE=1, CAPTION=���Ĺ��;
			 INDEX=3, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=4, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=5, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=6, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=���º�й�ȣ;
			 INDEX=7, ITEM=INQ_DVSN, TYPE=string, SIZE=1, CAPTION=��ȸ����;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5913Q53_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=FDM_UNQ_NO_PRDT_CD, TYPE=string, SIZE=35, CAPTION=�����Ͽ콺������ȣ��ǰ�ڵ�;
			 INDEX=1, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=���հ��¹�ȣ;
			 INDEX=2, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=3, ITEM=ODRV_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ��ֹ���ȣ;
			 INDEX=4, ITEM=FDM_UNQ_NO, TYPE=string, SIZE=3, CAPTION=�����Ͽ콺������ȣ;
			 INDEX=5, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=6, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ����ֹ���ȣ;
			 INDEX=7, ITEM=ODRV_MO_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ����ֹ���ȣ;
			 INDEX=8, ITEM=ORDR_GRUP_NO, TYPE=string, SIZE=16, CAPTION=�ֹ��׷��ȣ;
			 INDEX=9, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=10, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=11, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=����;
			 INDEX=12, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ��ŵ��ż������ڵ�;
			 INDEX=13, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ��ֹ�����;
			 INDEX=14, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=15, ITEM=RVSE_QNT, TYPE=string, SIZE=19, CAPTION=��������;
			 INDEX=16, ITEM=CNCL_QNT, TYPE=string, SIZE=19, CAPTION=��Ҽ���;
			 INDEX=17, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=ü�����;
			 INDEX=18, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ��ܿ�����;
			 INDEX=19, ITEM=CTRT_UN_AMT, TYPE=string, SIZE=24, CAPTION=�������ݾ�;
			 INDEX=20, ITEM=FX_ORDR_TOT_AMT, TYPE=string, SIZE=24, CAPTION=FX�ֹ��ѱݾ�;
			 INDEX=21, ITEM=FX_RMN_TOT_AMT, TYPE=string, SIZE=24, CAPTION=FX�ܿ��ѱݾ�;
			 INDEX=22, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=�������Ǳ����ڵ�;
			 INDEX=23, ITEM=CNCS_CND_DCD, TYPE=string, SIZE=1, CAPTION=ü�����Ǳ����ڵ�;
			 INDEX=24, ITEM=SQ1_STLS_YN, TYPE=string, SIZE=1, CAPTION=1����ž�ν�����;
			 INDEX=25, ITEM=SQ1_APMPR_YN, TYPE=string, SIZE=1, CAPTION=1������������;
			 INDEX=26, ITEM=SQ1_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1����ž�ν�����;
			 INDEX=27, ITEM=SQ1_APPN_PRC, TYPE=string, SIZE=24, CAPTION=1����������;
			 INDEX=28, ITEM=SQ1_CHAS_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1�����������Ű���;
			 INDEX=29, ITEM=SQ2_STLS_YN, TYPE=string, SIZE=1, CAPTION=2����ž�ν�����;
			 INDEX=30, ITEM=SQ2_APMPR_YN, TYPE=string, SIZE=1, CAPTION=2������������;
			 INDEX=31, ITEM=SQ2_STLS_PRC, TYPE=string, SIZE=24, CAPTION=2����ž�ν�����;
			 INDEX=32, ITEM=SQ2_APPN_PRC, TYPE=string, SIZE=24, CAPTION=2����������;
			 INDEX=33, ITEM=SQ2_CHAS_STLS_PRC, TYPE=string, SIZE=24, CAPTION=2�����������Ű���;
			 INDEX=34, ITEM=AVR_CNCS_PRC, TYPE=string, SIZE=24, CAPTION=���ü�ᰡ��;
			 INDEX=35, ITEM=CNCS_RT, TYPE=string, SIZE=17, CAPTION=ü����;
			 INDEX=36, ITEM=ODRV_NOW_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ����簡��;
			 INDEX=37, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ü�����ڵ�;
			 INDEX=38, ITEM=ODRV_ORDR_TP_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ��ֹ����������ڵ�;
			 INDEX=39, ITEM=ORDR_STTS_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ����±����ڵ�;
			 INDEX=40, ITEM=FCM_ODNO, TYPE=string, SIZE=60, CAPTION=FCM�ֹ���ȣ;
			 INDEX=41, ITEM=USR_ID, TYPE=string, SIZE=20, CAPTION=�����ID;
			 INDEX=42, ITEM=ATHZ_IP_ADDR, TYPE=string, SIZE=39, CAPTION=����IP�ּ�;
			 INDEX=43, ITEM=EXCG_ACPT_TM, TYPE=string, SIZE=6, CAPTION=�ŷ��������ð�;
			 INDEX=44, ITEM=EXCG_CNCS_TM, TYPE=string, SIZE=6, CAPTION=�ŷ���ü��ð�;
			 INDEX=45, ITEM=ORDR_TM, TYPE=string, SIZE=6, CAPTION=�ֹ��ð�;
			 INDEX=46, ITEM=CNCS_TM, TYPE=string, SIZE=6, CAPTION=ü��ð�;
			 INDEX=47, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=��ȭ�ڵ�;
			 INDEX=48, ITEM=PRC_DCPN_BLW_LNG, TYPE=string, SIZE=6, CAPTION=���ݼҼ������ϱ���;
			 INDEX=49, ITEM=TRDE_PRC_DFRN_CTNS, TYPE=string, SIZE=50, CAPTION=�ŸŰ������̳���;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strINQ_STRT_DT;		//��ȸ��������
CString strINQ_END_DT;		//��ȸ��������
CString strSORT_MTH;		//���Ĺ��
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strPRDT_CD;		//��ǰ�ڵ�
CString strACNT_PWD;		//���º�й�ȣ
CString strINQ_DVSN;		//��ȸ����

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "INQ_STRT_DT", strINQ_STRT_DT);		//��ȸ��������
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "INQ_END_DT", strINQ_END_DT);		//��ȸ��������
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "SORT_MTH", strSORT_MTH);		//���Ĺ��
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5913Q53", "OTS5913Q53_in", "INQ_DVSN", strINQ_DVSN);		//��ȸ����




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strFDM_UNQ_NO_PRDT_CD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FDM_UNQ_NO_PRDT_CD", nRow);		//�����Ͽ콺������ȣ��ǰ�ڵ�
CString strCANO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
CString strCTNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CTNO", nRow);		//���հ��´�ü��ȣ
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_ODNO", nRow);		//�ؿ��Ļ��ֹ���ȣ
CString strFDM_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FDM_UNQ_NO", nRow);		//�����Ͽ콺������ȣ
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
CString strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_OR_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
CString strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_MO_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
CString strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_GRUP_NO", nRow);		//�ֹ��׷��ȣ
CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_DT", nRow);		//�ֹ�����
CString strAPNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "APNO", nRow);		//���»�ǰ��ȣ
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CUST_NM", nRow);		//����
CString strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//�ؿ��Ļ��ŵ��ż������ڵ�
CString strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_ORDR_PRC", nRow);		//�ؿ��Ļ��ֹ�����
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
CString strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "RVSE_QNT", nRow);		//��������
CString strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCL_QNT", nRow);		//��Ҽ���
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_QNT", nRow);		//ü�����
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
CString strCTRT_UN_AMT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CTRT_UN_AMT", nRow);		//�������ݾ�
CString strFX_ORDR_TOT_AMT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FX_ORDR_TOT_AMT", nRow);		//FX�ֹ��ѱݾ�
CString strFX_RMN_TOT_AMT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FX_RMN_TOT_AMT", nRow);		//FX�ܿ��ѱݾ�
CString strPRC_CND_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "PRC_CND_DCD", nRow);		//�������Ǳ����ڵ�
CString strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_CND_DCD", nRow);		//ü�����Ǳ����ڵ�
CString strSQ1_STLS_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_STLS_YN", nRow);		//1����ž�ν�����
CString strSQ1_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_APMPR_YN", nRow);		//1������������
CString strSQ1_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_STLS_PRC", nRow);		//1����ž�ν�����
CString strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_APPN_PRC", nRow);		//1����������
CString strSQ1_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ1_CHAS_STLS_PRC", nRow);		//1�����������Ű���
CString strSQ2_STLS_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_STLS_YN", nRow);		//2����ž�ν�����
CString strSQ2_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_APMPR_YN", nRow);		//2������������
CString strSQ2_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_STLS_PRC", nRow);		//2����ž�ν�����
CString strSQ2_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_APPN_PRC", nRow);		//2����������
CString strSQ2_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "SQ2_CHAS_STLS_PRC", nRow);		//2�����������Ű���
CString strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "AVR_CNCS_PRC", nRow);		//���ü�ᰡ��
CString strCNCS_RT = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_RT", nRow);		//ü����
CString strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_NOW_PRC", nRow);		//�ؿ��Ļ����簡��
CString strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "COMM_MDIA_DCD", nRow);		//��Ÿ�ü�����ڵ�
CString strODRV_ORDR_TP_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ODRV_ORDR_TP_DCD", nRow);		//�ؿ��Ļ��ֹ����������ڵ�
CString strORDR_STTS_DCD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_STTS_DCD", nRow);		//�ֹ����±����ڵ�
CString strFCM_ODNO = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "FCM_ODNO", nRow);		//FCM�ֹ���ȣ
CString strUSR_ID = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "USR_ID", nRow);		//�����ID
CString strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ATHZ_IP_ADDR", nRow);		//����IP�ּ�
CString strEXCG_ACPT_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "EXCG_ACPT_TM", nRow);		//�ŷ��������ð�
CString strEXCG_CNCS_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "EXCG_CNCS_TM", nRow);		//�ŷ���ü��ð�
CString strORDR_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "ORDR_TM", nRow);		//�ֹ��ð�
CString strCNCS_TM = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CNCS_TM", nRow);		//ü��ð�
CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
CString strPRC_DCPN_BLW_LNG = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "PRC_DCPN_BLW_LNG", nRow);		//���ݼҼ������ϱ���
CString strTRDE_PRC_DFRN_CTNS = m_CommAgent.GetTranOutputData("OTS5913Q53", "OTS5913Q53_out_sub01", "TRDE_PRC_DFRN_CTNS", nRow);		//�ŸŰ������̳���
