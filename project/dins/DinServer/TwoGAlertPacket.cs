using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.TwoG, DinPacketTypes.DcAlert)]
	public class TwoGAlertPacket : AlertPacket
	{		
		public TwoGAlertPacket()
		{
		}
	}
}
