import sys
import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import importlib

sys.path.append(os.path.abspath('C:\GitHub\Prince\hana'))
from lib_hana import *
from utils_hana import *
from tabulate import tabulate
#from Prince.hana.utils_hana import execute_logout

"""
import lib_hana
importlib.reload(lib_hana)
from lib_hana import *
"""

def _table(df):
    return tabulate(df, headers = 'keys', tablefmt = 'pipe')


loc = 'C:\Prince_Data'

pid = 'olguri'

login_mode = 0 #(0 - 리얼, 1 - 국내모의, 2 - 해외모의)



hana = HanaAPI()
execute_login(hana, login_mode, pid, "Dltmdals1205!", "ol751205@@")
#execute_logout(hana, pid)


#------------------------------------
# 해외선물종목리스트 FID
#------------------------------------
hana.request_id = hana.CreateRequestID()
strMarketCode = 'FF'
hana.SetFidInputData(hana.request_id, "9001", strMarketCode)
#hana.SetFidInputData(m_nRqId, "9002", "FESXU21"
hana.SetFidInputData(hana.request_id, "GID", "3299")

#hana.fid_list = ['1','2','3','16','2624']
hana.fid_list = ['1','2','3','1448','2083','661','1170','1987','2467','2456','2457','2295','1396',
				'1773','1772','1731','2460','226','132','981','1203','1268','1171','2459','133',
                '1759','16','10','28','1762','1870','1871','2486','2487','815','9','128','129','2596']
strOutputFidList = ','.join(hana.fid_list)
strScreenNo = "9999"

#n_return = hana.RequestFid(m_nRqId, strOutputFidList, strScreenNo)
n_return = hana.RequestFidArray(hana.request_id, strOutputFidList, "1", "", "9999", 9999)
if n_return < 0:
    print(hana.GetLastErrMsg())

#------------------------------------
# 주식 종목 리스트
#------------------------------------
hana.request_id = hana.CreateRequestID()
strMarketCode = 'J'
hana.SetFidInputData(hana.request_id, "9001", strMarketCode)
hana.SetFidInputData(hana.request_id, "GID", "1199")

hana.fid_list = ['1','2','3','827','1893','2574','1993','1994','1995','2604','2605',
				'2606','1257','1998','2607','1996','225','53','16','56','55','2067',
				'684','1253','1254','1258','1251','2608','1252','1992','1256',
				'222','2129','2148','19','21','1896']
strOutputFidList = ','.join(hana.fid_list)
strScreenNo = "9999"

n_return = hana.RequestFidArray(hana.request_id, strOutputFidList, "1", "", "9999", 9999)
if n_return < 0:
    print(hana.GetLastErrMsg())


#------------------------------------
# 
#------------------------------------
hana.request_id = hana.CreateRequestID()
strMarketCode = 'J'
hana.SetFidInputData(hana.request_id, "9001", strMarketCode)
hana.SetFidInputData(hana.request_id, "9002", "000660")
hana.SetFidInputData(hana.request_id, "GID", "1000")

hana.fid_list = ['8', '4']
strOutputFidList = ','.join(hana.fid_list)
strScreenNo = "9999"

n_return = hana.RequestFid(hana.request_id, strOutputFidList, strScreenNo)
if n_return < 0:
    print(hana.GetLastErrMsg())


#------------------------------------
# Tran - 해외노릐 보유계좌 조회
#------------------------------------
hana.request_id = hana.CreateRequestID()
hana.SetTranInputData(nRequestId, "OTS5991Q03", "OTS5991Q03_in", "USR_ID", "olguri")
#------------------------------------

execute_logout(hana, pid)

#------------------------------------
#------------------------------------
#------------------------------------
res_info = read_res(res_code, res_type)

open("%s/%s.res" % (dir_path, res_code), "r")

res_code = 'OTS5991Q03'
dir_path = "C:/1Q OpenAPI/1QApiAgent/TranRes"

res_info = {}
res_info['input'] = {}
res_info['output'] = {}

input_line = False
output_line = False
i = 0
for line in open("%s/%s.res" % (dir_path, res_code), "r"):
    curline = line.split("\n")[0].split(", ")
    if len(curline) > 1:
        rec_name_line = curline[0].split("\t\t")

        if len(rec_name_line) > 1:

            if (rec_name_line[1][:8] == 'REC_NAME') & ~input_line:
                input_line = True
                res_info['input']['rec_name'] = rec_name_line[1][9:]
                res_info['input']['items'] = pd.DataFrame(columns=['item', 'caption'])
                continue

            #if (input_line) & (curline[0].split("\t\t\t ")[1][:5] == 'INDEX'):
            if (input_line) & (curline[1][:4] == 'ITEM'):
                res_info['input']['items'].loc[i, 'item'] = curline[1][5:]
                res_info['input']['items'].loc[i, 'caption'] = curline[4][8:]
                i  += 1
                continue

            if (rec_name_line[1][:8] == 'REC_NAME') & input_line:
                input_line = False
                output_line = True 
                i = 0
                res_info['output']['rec_name'] = rec_name_line[1][9:]
                res_info['output']['items'] = pd.DataFrame(columns=['item', 'caption'])
                continue                

            if (output_line) & (curline[1][:4] == 'ITEM'):
                res_info['output']['items'].loc[i, 'item'] = curline[1][5:]
                res_info['output']['items'].loc[i, 'caption'] = curline[4][8:]
                i  += 1
                continue


curline[0].split(", ")[1]