from pykiwoom.kiwoom import *

kiwoom = Kiwoom()
kiwoom.CommConnect(block=True)
print("블록킹 로그인 완료")

# 사용자 정보 얻어오기
account_num = kiwoom.GetLoginInfo("ACCOUNT_CNT")        # 전체 계좌수
accounts = kiwoom.GetLoginInfo("ACCNO")                 # 전체 계좌 리스트
user_id = kiwoom.GetLoginInfo("USER_ID")                # 사용자 ID
user_name = kiwoom.GetLoginInfo("USER_NAME")            # 사용자명
keyboard = kiwoom.GetLoginInfo("KEY_BSECGB")            # 키보드보안 해지여부
firewall = kiwoom.GetLoginInfo("FIREW_SECGB")           # 방화벽 설정 여부

print(account_num)
print(accounts)
print(user_id)
print(user_name)
print(keyboard)
print(firewall)

# 종목코드 얻기

#파라미터	시장
#"0"	코스피
#"3"	ELWs
#"4"	뮤추얼펀드
#"5"	신주인수권
#"6"	리츠
#"8"	ETF
#"9"	하이얼펀드
#"10"	코스닥
#"30"	K-OTC
#"50"	코넥스

kospi = kiwoom.GetCodeListByMarket('0')
kosdaq = kiwoom.GetCodeListByMarket('10')
etf = kiwoom.GetCodeListByMarket('8')

print(len(kospi))
print(len(kosdaq))
print(len(etf))

# 종목명 얻기
name = kiwoom.GetMasterCodeName("005930")
print(name)

# 연결상태 확인
state = kiwoom.GetConnectState()
if state == 0:
    print("미연결")
elif state == 1:
    print("연결완료")

# 상장주식수 얻기
stock_cnt = kiwoom.GetMasterListedStockCnt("005930")
print("삼성전자 상장주식수: ", stock_cnt)

# 감리 구분
감리구분 = kiwoom.GetMasterConstruction("005930")
print(감리구분)

# 상장일
상장일 = kiwoom.GetMasterListedStockDate("005930")
print(상장일)
print(type(상장일))   

# 전일가
전일가 = kiwoom.GetMasterLastPrice("005930")
print(int(전일가))
print(type(전일가))

# 종목상태
종목상태 = kiwoom.GetMasterStockState("005930")
print(종목상태)

# 테마 그룹
import pprint
group = kiwoom.GetThemeGroupList(1)
pprint.pprint(group)

# 조건 검색
# 조건식을 PC로 다운로드
kiwoom.GetConditionLoad()

# 전체 조건식 리스트 얻기
conditions = kiwoom.GetConditionNameList()

# 0번 조건식에 해당하는 종목 리스트 출력
condition_index = conditions[0][0]
condition_name = conditions[0][1]
codes = kiwoom.SendCondition("0101", condition_name, condition_index, 0)

print(codes)
