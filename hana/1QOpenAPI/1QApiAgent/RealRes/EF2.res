BEGIN_FUNCTION_MAP
	REAL_TYPE=215, REAL_NAME=EF2, DESCRIPTION=�ؿܼ����̰���;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=rltm_dpch_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=�ǽð��뺸�����ڵ�, FID=0;
			 INDEX=1, ITEM=usr_id, TYPE=string, SIZE=20, KEY=1, CAPTION=�����ID, FID=0;
			 INDEX=2, ITEM=rltm_dpch_prcs_dcd, TYPE=string, SIZE=2, KEY=0, CAPTION=�ǽð��뺸ó�������ڵ�, FID=0;
			 INDEX=3, ITEM=cano, TYPE=string, SIZE=8, KEY=0, CAPTION=���հ��¹�ȣ, FID=0;
			 INDEX=4, ITEM=ctno, TYPE=string, SIZE=9, KEY=0, CAPTION=���հ��´�ü��ȣ, FID=0;
			 INDEX=5, ITEM=apno, TYPE=string, SIZE=3, KEY=0, CAPTION=���»�ǰ��ȣ, FID=0;
			 INDEX=6, ITEM=cust_nm, TYPE=string, SIZE=50, KEY=0, CAPTION=����, FID=0;
			 INDEX=7, ITEM=prdt_cd, TYPE=string, SIZE=32, KEY=0, CAPTION=��ǰ�ڵ�, FID=0;
			 INDEX=8, ITEM=prdt_nm, TYPE=string, SIZE=50, KEY=0, CAPTION=��ǰ��, FID=0;
			 INDEX=9, ITEM=odrv_sell_buy_dcd, TYPE=string, SIZE=1, KEY=0, CAPTION=�ؿ��Ļ��ŵ��ż������ڵ�, FID=0;
			 INDEX=10, ITEM=ustl_ctrc_qnt_ctns, TYPE=string, SIZE=30, KEY=0, CAPTION=�̰���������������, FID=0;
			 INDEX=11, ITEM=avr_cncs_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=���ü�ᰡ�ݳ���, FID=0;
			 INDEX=12, ITEM=clr_psbl_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=û�갡�ɼ�������, FID=0;
			 INDEX=13, ITEM=ncnc_qnt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=��ü���������, FID=0;
			 INDEX=14, ITEM=odrv_pv_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=�ؿ��Ļ����簡����, FID=0;
			 INDEX=15, ITEM=bfdt_prpt_mark, TYPE=string, SIZE=1, KEY=0, CAPTION=���ϴ���ȣ, FID=0;
			 INDEX=16, ITEM=bfdt_prpt_prc_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=���ϴ�񰡰ݳ���, FID=0;
			 INDEX=17, ITEM=bfdt_prpt_prc_rto_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=���ϴ�񰡰ݺ�������, FID=0;
			 INDEX=18, ITEM=odrv_evl_amt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=�ؿ��Ļ��򰡱ݾ׳���, FID=0;
			 INDEX=19, ITEM=evl_pfls_amt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=�򰡼��ͱݾ׳���, FID=0;
			 INDEX=20, ITEM=pfls_rt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=����������, FID=0;
			 INDEX=21, ITEM=pchs_amt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=���Աݾ׳���, FID=0;
			 INDEX=22, ITEM=mlt_ctns, TYPE=string, SIZE=20, KEY=0, CAPTION=�¼�����, FID=0;
			 INDEX=23, ITEM=itm_dvsn, TYPE=string, SIZE=1, KEY=0, CAPTION=���񱸺�, FID=0;
			 INDEX=24, ITEM=crry_cd, TYPE=string, SIZE=3, KEY=0, CAPTION=��ȭ�ڵ�, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 ���� ���Ǹ� ���� GetRealOutputData �޼ҵ� MFC �ҽ� ���ø�
 **********************************************/
