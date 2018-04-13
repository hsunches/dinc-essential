using System;

namespace DinServer
{
	public class FrameStatistics
	{
		[Order(0)] public ushort txFrameCount;
		[Order(1)] public ushort rxFrameCount;
		[Order(2)] public byte txFrameErrorRate;
		[Order(3)] public byte rxFrameErrorRate;
		
		public FrameStatistics()
		{
		}
	}
}
