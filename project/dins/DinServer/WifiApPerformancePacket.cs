using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.WifiAp, DinPacketTypes.DcPerformance)]
	public class WifiApPerformancePacket : DinPacket<WifiApPerformancePacket, WifiApPerformancePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte workingFrequencyBands;
			[Order(1)] public byte workingModes;
			[Order(2)] public byte[] workingChannels;
			[Order(3)] public SsidConfiguration[] ssidConfigurations;
			[Order(4)] public byte[] wanIpAddress;
			[Order(5)] public WifiClient[] wifiClients;
			[Order(6)] public LanUplinkThroughputStatistics lanUplinkThroughputStatistics;
			[Order(7)] public LanDownlinkThroughputStatistics lanDownlinkThroughputStatistics;
			[Order(8)] public ushort txFragmentSuccessCount;
			[Order(9)] public ushort rxFragmentSuccessCount;
			[Order(10)] public ushort txFrameRetryCount;
			[Order(11)] public ushort txAckLossCount;
			[Order(12)] public ushort rxFrameFcsErrorCount;
			[Order(13)] public sbyte txPower;
			[Order(14)] public byte reportInterval;
		}
		
		public WifiApPerformancePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
