using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.TwoG, DinPacketTypes.DcPerformance)]
	public class TwoGPerformancePacket : DinPacket<TwoGPerformancePacket, TwoGPerformancePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte[] ipAddress;
			[Order(1)] public byte workingMode;
			[Order(2)] public ushort cellId;
			[Order(3)] public ushort arfcn;
			[Order(4)] public RssiStatistics rssiStatistics;
			[Order(5)] public RxqualStatistics rxqualStatistics;
			[Order(6)] public TwoGUplinkModulationStatistics uplinkModulationStatistics;
			[Order(7)] public TwoGDownlinkModulationStatistics downlinkModulationStatistics;
			[Order(8)] public UplinkThroughputStatistics uplinkThroughputStatistics;
			[Order(9)] public DownlinkThroughputStatistics downlinkThroughputStatistics;
			[Order(10)] public PacketStatistics packetStatistics;
			[Order(11)] public FrameStatistics frameStatistics;
			[Order(12)] public HandoverStatistics handoverStatistics;
			[Order(13)] public sbyte txPower;
			[Order(14)] public DeviceStatus deviceStatus;
			[Order(15)] public byte activatedTime;
			[Order(16)] public ushort reportLatency;
		}
		
		public TwoGPerformancePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
