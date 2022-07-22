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
using System.Threading;

namespace trivia_client
{
    /// <summary>
    /// Interaction logic for GameResults.xaml
    /// </summary>
    public partial class GameResults : Page
    {
        Connector _connector;
        bool _runUpdateThread = true;
        public GameResults(Connector connector)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;
            Error_gameIsNotOver.Visibility = Visibility.Visible;
            createThread();
        }

        private void showResults()
        {
            List<classes.PlayerResultsForList> res = getResults();
            if(res.ToArray().Length != 0)
            {
                this.Dispatcher.Invoke(() =>
                {
                    results.ItemsSource = res;
                    results.Visibility = Visibility.Visible;
                    Error_gameIsNotOver.Visibility = Visibility.Hidden;
                    _runUpdateThread = false;
                });
            }
        }


        [STAThread]
        public void update()
        {
            while (_runUpdateThread)
            {
                showResults();
                Thread.Sleep(1000); //will sleep for 3 sec
            }
        }

        [STAThread]
        public Thread createThread()
        {

            // Create a secondary thread by passing a ThreadStart delegate  
            Thread updateThread = new Thread(new ThreadStart(update));
            // Start secondary thread  
            updateThread.Start();

            return updateThread;
        }
        private void backToMenu_Click(object sender, RoutedEventArgs e)
        {
            byte[] res = _connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.LEAVE_GAME));
            classes.LeaveGameResponse r = classes.Deserializer.deserializeLeaveGameResponse(res);
            if(r.status == classes.Deserializer.LEAVE_GAME)
            {
                Menu page = new Menu(_connector);
                NavigationService.Navigate(page);
            }   
        }

        private List<classes.PlayerResultsForList> getResults()
        {
            classes.GetGameResultsResponse r;
            
            byte[] res = _connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.GET_GAME_RESULTS));
            r = classes.Deserializer.deserializeGetGameResultsResponse(res);
            
            //get the results to the list
            List<classes.PlayerResultsForList> results = new List<classes.PlayerResultsForList>();
            for (int i = 0; i < r.results.Length; i++)
            {
                if(r.results[i].username.Length > 2)
                {
                    results.Add(new classes.PlayerResultsForList()
                    {
                        username = r.results[i].username.Substring(1, r.results[i].username.Length - 2),
                        correctAnswerCount = r.results[i].correctAnswerCount,
                        averageAnswerTime = r.results[i].averageAnswerTime
                    });
                }
            }
            return results;
        }
    }
}
