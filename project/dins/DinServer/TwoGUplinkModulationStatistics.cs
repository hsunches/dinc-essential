using System;

namespace DinServer
{
	public class TwoGUplinkModulationStatistics
	{
		[Order(0)] public byte uplinkGmskCount;
		[Order(1)] public byte uplink8pskCount;
		
		public TwoGUplinkModulationStatistics()
		{
		}
	}
}
