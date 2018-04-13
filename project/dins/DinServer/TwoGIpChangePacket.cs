using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.TwoG, DinPacketTypes.DcIpChange)]
	public class TwoGIpChangePacket : IpChangePacket
	{		
		public TwoGIpChangePacket()
		{
		}
	}
}
