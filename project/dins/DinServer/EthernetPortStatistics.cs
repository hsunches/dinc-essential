using System;

namespace DinServer
{
	public class EthernetPortStatistics
	{
		[Order(0)] public byte portIndex;
		[Order(1)] public byte portSpeed;
		[Order(2)] public LanUplinkThroughputStatistics lanUplinkThroughputStatistics;
		[Order(3)] public LanDownlinkThroughputStatistics lanDownlinkThroughputStatistics;
		[Order(4)] public PacketStatistics packetStatistics;
		[Order(5)] public FrameStatistics frameStatistics;
		
		public EthernetPortStatistics()
		{
		}
	}
}
