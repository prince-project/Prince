BEGIN_FUNCTION_MAP
	REAL_TYPE=214, REAL_NAME=EF1, DESCRIPTION=�ؿܼ���ü��Ȯ��;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=rltm_dpch_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=�ǽð��뺸�����ڵ�, FID=0;
			 INDEX=1, ITEM=usr_id, TYPE=string, SIZE=20, KEY=1, CAPTION=�����ID, FID=0;
			 INDEX=2, ITEM=rltm_dpch_prcs_dcd, TYPE=string, SIZE=2, KEY=0, CAPTION=�ǽð��뺸ó�������ڵ�, FID=0;
			 INDEX=3, ITEM=cano, TYPE=string, SIZE=8, KEY=0, CAPTION=���հ��¹�ȣ, FID=0;
			 INDEX=4, ITEM=ctno, TYPE=string, SIZE=9, KEY=0, CAPTION=���հ��´�ü��ȣ, FID=0;
			 INDEX=5, ITEM=apno, TYPE=string, SIZE=3, KEY=0, CAPTION=���»�ǰ��ȣ, FID=0;
			 INDEX=6, ITEM=prdt_cd, TYPE=string, SIZE=32, KEY=0, CAPTION=��ǰ�ڵ�, FID=0;
			 INDEX=7, ITEM=odrv_ordr_tp_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=�ؿ��Ļ��ֹ����������ڵ�, FID=0;
			 INDEX=8, ITEM=ordr_stts_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=�ֹ����±����ڵ�, FID=0;
			 INDEX=9, ITEM=odrv_odno, TYPE=string, SIZE=16, KEY=0, CAPTION=�ؿ��Ļ��ֹ���ȣ, FID=0;
			 INDEX=10, ITEM=odrv_or_odno, TYPE=string, SIZE=16, KEY=0, CAPTION=�ؿ��Ļ����ֹ���ȣ, FID=0;
			 INDEX=11, ITEM=ordr_dt, TYPE=string, SIZE=8, KEY=0, CAPTION=�ֹ�����, FID=0;
			 INDEX=12, ITEM=cust_nm, TYPE=string, SIZE=50, KEY=0, CAPTION=����, FID=0;
			 INDEX=13, ITEM=odrv_sell_buy_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=�ؿ��Ļ��ŵ��ż������ڵ�, FID=0;
			 INDEX=14, ITEM=odrv_ordr_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=�ؿ��Ļ��ֹ����ݳ���, FID=0;
			 INDEX=15, ITEM=ordr_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=�ֹ���������, FID=0;
			 INDEX=16, ITEM=odrv_prc_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=�ؿ��Ļ����ݱ����ڵ�, FID=0;
			 INDEX=17, ITEM=cncs_cnd_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=ü�����Ǳ����ڵ�, FID=0;
			 INDEX=18, ITEM=cnd_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=���ǰ��ݳ���, FID=0;
			 INDEX=19, ITEM=comm_mdia_dcd, TYPE=string, SIZE=3, KEY=0, CAPTION=��Ÿ�ü�����ڵ�, FID=0;
			 INDEX=20, ITEM=acpt_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=�����ð�, FID=0;
			 INDEX=21, ITEM=excg_cncs_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=�ŷ���ü��ð�, FID=0;
			 INDEX=22, ITEM=acpl_acpt_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=���������ð�, FID=0;
			 INDEX=23, ITEM=cncs_tm, TYPE=string, SIZE=6, KEY=0, CAPTION=ü��ð�, FID=0;
			 INDEX=24, ITEM=cncs_dt, TYPE=string, SIZE=8, KEY=0, CAPTION=ü������, FID=0;
			 INDEX=25, ITEM=odrv_cncs_no, TYPE=string, SIZE=8, KEY=0, CAPTION=�ؿ��Ļ�ü���ȣ, FID=0;
			 INDEX=26, ITEM=cncs_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=ü���������, FID=0;
			 INDEX=27, ITEM=odrv_cncs_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=�ؿ��Ļ�ü�ᰡ�ݳ���, FID=0;
			 INDEX=28, ITEM=odrv_cncs_amt_ctns, TYPE=string, SIZE=30, KEY=0, CAPTION=�ؿ��Ļ�ü��ݾ׳���, FID=0;
			 INDEX=29, ITEM=crry_cd, TYPE=string, SIZE=3, KEY=0, CAPTION=��ȭ�ڵ�, FID=0;
			 INDEX=30, ITEM=ordr_rmn_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=�ֹ��ܿ���������, FID=0;
			 INDEX=31, ITEM=acnt_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=���±����ڵ�, FID=0;
			 INDEX=32, ITEM=entr_clr_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=����û�걸���ڵ�, FID=0;
			 INDEX=33, ITEM=clr_pst_no, TYPE=string, SIZE=16, KEY=0, CAPTION=û�������ǹ�ȣ, FID=0;
			 INDEX=34, ITEM=pst_no, TYPE=string, SIZE=16, KEY=0, CAPTION=�����ǹ�ȣ, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 ���� ���Ǹ� ���� GetRealOutputData �޼ҵ� MFC �ҽ� ���ø�
 **********************************************/
