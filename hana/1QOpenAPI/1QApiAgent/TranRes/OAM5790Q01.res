BEGIN_TRAN_LAYOUT

	TR_CODE=OAM5790Q01, TR_NAME=�ؿ��ֽĽǽð��ü���ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OAM5790Q01_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=USR_ID, TYPE=string, SIZE=20, CAPTION=�����ID;
			 INDEX=1, ITEM=INQ_DVSN, TYPE=string, SIZE=1, CAPTION=��ȸ����;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OAM5790Q01_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=OSTK_RLTM_QTTN_STL_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��ֽĽǽð��ü����������ڵ�;
		END_OUTPUT0_ITEM

		REC_NAME=OAM5790Q01_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=QTTN_INQ_RQS_YN, TYPE=string, SIZE=1, CAPTION=�ü���ȸ��û����;
			 INDEX=1, ITEM=OSTK_QTTN_DVSN_NM, TYPE=string, SIZE=20, CAPTION=�ؿ��ֽĽü����и�;
			 INDEX=2, ITEM=OVRS_EXCG_DSCM_NO, TYPE=string, SIZE=4, CAPTION=�ؿܰŷ��ҽĺ���ȣ;
			 INDEX=3, ITEM=OSTK_MKT_CD, TYPE=string, SIZE=2, CAPTION=�ؿ��ֽĽ����ڵ�;
			 INDEX=4, ITEM=PMNT_CRRY_CD, TYPE=string, SIZE=3, CAPTION=������ȭ�ڵ�;
			 INDEX=5, ITEM=MM_USE_CHGE, TYPE=string, SIZE=11, CAPTION=�������;
			 INDEX=6, ITEM=STDR_EXRT, TYPE=string, SIZE=17, CAPTION=����ȯ��;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strUSR_ID;		//�����ID
CString strINQ_DVSN;		//��ȸ����

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OAM5790Q01", "OAM5790Q01_in", "USR_ID", strUSR_ID);		//�����ID
m_CommAgent.SetTranInputData(nRequestId, "OAM5790Q01", "OAM5790Q01_in", "INQ_DVSN", strINQ_DVSN);		//��ȸ����




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCTNO = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out", "CTNO", 0);		//���հ��´�ü��ȣ
CString strAPNO = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out", "APNO", 0);		//���»�ǰ��ȣ
CString strOSTK_RLTM_QTTN_STL_DCD = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out", "OSTK_RLTM_QTTN_STL_DCD", 0);		//�ؿ��ֽĽǽð��ü����������ڵ�
CString strQTTN_INQ_RQS_YN = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "QTTN_INQ_RQS_YN", nRow);		//�ü���ȸ��û����
CString strOSTK_QTTN_DVSN_NM = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "OSTK_QTTN_DVSN_NM", nRow);		//�ؿ��ֽĽü����и�
CString strOVRS_EXCG_DSCM_NO = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "OVRS_EXCG_DSCM_NO", nRow);		//�ؿܰŷ��ҽĺ���ȣ
CString strOSTK_MKT_CD = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "OSTK_MKT_CD", nRow);		//�ؿ��ֽĽ����ڵ�
CString strPMNT_CRRY_CD = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "PMNT_CRRY_CD", nRow);		//������ȭ�ڵ�
CString strMM_USE_CHGE = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "MM_USE_CHGE", nRow);		//�������
CString strSTDR_EXRT = m_CommAgent.GetTranOutputData("OAM5790Q01", "OAM5790Q01_out_sub01", "STDR_EXRT", nRow);		//����ȯ��
