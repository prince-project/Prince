import yfinance as yf

#msft = yf.Ticker("MSFT")
#hist = msft.history(period="max")
#data = yf.download("SPY AAPL", start="2017-01-01", end="2017-04-30")
spx = yf.download("^GSPC", start="2021-01-01", end="2021-03-20")
