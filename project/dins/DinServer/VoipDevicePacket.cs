using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Voip, DinPacketTypes.DcDevice)]
	public class VoipDevicePacket : DinPacket<VoipDevicePacket, VoipDevicePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public string vendor;
			[Order(1)] public byte socketCount;
		}
		
		public VoipDevicePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
