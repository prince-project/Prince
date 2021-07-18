import yfinance as yf
import pandas as pd
import numpy as np
import os
import matplotlib as mpl
import matplotlib.pyplot as plt
import datetime as datetime
from scipy.stats import norm


# ###### Yahoo Down load
sdate = datetime.datetime(2000,1,1)
edate = datetime.datetime.today()
indices = {'VIX': '^vix', 'SKEW': '^skew', 'SPX': '^gspc'}
dt = {}
for index in indices.keys():
    dt[index] = yf.download(indices[index], sdate, edate).ffill()

# #####  Predict realized volatility with Intra information of high and low
dt['SPX']['HL'] = np.power(np.log(dt['SPX']['High']) - np.log(dt['SPX']['Low']), 2)
dt['SPX']['OC'] = np.power(np.log(np.maximum(dt['SPX']['Open'], dt['SPX']['Close'])) - np.log(np.minimum(dt['SPX']['Open'], dt['SPX']['Close'])), 2)
dt['SPX']['ON'] = np.power(dt['SPX']['Close'].pct_change(), 2)
dt['SPX']['VIDL'] = 0.8 * (dt['SPX']['HL'] - dt['SPX']['OC']) + 0.2 * dt['SPX']['ON']
exp_weight=[0.00170074,0.00426233,0.00743368,0.01111781,0.01525666,0.0198101,0.0247481,0.03004702,0.0356876,0.04165371,0.04793159,0.05450928,0.06137628,0.06852326,0.07594184,0.08362446,0.09156423,0.09975485,0.10819051,0.11686595]
dt['SPX']['VID'] = dt['SPX']['VIDL'].rolling(len(exp_weight)).apply(lambda x:np.sqrt(np.sum(np.array(x)*np.array(exp_weight))*250),raw=True)

# #### RV_Signal
rv = dt['VIX']['Close'].div(100.) - dt['SPX']['VID']
rv_signal = np.where(rv > 0, 1, 0)

#rv_min = np.sqrt(np.log(dt['SPX']['Close']).diff().pow(2.).rolling(10).mean()) * 16
#vrp = dt['VIX']['Close'].div(100.) - rv_min
#pd.concat([rv,vrp], axis=1)['2020':].plot()

# ##### Rolling data
dt['SPX']['ret'] = dt['SPX']['Close'].pct_change()
dt['VIX']['ret'] = dt['VIX']['Close'].diff()
dt['SPX']['ret_vol'] = dt['SPX']['ret'].rolling(window=20).std()*np.sqrt(252)
dt['SPX']['ewma_vol'] = dt['SPX']['ret'].ewm(10).std()*np.sqrt(252)
dt['VIX']['20_mov'] = dt['VIX']['Close'].rolling(window=22).mean()
dt['SKEW']['20_mov'] = dt['SKEW']['Close'].rolling(window=22).mean()
dt['SPX']['hvol'] = dt['SPX']['ret'].rolling(10).std()*np.sqrt(252)

# ##### Vix and Skew Signal
dt['VIX']['rank'] = dt['VIX']['20_mov'].rolling(window=500).apply(lambda x:( x.rank(ascending=True)[-1])/500,raw=False)
dt['SKEW']['rank'] = dt['SKEW']['20_mov'].rolling(window=500).apply(lambda x:( x.rank(ascending=True)[-1])/500,raw=False)

# #### Trend Signal
dt['VIX']['long_mov'] = dt['VIX']['Close'].rolling(window=100).mean()
dt['VIX']['short_mov'] = dt['VIX']['Close'].rolling(window=5).mean()
dt['VIX']['trend'] = np.where(dt['VIX']['long_mov'] > dt['VIX']['short_mov'], 1, -1)

# #### HRV_Signal
hrv = dt['VIX']['Close'].shift(1)/100 - dt['SPX']['hvol']
hrv_signal = np.where(hrv > 0, 1, 0)

# #### EWMA_Signal
ewmav = dt['VIX']['Close'].div(100.) - dt['SPX']['ewmav_vol']
ewmav_rank = ewmav.rolling(window=100).apply(lambda x:( x.rank(ascending=True)[-1])/100,raw=False)
ewmav_signal = np.where(ewmav_rank >= 0.1, -1, 0)

# #### Intra Signal
dt['VIX']['2_mov'] = dt['VIX']['Close'].rolling(window=2).mean()
scale_n=100
dt['VIX']['vol_rank'] = dt['VIX']['2_mov'].dropna().rolling(window=scale_n).apply(lambda x:( x.rank(ascending=True)[-1])/scale_n,raw=False)
intra_in_out = np.where(dt['VIX']['vol_rank'] > 0.6, 1, 0)

# #### Combine_VIX_Signal
com_vix_signal = (1 - dt['VIX'['vol_rank']]) + ewmav_rank
#df['com_vix_signal']=(1-df['vix_rank'])+df['skew_rank']
com_spx_in_out = np.where(com_vix_signal >= 0.5, 1, 0)
com_vix_profit_taking = np.where(com_vix_signal >= 1.5, 1, 0)

# #### Intra Vol
dt['SPX']['intra_vol'] = (dt['SPX']['High'] - dt['SPX']['Low']).div(dt['SPX']['Close'])
dt['SPX']['intra_barrier'] = dt['SPX']['intra_vol'].rolling(5).mean() * 100 * 0.5

# #### Vol Expected
df['vix_diff']=df['vix_close'].diff(15)/15
df['vix_diff'].plot()
df['vix_carry']=df['ewmav']/22*100

df['vix_diff_rank']=df['vix_diff'].dropna().rolling(window=250).apply(lambda x:( x.rank(ascending=True)[-1])/250,raw=False)
df['vix_carry_rank']=df['vix_carry'].dropna().rolling(window=250).apply(lambda x:( x.rank(ascending=True)[-1])/250,raw=False)

df['vix_ex']=df['vix_carry_rank']-df['vix_diff_rank']

#----------------------------
# final signals
#----------------------------

rst = {}
rst['spx_signal'] = np.where(com_spx_in_out.shift(1) == 1, 'Buy S&P500', 'Neutral')
rst['vix_signal'] = np.where(ewmav_signal == -1, 'Sell VIX', 'Neutral')
rst['profilt_taking'] = np.where(com_vix_profit_taking == 1, 'VIX Profit taking', 'No Action')
rst['intra_in_out'] = np.where(intra_in_out == 1, 'Enter', 'No Action')
rst['intra_barrier'] = dt['SPX']['intra_barrier']

rst = pd.concat(rst, axis=1)

# #####  Return Simulation
df['spx_fut_ret']=df['spx_ret']
df['vix_fut_ret']=df['vix_ret']

C=df['rt_signal'].shift(1)*df['spx_fut_ret']*-1
C1=df['rv_signal'].shift(2)*df['spx_fut_ret']*df['hrv_signal'].shift(2)*2
C2=df['com_spx_in_out'].shift(3)*df['spx_fut_ret']
C4=df['com_vix_profit_taking'].shift(2)*df['vix_fut_ret']
BM=df['spx_fut_ret']
#C1=(df['rv_signal'].shift(2)*df['skew_rank'].shift(2))*df['spx_fu_ret']*3#*df['ewmarv_signal'].shift(1)
#C1=df['hrv_signal'].shift(1)*df['spx_fu_ret']*5
CCC=(1+C).cumprod()
CCC1=(1+BM).cumprod()
CCC2=(1+C2).cumprod()
CD=C4.cumsum()

CD.loc['2020-01-01':].plot()
CCC2.loc['2007-01-01':].plot(legend=True)
CCC1.loc['2007-01-01':].plot()
