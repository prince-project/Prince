BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7723Q00, TR_NAME=API��CFD���ܰ�����ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7723Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=FEE_INCL_YN, TYPE=string, SIZE=1, CAPTION=���������Կ���;
			 INDEX=3, ITEM=CFD_STDR_DT, TYPE=string, SIZE=8, CAPTION=CFD��������;
			 INDEX=4, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7723Q00_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_DACA, TYPE=string, SIZE=23, CAPTION=CFD������;
			 INDEX=1, ITEM=CFD_NDY_DNCL_AMT, TYPE=string, SIZE=23, CAPTION=CFD���Ͽ����ݾ�;
			 INDEX=2, ITEM=CFD_NX_NDY_DNCL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�����Ͽ����ݾ�;
			 INDEX=3, ITEM=CFD_ORDR_PSBL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�ֹ����ɱݾ�;
			 INDEX=4, ITEM=CFD_DRWG_PSBL_AMT, TYPE=string, SIZE=23, CAPTION=CFD��ݰ��ɱݾ�;
			 INDEX=5, ITEM=CFD_RCVB_AMT, TYPE=string, SIZE=23, CAPTION=CFD�̼��ݾ�;
			 INDEX=6, ITEM=CFD_CLR_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFDû����ͱݾ�;
			 INDEX=7, ITEM=CFD_FEE, TYPE=string, SIZE=23, CAPTION=CFD������;
			 INDEX=8, ITEM=CFD_ROVR_INTR, TYPE=string, SIZE=23, CAPTION=CFD�ѿ�������;
			 INDEX=9, ITEM=CFD_BRW_FEE, TYPE=string, SIZE=23, CAPTION=CFD���Լ�����;
			 INDEX=10, ITEM=CFD_FRCR_SBST_AMT, TYPE=string, SIZE=23, CAPTION=CFD��ȭ���ݾ�;
			 INDEX=11, ITEM=CFD_ETC_LND_AMT, TYPE=string, SIZE=23, CAPTION=CFD��Ÿ�뿩�ݾ�;
			 INDEX=12, ITEM=ERN_RT, TYPE=string, SIZE=17, CAPTION=������;
			 INDEX=13, ITEM=CFD_CLR_VRT_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFDû�갡����ͱݾ�;
			 INDEX=14, ITEM=CFD_WMY_RTO, TYPE=string, SIZE=20, CAPTION=CFD���űݺ���;
			 INDEX=15, ITEM=CFD_CSGN_WMY, TYPE=string, SIZE=23, CAPTION=CFD��Ź���ű�;
			 INDEX=16, ITEM=CFD_ACBK_AMT, TYPE=string, SIZE=23, CAPTION=CFD��αݾ�;
			 INDEX=17, ITEM=CFD_EVL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�򰡱ݾ�;
			 INDEX=18, ITEM=CFD_EVL_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD�򰡼��ͱݾ�;
			 INDEX=19, ITEM=CFD_ACNT_EVL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�����򰡱ݾ�;
			 INDEX=20, ITEM=CFD_STL_DT, TYPE=string, SIZE=8, CAPTION=CFD��������;
			 INDEX=21, ITEM=CFD_ADIT_WMY, TYPE=string, SIZE=23, CAPTION=CFD�߰����ű�;
			 INDEX=22, ITEM=RGH_SBST_AMT, TYPE=string, SIZE=19, CAPTION=�Ǹ����ݾ�;
		END_OUTPUT0_ITEM

		REC_NAME=OTS7723Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=CFD_ACBK_DT, TYPE=string, SIZE=8, CAPTION=CFD�������;
			 INDEX=1, ITEM=CFD_PRDT_NM, TYPE=string, SIZE=100, CAPTION=CFD��ǰ��;
			 INDEX=2, ITEM=CFD_TRDE_DCD_NM, TYPE=string, SIZE=10, CAPTION=CFD�Ÿű����ڵ��;
			 INDEX=3, ITEM=CFD_CNCS_QNT, TYPE=string, SIZE=19, CAPTION=CFDü�����;
			 INDEX=4, ITEM=CFD_NCNC_QNT, TYPE=string, SIZE=19, CAPTION=CFD��ü�����;
			 INDEX=5, ITEM=CFD_CNCS_UNPR, TYPE=string, SIZE=20, CAPTION=CFDü��ܰ�;
			 INDEX=6, ITEM=CFD_ACBK_AMT, TYPE=string, SIZE=23, CAPTION=CFD��αݾ�;
			 INDEX=7, ITEM=CFD_EVL_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFD�򰡼��ͱݾ�;
			 INDEX=8, ITEM=CFD_ROVR_INTR, TYPE=string, SIZE=23, CAPTION=CFD�ѿ�������;
			 INDEX=9, ITEM=ERN_RT, TYPE=string, SIZE=17, CAPTION=������;
			 INDEX=10, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=�����ǰ�ڵ�;
			 INDEX=11, ITEM=CFD_WMY_RTO, TYPE=string, SIZE=20, CAPTION=CFD���űݺ���;
			 INDEX=12, ITEM=CFD_STL_QNT, TYPE=string, SIZE=19, CAPTION=CFD��������;
			 INDEX=13, ITEM=CFD_CLR_QNT, TYPE=string, SIZE=19, CAPTION=CFDû�����;
			 INDEX=14, ITEM=CFD_PV, TYPE=string, SIZE=20, CAPTION=CFD���簡;
			 INDEX=15, ITEM=CFD_EVL_AMT, TYPE=string, SIZE=23, CAPTION=CFD�򰡱ݾ�;
			 INDEX=16, ITEM=CFD_CLR_PFLS_AMT, TYPE=string, SIZE=23, CAPTION=CFDû����ͱݾ�;
			 INDEX=17, ITEM=CFD_BRW_FEE, TYPE=string, SIZE=23, CAPTION=CFD���Լ�����;
			 INDEX=18, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
			 INDEX=19, ITEM=CFD_CLR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFDû�갡�ɼ���;
			 INDEX=20, ITEM=CFD_BRKR_CD, TYPE=string, SIZE=20, CAPTION=CFD���Ŀ�ڵ�;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strFEE_INCL_YN;		//���������Կ���
