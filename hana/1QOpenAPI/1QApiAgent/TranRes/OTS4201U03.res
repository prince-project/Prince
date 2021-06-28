BEGIN_TRAN_LAYOUT

	TR_CODE=OTS4201U03, TR_NAME=�ؿ��ֽĿ¶����ֹ��������, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS4201U03_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=4, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ֹ��Ϸù�ȣ;
			 INDEX=5, ITEM=RVSE_CNCL_DCD, TYPE=string, SIZE=1, CAPTION=������ұ����ڵ�;
			 INDEX=6, ITEM=OSTK_ORDR_PRC_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��ֽ��ֹ����ݱ����ڵ�;
			 INDEX=7, ITEM=OSTK_RVSE_CNCL_QNT_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��ֽ�������Ҽ��������ڵ�;
			 INDEX=8, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=9, ITEM=OSTK_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��ֽ��ֹ�����;
			 INDEX=10, ITEM=OSTK_ORDR_CND_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��ֽ��ֹ����Ǳ����ڵ�;
			 INDEX=11, ITEM=WRAP_PLN_SN, TYPE=string, SIZE=11, CAPTION=WRAP��ȹ�Ϸù�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS4201U03_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ֹ��Ϸù�ȣ;
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
CString strORDR_DT;		//�ֹ�����
CString strORDR_SN;		//�ֹ��Ϸù�ȣ
CString strRVSE_CNCL_DCD;		//������ұ����ڵ�
CString strOSTK_ORDR_PRC_DCD;		//�ؿ��ֽ��ֹ����ݱ����ڵ�
CString strOSTK_RVSE_CNCL_QNT_DCD;		//�ؿ��ֽ�������Ҽ��������ڵ�
CString strORDR_QNT;		//�ֹ�����
CString strOSTK_ORDR_PRC;		//�ؿ��ֽ��ֹ�����
CString strOSTK_ORDR_CND_DCD;		//�ؿ��ֽ��ֹ����Ǳ����ڵ�
CString strWRAP_PLN_SN;		//WRAP��ȹ�Ϸù�ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS4201U03", "OTS4201U03_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U03", "OTS4201U03_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U03", "OTS4201U03_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U03", "OTS4201U03_in", "ORDR_DT", strORDR_DT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U03", "OTS4201U03_in", "ORDR_SN", strORDR_SN);		//�ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U03", "OTS4201U03_in", "RVSE_CNCL_DCD", strRVSE_CNCL_DCD);		//������ұ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U03", "OTS4201U03_in", "OSTK_ORDR_PRC_DCD", strOSTK_ORDR_PRC_DCD);		//�ؿ��ֽ��ֹ����ݱ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U03", "OTS4201U03_in", "OSTK_RVSE_CNCL_QNT_DCD", strOSTK_RVSE_CNCL_QNT_DCD);		//�ؿ��ֽ�������Ҽ��������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U03", "OTS4201U03_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U03", "OTS4201U03_in", "OSTK_ORDR_PRC", strOSTK_ORDR_PRC);		//�ؿ��ֽ��ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U03", "OTS4201U03_in", "OSTK_ORDR_CND_DCD", strOSTK_ORDR_CND_DCD);		//�ؿ��ֽ��ֹ����Ǳ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U03", "OTS4201U03_in", "WRAP_PLN_SN", strWRAP_PLN_SN);		//WRAP��ȹ�Ϸù�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS4201U03", "OTS4201U03_out", "ORDR_SN", 0);		//�ֹ��Ϸù�ȣ
