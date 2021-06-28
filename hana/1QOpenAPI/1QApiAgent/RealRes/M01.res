BEGIN_FUNCTION_MAP
	REAL_TYPE=201, REAL_NAME=M01, DESCRIPTION=마스터파일 버전처리 알림;
	BEGIN_DATA_MAP
	begin
			 INDEX=0, ITEM=VERSION_YN, TYPE=string, SIZE=1, KEY=1, CAPTION=실시간key, FID=0;
	end
	END_DATA_MAP
END_FUNCTION_MAP



/**********************************************
 개발 편의를 위한 GetRealOutputData 메소드 MFC 소스 템플릿
 **********************************************/
CString strVERSION_YN = m_CommAgent.GetRealOutputData("M01", "VERSION_YN");		//실시간key




/**********************************************
 개발 편의를 위한 메모리 인덱스 접근 소스 템플릿(C++에서만 사용 가능)
 **********************************************/
CCommRecvData realCommRecvData;
m_CommAgent.GetCommRealRecvDataBlock((long)&realCommRecvData);

CString strVERSION_YN = realCommRecvData.GetItem(0, 0);		//실시간key
