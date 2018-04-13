using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.ThreeG, DinPacketTypes.DcHandover)]
	public class ThreeGHandoverPacket : DinPacket<ThreeGHandoverPacket, ThreeGHandoverPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public ushort originalCellId;
			[Order(1)] public ushort originalLac;
			[Order(2)] public sbyte originalCellRssi;
			[Order(3)] public ThreeGNeighboringCell[] originalNeighboringCells;
			[Order(4)] public ushort destinationCellId;
			[Order(5)] public ushort destinationLac;
		}
		
		public ThreeGHandoverPacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
