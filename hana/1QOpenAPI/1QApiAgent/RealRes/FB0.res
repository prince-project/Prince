BEGIN_FUNCTION_MAP
	REAL_TYPE=230, REAL_NAME=FB0, DESCRIPTION=EUREX �̴��ڽ��� 200 ���� ü��;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=SHRN_ISCD, TYPE=string, SIZE=9, KEY=1, CAPTION=���� �ڵ�, FID=0;
			 INDEX=1, ITEM=BSOP_DATE, TYPE=string, SIZE=8, KEY=0, CAPTION=�ǽð�����, FID=0;
			 INDEX=2, ITEM=BSOP_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=ü�� �ð�, FID=0;
			 INDEX=3, ITEM=PRPR, TYPE=string, SIZE=11, KEY=0, CAPTION=���簡, FID=0;
			 INDEX=4, ITEM=PRPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRPR]������(+���, -�϶�), FID=0;
			 INDEX=5, ITEM=PRDY_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=���� ��� ��ȣ, FID=0;
			 INDEX=6, ITEM=PRDY_VRSS, TYPE=string, SIZE=11, KEY=0, CAPTION=���� ���, FID=0;
			 INDEX=7, ITEM=PRDY_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRDY_VRSS]������(+���, -�϶�), FID=0;
			 INDEX=8, ITEM=PRDY_CTRT, TYPE=string, SIZE=10, KEY=0, CAPTION=���� �����, FID=0;
			 INDEX=9, ITEM=PRDY_CTRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRDY_CTRT]������(+���, -�϶�), FID=0;
			 INDEX=10, ITEM=CNTG_VOL, TYPE=string, SIZE=12, KEY=0, CAPTION=ü�ᷮ, FID=0;
			 INDEX=11, ITEM=CNTG_VOL_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[CNTG_VOL]������(+���, -�϶�), FID=0;
			 INDEX=12, ITEM=ACML_VOL, TYPE=string, SIZE=13, KEY=0, CAPTION=���� �ŷ���, FID=0;
			 INDEX=13, ITEM=ACML_TR_PBMN, TYPE=string, SIZE=13, KEY=0, CAPTION=���� �ŷ� ���, FID=0;
			 INDEX=14, ITEM=OPRC, TYPE=string, SIZE=11, KEY=0, CAPTION=�ð�, FID=0;
			 INDEX=15, ITEM=OPRC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPRC]������(+���, -�϶�), FID=0;
			 INDEX=16, ITEM=HGPR, TYPE=string, SIZE=11, KEY=0, CAPTION=��, FID=0;
			 INDEX=17, ITEM=HGPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[HGPR]������(+���, -�϶�), FID=0;
			 INDEX=18, ITEM=LWPR, TYPE=string, SIZE=11, KEY=0, CAPTION=����, FID=0;
			 INDEX=19, ITEM=LWPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LWPR]������(+���, -�϶�), FID=0;
			 INDEX=20, ITEM=OPRC_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=�ð� �ð�, FID=0;
			 INDEX=21, ITEM=OPRC_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=�ð� ��� ��ȣ, FID=0;
			 INDEX=22, ITEM=OPRC_VRSS, TYPE=string, SIZE=11, KEY=0, CAPTION=�ð� ���, FID=0;
			 INDEX=23, ITEM=OPRC_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OPRC_VRSS]������(+���, -�϶�), FID=0;
			 INDEX=24, ITEM=HGPR_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=�� �ð�, FID=0;
			 INDEX=25, ITEM=HGPR_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=�� ��� ��ȣ, FID=0;
			 INDEX=26, ITEM=HGPR_VRSS, TYPE=string, SIZE=11, KEY=0, CAPTION=�� ���, FID=0;
			 INDEX=27, ITEM=HGPR_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[HGPR_VRSS]������(+���, -�϶�), FID=0;
			 INDEX=28, ITEM=LWPR_HOUR, TYPE=string, SIZE=6, KEY=0, CAPTION=���� �ð�, FID=0;
			 INDEX=29, ITEM=LWPR_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=���� ��� ��ȣ, FID=0;
			 INDEX=30, ITEM=LWPR_VRSS, TYPE=string, SIZE=11, KEY=0, CAPTION=���� ���, FID=0;
			 INDEX=31, ITEM=LWPR_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[LWPR_VRSS]������(+���, -�϶�), FID=0;
			 INDEX=32, ITEM=NMSC_FCTN_STPL_PRC, TYPE=string, SIZE=10, KEY=0, CAPTION=�ٿ��� ���� ������, FID=0;
			 INDEX=33, ITEM=FMSC_FCTN_STPL_PRC, TYPE=string, SIZE=10, KEY=0, CAPTION=������ ���� ������, FID=0;
			 INDEX=34, ITEM=SPEAD_PRC, TYPE=string, SIZE=9, KEY=0, CAPTION=��������, FID=0;
			 INDEX=35, ITEM=OTST_STPL_QTY, TYPE=string, SIZE=13, KEY=0, CAPTION=�̰��� ���� ����, FID=0;
			 INDEX=36, ITEM=OTST_STPL_QTY_ICDC, TYPE=string, SIZE=14, KEY=0, CAPTION=�̰��� ���� ���� ����, FID=0;
			 INDEX=37, ITEM=OTST_STPL_QTY_ICDC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OTST_STPL_QTY_ICDC]������(+���, -�϶�), FID=0;
			 INDEX=38, ITEM=OTST_STPL_QTY_REF_IC, TYPE=string, SIZE=14, KEY=0, CAPTION=�̰��� ���� ���� ���� ����, FID=0;
			 INDEX=39, ITEM=OTST_STPL_QTY_REF_IC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[OTST_STPL_QTY_REF_IC]������(+���, -�϶�), FID=0;
			 INDEX=40, ITEM=THPR, TYPE=string, SIZE=10, KEY=0, CAPTION=�̷а�, FID=0;
			 INDEX=41, ITEM=THPR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[THPR]������(+���, -�϶�), FID=0;
			 INDEX=42, ITEM=MRKT_BASIS, TYPE=string, SIZE=10, KEY=0, CAPTION=���� BASIS, FID=0;
			 INDEX=43, ITEM=MRKT_BASIS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[MRKT_BASIS]������(+���, -�϶�), FID=0;
			 INDEX=44, ITEM=THER_BASIS, TYPE=string, SIZE=10, KEY=0, CAPTION=�̷� BASIS, FID=0;
			 INDEX=45, ITEM=THER_BASIS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[THER_BASIS]������(+���, -�϶�), FID=0;
			 INDEX=46, ITEM=ESDG, TYPE=string, SIZE=10, KEY=0, CAPTION=������, FID=0;
			 INDEX=47, ITEM=ESDG_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ESDG]������(+���, -�϶�), FID=0;
			 INDEX=48, ITEM=DPRT, TYPE=string, SIZE=10, KEY=0, CAPTION=������, FID=0;
			 INDEX=49, ITEM=DPRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[DPRT]������(+���, -�϶�), FID=0;
			 INDEX=50, ITEM=SHNU_RATE, TYPE=string, SIZE=10, KEY=0, CAPTION=�ż�����, FID=0;
			 INDEX=51, ITEM=SHNU_RATE_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[SHNU_RATE]������(+���, -�϶�), FID=0;
			 INDEX=52, ITEM=CTTR, TYPE=string, SIZE=10, KEY=0, CAPTION=ü�ᰭ��, FID=0;
			 INDEX=53, ITEM=CTTR_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[CTTR]������(+���, -�϶�), FID=0;
			 INDEX=54, ITEM=ASKP1, TYPE=string, SIZE=11, KEY=0, CAPTION=�ŵ�ȣ��1, FID=0;
			 INDEX=55, ITEM=ASKP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[ASKP1]������(+���, -�϶�), FID=0;
			 INDEX=56, ITEM=BIDP1, TYPE=string, SIZE=11, KEY=0, CAPTION=�ż�ȣ��1, FID=0;
			 INDEX=57, ITEM=BIDP1_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[BIDP1]������(+���, -�϶�), FID=0;
			 INDEX=58, ITEM=ASKP_RSQN1, TYPE=string, SIZE=13, KEY=0, CAPTION=�ŵ�ȣ�� �ܷ�, FID=0;
			 INDEX=59, ITEM=BIDP_RSQN1, TYPE=string, SIZE=13, KEY=0, CAPTION=�ż�ȣ�� �ܷ�, FID=0;
			 INDEX=60, ITEM=SELN_CNTG_CSNU, TYPE=string, SIZE=5, KEY=0, CAPTION=�ŵ� ü�� �Ǽ�, FID=0;
			 INDEX=61, ITEM=SHNU_CNTG_CSNU, TYPE=string, SIZE=5, KEY=0, CAPTION=�ż� ü�� �Ǽ�, FID=0;
			 INDEX=62, ITEM=NTBY_CNTG_CSNU, TYPE=string, SIZE=6, KEY=0, CAPTION=���ż� ü�� �Ǽ�, FID=0;
			 INDEX=63, ITEM=NTBY_CNTG_CSNU_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[NTBY_CNTG_CSNU]������(+���, -�϶�), FID=0;
			 INDEX=64, ITEM=SELN_CNTG_SMTN, TYPE=string, SIZE=13, KEY=0, CAPTION=�ŵ� ü�� �հ�, FID=0;
			 INDEX=65, ITEM=SHNU_CNTG_SMTN, TYPE=string, SIZE=13, KEY=0, CAPTION=�ż� ü�� �հ�, FID=0;
			 INDEX=66, ITEM=TOTAL_ASKP_RSQN, TYPE=string, SIZE=13, KEY=0, CAPTION=�� �ŵ�ȣ�� �ܷ�, FID=0;
			 INDEX=67, ITEM=TOTAL_BIDP_RSQN, TYPE=string, SIZE=13, KEY=0, CAPTION=�� �ż�ȣ�� �ܷ�, FID=0;
			 INDEX=68, ITEM=PRDY_VRSS_VOL_RATE, TYPE=string, SIZE=10, KEY=0, CAPTION=���� ��� �ŷ��� ����, FID=0;
			 INDEX=69, ITEM=PRDY_VRSS_VOL_RATE_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[PRDY_VRSS_VOL_RATE]������(+���, -�϶�), FID=0;
			 INDEX=70, ITEM=UNAS_PRC, TYPE=string, SIZE=13, KEY=0, CAPTION=�����ڻ� ����, FID=0;
			 INDEX=71, ITEM=UNAS_PRC_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[UNAS_PRC]������(+���, -�϶�), FID=0;
			 INDEX=72, ITEM=UNAS_PRDY_VRSS_SIGN, TYPE=string, SIZE=1, KEY=0, CAPTION=�����ڻ� ���ϴ�񱸺�, FID=0;
			 INDEX=73, ITEM=UNAS_PRDY_VRSS, TYPE=string, SIZE=13, KEY=0, CAPTION=�����ڻ� ���� ���, FID=0;
			 INDEX=74, ITEM=UNAS_PRDY_VRSS_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[UNAS_PRDY_VRSS]������(+���, -�϶�), FID=0;
			 INDEX=75, ITEM=UNAS_PRDY_CTRT, TYPE=string, SIZE=10, KEY=0, CAPTION=�����ڻ� ���� �����, FID=0;
			 INDEX=76, ITEM=UNAS_PRDY_CTRT_CLR, TYPE=string, SIZE=1, KEY=0, CAPTION=[UNAS_PRDY_CTRT]������(+���, -�϶�), FID=0;
			 INDEX=77, ITEM=CNTG_PRGS, TYPE=string, SIZE=10, KEY=0, CAPTION=ü��ƽ����, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 ���� ���Ǹ� ���� GetRealOutputData �޼ҵ� MFC �ҽ� ���ø�
 **********************************************/
