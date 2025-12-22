import serial
import time 

import matplotlib
matplotlib.use("TkAgg")

import matplotlib.pyplot as plt
from collections import deque

#print(plt.get_backend())



arduino = serial.Serial(port='/dev/tty.usbmodem1201', baudrate=9600, timeout=.1)

window_size = 1000 #TODO: see how big window size should be
data_deque = deque([0]*window_size, maxlen=window_size)
time_deque = deque([0]*window_size, maxlen=window_size)

plt.ion()
fig, ax = plt.subplots()
line, = ax.plot(time_deque, data_deque)
ax.set_ylim(0, 1000)  
ax.set_xlabel("Time (sec)")
ax.set_ylabel("PPG Signal") #TODO: units


plt.show()
plt.pause(0.1)     

while True:
    data = arduino.readline().decode('utf-8').strip()
    if data:
        try:
            
            sensorVal, tov = map(int, data.split(","))

            data_deque.append(sensorVal)
            time_deque.append(tov/1000)

            # update plot
            line.set_ydata(data_deque)
            line.set_xdata(time_deque)
            ax.relim()        # Recompute limits
            ax.autoscale_view()  # Rescale axes
            plt.pause(0.01) 

        except ValueError:
            print("error")

