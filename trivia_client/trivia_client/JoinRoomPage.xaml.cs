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

    public partial class JoinRoomPage : Page
    {
        Connector _connector;
        List<classes.RoomData> _rooms;
        
        public JoinRoomPage(Connector connector)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;
            _rooms = getActiveRoomsFromServer();

            //show rooms names
            ConectedUsers.Items.Clear();
            ConectedUsers.ItemsSource = _rooms;
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
                var RoomName = item.Content;
                //TODO:Join the room by id
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
