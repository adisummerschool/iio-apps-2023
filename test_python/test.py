#print("hello")

#ex 1
# import iio
# ctxname="ip:10.76.84.156"
# 
# ctx = iio.Context(ctxname)
# for dev in ctx.devices:
#     if dev.channels:
#         for chan in dev.channels:
#             print("{} - {} - {}".format(ctxname, dev.name, chan._id))
#     else:
#         print("{} - {}".format(ctxname, dev.name))

#ex 2
import iio
import matplotlib.pyplot as plt

ctxname="ip:10.76.84.156"
ctx = iio.Context(ctxname)
dev = ctx.find_device("ad5592r_s")
# ch0 = dev.find_channel("voltage0")
channels = []
for i in range(6):
    channels.append(dev.find_channel("voltage"+str(i)))
plt.ion()
while True:
    
    x = int(channels[0].attrs["raw"].value) - int(channels[1].attrs["raw"].value)
    print("X = ", x)
    y = int(channels[2].attrs["raw"].value) - int(channels[3].attrs["raw"].value)
    print("Y = ", y)
    z = int(channels[4].attrs["raw"].value) - int(channels[5].attrs["raw"].value)
    print("Z = ", z)
    
    plt.plot([x], [y], "ro")
    plt.axis([-4095, 4095, -4095, 4095])
    plt.draw()
    plt.pause(0.05)
    plt.clf()
# for ch in channels:
#     print(ch.attrs["raw"].value)
