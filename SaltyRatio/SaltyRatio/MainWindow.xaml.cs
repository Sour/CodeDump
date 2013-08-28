using System;
using System.ComponentModel;
using System.Net;
using System.Threading;
using System.Windows;
using System.Windows.Forms;

namespace SaltyRatio
{
    public partial class MainWindow : Window
    {
        public WebBrowser webBrowser1;
        public MainWindow()
        {
            InitializeComponent();
            webBrowser1 = new System.Windows.Forms.WebBrowser();
            webBrowser1.ScriptErrorsSuppressed = true;
            host.Child = webBrowser1;

            webBrowser1.Navigate(new Uri("http://www.saltybet.com/authenticate?signin=1"));
            webBrowser1.DocumentCompleted += webBrowser1_DocumentCompleted;
        }


        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {

            if (((WebBrowser)sender).ReadyState != WebBrowserReadyState.Complete)
            {
                return;
            }
            else
            {
                waitLogin(((WebBrowser)sender));
            }

            ((WebBrowser)sender).Document.GetElementById("betstatus").AttachEventHandler("onpropertychange", delegate { statusEventHandler(((WebBrowser)sender).Document.GetElementById("betstatus"), EventArgs.Empty); });
        }

        private void statusEventHandler(object sender, EventArgs eventArgs)
        {
            var temp = (HtmlElement)sender;
            if (mLabel.Content != webBrowser1.Document.GetElementById("betstatus").InnerText)
            {
                if (mLabel.Content != "Bets are OPEN!" && webBrowser1.Document.GetElementById("betstatus").InnerText == "Bets are OPEN!")
                {
                    webBrowser1.Document.GetElementById("wager").SetAttribute("value", "10");
                    webBrowser1.Document.GetElementById("player1").InvokeMember("click");
                }
                mLabel.Content = webBrowser1.Document.GetElementById("betstatus").InnerText;
                oneButton.Content = webBrowser1.Document.GetElementById("p1name").InnerText;
                twoButton.Content = webBrowser1.Document.GetElementById("p2name").InnerText;
            }
        }

        private void waitLogin(WebBrowser webBrowser1)
        {
            HtmlElementCollection elements = webBrowser1.Document.GetElementsByTagName("input");
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
            webBrowser1.DocumentCompleted += webBrowser1_DocumentCompleted;
        }

        private void oneButton_Click(object sender, RoutedEventArgs e)
        {
            if (webBrowser1.Document.GetElementById("betstatus").InnerText == "Bets are OPEN!")
            {
                webBrowser1.Document.GetElementById("wager").SetAttribute("value", "10");
                webBrowser1.Document.GetElementById("player1").InvokeMember("click");

            }
        }

        private void twoButton_Click(object sender, RoutedEventArgs e)
        {
            if (webBrowser1.Document.GetElementById("betstatus").InnerText == "Bets are OPEN!")
            {
                webBrowser1.Document.GetElementById("wager").SetAttribute("value", "10");
                webBrowser1.Document.GetElementById("player2").InvokeMember("click");

            }
        }
    }
}