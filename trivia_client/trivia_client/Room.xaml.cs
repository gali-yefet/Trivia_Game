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
    public partial class RoomUsers : Page
    {
        Connector _connector;

        public RoomUsers(Connector connector, bool isAdmin)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;

            if(isAdmin)
            {
                closeRoomButton.Visibility = Visibility.Visible;
                startGameButton.Visibility = Visibility.Visible;
            }
            else
            {
                leaveRoomButton.Visibility = Visibility.Visible;
            }
        }

        private void leaveRoomButton_Click(object sender, RoutedEventArgs e)
        {
            //TODO
        }

        private void closeRoomButton_Click(object sender, RoutedEventArgs e)
        {
            //TODO
        }

        private void startGameButton_Click(object sender, RoutedEventArgs e)
        {
            //TODO
        }
    }
}
