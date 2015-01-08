using System;
using System.Threading;

namespace ClientTester
{
	class MainClass
	{

		public static void Main (string[] args)
		{
			tcpServer ts = new tcpServer ();
			ts.start ();

			Thread.Sleep (5000);

			Console.WriteLine ("Hello World!");
		}
	}
}
