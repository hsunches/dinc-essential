using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Wimax, DinPacketTypes.DcDevice)]
	public class WimaxDevicePacket : DinPacket<WimaxDevicePacket, WimaxDevicePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte frequencyBands;
		}
		
		public WimaxDevicePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
