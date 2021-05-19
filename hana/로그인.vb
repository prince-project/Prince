Option Explicit
Function FuncNumericString(strData) As String
'*************************************************
'* 함수명 :FuncNumericString
'* 인  자 :
'* 설  명 :숫자 포맷을 설정한다.
'*************************************************

    Dim nPos As Long
    Dim strValue As String

    strData = Trim(strData)
    nPos = InStr(1, strData, ".")
    If strData = "" Then strData = "0"

    Dim fValue As Double
    fValue = CDbl(strData)

    If nPos > 0 Then
        strValue = Format(fValue, "##,##0.00")
    Else
        strValue = Format(fValue, "##,##0")
    End If

    FuncNumericString = strValue

End Function
Function FuncSetLoginMode(nMode)
'*************************************************
'* 함수명 :FuncSetLoginMode
'* 인  자 :
'* 설  명 :로그인 접속 모드를 설정한다.
'*************************************************

    '*----------------------------------
    ' 접속서버를 설정한다.(0 - 리얼, 1 - 국내모의, 2 - 해외모의)
    '*----------------------------------*
    Call HFCommAgent1.SetLoginMode(0, nMode)

End Function
Private Sub ClearLogInButton_Click()
'*************************************************
'* 함수명 :CommandButtonLogin_Click
'* 인  자 :
'* 설  명 :로그인 정보 클리어
'*************************************************

    TextBoxID.Text = ""
    TextBoxPwd.Text = ""
    TextBoxCert.Text = ""
End Sub

Private Sub CommandButtonAPIPath_Click()
    MsgBox HFCommAgent1.GetApiAgentModulePath
End Sub

Private Sub CommandButtonLogin_Click()
'*************************************************
'* 함수명 :CommandButtonLogin_Click
'* 인  자 :
'* 설  명 :로그인
'*************************************************

    '**********************************************************
    'API에이전트에서 강제로 메시지 박스 실행하는 것을 막는다.
    '**********************************************************
    'HFCommAgent1.SetOffAgentMessageBox (1)

    '**********************************************************
    '이미 로그인한 상태인지 확인한다.
    '**********************************************************
    If HFCommAgent1.GetLoginState = 1 Then
        MsgBox "이미 로그인하셨습니다."
        Exit Sub
    End If

    '**********************************************************
    '통신을 연결한다.
    '**********************************************************
    If HFCommAgent1.CommInit < 0 Then
        MsgBox HFCommAgent1.GetLastErrMsg '마지막 에러 메시지
    End If

    '**********************************************************
    '통신이 정상적으로 연결되었는지 확인
    '**********************************************************
    If HFCommAgent1.CommGetConnectState <> 1 Then
        MsgBox "통신 연결 실패!"
        Exit Sub
    End If

    Dim strLogInID As String
    Dim strPWD As String
    Dim strCertPwd As String

    strLogInID = Trim(TextBoxID.Text) '로그인ID
    strPWD = Trim(TextBoxPwd.Text)    '로그인 비밀번호
    strCertPwd = Trim(TextBoxCert.Text)   '공인인증 비밀번호

    Dim nServerType As Long
    Dim strConSvrName As String

    nServerType = HFCommAgent1.GetLoginMode(0)

    '0-리얼, 1-국내모의, 2-해외모의
    Select Case nServerType
        Case 0
            strConSvrName = "운영"
            LoginOptionBtn1.Value = True
        Case 1
            strConSvrName = "국내모의"
            LoginOptionBtn2.Value = True
        Case 2
            strConSvrName = "해외모의"
            LoginOptionBtn3.Value = True
    End Select


    '**********************************************************
    '로그인 시도
    '**********************************************************
    If HFCommAgent1.CommLogin(strLogInID, strPWD, strCertPwd) <> 1 Then

        MsgBox HFCommAgent1.GetLastErrMsg '마지막 에러 메시지

    Else
        g_strLoginID = strLogInID
        MsgBox "[" & strConSvrName & "]로그인이 정상적으로 완료되었습니다."

        '**********************************
        '* 로그인이 완료되면 주문 실시간을 등록한다.
        '* 주문 실시간 통보는 사용자ID가 등록키가 된다.
        '**********************************
        '체결 실시간 통보
        Call HFCommAgent1.RegisterReal("EF1", g_strLoginID)
        '미체결 실시간 통보
        Call HFCommAgent1.RegisterReal("EF4", g_strLoginID)

    End If

End Sub

Private Sub CommandButtonLogOut_Click()
'*************************************************
'* 함수명 :CommandButtonLogOut_Click
'* 인  자 :
'* 설  명 :로그아웃
'*************************************************

    Dim strLogInID As String
    strLogInID = TextBoxID.Text '로그인ID

    '**********************************************************
    'LogOut 처리
    '**********************************************************
    Call HFCommAgent1.CommLogout(strLogInID)

    '**********************************************************
    '통신 연결을 종료한다.
    '**********************************************************
    Call HFCommAgent1.CommTerminate(1)

    MsgBox "로그아웃 처리가 완료되었습니다"

End Sub

