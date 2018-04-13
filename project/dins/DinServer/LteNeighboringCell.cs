using System;

namespace DinServer
{
	public class LteNeighboringCell
	{
		[Order(0)] public LteCellGlobalId cellGlobalId;
		[Order(1)] public LteSignalQualityParameters signalQualityParameters;
		
		public LteNeighboringCell()
		{
		}
	}
}
