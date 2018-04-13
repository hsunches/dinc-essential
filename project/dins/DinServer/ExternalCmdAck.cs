using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Device, DinPacketTypes.DincExtCmdAck)]
	public class ExternalCmdAck : DinPacket<ExternalCmdAck, ExternalCmdAck.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte prefix;
			[Order(1)] public byte dcId;
			[Order(2)] public byte cmdType;
			[Order(3)] public byte ack;
			[Order(4)] public int value;
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
