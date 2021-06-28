BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7722Q00, TR_NAME=API��CFD�̰����ܰ�����ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7722Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=CFD_STDR_DT, TYPE=string, SIZE=8, CAPTION=CFD��������;
			 INDEX=3, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7722Q00_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_BFDT_DPST_AMT, TYPE=string, SIZE=23, CAPTION=CFD���Ͽ�Ź�ݾ�;
			 INDEX=1, ITEM=CFD_RNDR_AMT, TYPE=string, SIZE=23, CAPTION=CFD����ݱݾ�;
			 INDEX=2, ITEM=CFD_STL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�����ݾ�;
			 INDEX=3, ITEM=CFD_DPST_AMT, TYPE=string, SIZE=23, CAPTION=CFD��Ź�ݾ�;
			 INDEX=4, ITEM=CFD_ORDR_PSBL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�ֹ����ɱݾ�;
			 INDEX=5, ITEM=CFD_DRWG_PSBL_AMT, TYPE=string, SIZE=23, CAPTION=CFD��ݰ��ɱݾ�;
			 INDEX=6, ITEM=CFD_CLR_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFDû����ͱݾ�;
			 INDEX=7, ITEM=CFD_FEE, TYPE=string, SIZE=23, CAPTION=CFD������;
			 INDEX=8, ITEM=CFD_FNN_CT_AMT, TYPE=string, SIZE=23, CAPTION=CFD�������ݾ�;
			 INDEX=9, ITEM=CFD_CSGN_WMY, TYPE=string, SIZE=23, CAPTION=CFD��Ź���ű�;
			 INDEX=10, ITEM=CFD_EVL_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD�򰡼��ͱݾ�;
			 INDEX=11, ITEM=CFD_ACNT_EVL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�����򰡱ݾ�;
			 INDEX=12, ITEM=CFD_ADIT_WMY, TYPE=string, SIZE=23, CAPTION=CFD�߰����ű�;
			 INDEX=13, ITEM=CFD_WMY_RTO, TYPE=string, SIZE=20, CAPTION=CFD���űݺ���;
			 INDEX=14, ITEM=CFD_RST_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD���¼��ͱݾ�;
		END_OUTPUT0_ITEM

		REC_NAME=OTS7722Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=�����ǰ�ڵ�;
			 INDEX=1, ITEM=CFD_PRDT_NM, TYPE=string, SIZE=100, CAPTION=CFD��ǰ��;
			 INDEX=2, ITEM=CFD_TRDE_DCD_NM, TYPE=string, SIZE=10, CAPTION=CFD�Ÿű����ڵ��;
			 INDEX=3, ITEM=CFD_ACBK_QNT, TYPE=string, SIZE=19, CAPTION=CFD��μ���;
			 INDEX=4, ITEM=CFD_ACBK_UNPR, TYPE=string, SIZE=20, CAPTION=CFD��δܰ�;
			 INDEX=5, ITEM=CFD_PV, TYPE=string, SIZE=20, CAPTION=CFD���簡;
			 INDEX=6, ITEM=CFD_EVL_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD�򰡼��ͱݾ�;
			 INDEX=7, ITEM=ERN_RT, TYPE=string, SIZE=17, CAPTION=������;
			 INDEX=8, ITEM=CFD_CLR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFDû�갡�ɼ���;
			 INDEX=9, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
			 INDEX=10, ITEM=CFD_BRKR_CD, TYPE=string, SIZE=20, CAPTION=CFD���Ŀ�ڵ�;
			 INDEX=11, ITEM=CFD_ACBK_AMT, TYPE=string, SIZE=23, CAPTION=CFD��αݾ�;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strCFD_STDR_DT;		//CFD��������
CString strPWD;		//��й�ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7722Q00", "OTS7722Q00_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7722Q00", "OTS7722Q00_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7722Q00", "OTS7722Q00_in", "CFD_STDR_DT", strCFD_STDR_DT);		//CFD��������
m_CommAgent.SetTranInputData(nRequestId, "OTS7722Q00", "OTS7722Q00_in", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCFD_BFDT_DPST_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_BFDT_DPST_AMT", 0);		//CFD���Ͽ�Ź�ݾ�
CString strCFD_RNDR_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_RNDR_AMT", 0);		//CFD����ݱݾ�
CString strCFD_STL_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_STL_AMT", 0);		//CFD�����ݾ�
CString strCFD_DPST_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_DPST_AMT", 0);		//CFD��Ź�ݾ�
CString strCFD_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_ORDR_PSBL_AMT", 0);		//CFD�ֹ����ɱݾ�
CString strCFD_DRWG_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_DRWG_PSBL_AMT", 0);		//CFD��ݰ��ɱݾ�
CString strCFD_CLR_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_CLR_PFLS_AMT", 0);		//CFDû����ͱݾ�
CString strCFD_FEE = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_FEE", 0);		//CFD������
CString strCFD_FNN_CT_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_FNN_CT_AMT", 0);		//CFD�������ݾ�
CString strCFD_CSGN_WMY = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_CSGN_WMY", 0);		//CFD��Ź���ű�
CString strCFD_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_EVL_PFLS_AMT", 0);		//CFD�򰡼��ͱݾ�
CString strCFD_ACNT_EVL_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_ACNT_EVL_AMT", 0);		//CFD�����򰡱ݾ�
CString strCFD_ADIT_WMY = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_ADIT_WMY", 0);		//CFD�߰����ű�
CString strCFD_WMY_RTO = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_WMY_RTO", 0);		//CFD���űݺ���
CString strCFD_RST_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out", "CFD_RST_PFLS_AMT", 0);		//CFD���¼��ͱݾ�
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
CString strCFD_PRDT_NM = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_PRDT_NM", nRow);		//CFD��ǰ��
CString strCFD_TRDE_DCD_NM = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_TRDE_DCD_NM", nRow);		//CFD�Ÿű����ڵ��
CString strCFD_ACBK_QNT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_ACBK_QNT", nRow);		//CFD��μ���
CString strCFD_ACBK_UNPR = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_ACBK_UNPR", nRow);		//CFD��δܰ�
CString strCFD_PV = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_PV", nRow);		//CFD���簡
CString strCFD_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_EVL_PFLS_AMT", nRow);		//CFD�򰡼��ͱݾ�
CString strERN_RT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "ERN_RT", nRow);		//������
CString strCFD_CLR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_CLR_PSBL_QNT", nRow);		//CFDû�갡�ɼ���
CString strCFD_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_PRDT_CD", nRow);		//CFD��ǰ�ڵ�
CString strCFD_BRKR_CD = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_BRKR_CD", nRow);		//CFD���Ŀ�ڵ�
CString strCFD_ACBK_AMT = m_CommAgent.GetTranOutputData("OTS7722Q00", "OTS7722Q00_out_sub01", "CFD_ACBK_AMT", nRow);		//CFD��αݾ�
