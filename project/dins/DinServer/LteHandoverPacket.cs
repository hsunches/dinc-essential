using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Lte, DinPacketTypes.DcHandover)]
	public class LteHandoverPacket : DinPacket<LteHandoverPacket, LteHandoverPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public uint originalCellId;
			[Order(1)] public sbyte originalCellRssi;
			[Order(2)] public LteNeighboringCell[] originalNeighboringCells;
			[Order(3)] public uint destinationCellId;
		}
		
		public LteHandoverPacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
