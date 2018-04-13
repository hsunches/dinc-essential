using System;

namespace DinServer
{
	public class CqiStatistics
	{
		[Order(0)] public byte maximumCqi;
		[Order(1)] public byte minimumCqi;
		[Order(2)] public byte averageCqi;
		[Order(3)] public ushort standardDeviationBelowAverageCqi;
		[Order(4)] public ushort standardDeviationAboveAverageCqi;
		
		public CqiStatistics()
		{
		}
	}
}
