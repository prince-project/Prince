BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1841Q00, TR_NAME=HTS�����ܰ�����ȸ1, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1841Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=INQ_DVSN, TYPE=string, SIZE=1, CAPTION=��ȸ����;
			 INDEX=4, ITEM=TRDE_CT_INCL_YN, TYPE=string, SIZE=1, CAPTION=�Ÿź�����Կ���;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1841Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=DACA, TYPE=string, SIZE=19, CAPTION=������;
			 INDEX=1, ITEM=NDY_PRSM_DACA, TYPE=string, SIZE=19, CAPTION=��������������;
			 INDEX=2, ITEM=NX_NDY_PRSM_DACA, TYPE=string, SIZE=19, CAPTION=����������������;
			 INDEX=3, ITEM=SBST_AMT, TYPE=string, SIZE=19, CAPTION=���ݾ�;
			 INDEX=4, ITEM=NDY_PRSM_SBST_AMT, TYPE=string, SIZE=19, CAPTION=�����������ݾ�;
			 INDEX=5, ITEM=NX_NDY_PRSM_SBST_AMT, TYPE=string, SIZE=19, CAPTION=�������������ݾ�;
			 INDEX=6, ITEM=BFDT_SELL_EXCAL_AMT, TYPE=string, SIZE=19, CAPTION=���ϸŵ�����ݾ�;
			 INDEX=7, ITEM=BFDT_BUY_EXCAL_AMT, TYPE=string, SIZE=19, CAPTION=���ϸż�����ݾ�;
			 INDEX=8, ITEM=TDAY_SELL_EXCAL_AMT, TYPE=string, SIZE=19, CAPTION=���ϸŵ�����ݾ�;
			 INDEX=9, ITEM=TDAY_BUY_EXCAL_AMT, TYPE=string, SIZE=19, CAPTION=���ϸż�����ݾ�;
			 INDEX=10, ITEM=CRDT_AMT, TYPE=string, SIZE=19, CAPTION=�ſ�ݾ�;
			 INDEX=11, ITEM=MRTG_RTO, TYPE=string, SIZE=17, CAPTION=�㺸����;
			 INDEX=12, ITEM=RQRM_MRTG_AMT, TYPE=string, SIZE=19, CAPTION=�ҿ�㺸�ݾ�;
			 INDEX=13, ITEM=MRTG_LACK_AMT, TYPE=string, SIZE=19, CAPTION=�㺸�����ݾ�;
			 INDEX=14, ITEM=MXM_ORDR_PSBL_AMT, TYPE=string, SIZE=20, CAPTION=�ִ��ֹ����ɱݾ�;
			 INDEX=15, ITEM=MINM_ORDR_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=�ּ��ֹ����ɱݾ�;
			 INDEX=16, ITEM=CRDT_MXM_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=�ſ��ִ밡�ɱݾ�;
			 INDEX=17, ITEM=ORDR_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=�ֹ���������;
			 INDEX=18, ITEM=ORDR_PSBL_SBST_AMT, TYPE=string, SIZE=19, CAPTION=�ֹ����ɴ��ݾ�;
			 INDEX=19, ITEM=DRWG_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=��ݰ��ɱݾ�;
			 INDEX=20, ITEM=NDY_DRWG_PSBL_AMT, TYPE=string, SIZE=19, CAPTION=������ݰ��ɱݾ�;
			 INDEX=21, ITEM=ACNT_EVL_AMT, TYPE=string, SIZE=19, CAPTION=�����򰡱ݾ�;
			 INDEX=22, ITEM=PCHS_TOT_AMT, TYPE=string, SIZE=19, CAPTION=�����ѱݾ�;
			 INDEX=23, ITEM=SCTS_EVL_AMT, TYPE=string, SIZE=19, CAPTION=���������򰡱ݾ�;
			 INDEX=24, ITEM=PFLS_AMT, TYPE=string, SIZE=19, CAPTION=���ͱݾ�;
			 INDEX=25, ITEM=EVL_PFLS_RT, TYPE=string, SIZE=17, CAPTION=�򰡼�����;
		END_OUTPUT0_ITEM

		REC_NAME=OTS1841Q00_out_sub02, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=�����ǰ�ڵ�;
			 INDEX=1, ITEM=PRDT_ABBR_NM, TYPE=string, SIZE=300, CAPTION=��ǰ����;
			 INDEX=2, ITEM=ITM_WMY_GRD_DCD, TYPE=string, SIZE=1, CAPTION=�������űݵ�ޱ����ڵ�;
			 INDEX=3, ITEM=INQ_BLN_DVSN_NM, TYPE=string, SIZE=30, CAPTION=��ȸ�ܰ��и�;
			 INDEX=4, ITEM=LOAN_DT, TYPE=string, SIZE=8, CAPTION=��������;
			 INDEX=5, ITEM=EXP_DT, TYPE=string, SIZE=8, CAPTION=��������;
			 INDEX=6, ITEM=LOAN_SN, TYPE=string, SIZE=11, CAPTION=�����Ϸù�ȣ;
			 INDEX=7, ITEM=STL_BLN_QNT, TYPE=string, SIZE=19, CAPTION=�����ܰ����;
			 INDEX=8, ITEM=CNCS_BLN_QNT, TYPE=string, SIZE=19, CAPTION=ü���ܰ����;
			 INDEX=9, ITEM=SELL_QNT, TYPE=string, SIZE=19, CAPTION=�ŵ�����;
			 INDEX=10, ITEM=BUY_QNT, TYPE=string, SIZE=19, CAPTION=�ż�����;
			 INDEX=11, ITEM=SELL_AVR_UNPR, TYPE=string, SIZE=17, CAPTION=�ŵ���մܰ�;
			 INDEX=12, ITEM=BUY_AVR_UNPR, TYPE=string, SIZE=19, CAPTION=�ż���մܰ�;
			 INDEX=13, ITEM=SELL_AMT, TYPE=string, SIZE=19, CAPTION=�ŵ��ݾ�;
			 INDEX=14, ITEM=BUY_AMT, TYPE=string, SIZE=19, CAPTION=�ż��ݾ�;
			 INDEX=15, ITEM=PV, TYPE=string, SIZE=19, CAPTION=���簡;
			 INDEX=16, ITEM=PFLS_AMT, TYPE=string, SIZE=19, CAPTION=���ͱݾ�;
			 INDEX=17, ITEM=PFLS_RT, TYPE=string, SIZE=20, CAPTION=������;
			 INDEX=18, ITEM=THDT_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=���ϼ��ͱݾ�;
			 INDEX=19, ITEM=THDT_PFLS_RT, TYPE=string, SIZE=19, CAPTION=���ϼ�����;
			 INDEX=20, ITEM=RMN_QNT, TYPE=string, SIZE=19, CAPTION=�ܿ�����;
			 INDEX=21, ITEM=EVL_AMT, TYPE=string, SIZE=19, CAPTION=�򰡱ݾ�;
			 INDEX=22, ITEM=CRDT_AMT, TYPE=string, SIZE=19, CAPTION=�ſ�ݾ�;
			 INDEX=23, ITEM=CRDT_INTR_AMT, TYPE=string, SIZE=19, CAPTION=�ſ����ڱݾ�;
			 INDEX=24, ITEM=PCHS_AMT, TYPE=string, SIZE=19, CAPTION=���Աݾ�;
			 INDEX=25, ITEM=FEE, TYPE=string, SIZE=19, CAPTION=������;
			 INDEX=26, ITEM=WHIT, TYPE=string, SIZE=19, CAPTION=������;
			 INDEX=27, ITEM=SELL_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=�ŵ����ɼ���;
			 INDEX=28, ITEM=INQ_BLN_DCD, TYPE=string, SIZE=2, CAPTION=��ȸ�ܰ����ڵ�;
			 INDEX=29, ITEM=FLC_RT, TYPE=string, SIZE=17, CAPTION=�����;
			 INDEX=30, ITEM=MARK_DCD, TYPE=string, SIZE=1, CAPTION=��ȣ�����ڵ�;
			 INDEX=31, ITEM=PRPT, TYPE=string, SIZE=17, CAPTION=���;
			 INDEX=32, ITEM=PCHS_UNPR, TYPE=string, SIZE=23, CAPTION=���Դܰ�;
			 INDEX=33, ITEM=SELL_PFLS_AMT, TYPE=string, SIZE=24, CAPTION=�ŵ����ͱݾ�;
			 INDEX=34, ITEM=SFGV, TYPE=string, SIZE=17, CAPTION=����;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strPWD;		//��й�ȣ
CString strINQ_DVSN;		//��ȸ����
CString strTRDE_CT_INCL_YN;		//�Ÿź�����Կ���

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "INQ_DVSN", strINQ_DVSN);		//��ȸ����
m_CommAgent.SetTranInputData(nRequestId, "OTS1841Q00", "OTS1841Q00_in", "TRDE_CT_INCL_YN", strTRDE_CT_INCL_YN);		//�Ÿź�����Կ���




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strDACA = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "DACA", nRow);		//������
CString strNDY_PRSM_DACA = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "NDY_PRSM_DACA", nRow);		//��������������
CString strNX_NDY_PRSM_DACA = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "NX_NDY_PRSM_DACA", nRow);		//����������������
CString strSBST_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "SBST_AMT", nRow);		//���ݾ�
CString strNDY_PRSM_SBST_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "NDY_PRSM_SBST_AMT", nRow);		//�����������ݾ�
CString strNX_NDY_PRSM_SBST_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "NX_NDY_PRSM_SBST_AMT", nRow);		//�������������ݾ�
CString strBFDT_SELL_EXCAL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "BFDT_SELL_EXCAL_AMT", nRow);		//���ϸŵ�����ݾ�
CString strBFDT_BUY_EXCAL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "BFDT_BUY_EXCAL_AMT", nRow);		//���ϸż�����ݾ�
CString strTDAY_SELL_EXCAL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "TDAY_SELL_EXCAL_AMT", nRow);		//���ϸŵ�����ݾ�
CString strTDAY_BUY_EXCAL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "TDAY_BUY_EXCAL_AMT", nRow);		//���ϸż�����ݾ�
CString strCRDT_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "CRDT_AMT", nRow);		//�ſ�ݾ�
CString strMRTG_RTO = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "MRTG_RTO", nRow);		//�㺸����
CString strRQRM_MRTG_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "RQRM_MRTG_AMT", nRow);		//�ҿ�㺸�ݾ�
CString strMRTG_LACK_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "MRTG_LACK_AMT", nRow);		//�㺸�����ݾ�
CString strMXM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "MXM_ORDR_PSBL_AMT", nRow);		//�ִ��ֹ����ɱݾ�
CString strMINM_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "MINM_ORDR_PSBL_AMT", nRow);		//�ּ��ֹ����ɱݾ�
CString strCRDT_MXM_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "CRDT_MXM_PSBL_AMT", nRow);		//�ſ��ִ밡�ɱݾ�
CString strORDR_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "ORDR_PSBL_CSH", nRow);		//�ֹ���������
CString strORDR_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "ORDR_PSBL_SBST_AMT", nRow);		//�ֹ����ɴ��ݾ�
CString strDRWG_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "DRWG_PSBL_AMT", nRow);		//��ݰ��ɱݾ�
CString strNDY_DRWG_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "NDY_DRWG_PSBL_AMT", nRow);		//������ݰ��ɱݾ�
CString strACNT_EVL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "ACNT_EVL_AMT", nRow);		//�����򰡱ݾ�
CString strPCHS_TOT_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "PCHS_TOT_AMT", nRow);		//�����ѱݾ�
CString strSCTS_EVL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "SCTS_EVL_AMT", nRow);		//���������򰡱ݾ�
CString strPFLS_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "PFLS_AMT", nRow);		//���ͱݾ�
CString strEVL_PFLS_RT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub01", "EVL_PFLS_RT", nRow);		//�򰡼�����
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
CString strPRDT_ABBR_NM = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PRDT_ABBR_NM", nRow);		//��ǰ����
CString strITM_WMY_GRD_DCD = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "ITM_WMY_GRD_DCD", nRow);		//�������űݵ�ޱ����ڵ�
CString strINQ_BLN_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "INQ_BLN_DVSN_NM", nRow);		//��ȸ�ܰ��и�
CString strLOAN_DT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "LOAN_DT", nRow);		//��������
CString strEXP_DT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "EXP_DT", nRow);		//��������
CString strLOAN_SN = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "LOAN_SN", nRow);		//�����Ϸù�ȣ
CString strSTL_BLN_QNT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "STL_BLN_QNT", nRow);		//�����ܰ����
CString strCNCS_BLN_QNT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "CNCS_BLN_QNT", nRow);		//ü���ܰ����
CString strSELL_QNT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SELL_QNT", nRow);		//�ŵ�����
CString strBUY_QNT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "BUY_QNT", nRow);		//�ż�����
CString strSELL_AVR_UNPR = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SELL_AVR_UNPR", nRow);		//�ŵ���մܰ�
CString strBUY_AVR_UNPR = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "BUY_AVR_UNPR", nRow);		//�ż���մܰ�
CString strSELL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SELL_AMT", nRow);		//�ŵ��ݾ�
CString strBUY_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "BUY_AMT", nRow);		//�ż��ݾ�
CString strPV = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PV", nRow);		//���簡
CString strPFLS_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PFLS_AMT", nRow);		//���ͱݾ�
CString strPFLS_RT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PFLS_RT", nRow);		//������
CString strTHDT_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "THDT_PFLS_AMT", nRow);		//���ϼ��ͱݾ�
CString strTHDT_PFLS_RT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "THDT_PFLS_RT", nRow);		//���ϼ�����
CString strRMN_QNT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "RMN_QNT", nRow);		//�ܿ�����
CString strEVL_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "EVL_AMT", nRow);		//�򰡱ݾ�
CString strCRDT_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "CRDT_AMT", nRow);		//�ſ�ݾ�
CString strCRDT_INTR_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "CRDT_INTR_AMT", nRow);		//�ſ����ڱݾ�
CString strPCHS_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PCHS_AMT", nRow);		//���Աݾ�
CString strFEE = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "FEE", nRow);		//������
CString strWHIT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "WHIT", nRow);		//������
CString strSELL_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SELL_PSBL_QNT", nRow);		//�ŵ����ɼ���
CString strINQ_BLN_DCD = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "INQ_BLN_DCD", nRow);		//��ȸ�ܰ����ڵ�
CString strFLC_RT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "FLC_RT", nRow);		//�����
CString strMARK_DCD = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "MARK_DCD", nRow);		//��ȣ�����ڵ�
CString strPRPT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PRPT", nRow);		//���
CString strPCHS_UNPR = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "PCHS_UNPR", nRow);		//���Դܰ�
CString strSELL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SELL_PFLS_AMT", nRow);		//�ŵ����ͱݾ�
CString strSFGV = m_CommAgent.GetTranOutputData("OTS1841Q00", "OTS1841Q00_out_sub02", "SFGV", nRow);		//����
