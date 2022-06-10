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
    /// Interaction logic for CreateRoomPage.xaml
    /// </summary>
    public partial class CreateRoomPage : Page
    {
        Connector _connector;
        int MAX_QUESTIONS = 10;
        public CreateRoomPage(Connector connector, bool firstTime = true)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;

            if (!firstTime)
                Error.Visibility = Visibility.Visible;
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            Menu page = new Menu(_connector);
            NavigationService.Navigate(page);
        }

        private void SendButton_Click(object sender, RoutedEventArgs e)
        {
            clearBorders();
            if (checkIfValid())
                return;

            //initilize a request
            classes.CreateRoomRequest r;
            r.answerTimeOut = UInt32.Parse(answerTimeoutInput.Text);
            r.maxUsers = UInt32.Parse(maxUsersInput.Text);
            r.questionsCount = UInt32.Parse(questionCountInput.Text);
            r.roomName = roomNameInput.Text;

            //send the request to the server
            byte[] msg = classes.Serializer.serializeCreateRoomRequest(r);
            msg = _connector.sendGetData(msg);
            classes.CreateRoomResponse response = classes.Deserializer.deserializeCreateRoomResponse(msg);

            //check if creation failed and move to page accordingly
            if (response.status != classes.Deserializer.CREATE_ROOM_CODE)
            {
                CreateRoomPage page = new CreateRoomPage(_connector, false);
                NavigationService.Navigate(page);
            }
            else
            {
                RoomUsers page = new RoomUsers(_connector, true);
                NavigationService.Navigate(page);
            }

        }

        //chek if the feilds contain what they should, and if so paint the border in red
        //in: none
        //out: if some feild is not valid - true, else - false
        private bool checkIfValid()
        {
            bool isEmpty = false;
            if (answerTimeoutInput.Text == "" || !classes.Serializer.checkifNumber(answerTimeoutInput.Text))
            {
                answerTimeoutInput.BorderBrush = Brushes.Red;
                isEmpty = true;
            }
            if (maxUsersInput.Text == "" || !classes.Serializer.checkifNumber(maxUsersInput.Text))
            {
                maxUsersInput.BorderBrush = Brushes.Red;
                isEmpty = true;
            }
            if (questionCountInput.Text == "" || !classes.Serializer.checkifNumber(questionCountInput.Text) || Int32.Parse(questionCountInput.Text) > MAX_QUESTIONS)
            {
                questionCountInput.BorderBrush = Brushes.Red;
                isEmpty = true;
            }
            if (roomNameInput.Text == "")
            {
                roomNameInput.BorderBrush = Brushes.Red;
                isEmpty = true;
            }
            return isEmpty;
        }

        private void clearBorders()
        {
            answerTimeoutInput.BorderBrush = Brushes.Transparent;
            maxUsersInput.BorderBrush = Brushes.Transparent;
            questionCountInput.BorderBrush = Brushes.Transparent;
            roomNameInput.BorderBrush = Brushes.Transparent;
        }
    }
}
