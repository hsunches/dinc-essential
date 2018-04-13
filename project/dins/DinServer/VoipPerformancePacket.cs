using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Voip, DinPacketTypes.DcPerformance)]
	public class VoipPerformancePacket : DinPacket<VoipPerformancePacket, VoipPerformancePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte socketIndex;
			[Order(1)] public UplinkThroughputStatistics uplinkThroughputStatistics;
			[Order(2)] public DownlinkThroughputStatistics downlinkThroughputStatistics;
			[Order(3)] public PacketStatistics packetStatistics;
			[Order(4)] public TxJitterStatistics txJitterStatistics;
			[Order(5)] public RxJitterStatistics rxJitterStatistics;
			[Order(6)] public byte reportInterval;
			[Order(7)] public ushort roundTripTime;
		}
		
		public VoipPerformancePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
