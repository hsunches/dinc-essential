using System;
using System.Net;
using System.IO;
using System.Reflection;

namespace DinServer
{
	public enum DinPacketCategories
	{
		Dinc		= 0x0000,
		Device		= 0x0100,
		WifiStation	= 0x0200,
		WifiAp		= 0x0300,
		Wimax		= 0x0400,
		TwoG		= 0x0500,
		ThreeG		= 0x0600,
		Lte			= 0x0700,
		Voip		= 0x0800,
		Ethernet	= 0x0900
	}

	public enum DinPacketTypes
	{
		DcDevice				= 0x0001,
		DcConnectionHistory		= 0x0002,
		DcNetworkEntry			= 0x0003,
		DcAlert					= 0x0004,
		DcHandover				= 0x0005,
		DcIpChange				= 0x0006,
		DcPerformance			= 0x0007,
		DcCall					= 0x0008,
		DcTermination			= 0x0009,
		
		DincLatencyTest			= 0x00C1,
		DincConnectionHistory	= 0x00C2,
		DincExtCmdAck			= 0x00C3,
		DincDevInfoUpdate		= 0x00C4
	}
	
	public enum DinPacketHeaderFormats
	{
		Location	= 0x8000,
		DeviceId	= 0x4000,
		Both		= 0xC000,
		None		= 0x0000
	}

	public abstract class DinPacket
	{
		internal class Info
		{
			public int PacketId { get; set; }
			public string Type { get; set; }
			public Func<DinPacket> Spawner { get; set; }
			
			public override string ToString()
			{
				return this.Type;
			}
		}

		private static Info[] spawners = new Info[0x4000];
		
		static DinPacket()
		{
			foreach (Type type in Assembly.GetExecutingAssembly().GetTypes())
			{
				object[] typeAttributes = type.GetCustomAttributes(true);
				PacketIdAttribute packetIdAttributes = null;

				if (typeAttributes != null && typeAttributes.Length > 0)
				{
					packetIdAttributes = Array.Find(typeAttributes, (a) => a is PacketIdAttribute) as PacketIdAttribute;
				}

				if (packetIdAttributes == null)
				{
					continue;
				}
				
				ConstructorInfo constructor = type.GetConstructor(System.Type.EmptyTypes);

				if (constructor == null)
				{
					throw new Exception(String.Format("Packet {0} has no constructor defined.", type.FullName));
				}

				int id = packetIdAttributes.Id;

				spawners[id] = new Info()
				{
					PacketId = id,
					Type = type.FullName,


					Spawner = () =>
					{
						try
						{
							return constructor.Invoke(null) as DinPacket;
						}
						catch
						{
							return null;
						}
					}
				};
			}
		}

		public static int GetId(byte first, byte second)
		{
			return ((int)(first & 0x3F) << 8) + second;
		}

		public static int GetId(DinPacketCategories category, DinPacketTypes type)
		{
			return (int)category | (int)type;
		}
		
		public static DinPacket Create(int id)
		{
			if (id >= spawners.Length)
			{
				return null;
			}
			
			Info info = spawners[id];

			if (info == null)
			{
				return null;
			}
			
			return info.Spawner();
		}

		public bool HasDeviceId
		{
			get { return ((int)this.HeaderFormat & (int)DinPacketHeaderFormats.DeviceId) != 0; }
		}
		
		internal DinPacketHeaderFormats HeaderFormat { get; private set; }
		internal DinPacketCategories Category { get; private set; }
		internal DinPacketTypes Type { get; private set; }

		public ulong DeviceId { get; set; }

		public int DecodeData(byte[] data, int dataLength, Context context)
		{
			this.HeaderFormat = (DinPacketHeaderFormats)((data[0] & 0xC0) << 8);
			this.Category = (DinPacketCategories)((data[0] & 0x3F) << 8);
			this.Type = (DinPacketTypes)data[1];
			
			int offset = 2;
			if (HasDeviceId)
			{
				this.DeviceId = (ulong)IPAddress.HostToNetworkOrder(BitConverter.ToInt64(data, offset));
				offset += 8;
			}

			if (context.showSimpleMessage)
			{
				return offset;
			}

			// to avoid any unexpected issue
			try 
			{
				return this.DecodeBody(data, dataLength, offset);
			}
			catch {
				return -1;
			}
		}
		
		protected abstract int DecodeBody(Byte[] bytes, int dataLength, int offset);
		
		internal DinPacket()
		{
		}

	}

	public abstract class DinPacket<PACKET, FORMAT> : DinPacket 
		where PACKET : DinPacket<PACKET, FORMAT>
			where FORMAT : class, new()
	{

		protected DinPacket()
		{
		}

		protected override int DecodeBody(Byte[] bytes, int dataLength, int offset)
		{
			FORMAT rawFormat = new FORMAT();

			return DataDeserializer.Instance.DeserializeEx (rawFormat, bytes, dataLength, offset);
		}

		protected abstract bool Decode(FORMAT format);
	}
}
