using System;

namespace DinServer
{
	public class RxqualStatistics
	{
		[Order(0)] public byte maximumRxqual;
		[Order(1)] public byte minimumRxqual;
		[Order(2)] public byte averageRxqual;
		[Order(3)] public ushort standardDeviationBelowAverageRxqual;
		[Order(4)] public ushort standardDeviationAboveAverageRxqual;
		
		public RxqualStatistics()
		{
		}
	}
}
