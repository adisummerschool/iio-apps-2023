import iio
import matplotlib.pyplot as plt
from array import array
import numpy as np

URI="ip:10.76.84.210"
ctx = iio.Context(URI)

dev = ctx.find_device("ad5592r_s")


channels = []
for i in range(6):
    channels.append(dev.find_channel(f"voltage{i}"))

for chn in channels:
    chn.enabled = True

buff = iio.Buffer(dev, 32)

while True:
    buff.refill()
    byte_data = buff.read()
    data = []

    for i in range(0, len(byte_data), 2):
        # Combine two bytes into one 16-bit number little-endian)
        sixteen_bit_num = (byte_data[i+1] << 8) | byte_data[i]
        data.append(sixteen_bit_num)

    xpoz = np.array(data[0::6])
    xneg = np.array(data[1::6])
    ypoz = np.array(data[2::6])
    yneg = np.array(data[3::6])
    zpoz = np.array(data[4::6])
    zneg = np.array(data[5::6])

    X = xpoz - xneg
    Y = ypoz - yneg
    Z = zpoz - zneg
    
    plt.plot(X, 'r')
    plt.plot(Y, 'g')
    plt.plot(Z, 'b')

    plt.axis([0, len(X), -4200, 4200])
    plt.draw()
    plt.pause(0.01)
    plt.clf()

