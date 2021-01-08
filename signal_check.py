from _setting import *
#from _setting_prince import *
from datetime import timedelta

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


#------------------
# verify VIX signal
#------------------
## miniVIX
## multiplier = $100 (c.f. VIX = $1,000)
## tickvalue = 0.05 * $100 = $5 (c.f. VIX = $50)

# load futures price
qry = """
SELECT date, expiry, open, high, low, close, volume, open_int FROM marketdata.futures_raw_data p
left join marketdata.market_info i on i.index = p.market_index
where market_index = 160
order by date, expiry
"""
dt = pd.read_sql(qry, engine_dev, parse_dates=['date'], index_col=['date', 'expiry'])
dt = dt[~dt.close.isnull()] # delete if close is nan

# load futures spec
qry = """
SELECT expiry,ticker,first_trade_date,last_trade_date,first_notice_date,first_delivery_date,contract_size,point_value,tick_size,margin_init,margin_sec FROM marketdata.futures_raw_spec
where market_index = '160'
"""
spec = pd.read_sql(qry, engine_dev, parse_dates=['date'], index_col=['expiry'])

# add roll_date that is 7 days prior to last_trade_date
spec['roll_date'] = spec.last_trade_date - timedelta(days=7)
## dt.loc[(spec.loc['2020M'].roll_date, ['2020M', '2020N']), 'close'] # to check roll_cost

# get expiry code for each day/contract
expiry = pd.DataFrame(index=dt.droplevel(1, axis=0).index.unique(), columns=['c%s'%i for i in np.arange(1,10)])
for d in spec.roll_date.values:
    if d >= today-timedelta(days=2):
        continue
    else:
        for i in np.arange(1,10):
            if (spec.roll_date.shift(i)==d).sum() == 1:
                expiry.loc[d]['c%s'%i] = spec[spec.roll_date.shift(i)==d].index[0]
expiry = expiry.ffill()['2005':]

# get price for each day/contract
price = pd.DataFrame(index=expiry.index, columns=expiry.columns)
for d in price.index:
    tmp = dt.loc[(d, expiry.loc[d].values), 'close']
    price.loc[d, expiry.loc[d][expiry.loc[d].isin(tmp.droplevel(0, axis=0).index)].index.values] = tmp.values

# price on roll dates
price_on_roll = price.loc[price.index.intersection(spec.roll_date.values)]
price_on_roll.index = pd.to_datetime(price_on_roll.index, format='%Y-%m-%d')

# roll cost
roll_cost = price_on_roll.diff(axis=1).iloc[:,1:] * -1
roll_cost.columns = ['c%s'%i for i in np.arange(1, 9)]

pnl = pd.concat([price.diff().c1, roll_cost.c1], axis=1).sum(axis=1)

#tmp = pd.concat([vf.close.diff(), rt_signal.shift()], axis=1)
tmp = pd.concat([pnl, rt_signal.shift()], axis=1)

vix_pnl = tmp.iloc[:,0] * tmp.iloc[:,1] * 100

fig, axe = plt.subplots(nrows=1, ncols=1, figsize=(10,8))
vix_pnl.cumsum().plot(ax=axe, title='miniVIX')
axe.title.set_size(14)
axe.set_xlabel('', fontsize=10)
axe.set_ylabel('$', fontsize=10)
axe.tick_params(axis='both', which='both', labelsize=10)
axe.tick_params(axis='x', rotation=0)
axe.grid(alpha=0.2)
axe.autoscale(tight=False)
plt.tight_layout()
plt.savefig('%s/pnl_vix_signal.png' % (tloc))

#--------------------
# verify Intra signal
#--------------------
## micro E-mini
## multiplier $5 (c.f E-mini $50)
## tick value = 0.25*$5 = $.125

#sf = get_data_ready('SP500', 0, fxrate, conn_dev)
#tmp = pd.concat([spx.close, sf.close], axis=1)

spx['barrier'] = (spx['high'] - spx['low']) / spx['close']
spx['bsmth'] = spx['barrier'].rolling(5).mean() * 0.5
spx['dlvl'] = (spx['close'] - spx['close'] * spx['bsmth']).shift(1)
spx['down'] = np.where(spx['dlvl'] >= spx['low'],1,0)
spx['open_lower'] = np.where(spx['open'] < spx['dlvl'], 1, 0)
spx['pnl_down'] = -5 * np.where(spx['open'] < spx['dlvl'], spx['down'] * (spx['close'] - spx['open']), spx['down'] * (spx['close'] - spx['dlvl']))
spx['pnl_down2'] = -5 * np.where(spx['open'] < spx['dlvl'], spx['down'] * (spx['close'] - spx['dlvl']), spx['down'] * (spx['close'] - spx['dlvl']))




#--------------------
# determine wegiths
#--------------------
vf = load_fut_data_db('VIX', conn_dev).close.to_frame()
sf = get_data_ready('SP500', 0, fxrate, conn_dev).close.to_frame()

vf['year'] = vf.index.year
vf['week'] = vf.index.week
vf_group = vf.groupby(['year', 'week']).last()
vf_wret =  vf_group.diff()
vf_ret = vf.close.diff().to_frame()

sf['year'] = sf.index.year
sf['week'] = sf.index.week
sf_group = sf.groupby(['year', 'week']).last()
sf_wret =  sf_group.diff()
sf_ret = sf.close.diff().to_frame()
