import sys
import time
import os
from datetime import timedelta, datetime
import pandas as pd
import PyQt5
from PyQt5.QAxContainer import QAxWidget
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from apscheduler.schedulers.qt import QtScheduler
from PyQt5.QtGui import QIcon

sys.path.append(os.path.abspath('C:\GitHub\hana'))

# base class for HanaAPI
class HanaAPI(QAxWidget):
    def __init__(self, event_loop):
        super().__init__()

        # get common part
        self.setControl("ITGExpertCtl.ITGExpertCtlCtrl.1")
        self.event_loop = event_loop
        self.ReceiveData.connect(self.receive_data)
        # for prod, commented out this statement if you cannot receive any data
        #self.dynamicCall("SetConnectID(Qstring)", "linecorp")
        self.account = self.dynamicCall("GetAccount(0)")[:8]
        self.fund_index = fund_index
        self.encrypted_pw = None

        self.need_postprocess = False
        self.initialize()

    def __del__(self):
        pass

    def request_data(self, password, target_date, encrypted_pw=None):
        print("Start of request_data on TR ", self.service_id)
        time.sleep(0.1)
        if encrypted_pw is not None:
            self.encrypted_pw = encrypted_pw
        else:
            self.encrypted_pw = self.dynamicCall("GetEncryptPassword(Qstring)", password)
        print("Get password")
        self.target_date = target_date
        print("Set Single data")
        self.set_single_data()
        self.dynamicCall("RequestData(Qstring)", self.service_id)
        print("Request Data on TR ", self.service_id)
        self.event_loop.exec_()

    def receive_data_internal(self):
        return_code = self.dynamicCall("GetReqMessage()")
        print("Received return message: " + return_code)

        record_count = self.dynamicCall("GetMultiRecordCount(int)", self.multi_block_id)
        if record_count == 0:
            print("Received nothing")
            return

        matrix = []
        for i in range(record_count):
            row = []
            for j in self.request_col_ids:
                HTS_data = self.dynamicCall("GetMultiData(int, int, int, int)", self.multi_block_id, i, j, 0)
                row.append(HTS_data)
            matrix.append(row)

        data = pd.DataFrame(matrix)
        if self.add_date:
            data.insert(0, 'date', self.target_date)
        data.columns = self.col_name
        data.insert(1, 'fund_index', self.fund_index)
        index_cols = self.index_cols
        index_cols.append('fund_index')
        if self.need_postprocess:
            data = self.postprocess(data)
        dl.upsert_data_row_by_row(data, self.target_table, index_cols, dl.get_engine("strategy_backtest"))

    def postprocess(self, data):
        # this is just a mark that you can use postprocess
        pass

    def receive_data(self):
        self.receive_data_internal()
        if self.dynamicCall("IsMoreNextData()"):
            self.dynamicCall("RequestNextData(Qstring)", self.service_id)
        else:
            self.event_loop.exit()

    # would be specialized for each KISAPI subclass
    def initialize(self):
        # index info for fetching from expert
        self.multi_block_id = 0
        self.request_col_ids = [0]
        self.target_table = "sample_table"
        self.service_id = "sample_id"

    def set_single_data(self):
        # Following is a sample code
        # self.dynamicCall("SetSingleData(int, Qstring)", 0, self.account)
        # self.dynamicCall("SetSingleData(int, Qstring)", 1, "03")
        # self.dynamicCall("SetSingleData(int, Qstring)", 2, self.encrypted_pw)
        pass
