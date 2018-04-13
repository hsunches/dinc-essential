using System;

namespace DinServer
{
	public class WimaxSignalQualityParameters : SignalQualityParameters
	{
		[Order(0)] public sbyte rssi;
		[Order(1)] public sbyte cinrR3;
		[Order(2)] public sbyte cinrR1;
		
		public WimaxSignalQualityParameters()
		{
		}
	}
}
