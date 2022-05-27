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
    /// Interaction logic for GamePage.xaml
    /// </summary>
    public partial class GamePage : Page
    {
        Connector _connector;

        public GamePage(Connector connector)
        {
            InitializeComponent();
            backgroundPage.Content = new BackgroundPage();
            _connector = connector;


            //testing
            byte[] res = _connector.sendGetData(classes.Serializer.serializeRequest(classes.Deserializer.GET_QUESTION));
            classes.GetQuestionResponse r = classes.Deserializer.deserializeGetQuestionResponse(res);

        }
    }
}
