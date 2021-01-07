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

qry = """
SELECT date, open, close FROM marketdata.index_data p
left join marketdata.index_info i on i.index = p.index_index
where i.index_name = 'SKEW'
order by date
"""
skew = pd.read_sql(qry, engine_dev, parse_dates=['date'], index_col=['date'])

vf = load_fut_data_db('VIX', conn_dev).close

spx['ret'] = spx.close.pct_change()
spx['intra_vol'] = (spx.high - spx.low) / spx.close
spx['intra_bar'] = spx.intra_vol.rolling(3).mean().shift(1)*100*0.5

vix['mov_2'] = vix.close.rolling(window=2).mean()
vix['mov_20'] = vix.close.rolling(window=20).mean()
vix['mov_long'] = vix.close.rolling(window=100).mean()
vix['mov_short'] = vix.close.rolling(window=5).mean()
skew['mov_20'] = skew.close.rolling(window=20).mean()

nn = 500
vix['rank'] = vix.mov_20.dropna().rolling(window=nn).apply(lambda x:( x.rank(ascending=True)[-1])/nn,raw=False)
skew['rank'] = skew.mov_20.dropna().rolling(window=nn).apply(lambda x:( x.rank(ascending=True)[-1])/nn,raw=False)

vix['trend'] = np.where(vix.mov_long > vix.mov_short, 1, 0)
vix['signal'] = pd.concat([vix['rank'], skew['rank']], axis=1).dropna().apply(lambda x: vix_s(x[0],x[1]),axis=1)

rt_signal = vix[['signal', 'trend']].dropna().apply(lambda x: rt_s(x[0],x[1]),axis=1)
scale_n = 100
vol_scale = vix.mov_2.dropna().rolling(window=scale_n).apply(lambda x:( x.rank(ascending=True)[-1])/scale_n,raw=False)

ot = pd.concat([rt_signal.shift(1), spx.intra_bar, vol_scale.shift(1)], axis=1)
ot.columns = ['vix_signal', 'intra_barrier', 'exposure']
print(ot)


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

# how to determine the number of lots to hold given capital
## drawdown analysis
## calcualte dollar pnl for miniVIX

# miniVIX
## multiplier = $100 (c.f. VIX = $1,000)
## tickvalue = 0.05 * $100 = $5 (c.f. VIX = $50)

## verify VIX signal

tmp = pd.concat([vf.close.diff(), rt_signal.shift()], axis=1)

pnl = tmp.iloc[:,0] * tmp.iloc[:,1] * 100

fig, axe = plt.subplots(nrows=1, ncols=1, figsize=(10,8))
pnl.cumsum().plot(ax=axe, title='miniVIX - trading 1 lot')
axe.title.set_size(14)
axe.set_xlabel('', fontsize=10)
axe.set_ylabel('$', fontsize=10)
axe.tick_params(axis='both', which='both', labelsize=10)
axe.tick_params(axis='x', rotation=0)
axe.grid(alpha=0.2)
axe.autoscale(tight=False)
plt.tight_layout()
plt.savefig('%s/pnl_vix_signal.png' % (tloc))