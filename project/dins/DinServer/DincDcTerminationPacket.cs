using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Dinc, DinPacketTypes.DcTermination)]
	public class DincDcTerminationPacket : DinPacket<DincDcTerminationPacket, DincDcTerminationPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public UInt32 DcId;
			[Order(1)] public Int32 StopSignal;
			[Order(1)] public Int32 TermSignal;
			[Order(1)] public Int32 ExitSignal;

		}

		public DincDcTerminationPacket ()
		{
		}

		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}