Private Sub HFCommAgent1_OnGetFidData(ByVal nRequestId As Long, ByVal pBlock As String, ByVal nBlockLength As Long)
'*************************************************
'* 함수명 :HFCommAgent1_OnGetFidData
'* 인  자 :ByVal nRequestId As Long, ByVal pBlock As String, ByVal nBlockLength As Long
'* 설  명 :투자정보 FID 조회 결과 데이터를 서버로부터 수신하는 이벤트
'*************************************************

    '주의 : OnGetFidData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
    '이벤트 콜백함수 종료 후에는 유효하지 않습니다.
    g_strLoginID = ""

    Dim strPreNext As String
    Dim strPreNextContext As String
    Dim strMsgCode As String
    Dim strMsg As String
    Dim strIsError As String
    Dim strErrMsg As String

    '0 : 연속조회 미사용,        1 : 이전 데이터 있음,   2 : 다음 데이터 있음
    '3 : 이전/다음 데이터 있음
    strPreNext = HFCommAgent1.GetCommRecvOptionValue(commPrevNextCode)

    '연속조회키
    strPreNextContext = HFCommAgent1.GetCommRecvOptionValue(commPrevNextKey)

    '조회응답 메시지코드
    strMsgCode = HFCommAgent1.GetCommRecvOptionValue(commMsgCode)

    '조회응답 메시지
    strMsg = HFCommAgent1.GetCommRecvOptionValue(commMsg)

    '에러여부( "1" : 에러, "0" : 정상)
    strIsError = HFCommAgent1.GetCommRecvOptionValue(commError)

    strErrMsg = HFCommAgent1.GetLastErrMsg()

    Dim strData As String
    Dim strRealName As String
    Dim nRowCnt As Long
    Dim nDataCnt As Long
    Dim nRow As Long
    Dim i As Long
    Dim j As Long

    '***************************************
    '* 해외선물 종목 리스트(마스터) 조회 데이터 수신 처리
    '****************************************
    If g_nRqIdCodeList = nRequestId Then

        nDataCnt = HFCommAgent1.GetFidOutputRowCnt(nRequestId)
        nRowCnt = Sheet2.Cells(Sheet2.Rows.Count, "A").End(xlUp).Row + 1

        Dim arrItemCodeListValue(38)

        nRow = nRowCnt

        For i = 0 To nDataCnt - 1

            '--------------------------------------
            'FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
            '---------------------------------------
            arrItemCodeListValue(0) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1", i)         '종목코드(내부)
            arrItemCodeListValue(1) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "2", i)         '시세종목코드
            arrItemCodeListValue(2) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "3", i)         '해외파생상품명
            arrItemCodeListValue(3) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1448", i)      '품목코드
            arrItemCodeListValue(4) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "2083", i)      '해외파생품목명
            arrItemCodeListValue(5) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "661", i)       '행사가격
            arrItemCodeListValue(6) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1170", i)      '국가코드
            arrItemCodeListValue(7) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1987", i)      '거래소코드
            arrItemCodeListValue(8) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "2467", i)      '품목유형구분명
            arrItemCodeListValue(9) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "2456", i)      '가격소수점정보
            arrItemCodeListValue(10) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "2457", i)     '진법
            arrItemCodeListValue(11) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "2295", i)     'Tick Size
            arrItemCodeListValue(12) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1396", i)     '최소가격변동금액
            arrItemCodeListValue(13) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1773", i)     '환산승수
            arrItemCodeListValue(14) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1772", i)     '계약단위, 계약크기
            arrItemCodeListValue(15) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1731", i)     '위탁증거금
            arrItemCodeListValue(16) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "2460", i)     '유지증거금
            arrItemCodeListValue(17) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "226", i)      '상장일자
            arrItemCodeListValue(18) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "132", i)      '최종거래일(LTD)
            arrItemCodeListValue(19) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "981", i)      '만기일자(Expire Date)
            arrItemCodeListValue(20) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1203", i)     '만기년월(Expire Month / Year)
            arrItemCodeListValue(21) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1268", i)     '결제통화(거래통화 ? )
            arrItemCodeListValue(22) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1171", i)     '표시통화
            arrItemCodeListValue(23) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "2459", i)     '근월물순서
            arrItemCodeListValue(24) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "133", i)      '잔존일수
            arrItemCodeListValue(25) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1759", i)     'Active Flag
            arrItemCodeListValue(26) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "16", i)       '기준가
            arrItemCodeListValue(27) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "10", i)       '전일종가
            arrItemCodeListValue(28) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "28", i)       '전일거래량
            arrItemCodeListValue(29) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1762", i)     '거래가능 여부
            arrItemCodeListValue(30) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1870", i)     '시작시간
            arrItemCodeListValue(31) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "1871", i)     '종료시간
            arrItemCodeListValue(32) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "2486", i)     '장시작시간(한국)
            arrItemCodeListValue(33) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "2487", i)     '장종료시간(한국)
            arrItemCodeListValue(34) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "815", i)      '직전거래일
            arrItemCodeListValue(35) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "9", i)            '현영업일, 거래일자
            arrItemCodeListValue(36) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "128", i)      '상장후고가
            arrItemCodeListValue(37) = HFCommAgent1.GetFidOutputData(g_nRqIdCodeList, "129", i)      '상장후저가

            For j = 1 To 38
                Sheet2.Cells(nRow, j) = arrItemCodeListValue(j - 1)
            Next

            nRow = nRow + 1

        Next


        '*--------------------------------------
        '연속조회키를 저장해 놓는다.
        '---------------------------------------*
        g_strCodeListNextRqKey = strPreNextContext

        '*--------------------------------------
        '연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
        '---------------------------------------*
        If strPreNext = "2" Or strPreNext = "3" Then
            Sheet2.CBtnRQCodeListNext.Enabled = True
        Else
            Sheet2.CBtnRQCodeListNext.Enabled = False
        End If

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*
        g_nRqIdCodeList = 0    '해외선물 종목 리스트(마스터) 조회 Request ID


    '***************************************
    '* 해외선물 5단계호가 조회
    '***************************************
    ElseIf g_nRqIdHoga = nRequestId Then

        '/*--------------------------------------
        'FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
        '---------------------------------------*/
        strData = HFCommAgent1.GetFidOutputData(nRequestId, "29", 0) '매도 1호가
        Sheet3.Cells(7, 3) = HFCommAgent1.GetFidOutputData(nRequestId, "30", 0) '매도 2호가
        Sheet3.Cells(6, 3) = HFCommAgent1.GetFidOutputData(nRequestId, "31", 0) '매도 3호가
        Sheet3.Cells(5, 3) = HFCommAgent1.GetFidOutputData(nRequestId, "32", 0) '매도 4호가
        Sheet3.Cells(4, 3) = HFCommAgent1.GetFidOutputData(nRequestId, "33", 0) '매도 5호가
        Sheet3.Cells(8, 2) = HFCommAgent1.GetFidOutputData(nRequestId, "63", 0)   '매도 1호가잔량
        Sheet3.Cells(7, 2) = HFCommAgent1.GetFidOutputData(nRequestId, "64", 0)   '매도 2호가잔량
        Sheet3.Cells(6, 2) = HFCommAgent1.GetFidOutputData(nRequestId, "65", 0)   '매도 3호가잔량
        Sheet3.Cells(5, 2) = HFCommAgent1.GetFidOutputData(nRequestId, "66", 0)   '매도 4호가잔량
        Sheet3.Cells(4, 2) = HFCommAgent1.GetFidOutputData(nRequestId, "67", 0)   '매도 5호가잔량
        Sheet3.Cells(8, 1) = HFCommAgent1.GetFidOutputData(nRequestId, "196", 0)     '매도 1호가건수
        Sheet3.Cells(7, 1) = HFCommAgent1.GetFidOutputData(nRequestId, "197", 0)     '매도 2호가건수
        Sheet3.Cells(6, 1) = HFCommAgent1.GetFidOutputData(nRequestId, "198", 0)     '매도 3호가건수
        Sheet3.Cells(5, 1) = HFCommAgent1.GetFidOutputData(nRequestId, "199", 0)     '매도 4호가건수
        Sheet3.Cells(4, 1) = HFCommAgent1.GetFidOutputData(nRequestId, "200", 0)     '매도 5호가건수

        '매수호가/잔량
        Sheet3.Cells(9, 3) = HFCommAgent1.GetFidOutputData(nRequestId, "39", 0)      '매수 1호가
        Sheet3.Cells(10, 3) = HFCommAgent1.GetFidOutputData(nRequestId, "40", 0)      '매수 2호가
        Sheet3.Cells(11, 3) = HFCommAgent1.GetFidOutputData(nRequestId, "41", 0)      '매수 3호가
        Sheet3.Cells(12, 3) = HFCommAgent1.GetFidOutputData(nRequestId, "42", 0)      '매수 4호가
        Sheet3.Cells(13, 3) = HFCommAgent1.GetFidOutputData(nRequestId, "43", 0)      '매수 5호가
        Sheet3.Cells(9, 4) = HFCommAgent1.GetFidOutputData(nRequestId, "73", 0)    '매수 1호가잔량
        Sheet3.Cells(10, 4) = HFCommAgent1.GetFidOutputData(nRequestId, "74", 0)    '매수 2호가잔량
        Sheet3.Cells(11, 4) = HFCommAgent1.GetFidOutputData(nRequestId, "75", 0)    '매수 3호가잔량
        Sheet3.Cells(12, 4) = HFCommAgent1.GetFidOutputData(nRequestId, "76", 0)    '매수 4호가잔량
        Sheet3.Cells(13, 4) = HFCommAgent1.GetFidOutputData(nRequestId, "77", 0)    '매수 5호가잔량
        Sheet3.Cells(9, 5) = HFCommAgent1.GetFidOutputData(nRequestId, "201", 0)      '매수 1호가건수
        Sheet3.Cells(10, 5) = HFCommAgent1.GetFidOutputData(nRequestId, "202", 0)      '매수 2호가건수
        Sheet3.Cells(11, 5) = HFCommAgent1.GetFidOutputData(nRequestId, "203", 0)      '매수 3호가건수
        Sheet3.Cells(12, 5) = HFCommAgent1.GetFidOutputData(nRequestId, "204", 0)      '매수 4호가건수
        Sheet3.Cells(13, 5) = HFCommAgent1.GetFidOutputData(nRequestId, "205", 0)      '매수 5호가건수


        '/*--------------------------------------
        '해외선물호가 실시간키로 실시간을 등록한다.
        '실시간 등록은 첫 조회 시 한번만 한다.
        '---------------------------------------*/
        If g_strHogaRealKey <> "" Then
            strRealName = "V11"
            Call HFCommAgent1.RegisterReal(strRealName, g_strHogaRealKey) '실시간 등록
        End If

        '/*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*/
        g_nRqIdHoga = 0    '해외선물 5단계호가 조회 Request ID

    '***************************************
    '* 해외선물 현재가 조회 데이터 수신 처리
    '****************************************
    ElseIf g_nRqIdCurPrice = nRequestId Then

        '*--------------------------------------
        'FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
        '---------------------------------------*
        Sheet3.Cells(3, 8) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "4", 0))       '현재가
        Sheet3.Cells(4, 8) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "6", 0))     '부호
        Sheet3.Cells(5, 8) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "5", 0))         '전일대비
        Sheet3.Cells(6, 8) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "7", 0))     '대비율
        Sheet3.Cells(7, 8) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "11", 0))      '거래량
        Sheet3.Cells(8, 8) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "28", 0))   '전일거래량
        Sheet3.Cells(9, 8) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "13", 0))   '시가
        Sheet3.Cells(10, 8) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "14", 0))   '고가
        Sheet3.Cells(11, 8) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "15", 0))    '저가

        '*--------------------------------------
        '지선물 체결(현재가) 실시간등록키로 실시간을 등록한다.
        '실시간 등록은 첫 조회 시 한번만 한다.
        '---------------------------------------*
        If g_strCurPriceRealKey <> "" Then
            strRealName = "V10"
            Call HFCommAgent1.RegisterReal(strRealName, g_strCurPriceRealKey) '실시간 등록
        End If

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*
        g_nRqIdCurPrice = 0    '해외선물 현재가 조회 Request ID

    '***************************************
    '* 해외선물 체결틱 조회 데이터 수신 처리
    '****************************************
    ElseIf g_nRqIdTick = nRequestId Then

        Dim strTime As String     '시간
        Dim strPrice As String    '체결가
        Dim strDiff As String     '대비
        Dim strDiffRate As String '등률
        Dim strVolume As String   '체결량

        nRowCnt = Sheet4.Cells(Sheet4.Rows.Count, "A").End(xlUp).Row + 1
        nRow = nRowCnt
        nDataCnt = Sheet1.HFCommAgent1.GetFidOutputRowCnt(nRequestId)

        For i = 0 To nDataCnt - 1
            '*--------------------------------------
            'FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
            '---------------------------------------*
            strTime = HFCommAgent1.GetFidOutputData(nRequestId, "8", i)  '시간
            strPrice = HFCommAgent1.GetFidOutputData(nRequestId, "4", i) '체결가
            strDiff = HFCommAgent1.GetFidOutputData(nRequestId, "5", i)  '대비
            strDiffRate = HFCommAgent1.GetFidOutputData(nRequestId, "7", i)  '등률
            strVolume = HFCommAgent1.GetFidOutputData(nRequestId, "83", i) '체결량

            Sheet4.Cells(nRow, 1) = Trim(strTime)
            Sheet4.Cells(nRow, 2) = Trim(strPrice)
            Sheet4.Cells(nRow, 3) = Trim(strDiff)
            Sheet4.Cells(nRow, 4) = Trim(strDiffRate)
            Sheet4.Cells(nRow, 5) = Trim(strVolume)

            nRow = nRow + 1

        Next

        '*--------------------------------------
        '선물체결 실시간을 등록한다.
        '실시간 등록은 첫 조회 시 한번만 한다.
        '---------------------------------------*
        If g_strTickRealKey <> "" And g_strTickNextRqKey = "" Then
            strRealName = "V10"
            Call HFCommAgent1.RegisterReal(strRealName, g_strTickRealKey) '실시간 등록
        End If

        '*--------------------------------------
        '연속조회키를 저장해 놓는다.
        '---------------------------------------*
        g_strTickNextRqKey = strPreNextContext

        '*--------------------------------------
        '연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
        '---------------------------------------*
        If strPreNext = "2" Or strPreNext = "3" Then
            Sheet4.NextExecListButton.Enabled = True
        Else
            Sheet4.NextExecListButton.Enabled = False
        End If

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*/
        g_nRqIdTick = 0 '해외선물 시간대별체결 조회 Request ID

    '***************************************
    '* 해외선물 차트 조회 데이터 수신 처리
    '****************************************/
    ElseIf g_nRqIdChart = nRequestId Then

        '***************************************
        '* 에이전트 컨트롤을 통해 간적접으로 항목별 데이타를 빼낸다.
        '****************************************/
        nDataCnt = HFCommAgent1.GetFidOutputRowCnt(nRequestId)

        nRowCnt = Sheet5.Cells(Sheet5.Rows.Count, "A").End(xlUp).Row + 1
        nRow = nRowCnt

        For i = 0 To nDataCnt - 1

            '*--------------------------------------
            'FID 번호로 조회된 수신 데이터를 항목별로 빼낸다.
            '---------------------------------------*
            Sheet5.Cells(nRow, 1) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "9", i))  '0009 : 일자
            Sheet5.Cells(nRow, 2) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "8", i))  '0008 : 시간
            Sheet5.Cells(nRow, 3) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "4", i))  '0004 : 종가
            Sheet5.Cells(nRow, 4) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "13", i)) '0013 : 시가
            Sheet5.Cells(nRow, 5) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "14", i)) '0014 : 고가
            Sheet5.Cells(nRow, 6) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "15", i)) '0015 : 저가
            Sheet5.Cells(nRow, 7) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "83", i)) '0083 : 체결량
            Sheet5.Cells(nRow, 8) = Trim(HFCommAgent1.GetFidOutputData(nRequestId, "11", i)) '0011 : 거래량

            nRow = nRow + 1

        Next

        '*--------------------------------------
        '연속조회키를 저장해 놓는다.
        '---------------------------------------*
        g_strChartNextRqKey = strPreNextContext

        '*--------------------------------------
        '연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
        '---------------------------------------*
        If strPreNext = "2" Or strPreNext = "3" Then
            Sheet5.NextChartRequestButton.Enabled = True
        Else
            Sheet5.NextChartRequestButton.Enabled = False
        End If

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*/
        g_nRqIdChart = 0    '해외선물 종목 리스트(마스터) 조회 Request ID

    End If

End Sub


