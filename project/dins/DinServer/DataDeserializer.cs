using System;
using System.Text;
using System.Reflection;
using System.Collections.Generic;

namespace DinServer
{
	public class DataDeserializer
	{
		private static DataDeserializer instance = null;
		
		public static DataDeserializer Instance
		{
			get 
			{
				if (instance == null)
				{
					instance = new DataDeserializer();
				}
				return instance;
			}
		}

		private Dictionary<Type, List<FieldDecoder>> decoders;

		public DataDeserializer ()
		{
			this.decoders = new Dictionary<Type, List<FieldDecoder>>();
		}

		public class DecodeArg
		{
			public byte[] data;
			public int length;
			public int offset;
			public Object result;

			public void ResetResult()
			{
				result = null;
			}
		}

		public class FieldDecoder
		{
			public FieldInfo Accessor { set; get; }
			public Func<DecodeArg, String, bool> DecoderMethod { set; get; } 
		}

		public int DeserializeEx (Object rawBody, byte[] buffer, int dataLength, int offset)
		{	
			Console.WriteLine(" --- Decode Start \n");

			DecodeArg arg = new DecodeArg();
			arg.data = buffer;
			arg.length = dataLength;
			arg.offset = offset;
			arg.ResetResult();
			bool done = this.DeserializeEx(rawBody, arg);
			if (!done)
			{
				return -1;
			}
			Console.WriteLine("\n --- Decode End, Decoded Length: {0}", arg.offset);
			
			return arg.offset;
		}

		private bool DeserializeEx (Object rawBody, DecodeArg arg)
		{
			List<FieldDecoder> decoderList = null;
			if (!this.decoders.TryGetValue (rawBody.GetType (), out(decoderList))) 
			{
				decoderList = CreateDecoder(rawBody.GetType());
				this.decoders.Add (rawBody.GetType (), decoderList);
			}
			
			foreach (var decoder in decoderList) 
			{
				arg.ResetResult();

				if (!decoder.DecoderMethod(arg, decoder.Accessor.Name) || arg.offset > arg.length)
				{
					return false;
				}
				decoder.Accessor.SetValue(rawBody, arg.result);
			}
			return true;
		}

		public static List<FieldDecoder> CreateDecoder (Type rawBodyType)
		{
			List<FieldInfo> fields = new List<FieldInfo> (rawBodyType.GetFields());
			fields.Sort ((f1, f2) =>
			{
				if (f1.DeclaringType.IsSubclassOf(f2.DeclaringType))
				{
					return 1;
				}
				
				if (f2.DeclaringType.IsSubclassOf(f1.DeclaringType))
				{
					return -1;
				}
				
				OrderAttribute[] order1 = f1.GetCustomAttributes (typeof(OrderAttribute), false) as OrderAttribute[];
				OrderAttribute[] order2 = f2.GetCustomAttributes (typeof(OrderAttribute), false) as OrderAttribute[];
				
				if (order1 == null && order2 == null) {
					return 0;
				}
				
				if (order1 == null) {
					return -1;
				} else if (order2 == null) {
					return 1;
				}
				
				if (order1 [0].Order > order2 [0].Order) {
					return 1;
				} else if (order1 [0].Order < order2 [0].Order) {
					return -1;
				} else {
					return 0;
				}
			});
			
			List<FieldDecoder> decoders = new List<FieldDecoder>(fields.Count);
			
			foreach (FieldInfo field in fields) 
			{
				if (field.FieldType.IsEnum)
				{
					// check explicit size
					// and convert to enum values...
				}
				
				MsbSizeAttribute[] attrs = field.GetCustomAttributes(typeof(MsbSizeAttribute), false) as MsbSizeAttribute[];
				int msbSize = (attrs == null || attrs.Length <= 0) ? -1 : attrs [0].Size;

				switch (Type.GetTypeCode(field.FieldType))
				{
					case TypeCode.Byte:
					{
						decoders.Add(new FieldDecoder{
							Accessor = field,
							DecoderMethod = DecodeByte
						});
						break;
					}
					case TypeCode.SByte:
					{
						decoders.Add(new FieldDecoder{
							Accessor = field,
							DecoderMethod = DecodeSByte
						});
						break;
					}
					case TypeCode.Int16:
					{
						decoders.Add(new FieldDecoder{
							Accessor = field,
							DecoderMethod = DecodeInt16
						});
						break;
					}
					case TypeCode.UInt16:
					{
						decoders.Add(new FieldDecoder{
							Accessor = field,
							DecoderMethod = DecodeUInt16
						});
						break;
					}
					case TypeCode.Int32:
					{
						decoders.Add(new FieldDecoder{
							Accessor = field,
							DecoderMethod = (msbSize < 0) ? DecodeInt32 : DecodeVarInt32(msbSize)
						});
						break;
					}
					case TypeCode.UInt32:
					{
						decoders.Add(new FieldDecoder{
							Accessor = field,
							DecoderMethod = DecodeUInt32
						});
						break;
					}
					case TypeCode.Int64:
					{
						decoders.Add(new FieldDecoder{
							Accessor = field,
							DecoderMethod = DecodeInt64
						});
						break;
					}
					case TypeCode.UInt64:
					{
						decoders.Add(new FieldDecoder{
							Accessor = field,
							DecoderMethod = DecodeUInt64
						});
						break;
					}
					case TypeCode.String:
					{
						decoders.Add(new FieldDecoder{
							Accessor = field,
							DecoderMethod = DecodeString
						});
						break;
					}
					case TypeCode.Object:
					{
						if (field.FieldType.IsArray)
						{
							Type assignedType = field.FieldType.GetElementType();
							if (assignedType == null)
							{
								continue;
							}

							ExplicitSizeAttribute[] size = field.GetCustomAttributes(typeof(ExplicitSizeAttribute), false) as ExplicitSizeAttribute[];
							if (size.Length > 0)
							{
								decoders.Add(new FieldDecoder()
								{
									Accessor = field,
									DecoderMethod = CreateArrayDecoder(assignedType, size[0].Size, msbSize)
								});
							}
							else
							{
								decoders.Add(new FieldDecoder()
								{
									Accessor = field,
									DecoderMethod = CreateArrayDecoder(assignedType, -1, msbSize)
								});
							}
						}
						else
						{
							decoders.Add(new FieldDecoder()
				            {
								Accessor = field,
								DecoderMethod = CreateObjectDecoder(field.FieldType)
							});
						}
						break;
					}
				}
			}
			
			return decoders;
		}
		
		public static bool DecodeByte(DecodeArg arg, String name)
		{			arg.result = (Object) arg.data [arg.offset++];
			
			if (arg.result == null) 
			{
				return false;
			}
			else
			{
				PrintValue(name, arg.result);
			}
			
			return true;
		}
		
		public static bool DecodeSByte(DecodeArg arg, String name)
		{
			sbyte result = unchecked((sbyte)arg.data[arg.offset++]);
			
			arg.result = result;
			
			if (arg.result == null) 
			{
				return false;
			}
			else
			{
				PrintValue(name, arg.result);
			}
			
			return true;
		}
		
		public static bool DecodeString(DecodeArg arg, String name)
		{
			int length = arg.data[arg.offset++];
			
			if (length == 255)
			{
				arg.result = "*No Data*";
			}
			else
			{
				arg.result = Encoding.UTF8.GetString(arg.data, arg.offset, length);
				arg.offset += length;
				
				if (arg.result == null) 
				{
					return false;
				}
			}
			
			PrintValue(name, arg.result);
			return true;
		}
		
		public static bool DecodeInt16(DecodeArg arg, String name)
		{
			if (arg.data == null && arg.data.Length == 0) 
			{
				arg.result = (Object)0;
				
				return false;
			}
			
			try
			{
				arg.result = (Object)System.Net.IPAddress.HostToNetworkOrder (BitConverter.ToInt16 (arg.data, arg.offset));
				arg.offset += 2;
				PrintValue(name, arg.result);
			} 
			catch (ArgumentException ex) {
				Console.WriteLine("Exception: " + ex.Message);
				
				arg.result = (Object)0;
				arg.offset += 2;
				
				return false;
			}
			
			return true;
		}
		
		public static bool DecodeUInt16(DecodeArg arg, String name)
		{
			if (arg.data == null && arg.data.Length == 0) 
			{
				arg.result = (Object)0;
				
				return false;
			}
			
			try 
			{
				byte[] bytes = BitConverter.GetBytes(BitConverter.ToUInt16(arg.data, arg.offset));
				if (BitConverter.IsLittleEndian)
				{
					Array.Reverse(bytes);
				}
				arg.result = (Object) BitConverter.ToUInt16(bytes, 0);				
				arg.offset += 2;
				PrintValue(name, arg.result);
			} 
			catch (ArgumentException ex) {
				Console.WriteLine("Exception: " + ex.Message);
				
				arg.result = (Object)0;
				arg.offset += 2;
				
				return false;
			}
			
			return true;
		}

