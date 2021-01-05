from _setting import *
#from _setting_prince import *

tloc = '%s/Prince' % gloc

qry = """
SELECT date, open, high, low, close FROM marketdata.index_data p
left join marketdata.index_info i on i.index = p.index_index
where i.index_name = 'SP500'
and p.type = 2
order by date
"""
spx = pd.read_sql(qry, engine_dev, parse_dates=['date'], index_col=['date'])['2000-1-1':]

qry = """
SELECT date, open, close FROM marketdata.index_data p
left join marketdata.index_info i on i.index = p.index_index
where i.index_name = 'VIX'
order by date
"""
vix = pd.read_sql(qry, engine_dev, parse_dates=['date'], index_col=['date'])

spx.ret = spx.close.pct_change()
spx.intra_vol = (spx.high - spx.low) / spx.close
spx.intra_bar = spx.intra_vol.rolling(3).mean().shift(1)*100*0.5

vix.mov_2 = vix.close.rolling(window=2).mean()
vix.mov_20 = vix.close.rolling(window=20).mean()
skew.mov_20 = skew.close.rolling(window=20).mean()
vix.mov_long = vix.close.rolling(window=100).mean()
vix.mov_short = vix.close.rolling(window=5).mean()

nn = 500
vix.rank = vix.mov_20.dropna().rolling(window=nn).apply(lambda x:( x.rank(ascending=True)[-1])/nn,raw=False)
skew.rank = skew.mov_20.dropna().rolling(window=nn).apply(lambda x:( x.rank(ascending=True)[-1])/nn,raw=False)

vix.trend = np.where(vix.mov_long > vix.mov_short, 1, 0)
vix.signal = pd.concat([vix.rank, skew.rank], axis=1).dropna().apply(lambda x: vix_s(x[0],x[1]),axis=1)

rt_signal = vix[['signal', 'trend']].dropna().apply(lambda x: rt_s(x[0],x[1]),axis=1)
vol_scale = vix.mov_2.dropna().rolling(window=scale_n).apply(lambda x:( x.rank(ascending=True)[-1])/scale_n,raw=False)

print(pd.concat([rt_signal.shift(1), spx.intra_bar, vol_scale.shift(1)], axis=1))


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
