using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Lte, DinPacketTypes.DcIpChange)]
	public class LteIpChangePacket : IpChangePacket
	{
		public LteIpChangePacket()
		{
		}
	}
}
