import yfinance as yf

#msft = yf.Ticker("MSFT")
#hist = msft.history(period="max")
#data = yf.download("SPY AAPL", start="2017-01-01", end="2017-04-30")

spx = yf.download("^GSPC", start="2020-01-01", end="2021-03-20")
vix = yf.download("^VIX", start="2020-01-01", end="2021-03-20")

spx['intra_vol'] = (spx.High - spx.Low) / spx.Close
spx['intra_bar'] = spx.intra_vol.rolling(3).mean() * 0.5
vix['mov_2'] = vix.Close.rolling(window=2).mean()

vol_scale = vix.mov_2.dropna().rolling(window=100).apply(lambda x:( x.rank(ascending=True)[-1])/scale_n,raw=False)

# calculate intra level
close_price = 3846.25# put in 16:00 C.T. price of S&P500 futures on the previous day
intra_level = close_price - close_price * spx['intra_bar'][-1]

print(pd.DataFrame([intra_level, vol_scale[-1]], index=['Level', 'Exposure']))