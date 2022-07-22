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
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;

            List<classes.Statistics> list = Statistics.GetStatisticsListFromServer(_connector);
            if (list.Count != 1)
            {
                Error_noStatistics.Visibility = Visibility.Visible;
                PersonalStatistics.Visibility = Visibility.Hidden;
            }
            else
            {
                //show statistics
                PersonalStatistics.Items.Clear();
                PersonalStatistics.ItemsSource = list;
            }
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            Statistics page = new Statistics(_connector);
            NavigationService.Navigate(page);
        }

        
    }
}
