using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.ThreeG, DinPacketTypes.DcNetworkEntry)]
	public class ThreeGNetworkEntryPacket : DinPacket<ThreeGNetworkEntryPacket, ThreeGNetworkEntryPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte[] ipAddress;
			[Order(1)] public byte workingMode;
			[Order(2)] public CellGlobalId cellGlobalId;
			[Order(3)] public ushort networkEntryLatency;
			[Order(4)][ExplicitSize(5)] public int[] connectedTimes;
			[Order(5)] public byte disconnectionReason;
			[Order(6)] public ThreeGNeighboringCell[] neighboringCells;
			[Order(7)] public ushort uplinkMaxBearerSpeed;
			[Order(8)] public ushort downlinkMaxBearerSpeed;
		}
		
		public ThreeGNetworkEntryPacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
