using System;

namespace PINServer
{
	[AttributeUsage(AttributeTargets.Field, AllowMultiple = false, Inherited = true)]
	public class DecimalDigitalAttribute : Attribute
	{
		public TypeCode MappedType { get; private set; }
		public double Digital { get; private set; }
		
		public DecimalDigitalAttribute(Type mappedType, double digital)
		{
			this.MappedType = Type.GetTypeCode(mappedType);
			this.Digital = digital;
		}
	}
}

