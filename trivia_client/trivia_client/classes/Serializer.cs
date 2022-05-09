using System;
using System.Collections.Generic;
using System.Text;
using Newtonsoft.Json;

namespace trivia_client.classes
{

    struct LoginRequest
    {
        String username;
        String password;
    }

    struct SignupRequest
    {
        String username;
        String password;
        String email;
    }

    struct GetPlayersInROmmRequest
    {
        uint roomId;
    }

    struct JoinRoomRequest
    {
        uint roomId;
    }

    struct CreateRoomRequest
    {
        String roomName;
        uint maxUsers;
        uint questionsCount;
        uint answerTimeOut;
    }

    class Serializer
    {
        /*
         * serilize a request
         * in: request code, msg
         * out: request in byte[]
         */
        private static byte[] serializeRequest(int code, String msg)
        {
            int len = msg.Length;
            String allMsg = code.ToString() + len.ToString() + msg;
            byte[] buffer = new ASCIIEncoding().GetBytes(allMsg);
            return buffer;
        }

        public static byte[] serializeLoginRequest(LoginRequest r)
        {
            String json = JsonConvert.SerializeObject(r);
            return serializeRequest(Deserializer.LOGIN_CODE, json);
        }

        public static byte[] serializeSignupRequest(SignupRequest r)
        {
            String json = JsonConvert.SerializeObject(r);
            return serializeRequest(Deserializer.SIGNUP_CODE, json);
        }

        public static byte[] serializeGetPlayersInRoomRequest(GetPlayersInROmmRequest r)
        {
            String json = JsonConvert.SerializeObject(r);
            return serializeRequest(Deserializer.GET_PLAYERS_IN_ROOM_CODE, json);
        }

        public static byte[] serializeJoinRoomRequest(JoinRoomRequest r)
        {
            String json = JsonConvert.SerializeObject(r);
            return serializeRequest(Deserializer.JOIN_ROOM_CODE, json);
        }

        public static byte[] serializeCreateRoomRequest(CreateRoomRequest r)
        {
            String json = JsonConvert.SerializeObject(r);
            return serializeRequest(Deserializer.CREATE_ROOM_CODE, json);
        }
    }
}
