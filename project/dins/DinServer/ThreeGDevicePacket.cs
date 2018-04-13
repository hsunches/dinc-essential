using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.ThreeG, DinPacketTypes.DcDevice)]
	public class ThreeGDevicePacket : DinPacket<ThreeGDevicePacket, ThreeGDevicePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)][ExplicitSize(4)] public byte[] frequencyBands;
		}
		
		public ThreeGDevicePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
