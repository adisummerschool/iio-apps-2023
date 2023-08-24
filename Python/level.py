import iio
import matplotlib.pyplot as plt

ctxname="ip:10.76.84.153"

ctx = iio.Context(ctxname)
dev = ctx.find_device("ad5592r_s")

channels = []
for i in range(6):
    channels.append(dev.find_channel("voltage"+str(i)))
    
plt.ion()
while True:
    x = int(channels[0].attrs["raw"].value) - int(channels[1].attrs["raw"].value)
    y = int(channels[2].attrs["raw"].value) - int(channels[3].attrs["raw"].value)
    plt.plot([x], [y], 'ro')
    
    plt.axis([-4095, 4095, -4095, 4095])
    plt.draw()
    plt.pause(0.05)
    plt.clf()
    