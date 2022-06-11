using System;
using System.Collections.Generic;
using System.Text;
using Newtonsoft.Json;
using System.Collections;

namespace trivia_client.classes
{
    public struct RoomData
    {
        public uint id { get; set; }
        public String name { get; set; }
        public uint maxPlayers { get; set; }
        public uint numOfQuestionsInGame { get; set; }
        public uint timePerQuestion { get; set; }
        public uint isActive { get; set; }
    }

    public struct Statistics
    {
        public String name { get; set; }
        public int victories { get; set; }
        public int games { get; set; }
        public int avgTime { get; set; }

    }

    class User
    {
        public String username { get; set; }
        public bool isAdmin { get; set; }
    }

    class PlayerResultsForList
    {
        public String username { get; set; }
        public uint correctAnswerCount { get; set; }
        public uint averageAnswerTime { get; set; }
    }

    public struct PlayerResults
    {
        public String username;
        public uint correctAnswerCount;
        public uint wrongAnswerCount;
        public uint averageAnswerTime;
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
        public Statistics[] statistics;
    }

    struct GetPersonalStatsResponse
    {
        public uint status;
        public Statistics[] statistics;
    }

    struct JoinRoomResponse
    {
        public uint status;
    }

    struct CreateRoomResponse
    {
        public uint status;
    }

    struct CloseRoomResponse
    {
        public uint status;
    }

    struct StartGameResponse
    {
        public uint status;
    }

    struct GetRoomStateResponse
    {
        public uint status;
        public bool hasGameBegun;
        public String[] players;
        public uint questionCount;
        public uint answerTimeout;
        public bool isRoomClosed;
    }

    struct LeaveRoomResponse
    {
        public uint status;
    }

    struct LeaveGameResponse
    {
        public uint status;
    }

    struct GetQuestionResponse
    {
        public uint status;
        public String question;
        public Dictionary<uint, String> answers;
    }

    struct SubmitAnswerResponse
    {
        public uint status;
        public uint correctAnswerId;
    }

    struct GetGameResultsResponse
    {
        public uint status;
        public PlayerResults[] results;
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
        public const int CLOSE_ROOM = 10;
	    public const int START_GAME = 11;
	    public const int GET_ROOM_STATE = 12;
        public const int LEAVE_ROOM = 13;
        public const int GET_QUESTION = 14;
	    public const int SUBMIT_ANSWER = 15;
	    public const int GET_GAME_RESULTS = 16;
        public const int LEAVE_GAME = 17;

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
                
                if(json.IndexOf(goTo) != -1)
                    value = json.Substring(json.IndexOf(':') + 1, json.IndexOf(goTo) - json.IndexOf(':') - 1);
                else
                    value = json.Substring(json.IndexOf(':') + 1);

                if (goTo == ']')
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

            //add rooms
            String rooms = extractValue(bufferStr);
            Stack<RoomData> stack = new Stack<RoomData>();
            while (rooms.Length>0)
            {
                String roomStr = rooms.Substring(0, rooms.IndexOf('}')+1);
                int len = roomStr.Length;

                //get the current room data
                RoomData roomData = new RoomData() { };
                roomData.id = UInt32.Parse(extractValue(roomStr));
                roomStr = roomStr.Substring(roomStr.IndexOf(',') + 1);
                roomData.isActive = UInt32.Parse(extractValue(roomStr));
                roomStr = roomStr.Substring(roomStr.IndexOf(',') + 1);
                roomData.maxPlayers = UInt32.Parse(extractValue(roomStr));
                roomStr = roomStr.Substring(roomStr.IndexOf(',') + 1);
                roomData.name = extractValue(roomStr);
                roomStr = roomStr.Substring(roomStr.IndexOf(',') + 1);
                roomData.numOfQuestionsInGame = UInt32.Parse(extractValue(roomStr));
                roomStr = roomStr.Substring(roomStr.IndexOf(',') + 1);
                roomData.timePerQuestion = UInt32.Parse(extractValue(roomStr));
                stack.Push(roomData);

                if (rooms.Length > len)
                    rooms = rooms.Substring(len + 1);
                else
                    break;
            }
            r.rooms = stack.ToArray();

            bufferStr = bufferStr.Substring(bufferStr.IndexOf(']') + 2);
            r.status = UInt32.Parse(extractValue(bufferStr));

            return r;
        }

        public static GetPlayersInRoomResponse deserializeGetPlayersInRoomResponse(byte[] buffer)
        {
            GetPlayersInRoomResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);

            //add players
            String nameArrayStr = extractValue(bufferStr);
            Stack<String> namesStack = new Stack<String>();
            while (nameArrayStr.Length > 0)
            {
                String name;
                if (nameArrayStr.IndexOf(',') != -1)
                    name = nameArrayStr.Substring(0, nameArrayStr.IndexOf(','));
                else
                    name = nameArrayStr;
                namesStack.Push(name);

                if (nameArrayStr.IndexOf(',') != -1)
                    nameArrayStr = nameArrayStr.Substring(name.Length + 1);
                else
                    nameArrayStr = "";
            }
            r.players = namesStack.ToArray();
            bufferStr = bufferStr.Substring(bufferStr.IndexOf(']') + 2);
            return r;
        }

        public static GetHighScoreResponse deserializeGetHighScoreResponse(byte[] buffer)
        {
            GetHighScoreResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);

            //add statistics
            String statistics = extractValue(bufferStr);
            Stack<Statistics> stack = new Stack<Statistics>();
            while (statistics.Length > 0)
            {
                //get the current statistics
                Statistics currStatistic = new Statistics() { };
                String name = extractValue(statistics);
                currStatistic.name = name.Length >= 2 ? name : "\"\"";
                statistics = statistics.Substring(statistics.IndexOf(',') + 1);

                String games = extractValue(statistics);
                currStatistic.games = classes.Serializer.checkifNumber(games) ? Int32.Parse(games) : 0;
                statistics = statistics.Substring(statistics.IndexOf(',') + 1);

                String victories = extractValue(statistics);
                currStatistic.victories = classes.Serializer.checkifNumber(victories) ? Int32.Parse(victories) : 0;
                statistics = statistics.Substring(statistics.IndexOf(',') + 1);

                String avgTime = extractValue(statistics);
                currStatistic.avgTime = classes.Serializer.checkifNumber(avgTime) ? Int32.Parse(avgTime) : 0;
                if (statistics.IndexOf(',') != -1)
                    statistics = statistics.Substring(statistics.IndexOf(',') + 1);
                else
                    statistics = "";
                stack.Push(currStatistic);
            }
            r.statistics = stack.ToArray();

            bufferStr = bufferStr.Substring(bufferStr.IndexOf(']') + 2);
            r.status = UInt32.Parse(extractValue(bufferStr));

            return r;
        }

        public static GetPersonalStatsResponse deserializeGetPersonalStatsResponse(byte[] buffer)
        {
            GetPersonalStatsResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);

            //add statistics
            String statistics = extractValue(bufferStr);
            Stack<Statistics> stack = new Stack<Statistics>();
            while (statistics.Length > 0)
            {
                //get the current statistics
                Statistics currStatistic = new Statistics() { };
                String name = extractValue(statistics);
                currStatistic.name = name.Length>=2 ? name : "\"\"";
                statistics = statistics.Substring(statistics.IndexOf(',') + 1);

                String games = extractValue(statistics);
                currStatistic.games = classes.Serializer.checkifNumber(games) ? Int32.Parse(games):0;
                statistics = statistics.Substring(statistics.IndexOf(',') + 1);

                String victories = extractValue(statistics);
                currStatistic.victories = classes.Serializer.checkifNumber(victories) ? Int32.Parse(victories) : 0;
                statistics = statistics.Substring(statistics.IndexOf(',') + 1);

                String avgTime = extractValue(statistics);
                currStatistic.avgTime = classes.Serializer.checkifNumber(avgTime) ? Int32.Parse(avgTime) : 0;
                if (statistics.IndexOf(',') != -1)
                    statistics = statistics.Substring(statistics.IndexOf(',') + 1);
                else
                    statistics = "";
                stack.Push(currStatistic);
            }
            r.statistics = stack.ToArray();

            bufferStr = bufferStr.Substring(bufferStr.IndexOf(']') + 2);
            r.status = UInt32.Parse(extractValue(bufferStr));

            return r;
        }

        public static JoinRoomResponse deserializeJoinRoomResponse(byte[] buffer)
        {
            JoinRoomResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            if (bufferStr.Contains("status"))
                r.status = UInt32.Parse(extractValue(bufferStr, true));
            else
                r.status = ERROR_CODE;
            return r;
        }

        public static CreateRoomResponse deserializeCreateRoomResponse(byte[] buffer)
        {
            CreateRoomResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            r.status = UInt32.Parse(extractValue(bufferStr, true));
            return r;
        }

        public static CloseRoomResponse deserializeCloseRoomResponse(byte[] buffer)
        {
            CloseRoomResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            r.status = bufferStr.Contains("status") ? UInt32.Parse(extractValue(bufferStr)) : ERROR_CODE;
            return r;
        }

        public static StartGameResponse deserializeStartGameResponse(byte[] buffer)
        {
            StartGameResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            r.status = bufferStr.Contains("status") ? UInt32.Parse(extractValue(bufferStr)) : ERROR_CODE;
            return r;
        }

        public static GetRoomStateResponse deserializeGetRoomStateResponse(byte[] buffer)
        {
            GetRoomStateResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);

            r.answerTimeout = UInt32.Parse(extractValue(bufferStr));
            bufferStr = bufferStr.Substring(bufferStr.IndexOf(',') + 1);

            r.hasGameBegun = extractValue(bufferStr) == "true";
            bufferStr = bufferStr.Substring(bufferStr.IndexOf(',') + 1);

            r.isRoomClosed = extractValue(bufferStr) == "true";
            bufferStr = bufferStr.Substring(bufferStr.IndexOf(',') + 1);

            //add players
            String nameArrayStr = extractValue(bufferStr);
            Stack<String> namesStack = new Stack<String>();
            while (nameArrayStr.Length>0)
            {
                String name;
                if (nameArrayStr.IndexOf(',') != -1)
                    name = nameArrayStr.Substring(0, nameArrayStr.IndexOf(','));
                else
                    name = nameArrayStr;
                namesStack.Push(name);

                if (nameArrayStr.IndexOf(',') != -1)
                    nameArrayStr = nameArrayStr.Substring(name.Length + 1);
                else
                    nameArrayStr = "";
            }
            r.players = namesStack.ToArray();
            bufferStr = bufferStr.Substring(bufferStr.IndexOf(']') + 2);

            r.questionCount = UInt32.Parse(extractValue(bufferStr));
            bufferStr = bufferStr.Substring(bufferStr.IndexOf(',') + 1);

            r.status = UInt32.Parse(extractValue(bufferStr));
            return r;
        }

        public static LeaveRoomResponse deserializeLeaveRoomResponse(byte[] buffer)
        {
            LeaveRoomResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            r.status = bufferStr.Contains("status") ? UInt32.Parse(extractValue(bufferStr)) : ERROR_CODE;
            return r;
        }

        public static LeaveGameResponse deserializeLeaveGameResponse(byte[] buffer) 
        {
            LeaveGameResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            r.status = bufferStr.Contains("status") ? UInt32.Parse(extractValue(bufferStr)) : ERROR_CODE;
            return r;
        }

        public static GetQuestionResponse deserializeGetQuestionResponse(byte[] buffer)
        {
            GetQuestionResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);

            //add answers
            Dictionary<uint, String> map = new Dictionary<uint, String>();
            bufferStr = bufferStr.Substring(bufferStr.IndexOf('[')+1);
            while (bufferStr.IndexOf(']') != -1)
            {
                String answer = bufferStr.Substring(1, bufferStr.IndexOf(']')-1);
                uint correctAnswerId = UInt32.Parse(answer.Substring(0, answer.IndexOf(',')));
                String question = answer.Substring(answer.IndexOf(',') + 2, answer.Length - answer.IndexOf(',') - 3);
                map.Add(correctAnswerId, question);
                bufferStr = bufferStr.Substring(bufferStr.IndexOf(']') + 2);
            }
            r.answers = map;
            bufferStr = bufferStr.Substring(bufferStr.IndexOf(',') + 1);

            r.question = extractValue(bufferStr);
            bufferStr = bufferStr.Substring(bufferStr.IndexOf(',') + 1);

            r.status = bufferStr.Contains("status") ? UInt32.Parse(extractValue(bufferStr)) : ERROR_CODE;
            return r;
        }

        public static SubmitAnswerResponse deserializeSubmitAnswerResponse(byte[] buffer)
        {
            SubmitAnswerResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);
            r.correctAnswerId = UInt32.Parse(extractValue(bufferStr));
            bufferStr = bufferStr.Substring(bufferStr.IndexOf(',') + 1);
            r.status = bufferStr.Contains("status") ? UInt32.Parse(extractValue(bufferStr)) : ERROR_CODE;
            return r;
        }

        public static GetGameResultsResponse deserializeGetGameResultsResponse(byte[] buffer)
        {
            GetGameResultsResponse r;
            String bufferStr = Encoding.UTF8.GetString(buffer);

            //add statistics
            String results = extractValue(bufferStr);
            Stack<PlayerResults> stack = new Stack<PlayerResults>();
            while (results.Length > 0)
            {
                //get the current statistics
                PlayerResults currrResults;

                String averageAnswerTime = extractValue(results);
                currrResults.averageAnswerTime = classes.Serializer.checkifNumber(averageAnswerTime) ? UInt32.Parse(averageAnswerTime) : 0;
                results = results.Substring(results.IndexOf(',') + 1);

                String correctAnswerCount = extractValue(results);
                currrResults.correctAnswerCount = classes.Serializer.checkifNumber(correctAnswerCount) ? UInt32.Parse(correctAnswerCount) : 0;
                results = results.Substring(results.IndexOf(',') + 1);

                String name = extractValue(results);
                currrResults.username = name.Length >= 2 ? name : "\"\"";
                results = results.Substring(results.IndexOf(',') + 1);

                String wrongAnswerCount = extractValue(results);
                currrResults.wrongAnswerCount = classes.Serializer.checkifNumber(wrongAnswerCount) ? UInt32.Parse(wrongAnswerCount) : 0;

                if (results.IndexOf(',') != -1)
                    results = results.Substring(results.IndexOf(',') + 1);
                else
                    results = "";
                stack.Push(currrResults);
            }
            r.results = stack.ToArray();

            bufferStr = bufferStr.Substring(bufferStr.IndexOf(']') + 2);
            r.status = bufferStr.Contains("status") ? UInt32.Parse(extractValue(bufferStr)) : ERROR_CODE;
            return r;
        }

    }
}
