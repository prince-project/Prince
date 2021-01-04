from _setting_prince import *

tloc = '%s/Prince' % gloc

df = pd.read_pickle('%s/under_development/projects/202011_Vol/intra/bbg_data.pickle' % gloc)['2000':]



df['down']=df['spx_down_tailrisk'].apply(lambda x:  Function_moneyness(-0.25,30/250,x/100))-1
df['up']=df['spx_up_tailrisk'].apply(lambda x:  Function_moneyness(0.25,30/250,x/100))-1
df['tail']=df['up']/np.abs( df['down'])
df['down_zscore']=df['down'].fillna(method='ffill').rolling(window=250).apply(lambda x:(x[-1]-x.mean() )/x.std(),raw=False)
df['down_signal']=np.where(df['down_zscore']<-2,1,0)
df['vol_skew']=df['spx_down_tailrisk']-df['spx_up_tailrisk']

df['spx_fut_ret']=df['spx_ret'].shift(-1)
df['vix_fut_ret']=df['vxx_ret'].shift(-1)

df['spx_hl']=np.power(np.log(df['spx_high'])-np.log(df['spx_low']),2)
df['spx_oc']=np.power((np.log(np.maximum(df['spx_open'],df['spx_close']))-np.log(np.minimum(df['spx_open'],df['spx_close']))),2)
df['spx_on']=np.power(df['spx_close'].pct_change(),2)
df['spx_vidl']=0.8*(df['spx_hl']-df['spx_oc'])+0.2*(df['spx_on'])
exp_weight=[0.00170074,0.00426233,0.00743368,0.01111781,0.01525666,0.0198101,0.0247481,0.03004702,0.0356876,0.04165371,0.04793159,0.05450928,0.06137628,0.06852326,0.07594184,0.08362446,0.09156423,0.09975485,0.10819051,0.11686595]
df['spx_vid']=df['spx_vidl'].rolling(len(exp_weight)).apply(lambda x:np.sqrt(np.sum(np.array(x)*np.array(exp_weight))*250),raw=True)*100

df['rv']=df['vix_close'].shift(0)-df['spx_vid']

df['rv_signal']=np.where(df['rv']>0,1,0)


df['vix_zscore']=df['vix_close'].rolling(window=500).apply(lambda x:(x[-1]-x.mean() )/x.std(),raw=True)
df['skew_zscore']=df['skew_close'].rolling(window=500).apply(lambda x:(x[-1]-x.mean() )/x.std(),raw=True)

#df['spx_barri']=(df['spx_high']-df['spx_low'])/df['spx_close']
#df['vix_close']=df['spx_barri'].rolling(20).mean()*np.sqrt(252)

df['spx_ret']=df['spx_close'].pct_change()
df['spx_r_vol']=df['spx_ret'].rolling(window=20).std()*np.sqrt(252)
df['vix_20_mov']=df['vix_close'].rolling(window=20).mean()
df['vix_5_mov']=df['vix_close'].rolling(window=10).mean()
df['vix_2_mov']=df['vix_close'].rolling(window=2).mean()
df['skew_20_mov']=df['skew_close'].rolling(window=20).mean()
df['skew_5_mov']=df['skew_close'].rolling(window=5).mean()
df['spx_hvol']=df['spx_ret'].ewm(10).std()*np.sqrt(252)

df['hrv']=df['vix_close'].shift(1)/100-df['spx_hvol']
df['hrv_signal']=np.where(df['hrv']>0,1,0)

nn=500
nnn=500
df['vix_rank']=df['vix_20_mov'].dropna().rolling(window=nn).apply(lambda x:( x.rank(ascending=True)[-1])/nn,raw=False)
df['skew_rank']=df['skew_20_mov'].dropna().rolling(window=nn).apply(lambda x:( x.rank(ascending=True)[-1])/nn,raw=False)
df['rv_rank']=df['rv'].dropna().rolling(window=nn).apply(lambda x:( x.rank(ascending=True)[-1])/500,raw=False)

nnn=250
df['s_vix_rank']=df['vix_5_mov'].dropna().rolling(window=nnn).apply(lambda x:( x.rank(ascending=True)[-1])/nnn,raw=False)


scale_n=100
df['vol_scale']=df['vix_2_mov'].dropna().rolling(window=scale_n).apply(lambda x:( x.rank(ascending=True)[-1])/scale_n,raw=False)
df['intra_in_out']=np.where(df['vol_scale'] > 0.5,1,0)

df['vix_long_mov']=df['vix_close'].rolling(window=100).mean()
df['vix_short_mov']=df['vix_close'].rolling(window=5).mean()

df['vix_trend']=np.where(df['vix_long_mov']>df['vix_short_mov'],1,0)

df['level_signal']=np.where(df['vix_rank']>0.5,0,1)
df['skew_signal']=np.where(df['skew_rank']>=0.5,1,0)
df['s_level_signal']=np.where(df['s_vix_rank']>=0.5,1,0)

df['s_vix_signal']=df.loc[:,['s_vix_rank','skew_rank']].dropna().apply(lambda x: vix_s(x[0],x[1]),axis=1)
df['vix_signal']=df.loc[:,['vix_rank','skew_rank']].dropna().apply(lambda x: vix_s(x[0],x[1]),axis=1)
df['rt_signal']=df.loc[:,['vix_signal','vix_trend']].dropna().apply(lambda x: rt_s(x[0],x[1]),axis=1)

df['spx_micro_notional']=df['spx_close'].apply(lambda x: future_notional(x,Tick_Size=0.25, Tick_Value=1.25))
df['spx_mini_notional']=df['spx_close'].apply(lambda x: future_notional(x,Tick_Size=0.25, Tick_Value=12.5))
df['vix_notional']=df['vix_close'].apply(lambda x: future_notional(x,Tick_Size=0.05, Tick_Value=50))

C=df['rt_signal'].shift(1)*df['vix_fut_ret']#*df['hrv_signal'].shift(2)
#C=df['vix_signal'].shift(2)*df['spx_fu_ret']*-1#*df['rv_signal'].shift(1)
#C=df['rv_signal'].shift(1)*df['spx_fu_ret']
C1=df['rv_signal'].shift(2)*df['spx_fut_ret']*df['hrv_signal'].shift(2)
#df['rv_signal'].shift(2)
CCC=(1+C).cumprod()

CCC1=(1+C1).cumprod()
CCC1.loc['2017-09-01':'2020-12-31'].plot()

df['seokgoo_vix_signal']=df['rt_signal'].shift(1)
df['seokgoo_spx_signal']=df['rv_signal'].shift(2)*df['hrv_signal'].shift(2)
df['spx_intra_vol']=(df['spx_high']-df['spx_low'])/df['spx_close']
df['seokgoo_spx_intra_barri']=df['spx_intra_vol'].rolling(3).mean().shift(1)*100*0.5
df['intra_expo']=df['vol_scale'].shift(1)



seokgoo=pd.concat([df['seokgoo_spx_signal'],df['seokgoo_vix_signal'],df['seokgoo_spx_intra_barri'],df['intra_expo']],axis=1)
print(seokgoo.tail(2))

def rt_s(r,t):
    c=np.empty
    if r >= 0 and t == 1:
        c = -0.4 # 0.1
    #elif r ==-1 and t ==1:
     #   c = -1
    #elif r ==-1 and t ==0:
     #   c = -0.4
        
    else:
        c= r
    return c 

def vix_s(v,s):
    c=np.empty
    if v > 0.5 and s >0.5:
        c = 0 # 0.1
    elif v >0.5 and s <=0.5:
        c= -1  #9.5 
    elif v<=0.5 and s > 0.5:
        c = -0.7
    elif v <=0.5 and s <= 0.5:
        c = -0.3
    else:
        c=0
    return c 

