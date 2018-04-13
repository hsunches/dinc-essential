using System;

namespace DinServer
{
	public class LteConnectionHistory : ConnectionHistory
	{	
		[Order(0)] public int time;
		[Order(1)] public byte category;
		[Order(2)] public byte type;
		[Order(3)] public LteSignalQualityParameters signalQualityParameters;
		
		public LteConnectionHistory()
		{
		}
	}
}
