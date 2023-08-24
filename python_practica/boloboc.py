import iio
import matplotlib.pyplot as plt

URI="ip:10.76.84.210"
ctx = iio.Context(URI)

dev = ctx.find_device("ad5592r_s")


channels = []
for i in range(6):
    channels.append(dev.find_channel(f"voltage{i}"))

while True:
    chn_raws = [int(chn.attrs['raw'].value ) for chn in channels]
    X = chn_raws[0] - chn_raws[1] 
    Y = chn_raws[2] - chn_raws[3]

    plt.plot([X], [Y], 'ro')

    plt.axis([-4096, 4096, -4096, 4096])
    plt.draw()
    plt.pause(0.01)
    plt.clf()