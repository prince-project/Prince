BEGIN_TRAN_LAYOUT

	TR_CODE=OTS4201Q21, TR_NAME=�ؿ��ֽĿ¶����ֹ���ȭ�ܰ�API, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS4201Q21_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS4201Q21_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=CRRY_CD, TYPE=string, SIZE=3, CAPTION=��ȭ�ڵ�;
			 INDEX=1, ITEM=FRCR_BLN_AMT, TYPE=string, SIZE=26, CAPTION=��ȭ�ܰ�ݾ�;
			 INDEX=2, ITEM=FRCR_PRSM_DACA, TYPE=string, SIZE=26, CAPTION=��ȭ����������;
			 INDEX=3, ITEM=OSTK_ORDR_PSBL_AMT, TYPE=string, SIZE=26, CAPTION=�ؿ��ֽ��ֹ����ɱݾ�;
			 INDEX=4, ITEM=FRCR_DRWG_PSBL_AMT, TYPE=string, SIZE=26, CAPTION=��ȭ��ݰ��ɱݾ�;
			 INDEX=5, ITEM=OSTK_ORDR_WMY, TYPE=string, SIZE=24, CAPTION=�ؿ��ֽ��ֹ����ű�;
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

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q21", "OTS4201Q21_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q21", "OTS4201Q21_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS4201Q21", "OTS4201Q21_in", "PWD", strPWD);		//��й�ȣ




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strCRRY_CD = m_CommAgent.GetTranOutputData("OTS4201Q21", "OTS4201Q21_out_sub01", "CRRY_CD", nRow);		//��ȭ�ڵ�
CString strFRCR_BLN_AMT = m_CommAgent.GetTranOutputData("OTS4201Q21", "OTS4201Q21_out_sub01", "FRCR_BLN_AMT", nRow);		//��ȭ�ܰ�ݾ�
CString strFRCR_PRSM_DACA = m_CommAgent.GetTranOutputData("OTS4201Q21", "OTS4201Q21_out_sub01", "FRCR_PRSM_DACA", nRow);		//��ȭ����������
CString strOSTK_ORDR_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS4201Q21", "OTS4201Q21_out_sub01", "OSTK_ORDR_PSBL_AMT", nRow);		//�ؿ��ֽ��ֹ����ɱݾ�
CString strFRCR_DRWG_PSBL_AMT = m_CommAgent.GetTranOutputData("OTS4201Q21", "OTS4201Q21_out_sub01", "FRCR_DRWG_PSBL_AMT", nRow);		//��ȭ��ݰ��ɱݾ�
CString strOSTK_ORDR_WMY = m_CommAgent.GetTranOutputData("OTS4201Q21", "OTS4201Q21_out_sub01", "OSTK_ORDR_WMY", nRow);		//�ؿ��ֽ��ֹ����ű�
