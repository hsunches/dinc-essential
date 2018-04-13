using System;

namespace DinServer
{
	public class SsidConfiguration
	{
		[Order(0)] public string ssid;
		[Order(1)] public byte encryption;
		
		public SsidConfiguration()
		{
		}
	}
}
