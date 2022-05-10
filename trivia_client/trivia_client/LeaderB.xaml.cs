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
    /// Interaction logic for LeaderB.xaml
    /// </summary>
    public partial class LeaderB : Page
    {
        public LeaderB()
        {
            InitializeComponent();
            //--> get data from database and put it in the list
            //ServiceReference1.ImojWCFServiceClient client = new ServiceReference1.ImojWCFServiceClient();
            //listView1.Items.Clear();
            //var userList = client.getUsers();
            //listView1.ItemsSource = userList;

        }
        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            Statistics page = new Statistics();
            NavigationService.Navigate(page);
        }

    }
}
