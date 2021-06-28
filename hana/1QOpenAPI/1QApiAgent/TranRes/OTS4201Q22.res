BEGIN_TRAN_LAYOUT

	TR_CODE=OTS4201Q22, TR_NAME=�ؿ��ֽĿ¶����ֹ��ֽ��ܰ�API, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS4201Q22_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=FEE_DVSN, TYPE=string, SIZE=1, CAPTION=�����ᱸ��;
			 INDEX=4, ITEM=BLN_DCD, TYPE=string, SIZE=1, CAPTION=�ܰ����ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS4201Q22_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=OSTK_INV_INF_MKT_DCD, TYPE=string, SIZE=2, CAPTION=�ؿ��ֽ������������屸���ڵ�;
			 INDEX=1, ITEM=OSTK_MKT_CD, TYPE=string, SIZE=2, CAPTION=�ؿ��ֽĽ����ڵ�;
			 INDEX=2, ITEM=OSTK_MKT_NM, TYPE=string, SIZE=100, CAPTION=�ؿ��ֽĽ����;
			 INDEX=3, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=��ȭ�ڵ�;
			 INDEX=4, ITEM=OVRS_SMBL_CD, TYPE=string, SIZE=12, CAPTION=�ؿܻ�¡�ڵ�;
			 INDEX=5, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=��ǰ��;
			 INDEX=6, ITEM=CNB_BLN_QNT, TYPE=string, SIZE=26, CAPTION=ü������ܰ����;
			 INDEX=7, ITEM=SELL_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=�ŵ����ɼ���;
			 INDEX=8, ITEM=OSTK_BUY_AMT, TYPE=string, SIZE=24, CAPTION=�ؿ��ֽĸż��ݾ�;
			 INDEX=9, ITEM=OSTK_BUY_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��ֽĸż�����;
			 INDEX=10, ITEM=OSTK_CLPR, TYPE=string, SIZE=24, CAPTION=�ؿ��ֽ�����;
			 INDEX=11, ITEM=OSTK_FRCR_EVL_AMT, TYPE=string, SIZE=24, CAPTION=�ؿ��ֽĿ�ȭ�򰡱ݾ�;
			 INDEX=12, ITEM=TRDE_UN_QNT, TYPE=string, SIZE=19, CAPTION=�ŸŴ�������;
			 INDEX=13, ITEM=LOAN_SN, TYPE=string, SIZE=11, CAPTION=�����Ϸù�ȣ;
			 INDEX=14, ITEM=LOAN_DT, TYPE=string, SIZE=8, CAPTION=��������;
			 INDEX=15, ITEM=LOAN_AMT, TYPE=string, SIZE=19, CAPTION=����ݾ�;
			 INDEX=16, ITEM=BLN_DCD, TYPE=string, SIZE=1, CAPTION=�ܰ����ڵ�;
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
CString strFEE_DVSN;		//�����ᱸ��
CString strBLN_DCD;		//�ܰ����ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q22", "OTS4201Q22_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q22", "OTS4201Q22_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q22", "OTS4201Q22_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q22", "OTS4201Q22_in", "FEE_DVSN", strFEE_DVSN);		//�����ᱸ��
m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q22", "OTS4201Q22_in", "BLN_DCD", strBLN_DCD);		//�ܰ����ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strOSTK_INV_INF_MKT_DCD = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_INV_INF_MKT_DCD", nRow);		//�ؿ��ֽ������������屸���ڵ�
CString strOSTK_MKT_CD = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_MKT_CD", nRow);		//�ؿ��ֽĽ����ڵ�
CString strOSTK_MKT_NM = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_MKT_NM", nRow);		//�ؿ��ֽĽ����
CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
CString strOVRS_SMBL_CD = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OVRS_SMBL_CD", nRow);		//�ؿܻ�¡�ڵ�
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "PRDT_NM", nRow);		//��ǰ��
CString strCNB_BLN_QNT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "CNB_BLN_QNT", nRow);		//ü������ܰ����
CString strSELL_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "SELL_PSBL_QNT", nRow);		//�ŵ����ɼ���
CString strOSTK_BUY_AMT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_BUY_AMT", nRow);		//�ؿ��ֽĸż��ݾ�
CString strOSTK_BUY_PRC = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_BUY_PRC", nRow);		//�ؿ��ֽĸż�����
CString strOSTK_CLPR = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_CLPR", nRow);		//�ؿ��ֽ�����
CString strOSTK_FRCR_EVL_AMT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "OSTK_FRCR_EVL_AMT", nRow);		//�ؿ��ֽĿ�ȭ�򰡱ݾ�
CString strTRDE_UN_QNT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "TRDE_UN_QNT", nRow);		//�ŸŴ�������
CString strLOAN_SN = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "LOAN_SN", nRow);		//�����Ϸù�ȣ
CString strLOAN_DT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "LOAN_DT", nRow);		//��������
CString strLOAN_AMT = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "LOAN_AMT", nRow);		//����ݾ�
CString strBLN_DCD = m_CommAgent.GetTranOutputData("OTS4201Q22", "OTS4201Q22_out_sub01", "BLN_DCD", nRow);		//�ܰ����ڵ�
