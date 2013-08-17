using System;
using System.Threading;
using System.Windows;
using System.Windows.Interop;
using System.Diagnostics;
using System.Windows.Forms;
using System.Windows.Navigation;
using SaltyRatio.Plugins;

namespace SaltyRatio
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            WebBrowser webBrowser1 = new System.Windows.Forms.WebBrowser();
            webBrowser1.ScriptErrorsSuppressed = true;
            host.Child = webBrowser1;

            webBrowser1.Navigate(new Uri("http://www.saltybet.com/authenticate?signin=1"));
            webBrowser1.DocumentCompleted += webBrowser1_DocumentCompleted;
            webBrowser1.Refresh();
            Console.WriteLine("does this loop");
        }

        private void webBrowser1_DetectedChange(WebBrowser webBrowser1)
        {
            if (webBrowser1.Document.GetElementById("betstatus").InnerText != null)
                mLabel.Content = webBrowser1.Document.GetElementById("betstatus").InnerText;
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
                Console.WriteLine("switching to bets");
            }
            //Check if page is fully loaded or not
            if (((WebBrowser)sender).ReadyState != WebBrowserReadyState.Complete)
                return;
            else
                waitLogin(((WebBrowser)sender));
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
            webBrowser.DocumentCompleted += webBrowser1_DocumentCompletedMain;
            
        }
        private void webBrowser1_DocumentCompletedMain(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            //Check if page is fully loaded or not
            if (((WebBrowser)sender).ReadyState != WebBrowserReadyState.Complete)
                return;
        }
    }
}