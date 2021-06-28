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

namespace CSharpOpenAPI
{
    /***********************************
     * 통신조회 응답 옵션값
     ***********************************/
	enum CommRecvOpt
	{
		TranCode		= 0, //Tr코드
		PrevNextCode	= 1, //연속데이타 구분(0:없음, 1:이전, 2:다음, 3:이전/다음)
		PrevNextKey		= 2, //연속조회키
		MsgCode			= 3, //메시지코드
		Msg				= 4, //메시지
		SubMsgCode		= 5, //부가메시지코드
		SubMsg			= 6  //부가메시지
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

    public partial class IndexFutSiseForm : Form
    {
        Int32 m_nSeverType = 0;

        public IndexFutSiseForm()
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

            InitListCode();
            InitListTick();
            InitListChart();

            radioMin.Checked = true;
            textChartCnt.Text = "60";

            dateFromChart.Format = DateTimePickerFormat.Custom;
            dateFromChart.CustomFormat = "yyyy-MM-dd";

            dateToChart.Format = DateTimePickerFormat.Custom;
            dateToChart.CustomFormat = "yyyy-MM-dd";

            /**********************************
             * 조회Tr, 실시간 통신 I/O 정보 리소스 파일 로드
             **********************************/
            string strApidAgentModulePath = axHFCommAgent1.GetApiAgentModulePath();
            labelCommAgentPath.Text = strApidAgentModulePath;

            /**********************************
             * 접속서버 선택
             **********************************/
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

        //*******************************************************************
        // Function Name : InitListCode
        // Function      : 종목코드리스트
        // Param         : 종목코드리스트 컨트롤 초기화
        // Return        :         void 
        // Create        : 
        // Comment       : 
        //******************************************************************
        void InitListCode()
        {
            int i = 0;
            ColumnHeader[] colHeader = new ColumnHeader[4];

            colHeader[0] = new ColumnHeader();
            colHeader[1] = new ColumnHeader();
            colHeader[2] = new ColumnHeader();
            colHeader[3] = new ColumnHeader();

            colHeader[0].Text = "단축코드";
            colHeader[1].Text = "표준코드";
            colHeader[2].Text = "종목명";
            colHeader[3].Text = "기준가";

            colHeader[0].Width = 80;
            colHeader[1].Width = 80;
            colHeader[2].Width = 80;
            colHeader[3].Width = 80;

            for(i = 0; i < 4 ; i++)
            {
                listViewCode.Columns.Add(colHeader[i]);
            }

        }

        //*******************************************************************
        // Function Name : InitListTick
        // Function      : 시간대별체결리스트  컨트롤 초기화
        // Param         : 
        // Return        :         void 
        // Create        : 
        // Comment       : 
        //******************************************************************
        void InitListTick()
        {
            int i = 0;
            ColumnHeader[] colHeader = new ColumnHeader[5];

            colHeader[0] = new ColumnHeader();
            colHeader[1] = new ColumnHeader();
            colHeader[2] = new ColumnHeader();
            colHeader[3] = new ColumnHeader();
            colHeader[4] = new ColumnHeader();

            colHeader[0].Text = "시간";
            colHeader[1].Text = "체결가";
            colHeader[2].Text = "대비";
            colHeader[3].Text = "등락률";
            colHeader[4].Text = "체결량";

            colHeader[0].Width = 80;
            colHeader[1].Width = 80;
            colHeader[2].Width = 80;
            colHeader[3].Width = 80;
            colHeader[4].Width = 80;

            for (i = 0; i < 5; i++)
            {
                listViewTick.Columns.Add(colHeader[i]);
            }
        }

        //*******************************************************************
        // Function Name : InitListChart
        // Function      : 
        // Param         : 
        // Return        :         void 
        // Create        : 변윤식, 2016/05/30
        // Comment       : 
        //******************************************************************
        void InitListChart()
        {
            int i = 0;
            ColumnHeader[] colHeader = new ColumnHeader[8];

            colHeader[0] = new ColumnHeader();
            colHeader[1] = new ColumnHeader();
            colHeader[2] = new ColumnHeader();
            colHeader[3] = new ColumnHeader();
            colHeader[4] = new ColumnHeader();
            colHeader[5] = new ColumnHeader();
            colHeader[6] = new ColumnHeader();
            colHeader[7] = new ColumnHeader();

            colHeader[0].Text = "일자";
            colHeader[1].Text = "시간";
            colHeader[2].Text = "종가";
            colHeader[3].Text = "시가";
            colHeader[4].Text = "고가";
            colHeader[5].Text = "저가";
            colHeader[6].Text = "체결량";
            colHeader[7].Text = "거래량";

            colHeader[0].Width = 80;
            colHeader[1].Width = 80;
            colHeader[2].Width = 80;
            colHeader[3].Width = 80;
            colHeader[4].Width = 80;
            colHeader[5].Width = 80;
            colHeader[6].Width = 80;
            colHeader[7].Width = 80;

            for (i = 0; i < 8; i++)
            {
                listViewChart.Columns.Add(colHeader[i]);
            }
        }

        //*******************************************************************
        // Function Name : BtnCommInit_Click
        // Function      : 통신모듈 초기화 및 소켓 연결
        // Param         : object sender, EventArgs e
        // Return        :         private void 
        // Create        : 
        // Comment       : 
        //******************************************************************
        private void BtnCommInit_Click(object sender, EventArgs e)
        {

        }

        //*******************************************************************
        // Function Name : BtnCommTerminate_Click
        // Function      : 통신모듈 종료
        // Param         : object sender, EventArgs e
        // Return        :         private void 
        // Create        : 
        // Comment       : 
        //******************************************************************
        private void BtnCommTerminate_Click(object sender, EventArgs e)
        {

        }

        //*******************************************************************
        // Function Name : BtnLogin_Click
        // Function      : 로그인 처리
        // Param         : object sender, EventArgs e
        // Return        :         private void 
        // Create        : 
        // Comment       : 
        //******************************************************************
        private void BtnLogin_Click(object sender, EventArgs e)
        {
            string strUserID = textLoginID.Text;
            string strUserPwd = textLoginPwd.Text;
            string strCertPwd = textCertPwd.Text;

            if(strUserID == "" || strUserPwd == "")
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
                BtnReqCodeList.PerformClick();
            }
            else
            {
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
            }
        }

        //*******************************************************************
        // Function Name : BtnLogout_Click
        // Function      : 로그아웃 처리
        // Param         : object sender, EventArgs e
        // Return        :         private void 
        // Create        : 
        // Comment       : 
        //******************************************************************
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

        string m_strCodeListNextRqKey = "";
        int m_nRqIdCodeList = 0;

