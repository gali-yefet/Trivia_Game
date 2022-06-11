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
    /// Interaction logic for GameResults.xaml
    /// </summary>
    public partial class GameResults : Page
    {
        Connector _connector;
        public GameResults(Connector connector)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;
            results.ItemsSource = getResults();
        }

        private void backToMenu_Click(object sender, RoutedEventArgs e)
        {
            Menu page = new Menu(_connector);
            NavigationService.Navigate(page);
        }

        private List<classes.PlayerResults> getResults()
        {
            classes.GetGameResultsResponse r;
            do
            {
                byte[] res = _connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.GET_GAME_RESULTS));
                r = classes.Deserializer.deserializeGetGameResultsResponse(res);
            } while (r.status != classes.Deserializer.GET_GAME_RESULTS);

            List<classes.PlayerResults> results = new List<classes.PlayerResults>(r.results);
            return results;
        }
    }
}
