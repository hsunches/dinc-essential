using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Wimax, DinPacketTypes.DcHandover)]
	public class WimaxHandoverPacket : DinPacket<WimaxHandoverPacket, WimaxHandoverPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)][ExplicitSize(6)] public byte[] originalBsId;
			[Order(1)] public sbyte originalCellRssi;
			[Order(2)] public WimaxNeighboringCell[] originalNeighboringCells;
			[Order(3)][ExplicitSize(6)] public byte[] destinationBsId;
		}
		
		public WimaxHandoverPacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
