using System;
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

namespace trivia_client
{
    /// <summary>
    /// Interaction logic for RoomUsers.xaml
    /// </summary>
    ///

    public partial class RoomUsers : Page
    {
        Connector _connector;
        List<classes.User> _users;

        public RoomUsers(Connector connector, bool isAdmin)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;
            _users = getUsersFromServer();

            if (isAdmin)
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
                GamePage page = new GamePage(_connector);
                NavigationService.Navigate(page);
            }
            else
            {
                //TODO: show an error
            }
        }

        private List<classes.User> getUsersFromServer()
        {
            byte[] res = _connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.GET_ROOM_STATE));
            classes.GetRoomStateResponse r = classes.Deserializer.deserializeGetRoomStateResponse(res);
            List<classes.User> users = new List<classes.User>();
            for(int i = 0; i< r.players.Length; i++)
            {
                users.Add(new classes.User()
                {
                    username = r.players[i].Substring(1, r.players[i].Length - 2),
                    isAdmin = i == r.players.Length - 1
                }) ;
            }
            return users;
        }
    }
}
