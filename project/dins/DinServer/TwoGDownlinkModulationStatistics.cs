using System;

namespace DinServer
{
	public class TwoGDownlinkModulationStatistics
	{
		[Order(0)] public byte downlinkGmskCount;
		[Order(1)] public byte downlink8pskCount;
		
		public TwoGDownlinkModulationStatistics()
		{
		}
	}
}
