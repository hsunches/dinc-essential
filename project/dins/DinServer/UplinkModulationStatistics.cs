using System;

namespace DinServer
{
	public class UplinkModulationStatistics
	{
		[Order(0)] public byte uplinkQpskCount;
		[Order(1)] public byte uplink16QamCount;
		[Order(2)] public byte uplink64QamCount;
		
		public UplinkModulationStatistics()
		{
		}
	}
}