CString strrltm_dpch_dcd = m_CommAgent.GetRealOutputData("EF1", "rltm_dpch_dcd");		//�ǽð��뺸�����ڵ�
CString strusr_id = m_CommAgent.GetRealOutputData("EF1", "usr_id");		//�����ID
CString strrltm_dpch_prcs_dcd = m_CommAgent.GetRealOutputData("EF1", "rltm_dpch_prcs_dcd");		//�ǽð��뺸ó�������ڵ�
CString strcano = m_CommAgent.GetRealOutputData("EF1", "cano");		//���հ��¹�ȣ
CString strctno = m_CommAgent.GetRealOutputData("EF1", "ctno");		//���հ��´�ü��ȣ
CString strapno = m_CommAgent.GetRealOutputData("EF1", "apno");		//���»�ǰ��ȣ
CString strprdt_cd = m_CommAgent.GetRealOutputData("EF1", "prdt_cd");		//��ǰ�ڵ�
CString strodrv_ordr_tp_dcd = m_CommAgent.GetRealOutputData("EF1", "odrv_ordr_tp_dcd");		//�ؿ��Ļ��ֹ����������ڵ�
CString strordr_stts_dcd = m_CommAgent.GetRealOutputData("EF1", "ordr_stts_dcd");		//�ֹ����±����ڵ�
CString strodrv_odno = m_CommAgent.GetRealOutputData("EF1", "odrv_odno");		//�ؿ��Ļ��ֹ���ȣ
CString strodrv_or_odno = m_CommAgent.GetRealOutputData("EF1", "odrv_or_odno");		//�ؿ��Ļ����ֹ���ȣ
CString strordr_dt = m_CommAgent.GetRealOutputData("EF1", "ordr_dt");		//�ֹ�����
CString strcust_nm = m_CommAgent.GetRealOutputData("EF1", "cust_nm");		//����
CString strodrv_sell_buy_dcd = m_CommAgent.GetRealOutputData("EF1", "odrv_sell_buy_dcd");		//�ؿ��Ļ��ŵ��ż������ڵ�
CString strodrv_ordr_prc_ctns = m_CommAgent.GetRealOutputData("EF1", "odrv_ordr_prc_ctns");		//�ؿ��Ļ��ֹ����ݳ���
CString strordr_qnt_ctns = m_CommAgent.GetRealOutputData("EF1", "ordr_qnt_ctns");		//�ֹ���������
CString strodrv_prc_dcd = m_CommAgent.GetRealOutputData("EF1", "odrv_prc_dcd");		//�ؿ��Ļ����ݱ����ڵ�
CString strcncs_cnd_dcd = m_CommAgent.GetRealOutputData("EF1", "cncs_cnd_dcd");		//ü�����Ǳ����ڵ�
CString strcnd_prc_ctns = m_CommAgent.GetRealOutputData("EF1", "cnd_prc_ctns");		//���ǰ��ݳ���
CString strcomm_mdia_dcd = m_CommAgent.GetRealOutputData("EF1", "comm_mdia_dcd");		//��Ÿ�ü�����ڵ�
CString stracpt_tm = m_CommAgent.GetRealOutputData("EF1", "acpt_tm");		//�����ð�
CString strexcg_cncs_tm = m_CommAgent.GetRealOutputData("EF1", "excg_cncs_tm");		//�ŷ���ü��ð�
CString stracpl_acpt_tm = m_CommAgent.GetRealOutputData("EF1", "acpl_acpt_tm");		//���������ð�
CString strcncs_tm = m_CommAgent.GetRealOutputData("EF1", "cncs_tm");		//ü��ð�
CString strcncs_dt = m_CommAgent.GetRealOutputData("EF1", "cncs_dt");		//ü������
CString strodrv_cncs_no = m_CommAgent.GetRealOutputData("EF1", "odrv_cncs_no");		//�ؿ��Ļ�ü���ȣ
CString strcncs_qnt_ctns = m_CommAgent.GetRealOutputData("EF1", "cncs_qnt_ctns");		//ü���������
CString strodrv_cncs_prc_ctns = m_CommAgent.GetRealOutputData("EF1", "odrv_cncs_prc_ctns");		//�ؿ��Ļ�ü�ᰡ�ݳ���
CString strodrv_cncs_amt_ctns = m_CommAgent.GetRealOutputData("EF1", "odrv_cncs_amt_ctns");		//�ؿ��Ļ�ü��ݾ׳���
CString strcrry_cd = m_CommAgent.GetRealOutputData("EF1", "crry_cd");		//��ȭ�ڵ�
CString strordr_rmn_qnt_ctns = m_CommAgent.GetRealOutputData("EF1", "ordr_rmn_qnt_ctns");		//�ֹ��ܿ���������
CString stracnt_dcd = m_CommAgent.GetRealOutputData("EF1", "acnt_dcd");		//���±����ڵ�
CString strentr_clr_dcd = m_CommAgent.GetRealOutputData("EF1", "entr_clr_dcd");		//����û�걸���ڵ�
CString strclr_pst_no = m_CommAgent.GetRealOutputData("EF1", "clr_pst_no");		//û�������ǹ�ȣ
CString strpst_no = m_CommAgent.GetRealOutputData("EF1", "pst_no");		//�����ǹ�ȣ




/**********************************************
 ���� ���Ǹ� ���� �޸� �ε��� ���� �ҽ� ���ø�(C++������ ��� ����)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strrltm_dpch_dcd = realCommRecvData.GetItem(0, 0);		//�ǽð��뺸�����ڵ�
CString strusr_id = realCommRecvData.GetItem(0, 1);		//�����ID
CString strrltm_dpch_prcs_dcd = realCommRecvData.GetItem(0, 2);		//�ǽð��뺸ó�������ڵ�
CString strcano = realCommRecvData.GetItem(0, 3);		//���հ��¹�ȣ
CString strctno = realCommRecvData.GetItem(0, 4);		//���հ��´�ü��ȣ
CString strapno = realCommRecvData.GetItem(0, 5);		//���»�ǰ��ȣ
CString strprdt_cd = realCommRecvData.GetItem(0, 6);		//��ǰ�ڵ�
CString strodrv_ordr_tp_dcd = realCommRecvData.GetItem(0, 7);		//�ؿ��Ļ��ֹ����������ڵ�
CString strordr_stts_dcd = realCommRecvData.GetItem(0, 8);		//�ֹ����±����ڵ�
CString strodrv_odno = realCommRecvData.GetItem(0, 9);		//�ؿ��Ļ��ֹ���ȣ
CString strodrv_or_odno = realCommRecvData.GetItem(0, 10);		//�ؿ��Ļ����ֹ���ȣ
CString strordr_dt = realCommRecvData.GetItem(0, 11);		//�ֹ�����
CString strcust_nm = realCommRecvData.GetItem(0, 12);		//����
CString strodrv_sell_buy_dcd = realCommRecvData.GetItem(0, 13);		//�ؿ��Ļ��ŵ��ż������ڵ�
CString strodrv_ordr_prc_ctns = realCommRecvData.GetItem(0, 14);		//�ؿ��Ļ��ֹ����ݳ���
CString strordr_qnt_ctns = realCommRecvData.GetItem(0, 15);		//�ֹ���������
CString strodrv_prc_dcd = realCommRecvData.GetItem(0, 16);		//�ؿ��Ļ����ݱ����ڵ�
CString strcncs_cnd_dcd = realCommRecvData.GetItem(0, 17);		//ü�����Ǳ����ڵ�
CString strcnd_prc_ctns = realCommRecvData.GetItem(0, 18);		//���ǰ��ݳ���
CString strcomm_mdia_dcd = realCommRecvData.GetItem(0, 19);		//��Ÿ�ü�����ڵ�
CString stracpt_tm = realCommRecvData.GetItem(0, 20);		//�����ð�
CString strexcg_cncs_tm = realCommRecvData.GetItem(0, 21);		//�ŷ���ü��ð�
CString stracpl_acpt_tm = realCommRecvData.GetItem(0, 22);		//���������ð�
CString strcncs_tm = realCommRecvData.GetItem(0, 23);		//ü��ð�
CString strcncs_dt = realCommRecvData.GetItem(0, 24);		//ü������
CString strodrv_cncs_no = realCommRecvData.GetItem(0, 25);		//�ؿ��Ļ�ü���ȣ
CString strcncs_qnt_ctns = realCommRecvData.GetItem(0, 26);		//ü���������
CString strodrv_cncs_prc_ctns = realCommRecvData.GetItem(0, 27);		//�ؿ��Ļ�ü�ᰡ�ݳ���
CString strodrv_cncs_amt_ctns = realCommRecvData.GetItem(0, 28);		//�ؿ��Ļ�ü��ݾ׳���
CString strcrry_cd = realCommRecvData.GetItem(0, 29);		//��ȭ�ڵ�
CString strordr_rmn_qnt_ctns = realCommRecvData.GetItem(0, 30);		//�ֹ��ܿ���������
CString stracnt_dcd = realCommRecvData.GetItem(0, 31);		//���±����ڵ�
CString strentr_clr_dcd = realCommRecvData.GetItem(0, 32);		//����û�걸���ڵ�
CString strclr_pst_no = realCommRecvData.GetItem(0, 33);		//û�������ǹ�ȣ
CString strpst_no = realCommRecvData.GetItem(0, 34);		//�����ǹ�ȣ
