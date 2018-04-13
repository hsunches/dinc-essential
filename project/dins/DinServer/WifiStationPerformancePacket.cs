using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.WifiStation, DinPacketTypes.DcPerformance)]
	public class WifiStationPerformancePacket : DinPacket<WifiStationPerformancePacket, WifiStationPerformancePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public RssiStatistics rssiStatistics;
			[Order(1)] public UplinkThroughputStatistics uplinkThroughputStatistics;
			[Order(2)] public DownlinkThroughputStatistics downlinkThroughputStatistics;
			[Order(3)] public ushort txFragmentSuccessCount;
			[Order(4)] public ushort rxFragmentSuccessCount;
			[Order(5)] public ushort txFrameRetryCount;
			[Order(6)] public ushort txAckLossCount;
			[Order(7)] public ushort rxFrameFcsErrorCount;
			[Order(8)] public sbyte txPower;
			[Order(9)] public DeviceStatus deviceStatus;
			[Order(10)] public byte activatedTime;
			[Order(11)] public ushort reportLatency;
		}
		
		public WifiStationPerformancePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
