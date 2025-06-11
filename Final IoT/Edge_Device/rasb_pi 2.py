import serial
import time
import redis
import json
import time
from datetime import datetime
r = redis.Redis(host='127.0.0.1',port=6379, db=0)

# === Serial port setup ===

ser1 = serial.Serial('/dev/ttyACM1', 9600)
ser2 = serial.Serial('/dev/ttyACM0', 9600)

time.sleep(2)



# === Sensor and parking state tracking ===
light_level = None
distance = None

ultra_occupied = False
light_occupied = False
ultra_start_time = None
light_start_time = None

def update_history(distance):
    timestamp_label = time.strftime("%H:%M")
    
    try: # current
        historyval = r.get('disthistory')
        history = json.loads(historyval)
        labels = history.get('labels', [])
        dists = history.get('dists', [])
        # new
        labels.append(timestamp_label)
        dists.append(distance)
        # cycle
        labels = labels[-7:]
        dists = dists[-7:]
        
        r.set('disthistory', json.dumps({ "labels": labels, "dists": dists }))
              
            
        print("Updated history")
              
    except Exception as e:
        print(f"Error updating history for module {e}")



lastTime = int(time.time())
# === Main Loop ===
while True:
    
    if (int(time.time()) - lastTime) > 1:
        lastTime = int(time.time())
        print("Update fan state now")
        fan = r.get('fanState')
        
        com = fan.decode('utf-8')
        msg = (f'f:{com}\n')
        #print(fan.decode('utf-8'))
        ser1.write(msg.encode('utf-8'))
        ser2.write(msg.encode('utf-8'))

    #print(msg)
    
    if ser1.in_waiting > 0:
        line = ser1.readline().decode('utf-8').strip()
        #print(f"Raw line1: {line}")
        args=line.split(':')
        if len(args) < 2:
            continue
        
        print(line)
        #print(args)
        r.set(args[0],args[1])
        if args[0] == "Percen_capa":
            update_history(args[1])
        '''if args[0] == 'p':
            value = args[1]'''
    
    if ser2.in_waiting > 0:
        line = ser2.readline().decode('utf-8').strip()
        #print(f"Raw line2: {line}")
        
        args=line.split(':')
        if len(args) < 2:
            continue

        

            
        
        #print(args)
        r.set(args[0],args[1])
        
        
        
        
        
    
    
    
        
        
    
    
   
        

        
            

        
   
        

        
