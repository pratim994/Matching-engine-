import socket 


target_host = "127.1.1.1"

target_port = 9979


client = socket.socket(socket.AF_INET , socket.SOCK_DGRAM)

client.sendTo(b"AAABBBCCC", (target_host, target_port))

data, addr = client.recvfrom(4096)

print(data.decode())

client.close()
