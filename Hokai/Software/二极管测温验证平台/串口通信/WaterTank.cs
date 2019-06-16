using System;
using System.IO.Ports;
using System.Threading;
using EXCEL_LGL;
namespace Module_WaterTank
{
    /// <summary>
    /// 水槽模块
    /// </summary>
    public class WaterTank 
    {
        private static string serialportCOM = "COM3";
        private const int serialportBaudrate = 9600;
        private const int serialdataBits = 8;
        private static SerialPort comPort = new SerialPort();
        private static String ModuleStatus;
        private static Thread thread;
        private static double TempVal;
        private static double SetVal;
        private static bool m_SetStaus;
        private static double m_UserSetVal;

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
        private static double RS232CommunicationGetData(Byte cmd)
        {
            double ret = 0;
            byte[] buf = new byte[3];
            string str = "";
            buf[0]=0x01;
            buf[1]=cmd;
            buf[2]=(Byte)(buf[0]+buf[1]);
            comPort.Write(buf ,0, buf.Length);
            Thread.Sleep(1000);
            int recNum = comPort.BytesToRead;
            //Console.WriteLine("recNum:"+recNum);
            if (recNum < 7)
                return 0;
            byte[] recData = new byte[recNum];
            comPort.Read(recData, 0, recNum);
            //for (int i = 0; i < 7; i++)
            //{
            //    str += recData[i].ToString("X2") + " "; 
            //}
            //Console.WriteLine("RecData: "+str);
            ret = ((recData[3] << 16) + (recData[4] << 8) + recData[5])/1000.0;
            //Console.WriteLine("ReceiveData:" + ret.ToString());
            return ret;
        }
        private static bool RS232CommunicationSetData(double temp)
        {
            bool ret = true;
            Int32 data = (Int32)(temp*1000);
            byte[] buf = new byte[7];
            buf[0] = 0x01;
            buf[1] = 0x07;
            buf[2] = (Byte)((data >>24)&0xff);
            buf[3] = (Byte)((data >>16)&0xff);
            buf[4] = (Byte)((data >>8)&0xff);
            buf[5] = (Byte)(data&0xff);
            buf[6] = (Byte)(buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5]);
            //Console.WriteLine("Send:");
            //for (int i = 0; i < 7; i++)
            comPort.Write(buf, 0, buf.Length);
            Thread.Sleep(1000);
            int recNum = comPort.BytesToRead;
            //Console.WriteLine("recNum:"+recNum);
            if (recNum < 7)
                return false;
            byte[] recData = new byte[recNum];
            comPort.Read(recData, 0, recNum);
            //ret = (recData[2] << 16 + recData[3] << 8 + recData[4]) / 1000.0;
            //Console.WriteLine("ReceiveData:" + ret.ToString());
            return ret;
        }

        private static void ThreadMethod()
        {
            while (true)
            {
                SetVal = RS232CommunicationGetData(0x03);
                Thread.Sleep(500);
                TempVal = RS232CommunicationGetData(0x05);
                Thread.Sleep(500);
                if (m_SetStaus == true)
                {
                    m_SetStaus = false;
                    if (RS232CommunicationSetData(m_UserSetVal))
                    {
                        ModuleStatus = "Set Temp:" + m_UserSetVal.ToString() + " Success!";
                        Excel_Lgl.SaveLog("[ThreadMethod()]" + m_UserSetVal.ToString());
                    }
                    else
                    {
                        ModuleStatus = "Communication Error!";
                    }
                    Thread.Sleep(500);
                }

                //SetTempVal(12);
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
                comPort.StopBits = StopBits.Two;
                comPort.Parity = Parity.None;
                comPort.ReadBufferSize = 1024;
                if (!comPort.IsOpen)
                {
                    comPort.Open();
                }
                else
                {
                    comPort.Close();
                    comPort.Open();
                }
                Thread.Sleep(500);
                thread = new Thread(new ThreadStart(ThreadMethod));
                thread.Start();
                ModuleStatus = "Port Open Success";
                m_SetStaus = false;
                //Console.WriteLine("Port Open Success.\n");
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
        /// 获取水槽的端口状态
        /// </summary>
        /// <returns></returns>
        public static String GetModuleStatus()
        {
            return ModuleStatus;
        }
        /// <summary>
        /// 获取水槽现在的温度
        /// </summary>
        /// <returns></returns>
        public static double GetModuleVal()
        {
            return TempVal ;
        }
        /// <summary>
        /// 获取水槽需要设置的温度
        /// </summary>
        /// <returns></returns>
        public static double GetModuleSetVal()
        {
            return SetVal;
        }
        public static void SetTempVal(double temp)
        {
            m_SetStaus = true;
            m_UserSetVal = temp;
            Excel_Lgl.SaveLog("[SetTempVal]" + temp.ToString());
        }
        #endregion
    }
}
