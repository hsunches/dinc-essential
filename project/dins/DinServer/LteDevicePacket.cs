using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Lte, DinPacketTypes.DcDevice)]
	public class LteDevicePacket : DinPacket<LteDevicePacket, LteDevicePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)][ExplicitSize(6)] public byte[] frequencyBands;
		}
		
		public LteDevicePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
