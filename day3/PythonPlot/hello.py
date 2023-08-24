import iio
import matplotlib.pyplot as plt
import numpy as np

ctxname="ip:10.76.84.208"

ctx = iio.Context(ctxname)
dev = ctx.find_device("ad5592r_s")

channels = []
for i in range(6):
    channels.append(dev.find_channel("voltage"+str(i)))
    
plt.ion()

for ch in channels:
    ch.enabled = True
    
nr_samples = 32
buf = iio.Buffer(dev,nr_samples,False)
time = range(nr_samples)


while True:
    buf.refill()
    data = buf.read()
    
    dt = '<u2'
    data = np.frombuffer(data, dtype=dt)
    
    xpoz = np.int32(data[0::6])
    xneg = np.int32(data[1::6])
    ypoz = np.int32(data[2::6])
    yneg = np.int32(data[3::6])
    zpoz = np.int32(data[4::6])
    zneg = np.int32(data[5::6])

    x = xpoz - xneg
    y = ypoz - yneg
    z = zpoz - zneg
    
    plt.plot(x,'r')
    plt.plot(y,'g')
    plt.plot(z,'b')
    plt.axis([0, 32, -10000 ,10000])
    plt.draw()
    plt.pause(0.05)
    plt.clf()