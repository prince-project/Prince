import sys
import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
sys.path.append(os.path.abspath('C:\GitHub\Prince\hana'))
from lib_hana import *
from tabulate import tabulate

def _table(df):
    return tabulate(df, headers = 'keys', tablefmt = 'pipe')


loc = 'C:\Prince_Data'

hana = Hana()
hana.SetLoginMode(0, 2)
hana.GetLoginState()
hana.CommInit()
hana.CommGetConnectState()
hana.CommLogin("olguri", "Dltmdals1205!", "ol751205@@")
hana.GetLoginState()
hana.CommLogout("olguri")
hana.GetLoginState()

hana = Hana()
hana._execute_login(2, "olguri", "Dltmdals1205!", "ol751205@@")