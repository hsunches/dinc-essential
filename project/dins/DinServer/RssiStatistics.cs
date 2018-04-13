using System;

namespace DinServer
{
	public class RssiStatistics
	{
		[Order(0)] public sbyte maximumRssi;
		[Order(1)] public sbyte minimumRssi;
		[Order(2)] public sbyte averageRssi;
		[Order(3)] public ushort standardDeviationBelowAverageRssi;
		[Order(4)] public ushort standardDeviationAboveAverageRssi;
		
		public RssiStatistics()
		{
		}
	}
}
