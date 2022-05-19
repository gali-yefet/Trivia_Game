﻿using System;
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
            backgroundPage.Content = new BackgroundPage();

            _connector = connector;

            //show statistics
            LeaderBoard.Items.Clear();
            LeaderBoard.ItemsSource = Statistics.GetStatisticsListFromServer(_connector);

        }
        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            Statistics page = new Statistics(_connector);
            NavigationService.Navigate(page);
        }

    }
}
