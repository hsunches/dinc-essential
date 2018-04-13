using System;

namespace DinServer
{
	public class NormalNetworkInterface : NetworkInterface
	{
		[Order(0)] public byte type;
		[Order(1)][ExplicitSize(6)] public byte[] macAddress;

		public NormalNetworkInterface()
		{
		}
	}
}
