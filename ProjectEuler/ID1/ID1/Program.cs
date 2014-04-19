using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ID1
{
    class Program
    {
        static void Main(string[] args)
        {
            int t = 0;
            for (int i = 1; i < 1000; i++)
                if (i % 3 == 0 || i % 5 == 0)
                    t += i;
            Console.WriteLine(t);
            System.Threading.Thread.Sleep(5000);
        }
    }
}
