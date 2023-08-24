import iio
import matplotlib.pyplot as plt

ctxname="ip:10.76.84.153"
ctx = iio.Context(ctxname)
dev = ctx.find_device("ad5592r_s")

channels = []

for i in range(6):
    channels.append(dev.find_channel("voltage" + str(i)))
    
for ch in channels:    
    print(ch.attrs["raw"].value)



for i in range(0, 100):
        x = int(channels[0].attrs["raw"].value) - int(channels[1].attrs["raw"].value)
        print("x = ",x)
        y = int(channels[2].attrs["raw"].value) - int(channels[3].attrs["raw"].value)
        print("y = ",y)
        z = int(channels[4].attrs["raw"].value) - int(channels[5].attrs["raw"].value)
        print("z = ",z)
        plt.plot([x], [y], 'ro')
        plt.axis([-4096, 4096, -4096, 4096])
        plt.draw()
        plt.pause(0.05)
        plt.clf()
        

        
    
