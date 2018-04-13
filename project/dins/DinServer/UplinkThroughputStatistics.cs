using System;

namespace DinServer
{
	public class UplinkThroughputStatistics
	{
		[Order(0)] public ushort maximumUplinkThroughput;
		[Order(1)] public ushort minimumUplinkThroughput;
		[Order(2)] public ushort averageUplinkThroughput;
		[Order(3)] public ushort standardDeviationBelowAverageUplinkThroughput;
		[Order(4)] public ushort standardDeviationAboveAverageUplinkThroughput;
		
		public UplinkThroughputStatistics()
		{
		}
	}
}
