using System;
using System.Net;
using System.IO;
using System.Net.Sockets;
using System.Runtime.Remoting.Metadata.W3cXsd2001;
using System.Security.Cryptography;
using System.Threading;

namespace DinServer
{
	public class Context
	{
		public string inputLogFile;
		public bool showSimpleMessage;
		public string logFullFilePath;
	};

	class MainClass
	{
		private static Mutex mut = new Mutex();

		public static void Main (string[] args)
		{
			UdpClient server = new UdpClient(52888);
			IPEndPoint remoteAddress = new IPEndPoint(IPAddress.Any, 0);

			Context ctx = new Context();

			// read application arguments
			if (args.Length > 0 && args[0].Equals("-l"))
			{
				ctx.inputLogFile = args[1];
			}

			ctx.showSimpleMessage = (args.Length > 0 && args[0].Equals ("fd"));

			if (ctx.inputLogFile != null && ctx.inputLogFile.Length > 0)
			{
				Console.ForegroundColor = ConsoleColor.White;
				foreach (var line in File.ReadAllLines(ctx.inputLogFile))
				{
					if (line.Trim ().Length == 0) {
						continue;
					}

					if (Console.ForegroundColor == ConsoleColor.White)
					{
						Console.ForegroundColor = ConsoleColor.Yellow;
					} 
					else
					{
						Console.ForegroundColor = ConsoleColor.White;
					}

					var tokens = line.Split (",".ToCharArray());
					var b64 = tokens [tokens.Length - 1];
					var bytes = Convert.FromBase64String (b64);

					Console.WriteLine ("{0} {3:X16} {1}.{2}", tokens[0], tokens[1], tokens[2], Convert.ToUInt64(tokens[3]));

					if (IsHandshakingData(bytes)) 
					{
						Console.WriteLine("Doing handshake...");
						CreatePacket(bytes, bytes.Length, ctx);
					} else if (IsLatencyTestData(bytes)) {

						Console.WriteLine("Latency test received...\n");
					} else {

						CreatePacket(bytes, bytes.Length, ctx);
					}
					Console.ReadLine();
				}
			}
			else
			{
				// create log file folder
				string logPath = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
				logPath = Path.Combine(logPath, "log");
				if (!Directory.Exists(logPath))
				{
					Directory.CreateDirectory(logPath);
				}

				// create log file
				logPath = Path.Combine(logPath, DateTime.Now.ToString("yyyy_MM_dd_HH_mm_ss") + ".log");
				if (!File.Exists(logPath))
				{
					File.Create(logPath).Close();
					ctx.logFullFilePath = logPath;
				}
				// Start new thread to detect keypad input.
				Thread workerThread = new Thread(new ThreadStart(() => KeypadDetectionWork(ref server, ref remoteAddress)));
				workerThread.Start();

				while (true)
				{
					byte[] receivedData = new byte[0];

					try {
						mut.WaitOne();
						receivedData = server.Receive(ref remoteAddress);
					} catch(SocketException e) {
						Console.WriteLine("Exception");
						if (e.ErrorCode != (int)SocketError.TimedOut) {
							throw new Exception ("Unexpected Socket error", e);
						}
					} finally {
						mut.ReleaseMutex();
						Thread.Sleep (1000);
					}

					// receivedData = server.Receive(ref remoteAddress);

					if (receivedData.Length <= 0) {
						continue;
					}
					
					int descrambledDataLength = DescrambleData(ref receivedData);
					
					if (descrambledDataLength <= 0) {
						Console.WriteLine("Descrambling fail");
						continue;
					}
					
					int realDataLength = ValidateReceivedData(ref receivedData);
					
					if (realDataLength <= 0) {
						Console.WriteLine("Validation fail");
						continue;
					}
					
					Console.Write("[" + DateTime.UtcNow.ToString() + "]" + ((ctx.showSimpleMessage) ? "" : "\n\n"));
					
					//SoapHexBinary shb = new SoapHexBinary(receivedData);
					//Console.WriteLine(shb.ToString());
					//Console.WriteLine("Data Length: " + realDataLength + "\n");

					if (IsHandshakingData (receivedData)) {
						SendResponse ("AUTH", 1, server, remoteAddress);
						CreatePacket (receivedData, realDataLength, ctx);
					} else if (IsLatencyTestData (receivedData)) {
						Console.WriteLine ("Latency test received...\n");
						SendResponse ("LATT", receivedData [2], server, remoteAddress);
						// SendExtCmd (0, server, remoteAddress);
					} else {
						CreatePacket(receivedData, realDataLength, ctx);
					}
				}
			}
		}

