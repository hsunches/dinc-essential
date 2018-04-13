using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Ethernet, DinPacketTypes.DcPerformance)]
	public class EthernetPortStatisticsPerformancePacket : DinPacket<EthernetPortStatisticsPerformancePacket, EthernetPortStatisticsPerformancePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public EthernetPortStatistics[] portStatistics;
			[Order(1)] public byte reportInterval;
		}
		
		public EthernetPortStatisticsPerformancePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
