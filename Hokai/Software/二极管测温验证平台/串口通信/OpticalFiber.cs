/*----------------------------------------------------------------
// 和佳医疗设备股份有限公司
// 版权所有。 
// 
// 文件名：OpticalFiber.cs
// 文件功能描述：光纤测温控制反馈接口。
// 
// 
// 创建标识：创建人：林群仰 2015.05.12
// 
// 修改描述：林群仰 2016.01.30 修改提供修改串口通信接口，修改测试模块ID号接口
// 修改描述：林群仰 2016.05.12 更换测温仪，修改通信协议指令，删除原充电模块的功能
//----------------------------------------------------------------*/

using System;
using System.IO.Ports;
using System.Threading;
using Hokai;

namespace Module_HardWare
{
    /// <summary>光纤控制模块
    /// 
    /// </summary>
    public class OpticalFiber
    {
        private static string serialportCOM = "COM3";
        private const int serialportBaudrate = 19200;
        private const int serialdataBits = 8;


        private static SerialPort comPort = new SerialPort();
        private static modbusRTU RTU = new modbusRTU();

        private static int retryTime = 0;

        private static double[] value = new double[6];
        private static int[] err_mess_00 = new int[6];
        private static string[] err_mess_01 = new string[6];


        private static bool[] getData = new bool[7];

        private static Thread thread;

        private static SmoothData[] ad_Smooth;
        private static double[] adValue_Smooth = new double[6];   //经过平滑

        private static bool[] isErrConn = new bool[5]{false,false,false,false,false};


        #region 属性

        public static bool IsErrConn_01
        {
            get { return isErrConn[0];}
        }
        public static bool IsErrConn_02
        {
            get { return isErrConn[1]; }
        }
        public static bool IsErrConn_03
        {
            get { return isErrConn[2]; }
        }
        public static bool IsErrConn_04
        {
            get { return isErrConn[3]; }
        }
        public static bool IsErrConn_05
        {
            get { return isErrConn[4]; }
        }

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
            get
            {
                return adValue_Smooth[1];
            }
        }
        /// <summary>2路测温
        /// 
        /// </summary>
        public static double Temperature_02
        {
            get
            {
                return adValue_Smooth[2];
            }
        }
        /// <summary>3路测温
        /// 
        /// </summary>
        public static double Temperature_03
        {
            get
            {
                return adValue_Smooth[3];
            }
        }
        /// <summary>4路测温
        /// 
        /// </summary>
        public static double Temperature_04
        {
            get
            {
                return adValue_Smooth[4];
            }
        }
        /// <summary>5路测温
        /// 
        /// </summary>
        public static double Temperature_05
        {
            get { return adValue_Smooth[5]; }
        }


        #endregion

        #region 内部函数

        /// <summary>测温仪获取温度值
        /// 测温仪获取温度值
        /// </summary>
        /// <param name="Device">测温模块选择</param>
        /// <param name="value">返回数值</param>
        /// <returns>错误码</returns>
        private static int GetTemperature(byte Device, ref double value)
        {
            //status = (int)errorCode.errorWriteSingleRegister; 通讯错误，传参错误，写寄存器错误
            int status = (int)errorCode.errorNoError;
            byte[] sendFrame = new byte[7];
            byte[] data_temp = new byte[2];
            byte[] addr_temp = new byte[2];

            //第一步, 无错则获得读数包，返回错误信息
            if (status == (int)errorCode.errorNoError)
                status = RTU.TempModReadData(Device, ref sendFrame);

            //第二步，无错，则发送并延时接收读数包， 并检查数据包CRC
            if (status == (int)errorCode.errorNoError)
            {
                comPort.Write(sendFrame, 0, sendFrame.Length);
                Thread.Sleep(200);

                int recNum = comPort.BytesToRead;
                if (recNum < 7)
                    return (int)errorCode.errorFrameInfLack;
                byte[] recData = new byte[recNum];
                comPort.Read(recData, 0, recNum);

                status = RTU.TempModDataCheck(recData, ref data_temp);
            }
            //写入返回结果
            value = (data_temp[1] * 256 + data_temp[0]) / 100.0;
            //Console.WriteLine(value);
            //返回错误结果
            return status;
        }


        /// <summary>
        /// 往指定通道里加入AD数。
        /// </summary>
        /// <param name="i">通道号。</param>
        /// <param name="advalue">AD数。</param>
        private static void AddADValue(int i, double advalue)
        {
            ad_Smooth[i].Add(advalue);

            adValue_Smooth[i] = ad_Smooth[i].Value;
        }
        private static void InitializeSmooth()
        {
            //初始化数据平滑对象
            int num = 8;
            ad_Smooth = new SmoothData[6] {
                new SmoothData(num),new SmoothData(num),new SmoothData(num),new SmoothData(num),new SmoothData(num),
                new SmoothData(num)
            };

        }


