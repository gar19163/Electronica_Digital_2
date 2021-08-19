# Código de ejemplo AdafruitIO
# Universidad del Valle de Guatemala
# IE3027 - Electrónica Digital 2
# Diego Morales

# Adafruit IO
# https://io.adafruit.com/

# if Module not Found. Open Terminal/CMD and execute:
# pip3 install Adafruit_IO

from Adafruit_IO import Client, RequestError, Feed

ADAFRUIT_IO_USERNAME = "aleaguirre"
ADAFRUIT_IO_KEY = "aio_vaar6105OJ2GfRF9phRfrCgTzyQY"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

#Sensor 1 Feed
lab05s1_feed = aio.feeds('lab05s1')
aio.send_data(lab05s1_feed.key, 8)
lab05s1_data = aio.receive(lab05s1_feed.key)
print(f'Valor de sensor 1: {lab05s1_data.value}')


#Sensor 2 Feed
lab05s2_feed = aio.feeds('lab05s2')
aio.send_data(lab05s2_feed.key, 14)
lab05s2_data = aio.receive(lab05s2_feed.key)
print(f'Valor de sensor 2: {lab05s2_data.value}')
