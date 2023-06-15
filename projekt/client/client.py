import math
import sys
import socket
import matplotlib.pyplot as plt

if len(sys.argv) != 2:
    print(f"Usage {sys.argv[0]} <ip>")
    sys.exit(1)

ip = sys.argv[1]
port = 9090

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(b"START", (ip, port))

xs = []
ys = []

while True:
    try:
        data, addr = sock.recvfrom(512)
        data = data.decode()
        angle, distance = [int(x) for x in str(data).split(" ")]
        x = distance * math.cos(math.radians(angle))
        y = distance * math.sin(math.radians(angle))
        xs.append(x)
        ys.append(y)

        plt.clf()
        plt.plot(xs, ys)
        plt.xlim(-100, 100)
        plt.ylim(-100, 100)
        plt.pause(0.1)
    except KeyboardInterrupt:
        break

sock.sendto(b"STOP", (ip, port))