CString strrltm_dpch_dcd = m_CommAgent.GetRealOutputData("EF2", "rltm_dpch_dcd");		//�ǽð��뺸�����ڵ�
CString strusr_id = m_CommAgent.GetRealOutputData("EF2", "usr_id");		//�����ID
CString strrltm_dpch_prcs_dcd = m_CommAgent.GetRealOutputData("EF2", "rltm_dpch_prcs_dcd");		//�ǽð��뺸ó�������ڵ�
CString strcano = m_CommAgent.GetRealOutputData("EF2", "cano");		//���հ��¹�ȣ
CString strctno = m_CommAgent.GetRealOutputData("EF2", "ctno");		//���հ��´�ü��ȣ
CString strapno = m_CommAgent.GetRealOutputData("EF2", "apno");		//���»�ǰ��ȣ
CString strcust_nm = m_CommAgent.GetRealOutputData("EF2", "cust_nm");		//����
CString strprdt_cd = m_CommAgent.GetRealOutputData("EF2", "prdt_cd");		//��ǰ�ڵ�
CString strprdt_nm = m_CommAgent.GetRealOutputData("EF2", "prdt_nm");		//��ǰ��
CString strodrv_sell_buy_dcd = m_CommAgent.GetRealOutputData("EF2", "odrv_sell_buy_dcd");		//�ؿ��Ļ��ŵ��ż������ڵ�
CString strustl_ctrc_qnt_ctns = m_CommAgent.GetRealOutputData("EF2", "ustl_ctrc_qnt_ctns");		//�̰���������������
CString stravr_cncs_prc_ctns = m_CommAgent.GetRealOutputData("EF2", "avr_cncs_prc_ctns");		//���ü�ᰡ�ݳ���
CString strclr_psbl_qnt_ctns = m_CommAgent.GetRealOutputData("EF2", "clr_psbl_qnt_ctns");		//û�갡�ɼ�������
CString strncnc_qnt_ctns = m_CommAgent.GetRealOutputData("EF2", "ncnc_qnt_ctns");		//��ü���������
CString strodrv_pv_ctns = m_CommAgent.GetRealOutputData("EF2", "odrv_pv_ctns");		//�ؿ��Ļ����簡����
CString strbfdt_prpt_mark = m_CommAgent.GetRealOutputData("EF2", "bfdt_prpt_mark");		//���ϴ���ȣ
CString strbfdt_prpt_prc_ctns = m_CommAgent.GetRealOutputData("EF2", "bfdt_prpt_prc_ctns");		//���ϴ�񰡰ݳ���
CString strbfdt_prpt_prc_rto_ctns = m_CommAgent.GetRealOutputData("EF2", "bfdt_prpt_prc_rto_ctns");		//���ϴ�񰡰ݺ�������
CString strodrv_evl_amt_ctns = m_CommAgent.GetRealOutputData("EF2", "odrv_evl_amt_ctns");		//�ؿ��Ļ��򰡱ݾ׳���
CString strevl_pfls_amt_ctns = m_CommAgent.GetRealOutputData("EF2", "evl_pfls_amt_ctns");		//�򰡼��ͱݾ׳���
CString strpfls_rt_ctns = m_CommAgent.GetRealOutputData("EF2", "pfls_rt_ctns");		//����������
CString strpchs_amt_ctns = m_CommAgent.GetRealOutputData("EF2", "pchs_amt_ctns");		//���Աݾ׳���
CString strmlt_ctns = m_CommAgent.GetRealOutputData("EF2", "mlt_ctns");		//�¼�����
CString stritm_dvsn = m_CommAgent.GetRealOutputData("EF2", "itm_dvsn");		//���񱸺�
CString strcrry_cd = m_CommAgent.GetRealOutputData("EF2", "crry_cd");		//��ȭ�ڵ�




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
CString strcust_nm = realCommRecvData.GetItem(0, 6);		//����
CString strprdt_cd = realCommRecvData.GetItem(0, 7);		//��ǰ�ڵ�
CString strprdt_nm = realCommRecvData.GetItem(0, 8);		//��ǰ��
CString strodrv_sell_buy_dcd = realCommRecvData.GetItem(0, 9);		//�ؿ��Ļ��ŵ��ż������ڵ�
CString strustl_ctrc_qnt_ctns = realCommRecvData.GetItem(0, 10);		//�̰���������������
CString stravr_cncs_prc_ctns = realCommRecvData.GetItem(0, 11);		//���ü�ᰡ�ݳ���
CString strclr_psbl_qnt_ctns = realCommRecvData.GetItem(0, 12);		//û�갡�ɼ�������
CString strncnc_qnt_ctns = realCommRecvData.GetItem(0, 13);		//��ü���������
CString strodrv_pv_ctns = realCommRecvData.GetItem(0, 14);		//�ؿ��Ļ����簡����
CString strbfdt_prpt_mark = realCommRecvData.GetItem(0, 15);		//���ϴ���ȣ
CString strbfdt_prpt_prc_ctns = realCommRecvData.GetItem(0, 16);		//���ϴ�񰡰ݳ���
CString strbfdt_prpt_prc_rto_ctns = realCommRecvData.GetItem(0, 17);		//���ϴ�񰡰ݺ�������
CString strodrv_evl_amt_ctns = realCommRecvData.GetItem(0, 18);		//�ؿ��Ļ��򰡱ݾ׳���
CString strevl_pfls_amt_ctns = realCommRecvData.GetItem(0, 19);		//�򰡼��ͱݾ׳���
CString strpfls_rt_ctns = realCommRecvData.GetItem(0, 20);		//����������
CString strpchs_amt_ctns = realCommRecvData.GetItem(0, 21);		//���Աݾ׳���
CString strmlt_ctns = realCommRecvData.GetItem(0, 22);		//�¼�����
CString stritm_dvsn = realCommRecvData.GetItem(0, 23);		//���񱸺�
CString strcrry_cd = realCommRecvData.GetItem(0, 24);		//��ȭ�ڵ�
