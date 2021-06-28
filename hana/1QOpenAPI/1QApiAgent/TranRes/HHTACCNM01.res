BEGIN_TRAN_LAYOUT

	TR_CODE=HHTACCNM01, TR_NAME=����/����/����/��й�ȣ����, SERVER=M, ENCODE=0, COMPRESS=0, CERT=0;

	BEGIN_RECORD

		'*******************************************
		'* ����Է� �κ��Դϴ�.
		'*******************************************
		REC_NAME=InRec1, INOUT=0, ARRAY=0, ARRINFO=;
		BEGIN_INPUT0_ITEM
			 INDEX=0, ITEM=func, TYPE=string, SIZE=1, CAPTION=��ɱ����ڵ�;
			 INDEX=1, ITEM=usid, TYPE=string, SIZE=20, CAPTION=����ھ��̵�;
			 INDEX=2, ITEM=errc, TYPE=string, SIZE=1, CAPTION=�����ڵ�;
			 INDEX=3, ITEM=emsg, TYPE=string, SIZE=80, CAPTION=�����޽���;
			 INDEX=4, ITEM=nrec, TYPE=string, SIZE=4, CAPTION=�Է°Ǽ�;
		END_INPUT0_ITEM

		REC_NAME=InRec2, INOUT=0, ARRAY=3, ARRINFO=InRec1.nrec;
		BEGIN_INPUT1_ITEM
			 INDEX=0, ITEM=accn, TYPE=string, SIZE=64, CAPTION=���¹�ȣ;
			 INDEX=1, ITEM=sub_accn, TYPE=string, SIZE=12, CAPTION=��ü���¹�ȣ;
			 INDEX=2, ITEM=acnm, TYPE=string, SIZE=50, CAPTION=���¸�;
			 INDEX=3, ITEM=acal, TYPE=string, SIZE=40, CAPTION=���º���;
			 INDEX=4, ITEM=achk, TYPE=string, SIZE=2, CAPTION=����Ư��;
			 INDEX=5, ITEM=pwch, TYPE=string, SIZE=1, CAPTION=���࿬����¿���;
		END_INPUT1_ITEM

		'*******************************************
		'* ������ �κ��Դϴ�.
		'*******************************************
		REC_NAME=OutRec1, INOUT=1, ARRAY=0, ARRINFO=;
		BEGIN_OUTPUT0_ITEM
			 INDEX=0, ITEM=func, TYPE=string, SIZE=1, CAPTION=��ɱ����ڵ�;
			 INDEX=1, ITEM=usid, TYPE=string, SIZE=20, CAPTION=����ھ��̵�;
			 INDEX=2, ITEM=errc, TYPE=string, SIZE=1, CAPTION=�����ڵ�;
			 INDEX=3, ITEM=emsg, TYPE=string, SIZE=80, CAPTION=�����޽���;
			 INDEX=4, ITEM=nrec, TYPE=string, SIZE=4, CAPTION=��°Ǽ�;
		END_OUTPUT0_ITEM

		REC_NAME=OutRec2, INOUT=1, ARRAY=3, ARRINFO=OutRec1.nrec;
		BEGIN_OUTPUT1_ITEM
			 INDEX=0, ITEM=accn, TYPE=string, SIZE=64, CAPTION=���¹�ȣ;
			 INDEX=1, ITEM=sub_accn, TYPE=string, SIZE=12, CAPTION=��ü���¹�ȣ;
			 INDEX=2, ITEM=acnm, TYPE=string, SIZE=50, CAPTION=���¸�;
			 INDEX=3, ITEM=acal, TYPE=string, SIZE=40, CAPTION=���º���;
			 INDEX=4, ITEM=achk, TYPE=string, SIZE=2, CAPTION=����Ư��;
			 INDEX=5, ITEM=pwch, TYPE=string, SIZE=1, CAPTION=���࿬����¿���;
		END_OUTPUT1_ITEM

	END_RECORD

END_TRAN_LAYOUT



/**********************************************
 ���� ���Ǹ� ���� SetTranInputData �޼ҵ� MFC �ҽ� ���ø�
 I N - P U T
 **********************************************/
CString strfunc;		//��ɱ����ڵ�
CString strusid;		//����ھ��̵�
CString strerrc;		//�����ڵ�
CString stremsg;		//�����޽���
CString strnrec;		//�Է°Ǽ�
CString straccn;		//���¹�ȣ
CString strsub_accn;		//��ü���¹�ȣ
CString stracnm;		//���¸�
CString stracal;		//���º���
CString strachk;		//����Ư��
CString strpwch;		//���࿬����¿���

int nRequestId = 0;

m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec1", "func", strfunc);		//��ɱ����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec1", "usid", strusid);		//����ھ��̵�
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec1", "errc", strerrc);		//�����ڵ�
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec1", "emsg", stremsg);		//�����޽���
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec1", "nrec", strnrec);		//�Է°Ǽ�
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec2", "accn", straccn);		//���¹�ȣ
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec2", "sub_accn", strsub_accn);		//��ü���¹�ȣ
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec2", "acnm", stracnm);		//���¸�
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec2", "acal", stracal);		//���º���
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec2", "achk", strachk);		//����Ư��
m_CommAgent.SetTranInputData(nRequestId, "HHTACCNM01", "InRec2", "pwch", strpwch);		//���࿬����¿���




/**********************************************
 ���� ���Ǹ� ���� GetTranOutputData �޼ҵ� MFC �ҽ� ���ø�
 O U T - P U T
 **********************************************/
int nRow = 0;

CString strfunc = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec1", "func", 0);		//��ɱ����ڵ�
CString strusid = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec1", "usid", 0);		//����ھ��̵�
CString strerrc = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec1", "errc", 0);		//�����ڵ�
CString stremsg = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec1", "emsg", 0);		//�����޽���
CString strnrec = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec1", "nrec", 0);		//��°Ǽ�
CString straccn = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec2", "accn", nRow);		//���¹�ȣ
CString strsub_accn = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec2", "sub_accn", nRow);		//��ü���¹�ȣ
CString stracnm = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec2", "acnm", nRow);		//���¸�
CString stracal = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec2", "acal", nRow);		//���º���
CString strachk = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec2", "achk", nRow);		//����Ư��
CString strpwch = m_CommAgent.GetTranOutputData("HHTACCNM01", "OutRec2", "pwch", nRow);		//���࿬����¿���
