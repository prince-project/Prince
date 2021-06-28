BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2850Q82, TR_NAME=�̰����ܰ���, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2850Q82_in, INOUT=0, ARRAY=0, ARRINFO=;
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
		REC_NAME=OTS2850Q82_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=1, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=�����ǰ�ڵ�;
			 INDEX=2, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=��ǰ��;
			 INDEX=3, ITEM=SELL_BUY_DVSN_NM, TYPE=string, SIZE=40, CAPTION=�ŵ��ż����и�;
			 INDEX=4, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
			 INDEX=5, ITEM=USTL_QNT, TYPE=string, SIZE=19, CAPTION=�̰�������;
			 INDEX=6, ITEM=AVR_PRC, TYPE=string, SIZE=20, CAPTION=��հ���;
			 INDEX=7, ITEM=NOW_PRC, TYPE=string, SIZE=22, CAPTION=���簡��;
			 INDEX=8, ITEM=PRPT, TYPE=string, SIZE=17, CAPTION=���;
			 INDEX=9, ITEM=EVL_AMT, TYPE=string, SIZE=19, CAPTION=�򰡱ݾ�;
			 INDEX=10, ITEM=EVL_PFLS, TYPE=string, SIZE=19, CAPTION=�򰡼���;
			 INDEX=11, ITEM=PFLS_RT, TYPE=string, SIZE=20, CAPTION=������;
			 INDEX=12, ITEM=CLR_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=û�갡�ɼ���;
			 INDEX=13, ITEM=PCHS_ACBK_AMT, TYPE=string, SIZE=19, CAPTION=������αݾ�;
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

m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q82", "OTS2850Q82_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q82", "OTS2850Q82_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q82", "OTS2850Q82_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q82", "OTS2850Q82_in", "INQ_DT", strINQ_DT);		//��ȸ����
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q82", "OTS2850Q82_in", "INQ_DVSN", strINQ_DVSN);		//��ȸ����




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PRDT_NM", nRow);		//��ǰ��
CString strSELL_BUY_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//�ŵ��ż����и�
CString strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "SELL_BUY_DCD", nRow);		//�ŵ��ż������ڵ�
CString strUSTL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "USTL_QNT", nRow);		//�̰�������
CString strAVR_PRC = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "AVR_PRC", nRow);		//��հ���
CString strNOW_PRC = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "NOW_PRC", nRow);		//���簡��
CString strPRPT = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PRPT", nRow);		//���
CString strEVL_AMT = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "EVL_AMT", nRow);		//�򰡱ݾ�
CString strEVL_PFLS = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "EVL_PFLS", nRow);		//�򰡼���
CString strPFLS_RT = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PFLS_RT", nRow);		//������
CString strCLR_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "CLR_PSBL_QNT", nRow);		//û�갡�ɼ���
CString strPCHS_ACBK_AMT = m_CommAgent.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PCHS_ACBK_AMT", nRow);		//������αݾ�
