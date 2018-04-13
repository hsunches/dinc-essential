using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Wimax, DinPacketTypes.DcPerformance)]
	public class WimaxPerformancePacket : DinPacket<WimaxPerformancePacket, WimaxPerformancePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte[] ipAddress;
			[Order(1)][ExplicitSize(6)] public byte[] bsId;
			[Order(2)] public ushort frequencyIn100kHz;
			[Order(3)] public ushort bandwidth;
			[Order(4)] public RssiStatistics rssiStatistics;
			[Order(5)] public CinrR3Statistics cinrR3Statistics;
			[Order(6)] public CinrR1Statistics cinrR1Statistics;
			[Order(7)] public UplinkModulationStatistics uplinkModulationStatistics;
			[Order(8)] public DownlinkModulationStatistics downlinkModulationStatistics;
			[Order(9)] public UplinkThroughputStatistics uplinkThroughputStatistics;
			[Order(10)] public DownlinkThroughputStatistics downlinkThroughputStatistics;
			[Order(11)] public PacketStatistics packetStatistics;
			[Order(12)] public FrameStatistics frameStatistics;
			[Order(13)] public HandoverStatistics handoverStatistics;
			[Order(14)] public sbyte txPower;
			[Order(15)] public DeviceStatus deviceStatus;
			[Order(16)] public byte activatedTime;
			[Order(17)] public ushort reportLatency;
		}
		
		public WimaxPerformancePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
