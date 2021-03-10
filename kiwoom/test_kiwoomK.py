import sys
import os
import pandas as pd
import numpy as np 
import matplotlib.pyplot as plt 

#from pykiwoom.kiwoom import *
sys.path.append(os.path.abspath('C:\GitHub\kiwoom\kiwoom'))
from lib_kiwoomK import *

kiwoom = Kiwoom()
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

# 종목코드 얻기

#파라미터	시장
#"0"	코스피
#"3"	ELWs
#"4"	뮤추얼펀드
#"5"	신주인수권
#"6"	리츠
#"8"	ETF
#"9"	하이얼펀드
#"10"	코스닥
#"30"	K-OTC
#"50"	코넥스

kospi = kiwoom.GetCodeListByMarket('0')
kosdaq = kiwoom.GetCodeListByMarket('10')
etf = kiwoom.GetCodeListByMarket('8')

print(len(kospi))
print(len(kosdaq))
print(len(etf))

# 종목명 얻기
name = kiwoom.GetMasterCodeName("005930")
print(name)

# 연결상태 확인
state = kiwoom.GetConnectState()
if state == 0:
    print("미연결")
elif state == 1:
    print("연결완료")

# 상장주식수 얻기
stock_cnt = kiwoom.GetMasterListedStockCnt("005930")
print("삼성전자 상장주식수: ", stock_cnt)

# 감리 구분
감리구분 = kiwoom.GetMasterConstruction("005930")
print(감리구분)

# 상장일
상장일 = kiwoom.GetMasterListedStockDate("005930")
print(상장일)
print(type(상장일))   

# 전일가
전일가 = kiwoom.GetMasterLastPrice("005930")
print(int(전일가))
print(type(전일가))

# 종목상태
종목상태 = kiwoom.GetMasterStockState("005930")
print(종목상태)

# 테마 그룹
import pprint
group = kiwoom.GetThemeGroupList(1)
pprint.pprint(group)

# 그룹 코드
tickers = kiwoom.GetThemeGroupCode('141')
print(tickers)

# 매수/매도
## 주식계좌
accounts = kiwoom.GetLoginInfo("ACCNO")
stock_account = accounts[0]

## 삼성전자, 10주, 시장가주문 매수
for i in range(10):
    kiwoom.SendOrder("시장가매수", "0101", stock_account, 1, "005930", 10, 0, "03", "")
    time.sleep(0.2)
    print(i, "매수 완료")

# 삼성전자, 10주, 시장가주문 매도
kiwoom.SendOrder("시장가매도", "0101", stock_account, 2, "005930", 10, 0, "03", "")

# 조건 검색
## 조건식을 PC로 다운로드
kiwoom.GetConditionLoad()
## 전체 조건식 리스트 얻기
conditions = kiwoom.GetConditionNameList()
## 0번 조건식에 해당하는 종목 리스트 출력
condition_index, condition_name = conditions[0]
codes = kiwoom.SendCondition("0101", condition_name, condition_index, 0)
print(codes)

# 싱글 데이터 TR
df = kiwoom.block_request("opt10001",
                          종목코드="005930",
                          output="주식기본정보",
                          next=0)
print(df)

# 멀티 데이터 TR
df = kiwoom.block_request("opt10081",
                          종목코드="005930",
                          기준일자="20200424",
                          수정주가구분=1,
                          output="주식일봉차트",
                          next=0)
print(df.head())
dfs.append(df)

## TR 요청 (연속조회)
dfs = []
df = kiwoom.block_request("opt10081",
                          종목코드="005930",
                          기준일자="20200424",
                          수정주가구분=1,
                          output="주식일봉차트조회",
                          next=0)
dfs.append(df)

while kiwoom.tr_remained:
    df = kiwoom.block_request("opt10081",
                              종목코드="005930",
                              기준일자="20200424",
                              수정주가구분=1,
                              output="주식일봉차트조회",
                              next=2)
    dfs.append(df)
    time.sleep(1)

df = pd.concat(dfs)
df.to_excel("005930.xlsx")

# 전 종목 일봉 데이터 엑셀로 저장
## 전종목 종목코드
kospi = kiwoom.GetCodeListByMarket('0')
kosdaq = kiwoom.GetCodeListByMarket('10')
codes = kospi + kosdaq

## 문자열로 오늘 날짜 얻기
now = datetime.datetime.now()
today = now.strftime("%Y%m%d")

## 전 종목의 일봉 데이터
for i, code in enumerate(codes):
    print(f"{i}/{len(codes)} {code}")
    df = kiwoom.block_request("opt10081",
                              종목코드=code,
                              기준일자=today,
                              수정주가구분=1,
                              output="주식일봉차트조회",
                              next=0)

    out_name = f"{code}.xlsx"
    df.to_excel(out_name)
    time.sleep(3.6)

# 전 종목 일봉 데이터 머지(merge) 
flist = os.listdir()
xlsx_list = [x for x in flist if x.endswith('.xlsx')]
close_data = []

for xls in xlsx_list:
    code = xls.split('.')[0]
    df = pd.read_excel(xls)
    df2 = df[['일자', '현재가']].copy()
    df2.rename(columns={'현재가': code}, inplace=True)
    df2 = df2.set_index('일자')
    df2 = df2[::-1]
    close_data.append(df2)

df = pd.concat(close_data, axis=1)
df.to_excel("merge.xlsx")

# 매수하기
df = pd.read_excel("momentum_list.xlsx")
df.columns = ["종목코드", "모멘텀", "순위"]

## 종목명 추가하기
kiwoom = Kiwoom()
kiwoom.CommConnect(block=True)
codes = df["종목코드"]
names = [kiwoom.GetMasterCodeName(code) for code in codes]
df['종목명'] = pd.Series(data=names)

## 매수하기
accounts = kiwoom.GetLoginInfo('ACCNO')
account = accounts[0]

for code in codes:
    ret = kiwoom.SendOrder("시장가매수", "0101", account, 1, code, 100, 0, "03", "")
    time.sleep(0.2)
    print(code, "종목 시장가 주문 완료")