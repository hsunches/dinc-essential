using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.TwoG, DinPacketTypes.DcHandover)]
	public class TwoGHandoverPacket : DinPacket<TwoGHandoverPacket, TwoGHandoverPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public ushort originalCellId;
			[Order(1)] public sbyte originalCellRssi;
			[Order(2)] public TwoGNeighboringCell[] originalNeighboringCells;
			[Order(3)] public ushort destinationCellId;
		}
		
		public TwoGHandoverPacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
