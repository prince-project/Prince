for i in np.arange(10000000):
    print(i)
    now = pd.Timestamp.today()
    if (now.hour >= 5) and (now.hour <= 6 ):
        exec(open('C:\GitHub\kiwoom\get_intraday_data.py', 'rt', encoding='UTF8').read())

    time.sleep(300)



