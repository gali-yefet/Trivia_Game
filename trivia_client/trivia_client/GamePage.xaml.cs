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
using System.Threading;

namespace trivia_client
{
    /// <summary>
    /// Interaction logic for GamePage.xaml
    /// </summary>
    public partial class GamePage : Page
    {
        Connector _connector;
        int _numOfQuestions;
        int _questionsLeft;
        int _correctAnswers;
        int _timeForQuestion;
        DispatcherTimer _timer;
        TimeSpan _time;

        public GamePage(Connector connector, int numOfQuestions, int timeForQuestion)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();

            _connector = connector;
            _numOfQuestions = numOfQuestions;
            _questionsLeft = numOfQuestions;
            _correctAnswers = 0;
            CreateTimer(timeForQuestion);

            getQuestion(true);
        }

        private void Ans_Click(object sender, RoutedEventArgs e)
        {
            int ansId = Int32.Parse((String)((Button)sender).Tag); //get the index of the button

            //TODO:
            //send answer, and get response

            int correctAnsId = 3;//TODO: change to real ansId
            checkAnswer(ansId, correctAnsId);
            Thread.Sleep(500); //wait so the user can see the color of his answer
            getQuestion();
        }

        private void getQuestion(bool isFirst = false)
        {

            if (!isFirst)
                _timer.Stop();//stops the timer

            if (_questionsLeft > 0)
            {
                _questionsLeft--;
                updateScreen();

                //TODO:
                //send get quesion request
                //change question
                //cahnge all answers
            }
            else
            {
                GameResults page = new GameResults(_connector);
                NavigationService.Navigate(page);
            }
        }

        private void CreateTimer(int timeForQuestion)
        {
            _timeForQuestion = timeForQuestion;
            _time = TimeSpan.FromSeconds(timeForQuestion);

            _timer = new DispatcherTimer(new TimeSpan(0, 0, 1), DispatcherPriority.Normal, delegate
            {
                Clock.Text = _time.ToString("c").Substring(4); //format the time m::ss
                if (_time == TimeSpan.Zero)
                    getQuestion();
                _time = _time.Add(TimeSpan.FromSeconds(-1));
            }, Application.Current.Dispatcher);

            _timer.Start();
        }

        private void updateScreen()
        {
            //update timer
            _time = TimeSpan.FromSeconds(_timeForQuestion);
            _timer.Start();
            
            //update data
            correctAnswer.Text = _correctAnswers.ToString() + " correct answers!";
            answers.Text = (_numOfQuestions - _questionsLeft).ToString() + " / " + _numOfQuestions;

            //clear buttons background
            Ans1.Background = Brushes.LightGray;
            Ans2.Background = Brushes.LightGray;
            Ans3.Background = Brushes.LightGray;
            Ans4.Background = Brushes.LightGray;
        }

        private void checkAnswer(int answerId, int correctAnswerId)
        {
            if(answerId == correctAnswerId)
                _correctAnswers++;
            else
            {
                //color wrong answer
                switch (answerId)
                {
                    case 1:
                        Ans1.Background = Brushes.PaleVioletRed;
                        break;
                    case 2:
                        Ans2.Background = Brushes.PaleVioletRed;
                        break;
                    case 3:
                        Ans3.Background = Brushes.PaleVioletRed;
                        break;
                    case 4:
                        Ans4.Background = Brushes.PaleVioletRed;
                        break;
                }
            }

            //color right answer
            switch (correctAnswerId)
            {
                case 1:
                    Ans1.Background = Brushes.PaleGreen;
                    break;
                case 2:
                    Ans2.Background = Brushes.PaleGreen;
                    break;
                case 3:
                    Ans3.Background = Brushes.PaleGreen;
                    break;
                case 4:
                    Ans4.Background = Brushes.PaleGreen;
                    break;
            }
        }

    }
}
