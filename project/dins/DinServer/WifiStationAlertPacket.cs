using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.WifiStation, DinPacketTypes.DcAlert)]
	public class WifiStationAlertPacket : AlertPacket
	{		
		public WifiStationAlertPacket()
		{
		}
	}
}
