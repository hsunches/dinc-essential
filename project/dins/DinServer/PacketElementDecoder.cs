using System;

namespace DinServer
{
	public abstract class PacketElementDecoder
	{
		public PacketElementDecoder()
		{
		}
		
		internal protected abstract bool DecodeObject(DataDeserializer.DecodeArg arg, String name);
	}
}
