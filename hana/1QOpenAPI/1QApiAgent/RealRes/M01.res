BEGIN_FUNCTION_MAP
	REAL_TYPE=201, REAL_NAME=M01, DESCRIPTION=���������� ����ó�� �˸�;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=VERSION_YN, TYPE=string, SIZE=1, KEY=1, CAPTION=�ǽð�key, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 ���� ���Ǹ� ���� GetRealOutputData �޼ҵ� MFC �ҽ� ���ø�
 **********************************************/
CString strVERSION_YN = m_CommAgent.GetRealOutputData("M01", "VERSION_YN");		//�ǽð�key




/**********************************************
 ���� ���Ǹ� ���� �޸� �ε��� ���� �ҽ� ���ø�(C++������ ��� ����)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strVERSION_YN = realCommRecvData.GetItem(0, 0);		//�ǽð�key
