using System;
using System.Reflection;

namespace DinServer
{
	[AttributeUsage(AttributeTargets.Class, Inherited = true, AllowMultiple = false)]
	public class PacketElementDecoderAttribute : Attribute
	{
		public PacketElementDecoder DecoderInstance { get; private set; }
		
		public PacketElementDecoderAttribute(Type packetElementDecoderType)
		{
			if (!packetElementDecoderType.IsSubclassOf(typeof(PacketElementDecoder)))
			{
				throw new Exception(String.Format("{0} is not a subclass of {1}", packetElementDecoderType, typeof(PacketElementDecoder)));
			}
			
			if (packetElementDecoderType.IsAbstract)
			{
				throw new Exception(String.Format("{0} is a abstract class", packetElementDecoderType));
			}
			
			ConstructorInfo constructor = packetElementDecoderType.GetConstructor(Type.EmptyTypes);
			
			if (constructor == null)
			{
				throw new Exception(String.Format("{0} does not have constructor", packetElementDecoderType));
			}
			
			this.DecoderInstance = constructor.Invoke(null) as PacketElementDecoder;
		}
	}
}
