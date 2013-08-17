using System;
using System.Threading;
using System.Windows;
using System.Windows.Forms;

namespace SaltyRatio
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private volatile bool _active, labelUpdate;
        Thread update;
        WebBrowser webBrowser1;


        public MainWindow()
        {
            InitializeComponent();
            webBrowser1 = new System.Windows.Forms.WebBrowser();
            webBrowser1.ScriptErrorsSuppressed = true;
            host.Child = webBrowser1;

            webBrowser1.Navigate(new Uri("http://www.saltybet.com/authenticate?signin=1"));
            webBrowser1.DocumentCompleted += webBrowser1_DocumentCompleted;

            _active = false;
            labelUpdate = false;
            update = new Thread(saltyUpdate);

        }

        private void saltyUpdate(object obj)
        {
            while (_active)
            {
                Console.WriteLine("i am active in the background");
                Thread.Sleep(1000);

            }
        }
        public void requestStop()
        {
            _active = false;
        }

        private void webBrowser1_DetectedChange(WebBrowser webBrowser1)
        {
            if (!_active)
            {
                _active = true;
                update.Start();
            }

            if (webBrowser1.Document.GetElementById("betstatus").InnerText != null)
            {
                mLabel.Content = webBrowser1.Document.GetElementById("betstatus").InnerText;
            }
            else
            {
                Console.WriteLine("null");
                mLabel.Content = "";
            }
        }


        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {

            if (((WebBrowser)sender).Url.ToString() == "http://www.saltybet.com/")
            {
                webBrowser1_DetectedChange(((WebBrowser)sender));
            }

            if (((WebBrowser)sender).ReadyState != WebBrowserReadyState.Complete)
            {
                return;
            }
            else
            {
                waitLogin(((WebBrowser)sender));
            }
        }

        private void waitLogin(WebBrowser webBrowser)
        {
            HtmlElementCollection elements = webBrowser.Document.GetElementsByTagName("input");
            foreach (HtmlElement element in elements)
            {
                if (element.Name == "email")
                {
                    element.SetAttribute("value", "mechanicfreak440@gmail.com");
                }

                if (element.Name == "pword") //look for the password field
                {
                    element.SetAttribute("value", "lolice440"); //set the password
                }
                if (element.GetAttribute("type").Equals("submit") && element.GetAttribute("value").Equals("Sign In"))
                {
                    element.InvokeMember("click"); //submit the form

                }
            }
            webBrowser.DocumentCompleted += webBrowser1_DocumentCompleted;
        }
    }
}