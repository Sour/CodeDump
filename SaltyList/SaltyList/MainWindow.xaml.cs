using System;
using System.Collections;
using System.Net;
using System.Windows;
using System.Windows.Controls;

namespace SaltyList
{
    public partial class MainWindow : Window
    {

        public Hashtable siteUrl = new Hashtable();
        public Hashtable location = new Hashtable();
        public CheckBox[] boxes = new CheckBox[6];
        public Button[] buttons = new Button[6];
        public Label[] labels = new Label[6];
        public int count;

        public MainWindow()
        {
            InitializeComponent();
            initHashTables();
            initControlArrays();
            



        }

        private void initControlArrays()
        {
            boxes[0] = cb1;
            boxes[1] = cb2;
            boxes[2] = cb3;
            boxes[3] = cb4;
            boxes[4] = cb5;
            boxes[5] = cb6;

            buttons[0] = btn1;
            buttons[1] = btn2;
            buttons[2] = btn3;
            buttons[3] = btn4;
            buttons[4] = btn5;
            buttons[5] = btn6;

            labels[0] = lbl1;
            labels[1] = lbl2;
            labels[2] = lbl3;
            labels[3] = lbl4;
            labels[4] = lbl5;
            labels[5] = lbl6;

        }

        private void initHashTables()
        {
            siteUrl[1] = "http://";
            siteUrl[2] = ".craigslist.org/search/cta?query=";
            siteUrl[3] = "&zoomToPosting=&srchType=T&minAsk=";
            siteUrl[4] = "&maxAsk=";

            location[1] = "bellingham";
            location[2] = "seattle";
            location[3] = "boise";
            location[4] = "spokane";
            location[5] = "portland";
            location[6] = "vancouver.en";
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            count = 0;
            if (searchContent.Text != "")
            {
                if (cb1.IsChecked == true)
                    addLabelChild((siteUrl[1] + location[1].ToString() + siteUrl[2] + searchContent.Text + siteUrl[3] + min.Text + siteUrl[4] + max.Text), 1);
                if (cb2.IsChecked == true)
                    addLabelChild((siteUrl[1] + location[2].ToString() + siteUrl[2] + searchContent.Text + siteUrl[3] + min.Text + siteUrl[4] + max.Text), 2);
                if (cb3.IsChecked == true)
                    addLabelChild((siteUrl[1] + location[3].ToString() + siteUrl[2] + searchContent.Text + siteUrl[3] + min.Text + siteUrl[4] + max.Text), 3);
                if (cb4.IsChecked == true)
                    addLabelChild((siteUrl[1] + location[4].ToString() + siteUrl[2] + searchContent.Text + siteUrl[3] + min.Text + siteUrl[4] + max.Text), 4);
                if (cb5.IsChecked == true)
                    addLabelChild((siteUrl[1] + location[5].ToString() + siteUrl[2] + searchContent.Text + siteUrl[3] + min.Text + siteUrl[4] + max.Text), 5);
                if (cb6.IsChecked == true)
                    addLabelChild((siteUrl[1] + location[6].ToString() + siteUrl[2] + searchContent.Text + siteUrl[3] + min.Text + siteUrl[4] + max.Text), 6);
            }
            if (count > 0)
                initSecondaryPane();
                
        }

        private void initSecondaryPane()
        {
            myWindow.Width = 850;
            btnLoad.Visibility = Visibility.Visible;
        }

        private void addLabelChild(string url, int position)
        {
            count++;
            switch (count)
            {
                case 1:
                    btn1.Visibility = Visibility.Visible;
                    lbl1.Visibility = Visibility.Visible;
                    lbl1.Content = url;

                    break;
                case 2:
                    btn2.Visibility = Visibility.Visible;
                    lbl2.Visibility = Visibility.Visible;
                    lbl2.Content = url;

                    break;
                case 3:
                    btn3.Visibility = Visibility.Visible;
                    lbl3.Visibility = Visibility.Visible;
                    lbl3.Content = url;

                    break;
                case 4:
                    btn4.Visibility = Visibility.Visible;
                    lbl4.Visibility = Visibility.Visible;
                    lbl4.Content = url;

                    break;
                case 5:
                    btn5.Visibility = Visibility.Visible;
                    lbl5.Visibility = Visibility.Visible;
                    lbl5.Content = url;

                    break;
                case 6:
                    btn6.Visibility = Visibility.Visible;
                    lbl6.Visibility = Visibility.Visible;
                    lbl6.Content = url;

                    break;
                default:
                    break;
            } 
        }

