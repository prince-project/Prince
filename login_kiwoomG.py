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


loc = 'C:\Prince_Data'

kiwoom = KiwoomG()
kiwoom.CommConnect(block=True)
print("블록킹 로그인 완료")

