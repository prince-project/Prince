import sys
import os

sys.path.append(os.path.abspath('C:\GitHub\hana'))
from lib_hana import *

def login(HanaAPI, login_mode, pid, pwd, cert_pwd):

    #**********************************************************
    # 접속서버를 설정한다.(0 - 리얼, 1 - 국내모의, 2 - 해외모의)
    #**********************************************************       
    HanaAPI.SetLoginMode(0, login_mode)

    #**********************************************************
    # API에이전트에서 강제로 메시지 박스 실행하는 것을 막는다.
    #**********************************************************
    HanaAPI.SetOffAgentMessageBox(1)

    #**********************************************************
    # 이미 로그인한 상태인지 확인한다.
    #**********************************************************
    login_state = HanaAPI.GetLoginState()
    if login_state == 1:
        return print('******* Already logged-in *******')

    #**********************************************************
    # 통신을 연결한다.
    #**********************************************************
    comm_init = HanaAPI.CommInit()
    if comm_init < 0:
        return print(HanaAPI.GetLastErrMsg())

    #**********************************************************
    # 통신이 정상적으로 연결되었는지 확인
    #**********************************************************
    if HanaAPI.CommGetConnectState() != 1:
        return print('******* Connection failed *******')

    #**********************************************************
    # 로그인 시도
    #**********************************************************
    try_login = HanaAPI.CommLogin(pid, pwd, cert_pwd)
    if try_login != 1:
        return print(HanaAPI.GetLastErrMsg())
    else:
        print('******* login succeeded *******')
        HanaAPI.connected = True

    #**********************************************************
    # 로그인이 완료되면 주문 실시간을 등록한다.
    # 주문 실시간 통보는 사용자ID가 등록키가 된다.
    #**********************************************************
    # 체결 실시간 통보
    #HanaAPI.RegisterReal("EF1", pid)
    # 미체결 실시간 통보
    #HanaAPI.RegisterReal("EF4", pid)

def logout(HanaAPI, pid):

    #**********************************************************
    # LogOut 처리
    #**********************************************************        
    HanaAPI.CommLogout(pid)

    #**********************************************************
    # 통신 연결을 종료한다.
    #**********************************************************
    HanaAPI.CommTerminate(1)
    
    print('******* Logged-out successfully *******')