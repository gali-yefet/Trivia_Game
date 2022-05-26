﻿using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Threading;

namespace trivia_client
{
    /// <summary>
    /// Interaction logic for RoomUsers.xaml
    /// </summary>
    /// 

    class User
    {
        public String username { get; set; }
        public bool isAdmin { get; set; }
    }

    public partial class RoomUsers : Page
    {
        Connector _connector;
        List<User> _users;
        bool _isAdmin;
        public RoomUsers(Connector connector, bool isAdmin)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;
            _isAdmin = isAdmin;
            display();
            createThread();
        }

        public void display()
        {
            _users = getUsersFromServer();

            if (_isAdmin)
            {
                closeRoomButton.Visibility = Visibility.Visible;
                startGameButton.Visibility = Visibility.Visible;
            }
            else
            {
                leaveRoomButton.Visibility = Visibility.Visible;
            }

            //show users list
            ConectedUsers.Items.Clear();
            ConectedUsers.ItemsSource = _users;        
        }

        public void update()
        {
            while(true)
            {
                display();
                Thread.Sleep(3000); //will sleep for 3 sec
            }
        }
        public void createThread()
        {
            // Create a secondary thread by passing a ThreadStart delegate  
            Thread updateThread = new Thread(new ThreadStart(update));
            // Start secondary thread  
            updateThread.Start();
            updateThread.Abort(); //detach thread
        }
        private void leaveRoomButton_Click(object sender, RoutedEventArgs e)
        {
            byte[] msg = classes.Serializer.serializeRequest(classes.Deserializer.LEAVE_ROOM);
            byte[] res = _connector.sendGetData(msg);
            classes.LeaveRoomResponse response = classes.Deserializer.deserializeLeaveRoomResponse(res);

            //check if login failed and move to page accordingly
            if (response.status == classes.Deserializer.LEAVE_ROOM)
            {
                Menu page = new Menu(_connector);
                NavigationService.Navigate(page);
            }
            else
            {
                //TODO: show an error
            }
        }

        private void closeRoomButton_Click(object sender, RoutedEventArgs e)
        {
            byte[] res = _connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.CLOSE_ROOM));
            classes.CloseRoomResponse response = classes.Deserializer.deserializeCloseRoomResponse(res);

            //check if login failed and move to page accordingly
            if (response.status == classes.Deserializer.CLOSE_ROOM)
            {
                Menu page = new Menu(_connector);
                NavigationService.Navigate(page);
            }
            else
            {
                //TODO: show an error
            }
        }

        private void startGameButton_Click(object sender, RoutedEventArgs e)
        {
            byte[] res = _connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.START_GAME));
            classes.StartGameResponse response = classes.Deserializer.deserializeStartGameResponse(res);

            //check if login failed and move to page accordingly
            if (response.status == classes.Deserializer.START_GAME)
            {
         //       GamePage page = new GamePage(_connector);
          //      NavigationService.Navigate(page);
            }
            else
            {
                //TODO: show an error
            }
        }

        private List<User> getUsersFromServer()
        {
            byte[] res = _connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.GET_ROOM_STATE));
            classes.GetRoomStateResponse r = classes.Deserializer.deserializeGetRoomStateResponse(res);
            List<User> users = new List<User>();
            for (int i = 0; i < r.players.Length; i++)
            {
                users.Add(new User()
                {
                    username = r.players[i].Substring(1, r.players[i].Length - 2),
                    isAdmin = i == r.players.Length - 1
                });
            }
            return users;
        }
    }
}
