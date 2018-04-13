using System;

namespace DinServer
{
	public class CellGlobalId
	{
		[Order(0)] public ushort cellId;
		[Order(1)] public ushort mcc;
		[Order(2)] public string mnc;
		[Order(3)] public ushort lac;
		
		public CellGlobalId()
		{
		}
	}
}
