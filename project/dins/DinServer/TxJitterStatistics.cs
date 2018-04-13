using System;

namespace DinServer
{
	public class TxJitterStatistics
	{
		[Order(0)] public ushort maximumTxJitter;
		[Order(1)] public ushort minimumTxJitter;
		[Order(2)] public ushort averageTxJitter;
		[Order(3)] public ushort standardDeviationBelowAverageTxJitter;
		[Order(4)] public ushort standardDeviationAboveAverageTxJitter;
		
		public TxJitterStatistics()
		{
		}
	}
}
