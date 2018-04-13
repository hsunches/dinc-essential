using System;

namespace DinServer
{
	public class WifiClient
	{
		[Order(0)][ExplicitSize(6)] public byte[] bssid;
		
		public WifiClient()
		{
		}
	}
}
