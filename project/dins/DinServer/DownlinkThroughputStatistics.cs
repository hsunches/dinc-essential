using System;

namespace DinServer
{
	public class DownlinkThroughputStatistics
	{
		[Order(0)] public ushort maximumDownlinkThroughput;
		[Order(1)] public ushort minimumDownlinkThroughput;
		[Order(2)] public ushort averageDownlinkThroughput;
		[Order(3)] public ushort standardDeviationBelowAverageDownlinkThroughput;
		[Order(4)] public ushort standardDeviationAboveAverageDownlinkThroughput;
		
		public DownlinkThroughputStatistics()
		{
		}
	}
}
