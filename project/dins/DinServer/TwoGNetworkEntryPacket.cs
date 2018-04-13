using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.TwoG, DinPacketTypes.DcNetworkEntry)]
	public class TwoGNetworkEntryPacket : DinPacket<TwoGNetworkEntryPacket, TwoGNetworkEntryPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte[] ipAddress;
			[Order(1)] public byte workingMode;
			[Order(2)] public CellGlobalId cellGlobalId;
			[Order(3)] public ushort networkEntryLatency;
			[Order(4)][ExplicitSize(5)] public int[] connectedTimes;
			[Order(5)] public byte disconnectionReason;
			[Order(6)] public TwoGNeighboringCell[] neighboringCells;
		}
		
		public TwoGNetworkEntryPacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
