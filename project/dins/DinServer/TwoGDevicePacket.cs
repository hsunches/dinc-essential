using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.TwoG, DinPacketTypes.DcDevice)]
	public class TwoGDevicePacket : DinPacket<TwoGDevicePacket, TwoGDevicePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)][ExplicitSize(2)] public byte[] frequencyBands;
		}
		
		public TwoGDevicePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