CString strSHRN_ISCD = m_CommAgent.GetRealOutputData("FB0", "SHRN_ISCD");		//���� �ڵ�
CString strBSOP_DATE = m_CommAgent.GetRealOutputData("FB0", "BSOP_DATE");		//�ǽð�����
CString strBSOP_HOUR = m_CommAgent.GetRealOutputData("FB0", "BSOP_HOUR");		//ü�� �ð�
CString strPRPR = m_CommAgent.GetRealOutputData("FB0", "PRPR");		//���簡
CString strPRPR_CLR = m_CommAgent.GetRealOutputData("FB0", "PRPR_CLR");		//[PRPR]������(+���, -�϶�)
CString strPRDY_VRSS_SIGN = m_CommAgent.GetRealOutputData("FB0", "PRDY_VRSS_SIGN");		//���� ��� ��ȣ
CString strPRDY_VRSS = m_CommAgent.GetRealOutputData("FB0", "PRDY_VRSS");		//���� ���
CString strPRDY_VRSS_CLR = m_CommAgent.GetRealOutputData("FB0", "PRDY_VRSS_CLR");		//[PRDY_VRSS]������(+���, -�϶�)
CString strPRDY_CTRT = m_CommAgent.GetRealOutputData("FB0", "PRDY_CTRT");		//���� �����
CString strPRDY_CTRT_CLR = m_CommAgent.GetRealOutputData("FB0", "PRDY_CTRT_CLR");		//[PRDY_CTRT]������(+���, -�϶�)
CString strCNTG_VOL = m_CommAgent.GetRealOutputData("FB0", "CNTG_VOL");		//ü�ᷮ
CString strCNTG_VOL_CLR = m_CommAgent.GetRealOutputData("FB0", "CNTG_VOL_CLR");		//[CNTG_VOL]������(+���, -�϶�)
CString strACML_VOL = m_CommAgent.GetRealOutputData("FB0", "ACML_VOL");		//���� �ŷ���
CString strACML_TR_PBMN = m_CommAgent.GetRealOutputData("FB0", "ACML_TR_PBMN");		//���� �ŷ� ���
CString strOPRC = m_CommAgent.GetRealOutputData("FB0", "OPRC");		//�ð�
CString strOPRC_CLR = m_CommAgent.GetRealOutputData("FB0", "OPRC_CLR");		//[OPRC]������(+���, -�϶�)
CString strHGPR = m_CommAgent.GetRealOutputData("FB0", "HGPR");		//��
CString strHGPR_CLR = m_CommAgent.GetRealOutputData("FB0", "HGPR_CLR");		//[HGPR]������(+���, -�϶�)
CString strLWPR = m_CommAgent.GetRealOutputData("FB0", "LWPR");		//����
CString strLWPR_CLR = m_CommAgent.GetRealOutputData("FB0", "LWPR_CLR");		//[LWPR]������(+���, -�϶�)
CString strOPRC_HOUR = m_CommAgent.GetRealOutputData("FB0", "OPRC_HOUR");		//�ð� �ð�
CString strOPRC_VRSS_SIGN = m_CommAgent.GetRealOutputData("FB0", "OPRC_VRSS_SIGN");		//�ð� ��� ��ȣ
CString strOPRC_VRSS = m_CommAgent.GetRealOutputData("FB0", "OPRC_VRSS");		//�ð� ���
CString strOPRC_VRSS_CLR = m_CommAgent.GetRealOutputData("FB0", "OPRC_VRSS_CLR");		//[OPRC_VRSS]������(+���, -�϶�)
CString strHGPR_HOUR = m_CommAgent.GetRealOutputData("FB0", "HGPR_HOUR");		//�� �ð�
CString strHGPR_VRSS_SIGN = m_CommAgent.GetRealOutputData("FB0", "HGPR_VRSS_SIGN");		//�� ��� ��ȣ
CString strHGPR_VRSS = m_CommAgent.GetRealOutputData("FB0", "HGPR_VRSS");		//�� ���
CString strHGPR_VRSS_CLR = m_CommAgent.GetRealOutputData("FB0", "HGPR_VRSS_CLR");		//[HGPR_VRSS]������(+���, -�϶�)
CString strLWPR_HOUR = m_CommAgent.GetRealOutputData("FB0", "LWPR_HOUR");		//���� �ð�
CString strLWPR_VRSS_SIGN = m_CommAgent.GetRealOutputData("FB0", "LWPR_VRSS_SIGN");		//���� ��� ��ȣ
CString strLWPR_VRSS = m_CommAgent.GetRealOutputData("FB0", "LWPR_VRSS");		//���� ���
CString strLWPR_VRSS_CLR = m_CommAgent.GetRealOutputData("FB0", "LWPR_VRSS_CLR");		//[LWPR_VRSS]������(+���, -�϶�)
CString strNMSC_FCTN_STPL_PRC = m_CommAgent.GetRealOutputData("FB0", "NMSC_FCTN_STPL_PRC");		//�ٿ��� ���� ������
CString strFMSC_FCTN_STPL_PRC = m_CommAgent.GetRealOutputData("FB0", "FMSC_FCTN_STPL_PRC");		//������ ���� ������
CString strSPEAD_PRC = m_CommAgent.GetRealOutputData("FB0", "SPEAD_PRC");		//��������
CString strOTST_STPL_QTY = m_CommAgent.GetRealOutputData("FB0", "OTST_STPL_QTY");		//�̰��� ���� ����
CString strOTST_STPL_QTY_ICDC = m_CommAgent.GetRealOutputData("FB0", "OTST_STPL_QTY_ICDC");		//�̰��� ���� ���� ����
CString strOTST_STPL_QTY_ICDC_CLR = m_CommAgent.GetRealOutputData("FB0", "OTST_STPL_QTY_ICDC_CLR");		//[OTST_STPL_QTY_ICDC]������(+���, -�϶�)
CString strOTST_STPL_QTY_REF_IC = m_CommAgent.GetRealOutputData("FB0", "OTST_STPL_QTY_REF_IC");		//�̰��� ���� ���� ���� ����
CString strOTST_STPL_QTY_REF_IC_CLR = m_CommAgent.GetRealOutputData("FB0", "OTST_STPL_QTY_REF_IC_CLR");		//[OTST_STPL_QTY_REF_IC]������(+���, -�϶�)
CString strTHPR = m_CommAgent.GetRealOutputData("FB0", "THPR");		//�̷а�
CString strTHPR_CLR = m_CommAgent.GetRealOutputData("FB0", "THPR_CLR");		//[THPR]������(+���, -�϶�)
CString strMRKT_BASIS = m_CommAgent.GetRealOutputData("FB0", "MRKT_BASIS");		//���� BASIS
CString strMRKT_BASIS_CLR = m_CommAgent.GetRealOutputData("FB0", "MRKT_BASIS_CLR");		//[MRKT_BASIS]������(+���, -�϶�)
CString strTHER_BASIS = m_CommAgent.GetRealOutputData("FB0", "THER_BASIS");		//�̷� BASIS
CString strTHER_BASIS_CLR = m_CommAgent.GetRealOutputData("FB0", "THER_BASIS_CLR");		//[THER_BASIS]������(+���, -�϶�)
CString strESDG = m_CommAgent.GetRealOutputData("FB0", "ESDG");		//������
CString strESDG_CLR = m_CommAgent.GetRealOutputData("FB0", "ESDG_CLR");		//[ESDG]������(+���, -�϶�)
CString strDPRT = m_CommAgent.GetRealOutputData("FB0", "DPRT");		//������
CString strDPRT_CLR = m_CommAgent.GetRealOutputData("FB0", "DPRT_CLR");		//[DPRT]������(+���, -�϶�)
CString strSHNU_RATE = m_CommAgent.GetRealOutputData("FB0", "SHNU_RATE");		//�ż�����
CString strSHNU_RATE_CLR = m_CommAgent.GetRealOutputData("FB0", "SHNU_RATE_CLR");		//[SHNU_RATE]������(+���, -�϶�)
CString strCTTR = m_CommAgent.GetRealOutputData("FB0", "CTTR");		//ü�ᰭ��
CString strCTTR_CLR = m_CommAgent.GetRealOutputData("FB0", "CTTR_CLR");		//[CTTR]������(+���, -�϶�)
CString strASKP1 = m_CommAgent.GetRealOutputData("FB0", "ASKP1");		//�ŵ�ȣ��1
CString strASKP1_CLR = m_CommAgent.GetRealOutputData("FB0", "ASKP1_CLR");		//[ASKP1]������(+���, -�϶�)
CString strBIDP1 = m_CommAgent.GetRealOutputData("FB0", "BIDP1");		//�ż�ȣ��1
CString strBIDP1_CLR = m_CommAgent.GetRealOutputData("FB0", "BIDP1_CLR");		//[BIDP1]������(+���, -�϶�)
CString strASKP_RSQN1 = m_CommAgent.GetRealOutputData("FB0", "ASKP_RSQN1");		//�ŵ�ȣ�� �ܷ�
CString strBIDP_RSQN1 = m_CommAgent.GetRealOutputData("FB0", "BIDP_RSQN1");		//�ż�ȣ�� �ܷ�
CString strSELN_CNTG_CSNU = m_CommAgent.GetRealOutputData("FB0", "SELN_CNTG_CSNU");		//�ŵ� ü�� �Ǽ�
CString strSHNU_CNTG_CSNU = m_CommAgent.GetRealOutputData("FB0", "SHNU_CNTG_CSNU");		//�ż� ü�� �Ǽ�
CString strNTBY_CNTG_CSNU = m_CommAgent.GetRealOutputData("FB0", "NTBY_CNTG_CSNU");		//���ż� ü�� �Ǽ�
CString strNTBY_CNTG_CSNU_CLR = m_CommAgent.GetRealOutputData("FB0", "NTBY_CNTG_CSNU_CLR");		//[NTBY_CNTG_CSNU]������(+���, -�϶�)
CString strSELN_CNTG_SMTN = m_CommAgent.GetRealOutputData("FB0", "SELN_CNTG_SMTN");		//�ŵ� ü�� �հ�
CString strSHNU_CNTG_SMTN = m_CommAgent.GetRealOutputData("FB0", "SHNU_CNTG_SMTN");		//�ż� ü�� �հ�
CString strTOTAL_ASKP_RSQN = m_CommAgent.GetRealOutputData("FB0", "TOTAL_ASKP_RSQN");		//�� �ŵ�ȣ�� �ܷ�
CString strTOTAL_BIDP_RSQN = m_CommAgent.GetRealOutputData("FB0", "TOTAL_BIDP_RSQN");		//�� �ż�ȣ�� �ܷ�
CString strPRDY_VRSS_VOL_RATE = m_CommAgent.GetRealOutputData("FB0", "PRDY_VRSS_VOL_RATE");		//���� ��� �ŷ��� ����
CString strPRDY_VRSS_VOL_RATE_CLR = m_CommAgent.GetRealOutputData("FB0", "PRDY_VRSS_VOL_RATE_CLR");		//[PRDY_VRSS_VOL_RATE]������(+���, -�϶�)
CString strUNAS_PRC = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRC");		//�����ڻ� ����
CString strUNAS_PRC_CLR = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRC_CLR");		//[UNAS_PRC]������(+���, -�϶�)
CString strUNAS_PRDY_VRSS_SIGN = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRDY_VRSS_SIGN");		//�����ڻ� ���ϴ�񱸺�
CString strUNAS_PRDY_VRSS = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRDY_VRSS");		//�����ڻ� ���� ���
CString strUNAS_PRDY_VRSS_CLR = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRDY_VRSS_CLR");		//[UNAS_PRDY_VRSS]������(+���, -�϶�)
CString strUNAS_PRDY_CTRT = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRDY_CTRT");		//�����ڻ� ���� �����
CString strUNAS_PRDY_CTRT_CLR = m_CommAgent.GetRealOutputData("FB0", "UNAS_PRDY_CTRT_CLR");		//[UNAS_PRDY_CTRT]������(+���, -�϶�)
CString strCNTG_PRGS = m_CommAgent.GetRealOutputData("FB0", "CNTG_PRGS");		//ü��ƽ����




/**********************************************
 ���� ���Ǹ� ���� �޸� �ε��� ���� �ҽ� ���ø�(C++������ ��� ����)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strSHRN_ISCD = realCommRecvData.GetItem(0, 0);		//���� �ڵ�
CString strBSOP_DATE = realCommRecvData.GetItem(0, 1);		//�ǽð�����
CString strBSOP_HOUR = realCommRecvData.GetItem(0, 2);		//ü�� �ð�
CString strPRPR = realCommRecvData.GetItem(0, 3);		//���簡
CString strPRPR_CLR = realCommRecvData.GetItem(0, 4);		//[PRPR]������(+���, -�϶�)
CString strPRDY_VRSS_SIGN = realCommRecvData.GetItem(0, 5);		//���� ��� ��ȣ
CString strPRDY_VRSS = realCommRecvData.GetItem(0, 6);		//���� ���
CString strPRDY_VRSS_CLR = realCommRecvData.GetItem(0, 7);		//[PRDY_VRSS]������(+���, -�϶�)
CString strPRDY_CTRT = realCommRecvData.GetItem(0, 8);		//���� �����
CString strPRDY_CTRT_CLR = realCommRecvData.GetItem(0, 9);		//[PRDY_CTRT]������(+���, -�϶�)
CString strCNTG_VOL = realCommRecvData.GetItem(0, 10);		//ü�ᷮ
CString strCNTG_VOL_CLR = realCommRecvData.GetItem(0, 11);		//[CNTG_VOL]������(+���, -�϶�)
CString strACML_VOL = realCommRecvData.GetItem(0, 12);		//���� �ŷ���
CString strACML_TR_PBMN = realCommRecvData.GetItem(0, 13);		//���� �ŷ� ���
CString strOPRC = realCommRecvData.GetItem(0, 14);		//�ð�
CString strOPRC_CLR = realCommRecvData.GetItem(0, 15);		//[OPRC]������(+���, -�϶�)
CString strHGPR = realCommRecvData.GetItem(0, 16);		//��
CString strHGPR_CLR = realCommRecvData.GetItem(0, 17);		//[HGPR]������(+���, -�϶�)
CString strLWPR = realCommRecvData.GetItem(0, 18);		//����
CString strLWPR_CLR = realCommRecvData.GetItem(0, 19);		//[LWPR]������(+���, -�϶�)
CString strOPRC_HOUR = realCommRecvData.GetItem(0, 20);		//�ð� �ð�
CString strOPRC_VRSS_SIGN = realCommRecvData.GetItem(0, 21);		//�ð� ��� ��ȣ
CString strOPRC_VRSS = realCommRecvData.GetItem(0, 22);		//�ð� ���
CString strOPRC_VRSS_CLR = realCommRecvData.GetItem(0, 23);		//[OPRC_VRSS]������(+���, -�϶�)
CString strHGPR_HOUR = realCommRecvData.GetItem(0, 24);		//�� �ð�
CString strHGPR_VRSS_SIGN = realCommRecvData.GetItem(0, 25);		//�� ��� ��ȣ
CString strHGPR_VRSS = realCommRecvData.GetItem(0, 26);		//�� ���
CString strHGPR_VRSS_CLR = realCommRecvData.GetItem(0, 27);		//[HGPR_VRSS]������(+���, -�϶�)
CString strLWPR_HOUR = realCommRecvData.GetItem(0, 28);		//���� �ð�
CString strLWPR_VRSS_SIGN = realCommRecvData.GetItem(0, 29);		//���� ��� ��ȣ
CString strLWPR_VRSS = realCommRecvData.GetItem(0, 30);		//���� ���
CString strLWPR_VRSS_CLR = realCommRecvData.GetItem(0, 31);		//[LWPR_VRSS]������(+���, -�϶�)
CString strNMSC_FCTN_STPL_PRC = realCommRecvData.GetItem(0, 32);		//�ٿ��� ���� ������
CString strFMSC_FCTN_STPL_PRC = realCommRecvData.GetItem(0, 33);		//������ ���� ������
CString strSPEAD_PRC = realCommRecvData.GetItem(0, 34);		//��������
CString strOTST_STPL_QTY = realCommRecvData.GetItem(0, 35);		//�̰��� ���� ����
CString strOTST_STPL_QTY_ICDC = realCommRecvData.GetItem(0, 36);		//�̰��� ���� ���� ����
CString strOTST_STPL_QTY_ICDC_CLR = realCommRecvData.GetItem(0, 37);		//[OTST_STPL_QTY_ICDC]������(+���, -�϶�)
CString strOTST_STPL_QTY_REF_IC = realCommRecvData.GetItem(0, 38);		//�̰��� ���� ���� ���� ����
CString strOTST_STPL_QTY_REF_IC_CLR = realCommRecvData.GetItem(0, 39);		//[OTST_STPL_QTY_REF_IC]������(+���, -�϶�)
CString strTHPR = realCommRecvData.GetItem(0, 40);		//�̷а�
CString strTHPR_CLR = realCommRecvData.GetItem(0, 41);		//[THPR]������(+���, -�϶�)
CString strMRKT_BASIS = realCommRecvData.GetItem(0, 42);		//���� BASIS
CString strMRKT_BASIS_CLR = realCommRecvData.GetItem(0, 43);		//[MRKT_BASIS]������(+���, -�϶�)
CString strTHER_BASIS = realCommRecvData.GetItem(0, 44);		//�̷� BASIS
CString strTHER_BASIS_CLR = realCommRecvData.GetItem(0, 45);		//[THER_BASIS]������(+���, -�϶�)
CString strESDG = realCommRecvData.GetItem(0, 46);		//������
CString strESDG_CLR = realCommRecvData.GetItem(0, 47);		//[ESDG]������(+���, -�϶�)
CString strDPRT = realCommRecvData.GetItem(0, 48);		//������
CString strDPRT_CLR = realCommRecvData.GetItem(0, 49);		//[DPRT]������(+���, -�϶�)
CString strSHNU_RATE = realCommRecvData.GetItem(0, 50);		//�ż�����
CString strSHNU_RATE_CLR = realCommRecvData.GetItem(0, 51);		//[SHNU_RATE]������(+���, -�϶�)
CString strCTTR = realCommRecvData.GetItem(0, 52);		//ü�ᰭ��
CString strCTTR_CLR = realCommRecvData.GetItem(0, 53);		//[CTTR]������(+���, -�϶�)
CString strASKP1 = realCommRecvData.GetItem(0, 54);		//�ŵ�ȣ��1
CString strASKP1_CLR = realCommRecvData.GetItem(0, 55);		//[ASKP1]������(+���, -�϶�)
CString strBIDP1 = realCommRecvData.GetItem(0, 56);		//�ż�ȣ��1
CString strBIDP1_CLR = realCommRecvData.GetItem(0, 57);		//[BIDP1]������(+���, -�϶�)
CString strASKP_RSQN1 = realCommRecvData.GetItem(0, 58);		//�ŵ�ȣ�� �ܷ�
CString strBIDP_RSQN1 = realCommRecvData.GetItem(0, 59);		//�ż�ȣ�� �ܷ�
CString strSELN_CNTG_CSNU = realCommRecvData.GetItem(0, 60);		//�ŵ� ü�� �Ǽ�
CString strSHNU_CNTG_CSNU = realCommRecvData.GetItem(0, 61);		//�ż� ü�� �Ǽ�
CString strNTBY_CNTG_CSNU = realCommRecvData.GetItem(0, 62);		//���ż� ü�� �Ǽ�
CString strNTBY_CNTG_CSNU_CLR = realCommRecvData.GetItem(0, 63);		//[NTBY_CNTG_CSNU]������(+���, -�϶�)
CString strSELN_CNTG_SMTN = realCommRecvData.GetItem(0, 64);		//�ŵ� ü�� �հ�
CString strSHNU_CNTG_SMTN = realCommRecvData.GetItem(0, 65);		//�ż� ü�� �հ�
CString strTOTAL_ASKP_RSQN = realCommRecvData.GetItem(0, 66);		//�� �ŵ�ȣ�� �ܷ�
CString strTOTAL_BIDP_RSQN = realCommRecvData.GetItem(0, 67);		//�� �ż�ȣ�� �ܷ�
CString strPRDY_VRSS_VOL_RATE = realCommRecvData.GetItem(0, 68);		//���� ��� �ŷ��� ����
CString strPRDY_VRSS_VOL_RATE_CLR = realCommRecvData.GetItem(0, 69);		//[PRDY_VRSS_VOL_RATE]������(+���, -�϶�)
CString strUNAS_PRC = realCommRecvData.GetItem(0, 70);		//�����ڻ� ����
CString strUNAS_PRC_CLR = realCommRecvData.GetItem(0, 71);		//[UNAS_PRC]������(+���, -�϶�)
CString strUNAS_PRDY_VRSS_SIGN = realCommRecvData.GetItem(0, 72);		//�����ڻ� ���ϴ�񱸺�
CString strUNAS_PRDY_VRSS = realCommRecvData.GetItem(0, 73);		//�����ڻ� ���� ���
CString strUNAS_PRDY_VRSS_CLR = realCommRecvData.GetItem(0, 74);		//[UNAS_PRDY_VRSS]������(+���, -�϶�)
CString strUNAS_PRDY_CTRT = realCommRecvData.GetItem(0, 75);		//�����ڻ� ���� �����
CString strUNAS_PRDY_CTRT_CLR = realCommRecvData.GetItem(0, 76);		//[UNAS_PRDY_CTRT]������(+���, -�϶�)
CString strCNTG_PRGS = realCommRecvData.GetItem(0, 77);		//ü��ƽ����
