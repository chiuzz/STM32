/*----------------------------------------------------------------
//----------------------------------------------------------------*/

using System;
using System.IO.Ports;
using System.Threading;
using Hokai;
using EXCEL_LGL;

namespace Module_HardWare
{
    /// <summary>控制模块
    /// 
    /// </summary>
    public class TempSensor
    {
        private static string serialportCOM = "COM3";
        private const int serialportBaudrate = 115200;
        private const int serialdataBits = 8;


        private static SerialPort comPort = new SerialPort();
        private static modbusRTU RTU = new modbusRTU();

        private static int retryTime = 0;

        private static double[] value = new double[7];
        private static Int16[] Advalue = new Int16[7];
        private static Thread thread;

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

        /// <summary>1路测温
        /// 
        /// </summary>
        public static double Temperature_01
        {
            get { return value[0]; }
        }
        public static double Temperature_02
        {
            get { return value[1]; }
        }
        public static double Temperature_03
        {
            get { return value[2]; }
        }
        public static double Temperature_04
        {
            get { return value[3]; }
        }
        public static double Temperature_05
        {
            get { return value[4]; }
        }
        public static double Temperature_06
        {
            get { return value[5]; }
        }
        public static double Temperature_07
        {
            get { return value[6]; }
        }
        public static Int16 AD_01
        {
            get { return Advalue[0]; }
        }
        public static Int16 AD_02
        {
            get { return Advalue[1]; }
        }
        public static Int16 AD_03
        {
            get { return Advalue[2]; }
        }
        public static Int16 AD_04
        {
            get { return Advalue[3]; }
        }
        public static Int16 AD_05
        {
            get { return Advalue[4]; }
        }
        public static Int16 AD_06
        {
            get { return Advalue[5]; }
        }
        public static Int16 AD_07
        {
            get { return Advalue[6]; }
        }

        #endregion

        #region 内部函数


        public static void SendStartCalcCmdPkg(string str, int PointNum)
        {
            try
            {

           
            int PkgNum = 19; 
            byte[] sendFrame = new byte[PkgNum];
            byte tmp=0;
            int i=0;
            while(i<PkgNum)
            {
                sendFrame[i] = 0;
                i++;
            }
            sendFrame[0] = 0xef;
            sendFrame[PkgNum-1] = 0xff;
            sendFrame[1] = 1;
            switch (str)
            {
                case "两点校准":
                    tmp = 1<<4;
                    break;
                case "多点校准":
                    tmp = 2<<4;
                    break;
                case "二次项校准":
                    tmp = 3<<4;
                    break;
                default: break;
            }
            sendFrame[2] = (byte)(tmp + PointNum);
            Console.WriteLine("Data: "+sendFrame[2]);
            for (i = 1; i< PkgNum-2; i++)
            {
                sendFrame[PkgNum-2] += sendFrame[i];
            }
            //for (i = 0; i < sendFrame.Length; i++)
            //{
                //sendFrame[i] = (byte)i;
                //Console.Write(sendFrame[i]);
            //}
            //Console.WriteLine("");
            comPort.Write(sendFrame, 0, sendFrame.Length);
          }
            catch (Exception ex)
            {
                Excel_Lgl.SaveLog("[SendStartCalcCmdPkg]" + ex.ToString());
            }
        }

        public static void SendSetVref(int val)
        {
            try
            {
            int PkgNum = 19;
            byte[] sendFrame = new byte[PkgNum];
            int i = 0;
            while (i < PkgNum)
            {
                sendFrame[i] = 0;
                i++;
            }
            sendFrame[0] = 0xef;
            sendFrame[PkgNum - 1] = 0xff;
            sendFrame[1] = 2;
            sendFrame[2] = (byte)((val&0xff00)>>8);
            sendFrame[3] = (byte)((val&0xff));
            for (i = 1; i < PkgNum - 2; i++)
            {
                sendFrame[PkgNum - 2] += sendFrame[i];
            }
            //for (i = 0; i < sendFrame.Length; i++)
            //{
                //sendFrame[i] = (byte)i;
                //Console.Write(sendFrame[i]);
            //}
            //Console.WriteLine("");
            comPort.Write(sendFrame, 0, sendFrame.Length);
           }
            catch (Exception ex)
            {
                Excel_Lgl.SaveLog("[SendSetVref]" + ex.ToString());
            }
        }

