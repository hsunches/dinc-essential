using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Voip, DinPacketTypes.DcCall)]
	public class VoipCallPacket : DinPacket<VoipCallPacket, VoipCallPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte socketIndex;
			[Order(1)] public byte callState;
			[Order(2)] public int startTime;
			[Order(3)] public int terminationTime;
			[Order(4)] public UInt16 terminationReason;
			[Order(5)] public byte codec;
			[Order(6)] public byte[] remoteIpAddress;
			[Order(7)] public ushort remotePort;

		}
		
		public VoipCallPacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
