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
    /// Interaction logic for SignupPage.xaml
    /// </summary>
    public partial class SignupPage : Page
    {
        public SignupPage()
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
        }
        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            WelcomePage page = new WelcomePage();
            NavigationService.Navigate(page);
        }

        private void SendButton_Click(object sender, RoutedEventArgs e)
        {
            //TODO
            //if some field is empty - paint it's border red
            //else - send login request

            if (usernameInput.Text.Length == 0 || passwordInput.Text.Length == 0 || email.Text.Length == 0)
            {
                if (usernameInput.Text.Length == 0)
                {
                    usernameInput.Background = Brushes.OrangeRed;

                }
                if (passwordInput.Text.Length == 0)
                {
                    passwordInput.Background = Brushes.OrangeRed;
                }

                if (email.Text.Length == 0)
                {
                    email.Background = Brushes.OrangeRed;
                }
            }
            else
            {
                //TODO: send signup req
                //if valid - move to main menu window
                //else - print not valid to the screen
            }
        }
    }
}