        public static void SendCalcStop()
        {
            int PkgNum = 19;
            byte[] sendFrame = new byte[PkgNum];
            int i = 0;
            while (i < PkgNum)
            {
                sendFrame[i] = 0;
                i++;
            }
            sendFrame[0] = 0xef;
            sendFrame[PkgNum - 1] = 0xff;
            sendFrame[1] = 5;
            for (i = 1; i < PkgNum - 2; i++)
            {
                sendFrame[PkgNum - 2] += sendFrame[i];
            }
            //for (i = 0; i < sendFrame.Length; i++)
            //{
                //sendFrame[i] = (byte)i;
                //Console.Write(sendFrame[i]);
            //}
            Console.WriteLine("SendCalcStop");
            comPort.Write(sendFrame, 0, sendFrame.Length);
        }

        public static void SendSetAdVal(int PointNo, Int16 val1, Int16 val2, Int16 val3, Int16 val4, Int16 val5, Int16 val6, Int16 val7)
        {
            try 
            {
           
            int PkgNum = 19;
            byte[] sendFrame = new byte[PkgNum];
            int i = 0;
            while (i < PkgNum)
            {
                sendFrame[i] = 0;
                i++;
            }
            Console.WriteLine("Send AD: "+val1+" "+val2+" "+val3+" "+val4+" "+val5+" "+val6+" "+val7);

            sendFrame[0] = 0xef;
            sendFrame[PkgNum - 1] = 0xff;
            sendFrame[1] = 3;
            sendFrame[2] = (byte)(PointNo);
            sendFrame[3] = (byte)((val1 & 0xff00)>>8);
            sendFrame[4] = (byte)(val1 & 0xff);
            sendFrame[5] = (byte)((val2 & 0xff00)>>8);
            sendFrame[6] = (byte)(val2 & 0xff);
            sendFrame[7] = (byte)((val3 & 0xff00)>>8);
            sendFrame[8] = (byte)(val3 & 0xff);
            sendFrame[9] = (byte)((val4 & 0xff00)>>8);
            sendFrame[10] = (byte)(val4 & 0xff);
            sendFrame[11] = (byte)((val5 & 0xff00)>>8);
            sendFrame[12] = (byte)(val5 & 0xff);
            sendFrame[13] = (byte)((val6 & 0xff00)>>8);
            sendFrame[14] = (byte)(val6 & 0xff);
            sendFrame[15] = (byte)((val7 & 0xff00)>>8);
            sendFrame[16] = (byte)(val7 & 0xff);
            for (i = 1; i < PkgNum - 2; i++)
            {
                sendFrame[PkgNum - 2] += sendFrame[i];
            }
            //for (i = 0; i < sendFrame.Length; i++)
            //{
                //sendFrame[i] = (byte)i;
                //Console.Write(sendFrame[i]);
            //}
            Console.WriteLine("SendSetAdVal");
            comPort.Write(sendFrame, 0, sendFrame.Length);
           }
            catch (Exception ex)
            {
                Excel_Lgl.SaveLog("[ SendSetAdVal]" + ex.ToString());
            }
        }

        public static void SendSetTempVal(int PointNo, Int16 val)
        {
            int PkgNum = 19;
            byte[] sendFrame = new byte[PkgNum];
            int i = 0;
            while (i < PkgNum)
            {
                sendFrame[i] = 0;
                i++;
            }
            Console.WriteLine("Send Temp: "+val);
            sendFrame[0] = 0xef;
            sendFrame[PkgNum - 1] = 0xff;
            sendFrame[1] = 4;
            sendFrame[2] = (byte)(PointNo);
            sendFrame[3] = (byte)((val & 0xff00)>>8);
            sendFrame[4] = (byte)(val & 0xff);
            sendFrame[5] = (byte)((val & 0xff00)>>8);
            sendFrame[6] = (byte)(val & 0xff);
            sendFrame[7] = (byte)((val & 0xff00)>>8);
            sendFrame[8] = (byte)(val & 0xff);
            sendFrame[9] = (byte)((val & 0xff00)>>8);
            sendFrame[10] = (byte)(val & 0xff);
            sendFrame[11] = (byte)((val & 0xff00)>>8);
            sendFrame[12] = (byte)(val & 0xff);
            sendFrame[13] = (byte)((val & 0xff00)>>8);
            sendFrame[14] = (byte)(val & 0xff);
            sendFrame[15] = (byte)((val & 0xff00)>>8);
            sendFrame[16] = (byte)(val & 0xff);
            for (i = 1; i < PkgNum - 2; i++)
            {
                sendFrame[PkgNum - 2] += sendFrame[i];
            }
            //for (i = 0; i < sendFrame.Length; i++)
            //{
                //sendFrame[i] = (byte)i;
                //Console.Write(sendFrame[i]);
            //}
            Console.WriteLine("SendSetTempVal");
            comPort.Write(sendFrame, 0, sendFrame.Length);
        }
        //

        static byte checksum(byte[] buffer, int count)
        {
            int i = 0;
            byte sum = 0;
            for (i = 1; i < count; i++) {
                sum += buffer[i];
            }
            return sum;            
        }
        
        /// <summary>测温仪获取温度值
        /// 测温仪获取温度值
        /// </summary>
        /// <param name="Device">测温模块选择</param>
        /// <param name="value">返回数值</param>
        /// <returns>错误码</returns>
        private static int GetTemperature()
        {
            try 
            { 
            int status = (int)errorCode.errorNoError;
            int recNum = comPort.BytesToRead;
            if (recNum != 0)
            {
                byte[] recData = new byte[recNum];
                comPort.Read(recData, 0, recNum);
                for (int i = 0; i < recNum; i++)
                {
                    //Console.Write(recData[i]);
                    //Console.Write(" ");
                }
                //Console.WriteLine(" ");
                switch (recData[0])
                {
                    case 0xef: //温度值
                        //if (checksum(recData, 18) == recData[18])
                        {
                            value[0] = ((recData[2] << 8) + recData[3]) / 100.0;
                            value[1] = ((recData[4] << 8) + recData[5]) / 100.0;
                            value[2] = ((recData[6] << 8) + recData[7]) / 100.0;
                            value[3] = ((recData[8] << 8) + recData[9]) / 100.0;
                            value[4] = ((recData[10] << 8) + recData[11]) / 100.0;
                            value[5] = ((recData[12] << 8) + recData[13]) / 100.0;
                            value[6] = ((recData[14] << 8) + recData[15]) / 100.0;
                            //Console.WriteLine("Get Temp: ", value[0] + " " + value[1] + " " + value[2] + " " + value[3] + " " + value[4] + " " + value[5] + " " + value[6]);
                        }
                        break;
                    case 0xfe: //AD值
                        //if (checksum(recData, 15) == recData[15])
                        {
                            Advalue[0] = (Int16)((recData[1] << 8) + recData[2]);
                            Advalue[1] = (Int16)((recData[3] << 8) + recData[4]);
                            Advalue[2] = (Int16)((recData[5] << 8) + recData[6]);
                            Advalue[3] = (Int16)((recData[7] << 8) + recData[8]);
                            Advalue[4] = (Int16)((recData[9] << 8) + recData[10]);
                            Advalue[5] = (Int16)((recData[11] << 8) + recData[12]);
                            Advalue[6] = (Int16)((recData[13] << 8 )+ recData[14]);
                            //Console.WriteLine("Get Ad: " + Advalue[0] + " " + Advalue[1] + " " + Advalue[2] + " " + Advalue[3] + " " + Advalue[4] + " " + Advalue[5] + " " + Advalue[6]);
                        }
                        break;
                    default: break;
                }
            }
            //写入返回结果
            //Console.WriteLine(value);
            //返回错误结果
            return status;
            }
            catch (Exception ex)
            {
                return 0; //异常报错
                Excel_Lgl.SaveLog("[GetTemperature]" + ex.ToString());
            }
        }

        private static void ThreadMethod()
        {
            int status = (int)errorCode.errorisBusyDeviceEnd;
            while (true)
            {
                status = GetTemperature();
                Thread.Sleep(10);
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

                Console.WriteLine("Port Open Success.\n");
                
                Thread.Sleep(500);
                thread = new Thread(new ThreadStart(ThreadMethod));
                thread.Start();
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Port Open Fail.\n");
                Excel_Lgl.SaveLog("[Open_sPort]" + ex.ToString());
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
                comPort.Close();
                thread.Abort();
                Console.WriteLine("Port Close Success.\n");
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Port Close Fail.\n");
                Excel_Lgl.SaveLog("[Open_sPort]" + ex.ToString());
                return false;
            }
        }

            #endregion


    }
}
