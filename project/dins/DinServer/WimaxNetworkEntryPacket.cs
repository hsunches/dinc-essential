using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Wimax, DinPacketTypes.DcNetworkEntry)]
	public class WimaxNetworkEntryPacket : DinPacket<WimaxNetworkEntryPacket, WimaxNetworkEntryPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte[] ipAddress;
			[Order(1)][ExplicitSize(6)] public byte[] bsId;
			[Order(2)] public ushort networkEntryLatency;
			[Order(3)][ExplicitSize(5)] public int[] connectedTimes;
			[Order(4)] public byte disconnectionReason;
			[Order(5)] public WimaxNeighboringCell[] neighboringCells;
			[Order(6)] public ushort uplinkMaxServiceFlowSpeed;
			[Order(7)] public ushort downlinkMaxServiceFlowSpeed;
		}
		
		public WimaxNetworkEntryPacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
