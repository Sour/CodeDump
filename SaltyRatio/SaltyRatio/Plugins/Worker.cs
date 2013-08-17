using System;
using System.Threading;
using System.Windows.Forms;

namespace SaltyRatio.Plugins
{
    class Worker
    {
        public void doWork()
        {
            itr = 0;
            while (!_shouldStop)
            {
                Console.WriteLine("worker thread: working...");
                Thread.Sleep(1000);
                itr++;
            }
            Console.WriteLine("worker thread: terminating gracefully.");
        }
        public void requestStop()
        {
            _shouldStop = true;
        }
        private volatile bool _shouldStop;
        public int itr;
    }
}
