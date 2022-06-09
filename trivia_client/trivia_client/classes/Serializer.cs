using System;
using System.Collections.Generic;
using System.Text;
using Newtonsoft.Json;

namespace trivia_client.classes
{

    struct LoginRequest
    {
        public String username;
        public String password;
    }

    struct SignupRequest
    {
        public String username;
        public String password;
        public String email;
    }

    struct GetPlayersInRoomRequest
    {
        public uint roomId;
    }

    struct JoinRoomRequest
    {
        public uint roomId;
    }

    struct CreateRoomRequest
    {
        public String roomName;
        public uint maxUsers;
        public uint questionsCount;
        public uint answerTimeOut;
    }

    struct SubmitAnswerRequest
    {
        public uint answerId;
    }

    class Serializer
    {
 

        //check if a string is only digits
        public static bool checkifNumber(String str)
        {
            foreach (char c in str)
            {
                if (c < '0' || c > '9')
                    return false;
            }
            return true;
        }

        /*
        * serilize a request
        * in: request code, msg
        * out: request in byte[]
        */
        public static byte[] serializeRequest(int code, String msg = "")
        {
            String codeStr = code.ToString();
            while (codeStr.Length < 2)
                codeStr = " "+codeStr;

            String len = msg.Length.ToString();
            while (len.Length < 4)
                len = " "+len;

            String allMsg = codeStr + len + msg;
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

        public static byte[] serializeGetPlayersInRoomRequest(GetPlayersInRoomRequest r)
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

        public static byte[] serializeSubmitAnswerRequest(SubmitAnswerRequest r)
        {
            String json = JsonConvert.SerializeObject(r);
            return serializeRequest(Deserializer.SUBMIT_ANSWER, json);
        }
    }
}
