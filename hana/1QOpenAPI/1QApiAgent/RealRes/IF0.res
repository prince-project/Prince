BEGIN_FUNCTION_MAP
	REAL_TYPE=211, REAL_NAME=IF0, DESCRIPTION=���������ɼ�ü���뺸;
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
			 INDEX=9, ITEM=sItemCode, TYPE=string, SIZE=12, KEY=0, CAPTION=���������ڵ�, FID=0;
			 INDEX=10, ITEM=sItemName, TYPE=string, SIZE=50, KEY=0, CAPTION=�����, FID=0;
			 INDEX=11, ITEM=sOrdVol, TYPE=string, SIZE=10, KEY=0, CAPTION=�ֹ�����, FID=0;
			 INDEX=12, ITEM=sOrdPrice, TYPE=string, SIZE=11, KEY=0, CAPTION=�ֹ�����, FID=0;
			 INDEX=13, ITEM=sHogaType, TYPE=string, SIZE=2, KEY=0, CAPTION=ȣ������, FID=0;
			 INDEX=14, ITEM=sOrderCon, TYPE=string, SIZE=2, KEY=0, CAPTION=�ֹ�����, FID=0;
			 INDEX=15, ITEM=sBrnNo, TYPE=string, SIZE=5, KEY=0, CAPTION=������ȣ, FID=0;
			 INDEX=16, ITEM=sOrdNo, TYPE=string, SIZE=10, KEY=0, CAPTION=�ֹ���ȣ, FID=0;
			 INDEX=17, ITEM=sOrgOrdNo, TYPE=string, SIZE=10, KEY=0, CAPTION=���ֹ���ȣ, FID=0;
			 INDEX=18, ITEM=sContVol, TYPE=string, SIZE=10, KEY=0, CAPTION=ü�����, FID=0;
			 INDEX=19, ITEM=sContPrice, TYPE=string, SIZE=11, KEY=0, CAPTION=ü�ᰡ��, FID=0;
			 INDEX=20, ITEM=sRejectCode, TYPE=string, SIZE=4, KEY=0, CAPTION=�źλ����ڵ�, FID=0;
			 INDEX=21, ITEM=sRejectReason, TYPE=string, SIZE=40, KEY=0, CAPTION=�źλ���, FID=0;
			 INDEX=22, ITEM=sUnContVol, TYPE=string, SIZE=10, KEY=0, CAPTION=��ü�����, FID=0;
			 INDEX=23, ITEM=sFotsTradeUnit, TYPE=string, SIZE=16, KEY=0, CAPTION=�ŷ��¼�, FID=0;
			 INDEX=24, ITEM=sChegNo, TYPE=string, SIZE=10, KEY=0, CAPTION=ü���ȣ, FID=0;
			 INDEX=25, ITEM=sFstPrc, TYPE=string, SIZE=11, KEY=0, CAPTION=�ٿ��� ü�ᰡ��(��������), FID=0;
			 INDEX=26, ITEM=sSndPrc, TYPE=string, SIZE=11, KEY=0, CAPTION=������ ü�ᰡ��(��������), FID=0;
			 INDEX=27, ITEM=sWrapNo, TYPE=string, SIZE=10, KEY=0, CAPTION=Wrap�ֹ���ȣ, FID=0;
			 INDEX=28, ITEM=sGroupNo, TYPE=string, SIZE=5, KEY=0, CAPTION=�׷��ȣ, FID=0;
			 INDEX=29, ITEM=sSeqNo, TYPE=string, SIZE=8, KEY=0, CAPTION=�ٽ��Ͻ�����, FID=0;
			 INDEX=30, ITEM=sFee, TYPE=string, SIZE=8, KEY=0, CAPTION=������, FID=0;
			 INDEX=31, ITEM=sFiller, TYPE=string, SIZE=31, KEY=0, CAPTION=Filler, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 ���� ���Ǹ� ���� GetRealOutputData �޼ҵ� MFC �ҽ� ���ø�
 **********************************************/
CString strsDataType = m_CommAgent.GetRealOutputData("IF0", "sDataType");		//�����ͱ���
CString strsProcTime = m_CommAgent.GetRealOutputData("IF0", "sProcTime");		//ó���ð�
CString strsComCode = m_CommAgent.GetRealOutputData("IF0", "sComCode");		//��ü����
CString strsUserID = m_CommAgent.GetRealOutputData("IF0", "sUserID");		//�����ID
CString strsCtno = m_CommAgent.GetRealOutputData("IF0", "sCtno");		//���´�ü��ȣ
CString strsAcctNo = m_CommAgent.GetRealOutputData("IF0", "sAcctNo");		//���¹�ȣ
CString strsAcctName = m_CommAgent.GetRealOutputData("IF0", "sAcctName");		//���¸�
CString strsBidCode = m_CommAgent.GetRealOutputData("IF0", "sBidCode");		//�ֹ�����
CString strsModType = m_CommAgent.GetRealOutputData("IF0", "sModType");		//������ұ���
CString strsItemCode = m_CommAgent.GetRealOutputData("IF0", "sItemCode");		//���������ڵ�
CString strsItemName = m_CommAgent.GetRealOutputData("IF0", "sItemName");		//�����
CString strsOrdVol = m_CommAgent.GetRealOutputData("IF0", "sOrdVol");		//�ֹ�����
CString strsOrdPrice = m_CommAgent.GetRealOutputData("IF0", "sOrdPrice");		//�ֹ�����
CString strsHogaType = m_CommAgent.GetRealOutputData("IF0", "sHogaType");		//ȣ������
CString strsOrderCon = m_CommAgent.GetRealOutputData("IF0", "sOrderCon");		//�ֹ�����
CString strsBrnNo = m_CommAgent.GetRealOutputData("IF0", "sBrnNo");		//������ȣ
CString strsOrdNo = m_CommAgent.GetRealOutputData("IF0", "sOrdNo");		//�ֹ���ȣ
CString strsOrgOrdNo = m_CommAgent.GetRealOutputData("IF0", "sOrgOrdNo");		//���ֹ���ȣ
CString strsContVol = m_CommAgent.GetRealOutputData("IF0", "sContVol");		//ü�����
CString strsContPrice = m_CommAgent.GetRealOutputData("IF0", "sContPrice");		//ü�ᰡ��
CString strsRejectCode = m_CommAgent.GetRealOutputData("IF0", "sRejectCode");		//�źλ����ڵ�
CString strsRejectReason = m_CommAgent.GetRealOutputData("IF0", "sRejectReason");		//�źλ���
CString strsUnContVol = m_CommAgent.GetRealOutputData("IF0", "sUnContVol");		//��ü�����
CString strsFotsTradeUnit = m_CommAgent.GetRealOutputData("IF0", "sFotsTradeUnit");		//�ŷ��¼�
CString strsChegNo = m_CommAgent.GetRealOutputData("IF0", "sChegNo");		//ü���ȣ
CString strsFstPrc = m_CommAgent.GetRealOutputData("IF0", "sFstPrc");		//�ٿ��� ü�ᰡ��(��������)
CString strsSndPrc = m_CommAgent.GetRealOutputData("IF0", "sSndPrc");		//������ ü�ᰡ��(��������)
CString strsWrapNo = m_CommAgent.GetRealOutputData("IF0", "sWrapNo");		//Wrap�ֹ���ȣ
CString strsGroupNo = m_CommAgent.GetRealOutputData("IF0", "sGroupNo");		//�׷��ȣ
CString strsSeqNo = m_CommAgent.GetRealOutputData("IF0", "sSeqNo");		//�ٽ��Ͻ�����
CString strsFee = m_CommAgent.GetRealOutputData("IF0", "sFee");		//������
CString strsFiller = m_CommAgent.GetRealOutputData("IF0", "sFiller");		//Filler




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
CString strsItemCode = realCommRecvData.GetItem(0, 9);		//���������ڵ�
CString strsItemName = realCommRecvData.GetItem(0, 10);		//�����
CString strsOrdVol = realCommRecvData.GetItem(0, 11);		//�ֹ�����
CString strsOrdPrice = realCommRecvData.GetItem(0, 12);		//�ֹ�����
CString strsHogaType = realCommRecvData.GetItem(0, 13);		//ȣ������
CString strsOrderCon = realCommRecvData.GetItem(0, 14);		//�ֹ�����
CString strsBrnNo = realCommRecvData.GetItem(0, 15);		//������ȣ
CString strsOrdNo = realCommRecvData.GetItem(0, 16);		//�ֹ���ȣ
CString strsOrgOrdNo = realCommRecvData.GetItem(0, 17);		//���ֹ���ȣ
CString strsContVol = realCommRecvData.GetItem(0, 18);		//ü�����
CString strsContPrice = realCommRecvData.GetItem(0, 19);		//ü�ᰡ��
CString strsRejectCode = realCommRecvData.GetItem(0, 20);		//�źλ����ڵ�
CString strsRejectReason = realCommRecvData.GetItem(0, 21);		//�źλ���
CString strsUnContVol = realCommRecvData.GetItem(0, 22);		//��ü�����
CString strsFotsTradeUnit = realCommRecvData.GetItem(0, 23);		//�ŷ��¼�
CString strsChegNo = realCommRecvData.GetItem(0, 24);		//ü���ȣ
CString strsFstPrc = realCommRecvData.GetItem(0, 25);		//�ٿ��� ü�ᰡ��(��������)
CString strsSndPrc = realCommRecvData.GetItem(0, 26);		//������ ü�ᰡ��(��������)
CString strsWrapNo = realCommRecvData.GetItem(0, 27);		//Wrap�ֹ���ȣ
CString strsGroupNo = realCommRecvData.GetItem(0, 28);		//�׷��ȣ
CString strsSeqNo = realCommRecvData.GetItem(0, 29);		//�ٽ��Ͻ�����
CString strsFee = realCommRecvData.GetItem(0, 30);		//������
CString strsFiller = realCommRecvData.GetItem(0, 31);		//Filler
