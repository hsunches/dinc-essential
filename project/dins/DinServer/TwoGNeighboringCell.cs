using System;

namespace DinServer
{
	public class TwoGNeighboringCell
	{
		[Order(0)] public CellGlobalId cellGlobalId;
		[Order(1)] public TwoGSignalQualityParameters signalQualityParameters;
		
		public TwoGNeighboringCell()
		{
		}
	}
}
