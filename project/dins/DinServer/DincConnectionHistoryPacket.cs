using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Dinc, DinPacketTypes.DincConnectionHistory)]
	public class DincConnectionHistoryPacket : DinPacket<DincConnectionHistoryPacket, DincConnectionHistoryPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public ConnectionHistory[] connectionHistory;
		}
		
		public DincConnectionHistoryPacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
