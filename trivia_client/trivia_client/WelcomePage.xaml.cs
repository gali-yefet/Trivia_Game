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
    /// Interaction logic for WelcomePage.xaml
    /// </summary>
    public partial class WelcomePage : Page
    {
        public WelcomePage()
        {
            InitializeComponent();
        }
        private void login_Click(object sender, RoutedEventArgs e)
        {
            LoginPage page = new LoginPage();
            NavigationService.Navigate(page);
        }

        private void signup_Click(object sender, RoutedEventArgs e)
        {
            SignupPage page = new SignupPage();
            NavigationService.Navigate(page);
        }
    }
}
