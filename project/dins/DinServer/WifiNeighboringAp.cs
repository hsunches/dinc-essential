using System;

namespace DinServer
{
	public class WifiNeighboringAp
	{
		[Order(0)][ExplicitSize(6)] public byte[] bssid;
		[Order(1)] public byte mode;
		[Order(2)] public byte encryption;
		[Order(3)] public byte channel;
		[Order(4)] public WifiSignalQualityParameters signalQualityParameters;
		
		public WifiNeighboringAp()
		{
		}
	}
}
