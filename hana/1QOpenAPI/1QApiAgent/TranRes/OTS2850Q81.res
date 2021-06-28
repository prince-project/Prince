BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2850Q81, TR_NAME=��Ź����ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2850Q81_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=INQ_DT, TYPE=string, SIZE=8, CAPTION=��ȸ����;
			 INDEX=4, ITEM=INQ_DVSN, TYPE=string, SIZE=1, CAPTION=��ȸ����;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2850Q81_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=EVL_DPST_TOT_AMT, TYPE=string, SIZE=19, CAPTION=�򰡿�Ź�ѱݾ�;
			 INDEX=1, ITEM=EVL_DPST_CSH, TYPE=string, SIZE=19, CAPTION=�򰡿�Ź����;
			 INDEX=2, ITEM=DPST_TOT_AMT, TYPE=string, SIZE=19, CAPTION=��Ź�ѱݾ�;
			 INDEX=3, ITEM=DPST_CSH, TYPE=string, SIZE=19, CAPTION=��Ź����;
			 INDEX=4, ITEM=DPST_SBST, TYPE=string, SIZE=19, CAPTION=��Ź���;
			 INDEX=5, ITEM=WDRW_PSBL_TOT_AMT, TYPE=string, SIZE=19, CAPTION=���Ⱑ���ѱݾ�;
			 INDEX=6, ITEM=WDRW_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=���Ⱑ������;
			 INDEX=7, ITEM=WDRW_PSBL_SBST_AMT, TYPE=string, SIZE=19, CAPTION=���Ⱑ�ɴ��ݾ�;
			 INDEX=8, ITEM=ORDR_PSBL_TOT_AMT, TYPE=string, SIZE=19, CAPTION=�ֹ������ѱݾ�;
			 INDEX=9, ITEM=ORDR_PSBL_CSH, TYPE=string, SIZE=19, CAPTION=�ֹ���������;
			 INDEX=10, ITEM=CSGN_WMY_TOT_AMT, TYPE=string, SIZE=19, CAPTION=��Ź���ű��ѱݾ�;
			 INDEX=11, ITEM=CSGN_WMY_CSH, TYPE=string, SIZE=19, CAPTION=��Ź���ű�����;
			 INDEX=12, ITEM=MNMG_TOT_AMT, TYPE=string, SIZE=19, CAPTION=�������ű��ѱݾ�;
			 INDEX=13, ITEM=MNMG_CSH, TYPE=string, SIZE=19, CAPTION=�������ű�����;
			 INDEX=14, ITEM=ADIT_WMY_TOT_AMT, TYPE=string, SIZE=19, CAPTION=�߰����ű��ѱݾ�;
			 INDEX=15, ITEM=ADIT_WMY_CSH, TYPE=string, SIZE=19, CAPTION=�߰����ű�����;
			 INDEX=16, ITEM=EVL_AMT, TYPE=string, SIZE=19, CAPTION=�򰡱ݾ�;
			 INDEX=17, ITEM=EVL_PFLS, TYPE=string, SIZE=19, CAPTION=�򰡼���;
			 INDEX=18, ITEM=FEE, TYPE=string, SIZE=19, CAPTION=������;
			 INDEX=19, ITEM=RCVA, TYPE=string, SIZE=19, CAPTION=�̼���;
			 INDEX=20, ITEM=THDT_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=���ϼ��ͱݾ�;
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
CString strINQ_DT;		//��ȸ����
CString strINQ_DVSN;		//��ȸ����

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q81", "OTS2850Q81_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q81", "OTS2850Q81_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q81", "OTS2850Q81_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q81", "OTS2850Q81_in", "INQ_DT", strINQ_DT);		//��ȸ����
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q81", "OTS2850Q81_in", "INQ_DVSN", strINQ_DVSN);		//��ȸ����




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strEVL_DPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "EVL_DPST_TOT_AMT", 0);		//�򰡿�Ź�ѱݾ�
CString strEVL_DPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "EVL_DPST_CSH", 0);		//�򰡿�Ź����
CString strDPST_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "DPST_TOT_AMT", 0);		//��Ź�ѱݾ�
CString strDPST_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "DPST_CSH", 0);		//��Ź����
CString strDPST_SBST = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "DPST_SBST", 0);		//��Ź���
CString strWDRW_PSBL_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "WDRW_PSBL_TOT_AMT", 0);		//���Ⱑ���ѱݾ�
CString strWDRW_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "WDRW_PSBL_CSH", 0);		//���Ⱑ������
CString strWDRW_PSBL_SBST_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "WDRW_PSBL_SBST_AMT", 0);		//���Ⱑ�ɴ��ݾ�
CString strORDR_PSBL_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "ORDR_PSBL_TOT_AMT", 0);		//�ֹ������ѱݾ�
CString strORDR_PSBL_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "ORDR_PSBL_CSH", 0);		//�ֹ���������
CString strCSGN_WMY_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "CSGN_WMY_TOT_AMT", 0);		//��Ź���ű��ѱݾ�
CString strCSGN_WMY_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "CSGN_WMY_CSH", 0);		//��Ź���ű�����
CString strMNMG_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "MNMG_TOT_AMT", 0);		//�������ű��ѱݾ�
CString strMNMG_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "MNMG_CSH", 0);		//�������ű�����
CString strADIT_WMY_TOT_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "ADIT_WMY_TOT_AMT", 0);		//�߰����ű��ѱݾ�
CString strADIT_WMY_CSH = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "ADIT_WMY_CSH", 0);		//�߰����ű�����
CString strEVL_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "EVL_AMT", 0);		//�򰡱ݾ�
CString strEVL_PFLS = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "EVL_PFLS", 0);		//�򰡼���
CString strFEE = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "FEE", 0);		//������
CString strRCVA = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "RCVA", 0);		//�̼���
CString strTHDT_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS2850Q81", "OTS2850Q81_out", "THDT_PFLS_AMT", 0);		//���ϼ��ͱݾ�
