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
using System.Windows.Shapes;

namespace trivia_client
{
    /// <summary>
    /// Interaction logic for LeaderBoard.xaml
    /// </summary>
    public partial class LeaderBoard : Window
    {
        public LeaderBoard()
        {
            InitializeComponent();
            //-->
            //ServiceReference1.ImojWCFServiceClient client = new ServiceReference1.ImojWCFServiceClient();
            //listView1.Items.Clear();
            //var userList = client.getUsers();
            //listView1.ItemsSource = userList;
        }
    }
}