		private static void SendExtCmd(uint cmd, string input, ref UdpClient server, ref IPEndPoint remoteAddress) 
		{
			// Send > to DINC to execute external cmd.
			char one = (char)('1' - '0');
			char zero = (char)0;
			char[] commands = {zero, one};
			if (cmd > commands.Length) return;

			int value = 0;

			// Input parameter
			if (cmd == 1) {
				value = Convert.ToInt32 (input);
			}

			// exec_cmd[0]: Indicate that this is a ext cmd.
			// 		   [1]: DC type, for now we use dev only.
			//         [2]: Ext cmd id, for now 0 for firmware up grade, 1 for opening wan.
			//         [3]: Reserved. For now we only use last bit to indicate ack. 
			string exec_cmd = new string(new char[] {'>', one , commands[cmd], one});
			SendResponse(exec_cmd, value, server, remoteAddress);
		}

		private static void KeypadDetectionWork(ref UdpClient server, ref IPEndPoint remoteAddress)
		{
			while (true)
			{
				uint cmd = 0;
				string input = "";

				Console.WriteLine("worker thread: working...");
				if (System.Console.ReadKey (true).Key == ConsoleKey.W ||
					System.Console.ReadKey (true).Key == ConsoleKey.F) {

					cmd = (System.Console.ReadKey (true).Key == ConsoleKey.W) ? 1U : 0U;
					Console.WriteLine ("Sending ExtCmd: {0}", (cmd == 0) ? "Firmware Update" : "Allow Web Access From WAN");

					if (cmd == 1U) 
					{
						Console.Write ("Please input the access duration (in seconds): ");
						int value = 0;
						for (;;) {
							input = Console.ReadLine ();
							if (int.TryParse (input, out value)) {
								break;
							} else {
								Console.Write ("Please input a valid duration integer (in seconds): ");
							}
						}
					}
				} else {
					Thread.Sleep(1000);
					continue;
				}

				try {
					Console.WriteLine("External command will be sent when the next packet received...");
					mut.WaitOne();
					SendExtCmd (cmd, input, ref server, ref remoteAddress);
				} catch (SocketException e) {
					Console.WriteLine ("Sending ExtCmd {0} failed: Reason {1}", (cmd == 0) ? "Firmware Update" : "WAN", e);
				} finally {
					mut.ReleaseMutex();
					Thread.Sleep(1000);
				}
			}
		}

		private static void CreatePacket(byte[] data, int dataLength, Context context)
		{
			if (data == null || data.Length <= 2 || dataLength <= 2)
			{
				return;
			}

			byte category = (byte)(data[0] & 0x3F);
			byte type = data[1];
			DinPacket packet = DinPacket.Create(DinPacket.GetId(category, type));

			if (packet == null)
			{
				return;
			}

			int length = packet.DecodeData(data, dataLength, context);
			if (length < 0)
			{
				return;
			}

			if (context.logFullFilePath != null && context.logFullFilePath.Length > 0)
			{
				// format packet log
				string logs = String.Join (",", new String[] {
					DateTime.Now.ToString("yyyy-MM-dd-HH:mm:ss"),
					packet.Category.ToString(),
					packet.Type.ToString(),
					packet.DeviceId.ToString(),
					Convert.ToBase64String(data, 0, dataLength)
				});
				File.AppendAllLines (context.logFullFilePath, new String[] { logs });
			}

			if (context.showSimpleMessage)
			{
				Console.WriteLine("[Category:" + packet.Category + "][Type:" + packet.Type + "][Device ID:{0:X}]", packet.DeviceId);
				return;
			}

			// server show full message
			if (context.inputLogFile == null || (context.inputLogFile != null && context.inputLogFile.Length <= 0))
			{
				Console.WriteLine(" --- Category: " + packet.Category + ", Type: " + packet.Type + " Device ID: {0:X}", packet.DeviceId + "\n");
			}
		}
		
		private static bool IsHandshakingData(byte[] data)
		{
			if (data != null && data.Length > 0) {
				byte category = (byte)(data[0] & 0x3F);
				byte type = data[1];

				if (DinPacket.GetId(category, type) == DinPacket.GetId(DinPacketCategories.Device, DinPacketTypes.DcDevice))
				{
					return true;
				}
			}
			
			return false;
		}

		private static bool IsLatencyTestData(byte[] data)
		{
			if (data != null && data.Length > 0)
			{
				byte category = (byte)(data[0] & 0x3F);
				byte type = data[1];

				if (DinPacket.GetId(category, type) == DinPacket.GetId(DinPacketCategories.Dinc, DinPacketTypes.DincLatencyTest))
				{
					return true;
				}
			}
			
			return false;
		}
		
		private static int ScrambleData(ref byte[] data)
		{
			if (data == null || data.Length == 0)
			{
				return -1;
			}
			
			Random rand = new Random();
			int randomArrayLength = rand.Next(1, 8);
			byte[] randomArray = new byte[randomArrayLength];
			
			for (int i = 0; i < randomArrayLength; i++)
			{
				randomArray[i] = (byte)(rand.Next(255));
			}
			
			int maskIndex = rand.Next(randomArrayLength);
			byte mask = randomArray[maskIndex];
			
			for (int i = 0; i < data.Length; i++)
			{
				data[i] ^= mask;	
			}
			
			byte[] scrambledData = new byte[(1 + randomArrayLength) + data.Length];
			
			scrambledData[0] = (byte)((randomArrayLength << 4) | maskIndex);
			Buffer.BlockCopy(randomArray, 0, scrambledData, 1, randomArray.Length);
			Buffer.BlockCopy(data, 0, scrambledData, 1 + randomArray.Length, data.Length);
			data = scrambledData;
			return scrambledData.Length;
		}
		
		private static int DescrambleData(ref byte[] data)
		{
			if (data == null || data.Length == 0)
			{
				return -1;
			}
			
			int randomArrayLength = data[0] >> 4;
			int maskIndex = data[0] & 0x0F;
			
			if (maskIndex >= randomArrayLength)
			{
				return -1;
			}
			
			byte mask = data[1 + maskIndex];
			int descrambledDataOffset = 1 + randomArrayLength;
			byte[] descrambledData = new byte[data.Length - descrambledDataOffset];
			
			for (int i = 0; i < descrambledData.Length; i++) {
				descrambledData[i] =  Convert.ToByte(data[descrambledDataOffset + i] ^ mask);
			}
			
			data = descrambledData;
			return descrambledData.Length;
		}
		
		private static int ValidateReceivedData(ref byte[] data)
		{
			if (data == null || data.Length == 0)
			{
				return -1;
			}
			
			uint checksum = BitConverter.ToUInt32(data, 0);

			data[0] = (byte)'R';
			data[1] = (byte)'N';
			data[2] = (byte)'C';
			data[3] = (byte)'E';

			byte[] digest = MD5.Create().ComputeHash(data);
			
			if (BitConverter.ToUInt32(digest, 0) != checksum)
			{
				return -1;
			}
			
			byte[] realData = new byte[data.Length - 8];
			
			Buffer.BlockCopy(data, 8, realData, 0, realData.Length);
			data = realData;
			return realData.Length;
		}

		private static void SendResponse(string command, int commandValue, UdpClient server, IPEndPoint remoteAddress)
		{
			if (command == null || server == null || remoteAddress == null)
			{
				return;
			}

			byte[] responseData = new byte[16];
			int timestamp = (int)(DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc)).TotalSeconds;

			responseData[0] = (byte)'N';
			responseData[1] = (byte)'E';
			responseData[2] = (byte)'I';
			responseData[3] = (byte)'L';

			Buffer.BlockCopy(BitConverter.GetBytes(IPAddress.HostToNetworkOrder(timestamp)), 0, responseData, 4, 4);

			responseData[8] = (byte)command[0];
			responseData[9] = (byte)command[1];
			responseData[10] = (byte)command[2];
			responseData[11] = (byte)command[3];

			Buffer.BlockCopy(BitConverter.GetBytes(IPAddress.HostToNetworkOrder(commandValue)), 0, responseData, 12, 4);

			byte[] hash = MD5.Create().ComputeHash(responseData, 0, 16);
			int checksum = BitConverter.ToInt32(hash, 0);
			
			Buffer.BlockCopy(BitConverter.GetBytes(BitConverter.ToUInt32(responseData, 4) ^ checksum), 0, responseData, 0, 4);
			Buffer.BlockCopy(BitConverter.GetBytes(BitConverter.ToUInt32(responseData, 8) ^ checksum), 0, responseData, 4, 4);
			Buffer.BlockCopy(BitConverter.GetBytes(BitConverter.ToUInt32(responseData, 12) ^ checksum), 0, responseData, 8, 4);
			Buffer.BlockCopy(hash, 0, responseData, 12, 4);

			ScrambleData(ref responseData);
			server.Send(responseData, responseData.Length, remoteAddress);
		}
	}
}
