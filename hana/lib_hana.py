import sys
from PyQt5.QtWidgets import *
from PyQt5.QAxContainer import *
import pythoncom
import datetime
#from pykiwoom import parser
import pandas as pd
import numpy as np
import time
import logging


class HanaAPI:
    def __init__(self, login=False):
        self.ocx = QAxWidget("HFCOMMAGENT.HFCommAgentCtrl.1")
        self.connected = False              # for login event
        self.request_id = 0
        self.tran_code = None
        self.prev_next_code = None
        self.prev_next_key = None
        self.msg_code = None
        self.msg = None
        self.sub_msg_code = None
        self.sub_msg = None
        self.fid_list = None
        self.fid_data = None
        self.data_cnt = None
        self.tmp_verify = None
        self.cur_price_real_key = None
        self.res_info = None
        self.output_rec_name = None        
        self.tr_code = None
        self.tr_data = None
        self.rq_id_hoga = 0
        self.rq_id_cur_price = 0
        self.rq_id_tick = 0
        self.rq_id_code_list = 0
        self.rq_id_code_list2 = 0
        self.rq_id_chart = 0
        
        

        self.received = False               # for tr event
        self.tr_items = None                # tr input/output items
        self.tr_data = None                 # tr output data
        self.next = None
        self.tr_record = None
        self.tr_remained = False
        self._set_signals_slots()

        if login:
            self.CommConnect()

    def _event_connect(self, nEventType, nParam, strParam):
        if nEventType >= 150:
            print(strParam)

    def _event_fid(self, nRequestId, pBlock, nBlockLength):
        logging.info(f"logging - OnGetFidData")
        print('*** OnGetFidData ***')

        self.prev_next_code = self.GetCommRecvOptionValue(1)
        self.prev_next_key = self.GetCommRecvOptionValue(2)
        self.msg_code = self.GetCommRecvOptionValue(3)
        self.msg = self.GetCommRecvOptionValue(4)
        self.sub_msg_code = self.GetCommRecvOptionValue(5)
        self.sub_msg = self.GetCommRecvOptionValue(6)

        #if self.request_id == nRequestId:
        #    self.data_cnt = self.GetFidOutputRowCnt(nRequestId)
        #    print(nRequestId)
        #    print(self.data_cnt)
        #    self.fid_data = pd.DataFrame(index=np.arange(self.data_cnt), columns=self.fid_list)
        #    for i in np.arange(self.data_cnt):
        #        for k in np.arange(len(self.fid_list)):
        #            self.fid_data.loc[i, self.fid_list[k]] = self.GetFidOutputData(nRequestId, self.fid_list[k], i)
        #            if k == 0:
        #                self.tmp_verify = self.VerifyRequestCode(self.fid_data.loc[i, self.fid_list[k]])
        #                if self.tmp_verify:
        #                    print("+++++++++++++++++++++")
        #                    continue
        #    self.request_id = 0

        if self.rq_id_code_list == nRequestId:
            self.data_cnt = self.GetFidOutputRowCnt(nRequestId)
            print(nRequestId)
            print(self.data_cnt)
            self.fid_data = pd.DataFrame(index=np.arange(self.data_cnt), columns=self.fid_list)
            for i in np.arange(self.data_cnt):
                for k in self.fid_list:
                    self.fid_data.loc[i, k] = self.GetFidOutputData(nRequestId, k, i)
                    if k == 0:
                        self.tmp_verify = self.VerifyRequestCode(self.fid_data.loc[i, k])
                        if self.tmp_verify:
                            print("+++++++++++++++++++++")
                            continue
            #m_strCodeListNextRqKey = strPreNextContext
            self.rq_id_code_list = 0

        if self.rq_id_cur_price == nRequestId:
            self.fid_data = pd.DataFrame(columns=self.fid_list)
            for k in self.fid_list:
                self.fid_data.loc[0, k] = self.GetFidOutputData(nRequestId, k, 0)
            
            if self.cur_price_real_key is not None:
                strRealName = "V10"
                self.RegisterReal(strRealName, self.cur_price_real_key)
            
            self.rq_id_cur_price = 0


        print(self.msg)

    def _event_tran(self, nRequestId, pBlock, nBlockLength):
        logging.info(f"logging - OnGetTranData")
        print('*** OnGeTranData ***')

        self.prev_next_code = self.GetCommRecvOptionValue(1)
        self.prev_next_key = self.GetCommRecvOptionValue(2)
        self.msg_code = self.GetCommRecvOptionValue(3)
        self.msg = self.GetCommRecvOptionValue(4)
        self.sub_msg_code = self.GetCommRecvOptionValue(5)
        self.sub_msg = self.GetCommRecvOptionValue(6)
        print(nRequestId)
        if self.request_id == nRequestId:
            data_cnt = self.GetTranOutputRowCnt(self.tr_code, self.output_rec_name)#self.res_info['output']['rec_name'])
            self.tmp_data_cnt = data_cnt
            self.tr_items = self.res_info['output']['items'].item
            self.tr_data = pd.DataFrame(index=np.arange(data_cnt), columns=self.fid_list)
            for i in np.arange(data_cnt):
                for k in self.tr_items:
                    self.tr_data.loc[i, k] = self.GetTranOutputData(self.tr_code, self.output_rec_name, k, i) #self.res_info['output']['rec_name'], k, i)

        self.request_id = 0

        print(self.msg)


    #-------------------------------------------------------------------------------------------------------------------
    # 이벤트 상세
    #-------------------------------------------------------------------------------------------------------------------
    def _set_signals_slots(self):
        self.ocx.OnAgentEventHandler.connect(self._event_connect)
        self.ocx.OnGetFidData.connect(self._event_fid)
        self.ocx.OnGetTranData.connect(self._event_tran)
        #self.ocx.OnReceiveMsg.connect(self._handler_msg)
        #self.ocx.OnReceiveChejanData.connect(self._handler_chejan)
        

    #-------------------------------------------------------------------------------------------------------------------
    # API 메소드 상세
    #-------------------------------------------------------------------------------------------------------------------

    ## 통신 관련
    def CommInit(self):
        """
        01
        원형: LONG CommInit(void)
        기능: 통신모듈 초기화 및 연결
        호출: 로그인 처리전에 호출한다.
        인자: void
              없음
        반환: LONG
              0: 성공, 음수: 오류
        """
        return self.ocx.dynamicCall("CommInit()")

    def CommTerminate(self, bSocketClose):
        """
        02
        원형: void CommTerminate(LONG bSocketClose)
        기능: 연결 해제
        호출: 로그아웃 처리 이후에 호출한다.
        인자: LONG bSocketClose
              1: 통신모듈 종료 및 연결 해제, 0 : 통신모듈과 연결 해제
        반환: void
              없음
        """
        self.ocx.dynamicCall("CommTerminate(int)", bSocketClose)

    def CommGetConnectState(self):
        """
        03
        원형: LONG CommGetConnectState(void)
        기능: 통신연결 상태 확인
        호출: CommInit 메소드 호출 후 통신연결 상태 확인을 위해 호출한다.
        인자: void	
              없음
        반환: LONG 
              0: 연결 끊김, 1: 연결
        """
        return self.ocx.dynamicCall("CommGetConnectState()")

    def CommLogin(self, sUserID, sPwd, sCertPwd):
        """
        04
        원형: LONG CommLogin(BSTR sUserID, BSTR sPwd, BSTR sCertPwd)
        기능: 로그인 처리
        호출: CommInit 호출 이후 통신 연결이 완료된 이후에 호출한다.
        인자: BSTR sUserID - 로그인 ID
              BSTR sPwd - 로그인 비밀번호
              BSTR sCertPwd	- 공인인증 비밀번호
        반환: LONG
              0: 실패, 1: 성공
        """
        return self.ocx.dynamicCall("CommLogin(QString, QString, QString)", sUserID, sPwd, sCertPwd)

    def CommLogout(self, sUserID):
        """
        05
        원형: LONG CommLogout(BSTR sUserID)
        기능: 로그아웃 처리
        호출: CommTerminate 호출 전에 호출한다.
        인자: BSTR sUserID - 로그인 ID
        반환: LONG
            0: 성공
        """
        return self.ocx.dynamicCall("CommLogout(QString)", sUserID)

    def GetLoginState(self):
        """
        06
        원형: LONG GetLoginState(void)
        기능: 로그인상태 확인
        호출: CommLogin 메소드 호출 이후, 로그인 상태 확인 목적으로 호출한다.
        인자: void
              없음
        반환: LONG
            0: 로그아웃, 1: 로그인
        """
        return self.ocx.dynamicCall("GetLoginState()")

    def SetLoginMode(self, nOption, nMode):
        """
        07
        원형: void SetLoginMode(LONG nOption, LONG nMode)
        기능: 로그인모드 설정
        호출: CommLogin 메소드 호출전, 로그인 접속 설정을 한다..
        인자: LONG nOption
            0: 모의투자 구분, 1: 시세전용 구분
            LONG nMode	
            if nOption(0) then  0:실거래, 1:국내모의, 2:해외모의
            if nOption(1) then  0:공인인증, 1:시세전용
        반 환: void
        예) m_commAgentCtrl.SetLoginMode(0, 0) //실거래 로그인
            m_commAgentCtrl.SetLoginMode(0, 1) //국내모의 로그인
            m_commAgentCtrl.SetLoginMode(1, 1) //시세전용 로그인(인증서X)
        """
        self.ocx.dynamicCall("SetLoginMode(int, int)", nOption, nMode)

    def GetLoginMode(self, nOption):
        """
        08
        원형: LONG GetLoginMode(LONG nOption)
        기능: 로그인상태 확인
        호출: CommLogin 메소드 호출 이후, 로그인 상태 확인 목적으로 호출한다.
        인자: LONG nOption
            0: 모의투자 체크, 1: 시제전용, 2: 직원/고객 로그인
        반환: LONG	
            -1: 실패, 
            성공: -1보다 큰 양수
        """
        return self.ocx.dynamicCall("GetLoginMode(int)", nOption)

    ## 리소스관련
    def LoadTranResource(self, strFilePath):
        """
        10
        원형: LONG LoadTranResource(BSTR strFilePath)
        기능: Tran조회 I/O Block 정보 리소스파일 로드
        호출: Tran조회 시에 반드시 리소스파일이 에이전트 컨트롤에 적재되어 있어야한다.
        인자: BSTR strFilePath	
            Tran I/O Block 정보 리소스파일(*.res) 경로
        반환: LONG	
            0: 실패, 1: 성공
        """
        return self.ocx.dynamicCall("LoadTranResource(QString)", strFilePath)

    def LoadRealResource(self, strFilePath):
        """
        11
        원형: LONG LoadRealResource(BSTR strFilePath)
        기능: 실시간 Block 정보 리소스파일 로드
        호출: 실시간 등록 시에 반드시 리소스파일이 에이전트 컨트롤에 적재되어 있어야한다.
        인자: BSTR strFilePath	
            실시간Block정보 리소스파일(*.res) 경로
        반환: LONG	
            0: 실패, 1: 성공
        """
        return self.ocx.dynamicCall("LoadRealResource(QString)", strFilePath)

    ## 통신조회관련공통
    def CreateRequestID(self):
        """
        15
        원형: LONG CreateRequestID(void)
        기능: 조회고유ID 생성(Request ID)
        호출: Tran/FID조회 시, RQ ID를 먼저 생성한다.
        인자: Void
            없음
        반환: LONG 신규 RQ ID 반환
            음수: 실패, 2보다 큰 정수: 성공)
        """
        return self.ocx.dynamicCall("CreateRequestID()")

    def GetCommRecvOptionValue(self, nOptionType):
        """
        16
        원형: BSTR GetCommRecvOptionValue(LONG nOptionType)
        기능: 조회응답 부가정보/옵션값 반환
        호출: Tran/FID조회(OnGetTranData, OnGetFidData) 응답 이벤트 안에서만 호출한다.
        인자: LONG nOptionType
            CommRecvOpt::TranCode= 0 : Tr코드
            CommRecvOpt::PrevNextCode= 1 : 연속데이타구분 
            (0:없음, 1:이전, 2:다음, 3:이전/다음)
            CommRecvOpt::PrevNextKey= 2 : 연속조회키
            CommRecvOpt::MsgCode= 3 : 메시지코드
            CommRecvOpt::Msg= 4 : 메시지
            CommRecvOpt::SubMsgCode= 5 : 부가메시지코드
            CommRecvOpt::SubMsg=6 : 부가메시지
        반환: BSTR nOptionType에 대응하는 문자열값 반환
        """
        return self.ocx.dynamicCall("GetCommRecvOptionValue(int)", nOptionType)

    def ReleaseRqId(self, nRqId):
        """ 
        17   
        원형: LONG ReleaseRqId(LONG nRqId)
        기능: 조회고유ID(Request ID) 할당 해제
        호출: CreateRequestID 함수로 생성(할당)한RQ ID를 해제할 때 사용.
        인자: LONG nRqId	
            CreateRequestID로 생성(할당) 받은 RQ ID
        반환: void
            없음
        """
        self.ocx.dynamicCall("ReleaseRqId(int)", nRqId)

    ## Tran조회관련
    def SetTranInputData(self, nRqId, strTrCode, strRecName, strItem, strValue):
        """
        20
        원형: LONG SetTranInputData(LONG nRqId, BSTR strTrCode, BSTR strRecName, BSTR strItem, BSTR strValue)
        기능: Tran조회, 항목별 입력값을 입력한다
        호출: RequestTran 호출 전에 통신 Input데이터 입력 목적으로 호출한다.
        인자: LONG nRqId - 조회고유ID(Request ID) - CreateRequestID메소드로 생성
              BSTR strTrCode - 서비스Tr코드(Tran 리소스파일(*.res)파일의 'TR_CODE=' 항목)
              BSTR strRecName - Input레코드명(Tran 리소스파일(*.res)파일의 'REC_NAME=' 항목)
              BSTR strItem - Input항목명(Tran 리소스파일(*.res)파일의 'ITEM=' 항목)
              BSTR strValue	- Input항목에 대응하는 입력값
        반환: LONG
            0: 실패, 1: 성공
        """
        return self.ocx.dynamicCall("SetTranInputData(int, QString, QString, QString, QString)", nRqId, strTrCode, strRecName, strItem, strValue)

    def RequestTran(self, nRqId, sTrCode, sIsBenefit, sPrevOrNext, sPrevNextKey, sScreenNo, sTranType, nRequestCount):
        """
        21
        원형: LONG RequestTran(LONG nRqId, BSTR sTrCode, BSTR sIsBenefit, BSTR sPrevOrNext, BSTR sPrevNextKey, BSTR sScreenNo, BSTR sTranType, LONG nRequestCount)
        기능: Tran조회 요청
        호출: 서버에 Tran조회 요청 시 호출
        인자: LONG nRqId - 조회고유ID(Request ID) - (CreateRequestID메소드로 생성)
              BSTR sTrCode - 서비스Tr코드(Tran 리소스파일(*.res)파일의 'TR_CODE=' 항목)
              BSTR sIsBenefit - 수익계좌여부("Y", "N")
              BSTR sPrevOrNext - 연속조회구분 ("0" :일반조회, "1" : 연속조회 첫 조회, "2" : 이전조회, "3" : 다음조회)
              BSTR sPrevNextKey - 다음/이전 조회 시 연속구분이 되는 키값 입력(조회응답으로 내려 온다.)
              BSTR sScreenNo - 화면번호(ex-> "9999")
              BSTR sTranType - Q': 조회,'U': Update (보통 조회는 'Q', 주문 등은 'U'를 입력한다.)
              LONG RequestCount - 조회 응답으로 받을 최대 데이터 건수(Maxium : 9999)
        반환: LONG
            음수: 실패, 0보다 큰 정수: 성공
        """
        return self.ocx.dynamicCall("RequestTran(int, QString, QString, QString, QString, QString, QString, int)", nRqId, sTrCode, sIsBenefit, sPrevOrNext, sPrevNextKey, sScreenNo, sTranType, nRequestCount)

    def GetTranOutputRowCnt(self, strTrCode, strRecName):
        """
        22
        원형: LONG GetTranOutputRowCnt(BSTR strTrCode, BSTR strRecName)
        기능: Tran조회응답 데이터 건수 반환
        호출: Tran조회응답 이벤트(OnGetTranData) 안에서만 호출한다.
        인자: BSTR strTrCode - 서비스 Tr코드(Tran 리소스파일(*.res)파일의 'TR_CODE=' 항목)
            BSTR strRecName - Input 레코드명(Tran 리소스파일(*.res)파일의 'REC_NAME=' 항목) 
        반환: LONG
            0: 데이터 없음, 0보다 큰 정수: 데이터 건수
        """
        return self.ocx.dynamicCall("GetTranOutputRowCnt(QString, QString)", strTrCode, strRecName)

    def GetTranOutputData(self, strTrCode, strRecName, strItemName, nRow):
        """
        23
        원형: BSTR GetTranOutputData(BSTR strTrCode, BSTR strRecName, BSTR strItemName, LONG nRow)
        기능: Tran조회 항목별 응답데이터 반환
        호출: Tran조회 응답 이벤트(OnGetTranData) 안에서만 호출한다.
        인자: BSTR strTrCode
              BSTR strRecName
              BSTR strItemName
              LONG nRow
        반환: BSTR
        """
        return self.ocx.dynamicCall("GetTranOutputData(QString, QString, QString, int)", strTrCode, strRecName, strItemName, nRow)

    def SetTranInputArrayCnt(self, nRqId, strTrCode, strRecName, nRecCnt):
        """
        24
        원형: LONG SetTranInputArrayCnt(LONG nRqId, BSTR strTrCode, BSTR strRecName, LONG nRecCnt)
        기능: Tran조회 입력 데이터 건수 설정
        호출: RequestTran 호출 전에 통신 Input데이터 건수 입력 목적으로 호출한다.
        인자: LONG nRqId
              BSTR strTrCode
              BSTR strRecName : 입력 레코드명
              LONG nRecCnt : 데이터 입력 건수
        반환: LONG
              0: 실패, 1: 성공
        """
        return self.ocx.dynamicCall("SetTranInputArrayCnt(int, QString, QString, int)", nRqId, strTrCode, strRecName, nRecCnt)

    def SetTranInputArrayData(self, nRqId, strTrCode, strRecName, strItem, strValue, nArrayIndex):
        """
        25
        원형: LONG SetTranInputArrayData(LONG nRqId, BSTR strTrCode, BSTR strRecName, BSTR strItem, BSTR strValue, LONG nArrayIndex)
        기능: Tran조회 복수건 입력
        호출: RequestTran 호출 전에 통신 복수건 Input데이터 입력 목적으로 호출한다.
        인자: LONG nRqId
              BSTR strTrCode
              BSTR strRecName : 입력 레코드명
              BSTR strItem : 항목명
              BSTR strValue : 입력값
              LONG nArrayIndex : 레코드 인덱스(0부터 시작)
        반환: LONG
              0 : 실패, 1 : 성공
        """
        return self.ocx.dynamicCall("SetTranInputArrayData(int, QString, QString, QString, QString, int)", nRqId, strTrCode, strRecName, strItem, strValue, nArrayIndex)

    ## FID 조회관련
    def SetFidInputData(self, nRqId, strFID, strValue):
        """
        30
        원형: LONG SetFidInputData(LONG nRqId, BSTR strFID, BSTR strValue)
        기능: FID 조회 시, 항목별 입력값 입력
        호출: RequestFid 또는 RequestFidArray 호출 전에 조회 Input 데이터 입력 목적으로 호출한다.
        인자: LONG nRqId - 조회고유ID(Request ID) - CreateRequestID메소드로 생성
              BSTR strFID - FID번호(ex-> "9002")
              BSTR strValue - FID번호에 대응하는 입력값 (ex-> "000660")
        반환: LONG 0: 실패, 1: 성공
        """
        return self.ocx.dynamicCall("SetFidInputData(int, QString, QString)", nRqId, strFID, strValue)

    def RequestFid(self, nRqId, strOutputFidList, strScreenNo):
        """
        31
        원형: LONG RequestFid(LONG nRqId, BSTR strOutputFidList, BSTR strScreenNo)
        기능: FID조회요청 - 응답데이터가 단건(single)
        호출: 서버에 FID조회 요청 시 호출(응답으로 받을 데이터 단건일 경우에 사용)
        인자: LONGnRqId - 조회고유ID(Request ID) - CreateRequestID메소드로 생성
              BSTR strOutputFidList - 응답으로 받을 FID번호들(ex-> "4,6,5,7,11,28,13,14,15")
              BSTR strScreenNo - 화면번호 (ex-> "9999")
        반환: LONG	음수: 실패, 1: 성공 : 2보다 큰 정수
        """
        return self.ocx.dynamicCall("RequestFid(int, QString, QString)", nRqId, strOutputFidList, strScreenNo)

    def RequestFidArray(self, nRqId, strOutputFidList, strPreNext, strPreNextContext, strScreenNo, nRequestCount):
        """
        32
        원형: LONG RequestFidArray(LONG nRqId, BSTR strOutputFidList, BSTR strPreNext, BSTR strPreNextContext, BSTR strScreenNo, LONG nRequestCount)
        기능: FID조회 요청 - 응답 데이터가 복수건(array)
        호출: 서버에 FID조회 요청 시 호출(응답받을 데이터가 복수건인 경우에 사용)
        인자: LONG nRqId - 조회고유ID(Request ID) - CreateRequestID메소드로 생성
        BSTR strOutputFidList - 응답으로 받을 FID번호들(ex-> "4,6,5,7,11,28,13,14,15")
        BSTR strPreNext - 연속조회 구분 ("0" :일반, "1" : 연속 첫 조회, "2" : 이전조회, "3" : 다음조회)
        BSTR strPreNextContext - 조회 응답으로 받은연속거래키
        BSTR strScreenNo - 화면변호(ex-> "9999")
        LONG nRequestCount - 조회 응답으로 받을 최대 데이터 건수(Maxium : 9999)
        반환: LONG 음수: 실패, 1 : 성공 : 2보다 큰 정수
        """
        return self.ocx.dynamicCall("RequestFidArray(int, QString, QString, QString, QString, int)", nRqId, strOutputFidList, strPreNext, strPreNextContext, strScreenNo, nRequestCount)

    def GetFidOutputRowCnt(self, nRequestId):
        """
        33
        원형: LONG GetFidOutputRowCnt(LONG nRequestId)
        기능: FID조회 응답데이터 건수
        호출: FID조회응답 이벤트(OnGetFidData) 안에서만 호출한다.
        인자: LONG nRequestId	조회고유ID(Request ID)- CreateRequestID메소드로 생성
        반환: LONG 0: 데이터 없음, 0보다 큰 정수 : 데이터 건수
        """
        return self.ocx.dynamicCall("GetFidOutputRowCnt(int)", nRequestId)

    def GetFidOutputData(self, nRequestId, strFid, nRow):
        """
        34
        원형: BSTR GetFidOutputData(LONG nRequestId, BSTR strFid, LONG nRow)
        기능: FID조회 항목별 응답 데이터 반환
        호출: FID조회응답 이벤트(OnGetFidData) 안에서만 호출한다.
        인자: LONG nRequestId - 조회고유ID(Request ID) - CreateRequestID메소드로 생성
              BSTR strFid - 응답 받은 FID번호(ex-> "4")
              LONG nRow - 항목값이 위치한 행 인덱스 (단건(single): 0; 복수건(array) : 해당 행의 인덱스 번호)
        반환: BSTR FID에 대응한 응답 데이터
        """
        return self.ocx.dynamicCall("GetFidOutputData(int, QString, int)", nRequestId, strFid, nRow)

    def SetPortfolioFidInputData(self, nRqId, strSymbolCode, strSymbolMarket):
        """
        36
        원형: LONG SetPortfolioFidInputData(LONG nRqId, BSTR strSymbolCode, BSTR strSymbolMarket)
        기능: 관심종목형(Portfolio) FID조회 시, 항목별 입력값 입력
        호출: RequestFid 또는 RequestFidArray 호출 전에 조회 Input데이터 입력 목적으로 호출한다.
        인자: LONG nRqId - 조회고유ID(Request ID) - CreateRequestID메소드로 생성
              BSTR strSymbolCode - 종목코드
              BSTR strSymbolMarket - 종목 시장코드
        반환: LONG 0: 실패, 1: 성공
        """
        return self.ocx.dynamicCall("SetPortfolioFidInputData(int, QString, QString)", nRqId, strSymbolCode, strSymbolMarket)

    ## 실시간관련
    def RegisterReal(self, strRealName, strRealKey):
        """
        40
        원형: LONG RegisterReal(BSTR strRealName, BSTR strRealKey)
        기능: 실시간 등록한다.
        호출: 로그인 처리가 완료된 이후 또는 Tran/FID조회응답 이벤트 안에서 호출한다.
        인자: BSTR strRealName - 실시간 등록할 실시간코드명 - 실시간 리소스파일(*.res)파일의 'REAL_NAME=' 항목(ex-> "S00")
              BSTR strRealKey - 실시간 수신 시데이터 구분키가 될 값(ex-> "000660" : SK하이닉스 종목코드)
        반환: LONG 음수: 실패, 0: 성공
        """
        return self.ocx.dynamicCall("RegisterReal(QString, QString)", strRealName, strRealKey)

    def UnRegisterReal(self, strRealName, strRealKey):
        """
        41
        원형: LONG UnRegisterReal(BSTR strRealName, BSTR strRealKey)
        기능: 실시간등록 해제한다.
        호출: RegisterReal 함수 호출 이후에 호출한다.
        인자: BSTR strRealName - 실시간등록 해제할 실시간코드명 - 실시간 리소스파일(*.res)파일의 'REAL_NAME=' 항목(ex-> "S00")
              BSTR strRealKey - 실시간등록 해제할 실시간등록키(ex-> "000660" : SK하이닉스 종목코드)
        반환: LONG 음수: 실패, 1: 성공
        """
        return self.ocx.dynamicCall("UnRegisterReal(QString, QString)", strRealName, strRealKey)

    def AllUnRegisterReal(self):
        """
        42
        원형: LONG AllUnRegisterReal(void)
        기능: 모든 실시간등록 해제한다.
        호출: RegisterReal 함수 호출 이후에 호출한다.
        인자: 없음	
        반환: LONG 음수: 실패, 1: 성공
        """
        return self.ocx.dynamicCall("AllUnRegisterReal()")

    def GetRealOutputData(self, strRealName, strItemName):
        """
        43
        원형: BSTR GetRealOutputData(BSTR strRealName, BSTR strItemName)
        기능: 항목별 실시간 수신 데이터를 반환한다.
        호출: 실시간데이터 수신 이벤트(OnGetRealData) 안에서만 호출한다.
        인자: BSTR strRealName - 실시간 수신 데이터 실시간코드명 - 실시간 리소스파일(*.res)파일의 'REAL_NAME=' 항목(ex-> "S00")
              BSTR strItemName - 실시간 리소스파일(*.res)파일의 'ITEM=' 항목(ex-> "SHRN_ISCD")
        반환: BSTR 해당 strItemName에 대응하는 데이터값 반환
        """
        return self.ocx.dynamicCall("GetRealOutputData(QString, QString)", strRealName, strItemName)

    ## 부가적인메소드
    def GetLastErrMsg(self):
        """
        50
        원형: BSTR GetLastErrMsg(void)
        기능: 에러 메시지 확인
        호출: API메소드에서 에러가 발생했을 경우, 에러메시지 확인하기 위해 호출한다.
        인자: 없음	
        반환: BSTR 마지막으로 호출된 API메소드에서 에러가 발생했을 경우 에러메시지 반환
        """
        return self.ocx.dynamicCall("GetLastErrMsg()")

    def GetApiAgentModulePath(self):
        """
        51
        원형: BSTR GetApiAgentModulePath(void)
        기능: OpenAPI 에이전트 모듈 파일경로 반환
        호출: 에이전트 오브젝트 생성 이후에 호출
        인자: 없음	
        반환: BSTR OpenAPI 에이전트 모듈 파일경로 반환
        """
        return self.ocx.dynamicCall("GetApiAgentModulePath()")

    def GetEncrpyt(self, strPlainText):
        """
        52
        원형: BSTR GetEncrpyt (BSTR strPlainText)
        기능: 평문을 암호화한다(계좌비밀번호 암호화 등에 사용된다.)
        호출:	
        인자: BSTR 평문
        반환: BSTR 암호문
        """
        return self.ocx.dynamicCall("GetEncrpyt(QString)", strPlainText)

    def SetOffAgentMessageBox(self, nOption):
        """
        53
        원형: void SetOffAgentMessageBox (LONG nOption)
        기능: 에이전트에 띄우는 메시박스를 막는다.
        호출: CommInit 함수 호출전 SetOffAgentMessageBox함수를 호출해야된다.
        인자: LONG 0: 에이전트 메시지박스 실행, 1: 에이전트 메시지박스 실행 안 함
        반 환	없음	
        """
        self.ocx.dynamicCall("SetOffAgentMessageBox(int)", nOption)

    def SetOptionalFunction(self, nOption, nValue1, nValue2, strValue1, strValue2):
        """
        54
        원형: BSTR SetOptionalFunction(LONG nOption, LONG nValue1, LONG nValue2, BSTR strValue1, BSTR strValue2)
        기능: 부가적인 옵션 처리(옵션 세부 설정은 신규 추가 시 가이드 문서에 포함 재배포)
        호출:	
        인자: 없음	
        반환: BSTR 옵션 처리 결과 문자열
        """
        return self.ocx.dynamicCall("SetOptionalFunction(int, int, int, QString, QString)", nOption, nValue1, nValue2, strValue1, strValue2)

    def VerifyRequestCode(self, strReturnVal):
        """
        반환: 0 or 1
        """
        return self.ocx.dynamicCall("VerifyRequestCode(QString)", strReturnVal)

    ## 계좌관련메소드
    def GetAccInfo(self, nOption, szAccNo):
        """
        60
        원형: BSTR GetAccInfo(LONG nOption, BSTR szAccNo)
        기능: 계좌 정보
        호출	
        인자: LONG nOption - 0 : 계좌대체번호, 1 : 계좌상품번호, 198 : 대리인 등록여부("Y" : 주문대리 계좌)
              BSTR szAccNo - 계좌번호
        반환: BSTR 옵션에 해당하는 값
        """
        return self.ocx.dynamicCall("GetAccInfo(int, QString)", nOption, szAccNo)

    def GetUserAccCnt(self):
        """
        61
        원형: LONG GetUserAccCnt()
        기능: 보유계좌 수
        호출	
        인자: 없음	
        반환: LONG 보유계좌 수
        """
        return self.ocx.dynamicCall("GetUserAccCnt()")

    def GetUserAccNo(self, nIndex):
        """
        62
        원형: BSTR GetUserAccNo(LONG nIndex)
        기능: 보유계좌 반환
        호출	
        인자: LONG nIndex - 보유계좌 인덱스
        반환: BSTR 계좌번호반환(종합계좌번호(8) + 계좌상품번호(3))
        """
        return self.ocx.dynamicCall("GetUserAccNo(int)", nIndex)


    def block_request(self, *args, **kwargs):
        trcode = args[0].lower()
        lines = read_trinfo(trcode, dir_path)
        #print(trcode)
        #print(lines)
        self.tr_items = parse_trinfo(trcode, lines)
        self.tr_record = kwargs["output"]
        next = kwargs["next"]

        # set input
        for id in kwargs:
            if id.lower() != "output" and id.lower() != "next":
                self.SetInputValue(id, kwargs[id])

        # initialize
        self.received = False
        self.tr_remained = False

        #print(trcode)
        #print(args)
        #print(kwargs)
        #print(self.tr_items)
        #print(self.tr_record)
        # request
        #print(self.tr_record)
        #print("11111 %s" % self.next)
        if self.tr_record == 'single':
            #print("***** single *****")
            self.CommRqData(trcode, trcode, next, "0101")
        else:
            self.CommRqData(trcode, trcode, next, "0101")
        #print("22222 %s" % self.next)
        while not self.received:
            pythoncom.PumpWaitingMessages()

        return self.tr_data


    def _request_balance(self, ctno, apno, acc_pwd):

        #**********************************************************
        # 잔고 조회
        #**********************************************************

        tr_code = "OTS5919Q41" # Tran코드(리소스파일 참고)
        in_rec_name1 = "OTS5919Q41_in" # 입력 레코드명(리소스파일 참고)
        in_rec_name2 = "OTS5919Q41_in_sub01" # 입력 레코드명(리소스파일 참고)
        odrv_sell_buy_dcd = "0" # 해외파생매도매수구분코드(0:전체, B:매수, S:매도)

        #*-------------------------------*
        # [1] Request ID생성
        #*-------------------------------*
        g_n_rq_id_balance_list = self.CreateRequestID()
        self.SetTranInputData(g_n_rq_id_balance_list, tr_code, in_rec_name1, "ODRV_SELL_BUY_DCD", odrv_sell_buy_dcd)

        #*-------------------------------*
        # [2] 입력 건수를 입력한다.
        #*-------------------------------*
        input_cnt = 1
        self.SetTranInputArrayCnt(g_n_rq_id_balance_list, tr_code, in_rec_name2, 1)

        #*-------------------------------*
        # [3] Tran조회 입력값을 입력한다.
        #*-------------------------------*
        for i in [0, 1, 2]:
            pwd = self.GetEncrpyt(acc_pwd)
            self.SetTranInputArrayData(g_n_rq_id_balance_list, tr_code, in_rec_name2, "CTNO", ctno, i)
            self.SetTranInputArrayData(g_n_rq_id_balance_list, tr_code, in_rec_name2, "APNO", apno, i)
            self.SetTranInputArrayData(g_n_rq_id_balance_list, tr_code, in_rec_name2, "PWD", pwd, i)
        
        benefit_acc = "N"
        pre_next = "1"
        screen_no = "9999"

        request_data_cnt = 0

        #*-------------------------------*
        # [4] 서버에 Tran조회 요청한다.
        #*-------------------------------*
        request_tran = self.RequestTran(g_n_rq_id_balance_list, tr_code, benefit_acc, pre_next, "", screen_no, "Q", 0)
        if request_tran < 0:
            self.GetLastErrMsg()


if not QApplication.instance():
    app = QApplication(sys.argv)

"""
if __name__ == "__main__":
    # 로그인
    kiwoom = KiwoomG()
    kiwoom.CommConnect(block=True)

    # 조건식 load
    kiwoom.GetConditionLoad()

    conditions = kiwoom.GetConditionNameList()

    # 0번 조건식에 해당하는 종목 리스트 출력
    condition_index = conditions[0][0]
    condition_name = conditions[0][1]
    codes = kiwoom.SendCondition("0101", condition_name, condition_index, 0)

    print(codes)
"""