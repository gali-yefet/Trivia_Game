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
        Connector _connector;
        public SignupPage(Connector connector, bool isFirst = true)
        {
            InitializeComponent();
            _connector = connector;
            backgroundPage.Content = new BackgroundPage();

            if (!isFirst)
                Error.Visibility = Visibility.Visible;

        }
        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            WelcomePage page = new WelcomePage(_connector);
            NavigationService.Navigate(page);
        }

        private void SendButton_Click(object sender, RoutedEventArgs e)
        {
            usernameInput.BorderBrush = Brushes.Transparent;
            passwordInput.BorderBrush = Brushes.Transparent;
            emailInput.BorderBrush = Brushes.Transparent;

            classes.SignupRequest r;
            r.username = usernameInput.Text;
            r.password = passwordInput.Text;
            r.email = emailInput.Text;

            //check if the fields are empty
            if (r.username == "")
            {
                usernameInput.BorderBrush = Brushes.Red;
                return;
            }
            if (r.password == "")
            {
                passwordInput.BorderBrush = Brushes.Red;
                return;
            }
            if (r.email == "")
            {
                emailInput.BorderBrush = Brushes.Red;
                return;
            }

            //send a signup request
            byte[] msg = classes.Serializer.serializeSignupRequest(r);
            msg = _connector.sendGetData(msg);
            classes.SignupResponse response = classes.Deserializer.deserializeSignupResponse(msg);

            //check if signup failed and move to page accordingly
            if (response.status != classes.Deserializer.SIGNUP_CODE)
            {
                SignupPage page = new SignupPage(_connector, false);
                NavigationService.Navigate(page);
            }
            else
            {
                Menu page = new Menu(_connector);
                NavigationService.Navigate(page);
            }
        }
    }
}
