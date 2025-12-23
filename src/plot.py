import serial
import time 
import numpy as np

import matplotlib
matplotlib.use("TkAgg")

import matplotlib.pyplot as plt
from collections import deque

#print(plt.get_backend())



arduino = serial.Serial(port='/dev/tty.usbmodem1201', baudrate=9600, timeout=.1)

# create rolling window
window_size = 1000 #TODO: see how big window size should be
data_deque = deque([0]*window_size, maxlen = window_size)
time_deque = deque([0]*window_size, maxlen = window_size)

# heartbeat marker storage
xBeat = deque(maxlen = window_size)
yBeat = deque(maxlen = window_size)


plt.ion()
fig, ax = plt.subplots()
line, = ax.plot(time_deque, data_deque)

beat_scatter = ax.scatter([], [], c='red', s=40)

ax.set_ylim(0, 1000)  
ax.set_xlabel("Time (sec)")
ax.set_ylabel("PPG Signal") #TODO: units


plt.show()
plt.pause(0.1)     

while True:
    data = arduino.readline().decode('utf-8').strip()
    if data:
        try:
            
            #print("Raw data:", repr(data))

            sensorVal, tov, beat = map(int, data.split(","))
            print(tov, sensorVal, beat)

            # update data 
            data_deque.append(sensorVal)
            time_deque.append(tov/1000)

            line.set_ydata(data_deque)
            line.set_xdata(time_deque)

            
            # add marker if beat is detected
            if beat == 1:
                xBeat.append(tov/1000)
                yBeat.append(sensorVal)
            
            # update scatterplot
            if beat == 1:
                xBeat.append(tov/1000)
                yBeat.append(sensorVal)

            if len(xBeat) > 0:
                offsets = np.column_stack((xBeat, yBeat))
            else:
                offsets = np.empty((0, 2))

            beat_scatter.set_offsets(offsets)


            # recompute limits and axes
            ax.relim()        
            ax.autoscale_view()  
            plt.pause(0.01) 

        except ValueError:
            print("error")

