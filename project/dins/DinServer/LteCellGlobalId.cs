using System;

namespace DinServer
{
	public class LteCellGlobalId
	{
		[Order(0)] public uint cellId;
		[Order(1)] public ushort mcc;
		[Order(2)] public string mnc;
		[Order(3)] public ushort lac;

		public LteCellGlobalId ()
		{
		}
	}
}

