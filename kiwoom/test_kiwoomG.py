import sys
import os
import pandas as pd
import numpy as np 
import matplotlib.pyplot as plt 
sys.path.append(os.path.abspath('C:\GitHub\kiwoom\kiwoom'))
from lib_kiwoomG import *

kiwoom = KiwoomG()
kiwoom.CommConnect(block=True)
print("블록킹 로그인 완료")


# 사용자 정보 얻어오기
account_num = kiwoom.GetLoginInfo("ACCOUNT_CNT")        # 전체 계좌수
accounts = kiwoom.GetLoginInfo("ACCNO")                 # 전체 계좌 리스트
user_id = kiwoom.GetLoginInfo("USER_ID")                # 사용자 ID
user_name = kiwoom.GetLoginInfo("USER_NAME")            # 사용자명
keyboard = kiwoom.GetLoginInfo("KEY_BSECGB")            # 키보드보안 해지여부
firewall = kiwoom.GetLoginInfo("FIREW_SECGB")           # 방화벽 설정 여부

print(account_num)
print(accounts)
print(user_id)
print(user_name)
print(keyboard)
print(firewall)

# global futures list
futures_list = kiwoom.GetGlobalFutureItemlist()
futures_code_list = kiwoom.GetGlobalFutureCodelist("ES") 

res = kiwoom.GetGlobalFutOpCodeInfoByType(0, "IDX")

#------------------------------
# sample
#------------------------------

# opt10001 - 종목정보조회
df = kiwoom.block_request("opt10001",
                          종목코드="ESH21",
                          output="single",
                          next=0)

df = kiwoom.block_request("opt10001",
                          종목코드="ESH21",
                          output="multi",
                          next=0)

# opt10005 - 관심종목조회
df = kiwoom.block_request("opt10005",
                          종목코드="ESH21",
                          output="multi",
                          next=0)

# opt10006 - 상품별현재가조회
df = kiwoom.block_request("opt10006",
                          상품코드="IDX",
                          output="multi",
                          next=0)

# opt10007 - 거래소별현재가조회
df = kiwoom.block_request("opt10007",
                          거래소코드="CME",
                          output="multi",
                          next=0)

# opt10009 - 전일대비등락율상위조회 
df = kiwoom.block_request("opt10009",
                          상품구분="",
                          정렬구분="1",
                          output="multi",
                          next=0)

# opt10010 - 당일거래량상위조회 
df = kiwoom.block_request("opt10010",
                          상품구분="",
                          output="multi",
                          next=0)

# opt10011 - 체결데이타조회 
df = kiwoom.block_request("opt10011",
                          종목코드="ESH21",
                          시간단위="00",
                          output="multi",
                          next=0)

# opt10012 - 분데이타조회 
df = kiwoom.block_request("opt10012",
                          종목코드="ESH21",
                          시간단위="60",
                          output="multi",
                          next=0)
                          
### 연속조회
dfs = []
df = kiwoom.block_request("opt10012",
                          종목코드="ESH21",
                          시간단위="1",
                          output="multi",
                          next=0)

while kiwoom.tr_remained:
    df = kiwoom.block_request("opt10012",
                          종목코드="ESH21",
                          시간단위="1",
                          output="multi",
                          next=2)
    dfs.append(df)
    time.sleep(1)

df = pd.concat(dfs)
df.to_excel("005930.xlsx")

# opt10013 - 일별데이타조회 
df = kiwoom.block_request("opt10013",
                          종목코드="ESH21",
                          시간단위="0",
                          output="multi",
                          next=0)

# opt10014 - 종목시작시간 
df = kiwoom.block_request("opt10014",
                          종목코드="ESH21",
                          output="single",
                          next=0)

# 매수/매도
#지정가 매수 - openApi.SendOrder(“RQ_1”, “0101”, “5015123410”, 2, “6AH16”, 10, “0.7900”, “2”, “”)
#시장가 매수 - openApi.SendOrder(“RQ_1”, “0101”, “5015123410”, 2, “6AH16”, 10, “0”, “1”, “”)

## 계좌
account = kiwoom.GetLoginInfo("ACCNO")[0]
kiwoom.SendOrder("시장가매수", "0101", account, 2, "ESH21", 1, "0", "", "1", "")

## 삼성전자, 10주, 시장가주문 매수
for i in range(10):
    kiwoom.SendOrder("시장가매수", "0101", account, 2, "ESH21", 1, "0", "1", "")
    time.sleep(0.2)
    print(i, "매수 완료")

# 삼성전자, 10주, 시장가주문 매도
kiwoom.SendOrder("시장가매도", "0101", stock_account, 2, "005930", 10, 0, "03", "")

kiwoom.CommTerminate()


#------------------------------
# test code
#------------------------------

open_time = kiwoom.block_request("opt10014", 종목코드="ESH21", output="single", next=0).iloc[:,1].values[0]
open_time = pd.Timestamp(open_time)

