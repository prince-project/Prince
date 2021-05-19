import numpy as np
import pandas as pd 
import yfinance as yf

#msft = yf.Ticker("MSFT")
#hist = msft.history(period="max")
#data = yf.download("SPY AAPL", start="2017-01-01", end="2017-04-30")

spx = yf.download("^GSPC", start="2020-01-01", end=pd.Timestamp.today())
vix = yf.download("^VIX", start="2020-01-01", end=pd.Timestamp.today())

spx['intra_vol'] = (spx.High - spx.Low) / spx.Close
spx['intra_bar'] = spx.intra_vol.rolling(3).mean() * 0.5
vix['mov_2'] = vix.Close.rolling(window=2).mean()

vol_scale = vix.mov_2.dropna().rolling(window=100).apply(lambda x:( x.rank(ascending=True)[-1])/100, raw=False)

# calculate intra level
ticker = 'MESM21'
open_hour = kiwoom.block_request("opt10014",
                          종목코드=ticker,
                          output="single",
                          next=0)
open_hour = open_hour['시작시간'].values[0]
tmp = (pd.to_datetime(open_hour) - pd.Timedelta(hours=2)).hour
close_hour = '0%s0000'%tmp

today = pd.Timestamp.today()
dt = pd.read_pickle('%s/%s_%s.pickle' % (loc, ticker, today.date()))
close_val = abs(float(dt[dt['체결시간n'] == close_hour]['현재가n'].values[0]))

close_val = 4199.75 # put in 16:00 C.T. price of S&P500 futures on the previous day
intra_level = close_val - close_val * spx['intra_bar'][-1]

print(pd.DataFrame([intra_level, vol_scale[-1]], index=['Level', 'Exposure']))
