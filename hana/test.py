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

hana = HanaAPI()
execute_login(hana, 2, pid, "Dltmdals1205!", "ol751205@@")
execute_logout(hana, pid)

m_nRqId = hana.CreateRequestID()
strMarketCode = 'U'
hana.SetFidInputData(m_nRqId, "9002", "001")
hana.SetFidInputData(m_nRqId, "9001", strMarketCode)
hana.SetFidInputData(m_nRqId, "GID", "1007")

strOutputFidList = "4,5,7,11,28,12,977"
strScreenNo = "9999"

hana.RequestFid(m_nRqId, strOutputFidList, strScreenNo)

nDataCnt = hana.GetFidOutputRowCnt(m_nRqId)

strTime = hana.GetFidOutputData(m_nRqId, "8", 0)
strPrice = hana.GetFidOutputData(m_nRqId, "4", 0)

m_nRqId = 0