        //*******************************************************************
        // Function Name : BtnReqCodeList_Click
        // Function      : 종목코드 리스트를 조회한다.
        // Param         : object sender, EventArgs e
        // Return        :         private void 
        // Create        : 
        // Comment       : 
        //******************************************************************
        private void BtnReqCodeList_Click(object sender, EventArgs e)
        {
            /**********************************
             * 1. 연속조회키 초기화
             **********************************/
            m_strCodeListNextRqKey = "";

            //지수선물 종목 리스트(마스터) 컨트롤 데이터 초기화
            listViewCode.Items.Clear();

            /**********************************
            * 2. 통신조회 Request ID를 생성한다.
            **********************************/
            m_nRqIdCodeList = axHFCommAgent1.CreateRequestID();

            if (m_nRqIdCodeList == -1)
            {
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
                return;
            }

            string strMarketCode;		//시장구분코드
            strMarketCode = "F";	//지수선물

            /**********************************
             * 3. 통신조회 요청 입력데이터
             **********************************/
            axHFCommAgent1.SetFidInputData(m_nRqIdCodeList, "9001", strMarketCode); //시장구분코드
            axHFCommAgent1.SetFidInputData(m_nRqIdCodeList, "GID", "1499");         //GID

            //서버에서 내려받을 출력항목들.
            string strOutputFidList;

            /**********************************
             * 4. 통신조회 응답으로 받을 항목 설정.
             **********************************/
            /* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
            단축코드(1), 표준중목코드(2), 한글종목명(3), 기준가(16) */
            strOutputFidList = "1,2,3,16";

            string strScreenNo;
            strScreenNo = "9999";

            //연속조회 옵션 : '0':미사용, '1'사용, '2' : 이전 데이터 조회, '3' : 다음 데이터 조회
            string strPreNext = "1";

            /**********************************
            * 5. 서버에 통신조회 요청한다.
            **********************************/
            int nReturn = axHFCommAgent1.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, "", strScreenNo, 0);
            if (nReturn < 0)
            {
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
            }
        }

        //*******************************************************************
        // Function Name : BtnReqCodeListNext_Click
        // Function      : 다음 종목코드 리스트를 조회한다.
        // Param         : object sender, EventArgs e
        // Return        :         private void 
        // Create        : 변윤식, 2016/05/27
        // Comment       : 
        //******************************************************************
        private void BtnReqCodeListNext_Click(object sender, EventArgs e)
        {
	        /**********************************
	        * 1. 통신조회 Request ID를 생성한다.
	        **********************************/
	        m_nRqIdCodeList = axHFCommAgent1.CreateRequestID();
	        if (m_nRqIdCodeList == -1)
	        {
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
		        return;
	        }

	        string strMarketCode;		//시장구분코드
	        strMarketCode = "F"; //지수선물

	        /**********************************
	        * 2. 통신조회 요청 입력데이터
	        **********************************/
	        axHFCommAgent1.SetFidInputData(m_nRqIdCodeList, "9001", strMarketCode);	//시장구분코드
	        axHFCommAgent1.SetFidInputData(m_nRqIdCodeList, "GID", "1499");		//GID

	        //통신조회 응답으로 받을 데이터 항목(FID)
	        string strOutputFidList;

	        /**********************************
	        * 3. 통신조회 응답으로 받을 항목 설정.
	        **********************************/
	        /* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	        단축코드(1), 표준중목코드(2), 한글종목명(3), 기준가(16) */
	        strOutputFidList = "1,2,3,16";

	        string strScreenNo;
	        strScreenNo = "9999";

	        string strPreNext = "3"; //다음 데이터 조회

	        /**********************************
	        * 4. 서버에 통신조회 요청한다.
	        **********************************/
	        int nReturn = axHFCommAgent1.RequestFidArray(m_nRqIdCodeList, strOutputFidList, strPreNext, m_strCodeListNextRqKey, strScreenNo, 0);
	        if (nReturn < 0)
		        MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        int m_nRqIdCurPrice = 0;
        string m_strCurPriceRealKey = "";
        string m_strHogaRealKey = "";

        //*******************************************************************
        // Function Name : BtnReqCurPrice_Click
        // Function      : 현재가 조회
        // Param         : object sender, EventArgs e
        // Return        :         private void 
        // Create        : 
        // Comment       : 
        //******************************************************************
        private void BtnReqCurPrice_Click(object sender, EventArgs e)
        {
	        string strSymBol = textCodePrice.Text;			    //종목코드
	        strSymBol.Trim();

	        if (strSymBol == "")
	        {
		        MessageBox.Show("종목코드 입력은 필수입니다!");
		        return;
	        }
	        /**********************************
	        * 1. 통신조회 Request ID를 생성한다.
	        **********************************/
	        m_nRqIdCurPrice = axHFCommAgent1.CreateRequestID();
	        if (m_nRqIdCurPrice == -1)
	        {
		        MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
		        return;
	        }

	        /**********************************
	        * 2. 이전에 등록된 지수선물체결(현재가) 실시간등록 해제.
	        **********************************/
	        if (m_strCurPriceRealKey != "")
	        {
		        string strRealName;
		        strRealName = "F00"; //지수선물체결 Real name

		        axHFCommAgent1.UnRegisterReal(strRealName, m_strCurPriceRealKey);
		        m_strCurPriceRealKey = "";
	        }

	        string strMarketCode;		//시장구분
	        strMarketCode = "F";	//지수옵션

	        //지수옵션체결(현재가) 실시간 등록키로 사용할 리얼키(종목코드)
	        m_strCurPriceRealKey = strSymBol;

	        /**********************************
	        * 3. 통신조회 요청 입력데이터
	        **********************************/
	        axHFCommAgent1.SetFidInputData(m_nRqIdCurPrice, "9001", strMarketCode);	//시장구분코드
	        axHFCommAgent1.SetFidInputData(m_nRqIdCurPrice, "9002", strSymBol);		//종목코드
	        axHFCommAgent1.SetFidInputData(m_nRqIdCurPrice, "GID", "1000");		    //GID

	        //통신조회 응답으로 받을 데이터 항목(FID)
	        string strOutputFidList;

	        /**********************************
	        * 4. 통신조회 응답으로 받을 항목 설정.
	        **********************************/
	        /* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	        현재가(4), 부호(6), 전일대비(5), 대비율(7), 거래량(11)
	        전일거래량(28), 시가(13), 고가(14), 저가(15) */
	        strOutputFidList = "4,6,5,7,11,28,13,14,15";

	        string strScreenNo;
	        strScreenNo = "9999";

	        /**********************************
	        * 5. 서버에 통신조회 요청한다.
	        **********************************/
	        int nReturn = axHFCommAgent1.RequestFid(m_nRqIdCurPrice, strOutputFidList, strScreenNo);

	        if (nReturn < 0)
		        MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        string GetDiffSign(string strSignCode)
        {
	        if (strSignCode == "2")			// 상승
		        return "▲";
	        else if (strSignCode == "1")	// 상한
		        return "↑";
	        else if (strSignCode == "3")	// 보합
		        return "-";
	        else if (strSignCode == "5")	// 하락
		        return "▼";
	        else if (strSignCode == "4")	// 하한가
		        return "↓";

	        return "";
        }

        int m_nRqIdHoga = 0;
        //*******************************************************************
        // Function Name : BtnReqHoga_Click
        // Function      : 호가를 조회
        // Param         : object sender, EventArgs e
        // Return        :         private void 
        // Create        : 
        // Comment       : 
        //******************************************************************
        private void BtnReqHoga_Click(object sender, EventArgs e)
        {
	        string strSymBol;			//종목코드
            strSymBol = textCodeHoga.Text;
	        strSymBol.Trim();
	        if (strSymBol == "")
	        {
                MessageBox.Show("종목코드 입력은 필수입니다!");
		        return;
	        }

	        /**********************************
	        * 1. 통신조회 Request ID를 생성한다.
	        **********************************/
	        m_nRqIdHoga = axHFCommAgent1.CreateRequestID();
	        if (m_nRqIdHoga == -1)
	        {
		        MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
		        return;
	        }

	        /**********************************
	        * 2. 이전에 등록된 지수호가 실시간등록 해제
	        **********************************/
	        if (m_strHogaRealKey != "")
	        {
		        string strRealName;
		        strRealName = "F01";

		        axHFCommAgent1.UnRegisterReal(strRealName, m_strHogaRealKey);
		        m_strHogaRealKey = "";
	        }

	        string strMarketCode;		//시장구분코드
	        strMarketCode = "F";

	        //지수호가 실시간 등록키로 사용할 리얼키(종목코드)
	        m_strHogaRealKey = strSymBol;

	        /**********************************
	        * 3. 통신조회 요청 입력데이터
	        **********************************/
	        axHFCommAgent1.SetFidInputData(m_nRqIdHoga, "9002", strSymBol);		//종목코드
	        axHFCommAgent1.SetFidInputData(m_nRqIdHoga, "9001", strMarketCode);	//시장구분코드
	        axHFCommAgent1.SetFidInputData(m_nRqIdHoga, "GID", "1000");		    //GID

	        /**********************************
	        * 4. 통신조회 응답으로 받을 항목 설정.
	        **********************************/
	        string strSellHoga = "29,30,31,32,33";	//매도 1~5 호가(FID)
	        string strSellRemain = "63,64,65,66,67"; //매도 1~5 호가잔량(FID)
	        string strBuyHoga = "39,40,41,42,43";	//매수 1~5 호가(FID)
	        string strBuyRemain = "73,74,75,76,77"; //매수 1~5 호가 잔량(FID)
	        string strSellCnt = "196,197,198,199,200"; //매도 1~5 호가건수(FID)
	        string strBuyCnt = "201,202,203,204,205"; //매수 1~5 호가건수(FID)

	        /* [ 통신조회 응답으로 받을 데이터 항목(FID) ]*/
	        string strOutputFidList = strSellHoga + "," + strSellRemain + "," + strBuyHoga + "," +
								        strBuyRemain + "," + strSellCnt + "," + strBuyCnt;

	        string strScreenNo;
	        strScreenNo = "9999";

	        /**********************************
	        * 5. 서버에 통신조회 요청한다.
	        **********************************/
	        int nReturn = axHFCommAgent1.RequestFid(m_nRqIdHoga, strOutputFidList, strScreenNo);

	        if (nReturn < 0)
		        MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        string m_strTickNextRqKey = "";
        string m_strTickRealKey = "";
        int m_nRqIdTick = 0;
        //*******************************************************************
        // Function Name : BtnReqTick_Click
        // Function      : 
        // Param         : object sender, EventArgs e
        // Return        :         private void 
        // Create        : 
        // Comment       : 
        //******************************************************************
        private void BtnReqTick_Click(object sender, EventArgs e)
        {
            string strSymBol;			//종목심볼코드
            strSymBol = textCodeTick.Text;
            strSymBol.Trim();

            if (strSymBol == "")
            {
                MessageBox.Show("종목코드 입력은 필수입니다!");
                return;
            }

            /**********************************
            * 1. 연속조회키 초기화
            **********************************/
            m_strTickNextRqKey = "";

            //지수선물 시간대별체결 리스트 컨트롤 데이터 초기화
            listViewTick.Items.Clear();

            /**********************************
            * 2. 통신조회 Request ID를 생성한다.
            **********************************/
            m_nRqIdTick = axHFCommAgent1.CreateRequestID();

            if (m_nRqIdTick == -1)
            {
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
                return;
            }

            /**********************************
            * 3. 이전에 등록된 지수선물체결(현재가) 실시간등록 해제.
            **********************************/
            if (m_strTickRealKey != "")
            {
                string strRealName;
                strRealName = "F00";

                axHFCommAgent1.UnRegisterReal(strRealName, m_strTickRealKey);
                m_strTickRealKey = "";
            }

            string strMarketCode;		//시장구분코드
            strMarketCode = "F";

            //지수선물체결(현재가) 실시간 등록키로 사용할 리얼키(종목코드)
            m_strTickRealKey = strSymBol;

            /**********************************
            * 4. 통신조회 요청 입력데이터
            **********************************/
            axHFCommAgent1.SetFidInputData(m_nRqIdTick, "9002", strSymBol);		//종목심볼
            axHFCommAgent1.SetFidInputData(m_nRqIdTick, "9001", strMarketCode);	//시장구분코드
            axHFCommAgent1.SetFidInputData(m_nRqIdTick, "GID", "1001");		//GID

            //서버에서 내려받을 출력항목들.
            string strOutputFidList;

            /**********************************
            * 5. 통신조회 응답으로 받을 항목 설정.
            **********************************/
            /* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
            시간(8), 체결가(4), 대비(5), 등락률(7), 체결량(83) */
            strOutputFidList = "8,4,5,7,83";

            string strScreenNo;
            strScreenNo = "9999";

            //연속조회 옵션 : '0':미사용, '1'사용, '2' : 이전 데이터 조회, '3' : 다음 데이터 조회
            string strPreNext = "1";

            /**********************************
            * 6. 서버에 통신조회 요청한다.
            **********************************/
            int nReturn = axHFCommAgent1.RequestFidArray(m_nRqIdTick, strOutputFidList, strPreNext, "", strScreenNo, 0);
            if (nReturn < 0)
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        //*******************************************************************
        // Function Name : BtnReqTickNext_Click
        // Function      : 
        // Param         : object sender, EventArgs e
        // Return        :         private void 
        // Create        : 
        // Comment       : 
        //******************************************************************
        private void BtnReqTickNext_Click(object sender, EventArgs e)
        {
            string strSymBol;			//종목심볼코드
            strSymBol = textCodeTick.Text;
            strSymBol.Trim();

            if (strSymBol == "")
            {
                MessageBox.Show("종목코드 입력은 필수입니다!");
                return;
            }

            /**********************************
            * 1. 통신조회 Request ID를 생성한다.
            **********************************/
            m_nRqIdTick = axHFCommAgent1.CreateRequestID();
            if (m_nRqIdTick == -1)
            {
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
                return;
            }

            string strMarketCode;		//시장구분코드
            strMarketCode = "F"; //지수선물

            /**********************************
            * 2. 통신조회 요청 입력데이터
            **********************************/
            axHFCommAgent1.SetFidInputData(m_nRqIdTick, "9002", strSymBol);		//종목심볼
            axHFCommAgent1.SetFidInputData(m_nRqIdTick, "9001", strMarketCode);	//시장구분코드
            axHFCommAgent1.SetFidInputData(m_nRqIdTick, "GID", "1001");		//GID

            //통신조회 응답으로 받을 데이터 항목(FID)
            string strOutputFidList;

            /**********************************
            * 3. 통신조회 응답으로 받을 항목 설정.
            **********************************/
            /* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
            시간(8), 체결가(4), 대비(5), 등락률(7), 체결량(83) */
            strOutputFidList = "8,4,5,7,83";

            string strScreenNo;
            strScreenNo = "9999";

            string strPreNext = "3"; //다음 데이터 조회

            /**********************************
            * 4. 서버에 통신조회 요청한다.
            **********************************/
            int nReturn = axHFCommAgent1.RequestFidArray(m_nRqIdTick, strOutputFidList, strPreNext, m_strTickNextRqKey, strScreenNo, 0);
            if (nReturn < 0)
                MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        string m_strChartNextRqKey = "";
        int m_nRqIdChart = 0;
        //*******************************************************************
        // Function Name : BtnReqChart_Click
        // Function      : 
        // Param         : object sender, EventArgs e
        // Return        :         private void 
        // Create        : 
        // Comment       : 
        //******************************************************************
        private void BtnReqChart_Click(object sender, EventArgs e)
        {
	        string strSymBol;			//종목심볼코드
	        strSymBol = textCodeChart.Text;
	        strSymBol.Trim();

	        if (strSymBol == "")
	        {
		        MessageBox.Show("종목코드 입력은 필수입니다!");
		        return;
	        }

	        /**********************************
	        * 1. 연속조회키 초기화
	        **********************************/
            m_strChartNextRqKey = "";

	        //지수선물 시간대별체결 리스트 컨트롤 데이터 초기화
            listViewChart.Items.Clear();

	        /**********************************
	        * 2. 통신조회 Request ID를 생성한다.
	        **********************************/
	        m_nRqIdChart = axHFCommAgent1.CreateRequestID();

	        if (m_nRqIdChart == -1)
	        {
		        MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
		        return;
	        }

	        string strChartCnt;
            strChartCnt = textChartCnt.Text;
            if (strChartCnt == "")
                strChartCnt = "0";

	        string strMarketCode;		//시장구분코드
	        strMarketCode = "F";

	        /**********************************
	        * 3. 통신조회 요청 입력데이터
	        **********************************/
	        int nRecvCnt = 9999;
	        string strFromDate, strToDate;

            strFromDate = dateFromChart.Text;
            strToDate = dateToChart.Text;

            strFromDate = strFromDate.Replace("-", "");
            strToDate = strToDate.Replace("-", "");

	        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9001", strMarketCode);	//시장구분코드
	        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9002", strSymBol);		//종목심볼
	        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9034", strFromDate);		//시작일
	        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9035", strToDate);		//종료일
            
	        if (radioTick.Checked == true) //틱
	        {
		        if (Convert.ToInt32(strChartCnt) > 0)
		        {
			        nRecvCnt = Convert.ToInt32(strChartCnt);
			        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9119", strChartCnt);	//9119 : 틱 건수
		        }
		
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "GID", "1002"); //GID
	        }
	        else if (radioMin.Checked == true) //분
	        {
		        string strMin;
		        strMin = (Convert.ToInt32(strChartCnt) * 60).ToString();

		        //9119 : 구분코드( 30: 30초, 60: 1분, 600: 10분, 3600: 60분, 60*N: N분 )
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9119", strMin);
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "GID", "1005"); //GID
	        }
	        else if (radioDay.Checked == true) //일
	        {
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "GID", "1007"); //GID

	        }
	        else if (radioWeek.Checked == true) //주
	        {
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9011", "W");				//주(W), 월(M)
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "GID", "1009"); //GID
	        }
	        else if (radioMonth.Checked == true) //월
	        {
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9011", "M");				//주(W), 월(M)
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "GID", "1009"); //GID
	        }

	        //서버에서 내려받을 출력항목들.
	        string strOutputFidList;

	        /**********************************
	        * 4. 통신조회 응답으로 받을 항목 설정.
	        **********************************/
	        /* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	        일자(9), 시간(8), 종가(4), 시가(13), 고가(14), 저가(15), 체결량(83), 거래량(11) */
	        strOutputFidList = "9,8,4,13,14,15,83,11";

	        string strScreenNo;
	        strScreenNo = "9999";

	        //연속조회 옵션 : '0':미사용, '1'사용, '2' : 이전 데이터 조회, '3' : 다음 데이터 조회
	        string strPreNext = "1";

	        /**********************************
	        * 6. 서버에 통신조회 요청한다.
	        **********************************/
	        int nReturn = axHFCommAgent1.RequestFidArray(m_nRqIdChart, strOutputFidList, strPreNext, "", strScreenNo, nRecvCnt);
	        if (nReturn < 0)
		        MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        //*******************************************************************
        // Function Name : BtnReqChartNext_Click
        // Function      : 
        // Param         : object sender, EventArgs e
        // Return        :         private void 
        // Create        : 
        // Comment       : 
        //******************************************************************
        private void BtnReqChartNext_Click(object sender, EventArgs e)
        {
	        string strSymBol;			//종목심볼코드
            strSymBol = textCodeChart.Text;
            strSymBol = strSymBol.Trim();

	        if (strSymBol == "")
	        {
		        MessageBox.Show("종목코드 입력은 필수입니다!");
		        return;
	        }


	        /**********************************
	        * 1. 통신조회 Request ID를 생성한다.
	        **********************************/
	        m_nRqIdChart = axHFCommAgent1.CreateRequestID();
	        if (m_nRqIdChart == -1)
	        {
		        MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
		        return;
	        }

	        string strChartCnt;
            strChartCnt = textChartCnt.Text;
            if (strChartCnt == "")
                strChartCnt = "0";

	        string strMarketCode;		//시장구분코드
	        strMarketCode = "F"; //지수선물

	        /**********************************
	        * 2. 통신조회 요청 입력데이터
	        **********************************/
	        int nRecvCnt = 9999;
	        string strFromDate, strToDate;

            strFromDate = dateFromChart.Text;
            strToDate = dateToChart.Text;

            strFromDate = strFromDate.Replace("-", "");
            strToDate = strToDate.Replace("-", "");

	        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9002", strSymBol);		//종목심볼
	        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9001", strMarketCode);	//시장구분코드
	        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9034", strFromDate);	//시작일
	        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9035", strToDate);	//종료일

	        if (radioTick.Checked == true) //틱
	        {
		        if (Convert.ToInt32(strChartCnt) > 0)
		        {
			        nRecvCnt = Convert.ToInt32(strChartCnt);
			        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9119", strChartCnt);	//9119 : 틱 건수
		        }
		
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "GID", "1002"); //GID
	        }
	        else if (radioMin.Checked == true) //분
	        {
		        string strMin;
		        strMin = (Convert.ToInt32(strChartCnt) * 60).ToString();

		        //9119 : 구분코드( 30: 30초, 60: 1분, 600: 10분, 3600: 60분, 60*N: N분 )
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9119", strMin);
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "GID", "1005"); //GID
	        }
	        else if (radioDay.Checked == true) //일
	        {
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "GID", "1007"); //GID

	        }
	        else if (radioWeek.Checked == true) //주
	        {
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9011", "W");				//주(W), 월(M)
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "GID", "1009"); //GID
	        }
	        else if (radioMonth.Checked == true) //월
	        {
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "9011", "M");				//주(W), 월(M)
		        axHFCommAgent1.SetFidInputData(m_nRqIdChart, "GID", "1009"); //GID
	        }

	        //통신조회 응답으로 받을 데이터 항목(FID)
	        string strOutputFidList;

	        /**********************************
	        * 3. 통신조회 응답으로 받을 항목 설정.
	        **********************************/
	        /* [ 통신조회 응답으로 받을 데이터 항목(FID) ]
	        일자(9), 시간(8), 종가(4), 시가(13), 고가(14), 저가(15), 체결량(83), 거래량(11) */
	        strOutputFidList = "9,8,4,13,14,15,83,11";

	        string strScreenNo;
	        strScreenNo = "9999";

	        string strPreNext = "3"; //다음 데이터 조회

	        /**********************************
	        * 4. 서버에 통신조회 요청한다.
	        **********************************/
	        int nReturn = axHFCommAgent1.RequestFidArray(m_nRqIdChart, strOutputFidList, strPreNext, m_strChartNextRqKey, strScreenNo, nRecvCnt);
	        if (nReturn < 0)
		        MessageBox.Show(axHFCommAgent1.GetLastErrMsg());
        }

        private void listViewCode_DoubleClick(object sender, EventArgs e)
        {
            string strCode = listViewCode.FocusedItem.SubItems[0].Text;
            string strCodeName = listViewCode.FocusedItem.SubItems[2].Text;

            textCodePrice.Text = strCode;
            textCodeHoga.Text = strCode;
            textCodeTick.Text = strCode;
            textCodeChart.Text = strCode;

            BtnReqCurPrice.PerformClick();
            BtnReqHoga.PerformClick();
            BtnReqTick.PerformClick();
            BtnReqChart.PerformClick();

            labelCodeNamePrice.Text = strCodeName;
            labelCodeNameHoga.Text = strCodeName;
            labelCodeNameTick.Text = strCodeName;
            labelCodeNameChart.Text = strCodeName;
        }

        private void radioSvr1_CheckedChanged(object sender, EventArgs e)
        {
            /*----------------------------------
	          접속서버를 설정한다.(0 - 리얼, 1 - 국내모의, 2 - 해외모의)
	         *----------------------------------*/
            m_nSeverType = 0;
            axHFCommAgent1.SetLoginMode(0, m_nSeverType);
        }

        private void radioSvr2_CheckedChanged(object sender, EventArgs e)
        {
            /*----------------------------------
	          접속서버를 설정한다.(0 - 리얼, 1 - 국내모의, 2 - 해외모의)
	         *----------------------------------*/
            m_nSeverType = 1;
            axHFCommAgent1.SetLoginMode(0, m_nSeverType);
        }

        private void radioSvr3_CheckedChanged(object sender, EventArgs e)
        {
            /*----------------------------------
	          접속서버를 설정한다.(0 - 리얼, 1 - 국내모의, 2 - 해외모의)
	         *----------------------------------*/
            m_nSeverType = 2;
            axHFCommAgent1.SetLoginMode(0, m_nSeverType);
        }

        private void axHFCommAgent1_OnGetTranData(object sender, AxHFCommAgentLib._DHFCommAgentEvents_OnGetTranDataEvent e)
        {
            MessageBox.Show("OnGetTranData");
        }

        private void axHFCommAgent1_OnGetFidData(object sender, AxHFCommAgentLib._DHFCommAgentEvents_OnGetFidDataEvent e)
        {
            /* 주의 : OnGetFidData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
                    이벤트 콜백함수 종료 후에는 유효하지 않습니다.*/

            /*	0 : 연속조회 미사용,		1 : 이전 데이터 있음,	2 : 다음 데이터 있음
                3 : 이전/다음 데이터 있음	*/
            string strPreNext = axHFCommAgent1.GetCommRecvOptionValue((Int32)CommRecvOpt.PrevNextCode);

	        //연속조회키
            string strPreNextContext = axHFCommAgent1.GetCommRecvOptionValue((Int32)CommRecvOpt.PrevNextKey);

	        //조회응답 메시지코드
            string strMsgCode = axHFCommAgent1.GetCommRecvOptionValue((Int32)CommRecvOpt.MsgCode);

	        //조회응답 메시지
            string strMsg = axHFCommAgent1.GetCommRecvOptionValue((Int32)CommRecvOpt.Msg);

        	string strErrMsg = axHFCommAgent1.GetLastErrMsg();

	        /***************************************
	        * 지수선물 종목 리스트(마스터) 조회 데이터 수신 처리
	        ****************************************/
	        if (m_nRqIdCodeList == e.nRequestId)
	        {
		        string strCode;			//단축코드
		        string strStandardCode;	//표준코드
		        string strCodeName;		//한글종목명
		        string strPrice;		//기준가

                listViewCode.BeginUpdate();
		        int nListIndex = 0;

		        /*--------------------------------------
		        다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		        붙여 삽입한다.
		        ---------------------------------------*/
		        int nViewScrollPos = 0;
		        if (m_strCodeListNextRqKey != "")
		        {
			        nListIndex = listViewCode.Items.Count;
			        nViewScrollPos = nListIndex;
		        }

		        int nDataCnt = axHFCommAgent1.GetFidOutputRowCnt(e.nRequestId);
		
		        for (int i = 0; i < nDataCnt; i++, nListIndex++)
		        {
			        /*--------------------------------------
			        FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
			        ---------------------------------------*/
			        strCode         = axHFCommAgent1.GetFidOutputData(e.nRequestId, "1", i);	//단축코드
			        strStandardCode = axHFCommAgent1.GetFidOutputData(e.nRequestId, "2", i);	//표준코드
			        strCodeName     = axHFCommAgent1.GetFidOutputData(e.nRequestId, "3", i);	//한글종목명
			        strPrice        = axHFCommAgent1.GetFidOutputData(e.nRequestId, "16", i);   //기준가

                    ListViewItem listViewItem = new ListViewItem(strCode);
                    listViewItem.SubItems.Add(strStandardCode);
                    listViewItem.SubItems.Add(strCodeName);
                    listViewItem.SubItems.Add(strPrice);
                    
			        listViewCode.Items.Add(listViewItem);
		        }//End of for

                if (nViewScrollPos > 0)
                    listViewCode.EnsureVisible(nViewScrollPos);
		        listViewCode.EndUpdate();

		        /*--------------------------------------
		        연속조회키를 저장해 놓는다.
		        ---------------------------------------*/
		        m_strCodeListNextRqKey = strPreNextContext;

		        /*--------------------------------------
		        연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
		        ---------------------------------------*/
		        if (strPreNext == "2" || strPreNext == "3")
                    BtnReqCodeListNext.Enabled = true;
                    
		        else
			        BtnReqCodeListNext.Enabled = false;

		        /*--------------------------------------
		        반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		        ---------------------------------------*/
		        m_nRqIdCodeList = 0;	//지수선물 종목 리스트(마스터) 조회 Request ID
            }
            /***************************************
             * 지수선물 현재가 조회 데이터 수신 처리
             ****************************************/
            else if (m_nRqIdCurPrice == e.nRequestId)
            {
                /*--------------------------------------
                FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
                ---------------------------------------*/
                string strCurPrice = axHFCommAgent1.GetFidOutputData(e.nRequestId, "4", 0);		//현재가
                string strDiffSign = axHFCommAgent1.GetFidOutputData(e.nRequestId, "6", 0);		//부호
                string strDiff = axHFCommAgent1.GetFidOutputData(e.nRequestId, "5", 0);			//전일대비
                string strDiffRate = axHFCommAgent1.GetFidOutputData(e.nRequestId, "7", 0);		//대비율
                string strVolume = axHFCommAgent1.GetFidOutputData(e.nRequestId, "11", 0);		//거래량
                string strPreVolume = axHFCommAgent1.GetFidOutputData(e.nRequestId, "28", 0);	//전일거래량
                string strOpenPrice = axHFCommAgent1.GetFidOutputData(e.nRequestId, "13", 0);	//시가
                string strHighPrice = axHFCommAgent1.GetFidOutputData(e.nRequestId, "14", 0);	//고가
                string strLowPrice = axHFCommAgent1.GetFidOutputData(e.nRequestId, "15", 0);	//저가

                labelCurPrice.Text      = strCurPrice;
                labelCurDiffSign.Text   = GetDiffSign(strDiffSign);
                labelDiff.Text          = strDiff;
                labelDiffRate.Text      = strDiffRate;
                labelVolume.Text        = strVolume;
                labelPrevVolume.Text    = strPreVolume;
                labelOpenPrice.Text     = strOpenPrice;
                labelHighPrice.Text     = strHighPrice;
                labelLowPrice.Text      = strLowPrice;

                /*--------------------------------------
                지선물 체결(현재가) 실시간등록키로 실시간을 등록한다.
                실시간 등록은 첫 조회 시 한번만 한다.
                ---------------------------------------*/
                if (m_strCurPriceRealKey != "")
                {
                    string strRealName;
                    strRealName = "F00";

                    axHFCommAgent1.RegisterReal(strRealName, m_strCurPriceRealKey); //실시간 등록
                }

                /*--------------------------------------
                반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
                ---------------------------------------*/
                m_nRqIdCurPrice = 0;	//지수선물 현재가 조회 Request ID
            }
           /***************************************
	        * 지수선물 5단계호가 조회 데이터 수신 처리
	        ****************************************/
	        else if (m_nRqIdHoga == e.nRequestId)
	        {
		        string[] arrSellHoga = new string[5];
		        string[] arrBuyHoga = new string[5];

		        string[] arrSellRemain = new string[5];
		        string[] arrBuyRemain = new string[5];

		        string[] arrSellCnt = new string[5];
                string[] arrBuyCnt = new string[5];

		        /*--------------------------------------
		         FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
		        ---------------------------------------*/
		        //매도호가/잔량
		        arrSellHoga[0] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "29", 0);	//매도 1호가
		        arrSellHoga[1] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "30", 0);	//매도 2호가
		        arrSellHoga[2] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "31", 0);	//매도 3호가
		        arrSellHoga[3] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "32", 0);	//매도 4호가
		        arrSellHoga[4] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "33", 0);	//매도 5호가
		        arrSellRemain[0] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "63", 0);	//매도 1호가잔량
		        arrSellRemain[1] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "64", 0);	//매도 2호가잔량
		        arrSellRemain[2] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "65", 0);	//매도 3호가잔량
		        arrSellRemain[3] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "66", 0);	//매도 4호가잔량
		        arrSellRemain[4] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "67", 0);	//매도 5호가잔량
		        arrSellCnt[0] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "196", 0);	//매도 1호가건수
		        arrSellCnt[1] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "197", 0);	//매도 2호가건수
		        arrSellCnt[2] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "198", 0);	//매도 3호가건수
		        arrSellCnt[3] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "199", 0);	//매도 4호가건수
		        arrSellCnt[4] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "200", 0);	//매도 5호가건수

		        //매수호가/잔량
                arrBuyHoga[0] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "39", 0);		//매수 1호가
                arrBuyHoga[1] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "40", 0);		//매수 2호가
                arrBuyHoga[2] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "41", 0);		//매수 3호가
                arrBuyHoga[3] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "42", 0);		//매수 4호가
                arrBuyHoga[4] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "43", 0);		//매수 5호가
                arrBuyRemain[0] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "73", 0);	//매수 1호가잔량
                arrBuyRemain[1] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "74", 0);	//매수 2호가잔량
                arrBuyRemain[2] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "75", 0);	//매수 3호가잔량
                arrBuyRemain[3] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "76", 0);	//매수 4호가잔량
                arrBuyRemain[4] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "77", 0);	//매수 5호가잔량
                arrBuyCnt[0] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "201", 0);		//매수 1호가건수
                arrBuyCnt[1] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "202", 0);		//매수 2호가건수
                arrBuyCnt[2] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "203", 0);		//매수 3호가건수
                arrBuyCnt[3] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "204", 0);		//매수 4호가건수
                arrBuyCnt[4] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "205", 0);		//매수 5호가건수

		        /*--------------------------------------
		        조회된 수신 데이터를 화면 컨트롤에 표시한다.
		        ---------------------------------------*/
		        SetHogaData(arrSellHoga, arrBuyHoga, arrSellRemain, arrBuyRemain, arrSellCnt, arrBuyCnt);

		        /*--------------------------------------
		        지수선물호가 실시간키로 실시간을 등록한다.
		        실시간 등록은 첫 조회 시 한번만 한다.
		        ---------------------------------------*/
		        if (m_strHogaRealKey != "")
		        {
			        string strRealName;
			        strRealName = "F01";

			        axHFCommAgent1.RegisterReal(strRealName, m_strHogaRealKey); //실시간 등록
		        }

		        /*--------------------------------------
		        반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		        ---------------------------------------*/
		        m_nRqIdHoga = 0;	//지수선물 5단계호가 조회 Request ID
	        }
            /***************************************
             * 지수선물 시간대별체결 조회 데이터 수신 처리
             ****************************************/
            else if (m_nRqIdTick == e.nRequestId)
            {
                string strTime;		//시간
                string strPrice;		//체결가
                string strDiff;		//대비
                string strDiffRate;	//등률
                string strVolume;		//체결량

                listViewTick.BeginUpdate();

                int nListIndex = 0;

                /*--------------------------------------
                다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
                붙여 삽입한다.
                ---------------------------------------*/
                int nViewScrollPos = 0;
                if (m_strTickNextRqKey != "")
                {
                    nListIndex = listViewTick.Items.Count;
                    nViewScrollPos = nListIndex;
                }

                int nDataCnt = axHFCommAgent1.GetFidOutputRowCnt(e.nRequestId);

                for (int i = 0; i < nDataCnt; i++, nListIndex++)
                {
                    /*--------------------------------------
                    FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
                    ---------------------------------------*/
                    strTime = axHFCommAgent1.GetFidOutputData(e.nRequestId, "8", i);	//시간
                    strPrice = axHFCommAgent1.GetFidOutputData(e.nRequestId, "4", i);	//체결가
                    strDiff = axHFCommAgent1.GetFidOutputData(e.nRequestId, "5", i);	//대비
                    strDiffRate = axHFCommAgent1.GetFidOutputData(e.nRequestId, "7", i);	//등률
                    strVolume = axHFCommAgent1.GetFidOutputData(e.nRequestId, "83", i);//체결량

                    ListViewItem listViewItem = new ListViewItem(strTime);
                    listViewItem.SubItems.Add(strPrice);
                    listViewItem.SubItems.Add(strDiff);
                    listViewItem.SubItems.Add(strDiffRate);
                    listViewItem.SubItems.Add(strVolume);

                    listViewTick.Items.Add(listViewItem);
                }

                if(nViewScrollPos > 0)
                    listViewTick.EnsureVisible(nViewScrollPos);
                listViewTick.EndUpdate();

                /*--------------------------------------
                선물체결 실시간을 등록한다.
                실시간 등록은 첫 조회 시 한번만 한다.
                ---------------------------------------*/
                if (m_strTickRealKey != "" && m_strTickNextRqKey == "")
                {
                    string strRealName;
                    strRealName = "F00";

                    axHFCommAgent1.RegisterReal(strRealName, m_strTickRealKey); //실시간 등록
                }

                /*--------------------------------------
                연속조회키를 저장해 놓는다.
                ---------------------------------------*/
                m_strTickNextRqKey = strPreNextContext;

                /*--------------------------------------
                연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
                ---------------------------------------*/
                if (strPreNext == "2" || strPreNext == "3")
                    BtnReqTickNext.Enabled = true;
                else
                    BtnReqTickNext.Enabled = false;

                /*--------------------------------------
                반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
                ---------------------------------------*/
                m_nRqIdTick = 0;	//지수선물 시간대별체결 조회 Request ID

            }
            /***************************************
	         * 지수선물 차트 조회 데이터 수신 처리
	         ****************************************/
	        else if (m_nRqIdChart == e.nRequestId)
	        {
		        string[] arrItem = new string[8];

                listViewChart.BeginUpdate();

		        int nListIndex = 0;
		        int nViewScrollPos = 0;

		        /*--------------------------------------
		        다음 조회 데이터 수신이면 이전에 받은 데이타 뒤에
		        붙여 삽입한다.
		        ---------------------------------------*/
		        if (m_strChartNextRqKey != "")
		        {
			        nListIndex = listViewChart.Items.Count;
			        nViewScrollPos = nListIndex;
		        }

                /***************************************
		        * 에이전트 컨트롤을 통해 간적접으로 항목별 데이타를 빼낸다.
		        ****************************************/
                int nDataCnt = axHFCommAgent1.GetFidOutputRowCnt(e.nRequestId);
                
		        for (int i = 0; i < nDataCnt; i++, nListIndex++)
		        {
			        /*--------------------------------------
			        FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
			        ---------------------------------------*/
                    arrItem[0] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "9", i);	    //0009 : 일자
                    arrItem[1] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "8", i);	    //0008 : 시간
                    arrItem[2] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "4", i);	    //0004 : 종가
                    arrItem[3] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "13", i);	//0013 : 시가
                    arrItem[4] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "14", i);	//0014 : 고가
                    arrItem[5] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "15", i);	//0015 : 저가
                    arrItem[6] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "83", i);	//0083 : 체결량
                    arrItem[7] = axHFCommAgent1.GetFidOutputData(e.nRequestId, "11", i);	//0011 : 거래량


                    ListViewItem listViewItem = new ListViewItem(arrItem[0]);

			        //리스트 컨트롤에 항목별 데이타 입력
			        for (int col = 1; col < 8; col++)
			        {
                        listViewItem.SubItems.Add(arrItem[col]);
			        }

                    listViewChart.Items.Add(listViewItem);

		        }//End of for
        
                if(nViewScrollPos > 0)
                    listViewChart.EnsureVisible(nViewScrollPos);
                listViewChart.EndUpdate();

		        /*--------------------------------------
		        연속조회키를 저장해 놓는다.
		        ---------------------------------------*/
		        m_strChartNextRqKey = strPreNextContext;

		        /*--------------------------------------
		        연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
		        ---------------------------------------*/
		        if (strPreNext == "2" || strPreNext == "3")
                    BtnReqChartNext.Enabled = true;
		        else
                    BtnReqChartNext.Enabled = false;

		        /*--------------------------------------
		        반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
		        ---------------------------------------*/
		        m_nRqIdChart = 0;	//지수선물 종목 리스트(마스터) 조회 Request ID

	        }//End of if

            if (strErrMsg != "")
            {
                MessageBox.Show(strErrMsg);
            }
        }

        void SetHogaData(string[] arrSellHoga, string[] arrBuyHoga, string[] arrSellRemain,
	                                        string[] arrBuyRemain, string[] arrSellCnt, string[] arrBuyCnt)
        {
	        //공백문자 제거
	        arrSellHoga[0] = arrSellHoga[0].Trim();		arrSellHoga[1] = arrSellHoga[1].Trim();
	        arrSellHoga[2] = arrSellHoga[2].Trim();		arrSellHoga[3] = arrSellHoga[3].Trim();
	        arrSellHoga[4] = arrSellHoga[4].Trim();

	        arrSellRemain[0] = arrSellRemain[0].Trim();	arrSellRemain[1] = arrSellRemain[1].Trim();
	        arrSellRemain[2] = arrSellRemain[2].Trim();	arrSellRemain[3] = arrSellRemain[3].Trim();
	        arrSellRemain[4] = arrSellRemain[4].Trim();

	        arrBuyHoga[0] = arrBuyHoga[0].Trim();		arrBuyHoga[1] = arrBuyHoga[1].Trim();
	        arrBuyHoga[2] = arrBuyHoga[2].Trim();		arrBuyHoga[3] = arrBuyHoga[3].Trim();
	        arrBuyHoga[4] = arrBuyHoga[4].Trim();

	        arrBuyRemain[0] = arrBuyRemain[0].Trim();	arrBuyRemain[1] = arrBuyRemain[1].Trim();
	        arrBuyRemain[2] = arrBuyRemain[2].Trim();	arrBuyRemain[3] = arrBuyRemain[3].Trim();
	        arrBuyRemain[4] = arrBuyRemain[4].Trim();

	        arrSellCnt[0] = arrSellCnt[0].Trim();		arrSellCnt[1] = arrSellCnt[1].Trim();
	        arrSellCnt[2] = arrSellCnt[2].Trim();		arrSellCnt[3] = arrSellCnt[3].Trim();
	        arrSellCnt[4] = arrSellCnt[4].Trim();

	        arrBuyCnt[0] = arrBuyCnt[0].Trim();	    	arrBuyCnt[1] = arrBuyCnt[1].Trim();
	        arrBuyCnt[2] = arrBuyCnt[2].Trim();	    	arrBuyCnt[3] = arrBuyCnt[3].Trim();
	        arrBuyCnt[4] = arrBuyCnt[4].Trim();

	        //매도호가 컨트롤 입력
            labelSell1.Text = arrSellHoga[0];
	        labelSell2.Text = arrSellHoga[1];
	        labelSell3.Text = arrSellHoga[2];
	        labelSell4.Text = arrSellHoga[3];
	        labelSell5.Text = arrSellHoga[4];
            
	        //매도호가잔량 컨트롤 입력
	        labelSellRemain1.Text = arrSellRemain[0];
	        labelSellRemain2.Text = arrSellRemain[1];
	        labelSellRemain3.Text = arrSellRemain[2];
	        labelSellRemain4.Text = arrSellRemain[3];
	        labelSellRemain5.Text = arrSellRemain[4];
            
	        //매도호가건수 컨트롤 입력
	        labelSellCnt1.Text = arrSellRemain[0];
	        labelSellCnt2.Text = arrSellRemain[1];
	        labelSellCnt3.Text = arrSellRemain[2];
	        labelSellCnt4.Text = arrSellRemain[3];
	        labelSellCnt5.Text = arrSellRemain[4];

	        //매수호가 컨트롤 입력
	        labelBuy1.Text = arrBuyHoga[0];
	        labelBuy2.Text = arrBuyHoga[1];
	        labelBuy3.Text = arrBuyHoga[2];
	        labelBuy4.Text = arrBuyHoga[3];
	        labelBuy5.Text = arrBuyHoga[4];
            
	        //매수호가잔량 컨트롤 입력
	        labelBuyRemain1.Text = arrBuyRemain[0];
	        labelBuyRemain2.Text = arrBuyRemain[1];
	        labelBuyRemain3.Text = arrBuyRemain[2];
	        labelBuyRemain4.Text = arrBuyRemain[3];
	        labelBuyRemain5.Text = arrBuyRemain[4];

	        //매수호가건수 컨트롤 입력
	        labelBuyCnt1.Text = arrSellRemain[0];
	        labelBuyCnt2.Text = arrSellRemain[1];
	        labelBuyCnt3.Text = arrSellRemain[2];
	        labelBuyCnt4.Text = arrSellRemain[3];
	        labelBuyCnt5.Text = arrSellRemain[4];
        }

        private void axHFCommAgent1_OnGetRealData(object sender, AxHFCommAgentLib._DHFCommAgentEvents_OnGetRealDataEvent e)
        {
           	/***************************************
        	 * 지수선물 호가 실시간 데이터 수신
        	 ****************************************/
	        if (e.strRealName == "F01")
	        {
		        /*--------------------------------------
		        조회 시점에 등록한 지수선물 호가 실시간키와 동일한지 비교
		        ---------------------------------------*/
		        if (m_strHogaRealKey == e.strRealKey)
		        {
			        string[] arrSellHoga = new string[5];
			        string[] arrBuyHoga = new string[5];

			        string[] arrSellRemain = new string[5];
			        string[] arrBuyRemain = new string[5];

			        string[] arrSellCnt = new string[5];
			        string[] arrBuyCnt = new string[5];

			        /*--------------------------------------
			         아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
			         ---------------------------------------*/
			        //매도 1~5호가
			        arrSellHoga[0] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP1");
                    arrSellHoga[1] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP2");
                    arrSellHoga[2] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP3");
                    arrSellHoga[3] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP4");
                    arrSellHoga[4] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP5");
			        //매도 1~5호가잔량
                    arrSellRemain[0] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP_RSQN1");
                    arrSellRemain[1] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP_RSQN2");
                    arrSellRemain[2] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP_RSQN3");
                    arrSellRemain[3] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP_RSQN4");
                    arrSellRemain[4] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP_RSQN5");
			        //매도 1~5호가건수
                    arrSellCnt[0] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP_CSNU1");
                    arrSellCnt[1] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP_CSNU2");
                    arrSellCnt[2] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP_CSNU3");
                    arrSellCnt[3] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP_CSNU4");
                    arrSellCnt[4] = axHFCommAgent1.GetRealOutputData(e.strRealName, "ASKP_CSNU5");

			        //매수 1~5호가
                    arrBuyHoga[0] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP1");
                    arrBuyHoga[1] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP2");
                    arrBuyHoga[2] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP3");
                    arrBuyHoga[3] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP4");
                    arrBuyHoga[4] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP5");
			        //매수 1~5호가잔량
                    arrBuyRemain[0] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP_RSQN1");
                    arrBuyRemain[1] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP_RSQN2");
                    arrBuyRemain[2] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP_RSQN3");
                    arrBuyRemain[3] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP_RSQN4");
                    arrBuyRemain[4] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP_RSQN5");
			        //매수 1~5호가건수
                    arrBuyCnt[0] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP_CSNU1");
                    arrBuyCnt[1] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP_CSNU2");
                    arrBuyCnt[2] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP_CSNU3");
                    arrBuyCnt[3] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP_CSNU4");
                    arrBuyCnt[4] = axHFCommAgent1.GetRealOutputData(e.strRealName, "BIDP_CSNU5");

			        SetHogaData(arrSellHoga, arrBuyHoga, arrSellRemain, arrBuyRemain, arrSellCnt, arrBuyCnt);
		        }//End of if
	        }
	        /***************************************
	        * 지수선물 체결(현재가) 실시간 데이터 수신
	        ****************************************/
            else if (e.strRealName == "F00")
	        {
		        /*--------------------------------------
		        아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
		        ---------------------------------------*/
                string strCurPrice = axHFCommAgent1.GetRealOutputData(e.strRealName, "PRPR");			//현재가
                string strDiffSign = axHFCommAgent1.GetRealOutputData(e.strRealName, "PRDY_VRSS_SIGN");	//부호
                string strDiff = axHFCommAgent1.GetRealOutputData(e.strRealName, "PRDY_VRSS");		//전일대비
                string strDiffRate = axHFCommAgent1.GetRealOutputData(e.strRealName, "PRDY_CTRT");		//대비율
                string strVolume = axHFCommAgent1.GetRealOutputData(e.strRealName, "ACML_VOL");		//거래량

                string strOpenPrice = axHFCommAgent1.GetRealOutputData(e.strRealName, "OPRC");			//시가
                string strHighPrice = axHFCommAgent1.GetRealOutputData(e.strRealName, "HGPR");			//고가
                string strLowPrice = axHFCommAgent1.GetRealOutputData(e.strRealName, "LWPR");			//저가

                string strTime = axHFCommAgent1.GetRealOutputData(e.strRealName, "BSOP_HOUR");		//체결시간
                string strExecVolume = axHFCommAgent1.GetRealOutputData(e.strRealName, "CNTG_VOL");		//체결량

                strCurPrice = strCurPrice.Trim();
                strDiffSign = strDiffSign.Trim();
                strDiff = strDiff.Trim();
                strDiffRate = strDiffRate.Trim();
                strVolume = strVolume.Trim();

                strOpenPrice = strOpenPrice.Trim();
                strHighPrice = strHighPrice.Trim();
                strLowPrice = strLowPrice.Trim();

                strTime = strTime.Trim();
                strExecVolume = strExecVolume.Trim();

		        /*--------------------------------------
		        조회 시점에 등록한 지수선물 현재가 실시간키와 동일한지 비교
		        ---------------------------------------*/
		        if (m_strCurPriceRealKey == e.strRealKey)
		        {
                    
			        labelCurPrice.Text = strCurPrice;
			        labelCurDiffSign.Text = GetDiffSign(strDiffSign);
			        labelDiff.Text = strDiff;
                    labelDiffRate.Text = strDiffRate;
                    labelVolume.Text = strVolume;

			        labelOpenPrice.Text = strOpenPrice;
			        labelHighPrice.Text = strHighPrice;
			        labelLowPrice.Text = strLowPrice;
		        }

		        /*--------------------------------------
		        조회 시점에 등록한 지수선물 시간대별 체결 실시간키와 동일한지 비교
		        ---------------------------------------*/
		        else if (m_strTickRealKey == e.strRealKey)
		        {
                    listViewTick.BeginUpdate();


                    Int32 nListRowCnt = listViewTick.Items.Count;

			        //데이터 500건이 넘으면 100건만 남기고 지운다.
			        if (nListRowCnt > 500)
			        {
				        for (int i = 100; i < 500; i++)
                            listViewTick.Items.RemoveAt(i);
			        }

                    ListViewItem listViewItem = new ListViewItem(strTime);
                    listViewItem.SubItems.Add(strCurPrice);
                    listViewItem.SubItems.Add(strDiff);
                    listViewItem.SubItems.Add(strDiffRate);
                    listViewItem.SubItems.Add(strExecVolume);

                    listViewTick.Items.Insert(0, listViewItem);
                    listViewTick.EndUpdate();

		        }//End of if

	        }//End of if
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
