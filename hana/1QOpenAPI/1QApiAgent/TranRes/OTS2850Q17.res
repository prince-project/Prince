BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2850Q17, TR_NAME=���¿�Ź�ݼ��γ���, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2850Q17_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2850Q17_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=OPMK_DPST_TOT_AMT, TYPE=string, SIZE=19, CAPTION=���忹Ź�ѱݾ�;
			 INDEX=1, ITEM=OPMK_DPST_CSH, TYPE=string, SIZE=19, CAPTION=���忹Ź����;
			 INDEX=2, ITEM=OPMK_DPST_SBST_AMT, TYPE=string, SIZE=19, CAPTION=���忹Ź���ݾ�;
			 INDEX=3, ITEM=FTR_EXCAL_DEB_AMT, TYPE=string, SIZE=19, CAPTION=�����������ݱݾ�;
			 INDEX=4, ITEM=OPT_STL_DEB_AMT, TYPE=string, SIZE=19, CAPTION=�ɼǰ������ݱݾ�;
			 INDEX=5, ITEM=FEE_SMM_AMT, TYPE=string, SIZE=19, CAPTION=�������հ�ݾ�;
			 INDEX=6, ITEM=RNDR_SMM, TYPE=string, SIZE=19, CAPTION=������հ�;
			 INDEX=7, ITEM=EVL_DPST_TOT_AMT, TYPE=string, SIZE=19, CAPTION=�򰡿�Ź�ѱݾ�;
			 INDEX=8, ITEM=FTR_RLZ_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=�����������ͱݾ�;
			 INDEX=9, ITEM=OPT_RLZ_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=�ɼǽ������ͱݾ�;
			 INDEX=10, ITEM=FTR_FEE, TYPE=string, SIZE=19, CAPTION=����������;
			 INDEX=11, ITEM=RCTM_AMT, TYPE=string, SIZE=19, CAPTION=�Աݱݾ�;
			 INDEX=12, ITEM=EVL_DPST_CSH, TYPE=string, SIZE=19, CAPTION=�򰡿�Ź����;
			 INDEX=13, ITEM=FTR_EVL_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=�����򰡼��ͱݾ�;
			 INDEX=14, ITEM=OPT_EVL_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=�ɼ��򰡼��ͱݾ�;
			 INDEX=15, ITEM=OPT_FEE, TYPE=string, SIZE=19, CAPTION=�ɼǼ�����;
			 INDEX=16, ITEM=DRWG_AMT, TYPE=string, SIZE=19, CAPTION=��ݱݾ�;
			 INDEX=17, ITEM=STL_DPST_TOT_AMT, TYPE=string, SIZE=19, CAPTION=������Ź�ѱݾ�;
			 INDEX=18, ITEM=DPST_TOT_AMT, TYPE=string, SIZE=19, CAPTION=��Ź�ѱݾ�;
			 INDEX=19, ITEM=CSGN_WMY_TOT_AMT, TYPE=string, SIZE=19, CAPTION=��Ź���ű��ѱݾ�;
			 INDEX=20, ITEM=ADIT_WMY_TOT_AMT, TYPE=string, SIZE=19, CAPTION=�߰����ű��ѱݾ�;
			 INDEX=21, ITEM=ORDR_PSBL_TOT_AMT, TYPE=string, SIZE=19, CAPTION=�ֹ������ѱݾ�;
			 INDEX=22, ITEM=WDRW_PSBL_TOT_AMT, TYPE=string, SIZE=19, CAPTION=���Ⱑ���ѱݾ�;
			 INDEX=23, ITEM=DPST_CSH, TYPE=string, SIZE=19, CAPTION=��Ź����;
			 INDEX=24, ITEM=CSGN_WMY_CSH, TYPE=string, SIZE=19, CAPTION=��Ź���ű�����;
			 INDEX=25, ITEM=ADIT_WMY_CSH, TYPE=string, SIZE=19, CAPTION=�߰����ű�����;
			 INDEX=26, ITEM=ORDR_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=�ֹ���������;
			 INDEX=27, ITEM=WDRW_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=���Ⱑ������;
			 INDEX=28, ITEM=DPST_SBST_AMT, TYPE=string, SIZE=19, CAPTION=��Ź���ݾ�;
			 INDEX=29, ITEM=WMY_SBST_AMT, TYPE=string, SIZE=19, CAPTION=���űݴ��ݾ�;
			 INDEX=30, ITEM=ADIT_WMY_SBST_AMT, TYPE=string, SIZE=19, CAPTION=�߰����űݴ��ݾ�;
			 INDEX=31, ITEM=ORDR_PSBL_SBST_AMT, TYPE=string, SIZE=19, CAPTION=�ֹ����ɴ��ݾ�;
			 INDEX=32, ITEM=WDRW_PSBL_SBST_AMT, TYPE=string, SIZE=19, CAPTION=���Ⱑ�ɴ��ݾ�;
			 INDEX=33, ITEM=FTR_USTL_TOT_QNT, TYPE=string, SIZE=19, CAPTION=�����̰����Ѽ���;
			 INDEX=34, ITEM=OPT_USTL_TOT_QNT, TYPE=string, SIZE=19, CAPTION=�ɼǹ̰����Ѽ���;
			 INDEX=35, ITEM=FTR_CTRC_TOT_AMT, TYPE=string, SIZE=19, CAPTION=���������ѱݾ�;
			 INDEX=36, ITEM=OPT_CTRC_TOT_AMT, TYPE=string, SIZE=19, CAPTION=�ɼǾ����ѱݾ�;
			 INDEX=37, ITEM=FTR_TR_TOT_QNT, TYPE=string, SIZE=19, CAPTION=�����ŷ��Ѽ���;
			 INDEX=38, ITEM=OPT_TR_TOT_QNT, TYPE=string, SIZE=19, CAPTION=�ɼǰŷ��Ѽ���;
			 INDEX=39, ITEM=FTR_SELL_USTL_QNT, TYPE=string, SIZE=19, CAPTION=�����ŵ��̰�������;
			 INDEX=40, ITEM=OPT_SELL_USTL_QNT, TYPE=string, SIZE=19, CAPTION=�ɼǸŵ��̰�������;
			 INDEX=41, ITEM=FTR_SELL_CTRC_AMT, TYPE=string, SIZE=19, CAPTION=�����ŵ������ݾ�;
			 INDEX=42, ITEM=OPT_SELL_CTRC_AMT, TYPE=string, SIZE=19, CAPTION=�ɼǸŵ������ݾ�;
			 INDEX=43, ITEM=FTR_SELL_TR_QNT, TYPE=string, SIZE=19, CAPTION=�����ŵ��ŷ�����;
			 INDEX=44, ITEM=OPT_SELL_TR_QNT, TYPE=string, SIZE=19, CAPTION=�ɼǸŵ��ŷ�����;
			 INDEX=45, ITEM=FTR_BUY_USTL_QNT, TYPE=string, SIZE=19, CAPTION=�����ż��̰�������;
			 INDEX=46, ITEM=OPT_BUY_USTL_QNT, TYPE=string, SIZE=19, CAPTION=�ɼǸż��̰�������;
			 INDEX=47, ITEM=FTR_BUY_CTRC_AMT, TYPE=string, SIZE=19, CAPTION=�����ż������ݾ�;
			 INDEX=48, ITEM=OPT_BUY_CTRC_AMT, TYPE=string, SIZE=19, CAPTION=�ɼǸż������ݾ�;
			 INDEX=49, ITEM=FTR_BUY_TR_QNT, TYPE=string, SIZE=19, CAPTION=�����ż��ŷ�����;
			 INDEX=50, ITEM=OPT_BUY_TR_QNT, TYPE=string, SIZE=19, CAPTION=�ɼǸż��ŷ�����;
			 INDEX=51, ITEM=NOW_TOT_WMY_RT, TYPE=string, SIZE=17, CAPTION=���������ű���;
			 INDEX=52, ITEM=CSH_WMY_RT, TYPE=string, SIZE=17, CAPTION=�������ű���;
			 INDEX=53, ITEM=MNTN_WMY, TYPE=string, SIZE=19, CAPTION=�������ű�;
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

m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q17", "OTS2850Q17_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q17", "OTS2850Q17_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q17", "OTS2850Q17_in", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strOPMK_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPMK_DPST_TOT_AMT", 0);		//���忹Ź�ѱݾ�
CString strOPMK_DPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPMK_DPST_CSH", 0);		//���忹Ź����
CString strOPMK_DPST_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPMK_DPST_SBST_AMT", 0);		//���忹Ź���ݾ�
CString strFTR_EXCAL_DEB_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_EXCAL_DEB_AMT", 0);		//�����������ݱݾ�
CString strOPT_STL_DEB_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_STL_DEB_AMT", 0);		//�ɼǰ������ݱݾ�
CString strFEE_SMM_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FEE_SMM_AMT", 0);		//�������հ�ݾ�
CString strRNDR_SMM = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "RNDR_SMM", 0);		//������հ�
CString strEVL_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "EVL_DPST_TOT_AMT", 0);		//�򰡿�Ź�ѱݾ�
CString strFTR_RLZ_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_RLZ_PFLS_AMT", 0);		//�����������ͱݾ�
CString strOPT_RLZ_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_RLZ_PFLS_AMT", 0);		//�ɼǽ������ͱݾ�
CString strFTR_FEE = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_FEE", 0);		//����������
CString strRCTM_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "RCTM_AMT", 0);		//�Աݱݾ�
CString strEVL_DPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "EVL_DPST_CSH", 0);		//�򰡿�Ź����
CString strFTR_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_EVL_PFLS_AMT", 0);		//�����򰡼��ͱݾ�
CString strOPT_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_EVL_PFLS_AMT", 0);		//�ɼ��򰡼��ͱݾ�
CString strOPT_FEE = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_FEE", 0);		//�ɼǼ�����
CString strDRWG_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DRWG_AMT", 0);		//��ݱݾ�
CString strSTL_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "STL_DPST_TOT_AMT", 0);		//������Ź�ѱݾ�
CString strDPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DPST_TOT_AMT", 0);		//��Ź�ѱݾ�
CString strCSGN_WMY_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "CSGN_WMY_TOT_AMT", 0);		//��Ź���ű��ѱݾ�
CString strADIT_WMY_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ADIT_WMY_TOT_AMT", 0);		//�߰����ű��ѱݾ�
CString strORDR_PSBL_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ORDR_PSBL_TOT_AMT", 0);		//�ֹ������ѱݾ�
CString strWDRW_PSBL_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WDRW_PSBL_TOT_AMT", 0);		//���Ⱑ���ѱݾ�
CString strDPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DPST_CSH", 0);		//��Ź����
CString strCSGN_WMY_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "CSGN_WMY_CSH", 0);		//��Ź���ű�����
CString strADIT_WMY_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ADIT_WMY_CSH", 0);		//�߰����ű�����
CString strORDR_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ORDR_PSBL_CSH", 0);		//�ֹ���������
CString strWDRW_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WDRW_PSBL_CSH", 0);		//���Ⱑ������
CString strDPST_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "DPST_SBST_AMT", 0);		//��Ź���ݾ�
CString strWMY_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WMY_SBST_AMT", 0);		//���űݴ��ݾ�
CString strADIT_WMY_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ADIT_WMY_SBST_AMT", 0);		//�߰����űݴ��ݾ�
CString strORDR_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "ORDR_PSBL_SBST_AMT", 0);		//�ֹ����ɴ��ݾ�
CString strWDRW_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "WDRW_PSBL_SBST_AMT", 0);		//���Ⱑ�ɴ��ݾ�
CString strFTR_USTL_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_USTL_TOT_QNT", 0);		//�����̰����Ѽ���
CString strOPT_USTL_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_USTL_TOT_QNT", 0);		//�ɼǹ̰����Ѽ���
CString strFTR_CTRC_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_CTRC_TOT_AMT", 0);		//���������ѱݾ�
CString strOPT_CTRC_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_CTRC_TOT_AMT", 0);		//�ɼǾ����ѱݾ�
CString strFTR_TR_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_TR_TOT_QNT", 0);		//�����ŷ��Ѽ���
CString strOPT_TR_TOT_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_TR_TOT_QNT", 0);		//�ɼǰŷ��Ѽ���
CString strFTR_SELL_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_SELL_USTL_QNT", 0);		//�����ŵ��̰�������
CString strOPT_SELL_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_SELL_USTL_QNT", 0);		//�ɼǸŵ��̰�������
CString strFTR_SELL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_SELL_CTRC_AMT", 0);		//�����ŵ������ݾ�
CString strOPT_SELL_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_SELL_CTRC_AMT", 0);		//�ɼǸŵ������ݾ�
CString strFTR_SELL_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_SELL_TR_QNT", 0);		//�����ŵ��ŷ�����
CString strOPT_SELL_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_SELL_TR_QNT", 0);		//�ɼǸŵ��ŷ�����
CString strFTR_BUY_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_BUY_USTL_QNT", 0);		//�����ż��̰�������
CString strOPT_BUY_USTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_BUY_USTL_QNT", 0);		//�ɼǸż��̰�������
CString strFTR_BUY_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_BUY_CTRC_AMT", 0);		//�����ż������ݾ�
CString strOPT_BUY_CTRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_BUY_CTRC_AMT", 0);		//�ɼǸż������ݾ�
CString strFTR_BUY_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "FTR_BUY_TR_QNT", 0);		//�����ż��ŷ�����
CString strOPT_BUY_TR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "OPT_BUY_TR_QNT", 0);		//�ɼǸż��ŷ�����
CString strNOW_TOT_WMY_RT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "NOW_TOT_WMY_RT", 0);		//���������ű���
CString strCSH_WMY_RT = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "CSH_WMY_RT", 0);		//�������ű���
CString strMNTN_WMY = m_CommAgent.GetTranOutputData("OTS2850Q17", "OTS2850Q17_out", "MNTN_WMY", 0);		//�������ű�
