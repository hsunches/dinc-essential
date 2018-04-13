using System;

namespace DinServer
{
	public class TwoGSignalQualityParameters : SignalQualityParameters
	{
		[Order(0)] public sbyte rssi;
		[Order(1)] public byte rxqual;
		
		public TwoGSignalQualityParameters()
		{
		}
	}
}
