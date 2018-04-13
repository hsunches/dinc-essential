using System;

namespace DinServer
{
	public class DownlinkModulationStatistics
	{
		[Order(0)] public byte downlinkQpskCount;
		[Order(1)] public byte downlink16QamCount;
		[Order(2)] public byte downlink64QamCount;
		
		public DownlinkModulationStatistics()
		{
		}
	}
}
