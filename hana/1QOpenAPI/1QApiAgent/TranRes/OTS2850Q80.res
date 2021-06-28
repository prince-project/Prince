BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2850Q80, TR_NAME=�ֹ�ü�᳻��, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2850Q80_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=ORDR_STRT_SN, TYPE=string, SIZE=11, CAPTION=�ֹ������Ϸù�ȣ;
			 INDEX=4, ITEM=INQ_DT, TYPE=string, SIZE=8, CAPTION=��ȸ����;
			 INDEX=5, ITEM=CNCS_NCNC_DCD, TYPE=string, SIZE=1, CAPTION=ü���ü�ᱸ���ڵ�;
			 INDEX=6, ITEM=INQ_CHNL_DVSN, TYPE=string, SIZE=1, CAPTION=��ȸä�α���;
			 INDEX=7, ITEM=SORT_DCD, TYPE=string, SIZE=1, CAPTION=���ı����ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2850Q80_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=FTR_SELL_QNT, TYPE=string, SIZE=19, CAPTION=�����ŵ�����;
			 INDEX=1, ITEM=FTR_BUY_QNT, TYPE=string, SIZE=19, CAPTION=�����ż�����;
			 INDEX=2, ITEM=IDX_CLPT_SELL_QNT, TYPE=string, SIZE=19, CAPTION=�����ݿɼǸŵ�����;
			 INDEX=3, ITEM=IDX_PTPT_SELL_QNT, TYPE=string, SIZE=19, CAPTION=����ǲ�ɼǸŵ�����;
			 INDEX=4, ITEM=IDX_CLPT_BUY_QNT, TYPE=string, SIZE=19, CAPTION=�����ݿɼǸż�����;
			 INDEX=5, ITEM=IDX_PTPT_BUY_QNT, TYPE=string, SIZE=19, CAPTION=����ǲ�ɼǸż�����;
			 INDEX=6, ITEM=KOSPI_FTR_SELL_QNT, TYPE=string, SIZE=19, CAPTION=�ڽ��Ǽ����ŵ�����;
			 INDEX=7, ITEM=KOSPI_FTR_BUY_QNT, TYPE=string, SIZE=19, CAPTION=�ڽ��Ǽ����ż�����;
			 INDEX=8, ITEM=STK_FTR_SELL_QNT, TYPE=string, SIZE=19, CAPTION=�ֽļ����ŵ�����;
			 INDEX=9, ITEM=STK_FTR_BUY_QNT, TYPE=string, SIZE=19, CAPTION=�ֽļ����ż�����;
			 INDEX=10, ITEM=STK_OPT_SELL_QNT, TYPE=string, SIZE=19, CAPTION=�ֽĿɼǸŵ�����;
			 INDEX=11, ITEM=STK_OPT_BUY_QNT, TYPE=string, SIZE=19, CAPTION=�ֽĿɼǸż�����;
			 INDEX=12, ITEM=CNCS_FTR_SELL_QNT, TYPE=string, SIZE=19, CAPTION=ü�ἱ���ŵ�����;
			 INDEX=13, ITEM=CNCS_FTR_BUY_QNT, TYPE=string, SIZE=19, CAPTION=ü�ἱ���ż�����;
			 INDEX=14, ITEM=CNCS_IDX_CLPT_SELL_QNT, TYPE=string, SIZE=19, CAPTION=ü�������ݿɼǸŵ�����;
			 INDEX=15, ITEM=CNCS_IDX_PTPT_SELL_QNT, TYPE=string, SIZE=19, CAPTION=ü������ǲ�ɼǸŵ�����;
			 INDEX=16, ITEM=CNCS_IDX_CLPT_BUY_QNT, TYPE=string, SIZE=19, CAPTION=ü�������ݿɼǸż�����;
			 INDEX=17, ITEM=CNCS_IDX_PTPT_BUY_QNT, TYPE=string, SIZE=19, CAPTION=ü������ǲ�ɼǸż�����;
			 INDEX=18, ITEM=CNCS_KOSPI_FTR_SELL_QNT, TYPE=string, SIZE=19, CAPTION=ü���ڽ��Ǽ����ŵ�����;
			 INDEX=19, ITEM=CNCS_KOSPI_FTR_BUY_QNT, TYPE=string, SIZE=19, CAPTION=ü���ڽ��Ǽ����ż�����;
			 INDEX=20, ITEM=CNCS_STK_FTR_SELL_QNT, TYPE=string, SIZE=19, CAPTION=ü���ֽļ����ŵ�����;
			 INDEX=21, ITEM=CNCS_STK_FTR_BUY_QNT, TYPE=string, SIZE=19, CAPTION=ü���ֽļ����ż�����;
			 INDEX=22, ITEM=CNCS_STK_OPT_SELL_QNT, TYPE=string, SIZE=19, CAPTION=ü���ֽĿɼǸŵ�����;
			 INDEX=23, ITEM=CNCS_STK_OPT_BUY_QNT, TYPE=string, SIZE=19, CAPTION=ü���ֽĿɼǸż�����;
		END_OUTPUT0_ITEM

		REC_NAME=OTS2850Q80_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=ODNO, TYPE=string, SIZE=10, CAPTION=�ֹ���ȣ;
			 INDEX=1, ITEM=OR_ODNO, TYPE=string, SIZE=10, CAPTION=���ֹ���ȣ;
			 INDEX=2, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=3, ITEM=SHTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=�����ǰ�ڵ�;
			 INDEX=4, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=��ǰ��;
			 INDEX=5, ITEM=SELL_BUY_DVSN_NM, TYPE=string, SIZE=40, CAPTION=�ŵ��ż����и�;
			 INDEX=6, ITEM=DRVS_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=�Ļ���ǰȣ�������ڵ�;
			 INDEX=7, ITEM=NMPR_DCD, TYPE=string, SIZE=2, CAPTION=ȣ�������ڵ�;
			 INDEX=8, ITEM=ORDR_PRC_AMT, TYPE=string, SIZE=30, CAPTION=�ֹ����ݱݾ�;
			 INDEX=9, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=10, ITEM=CNCS_DVSN_NM, TYPE=string, SIZE=50, CAPTION=ü�ᱸ�и�;
			 INDEX=11, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=ü�����;
			 INDEX=12, ITEM=CNCS_PRC_AMT, TYPE=string, SIZE=30, CAPTION=ü�ᰡ�ݱݾ�;
			 INDEX=13, ITEM=KOR_CNCS_TM, TYPE=string, SIZE=7, CAPTION=�ѱ�ü��ð�;
			 INDEX=14, ITEM=RVSE_CNCL_CNFM_QNT, TYPE=string, SIZE=19, CAPTION=�������Ȯ�μ���;
			 INDEX=15, ITEM=NCNC_QNT, TYPE=string, SIZE=19, CAPTION=��ü�����;
			 INDEX=16, ITEM=DRVS_NMPR_ACPT_DCD, TYPE=string, SIZE=2, CAPTION=�Ļ���ǰȣ�����������ڵ�;
			 INDEX=17, ITEM=DRVS_NMPR_ACPT_DVSN_NM, TYPE=string, SIZE=50, CAPTION=�Ļ���ǰȣ���������и�;
			 INDEX=18, ITEM=EXCG_ACPT_HR, TYPE=string, SIZE=6, CAPTION=�ŷ��������ð�;
			 INDEX=19, ITEM=KRX_MSG_NO, TYPE=string, SIZE=12, CAPTION=�ѱ��ŷ��Ҹ޽�����ȣ;
			 INDEX=20, ITEM=COMM_MDIA_DCD_NM, TYPE=string, SIZE=24, CAPTION=��Ÿ�ü�����ڵ��;
			 INDEX=21, ITEM=XTNL_ISTT_RJCT_RSN_CD, TYPE=string, SIZE=5, CAPTION=�ܺα���źλ����ڵ�;
			 INDEX=22, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strPWD;		//��й�ȣ
