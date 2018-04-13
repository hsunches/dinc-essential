using System;

namespace DinServer
{
	public class ThreeGNeighboringCell
	{
		[Order(0)] public CellGlobalId cellGlobalId;
		[Order(1)] public ThreeGSignalQualityParameters signalQualityParameters;
		
		public ThreeGNeighboringCell()
		{
		}
	}
}
