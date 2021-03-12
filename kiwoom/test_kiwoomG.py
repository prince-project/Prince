import sys
import os
import pandas as pd
import numpy as np 
import matplotlib.pyplot as plt 
sys.path.append(os.path.abspath('C:\GitHub\kiwoom\kiwoom'))
from lib_kiwoomG import *
from tabulate import tabulate

def _table(df):
    return tabulate(df, headers = 'keys', tablefmt = 'pipe')

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

kiwoom.CommTerminate()

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
                          시간단위="10",
                          output="multi",
                          next=0)
                          
### 연속조회
dfs = []
df = kiwoom.block_request("opt10012",
                          종목코드="ESH21",
                          시간단위="1",
                          output="multi",
                          next=0)
dfs.append(df)

while kiwoom.tr_remained:
    df = kiwoom.block_request("opt10012",
                          종목코드="ESH21",
                          시간단위="1",
                          output="multi",
                          next=self.next)
    dfs.append(df)
    time.sleep(1)

df = pd.concat(dfs)
#df.to_excel("005930.xlsx")

# opt10013 - 일별데이타조회 
dfs = []
df = kiwoom.block_request("opt10013",
                          종목코드="ESH21",
                          시간단위="0",
                          output="multi",
                          next=0)
dfs.append(df)

while kiwoom.tr_remained:
    df = kiwoom.block_request("opt10013",
                          종목코드="ESH21",
                          시간단위="1",
                          output="multi",
                          next=2)
    dfs.append(df)
    time.sleep(1)

df = pd.concat(dfs)

# opt10014 - 종목시작시간 
df = kiwoom.block_request("opt10014",
                          종목코드="ESH21",
                          output="single",
                          next=0)

# 매수/매도

## 계좌
account = kiwoom.GetLoginInfo("ACCNO")[0]
## 시장가 매수
kiwoom.SendOrder("시장가매수", "0101", account, 2, "ESH21", 1, "0", "", "1", "")
## 시장가매도
kiwoom.SendOrder("시장가매도", "0101", account, 1, "ESH21", 1, "0", "", "1", "")
## 지정가매수 
kiwoom.SendOrder("지정가매수", "0101", account, 2, "ESH21", 1, "3900.00", "", "2", "")
## 매수취소
df = kiwoom.block_request("opw30002",
                          계좌번호="%s"%account,
                          비밀번호="0000",
                          종목코드="ESH21",
                          통화코드="USD",
                          매도수구분="2", #매도-1, 매수-2
                          output="multi",
                          next=0)
kiwoom.SendOrder("매수취소", "0101", account, 4, "ESH21", 1, "0", "", "0", df.iloc[:,0].values[0][-9:])

# 매수/매도
df = kiwoom.block_request("opw40001",
                          계좌번호="%s"%account,
                          비밀번호="0000",
                          비밀번호입력매체="00",
                          시작일자="20210301",
                          종료일자="20210312",
                          통화코드="",
                          output="multi",
                          next=0)

trcode='opw30002'
trcode = 'opw40001'
lines = read_trinfo(trcode, dir_path)
tr_items = parse_trinfo(trcode, lines)

[opw40001_INPUT]
Title =기간손익내역조회
	계좌번호		=	10	,	-1
	비밀번호		=	64	,	-1
	비밀번호입력매체 	= 	2	,	-1
	시작일자		=	8	,	-1
	종료일자		=	8	,	-1
	통화코드		=	3	,	-1
#------------------------------
# test code
#------------------------------

open_time = kiwoom.block_request("opt10014", 종목코드="ESH21", output="single", next=0).iloc[:,1].values[0]
open_time = pd.Timestamp(open_time)

