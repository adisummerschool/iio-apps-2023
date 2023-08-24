import iio
import matplotlib.pyplot as plt
import numpy as np

ctxname = "ip:10.76.84.210"
ctx = iio.Context(ctxname)
dev = ctx.find_device("ad5592r_s")

channels = []
for i in range(6):
    channels.append(dev.find_channel("voltage" + str(i)))
    
for ch in channels:
    ch.enabled = True

sample_count = 32
buff = iio.Buffer(dev, sample_count, False)

# i = 0
# acceleration = []
# for ch in channels:
# #     print(ch.attrs["raw"].value)
#     adc_nr = int(ch.attrs["raw"].value)
#     voltage = float(adc_nr) * 2.5 / 4096
#     acceleration.append(float(adc_nr) / 4096)
#     
#     print("%d\t" % adc_nr + "%.2f\t" % voltage + "%.4f" % acceleration[i])
#     i = i + 1


plt.ion()

time = range(sample_count)

while True:
    buff.refill()
    data = buff.read()
    
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
    plt.axis([0, 32, -5000 ,5000])
    plt.draw()
    plt.pause(0.05)
    plt.clf()
    
#     x = int(channels[0].attrs["raw"].value) - int(channels[1].attrs["raw"].value)
#     y = int(channels[2].attrs["raw"].value) - int(channels[3].attrs["raw"].value)
#     z = int(channels[4].attrs["raw"].value) - int(channels[5].attrs["raw"].value)
#     
#     plt.plot([x], [y], 'ro')
#     
#     plt.axis([-4096, 4096, -4096, 4096])
#     plt.draw()
#     plt.pause(0.05)
#     plt.clf()



# for dev in ctx.devices:
#     if dev.channels:
#         for chan in dev.channels:
#             print("{} - {} - {}".format(ctxname, dev.name, chan._id))
#     else:
#         print("{} - {}".format(ctxname, dev.name))
