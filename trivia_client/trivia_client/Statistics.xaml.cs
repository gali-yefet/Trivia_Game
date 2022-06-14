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
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Page
    {
        Connector _connector;
        public Statistics(Connector connector)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();

            _connector = connector;
        }
        private void LeaderB_Click(object sender, RoutedEventArgs e)
        {
            LeaderB page = new LeaderB(_connector);
            NavigationService.Navigate(page);
        }

        private void PersonalS_Click(object sender, RoutedEventArgs e)
        {
            PersonalS page = new PersonalS(_connector);
            NavigationService.Navigate(page);
        }
        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            Menu page = new Menu(_connector);
            NavigationService.Navigate(page);
        }

        //for getting personal statistics List
        static public List<classes.Statistics> GetStatisticsListFromServer(Connector connector)
        {
            byte[] res = connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.GET_PERSONAL_STATS_CODE));
            classes.GetPersonalStatsResponse r = classes.Deserializer.deserializeGetPersonalStatsResponse(res);

            List<classes.Statistics> statistics = new List<classes.Statistics>();
            foreach (classes.Statistics currStat in r.statistics)
            {
                statistics.Add(new classes.Statistics()
                {
                    avgTime = currStat.avgTime,
                    victories = currStat.victories,
                    games = currStat.games,
                    name = currStat.name.Substring(1, currStat.name.Length - 2)
                });
            }
            return statistics;
        }

        //for getting leader board List
        static public List<classes.Statistics> GetLeaderBoardListFromServer(Connector connector)
        {
            byte[] res = connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.GET_HIGH_SCORE_CODE));
            classes.GetHighScoreResponse r = classes.Deserializer.deserializeGetHighScoreResponse(res);

            List<classes.Statistics> statistics = new List<classes.Statistics>();
            foreach (classes.Statistics currStat in r.statistics)
            {
                statistics.Add(new classes.Statistics()
                {
                    avgTime = currStat.avgTime,
                    victories = currStat.victories,
                    games = currStat.games,
                    name = currStat.name.Substring(1, currStat.name.Length - 2)
                });
            }
            return statistics;
        }
    }
}
