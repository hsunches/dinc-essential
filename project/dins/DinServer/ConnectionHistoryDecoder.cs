using System;

namespace DinServer
{
	public class ConnectionHistoryDecoder : PacketElementDecoder
	{
		static Func<DataDeserializer.DecodeArg, string, bool> twoGDecoder = null;
		static Func<DataDeserializer.DecodeArg, string, bool> threeGDecoder = null;
		static Func<DataDeserializer.DecodeArg, string, bool> lteDecoder = null;
		static Func<DataDeserializer.DecodeArg, string, bool> wimaxDecoder = null;
		static Func<DataDeserializer.DecodeArg, string, bool> wifiStationDecoder = null;

		internal protected override bool DecodeObject(DataDeserializer.DecodeArg arg, String name)
		{
			if (twoGDecoder == null)
			{
				twoGDecoder			= DataDeserializer.CreateObjectDecoder(typeof(TwoGConnectionHistory), false);
				threeGDecoder		= DataDeserializer.CreateObjectDecoder(typeof(ThreeGConnectionHistory), false);
				lteDecoder			= DataDeserializer.CreateObjectDecoder(typeof(LteConnectionHistory), false);
				wimaxDecoder		= DataDeserializer.CreateObjectDecoder(typeof(WimaxConnectionHistory), false);
				wifiStationDecoder	= DataDeserializer.CreateObjectDecoder(typeof(WifiStationConnectionHistory), false);
			}

			int category = ((int)arg.data[arg.offset + 4] & 0x3F) << 8;
			
			switch (category)
			{
			case (int)DinPacketCategories.TwoG:
				return twoGDecoder(arg, name);

			case (int)DinPacketCategories.ThreeG:
				return threeGDecoder(arg, name);

			case (int)DinPacketCategories.Lte:
				return lteDecoder(arg, name);

			case (int)DinPacketCategories.Wimax:
				return wimaxDecoder(arg, name);

			case (int)DinPacketCategories.WifiStation:
				return wifiStationDecoder(arg, name);
			
			default:
				return false;
			}
		}
	}
}
