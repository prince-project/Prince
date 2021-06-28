BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1111U10, TR_NAME=���������峻�ֽ��ֹ��ŵ�, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1111U10_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=3, ITEM=FTS_CTNO, TYPE=string, SIZE=9, CAPTION=����������հ��´�ü��ȣ;
			 INDEX=4, ITEM=FTS_APNO, TYPE=string, SIZE=3, CAPTION=���������»�ǰ��ȣ;
			 INDEX=5, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=���º�й�ȣ;
			 INDEX=6, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=7, ITEM=BUY_DT, TYPE=string, SIZE=8, CAPTION=�ż�����;
			 INDEX=8, ITEM=SPTX_DCD, TYPE=string, SIZE=1, CAPTION=�и����������ڵ�;
			 INDEX=9, ITEM=LOAN_SN, TYPE=string, SIZE=11, CAPTION=�����Ϸù�ȣ;
			 INDEX=10, ITEM=CRDT_TR_DCD, TYPE=string, SIZE=2, CAPTION=�ſ�ŷ������ڵ�;
			 INDEX=11, ITEM=ALMN_RDMP_DCD, TYPE=string, SIZE=1, CAPTION=���׻�ȯ�����ڵ�;
			 INDEX=12, ITEM=SSS_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=���ŵ�ȣ�������ڵ�;
			 INDEX=13, ITEM=FTS_ORDR_DCD, TYPE=string, SIZE=2, CAPTION=��������ֹ������ڵ�;
			 INDEX=14, ITEM=NMPR_DCD, TYPE=string, SIZE=2, CAPTION=ȣ�������ڵ�;
			 INDEX=15, ITEM=ORDR_CND_DCD, TYPE=string, SIZE=2, CAPTION=�ֹ����Ǳ����ڵ�;
			 INDEX=16, ITEM=RSVN_ORDR_DCD, TYPE=string, SIZE=1, CAPTION=�����ֹ������ڵ�;
			 INDEX=17, ITEM=CVRG_PRCS_DCD, TYPE=string, SIZE=2, CAPTION=�ݴ�Ÿ�ó�������ڵ�;
			 INDEX=18, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=19, ITEM=ORDR_UNPR, TYPE=string, SIZE=19, CAPTION=�ֹ��ܰ�;
			 INDEX=20, ITEM=EMR_ORDR_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=����ֹ���ü�����ڵ�;
			 INDEX=21, ITEM=RSV_ORDR_SN, TYPE=string, SIZE=11, CAPTION=�����ֹ��Ϸù�ȣ;
			 INDEX=22, ITEM=FIX_ODNO, TYPE=string, SIZE=40, CAPTION=FIX�ֹ���ȣ;
			 INDEX=23, ITEM=WRAP_ORDR_KND_DCD, TYPE=string, SIZE=2, CAPTION=WRAP�ֹ����������ڵ�;
			 INDEX=24, ITEM=RCMD_ORTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=��õ����ǰ�ڵ�;
			 INDEX=25, ITEM=GRUP_ODNO, TYPE=string, SIZE=13, CAPTION=�׷��ֹ���ȣ;
			 INDEX=26, ITEM=BSK_ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ٽ����ֹ��Ϸù�ȣ;
			 INDEX=27, ITEM=ORDR_ANGT_ORDR_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ��븮���ֹ������ڵ�;
			 INDEX=28, ITEM=MTS_KEY, TYPE=string, SIZE=7, CAPTION=MTSŰ;
			 INDEX=29, ITEM=HTS_ORDR_PSBL_MDIA_YN, TYPE=string, SIZE=1, CAPTION=HTS�ֹ����ɸ�ü����;
			 INDEX=30, ITEM=NMPR_PROP_XCP_YN, TYPE=string, SIZE=1, CAPTION=ȣ�����������ܿ���;
			 INDEX=31, ITEM=BNDL_SELL_ORDR_YN, TYPE=string, SIZE=1, CAPTION=�ϰ��ŵ��ֹ�����;
			 INDEX=32, ITEM=AGCP_OPPS_SELL_DCD, TYPE=string, SIZE=1, CAPTION=�����ݴ�ŵ������ڵ�;
			 INDEX=33, ITEM=PGM_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=���α׷�ȣ�������ڵ�;
			 INDEX=34, ITEM=PRTR_PANC_DCD, TYPE=string, SIZE=2, CAPTION=���α׷��ŸŰ��ñ����ڵ�;
			 INDEX=35, ITEM=HTRD_NEGO_NO, TYPE=string, SIZE=7, CAPTION=�뷮�Ÿ������ȣ;
			 INDEX=36, ITEM=HTRD_SRV_NO, TYPE=string, SIZE=7, CAPTION=�뷮�Ÿż�����ȣ;
			 INDEX=37, ITEM=HTRD_USR_NO, TYPE=string, SIZE=20, CAPTION=�뷮�ŸŻ���ڹ�ȣ;
			 INDEX=38, ITEM=BOND_ORDR_OR_UN_DCD, TYPE=string, SIZE=1, CAPTION=ä���ֹ������������ڵ�;
			 INDEX=39, ITEM=SMLN_YN, TYPE=string, SIZE=1, CAPTION=�ùķ��̼ǿ���;
			 INDEX=40, ITEM=LOAN_DT, TYPE=string, SIZE=8, CAPTION=��������;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1111U10_out, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ֹ��Ϸù�ȣ;
			 INDEX=1, ITEM=MSG_CD, TYPE=string, SIZE=6, CAPTION=�޽����ڵ�;
			 INDEX=2, ITEM=MSG_CTNS, TYPE=string, SIZE=500, CAPTION=�޽�������;
		END_OUTPUT0_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strORDR_DT;		//�ֹ�����
