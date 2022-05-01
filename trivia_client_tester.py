import json
import socket
SERVER_IP = '127.0.0.1'
SERVER_PORT = 3086
SIGN_CODE = 5
LOGIN_CODE = 6

SIZE_OF_LEN = 4

#create a socket according to ip and port
def create_socket(ip, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (ip, port)
    sock.connect(server_address)
    return sock

#send msg and get the response from the server
def send_msg(msg, sock):
    sock.send(msg.encode())
    sock.recv(1).decode()
    len = int(sock.recv(SIZE_OF_LEN).decode())
    server_msg = sock.recv(len).decode()
    return server_msg

#create buffer according to protocol
def create_buffer(code, dictionary):
    json_str = json.dumps(dictionary)
    json_len = str(len(json_str))#mabey it wouldn't be here 4 bytes...
    json_len_str = "0"*(SIZE_OF_LEN - len(json_len)) + json_len
    buffer = str(code) + json_len_str +json_str
    return buffer

#send a login msg according to name and passworrd
def login(name, password, sock):
    dict = {"name": name, "password":password}
    buffer = create_buffer(LOGIN_CODE, dict)
    return send_msg(buffer, sock)

#send a signup msg according to name, password and email
def signup(name, password, email, sock):
    dict = {"name": name, "password":password, "email": email}
    buffer = create_buffer(SIGN_CODE, dict)
    return send_msg(buffer, sock)



def main():
    print("start")
    sock = create_socket(SERVER_IP, SERVER_PORT)

    #seposed to work
    print("signup (work): " + signup("n1", "111", "1@gmail.com", sock))
    #print("login (work): " + login("n1", "111", sock))

    print("login (fail, cant login to a loged in user): " + login("n1", "111", sock))
    print("signup (fail, can't signup with the same name): " + signup("n1", "111", "1@gmail.com", sock))

    print("signup (?): " + signup("n2", "222", "2@gmail.com", sock))


if __name__ == "__main__":
    main()