        /// <summary>获取第一路温度值
        /// 获取第一路温度值
        /// </summary>
        /// <returns>返回通信状态</returns>
        /// 正常状态：(int)errorCode.errorNoError
        private static int cwyGetTemperature_1()
        {
            int status = (int)errorCode.errorisBusyDeviceEnd;
            int timeup = retryTime;
            byte[] data = new byte[2];
           
            status = GetTemperature(201, ref value[1]);

            if (status == (int)errorCode.errorNoError)
                isErrConn[0] = false;
            else
                isErrConn[0] = true;

            AddADValue(1, value[1]);
            if (value[1] > 5000)
                err_mess_01[1] = "未插好第一路光纤";
            else
                err_mess_01[1] = "";
            return status;
        }

        /// <summary>获取第二路温度值
        /// 获取第二路温度值
        /// </summary>
        /// <returns>返回通信状态</returns>
        /// 正常状态：(int)errorCode.errorNoError
        private static int cwyGetTemperature_2()
        {
            int status = (int)errorCode.errorisBusyDeviceEnd;
            int timeup = retryTime;
            byte[] data = new byte[2];
            status = GetTemperature(202, ref value[2]);

            if (status == (int)errorCode.errorNoError)
                isErrConn[1] = false;
            else
                isErrConn[1] = true;

            AddADValue(2, value[2]);
            if (value[2] > 5000)
                err_mess_01[2] = "未插好第二路光纤";
            else
                err_mess_01[2] = "";

            return status;
        }

        /// <summary>获取第三路温度值
        /// 获取第三路温度值
        /// </summary>
        /// <returns>返回通信状态</returns>
        /// 正常状态：(int)errorCode.errorNoError
        private static int cwyGetTemperature_3()
        {
            int status = (int)errorCode.errorisBusyDeviceEnd;
            int timeup = retryTime;
            byte[] data = new byte[2];
            status = GetTemperature(203, ref value[3]);

            if (status == (int)errorCode.errorNoError)
                isErrConn[2] = false;
            else
                isErrConn[2] = true;

            AddADValue(3, value[3]);
            if (value[3] > 5000)
                err_mess_01[3] = "未插好第二路光纤";
            else
                err_mess_01[3] = "";
            return status;
        }

        /// <summary>获取第四路温度值
        /// 获取第四路温度值
        /// </summary>
        /// <returns>返回通信状态</returns>
        /// 正常状态：(int)errorCode.errorNoError
        private static int cwyGetTemperature_4()
        {
            int status = (int)errorCode.errorisBusyDeviceEnd;
            int timeup = retryTime;
            byte[] data = new byte[2];
            status = GetTemperature(204, ref value[4]);

            if (status == (int)errorCode.errorNoError)
                isErrConn[3] = false;
            else
                isErrConn[3] = true;

            AddADValue(4, value[4]);
            if (value[4] > 5000)
                err_mess_01[4] = "未插好第四路光纤";
            else
                err_mess_01[4] = "";
            return status;
        }

        /// <summary>获取第五路温度值
        /// 获取第五路温度值
        /// </summary>
        /// <returns>返回通信状态</returns>
        /// 正常状态：(int)errorCode.errorNoError
        private static int cwyGetTemperature_5()
        {
            int status = (int)errorCode.errorisBusyDeviceEnd;
            int timeup = retryTime;
            byte[] data = new byte[2];
            status = GetTemperature(205, ref value[5]);

            if (status == (int)errorCode.errorNoError)
                isErrConn[4] = false;
            else
                isErrConn[4] = true;

            AddADValue(5, value[5]);
            if (value[5] > 5000)
                err_mess_01[5] = "未插好第五路光纤";
            else
                err_mess_01[5] = "";
            return status;
        }



        private static void ThreadMethod()
        {

            while (true)
            {
                if (getData[1])
                    err_mess_00[1] = cwyGetTemperature_1();
                if (getData[2])
                    err_mess_00[2] = cwyGetTemperature_2();
                if (getData[3])
                    err_mess_00[3] = cwyGetTemperature_3();
                if (getData[4])
                    err_mess_00[4] = cwyGetTemperature_4();
                if (getData[5])
                    err_mess_00[5] = cwyGetTemperature_5();

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

                InitializeSmooth();
                Thread.Sleep(500);
                thread = new Thread(new ThreadStart(ThreadMethod));
                thread.Start();
                return true;
            }
            catch
            {
                Console.WriteLine("Port Open Fail.\n");
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
            catch
            {
                Console.WriteLine("Port Close Fail.\n");
                return false;
            }
        }

        /// <summary>获取信息
        /// 
        /// </summary>
        public static void GetData(int num, bool value)
        {
            if (num < getData.Length)
                getData[num] = value;
        }


        /// <summary>故障信息1-5
        /// （1路测温，2路测温，3路测温，4路测温，5路测温，）
        /// </summary>
        public static string Err_Mess(int num)
        {
            try
            {
                return "编号：" + err_mess_00[num].ToString() + "——" + err_mess_01[num];
            }
            catch
            {
                return "";
            }
        }

        #endregion


    }
}
