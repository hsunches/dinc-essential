using System;

namespace DinServer
{
	public class TwoGConnectionHistory : ConnectionHistory
	{	
		[Order(0)] public int time;
		[Order(1)] public byte category;
		[Order(2)] public byte type;
		[Order(3)] public TwoGSignalQualityParameters signalQualityParameters;
		
		public TwoGConnectionHistory()
		{
		}
	}
}
