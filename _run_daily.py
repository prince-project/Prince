from _setting import *
#from _setting_prince import *
from datetime import timedelta

tloc = '%s/Prince' % gloc

#-------------------------------
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
#-------------------------------

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

qry = """
SELECT date, open, close FROM marketdata.index_data p
left join marketdata.index_info i on i.index = p.index_index
where i.index_name = 'SKEW'
order by date
"""
skew = pd.read_sql(qry, engine_dev, parse_dates=['date'], index_col=['date'])

spx['intra_vol'] = (spx.high - spx.low) / spx.close
spx['intra_bar'] = spx.intra_vol.rolling(3).mean() * 0.5

vix['mov_2'] = vix.close.rolling(window=2).mean()
scale_n = 100
vol_scale = vix.mov_2.dropna().rolling(window=scale_n).apply(lambda x:( x.rank(ascending=True)[-1])/scale_n,raw=False)


# calculate intra level
close_price = 3846.25# put in 16:00 C.T. price of S&P500 futures on the previous day
intra_level = close_price - close_price * spx['intra_bar'][-1]

print(pd.DataFrame([intra_level, vol_scale[-1]], index=['Level', 'Exposure']))