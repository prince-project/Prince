import sys
import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
sys.path.append(os.path.abspath('C:\GitHub\Prince\hana'))
from lib_hana import *
from utils_hana import *
from tabulate import tabulate
#from Prince.hana.utils_hana import execute_logout

def _table(df):
    return tabulate(df, headers = 'keys', tablefmt = 'pipe')


loc = 'C:\Prince_Data'

pid = 'olguri'

login_mode = 0 #(0 - 리얼, 1 - 국내모의, 2 - 해외모의)

hana = HanaAPI()
execute_login(hana, login_mode, pid, "Dltmdals1205!", "ol751205@@")
execute_logout(hana, pid)

m_nRqId = hana.CreateRequestID()
hana.m_nRqId = m_nRqId
strMarketCode = 'CM'
hana.SetFidInputData(m_nRqId, "9001", strMarketCode)
#hana.SetFidInputData(m_nRqId, "9002", "FESXU21")
hana.SetFidInputData(m_nRqId, "GID", "1499")

strOutputFidList = "1,2,3,16,2624"
strScreenNo = "9999"

hana.RequestFid(m_nRqId, strOutputFidList, strScreenNo)
hana.RequestFidArray(m_nRqId, strOutputFidList, "1", "", "9999", 9999)

nDataCnt = hana.GetFidOutputRowCnt(m_nRqId)

strTime = hana.GetFidOutputData(m_nRqId, "8", 0)
strPrice = hana.GetFidOutputData(m_nRqId, "4", 0)

m_nRqId = 0