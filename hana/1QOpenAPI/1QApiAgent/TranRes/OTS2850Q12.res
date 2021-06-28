BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2850Q12, TR_NAME=ü��Ǻ��ֹ�ü�᳻����ȸ, SERVER=B, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2850Q12_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=PWD, TYPE=string, SIZE=64, CAPTION=��й�ȣ;
			 INDEX=3, ITEM=CNCS_DCD, TYPE=string, SIZE=2, CAPTION=ü�ᱸ���ڵ�;
			 INDEX=4, ITEM=STRT_ORDR_SN, TYPE=string, SIZE=11, CAPTION=�����ֹ��Ϸù�ȣ;
			 INDEX=5, ITEM=INQ_DVSN, TYPE=string, SIZE=1, CAPTION=��ȸ����;
			 INDEX=6, ITEM=INQ_STDR_DT, TYPE=string, SIZE=8, CAPTION=��ȸ��������;
			 INDEX=7, ITEM=DRVS_ITM_DVSN, TYPE=string, SIZE=1, CAPTION=�Ļ���ǰ���񱸺�;
			 INDEX=8, ITEM=FTOP_DCD, TYPE=string, SIZE=1, CAPTION=�����ɼǱ����ڵ�;
			 INDEX=9, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
			 INDEX=10, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2850Q12_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=FTR_SELL_ORDR_QNT_SMM, TYPE=string, SIZE=19, CAPTION=�����ŵ��ֹ������հ�;
			 INDEX=1, ITEM=FTR_BUY_ORDR_QNT_SMM, TYPE=string, SIZE=19, CAPTION=�����ż��ֹ������հ�;
			 INDEX=2, ITEM=IDX_CLPT_SELL_ORDR_QNT_SMM, TYPE=string, SIZE=19, CAPTION=�����ݿɼǸŵ��ֹ������հ�;
			 INDEX=3, ITEM=IDX_PTPT_SELL_ORDR_QNT_SMM, TYPE=string, SIZE=19, CAPTION=����ǲ�ɼǸŵ��ֹ������հ�;
			 INDEX=4, ITEM=IDX_CLPT_BUY_ORDR_QNT_SMM, TYPE=string, SIZE=19, CAPTION=�����ݿɼǸż��ֹ������հ�;
			 INDEX=5, ITEM=IDX_PTPT_BUY_ORDR_QNT_SMM, TYPE=string, SIZE=19, CAPTION=����ǲ�ɼǸż��ֹ������հ�;
			 INDEX=6, ITEM=FTR_SELL_CNCS_QNT_SMM, TYPE=string, SIZE=19, CAPTION=�����ŵ�ü������հ�;
			 INDEX=7, ITEM=FTR_BUY_CNCS_QNT_SMM, TYPE=string, SIZE=19, CAPTION=�����ż�ü������հ�;
			 INDEX=8, ITEM=IDX_CLPT_SELL_CNCS_QNT_SMM, TYPE=string, SIZE=19, CAPTION=�����ݿɼǸŵ�ü������հ�;
			 INDEX=9, ITEM=IDX_PTPT_SELL_CNCS_QNT_SMM, TYPE=string, SIZE=19, CAPTION=����ǲ�ɼǸŵ�ü������հ�;
			 INDEX=10, ITEM=IDX_CLPT_BUY_CNCS_QNT_SMM, TYPE=string, SIZE=19, CAPTION=�����ݿɼǸż�ü������հ�;
			 INDEX=11, ITEM=IDX_PTPT_BUY_CNCS_QNT_SMM, TYPE=string, SIZE=20, CAPTION=����ǲ�ɼǸż�ü������հ�;
		END_OUTPUT0_ITEM

		REC_NAME=OTS2850Q12_out_sub01, INOUT=1, ARRAY=1, ARRINFO=;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=MNGM_BDCD, TYPE=string, SIZE=5, CAPTION=���������ڵ�;
			 INDEX=1, ITEM=MNGM_BD_NM, TYPE=string, SIZE=40, CAPTION=����������;
			 INDEX=2, ITEM=MO_ORDR_SN, TYPE=string, SIZE=11, CAPTION=���ֹ��Ϸù�ȣ;
			 INDEX=3, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ֹ��Ϸù�ȣ;
			 INDEX=4, ITEM=OR_ORDR_SN, TYPE=string, SIZE=11, CAPTION=���ֹ��Ϸù�ȣ;
			 INDEX=5, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=6, ITEM=PRDT_NM, TYPE=string, SIZE=300, CAPTION=��ǰ��;
			 INDEX=7, ITEM=DRVS_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=�Ļ���ǰȣ�������ڵ�;
			 INDEX=8, ITEM=DRVS_NMPR_DVSN_NM, TYPE=string, SIZE=50, CAPTION=�Ļ���ǰȣ�����и�;
			 INDEX=9, ITEM=ORDR_PRC_CTNS, TYPE=string, SIZE=40, CAPTION=�ֹ����ݳ���;
			 INDEX=10, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=11, ITEM=CNCS_DVSN_NM, TYPE=string, SIZE=50, CAPTION=ü�ᱸ�и�;
			 INDEX=12, ITEM=CNCS_PRC_CTNS, TYPE=string, SIZE=30, CAPTION=ü�ᰡ�ݳ���;
			 INDEX=13, ITEM=CNCS_QNT, TYPE=string, SIZE=19, CAPTION=ü�����;
			 INDEX=14, ITEM=CNCS_DTMD, TYPE=string, SIZE=9, CAPTION=ü��󼼽ð�;
			 INDEX=15, ITEM=NCNC_QNT, TYPE=string, SIZE=19, CAPTION=��ü�����;
			 INDEX=16, ITEM=DRVS_NMPR_ACPT_DCD, TYPE=string, SIZE=2, CAPTION=�Ļ���ǰȣ�����������ڵ�;
			 INDEX=17, ITEM=DRVS_NMPR_ACPT_DVSN_NM, TYPE=string, SIZE=50, CAPTION=�Ļ���ǰȣ���������и�;
			 INDEX=18, ITEM=HND_DETL_DTM, TYPE=string, SIZE=17, CAPTION=���ۻ��Ͻ�;
			 INDEX=19, ITEM=KRX_MSG_NO, TYPE=string, SIZE=12, CAPTION=�ѱ��ŷ��Ҹ޽�����ȣ;
			 INDEX=20, ITEM=CNCS_SN, TYPE=string, SIZE=11, CAPTION=ü���Ϸù�ȣ;
			 INDEX=21, ITEM=XTNL_ISTT_RJCT_RSN_CD, TYPE=string, SIZE=5, CAPTION=�ܺα���źλ����ڵ�;
			 INDEX=22, ITEM=COMM_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ü�����ڵ�;
			 INDEX=23, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
			 INDEX=24, ITEM=SELL_BUY_DVSN_NM, TYPE=string, SIZE=40, CAPTION=�ŵ��ż����и�;
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
CString strCNCS_DCD;		//ü�ᱸ���ڵ�
CString strSTRT_ORDR_SN;		//�����ֹ��Ϸù�ȣ
CString strINQ_DVSN;		//��ȸ����
CString strINQ_STDR_DT;		//��ȸ��������
CString strDRVS_ITM_DVSN;		//�Ļ���ǰ���񱸺�
CString strFTOP_DCD;		//�����ɼǱ����ڵ�
CString strSELL_BUY_DCD;		//�ŵ��ż������ڵ�
CString strPRDT_CD;		//��ǰ�ڵ�

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "PWD", strPWD);		//��й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "CNCS_DCD", strCNCS_DCD);		//ü�ᱸ���ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "STRT_ORDR_SN", strSTRT_ORDR_SN);		//�����ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "INQ_DVSN", strINQ_DVSN);		//��ȸ����
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "INQ_STDR_DT", strINQ_STDR_DT);		//��ȸ��������
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "DRVS_ITM_DVSN", strDRVS_ITM_DVSN);		//�Ļ���ǰ���񱸺�
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "FTOP_DCD", strFTOP_DCD);		//�����ɼǱ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//�ŵ��ż������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2850Q12", "OTS2850Q12_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strFTR_SELL_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_SELL_ORDR_QNT_SMM", 0);		//�����ŵ��ֹ������հ�
CString strFTR_BUY_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_BUY_ORDR_QNT_SMM", 0);		//�����ż��ֹ������հ�
CString strIDX_CLPT_SELL_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_SELL_ORDR_QNT_SMM", 0);		//�����ݿɼǸŵ��ֹ������հ�
CString strIDX_PTPT_SELL_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_SELL_ORDR_QNT_SMM", 0);		//����ǲ�ɼǸŵ��ֹ������հ�
CString strIDX_CLPT_BUY_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_BUY_ORDR_QNT_SMM", 0);		//�����ݿɼǸż��ֹ������հ�
CString strIDX_PTPT_BUY_ORDR_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_BUY_ORDR_QNT_SMM", 0);		//����ǲ�ɼǸż��ֹ������հ�
CString strFTR_SELL_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_SELL_CNCS_QNT_SMM", 0);		//�����ŵ�ü������հ�
CString strFTR_BUY_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "FTR_BUY_CNCS_QNT_SMM", 0);		//�����ż�ü������հ�
CString strIDX_CLPT_SELL_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_SELL_CNCS_QNT_SMM", 0);		//�����ݿɼǸŵ�ü������հ�
CString strIDX_PTPT_SELL_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_SELL_CNCS_QNT_SMM", 0);		//����ǲ�ɼǸŵ�ü������հ�
CString strIDX_CLPT_BUY_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_CLPT_BUY_CNCS_QNT_SMM", 0);		//�����ݿɼǸż�ü������հ�
CString strIDX_PTPT_BUY_CNCS_QNT_SMM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out", "IDX_PTPT_BUY_CNCS_QNT_SMM", 0);		//����ǲ�ɼǸż�ü������հ�
CString strMNGM_BDCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "MNGM_BDCD", nRow);		//���������ڵ�
CString strMNGM_BD_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "MNGM_BD_NM", nRow);		//����������
CString strMO_ORDR_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "MO_ORDR_SN", nRow);		//���ֹ��Ϸù�ȣ
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "ORDR_SN", nRow);		//�ֹ��Ϸù�ȣ
CString strOR_ORDR_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "OR_ORDR_SN", nRow);		//���ֹ��Ϸù�ȣ
CString strPRDT_CD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "PRDT_CD", nRow);		//��ǰ�ڵ�
CString strPRDT_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "PRDT_NM", nRow);		//��ǰ��
CString strDRVS_NMPR_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_DCD", nRow);		//�Ļ���ǰȣ�������ڵ�
CString strDRVS_NMPR_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_DVSN_NM", nRow);		//�Ļ���ǰȣ�����и�
CString strORDR_PRC_CTNS = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "ORDR_PRC_CTNS", nRow);		//�ֹ����ݳ���
CString strORDR_QNT = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "ORDR_QNT", nRow);		//�ֹ�����
CString strCNCS_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_DVSN_NM", nRow);		//ü�ᱸ�и�
CString strCNCS_PRC_CTNS = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_PRC_CTNS", nRow);		//ü�ᰡ�ݳ���
CString strCNCS_QNT = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_QNT", nRow);		//ü�����
CString strCNCS_DTMD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_DTMD", nRow);		//ü��󼼽ð�
CString strNCNC_QNT = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "NCNC_QNT", nRow);		//��ü�����
CString strDRVS_NMPR_ACPT_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_ACPT_DCD", nRow);		//�Ļ���ǰȣ�����������ڵ�
CString strDRVS_NMPR_ACPT_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "DRVS_NMPR_ACPT_DVSN_NM", nRow);		//�Ļ���ǰȣ���������и�
CString strHND_DETL_DTM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "HND_DETL_DTM", nRow);		//���ۻ��Ͻ�
CString strKRX_MSG_NO = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "KRX_MSG_NO", nRow);		//�ѱ��ŷ��Ҹ޽�����ȣ
CString strCNCS_SN = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "CNCS_SN", nRow);		//ü���Ϸù�ȣ
CString strXTNL_ISTT_RJCT_RSN_CD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "XTNL_ISTT_RJCT_RSN_CD", nRow);		//�ܺα���źλ����ڵ�
CString strCOMM_MDIA_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "COMM_MDIA_DCD", nRow);		//��Ÿ�ü�����ڵ�
CString strSELL_BUY_DCD = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "SELL_BUY_DCD", nRow);		//�ŵ��ż������ڵ�
CString strSELL_BUY_DVSN_NM = m_CommAgent.GetTranOutputData("OTS2850Q12", "OTS2850Q12_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//�ŵ��ż����и�
