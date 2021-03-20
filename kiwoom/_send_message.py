import telepot 
import pprint

token = "1385119781:AAExma3hOSbMJ4AsMJVEgx5NDGJANZfcN1Y"
id =  34316367
token = "1698192054:AAHN88q2aPx88pGuMRHcXYBeCdtWL4L9L4E"
id = 1524661832
bot = telepot.Bot(token)
bot.sendMessage(chat_id=id, text="Prince Project Under Construction")

info = bot.getMe()
pprint.pprint(info)


url = 'https://api.telegram.org/bot{}/sendMessage'.format(token)
requests.get(url, params = {"chat_id" : '34316367', "text" : "Prince Project Under Construction"})


token = "1698192054:AAHN88q2aPx88pGuMRHcXYBeCdtWL4L9L4E"
#id = 1698192054
bot = telepot.Bot(token)
resp = bot.getUpdates()
pprint.pprint(resp)


