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


SetTranInputData(nRequestId, "HHTACCNM01", "InRec1", "func", strfunc)