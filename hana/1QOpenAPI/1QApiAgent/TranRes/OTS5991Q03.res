BEGIN_TRAN_LAYOUT

	TR_CODE=OTS5991Q03, TR_NAME=�������ڰ�������ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5991Q03_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=USR_ID, TYPE=string, SIZE=20, CAPTION=�����ID;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS5991Q03_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=���հ��¹�ȣ;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=3, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=����;
			 INDEX=4, ITEM=RMS_ACNT_YN, TYPE=string, SIZE=1, CAPTION=RMS���¿���;
			 INDEX=5, ITEM=ACNT_STTS_DCD, TYPE=string, SIZE=1, CAPTION=���»��±����ڵ�;
			 INDEX=6, ITEM=WRAP_OPER_ACNT_DCD, TYPE=string, SIZE=1, CAPTION=WRAP����±����ڵ�;
			 INDEX=7, ITEM=USE_MDIA_DCD, TYPE=string, SIZE=1, CAPTION=����ü�����ڵ�;
			 INDEX=8, ITEM=ACNT_PRDT_CD, TYPE=string, SIZE=2, CAPTION=���»�ǰ�ڵ�;
			 INDEX=9, ITEM=GSPT_BSNM_YN, TYPE=string, SIZE=1, CAPTION=����������ڿ���;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strUSR_ID;		//�����ID

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS5991Q03", "OTS5991Q03_in", "USR_ID", strUSR_ID);		//�����ID




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCTNO = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "CTNO", nRow);		//���հ��´�ü��ȣ
CString strCANO = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
CString strAPNO = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "APNO", nRow);		//���»�ǰ��ȣ
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "CUST_NM", nRow);		//����
CString strRMS_ACNT_YN = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "RMS_ACNT_YN", nRow);		//RMS���¿���
CString strACNT_STTS_DCD = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "ACNT_STTS_DCD", nRow);		//���»��±����ڵ�
CString strWRAP_OPER_ACNT_DCD = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "WRAP_OPER_ACNT_DCD", nRow);		//WRAP����±����ڵ�
CString strUSE_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "USE_MDIA_DCD", nRow);		//����ü�����ڵ�
CString strACNT_PRDT_CD = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "ACNT_PRDT_CD", nRow);		//���»�ǰ�ڵ�
CString strGSPT_BSNM_YN = m_CommAgent.GetTranOutputData("OTS5991Q03", "OTS5991Q03_out_sub01", "GSPT_BSNM_YN", nRow);		//����������ڿ���
