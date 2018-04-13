using System;

namespace DinServer
{
	public class HandoverStatistics
	{
		[Order(0)] public byte handoverSuccessCount;
		[Order(1)] public byte handoverFailCount;
		[Order(2)] public ushort averageHandoverLatency;
		
		public HandoverStatistics()
		{
		}
	}
}