		private static String indent = "\t";
		private static void PrintLabel(String name)
		{
			Console.WriteLine("{1}{0}", name, indent);
		}
		private static void PrintValue(String name, Object value)
		{
			Console.WriteLine("{2}{0} = {1}", name, value, indent);
		}

		public static Func<DecodeArg,String, bool> DecodeVarInt32(int msbSize)
		{
			return (DecodeArg arg, String name) =>
			{
				int prefix = arg.data[arg.offset] >> (8 - msbSize);
				int result = 0;
				switch (prefix)
				{
				case (Byte)0x00:
					result = arg.data[arg.offset++] & 0x3F;
					arg.result = result;
					PrintValue(name, arg.result);
					return true;
				case (Byte)0x01: // 2 byte
					result = (arg.data[arg.offset++] & 0x3F) << 8;
					result += (arg.data[arg.offset++]);
					arg.result = result;
					PrintValue(name, arg.result);
					return true;
				case (Byte)0x02: // 3 byte
					result = (arg.data[arg.offset++] & 0x3F) << 8;
					result += (arg.data[arg.offset++]) << 8;
					result += (arg.data[arg.offset++]);
					arg.result = result;
					PrintValue(name, arg.result);
					return true;
				case (Byte)0x03: // 4 byte
					result = (arg.data[arg.offset++] & 0x3F) << 8;
					result += (arg.data[arg.offset++]) << 8;
					result += (arg.data[arg.offset++]) << 8;
					result += (arg.data[arg.offset++]);
					arg.result = result;
					PrintValue(name, arg.result);
					return true;
				default:
					return false;
				}
			};
		}

		public static bool DecodeInt32(DecodeArg arg, String name)
		{
			if (arg.data == null && arg.data.Length == 0) 
			{
				arg.result = (Object)0;
				
				return false;
			}
			
			try 
			{
				arg.result = (Object)System.Net.IPAddress.HostToNetworkOrder (BitConverter.ToInt32 (arg.data, arg.offset));
				arg.offset += 4;
				//Console.WriteLine ("[Int32] " + name);
				PrintValue(name, arg.result);
			} 
			catch (ArgumentException ex) {
				Console.WriteLine("Exception: " + ex.Message);
				
				arg.result = (Object)0;
				arg.offset += 4;
				
				return false;
			}
			
			return true;
		}
		
		public static bool DecodeUInt32(DecodeArg arg, String name)
		{
			if (arg.data == null && arg.data.Length == 0) 
			{
				arg.result = (Object)0;
				
				return false;
			}
			
			try 
			{
				byte[] bytes = BitConverter.GetBytes(BitConverter.ToUInt32(arg.data, arg.offset));
				if (BitConverter.IsLittleEndian)
				{
					Array.Reverse(bytes);
				}
				arg.result = (Object) BitConverter.ToUInt32(bytes, 0);
				
				arg.offset += 4;
				//Console.WriteLine ("[UInt32] " + name);
				PrintValue(name, arg.result);
			} 
			catch (ArgumentException ex) {
				Console.WriteLine("Exception: " + ex.Message);
				
				arg.result = (Object)0;
				arg.offset += 4;
				
				return false;
			}
			
			return true;
		}
		
		public static bool DecodeInt64(DecodeArg arg, String name)
		{
			if (arg.data == null && arg.data.Length == 0) 
			{
				arg.result = (Object) 0;
				
				return false;
			}
			
			try
			{
				arg.result = (Object)System.Net.IPAddress.HostToNetworkOrder (BitConverter.ToInt64 (arg.data, arg.offset));
				arg.offset += 8;
				//Console.WriteLine ("[Int64] " + name);
				PrintValue(name, arg.result);
			} 
			catch (ArgumentException ex) {
				Console.WriteLine("Exception: " + ex.Message);
				
				arg.result = (Object) 0;
				arg.offset += 8;
				
				return false;
			}
			
			return true;
		}
		
		public static bool DecodeUInt64(DecodeArg arg, String name)
		{
			if (arg.data == null && arg.data.Length == 0) 
			{
				arg.result = (Object) 0;
				
				return false;
			}
			
			try 
			{
				byte[] bytes = BitConverter.GetBytes(BitConverter.ToUInt64(arg.data, arg.offset));
				if (BitConverter.IsLittleEndian)
				{
					Array.Reverse(bytes);
				}
				arg.result = (Object) BitConverter.ToUInt64(bytes, 0);
				
				arg.offset += 8;
				//Console.WriteLine ("[UInt64] " + name);
				PrintValue(name, arg.result);
			} 
			catch (ArgumentException ex) {
				Console.WriteLine("Exception: " + ex.Message);
				
				arg.result = (Object) 0;
				arg.offset += 8;
				
				return false;
			}
			
			return true;
		}
	
		public static Func<DecodeArg, String, bool> CreateObjectDecoder (Type objectType)
		{
			return CreateObjectDecoder(objectType, true);
		}
		
		public static Func<DecodeArg, String, bool> CreateObjectDecoder (Type objectType, bool useCustomDecoder)
		{
			if (useCustomDecoder)
			{
				var attrs = objectType.GetCustomAttributes(typeof(PacketElementDecoderAttribute), true);
				if (attrs != null && attrs.Length == 1)
				{
					PacketElementDecoderAttribute attr = attrs[0] as PacketElementDecoderAttribute;
					return (DecodeArg arg, String name) =>
					{
						return attr.DecoderInstance.DecodeObject(arg, name);
					};
				}
			}
			
			var subDecoders = CreateDecoder(objectType);
			var constructor = objectType.GetConstructor(Type.EmptyTypes);
			
			return (DecodeArg arg, String name) =>
			{
				PrintLabel(name);
				indent += "\t";
				var instance = constructor.Invoke(null);
				for (int i = 0; i < subDecoders.Count; ++i)
				{
					if (!subDecoders[i].DecoderMethod(arg, subDecoders[i].Accessor.Name) || arg.offset > arg.length)
					{
						return false;
					}
					subDecoders[i].Accessor.SetValue(instance, arg.result);
				}

				arg.result = instance;
				indent = indent.Remove(indent.Length - 1);
				return true;
			};
		}
		
		private static Func<DecodeArg, String, bool> CreateArrayDecoder (Type elementType, int explicitSize, int msbSize)
		{	
			Func<DecodeArg, String, bool> elementDecoder = null;
			switch (Type.GetTypeCode(elementType)) 
			{
			case TypeCode.Byte:
				elementDecoder = DecodeByte;
				break;
			case TypeCode.SByte:
				elementDecoder = DecodeSByte;
				break;
			case TypeCode.Int16:
				elementDecoder = DecodeInt16;
				break;
			case TypeCode.Int32:
				elementDecoder = (msbSize < 0) ? DecodeInt32 : DecodeVarInt32(msbSize);
				break;
			case TypeCode.Int64:
				elementDecoder = DecodeInt64;
				break;
			case TypeCode.UInt16:
				elementDecoder = DecodeUInt16;
				break;
			case TypeCode.UInt32:
				elementDecoder = DecodeUInt32;
				break;
			case TypeCode.UInt64:
				elementDecoder = DecodeUInt64;
				break;
			case TypeCode.String:
				elementDecoder = DecodeString;
				break;
			case TypeCode.Object:
				elementDecoder = CreateObjectDecoder(elementType);
				break;
			}

			if (elementDecoder != null)
			{
				return (DecodeArg arg, String name) =>
				{
					int arraySize = explicitSize;

					if (arraySize <= 0)
					{
						arraySize = arg.data[arg.offset++];

						if (arraySize == 255)
						{
							arg.result = null;
							return true;
						}
					}

					PrintLabel(name + "[]");
					indent += "\t";
					Array data = Array.CreateInstance(elementType, arraySize);
					for (int i = 0; i < arraySize; i++) 
					{
						if (!elementDecoder(arg, name) || arg.offset > arg.length)
						{
							arg.result = null;
							return false;
						}
						//data [i] = arg.result;
						data.SetValue(arg.result, i);
					}

					arg.result = data;
					indent = indent.Remove(indent.Length - 1);
					return true;
				};
			}

			throw new Exception(String.Format("Array handler of {0} not implemented", elementType));
		}
	}
}

