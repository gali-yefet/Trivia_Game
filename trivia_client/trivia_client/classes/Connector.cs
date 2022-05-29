﻿using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Net;


namespace trivia_client
{
    public class Connector
    {
        public const int PORT = 3086;
        public const String IP = "127.0.0.1";

        private TcpClient _client;
        private NetworkStream _clientStream;

        //connect to server
        public Connector()
        {
            _client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(IP), PORT);
            _client.Connect(serverEndPoint);
            _clientStream = _client.GetStream();
        }

        public byte[] readData()
        {
            //get code
            byte[] code = new byte[2];
            _clientStream.Read(code, 0, 2);

            //get length
            byte[] len_byte = new byte[4];
            _clientStream.Read(len_byte, 0, 4);
            string s = Encoding.UTF8.GetString(len_byte);
            if (s.Contains("{") && s.Length >= 2)
                s = s.Substring(0, s.Length - 2);

            int len = Int32.Parse(s);

            //get data
            byte[] buffer = new byte[len];
            _clientStream.Read(buffer, 0, len);
            return buffer;
        }

        public void sendData(byte[] msg)
        {
            string s = System.Text.Encoding.UTF8.GetString(msg);
            _clientStream.Write(msg, 0, s.Length);
            _clientStream.FlushAsync();
        }

        public byte[] sendGetData(byte[] msg)
        {
            sendData(msg);
            return readData();
        }
    }
}
