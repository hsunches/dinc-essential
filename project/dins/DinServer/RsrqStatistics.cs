using System;

namespace DinServer
{
	public class RsrqStatistics
	{
		[Order(0)] public sbyte maximumRsrq;
		[Order(1)] public sbyte minimumRsrq;
		[Order(2)] public sbyte averageRsrq;
		[Order(3)] public ushort standardDeviationBelowAverageRsrq;
		[Order(4)] public ushort standardDeviationAboveAverageRsrq;
		
		public RsrqStatistics()
		{
		}
	}
}
