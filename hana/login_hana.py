import sys
import os
import pandas as pd
import numpy as np 
import matplotlib.pyplot as plt 
sys.path.append(os.path.abspath('C:\GitHub\hana'))
from lib_hana import *
from tabulate import tabulate

def _table(df):
    return tabulate(df, headers = 'keys', tablefmt = 'pipe')


loc = 'C:\Prince_Data'

hana = Hana()
hana.SetLoginMode(0, 2) # 해외모의
#**********************************************************
#이미 로그인한 상태인지 확인한다.
#**********************************************************
hana.GetLoginState()
#**********************************************************
#통신을 연결한다.
#**********************************************************
hana.CommInit()
#**********************************************************
#통신이 정상적으로 연결되었는지 확인
#**********************************************************
hana.CommGetConnectState()
#**********************************************************
#로그인 시도
#**********************************************************
hana.CommLogin("olguri", "Dltmdals1205!", "ol751205@@")
hana.GetLoginState()
#**********************************************************
#LogOut 처리
#**********************************************************
hana.CommLogout("olguri")
hana.GetLoginState()
#**********************************************************
#통신 연결을 종료한다.
#**********************************************************
hana.CommTerminate(1)

