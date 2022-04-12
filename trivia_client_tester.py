import socket
SERVER_IP = '127.0.0.1'
SERVER_PORT = 3086

def createLoginMessage():
    request = "634  { username: gali, password: 1234 }";
    return request

def createSignUpMessage():
    request = "663  { username: gali, password: 1234, email: gali.yefet@gmail.com }";
    return request

def main():
    print("start")
    #create socket and connect to the server
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)

    sock.send(createLoginMessage().encode())
    server_msg = sock.recv(34).decode()
    print(server_msg)

if __name__ == "__main__":
    main()
