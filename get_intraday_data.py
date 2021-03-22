ticker = 'MESM21'
dfs = []
df = kiwoom.block_request("opt10012",
                          종목코드=ticker,
                          시간단위="1",
                          output="multi",
                          next="")
dfs.append(df)

while kiwoom.tr_remained:
    df = kiwoom.block_request("opt10012",
                          종목코드=ticker,
                          시간단위="1",
                          output="multi",
                          next=kiwoom.next)
    dfs.append(df)
    time.sleep(1)

df = pd.concat(dfs)

today = pd.Timestamp.today()
df.to_pickle('%s/%s_%s.pickle' % (loc, ticker, today.date()))
#df.to_excel("005930.xlsx")