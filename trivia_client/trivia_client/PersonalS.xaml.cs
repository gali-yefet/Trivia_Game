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
    /// Interaction logic for PersonalS.xaml
    /// </summary>
    public partial class PersonalS : Page
    {
        Connector _connector;
        public PersonalS(Connector connector)
        {
            InitializeComponent();
            _connector = connector;
            //--> get data from database and put it in the listView
            PersonalStatistics.Items.Clear();
            var res = _connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.GET_PERSONAL_STATS_CODE));
            var personalS = classes.Deserializer.deserializeGetPersonalStatsResponse(res).statistics;
            PersonalStatistics.ItemsSource = personalS;

        }
        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            Statistics page = new Statistics(_connector);
            NavigationService.Navigate(page);
        }

    }
}
