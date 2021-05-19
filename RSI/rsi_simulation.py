from _setting_prince import *

tloc = '%s/Prince/RSI' % gloc

data = pd.read_csv('%s/under_development/projects/202011_Vol/intra/ES_5min_UStime.csv'%gloc, parse_dates=[['Date', 'Time']]).set_index('Date_Time')

# RSI
# def: 100 - 100/(1 + avg up change/avg dn change)
#     = 100 * avg up change / (avg up change + avg dn change)

rsi_lookback = 14
#data['U'] = np.where(data['Close'].diff(1) > 0, data['Close'].diff(1), 0)
#data['D'] = np.where(df['Close'].diff(1) < 0, df['Close'].diff(1) *(-1), 0)
data['U'] = np.where(data['Close'].pct_change() > 0, data['Close'].pct_change(), 0)
data['D'] = np.where(data['Close'].pct_change() < 0, data['Close'].pct_change() *(-1), 0)
data['AU'] = data['U'].rolling(window=rsi_lookback, min_periods=rsi_lookback).mean()
data['AD'] = data['D'].rolling(window=rsi_lookback, min_periods=rsi_lookback).mean()
data['RSI'] = data['AU'].div(data['AD']+data['AU']) *100

data['time_s'] = 0
data.loc[data.between_time('23:35', '3:30').index, 'time_s'] = 1

# w/o RSI conditions
time_in = '23:35'
time_out = '3:30'
d2 = data.between_time(time_in, time_out).Close.to_frame()
d2.index = d2.index + pd.DateOffset(minutes=25)
d2['date'] = d2.index.date

trade_in_out = pd.concat([d2.groupby('date').first(),d2.groupby('date').last()], axis=1)
trade_in_out.columns = ['in', 'out']
trade_in_out['pnl'] = trade_in_out.diff(axis=1).iloc[:,1] * 50
trade_in_out['pnl_cost'] = trade_in_out['pnl'] - 0.25 * 2 * 50

trade_in_out.pnl.cumsum().plot()

fig, axe = plt.subplots(nrows=1, ncols=1, figsize=(12,8))
trade_in_out[['pnl', 'pnl_cost']].fillna(0).cumsum().plot(ax=axe, title='Go long 1 lot')
axe.title.set_size(14)
axe.set_xlabel('', fontsize=12)
axe.set_ylabel('$', fontsize=12)
axe.tick_params(axis='both', which='both', labelsize=12)
axe.tick_params(axis='x', rotation=0)
axe.legend(loc='upper left',prop={'size':12})
axe.grid(alpha=0.2)
plt.tight_layout()
plt.savefig('%s/pnl_gap_hours.png' % (tloc))

# with RSI conditions

###
data = pd.read_csv('%s/under_development/projects/202011_Vol/intra/ES_5min_UStime.csv'%gloc)
data['day']=pd.to_datetime(data['Date']+ ' ' + data['Time'])
df=data.copy()
df.index=data['day']

def fnRSI(Co, m_N):
    df=pd.DataFrame(Co.copy())
    df.columns=['C']
    #ind=Co.index
    #df=pd.DataFrame({'C':Co})
    #df.index=ind

    df['U']= np.where(df['C'].pct_change() > 0, df['C'].pct_change(), 0)
    df['D'] = np.where(df['C'].pct_change() < 0, df['C'].pct_change() *(-1), 0)

    df['AU'] = df['U'].rolling( window=m_N, min_periods=m_N).mean()
    df['AD'] = df['D'].rolling( window=m_N, min_periods=m_N).mean()
    df['RSI'] = df['AU'].div(df['AD']+df['AU']) *100
    
    return df['RSI']

RS=fnRSI(df['Close'],14)
df['RSI']=RS
df.head(50)

df.index=data['day']
start='23:35'
end='3:30'

df['time_s']=0
re_index=df.between_time(start,end).index
df['time_s'].loc[re_index]=1
df.head(100)

def rsi_trading(cc,rsi,time):
    df=pd.DataFrame({'cc':cc.copy()})
    ind=cc.index
    df.index=ind
    df['rsi']=rsi
    df['time']=time
    df['book']=0
    for i in df.index:
        if df['rsi'].loc[i] > 70 and df['time'].loc[i] ==1:
            df['book'].loc[i]= 0
        elif df['rsi'].loc[i] <30 and df['time'].loc[i] ==1:
            if df['book'].shift(1).loc[i] == 1:
                df['book'].loc[i]=1
            else:
                df['book'].loc[i] =1
        elif df['rsi'].loc[i] >=30 and  df['rsi'].loc[i] <=70 and df['time'].loc[i] ==1:
            if df['book'].shift(1).loc[i] ==1:
                df['book'].loc[i] =1
            else:
                df['book'].loc[i] =0
        else:
            df['book'].loc[i] =0
    return df

def rsi_trading2(cc,rsi,time):
    df=pd.DataFrame({'cc':cc.copy()})
    ind=cc.index
    df.index=ind
    df['rsi']=rsi
    df['time']=time
    df['book']=0
    for i in df.index:
        if df['rsi'].loc[i] < 70 and df['time'].loc[i] ==1:
            df['book'].loc[i]= 1
        elif df['rsi'].loc[i] >=70 and df['time'].loc[i] ==1:
            if df['book'].shift(1).loc[i] ==1:
                df['book'].loc[i] =1
            else:
                df['book'].loc[i] =0

    return df   

def rsi_trading3(cc,rsi,time):
    df=pd.DataFrame({'cc':cc.copy()})
    ind=cc.index
    df.index=ind
    df['rsi']=rsi
    df['time']=time
    df['book']=0
    for i in df.index:
        if df['rsi'].loc[i] < 30 and df['time'].loc[i] ==1:
            df['book'].loc[i]= 1
        elif df['rsi'].loc[i] >=30 and df['time'].loc[i] ==1:
            if df['book'].shift(1).loc[i] ==1:
                df['book'].loc[i] =1
            else:
                df['book'].loc[i] =0

    return df   

nam=df.loc['2010-1-1':]

T=rsi_trading(nam['Close'],nam['RSI'],nam['time_s'])

