BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5919Q51, TR_NAME=�̰���������ȲFX�������±׷캰, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5919Q51_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ��ŵ��ż������ڵ�;
		END_INPUT0_ITEM

		REC_NAME=OTS5919Q51_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		BEGIN_INPUT1_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT1_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5919Q51_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=PST_NO, TYPE=string, SIZE=16, CAPTION=�����ǹ�ȣ;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=���հ��¹�ȣ;
			 INDEX=3, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=4, ITEM=CNCS_DT, TYPE=string, SIZE=8, CAPTION=ü������;
			 INDEX=5, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=���������ڵ�;
			 INDEX=6, ITEM=ODRV_CSGN_SLF_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ���Ź�ڱⱸ���ڵ�;
			 INDEX=7, ITEM=FDM_UNQ_NO, TYPE=string, SIZE=3, CAPTION=�����Ͽ콺������ȣ;
			 INDEX=8, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=9, ITEM=NMPR_UNQ_NO, TYPE=string, SIZE=11, CAPTION=ȣ��������ȣ;
			 INDEX=10, ITEM=ODRV_SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��Ļ��ŵ��ż������ڵ�;
			 INDEX=11, ITEM=ODRV_CNCS_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ�ü�ᰡ��;
			 INDEX=12, ITEM=FRS_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=����ü�����;
			 INDEX=13, ITEM=CLR_QNT, TYPE=string, SIZE=19, CAPTION=û�����;
			 INDEX=14, ITEM=CNCS_CNCL_TR_QNT, TYPE=string, SIZE=19, CAPTION=ü����Ұŷ�����;
			 INDEX=15, ITEM=USTL_CTRC_QNT, TYPE=string, SIZE=19, CAPTION=�̰�����������;
			 INDEX=16, ITEM=USTL_CTRC_AMT2, TYPE=string, SIZE=24, CAPTION=�̰��������ݾ�2;
			 INDEX=17, ITEM=USTL_CTRC_AMT3, TYPE=string, SIZE=24, CAPTION=�̰��������ݾ�3;
			 INDEX=18, ITEM=CNCS_PIP_VALU_AMT, TYPE=string, SIZE=24, CAPTION=ü��PIP��ġ�ݾ�;
			 INDEX=19, ITEM=ODRV_CTRC_AMT, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ������ݾ�;
			 INDEX=20, ITEM=USTL_CTRC_AMT, TYPE=string, SIZE=24, CAPTION=�̰��������ݾ�;
			 INDEX=21, ITEM=CRSS_EXRT, TYPE=string, SIZE=23, CAPTION=����ȯ��;
			 INDEX=22, ITEM=ODRV_EXCAL_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ����갡��;
			 INDEX=23, ITEM=ODRV_EVL_PFLS_AMT, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ��򰡼��ͱݾ�;
			 INDEX=24, ITEM=PIP_VALU_AMT, TYPE=string, SIZE=24, CAPTION=PIP��ġ�ݾ�;
			 INDEX=25, ITEM=TRSL_EVL_PFLS_AMT, TYPE=string, SIZE=24, CAPTION=ȯ���򰡼��ͱݾ�;
			 INDEX=26, ITEM=EXCAL_CRSS_EXRT, TYPE=string, SIZE=23, CAPTION=���걳��ȯ��;
			 INDEX=27, ITEM=ONL_TR_YN, TYPE=string, SIZE=1, CAPTION=�¶��ΰŷ�����;
			 INDEX=28, ITEM=ODRV_CNCS_NO, TYPE=string, SIZE=8, CAPTION=�ؿ��Ļ�ü���ȣ;
			 INDEX=29, ITEM=HOLD_PST_YN, TYPE=string, SIZE=1, CAPTION=���������ǿ���;
			 INDEX=30, ITEM=USE_YN, TYPE=string, SIZE=1, CAPTION=��뿩��;
			 INDEX=31, ITEM=ODRV_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ��ֹ���ȣ;
			 INDEX=32, ITEM=ODRV_OR_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ����ֹ���ȣ;
			 INDEX=33, ITEM=ODRV_MO_ODNO, TYPE=string, SIZE=16, CAPTION=�ؿ��Ļ����ֹ���ȣ;
			 INDEX=34, ITEM=ORDR_GRUP_NO, TYPE=string, SIZE=16, CAPTION=�ֹ��׷��ȣ;
			 INDEX=35, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=36, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=����;
			 INDEX=37, ITEM=ODRV_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ��ֹ�����;
			 INDEX=38, ITEM=MKT_PRC_APLY_STUP_AMT, TYPE=string, SIZE=26, CAPTION=���尡�����뼳���ݾ�;
			 INDEX=39, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=40, ITEM=RVSE_QNT, TYPE=string, SIZE=19, CAPTION=��������;
			 INDEX=41, ITEM=CNCL_QNT, TYPE=string, SIZE=19, CAPTION=��Ҽ���;
			 INDEX=42, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=ü�����;
			 INDEX=43, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ��ܿ�����;
			 INDEX=44, ITEM=PRC_CND_DCD, TYPE=string, SIZE=1, CAPTION=�������Ǳ����ڵ�;
			 INDEX=45, ITEM=CNCS_CND_DCD, TYPE=string, SIZE=1, CAPTION=ü�����Ǳ����ڵ�;
			 INDEX=46, ITEM=SQ1_STLS_YN, TYPE=string, SIZE=1, CAPTION=1����ž�ν�����;
			 INDEX=47, ITEM=SQ1_APMPR_YN, TYPE=string, SIZE=1, CAPTION=1������������;
			 INDEX=48, ITEM=SQ1_DVSN_YN, TYPE=string, SIZE=1, CAPTION=1�����п���;
			 INDEX=49, ITEM=SQ1_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1����ž�ν�����;
			 INDEX=50, ITEM=SQ1_APPN_PRC, TYPE=string, SIZE=24, CAPTION=1����������;
			 INDEX=51, ITEM=SQ1_CHAS_STLS_PRC, TYPE=string, SIZE=24, CAPTION=1�����������Ű���;
			 INDEX=52, ITEM=CTRT_UN_AMT, TYPE=string, SIZE=24, CAPTION=�������ݾ�;
			 INDEX=53, ITEM=ORDR_DRCN_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ����ⱸ���ڵ�;
			 INDEX=54, ITEM=AVR_CNCS_PRC, TYPE=string, SIZE=24, CAPTION=���ü�ᰡ��;
			 INDEX=55, ITEM=ODRV_NOW_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��Ļ����簡��;
			 INDEX=56, ITEM=PRDT_CD2, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�2;
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

