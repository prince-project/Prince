BEGIN_TRAN_LAYOUT

	TR_CODE=OAM5760Q50, TR_NAME=�Ļ��ü���û������ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OAM5760Q50_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=API_USE_YN, TYPE=string, SIZE=1, CAPTION=API��뿩��;
			 INDEX=1, ITEM=USR_ID, TYPE=string, SIZE=20, CAPTION=�����ID;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OAM5760Q50_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=EXCG_CD, TYPE=string, SIZE=10, CAPTION=�ŷ����ڵ�;
			 INDEX=1, ITEM=QTTN_INQ_RQS_YN, TYPE=string, SIZE=1, CAPTION=�ü���ȸ��û����;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strAPI_USE_YN;		//API��뿩��
CString strUSR_ID;		//�����ID

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OAM5760Q50", "OAM5760Q50_in", "API_USE_YN", strAPI_USE_YN);		//API��뿩��
m_CommAgent.SetTranInputData(nRequestId, "OAM5760Q50", "OAM5760Q50_in", "USR_ID", strUSR_ID);		//�����ID




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strEXCG_CD = m_CommAgent.GetTranOutputData("OAM5760Q50", "OAM5760Q50_out_sub01", "EXCG_CD", nRow);		//�ŷ����ڵ�
CString strQTTN_INQ_RQS_YN = m_CommAgent.GetTranOutputData("OAM5760Q50", "OAM5760Q50_out_sub01", "QTTN_INQ_RQS_YN", nRow);		//�ü���ȸ��û����
