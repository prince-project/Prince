BEGIN_TRAN_LAYOUT

	TR_CODE=OTS4296Q23, TR_NAME=�ؿ��ֽ��ֹ�ü�᳻����ȸAPI��, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS4296Q23_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=INQ_STRT_DT, TYPE=string, SIZE=8, CAPTION=��ȸ��������;
			 INDEX=4, ITEM=INQ_END_DT, TYPE=string, SIZE=8, CAPTION=��ȸ��������;
			 INDEX=5, ITEM=OSTK_MKT_GRUP_CD, TYPE=string, SIZE=2, CAPTION=�ؿ��ֽĽ���׷��ڵ�;
			 INDEX=6, ITEM=OVRS_SMBL_CD, TYPE=string, SIZE=12, CAPTION=�ؿܻ�¡�ڵ�;
			 INDEX=7, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
			 INDEX=8, ITEM=CNCS_NCNC_DCD, TYPE=string, SIZE=1, CAPTION=ü���ü�ᱸ���ڵ�;
			 INDEX=9, ITEM=SORT_DCD, TYPE=string, SIZE=1, CAPTION=���ı����ڵ�;
			 INDEX=10, ITEM=FTNG_DCD, TYPE=string, SIZE=1, CAPTION=�ջ걸���ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS4296Q23_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=1, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ֹ��Ϸù�ȣ;
			 INDEX=2, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=���ֹ��Ϸù�ȣ;
			 INDEX=3, ITEM=OSTK_INV_INF_MKT_DCD, TYPE=string, SIZE=2, CAPTION=�ؿ��ֽ������������屸���ڵ�;
			 INDEX=4, ITEM=OSTK_MKT_CD, TYPE=string, SIZE=2, CAPTION=�ؿ��ֽĽ����ڵ�;
			 INDEX=5, ITEM=OSTK_MKT_NM, TYPE=string, SIZE=100, CAPTION=�ؿ��ֽĽ����;
			 INDEX=6, ITEM=OVRS_SMBL_CD, TYPE=string, SIZE=12, CAPTION=�ؿܻ�¡�ڵ�;
			 INDEX=7, ITEM=OSTK_SMBL_NM, TYPE=string, SIZE=130, CAPTION=�ؿ��ֽĻ�¡��;
			 INDEX=8, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
			 INDEX=9, ITEM=SELL_BUY_DVSN_NM, TYPE=string, SIZE=40, CAPTION=�ŵ��ż����и�;
			 INDEX=10, ITEM=OSTK_ORDR_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��ֽ��ֹ������ڵ�;
			 INDEX=11, ITEM=OSTK_ORDR_DVSN_NM, TYPE=string, SIZE=80, CAPTION=�ؿ��ֽ��ֹ����и�;
			 INDEX=12, ITEM=OSTK_ORDR_PRC_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��ֽ��ֹ����ݱ����ڵ�;
			 INDEX=13, ITEM=OSTK_ORDR_PRC_DVSN_NM, TYPE=string, SIZE=20, CAPTION=�ؿ��ֽ��ֹ����ݱ��и�;
			 INDEX=14, ITEM=OSTK_ORDR_CND_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��ֽ��ֹ����Ǳ����ڵ�;
			 INDEX=15, ITEM=OSTK_ORDR_CND_DVSN_NM, TYPE=string, SIZE=40, CAPTION=�ؿ��ֽ��ֹ����Ǳ��и�;
			 INDEX=16, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=17, ITEM=OSTK_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��ֽ��ֹ�����;
			 INDEX=18, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=ü�����;
			 INDEX=19, ITEM=OSTK_CNCS_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��ֽ�ü�ᰡ��;
			 INDEX=20, ITEM=ORDR_RMN_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ��ܿ�����;
			 INDEX=21, ITEM=OSTK_CNCS_AMT, TYPE=string, SIZE=24, CAPTION=�ؿ��ֽ�ü��ݾ�;
			 INDEX=22, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=��ȭ�ڵ�;
			 INDEX=23, ITEM=OSTK_ORDR_STTS_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��ֽ��ֹ����±����ڵ�;
			 INDEX=24, ITEM=OSTK_ORDR_STTS_NM, TYPE=string, SIZE=80, CAPTION=�ؿ��ֽ��ֹ����¸�;
			 INDEX=25, ITEM=ORDR_DTM, TYPE=string, SIZE=14, CAPTION=�ֹ��Ͻ�;
			 INDEX=26, ITEM=CNCS_DTM, TYPE=string, SIZE=14, CAPTION=ü���Ͻ�;
			 INDEX=27, ITEM=OSTK_ACPL_ORDR_DTM, TYPE=string, SIZE=14, CAPTION=�ؿ��ֽ������ֹ��Ͻ�;
			 INDEX=28, ITEM=ACPL_CNCS_DTM, TYPE=string, SIZE=14, CAPTION=����ü���Ͻ�;
			 INDEX=29, ITEM=ODER_NM, TYPE=string, SIZE=100, CAPTION=�ֹ��ڸ�;
			 INDEX=30, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ü�����ڵ�;
			 INDEX=31, ITEM=COMM_MDIA_DVSN_NM, TYPE=string, SIZE=24, CAPTION=��Ÿ�ü���и�;
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
CString strINQ_STRT_DT;		//��ȸ��������
CString strINQ_END_DT;		//��ȸ��������
CString strOSTK_MKT_GRUP_CD;		//�ؿ��ֽĽ���׷��ڵ�
CString strOVRS_SMBL_CD;		//�ؿܻ�¡�ڵ�
CString strSELL_BUY_DCD;		//�ŵ��ż������ڵ�
CString strCNCS_NCNC_DCD;		//ü���ü�ᱸ���ڵ�
CString strSORT_DCD;		//���ı����ڵ�
CString strFTNG_DCD;		//�ջ걸���ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "INQ_STRT_DT", strINQ_STRT_DT);		//��ȸ��������
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "INQ_END_DT", strINQ_END_DT);		//��ȸ��������
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "OSTK_MKT_GRUP_CD", strOSTK_MKT_GRUP_CD);		//�ؿ��ֽĽ���׷��ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "OVRS_SMBL_CD", strOVRS_SMBL_CD);		//�ؿܻ�¡�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//�ŵ��ż������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "CNCS_NCNC_DCD", strCNCS_NCNC_DCD);		//ü���ü�ᱸ���ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "SORT_DCD", strSORT_DCD);		//���ı����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4296Q23", "OTS4296Q23_in", "FTNG_DCD", strFTNG_DCD);		//�ջ걸���ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strORDR_DT = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ORDR_DT", nRow);		//�ֹ�����
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ORDR_SN", nRow);		//�ֹ��Ϸù�ȣ
CString strOR_ORDR_SN = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OR_ORDR_SN", nRow);		//���ֹ��Ϸù�ȣ
CString strOSTK_INV_INF_MKT_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_INV_INF_MKT_DCD", nRow);		//�ؿ��ֽ������������屸���ڵ�
CString strOSTK_MKT_CD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_MKT_CD", nRow);		//�ؿ��ֽĽ����ڵ�
CString strOSTK_MKT_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_MKT_NM", nRow);		//�ؿ��ֽĽ����
CString strOVRS_SMBL_CD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OVRS_SMBL_CD", nRow);		//�ؿܻ�¡�ڵ�
CString strOSTK_SMBL_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_SMBL_NM", nRow);		//�ؿ��ֽĻ�¡��
CString strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "SELL_BUY_DCD", nRow);		//�ŵ��ż������ڵ�
CString strSELL_BUY_DVSN_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//�ŵ��ż����и�
CString strOSTK_ORDR_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_DCD", nRow);		//�ؿ��ֽ��ֹ������ڵ�
CString strOSTK_ORDR_DVSN_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_DVSN_NM", nRow);		//�ؿ��ֽ��ֹ����и�
CString strOSTK_ORDR_PRC_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_PRC_DCD", nRow);		//�ؿ��ֽ��ֹ����ݱ����ڵ�
CString strOSTK_ORDR_PRC_DVSN_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_PRC_DVSN_NM", nRow);		//�ؿ��ֽ��ֹ����ݱ��и�
CString strOSTK_ORDR_CND_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_CND_DCD", nRow);		//�ؿ��ֽ��ֹ����Ǳ����ڵ�
CString strOSTK_ORDR_CND_DVSN_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_CND_DVSN_NM", nRow);		//�ؿ��ֽ��ֹ����Ǳ��и�
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
CString strOSTK_ORDR_PRC = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_PRC", nRow);		//�ؿ��ֽ��ֹ�����
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "CNCS_QNT", nRow);		//ü�����
CString strOSTK_CNCS_PRC = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_CNCS_PRC", nRow);		//�ؿ��ֽ�ü�ᰡ��
CString strORDR_RMN_QNT = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ORDR_RMN_QNT", nRow);		//�ֹ��ܿ�����
CString strOSTK_CNCS_AMT = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_CNCS_AMT", nRow);		//�ؿ��ֽ�ü��ݾ�
CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
CString strOSTK_ORDR_STTS_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_STTS_DCD", nRow);		//�ؿ��ֽ��ֹ����±����ڵ�
CString strOSTK_ORDR_STTS_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ORDR_STTS_NM", nRow);		//�ؿ��ֽ��ֹ����¸�
CString strORDR_DTM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ORDR_DTM", nRow);		//�ֹ��Ͻ�
CString strCNCS_DTM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "CNCS_DTM", nRow);		//ü���Ͻ�
CString strOSTK_ACPL_ORDR_DTM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "OSTK_ACPL_ORDR_DTM", nRow);		//�ؿ��ֽ������ֹ��Ͻ�
CString strACPL_CNCS_DTM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ACPL_CNCS_DTM", nRow);		//����ü���Ͻ�
CString strODER_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "ODER_NM", nRow);		//�ֹ��ڸ�
CString strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "COMM_MDIA_DCD", nRow);		//��Ÿ�ü�����ڵ�
CString strCOMM_MDIA_DVSN_NM = m_CommAgent.GetTranOutputData("OTS4296Q23", "OTS4296Q23_out_sub01", "COMM_MDIA_DVSN_NM", nRow);		//��Ÿ�ü���и�
