using System;

namespace DinServer
{
	public class DeviceStatus
	{
		[Order(0)] public sbyte deviceTemperature;
		[Order(1)] public sbyte batteryTemperature;
		[Order(2)] public byte batteryLevel;
		[Order(3)] public byte averageCpuUsage;
		[Order(4)] public byte averageMemoryUsage;
		
		public DeviceStatus()
		{
		}
	}
}
