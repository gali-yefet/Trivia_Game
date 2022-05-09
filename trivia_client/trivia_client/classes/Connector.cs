using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Net;


namespace trivia_client
{
    class Connector
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

        private byte[] readData()
        {
            //get code
            byte[] code = new byte[1];
            _clientStream.Read(code, 0, 1);

            //get length
            byte[] len_byte = new byte[4];
            _clientStream.Read(code, 0, 4);
            int len = BitConverter.ToInt32(len_byte);

            //get data
            byte[] buffer = new byte[len];
            _clientStream.Read(buffer, 0, len);
            return buffer;
        }

        private void sendData(String msg)
        {
            byte[] buffer = new ASCIIEncoding().GetBytes(msg);
            _clientStream.Write(buffer, 0, buffer.Length);
            _clientStream.Flush();
        }

        public byte[] sendGetData(String msg)
        {
            sendData(msg);
            return readData();
        }


    }
}
