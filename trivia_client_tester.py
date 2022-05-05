import json
import socket
SERVER_IP = '127.0.0.1'
SERVER_PORT = 3086
ERROR_CODE = 0
SIGN_CODE = 1
LOGIN_CODE = 2
CREATE_ROOM = 3
GET_ROOMS = 4
GET_PLAYERS_IN_ROOM = 5
JOIN_ROOM = 6
GET_STATISTICS = 7
LOGOUT = 8

SIZE_OF_LEN = 4

#create a socket according to ip and port
def create_socket(ip, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (ip, port)
    sock.connect(server_address)
    return sock

#create buffer according to protocol
def create_buffer(code, dictionary):
    json_str = json.dumps(dictionary)
    json_len = str(len(json_str))#mabey it wouldn't be here 4 bytes...
    json_len_str = "0"*(SIZE_OF_LEN - len(json_len)) + json_len
    buffer = str(code) + json_len_str +json_str
    return buffer

#send msg and get the response from the server
def send_msg(code, sock, dict):
    #send
    msg = create_buffer(code, dict)
    sock.send(msg.encode())
    #recv
    sock.recv(1).decode()
    len = int(sock.recv(SIZE_OF_LEN).decode())
    server_msg = sock.recv(len).decode()
    return server_msg



def main():
    print("start")
    sock1 = create_socket(SERVER_IP, SERVER_PORT)
    sock2 = create_socket(SERVER_IP, SERVER_PORT)

    print("sign user 1:", send_msg(SIGN_CODE, sock1, {"username": "user1", "password": "111", "email": "1@gmail.com"}))
    print("sign user 2:", send_msg(SIGN_CODE, sock2, {"username": "user2", "password": "22222222", "email": "2@gmail.com"}))
    print("user1 create room1:", send_msg(CREATE_ROOM, sock1, {"roomName": "room1", "maxUsers":"3", "questionsCount": "5", "answerTimeout": "30"}))
    print("user2 join roomId 0:", send_msg(JOIN_ROOM, sock2, {"roomID": "0"}))


if __name__ == "__main__":
    main()