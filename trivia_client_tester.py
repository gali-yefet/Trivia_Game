import socket
SERVER_IP = '127.0.0.1'
SERVER_PORT = 3086

print("start")
#create socket and connect to the server
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = (SERVER_IP, SERVER_PORT)
sock.connect(server_address)

<<<<<<< HEAD
sock.send(createLoginMessage().encode())
server_msg = sock.recv(10).decode()
print(server_msg)


def createLoginMessage():
    request = "668{ username: gali, password: 1234 }";
    return request

def createSignUpMessage():
    request = "6126{ username: gali, password: 1234, email: gali.yefet@gmail.com }";
    return request
=======
server_msg = sock.recv(5).decode()
if server_msg == "Hello":
    print(server_msg)
    sock.send("Hello".encode())
>>>>>>> 5060f6ee31128b8355c8d61e7e55d48b17568996
