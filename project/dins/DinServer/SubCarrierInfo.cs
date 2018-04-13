using System;

namespace DinServer
{
	public class SubCarrierInfo
	{
		[Order(0)] public int cellId;
		[Order(1)] public byte channelBandwidth;
		[Order(2)] public RsrpStatistics rsrpStatistics;
		[Order(3)] public RsrqStatistics rsrqStatistics;
		[Order(4)] public uint downlinkEarfcn;		

		public SubCarrierInfo ()
		{
		}
	}
}

