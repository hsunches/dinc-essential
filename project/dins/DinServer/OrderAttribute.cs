using System;

namespace DinServer
{
	[AttributeUsage(AttributeTargets.Field, AllowMultiple = false, Inherited = true)]
	public class OrderAttribute : Attribute
	{
		public int Order { get; private set; }
		
		public OrderAttribute(int order)
		{
			this.Order = order;
		}
	}
}

