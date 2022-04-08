import socket
SERVER_IP = '127.0.0.1'
SERVER_PORT = 3086

print("start")
#create socket and connect to the server
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = (SERVER_IP, SERVER_PORT)
sock.connect(server_address)

server_msg = sock.recv(5).decode()
if server_msg == "Hello":
    print(server_msg)
    sock.send("Hello".encode())