import socket


target_host = "google.com"

target_port = 80


client  = socekt.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect((target_host, target_port))

client.send(b"GET /HTTP/1.1\r\nhost: google.com\r\n\r\n")

response = client.recv(4096)

print(repsonse.decode())

client.close()

#the AF_INET indicates that we will be using a ipv4 address SOCK_STREAM indicates it will be a tcp client 