CString strCFD_STDR_DT;		//CFD��������
CString strPWD;		//��й�ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7723Q00", "OTS7723Q00_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7723Q00", "OTS7723Q00_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7723Q00", "OTS7723Q00_in", "FEE_INCL_YN", strFEE_INCL_YN);		//���������Կ���
m_CommAgent.SetTranInputData(nRequestId, "OTS7723Q00", "OTS7723Q00_in", "CFD_STDR_DT", strCFD_STDR_DT);		//CFD��������
m_CommAgent.SetTranInputData(nRequestId, "OTS7723Q00", "OTS7723Q00_in", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCFD_DACA = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_DACA", 0);		//CFD������
CString strCFD_NDY_DNCL_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_NDY_DNCL_AMT", 0);		//CFD���Ͽ����ݾ�
CString strCFD_NX_NDY_DNCL_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_NX_NDY_DNCL_AMT", 0);		//CFD�����Ͽ����ݾ�
CString strCFD_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_ORDR_PSBL_AMT", 0);		//CFD�ֹ����ɱݾ�
CString strCFD_DRWG_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_DRWG_PSBL_AMT", 0);		//CFD��ݰ��ɱݾ�
CString strCFD_RCVB_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_RCVB_AMT", 0);		//CFD�̼��ݾ�
CString strCFD_CLR_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_CLR_PFLS_AMT", 0);		//CFDû����ͱݾ�
CString strCFD_FEE = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_FEE", 0);		//CFD������
CString strCFD_ROVR_INTR = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_ROVR_INTR", 0);		//CFD�ѿ�������
CString strCFD_BRW_FEE = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_BRW_FEE", 0);		//CFD���Լ�����
CString strCFD_FRCR_SBST_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_FRCR_SBST_AMT", 0);		//CFD��ȭ���ݾ�
CString strCFD_ETC_LND_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_ETC_LND_AMT", 0);		//CFD��Ÿ�뿩�ݾ�
CString strERN_RT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "ERN_RT", 0);		//������
CString strCFD_CLR_VRT_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_CLR_VRT_PFLS_AMT", 0);		//CFDû�갡����ͱݾ�
CString strCFD_WMY_RTO = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_WMY_RTO", 0);		//CFD���űݺ���
CString strCFD_CSGN_WMY = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_CSGN_WMY", 0);		//CFD��Ź���ű�
CString strCFD_ACBK_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_ACBK_AMT", 0);		//CFD��αݾ�
CString strCFD_EVL_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_EVL_AMT", 0);		//CFD�򰡱ݾ�
CString strCFD_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_EVL_PFLS_AMT", 0);		//CFD�򰡼��ͱݾ�
CString strCFD_ACNT_EVL_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_ACNT_EVL_AMT", 0);		//CFD�����򰡱ݾ�
CString strCFD_STL_DT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_STL_DT", 0);		//CFD��������
CString strCFD_ADIT_WMY = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "CFD_ADIT_WMY", 0);		//CFD�߰����ű�
CString strRGH_SBST_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out", "RGH_SBST_AMT", 0);		//�Ǹ����ݾ�
CString strCFD_ACBK_DT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_ACBK_DT", nRow);		//CFD�������
CString strCFD_PRDT_NM = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_PRDT_NM", nRow);		//CFD��ǰ��
CString strCFD_TRDE_DCD_NM = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_TRDE_DCD_NM", nRow);		//CFD�Ÿű����ڵ��
CString strCFD_CNCS_QNT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_CNCS_QNT", nRow);		//CFDü�����
CString strCFD_NCNC_QNT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_NCNC_QNT", nRow);		//CFD��ü�����
CString strCFD_CNCS_UNPR = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_CNCS_UNPR", nRow);		//CFDü��ܰ�
CString strCFD_ACBK_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_ACBK_AMT", nRow);		//CFD��αݾ�
CString strCFD_EVL_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_EVL_PFLS_AMT", nRow);		//CFD�򰡼��ͱݾ�
CString strCFD_ROVR_INTR = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_ROVR_INTR", nRow);		//CFD�ѿ�������
CString strERN_RT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "ERN_RT", nRow);		//������
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
CString strCFD_WMY_RTO = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_WMY_RTO", nRow);		//CFD���űݺ���
CString strCFD_STL_QNT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_STL_QNT", nRow);		//CFD��������
CString strCFD_CLR_QNT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_CLR_QNT", nRow);		//CFDû�����
CString strCFD_PV = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_PV", nRow);		//CFD���簡
CString strCFD_EVL_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_EVL_AMT", nRow);		//CFD�򰡱ݾ�
CString strCFD_CLR_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_CLR_PFLS_AMT", nRow);		//CFDû����ͱݾ�
CString strCFD_BRW_FEE = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_BRW_FEE", nRow);		//CFD���Լ�����
CString strCFD_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_PRDT_CD", nRow);		//CFD��ǰ�ڵ�
CString strCFD_CLR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_CLR_PSBL_QNT", nRow);		//CFDû�갡�ɼ���
CString strCFD_BRKR_CD = m_CommAgent.GetTranOutputData("OTS7723Q00", "OTS7723Q00_out_sub01", "CFD_BRKR_CD", nRow);		//CFD���Ŀ�ڵ�
