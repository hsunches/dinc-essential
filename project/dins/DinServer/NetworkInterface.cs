using System;

namespace DinServer
{
	[PacketElementDecoder(typeof(NetworkInterfaceDecoder))]
	public abstract class NetworkInterface
	{	
		public NetworkInterface ()
		{
		}
	}
}
