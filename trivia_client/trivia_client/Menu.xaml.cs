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
        public Menu()
        {
            InitializeComponent();
        }

        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            JoinRoomPage page = new JoinRoomPage();
            NavigationService.Navigate(page);
        }

        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomPage page = new CreateRoomPage();
            NavigationService.Navigate(page);
        }

    }
}
