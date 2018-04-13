using System;

namespace DinServer
{
	public class CinrR1Statistics
	{
		[Order(0)] public sbyte maximumCinrR1;
		[Order(1)] public sbyte minimumCinrR1;
		[Order(2)] public sbyte averageCinrR1;
		[Order(3)] public ushort standardDeviationBelowAverageCinrR1;
		[Order(4)] public ushort standardDeviationAboveAverageCinrR1;
		
		public CinrR1Statistics()
		{
		}
	}
}
