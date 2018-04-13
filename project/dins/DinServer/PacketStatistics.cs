using System;

namespace DinServer
{
	public class PacketStatistics
	{
		[Order(0)] public ushort txPacketCount;
		[Order(1)] public ushort rxPacketCount;
		[Order(2)] public byte txPacketErrorRate;
		[Order(3)] public byte rxPacketErrorRate;
		
		public PacketStatistics()
		{
		}
	}
}
