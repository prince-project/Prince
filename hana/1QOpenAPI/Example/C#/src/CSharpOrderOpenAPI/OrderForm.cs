using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace CSharpOrderOpenAPI
{
    /***********************************
     * 통신조회 응답 옵션값
     ***********************************/
    enum CommRecvOpt
    {
        TranCode        = 0, //Tr코드
        PrevNextCode    = 1, //연속데이타 구분(0:없음, 1:이전, 2:다음, 3:이전/다음)
        PrevNextKey     = 2, //연속조회키
        MsgCode         = 3, //메시지코드
        Msg             = 4, //메시지
        SubMsgCode      = 5, //부가메시지코드
        SubMsg          = 6,  //부가메시지
        Error           = 7   //에러코드
    }

    /***********************************
     * 통신 상태 이벤트
     ***********************************/
    enum CommEvent
    {
        Connected = 100,		// 연결 완료
        Connecting = 101,		// 소켓연결중
        Closed = 102,			// 소켓 단절 상태
        Closing = 103,			// 소켓 단절 중
        ReconnectRequest = 104,	// 재접속 요청
        ConnectFail = 105,		// 소켓 연결 실패

        //서버 공지 메시지
        NotifyMultiLogin = 150,	// 다중접속 알림 메시지
        NotifyEmergency = 151,	// 긴급공지 메시지

        //팝업메시지
		PopUpMsg = 160
    }

    public partial class OrderForm : Form
    {
        Int32 m_nSeverType = 0;

        public OrderForm()
        {
            InitializeComponent();

            string strFullPath = Application.StartupPath + "\\HFCommAgent.dll";
            FileInfo fileInfo = new FileInfo(strFullPath);
            
            /*********************************
             * 예제 프로그램과 동일한 위치에 OpenAPI 에이젠트 컨트롤(HFCommAgent.dll)
             * 모듈이 있을 경우 레지스트리에 자동 등록처리를 한다.
             *********************************/
            if (fileInfo.Exists == true)
                Process.Start("regsvr32.exe", string.Format("-s \"{0}\"", strFullPath));
            else
            {
                strFullPath = Application.StartupPath + "\\..\\..\\..\\1QApiAgent\\HFCommAgent.dll";
                fileInfo = null;
                fileInfo = new FileInfo(strFullPath);
                if (fileInfo.Exists == true)
                    Process.Start("regsvr32.exe", string.Format("-s \"{0}\"", strFullPath));
                else
                    MessageBox.Show("HFCommAgent.dll 파일을 찾지 못했습니다.");
            }

            InitListAcc();
            InitListOrdPush();
            InitListExec();
            InitListBalance();
            
            /**********************************
             * 조회Tr, 실시간 통신 I/O 정보 리소스 파일 로드
             **********************************/
            string strApidAgentModulePath = axHFCommAgent1.GetApiAgentModulePath();
            labelAgentPath.Text = strApidAgentModulePath;
            
            /**********************************
             * 접속서버 선택
             **********************************/
            //0 : 실거래서버, 1 : 국내모의서버, 2 : 해외모의서버
            m_nSeverType = axHFCommAgent1.GetLoginMode(0);
            switch (m_nSeverType)
            {
                case 1: //국내모의서버
                    radioSvr2.Checked = true;
                    break;
                case 2: //해외모의서버
                    radioSvr3.Checked = true;
                    break;
                default: //실거래서버
                    radioSvr1.Checked = true;
                    break;
            }//End of switch
        }

        void InitListAcc()
        {
            int i = 0;
            int nCnt = 6;
            ColumnHeader[] colHeader = new ColumnHeader[nCnt];

            for (i = 0; i < nCnt; i++)
            {
                colHeader[i] = new ColumnHeader();
                colHeader[i].Width = 80;
            }

            colHeader[0].Text = "계좌번호";
            colHeader[1].Text = "대체번호";
            colHeader[2].Text = "계좌상품번호";
            colHeader[3].Text = "계좌명";
            colHeader[4].Text = "계좌특정";
            colHeader[5].Text = "은행연계여부";

            for (i = 0; i < nCnt; i++)
            {
                listViewAcc.Columns.Add(colHeader[i]);
            }

        }

        void InitListOrdPush()
        {
            int i = 0;
            int nCnt = 1;
            ColumnHeader[] colHeader = new ColumnHeader[nCnt];

            for (i = 0; i < nCnt; i++)
            {
                colHeader[i] = new ColumnHeader();
                colHeader[i].Width = 700;
            }

            colHeader[0].Text = "메시지";
            
            for (i = 0; i < nCnt; i++)
            {
                listViewOrdPush.Columns.Add(colHeader[i]);
            }

        }

        void InitListExec()
        {
            int i = 0;
            int nCnt = 22;
            ColumnHeader[] colHeader = new ColumnHeader[nCnt];

            for (i = 0; i < nCnt; i++)
            {
                colHeader[i] = new ColumnHeader();
                colHeader[i].Width = 80;
            }

            colHeader[0].Text = "주문번호";
            colHeader[1].Text = "원주문번호";
            colHeader[2].Text = "상품코드";
            colHeader[3].Text = "단축코드";
            colHeader[4].Text = "상품명";
            colHeader[5].Text = "매매구분명";
            colHeader[6].Text = "호가구분코드";
            colHeader[7].Text = "호가구분코드";
            colHeader[8].Text = "주문가격금액";
            colHeader[9].Text = "주문수량";
            colHeader[10].Text = "체결구분명";
            colHeader[11].Text = "체결수량";
            colHeader[12].Text = "체결가격금액";
            colHeader[13].Text = "한국체결시간";
            colHeader[14].Text = "정정취소확인수량";
            colHeader[15].Text = "미체결수량";
		    colHeader[16].Text = "접수구분코드";
            colHeader[17].Text = "접수구분명";
            colHeader[18].Text = "거래소접수시간";
            colHeader[19].Text = "거래소메시지";
            colHeader[20].Text = "통신매체구분";
            colHeader[21].Text = "외부기관거부사유코드";

            for (i = 0; i < nCnt; i++)
            {
                listViewExe.Columns.Add(colHeader[i]);
            }

        }

        void InitListBalance()
        {
            int i = 0;
            int nCnt = 14;
            ColumnHeader[] colHeader = new ColumnHeader[nCnt];

            for (i = 0; i < nCnt; i++)
            {
                colHeader[i] = new ColumnHeader();
                colHeader[i].Width = 80;
            }

            colHeader[0].Text = "상품코드";
            colHeader[1].Text = "단축상품코드";
            colHeader[2].Text = "상품명";
            colHeader[3].Text = "매매구분";
            colHeader[4].Text = "매매구분코드";
            colHeader[5].Text = "미결제수량";
            colHeader[6].Text = "평균가격";
            colHeader[7].Text = "현재가격";
            colHeader[8].Text = "대비";
            colHeader[9].Text = "평가금액";
            colHeader[10].Text = "평가손익";
            colHeader[11].Text = "손익율";
            colHeader[12].Text = "청산가능";
            colHeader[13].Text = "매입금액";

            for (i = 0; i < nCnt; i++)
            {
                listViewBalance.Columns.Add(colHeader[i]);
            }

        }

        private void 지수선옵주문_Load(object sender, EventArgs e)
        {

        }

        string m_strLoginID = "";
        private void BtnLogin_Click(object sender, EventArgs e)
        {
            string strUserID = textLoginID.Text;
            string strUserPwd = textLoginPwd.Text;
            string strCertPwd = textCertPwd.Text;
            m_strLoginID = "";

            if (strUserID == "" || strUserPwd == "")
            {
                MessageBox.Show("로그인 ID/비번은 필수 입력사항입니다.");
                return;
            }

            //강제접속IP를 설정한다.
            string strIPAddress = textBoxIP.Text;
            axHFCommAgent1.SetConnectIPList(strIPAddress);

            //통신모듈 초기화 및 연결
            Int32 nRtn = axHFCommAgent1.CommInit();
            string strAgentPath = axHFCommAgent1.GetApiAgentModulePath();

            if (nRtn != 0)
            {
                MessageBox.Show("통신모듈 초기화 실패!!");
                return;
            }

            nRtn = axHFCommAgent1.CommLogin(strUserID, strUserPwd, strCertPwd);

            if (nRtn == 1)
            {
                MessageBox.Show("로그인 처리 성공했습니다.");
                textLoginID.Enabled = false;
                textLoginPwd.Enabled = false;
                textCertPwd.Enabled = false;

                m_strLoginID = strUserID;
            }
            else
            {
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
            }

            /**********************************
             * 로그인이 완료되면 주문 실시간을 등록한다.
             * 주문 실시간 통보는 사용자ID가 등록키가 된다.
             **********************************/
            //주문확인/체결/미체결(정정/취소) 실시간 통보
            axHFCommAgent1.RegisterReal("IF0", m_strLoginID);
        }

        private void BtnLogout_Click(object sender, EventArgs e)
        {
            Int32 nRtn = axHFCommAgent1.CommLogout(textLoginID.Text);

            if (nRtn == 1)
            {
                MessageBox.Show("로그인아웃 처리 성공했습니다.");
                textLoginID.Enabled = true;
                textLoginPwd.Enabled = true;
                textCertPwd.Enabled = true;
            }
            else
                MessageBox.Show("로그인아웃 처리 실패했습니다.");

            Int32 bSocketClose = 1;
            axHFCommAgent1.CommTerminate(bSocketClose);
        }

        bool SendSellBuyOrder(string strDealSide, Int32 nRqId)
        {
	        string strInRecName = "";
	        string strTrCode = "";
	
	        //입력항목 변수들
	        string strCTNO = "";				//대체종합계좌번호
            string strAPNO = "";				//계좌상품번호
            string strACNT_PWD = "";			//비밀번호
            string strSELL_BUY_DCD = "";		//상품코드
            string strPRDT_CD = "";				//매도매수구분코드
            string strDRVS_NMPR_DCD = "";		//가격조건구분코드
            string strORDR_PRC = "";			//주문가격
            string strORDR_QNT = "";			//주문수량
	        string strPWD_CNFM_YN = "Y";	//비밀번호확인여부
	        string strCVRG_YN = "N";		//반대매매여부
            string strDRVS_ORDR_CND_DCD = "";	//주문조건(' ' : 없음, 'I' : IOC, 'F' : FOK)

	        if (strDealSide == "S") //매도
	        {
		        strTrCode = "OTS2100U10";
		        strSELL_BUY_DCD = "1";
	        }
	        else if (strDealSide == "B") //매수
	        {
		        strTrCode = "OTS2100U20";
		        strSELL_BUY_DCD = "2";
	        }

	        strInRecName = strTrCode + "_in";		//입력 레코드명(리소스파일 참고)

	        string strAccNo;
	        string strAccPwd;

	        strAccNo = textAccNo.Text;
	        strAPNO = textAPNO.Text;				//계좌상품번호
            strCTNO = GetAccAPNO(strAccNo + strAPNO);					//대체종합계좌번호
	        strAccPwd = textPwd.Text;			//비밀번호
	        strACNT_PWD = axHFCommAgent1.GetEncrpyt(strAccPwd);				//계좌비밀번호는 단방향 암호화를 해야된다.
	        strPRDT_CD = textJMCode.Text;		//상품코드

            //파생상품호가구분코드
            //01-지정가;03-시장가;02-조건부지정가;04-최유리지정가;
            switch(comboOrdType.SelectedIndex)
            {
                case 0:
                    strDRVS_NMPR_DCD = "01";
                    break;
                case 1:
                    strDRVS_NMPR_DCD = "03";
                    break;
                case 2:
                    strDRVS_NMPR_DCD = "02";
                    break;
                case 3:
                    strDRVS_NMPR_DCD = "04";
                    break;
            }

	        strORDR_PRC = textOrdPrice.Text;	//주문가격
	        strORDR_QNT = textOrdQty.Text;		//주문수량

            //주문조건(' ' : 없음, 'I' : IOC, 'F' : FOK)
            switch(comboOrdCond.SelectedIndex)
            {
                case 1:
                    strDRVS_ORDR_CND_DCD = "I";
                    break;
                case 2:
                    strDRVS_ORDR_CND_DCD = "F";
                    break;
            }

	        //[2] Tran조회 입력값을 입력한다.
	        axHFCommAgent1.SetTranInputData(nRqId, strTrCode, strInRecName, "CTNO", strCTNO);					//대체종합계좌번호
	        axHFCommAgent1.SetTranInputData(nRqId, strTrCode, strInRecName, "APNO", strAPNO);					//계좌상품번호
	        axHFCommAgent1.SetTranInputData(nRqId, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);			//비밀번호
	        axHFCommAgent1.SetTranInputData(nRqId, strTrCode, strInRecName, "SELL_BUY_DCD", strSELL_BUY_DCD);	//상품코드
	        axHFCommAgent1.SetTranInputData(nRqId, strTrCode, strInRecName, "PRDT_CD", strPRDT_CD);			//매도매수구분코드
	        axHFCommAgent1.SetTranInputData(nRqId, strTrCode, strInRecName, "DRVS_NMPR_DCD", strDRVS_NMPR_DCD);//가격조건구분코드
	        axHFCommAgent1.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_PRC", strORDR_PRC);			//주문가격
	        axHFCommAgent1.SetTranInputData(nRqId, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);			//주문수량
	        axHFCommAgent1.SetTranInputData(nRqId, strTrCode, strInRecName, "PWD_CNFM_YN", strPWD_CNFM_YN);	//비밀번호확인여부
	        axHFCommAgent1.SetTranInputData(nRqId, strTrCode, strInRecName, "CVRG_YN", strCVRG_YN);			//반대매매여부
	        axHFCommAgent1.SetTranInputData(nRqId, strTrCode, strInRecName, "DRVS_ORDR_CND_DCD", strDRVS_ORDR_CND_DCD);	//주문조건(' ' : 없음, 'I' : IOC, 'F' : FOK)

	        string strBenefitAcc = "N";	//수익증권계좌 구분
	        string strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	        string strScreenNo = "9999";	//화면번호
	
	        //[3] 서버에 Tran조회 요청한다.
	        if (axHFCommAgent1.RequestTran(nRqId, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", 0) < 0)
	        {
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
		        return false;
	        }

	        return true;
        }

        Int32 m_nRqIdSellOrd = 0;
        private void buttonSell_Click(object sender, EventArgs e)
        {
            m_nRqIdSellOrd = axHFCommAgent1.CreateRequestID();
            SendSellBuyOrder("S", m_nRqIdSellOrd);	//매도주문 전송
        }

        Int32 m_nRqIdBuyOrd = 0;
        private void buttonBuy_Click(object sender, EventArgs e)
        {
            m_nRqIdBuyOrd = axHFCommAgent1.CreateRequestID();
            SendSellBuyOrder("B", m_nRqIdBuyOrd);	//매도주문 전송
        }

        Int32 m_nRqIdChangeOrd = 0;
        private void buttonChange_Click(object sender, EventArgs e)
        {
            string strTrCode = "OTS2100U30";			//Tran코드(리소스파일 참고)
	        string strInRecName = "OTS2100U30_in";	//입력 레코드명(리소스파일 참고)
	
	        //[1] Request ID생성
	        m_nRqIdChangeOrd = axHFCommAgent1.CreateRequestID();

	        //[2] Tran조회 입력값을 입력한다.
	        string strCTNO = "";				//종합계좌대체번호
	        string strAPNO = "";				//계좌상품번호
	        string strACNT_PWD = "";			//계좌비밀번호
	        string strOR_ORDR_SN = "";			//원주문일련번호
	        string strDRVS_NMPR_DCD = "";		//파생상품호가구분코드
	        string strORDR_PRC = "";			//주문가격
	        string strORDR_QNT = "";			//주문수량
	        string strALL_YN = "";				//전체여부
	        string strDRVS_ORDR_CND_DCD = "";	//파생상품주문조건구분코드
	        string strPWD_CNFM_YN = "Y";	//비밀번호확인여부
	        string strCVRG_YN = "N";		//반대매매여부
	
	        strCTNO = textAccNo.Text;
            strAPNO = textAPNO.Text;				//계좌상품번호
            strCTNO = GetAccAPNO(strCTNO + strAPNO);					//대체종합계좌번호//대체종합계좌번호
	        strACNT_PWD = textPwd.Text;			//비밀번호
	        strACNT_PWD = axHFCommAgent1.GetEncrpyt(strACNT_PWD);						//계좌비밀번호는 단방향 암호화를 해야된다.

	        //원주문번호
	        strOR_ORDR_SN = textOrgOrdNo.Text;
	
	        //가격조건구분코드
            //01-지정가;02-조건부지정가;03-시장가;04-최유리지정가;
            switch(comboOrdType.SelectedIndex)
            {
                case 0:
                    strDRVS_NMPR_DCD = "01";
                    break;
                case 1:
                    strDRVS_NMPR_DCD = "02";
                    break;
                case 2:
                    strDRVS_NMPR_DCD = "03";
                    break;
                case 3:
                    strDRVS_NMPR_DCD = "04";
                    break;
            }

	        //정정가격
	        strORDR_PRC = textOrdPrice.Text;

	        //정정수량
	        strORDR_QNT = textOrdQty.Text;

	        //전체여부
	        if(checkAllQty.Checked == true)
		        strALL_YN = "Y";
	        else
		        strALL_YN = "N";

	
	        //주문조건(' ' : 없음, 'I' : IOC, 'F' : FOK)
            switch(comboOrdCond.SelectedIndex)
            {
                case 1:
                    strDRVS_ORDR_CND_DCD = "I";
                    break;
                case 2:
                    strDRVS_ORDR_CND_DCD = "F";
                    break;
            }

	        axHFCommAgent1.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "CTNO", strCTNO);					//종합계좌대체번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "APNO", strAPNO);					//계좌상품번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);			//계좌비밀번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "OR_ORDR_SN", strOR_ORDR_SN);		//원주문일련번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "DRVS_NMPR_DCD", strDRVS_NMPR_DCD);	//파생상품호가구분코드
	        axHFCommAgent1.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_PRC", strORDR_PRC);			//주문가격
	        axHFCommAgent1.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);			//주문수량
	        axHFCommAgent1.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "ALL_YN", strALL_YN);				//전체여부
	        axHFCommAgent1.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "DRVS_ORDR_CND_DCD", strDRVS_ORDR_CND_DCD);	//파생상품주문조건구분코드
	        axHFCommAgent1.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "PWD_CNFM_YN", strPWD_CNFM_YN);		//비밀번호확인여부
	        axHFCommAgent1.SetTranInputData(m_nRqIdChangeOrd, strTrCode, strInRecName, "CVRG_YN", strCVRG_YN);				//반대매매여부

	        string strBenefitAcc = "N";		//수익증권계좌 구분
	        string strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	        string strScreenNo = "9999";	//화면번호
	
	        //[3] 서버에 Tran조회 요청한다.
	        if (axHFCommAgent1.RequestTran(m_nRqIdChangeOrd, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", 0) < 0)
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        Int32 m_nRqIdCancelOrd = 0;
        private void buttonCancel_Click(object sender, EventArgs e)
        {
	        string strTrCode = "OTS2100U40";			//Tran코드(리소스파일 참고)
	        string strInRecName = "OTS2100U40_in ";	//입력 레코드명(리소스파일 참고)

	        //[1] Request ID생성
	        m_nRqIdCancelOrd = axHFCommAgent1.CreateRequestID();

	        //[2] Tran조회 입력값을 입력한다.
	        string strCTNO = "";			//종합계좌대체번호
	        string strAPNO = "";			//계좌상품번호
	        string strACNT_PWD = "";		//계좌비밀번호
	        string strOR_ORDR_SN = "";		//원주문일련번호
	        string strORDR_QNT = "";		//주문수량
	        string strALL_YN = "";			//전체여부
	        string strPWD_CNFM_YN = "Y";//비밀번호확인여부

	        strCTNO = textAccNo.Text;
	        strAPNO = textAPNO.Text;				//대체종합계좌번호
            strCTNO = GetAccAPNO(strCTNO + strAPNO);
	        strACNT_PWD = textPwd.Text;		//비밀번호
	        strACNT_PWD = axHFCommAgent1.GetEncrpyt(strACNT_PWD);				//계좌비밀번호는 단방향 암호화를 해야된다.

	        //원주문번호
	        strOR_ORDR_SN = textOrgOrdNo.Text;

	        //취소수량
	        strORDR_QNT = textOrdQty.Text;

	        //전체여부
	        if(checkAllQty.Checked == true)
		        strALL_YN = "Y";
	        else
		        strALL_YN = "N";

	        axHFCommAgent1.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "CTNO", strCTNO);		//종합계좌대체번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "APNO", strAPNO);				//계좌상품번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ACNT_PWD", strACNT_PWD);		//계좌비밀번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "OR_ORDR_SN", strOR_ORDR_SN);	//원주문일련번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ORDR_QNT", strORDR_QNT);		//주문수량
	        axHFCommAgent1.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "ALL_YN", strALL_YN);			//전체여부
	        axHFCommAgent1.SetTranInputData(m_nRqIdCancelOrd, strTrCode, strInRecName, "PWD_CNFM_YN", strPWD_CNFM_YN);	//비밀번호확인여부

	        string strBenefitAcc = "N";		//수익증권계좌 구분
	        string strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	        string strScreenNo = "9999";	//화면번호
	
	        //[3] 서버에 Tran조회 요청한다.
	        if (axHFCommAgent1.RequestTran(m_nRqIdCancelOrd, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "U", 0) < 0)
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        Int32 m_nRqIdDepositList = 0;
        private void buttonDepRQ_Click(object sender, EventArgs e)
        {

	        labelEVL_DPST_TOT_AMT.Text = "";	labelEVL_DPST_CSH.Text = "";
	        labelDPST_TOT_AMT.Text = "";		labelDPST_CSH.Text = "";
	        labelDPST_SBST.Text = "";			labelWDRW_PSBL_TOT_AMT.Text = "";
	        labelWDRW_PSBL_CSH.Text = "";		labelWDRW_PSBL_SBST_AMT.Text = "";
	        labelORDR_PSBL_TOT_AMT.Text = "";	labelORDR_PSBL_CSH.Text = "";
	        labelCSGN_WMY_TOT_AMT.Text = "";	labelCSGN_WMY_CSH.Text = "";
	        labelMNMG_TOT_AMT.Text = "";		labelMNMG_CSH.Text = "";
	        labelADIT_WMY_TOT_AMT.Text = "";	labelADIT_WMY_CSH.Text = "";
	        labelEVL_AMT.Text = "";				labelEVL_PFLS.Text = "";
	        labelFEE.Text = "";					labelRCVA.Text = "";
	        labelTHDT_PFLS_AMT.Text = "";

	        // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	        string strTrCode = "OTS2850Q81";				//Tran코드(리소스파일 참고)
	        string strInRecName = "OTS2850Q81_in";			//입력 레코드명(리소스파일 참고)

	        /*-------------------------------*
	         [1] Request ID생성
	        *-------------------------------*/
	        m_nRqIdDepositList = axHFCommAgent1.CreateRequestID();

	        string strCTNO = "";			//종합계좌대체번호
	        string strAPNO = "";			//계좌상품번호
	        string strPWD = "";				//비밀번호
	        string strINQ_DT = "";			//조회일자
	        string strINQ_DVSN = "1";	//조회구분(1:정산전, 2:정산후 -  (1:전체 2:최종거래일이 당영업일이 아닌경우))
	
	        //계좌번호
	        strCTNO = textAccNo.Text;
            
	        //계좌상품번호
	        strAPNO = textAPNO.Text;

            strCTNO = GetAccAPNO(strCTNO + strAPNO);

	        //계좌비번
	        strPWD = textPwd.Text;
	        strPWD = axHFCommAgent1.GetEncrpyt(strPWD); //암호화한다.

	        //조회일자
            DateTime dt = dateTimeDep.Value;
            strINQ_DT = string.Format("{0:D4}{1:D2}{2:D2}", dt.Year, dt.Month, dt.Day);

	        //조회구분(1:정산전, 2:정산후 -  (1:전체 2:최종거래일이 당영업일이 아닌경우))
	        if(radioDep1.Checked == true)
		        strINQ_DVSN = "1";
	        else if(radioDep2.Checked == true)
		        strINQ_DVSN = "2";


	        /*-------------------------------*
	         [2] Tran조회 입력값을 입력한다.
	         *-------------------------------*/
	        axHFCommAgent1.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "CTNO", strCTNO);			//종합계좌대체번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "APNO", strAPNO);			//계좌상품번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "PWD", strPWD);			//비밀번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "INQ_DT", strINQ_DT);		//조회일자
	        axHFCommAgent1.SetTranInputData(m_nRqIdDepositList, strTrCode, strInRecName, "INQ_DVSN", strINQ_DVSN);	//조회구분

	        string strBenefitAcc = "N";	//수익증권계좌 구분
	        string strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	        string strScreenNo = "9999";	//화면번호
	
	        /*-------------------------------*
	         [3] 서버에 Tran조회 요청한다.
	         *-------------------------------*/
	        if(axHFCommAgent1.RequestTran(m_nRqIdDepositList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        private void buttonLoadAcc_Click(object sender, EventArgs e)
        {
            listViewAcc.Items.Clear();
            
            //보유계좌 수를 반환한다.
            Int32 nAccCnt = axHFCommAgent1.GetUserAccCnt();
            string strAccNoPrtd = ""; //종합계좌번호(8) + 상품번호(3)
            string strAccNo = "";	//계좌번호
            string strAPNO = "";	//계좌대체번호
            string strPrdtNo = "";	//계좌상품번호

            listViewAcc.BeginUpdate();

            for (int i = 0; i < nAccCnt; i++)
            {
                //종합계좌번호(8) + 상품번호(3)
                strAccNoPrtd = axHFCommAgent1.GetUserAccNo(i);

                if (strAccNoPrtd == "") continue;
                
                //앞에 8자리는 종합계좌번호
                strAccNo = strAccNoPrtd.Substring(0, 8);

                //뒤에 3자리는 계좌상품번호
                strPrdtNo = strAccNoPrtd.Substring(8, 3);

                strAPNO = GetAccAPNO(strAccNo + strPrdtNo); //종합계좌대체번호

                if (strPrdtNo != "")
                {
                    ListViewItem listViewItem = new ListViewItem(strAccNo);
                    listViewItem.SubItems.Add(strAPNO);
                    listViewItem.SubItems.Add(strPrdtNo);

                    listViewAcc.Items.Add(listViewItem);
                }
            }

            listViewAcc.EndUpdate();
        }


        string[] m_arrAccNo = null;			//계좌목록
        string[] m_arrAccAPNO = null;		//종합계좌대체번호목록
        int m_nAccNoCnt = 0;			//계좌목록
        int m_nAccAPNOCnt = 0;		//종합계좌대체번호목록

        string GetAccAPNO(string strAccNo)
        {
	        string strAPNO = "";

	        //0-리얼, 1-국내모의, 2-해외모의
	        switch (m_nSeverType)
	        {
		        case 0:	//리얼
		        case 1:	//국내모의
		        {
                    strAPNO = axHFCommAgent1.GetAccInfo(0, strAccNo);
		        }
		        break;
		        case 2:	//해외모의
		        {
			        strAccNo.Trim();

			        if (strAccNo.Length > 8)
				        strAccNo = strAccNo.Substring(0, 8);

			        //모의일 때는 모의용 계좌조회 Tran으로 가져온 대체번호를 사용한다.

                    if (m_nAccNoCnt != m_nAccAPNOCnt) return strAPNO;

                    for (int i = 0; i < m_nAccNoCnt; i++)
			        {
				        if (m_arrAccNo[i] == strAccNo)
				        {
					        strAPNO = m_arrAccAPNO[i];
					        break;
				        }
			        }
		        }
		        break;

	        }//End of switch

	        return strAPNO;
        }

        private void buttonAccRQ_Click(object sender, EventArgs e)
        {
            switch (m_nSeverType)
            {
                case 0: //실거래
                    RequestAccList();
                    break;
                case 1: //국내모의
                    buttonLoadAcc.PerformClick();
                    break;
                case 2: //해외모의
                    RequestFDemoAccList();
                    break;
            }
        }

        Int32 m_nRqIdAccNoList = 0;

        void RequestAccList()
        {
	        listViewAcc.Items.Clear();

	        string strTrCode = "HHTACCNM01";	//Tran코드(리소스파일 참고)
	        string strInRecName1 = "InRec1";	//입력 레코드명(리소스파일 참고)
	        string strInRecName2 = "InRec2";	//입력 레코드명(리소스파일 참고)

	        //InRec1 입력
	        string strfunc = "";		//기능구분코드(Q:Query,U:UPDATE,M:Upate and Query)
            string strusid = "";		//사용자아이디
            string strerrc = "";		//에러코드
            string stremsg = "";		//에러메시지
            string strnrec = "";		//입력건수

	        //InRec2 입력
            string straccn = "";		//계좌번호
            string strsub_accn = "";	//대체계좌번호
            string stracnm = "";		//계좌명
            string strachk = "";		//계좌특성(00:기본계좌,01: 화면상에 보이지 않는계좌)
            string strpwch = "";		//은행연계계좌여부

	        /*-------------------------------*
	        [1] Request ID생성
	        *-------------------------------*/
	        m_nRqIdAccNoList = axHFCommAgent1.CreateRequestID();

	        strfunc = "Q";			//기능구분코드(Q:Query,U:UPDATE,M:Upate and Query)
	        strusid = m_strLoginID;	//사용자아이디
	        strnrec = "1";			//입력건수

	        /*InRec1 레코드는 단건 입력이다.*/
	        axHFCommAgent1.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "func", strfunc); //기능구분코드
	        axHFCommAgent1.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "usid", strusid); //사용자아이디
	        axHFCommAgent1.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "errc", strerrc); //에러코드
	        axHFCommAgent1.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "emsg", stremsg); //에러메시지
	        axHFCommAgent1.SetTranInputData(m_nRqIdAccNoList, strTrCode, strInRecName1, "nrec", strnrec); //입력건수

	        /*InRec2 레코드는 복수건 입력이다.*/
	        /*	REC_NAME=InRec2, INOUT=0, ARRAY=3, ARRINFO=InRec1.nrec;
	        ARRAY 가 '0'보다 크면 입력이 복수건이다.	*/
	        axHFCommAgent1.SetTranInputArrayCnt(m_nRqIdAccNoList, strTrCode, strInRecName2, Int32.Parse(strnrec));

	        for (int i = 0; i < Int32.Parse(strnrec); i++)
	        {
		        axHFCommAgent1.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "accn", straccn, i);			//계좌번호
		        axHFCommAgent1.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "sub_accn", strsub_accn, i);	//대체계좌번호
		        axHFCommAgent1.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "acnm", stracnm, i);			//계좌명
		        axHFCommAgent1.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "achk", strachk, i);			//계좌특성
		        axHFCommAgent1.SetTranInputArrayData(m_nRqIdAccNoList, strTrCode, strInRecName2, "pwch", strpwch, i);			//은행연계계좌여부
	        }//End of for

	        string strBenefitAcc = "N";		//수익증권계좌 구분
	        string strPreNext = "0";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	        string strScreenNo = "9999";	//화면번호

	        //[4] 서버에 Tran조회 요청한다.
	        if (axHFCommAgent1.RequestTran(m_nRqIdAccNoList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        Int32 m_nRqIdFDemoAccNoList = 0;
        void RequestFDemoAccList()
        {
            listViewAcc.Items.Clear();

	        string strTrCode = "OTS5991Q03";	//Tran코드(리소스파일 참고)
	        string strInRecName1 = "OTS5991Q03_in";	//입력 레코드명(리소스파일 참고)
	        string strUSR_ID = m_strLoginID;		//사용자ID

	        /*-------------------------------*
		        [1] Request ID생성
	         *-------------------------------*/
	        m_nRqIdFDemoAccNoList = axHFCommAgent1.CreateRequestID();
	        axHFCommAgent1.SetTranInputData(m_nRqIdFDemoAccNoList, strTrCode, strInRecName1, "USR_ID", strUSR_ID);		//사용자ID

	        string strBenefitAcc = "N";	//수익증권계좌 구분
	        string strPreNext = "1";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	        string strScreenNo = "9999";	//화면번호

	        /*-------------------------------*
		        [2] 서버에 Tran조회 요청한다.
	         *-------------------------------*/
	        if (axHFCommAgent1.RequestTran(m_nRqIdFDemoAccNoList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0)
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        string m_strListExecNextRqKey = "";
        Int32 m_nRqIdExecList = 0;
        private void buttonExeRQ_Click(object sender, EventArgs e)
        {
            listViewExe.Items.Clear();
	        m_strListExecNextRqKey = ""; //연속키를 초기화시킨다.

	        string strTrCode = "OTS2850Q80";			//Tran코드(리소스파일 참고)
	        string strInRecName = "OTS2850Q80_in";		//입력 레코드명(리소스파일 참고)
	
	        /*-------------------------------*
		        [1] Request ID생성
	         *-------------------------------*/
	        m_nRqIdExecList = axHFCommAgent1.CreateRequestID();

	        /*-------------------------------*
		        [2] Tran조회 입력값을 입력한다.
	         *-------------------------------*/
	        string strCTNO = "";				//종합계좌대체번호
	        string strAPNO = "";				//계좌상품번호
	        string strPWD = "";					//비밀번호
	        string strORDR_STRT_SN = "";		//주문시작일련번호(필수입력아님)
	        string strINQ_DT = "";				//조회일자
	        string strCNCS_NCNC_DCD = "0";	//체결미체결구분코드(0: 전체, 1: 체결, 2: 미체결)
	        string strINQ_CHNL_DVSN = "0";	//조회채널구분(0: 전체, 1: 영업점, 2: 사이버, 3: 콜센터)
	        string strSORT_DCD = "0";		//정렬구분코드(1: 역순, 그외 값은 정순)

	        //계좌대체번호를 얻어온다.
	        strCTNO = textAccNo.Text;
            
	        //계좌상품번호
	        strAPNO = textAPNO.Text;

            strCTNO = GetAccAPNO(strCTNO + strAPNO); //종합계좌대체번호

	        //계좌비밀번호
	        strPWD = textPwd.Text;
	        strPWD = axHFCommAgent1.GetEncrpyt(strPWD);

	        //조회일자
            DateTime dt = dateTimeExec.Value;
            strINQ_DT = string.Format("{0:D4}{1:D2}{2:D2}", dt.Year, dt.Month, dt.Day);

	        //체결미체결구분코드(0: 전체, 1: 체결, 2: 미체결)
	        if(radioExeOpt1.Checked == true)
		        strCNCS_NCNC_DCD = "0";
	        else if(radioExeOpt2.Checked == true)
		        strCNCS_NCNC_DCD = "1";
	        else if(radioExeOpt3.Checked == true)
		        strCNCS_NCNC_DCD = "2";

	        //정렬구분코드(1: 역순, 그외 값은 정순)
	        if(radioExeSort1.Checked == true)
		        strSORT_DCD = "1";
	        else if(radioExeSort2.Checked == true)
		        strSORT_DCD = "0";

	        axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO);						//종합계좌대체번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strAPNO);						//계좌상품번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD);						//비밀번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_STRT_SN", strORDR_STRT_SN);		//주문시작일련번호(필수입력아님)
	        axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_DT", strINQ_DT);					//조회일자
	        axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CNCS_NCNC_DCD", strCNCS_NCNC_DCD);	//체결미체결구분코드(0: 전체, 1: 체결, 2: 미체결)
	        axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_CHNL_DVSN", strINQ_CHNL_DVSN);	//조회채널구분(0: 전체, 1: 영업점, 2: 사이버, 3: 콜센터)
	        axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "SORT_DCD", strSORT_DCD);				//정렬구분코드(1: 역순, 그외 값은 정순)

	        string strBenefitAcc = "N";	//수익증권계좌 구분
	        string strPreNext = "1";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	        string strScreenNo = "9999";	//화면번호
	        int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	        //[4] 서버에 Tran조회 요청한다.
	        if (axHFCommAgent1.RequestTran(m_nRqIdExecList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", nRequestDataCnt) < 0)
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        private void buttonExeRQNext_Click(object sender, EventArgs e)
        {
            string strTrCode = "OTS2850Q80";			//Tran코드(리소스파일 참고)
            string strInRecName = "OTS2850Q80_in";		//입력 레코드명(리소스파일 참고)

            /*-------------------------------*
                [1] Request ID생성
             *-------------------------------*/
            m_nRqIdExecList = axHFCommAgent1.CreateRequestID();

            /*-------------------------------*
                [2] Tran조회 입력값을 입력한다.
             *-------------------------------*/
            string strCTNO = "";				//종합계좌대체번호
            string strAPNO = "";				//계좌상품번호
            string strPWD = "";					//비밀번호
            string strORDR_STRT_SN = "";		//주문시작일련번호(필수입력아님)
            string strINQ_DT = "";				//조회일자
            string strCNCS_NCNC_DCD = "0";	//체결미체결구분코드(0: 전체, 1: 체결, 2: 미체결)
            string strINQ_CHNL_DVSN = "0";	//조회채널구분(0: 전체, 1: 영업점, 2: 사이버, 3: 콜센터)
            string strSORT_DCD = "0";		//정렬구분코드(1: 역순, 그외 값은 정순)

            //계좌대체번호를 얻어온다.
            strCTNO = textAccNo.Text;
            
            //계좌상품번호
            strAPNO = textAPNO.Text;

            strCTNO = GetAccAPNO(strCTNO + strAPNO); //종합계좌대체번호

            //계좌비밀번호
            strPWD = textPwd.Text;
            strPWD = axHFCommAgent1.GetEncrpyt(strPWD);

            //조회일자
            DateTime dt = dateTimeExec.Value;
            strINQ_DT = String.Format("{0:D4}{1:D2}{2:D2}", dt.Year, dt.Month, dt.Day);

            //체결미체결구분코드(0: 전체, 1: 체결, 2: 미체결)
            if (radioExeOpt1.Checked == true)
                strCNCS_NCNC_DCD = "0";
            else if (radioExeOpt2.Checked == true)
                strCNCS_NCNC_DCD = "1";
            else if (radioExeOpt3.Checked == true)
                strCNCS_NCNC_DCD = "2";

            //정렬구분코드(1: 역순, 그외 값은 정순)
            if (radioExeSort1.Checked == true)
                strSORT_DCD = "1";
            else if (radioExeSort2.Checked == true)
                strSORT_DCD = "0";

            axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CTNO", strCTNO);						//종합계좌대체번호
            axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "APNO", strAPNO);						//계좌상품번호
            axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "PWD", strPWD);						//비밀번호
            axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "ORDR_STRT_SN", strORDR_STRT_SN);		//주문시작일련번호(필수입력아님)
            axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_DT", strINQ_DT);					//조회일자
            axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "CNCS_NCNC_DCD", strCNCS_NCNC_DCD);	//체결미체결구분코드(0: 전체, 1: 체결, 2: 미체결)
            axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "INQ_CHNL_DVSN", strINQ_CHNL_DVSN);	//조회채널구분(0: 전체, 1: 영업점, 2: 사이버, 3: 콜센터)
            axHFCommAgent1.SetTranInputData(m_nRqIdExecList, strTrCode, strInRecName, "SORT_DCD", strSORT_DCD);				//정렬구분코드(1: 역순, 그외 값은 정순)

            string strBenefitAcc = "N";	//수익증권계좌 구분
            string strPreNext = "3";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
            string strScreenNo = "9999";	//화면번호
            int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

            //[4] 서버에 Tran조회 요청한다.
            if (axHFCommAgent1.RequestTran(m_nRqIdExecList, strTrCode, strBenefitAcc, strPreNext, m_strListExecNextRqKey, strScreenNo, "Q", nRequestDataCnt) < 0)
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        string m_strListBalanceNextRqKey;
        Int32 m_nRqIdBalanceList = 0;
        private void buttonBalRQ_Click(object sender, EventArgs e)
        {
            listViewBalance.Items.Clear();
	        m_strListBalanceNextRqKey = ""; //연속키를 초기화시킨다.

	        string strTrCode = "OTS2850Q82";				//Tran코드(리소스파일 참고)
	        string strInRecName1 = "OTS2850Q82_in";	//입력 레코드명(리소스파일 참고)

	        string strCTNO = "";			//대체종합계좌번호
	        string strAPNO = "";			//계좌상품번호
	        string strPWD = "";				//비밀번호
	        string strINQ_DT = "";			//조회일자
	        string strINQ_DVSN = "1";	//조회구분(1:정산전, 2:정산후 -  (1:전체 2:최종거래일이 당영업일이 아닌경우))

	        //계좌대체번호를 얻어온다.
	        strCTNO = textAccNo.Text;

	        //계좌상품번호
	        strAPNO = textAPNO.Text;
            strCTNO = GetAccAPNO(strCTNO + strAPNO); //종합계좌대체번호

	        //계좌비밀번호
	        strPWD = textPwd.Text;
	        strPWD = axHFCommAgent1.GetEncrpyt(strPWD);

            DateTime dt = dateTimeBal.Value;
            strINQ_DT = string.Format("{0:D4}{1:D2}{2:D2}", dt.Year, dt.Month, dt.Day);

	        //조회구분(1:정산전, 2:정산후 -  (1:전체 2:최종거래일이 당영업일이 아닌경우))
	        if(radioBalOpt1.Checked == true)
		        strINQ_DVSN = "1";
	        else if(radioBalOpt2.Checked == true)
		        strINQ_DVSN = "2";


	        /*-------------------------------*
	        [1] Request ID생성
	        *-------------------------------*/
	        m_nRqIdBalanceList = axHFCommAgent1.CreateRequestID();

	        axHFCommAgent1.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "CTNO", strCTNO);			//종합계좌대체번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "APNO", strAPNO);			//계좌상품번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "PWD", strPWD);				//비밀번호
	        axHFCommAgent1.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "INQ_DT", strINQ_DT);		//조회일자
	        axHFCommAgent1.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "INQ_DVSN", strINQ_DVSN);	//조회구분

	        string strBenefitAcc = "N";	//수익증권계좌 구분
	        string strPreNext = "1";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
	        string strScreenNo = "9999";	//화면번호
	        int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

	        //[4] 서버에 Tran조회 요청한다.
	        if (axHFCommAgent1.RequestTran(m_nRqIdBalanceList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", nRequestDataCnt) < 0)
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        private void buttonBalRQNext_Click(object sender, EventArgs e)
        {
            string strTrCode = "OTS2850Q82";				//Tran코드(리소스파일 참고)
            string strInRecName1 = "OTS2850Q82_in";	//입력 레코드명(리소스파일 참고)

            string strCTNO = "";			//대체종합계좌번호
            string strAPNO = "";			//계좌상품번호
            string strPWD = "";				//비밀번호
            string strINQ_DT = "";			//조회일자
            string strINQ_DVSN = "1";	//조회구분(1:정산전, 2:정산후 -  (1:전체 2:최종거래일이 당영업일이 아닌경우))

            //계좌대체번호를 얻어온다.
            strCTNO = textAccNo.Text;
            
            //계좌상품번호
            strAPNO = textAPNO.Text;

            strCTNO = GetAccAPNO(strCTNO + strAPNO); //종합계좌대체번호

            //계좌비밀번호
            strPWD = textPwd.Text;
            strPWD = axHFCommAgent1.GetEncrpyt(strPWD);

            DateTime dt = dateTimeBal.Value;
            strINQ_DT = string.Format("{0:D4}{1:D2}{2:D2}", dt.Year, dt.Month, dt.Day);

            //조회구분(1:정산전, 2:정산후 -  (1:전체 2:최종거래일이 당영업일이 아닌경우))
            if (radioBalOpt1.Checked == true)
                strINQ_DVSN = "1";
            else if (radioBalOpt2.Checked == true)
                strINQ_DVSN = "2";


            /*-------------------------------*
            [1] Request ID생성
            *-------------------------------*/
            m_nRqIdBalanceList = axHFCommAgent1.CreateRequestID();

            axHFCommAgent1.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "CTNO", strCTNO);			//종합계좌대체번호
            axHFCommAgent1.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "APNO", strAPNO);			//계좌상품번호
            axHFCommAgent1.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "PWD", strPWD);				//비밀번호
            axHFCommAgent1.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "INQ_DT", strINQ_DT);		//조회일자
            axHFCommAgent1.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "INQ_DVSN", strINQ_DVSN);	//조회구분

            string strBenefitAcc = "N";	//수익증권계좌 구분
            string strPreNext = "3";		//연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
            string strScreenNo = "9999";	//화면번호
            int nRequestDataCnt = 0; 		//응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

            //[4] 서버에 Tran조회 요청한다.
            if (axHFCommAgent1.RequestTran(m_nRqIdBalanceList, strTrCode, strBenefitAcc, strPreNext, m_strListBalanceNextRqKey, strScreenNo, "Q", nRequestDataCnt) < 0)
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        private void Numeristring(ref string strValue, bool bNotDisplayZero = false)
        {
            strValue = strValue.Trim();
            if(strValue == "")
            {
                if(!bNotDisplayZero)
                    strValue = "0";
                return;
            }

            double fValue = Convert.ToDouble(strValue);
            
            if (strValue.IndexOf('.') != -1)
                strValue = string.Format("{0:G}", fValue);
            else
                strValue = string.Format("{0:0}", fValue);

            if (bNotDisplayZero && Double.Parse(strValue) == 0.0f)
                strValue = "";
        }

        private void axHFCommAgent1_OnGetTranData(object sender, AxHFCommAgentLib._DHFCommAgentEvents_OnGetTranDataEvent e)
        {
            string strTrCode = axHFCommAgent1.GetCommRecvOptionValue((Int32)CommRecvOpt.TranCode);

	        /*	0 : 연속조회 미사용,		1 : 이전 데이터 있음,	2 : 다음 데이터 있음
		        3 : 이전/다음 데이터 있음	*/
            string strPreNext = axHFCommAgent1.GetCommRecvOptionValue((Int32)CommRecvOpt.PrevNextCode);

	        //연속조회키
            string strPreNextContext = axHFCommAgent1.GetCommRecvOptionValue((Int32)CommRecvOpt.PrevNextKey);

	        //조회응답 메시지코드
            string strMsgCode = axHFCommAgent1.GetCommRecvOptionValue((Int32)CommRecvOpt.MsgCode);

	        //조회응답 메시지
            string strMsg = axHFCommAgent1.GetCommRecvOptionValue((Int32)CommRecvOpt.Msg);

	        //조회응답 부가메시지코드
            string strSubMsgCode = axHFCommAgent1.GetCommRecvOptionValue((Int32)CommRecvOpt.SubMsgCode);

	        //조회응답 부가메시지
            string strSubMsg = axHFCommAgent1.GetCommRecvOptionValue((Int32)CommRecvOpt.SubMsg);

            //에러여부( "1" : 에러, "0" : 정상)
            string strIsError = axHFCommAgent1.GetCommRecvOptionValue((Int32)CommRecvOpt.Error);

	        string strErrMsg = axHFCommAgent1.GetLastErrMsg();

	        string strOutRecName;
	        int nRowCnt = 0;

	        /*---------------------------------------------
		        통신 메시지
	         ---------------------------------------------*/
	        if (strErrMsg != "")
		        labelTranMsg.Text = strErrMsg;
	        else
		        labelTranMsg.Text = strMsg;

	        //주문체결내역 조회
	        if (e.nRequestId == m_nRqIdExecList)
	        {
		        /*-------------------------
		          OTS2850Q80_out 단건 출력
		         --------------------------*/
		        string strFTR_SELL_QNT, strFTR_BUY_QNT, strIDX_CLPT_SELL_QNT, strIDX_PTPT_SELL_QNT, strIDX_CLPT_BUY_QNT;
		        string strIDX_PTPT_BUY_QNT, strKOSPI_FTR_SELL_QNT, strKOSPI_FTR_BUY_QNT, strSTK_FTR_SELL_QNT, strSTK_FTR_BUY_QNT;
		        string strSTK_OPT_SELL_QNT, strSTK_OPT_BUY_QNT, strCNCS_FTR_SELL_QNT, strCNCS_FTR_BUY_QNT, strCNCS_IDX_CLPT_SELL_QNT;
		        string strCNCS_IDX_PTPT_SELL_QNT, strCNCS_IDX_CLPT_BUY_QNT, strCNCS_IDX_PTPT_BUY_QNT, strCNCS_KOSPI_FTR_SELL_QNT;
		        string strCNCS_KOSPI_FTR_BUY_QNT, strCNCS_STK_FTR_SELL_QNT, strCNCS_STK_FTR_BUY_QNT, strCNCS_STK_OPT_SELL_QNT;
		        string strCNCS_STK_OPT_BUY_QNT;

		        strFTR_SELL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "FTR_SELL_QNT", 0);				//선물매도수량
		        strFTR_BUY_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "FTR_BUY_QNT", 0);				//선물매수수량
		        strIDX_CLPT_SELL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "FTR_BUY_QNT", 0);			//지수콜옵션매도수량
		        strIDX_PTPT_SELL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_PTPT_SELL_QNT", 0);	//지수풋옵션매도수량
		        strIDX_CLPT_BUY_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_PTPT_SELL_QNT", 0);	//지수콜옵션매수수량
		        strIDX_PTPT_BUY_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "IDX_PTPT_BUY_QNT", 0);		//지수풋옵션매수수량
		        strKOSPI_FTR_SELL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "KOSPI_FTR_SELL_QNT", 0);	//코스피선물매도수량
		        strKOSPI_FTR_BUY_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "KOSPI_FTR_BUY_QNT", 0);	//코스피선물매수수량
		        strSTK_FTR_SELL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_FTR_SELL_QNT", 0);		//주식선물매도수량
		        strSTK_FTR_BUY_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_FTR_BUY_QNT", 0);		//주식선물매수수량
		        strSTK_OPT_SELL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_OPT_SELL_QNT", 0);		//주식옵션매도수량
		        strSTK_OPT_BUY_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "STK_OPT_BUY_QNT", 0);		//주식옵션매수수량
		        strCNCS_FTR_SELL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_FTR_SELL_QNT", 0);	//체결선물매도수량
		        strCNCS_FTR_BUY_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_FTR_BUY_QNT", 0);		//체결선물매수수량
		        strCNCS_IDX_CLPT_SELL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_CLPT_SELL_QNT", 0);		//체결지수콜옵션매도수량
		        strCNCS_IDX_PTPT_SELL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_PTPT_SELL_QNT", 0);		//체결지수풋옵션매도수량
		        strCNCS_IDX_CLPT_BUY_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_CLPT_BUY_QNT", 0);		//체결지수콜옵션매수수량
		        strCNCS_IDX_PTPT_BUY_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_IDX_PTPT_BUY_QNT", 0);		//체결지수풋옵션매수수량
		        strCNCS_KOSPI_FTR_SELL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_KOSPI_FTR_SELL_QNT", 0);	//체결코스피선물매도수량
		        strCNCS_KOSPI_FTR_BUY_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_KOSPI_FTR_BUY_QNT", 0);		//체결코스피선물매수수량
		        strCNCS_STK_FTR_SELL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_FTR_SELL_QNT", 0);		//체결주식선물매도수량
		        strCNCS_STK_FTR_BUY_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_FTR_BUY_QNT", 0);			//체결주식선물매수수량
		        strCNCS_STK_OPT_SELL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_OPT_SELL_QNT", 0);		//체결주식옵션매도수량
		        strCNCS_STK_OPT_BUY_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out", "CNCS_STK_OPT_BUY_QNT", 0);			//체결주식옵션매수수량

		        Numeristring(ref strFTR_SELL_QNT);				//선물매도수량
		        Numeristring(ref strFTR_BUY_QNT);				//선물매수수량
		        Numeristring(ref strIDX_CLPT_SELL_QNT);		//지수콜옵션매도수량
		        Numeristring(ref strIDX_PTPT_SELL_QNT);		//지수풋옵션매도수량
		        Numeristring(ref strIDX_CLPT_BUY_QNT);			//지수콜옵션매수수량
		        Numeristring(ref strIDX_PTPT_BUY_QNT);			//지수풋옵션매수수량
		        Numeristring(ref strKOSPI_FTR_SELL_QNT);		//코스피선물매도수량
		        Numeristring(ref strKOSPI_FTR_BUY_QNT);		//코스피선물매수수량
		        Numeristring(ref strSTK_FTR_SELL_QNT);			//주식선물매도수량
		        Numeristring(ref strSTK_FTR_BUY_QNT);			//주식선물매수수량
		        Numeristring(ref strSTK_OPT_SELL_QNT);			//주식옵션매도수량
		        Numeristring(ref strSTK_OPT_BUY_QNT);			//주식옵션매수수량
		        Numeristring(ref strCNCS_FTR_SELL_QNT);		//체결선물매도수량
		        Numeristring(ref strCNCS_FTR_BUY_QNT);			//체결선물매수수량
		        Numeristring(ref strCNCS_IDX_CLPT_SELL_QNT);	//체결지수콜옵션매도수량
		        Numeristring(ref strCNCS_IDX_PTPT_SELL_QNT);	//체결지수풋옵션매도수량
		        Numeristring(ref strCNCS_IDX_CLPT_BUY_QNT);	//체결지수콜옵션매수수량
		        Numeristring(ref strCNCS_IDX_PTPT_BUY_QNT);	//체결지수풋옵션매수수량
		        Numeristring(ref strCNCS_KOSPI_FTR_SELL_QNT);	//체결코스피선물매도수량
		        Numeristring(ref strCNCS_KOSPI_FTR_BUY_QNT);	//체결코스피선물매수수량
		        Numeristring(ref strCNCS_STK_FTR_SELL_QNT);	//체결주식선물매도수량
		        Numeristring(ref strCNCS_STK_FTR_BUY_QNT);		//체결주식선물매수수량
		        Numeristring(ref strCNCS_STK_OPT_SELL_QNT);	//체결주식옵션매도수량
		        Numeristring(ref strCNCS_STK_OPT_BUY_QNT);		//체결주식옵션매수수량


		        /*-------------------------
		         OTS2850Q80_out_sub01 복수건 출력
		         --------------------------*/
		        string strODNO, strOR_ODNO, strPRDT_CD, strSHTN_PRDT_CD, strPRDT_NM, strSELL_BUY_DVSN_NM;
		        string strDRVS_NMPR_DCD, strNMPR_DCD, strORDR_PRC_AMT, strORDR_QNT, strCNCS_DVSN_NM, strCNCS_QNT;
		        string strCNCS_PRC_AMT, strKOR_CNCS_TM, strRVSE_CNCL_CNFM_QNT, strNCNC_QNT, strDRVS_NMPR_ACPT_DCD;
		        string strDRVS_NMPR_ACPT_DVSN_NM, strEXCG_ACPT_HR, strKRX_MSG_NO, strCOMM_MDIA_DCD_NM, strXTNL_ISTT_RJCT_RSN_CD;

		        listViewExe.BeginUpdate();
		        int nListIndex = 0;

		        /*--------------------------------------
		        다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		        붙여 삽입한다.
		        ---------------------------------------*/
		        int nViewScrollPos = 0;
		        if (m_strListExecNextRqKey != "")
		        {
			        nListIndex = listViewExe.Items.Count;
			        nViewScrollPos = nListIndex;
		        }

		        strOutRecName = "OTS2850Q80_out_sub01";

		        nRowCnt = axHFCommAgent1.GetTranOutputRowCnt(strTrCode, strOutRecName);
		        for (int nRow = 0; nRow < nRowCnt; nRow++)
		        {
			        strODNO = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "ODNO", nRow);		//주문번호
			        strOR_ODNO = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "OR_ODNO", nRow);		//원주문번호
			        strPRDT_CD = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "PRDT_CD", nRow);		//상품코드
			        strSHTN_PRDT_CD = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "SHTN_PRDT_CD", nRow);		//단축상품코드
			        strPRDT_NM = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "PRDT_NM", nRow);		//상품명
			        strSELL_BUY_DVSN_NM = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//매도매수구분명
			        strDRVS_NMPR_DCD = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "DRVS_NMPR_DCD", nRow);		//파생상품호가구분코드
			        strNMPR_DCD = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "NMPR_DCD", nRow);		//호가구분코드
			        strORDR_PRC_AMT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "ORDR_PRC_AMT", nRow);		//주문가격금액
			        strORDR_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "ORDR_QNT", nRow);		//주문수량
			        strCNCS_DVSN_NM = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "CNCS_DVSN_NM", nRow);		//체결구분명
			        strCNCS_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "CNCS_QNT", nRow);		//체결수량
			        strCNCS_PRC_AMT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "CNCS_PRC_AMT", nRow);		//체결가격금액
			        strKOR_CNCS_TM = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "KOR_CNCS_TM", nRow);		//한국체결시간
			        strRVSE_CNCL_CNFM_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "RVSE_CNCL_CNFM_QNT", nRow);		//정정취소확인수량
			        strNCNC_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "NCNC_QNT", nRow);		//미체결수량
			        strDRVS_NMPR_ACPT_DCD = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "DRVS_NMPR_ACPT_DCD", nRow);		//파생상품호가접수구분코드
			        strDRVS_NMPR_ACPT_DVSN_NM = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "DRVS_NMPR_ACPT_DVSN_NM", nRow);		//파생상품호가접수구분명
			        strEXCG_ACPT_HR = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "EXCG_ACPT_HR", nRow);		//거래소접수시간
			        strKRX_MSG_NO = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "KRX_MSG_NO", nRow);		//한국거래소메시지번호
			        strCOMM_MDIA_DCD_NM = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "COMM_MDIA_DCD_NM", nRow);		//통신매체구분코드명
			        strXTNL_ISTT_RJCT_RSN_CD = axHFCommAgent1.GetTranOutputData("OTS2850Q80", "OTS2850Q80_out_sub01", "XTNL_ISTT_RJCT_RSN_CD", nRow);		//외부기관거부사유코드

                    strODNO = strODNO.Trim();							//주문번호
                    strOR_ODNO = strOR_ODNO.Trim();						//원주문번호
                    strPRDT_CD = strPRDT_CD.Trim();						//상품코드
                    strSHTN_PRDT_CD = strSHTN_PRDT_CD.Trim();					//단축상품코드
                    strPRDT_NM = strPRDT_NM.Trim();						//상품명
                    strSELL_BUY_DVSN_NM = strSELL_BUY_DVSN_NM.Trim();				//매도매수구분명
                    strDRVS_NMPR_DCD = strDRVS_NMPR_DCD.Trim();				//파생상품호가구분코드
                    strNMPR_DCD = strNMPR_DCD.Trim();						//호가구분코드
			        Numeristring(ref strORDR_PRC_AMT);			//주문가격금액
			        Numeristring(ref strORDR_QNT);				//주문수량
                    strCNCS_DVSN_NM = strCNCS_DVSN_NM.Trim();					//체결구분명
                    Numeristring(ref strCNCS_QNT);				//체결수량
                    Numeristring(ref strCNCS_PRC_AMT);			//체결가격금액
                    strKOR_CNCS_TM = strKOR_CNCS_TM.Trim();					//한국체결시간
			        Numeristring(ref strRVSE_CNCL_CNFM_QNT);	//정정취소확인수량
			        Numeristring(ref strNCNC_QNT);				//미체결수량
                    strDRVS_NMPR_ACPT_DCD = strDRVS_NMPR_ACPT_DCD.Trim();			//파생상품호가접수구분코드
                    strDRVS_NMPR_ACPT_DVSN_NM = strDRVS_NMPR_ACPT_DVSN_NM.Trim();		//파생상품호가접수구분명
                    strEXCG_ACPT_HR = strEXCG_ACPT_HR.Trim();					//거래소접수시간
                    strKRX_MSG_NO = strKRX_MSG_NO.Trim();					//한국거래소메시지번호
                    strCOMM_MDIA_DCD_NM = strCOMM_MDIA_DCD_NM.Trim();				//통신매체구분코드명
                    strXTNL_ISTT_RJCT_RSN_CD = strXTNL_ISTT_RJCT_RSN_CD.Trim();		//외부기관거부사유코드

			        
                    ListViewItem listViewItem = new ListViewItem(strODNO);

                    listViewItem.SubItems.Add(strOR_ODNO);				//원주문번호
			        listViewItem.SubItems.Add(strPRDT_CD);				//상품코드
			        listViewItem.SubItems.Add(strSHTN_PRDT_CD);			//단축상품코드
			        listViewItem.SubItems.Add(strPRDT_NM);				//상품명
			        listViewItem.SubItems.Add(strSELL_BUY_DVSN_NM);		//매도매수구분명
			        listViewItem.SubItems.Add(strDRVS_NMPR_DCD);		//파생상품호가구분코드
			        listViewItem.SubItems.Add(strNMPR_DCD);				//호가구분코드
			        listViewItem.SubItems.Add(strORDR_PRC_AMT);			//주문가격금액
			        listViewItem.SubItems.Add(strORDR_QNT);				//주문수량
			        listViewItem.SubItems.Add(strCNCS_DVSN_NM);			//체결구분명
			        listViewItem.SubItems.Add(strCNCS_QNT);				//체결수량
			        listViewItem.SubItems.Add(strCNCS_PRC_AMT);			//체결가격금액
			        listViewItem.SubItems.Add(strKOR_CNCS_TM);			//한국체결시간
			        listViewItem.SubItems.Add(strRVSE_CNCL_CNFM_QNT);	//정정취소확인수량
			        listViewItem.SubItems.Add(strNCNC_QNT);				//미체결수량
			        listViewItem.SubItems.Add(strDRVS_NMPR_ACPT_DCD);		//파생상품호가접수구분코드
			        listViewItem.SubItems.Add(strDRVS_NMPR_ACPT_DVSN_NM);	//파생상품호가접수구분명
			        listViewItem.SubItems.Add(strEXCG_ACPT_HR);			//거래소접수시간
			        listViewItem.SubItems.Add(strKRX_MSG_NO);				//한국거래소메시지번호
			        listViewItem.SubItems.Add(strCOMM_MDIA_DCD_NM);		//통신매체구분코드명
			        listViewItem.SubItems.Add(strXTNL_ISTT_RJCT_RSN_CD);	//외부기관거부사유코드

                    listViewExe.Items.Add(listViewItem);
		        }//End of for

                if(nViewScrollPos > 0)
                    listViewExe.EnsureVisible(nViewScrollPos);
		        listViewExe.EndUpdate();
		
		        /*--------------------------------------
		        연속조회키를 저장해 놓는다.
		        ---------------------------------------*/
		        m_strListExecNextRqKey = strPreNextContext;

		        /*--------------------------------------
		        연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
		        ---------------------------------------*/
		        if (strPreNext == "2" || strPreNext == "3")
			        buttonExeRQNext.Enabled = true;
		        else
			        buttonExeRQNext.Enabled = false;

		        /*--------------------------------------
		        반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		        ---------------------------------------*/
		        m_nRqIdExecList = 0;	//주문체결조회 Rq ID

	        }
	        //계좌목록 조회
	        else if (m_nRqIdAccNoList == e.nRequestId)
	        {
		        string strfunc, strusid, strerrc, stremsg, strnrec, straccn, strsub_accn;
		        string stracnm, strachk, strpwch;

		        strfunc = axHFCommAgent1.GetTranOutputData(strTrCode, "OutRec1", "func", 0);		//기능구분코드
		        strusid = axHFCommAgent1.GetTranOutputData(strTrCode, "OutRec1", "usid", 0);		//사용자아이디
		        strerrc = axHFCommAgent1.GetTranOutputData(strTrCode, "OutRec1", "errc", 0);		//에러코드
		        stremsg = axHFCommAgent1.GetTranOutputData(strTrCode, "OutRec1", "emsg", 0);		//에러메시지
		        strnrec = axHFCommAgent1.GetTranOutputData(strTrCode, "OutRec1", "nrec", 0);		//출력건수
		
		        listViewAcc.BeginUpdate();
		        nRowCnt = axHFCommAgent1.GetTranOutputRowCnt(strTrCode, "OutRec2");

		        string strAccNo;
		        string strPrdt;

                m_arrAccNo = null;
                m_arrAccAPNO = null;

                m_arrAccNo      = new string[nRowCnt];
                m_arrAccAPNO    = new string[nRowCnt];

                m_nAccNoCnt = nRowCnt;
                m_nAccAPNOCnt = nRowCnt;

		        for (int nRow = 0; nRow < nRowCnt; nRow++)
		        {
			        straccn = axHFCommAgent1.GetTranOutputData(strTrCode, "OutRec2", "accn", nRow);		//계좌번호
			        strsub_accn = axHFCommAgent1.GetTranOutputData(strTrCode, "OutRec2", "sub_accn", nRow);		//대체계좌번호
			        stracnm = axHFCommAgent1.GetTranOutputData(strTrCode, "OutRec2", "acnm", nRow);		//계좌명
			        strachk = axHFCommAgent1.GetTranOutputData(strTrCode, "OutRec2", "achk", nRow);		//계좌특성
			        strpwch = axHFCommAgent1.GetTranOutputData(strTrCode, "OutRec2", "pwch", nRow);		//은행연계계좌여부

                    straccn = straccn.Trim();
                    strsub_accn = strsub_accn.Trim();
                    stracnm = stracnm.Trim();
                    strachk = strachk.Trim();
                    strpwch = strpwch.Trim();

			        strAccNo = straccn.Substring(0, 8);
			        strPrdt = straccn.Substring(8, 3);

                    m_arrAccNo[nRow] = strAccNo;
                    m_arrAccAPNO[nRow] = strsub_accn;

			        ListViewItem listViewItem = new ListViewItem(strAccNo);

			        listViewItem.SubItems.Add(strsub_accn);
			        listViewItem.SubItems.Add(strPrdt);
			        listViewItem.SubItems.Add(stracnm);
			        listViewItem.SubItems.Add(strachk);
			        listViewItem.SubItems.Add(strpwch);

                    listViewAcc.Items.Add(listViewItem);
		        }

		        if (nRowCnt > 0)
                    listViewAcc.EnsureVisible(0);
		        listViewAcc.EndUpdate();

		        /*--------------------------------------
		        반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		        ---------------------------------------*/
		        m_nRqIdAccNoList = 0;	//계좌목록
	        }
	        //계좌목록 조회
	        else if (m_nRqIdFDemoAccNoList == e.nRequestId)
	        {
                string strCTNO;     //종합계좌대체번호
		        string strCANO;		//종합계좌번호
		        string strAPNO;		//계좌상품번호
		        string strCUST_NM;		//고객명

                listViewAcc.BeginUpdate();

		        nRowCnt = axHFCommAgent1.GetTranOutputRowCnt(strTrCode, "OTS5991Q03_out_sub01");

                m_arrAccNo = null;
                m_arrAccAPNO = null;

                m_arrAccNo = new string[nRowCnt];
                m_arrAccAPNO = new string[nRowCnt];

                m_nAccNoCnt = nRowCnt;
                m_nAccAPNOCnt = nRowCnt;

		        for (int nRow = 0; nRow < nRowCnt; nRow++)
		        {
                    strCTNO = axHFCommAgent1.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CTNO", nRow);		//종합계좌대체번호
			        strCANO = axHFCommAgent1.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CANO", nRow);		//종합계좌번호
			        strAPNO = axHFCommAgent1.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "APNO", nRow);		//계좌상품번호
			        strCUST_NM = axHFCommAgent1.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CUST_NM", nRow);		//고객명

                    strCANO = strCANO.Trim();
                    strCTNO = strCTNO.Trim();
                    strAPNO = strAPNO.Trim();
                    strCUST_NM = strCUST_NM.Trim();

                    m_arrAccNo[nRow] = strCANO;
                    m_arrAccAPNO[nRow] = strCTNO;

			        ListViewItem listViewItem = new ListViewItem(strCANO);
                    listViewItem.SubItems.Add(strCTNO);
			        listViewItem.SubItems.Add(strAPNO);
			        listViewItem.SubItems.Add(strCUST_NM);
			        
                    listViewAcc.Items.Add(listViewItem);
		        }

		        if (nRowCnt > 0)
                    listViewAcc.EnsureVisible(0);
		        listViewAcc.EndUpdate();

		        /*--------------------------------------
		        반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		        ---------------------------------------*/
		        m_nRqIdFDemoAccNoList = 0;	//해외선물데모계좌리스트
	        }
	        //예수금(예탁금) 조회
	        else if (m_nRqIdDepositList == e.nRequestId)
	        {
		        string strEVL_DPST_TOT_AMT, strEVL_DPST_CSH, strDPST_TOT_AMT, strDPST_CSH, strDPST_SBST;
		        string strWDRW_PSBL_TOT_AMT, strWDRW_PSBL_CSH, strWDRW_PSBL_SBST_AMT, strORDR_PSBL_TOT_AMT;
		        string strORDR_PSBL_CSH, strCSGN_WMY_TOT_AMT, strCSGN_WMY_CSH, strMNMG_TOT_AMT, strMNMG_CSH;
		        string strADIT_WMY_TOT_AMT, strADIT_WMY_CSH, strEVL_AMT, strEVL_PFLS, strFEE, strRCVA;
		        string strTHDT_PFLS_AMT;

		        strOutRecName = "OTS2850Q81_out";

		        strEVL_DPST_TOT_AMT		= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "EVL_DPST_TOT_AMT", 0);	//평가예탁총금액
		        strEVL_DPST_CSH			= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "EVL_DPST_CSH", 0);		//평가예탁현금;
		        strDPST_TOT_AMT			= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "DPST_TOT_AMT", 0);		//예탁총금액;
		        strDPST_CSH				= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "DPST_CSH", 0);			//예탁현금;
		        strDPST_SBST			= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "DPST_SBST", 0);			//예탁대용;
		        strWDRW_PSBL_TOT_AMT	= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "WDRW_PSBL_TOT_AMT", 0);	//인출가능총금액;
		        strWDRW_PSBL_CSH		= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "WDRW_PSBL_CSH", 0);		//인출가능현금;
		        strWDRW_PSBL_SBST_AMT	= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "WDRW_PSBL_SBST_AMT", 0);	//인출가능대용금액;
		        strORDR_PSBL_TOT_AMT	= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ORDR_PSBL_TOT_AMT", 0);	//주문가능총금액;
		        strORDR_PSBL_CSH		= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ORDR_PSBL_CSH", 0);		//주문가능현금;
		        strCSGN_WMY_TOT_AMT		= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CSGN_WMY_TOT_AMT", 0);	//위탁증거금총금액;
		        strCSGN_WMY_CSH			= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CSGN_WMY_CSH", 0);		//위탁증거금현금;
		        strMNMG_TOT_AMT			= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "MNMG_TOT_AMT", 0);		//유지증거금총금액;
		        strMNMG_CSH				= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "MNMG_CSH", 0);			//유지증거금현금;
		        strADIT_WMY_TOT_AMT		= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ADIT_WMY_TOT_AMT", 0);	//추가증거금총금액;
		        strADIT_WMY_CSH			= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ADIT_WMY_CSH", 0);		//추가증거금현금;
		        strEVL_AMT				= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "EVL_AMT", 0);			//평가금액;
		        strEVL_PFLS				= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "EVL_PFLS", 0);			//평가손익;
		        strFEE					= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "FEE", 0);				//수수료;
		        strRCVA					= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "RCVA", 0);				//미수금;
		        strTHDT_PFLS_AMT		= axHFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "THDT_PFLS_AMT", 0);		//당일손익금액;
		
		        Numeristring(ref strEVL_DPST_TOT_AMT);
		        Numeristring(ref strEVL_DPST_CSH);
		        Numeristring(ref strDPST_TOT_AMT);
		        Numeristring(ref strDPST_CSH);
		        Numeristring(ref strDPST_SBST);
		        Numeristring(ref strWDRW_PSBL_TOT_AMT);
		        Numeristring(ref strWDRW_PSBL_CSH);
		        Numeristring(ref strWDRW_PSBL_SBST_AMT);
		        Numeristring(ref strORDR_PSBL_TOT_AMT);
		        Numeristring(ref strORDR_PSBL_CSH);
		        Numeristring(ref strCSGN_WMY_TOT_AMT);
		        Numeristring(ref strCSGN_WMY_CSH);
		        Numeristring(ref strMNMG_TOT_AMT);
		        Numeristring(ref strMNMG_CSH);
		        Numeristring(ref strADIT_WMY_TOT_AMT);
		        Numeristring(ref strADIT_WMY_CSH);
		        Numeristring(ref strEVL_AMT);
		        Numeristring(ref strEVL_PFLS);
		        Numeristring(ref strFEE);
		        Numeristring(ref strRCVA);
		        Numeristring(ref strTHDT_PFLS_AMT);
                
		        labelEVL_DPST_TOT_AMT.Text = strEVL_DPST_TOT_AMT;
		        labelEVL_DPST_CSH.Text = strEVL_DPST_CSH;
		        labelDPST_TOT_AMT.Text = strDPST_TOT_AMT;
		        labelDPST_CSH.Text = strDPST_CSH;
		        labelDPST_SBST.Text = strDPST_SBST;
		        labelWDRW_PSBL_TOT_AMT.Text = strWDRW_PSBL_TOT_AMT;
		        labelWDRW_PSBL_CSH.Text = strWDRW_PSBL_CSH;
		        labelWDRW_PSBL_SBST_AMT.Text = strWDRW_PSBL_SBST_AMT;
		        labelORDR_PSBL_TOT_AMT.Text = strORDR_PSBL_TOT_AMT;
		        labelORDR_PSBL_CSH.Text = strORDR_PSBL_CSH;
		        labelCSGN_WMY_TOT_AMT.Text = strCSGN_WMY_TOT_AMT;
		        labelCSGN_WMY_CSH.Text = strCSGN_WMY_CSH;
		        labelMNMG_TOT_AMT.Text = strMNMG_TOT_AMT;
		        labelMNMG_CSH.Text = strMNMG_CSH;
		        labelADIT_WMY_TOT_AMT.Text = strADIT_WMY_TOT_AMT;
		        labelADIT_WMY_CSH.Text = strADIT_WMY_CSH;
		        labelEVL_AMT.Text = strEVL_AMT;
		        labelEVL_PFLS.Text = strEVL_PFLS;
		        labelFEE.Text = strFEE;
		        labelRCVA.Text = strRCVA;
		        labelTHDT_PFLS_AMT.Text = strTHDT_PFLS_AMT;

		        /*--------------------------------------
		          반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		         ---------------------------------------*/
		        m_nRqIdDepositList = 0;	//예수금

	        }
	        //잔고 조회
	        else if (m_nRqIdBalanceList == e.nRequestId)
	        {
		        string strPRDT_CD;				//상품코드;
		        string strSHTN_PRDT_CD;		//단축상품코드;
		        string strPRDT_NM;				//상품명;
		        string strSELL_BUY_DVSN_NM;	//매도매수구분명;
		        string strSELL_BUY_DCD;		//매도매수구분코드;
		        string strUSTL_QNT;			//미결제수량;
		        string strAVR_PRC;				//평균가격;
		        string strNOW_PRC;				//현재가격;
		        string strPRPT;				//대비;
		        string strEVL_AMT;				//평가금액;
		        string strEVL_PFLS;			//평가손익;
		        string strPFLS_RT;				//손익율;
		        string strCLR_PSBL_QNT;		//청산가능수량;
		        string strPCHS_ACBK_AMT;		//매입장부금액;

                listViewBalance.BeginUpdate();
		        int nListIndex = 0;

		        /*--------------------------------------
		          다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		          붙여 삽입한다.
		         ---------------------------------------*/
		        int nViewScrollPos = 0;
		        if (m_strListBalanceNextRqKey != "")
		        {
			        nListIndex = listViewBalance.Items.Count;
			        nViewScrollPos = nListIndex;
		        }

		        nRowCnt = axHFCommAgent1.GetTranOutputRowCnt(strTrCode, "OTS2850Q82_out_sub01");

		        for (int nRow = 0; nRow < nRowCnt; nRow++)
		        {
			        strPRDT_CD = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PRDT_CD", nRow);		//상품코드
			        strSHTN_PRDT_CD = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "SHTN_PRDT_CD", nRow);		//단축상품코드
			        strPRDT_NM = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PRDT_NM", nRow);		//상품명
			        strSELL_BUY_DVSN_NM = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "SELL_BUY_DVSN_NM", nRow);		//매도매수구분명
			        strSELL_BUY_DCD = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "SELL_BUY_DCD", nRow);		//매도매수구분코드
			        strUSTL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "USTL_QNT", nRow);		//미결제수량
			        strAVR_PRC = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "AVR_PRC", nRow);		//평균가격
			        strNOW_PRC = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "NOW_PRC", nRow);		//현재가격
			        strPRPT = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PRPT", nRow);		//대비
			        strEVL_AMT = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "EVL_AMT", nRow);		//평가금액
			        strEVL_PFLS = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "EVL_PFLS", nRow);		//평가손익
			        strPFLS_RT = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PFLS_RT", nRow);		//손익율
			        strCLR_PSBL_QNT = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "CLR_PSBL_QNT", nRow);		//청산가능수량
			        strPCHS_ACBK_AMT = axHFCommAgent1.GetTranOutputData("OTS2850Q82", "OTS2850Q82_out_sub01", "PCHS_ACBK_AMT", nRow);		//매입장부금액

                    strPRDT_CD = strPRDT_CD.Trim();
                    strSHTN_PRDT_CD = strSHTN_PRDT_CD.Trim();
                    strPRDT_NM = strPRDT_NM.Trim();
                    strSELL_BUY_DVSN_NM = strSELL_BUY_DVSN_NM.Trim();
                    strSELL_BUY_DCD = strSELL_BUY_DCD.Trim();
			        Numeristring(ref strUSTL_QNT);
			        Numeristring(ref strAVR_PRC);
			        Numeristring(ref strNOW_PRC);
			        Numeristring(ref strPRPT);
			        Numeristring(ref strEVL_AMT);
			        Numeristring(ref strEVL_PFLS);
			        Numeristring(ref strPFLS_RT);
			        Numeristring(ref strCLR_PSBL_QNT);
			        Numeristring(ref strPCHS_ACBK_AMT);

			        ListViewItem listViewItem = new ListViewItem(strPRDT_CD);

			        listViewItem.SubItems.Add(strSHTN_PRDT_CD);		//단축상품코드;
			        listViewItem.SubItems.Add(strPRDT_NM);			//상품명;
			        listViewItem.SubItems.Add(strSELL_BUY_DVSN_NM);	//매도매수구분명;
			        listViewItem.SubItems.Add(strSELL_BUY_DCD);		//매도매수구분코드;
			        listViewItem.SubItems.Add(strUSTL_QNT);			//미결제수량;
			        listViewItem.SubItems.Add(strAVR_PRC);			//평균가격;
			        listViewItem.SubItems.Add(strNOW_PRC);			//현재가격;
			        listViewItem.SubItems.Add(strPRPT);				//대비;
			        listViewItem.SubItems.Add(strEVL_AMT);			//평가금액;
			        listViewItem.SubItems.Add(strEVL_PFLS);		//평가손익;
			        listViewItem.SubItems.Add(strPFLS_RT);			//손익율;
			        listViewItem.SubItems.Add(strCLR_PSBL_QNT);	//청산가능수량;
			        listViewItem.SubItems.Add(strPCHS_ACBK_AMT);	//매입장부금액;

                    listViewBalance.Items.Add(listViewItem);
		        }

		        if (nViewScrollPos > 0)
                    listViewBalance.EnsureVisible(nViewScrollPos);
		        listViewBalance.EndUpdate();

		        /*--------------------------------------
		        연속조회키를 저장해 놓는다.
		        ---------------------------------------*/
		        m_strListBalanceNextRqKey = strPreNextContext;

		        /*--------------------------------------
		        연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
		        ---------------------------------------*/
		        if (strPreNext == "2" || strPreNext == "3")
			        buttonBalRQNext.Enabled = true;
		        else
			        buttonBalRQNext.Enabled = false;

		        /*--------------------------------------
		        반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		        ---------------------------------------*/
		        m_nRqIdBalanceList = 0;	//주문체결조회 Rq ID

	        }
	        //매도주문 Request ID
	        else if (m_nRqIdSellOrd == e.nRequestId)
	        {
		        string strODRV_ODNO = axHFCommAgent1.GetTranOutputData(strTrCode, "OTS2100U10_out", "ORDR_SN", 0);		//주문번호
		        Numeristring(ref strODRV_ODNO, true);

		        labelOrdNo.Text = strODRV_ODNO;

		        /*--------------------------------------
		          반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		         ---------------------------------------*/
		        m_nRqIdSellOrd = 0;
	        }
	        //매수주문 Request ID
	        else if (m_nRqIdBuyOrd == e.nRequestId)
	        {
		        string strODRV_ODNO = axHFCommAgent1.GetTranOutputData(strTrCode, "OTS2100U20_out", "ORDR_SN", 0);		//주문번호
		        Numeristring(ref strODRV_ODNO, true);

		        labelOrdNo.Text = strODRV_ODNO;

		        /*--------------------------------------
		          반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		         ---------------------------------------*/
		        m_nRqIdBuyOrd = 0;
	        }
	        //정정주문 Request ID
	        else if (m_nRqIdChangeOrd == e.nRequestId)
	        {
		        string strODRV_ODNO = axHFCommAgent1.GetTranOutputData(strTrCode, "OTS2100U30_out", "ORDR_SN", 0);		//주문번호
		        Numeristring(ref strODRV_ODNO, true);

		       labelOrdNo.Text = strODRV_ODNO;

		        /*--------------------------------------
		          반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		         ---------------------------------------*/
		        m_nRqIdChangeOrd = 0;
	        }
	        //취소주문 Request ID
	        else if (m_nRqIdCancelOrd == e.nRequestId)
	        {
		        string strODRV_ODNO = axHFCommAgent1.GetTranOutputData(strTrCode, "OTS2100U40_out", "ORDR_SN", 0);		//주문번호
		        Numeristring(ref strODRV_ODNO, true);

		        labelOrdNo.Text = strODRV_ODNO;

		        /*--------------------------------------
		          반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		         ---------------------------------------*/
		        m_nRqIdCancelOrd = 0;
	        }

	        if (strErrMsg != "")
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        private void listViewAcc_DoubleClick(object sender, EventArgs e)
        {
            string strAccNo = listViewAcc.FocusedItem.SubItems[0].Text;
            string strAccAPNO = listViewAcc.FocusedItem.SubItems[2].Text;

            textAccNo.Text = strAccNo;
            textAPNO.Text = strAccAPNO;
        }

        private void listViewExe_DoubleClick(object sender, EventArgs e)
        {
            string strOrgOrdNo = listViewExe.FocusedItem.SubItems[0].Text;
            string strCode = listViewExe.FocusedItem.SubItems[2].Text;
            string strOrdPrice = listViewExe.FocusedItem.SubItems[8].Text;
            string strOrdQty = listViewExe.FocusedItem.SubItems[15].Text;

            textOrgOrdNo.Text = strOrgOrdNo;
            textJMCode.Text = strCode;
            textOrdPrice.Text = strOrdPrice;
            textOrdQty.Text = strOrdQty;
        }

        private void listViewBalance_DoubleClick(object sender, EventArgs e)
        {
            string strCode = listViewBalance.FocusedItem.SubItems[0].Text;
            string strOrdPrice = listViewBalance.FocusedItem.SubItems[7].Text;
            string strOrdQty = listViewBalance.FocusedItem.SubItems[12].Text;

            textOrgOrdNo.Text = "";
            textJMCode.Text = strCode;
            textOrdPrice.Text = strOrdPrice;
            textOrdQty.Text = strOrdQty;
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void radioSvr1_CheckedChanged(object sender, EventArgs e)
        {
            //0 : 실거래서버, 1 : 국내모의서버, 2 : 해외모의서버
            if (radioSvr1.Checked == true)
            {
                m_nSeverType = 0;
                axHFCommAgent1.SetLoginMode(0, m_nSeverType);
            }
        }

        private void radioSvr2_CheckedChanged(object sender, EventArgs e)
        {
            //0 : 실거래서버, 1 : 국내모의서버, 2 : 해외모의서버
            if (radioSvr2.Checked == true)
            {
                m_nSeverType = 1;
                axHFCommAgent1.SetLoginMode(0, m_nSeverType);
            }
        }

        private void radioSvr3_CheckedChanged(object sender, EventArgs e)
        {
            //0 : 실거래서버, 1 : 국내모의서버, 2 : 해외모의서버
            if (radioSvr3.Checked == true)
            {
                m_nSeverType = 2;
                axHFCommAgent1.SetLoginMode(0, m_nSeverType);
            }
        }

        private void axHFCommAgent1_OnGetRealData(object sender, AxHFCommAgentLib._DHFCommAgentEvents_OnGetRealDataEvent e)
        {
            string strRealMessage = "";
            string strTemp = "";

            /***************************************
             * 지수선물옵션 주문확인/체결/미체결(정정/취소) 실시간 통보
             ****************************************/
            if (e.strRealName == "IF0")
            {
                /*--------------------------------------
                 아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
                 ---------------------------------------*/
                string strsDataType = axHFCommAgent1.GetRealOutputData("IF0", "sDataType");		//데이터구분
                string strsProcTime = axHFCommAgent1.GetRealOutputData("IF0", "sProcTime");		//처리시간
                string strsComCode = axHFCommAgent1.GetRealOutputData("IF0", "sComCode");		//매체구분
                string strsUserID = axHFCommAgent1.GetRealOutputData("IF0", "sUserID");		//사용자ID
                string strsCtno = axHFCommAgent1.GetRealOutputData("IF0", "sCtno");		//계좌대체번호
                string strsAcctNo = axHFCommAgent1.GetRealOutputData("IF0", "sAcctNo");		//계좌번호
                string strsAcctName = axHFCommAgent1.GetRealOutputData("IF0", "sAcctName");		//계좌명
                string strsBidCode = axHFCommAgent1.GetRealOutputData("IF0", "sBidCode");		//주문구분
                string strsModType = axHFCommAgent1.GetRealOutputData("IF0", "sModType");		//정정취소구분
                string strsItemCode = axHFCommAgent1.GetRealOutputData("IF0", "sItemCode");		//단축종목코드
                string strsItemName = axHFCommAgent1.GetRealOutputData("IF0", "sItemName");		//종목명
                string strsOrdVol = axHFCommAgent1.GetRealOutputData("IF0", "sOrdVol");		//주문수량
                string strsOrdPrice = axHFCommAgent1.GetRealOutputData("IF0", "sOrdPrice");		//주문가격
                string strsHogaType = axHFCommAgent1.GetRealOutputData("IF0", "sHogaType");		//호가구분
                string strsOrderCon = axHFCommAgent1.GetRealOutputData("IF0", "sOrderCon");		//주문조건
                string strsBrnNo = axHFCommAgent1.GetRealOutputData("IF0", "sBrnNo");		//지점번호
                string strsOrdNo = axHFCommAgent1.GetRealOutputData("IF0", "sOrdNo");		//주문번호
                string strsOrgOrdNo = axHFCommAgent1.GetRealOutputData("IF0", "sOrgOrdNo");		//원주문번호
                string strsContVol = axHFCommAgent1.GetRealOutputData("IF0", "sContVol");		//체결수량(정정일 경우 정정확인 가격)
                string strsContPrice = axHFCommAgent1.GetRealOutputData("IF0", "sContPrice");		//체결가격(정정일 경우 정정확인 가격)
                string strsRejectCode = axHFCommAgent1.GetRealOutputData("IF0", "sRejectCode");		//거부사유코드
                string strsRejectReason = axHFCommAgent1.GetRealOutputData("IF0", "sRejectReason");		//거부사유
                string strsUnContVol = axHFCommAgent1.GetRealOutputData("IF0", "sUnContVol");		//미체결수량
                string strsFotsTradeUnit = axHFCommAgent1.GetRealOutputData("IF0", "sFotsTradeUnit");		//거래승수(파생만, 선물:50만, 옵션:10만,  실 데이터는 *100000000)
                string strsChegNo = axHFCommAgent1.GetRealOutputData("IF0", "sChegNo");		//체결번호
                string strsFstPrc = axHFCommAgent1.GetRealOutputData("IF0", "sFstPrc");		//근월물 체결가격(스프레드)
                string strsSndPrc = axHFCommAgent1.GetRealOutputData("IF0", "sSndPrc");		//원월물 체결가격(스프레드)
                string strsWrapNo = axHFCommAgent1.GetRealOutputData("IF0", "sWrapNo");		//Wrap주문번호
                string strsGroupNo = axHFCommAgent1.GetRealOutputData("IF0", "sGroupNo");		//그룹번호
                string strsSeqNo = axHFCommAgent1.GetRealOutputData("IF0", "sSeqNo");		//바스켓시퀀스
                string strsFee = axHFCommAgent1.GetRealOutputData("IF0", "sFee");		//수수료
                string strsFiller = axHFCommAgent1.GetRealOutputData("IF0", "sFiller");		//Filler

                strsAcctNo = strsAcctNo.Trim();
                strsItemName = strsItemName.Trim();

                Numeristring(ref strsUnContVol);		//미체결수량
                Numeristring(ref strsContVol);			//체결수량

                //01:체결, 02 : 정정확인, 03 : 취소확인, 04 : 거부, 21 : 접수, 29 : 접수오류(01~21 거래소응답, 29 FEP응답)
                switch (Int32.Parse(strsDataType))
                {
                    case 1:		//체결
                        strTemp = "체결";
                        break;
                    case 2:		//정정확인
                        strTemp = "정정확인";
                        break;
                    case 3:		//취소확인
                        strTemp = "취소확인";
                        break;
                    case 4:		//거부
                        strTemp = "거부";
                        break;
                    case 21:	//접수
                        strTemp = "접수";
                        break;
                    case 29:	//접수오류
                        strTemp = "접수오류";
                        break;
                }//End of switch

                /*--------------------------------------
                조회 시점에 등록한 주식 현재가 실시간키와 동일한지 비교
                ---------------------------------------*/
                if (m_strLoginID == e.strRealKey)
                {
                    strRealMessage = "[" + e.strRealName + "][상태:"+strTemp+"][계좌:"+strsAcctNo+"][상품:"+strsItemName+"][미체결:"+strsUnContVol+"][확인/체결:"+strsContVol+"]";
                }//End of if

            }

            if (strRealMessage != "")
            {
                listViewOrdPush.BeginUpdate();
                int nListRowCnt = listViewOrdPush.Items.Count;

                //데이터 500건이 넘으면 100건만 남기고 지운다.
                if (nListRowCnt > 500)
                {
                    for (int i = 100; i < 500; i++)
                        listViewOrdPush.Items.RemoveAt(i);
                }

                ListViewItem listViewItem = new ListViewItem(strRealMessage);

                listViewOrdPush.Items.Insert(0, listViewItem);
                listViewOrdPush.EndUpdate();
            }
        }

        private void axHFCommAgent1_OnAgentEventHandler(object sender, AxHFCommAgentLib._DHFCommAgentEvents_OnAgentEventHandlerEvent e)
        {
            string strEventMsg;

            switch ((CommEvent)e.nEventType)
            {
                case CommEvent.Connecting:			// 연결중
                    {
                        strEventMsg = "[통신 이벤트] 통신 연결중";
                        MessageBox.Show(strEventMsg);
                    }
                    break;
                case CommEvent.Connected:			// 연결 완료
                    {
                        strEventMsg = "[통신 이벤트] 통신 연결 완료";
                        MessageBox.Show(strEventMsg);
                    }
                    break;
                case CommEvent.Closed:			// 소켓 단절 상태
                case CommEvent.Closing:			// 소켓 단절 중
                case CommEvent.ReconnectRequest:	// 재접속 요청
                    {
                        strEventMsg = "[통신 이벤트] 소켓이 단절되었습니다.";
                        MessageBox.Show(strEventMsg);
                    }
                    break;
                case CommEvent.ConnectFail:		// 소켓 연결 실패
                    {
                        strEventMsg = "[통신 이벤트] 통신연결 실패.";
                        MessageBox.Show(strEventMsg);
                    }
                    break;
                //복수 로그인 메시지
                case CommEvent.NotifyMultiLogin:	// 다중접속 알림 메시지
                    {
                        strEventMsg = "[복수 로그인 이벤트] " + e.strParam;
                        MessageBox.Show(strEventMsg);

                        //nParam 값이 1 이면 연결을 해제하라는 메시지이다.
                        //실제로 해제할지는 API 사용자가 알아서 코딩한다.
                        if (e.nParam == 1)
                        {
                            strEventMsg = "[복수 로그인 이벤트] 다중 접속으로 인한 연결 해제";
                            MessageBox.Show(strEventMsg);
                        }
                    }
                    break;
                case CommEvent.NotifyEmergency:	// 긴급공지 메시지
                    {
                        strEventMsg = "[긴급공지 이벤트] " + e.strParam;
                        MessageBox.Show(strEventMsg);
                    }
                    break;
                case CommEvent.PopUpMsg:        //팝업메시지
                    {
                        strEventMsg = "[팝업 이벤트] " + e.strParam;
                        MessageBox.Show(strEventMsg);
                    }
                    break;
            }//End of switch
        }
    }
}
