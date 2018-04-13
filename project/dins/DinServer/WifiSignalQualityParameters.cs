using System;

namespace DinServer
{
	public class WifiSignalQualityParameters : SignalQualityParameters
	{
		[Order(0)] public sbyte rssi;
		
		public WifiSignalQualityParameters()
		{
		}
	}
}