CString strCTNO;		//���հ��´�ü��ȣ
CString strAPNO;		//���»�ǰ��ȣ
CString strFTS_CTNO;		//����������հ��´�ü��ȣ
CString strFTS_APNO;		//���������»�ǰ��ȣ
CString strACNT_PWD;		//���º�й�ȣ
CString strPRDT_CD;		//��ǰ�ڵ�
CString strBUY_DT;		//�ż�����
CString strSPTX_DCD;		//�и����������ڵ�
CString strLOAN_SN;		//�����Ϸù�ȣ
CString strCRDT_TR_DCD;		//�ſ�ŷ������ڵ�
CString strALMN_RDMP_DCD;		//���׻�ȯ�����ڵ�
CString strSSS_NMPR_DCD;		//���ŵ�ȣ�������ڵ�
CString strFTS_ORDR_DCD;		//��������ֹ������ڵ�
CString strNMPR_DCD;		//ȣ�������ڵ�
CString strORDR_CND_DCD;		//�ֹ����Ǳ����ڵ�
CString strRSVN_ORDR_DCD;		//�����ֹ������ڵ�
CString strCVRG_PRCS_DCD;		//�ݴ�Ÿ�ó�������ڵ�
CString strORDR_QNT;		//�ֹ�����
CString strORDR_UNPR;		//�ֹ��ܰ�
CString strEMR_ORDR_MDIA_DCD;		//����ֹ���ü�����ڵ�
CString strRSV_ORDR_SN;		//�����ֹ��Ϸù�ȣ
CString strFIX_ODNO;		//FIX�ֹ���ȣ
CString strWRAP_ORDR_KND_DCD;		//WRAP�ֹ����������ڵ�
CString strRCMD_ORTN_PRDT_CD;		//��õ����ǰ�ڵ�
CString strGRUP_ODNO;		//�׷��ֹ���ȣ
CString strBSK_ORDR_SN;		//�ٽ����ֹ��Ϸù�ȣ
CString strORDR_ANGT_ORDR_DCD;		//�ֹ��븮���ֹ������ڵ�
CString strMTS_KEY;		//MTSŰ
CString strHTS_ORDR_PSBL_MDIA_YN;		//HTS�ֹ����ɸ�ü����
CString strNMPR_PROP_XCP_YN;		//ȣ�����������ܿ���
CString strBNDL_SELL_ORDR_YN;		//�ϰ��ŵ��ֹ�����
CString strAGCP_OPPS_SELL_DCD;		//�����ݴ�ŵ������ڵ�
CString strPGM_NMPR_DCD;		//���α׷�ȣ�������ڵ�
CString strPRTR_PANC_DCD;		//���α׷��ŸŰ��ñ����ڵ�
CString strHTRD_NEGO_NO;		//�뷮�Ÿ������ȣ
CString strHTRD_SRV_NO;		//�뷮�Ÿż�����ȣ
CString strHTRD_USR_NO;		//�뷮�ŸŻ���ڹ�ȣ
CString strBOND_ORDR_OR_UN_DCD;		//ä���ֹ������������ڵ�
CString strSMLN_YN;		//�ùķ��̼ǿ���
CString strLOAN_DT;		//��������

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ORDR_DT", strORDR_DT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "FTS_CTNO", strFTS_CTNO);		//����������հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "FTS_APNO", strFTS_APNO);		//���������»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "BUY_DT", strBUY_DT);		//�ż�����
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "SPTX_DCD", strSPTX_DCD);		//�и����������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "LOAN_SN", strLOAN_SN);		//�����Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "CRDT_TR_DCD", strCRDT_TR_DCD);		//�ſ�ŷ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ALMN_RDMP_DCD", strALMN_RDMP_DCD);		//���׻�ȯ�����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "SSS_NMPR_DCD", strSSS_NMPR_DCD);		//���ŵ�ȣ�������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "FTS_ORDR_DCD", strFTS_ORDR_DCD);		//��������ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "NMPR_DCD", strNMPR_DCD);		//ȣ�������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ORDR_CND_DCD", strORDR_CND_DCD);		//�ֹ����Ǳ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "RSVN_ORDR_DCD", strRSVN_ORDR_DCD);		//�����ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "CVRG_PRCS_DCD", strCVRG_PRCS_DCD);		//�ݴ�Ÿ�ó�������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ORDR_UNPR", strORDR_UNPR);		//�ֹ��ܰ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//����ֹ���ü�����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "RSV_ORDR_SN", strRSV_ORDR_SN);		//�����ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "FIX_ODNO", strFIX_ODNO);		//FIX�ֹ���ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "WRAP_ORDR_KND_DCD", strWRAP_ORDR_KND_DCD);		//WRAP�ֹ����������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "RCMD_ORTN_PRDT_CD", strRCMD_ORTN_PRDT_CD);		//��õ����ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "GRUP_ODNO", strGRUP_ODNO);		//�׷��ֹ���ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "BSK_ORDR_SN", strBSK_ORDR_SN);		//�ٽ����ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//�ֹ��븮���ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "MTS_KEY", strMTS_KEY);		//MTSŰ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "HTS_ORDR_PSBL_MDIA_YN", strHTS_ORDR_PSBL_MDIA_YN);		//HTS�ֹ����ɸ�ü����
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "NMPR_PROP_XCP_YN", strNMPR_PROP_XCP_YN);		//ȣ�����������ܿ���
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "BNDL_SELL_ORDR_YN", strBNDL_SELL_ORDR_YN);		//�ϰ��ŵ��ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "AGCP_OPPS_SELL_DCD", strAGCP_OPPS_SELL_DCD);		//�����ݴ�ŵ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "PGM_NMPR_DCD", strPGM_NMPR_DCD);		//���α׷�ȣ�������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "PRTR_PANC_DCD", strPRTR_PANC_DCD);		//���α׷��ŸŰ��ñ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "HTRD_NEGO_NO", strHTRD_NEGO_NO);		//�뷮�Ÿ������ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "HTRD_SRV_NO", strHTRD_SRV_NO);		//�뷮�Ÿż�����ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "HTRD_USR_NO", strHTRD_USR_NO);		//�뷮�ŸŻ���ڹ�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "BOND_ORDR_OR_UN_DCD", strBOND_ORDR_OR_UN_DCD);		//ä���ֹ������������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "SMLN_YN", strSMLN_YN);		//�ùķ��̼ǿ���
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U10", "OTS1111U10_in", "LOAN_DT", strLOAN_DT);		//��������




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS1111U10", "OTS1111U10_out", "ORDR_SN", 0);		//�ֹ��Ϸù�ȣ
CString strMSG_CD = m_CommAgent.GetTranOutputData("OTS1111U10", "OTS1111U10_out", "MSG_CD", 0);		//�޽����ڵ�
CString strMSG_CTNS = m_CommAgent.GetTranOutputData("OTS1111U10", "OTS1111U10_out", "MSG_CTNS", 0);		//�޽�������
