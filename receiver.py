import socket
import struct

multicast_group = '224.0.0.1'
server_address = ('', 2390)

# Create the socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind to the server address
sock.bind(server_address)

# Tell the operating system to add the socket to the multicast group
# on all interfaces.
group = socket.inet_aton(multicast_group)
mreq = struct.pack('4sL', group, socket.INADDR_ANY)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

print(f"Listening for multicast messages on {multicast_group}:{server_address[1]}...")

while True:
    data, address = sock.recvfrom(1024)
    print(f"Received {len(data)} bytes from {address}: {data.decode('utf-8', errors='ignore')}")
