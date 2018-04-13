using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Lte, DinPacketTypes.DcAlert)]
	public class LteAlertPacket : AlertPacket
	{
		public LteAlertPacket()
		{
		}
	}
}
