BEGIN_TRAN_LAYOUT

	TR_CODE=OTS7701Q00, TR_NAME=API��CFD�ֹ��ŷ�������������, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7701Q00_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=EXCG_CD, TYPE=string, SIZE=10, CAPTION=�ŷ����ڵ�;
			 INDEX=1, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS7701Q00_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=EXCG_CD, TYPE=string, SIZE=10, CAPTION=�ŷ����ڵ�;
			 INDEX=1, ITEM=CFD_PRDT_CD, TYPE=string, SIZE=32, CAPTION=CFD��ǰ�ڵ�;
			 INDEX=2, ITEM=CFD_WMY_RT, TYPE=string, SIZE=20, CAPTION=CFD���ű���;
			 INDEX=3, ITEM=CFD_BUY_PSBL_YN, TYPE=string, SIZE=1, CAPTION=CFD�ż����ɿ���;
			 INDEX=4, ITEM=CFD_SELL_PSBL_YN, TYPE=string, SIZE=1, CAPTION=CFD�ŵ����ɿ���;
			 INDEX=5, ITEM=CFD_BUY_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFD�ż����ɼ���;
			 INDEX=6, ITEM=CFD_SELL_PSBL_QNT, TYPE=string, SIZE=19, CAPTION=CFD�ŵ����ɼ���;
			 INDEX=7, ITEM=CFD_ITNT_STN_NTN_CD, TYPE=string, SIZE=2, CAPTION=CFD����ǥ�ر����ڵ�;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strEXCG_CD;		//�ŷ����ڵ�
CString strCFD_PRDT_CD;		//CFD��ǰ�ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q00", "OTS7701Q00_in", "EXCG_CD", strEXCG_CD);		//�ŷ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS7701Q00", "OTS7701Q00_in", "CFD_PRDT_CD", strCFD_PRDT_CD);		//CFD��ǰ�ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strEXCG_CD = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "EXCG_CD", nRow);		//�ŷ����ڵ�
CString strCFD_PRDT_CD = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_PRDT_CD", nRow);		//CFD��ǰ�ڵ�
CString strCFD_WMY_RT = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_WMY_RT", nRow);		//CFD���ű���
CString strCFD_BUY_PSBL_YN = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_BUY_PSBL_YN", nRow);		//CFD�ż����ɿ���
CString strCFD_SELL_PSBL_YN = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_SELL_PSBL_YN", nRow);		//CFD�ŵ����ɿ���
CString strCFD_BUY_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_BUY_PSBL_QNT", nRow);		//CFD�ż����ɼ���
CString strCFD_SELL_PSBL_QNT = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_SELL_PSBL_QNT", nRow);		//CFD�ŵ����ɼ���
CString strCFD_ITNT_STN_NTN_CD = m_CommAgent.GetTranOutputData("OTS7701Q00", "OTS7701Q00_out_sub01", "CFD_ITNT_STN_NTN_CD", nRow);		//CFD����ǥ�ر����ڵ�
