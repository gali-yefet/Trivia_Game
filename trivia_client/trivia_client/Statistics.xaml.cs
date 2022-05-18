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


    }
}
