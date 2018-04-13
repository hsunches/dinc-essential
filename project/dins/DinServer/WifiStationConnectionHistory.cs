using System;

namespace DinServer
{
	public class WifiStationConnectionHistory : ConnectionHistory
	{	
		[Order(0)] public int time;
		[Order(1)] public byte category;
		[Order(2)] public byte type;
		[Order(3)] public WifiSignalQualityParameters signalQualityParameters;
		
		public WifiStationConnectionHistory()
		{
		}
	}
}
