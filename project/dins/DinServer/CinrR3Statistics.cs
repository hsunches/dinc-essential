using System;

namespace DinServer
{
	public class CinrR3Statistics
	{
		[Order(0)] public sbyte maximumCinrR3;
		[Order(1)] public sbyte minimumCinrR3;
		[Order(2)] public sbyte averageCinrR3;
		[Order(3)] public ushort standardDeviationBelowAverageCinrR3;
		[Order(4)] public ushort standardDeviationAboveAverageCinrR3;
		
		public CinrR3Statistics()
		{
		}
	}
}
