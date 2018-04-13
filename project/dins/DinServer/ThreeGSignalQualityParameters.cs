using System;

namespace DinServer
{
	public class ThreeGSignalQualityParameters : SignalQualityParameters
	{
		[Order(0)] public sbyte rssi;
		[Order(1)] public sbyte rscp;
		
		public ThreeGSignalQualityParameters()
		{
		}
	}
}
