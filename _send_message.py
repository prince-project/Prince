import telepot
import pprint

token = {}
id = {}
token['smlee'] = "1385119781:AAExma3hOSbMJ4AsMJVEgx5NDGJANZfcN1Y"
token['shlee'] = "1698192054:AAHN88q2aPx88pGuMRHcXYBeCdtWL4L9L4E"
#token['sknam']

id['smlee'] = 34316367
id['shlee'] = 1524661832
#id['sknam']

bot = telepot.Bot(token['smlee'])
bot.sendMessage(chat_id=id['smlee'], text="test")

info = bot.getMe()
pprint.pprint(info)


url = 'https://api.telegram.org/bot{}/sendMessage'.format(token)
requests.get(url, params = {"chat_id" : '34316367', "text" : "Prince Project Under Construction"})


token = "1698192054:AAHN88q2aPx88pGuMRHcXYBeCdtWL4L9L4E"
#id = 1698192054
bot = telepot.Bot(token)
resp = bot.getUpdates()
pprint.pprint(resp)