m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q51", "OTS5919Q51_in", "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD);		//�ؿ��Ļ��ŵ��ż������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q51", "OTS5919Q51_in_sub01", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q51", "OTS5919Q51_in_sub01", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS5919Q51", "OTS5919Q51_in_sub01", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strPST_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PST_NO", nRow);		//�����ǹ�ȣ
CString strCTNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CTNO", nRow);		//���հ��´�ü��ȣ
CString strCANO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
CString strAPNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "APNO", nRow);		//���»�ǰ��ȣ
CString strCNCS_DT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_DT", nRow);		//ü������
CString strMNGM_BDCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "MNGM_BDCD", nRow);		//���������ڵ�
CString strODRV_CSGN_SLF_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CSGN_SLF_DCD", nRow);		//�ؿ��Ļ���Ź�ڱⱸ���ڵ�
CString strFDM_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "FDM_UNQ_NO", nRow);		//�����Ͽ콺������ȣ
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
CString strNMPR_UNQ_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "NMPR_UNQ_NO", nRow);		//ȣ��������ȣ
CString strODRV_SELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_SELL_BUY_DCD", nRow);		//�ؿ��Ļ��ŵ��ż������ڵ�
CString strODRV_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CNCS_PRC", nRow);		//�ؿ��Ļ�ü�ᰡ��
CString strFRS_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "FRS_CNCS_QNT", nRow);		//����ü�����
CString strCLR_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CLR_QNT", nRow);		//û�����
CString strCNCS_CNCL_TR_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_CNCL_TR_QNT", nRow);		//ü����Ұŷ�����
CString strUSTL_CTRC_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_QNT", nRow);		//�̰�����������
CString strUSTL_CTRC_AMT2 = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_AMT2", nRow);		//�̰��������ݾ�2
CString strUSTL_CTRC_AMT3 = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_AMT3", nRow);		//�̰��������ݾ�3
CString strCNCS_PIP_VALU_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_PIP_VALU_AMT", nRow);		//ü��PIP��ġ�ݾ�
CString strODRV_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CTRC_AMT", nRow);		//�ؿ��Ļ������ݾ�
CString strUSTL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USTL_CTRC_AMT", nRow);		//�̰��������ݾ�
CString strCRSS_EXRT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CRSS_EXRT", nRow);		//����ȯ��
CString strODRV_EXCAL_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_EXCAL_PRC", nRow);		//�ؿ��Ļ����갡��
CString strODRV_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_EVL_PFLS_AMT", nRow);		//�ؿ��Ļ��򰡼��ͱݾ�
CString strPIP_VALU_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PIP_VALU_AMT", nRow);		//PIP��ġ�ݾ�
CString strTRSL_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "TRSL_EVL_PFLS_AMT", nRow);		//ȯ���򰡼��ͱݾ�
CString strEXCAL_CRSS_EXRT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "EXCAL_CRSS_EXRT", nRow);		//���걳��ȯ��
CString strONL_TR_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ONL_TR_YN", nRow);		//�¶��ΰŷ�����
CString strODRV_CNCS_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_CNCS_NO", nRow);		//�ؿ��Ļ�ü���ȣ
CString strHOLD_PST_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "HOLD_PST_YN", nRow);		//���������ǿ���
CString strUSE_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "USE_YN", nRow);		//��뿩��
CString strODRV_ODNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_ODNO", nRow);		//�ؿ��Ļ��ֹ���ȣ
CString strODRV_OR_ODNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_OR_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
CString strODRV_MO_ODNO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_MO_ODNO", nRow);		//�ؿ��Ļ����ֹ���ȣ
CString strORDR_GRUP_NO = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_GRUP_NO", nRow);		//�ֹ��׷��ȣ
CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_DT", nRow);		//�ֹ�����
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CUST_NM", nRow);		//����
CString strODRV_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_ORDR_PRC", nRow);		//�ؿ��Ļ��ֹ�����
CString strMKT_PRC_APLY_STUP_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "MKT_PRC_APLY_STUP_AMT", nRow);		//���尡�����뼳���ݾ�
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
CString strRVSE_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "RVSE_QNT", nRow);		//��������
CString strCNCL_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCL_QNT", nRow);		//��Ҽ���
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_QNT", nRow);		//ü�����
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
CString strPRC_CND_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PRC_CND_DCD", nRow);		//�������Ǳ����ڵ�
CString strCNCS_CND_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CNCS_CND_DCD", nRow);		//ü�����Ǳ����ڵ�
CString strSQ1_STLS_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_STLS_YN", nRow);		//1����ž�ν�����
CString strSQ1_APMPR_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_APMPR_YN", nRow);		//1������������
CString strSQ1_DVSN_YN = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_DVSN_YN", nRow);		//1�����п���
CString strSQ1_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_STLS_PRC", nRow);		//1����ž�ν�����
CString strSQ1_APPN_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_APPN_PRC", nRow);		//1����������
CString strSQ1_CHAS_STLS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "SQ1_CHAS_STLS_PRC", nRow);		//1�����������Ű���
CString strCTRT_UN_AMT = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "CTRT_UN_AMT", nRow);		//�������ݾ�
CString strORDR_DRCN_DCD = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ORDR_DRCN_DCD", nRow);		//�ֹ����ⱸ���ڵ�
CString strAVR_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "AVR_CNCS_PRC", nRow);		//���ü�ᰡ��
CString strODRV_NOW_PRC = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "ODRV_NOW_PRC", nRow);		//�ؿ��Ļ����簡��
CString strPRDT_CD2 = m_CommAgent.GetTranOutputData("OTS5919Q51", "OTS5919Q51_out_sub01", "PRDT_CD2", nRow);		//��ǰ�ڵ�2
