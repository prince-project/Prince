BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5992Q02, TR_NAME=�ñ׳θ���Ŀ��ȸ��API��, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5992Q02_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=USR_ID, TYPE=string, SIZE=20, CAPTION=�����ID;
			 INDEX=1, ITEM=AFFL_SRVC_DCD, TYPE=string, SIZE=3, CAPTION=���޼��񽺱����ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5992Q02_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=���հ��¹�ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=����;
			 INDEX=3, ITEM=AFFL_SRVC_DCD, TYPE=string, SIZE=3, CAPTION=���޼��񽺱����ڵ�;
			 INDEX=4, ITEM=SRVC_NM, TYPE=string, SIZE=80, CAPTION=���񽺸�;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strUSR_ID;		//�����ID
CString strAFFL_SRVC_DCD;		//���޼��񽺱����ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5992Q02", "OTS5992Q02_in", "USR_ID", strUSR_ID);		//�����ID
m_CommAgent.SetTranInputData(nRequestId, "OTS5992Q02", "OTS5992Q02_in", "AFFL_SRVC_DCD", strAFFL_SRVC_DCD);		//���޼��񽺱����ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCANO = m_CommAgent.GetTranOutputData("OTS5992Q02", "OTS5992Q02_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
CString strAPNO = m_CommAgent.GetTranOutputData("OTS5992Q02", "OTS5992Q02_out_sub01", "APNO", nRow);		//���»�ǰ��ȣ
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5992Q02", "OTS5992Q02_out_sub01", "CUST_NM", nRow);		//����
CString strAFFL_SRVC_DCD = m_CommAgent.GetTranOutputData("OTS5992Q02", "OTS5992Q02_out_sub01", "AFFL_SRVC_DCD", nRow);		//���޼��񽺱����ڵ�
CString strSRVC_NM = m_CommAgent.GetTranOutputData("OTS5992Q02", "OTS5992Q02_out_sub01", "SRVC_NM", nRow);		//���񽺸�
