BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1201Q00, TR_NAME=�ֹ�ü�᳻��ü��ܰ���, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1201Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=3, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=4, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=5, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ֹ��Ϸù�ȣ;
			 INDEX=6, ITEM=CNCS_DVSN, TYPE=string, SIZE=1, CAPTION=ü�ᱸ��;
			 INDEX=7, ITEM=INQ_ORD_DVSN, TYPE=string, SIZE=1, CAPTION=��ȸ��������;
			 INDEX=8, ITEM=PRDT_DVSN, TYPE=string, SIZE=1, CAPTION=��ǰ����;
			 INDEX=9, ITEM=MKT_TR_DCD, TYPE=string, SIZE=2, CAPTION=����ŷ������ڵ�;
			 INDEX=10, ITEM=CRDT_TR_DCD, TYPE=string, SIZE=2, CAPTION=�ſ�ŷ������ڵ�;
			 INDEX=11, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ü�����ڵ�;
			 INDEX=12, ITEM=ORDR_PRCS_STTS_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ�ó�����±����ڵ�;
			 INDEX=13, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1201Q00_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=���������ڵ�;
			 INDEX=1, ITEM=SELL_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=�ŵ�ü�����;
			 INDEX=2, ITEM=SELL_CNCS_AMT, TYPE=string, SIZE=19, CAPTION=�ŵ�ü��ݾ�;
			 INDEX=3, ITEM=BUY_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=�ż�ü�����;
			 INDEX=4, ITEM=BUY_CNCS_AMT, TYPE=string, SIZE=19, CAPTION=�ż�ü��ݾ�;
		END_OUTPUT0_ITEM

		REC_NAME=OTS1201Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ֹ��Ϸù�ȣ;
			 INDEX=1, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=���ֹ��Ϸù�ȣ;
			 INDEX=2, ITEM=ORDR_RVSE_CNCL_DVSN_NM, TYPE=string, SIZE=40, CAPTION=�ֹ�������ұ��и�;
			 INDEX=3, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=4, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=�����ǰ�ڵ�;
			 INDEX=5, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=��ǰ��;
			 INDEX=6, ITEM=ORDR_DCD_NM, TYPE=string, SIZE=40, CAPTION=�ֹ������ڵ��;
			 INDEX=7, ITEM=NMPR_DVSN_NM, TYPE=string, SIZE=80, CAPTION=ȣ�����и�;
			 INDEX=8, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=9, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=ü�����;
			 INDEX=10, ITEM=ORDR_UNPR, TYPE=string, SIZE=19, CAPTION=�ֹ��ܰ�;
			 INDEX=11, ITEM=ITG_BOND_ORDR_UNPR, TYPE=string, SIZE=17, CAPTION=�峻ä���ֹ��ܰ�;
			 INDEX=12, ITEM=CNCS_UNPR, TYPE=string, SIZE=19, CAPTION=ü��ܰ�;
			 INDEX=13, ITEM=ITG_BOND_CNCS_UNPR, TYPE=string, SIZE=17, CAPTION=�峻ä��ü��ܰ�;
			 INDEX=14, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ��ܿ�����;
			 INDEX=15, ITEM=CNCS_QNT_SMM, TYPE=string, SIZE=19, CAPTION=ü������հ�;
			 INDEX=16, ITEM=ORDR_MDIA_NM, TYPE=string, SIZE=50, CAPTION=�ֹ���ü��;
			 INDEX=17, ITEM=ORDR_PRCS_STTS_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ�ó�����±����ڵ�;
			 INDEX=18, ITEM=ORDR_TM, TYPE=string, SIZE=6, CAPTION=�ֹ��ð�;
			 INDEX=19, ITEM=LOAN_DT, TYPE=string, SIZE=8, CAPTION=��������;
			 INDEX=20, ITEM=LOAN_SN, TYPE=string, SIZE=11, CAPTION=�����Ϸù�ȣ;
			 INDEX=21, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=22, ITEM=CNCS_DT, TYPE=string, SIZE=8, CAPTION=ü������;
			 INDEX=23, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=���������ڵ�;
			 INDEX=24, ITEM=SCTS_DCD, TYPE=string, SIZE=2, CAPTION=�������Ǳ����ڵ�;
			 INDEX=25, ITEM=TRDE_STL_DE_DCD, TYPE=string, SIZE=1, CAPTION=�ŸŰ����ϱ����ڵ�;
			 INDEX=26, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
			 INDEX=27, ITEM=ORDR_PRCS_STTS_DVSN_NM, TYPE=string, SIZE=40, CAPTION=�ֹ�ó�����±��и�;
			 INDEX=28, ITEM=CRDT_TR_DCD, TYPE=string, SIZE=2, CAPTION=�ſ�ŷ������ڵ�;
			 INDEX=29, ITEM=ORDR_KND_DCD, TYPE=string, SIZE=2, CAPTION=�ֹ����������ڵ�;
			 INDEX=30, ITEM=CSGN_TRDE_DCD, TYPE=string, SIZE=2, CAPTION=��Ź�Ÿű����ڵ�;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strPWD;		//��й�ȣ
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strORDR_DT;		//�ֹ�����
CString strPRDT_CD;		//��ǰ�ڵ�
CString strORDR_SN;		//�ֹ��Ϸù�ȣ
CString strCNCS_DVSN;		//ü�ᱸ��
CString strINQ_ORD_DVSN;		//��ȸ��������
CString strPRDT_DVSN;		//��ǰ����
CString strMKT_TR_DCD;		//����ŷ������ڵ�
CString strCRDT_TR_DCD;		//�ſ�ŷ������ڵ�
CString strCOMM_MDIA_DCD;		//��Ÿ�ü�����ڵ�
CString strORDR_PRCS_STTS_DCD;		//�ֹ�ó�����±����ڵ�
CString strSELL_BUY_DCD;		//�ŵ��ż������ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "ORDR_DT", strORDR_DT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "ORDR_SN", strORDR_SN);		//�ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "CNCS_DVSN", strCNCS_DVSN);		//ü�ᱸ��
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "INQ_ORD_DVSN", strINQ_ORD_DVSN);		//��ȸ��������
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "PRDT_DVSN", strPRDT_DVSN);		//��ǰ����
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "MKT_TR_DCD", strMKT_TR_DCD);		//����ŷ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "CRDT_TR_DCD", strCRDT_TR_DCD);		//�ſ�ŷ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "COMM_MDIA_DCD", strCOMM_MDIA_DCD);		//��Ÿ�ü�����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "ORDR_PRCS_STTS_DCD", strORDR_PRCS_STTS_DCD);		//�ֹ�ó�����±����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1201Q00", "OTS1201Q00_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//�ŵ��ż������ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strMNGM_BDCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out", "MNGM_BDCD", 0);		//���������ڵ�
CString strSELL_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out", "SELL_CNCS_QNT", 0);		//�ŵ�ü�����
CString strSELL_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out", "SELL_CNCS_AMT", 0);		//�ŵ�ü��ݾ�
CString strBUY_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out", "BUY_CNCS_QNT", 0);		//�ż�ü�����
CString strBUY_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out", "BUY_CNCS_AMT", 0);		//�ż�ü��ݾ�
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_SN", nRow);		//�ֹ��Ϸù�ȣ
CString strOR_ORDR_SN = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "OR_ORDR_SN", nRow);		//���ֹ��Ϸù�ȣ
CString strORDR_RVSE_CNCL_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_RVSE_CNCL_DVSN_NM", nRow);		//�ֹ�������ұ��и�
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "PRDT_NM", nRow);		//��ǰ��
CString strORDR_DCD_NM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_DCD_NM", nRow);		//�ֹ������ڵ��
CString strNMPR_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "NMPR_DVSN_NM", nRow);		//ȣ�����и�
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "CNCS_QNT", nRow);		//ü�����
CString strORDR_UNPR = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_UNPR", nRow);		//�ֹ��ܰ�
CString strITG_BOND_ORDR_UNPR = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ITG_BOND_ORDR_UNPR", nRow);		//�峻ä���ֹ��ܰ�
CString strCNCS_UNPR = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "CNCS_UNPR", nRow);		//ü��ܰ�
CString strITG_BOND_CNCS_UNPR = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ITG_BOND_CNCS_UNPR", nRow);		//�峻ä��ü��ܰ�
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
CString strCNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "CNCS_QNT_SMM", nRow);		//ü������հ�
CString strORDR_MDIA_NM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_MDIA_NM", nRow);		//�ֹ���ü��
CString strORDR_PRCS_STTS_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_PRCS_STTS_DCD", nRow);		//�ֹ�ó�����±����ڵ�
CString strORDR_TM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_TM", nRow);		//�ֹ��ð�
CString strLOAN_DT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "LOAN_DT", nRow);		//��������
CString strLOAN_SN = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "LOAN_SN", nRow);		//�����Ϸù�ȣ
CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_DT", nRow);		//�ֹ�����
CString strCNCS_DT = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "CNCS_DT", nRow);		//ü������
CString strMNGM_BDCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "MNGM_BDCD", nRow);		//���������ڵ�
CString strSCTS_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "SCTS_DCD", nRow);		//�������Ǳ����ڵ�
CString strTRDE_STL_DE_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "TRDE_STL_DE_DCD", nRow);		//�ŸŰ����ϱ����ڵ�
CString strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "SELL_BUY_DCD", nRow);		//�ŵ��ż������ڵ�
CString strORDR_PRCS_STTS_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_PRCS_STTS_DVSN_NM", nRow);		//�ֹ�ó�����±��и�
CString strCRDT_TR_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "CRDT_TR_DCD", nRow);		//�ſ�ŷ������ڵ�
CString strORDR_KND_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "ORDR_KND_DCD", nRow);		//�ֹ����������ڵ�
CString strCSGN_TRDE_DCD = m_CommAgent.GetTranOutputData("OTS1201Q00", "OTS1201Q00_out_sub01", "CSGN_TRDE_DCD", nRow);		//��Ź�Ÿű����ڵ�
