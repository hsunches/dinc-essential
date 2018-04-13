using System;

namespace DinServer
{
	public class LteSignalQualityParameters : SignalQualityParameters
	{
		[Order(0)] public sbyte rssi;
		[Order(1)] public sbyte rsrp;
		[Order(2)] public sbyte rsrq;
		
		public LteSignalQualityParameters()
		{
		}
	}
}
