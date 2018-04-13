using System;

namespace DinServer
{
	[PacketElementDecoder(typeof(ConnectionHistoryDecoder))]
	public abstract class ConnectionHistory
	{	
		public ConnectionHistory()
		{
		}
	}
}
