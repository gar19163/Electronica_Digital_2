#Laboratorio 05
#Conección con ADAFRUIT
#PIC16F887
import serial
import time

from Adafruit_IO import Client, RequestError, Feed

ADAFRUIT_IO_USERNAME = "aleaguirre"
ADAFRUIT_IO_KEY = "aio_vaar6105OJ2GfRF9phRfrCgTzyQY"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

#Definimos serial
srl = serial.Serial('COM2',baudrate = 9600)
srl.time = 3
time.sleep(1)
while(1):

#----------------inicia lectura-----------------------
    sen0 = str(srl.read(9))
    sen1 = sen0.split(',')
    dato1 = sen1[1]
    print(dato1)
#--------------Envio datos a ADAFRUIT------------------
    #Sensor 1 Feed
    lab05s1_feed = aio.feeds('lab05s1')
    aio.send_data(lab05s1_feed.key, dato1)
    lab05s1_data = aio.receive(lab05s1_feed.key)
    print(f'Valor de contador: {lab05s1_data.value}')

#-----------------Inicio Escritura---------------------
    #Terminal Feed
    lab05s2_feed = aio.feeds('lab05s2')
    lab05s2_data = aio.receive(lab05s2_feed.key)
    print(f'Valor de AdaFruit: {lab05s2_data.value}')
    dato2 = int(lab05s2_data.value)
    dato_t = dato2.to_bytes(3, 'big')
    srl.write(dato_t)
    time.sleep(15)
