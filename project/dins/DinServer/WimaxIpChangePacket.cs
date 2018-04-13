using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Wimax, DinPacketTypes.DcIpChange)]
	public class WimaxIpChangePacket : IpChangePacket
	{		
		public WimaxIpChangePacket()
		{
		}
	}
}
