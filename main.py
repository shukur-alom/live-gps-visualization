import paho.mqtt.client as paho
import streamlit as st
import pandas as pd

try:
    client = paho.Client()
    client.connect('broker.hivemq.com', 1883)
    client.loop_start()
    client.subscribe('gps/53384', qos=1)
    client.subscribe('gps/count/53384', qos=1)

except: print("\n\n\n\t\tCheck Your Internet Connection\n\n")


latitude = 23.7840857
longitude = 90.3452895
set_count = 0

def on_message(client, userdata, msg):
    global latitude
    global longitude
    global set_count
    #print(msg.topic+" "+str(msg.qos)+" "+str(msg.payload))
    if msg.topic == "gps/53384":
        cor = str(msg.payload)[2:-1].split(",")
        latitude = float(cor[0])
        longitude = float(cor[1])


    elif msg.topic == "gps/count/53384":
        set_count = int(msg.payload)

map_container = st.empty()
la = ""
lo = ""

while 1:
    client.on_message = on_message
    if str(latitude)[:7] != la or str(longitude)[:7] != lo:
        print(la,latitude)
        print(lo,longitude)

        map_container.empty()

        df = pd.DataFrame(
            [[latitude,longitude]],
            columns=['lat', 'lon'])
        map_container.map(df,zoom=18,size=2,use_container_width=True)
        
        la = str(latitude)[:7]
        lo = str(longitude)[:7]