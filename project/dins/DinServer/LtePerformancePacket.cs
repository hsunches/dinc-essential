using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Lte, DinPacketTypes.DcPerformance)]
	public class LtePerformancePacket : DinPacket<LtePerformancePacket, LtePerformancePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte[] ipAddress;
			[Order(1)] public uint cellId;
			[Order(2)] public uint uplinkEarfcn;
			[Order(3)] public uint downlinkEarfcn;
			[Order(4)] public byte channelBandwidth;
			[Order(5)] public RssiStatistics rssiStatistics;
			[Order(6)] public RsrpStatistics rsrpStatistics;
			[Order(7)] public RsrqStatistics rsrqStatistics;
			[Order(8)] public CqiStatistics cqiStatistics;
			[Order(9)] public UplinkModulationStatistics uplinkModulationStatistics;
			[Order(10)] public DownlinkModulationStatistics downlinkModulationStatistics;
			[Order(11)] public UplinkThroughputStatistics uplinkThroughputStatistics;
			[Order(12)] public DownlinkThroughputStatistics downlinkThroughputStatistics;
			[Order(13)] public PacketStatistics packetStatistics;
			[Order(14)] public FrameStatistics frameStatistics;
			[Order(15)] public HandoverStatistics handoverStatistics;
			[Order(16)] public sbyte txPower;
			[Order(17)] public DeviceStatus deviceStatus;
			[Order(18)] public byte activatedTime;
			[Order(19)] public ushort reportLatency;
			[Order(20)] public SubCarrierInfo[] subCarrierInfo;
		}
		
		public LtePerformancePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
