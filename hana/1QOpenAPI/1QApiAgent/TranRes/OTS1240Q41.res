BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1240Q41, TR_NAME=OFSü��ܰ����ֹ�ü�᳻����ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1240Q41_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=4, ITEM=INQ_END_DT, TYPE=string, SIZE=8, CAPTION=��ȸ��������;
			 INDEX=5, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=6, ITEM=SCTS_DVSN, TYPE=string, SIZE=1, CAPTION=�������Ǳ���;
			 INDEX=7, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
			 INDEX=8, ITEM=INP_MKT_DCD, TYPE=string, SIZE=1, CAPTION=�Է½��屸���ڵ�;
			 INDEX=9, ITEM=ORDR_STTS_CD, TYPE=string, SIZE=2, CAPTION=�ֹ������ڵ�;
			 INDEX=10, ITEM=CRDT_DCD, TYPE=string, SIZE=2, CAPTION=�ſ뱸���ڵ�;
			 INDEX=11, ITEM=COMM_MDIA_DVSN, TYPE=string, SIZE=2, CAPTION=��Ÿ�ü����;
			 INDEX=12, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ֹ��Ϸù�ȣ;
			 INDEX=13, ITEM=ORDR_ORD, TYPE=string, SIZE=1, CAPTION=�ֹ�����;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1240Q41_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=SELL_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=�ŵ�ü�����;
			 INDEX=1, ITEM=SELL_CNCS_AMT, TYPE=string, SIZE=19, CAPTION=�ŵ�ü��ݾ�;
			 INDEX=2, ITEM=BUY_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=�ż�ü�����;
			 INDEX=3, ITEM=BUY_CNCS_AMT, TYPE=string, SIZE=19, CAPTION=�ż�ü��ݾ�;
			 INDEX=4, ITEM=CSGN_ACNT_NM, TYPE=string, SIZE=80, CAPTION=��Ź���¸�;
		END_OUTPUT0_ITEM

		REC_NAME=OTS1240Q41_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ֹ��Ϸù�ȣ;
			 INDEX=1, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=���ֹ��Ϸù�ȣ;
			 INDEX=2, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=3, ITEM=SELL_BUY_DCD_NM, TYPE=string, SIZE=40, CAPTION=�ŵ��ż������ڵ��;
			 INDEX=4, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=5, ITEM=ITG_BOND_ORDR_UNPR, TYPE=string, SIZE=17, CAPTION=�峻ä���ֹ��ܰ�;
			 INDEX=6, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ��ܿ�����;
			 INDEX=7, ITEM=COMM_MDIA_DCD_NM, TYPE=string, SIZE=24, CAPTION=��Ÿ�ü�����ڵ��;
			 INDEX=8, ITEM=ORDR_TM, TYPE=string, SIZE=6, CAPTION=�ֹ��ð�;
			 INDEX=9, ITEM=RVSE_CNCL_DVSN_NM, TYPE=string, SIZE=40, CAPTION=������ұ��и�;
			 INDEX=10, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=��ǰ��;
			 INDEX=11, ITEM=NMPR_DVSN_NM, TYPE=string, SIZE=80, CAPTION=ȣ�����и�;
			 INDEX=12, ITEM=SMM_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=�հ�ü�����;
			 INDEX=13, ITEM=ITG_BOND_CNCS_UNPR, TYPE=string, SIZE=17, CAPTION=�峻ä��ü��ܰ�;
			 INDEX=14, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=ü�����;
			 INDEX=15, ITEM=PRCS_STTS_NM, TYPE=string, SIZE=20, CAPTION=ó�����¸�;
			 INDEX=16, ITEM=LOAN_SN, TYPE=string, SIZE=11, CAPTION=�����Ϸù�ȣ;
			 INDEX=17, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=18, ITEM=BDCD, TYPE=string, SIZE=5, CAPTION=�����ڵ�;
			 INDEX=19, ITEM=SCTS_DCD, TYPE=string, SIZE=2, CAPTION=�������Ǳ����ڵ�;
			 INDEX=20, ITEM=TRDE_STL_DE_DCD, TYPE=string, SIZE=1, CAPTION=�ŸŰ����ϱ����ڵ�;
			 INDEX=21, ITEM=DETL_PRCS_DVSN, TYPE=string, SIZE=1, CAPTION=��ó������;
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
CString strORDR_DT;		//�ֹ�����
CString strINQ_END_DT;		//��ȸ��������
CString strPRDT_CD;		//��ǰ�ڵ�
CString strSCTS_DVSN;		//�������Ǳ���
CString strSELL_BUY_DCD;		//�ŵ��ż������ڵ�
CString strINP_MKT_DCD;		//�Է½��屸���ڵ�
CString strORDR_STTS_CD;		//�ֹ������ڵ�
CString strCRDT_DCD;		//�ſ뱸���ڵ�
CString strCOMM_MDIA_DVSN;		//��Ÿ�ü����
CString strORDR_SN;		//�ֹ��Ϸù�ȣ
CString strORDR_ORD;		//�ֹ�����

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "ORDR_DT", strORDR_DT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "INQ_END_DT", strINQ_END_DT);		//��ȸ��������
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "SCTS_DVSN", strSCTS_DVSN);		//�������Ǳ���
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//�ŵ��ż������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "INP_MKT_DCD", strINP_MKT_DCD);		//�Է½��屸���ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "ORDR_STTS_CD", strORDR_STTS_CD);		//�ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "CRDT_DCD", strCRDT_DCD);		//�ſ뱸���ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "COMM_MDIA_DVSN", strCOMM_MDIA_DVSN);		//��Ÿ�ü����
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "ORDR_SN", strORDR_SN);		//�ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1240Q41", "OTS1240Q41_in", "ORDR_ORD", strORDR_ORD);		//�ֹ�����




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strSELL_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out", "SELL_CNCS_QNT", 0);		//�ŵ�ü�����
CString strSELL_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out", "SELL_CNCS_AMT", 0);		//�ŵ�ü��ݾ�
CString strBUY_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out", "BUY_CNCS_QNT", 0);		//�ż�ü�����
CString strBUY_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out", "BUY_CNCS_AMT", 0);		//�ż�ü��ݾ�
CString strCSGN_ACNT_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out", "CSGN_ACNT_NM", 0);		//��Ź���¸�
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ORDR_SN", nRow);		//�ֹ��Ϸù�ȣ
CString strOR_ORDR_SN = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "OR_ORDR_SN", nRow);		//���ֹ��Ϸù�ȣ
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
CString strSELL_BUY_DCD_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "SELL_BUY_DCD_NM", nRow);		//�ŵ��ż������ڵ��
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
CString strITG_BOND_ORDR_UNPR = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ITG_BOND_ORDR_UNPR", nRow);		//�峻ä���ֹ��ܰ�
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
CString strCOMM_MDIA_DCD_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "COMM_MDIA_DCD_NM", nRow);		//��Ÿ�ü�����ڵ��
CString strORDR_TM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ORDR_TM", nRow);		//�ֹ��ð�
CString strRVSE_CNCL_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "RVSE_CNCL_DVSN_NM", nRow);		//������ұ��и�
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "PRDT_NM", nRow);		//��ǰ��
CString strNMPR_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "NMPR_DVSN_NM", nRow);		//ȣ�����и�
CString strSMM_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "SMM_CNCS_QNT", nRow);		//�հ�ü�����
CString strITG_BOND_CNCS_UNPR = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ITG_BOND_CNCS_UNPR", nRow);		//�峻ä��ü��ܰ�
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "CNCS_QNT", nRow);		//ü�����
CString strPRCS_STTS_NM = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "PRCS_STTS_NM", nRow);		//ó�����¸�
CString strLOAN_SN = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "LOAN_SN", nRow);		//�����Ϸù�ȣ
CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "ORDR_DT", nRow);		//�ֹ�����
CString strBDCD = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "BDCD", nRow);		//�����ڵ�
CString strSCTS_DCD = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "SCTS_DCD", nRow);		//�������Ǳ����ڵ�
CString strTRDE_STL_DE_DCD = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "TRDE_STL_DE_DCD", nRow);		//�ŸŰ����ϱ����ڵ�
CString strDETL_PRCS_DVSN = m_CommAgent.GetTranOutputData("OTS1240Q41", "OTS1240Q41_out_sub01", "DETL_PRCS_DVSN", nRow);		//��ó������
