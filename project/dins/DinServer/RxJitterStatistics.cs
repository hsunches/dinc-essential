using System;

namespace DinServer
{
	public class RxJitterStatistics
	{
		[Order(0)] public ushort maximumRxJitter;
		[Order(1)] public ushort minimumRxJitter;
		[Order(2)] public ushort averageRxJitter;
		[Order(3)] public ushort standardDeviationBelowAverageRxJitter;
		[Order(4)] public ushort standardDeviationAboveAverageRxJitter;
		
		public RxJitterStatistics()
		{
		}
	}
}
