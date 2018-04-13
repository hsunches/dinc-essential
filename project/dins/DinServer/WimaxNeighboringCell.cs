using System;

namespace DinServer
{
	public class WimaxNeighboringCell
	{
		[Order(0)][ExplicitSize(6)] public byte[] bsId;
		[Order(1)] public WimaxSignalQualityParameters signalQualityParameters;
		
		public WimaxNeighboringCell()
		{
		}
	}
}
