BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1225Q00, TR_NAME=���º����ϸŸż���, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1225Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=TRDE_DT, TYPE=string, SIZE=8, CAPTION=�Ÿ�����;
			 INDEX=4, ITEM=FEE_RT, TYPE=string, SIZE=17, CAPTION=��������;
			 INDEX=5, ITEM=TRDE_CT_INCL_YN, TYPE=string, SIZE=1, CAPTION=�Ÿź�����Կ���;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1225Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=�����ǰ�ڵ�;
			 INDEX=1, ITEM=PRDT_ABBR_NM, TYPE=string, SIZE=300, CAPTION=��ǰ����;
			 INDEX=2, ITEM=ITM_WMY_GRD_DCD, TYPE=string, SIZE=1, CAPTION=�������űݵ�ޱ����ڵ�;
			 INDEX=3, ITEM=INQ_BLN_DVSN_NM, TYPE=string, SIZE=30, CAPTION=��ȸ�ܰ��и�;
			 INDEX=4, ITEM=LOAN_DT, TYPE=string, SIZE=8, CAPTION=��������;
			 INDEX=5, ITEM=EXP_DT, TYPE=string, SIZE=8, CAPTION=��������;
			 INDEX=6, ITEM=SELL_QNT, TYPE=string, SIZE=19, CAPTION=�ŵ�����;
			 INDEX=7, ITEM=BUY_QNT, TYPE=string, SIZE=19, CAPTION=�ż�����;
			 INDEX=8, ITEM=SELL_AVR_UNPR, TYPE=string, SIZE=17, CAPTION=�ŵ���մܰ�;
			 INDEX=9, ITEM=BUY_AVR_UNPR, TYPE=string, SIZE=19, CAPTION=�ż���մܰ�;
			 INDEX=10, ITEM=BUY_AMT, TYPE=string, SIZE=19, CAPTION=�ż��ݾ�;
			 INDEX=11, ITEM=SELL_AMT, TYPE=string, SIZE=19, CAPTION=�ŵ��ݾ�;
			 INDEX=12, ITEM=PV, TYPE=string, SIZE=19, CAPTION=���簡;
			 INDEX=13, ITEM=PFLS_AMT, TYPE=string, SIZE=19, CAPTION=���ͱݾ�;
			 INDEX=14, ITEM=PFLS_RT, TYPE=string, SIZE=20, CAPTION=������;
			 INDEX=15, ITEM=THDT_PFLS_AMT, TYPE=string, SIZE=19, CAPTION=���ϼ��ͱݾ�;
			 INDEX=16, ITEM=THDT_PFLS_RT, TYPE=string, SIZE=19, CAPTION=���ϼ�����;
			 INDEX=17, ITEM=RMN_QNT, TYPE=string, SIZE=19, CAPTION=�ܿ�����;
			 INDEX=18, ITEM=EVL_AMT, TYPE=string, SIZE=19, CAPTION=�򰡱ݾ�;
			 INDEX=19, ITEM=PCHS_AMT, TYPE=string, SIZE=19, CAPTION=���Աݾ�;
			 INDEX=20, ITEM=FEE, TYPE=string, SIZE=19, CAPTION=������;
			 INDEX=21, ITEM=WHIT, TYPE=string, SIZE=19, CAPTION=������;
			 INDEX=22, ITEM=STL_BLN_QNT, TYPE=string, SIZE=19, CAPTION=�����ܰ����;
			 INDEX=23, ITEM=CNCS_BLN_QNT, TYPE=string, SIZE=19, CAPTION=ü���ܰ����;
			 INDEX=24, ITEM=THDT_RMN_PFLS, TYPE=string, SIZE=19, CAPTION=�����ܿ�����;
			 INDEX=25, ITEM=SELL_EXCAL_UNPR, TYPE=string, SIZE=19, CAPTION=�ŵ�����ܰ�;
			 INDEX=26, ITEM=BUY_EXCAL_UNPR, TYPE=string, SIZE=19, CAPTION=�ż�����ܰ�;
			 INDEX=27, ITEM=CRDT_AMT, TYPE=string, SIZE=19, CAPTION=�ſ�ݾ�;
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
CString strTRDE_DT;		//�Ÿ�����
CString strFEE_RT;		//��������
CString strTRDE_CT_INCL_YN;		//�Ÿź�����Կ���

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q00", "OTS1225Q00_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q00", "OTS1225Q00_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q00", "OTS1225Q00_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q00", "OTS1225Q00_in", "TRDE_DT", strTRDE_DT);		//�Ÿ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q00", "OTS1225Q00_in", "FEE_RT", strFEE_RT);		//��������
m_CommAgent.SetTranInputData(nRequestId, "OTS1225Q00", "OTS1225Q00_in", "TRDE_CT_INCL_YN", strTRDE_CT_INCL_YN);		//�Ÿź�����Կ���




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
CString strPRDT_ABBR_NM = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "PRDT_ABBR_NM", nRow);		//��ǰ����
CString strITM_WMY_GRD_DCD = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "ITM_WMY_GRD_DCD", nRow);		//�������űݵ�ޱ����ڵ�
CString strINQ_BLN_DVSN_NM = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "INQ_BLN_DVSN_NM", nRow);		//��ȸ�ܰ��и�
CString strLOAN_DT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "LOAN_DT", nRow);		//��������
CString strEXP_DT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "EXP_DT", nRow);		//��������
CString strSELL_QNT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "SELL_QNT", nRow);		//�ŵ�����
CString strBUY_QNT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "BUY_QNT", nRow);		//�ż�����
CString strSELL_AVR_UNPR = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "SELL_AVR_UNPR", nRow);		//�ŵ���մܰ�
CString strBUY_AVR_UNPR = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "BUY_AVR_UNPR", nRow);		//�ż���մܰ�
CString strBUY_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "BUY_AMT", nRow);		//�ż��ݾ�
CString strSELL_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "SELL_AMT", nRow);		//�ŵ��ݾ�
CString strPV = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "PV", nRow);		//���簡
CString strPFLS_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "PFLS_AMT", nRow);		//���ͱݾ�
CString strPFLS_RT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "PFLS_RT", nRow);		//������
CString strTHDT_PFLS_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "THDT_PFLS_AMT", nRow);		//���ϼ��ͱݾ�
CString strTHDT_PFLS_RT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "THDT_PFLS_RT", nRow);		//���ϼ�����
CString strRMN_QNT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "RMN_QNT", nRow);		//�ܿ�����
CString strEVL_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "EVL_AMT", nRow);		//�򰡱ݾ�
CString strPCHS_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "PCHS_AMT", nRow);		//���Աݾ�
CString strFEE = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "FEE", nRow);		//������
CString strWHIT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "WHIT", nRow);		//������
CString strSTL_BLN_QNT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "STL_BLN_QNT", nRow);		//�����ܰ����
CString strCNCS_BLN_QNT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "CNCS_BLN_QNT", nRow);		//ü���ܰ����
CString strTHDT_RMN_PFLS = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "THDT_RMN_PFLS", nRow);		//�����ܿ�����
CString strSELL_EXCAL_UNPR = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "SELL_EXCAL_UNPR", nRow);		//�ŵ�����ܰ�
CString strBUY_EXCAL_UNPR = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "BUY_EXCAL_UNPR", nRow);		//�ż�����ܰ�
CString strCRDT_AMT = m_CommAgent.GetTranOutputData("OTS1225Q00", "OTS1225Q00_out_sub01", "CRDT_AMT", nRow);		//�ſ�ݾ�
