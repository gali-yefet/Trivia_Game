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
        public JoinRoomPage(Connector connector)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;

            //TODO:
            //--> get data from database and put it in the list
            //ServiceReference1.ImojWCFServiceClient client = new ServiceReference1.ImojWCFServiceClient();
            //listView1.Items.Clear();
            //var userList = client.getUsers();
            //listView1.ItemsSource = userList;//TODO

            ConectedUsers.Items.Clear();
            byte[] res = _connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.GET_ROOMS_CODE));
            classes.GetRoomsResponse r = classes.Deserializer.deserializeGetRoomsResponse(res);
            ConectedUsers.ItemsSource = r.rooms;

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

    }
}
