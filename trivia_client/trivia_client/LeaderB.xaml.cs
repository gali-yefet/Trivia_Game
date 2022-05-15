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
        Connector _connector;
        public LeaderB(Connector connector)
        {
            InitializeComponent();
            _connector = connector;

            //--> get data from database and put it in the listView
            LeaderBoard.Items.Clear();
            var res = _connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.GET_HIGH_SCORE_CODE));
            var leaderB = classes.Deserializer.deserializeGetHighScoreResponse(res).statistics;
            LeaderBoard.ItemsSource = leaderB;

        }
        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            Statistics page = new Statistics(_connector);
            NavigationService.Navigate(page);
        }

    }
}
