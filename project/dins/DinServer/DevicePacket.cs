using System;

namespace DinServer
{
	[PacketId(DinPacketCategories.Device, DinPacketTypes.DcDevice)]
	public class DevicePacket : DinPacket<DevicePacket, DevicePacket.BodyFormat>
	{
		public class BodyFormat {
			[Order(0)] public string vendor;
			[Order(1)] public string model;
			[Order(2)] public string firmwareVersion;
			[Order(3)] public string serialNumber;
			[Order(4)] public string chipRevision;
			[Order(5)] public byte cpuCoreCount;
			[Order(6)] public ushort cpuClock;
			[Order(7)] public ushort ramSize;
			[Order(8)] public ushort flashMemorySize;
			[Order(9)] public ushort batteryCapacity;
			[Order(10)] public byte[] usbDevices;
			[Order(11)] public NetworkInterface[] networkInterfaces;
		}
		
		public DevicePacket()
		{
		}
		
		protected override bool Decode(BodyFormat format)
		{
			throw new NotImplementedException();
		}
	}
}