Private Sub HFCommAgent1_OnGetTranData(ByVal nRequestId As Long, ByVal pBlock As String, ByVal nBlockLength As Long)
'*************************************************
'* 함수명 :HFCommAgent1_OnGetTranData
'* 인  자 :ByVal nRequestId As Long, ByVal pBlock As String, ByVal nBlockLength As Long
'* 설  명 :주문체결/잔고 등 조회 결과 데이터를 서버로부터 수신하는 이벤트
'*************************************************

    '/* 주의 : OnGetTranData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
    '이벤트 콜백함수 종료 후에는 유효하지 않습니다.*/
    Dim strTrCode, strPreNext, strPreNextContext, strMsgCode, strMsg, strSubMsgCode, strSubMsg, strIsError, strErrMsg As String

    strTrCode = HFCommAgent1.GetCommRecvOptionValue(commTranCode)

    '/*  0 : 연속조회 미사용,        1 : 이전 데이터 있음,   2 : 다음 데이터 있음
    '3 : 이전/다음 데이터 있음   */
    strPreNext = HFCommAgent1.GetCommRecvOptionValue(commPrevNextCode)

    '연속조회키
    strPreNextContext = HFCommAgent1.GetCommRecvOptionValue(commPrevNextKey)

    '조회응답 메시지코드
    strMsgCode = HFCommAgent1.GetCommRecvOptionValue(commMsgCode)

    '조회응답 메시지
    strMsg = HFCommAgent1.GetCommRecvOptionValue(commMsg)

    '조회응답 부가메시지코드
    strSubMsgCode = HFCommAgent1.GetCommRecvOptionValue(commSubMsgCode)

    '조회응답 부가메시지
    strSubMsg = HFCommAgent1.GetCommRecvOptionValue(commSubMsg)

    '에러여부( "1" : 에러, "0" : 정상)
    strIsError = HFCommAgent1.GetCommRecvOptionValue(commError)

    strErrMsg = HFCommAgent1.GetLastErrMsg()

    Dim nRowCnt, nRow, i, nDataCnt As Long
    Dim strODRV_ODNO As String
    Dim strOutRecName As String

    '계좌목록 조회
    If g_nRqIdAccNoList = nRequestId Then

        Dim strfunc, strusid, strerrc, stremsg, strnrec, straccn, strsub_accn As String
        Dim stracnm, strachk, strpwch As String

        strfunc = HFCommAgent1.GetTranOutputData(strTrCode, "OutRec1", "func", 0)       '기능구분코드
        strusid = HFCommAgent1.GetTranOutputData(strTrCode, "OutRec1", "usid", 0)       '사용자아이디
        strerrc = HFCommAgent1.GetTranOutputData(strTrCode, "OutRec1", "errc", 0)       '에러코드
        stremsg = HFCommAgent1.GetTranOutputData(strTrCode, "OutRec1", "emsg", 0)       '에러메시지
        strnrec = HFCommAgent1.GetTranOutputData(strTrCode, "OutRec1", "nrec", 0)       '출력건수

        nDataCnt = HFCommAgent1.GetTranOutputRowCnt(strTrCode, "OutRec2")

        Dim strAccNo As String
        Dim strPrdt As String

        nRowCnt = Sheet6.Cells(Sheet6.Rows.Count, "B").End(xlUp).Row
        nRow = nRowCnt + 1

        ReDim g_arrUserAccNo(nDataCnt)
        ReDim g_arrUserAPNo(nDataCnt)
        g_nUserAccCnt = nDataCnt

        For i = 0 To nDataCnt - 1

            straccn = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OutRec2", "accn", i))          '계좌번호
            strsub_accn = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OutRec2", "sub_accn", i))  '대체계좌번호
            stracnm = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OutRec2", "acnm", i))        '계좌명
            strachk = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OutRec2", "achk", i))        '계좌특성
            strpwch = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OutRec2", "pwch", i))        '은행연계계좌여부

            strAccNo = straccn.Mid(1, 8)
            strPrdt = straccn.Mid(9, 3)

            g_arrUserAccNo(i) = strAccNo '종합계좌번호
            g_arrUserAPNo(i) = strsub_accn '종합계좌대체번호

            Sheet6.Cells(nRow, 2) = strAccNo      '종합계좌번호
            Sheet6.Cells(nRow, 3) = strsub_accn       '대체종합계좌번호
            Sheet6.Cells(nRow, 4) = strPrdt     '계좌상품번호
            Sheet6.Cells(nRow, 5) = stracnm  '계좌명
            Sheet6.Cells(nRow, 6) = strachk  '계좌특성
            Sheet6.Cells(nRow, 7) = strpwch  '은행연계계좌여부

            nRow = nRow + 1
        Next

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*
        g_nRqIdAccNoList = 0   '계좌목록

    '계좌목록 조회
    ElseIf g_nRqIdFDemoAccNoList = nRequestId Then

        Dim strCTNO, strCANO, strAPNO, strCUST_NM As String

        nRowCnt = Sheet6.Cells(Sheet6.Rows.Count, "B").End(xlUp).Row
        nRow = nRowCnt + 1

        nDataCnt = HFCommAgent1.GetTranOutputRowCnt(strTrCode, "OTS5991Q03_out_sub01")

        ReDim g_arrUserAccNo(nDataCnt)
        ReDim g_arrUserAPNo(nDataCnt)
        g_nUserAccCnt = nDataCnt

        For i = 0 To nDataCnt - 1

            strCTNO = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CTNO", i))       '종합계좌대체번호
            strCANO = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CANO", i))       '종합계좌번호
            strAPNO = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "APNO", i))       '계좌상품번호
            strCUST_NM = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OTS5991Q03_out_sub01", "CUST_NM", i))     '고객명

            g_arrUserAccNo(i) = strCANO '종합계좌번호
            g_arrUserAPNo(i) = strCTNO '종합계좌대체번호

            Sheet6.Cells(nRow, 2) = strCANO      '종합계좌번호
            Sheet6.Cells(nRow, 3) = strCTNO       '대체종합계좌번호
            Sheet6.Cells(nRow, 4) = strAPNO     '계좌상품번호
            Sheet6.Cells(nRow, 5) = strCUST_NM  '계좌명
            Sheet6.Cells(nRow, 6) = ""  '계좌특성
            Sheet6.Cells(nRow, 7) = ""  '은행연계계좌여부

            nRow = nRow + 1
        Next

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*
        g_nRqIdFDemoAccNoList = 0  '해외선물데모계좌리스트

    '매도주문 Request ID
    ElseIf g_nRqIdSellOrd = nRequestId Then

        strODRV_ODNO = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OTS5901U01_out", "ODRV_ODNO", 0))       '해외파생주문번호

        Sheet7.LabelOrderNo.Caption = strODRV_ODNO

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*
        g_nRqIdSellOrd = 0

        If strODRV_ODNO <> "" Then MsgBox "매도주문 완료되었습니다.[" & strODRV_ODNO & "]"

    '매수주문 Request ID
    ElseIf g_nRqIdBuyOrd = nRequestId Then

        strODRV_ODNO = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OTS5901U01_out", "ODRV_ODNO", 0))      '해외파생주문번호

        Sheet7.LabelOrderNo.Caption = strODRV_ODNO

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*
        g_nRqIdBuyOrd = 0

        If strODRV_ODNO <> "" Then MsgBox "매수주문 완료되었습니다.[" & strODRV_ODNO & "]"

    '정정주문 Request ID
    ElseIf g_nRqIdChangeOrd = nRequestId Then

        strODRV_ODNO = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OTS5901U02_out", "ODRV_ODNO", 0))      '해외파생주문번호

        Sheet7.LabelOrderNo.Caption = strODRV_ODNO

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*
        g_nRqIdChangeOrd = 0

        If strODRV_ODNO <> "" Then MsgBox "정정주문 완료되었습니다.[" & strODRV_ODNO & "]"

    '취소주문 Request ID
    ElseIf g_nRqIdCancelOrd = nRequestId Then

        strODRV_ODNO = Trim(HFCommAgent1.GetTranOutputData(strTrCode, "OTS5901U03_out", "ODRV_ODNO", 0))      '해외파생주문번호

        Sheet7.LabelOrderNo.Caption = strODRV_ODNO

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*
        g_nRqIdCancelOrd = 0

        If strODRV_ODNO <> "" Then MsgBox "취소주문 완료되었습니다.[" & strODRV_ODNO & "]"

    '예수금 조회
    ElseIf g_nRqIdDepositList = nRequestId Then

        Dim strCRRY_CD, strODRV_STDR_EXRT_CTNS, strBFDT_CSH_BLCE_CTNS, strODRV_CSH_RCTg_AMT_CTNS, _
        strODRV_CSH_DRWG_AMT_CTNS, strODRV_CLR_PFLS_AMT_CTNS, strODRV_OPT_SELL_AMT_CTNS, _
        strODRV_OPT_BUY_AMT_CTNS, strODRV_FEE_CTNS, strTHDT_CSH_BLCE_CTNS, strODRV_EVL_PFLS_AMT_CTNS, _
        strEVL_DPST_AMT_CTNS, strODRV_OPT_EVL_AMT_CTNS, strTOT_ACC_ASST_VALU_AMT_CTNS, _
        strOPNG_WMY_CTNS, strODRV_ORDR_WMY_CTNS, strODRV_MNTN_WMY_CTNS, strWMY_LACK_AMT_CTNS, strODRV_WDRW_PSBL_AMT_CTNS, _
        strECHg_PSBL_AMT_CTNS, strODRV_ORDR_PSBL_AMT_CTNS, strODRV_ADIT_WMY_CTNS, strRCVB_OVDU_INTR_CTNS As String

        nDataCnt = HFCommAgent1.GetTranOutputRowCnt(strTrCode, "OTS5943Q01_out_sub01")

        nRowCnt = Sheet8.Cells(Sheet8.Rows.Count, "A").End(xlUp).Row + 1
        nRow = nRowCnt

        For i = 0 To nDataCnt - 1

            strCRRY_CD = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "CRRY_CD", i)     '통화코드
            strODRV_STDR_EXRT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_STDR_EXRT_CTNS", i)         '해외파생기준환율내용
            strBFDT_CSH_BLCE_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "BFDT_CSH_BLCE_CTNS", i)           ' 전일현금잔액내용
            strODRV_CSH_RCTg_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "BFDT_CSH_BLCE_CTNS", i)       '해외파생현금입금금액내용
            strODRV_CSH_DRWG_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_CSH_DRWG_AMT_CTNS", i)       '해외파생현금출금금액내용
            strODRV_CLR_PFLS_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_CLR_PFLS_AMT_CTNS", i)       '해외파생청산손익금액내용
            strODRV_OPT_SELL_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_OPT_SELL_AMT_CTNS", i)       '해외파생옵션매도금액내용
            strODRV_OPT_BUY_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_OPT_BUY_AMT_CTNS", i)     '해외파생옵션매수금액내용
            strODRV_FEE_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_FEE_CTNS", i)             '해외파생수수료내용
            strTHDT_CSH_BLCE_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "THDT_CSH_BLCE_CTNS", i)           '당일현금잔액내용
            strODRV_EVL_PFLS_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_EVL_PFLS_AMT_CTNS", i)       '해외파생평가손익금액내용
            strEVL_DPST_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "EVL_DPST_AMT_CTNS", i)         '평가예탁금액내용
            strODRV_OPT_EVL_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_OPT_EVL_AMT_CTNS", i)     '해외파생옵션평가금액내용
            strTOT_ACC_ASST_VALU_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "TOT_ACC_ASST_VALU_AMT_CTNS", i)   '총계정자산가치금액내용
            strOPNG_WMY_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "OPNG_WMY_CTNS", i)             '개시증거금내용
            strODRV_ORDR_WMY_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_ORDR_WMY_CTNS", i)           '해외파생주문증거금내용
            strODRV_MNTN_WMY_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_MNTN_WMY_CTNS", i)           '해외파생유지증거금내용
            strWMY_LACK_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "WMY_LACK_AMT_CTNS", i)         '증거금부족금액내용
            strODRV_WDRW_PSBL_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_WDRW_PSBL_AMT_CTNS", i)     '해외파생인출가능금액내용
            strECHg_PSBL_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ECHg_PSBL_AMT_CTNS", i)           '환전가능금액내용
            strODRV_ORDR_PSBL_AMT_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_ORDR_PSBL_AMT_CTNS", i)     '해외파생주문가능금액내용
            strODRV_ADIT_WMY_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "ODRV_ADIT_WMY_CTNS", i)           '해외파생추가증거금내용
            strRCVB_OVDU_INTR_CTNS = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5943Q01_out_sub01", "RCVB_OVDU_INTR_CTNS", i)         '미수연체이자내용

            strCRRY_CD = Trim(strCRRY_CD)

            strODRV_STDR_EXRT_CTNS = FuncNumericString(strODRV_STDR_EXRT_CTNS)
            strBFDT_CSH_BLCE_CTNS = FuncNumericString(strBFDT_CSH_BLCE_CTNS)
            strODRV_CSH_RCTg_AMT_CTNS = FuncNumericString(strODRV_CSH_RCTg_AMT_CTNS)
            strODRV_CSH_DRWG_AMT_CTNS = FuncNumericString(strODRV_CSH_DRWG_AMT_CTNS)
            strODRV_CLR_PFLS_AMT_CTNS = FuncNumericString(strODRV_CLR_PFLS_AMT_CTNS)
            strODRV_OPT_SELL_AMT_CTNS = FuncNumericString(strODRV_OPT_SELL_AMT_CTNS)
            strODRV_OPT_BUY_AMT_CTNS = FuncNumericString(strODRV_OPT_BUY_AMT_CTNS)
            strODRV_FEE_CTNS = FuncNumericString(strODRV_FEE_CTNS)
            strTHDT_CSH_BLCE_CTNS = FuncNumericString(strTHDT_CSH_BLCE_CTNS)
            strODRV_EVL_PFLS_AMT_CTNS = FuncNumericString(strODRV_EVL_PFLS_AMT_CTNS)
            strEVL_DPST_AMT_CTNS = FuncNumericString(strEVL_DPST_AMT_CTNS)
            strODRV_OPT_EVL_AMT_CTNS = FuncNumericString(strODRV_OPT_EVL_AMT_CTNS)
            strTOT_ACC_ASST_VALU_AMT_CTNS = FuncNumericString(strTOT_ACC_ASST_VALU_AMT_CTNS)
            strOPNG_WMY_CTNS = FuncNumericString(strOPNG_WMY_CTNS)
            strODRV_ORDR_WMY_CTNS = FuncNumericString(strODRV_ORDR_WMY_CTNS)
            strODRV_MNTN_WMY_CTNS = FuncNumericString(strODRV_MNTN_WMY_CTNS)
            strWMY_LACK_AMT_CTNS = FuncNumericString(strWMY_LACK_AMT_CTNS)
            strODRV_WDRW_PSBL_AMT_CTNS = FuncNumericString(strODRV_WDRW_PSBL_AMT_CTNS)
            strECHg_PSBL_AMT_CTNS = FuncNumericString(strECHg_PSBL_AMT_CTNS)
            strODRV_ORDR_PSBL_AMT_CTNS = FuncNumericString(strODRV_ORDR_PSBL_AMT_CTNS)
            strODRV_ADIT_WMY_CTNS = FuncNumericString(strODRV_ADIT_WMY_CTNS)
            strRCVB_OVDU_INTR_CTNS = FuncNumericString(strRCVB_OVDU_INTR_CTNS)

            Sheet8.Cells(nRow, 1) = strCRRY_CD
            Sheet8.Cells(nRow, 2) = strODRV_STDR_EXRT_CTNS
            Sheet8.Cells(nRow, 3) = strBFDT_CSH_BLCE_CTNS
            Sheet8.Cells(nRow, 4) = strODRV_CSH_RCTg_AMT_CTNS
            Sheet8.Cells(nRow, 5) = strODRV_CSH_DRWG_AMT_CTNS
            Sheet8.Cells(nRow, 6) = strODRV_CLR_PFLS_AMT_CTNS
            Sheet8.Cells(nRow, 7) = strODRV_OPT_SELL_AMT_CTNS
            Sheet8.Cells(nRow, 8) = strODRV_OPT_BUY_AMT_CTNS
            Sheet8.Cells(nRow, 9) = strODRV_FEE_CTNS
            Sheet8.Cells(nRow, 10) = strTHDT_CSH_BLCE_CTNS
            Sheet8.Cells(nRow, 11) = strODRV_EVL_PFLS_AMT_CTNS
            Sheet8.Cells(nRow, 12) = strEVL_DPST_AMT_CTNS
            Sheet8.Cells(nRow, 13) = strODRV_OPT_EVL_AMT_CTNS
            Sheet8.Cells(nRow, 14) = strTOT_ACC_ASST_VALU_AMT_CTNS
            Sheet8.Cells(nRow, 15) = strOPNG_WMY_CTNS
            Sheet8.Cells(nRow, 16) = strODRV_ORDR_WMY_CTNS
            Sheet8.Cells(nRow, 17) = strODRV_MNTN_WMY_CTNS
            Sheet8.Cells(nRow, 18) = strWMY_LACK_AMT_CTNS
            Sheet8.Cells(nRow, 19) = strODRV_WDRW_PSBL_AMT_CTNS
            Sheet8.Cells(nRow, 20) = strECHg_PSBL_AMT_CTNS
            Sheet8.Cells(nRow, 21) = strODRV_ORDR_PSBL_AMT_CTNS
            Sheet8.Cells(nRow, 22) = strODRV_ADIT_WMY_CTNS
            Sheet8.Cells(nRow, 23) = strRCVB_OVDU_INTR_CTNS

            nRow = nRow + 1

        Next

        '*--------------------------------------
        '연속조회키를 저장해 놓는다.
        '---------------------------------------*
        g_strListDepositNextRqKey = strPreNextContext

        '*--------------------------------------
        '연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
        '---------------------------------------*
        If strPreNext = "2" Or strPreNext = "3" Then
            Sheet8.NextRequestDeposit.Enabled = True
        Else
            Sheet8.NextRequestDeposit.Enabled = False
        End If

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*
        g_nRqIdDepositList = 0  '예수금

    '주문미체결내역
    ElseIf nRequestId = g_nRqIdNonExecList Then

        Dim strBSN_DT, strPRDT_CD, strODRV_OR_ODNO, strODRV_MO_ODNO, strORDR_GRUP_NO, _
        strORDR_DT, strSELL_BUY_DCD, strODRV_ORDR_PRC, strORDR_QNT, strRVSE_QNT, strCNCL_QNT, _
        strCNCS_QNT, strRMN_QNT, strPRC_CND_DCD, strCNCS_CND_DCD, strSQ1_APPN_PRC, strAVR_CNCS_PRC, strCNCS_RT, _
        strNOW_PRC, strMDIA_DCD, strORDR_DCD, strORDR_STTS_DCD, strFCM_ODNO, strUSER_ID, strATHZ_IP_ADDR, _
        strACPT_TM, strCNCS_TM, strACPL_ACPT_TM, strACPL_CNCS_TM As String

        strOutRecName = "OTS5911Q41_out_sub01"

        nRowCnt = Sheet9.Cells(Sheet9.Rows.Count, "A").End(xlUp).Row + 1
        nRow = nRowCnt

        nDataCnt = Sheet1.HFCommAgent1.GetTranOutputRowCnt(strTrCode, strOutRecName)

        For i = 0 To nDataCnt - 1

            strBSN_DT = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "BSN_DT", i)        '영업일자
            strCANO = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CANO", i)        '종합계좌번호
            strODRV_ODNO = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ODRV_ODNO", i)      '해외파생주문번호
            strPRDT_CD = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "PRDT_CD", i)      '상품코드
            strODRV_OR_ODNO = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ODRV_OR_ODNO", i)        '해외파생원주문번호
            strODRV_MO_ODNO = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ODRV_MO_ODNO", i)        '해외파생모주문번호
            strORDR_GRUP_NO = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ORDR_GRUP_NO", i)        '주문그룹번호
            strORDR_DT = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DT", i)      '주문일자
            strCUST_NM = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CUST_NM", i)      '고객명
            strSELL_BUY_DCD = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "SELL_BUY_DCD", i)        '매도매수구분코드
            strODRV_ORDR_PRC = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ODRV_ORDR_PRC", i)      '해외파생주문가격
            strORDR_QNT = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ORDR_QNT", i)        '주문수량
            strRVSE_QNT = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "RVSE_QNT", i)        '정정수량
            strCNCL_QNT = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CNCL_QNT", i)        '취소수량
            strCNCS_QNT = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT", i)        '체결수량
            strRMN_QNT = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "RMN_QNT", i)      '잔여수량
            strPRC_CND_DCD = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "PRC_CND_DCD", i)      '가격조건구분코드
            strCNCS_CND_DCD = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CNCS_CND_DCD", i)        '체결조건구분코드
            strSQ1_APPN_PRC = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "SQ1_APPN_PRC", i)        '1차지정가격
            strAVR_CNCS_PRC = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "AVR_CNCS_PRC", i)        '평균체결가격
            strCNCS_RT = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CNCS_RT", i)      '체결율
            strNOW_PRC = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "NOW_PRC", i)      '현재가격
            strMDIA_DCD = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "MDIA_DCD", i)        '매체구분코드
            strORDR_DCD = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DCD", i)        '주문구분코드
            strORDR_STTS_DCD = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ORDR_STTS_DCD", i)      '주문상태구분코드
            strFCM_ODNO = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "FCM_ODNO", i)        'FCM주문번호
            strUSER_ID = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "USER_ID", i)      '사용자ID
            strATHZ_IP_ADDR = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ATHZ_IP_ADDR", i)        '공인IP주소
            strACPT_TM = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ACPT_TM", i)      '접수시각
            strCNCS_TM = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CNCS_TM", i)      '체결시각
            strACPL_ACPT_TM = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ACPL_ACPT_TM", i)        '현지접수시각
            strACPL_CNCS_TM = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ACPL_CNCS_TM", i)        '현지체결시각
            strCRRY_CD = Sheet1.HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CRRY_CD", i)      '통화코드

            strBSN_DT = Trim(strBSN_DT) '영업일자
            strCANO = Trim(strCANO)      '종합계좌번호
            strODRV_ODNO = Trim(strODRV_ODNO)     '해외파생주문번호
            strPRDT_CD = Trim(strPRDT_CD)       '상품코드
            strODRV_OR_ODNO = Trim(strODRV_OR_ODNO)      '해외파생원주문번호
            strODRV_MO_ODNO = Trim(strODRV_MO_ODNO)    '해외파생모주문번호
            strORDR_GRUP_NO = Trim(strORDR_GRUP_NO)    '주문그룹번호
            strORDR_DT = Trim(strORDR_DT)     '주문일자
            strCUST_NM = Trim(strCUST_NM)     '고객명
            strSELL_BUY_DCD = Trim(strSELL_BUY_DCD)    '매도매수구분코드
            strODRV_ORDR_PRC = FuncNumericString(strODRV_ORDR_PRC)     '해외파생주문가격
            strORDR_QNT = FuncNumericString(strORDR_QNT)    '주문수량
            strRVSE_QNT = FuncNumericString(strRVSE_QNT)    '정정수량
            strCNCL_QNT = FuncNumericString(strCNCL_QNT)    '취소수량
            strCNCS_QNT = FuncNumericString(strCNCS_QNT)    '체결수량
            strRMN_QNT = FuncNumericString(strRMN_QNT)     '잔여수량
            strPRC_CND_DCD = Trim(strPRC_CND_DCD)     '가격조건구분코드
            strCNCS_CND_DCD = Trim(strCNCS_CND_DCD)    '체결조건구분코드
            strSQ1_APPN_PRC = FuncNumericString(strSQ1_APPN_PRC)    '1차지정가격
            strAVR_CNCS_PRC = FuncNumericString(strAVR_CNCS_PRC)    '평균체결가격
            strCNCS_RT = FuncNumericString(strCNCS_RT)     '체결율
            strNOW_PRC = FuncNumericString(strNOW_PRC)     '현재가격
            strMDIA_DCD = Trim(strMDIA_DCD)    '매체구분코드
            strORDR_DCD = Trim(strORDR_DCD)    '주문구분코드
            strORDR_STTS_DCD = Trim(strORDR_STTS_DCD)   '주문상태구분코드
            strFCM_ODNO = Trim(strFCM_ODNO)    'FCM주문번호
            strUSER_ID = Trim(strUSER_ID)     '사용자ID
            strATHZ_IP_ADDR = Trim(strATHZ_IP_ADDR)    '공인IP주소
            strACPT_TM = Trim(strACPT_TM)     '접수시각
            strCNCS_TM = Trim(strCNCS_TM)     '체결시각
            strACPL_ACPT_TM = Trim(strACPL_ACPT_TM)    '현지접수시각
            strACPL_CNCS_TM = Trim(strACPL_CNCS_TM)    '현지체결시각
            strCRRY_CD = Trim(strCRRY_CD)     '통화코드

            Sheet9.Cells(nRow, 1) = strBSN_DT        '영업일자
            Sheet9.Cells(nRow, 2) = strCANO      '종합계좌번호
            Sheet9.Cells(nRow, 3) = strODRV_ODNO     '해외파생주문번호
            Sheet9.Cells(nRow, 4) = strPRDT_CD       '상품코드
            Sheet9.Cells(nRow, 5) = strODRV_OR_ODNO      '해외파생원주문번호
            Sheet9.Cells(nRow, 6) = strODRV_MO_ODNO      '해외파생모주문번호
            Sheet9.Cells(nRow, 7) = strORDR_GRUP_NO      '주문그룹번호
            Sheet9.Cells(nRow, 8) = strORDR_DT       '주문일자
            Sheet9.Cells(nRow, 9) = strCUST_NM       '고객명
            Sheet9.Cells(nRow, 10) = strSELL_BUY_DCD      '매도매수구분코드
            Sheet9.Cells(nRow, 11) = strODRV_ORDR_PRC        '해외파생주문가격
            Sheet9.Cells(nRow, 12) = strORDR_QNT     '주문수량
            Sheet9.Cells(nRow, 13) = strRVSE_QNT     '정정수량
            Sheet9.Cells(nRow, 14) = strCNCL_QNT     '취소수량
            Sheet9.Cells(nRow, 15) = strCNCS_QNT     '체결수량
            Sheet9.Cells(nRow, 16) = strRMN_QNT      '잔여수량
            Sheet9.Cells(nRow, 17) = strPRC_CND_DCD      '가격조건구분코드
            Sheet9.Cells(nRow, 18) = strCNCS_CND_DCD     '체결조건구분코드
            Sheet9.Cells(nRow, 19) = strSQ1_APPN_PRC     '1차지정가격
            Sheet9.Cells(nRow, 20) = strAVR_CNCS_PRC     '평균체결가격
            Sheet9.Cells(nRow, 21) = strCNCS_RT      '체결율
            Sheet9.Cells(nRow, 22) = strNOW_PRC      '현재가격
            Sheet9.Cells(nRow, 23) = strMDIA_DCD     '매체구분코드
            Sheet9.Cells(nRow, 24) = strORDR_DCD     '주문구분코드
            Sheet9.Cells(nRow, 25) = strORDR_STTS_DCD        '주문상태구분코드
            Sheet9.Cells(nRow, 26) = strFCM_ODNO     'FCM주문번호
            Sheet9.Cells(nRow, 27) = strUSER_ID      '사용자ID
            Sheet9.Cells(nRow, 28) = strATHZ_IP_ADDR     '공인IP주소
            Sheet9.Cells(nRow, 29) = strACPT_TM      '접수시각
            Sheet9.Cells(nRow, 30) = strCNCS_TM      '체결시각
            Sheet9.Cells(nRow, 31) = strACPL_ACPT_TM     '현지접수시각
            Sheet9.Cells(nRow, 32) = strACPL_CNCS_TM     '현지체결시각
            Sheet9.Cells(nRow, 33) = strCRRY_CD      '통화코드

            nRow = nRow + 1
        Next

        '*--------------------------------------
        '연속조회키를 저장해 놓는다.
        '---------------------------------------*
        g_strListNonExecNextRqKey = strPreNextContext

        '*--------------------------------------
        '연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
        '---------------------------------------*
        If strPreNext = "2" Or strPreNext = "3" Then
            Sheet9.NextRequestNonExecButton.Enabled = True
        Else
            Sheet9.NextRequestNonExecButton.Enabled = False
        End If

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*/
        g_nRqIdNonExecList = 0  '주문체결조회 Rq ID

    '주문체결내역 조회
    ElseIf nRequestId = g_nRqIdExecList Then

        Dim strACNT_PRDT_CD, strCNCS_DETL_DTM

        nRowCnt = Sheet10.Cells(Sheet10.Rows.Count, "A").End(xlUp).Row + 1
        nRow = nRowCnt

        strOutRecName = "OTS5911Q52_out_sub01"

        nDataCnt = HFCommAgent1.GetTranOutputRowCnt(strTrCode, strOutRecName)
        For i = 0 To nDataCnt - 1

            strCANO = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CANO", i)        '종합계좌번호
            strODRV_ODNO = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ODRV_ODNO", i)      '해외파생주문번호
            strPRDT_CD = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "PRDT_CD", i)      '상품코드
            strODRV_OR_ODNO = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ODRV_OR_ODNO", i)        '해외파생원주문번호
            strODRV_MO_ODNO = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ODRV_MO_ODNO", i)        '해외파생모주문번호
            strORDR_GRUP_NO = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ORDR_GRUP_NO", i)        '주문그룹번호
            strORDR_DT = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DT", i)      '주문일자
            strACNT_PRDT_CD = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ACNT_PRDT_CD", i)        '계좌상품코드
            strCUST_NM = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CUST_NM", i)      '고객명
            strSELL_BUY_DCD = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "SELL_BUY_DCD", i)        '매도매수구분코드
            strODRV_ORDR_PRC = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ODRV_ORDR_PRC", i)      '해외파생주문가격
            strORDR_QNT = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ORDR_QNT", i)        '주문수량
            strRVSE_QNT = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "RVSE_QNT", i)        '정정수량
            strCNCL_QNT = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CNCL_QNT", i)        '취소수량
            strCNCS_QNT = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CNCS_QNT", i)        '체결수량
            strRMN_QNT = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "RMN_QNT", i)      '잔여수량
            strPRC_CND_DCD = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "PRC_CND_DCD", i)      '가격조건구분코드
            strCNCS_CND_DCD = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CNCS_CND_DCD", i)        '체결조건구분코드
            strSQ1_APPN_PRC = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "SQ1_APPN_PRC", i)        '1차지정가격
            strAVR_CNCS_PRC = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "AVR_CNCS_PRC", i)        '평균체결가격
            strCNCS_RT = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CNCS_RT", i)      '체결율
            strNOW_PRC = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "NOW_PRC", i)      '현재가격
            strMDIA_DCD = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "MDIA_DCD", i)        '매체구분코드
            strORDR_DCD = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ORDR_DCD", i)        '주문구분코드
            strORDR_STTS_DCD = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ORDR_STTS_DCD", i)      '주문상태구분코드
            strFCM_ODNO = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "FCM_ODNO", i)        'FCM주문번호
            strUSER_ID = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "USER_ID", i)      '사용자ID
            strATHZ_IP_ADDR = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ATHZ_IP_ADDR", i)        '공인IP주소
            strACPT_TM = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ACPT_TM", i)      '접수시각
            strCNCS_TM = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CNCS_TM", i)      '체결시각
            strACPL_ACPT_TM = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "ACPL_ACPT_TM", i)        '현지접수시각
            strCNCS_DETL_DTM = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CNCS_DETL_DTM", i)      '체결상세일시
            strCRRY_CD = HFCommAgent1.GetTranOutputData(strTrCode, strOutRecName, "CRRY_CD", i)      '통화코드

            strCANO = Trim(strCANO)      '종합계좌번호
            strODRV_ODNO = Trim(strODRV_ODNO)   '해외파생주문번호
            strPRDT_CD = Trim(strPRDT_CD)     '상품코드
            strODRV_OR_ODNO = Trim(strODRV_OR_ODNO)    '해외파생원주문번호
            strODRV_MO_ODNO = Trim(strODRV_MO_ODNO)    '해외파생모주문번호
            strORDR_GRUP_NO = Trim(strORDR_GRUP_NO)    '주문그룹번호
            strORDR_DT = Trim(strORDR_DT)     '주문일자
            strACNT_PRDT_CD = Trim(strACNT_PRDT_CD)    '계좌상품코드
            strCUST_NM = Trim(strCUST_NM)     '고객명
            strSELL_BUY_DCD = Trim(strSELL_BUY_DCD)    '매도매수구분코드
            strODRV_ORDR_PRC = FuncNumericString(strODRV_ORDR_PRC)     '해외파생주문가격
            strORDR_QNT = FuncNumericString(strORDR_QNT)    '주문수량
            strRVSE_QNT = FuncNumericString(strRVSE_QNT)    '정정수량
            strCNCL_QNT = FuncNumericString(strCNCL_QNT)    '취소수량
            strCNCS_QNT = FuncNumericString(strCNCS_QNT)    '체결수량
            strRMN_QNT = FuncNumericString(strRMN_QNT)     '잔여수량
            strPRC_CND_DCD = Trim(strPRC_CND_DCD)     '가격조건구분코드
            strCNCS_CND_DCD = Trim(strCNCS_CND_DCD)    '체결조건구분코드
            strSQ1_APPN_PRC = FuncNumericString(strSQ1_APPN_PRC)    '1차지정가격
            strAVR_CNCS_PRC = FuncNumericString(strAVR_CNCS_PRC)    '평균체결가격
            strCNCS_RT = FuncNumericString(strCNCS_RT)     '체결율
            strNOW_PRC = FuncNumericString(strNOW_PRC)     '현재가격
            strMDIA_DCD = Trim(strMDIA_DCD)    '매체구분코드
            strORDR_DCD = Trim(strORDR_DCD)    '주문구분코드
            strORDR_STTS_DCD = Trim(strORDR_STTS_DCD)   '주문상태구분코드
            strFCM_ODNO = Trim(strFCM_ODNO)    'FCM주문번호
            strUSER_ID = Trim(strUSER_ID)     '사용자ID
            strATHZ_IP_ADDR = Trim(strATHZ_IP_ADDR)    '공인IP주소
            strACPT_TM = Trim(strACPT_TM)     '접수시각
            strCNCS_TM = Trim(strCNCS_TM)     '체결시각
            strACPL_ACPT_TM = Trim(strACPL_ACPT_TM)    '현지접수시각
            strCNCS_DETL_DTM = Trim(strCNCS_DETL_DTM)   '체결상세일시
            strCRRY_CD = Trim(strCRRY_CD)     '통화코드

            Sheet10.Cells(nRow, 1) = strCANO     '종합계좌번호
            Sheet10.Cells(nRow, 2) = strODRV_ODNO        '해외파생주문번호
            Sheet10.Cells(nRow, 3) = strPRDT_CD      '상품코드
            Sheet10.Cells(nRow, 4) = strODRV_OR_ODNO     '해외파생원주문번호
            Sheet10.Cells(nRow, 5) = strODRV_MO_ODNO     '해외파생모주문번호
            Sheet10.Cells(nRow, 6) = strORDR_GRUP_NO     '주문그룹번호
            Sheet10.Cells(nRow, 7) = strORDR_DT      '주문일자
            Sheet10.Cells(nRow, 8) = strACNT_PRDT_CD     '계좌상품코드
            Sheet10.Cells(nRow, 9) = strCUST_NM      '고객명
            Sheet10.Cells(nRow, 10) = strSELL_BUY_DCD     '매도매수구분코드
            Sheet10.Cells(nRow, 11) = strODRV_ORDR_PRC       '해외파생주문가격
            Sheet10.Cells(nRow, 12) = strORDR_QNT        '주문수량
            Sheet10.Cells(nRow, 13) = strRVSE_QNT        '정정수량
            Sheet10.Cells(nRow, 14) = strCNCL_QNT        '취소수량
            Sheet10.Cells(nRow, 15) = strCNCS_QNT        '체결수량
            Sheet10.Cells(nRow, 16) = strRMN_QNT     '잔여수량
            Sheet10.Cells(nRow, 17) = strPRC_CND_DCD     '가격조건구분코드
            Sheet10.Cells(nRow, 18) = strCNCS_CND_DCD        '체결조건구분코드
            Sheet10.Cells(nRow, 19) = strSQ1_APPN_PRC        '1차지정가격
            Sheet10.Cells(nRow, 20) = strAVR_CNCS_PRC        '평균체결가격
            Sheet10.Cells(nRow, 21) = strCNCS_RT     '체결율
            Sheet10.Cells(nRow, 22) = strNOW_PRC     '현재가격
            Sheet10.Cells(nRow, 23) = strMDIA_DCD        '매체구분코드
            Sheet10.Cells(nRow, 24) = strORDR_DCD        '주문구분코드
            Sheet10.Cells(nRow, 25) = strORDR_STTS_DCD       '주문상태구분코드
            Sheet10.Cells(nRow, 26) = strFCM_ODNO        'FCM주문번호
            Sheet10.Cells(nRow, 27) = strUSER_ID     '사용자ID
            Sheet10.Cells(nRow, 28) = strATHZ_IP_ADDR        '공인IP주소
            Sheet10.Cells(nRow, 29) = strACPT_TM     '접수시각
            Sheet10.Cells(nRow, 30) = strCNCS_TM     '체결시각
            Sheet10.Cells(nRow, 31) = strACPL_ACPT_TM        '현지접수시각
            Sheet10.Cells(nRow, 32) = strCNCS_DETL_DTM       '체결상세일시
            Sheet10.Cells(nRow, 33) = strCRRY_CD     '통화코드

            nRow = nRow + 1
        Next

        '*--------------------------------------
        '연속조회키를 저장해 놓는다.
        '---------------------------------------*
        g_strListExecNextRqKey = strPreNextContext

        '*--------------------------------------
        '연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
        '---------------------------------------*
        If strPreNext = "2" Or strPreNext = "3" Then
            Sheet10.NextRequestExecButton.Enabled = True
        Else
            Sheet10.NextRequestExecButton.Enabled = False
        End If

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*
        g_nRqIdExecList = 0 '주문체결조회 Rq ID

    '잔고 조회
    ElseIf g_nRqIdBalanceList = nRequestId Then

        Dim strPRDT_NM, strODRV_SELL_BUY_DCD, _
            strUSTL_CTRC_QNT, strTRDE_AVR_UNPR, strCLR_PSBL_QNT, strORDR_RMN_QNT, strODRV_NOW_PRC, _
            strODRV_BFDT_PRPT, strODRV_BFDT_PRPT_RT, strODRV_EVL_AMT, strODRV_EVL_PFLS_AMT, _
            strODRV_PFLS_RT, strUSTL_CTRC_AMT, strTRSL_MLT, strODRV_FTOP_DCD, _
            strMNGM_BDCD, strMNGM_BR_NM, strMNGM_EMPNO, strMNGR_NM, strPRC_DCPN_BLW_LNG, _
            strINDC_PRC As String

        nRowCnt = Sheet10.Cells(Sheet10.Rows.Count, "A").End(xlUp).Row + 1
        nRow = nRowCnt

        nDataCnt = HFCommAgent1.GetTranOutputRowCnt(strTrCode, "OTS5919Q41_out_sub01")

        For i = 0 To nDataCnt - 1

            strCANO = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CANO", i)      '종합계좌번호
            strCTNO = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CTNO", i)      '대체종합계좌번호
            strAPNO = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "APNO", i)      '계좌상품번호
            strCUST_NM = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CUST_NM", i)        '고객명
            strPRDT_CD = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "PRDT_CD", i)        '상품코드
            strPRDT_NM = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "PRDT_NM", i)        '상품명
            strODRV_SELL_BUY_DCD = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_SELL_BUY_DCD", i)        '해외파생매도매수구분코드
            strUSTL_CTRC_QNT = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "USTL_CTRC_QNT", i)        '미결제약정수량
            strTRDE_AVR_UNPR = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "TRDE_AVR_UNPR", i)        '매매평균단가
            strCLR_PSBL_QNT = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CLR_PSBL_QNT", i)      '청산가능수량
            strORDR_RMN_QNT = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ORDR_RMN_QNT", i)      '주문잔여수량
            strODRV_NOW_PRC = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_NOW_PRC", i)      '해외파생현재가격
            strODRV_BFDT_PRPT = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_BFDT_PRPT", i)      '해외파생전일대비
            strODRV_BFDT_PRPT_RT = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_BFDT_PRPT_RT", i)        '해외파생전일대비율
            strODRV_EVL_AMT = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_EVL_AMT", i)      '해외파생평가금액
            strODRV_EVL_PFLS_AMT = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_EVL_PFLS_AMT", i)        '해외파생평가손익금액
            strODRV_PFLS_RT = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_PFLS_RT", i)      '해외파생손익율
            strUSTL_CTRC_AMT = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "USTL_CTRC_AMT", i)        '미결제약정금액
            strTRSL_MLT = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "TRSL_MLT", i)      '환산승수
            strODRV_FTOP_DCD = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "ODRV_FTOP_DCD", i)        '해외파생선물옵션구분코드
            strCRRY_CD = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "CRRY_CD", i)        '통화코드
            strMNGM_BDCD = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "MNGM_BDCD", i)        '관리부점코드
            strMNGM_BR_NM = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "MNGM_BR_NM", i)      '관리지점명
            strMNGM_EMPNO = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "MNGM_EMPNO", i)      '관리사원번호
            strMNGR_NM = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "MNGR_NM", i)        '관리자명
            strPRC_DCPN_BLW_LNG = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "PRC_DCPN_BLW_LNG", i)      '가격소수점이하길이
            strINDC_PRC = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "INDC_PRC", i)      '표시가격
            strBSN_DT = HFCommAgent1.GetTranOutputData(strTrCode, "OTS5919Q41_out_sub01", "BSN_DT", i)      '영업일자

            strCANO = Trim(strCANO)
            strCTNO = Trim(strCTNO)
            strAPNO = Trim(strAPNO)
            strCUST_NM = Trim(strCUST_NM)
            strPRDT_CD = Trim(strPRDT_CD)
            strPRDT_NM = Trim(strPRDT_NM)
            strODRV_SELL_BUY_DCD = Trim(strODRV_SELL_BUY_DCD)
            strUSTL_CTRC_QNT = FuncNumericString(strUSTL_CTRC_QNT)   '미결제약정수량
            strTRDE_AVR_UNPR = FuncNumericString(strTRDE_AVR_UNPR)   '매매평균단가
            strCLR_PSBL_QNT = FuncNumericString(strCLR_PSBL_QNT)    '청산가능수량
            strORDR_RMN_QNT = FuncNumericString(strORDR_RMN_QNT)    '주문잔여수량
            strODRV_NOW_PRC = FuncNumericString(strODRV_NOW_PRC)    '해외파생현재가격
            strODRV_BFDT_PRPT = FuncNumericString(strODRV_BFDT_PRPT)      '해외파생전일대비
            strODRV_BFDT_PRPT_RT = FuncNumericString(strODRV_BFDT_PRPT_RT)   '해외파생전일대비율
            strODRV_EVL_AMT = FuncNumericString(strODRV_EVL_AMT)    '해외파생평가금액
            strODRV_EVL_PFLS_AMT = FuncNumericString(strODRV_EVL_PFLS_AMT)   '해외파생평가손익금액
            strODRV_PFLS_RT = FuncNumericString(strODRV_PFLS_RT)    '해외파생손익율
            strUSTL_CTRC_AMT = FuncNumericString(strUSTL_CTRC_AMT)   '미결제약정금액
            strTRSL_MLT = FuncNumericString(strTRSL_MLT)    '환산승수
            strODRV_FTOP_DCD = Trim(strODRV_FTOP_DCD)   '해외파생선물옵션구분코드
            strCRRY_CD = Trim(strCRRY_CD)     '통화코드
            strMNGM_BDCD = Trim(strMNGM_BDCD)   '관리부점코드
            strMNGM_BR_NM = Trim(strMNGM_BR_NM)      '관리지점명
            strMNGM_EMPNO = Trim(strMNGM_EMPNO)      '관리사원번호
            strMNGR_NM = Trim(strMNGR_NM)     '관리자명
            strPRC_DCPN_BLW_LNG = FuncNumericString(strPRC_DCPN_BLW_LNG)    '가격소수점이하길이
            strINDC_PRC = FuncNumericString(strINDC_PRC)    '표시가격
            strBSN_DT = Trim(strBSN_DT)      '영업일자

            Sheet11.Cells(nRow, 1) = strCANO      '종합계좌번호
            Sheet11.Cells(nRow, 2) = strCTNO      '대체종합계좌번호
            Sheet11.Cells(nRow, 3) = strAPNO      '계좌상품번호
            Sheet11.Cells(nRow, 4) = strCUST_NM       '고객명
            Sheet11.Cells(nRow, 5) = strPRDT_CD       '상품코드
            Sheet11.Cells(nRow, 6) = strPRDT_NM       '상품명
            Sheet11.Cells(nRow, 7) = strODRV_SELL_BUY_DCD     '해외파생매도매수구분코드
            Sheet11.Cells(nRow, 8) = strUSTL_CTRC_QNT     '미결제약정수량
            Sheet11.Cells(nRow, 9) = strTRDE_AVR_UNPR     '매매평균단가
            Sheet11.Cells(nRow, 10) = strCLR_PSBL_QNT      '청산가능수량
            Sheet11.Cells(nRow, 11) = strORDR_RMN_QNT     '주문잔여수량
            Sheet11.Cells(nRow, 12) = strODRV_NOW_PRC     '해외파생현재가격
            Sheet11.Cells(nRow, 13) = strODRV_BFDT_PRPT       '해외파생전일대비
            Sheet11.Cells(nRow, 14) = strODRV_BFDT_PRPT_RT        '해외파생전일대비율
            Sheet11.Cells(nRow, 15) = strODRV_EVL_AMT     '해외파생평가금액
            Sheet11.Cells(nRow, 16) = strODRV_EVL_PFLS_AMT        '해외파생평가손익금액
            Sheet11.Cells(nRow, 17) = strODRV_PFLS_RT     '해외파생손익율
            Sheet11.Cells(nRow, 18) = strUSTL_CTRC_AMT        '미결제약정금액
            Sheet11.Cells(nRow, 19) = strTRSL_MLT     '환산승수
            Sheet11.Cells(nRow, 20) = strODRV_FTOP_DCD        '해외파생선물옵션구분코드
            Sheet11.Cells(nRow, 21) = strCRRY_CD      '통화코드
            Sheet11.Cells(nRow, 22) = strMNGM_BDCD        '관리부점코드
            Sheet11.Cells(nRow, 23) = strMNGM_BR_NM       '관리지점명
            Sheet11.Cells(nRow, 24) = strMNGM_EMPNO       '관리사원번호
            Sheet11.Cells(nRow, 25) = strMNGR_NM      '관리자명
            Sheet11.Cells(nRow, 26) = strPRC_DCPN_BLW_LNG     '가격소수점이하길이
            Sheet11.Cells(nRow, 27) = strINDC_PRC     '표시가격
            Sheet11.Cells(nRow, 28) = strBSN_DT       '영업일자

            nRow = nRow + 1

        Next

        '*--------------------------------------
        '연속조회키를 저장해 놓는다.
        '---------------------------------------*
        g_strListBalanceNextRqKey = strPreNextContext

        '*--------------------------------------
        '연속조회키가 '2', '3'이면 '다음'버튼을 활성화 시킨다.
        '---------------------------------------*
        If strPreNext = "2" Or strPreNext = "3" Then
            Sheet11.NextRequestBalanceButton.Enabled = True
        Else
            Sheet11.NextRequestBalanceButton.Enabled = False
        End If

        '*--------------------------------------
        '반드시 사용이 끝난 RQ ID는 0으로 초기화한다.
        '---------------------------------------*
        g_nRqIdBalanceList = 0  '주문체결조회 Rq ID

    End If

    If strIsError = "1" Then
        MsgBox "[오류] " & strMsg & "(" & strErrMsg & ")"
    Else
        MsgBox strMsg
    End If

