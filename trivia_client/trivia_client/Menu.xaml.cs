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
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : Page
    {
        Connector _connector;
        public Menu(Connector connector)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;

        }

        private void Statistics_Click(object sender, RoutedEventArgs e)
        {
            Statistics page = new Statistics(_connector);
            NavigationService.Navigate(page);
        }

        private void logout_Click(object sender, RoutedEventArgs e)
        {
            byte[] msg = classes.Serializer.serializeRequest(classes.Deserializer.LOGOUT_CODE);
            _connector.sendGetData(msg);
            WelcomePage page = new WelcomePage();
            NavigationService.Navigate(page);
        }

        private void join_Click(object sender, RoutedEventArgs e)
        {
            JoinRoomPage page = new JoinRoomPage(_connector);
            NavigationService.Navigate(page);
        }

        private void create_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomPage page = new CreateRoomPage(_connector);
            NavigationService.Navigate(page);
        }
    }
}
