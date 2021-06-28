BEGIN_TRAN_LAYOUT

	TR_CODE=OTS1111U20, TR_NAME=���������峻�ֽ��ֹ��ż�, SERVER=A, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1111U20_in, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=ORDR_DT, TYPE=string, SIZE=8, CAPTION=�ֹ�����;
			 INDEX=1, ITEM=CTNO, TYPE=string, SIZE=9, CAPTION=���հ��´�ü��ȣ;
			 INDEX=2, ITEM=APNO, TYPE=string, SIZE=3, CAPTION=���»�ǰ��ȣ;
			 INDEX=3, ITEM=FTS_CTNO, TYPE=string, SIZE=9, CAPTION=����������հ��´�ü��ȣ;
			 INDEX=4, ITEM=FTS_APNO, TYPE=string, SIZE=3, CAPTION=���������»�ǰ��ȣ;
			 INDEX=5, ITEM=ACNT_PWD, TYPE=string, SIZE=64, CAPTION=���º�й�ȣ;
			 INDEX=6, ITEM=PRDT_CD, TYPE=string, SIZE=32, CAPTION=��ǰ�ڵ�;
			 INDEX=7, ITEM=LOAN_SN, TYPE=string, SIZE=11, CAPTION=�����Ϸù�ȣ;
			 INDEX=8, ITEM=CRDT_TR_DCD, TYPE=string, SIZE=2, CAPTION=�ſ�ŷ������ڵ�;
			 INDEX=9, ITEM=ALMN_RDMP_DCD, TYPE=string, SIZE=1, CAPTION=���׻�ȯ�����ڵ�;
			 INDEX=10, ITEM=SSS_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=���ŵ�ȣ�������ڵ�;
			 INDEX=11, ITEM=FTS_ORDR_DCD, TYPE=string, SIZE=2, CAPTION=��������ֹ������ڵ�;
			 INDEX=12, ITEM=NMPR_DCD, TYPE=string, SIZE=2, CAPTION=ȣ�������ڵ�;
			 INDEX=13, ITEM=ORDR_CND_DCD, TYPE=string, SIZE=2, CAPTION=�ֹ����Ǳ����ڵ�;
			 INDEX=14, ITEM=RSVN_ORDR_DCD, TYPE=string, SIZE=1, CAPTION=�����ֹ������ڵ�;
			 INDEX=15, ITEM=CVRG_PRCS_DCD, TYPE=string, SIZE=2, CAPTION=�ݴ�Ÿ�ó�������ڵ�;
			 INDEX=16, ITEM=ORDR_QNT, TYPE=string, SIZE=19, CAPTION=�ֹ�����;
			 INDEX=17, ITEM=ORDR_UNPR, TYPE=string, SIZE=19, CAPTION=�ֹ��ܰ�;
			 INDEX=18, ITEM=EMR_ORDR_MDIA_DCD, TYPE=string, SIZE=3, CAPTION=����ֹ���ü�����ڵ�;
			 INDEX=19, ITEM=RSV_ORDR_SN, TYPE=string, SIZE=11, CAPTION=�����ֹ��Ϸù�ȣ;
			 INDEX=20, ITEM=FIX_ODNO, TYPE=string, SIZE=40, CAPTION=FIX�ֹ���ȣ;
			 INDEX=21, ITEM=WRAP_ORDR_KND_DCD, TYPE=string, SIZE=2, CAPTION=WRAP�ֹ����������ڵ�;
			 INDEX=22, ITEM=RCMD_ORTN_PRDT_CD, TYPE=string, SIZE=32, CAPTION=��õ����ǰ�ڵ�;
			 INDEX=23, ITEM=GRUP_ODNO, TYPE=string, SIZE=13, CAPTION=�׷��ֹ���ȣ;
			 INDEX=24, ITEM=BSK_ORDR_SN, TYPE=string, SIZE=11, CAPTION=�ٽ����ֹ��Ϸù�ȣ;
			 INDEX=25, ITEM=ORDR_ANGT_ORDR_DCD, TYPE=string, SIZE=1, CAPTION=�ֹ��븮���ֹ������ڵ�;
			 INDEX=26, ITEM=MTS_KEY, TYPE=string, SIZE=7, CAPTION=MTSŰ;
			 INDEX=27, ITEM=HTS_ORDR_PSBL_MDIA_YN, TYPE=string, SIZE=1, CAPTION=HTS�ֹ����ɸ�ü����;
			 INDEX=28, ITEM=NMPR_PROP_XCP_YN, TYPE=string, SIZE=1, CAPTION=ȣ�����������ܿ���;
			 INDEX=29, ITEM=PGM_NMPR_DCD, TYPE=string, SIZE=2, CAPTION=���α׷�ȣ�������ڵ�;
			 INDEX=30, ITEM=PRTR_PANC_DCD, TYPE=string, SIZE=2, CAPTION=���α׷��ŸŰ��ñ����ڵ�;
			 INDEX=31, ITEM=HTRD_NEGO_NO, TYPE=string, SIZE=7, CAPTION=�뷮�Ÿ������ȣ;
			 INDEX=32, ITEM=HTRD_SRV_NO, TYPE=string, SIZE=7, CAPTION=�뷮�Ÿż�����ȣ;
			 INDEX=33, ITEM=HTRD_USR_NO, TYPE=string, SIZE=20, CAPTION=�뷮�ŸŻ���ڹ�ȣ;
			 INDEX=34, ITEM=BOND_ORDR_OR_UN_DCD, TYPE=string, SIZE=1, CAPTION=ä���ֹ������������ڵ�;
			 INDEX=35, ITEM=SMLN_YN, TYPE=string, SIZE=1, CAPTION=�ùķ��̼ǿ���;
			 INDEX=36, ITEM=LOAN_DT, TYPE=string, SIZE=8, CAPTION=��������;
		END_INPUT0_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OTS1111U20_out, INOUT=1, ARRAY=0, ARRINFO=;
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
CString strPGM_NMPR_DCD;		//���α׷�ȣ�������ڵ�
CString strPRTR_PANC_DCD;		//���α׷��ŸŰ��ñ����ڵ�
CString strHTRD_NEGO_NO;		//�뷮�Ÿ������ȣ
CString strHTRD_SRV_NO;		//�뷮�Ÿż�����ȣ
CString strHTRD_USR_NO;		//�뷮�ŸŻ���ڹ�ȣ
CString strBOND_ORDR_OR_UN_DCD;		//ä���ֹ������������ڵ�
CString strSMLN_YN;		//�ùķ��̼ǿ���
CString strLOAN_DT;		//��������

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "ORDR_DT", strORDR_DT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "CTNO", strCTNO);		//���հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "APNO", strAPNO);		//���»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "FTS_CTNO", strFTS_CTNO);		//����������հ��´�ü��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "FTS_APNO", strFTS_APNO);		//���������»�ǰ��ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "ACNT_PWD", strACNT_PWD);		//���º�й�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "PRDT_CD", strPRDT_CD);		//��ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "LOAN_SN", strLOAN_SN);		//�����Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "CRDT_TR_DCD", strCRDT_TR_DCD);		//�ſ�ŷ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "ALMN_RDMP_DCD", strALMN_RDMP_DCD);		//���׻�ȯ�����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "SSS_NMPR_DCD", strSSS_NMPR_DCD);		//���ŵ�ȣ�������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "FTS_ORDR_DCD", strFTS_ORDR_DCD);		//��������ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "NMPR_DCD", strNMPR_DCD);		//ȣ�������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "ORDR_CND_DCD", strORDR_CND_DCD);		//�ֹ����Ǳ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "RSVN_ORDR_DCD", strRSVN_ORDR_DCD);		//�����ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "CVRG_PRCS_DCD", strCVRG_PRCS_DCD);		//�ݴ�Ÿ�ó�������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "ORDR_QNT", strORDR_QNT);		//�ֹ�����
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "ORDR_UNPR", strORDR_UNPR);		//�ֹ��ܰ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "EMR_ORDR_MDIA_DCD", strEMR_ORDR_MDIA_DCD);		//����ֹ���ü�����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "RSV_ORDR_SN", strRSV_ORDR_SN);		//�����ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "FIX_ODNO", strFIX_ODNO);		//FIX�ֹ���ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "WRAP_ORDR_KND_DCD", strWRAP_ORDR_KND_DCD);		//WRAP�ֹ����������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "RCMD_ORTN_PRDT_CD", strRCMD_ORTN_PRDT_CD);		//��õ����ǰ�ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "GRUP_ODNO", strGRUP_ODNO);		//�׷��ֹ���ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "BSK_ORDR_SN", strBSK_ORDR_SN);		//�ٽ����ֹ��Ϸù�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "ORDR_ANGT_ORDR_DCD", strORDR_ANGT_ORDR_DCD);		//�ֹ��븮���ֹ������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "MTS_KEY", strMTS_KEY);		//MTSŰ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "HTS_ORDR_PSBL_MDIA_YN", strHTS_ORDR_PSBL_MDIA_YN);		//HTS�ֹ����ɸ�ü����
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "NMPR_PROP_XCP_YN", strNMPR_PROP_XCP_YN);		//ȣ�����������ܿ���
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "PGM_NMPR_DCD", strPGM_NMPR_DCD);		//���α׷�ȣ�������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "PRTR_PANC_DCD", strPRTR_PANC_DCD);		//���α׷��ŸŰ��ñ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "HTRD_NEGO_NO", strHTRD_NEGO_NO);		//�뷮�Ÿ������ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "HTRD_SRV_NO", strHTRD_SRV_NO);		//�뷮�Ÿż�����ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "HTRD_USR_NO", strHTRD_USR_NO);		//�뷮�ŸŻ���ڹ�ȣ
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "BOND_ORDR_OR_UN_DCD", strBOND_ORDR_OR_UN_DCD);		//ä���ֹ������������ڵ�
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "SMLN_YN", strSMLN_YN);		//�ùķ��̼ǿ���
m_CommAgent.SetTranInputData(nRequestId, "OTS1111U20", "OTS1111U20_in", "LOAN_DT", strLOAN_DT);		//��������




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
CString strORDR_SN = m_CommAgent.GetTranOutputData("OTS1111U20", "OTS1111U20_out", "ORDR_SN", 0);		//�ֹ��Ϸù�ȣ
CString strMSG_CD = m_CommAgent.GetTranOutputData("OTS1111U20", "OTS1111U20_out", "MSG_CD", 0);		//�޽����ڵ�
CString strMSG_CTNS = m_CommAgent.GetTranOutputData("OTS1111U20", "OTS1111U20_out", "MSG_CTNS", 0);		//�޽�������
