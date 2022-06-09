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
using System.Windows.Threading;


namespace trivia_client
{
    /// <summary>
    /// Interaction logic for GamePage.xaml
    /// </summary>
    public partial class GamePage : Page
    {
        Connector _connector;
        int _questionsLeft;
        int _correctAnswers;
        DispatcherTimer _timer;

        public GamePage(Connector connector, int numOfQuestions, int timeForQuestion)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;
            _questionsLeft = numOfQuestions;
            _correctAnswers = 0;

            //show first question
            getQuestion();

            //start clock
            timer(timeForQuestion);
        }

        private void Ans_Click(object sender, RoutedEventArgs e)
        {
            var ansNum = ((Button)sender).Tag; //get the index of the button

            //send answer
            //show correct answer (paint in green, switch case?)
            //if it's the correct answer - _correctAnswers++
            getQuestion();
        }

        private void getQuestion()
        {
            if (_questionsLeft > 1)
            {
                _questionsLeft--;
                //send get quesion request
                //change question
                //cahnge all answers
            }
            else
            {
                _timer.Stop();//stops the timer
                GameResults page = new GameResults(_connector);
                NavigationService.Navigate(page);
            }
        }

        private void timer(int seconds)
        {
            TimeSpan time = TimeSpan.FromSeconds(seconds);

            _timer = new DispatcherTimer(new TimeSpan(0, 0, 1), DispatcherPriority.Normal, delegate
            {
                Clock.Text = time.ToString("c");
                if (time == TimeSpan.Zero) 
                    _timer.Stop();
                time = time.Add(TimeSpan.FromSeconds(-1));
            }, Application.Current.Dispatcher);

            _timer.Start();
        }
    }
}
