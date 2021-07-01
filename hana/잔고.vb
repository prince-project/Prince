
Private Sub ClearRequestBalanceButton_Click()
'*************************************************
'* 함수명 : ClearRequestBalanceButton_Click
'* 인  자 :
'* 설  명 : 잔고 조회 클리어
'*************************************************

    '실제 그리드에 데이터가 입력된 행수를 구한다.
    Dim nRowCnt As Long
    nRowCnt = Sheet11.Cells(Sheet11.Rows.Count, "A").End(xlUp).Row

    '기존의 데이터를 삭제한다.
    Dim strRows As String
    strRows = "4:" & CStr(nRowCnt)
    If nRowCnt > 3 Then Sheet11.Rows(strRows).Delete

End Sub

Private Sub NextRequestBalanceButton_Click()
'*************************************************
'* 함수명 : RequestBalanceButton_Click
'* 인  자 :
'* 설  명 : 잔고 연속 조회
'*************************************************
    Dim strTrCode, strInRecName1, strInRecName2 As String

    strTrCode = "OTS5919Q41"                'Tran코드(리소스파일 참고)
    strInRecName1 = "OTS5919Q41_in" '입력 레코드명(리소스파일 참고)
    strInRecName2 = "OTS5919Q41_in_sub01"   '입력 레코드명(리소스파일 참고)

    Dim strODRV_SELL_BUY_DCD As String   '해외파생매도매수구분코드(0:전체, B:매수, S:매도)
    Dim strCTNO As String             '대체종합계좌번호
    Dim strAPNO As String             '계좌상품번호

    strODRV_SELL_BUY_DCD = "0"  '해외파생매도매수구분코드(0:전체, B:매수, S:매도)

    '*-------------------------------*
    '[1] Request ID생성
    '*-------------------------------*
    g_nRqIdBalanceList = Sheet1.HFCommAgent1.CreateRequestID()

    Call Sheet1.HFCommAgent1.SetTranInputData(m_nRqIdBalanceList, strTrCode, strInRecName1, "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD)       '해외파생매도매수구분코드

    '*-------------------------------*
    '[2] 입력 건수를 입력한다.
    '*-------------------------------*
    ' REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=
    'ARRAY 가 '0'보다 크면 입력이 복수건이다.
    Dim nInputCnt As Long
    nInputCnt = 1
    Call Sheet1.HFCommAgent1.SetTranInputArrayCnt(m_nRqIdBalanceList, strTrCode, strInRecName2, nInputCnt)

    Dim strAccNo
    Dim strPrdt
    Dim strPWD

    '[3] Tran조회 입력값을 입력한다.
    For i = 0 To 2
        '계좌대체번호를 얻어온다.
        strAccNo = Trim(AccNoTextBox.Text)

        '계좌상품번호
        strPrdt = Trim(APNOTextBox.Text)
        strCTNO = Sheet6.FuncGetAccAPNO(strAccNo + strPrdt) '종합계좌대체번호 조회

        '계좌비밀번호
        strPWD = Trim(AccPwdTextBox.Text)
        strPWD = Sheet1.HFCommAgent1.GetEncrpyt(strPWD)

        '대체종합계좌번호
        Call Sheet1.HFCommAgent1.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "CTNO", strCTNO, i)

        '계좌상품번호
        Call Sheet1.HFCommAgent1.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "APNO", strPrdt, i)

        '계좌비밀번호
        Call Sheet1.HFCommAgent1.SetTranInputArrayData(m_nRqIdBalanceList, strTrCode, strInRecName2, "PWD", strPWD, i)
    Next

    Dim strBenefitAcc, strPreNext, strScreenNo As String

    strBenefitAcc = "N" '수익증권계좌 구분
    strPreNext = "3"        '연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
    strScreenNo = "9999"    '화면번호

    Dim nRequestDataCnt As Long
    nRequestDataCnt = 0         '응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

    '[4] 서버에 Tran조회 요청한다.
    If Sheet1.HFCommAgent1.RequestTran(g_nRqIdBalanceList, strTrCode, strBenefitAcc, strPreNext, g_strListBalanceNextRqKey, strScreenNo, "Q", 0) < 0 Then
        MsgBox Sheet1.HFCommAgent1.GetLastErrMsg()
    End If

End Sub

Private Sub RequestBalanceButton_Click()
'*************************************************
'* 함수명 : RequestBalanceButton_Click
'* 인  자 :
'* 설  명 : 잔고 조회
'*************************************************

    '조회 데이터 지운다.
    Call ClearRequestBalanceButton_Click

    Dim strTrCode, strInRecName1, strInRecName2 As String

    strTrCode = "OTS5919Q41"                'Tran코드(리소스파일 참고)
    strInRecName1 = "OTS5919Q41_in" '입력 레코드명(리소스파일 참고)
    strInRecName2 = "OTS5919Q41_in_sub01"   '입력 레코드명(리소스파일 참고)

    Dim strODRV_SELL_BUY_DCD As String  '해외파생매도매수구분코드(0:전체, B:매수, S:매도)
    Dim strCTNO As String             '대체종합계좌번호
    Dim strAPNO As String             '계좌상품번호

    strODRV_SELL_BUY_DCD = "0"  '해외파생매도매수구분코드(0:전체, B:매수, S:매도)

    '*-------------------------------*
    '[1] Request ID생성
    '*-------------------------------*
    g_nRqIdBalanceList = Sheet1.HFCommAgent1.CreateRequestID()

    Call Sheet1.HFCommAgent1.SetTranInputData(g_nRqIdBalanceList, strTrCode, strInRecName1, "ODRV_SELL_BUY_DCD", strODRV_SELL_BUY_DCD)      '해외파생매도매수구분코드

    '*-------------------------------*
    '[2] 입력 건수를 입력한다.
    '*-------------------------------*
    '  REC_NAME=OTS5911Q52_in_sub01, INOUT=0, ARRAY=1, ARRINFO=
    'ARRAY 가 '0'보다 크면 입력이 복수건이다.
    Dim nInputCnt As Long
    nInputCnt = 1

    Call Sheet1.HFCommAgent1.SetTranInputArrayCnt(g_nRqIdBalanceList, strTrCode, strInRecName2, 1)

    Dim strAccNo, strPrdt, strPWD As String
    Dim i As Long

    '[3] Tran조회 입력값을 입력한다.
    For i = 0 To 2

        '계좌대체번호를 얻어온다.
        strAccNo = Trim(AccNoTextBox.Text)

        '계좌상품번호
        strPrdt = Trim(APNOTextBox.Text)
        strCTNO = Sheet6.FuncGetAccAPNO(strAccNo + strPrdt) '종합계좌대체번호 조회

        '계좌비밀번호
        strPWD = Trim(AccPwdTextBox.Text)
        strPWD = Sheet1.HFCommAgent1.GetEncrpyt(strPWD)

        '대체종합계좌번호
        Call Sheet1.HFCommAgent1.SetTranInputArrayData(g_nRqIdBalanceList, strTrCode, strInRecName2, "CTNO", strCTNO, i)

        '계좌상품번호
        Call Sheet1.HFCommAgent1.SetTranInputArrayData(g_nRqIdBalanceList, strTrCode, strInRecName2, "APNO", strPrdt, i)

        '계좌비밀번호
        Call Sheet1.HFCommAgent1.SetTranInputArrayData(g_nRqIdBalanceList, strTrCode, strInRecName2, "PWD", strPWD, i)
    Next

    Dim strBenefitAcc, strPreNext, strScreenNo As String

    strBenefitAcc = "N" '수익증권계좌 구분
    strPreNext = "1"        '연속조회("0"-일반, "1"-연속조회 첫 조회, "2"-이전조회, "3"-다음조회)
    strScreenNo = "9999"    '화면번호

    Dim nRequestDataCnt As Long
    nRequestDataCnt = 0         '응답 데이터 건수(0으로 입력하면 Default 응답 건수가 입력된다.

    '[4] 서버에 Tran조회 요청한다.
    If Sheet1.HFCommAgent1.RequestTran(g_nRqIdBalanceList, strTrCode, strBenefitAcc, strPreNext, "", strScreenNo, "Q", 0) < 0 Then
        MsgBox Sheet1.HFCommAgent1.GetLastErrMsg()
    End If

End Sub
