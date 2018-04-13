using System;

namespace DinServer
{
	public class RsrpStatistics
	{
		[Order(0)] public sbyte maximumRsrp;
		[Order(1)] public sbyte minimumRsrp;
		[Order(2)] public sbyte averageRsrp;
		[Order(3)] public ushort standardDeviationBelowAverageRsrp;
		[Order(4)] public ushort standardDeviationAboveAverageRsrp;
		
		public RsrpStatistics()
		{
		}
	}
}
