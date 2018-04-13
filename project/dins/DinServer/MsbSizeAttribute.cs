using System;

namespace DinServer
{
	[AttributeUsage(AttributeTargets.Field, AllowMultiple = false, Inherited = true)]
	public class MsbSizeAttribute : Attribute
	{
		public int Size { get; private set; }
		
		public MsbSizeAttribute(int size)
		{
			this.Size = size;
		}
	}
}
