using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.ThreeG, DinPacketTypes.DcAlert)]
	public class ThreeGAlertPacket : AlertPacket
	{		
		public ThreeGAlertPacket()
		{
		}
	}
}
