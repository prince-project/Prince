for i in np.arange(10000000):
    now = pd.Timestamp.today()
    print(now)
    if (now.hour >= 5) and (now.hour <= 6):
        exec(open('C:\GitHub\kiwoom\get_intraday_data.py', 'rt', encoding='UTF8').read())

    if now.hour == 7:
        break

    time.sleep(300)

test = pd.read_pickle('%s/%s_%s.pickle' % (loc, ticker, today.date()))

test = pd.read_pickle('%s/%s_%s.pickle' % (loc, ticker, '2021-03-25'))
abs(float(test['현재가n']).values[0]))
test['현재가n'].plot()