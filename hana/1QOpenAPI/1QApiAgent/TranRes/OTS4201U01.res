BEGIN_TRAN_LAYOUT

	TR_CODE=OTS4201U01, TR_NAME=�ؿ��ֽĿ¶����ֹ��ż�, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS4201U01_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=OVRS_SMBL_CD, TYPE=string, SIZE=12, CAPTION=�ؿܻ�¡�ڵ�;
			 INDEX=4, ITEM=OSTK_MKT_CD, TYPE=string, SIZE=2, CAPTION=�ؿ��ֽĽ����ڵ�;
			 INDEX=5, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
			 INDEX=6, ITEM=OSTK_ORDR_PRC_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��ֽ��ֹ����ݱ����ڵ�;
			 INDEX=7, ITEM=OSTK_ORDR_CND_DCD, TYPE=string, SIZE=1, CAPTION=�ؿ��ֽ��ֹ����Ǳ����ڵ�;
			 INDEX=8, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=9, ITEM=OSTK_ORDR_PRC, TYPE=string, SIZE=24, CAPTION=�ؿ��ֽ��ֹ�����;
			 INDEX=10, ITEM=WRAP_PLN_SN, TYPE=string, SIZE=11, CAPTION=WRAP��ȹ�Ϸù�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS4201U01_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strOVRS_SMBL_CD;		//�ؿܻ�¡�ڵ�
CString strOSTK_MKT_CD;		//�ؿ��ֽĽ����ڵ�
CString strSELL_BUY_DCD;		//�ŵ��ż������ڵ�
CString strOSTK_ORDR_PRC_DCD;		//�ؿ��ֽ��ֹ����ݱ����ڵ�
CString strOSTK_ORDR_CND_DCD;		//�ؿ��ֽ��ֹ����Ǳ����ڵ�
CString strORDR_QNT;		//�ֹ�����
CString strOSTK_ORDR_PRC;		//�ؿ��ֽ��ֹ�����
CString strWRAP_PLN_SN;		//WRAP��ȹ�Ϸù�ȣ

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS4201U01", "OTS4201U01_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U01", "OTS4201U01_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U01", "OTS4201U01_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U01", "OTS4201U01_in", "OVRS_SMBL_CD", strOVRS_SMBL_CD);		//�ؿܻ�¡�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U01", "OTS4201U01_in", "OSTK_MKT_CD", strOSTK_MKT_CD);		//�ؿ��ֽĽ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U01", "OTS4201U01_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//�ŵ��ż������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U01", "OTS4201U01_in", "OSTK_ORDR_PRC_DCD", strOSTK_ORDR_PRC_DCD);		//�ؿ��ֽ��ֹ����ݱ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U01", "OTS4201U01_in", "OSTK_ORDR_CND_DCD", strOSTK_ORDR_CND_DCD);		//�ؿ��ֽ��ֹ����Ǳ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U01", "OTS4201U01_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U01", "OTS4201U01_in", "OSTK_ORDR_PRC", strOSTK_ORDR_PRC);		//�ؿ��ֽ��ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS4201U01", "OTS4201U01_in", "WRAP_PLN_SN", strWRAP_PLN_SN);		//WRAP��ȹ�Ϸù�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS4201U01", "OTS4201U01_out", "ORDR_SN", 0);		//�ֹ��Ϸù�ȣ
