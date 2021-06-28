BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7725Q00, TR_NAME=API��CFDû�곻�������ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7725Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=���������ڵ�;
			 INDEX=1, ITEM=CFD_BRKR_CD, TYPE=string, SIZE=20, CAPTION=CFD���Ŀ�ڵ�;
			 INDEX=2, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=3, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=4, ITEM=SCTN_STRT_DT, TYPE=string, SIZE=8, CAPTION=������������;
			 INDEX=5, ITEM=SCTN_END_DT, TYPE=string, SIZE=8, CAPTION=������������;
			 INDEX=6, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
			 INDEX=7, ITEM=CFD_BRKR_TRDE_DCD, TYPE=string, SIZE=1, CAPTION=CFD���Ŀ�Ÿű����ڵ�;
			 INDEX=8, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7725Q00_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_BYCL_PRNA, TYPE=string, SIZE=23, CAPTION=CFD�ż�û�����;
			 INDEX=1, ITEM=CFD_BYCL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�ż�û��ݾ�;
			 INDEX=2, ITEM=CFD_BYCL_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD�ż�û����ͱݾ�;
			 INDEX=3, ITEM=CFD_BUY_FEE, TYPE=string, SIZE=23, CAPTION=CFD�ż�������;
			 INDEX=4, ITEM=CFD_BUY_NIAL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�ż������ͱݾ�;
			 INDEX=5, ITEM=CFD_SLCL_PRNA, TYPE=string, SIZE=23, CAPTION=CFD�ŵ�û�����;
			 INDEX=6, ITEM=CFD_SLCL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�ŵ�û��ݾ�;
			 INDEX=7, ITEM=CFD_SLCL_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD�ŵ�û����ͱݾ�;
			 INDEX=8, ITEM=CFD_SELL_FEE, TYPE=string, SIZE=23, CAPTION=CFD�ŵ�������;
			 INDEX=9, ITEM=CFD_SELL_NIAL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�ŵ������ͱݾ�;
		END_OUTPUT0_ITEM

		REC_NAME=OTS7725Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=CFD_CVRG_DT, TYPE=string, SIZE=8, CAPTION=CFD�ݴ�Ÿ�����;
			 INDEX=1, ITEM=BD_NM, TYPE=string, SIZE=80, CAPTION=������;
			 INDEX=2, ITEM=CANO, TYPE=string, SIZE=32, CAPTION=���հ��¹�ȣ;
			 INDEX=3, ITEM=CUST_NM, TYPE=string, SIZE=192, CAPTION=����;
			 INDEX=4, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=�����ǰ�ڵ�;
			 INDEX=5, ITEM=CFD_PRDT_NM, TYPE=string, SIZE=100, CAPTION=CFD��ǰ��;
			 INDEX=6, ITEM=CFD_BRKR_TRDE_DCD_NM, TYPE=string, SIZE=10, CAPTION=CFD���Ŀ�Ÿű����ڵ��;
			 INDEX=7, ITEM=CFD_CLR_QNT, TYPE=string, SIZE=19, CAPTION=CFDû�����;
			 INDEX=8, ITEM=CFD_ACBK_DT, TYPE=string, SIZE=8, CAPTION=CFD�������;
			 INDEX=9, ITEM=CFD_ACBK_UNPR, TYPE=string, SIZE=20, CAPTION=CFD��δܰ�;
			 INDEX=10, ITEM=CFD_CLR_UNPR, TYPE=string, SIZE=20, CAPTION=CFDû��ܰ�;
			 INDEX=11, ITEM=CFD_CLR_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFDû����ͱݾ�;
			 INDEX=12, ITEM=CFD_FEE, TYPE=string, SIZE=23, CAPTION=CFD������;
			 INDEX=13, ITEM=CFD_PUR_CLR_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD����û����ͱݾ�;
			 INDEX=14, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strMNGM_BDCD;		//���������ڵ�
CString strCFD_BRKR_CD;		//CFD���Ŀ�ڵ�
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strSCTN_STRT_DT;		//������������
CString strSCTN_END_DT;		//������������
CString strCFD_PRDT_CD;		//CFD��ǰ�ڵ�
CString strCFD_BRKR_TRDE_DCD;		//CFD���Ŀ�Ÿű����ڵ�
CString strPWD;		//��й�ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "MNGM_BDCD", strMNGM_BDCD);		//���������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "CFD_BRKR_CD", strCFD_BRKR_CD);		//CFD���Ŀ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "SCTN_STRT_DT", strSCTN_STRT_DT);		//������������
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "SCTN_END_DT", strSCTN_END_DT);		//������������
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "CFD_BRKR_TRDE_DCD", strCFD_BRKR_TRDE_DCD);		//CFD���Ŀ�Ÿű����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7725Q00", "OTS7725Q00_in", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCFD_BYCL_PRNA = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_BYCL_PRNA", 0);		//CFD�ż�û�����
CString strCFD_BYCL_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_BYCL_AMT", 0);		//CFD�ż�û��ݾ�
CString strCFD_BYCL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_BYCL_PFLS_AMT", 0);		//CFD�ż�û����ͱݾ�
CString strCFD_BUY_FEE = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_BUY_FEE", 0);		//CFD�ż�������
CString strCFD_BUY_NIAL_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_BUY_NIAL_AMT", 0);		//CFD�ż������ͱݾ�
CString strCFD_SLCL_PRNA = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_SLCL_PRNA", 0);		//CFD�ŵ�û�����
CString strCFD_SLCL_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_SLCL_AMT", 0);		//CFD�ŵ�û��ݾ�
CString strCFD_SLCL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_SLCL_PFLS_AMT", 0);		//CFD�ŵ�û����ͱݾ�
CString strCFD_SELL_FEE = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_SELL_FEE", 0);		//CFD�ŵ�������
CString strCFD_SELL_NIAL_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out", "CFD_SELL_NIAL_AMT", 0);		//CFD�ŵ������ͱݾ�
CString strCFD_CVRG_DT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_CVRG_DT", nRow);		//CFD�ݴ�Ÿ�����
CString strBD_NM = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "BD_NM", nRow);		//������
CString strCANO = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CANO", nRow);		//���հ��¹�ȣ
CString strCUST_NM = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CUST_NM", nRow);		//����
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
CString strCFD_PRDT_NM = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_PRDT_NM", nRow);		//CFD��ǰ��
CString strCFD_BRKR_TRDE_DCD_NM = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_BRKR_TRDE_DCD_NM", nRow);		//CFD���Ŀ�Ÿű����ڵ��
CString strCFD_CLR_QNT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_CLR_QNT", nRow);		//CFDû�����
CString strCFD_ACBK_DT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_ACBK_DT", nRow);		//CFD�������
CString strCFD_ACBK_UNPR = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_ACBK_UNPR", nRow);		//CFD��δܰ�
CString strCFD_CLR_UNPR = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_CLR_UNPR", nRow);		//CFDû��ܰ�
CString strCFD_CLR_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_CLR_PFLS_AMT", nRow);		//CFDû����ͱݾ�
CString strCFD_FEE = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_FEE", nRow);		//CFD������
CString strCFD_PUR_CLR_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_PUR_CLR_PFLS_AMT", nRow);		//CFD����û����ͱݾ�
CString strCFD_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7725Q00", "OTS7725Q00_out_sub01", "CFD_PRDT_CD", nRow);		//CFD��ǰ�ڵ�
