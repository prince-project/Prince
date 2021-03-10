import sys
from PyQt5.QtWidgets import *
from PyQt5.QAxContainer import *
import pythoncom
import datetime
#from pykiwoom import parser
import pandas as pd
import time
import logging
import os

sys.path.append(os.path.abspath('C:\GitHub\kiwoom\kiwoom'))
from kiwoomG_parser import *
#from kiwoomK_parser import *

logging.basicConfig(filename="log.txt", level=logging.ERROR)


class KiwoomG:
    def __init__(self, login=False):
        self.ocx = QAxWidget("KFOpenAPI.KFOpenAPICtrl.1")
        self.connected = False              # for login event
        self.received = False               # for tr event
        self.tr_items = None                # tr input/output items
        self.tr_data = None                 # tr output data
        self.tr_record = None
        self.tr_remained = False
        self._set_signals_slots()

        if login:
            self.CommConnect()

    def _handler_login(self, err_code):
        logging.info(f"hander login {err_code}")
        if err_code == 0:
            self.connected = True

    def _handler_tr(self, screen, rqname, trcode, record, next):
        #print('*********************************************')
        logging.info(f"OnReceiveTrData {screen} {rqname} {trcode} {record} {next}")
        try:
            record = None
            items = None
            #print(self.tr_remained)
            print(self)
            print(screen)
            print(rqname)
            print(record)
            print(next)
            # remained data
            if next == '2':
                self.tr_remained = True
            else:
                self.tr_remained = False

            for record in self.tr_items['output'][0]:
                #record = list(output.keys())[0]
                items = self.tr_items['output'][0][record]
                if record == self.tr_record:
                    break
            
            #print(self.tr_items['output'])
            #print(record)
            #print(self.tr_record)
            #print(items)
            rows = self.GetRepeatCnt(trcode, rqname)
            if rows == 0:
                rows = 1

            data_list = []
            for row in range(rows):
                row_data = []
                for item in items:
                    #print(item)
                    data = self.GetCommData(trcode, rqname, row, item)
                    row_data.append(data)
                data_list.append(row_data)

            # data to DataFrame
            df = pd.DataFrame(data=data_list, columns=items)
            self.tr_data = df
            self.received = True
        except:
            pass

    def _handler_msg(self, screen, rqname, trcode, msg):
        logging.info(f"OnReceiveMsg {screen} {rqname} {trcode} {msg}")

    def _handler_chejan(self, gubun, item_cnt, fid_list):
        logging.info(f"OnReceiveChejanData {gubun} {item_cnt} {fid_list}")

    def _set_signals_slots(self):
        self.ocx.OnEventConnect.connect(self._handler_login)
        self.ocx.OnReceiveTrData.connect(self._handler_tr)
        self.ocx.OnReceiveMsg.connect(self._handler_msg)
        self.ocx.OnReceiveChejanData.connect(self._handler_chejan)

    #-------------------------------------------------------------------------------------------------------------------
    # OpenAPI+ 메서드
    #-------------------------------------------------------------------------------------------------------------------
    def CommConnect(self, block=True, login_type=0): # checked
        """
        로그인 윈도우를 실행합니다.
        :param block: True: 로그인완료까지 블록킹 됨, False: 블록킹 하지 않음
        : 0 - 버전 수동처리, 1 - 버전 자동처리
        :return: None
        """
        self.ocx.dynamicCall("CommConnect(%s)"%login_type)
        if block:
            while not self.connected:
                pythoncom.PumpWaitingMessages()

    def CommRqData(self, rqname, trcode, next, screen): # checked
        """
        TR을 서버로 송신합니다.
        :param rqname: 사용자가 임의로 지정할 수 있는 요청 이름
        :param trcode: 요청하는 TR의 코드
        :param next: 0: 처음 조회, 2: 연속 조회
        :param screen: 화면번호 ('0000' 또는 '0' 제외한 숫자값으로 200개로 한정된 값
        :return: None
        """
        #print("***** CommRqData *****")
        #print(rqname)
        #print(trcode)
        self.ocx.dynamicCall("CommRqData(QString, QString, int, QString)", rqname, trcode, next, screen)

    def SetInputValue(self, id, value): #checked
        """
        TR 입력값을 설정하는 메서드
        :param id: TR INPUT의 아이템명
        :param value: 입력 값
        :return: None
        """
        self.ocx.dynamicCall("SetInputValue(QString, QString)", id, value)

    def GetCommData(self, trcode, rqname, index, item): #checked
        """
        수신 데이터를 가져가는 메서드
        :param trcode: TR 코드
        :param rqname: 요청 이름
        :param index: 멀티데이터의 경우 row index
        :param item: 얻어오려는 항목 이름
        :return: 수신 데이터
        :ex) 현재가출력 - GetCommData("OPT00001", "해외선물기본정보", 0, "현재가")
        """
        data = self.ocx.dynamicCall("GetCommData(QString, QString, int, QString)", trcode, rqname, index, item)
        return data.strip()

    def CommTerminate(self): #checked
        """
        OpenAPI의 서버 접속을 해제한다
        """
        self.ocx.dynamicCall("CommTerminate()")

    def GetRepeatCnt(self, trcode, rqname): #checked
        """
        레코드 반복횟수를 반환
        멀티데이터의 행(row)의 개수를 얻는 메서드
        :param trcode: TR코드
        :param rqname: 사용자가 설정한 요청이름
        :return: 멀티데이터의 행의 개수
        :        레코드의 반복횟수
        :ex) GetRepeatCnt("OPT00001", "해외선물체결데이타")
        """
        count = self.ocx.dynamicCall("GetRepeatCnt(QString, QString)", trcode, rqname)
        return count

    def DisconnectRealData(self, screen): #checked
        """
        화면번호에 대한 리얼 데이터 요청을 해제하는 메서드
        :param screen: 화면번호
        :return: None
        """
        self.ocx.dynamicCall("DisconnectRealData(QString)", screen)

    def GetCommRealData(self, code, fid): #checked
        """
        실시간 데이터를 반환
        ex) GetCommRealData("해외선물시세", 10)
        """
        data = self.ocx.dynamicCall("GetCommRealData(QString, int)", code, fid)
        return data

    def GetChejanData(self, fid): #checked
        """
        체결잔고 데이터 반환
        ex) GetChejanData(910) //체결가격
        """
        data = self.ocx.dynamicCall("GetChejanData(int)", fid)
        return data

    def SendOrder(self, rqname, screen, accno, order_type, code, quantity, price, stop, hoga, order_no): #checked
        """
        주문을 서버로 전송하는 메서드
        시장가 주문시 주문단가는 0으로 입력해야 함 (가격을 입력하지 않음을 의미)
        :param rqname: 사용자가 임의로 지정할 수 있는 요청 이름
        :param screen: 화면번호[4] (1~9999 :숫자값으로만 가능)
        :param accno: 계좌번호[10]
        :param order_type: 주문유형 (1:신규매도, 2:신규매수, 3:매도취소, 4:매수취소, 5:매도정정, 6:매수정정)
        :param code: 종목코드
        :param quantity: 주문수량
        :param price: 주문단가
        :param stop: Stop단가
        :param hoga: 거래구분 (1:시장가, 2:지정가, 3:STOP, 4:STOP LIMIT)
        :param order_no: 원주문번호
        :return:
        ex)
        지정가 매수 - openApi.SendOrder(“RQ_1”, “0101”, “5015123410”, 2, “6AH16”, 10, “0.7900”, “2”, “”);
        시장가 매수 - openApi.SendOrder(“RQ_1”, “0101”, “5015123410”, 2, “6AH16”, 10, “0”, “1”, “”);
        매수 정정 - openApi.SendOrder(“RQ_1”,“0101”, “5015123410”, 6, “6AH16”, 10, “0.7800”, “0”, “200060”);
        매수 취소 - openApi.SendOrder(“RQ_1”, “0101”, “5015123410”, 4, “6AH16”, 10, “0”, “0”, “200061”);
        """
        ret = self.ocx.dynamicCall("SendOrder(QString, QString, QString, int, QString, int, QString, QString, QString, QString)",
                                   [rqname, screen, accno, order_type, code, quantity, price, stop, hoga, order_no])
        return ret


    def GetLoginInfo(self, tag): #checked
        """
        로그인한 사용자 정보를 반환하는 메서드
        :param tag: ("ACCOUNT_CNT, "ACCNO", "USER_ID", "USER_NAME", "KEY_BSECGB", "FIREW_SECGB")
        :return: tag에 대한 데이터 값
        """
        data = self.ocx.dynamicCall("GetLoginInfo(QString)", tag)

        if tag == "ACCNO":
            return data.split(';')[:-1]
        else:
            return data
    
    def GetGlobalFutureItemlist(self): #checked
        """
        해외선물 상품리스트를 반환
        """
        data = self.ocx.dynamicCall("GetGlobalFutureItemlist()")
        return data
    
    def GetGlobalOptionItemlist(self): #checked
        """
        해외옵션 상품리스트를 반환
        """
        data = self.ocx.dynamicCall("GetGlobalFutureItemlist()")
        return data
    
    def GetGlobalFutureCodelist(self, item): #checked
        """
        해외상품별 해외선물 종목코드리스트를 반환
        :param item: 해외상품
        :return:
        """
        data = self.ocx.dynamicCall("GetGlobalFutureCodelist(QString)", item)
        return data

    def GetGlobalOptionCodelist(self, item): #checked
        """
        해외상품별 해외옵션 종목코드리스트를 반환
        :param item: 해외상품
        :return:
        """
        data = self.ocx.dynamicCall("GetGlobalFutureCodelist(QString)", item)
        return data

    def GetConnectState(self): #checked
        """
        현재접속 상태를 반환하는 메서드
        :return: 0:미연결, 1: 연결완료
        """
        ret = self.ocx.dynamicCall("GetConnectState()")
        return ret

    def GetAPIModulePath(self): #checked
        """
        OpenAPI 모듈의 경로를 반환하는 메서드
        :return: 모듈의 경로
        """
        ret = self.ocx.dynamicCall("GetAPIModulePath()")
        return ret

    def GetCommonFunc(self, func_name, param): #checked
        """
        공통함수로 추후 추가함수가 필요시 사용할 함수
        :param func_name: 함수명
        :param param: 인자값
        :return: 문자값으로 반환
        """
        ret = self.ocx.dynamicCall("GetCommonFunc(QString, QString)", [func_name, param])
        return ret

    def GetConvertPrice(self, code, price, ntype): # checked
        """
        가격 진법에 따라 변환된 가격을 반환
        :param code: 종목코드
        :param price: 가격
        :param ntype: 타입(0 : 진법->10진수, 1 : 10진수->진법)
        :return: 문자값으로 반환
        """
        ret = self.ocx.dynamicCall("GetConvertPrice(QString, QString, int)", [code, price, ntype])
        return ret 

    def GetGlobalFutOpCodeInfoByType(self, gubun, stype): #checked
        """
        해외선물옵션종목코드정보를 타입별로 반환
        :param gubun: 0(해외선물), 1(해외옵션)
        :param stype: IDX(지수), CUR(통화), INT(금리), MLT(금속), ENG(에너지), CMD(농산물)
        :return: 종목코드정보리스트들을 문자값으로 반환
        """
        ret = self.ocx.dynamicCall("GetGlobalFutOpCodeInfoByType(int, QString)", [gubun, stype])
        return ret 

    def GetGlobalFutOpCodeInfoByCode(self, scode): #checked
        """
        해외선물옵션종목코드정보를 종목코드별로 반환
        :param scode: 해외선물옵션 종목코드
        :return: 종목코드정보리스트들을 문자값으로 반환
        """
        ret = self.ocx.dynamicCall("GetGlobalFutOpCodeInfoByCode(QString)", scode)
        return ret 

    def GetGlobalFutureItemlistByType(self, stype): #checked
        """
        해외선물상품리스트를 타입별로 반환
        :param stype: IDX(지수), CUR(통화), INT(금리), MLT(금속), ENG(에너지), CMD(농산물)
        :return: 상품리스트를 문자값으로 반환
        """
        ret = self.ocx.dynamicCall("GetGlobalFutureItemlistByType(QString)", stype)
        return ret 

    def GetGlobalFutureCodeByItemMonth(self, sitem, smonth): #checked
        """
        해외선물종목코드를 상품/월물별로 반환
        :param sitem: 상품코드(6A, ES..)
        :param smonth: “201606”
        :return: 종목코드를 문자값으로 반환
        """
        ret = self.ocx.dynamicCall("GetGlobalFutureCodeByItemMonth(QString, QString)", [sitem, smonth])
        return ret 

    def GetGlobalOptionCodeByMonth(self, sitem, cp_gubun, act_price, smonth): #checked
        """
        해외옵션종목코드를 상품/콜풋/행사가/월물별로 반환
        :param sitem: 상품코드(6A, ES..)
        :param cp_gubun: C(콜)/P(풋)
        :param act_price: 0.760
        :param smonth: “201606”
        :return: 종목코드를 문자값으로 반환
        """
        ret = self.ocx.dynamicCall("GetGlobalOptionCodeByMonth(QString, QString, QString, QString)", [sitem, cp_gubun, act_price, smonth])
        return ret 

    def GetGlobalOptionMonthByItem(self, sitem): #checked
        """
        해외옵션월물리스트를 상품별로 반환
        :param sitem: 상품코드(6A, ES..)
        :return: 월물리스트를 문자값으로 반환
        """
        ret = self.ocx.dynamicCall("GetGlobalOptionMonthByItem(QString)", sitem)
        return ret 

    def GetGlobalOptionActPriceByItem(self, sitem): #checked
        """
        해외옵션행사가리스트를 상품별로 반환
        :param sitem: 상품코드(6A, ES..)
        :return: 행사가리스트를 문자값으로 반환
        """
        ret = self.ocx.dynamicCall("GetGlobalOptionActPriceByItem(QString)", sitem)
        return ret 

    def GetGlobalFutureItemTypelist(self): #checked
        """
        해외선물상품타입리스트를 반환
        :return: 상품타입리스트를 문자값으로 반환; e.g) IDX;CUR;INT;MLT;ENG;CMD; 반환
        """
        ret = self.ocx.dynamicCall("GetGlobalFutureItemTypelist()")
        return ret

    def GetCommFullData(self, tr_code, record_name, gubun): #checked
        """
        수신된 전체데이터를 반환
        :param tr_code: Tran 코드
        :param record_name: 레코드명
        :param gubun: 0 : 전체(싱글+멀티), 1 : 싱글데이타, 2 : 멀티데이타
        :return: 수신 전체데이터를 문자값으로 반환
        :비고
            WKOAStudio의 TR목록탭에서 필드 사이즈 참조.(필드명 옆 가로안의 값들)
            모든 시세/원장 조회에 사용 가능하며, 특히 차트데이타 같은 대용량 데이터를 한번에 받아서 처리가능
        """
        ret = self.ocx.dynamicCall("GetCommFullData(QString, QString, int)", [tr_code, record_name, gubun])
        return ret 

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
        if self.tr_record == 'single':
            #print("***** single *****")
            self.CommRqData(trcode, trcode, next, "0001")
        else:
            self.CommRqData(trcode, trcode, next, "0101")

        while not self.received:
            pythoncom.PumpWaitingMessages()

        return self.tr_data



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