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
    /// Interaction logic for JoinRoomPage.xaml
    /// </summary>
    class Room
    {
        public String name { get; set; }
        public int maxPlayers { get; set; }
    }

    public partial class JoinRoomPage : Page
    {
        Connector _connector;
        List<classes.RoomData> _rooms;
        
        public JoinRoomPage(Connector connector, bool firstTime = true)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;
            _rooms = getActiveRoomsFromServer();

            if(_rooms.Count == 0)
            {
                Error_noRooms.Visibility = Visibility.Visible;
                ConectedUsers.Visibility = Visibility.Hidden;
            }
            else
            {
                //show rooms names
                ConectedUsers.Items.Clear();
                ConectedUsers.ItemsSource = _rooms;

                if (!firstTime)
                    Error_joinFaild.Visibility = Visibility.Visible;
            }
            
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            Menu page = new Menu(_connector);
            NavigationService.Navigate(page);
        }

        private void ListViewItem_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            var item = sender as ListViewItem;
            if (item != null && item.IsSelected)
            {
                //find the right id
                classes.JoinRoomRequest r;
                r.roomId = 0;
                var room = (classes.RoomData)ConectedUsers.SelectedItems[0];
                foreach (var curr in _rooms)
                {
                    if (curr.name == room.name)
                    {
                        r.roomId = curr.id;
                        break;
                    }
                }

                //send the request to the server
                byte[] msg = classes.Serializer.serializeJoinRoomRequest(r);
                msg = _connector.sendGetData(msg);
                classes.JoinRoomResponse response = classes.Deserializer.deserializeJoinRoomResponse(msg);

                //check if joining failed and move to page accordingly
                if (response.status != classes.Deserializer.JOIN_ROOM_CODE)
                {
                    JoinRoomPage page = new JoinRoomPage(_connector, false);
                    NavigationService.Navigate(page);
                }
                else
                {
                    RoomUsers page = new RoomUsers(_connector, false);
                    NavigationService.Navigate(page);
                }
            }
        }

        private List<classes.RoomData> getActiveRoomsFromServer()
        {
            byte[] res = _connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.GET_ROOMS_CODE));
            classes.GetRoomsResponse r = classes.Deserializer.deserializeGetRoomsResponse(res);
            List<classes.RoomData> rooms = new List<classes.RoomData>();
            foreach(classes.RoomData room in r.rooms)
            {
                if(room.isActive==1)
                {
                    rooms.Add(new classes.RoomData()
                    {
                        id = room.id,
                        isActive = room.id,
                        maxPlayers = room.maxPlayers,
                        name = room.name.Substring(1, room.name.Length - 2),
                        numOfQuestionsInGame = room.numOfQuestionsInGame,
                        timePerQuestion = room.timePerQuestion
                    });
                }
            }
            return rooms;
        }

    }
}
