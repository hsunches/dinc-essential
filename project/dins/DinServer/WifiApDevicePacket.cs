using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.WifiAp, DinPacketTypes.DcDevice)]
	public class WifiApDevicePacket : DinPacket<WifiApDevicePacket, WifiApDevicePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)][ExplicitSize(2)] public byte[] countryCode;
			[Order(1)] public byte supportedFrequencyBands;
			[Order(2)] public byte supportedModes;
			[Order(3)] public byte supportedEncryptions;
			[Order(4)] public WifiNeighboringAp[] neighboringAps;
		}
		
		public WifiApDevicePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
