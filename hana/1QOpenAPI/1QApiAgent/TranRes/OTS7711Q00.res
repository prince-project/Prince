BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7711Q00, TR_NAME=API��CFD���űݰ�����ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7711Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT0_ITEM

		REC_NAME=OTS7711Q00_in_sub01, INOUT=0, ARRAY=1, ARRINFO=;
		BEGIN_INPUT1_ITEM
			 INDEX=0, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
			 INDEX=1, ITEM=CFD_ORDR_QNT, TYPE=string, SIZE=19, CAPTION=CFD�ֹ�����;
		END_INPUT1_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7711Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
			 INDEX=1, ITEM=CFD_PRDT_NM, TYPE=string, SIZE=100, CAPTION=CFD��ǰ��;
			 INDEX=2, ITEM=CFD_WMY_RT, TYPE=string, SIZE=20, CAPTION=CFD���ű���;
			 INDEX=3, ITEM=CFD_ORDR_QNT, TYPE=string, SIZE=19, CAPTION=CFD�ֹ�����;
			 INDEX=4, ITEM=CFD_PV, TYPE=string, SIZE=20, CAPTION=CFD���簡;
			 INDEX=5, ITEM=CFD_WMY, TYPE=string, SIZE=23, CAPTION=CFD���ű�;
			 INDEX=6, ITEM=PRCS_YN, TYPE=string, SIZE=1, CAPTION=ó������;
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
CString strCFD_PRDT_CD;		//CFD��ǰ�ڵ�
CString strCFD_ORDR_QNT;		//CFD�ֹ�����

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7711Q00", "OTS7711Q00_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7711Q00", "OTS7711Q00_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7711Q00", "OTS7711Q00_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS7711Q00", "OTS7711Q00_in_sub01", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7711Q00", "OTS7711Q00_in_sub01", "CFD_ORDR_QNT", strCFD_ORDR_QNT);		//CFD�ֹ�����




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCFD_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "CFD_PRDT_CD", nRow);		//CFD��ǰ�ڵ�
CString strCFD_PRDT_NM = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "CFD_PRDT_NM", nRow);		//CFD��ǰ��
CString strCFD_WMY_RT = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "CFD_WMY_RT", nRow);		//CFD���ű���
CString strCFD_ORDR_QNT = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "CFD_ORDR_QNT", nRow);		//CFD�ֹ�����
CString strCFD_PV = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "CFD_PV", nRow);		//CFD���簡
CString strCFD_WMY = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "CFD_WMY", nRow);		//CFD���ű�
CString strPRCS_YN = m_CommAgent.GetTranOutputData("OTS7711Q00", "OTS7711Q00_out_sub01", "PRCS_YN", nRow);		//ó������
