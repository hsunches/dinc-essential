using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.WifiStation, DinPacketTypes.DcDevice)]
	public class WifiStationDevicePacket : DinPacket<WifiStationDevicePacket, WifiStationDevicePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)][ExplicitSize(2)] public byte[] countryCode;
			[Order(1)] public byte supportedFrequencyBands;
			[Order(2)] public byte supportedModes;
			[Order(3)] public byte supportedEncryptions;
		}
		
		public WifiStationDevicePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
