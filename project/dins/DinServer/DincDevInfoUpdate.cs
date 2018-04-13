using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Device, DinPacketTypes.DincDevInfoUpdate)]
	public class DincDevInfoUpdate: DevicePacket
	{
	}
}

