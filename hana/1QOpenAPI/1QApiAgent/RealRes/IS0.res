BEGIN_FUNCTION_MAP
	REAL_TYPE=210, REAL_NAME=IS0, DESCRIPTION=�����ֽ�ü���뺸;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=sDataType, TYPE=string, SIZE=2, KEY=0, CAPTION=�����ͱ���, FID=0;
			 INDEX=1, ITEM=sProcTime, TYPE=string, SIZE=6, KEY=0, CAPTION=ó���ð�, FID=0;
			 INDEX=2, ITEM=sComCode, TYPE=string, SIZE=3, KEY=0, CAPTION=��ü����, FID=0;
			 INDEX=3, ITEM=sUserID, TYPE=string, SIZE=20, KEY=1, CAPTION=�����ID, FID=0;
			 INDEX=4, ITEM=sCtno, TYPE=string, SIZE=9, KEY=0, CAPTION=���´�ü��ȣ, FID=0;
			 INDEX=5, ITEM=sAcctNo, TYPE=string, SIZE=11, KEY=0, CAPTION=���¹�ȣ, FID=0;
			 INDEX=6, ITEM=sAcctName, TYPE=string, SIZE=50, KEY=0, CAPTION=���¸�, FID=0;
			 INDEX=7, ITEM=sBidCode, TYPE=string, SIZE=1, KEY=0, CAPTION=�ֹ�����, FID=0;
			 INDEX=8, ITEM=sModType, TYPE=string, SIZE=1, KEY=0, CAPTION=������ұ���, FID=0;
			 INDEX=9, ITEM=sBidDetail, TYPE=string, SIZE=3, KEY=0, CAPTION=�ֹ��󼼱���, FID=0;
			 INDEX=10, ITEM=sItemCode, TYPE=string, SIZE=12, KEY=0, CAPTION=���������ڵ�, FID=0;
			 INDEX=11, ITEM=sItemName, TYPE=string, SIZE=50, KEY=0, CAPTION=�����, FID=0;
			 INDEX=12, ITEM=sOrdVol, TYPE=string, SIZE=10, KEY=0, CAPTION=�ֹ�����, FID=0;
			 INDEX=13, ITEM=sOrdPrice, TYPE=string, SIZE=11, KEY=0, CAPTION=�ֹ�����, FID=0;
			 INDEX=14, ITEM=sHogaType, TYPE=string, SIZE=2, KEY=0, CAPTION=ȣ������, FID=0;
			 INDEX=15, ITEM=sOrderCon, TYPE=string, SIZE=2, KEY=0, CAPTION=�ֹ�����, FID=0;
			 INDEX=16, ITEM=sBrnNo, TYPE=string, SIZE=5, KEY=0, CAPTION=������ȣ, FID=0;
			 INDEX=17, ITEM=sOrdNo, TYPE=string, SIZE=10, KEY=0, CAPTION=�ֹ���ȣ, FID=0;
			 INDEX=18, ITEM=sOrgOrdNo, TYPE=string, SIZE=10, KEY=0, CAPTION=���ֹ���ȣ, FID=0;
			 INDEX=19, ITEM=sContVol, TYPE=string, SIZE=10, KEY=0, CAPTION=ü�����, FID=0;
			 INDEX=20, ITEM=sContPrice, TYPE=string, SIZE=11, KEY=0, CAPTION=ü�ᰡ��, FID=0;
			 INDEX=21, ITEM=sOrderModName, TYPE=string, SIZE=40, KEY=0, CAPTION=�ֹ�������ұ��и�, FID=0;
			 INDEX=22, ITEM=sOrderStatName, TYPE=string, SIZE=40, KEY=0, CAPTION=�ֹ�ó�����±��и�, FID=0;
			 INDEX=23, ITEM=sOrderTypeName, TYPE=string, SIZE=40, KEY=0, CAPTION=�ֹ������ڵ��, FID=0;
			 INDEX=24, ITEM=sRejectCode, TYPE=string, SIZE=4, KEY=0, CAPTION=�źλ����ڵ�, FID=0;
			 INDEX=25, ITEM=sRejectReason, TYPE=string, SIZE=40, KEY=0, CAPTION=�źλ���, FID=0;
			 INDEX=26, ITEM=sUnContVol, TYPE=string, SIZE=10, KEY=0, CAPTION=��ü�����, FID=0;
			 INDEX=27, ITEM=sCreditType, TYPE=string, SIZE=2, KEY=0, CAPTION=�ſ뱸��, FID=0;
			 INDEX=28, ITEM=sCreditLoanDate, TYPE=string, SIZE=8, KEY=0, CAPTION=�ſ������, FID=0;
			 INDEX=29, ITEM=sCreditSn, TYPE=string, SIZE=8, KEY=0, CAPTION=�����Ϸù�ȣ, FID=0;
			 INDEX=30, ITEM=sCreditPayment, TYPE=string, SIZE=10, KEY=0, CAPTION=�ſ��/�����ȯ��, FID=0;
			 INDEX=31, ITEM=sWrapNo, TYPE=string, SIZE=10, KEY=0, CAPTION=Wrap�ֹ���ȣ, FID=0;
			 INDEX=32, ITEM=sGroupNo, TYPE=string, SIZE=5, KEY=0, CAPTION=�׷��ȣ, FID=0;
			 INDEX=33, ITEM=sSeqNo, TYPE=string, SIZE=8, KEY=0, CAPTION=�ٽ��Ͻ�����, FID=0;
			 INDEX=34, ITEM=sBndlOrdrGrupSn, TYPE=string, SIZE=10, KEY=0, CAPTION=�ϰ��ֹ��׷��Ϸù�ȣ, FID=0;
			 INDEX=35, ITEM=sOrdrKndDcd, TYPE=string, SIZE=2, KEY=0, CAPTION=�ֹ����������ڵ�, FID=0;
			 INDEX=36, ITEM=sFiller, TYPE=string, SIZE=24, KEY=0, CAPTION=Filler, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 ���� ���Ǹ� ���� GetRealOutputData �޼ҵ� MFC �ҽ� ���ø�
 **********************************************/
