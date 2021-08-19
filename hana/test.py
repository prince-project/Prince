import sys
import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import importlib

sys.path.append(os.path.abspath('C:\GitHub\Prince\hana'))
from lib_hana import *
from parser_hana import *
from utils_hana import *

from tabulate import tabulate

"""
import lib_hana
importlib.reload(lib_hana)
from lib_hana import *
"""

def _table(df):
    return tabulate(df, headers = 'keys', tablefmt = 'pipe')

pid = 'olguri'
pwd = "Dltmdals1205!" #hana.GetEncrpyt()
login_mode = 0 #(0 - 리얼, 1 - 국내모의, 2 - 해외모의)

hana = HanaAPI()
login(hana, login_mode, pid, pwd, "ol751205@@")
#logout(hana, pid)


#------------------------------------
# 해외선물종목리스트 FID
#------------------------------------
#hana.request_id = hana.CreateRequestID()
hana.rq_id_code_list = hana.CreateRequestID()
strMarketCode = 'FF'
hana.SetFidInputData(hana.rq_id_code_list, "9001", strMarketCode)
hana.SetFidInputData(hana.rq_id_code_list, "GID", "3299")

hana.fid_list = ['1','2','3','1448','2083','661','1170','1987','2467','2456','2457','2295','1396',
				'1773','1772','1731','2460','226','132','981','1203','1268','1171','2459','133',
                '1759','16','10','28','1762','1870','1871','2486','2487','815','9','128','129','2596']
strOutputFidList = ','.join(hana.fid_list)
strScreenNo = "9999"

n_return = hana.RequestFidArray(hana.rq_id_code_list, strOutputFidList, "1", "", strScreenNo, 9999)
if n_return < 0:
    print(hana.GetLastErrMsg())

#------------------------------------
# 현재가 조회 FID
#------------------------------------

strMarketCode = 'FF'
strRealName = 'V10'
strSymBol = 'VXMU21'

hana.rq_id_cur_price = hana.CreateRequestID()
if hana.cur_price_real_key is not None:
    hana.UnRegisterReal(strRealName, hana.cur_price_real_key)
    hana.cur_price_real_key = None
hana.cur_price_real_key = strSymBol

hana.SetFidInputData(hana.rq_id_cur_price, "9002", strSymBol)
hana.SetFidInputData(hana.rq_id_cur_price, "9001", strMarketCode)
hana.SetFidInputData(hana.rq_id_cur_price, "GID", "1000")

hana.fid_list = ['4','6','5','7','11','28','13','14','15']
strOutputFidList = ','.join(hana.fid_list)
strScreenNo = "9999"

n_return = hana.RequestFid(hana.rq_id_cur_price, strOutputFidList, strScreenNo)
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
# Tran - 해외모의 보유계좌 조회
#------------------------------------
hana.tr_code = 'OTS5991Q03'
hana.res_info = read_tr_res(hana.tr_code)
hana.output_rec_name =  hana.res_info['output']['rec_name'] #'OTS5991Q03_out'
hana.request_id = hana.CreateRequestID()
hana.SetTranInputData(hana.request_id, hana.tr_code, hana.res_info['input']['rec_name'], hana.res_info['input']['items'].item[0], 'olguri')

n_return = hana.RequestTran(hana.request_id, hana.tr_code, "Y", "1", "", "9999", "Q", 9999)
if n_return < 0:
    print(hana.GetLastErrMsg())

#------------------------------------
# Tran - 파생시세신청여부조회
#------------------------------------
hana.tr_code = 'OAM5760Q50'
hana.res_info = read_tr_res(hana.tr_code)
hana.output_rec_name =  hana.res_info['output']['rec_name'] #'OTS5991Q03_out'
hana.request_id = hana.CreateRequestID()
hana.SetTranInputData(hana.request_id, hana.tr_code, hana.res_info['input']['rec_name'], hana.res_info['input']['items'].item[0], 'Y')
hana.SetTranInputData(hana.request_id, hana.tr_code, hana.res_info['input']['rec_name'], hana.res_info['input']['items'].item[1], pid)

n_return = hana.RequestTran(hana.request_id, hana.tr_code, "Y", "1", "", "9999", "Q", 9999)
if n_return < 0:
    print(hana.GetLastErrMsg())

#------------------------------------
# Tran - 예수금내역
#------------------------------------
hana.tr_code = 'OTS5943Q01'
hana.res_info = read_tr_res(hana.tr_code)
hana.output_rec_name =  hana.res_info['output']['rec_name'] #'OTS5991Q03_out'
hana.request_id = hana.CreateRequestID()
hana.SetTranInputData(hana.request_id, hana.tr_code, hana.res_info['input']['rec_name'], hana.res_info['input']['items'].item[0], '2021/7/9')
hana.SetTranInputData(hana.request_id, hana.tr_code, hana.res_info['input']['rec_name'], hana.res_info['input']['items'].item[1], 'A66242597')
hana.SetTranInputData(hana.request_id, hana.tr_code, hana.res_info['input']['rec_name'], hana.res_info['input']['items'].item[2], '220')
hana.SetTranInputData(hana.request_id, hana.tr_code, hana.res_info['input']['rec_name'], hana.res_info['input']['items'].item[3], '1205')

n_return = hana.RequestTran(hana.request_id, hana.tr_code, "Y", "1", "", "9999", "Q", 9999)
if n_return < 0:
    print(hana.GetLastErrMsg())



 dir_path = "C:/1Q OpenAPI/1QApiAgent/TranRes"
 hana.LoadTranResource(dir_path)


