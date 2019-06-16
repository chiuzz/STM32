using System;
using System.IO.Ports;
using System.Threading;

namespace Module_Omega
{
    /// <summary>
    /// 测温模块
    /// </summary>
    public class Omega
    {
        private static string serialportCOM = "COM3";
        private const int serialportBaudrate = 38400;
        private const int serialdataBits = 8;
        private static SerialPort comPort = new SerialPort();
        private static String ModuleStatus;
        private static Thread thread;
        private static double val;
        #region 属性

        /// <summary>串口名称
        /// 
        /// </summary>
        public static string COM_Name
        {
            get { return serialportCOM; }
            set { serialportCOM = value; }
        }
        /// <summary>
        /// 串口状态（true打开，false关闭）
        /// </summary>
        public static bool COM_State
        {
            get { return comPort.IsOpen; }
        }

        #endregion
        #region 内部函数
        private static bool RS232Communication_DP9602(byte[] buf, int len)
        {
            bool ret = false;
            comPort.Write(buf ,0, len);
            Thread.Sleep(500);
            int recNum = comPort.BytesToRead;
            if (recNum < 3)
                return false;
            byte[] recData = new byte[recNum];
            comPort.Read(recData, 0, recNum);
            if (recData[0] == 0x30)
                ret = true;
            return ret;
        }

        private static double RS232CommunicationGetData()
        {
            double ret = 0;
            String str = "";
            byte[] buf = new byte[3];
            buf[0]=0x4d; 
            buf[1]=0x45;
            buf[2]=0x0d;
            comPort.Write(buf ,0, buf.Length);
            Thread.Sleep(2500);
            int recNum = comPort.BytesToRead;
            //Console.WriteLine("recNum:"+recNum);
            if (recNum < 10)
                return 0;
            byte[] recData = new byte[recNum];
            comPort.Read(recData, 0, recNum);
            char cStr;
            for (int i = 4; i < recNum-2; i++)
            {
                cStr = (char)recData[i];
                str+= cStr;
            }
            ret = double.Parse(str);
            //Console.WriteLine("ReceiveData:" + ret.ToString());
            return ret;
        }


        private static bool InitOmega()
        {
            byte[] CmdBuffer = new byte[5];
            //1.选择单位为摄氏度：	55 4E 20 43 0D
            CmdBuffer[0] = 0x55;
            CmdBuffer[1] = 0x4E;
            CmdBuffer[2] = 0x20;
            CmdBuffer[3] = 0x43;
            CmdBuffer[4] = 0x0D;
            // Response: x30 0x0A 0x0D
            if (!RS232Communication_DP9602(CmdBuffer, CmdBuffer.Length))
            {
                ModuleStatus = "Set unit fail for DP9602!";
                //Console.WriteLine("Set unit fail for DP9602!");
                return false;
            }
            ModuleStatus = "Set unit fail for DP9602!";
            Thread.Sleep(500);
            byte[] CmdBuffer1 = new byte[7];
            //2.选择探头为PT100:	53 45 20 50 52 54 0D
            CmdBuffer1[0] = 0x53;
            CmdBuffer1[1] = 0x45;
            CmdBuffer1[2] = 0x20;
            CmdBuffer1[3] = 0x50;
            CmdBuffer1[4] = 0x52;
            CmdBuffer1[5] = 0x54;
            CmdBuffer1[6] = 0x0D;
            // Response: x30 0x0A 0x0D
            if (!RS232Communication_DP9602(CmdBuffer1, CmdBuffer1.Length))
            {
                ModuleStatus = "Select PT100 fail for DP9602!";
                //Console.WriteLine("Select PT100 fail for DP9602!", "Communication Error");
                return false;
            }
            ModuleStatus = "Select PT100 for DP9602!";
            Thread.Sleep(500);
            ModuleStatus = "Open DP6902 successfully!";
            //Console.WriteLine("Open DP6902 successfully!");
            return true;
        }

        private static void ThreadMethod()
        {
            while (true)
            {
                val = RS232CommunicationGetData();
                Thread.Sleep(500);
            }
        }

        #endregion

        #region 函数接口
        /// <summary>初始化开启串口
        /// 
        /// </summary>
        public static bool Open_sPort()
        {
            try
            {
                comPort.PortName = serialportCOM;
                comPort.BaudRate = serialportBaudrate;
                comPort.DataBits = serialdataBits;
                comPort.StopBits = StopBits.One;
                comPort.Parity = Parity.None;
                comPort.ReadBufferSize = 1024;

                if (!comPort.IsOpen)
                    comPort.Open();
                else
                {
                    comPort.Close();
                    comPort.Open();
                }
                ModuleStatus = "Port Open Success";
               // Console.WriteLine("Port Open Success.\n");
                Thread.Sleep(500);
                thread = new Thread(new ThreadStart(ThreadMethod));
                if (InitOmega() == true)
                    thread.Start();
                else
                    return false;
                return true;
            }
            catch
            {
                //Console.WriteLine("Port Open Fail.\n");
                ModuleStatus = "Port Open Fail";
                return false;
            }
        }
        /// <summary>关闭串口
        /// 
        /// </summary>
        public static bool Close_sPort()
        {
            try
            {
                thread.Abort();
                comPort.Close();
                ModuleStatus = "Port Close Sucess";
                //Console.WriteLine("Port Close Success.\n");
                return true;
            }
            catch
            {
                ModuleStatus = "Port Close Fail";
                //Console.WriteLine("Port Close Fail.\n");
                return false;
            }
        }
        /// <summary>
        /// 获取Omega设置端口的状态
        /// </summary>
        /// <returns></returns>
        public static String GetModuleStatus()
        {
            return ModuleStatus;
        }
        /// <summary>
        /// 获取Omega设置的温度
        /// </summary>
        /// <returns></returns>
         public static double GetModuleVal()
        {
            return val ;
        }
        #endregion
    }
}