CString strsDataType = m_CommAgent.GetRealOutputData("IS0", "sDataType");		//�����ͱ���
CString strsProcTime = m_CommAgent.GetRealOutputData("IS0", "sProcTime");		//ó���ð�
CString strsComCode = m_CommAgent.GetRealOutputData("IS0", "sComCode");		//��ü����
CString strsUserID = m_CommAgent.GetRealOutputData("IS0", "sUserID");		//�����ID
CString strsCtno = m_CommAgent.GetRealOutputData("IS0", "sCtno");		//���´�ü��ȣ
CString strsAcctNo = m_CommAgent.GetRealOutputData("IS0", "sAcctNo");		//���¹�ȣ
CString strsAcctName = m_CommAgent.GetRealOutputData("IS0", "sAcctName");		//���¸�
CString strsBidCode = m_CommAgent.GetRealOutputData("IS0", "sBidCode");		//�ֹ�����
CString strsModType = m_CommAgent.GetRealOutputData("IS0", "sModType");		//������ұ���
CString strsBidDetail = m_CommAgent.GetRealOutputData("IS0", "sBidDetail");		//�ֹ��󼼱���
CString strsItemCode = m_CommAgent.GetRealOutputData("IS0", "sItemCode");		//���������ڵ�
CString strsItemName = m_CommAgent.GetRealOutputData("IS0", "sItemName");		//�����
CString strsOrdVol = m_CommAgent.GetRealOutputData("IS0", "sOrdVol");		//�ֹ�����
CString strsOrdPrice = m_CommAgent.GetRealOutputData("IS0", "sOrdPrice");		//�ֹ�����
CString strsHogaType = m_CommAgent.GetRealOutputData("IS0", "sHogaType");		//ȣ������
CString strsOrderCon = m_CommAgent.GetRealOutputData("IS0", "sOrderCon");		//�ֹ�����
CString strsBrnNo = m_CommAgent.GetRealOutputData("IS0", "sBrnNo");		//������ȣ
CString strsOrdNo = m_CommAgent.GetRealOutputData("IS0", "sOrdNo");		//�ֹ���ȣ
CString strsOrgOrdNo = m_CommAgent.GetRealOutputData("IS0", "sOrgOrdNo");		//���ֹ���ȣ
CString strsContVol = m_CommAgent.GetRealOutputData("IS0", "sContVol");		//ü�����
CString strsContPrice = m_CommAgent.GetRealOutputData("IS0", "sContPrice");		//ü�ᰡ��
CString strsOrderModName = m_CommAgent.GetRealOutputData("IS0", "sOrderModName");		//�ֹ�������ұ��и�
CString strsOrderStatName = m_CommAgent.GetRealOutputData("IS0", "sOrderStatName");		//�ֹ�ó�����±��и�
CString strsOrderTypeName = m_CommAgent.GetRealOutputData("IS0", "sOrderTypeName");		//�ֹ������ڵ��
CString strsRejectCode = m_CommAgent.GetRealOutputData("IS0", "sRejectCode");		//�źλ����ڵ�
CString strsRejectReason = m_CommAgent.GetRealOutputData("IS0", "sRejectReason");		//�źλ���
CString strsUnContVol = m_CommAgent.GetRealOutputData("IS0", "sUnContVol");		//��ü�����
CString strsCreditType = m_CommAgent.GetRealOutputData("IS0", "sCreditType");		//�ſ뱸��
CString strsCreditLoanDate = m_CommAgent.GetRealOutputData("IS0", "sCreditLoanDate");		//�ſ������
CString strsCreditSn = m_CommAgent.GetRealOutputData("IS0", "sCreditSn");		//�����Ϸù�ȣ
CString strsCreditPayment = m_CommAgent.GetRealOutputData("IS0", "sCreditPayment");		//�ſ��/�����ȯ��
CString strsWrapNo = m_CommAgent.GetRealOutputData("IS0", "sWrapNo");		//Wrap�ֹ���ȣ
CString strsGroupNo = m_CommAgent.GetRealOutputData("IS0", "sGroupNo");		//�׷��ȣ
CString strsSeqNo = m_CommAgent.GetRealOutputData("IS0", "sSeqNo");		//�ٽ��Ͻ�����
CString strsBndlOrdrGrupSn = m_CommAgent.GetRealOutputData("IS0", "sBndlOrdrGrupSn");		//�ϰ��ֹ��׷��Ϸù�ȣ
CString strsOrdrKndDcd = m_CommAgent.GetRealOutputData("IS0", "sOrdrKndDcd");		//�ֹ����������ڵ�
CString strsFiller = m_CommAgent.GetRealOutputData("IS0", "sFiller");		//Filler




