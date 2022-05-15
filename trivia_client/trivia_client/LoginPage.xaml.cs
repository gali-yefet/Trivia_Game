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
    /// Interaction logic for LoginPage.xaml
    /// </summary>
    public partial class LoginPage : Page
    {
        Connector _connector;
        public LoginPage(Connector connector, bool firstTime=true)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;
            if (!firstTime)
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

            classes.LoginRequest r;
            r.username = usernameInput.Text;
            r.password = passwordInput.Text;

            //check if the fields are empty
            if (r.username == "")
            {
                usernameInput.BorderBrush = Brushes.Red;
                return;
            }
            if(r.password == "")
            {
                passwordInput.BorderBrush = Brushes.Red;
                return;
            }

            //send a login request
            byte[] msg = classes.Serializer.serializeLoginRequest(r);
            byte[] res = _connector.sendGetData(msg);
            classes.LoginResponse response = classes.Deserializer.deserializeLoginResponse(res);

            //check if login failed and move to page accordingly
            if(response.status != classes.Deserializer.LOGIN_CODE)
            {
                LoginPage page = new LoginPage(_connector, false);
                NavigationService.Navigate(page);
            }
            else
            {
                Menu page = new Menu();
                NavigationService.Navigate(page);
            }
        }
    }
}
