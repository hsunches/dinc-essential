using System;

namespace DinServer
{
	public class AlertPacket : DinPacket<AlertPacket, AlertPacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public byte alertTypeAndLevels;
			[Order(1)] public byte maximumCpuUsage;
			[Order(2)] public byte minimumCpuUsage;
			[Order(3)] public byte averageCpuUsage;
			[Order(4)] public byte maximumMemoryUsage;
			[Order(5)] public byte minimumMemoryUsage;
			[Order(6)] public byte averageMemoryUsage;
			[Order(7)] public sbyte deviceTemperature;
			[Order(8)] public sbyte batteryTemperature;
		}
		
		public AlertPacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}
