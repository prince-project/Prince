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
futures_code_list = kiwoom.GetGlobalFutureCodelist("6M") 