        private void cbAll_Checked(object sender, RoutedEventArgs e)
        {
            cb1.IsChecked = true;
            cb2.IsChecked = true;
            cb3.IsChecked = true;
            cb4.IsChecked = true;
            cb5.IsChecked = true;
            cb6.IsChecked = true;

        }

        private void cbAll_Unchecked(object sender, RoutedEventArgs e)
        {
            cb1.IsChecked = false;
            cb2.IsChecked = false;
            cb3.IsChecked = false;
            cb4.IsChecked = false;
            cb5.IsChecked = false;
            cb6.IsChecked = false;
        }

        private void btn1_Click_1(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start(lbl1.Content.ToString());
            btn1.Visibility = Visibility.Hidden;
            lbl1.Visibility = Visibility.Hidden;
            lbl1.Content = "";
            int temp = 0;
            foreach (Button btn in buttons)
            {
                if (btn.Visibility == Visibility.Hidden)
                {
                    temp++;
                }
            }
            if (temp == 6)
                myWindow.Width = 175;


        }

        private void btn1_Click_2(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start(lbl2.Content.ToString());
            btn2.Visibility = Visibility.Hidden;
            lbl2.Visibility = Visibility.Hidden;
            lbl2.Content = "";

            int temp = 0;
            foreach (Button btn in buttons)
            {
                if (btn.Visibility == Visibility.Hidden)
                {
                    temp++;
                }
            }
            if (temp == 6)
                myWindow.Width = 175;
        }

        private void btn1_Click_3(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start(lbl3.Content.ToString());
            btn3.Visibility = Visibility.Hidden;
            lbl3.Visibility = Visibility.Hidden;
            lbl3.Content = "";

            int temp = 0;
            foreach (Button btn in buttons)
            {
                if (btn.Visibility == Visibility.Hidden)
                {
                    temp++;
                }
            }
            if (temp == 6)
                myWindow.Width = 175;
        }

        private void btn1_Click_4(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start(lbl4.Content.ToString());
            btn4.Visibility = Visibility.Hidden;
            lbl4.Visibility = Visibility.Hidden;
            lbl4.Content = "";

            int temp = 0;
            foreach (Button btn in buttons)
            {
                if (btn.Visibility == Visibility.Hidden)
                {
                    temp++;
                }
            }
            if (temp == 6)
                myWindow.Width = 175;
        }

        private void btn1_Click_5(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start(lbl5.Content.ToString());
            btn5.Visibility = Visibility.Hidden;
            lbl5.Visibility = Visibility.Hidden;
            lbl5.Content = "";

            int temp = 0;
            foreach (Button btn in buttons)
            {
                if (btn.Visibility == Visibility.Hidden)
                {
                    temp++;
                }
            }
            if (temp == 6)
                myWindow.Width = 175;
        }

        private void btn1_Click_6(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start(lbl6.Content.ToString());
            btn6.Visibility = Visibility.Hidden;
            lbl6.Visibility = Visibility.Hidden;
            lbl6.Content = "";

            int temp = 0;
            foreach (Button btn in buttons)
            {
                if (btn.Visibility == Visibility.Hidden)
                {
                    temp++;
                }
            }
            if (temp == 6)
                myWindow.Width = 175;
        }

        private void btnLoad_Click(object sender, RoutedEventArgs e)
        {
            foreach (Label label in labels)
            {
                if(btn1.Visibility == Visibility.Visible)
                    System.Diagnostics.Process.Start(label.Content.ToString());

            }
            foreach (Button btn in buttons)
            {
                btn.Visibility = Visibility.Hidden;
            }
            myWindow.Width = 175;
        }
    }
}
