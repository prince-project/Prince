BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7703Q00, TR_NAME=API��CFD�ֹ�ü������ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7703Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=���������ڵ�;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=3, ITEM=SCTN_STRT_DT, TYPE=string, SIZE=8, CAPTION=������������;
			 INDEX=4, ITEM=SCTN_END_DT, TYPE=string, SIZE=8, CAPTION=������������;
			 INDEX=5, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
			 INDEX=6, ITEM=CFD_ODNO, TYPE=string, SIZE=11, CAPTION=CFD�ֹ���ȣ;
			 INDEX=7, ITEM=CFD_TRDE_DCD, TYPE=string, SIZE=1, CAPTION=CFD�Ÿű����ڵ�;
			 INDEX=8, ITEM=INQ_KND_DCD, TYPE=string, SIZE=1, CAPTION=��ȸ���������ڵ�;
			 INDEX=9, ITEM=INQ_ORD_DCD, TYPE=string, SIZE=1, CAPTION=��ȸ���������ڵ�;
			 INDEX=10, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7703Q00_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_BUY_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=CFD�ż�ü�����;
			 INDEX=1, ITEM=CFD_BUY_CNCS_AMT, TYPE=string, SIZE=23, CAPTION=CFD�ż�ü��ݾ�;
			 INDEX=2, ITEM=CFD_SELL_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=CFD�ŵ�ü�����;
			 INDEX=3, ITEM=CFD_SELL_CNCS_AMT, TYPE=string, SIZE=23, CAPTION=CFD�ŵ�ü��ݾ�;
		END_OUTPUT0_ITEM

		REC_NAME=OTS7703Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=CFD_ORDR_DT, TYPE=string, SIZE=8, CAPTION=CFD�ֹ�����;
			 INDEX=1, ITEM=CFD_OR_ODNO, TYPE=string, SIZE=11, CAPTION=CFD���ֹ���ȣ;
			 INDEX=2, ITEM=CFD_ODNO, TYPE=string, SIZE=11, CAPTION=CFD�ֹ���ȣ;
			 INDEX=3, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=���հ��¹�ȣ;
			 INDEX=4, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=����;
			 INDEX=5, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=�����ǰ�ڵ�;
			 INDEX=6, ITEM=CFD_PRDT_NM, TYPE=string, SIZE=100, CAPTION=CFD��ǰ��;
			 INDEX=7, ITEM=CFD_TRDE_DCD_NM, TYPE=string, SIZE=10, CAPTION=CFD�Ÿű����ڵ��;
			 INDEX=8, ITEM=CFD_RVSE_CNCL_DCD_NM, TYPE=string, SIZE=10, CAPTION=CFD������ұ����ڵ��;
			 INDEX=9, ITEM=CFD_ORDR_QNT, TYPE=string, SIZE=19, CAPTION=CFD�ֹ�����;
			 INDEX=10, ITEM=CFD_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=CFDü�����;
			 INDEX=11, ITEM=CFD_CNCL_QNT, TYPE=string, SIZE=19, CAPTION=CFD��Ҽ���;
			 INDEX=12, ITEM=CFD_RVSE_QNT, TYPE=string, SIZE=19, CAPTION=CFD��������;
			 INDEX=13, ITEM=CFD_ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=CFD�ֹ��ܿ�����;
			 INDEX=14, ITEM=CFD_ORDR_UNPR, TYPE=string, SIZE=20, CAPTION=CFD�ֹ��ܰ�;
			 INDEX=15, ITEM=CFD_CNCS_UNPR, TYPE=string, SIZE=20, CAPTION=CFDü��ܰ�;
			 INDEX=16, ITEM=CFD_ORDR_DTM, TYPE=string, SIZE=17, CAPTION=CFD�ֹ��Ͻ�;
			 INDEX=17, ITEM=CFD_CNCS_DTM, TYPE=string, SIZE=17, CAPTION=CFDü���Ͻ�;
			 INDEX=18, ITEM=CFD_ORDR_STTS_CD_NM, TYPE=string, SIZE=10, CAPTION=CFD�ֹ������ڵ��;
			 INDEX=19, ITEM=USR_NM, TYPE=string, SIZE=128, CAPTION=����ڸ�;
			 INDEX=20, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ü�����ڵ�;
			 INDEX=21, ITEM=ATHZ_IP_ADDR, TYPE=string, SIZE=39, CAPTION=����IP�ּ�;
			 INDEX=22, ITEM=MAC_ADDR, TYPE=string, SIZE=12, CAPTION=MAC�ּ�;
			 INDEX=23, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
			 INDEX=24, ITEM=CFD_NMPR_TP_DCD_NM, TYPE=string, SIZE=20, CAPTION=CFDȣ�����������ڵ��;
			 INDEX=25, ITEM=CFD_ORDR_TP_DCD_NM, TYPE=string, SIZE=10, CAPTION=CFD�ֹ����������ڵ��;
			 INDEX=26, ITEM=CFD_FEE, TYPE=string, SIZE=23, CAPTION=CFD������;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strMNGM_BDCD;		//���������ڵ�
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strSCTN_STRT_DT;		//������������
CString strSCTN_END_DT;		//������������
CString strCFD_PRDT_CD;		//CFD��ǰ�ڵ�
CString strCFD_ODNO;		//CFD�ֹ���ȣ
CString strCFD_TRDE_DCD;		//CFD�Ÿű����ڵ�
CString strINQ_KND_DCD;		//��ȸ���������ڵ�
CString strINQ_ORD_DCD;		//��ȸ���������ڵ�
CString strPWD;		//��й�ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "MNGM_BDCD", strMNGM_BDCD);		//���������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "SCTN_STRT_DT", strSCTN_STRT_DT);		//������������
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "SCTN_END_DT", strSCTN_END_DT);		//������������
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "CFD_ODNO", strCFD_ODNO);		//CFD�ֹ���ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "CFD_TRDE_DCD", strCFD_TRDE_DCD);		//CFD�Ÿű����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "INQ_KND_DCD", strINQ_KND_DCD);		//��ȸ���������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "INQ_ORD_DCD", strINQ_ORD_DCD);		//��ȸ���������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7703Q00", "OTS7703Q00_in", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCFD_BUY_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out", "CFD_BUY_CNCS_QNT", 0);		//CFD�ż�ü�����
CString strCFD_BUY_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out", "CFD_BUY_CNCS_AMT", 0);		//CFD�ż�ü��ݾ�
CString strCFD_SELL_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out", "CFD_SELL_CNCS_QNT", 0);		//CFD�ŵ�ü�����
CString strCFD_SELL_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out", "CFD_SELL_CNCS_AMT", 0);		//CFD�ŵ�ü��ݾ�
CString strCFD_ORDR_DT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_DT", nRow);		//CFD�ֹ�����
CString strCFD_OR_ODNO = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_OR_ODNO", nRow);		//CFD���ֹ���ȣ
CString strCFD_ODNO = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ODNO", nRow);		//CFD�ֹ���ȣ
CString strCANO = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CUST_NM", nRow);		//����
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
CString strCFD_PRDT_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_PRDT_NM", nRow);		//CFD��ǰ��
CString strCFD_TRDE_DCD_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_TRDE_DCD_NM", nRow);		//CFD�Ÿű����ڵ��
CString strCFD_RVSE_CNCL_DCD_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_RVSE_CNCL_DCD_NM", nRow);		//CFD������ұ����ڵ��
CString strCFD_ORDR_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_QNT", nRow);		//CFD�ֹ�����
CString strCFD_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_CNCS_QNT", nRow);		//CFDü�����
CString strCFD_CNCL_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_CNCL_QNT", nRow);		//CFD��Ҽ���
CString strCFD_RVSE_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_RVSE_QNT", nRow);		//CFD��������
CString strCFD_ORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_RMN_QNT", nRow);		//CFD�ֹ��ܿ�����
CString strCFD_ORDR_UNPR = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_UNPR", nRow);		//CFD�ֹ��ܰ�
CString strCFD_CNCS_UNPR = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_CNCS_UNPR", nRow);		//CFDü��ܰ�
CString strCFD_ORDR_DTM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_DTM", nRow);		//CFD�ֹ��Ͻ�
CString strCFD_CNCS_DTM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_CNCS_DTM", nRow);		//CFDü���Ͻ�
CString strCFD_ORDR_STTS_CD_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_STTS_CD_NM", nRow);		//CFD�ֹ������ڵ��
CString strUSR_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "USR_NM", nRow);		//����ڸ�
CString strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "COMM_MDIA_DCD", nRow);		//��Ÿ�ü�����ڵ�
CString strATHZ_IP_ADDR = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "ATHZ_IP_ADDR", nRow);		//����IP�ּ�
CString strMAC_ADDR = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "MAC_ADDR", nRow);		//MAC�ּ�
CString strCFD_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_PRDT_CD", nRow);		//CFD��ǰ�ڵ�
CString strCFD_NMPR_TP_DCD_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_NMPR_TP_DCD_NM", nRow);		//CFDȣ�����������ڵ��
CString strCFD_ORDR_TP_DCD_NM = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_ORDR_TP_DCD_NM", nRow);		//CFD�ֹ����������ڵ��
CString strCFD_FEE = m_CommAgent.GetTranOutputData("OTS7703Q00", "OTS7703Q00_out_sub01", "CFD_FEE", nRow);		//CFD������
