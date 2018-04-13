using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Wimax, DinPacketTypes.DcAlert)]
	public class WimaxAlertPacket : AlertPacket
	{		
		public WimaxAlertPacket()
		{
		}
	}
}
