using System;

namespace DinServer
{
	public class WimaxConnectionHistory : ConnectionHistory
	{	
		[Order(0)] public int time;
		[Order(1)] public byte category;
		[Order(2)] public byte type;
		[Order(3)] public WimaxSignalQualityParameters signalQualityParameters;
		
		public WimaxConnectionHistory()
		{
		}
	}
}