CString strORDR_STRT_SN;		//�ֹ������Ϸù�ȣ
CString strINQ_DT;		//��ȸ����
CString strCNCS_NCNC_DCD;		//ü���ü�ᱸ���ڵ�
CString strINQ_CHNL_DVSN;		//��ȸä�α���
CString strSORT_DCD;		//���ı����ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "ORDR_STRT_SN", strORDR_STRT_SN);		//�ֹ������Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "INQ_DT", strINQ_DT);		//��ȸ����
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "CNCS_NCNC_DCD", strCNCS_NCNC_DCD);		//ü���ü�ᱸ���ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "INQ_CHNL_DVSN", strINQ_CHNL_DVSN);		//��ȸä�α���
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q80", "OTS2850Q80_in", "SORT_DCD", strSORT_DCD);		//���ı����ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strFTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "FTR_SELL_QNT", 0);		//�����ŵ�����
CString strFTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "FTR_BUY_QNT", 0);		//�����ż�����
CString strIDX_CLPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_CLPT_SELL_QNT", 0);		//�����ݿɼǸŵ�����
CString strIDX_PTPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_PTPT_SELL_QNT", 0);		//����ǲ�ɼǸŵ�����
CString strIDX_CLPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_CLPT_BUY_QNT", 0);		//�����ݿɼǸż�����
CString strIDX_PTPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_PTPT_BUY_QNT", 0);		//����ǲ�ɼǸż�����
CString strKOSPI_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "KOSPI_FTR_SELL_QNT", 0);		//�ڽ��Ǽ����ŵ�����
CString strKOSPI_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "KOSPI_FTR_BUY_QNT", 0);		//�ڽ��Ǽ����ż�����
CString strSTK_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_FTR_SELL_QNT", 0);		//�ֽļ����ŵ�����
CString strSTK_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_FTR_BUY_QNT", 0);		//�ֽļ����ż�����
CString strSTK_OPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_OPT_SELL_QNT", 0);		//�ֽĿɼǸŵ�����
CString strSTK_OPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_OPT_BUY_QNT", 0);		//�ֽĿɼǸż�����
CString strCNCS_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_FTR_SELL_QNT", 0);		//ü�ἱ���ŵ�����
CString strCNCS_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_FTR_BUY_QNT", 0);		//ü�ἱ���ż�����
CString strCNCS_IDX_CLPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_CLPT_SELL_QNT", 0);		//ü�������ݿɼǸŵ�����
CString strCNCS_IDX_PTPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_PTPT_SELL_QNT", 0);		//ü������ǲ�ɼǸŵ�����
CString strCNCS_IDX_CLPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_CLPT_BUY_QNT", 0);		//ü�������ݿɼǸż�����
CString strCNCS_IDX_PTPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_PTPT_BUY_QNT", 0);		//ü������ǲ�ɼǸż�����
CString strCNCS_KOSPI_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_KOSPI_FTR_SELL_QNT", 0);		//ü���ڽ��Ǽ����ŵ�����
CString strCNCS_KOSPI_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_KOSPI_FTR_BUY_QNT", 0);		//ü���ڽ��Ǽ����ż�����
CString strCNCS_STK_FTR_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_FTR_SELL_QNT", 0);		//ü���ֽļ����ŵ�����
CString strCNCS_STK_FTR_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_FTR_BUY_QNT", 0);		//ü���ֽļ����ż�����
CString strCNCS_STK_OPT_SELL_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_OPT_SELL_QNT", 0);		//ü���ֽĿɼǸŵ�����
CString strCNCS_STK_OPT_BUY_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_OPT_BUY_QNT", 0);		//ü���ֽĿɼǸż�����
CString strODNO = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "ODNO", nRow);		//�ֹ���ȣ
CString strOR_ODNO = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "OR_ODNO", nRow);		//���ֹ���ȣ
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
CString strSHTN_PRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "SHTN_PRDT_CD", nRow);		//�����ǰ�ڵ�
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "PRDT_NM", nRow);		//��ǰ��
CString strSELL_BUY_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//�ŵ��ż����и�
CString strDRVS_NMPR_DCD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "DRVS_NMPR_DCD", nRow);		//�Ļ���ǰȣ�������ڵ�
CString strNMPR_DCD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "NMPR_DCD", nRow);		//ȣ�������ڵ�
CString strORDR_PRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "ORDR_PRC_AMT", nRow);		//�ֹ����ݱݾ�
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
CString strCNCS_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "CNCS_DVSN_NM", nRow);		//ü�ᱸ�и�
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "CNCS_QNT", nRow);		//ü�����
CString strCNCS_PRC_AMT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "CNCS_PRC_AMT", nRow);		//ü�ᰡ�ݱݾ�
CString strKOR_CNCS_TM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "KOR_CNCS_TM", nRow);		//�ѱ�ü��ð�
CString strRVSE_CNCL_CNFM_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "RVSE_CNCL_CNFM_QNT", nRow);		//�������Ȯ�μ���
CString strNCNC_QNT = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "NCNC_QNT", nRow);		//��ü�����
CString strDRVS_NMPR_ACPT_DCD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "DRVS_NMPR_ACPT_DCD", nRow);		//�Ļ���ǰȣ�����������ڵ�
CString strDRVS_NMPR_ACPT_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "DRVS_NMPR_ACPT_DVSN_NM", nRow);		//�Ļ���ǰȣ���������и�
CString strEXCG_ACPT_HR = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "EXCG_ACPT_HR", nRow);		//�ŷ��������ð�
CString strKRX_MSG_NO = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "KRX_MSG_NO", nRow);		//�ѱ��ŷ��Ҹ޽�����ȣ
CString strCOMM_MDIA_DCD_NM = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "COMM_MDIA_DCD_NM", nRow);		//��Ÿ�ü�����ڵ��
CString strXTNL_ISTT_RJCT_RSN_CD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "XTNL_ISTT_RJCT_RSN_CD", nRow);		//�ܺα���źλ����ڵ�
CString strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "SELL_BUY_DCD", nRow);		//�ŵ��ż������ڵ�
