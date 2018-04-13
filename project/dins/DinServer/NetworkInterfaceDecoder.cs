using System;

namespace DinServer
{
	public class NetworkInterfaceDecoder : PacketElementDecoder
	{
		public enum NetworkInterfaceTypes
		{
			Wifi		= 0x10,
			TwoG		= 0x20,
			Wcdma		= 0x30,
			Cdma2k		= 0x40,
			Wimax		= 0x50,
			Lte			= 0x60,
			Ethernet	= 0x70
		}

		static Func<DataDeserializer.DecodeArg, string, bool> normalDecoder = null;
		static Func<DataDeserializer.DecodeArg, string, bool> extendedDecoder = null;

		internal protected override bool DecodeObject(DataDeserializer.DecodeArg arg, string name)
		{
			if (normalDecoder == null)
			{
				normalDecoder = DataDeserializer.CreateObjectDecoder(typeof(NormalNetworkInterface), false);
				extendedDecoder = DataDeserializer.CreateObjectDecoder(typeof(ExtendedNetworkInterface), false);
			}

			int type = (int)arg.data[arg.offset];
			
			switch (type)
			{
			case (int)NetworkInterfaceTypes.Wifi:
			case (int)NetworkInterfaceTypes.Wimax:
			case (int)NetworkInterfaceTypes.Ethernet:
				return normalDecoder(arg, name);
			
			case (int)NetworkInterfaceTypes.TwoG:
			case (int)NetworkInterfaceTypes.Wcdma:
			case (int)NetworkInterfaceTypes.Cdma2k:
			case (int)NetworkInterfaceTypes.Lte:
				return extendedDecoder(arg, name);
			
			default:
				return false;
			}
		}
	}
}
