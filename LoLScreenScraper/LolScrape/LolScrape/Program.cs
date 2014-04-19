using System;
using System.Runtime.InteropServices;
using System.Text;



namespace LolScrape
{
    class Program
    {
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern int SendMessage(IntPtr hWnd, int wMsg, int wParam, StringBuilder lParam);
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern int GetWindowText(int hWnd, StringBuilder lpString, int length);
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern int GetWindowTextLength(int hWnd);
        [DllImport("user32.dll")]
        static extern bool EnumChildWindows(IntPtr hWndParent, WindowEnumDelegate lpEnumFunc, int lParam);
        [DllImport("user32.dll")]
        static extern IntPtr FindWindow(StringBuilder lpClassName, StringBuilder lpWindowName);
        [DllImport("user32.dll")]
        static extern uint RealGetWindowClass(IntPtr hwnd, StringBuilder pszType, uint cchType);

        const int WM_GETTEXT = 0x000D;
        const int WM_GETTEXTLENGTH = 0x000E;

        public delegate bool WindowEnumDelegate(IntPtr hwnd, int lParam);

        private static bool WindowEnumProc(IntPtr handle, int lParam)
        {
            int textLen;
            StringBuilder text;
            StringBuilder className = new StringBuilder(1024);
            RealGetWindowClass(handle, className, 1024);

            textLen = SendMessage(handle, WM_GETTEXTLENGTH, 0, null);
            if (textLen != 0)
            {
                text = new StringBuilder(textLen);
                SendMessage(handle, WM_GETTEXT, (textLen + 1), text);
                Console.WriteLine(GetWindowText(handle, text, textLen));
            }
            return true;
        }

        static void Main(string[] args)
        {

            StringBuilder name = new StringBuilder("Untitled - Notepad");
            IntPtr hWnd = FindWindow(null, name);
            Console.WriteLine(hWnd);

            WindowEnumDelegate del = new WindowEnumDelegate(WindowEnumProc);
            EnumChildWindows(hWnd, del, 0);

            System.Threading.Thread.Sleep(5000);

        }

        
    }
}
