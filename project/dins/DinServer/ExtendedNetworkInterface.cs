using System;

namespace DinServer
{
	public class ExtendedNetworkInterface : NetworkInterface
	{
		[Order(0)] public byte type;
		[Order(1)][ExplicitSize(6)] public byte[] macAddress;
		[Order(2)] public ulong imsi;
		[Order(3)] public ulong imei;

		public ExtendedNetworkInterface()
		{
		}
	}
}