End Sub

Private Sub HFCommAgent1_OnGetRealData(ByVal strRealName As String, ByVal strRealKey As String, ByVal pBlock As String, ByVal nBlockLength As Long)
'*************************************************
'* 함수명 :HFCommAgent1_OnGetRealData
'* 인  자 :ByVal strRealName As String, ByVal strRealKey As String, ByVal pBlock As String, ByVal nBlockLength As Long
'* 설  명 :시세/주문체결 데이터를 서버로부터 실시간으로 수신하는 이벤트
'*************************************************

    ' 주의 : OnGetRealData 이벤트에서 인자 또는 함수로 얻은 값은 모두 휘발성으로
    '이벤트 콜백함수 종료 후에는 유효하지 않습니다.

    Dim strRealMessage As String

    Dim strrltm_dpch_dcd, strusr_id, strrltm_dpch_prcs_dcd, strCANO, strCTNO, strAPNO, _
        strODRV_ODNO, strPRDT_CD, strODRV_OR_ODNO, strODRV_MO_ODNO, strORDR_GRUP_NO, _
        strORDR_DT, strCUST_NM, strODRV_SELL_BUY_DCD, strodrv_ordr_prc_ctns, strordr_qnt_ctns, _
        strrvse_qnt_ctns, strcncl_qnt_ctns, strcncs_qnt_smm_ctns, strordr_rmn_qnt_ctns, _
        strodrv_prc_dcd, strCNCS_CND_DCD, strcnd_prc_ctns, stravr_cncs_prc_ctns, strodrv_pv_ctns, _
        strcncs_rt_ctns, strcomm_mdia_dcd, strodrv_ordr_tp_dcd, strORDR_STTS_DCD, strFCM_ODNO, _
        strATHZ_IP_ADDR, strACPT_TM, strexcg_cncs_tm, strACPL_ACPT_TM, strCNCS_TM, strcncs_dt, _
        strCRRY_CD, strcncs_qnt_ctns, strordr_expr_dt, stracnt_dcd, strentr_clr_dcd, strclr_pst_no, _
        strodrv_cncs_no, strodrv_cncs_prc_ctns, strodrv_cncs_amt_ctns As String

    '***************************************
    '* 해외선물 호가 실시간 데이터 수신
    '***************************************
    If strRealName = "V11" Then

        '*--------------------------------------
        '조회 시점에 등록한 해외선물 호가 실시간키와 동일한지 비교
        '---------------------------------------*/
        If g_strHogaRealKey = strRealKey Then


            '*--------------------------------------
            '에이전트 컨트롤의 GetRealOutputData 함수로 아이템별 데이터를 빼낸다.
            '---------------------------------------*
            '*--------------------------------------
            '아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
            '---------------------------------------*
            '매도 1~5호가
            Sheet3.Cells(8, 3) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ASK1"))
            Sheet3.Cells(7, 3) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ASK2"))
            Sheet3.Cells(6, 3) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ASK3"))
            Sheet3.Cells(5, 3) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ASK4"))
            Sheet3.Cells(4, 3) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ASK5"))

            '매도 1~5호가잔량
            Sheet3.Cells(8, 2) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ASIZ1"))
            Sheet3.Cells(7, 2) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ASIZ2"))
            Sheet3.Cells(6, 2) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ASIZ3"))
            Sheet3.Cells(5, 2) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ASIZ4"))
            Sheet3.Cells(4, 2) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ASIZ5"))

            '매도 1~5호가건수
            Sheet3.Cells(8, 1) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ACNT1"))
            Sheet3.Cells(7, 1) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ACNT2"))
            Sheet3.Cells(6, 1) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ACNT3"))
            Sheet3.Cells(5, 1) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ACNT4"))
            Sheet3.Cells(4, 1) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_ACNT5"))

            '매수 1~5호가
            Sheet3.Cells(9, 3) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BID1"))
            Sheet3.Cells(10, 3) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BID2"))
            Sheet3.Cells(11, 3) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BID3"))
            Sheet3.Cells(12, 3) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BID4"))
            Sheet3.Cells(13, 3) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BID5"))

            '매수 1~5호가잔량
            Sheet3.Cells(9, 4) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BSIZ1"))
            Sheet3.Cells(10, 4) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BSIZ2"))
            Sheet3.Cells(11, 4) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BSIZ3"))
            Sheet3.Cells(12, 4) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BSIZ4"))
            Sheet3.Cells(13, 4) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BSIZ5"))

            '매수 1~5호가건수
            Sheet3.Cells(9, 5) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BCNT1"))
            Sheet3.Cells(10, 5) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BCNT2"))
            Sheet3.Cells(11, 5) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BCNT3"))
            Sheet3.Cells(12, 5) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BCNT4"))
            Sheet3.Cells(13, 5) = Trim(HFCommAgent1.GetRealOutputData(strRealName, "BEST_BCNT5"))

        End If

    '***************************************
    '* 해외선물 체결(현재가) 실시간 데이터 수신
    '****************************************
    ElseIf strRealName = "V10" Then

        Dim strCurPrice As String '현재가
        Dim strDiffSign As String '부호
        Dim strDiff As String '전일대비
        Dim strDiffRate As String '대비율
        Dim strVolume As String '거래량

        Dim strOpenPrice As String      '시가
        Dim strHighPrice As String        '고가
        Dim strLowPrice As String          '저가

        Dim strTime  As String  '체결시간
        Dim strExecVolume As String '체결량

        '*--------------------------------------
        '아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
        '---------------------------------------*
        strCurPrice = Trim(HFCommAgent1.GetRealOutputData(strRealName, "TRDPRC_1"))       '현재가
        strDiffSign = Trim(HFCommAgent1.GetRealOutputData(strRealName, "NETCHNG_CLS"))    '부호
        strDiff = Trim(HFCommAgent1.GetRealOutputData(strRealName, "NETCHNG_1"))          '전일대비
        strDiffRate = Trim(HFCommAgent1.GetRealOutputData(strRealName, "PCTCHNG_1"))      '대비율
        strVolume = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ACVOL_1"))          '거래량

        strOpenPrice = Trim(HFCommAgent1.GetRealOutputData(strRealName, "OPEN_PRC"))      '시가
        strHighPrice = Trim(HFCommAgent1.GetRealOutputData(strRealName, "HIGH_1"))        '고가
        strLowPrice = Trim(HFCommAgent1.GetRealOutputData(strRealName, "LOW_1"))          '저가

        strTime = Trim(HFCommAgent1.GetRealOutputData(strRealName, "TRADE_TIME"))         '체결시간
        strExecVolume = Trim(HFCommAgent1.GetRealOutputData(strRealName, "TRDVOL_1"))     '체결량

        '*--------------------------------------
        '조회 시점에 등록한 해외선물 현재가 실시간키와 동일한지 비교
        '---------------------------------------*
        If g_strCurPriceRealKey = strRealKey Then
            Sheet3.Cells(3, 8) = strCurPrice       '현재가
            Sheet3.Cells(4, 8) = strDiffSign     '부호
            Sheet3.Cells(5, 8) = strDiff         '전일대비
            Sheet3.Cells(6, 8) = strDiffRate     '대비율
            Sheet3.Cells(7, 8) = strVolume      '거래량

            Sheet3.Cells(9, 8) = strOpenPrice   '시가
            Sheet3.Cells(10, 8) = strHighPrice   '고가
            Sheet3.Cells(11, 8) = strLowPrice    '저가
        End If

        '*--------------------------------------
        '조회 시점에 등록한 해외선물 시간대별 체결 실시간키와 동일한지 비교
        '---------------------------------------*
        If g_strTickRealKey = strRealKey Then

            Sheet4.Cells(2, 11) = strTime        '시간
            Sheet4.Cells(2, 12) = strCurPrice    '체결가
            Sheet4.Cells(2, 13) = strDiff        '대비
            Sheet4.Cells(2, 14) = strDiffRate    '등률
            Sheet4.Cells(2, 15) = strExecVolume  '체결량

        End If
    '***************************************
    '* 해외선물체결확인
    '***************************************
    ElseIf strRealName = "EF1" Then

        '*--------------------------------------
        ' 아이템명으로 수신될 실시간 데이터를 항목별로 빼낸다.
        '---------------------------------------*

        strrltm_dpch_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "rltm_dpch_dcd"))        '실시간통보구분코드
        strusr_id = Trim(HFCommAgent1.GetRealOutputData(strRealName, "usr_id"))          '사용자ID
        strrltm_dpch_prcs_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "rltm_dpch_prcs_dcd"))      '실시간통보처리구분코드
        strCANO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cano"))      '종합계좌번호
        strCTNO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ctno"))      '대체종합계좌번호
        strAPNO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "apno"))      '계좌상품번호
        strPRDT_CD = Trim(HFCommAgent1.GetRealOutputData(strRealName, "prdt_cd"))        '상품코드
        strodrv_ordr_tp_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_ordr_tp_dcd"))      '해외파생주문유형구분코드
        strORDR_STTS_DCD = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ordr_stts_dcd"))        '주문상태구분코드
        strODRV_ODNO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_odno"))        '해외파생주문번호
        strODRV_OR_ODNO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_or_odno"))      '해외파생원주문번호
        strORDR_DT = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ordr_dt"))        '주문일자
        strCUST_NM = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cust_nm"))        '고객명
        strODRV_SELL_BUY_DCD = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_sell_buy_dcd"))        '해외파생매도매수구분코드
        strodrv_ordr_prc_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_ordr_prc_ctns"))      '해외파생주문가격내용
        strordr_qnt_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ordr_qnt_ctns"))        '주문수량내용
        strodrv_prc_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_prc_dcd"))      '해외파생가격구분코드
        strCNCS_CND_DCD = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cncs_cnd_dcd"))      '체결조건구분코드
        strcnd_prc_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cnd_prc_ctns"))      '조건가격내용
        strcomm_mdia_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "comm_mdia_dcd"))        '통신매체구분코드
        strACPT_TM = Trim(HFCommAgent1.GetRealOutputData(strRealName, "acpt_tm"))        '접수시각
        strexcg_cncs_tm = Trim(HFCommAgent1.GetRealOutputData(strRealName, "excg_cncs_tm"))      '거래소체결시각
        strACPL_ACPT_TM = Trim(HFCommAgent1.GetRealOutputData(strRealName, "acpl_acpt_tm"))      '현지접수시각
        strCNCS_TM = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cncs_tm"))        '체결시각
        strcncs_dt = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cncs_dt"))        '체결일자
        strodrv_cncs_no = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_cncs_no"))      '해외파생체결번호
        strcncs_qnt_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cncs_qnt_ctns"))        '체결수량내용
        strodrv_cncs_prc_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_cncs_prc_ctns"))      '해외파생체결가격내용
        strodrv_cncs_amt_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_cncs_amt_ctns"))      '해외파생체결금액내용
        strCRRY_CD = Trim(HFCommAgent1.GetRealOutputData(strRealName, "crry_cd"))        '통화코드
        strordr_rmn_qnt_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ordr_rmn_qnt_ctns"))        '주문잔여수량내용
        stracnt_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "acnt_dcd"))      '계좌구분코드
        strentr_clr_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "entr_clr_dcd"))      '진입청산구분코드
        strclr_pst_no = Trim(HFCommAgent1.GetRealOutputData(strRealName, "clr_pst_no"))      '청산포지션번호

        '*--------------------------------------
        '조회 시점에 등록한 주식 현재가 실시간키와 동일한지 비교
        '---------------------------------------*
        If g_strLoginID = strRealKey Then
            strRealMessage = "[" & strRealName & "][계좌:" & strCANO & "][상품:" & strPRDT_CD & "][체결:" & strcncs_qnt_ctns & "]"
        End If


    '***************************************
    '* 해외선물미체결
    '****************************************
    ElseIf strRealName = "EF4" Then

        strrltm_dpch_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "rltm_dpch_dcd"))        '실시간통보구분코드
        strusr_id = Trim(HFCommAgent1.GetRealOutputData(strRealName, "usr_id"))      '사용자ID
        strrltm_dpch_prcs_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "rltm_dpch_prcs_dcd"))      '실시간통보처리구분코드
        strCANO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cano"))      '종합계좌번호
        strCTNO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ctno"))      '대체종합계좌번호
        strAPNO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "apno"))      '계좌상품번호
        strODRV_ODNO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_odno"))        '해외파생주문번호
        strPRDT_CD = Trim(HFCommAgent1.GetRealOutputData(strRealName, "prdt_cd"))        '상품코드
        strODRV_OR_ODNO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_or_odno"))      '해외파생원주문번호
        strODRV_MO_ODNO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_mo_odno"))      '해외파생모주문번호
        strORDR_GRUP_NO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ordr_grup_no"))      '주문그룹번호
        strORDR_DT = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ordr_dt"))        '주문일자
        strCUST_NM = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cust_nm"))        '고객명
        strODRV_SELL_BUY_DCD = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_sell_buy_dcd"))        '해외파생매도매수구분코드
        strodrv_ordr_prc_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_ordr_prc_ctns"))      '해외파생주문가격내용
        strordr_qnt_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ordr_qnt_ctns"))        '주문수량내용
        strrvse_qnt_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "rvse_qnt_ctns"))        '정정수량내용
        strcncl_qnt_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cncl_qnt_ctns"))        '취소수량내용
        strcncs_qnt_smm_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cncs_qnt_smm_ctns"))        '체결수량합계내용
        strordr_rmn_qnt_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ordr_rmn_qnt_ctns"))        '주문잔여수량내용
        strodrv_prc_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_prc_dcd"))      '해외파생가격구분코드
        strCNCS_CND_DCD = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cncs_cnd_dcd"))      '체결조건구분코드
        strcnd_prc_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cnd_prc_ctns"))      '조건가격내용
        stravr_cncs_prc_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "avr_cncs_prc_ctns"))        '평균체결가격내용
        strodrv_pv_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_pv_ctns"))      '해외파생현재가내용
        strcncs_rt_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cncs_rt_ctns"))      '체결율내용
        strcomm_mdia_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "comm_mdia_dcd"))        '통신매체구분코드
        strodrv_ordr_tp_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "odrv_ordr_tp_dcd"))      '해외파생주문유형구분코드
        strORDR_STTS_DCD = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ordr_stts_dcd"))        '주문상태구분코드
        strFCM_ODNO = Trim(HFCommAgent1.GetRealOutputData(strRealName, "fcm_odno"))      'FCM주문번호
        strATHZ_IP_ADDR = Trim(HFCommAgent1.GetRealOutputData(strRealName, "athz_ip_addr"))      '공인IP주소
        strACPT_TM = Trim(HFCommAgent1.GetRealOutputData(strRealName, "acpt_tm"))        '접수시각
        strexcg_cncs_tm = Trim(HFCommAgent1.GetRealOutputData(strRealName, "excg_cncs_tm"))      '거래소체결시각
        strACPL_ACPT_TM = Trim(HFCommAgent1.GetRealOutputData(strRealName, "acpl_acpt_tm"))      '현지접수시각
        strCNCS_TM = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cncs_tm"))        '체결시각
        strCRRY_CD = Trim(HFCommAgent1.GetRealOutputData(strRealName, "crry_cd"))        '통화코드
        strcncs_qnt_ctns = Trim(HFCommAgent1.GetRealOutputData(strRealName, "cncs_qnt_ctns"))        '체결수량내용
        strordr_expr_dt = Trim(HFCommAgent1.GetRealOutputData(strRealName, "ordr_expr_dt"))      '주문만료일자
        stracnt_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "acnt_dcd"))      '계좌구분코드
        strentr_clr_dcd = Trim(HFCommAgent1.GetRealOutputData(strRealName, "entr_clr_dcd"))      '진입청산구분코드
        strclr_pst_no = Trim(HFCommAgent1.GetRealOutputData(strRealName, "clr_pst_no"))      '청산포지션번호

        '*--------------------------------------
        '조회 시점에 등록한 주식 현재가 실시간키와 동일한지 비교
        '---------------------------------------*
        If g_strLoginID = strRealKey Then
            strRealMessage = "[" & strRealName & "][주문상태:" & strORDR_STTS_DCD & "][계좌:" & strCANO & "][상품:" & _
                            strPRDT_CD & "][주문수:" & strordr_qnt_ctns & "][정정수:" & strrvse_qnt_ctns & "][취소수:" & strcncl_qnt_ctns & "]"
        End If

    End If

    If strRealMessage <> "" Then
        MsgBox strRealMessage
    End If

End Sub

Private Sub LoginOptionBtn1_Click()
    Call FuncSetLoginMode(0) '운영
End Sub

Private Sub LoginOptionBtn2_Click()
    Call FuncSetLoginMode(1) '국내모의
End Sub

Private Sub LoginOptionBtn3_Click()
    Call FuncSetLoginMode(2) '해외모의
End Sub
