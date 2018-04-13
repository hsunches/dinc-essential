using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.ThreeG, DinPacketTypes.DcPerformance)]
	public class ThreeGPerformancePacket : DinPacket<ThreeGPerformancePacket, ThreeGPerformancePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte[] ipAddress;
			[Order(1)] public byte workingMode;
			[Order(2)] public ushort cellId;
			[Order(3)] public ushort lac;
			[Order(4)] public ushort uplinkUarfcn;
			[Order(5)] public ushort downlinkUarfcn;
			[Order(6)] public byte channelBandwidth;
			[Order(7)] public RssiStatistics rssiStatistics;
			[Order(8)] public RscpStatistics rscpStatistics;
			[Order(9)] public CqiStatistics cqiStatistics;
			[Order(10)] public UplinkModulationStatistics uplinkModulationStatistics;
			[Order(11)] public DownlinkModulationStatistics downlinkModulationStatistics;
			[Order(12)] public UplinkThroughputStatistics uplinkThroughputStatistics;
			[Order(13)] public DownlinkThroughputStatistics downlinkThroughputStatistics;
			[Order(14)] public PacketStatistics packetStatistics;
			[Order(15)] public FrameStatistics frameStatistics;
			[Order(16)] public HandoverStatistics handoverStatistics;
			[Order(17)] public sbyte txPower;
			[Order(18)] public DeviceStatus deviceStatus;
			[Order(19)] public byte activatedTime;
			[Order(20)] public ushort reportLatency;
		}
		
		public ThreeGPerformancePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
