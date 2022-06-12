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
        uint _numOfQuestions;
        uint _questionsLeft;
        uint _correctAnswers;
        uint _timeForQuestion;
        DispatcherTimer _timer;
        TimeSpan _time;

        public GamePage(Connector connector, uint numOfQuestions, uint timeForQuestion)
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
            //get the time
            _timer.Stop();//stops the timer

            classes.SubmitAnswerRequest answerRequest;
            answerRequest.answerId = UInt32.Parse((String)((Button)sender).Tag); //get the index of the button
            answerRequest.time =(uint)(_timeForQuestion - _time.TotalSeconds);
            byte[] msg = classes.Serializer.serializeSubmitAnswerRequest(answerRequest);
            byte[] res = _connector.sendGetData(msg);
            classes.SubmitAnswerResponse r = classes.Deserializer.deserializeSubmitAnswerResponse(res);

            if (r.status == classes.Deserializer.SUBMIT_ANSWER)
            {
                checkAnswer(answerRequest.answerId, r.correctAnswerId);
                Thread.Sleep(500); //wait so the user can see the color of his answer
                getQuestion();
            }
         
        }

        private void getQuestion(bool isFirst = false)
        {
            if (_questionsLeft > 0)
            {
                _questionsLeft--;
                updateScreen();

                byte[] msg = classes.Serializer.serializeRequest(classes.Deserializer.GET_QUESTION);
                byte[] res = _connector.sendGetData(msg);
                classes.GetQuestionResponse r = classes.Deserializer.deserializeGetQuestionResponse(res);
                if(r.status == classes.Deserializer.GET_QUESTION)
                {
                    question.Content = r.question;
                    Ans1.Content = r.answers[1];
                    Ans2.Content = r.answers[2];
                    Ans3.Content = r.answers[3];
                    Ans4.Content = r.answers[4];
                }

            }
            else
            {
                GameResults page = new GameResults(_connector);
                NavigationService.Navigate(page);
                _timer.Stop();
            }
        }

        private void CreateTimer(uint timeForQuestion)
        {
            _timeForQuestion = timeForQuestion;
            _time = TimeSpan.FromSeconds(timeForQuestion);
            
            _timer = new DispatcherTimer(new TimeSpan(0, 0, 1), DispatcherPriority.Normal, delegate
            {
                Clock.Text = _time.ToString("c").Substring(4); //format the time m::ss
                if (_questionsLeft == 0 && _time == TimeSpan.Zero)
                {
                    GameResults page = new GameResults(_connector);
                    NavigationService.Navigate(page);
                    _timer.Stop();
                }
                else
                {
                    if (_time == TimeSpan.Zero)
                        getQuestion();
                    _time = _time.Add(TimeSpan.FromSeconds(-1));
                }
            }, Application.Current.Dispatcher);
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

        private void checkAnswer(uint answerId, uint correctAnswerId)
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
