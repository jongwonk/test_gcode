using System;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace ClientTester
{
	public class tcpServer
	{
		private TcpClient tc = null;
		private NetworkStream ns = null;

		public tcpServer ()
		{
		}

		public void start()
		{

			IPAddress iaddr = Dns.GetHostEntry ("localhost").AddressList [0];
			IPEndPoint ipe = new IPEndPoint (iaddr, 3000);

			try{

				tc = new TcpClient();
				tc.Connect(ipe);

				ns = tc.GetStream();


			}catch(Exception ex)
			{
				Console.WriteLine (ex.Message);
			}


			Thread thread = new Thread (run);
			thread.Start();
		}

		private void run()
		{
			byte[] buf1 = ASCIIEncoding.ASCII.GetBytes ("G01 X1.001 Y0.002");
			byte[] buf2 = ASCIIEncoding.ASCII.GetBytes ("G28 X Y Z");

			if (ns == null)
				return;

			while(true)
			{
				ns.Write (buf1, 0, buf1.Length);
				ns.Flush ();
				Thread.Sleep(1000);

				ns.Write (buf2, 0, buf2.Length);
				ns.Flush ();
				Thread.Sleep(1000);

			}

		}

	}
}

