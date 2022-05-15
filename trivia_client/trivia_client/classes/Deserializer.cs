using System;
using System.Collections.Generic;
using System.Text;
using Newtonsoft.Json;
using System.Collections;

namespace trivia_client.classes
{
    struct RoomData
    {
        public uint id;
        public String name;
        public uint maxPlayers;
        public uint numOfQuestionsInGame;
        public uint timePerQuestion;
        public uint isActive;
    }

    struct LoginResponse
    {
        public uint status;
    }

    struct SignupResponse
    {
        public uint status;
    }

    struct LogoutResponse
    {
        public uint status;
    }

    struct GetRoomsResponse
    {
        public uint status;
        public RoomData[] rooms;
    }

    struct GetPlayersInRoomResponse
    {
        public String[] players;
    }

    struct GetHighScoreResponse
    {
        public uint status;
        public String[] statistics;
    }

    struct GetPersonalStatsResponse
    {
        public uint status;
        public String[] statistics;
    }

    struct JoinRoomResponse
    {
        public uint status;
    }

    struct CreateRoomResponse
    {
        public uint status;
    }

    class Deserializer
    {
        //define codes
        public const int ERROR_CODE = 0;
        public const int SIGNUP_CODE = 1;
        public const int LOGIN_CODE = 2;
        public const int LOGOUT_CODE = 3;
        public const int CREATE_ROOM_CODE = 4;
        public const int GET_ROOMS_CODE = 5;
        public const int GET_PLAYERS_IN_ROOM_CODE = 6;
        public const int JOIN_ROOM_CODE = 7;
        public const int GET_HIGH_SCORE_CODE = 8;
        public const int GET_PERSONAL_STATS_CODE = 9;

        private static string extractValue(String json, bool eraseSides = false)
        {
            String value = "";
            if (json.IndexOf(':') != -1)
            {
                //check where is the end of this value
                char goTo;
                if (json.IndexOf('[') == json.IndexOf(':') + 1)
                    goTo = ']';
                else
                    goTo = (json.IndexOf(',') != -1) ? ',' : '}';

                value = json.Substring(json.IndexOf(':') + 1, json.IndexOf(goTo) - json.IndexOf(':') - 1);

                if(goTo == ']')
                    value = value.Substring(1, value.Length - 1);

                //erase spaces
                if (value.Length > 0)
                {
                    while (value[0] == ' ')
                        value = value.Substring(1, value.Length - 1);
                    while (value[value.Length - 1] == ' ')
                        value = value.Substring(1, value.Length - 1);
                }
                
            }
            //erace " in order to get an int
            if (eraseSides && value.Length > 2)
                value = value.Substring(1, value.Length - 2);

            return value;
        }

        public static LoginResponse deserializeLoginResponse(byte[] buffer)
        {
            LoginResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            r.status = bufferStr.Contains("status") ? UInt32.Parse(extractValue(bufferStr)) : ERROR_CODE;
            return r;
        }

        public static SignupResponse deserializeSignupResponse(byte[] buffer)
        {
            SignupResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            r.status = bufferStr.Contains("status") ? UInt32.Parse(extractValue(bufferStr)) : ERROR_CODE;
            return r;
        }

        public static LogoutResponse deserializeLogoutResponse(byte[] buffer)
        {
            LogoutResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            r.status = bufferStr.Contains("status") ? UInt32.Parse(extractValue(bufferStr)) : ERROR_CODE;
            return r;
        }

        public static GetRoomsResponse deserializeGetRoomsResponse(byte[] buffer)
        {
            GetRoomsResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            r.status = UInt32.Parse(extractValue(bufferStr, true));
            bufferStr = bufferStr.Substring(0, bufferStr.IndexOf(',') + 1);

            //add rooms
            bufferStr = extractValue(bufferStr, true);
            Stack<RoomData> stack = new Stack<RoomData>();
            while (bufferStr.IndexOf('"') != -1)
            {
                String roomStr = bufferStr.Substring(0, bufferStr.IndexOf(','));
                int len = roomStr.Length;

                //get the current room data
                RoomData roomData;
                roomData.name = extractValue(roomStr);
                roomStr = roomStr.Substring(0, roomStr.IndexOf(',') + 1);
                roomData.id = UInt32.Parse(extractValue(roomStr, true));
                roomStr = roomStr.Substring(0, roomStr.IndexOf(',') + 1);
                roomData.isActive = UInt32.Parse(extractValue(roomStr, true));
                roomStr = roomStr.Substring(0, roomStr.IndexOf(',') + 1);
                roomData.maxPlayers = UInt32.Parse(extractValue(roomStr, true));
                roomStr = roomStr.Substring(0, roomStr.IndexOf(',') + 1);
                roomData.numOfQuestionsInGame = UInt32.Parse(extractValue(roomStr, true));
                roomStr = roomStr.Substring(0, roomStr.IndexOf(',') + 1);
                roomData.timePerQuestion = UInt32.Parse(extractValue(roomStr, true));

                stack.Push(roomData);
                bufferStr = bufferStr.Substring(len + 1);
            }
            r.rooms = stack.ToArray();
            return r;
        }

        public static GetPlayersInRoomResponse deserializeGetPlayersInRoomResponse(byte[] buffer)
        {
            GetPlayersInRoomResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);

            //add players
            String nameArrayStr = extractValue(bufferStr, true);
            Stack<String> namesStack = new Stack<String>();
            while (nameArrayStr.IndexOf('"') != -1)
            {
                String name = nameArrayStr.Substring(0, nameArrayStr.IndexOf(','));
                namesStack.Push(name);
                nameArrayStr = nameArrayStr.Substring(name.Length + 1);
            }
            r.players = namesStack.ToArray();
            return r;
        }

        public static GetHighScoreResponse deserializeGetHighScoreResponse(byte[] buffer)
        {
            GetHighScoreResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);

            //add statistics
            String statistics = extractValue(bufferStr, true);
            Stack<String> stack = new Stack<String>();
            while (statistics.IndexOf('"') != -1)
            {
                String name = statistics.Substring(statistics.IndexOf(','));
                stack.Push(name);
                statistics = statistics.Substring(name.Length + 1);
            }
            r.statistics = stack.ToArray();

            bufferStr = bufferStr.Substring(bufferStr.IndexOf(']') + 2);
            r.status = UInt32.Parse(extractValue(bufferStr, true));

            return r;
        }

        public static GetPersonalStatsResponse deserializeGetPersonalStatsResponse(byte[] buffer)
        {
            GetPersonalStatsResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);

            //add statistics
            String statistics = extractValue(bufferStr, true);
            Stack<String> stack = new Stack<String>();
            while (statistics.IndexOf('"') != -1)
            {
                String name = statistics.Substring(statistics.IndexOf(','));
                stack.Push(name);
                statistics = statistics.Substring(name.Length + 1);
            }
            r.statistics = stack.ToArray();

            bufferStr = bufferStr.Substring(bufferStr.IndexOf(']') + 2);
            r.status = UInt32.Parse(extractValue(bufferStr, true));

            return r;
        }

        public static JoinRoomResponse deserializeJoinRoomResponse(byte[] buffer)
        {
            JoinRoomResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            r.status = UInt32.Parse(extractValue(bufferStr, true));
            return r;
        }

        public static CreateRoomResponse deserializeCreateRoomResponse(byte[] buffer)
        {
            CreateRoomResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            r.status = UInt32.Parse(extractValue(bufferStr, true));
            return r;
        }

    }
}
