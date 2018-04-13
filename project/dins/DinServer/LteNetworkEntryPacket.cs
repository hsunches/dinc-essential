using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Lte, DinPacketTypes.DcNetworkEntry)]
	public class LteNetworkEntryPacket : DinPacket<LteNetworkEntryPacket, LteNetworkEntryPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte[] ipAddress;
			[Order(1)] public LteCellGlobalId cellGlobalId;
			[Order(2)] public ushort networkEntryLatency;
			[Order(3)][ExplicitSize(5)] public int[] connectedTimes;
			[Order(4)] public byte disconnectionReason;
			[Order(5)] public LteNeighboringCell[] neighboringCells;
			[Order(6)] public ushort uplinkMaxBearerSpeed;
			[Order(7)] public ushort downlinkMaxBearerSpeed;
		}
		
		public LteNetworkEntryPacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