/**********************************************
 ���� ���Ǹ� ���� �޸� �ε��� ���� �ҽ� ���ø�(C++������ ��� ����)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strsDataType = realCommRecvData.GetItem(0, 0);		//�����ͱ���
CString strsProcTime = realCommRecvData.GetItem(0, 1);		//ó���ð�
CString strsComCode = realCommRecvData.GetItem(0, 2);		//��ü����
CString strsUserID = realCommRecvData.GetItem(0, 3);		//�����ID
CString strsCtno = realCommRecvData.GetItem(0, 4);		//���´�ü��ȣ
CString strsAcctNo = realCommRecvData.GetItem(0, 5);		//���¹�ȣ
CString strsAcctName = realCommRecvData.GetItem(0, 6);		//���¸�
CString strsBidCode = realCommRecvData.GetItem(0, 7);		//�ֹ�����
CString strsModType = realCommRecvData.GetItem(0, 8);		//������ұ���
CString strsBidDetail = realCommRecvData.GetItem(0, 9);		//�ֹ��󼼱���
CString strsItemCode = realCommRecvData.GetItem(0, 10);		//���������ڵ�
CString strsItemName = realCommRecvData.GetItem(0, 11);		//�����
CString strsOrdVol = realCommRecvData.GetItem(0, 12);		//�ֹ�����
CString strsOrdPrice = realCommRecvData.GetItem(0, 13);		//�ֹ�����
CString strsHogaType = realCommRecvData.GetItem(0, 14);		//ȣ������
CString strsOrderCon = realCommRecvData.GetItem(0, 15);		//�ֹ�����
CString strsBrnNo = realCommRecvData.GetItem(0, 16);		//������ȣ
CString strsOrdNo = realCommRecvData.GetItem(0, 17);		//�ֹ���ȣ
CString strsOrgOrdNo = realCommRecvData.GetItem(0, 18);		//���ֹ���ȣ
CString strsContVol = realCommRecvData.GetItem(0, 19);		//ü�����
CString strsContPrice = realCommRecvData.GetItem(0, 20);		//ü�ᰡ��
CString strsOrderModName = realCommRecvData.GetItem(0, 21);		//�ֹ�������ұ��и�
CString strsOrderStatName = realCommRecvData.GetItem(0, 22);		//�ֹ�ó�����±��и�
CString strsOrderTypeName = realCommRecvData.GetItem(0, 23);		//�ֹ������ڵ��
CString strsRejectCode = realCommRecvData.GetItem(0, 24);		//�źλ����ڵ�
CString strsRejectReason = realCommRecvData.GetItem(0, 25);		//�źλ���
CString strsUnContVol = realCommRecvData.GetItem(0, 26);		//��ü�����
CString strsCreditType = realCommRecvData.GetItem(0, 27);		//�ſ뱸��
CString strsCreditLoanDate = realCommRecvData.GetItem(0, 28);		//�ſ������
CString strsCreditSn = realCommRecvData.GetItem(0, 29);		//�����Ϸù�ȣ
CString strsCreditPayment = realCommRecvData.GetItem(0, 30);		//�ſ��/�����ȯ��
CString strsWrapNo = realCommRecvData.GetItem(0, 31);		//Wrap�ֹ���ȣ
CString strsGroupNo = realCommRecvData.GetItem(0, 32);		//�׷��ȣ
CString strsSeqNo = realCommRecvData.GetItem(0, 33);		//�ٽ��Ͻ�����
CString strsBndlOrdrGrupSn = realCommRecvData.GetItem(0, 34);		//�ϰ��ֹ��׷��Ϸù�ȣ
CString strsOrdrKndDcd = realCommRecvData.GetItem(0, 35);		//�ֹ����������ڵ�
CString strsFiller = realCommRecvData.GetItem(0, 36);		//Filler
