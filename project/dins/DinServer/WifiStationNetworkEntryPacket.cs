using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.WifiStation, DinPacketTypes.DcNetworkEntry)]
	public class WifiStationNetworkEntryPacket : DinPacket<WifiStationNetworkEntryPacket, WifiStationNetworkEntryPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte workingFrequencyBand;
			[Order(1)] public byte workingMode;
			[Order(2)] public byte workingEncryption;
			[Order(3)] public byte workingChannel;
			[Order(4)][ExplicitSize(6)] public byte[] apBssid;
			[Order(5)] public string ssid;
			[Order(6)] public WifiNeighboringAp[] neighboringAps;
		}
		
		public WifiStationNetworkEntryPacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
