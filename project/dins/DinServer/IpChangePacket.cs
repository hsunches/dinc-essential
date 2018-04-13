using System;

namespace DinServer
{
	public class IpChangePacket : DinPacket<IpChangePacket, IpChangePacket.BodyFormat>
	{
		public class BodyFormat
		{
			[OrderAttribute(0)] public byte[] originalIpAddress;
			[OrderAttribute(1)] public byte[] destinationIpAddress;
		}
		
		public IpChangePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
