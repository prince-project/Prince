BEGIN_TRAN_LAYOUT

	TR_CODE=HHTACCNM01, TR_NAME=계좌/순서/별명/비밀번호저장, SERVER=M, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* 통신입력 부분입니다.
		'*******************************************
		REC_NAME=InRec1, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=func, TYPE=string, SIZE=1, CAPTION=기능구분코드;
			 INDEX=1, ITEM=usid, TYPE=string, SIZE=20, CAPTION=사용자아이디;
			 INDEX=2, ITEM=errc, TYPE=string, SIZE=1, CAPTION=에러코드;
			 INDEX=3, ITEM=emsg, TYPE=string, SIZE=80, CAPTION=에러메시지;
			 INDEX=4, ITEM=nrec, TYPE=string, SIZE=4, CAPTION=입력건수;
		END_INPUT0_ITEM

		REC_NAME=InRec2, INOUT=0, ARRAY=3, ARRINFO=InRec1.nrec;
		BEGIN_INPUT1_ITEM
			 INDEX=0, ITEM=accn, TYPE=string, SIZE=64, CAPTION=계좌번호;
			 INDEX=1, ITEM=sub_accn, TYPE=string, SIZE=12, CAPTION=대체계좌번호;
			 INDEX=2, ITEM=acnm, TYPE=string, SIZE=50, CAPTION=계좌명;
			 INDEX=3, ITEM=acal, TYPE=string, SIZE=40, CAPTION=계좌별명;
			 INDEX=4, ITEM=achk, TYPE=string, SIZE=2, CAPTION=계좌특성;
			 INDEX=5, ITEM=pwch, TYPE=string, SIZE=1, CAPTION=은행연계계좌여부;
		END_INPUT1_ITEM

		'*******************************************
		'* 통신출력 부분입니다.
		'*******************************************
		REC_NAME=OutRec1, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=func, TYPE=string, SIZE=1, CAPTION=기능구분코드;
			 INDEX=1, ITEM=usid, TYPE=string, SIZE=20, CAPTION=사용자아이디;
			 INDEX=2, ITEM=errc, TYPE=string, SIZE=1, CAPTION=에러코드;
			 INDEX=3, ITEM=emsg, TYPE=string, SIZE=80, CAPTION=에러메시지;
			 INDEX=4, ITEM=nrec, TYPE=string, SIZE=4, CAPTION=출력건수;
		END_OUTPUT0_ITEM

		REC_NAME=OutRec2, INOUT=1, ARRAY=3, ARRINFO=OutRec1.nrec;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=accn, TYPE=string, SIZE=64, CAPTION=계좌번호;
			 INDEX=1, ITEM=sub_accn, TYPE=string, SIZE=12, CAPTION=대체계좌번호;
			 INDEX=2, ITEM=acnm, TYPE=string, SIZE=50, CAPTION=계좌명;
			 INDEX=3, ITEM=acal, TYPE=string, SIZE=40, CAPTION=계좌별명;
			 INDEX=4, ITEM=achk, TYPE=string, SIZE=2, CAPTION=계좌특성;
			 INDEX=5, ITEM=pwch, TYPE=string, SIZE=1, CAPTION=은행연계계좌여부;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 개발 편의를 위한 SetTranInputData 메소드 MFC 소스 템플릿
 I N - P U T
 **********************************************/
CString strfunc;		//기능구분코드
CString strusid;		//사용자아이디
CString strerrc;		//에러코드
CString stremsg;		//에러메시지
CString strnrec;		//입력건수
CString straccn;		//계좌번호
CString strsub_accn;		//대체계좌번호
CString stracnm;		//계좌명
CString stracal;		//계좌별명
CString strachk;		//계좌특성
CString strpwch;		//은행연계계좌여부

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec1", "func", strfunc);		//기능구분코드
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec1", "usid", strusid);		//사용자아이디
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec1", "errc", strerrc);		//에러코드
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec1", "emsg", stremsg);		//에러메시지
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec1", "nrec", strnrec);		//입력건수
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec2", "accn", straccn);		//계좌번호
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec2", "sub_accn", strsub_accn);		//대체계좌번호
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec2", "acnm", stracnm);		//계좌명
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec2", "acal", stracal);		//계좌별명
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec2", "achk", strachk);		//계좌특성
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec2", "pwch", strpwch);		//은행연계계좌여부




/**********************************************
 개발 편의를 위한 GetTranOutputData 메소드 MFC 소스 템플릿
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strfunc = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec1", "func", 0);		//기능구분코드
CString strusid = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec1", "usid", 0);		//사용자아이디
CString strerrc = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec1", "errc", 0);		//에러코드
CString stremsg = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec1", "emsg", 0);		//에러메시지
CString strnrec = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec1", "nrec", 0);		//출력건수
CString straccn = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec2", "accn", nRow);		//계좌번호
CString strsub_accn = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec2", "sub_accn", nRow);		//대체계좌번호
CString stracnm = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec2", "acnm", nRow);		//계좌명
CString stracal = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec2", "acal", nRow);		//계좌별명
CString strachk = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec2", "achk", nRow);		//계좌특성
CString strpwch = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec2", "pwch", nRow);		//은행연계계좌여부
