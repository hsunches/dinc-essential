using System;

namespace DinServer
{
	public class LanUplinkThroughputStatistics
	{
		[Order(0)][MsbSize(2)] public Int32 maximumUplinkThroughput;
		[Order(1)][MsbSize(2)] public Int32 minimumUplinkThroughput;
		[Order(2)][MsbSize(2)] public Int32 averageUplinkThroughput;
		[Order(3)][MsbSize(2)] public Int32 standardDeviationBelowAverageUplinkThroughput;
		[Order(4)][MsbSize(2)] public Int32 standardDeviationAboveAverageUplinkThroughput;
		
		public LanUplinkThroughputStatistics()
		{
		}
	}
}
