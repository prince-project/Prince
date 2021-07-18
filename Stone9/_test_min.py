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

rv = dt['VIX']['Close'].div(100.) - dt['SPX']['VID']


vol_carry['rv'] = np.sqrt(np.log(data[row.index_name_0]).diff().pow(2.).rolling(vc_rv_rolling_days).mean()) * 16 * 100
vol_carry['vrp'] = data[row.index_name_1].subtract(vol_carry['rv'])

# ##### Rolling data
dt['SPX']['ret'] = dt['SPX']['Close'].pct_change()
dt['VIX']['ret'] = dt['VIX']['Close'].diff()


df['spx_ret']=df['spx_close'].pct_change()
df['vix_ret']=df['vix_close'].diff()
df['spx_r_vol']=df['spx_ret'].rolling(window=20).std()*np.sqrt(252)
df['vix_20_mov']=df['vix_close'].rolling(window=22).mean()
df['skew_20_mov']=df['skew_close'].rolling(window=22).mean()
df['spx_hvol']=df['spx_ret'].rolling(10).std()*np.sqrt(252)
df['hrv']=df['vix_close'].shift(1)/100-df['spx_hvol']
df['spx_ewma_vol']=df['spx_ret'].ewm(10).std()*np.sqrt(252)

# ##### Vix and Skew Signal
df['vix_rank']=df['vix_20_mov'].rolling(window=500).apply(lambda x:( x.rank(ascending=True)[-1])/500,raw=False)
df['skew_rank']=df['skew_20_mov'].rolling(window=500).apply(lambda x:( x.rank(ascending=True)[-1])/500,raw=False)

# #### Trend Signal
df['vix_long_mov']=df['vix_close'].rolling(window=100).mean()
df['vix_short_mov']=df['vix_close'].rolling(window=5).mean()
df['vix_trend']=np.where(df['vix_long_mov']>df['vix_short_mov'],1,-1)

# #### HRV_Signal
df['hrv']=df['vix_close'].shift(1)/100-df['spx_hvol']
df['hrv_signal']=np.where(df['hrv']>0,1,0)

# #### EWMA_Signal
df['ewmav']=df['vix_close']/100-df['spx_ewma_vol']
df['ewmav_rank']=df['ewmav'].rolling(window=100).apply(lambda x:( x.rank(ascending=True)[-1])/100,raw=False)
df['ewmav_signal']=np.where(df['ewmav_rank'] >= 0.1,-1,0)

# #### RV_Signal
df['rv_signal']=np.where(df['rv']>0,1,0)

# #### Intra Signal
df['vix_2_mov']=df['vix_close'].rolling(window=2).mean()
scale_n=100
df['vol_rank']=df['vix_2_mov'].dropna().rolling(window=scale_n).apply(lambda x:( x.rank(ascending=True)[-1])/scale_n,raw=False)
df['intra_in_out']=np.where(df['vol_rank'] > 0.6,1,0)

# #### Combine_VIX_Signal
df['com_vix_signal']=(1-df['vol_rank'])+df['ewmav_rank']
#df['com_vix_signal']=(1-df['vix_rank'])+df['skew_rank']
df['com_spx_in_out']=np.where(df['com_vix_signal']>=0.5,1,0)
df['com_vix_profit_taking']=np.where(df['com_vix_signal']>=1.5,1,0)
df['com_vix_profit_taking'].tail(100)

# #### Vol Expected
df['vix_diff']=df['vix_close'].diff(15)/15
df['vix_diff'].plot()
df['vix_carry']=df['ewmav']/22*100

df['vix_diff_rank']=df['vix_diff'].dropna().rolling(window=250).apply(lambda x:( x.rank(ascending=True)[-1])/250,raw=False)
df['vix_carry_rank']=df['vix_carry'].dropna().rolling(window=250).apply(lambda x:( x.rank(ascending=True)[-1])/250,raw=False)

df['vix_ex']=df['vix_carry_rank']-df['vix_diff_rank']

# ##### Vix & Skew Signal
def vix_s(v,s):
    c=np.empty
    if v > 0.5 and s >0.5:
        c = 0 # 0.1
    elif v >0.5 and s <=0.75:
        c= -1.5  #9.5
    elif v<=0.5 and s > 0.5:
        c = -1
    elif v <=0.5 and s <= 0.5:
        c = -0.3
    else:
        c=0
    return c

def rt_s(r,t):
    c=np.empty
    if r >= 0 and t == 1:
        c = -0.4 # 0.1
    else:
        c= r
    return c

df['vix_signal']=df.loc[:,['vix_rank','skew_rank']].dropna().apply(lambda x: vix_s(x[0],x[1]),axis=1)
df['rt_signal']=df.loc[:,['vix_signal','vix_trend']].dropna().apply(lambda x: rt_s(x[0],x[1]),axis=1)

#df['seokgoo_vix_signal']=df['rt_signal'].shift(1)
df['seokgoo_spx_signal']=np.where(df['com_spx_in_out'].shift(1)==1,'BUY S&P500','Neutral')
df['spx_intra_vol']=(df['spx_high']-df['spx_low'])/df['spx_close']
df['seokgoo_spx_intra_barri']=df['spx_intra_vol'].rolling(5).mean()*100*0.5

df['seokgoo_vix_signal']=np.where(df['ewmav_signal']==-1, 'Sell VIX','Neutral')
df['seokgoo_profit_taking']=np.where(df['com_vix_profit_taking'] ==1,'Profit_taking','No Action')
df['seokgoo_intra_in_out']=np.where(df['intra_in_out'] ==1, 'Enter','No Action')

seokgoo=pd.concat([df['seokgoo_spx_signal'],df['seokgoo_vix_signal'],df['seokgoo_profit_taking'],df['seokgoo_intra_in_out'],df['seokgoo_spx_intra_barri']],axis=1)

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

# ##### mean Reverstion Strategy
def mean_reverting(da,nday):
    import numpy as np
    ww=[]
    for i in range(nday):
        ww.append(i+1)
    da=np.array(da)
    weight=np.dot(da,ww)*-1*4
    #weight=np.where(weight<0,0,weight)
    return weight

ww=[]
for i in range(5):
    ww.append(i+1)

q=np.array(ww)

x=df['spx_ret'].tail(5).T
mean_reverting(x,5)

df['wei']=df['spx_ret'].dropna().rolling(10).apply(lambda x: mean_reverting(x,10),raw=False)
df['wei'].plot()
