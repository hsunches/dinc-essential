using System;

namespace DinServer
{
	public class LanDownlinkThroughputStatistics
	{
		[Order(0)][MsbSize(2)] public Int32 maximumDownlinkThroughput;
		[Order(1)][MsbSize(2)] public Int32 minimumDownlinkThroughput;
		[Order(2)][MsbSize(2)] public Int32 averageDownlinkThroughput;
		[Order(3)][MsbSize(2)] public Int32 standardDeviationBelowAverageDownlinkThroughput;
		[Order(4)][MsbSize(2)] public Int32 standardDeviationAboveAverageDownlinkThroughput;
		
		public LanDownlinkThroughputStatistics()
		{
		}
	}
}
