BEGIN_TRAN_LAYOUT

	TR_CODE=OTS2100U20, TR_NAME=�����ɼ����ոż��ֹ�, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2100U20_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=1, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=2, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=���º�й�ȣ;
			 INDEX=3, ITEM=SELL_BUY_DCD, TYPE=string, SIZE=1, CAPTION=�ŵ��ż������ڵ�;
			 INDEX=4, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=5, ITEM=DRVS_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=�Ļ���ǰȣ�������ڵ�;
			 INDEX=6, ITEM=ORDR_PRC, TYPE=string, SIZE=20, CAPTION=�ֹ�����;
			 INDEX=7, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=8, ITEM=EMR_ORDR_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=����ֹ���ü�����ڵ�;
			 INDEX=9, ITEM=DFRT_HDGE_DCD, TYPE=string, SIZE=2, CAPTION=�������������ڵ�;
			 INDEX=10, ITEM=GRUP_ORDR_YN, TYPE=string, SIZE=1, CAPTION=�׷��ֹ�����;
			 INDEX=11, ITEM=ORDR_GRUP_NM, TYPE=string, SIZE=100, CAPTION=�ֹ��׷��;
			 INDEX=12, ITEM=BNDL_ORDR_GRUP_NO, TYPE=string, SIZE=7, CAPTION=�ϰ��ֹ��׷��ȣ;
			 INDEX=13, ITEM=DRVS_WRAP_ORDR_DCD, TYPE=string, SIZE=2, CAPTION=�Ļ���ǰWRAP�ֹ������ڵ�;
			 INDEX=14, ITEM=RCMD_ORTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=��õ����ǰ�ڵ�;
			 INDEX=15, ITEM=BSK_TRDE_ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ٽ��ϸŸ��ֹ��Ϸù�ȣ;
			 INDEX=16, ITEM=DRVS_ORDR_CND_DCD, TYPE=string, SIZE=1, CAPTION=�Ļ���ǰ�ֹ����Ǳ����ڵ�;
			 INDEX=17, ITEM=PWD_CNFM_YN, TYPE=string, SIZE=1, CAPTION=��й�ȣȮ�ο���;
			 INDEX=18, ITEM=CVRG_YN, TYPE=string, SIZE=1, CAPTION=�ݴ�Ÿſ���;
			 INDEX=19, ITEM=MDIA_ORDR_SN, TYPE=string, SIZE=11, CAPTION=��ü�ֹ��Ϸù�ȣ;
			 INDEX=20, ITEM=ADIT_WMY_BNDL_ORDR_YN, TYPE=string, SIZE=1, CAPTION=�߰����ű��ϰ��ֹ�����;
			 INDEX=21, ITEM=WRN_ORDR_CNFM_YN, TYPE=string, SIZE=1, CAPTION=����ֹ�Ȯ�ο���;
			 INDEX=22, ITEM=ETC_ORDR_DCD, TYPE=string, SIZE=3, CAPTION=��Ÿ�ֹ������ڵ�;
			 INDEX=23, ITEM=ORDR_ANGT_ORDR_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ��븮���ֹ������ڵ�;
			 INDEX=24, ITEM=ORDR_RPRC_YN, TYPE=string, SIZE=1, CAPTION=�ֹ���ó������;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS2100U20_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strACNT_PWD;		//���º�й�ȣ
CString strSELL_BUY_DCD;		//�ŵ��ż������ڵ�
CString strPRDT_CD;		//��ǰ�ڵ�
CString strDRVS_NMPR_DCD;		//�Ļ���ǰȣ�������ڵ�
CString strORDR_PRC;		//�ֹ�����
CString strORDR_QNT;		//�ֹ�����
CString strEMR_ORDR_MDIA_DCD;		//����ֹ���ü�����ڵ�
CString strDFRT_HDGE_DCD;		//�������������ڵ�
CString strGRUP_ORDR_YN;		//�׷��ֹ�����
CString strORDR_GRUP_NM;		//�ֹ��׷��
CString strBNDL_ORDR_GRUP_NO;		//�ϰ��ֹ��׷��ȣ
CString strDRVS_WRAP_ORDR_DCD;		//�Ļ���ǰWRAP�ֹ������ڵ�
CString strRCMD_ORTN_PRDT_CD;		//��õ����ǰ�ڵ�
CString strBSK_TRDE_ORDR_SN;		//�ٽ��ϸŸ��ֹ��Ϸù�ȣ
CString strDRVS_ORDR_CND_DCD;		//�Ļ���ǰ�ֹ����Ǳ����ڵ�
CString strPWD_CNFM_YN;		//��й�ȣȮ�ο���
CString strCVRG_YN;		//�ݴ�Ÿſ���
CString strMDIA_ORDR_SN;		//��ü�ֹ��Ϸù�ȣ
CString strADIT_WMY_BNDL_ORDR_YN;		//�߰����ű��ϰ��ֹ�����
CString strWRN_ORDR_CNFM_YN;		//����ֹ�Ȯ�ο���
CString strETC_ORDR_DCD;		//��Ÿ�ֹ������ڵ�
CString strORDR_ANGT_ORDR_DCD;		//�ֹ��븮���ֹ������ڵ�
CString strORDR_RPRC_YN;		//�ֹ���ó������

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "SELL_BUY_DCD", strSELL_BUY_DCD);		//�ŵ��ż������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "DRVS_NMPR_DCD", strDRVS_NMPR_DCD);		//�Ļ���ǰȣ�������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ORDR_PRC", strORDR_PRC);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//����ֹ���ü�����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "DFRT_HDGE_DCD", strDFRT_HDGE_DCD);		//�������������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "GRUP_ORDR_YN", strGRUP_ORDR_YN);		//�׷��ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ORDR_GRUP_NM", strORDR_GRUP_NM);		//�ֹ��׷��
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "BNDL_ORDR_GRUP_NO", strBNDL_ORDR_GRUP_NO);		//�ϰ��ֹ��׷��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "DRVS_WRAP_ORDR_DCD", strDRVS_WRAP_ORDR_DCD);		//�Ļ���ǰWRAP�ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "RCMD_ORTN_PRDT_CD", strRCMD_ORTN_PRDT_CD);		//��õ����ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "BSK_TRDE_ORDR_SN", strBSK_TRDE_ORDR_SN);		//�ٽ��ϸŸ��ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "DRVS_ORDR_CND_DCD", strDRVS_ORDR_CND_DCD);		//�Ļ���ǰ�ֹ����Ǳ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "PWD_CNFM_YN", strPWD_CNFM_YN);		//��й�ȣȮ�ο���
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "CVRG_YN", strCVRG_YN);		//�ݴ�Ÿſ���
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "MDIA_ORDR_SN", strMDIA_ORDR_SN);		//��ü�ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ADIT_WMY_BNDL_ORDR_YN", strADIT_WMY_BNDL_ORDR_YN);		//�߰����ű��ϰ��ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "WRN_ORDR_CNFM_YN", strWRN_ORDR_CNFM_YN);		//����ֹ�Ȯ�ο���
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ETC_ORDR_DCD", strETC_ORDR_DCD);		//��Ÿ�ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//�ֹ��븮���ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS2100U20", "OTS2100U20_in", "ORDR_RPRC_YN", strORDR_RPRC_YN);		//�ֹ���ó������




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS2100U20", "OTS2100U20_out", "ORDR_SN", 0);		//�ֹ��Ϸù�ȣ
