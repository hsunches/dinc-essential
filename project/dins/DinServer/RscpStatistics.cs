using System;

namespace DinServer
{
	public class RscpStatistics
	{
		[Order(0)] public sbyte maximumRscp;
		[Order(1)] public sbyte minimumRscp;
		[Order(2)] public sbyte averageRscp;
		[Order(3)] public ushort standardDeviationBelowAverageRscp;
		[Order(4)] public ushort standardDeviationAboveAverageRscp;
		
		public RscpStatistics()
		{
		}
	}
}
