BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2521Q20, TR_NAME=����Ʈ���̵������¸���Ʈ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2521Q20_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=USR_ID, TYPE=string, SIZE=20, CAPTION=�����ID;
			 INDEX=1, ITEM=STGY_DCD, TYPE=string, SIZE=1, CAPTION=���������ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2521Q20_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=INQ_CNT, TYPE=string, SIZE=19, CAPTION=��ȸ�Ǽ�;
		END_OUTPUT0_ITEM

		REC_NAME=OTS2521Q20_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=���հ��¹�ȣ;
			 INDEX=1, ITEM=ACNT_NM, TYPE=string, SIZE=192, CAPTION=���¸�;
			 INDEX=2, ITEM=STGY_DCD, TYPE=string, SIZE=1, CAPTION=���������ڵ�;
			 INDEX=3, ITEM=DCD_NM, TYPE=string, SIZE=40, CAPTION=�����ڵ��;
			 INDEX=4, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=5, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strUSR_ID;		//�����ID
CString strSTGY_DCD;		//���������ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2521Q20", "OTS2521Q20_in", "USR_ID", strUSR_ID);		//�����ID
m_CommAgent.SetTranInputData(nRequestId, "OTS2521Q20", "OTS2521Q20_in", "STGY_DCD", strSTGY_DCD);		//���������ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strINQ_CNT = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out", "INQ_CNT", 0);		//��ȸ�Ǽ�
CString strCANO = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
CString strACNT_NM = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out_sub01", "ACNT_NM", nRow);		//���¸�
CString strSTGY_DCD = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out_sub01", "STGY_DCD", nRow);		//���������ڵ�
CString strDCD_NM = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out_sub01", "DCD_NM", nRow);		//�����ڵ��
CString strCTNO = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out_sub01", "CTNO", nRow);		//���հ��´�ü��ȣ
CString strAPNO = m_CommAgent.GetTranOutputData("OTS2521Q20", "OTS2521Q20_out_sub01", "APNO", nRow);		//���»�ǰ��ȣ
