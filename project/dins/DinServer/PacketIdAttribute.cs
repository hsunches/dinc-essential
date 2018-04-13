using System;

namespace DinServer
{
	[AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = true)]
	public class PacketIdAttribute : Attribute
	{
		public DinPacketCategories Category { get; private set; }
		public DinPacketTypes Type { get; private set; }

		public int Id
		{
			get { return (int)Category | (int)Type; }
		}
		
		public PacketIdAttribute(DinPacketCategories category, DinPacketTypes type)
		{
			this.Category = category;
			this.Type = type;
		}
	}
}
