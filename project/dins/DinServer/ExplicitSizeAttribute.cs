using System;

namespace DinServer
{
	[AttributeUsage(AttributeTargets.Field, AllowMultiple = false, Inherited = true)]
	public class ExplicitSizeAttribute : Attribute
	{
		public int Size { get; private set; }
		
		public ExplicitSizeAttribute(int size)
		{
			this.Size = size;
		}
	}
}
