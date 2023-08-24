import iio

ctxname = "ip:10.76.84.240"
nb_channels = 6
channel_prefix = "voltage"

class axis:
    x, y, z = 0, 0, 0

def getRaw(channel):
    return int(channel.attrs["raw"].value)

# Get context and device
ctx = iio.Context(ctxname)
dev = ctx.find_device("ad5592r_s")

channels = []
for i in range(6):
# Get all channels
    channels.append(dev.find_channel("{}{}".format(channel_prefix, i)))


while True:
    x = getRaw(channels[0]) - getRaw(channels[1])
    y = getRaw(channels[2]) - getRaw(channels[3])
    z = getRaw(channels[4]) - getRaw(channels[5])
    print("x: {}, y: {}, z: {}".format(x, y, z))
    



# for dev in ctx.devices:
#     if dev.channels:
#         for chan in dev.channels:
#             print("{} - {} - {}".format(ctxname, dev.name, chan._id))
#     else:
#         print("{} - {}".format(ctxname, dev.name))
