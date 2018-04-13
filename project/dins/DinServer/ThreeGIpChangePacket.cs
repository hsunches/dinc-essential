using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.ThreeG, DinPacketTypes.DcIpChange)]
	public class ThreeGIpChangePacket : IpChangePacket
	{
		public ThreeGIpChangePacket()
		{
		}
	}
}
