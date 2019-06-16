using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace TemperatureCheck
{
    public partial class FormCheck : Form
    {
        #region 对象定义
        /// <summary>
        /// 串口对象
        /// </summary>
        private System.IO.Ports.SerialPort sp;

        private StringBuilder builder = new StringBuilder();
        private List<byte> buffer = new List<byte>(4096);
        /// <summary>
        /// 保存选择的通道数
        /// </summary>
        private int CheckCHIndex = 0;
        #endregion


        public FormCheck()
        {
            InitializeComponent();
            radioButDouble.Checked = true;
            try
            {
                ComInit();
                HardwareInit();
                test();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }

        
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }
        /// <summary>
        /// 硬件校准显示初始化
        /// </summary>
        public void HardwareInit()
        {
            try
            {
                CheckCH.Items.Add("通道1");
                CheckCH.Items.Add("通道2");
                CheckCH.Items.Add("通道3");
                CheckCH.SelectedIndex = 0;
                CheckCH.DropDownStyle = ComboBoxStyle.DropDownList;
                CheckCHIndex = CheckCH.SelectedIndex + 1;

                CheckTempLow.Text = "2800";
                CheckTempHigh.Text = "4300";
                CheckAdValue1.Text = "186";
                CheckAdValue2.Text = "3909";

            }
            catch (Exception ex)
            {

            }
        }

        /// <summary>
        /// 串口显示模块初始化
        /// </summary>
        public void ComInit()
        {

            sp = new SerialPort();//初始化串口对象
            sp.DataReceived += new SerialDataReceivedEventHandler(sp_DataReceived);
            butCloseCom.Enabled = false;
            butOpenCom.Enabled = true;
            ComStatus.Text = "串口关闭";
            string[] sAllPort = null;
            try
            {
                sAllPort = SerialPort.GetPortNames();
                foreach (string co in sAllPort)
                {
                    comPort.Items.Add(co);
                }

                if (comPort.Items.Count>0)
                {
                    comPort.SelectedIndex = 0;
                }
              
               
            }
            catch (Exception ex)
            {
                throw new Exception("获取计算机COM口列表失败!\r\n错误信息:" + ex.Message);
            }

        
            comPort.DropDownStyle = ComboBoxStyle.DropDownList;
            //列出常用的波特率
            comBaud.Items.Add("1200");
            comBaud.Items.Add("2400");
            comBaud.Items.Add("4800");
            comBaud.Items.Add("9600");
            comBaud.Items.Add("19200");
            comBaud.Items.Add("28800");
            comBaud.Items.Add("38400");
            comBaud.Items.Add("57600");
            comBaud.Items.Add("115200");
            comBaud.SelectedIndex = 4;
            comBaud.DropDownStyle = ComboBoxStyle.DropDownList;
            //列出数据位
            comData.Items.Add("8");
            comData.Items.Add("7");
            comData.Items.Add("6");
            comData.Items.Add("5");
            comData.SelectedIndex = 0;
            comData.DropDownStyle = ComboBoxStyle.DropDownList;
            //列出停止位
            comStop.Items.Add("0");
            comStop.Items.Add("1");
            comStop.Items.Add("1.5");
            comStop.Items.Add("2");
            comStop.SelectedIndex = 1;
            comStop.DropDownStyle = ComboBoxStyle.DropDownList;
            //列出奇偶校验位
            comCheck.Items.Add("None");
            comCheck.Items.Add("Odd");
            comCheck.Items.Add("Even");
            comCheck.Items.Add("Mark");
            comCheck.Items.Add("Space");
            comCheck.SelectedIndex = 0;
            comCheck.DropDownStyle = ComboBoxStyle.DropDownList;
        }
        int i = 0;
        /// <summary>
        /// 接受串口消息事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void sp_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int n = sp.BytesToRead;//待读字节个数

            byte[] buf = new byte[n];//创建n个字节的缓存
            byte[] ReceiveBytes = new byte[n];
            sp.Read(buf, 0, n);//读到在数据存储到buf
           
            //依次的拼接出16进制字符串  
            //foreach (byte b in buf)
            //{
            //    builder.Append(b.ToString("X2") + " ");
            //}

            //1.缓存数据
            buffer.AddRange(buf);//不断地将接收到的数据加入到buffer链表中
            //2.完整性判断
            while (buffer.Count >= 10) //根据设计文档定义的字节数
            {
                        //2.1 查找数据头
                        if (buffer[0] == 0xef) //传输数据有帧头用于判断找到帧头
                        {
                            byte bufCheck=(byte)(buffer[1]+buffer[2]+buffer[3]+buffer[4]+buffer[5]);
                            if (bufCheck == buffer[8]) //校验
                            {
                                //判断收到的数据是否选中的通道数据
                                if (buffer[1] == CheckCHIndex)
                                {
                                    this.Invoke((EventHandler)(delegate { this.ADValue.Text = Convert.ToString((buffer[6] << 8) + buffer[7]); }
                                         ));

                                    //if (buffer[1] == 0x01)
                                    //{
                                    //    this.Invoke((EventHandler)(delegate { this.ADValue.Text =Convert.ToString((buffer[6]<<8 )+ buffer[7]); }
                                    //      ));
                                    //}
                                    //if (buffer[1] == 0x02)
                                    //{
                                    //    this.Invoke((EventHandler)(delegate { this.CheckTemp.Text = buffer[6].ToString() + "." + buffer[7].ToString(); }
                                    //      ));
                                    //}
                                }

                                buffer.Clear();//处理完后,要把数据清除,准备接受下一次的数据信息
                                return;
                            } 
                    
                        }
                        else //帧头不正确时，记得清除
                        {
                            buffer.RemoveAt(0);//清除第一个字节，继续检测下一个。
                         }

            }
        }
        /// <summary>
        /// 点击打开串口按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void butOpenCom_Click(object sender, EventArgs e)
        {
            try
            {
                OpenCom();
                //thread = new Thread(new ThreadStart(ThreadMethod));
                //thread.Start();

            }
            catch (Exception ex)
            {

            }

            if (sp.IsOpen)
            {
                butCloseCom.Enabled = true;
                butOpenCom.Enabled = false;
                ComStatus.Text = "串口打开成功";
            }
            else
            {
                ComStatus.Text = "打开串口失败";
                butCloseCom.Enabled = false;
                butOpenCom.Enabled = true;
            }
          
        }
        //打开串口
        public void OpenCom()
        {
            int nSelect;
            butOpenCom.Enabled = false;
            Object selectedItem = comPort.SelectedItem;
            sp.PortName = selectedItem.ToString();//串口
            selectedItem = comBaud.SelectedItem;
            sp.BaudRate = int.Parse(selectedItem.ToString());//波特率
            nSelect = comData.SelectedIndex;//数据位
            switch (nSelect)
            {
                case 0:
                    sp.DataBits = 8;
                    break;
                case 1:
                    sp.DataBits = 7;
                    break;
                case 2:
                    sp.DataBits = 6;
                    break;
                case 3:
                    sp.DataBits = 5;
                    break;
            }
            nSelect = comCheck.SelectedIndex;
            switch (nSelect)
            {
                case 0:
                    sp.Parity = Parity.None;
                    break;
                case 1:
                    sp.Parity = Parity.Odd;
                    break;
                case 2:
                    sp.Parity = Parity.Even;
                    break;
                case 3:
                    sp.Parity = Parity.Mark;
                    break;
                case 4:
                    sp.Parity = Parity.Space;
                    break;
            }
            nSelect = comStop.SelectedIndex;
            switch (nSelect)
            {
                case 0:
                    sp.StopBits = StopBits.None;
                    break;
                case 1:
                    sp.StopBits = StopBits.One;
                    break;
                case 2:
                    sp.StopBits = StopBits.OnePointFive;
                    break;
                case 3:
                    sp.StopBits = StopBits.Two;
                    break;
            }
            sp.Open();
            
           
        }

        private void butCloseCom_Click(object sender, EventArgs e)
        {
            try 
            {
                //thread.Abort();
                sp.Close();
                butOpenCom.Enabled = true;
                butCloseCom.Enabled = false;
            }
            catch (Exception ex)
            {

            }
            if (sp.IsOpen)
            {
                ComStatus.Text = "关闭串口失败";
            }
            else
            {
                ComStatus.Text = "串口关闭";
            }
        }
        private static Thread thread;
        private void button3_Click(object sender, EventArgs e)
        {
            ShowAdValue(CheckCHIndex);

        }
        /// <summary>
        /// 显示AD的值
        /// </summary>
        public void ShowAdValue(int ch)
        {
            try
            {
                if (sp.IsOpen)//判断串口是否打开
                {
                    int n = 8;
                    byte[] buf = new byte[n];
                    buf[0] = 0xef; //包头
                    buf[1] = 0x02;   //发送命令,上传AD值
                    buf[2] = (byte)ch;//通道数
                    buf[3] = 0x01;//1-AD，2-TEMP
                    buf[4]= 0x00;
                    buf[5]= 0x00;
                    buf[6] = (byte)(buf[1] + buf[2] + buf[3] + buf[4] + buf[5]);
                    buf[7] = 0xff; //包尾
                    sp.Write(buf, 0, buf.Length);
                    Thread.Sleep(200);

                }
            }
            catch (Exception ex)
            {

            }
        }
        /// <summary>
        /// 发送串口消息
        /// </summary>
        public void ComSend(string[] _StringCom)
        {
            int IntLen = _StringCom.Length;
            byte[] _listByte = new byte[IntLen];
            switch (_StringCom[1])
            { 
                case "01":
                case "03":
                case "05":
                case "06":
                case "07":
                     for (int i = 0; i < IntLen; i++)
                    {
                        _listByte[i] = Convert.ToByte(_StringCom[i], 16);
                    }
                    
                    break;
                case "04":

                   _listByte[0]= Convert.ToByte(_StringCom[0], 16);
                   _listByte[1]= Convert.ToByte(_StringCom[1], 16);
                   _listByte[2]= Convert.ToByte(_StringCom[2], 16);
                   _listByte[3] = Convert.ToByte(_StringCom[3], 16);
                   if (string.IsNullOrEmpty(_StringCom[4]))
                   {
                       _StringCom[4] = "255";
                    }
                   int bufTemp = 0;
                    UInt16 buf=0;
                   try
                   {
                       bufTemp = (int)Convert.ToInt32(_StringCom[4]);
                       buf = (UInt16)Convert.ToInt16(bufTemp);
                      
                   }
                   catch (Exception ex)
                   {
                       buf = 65535;//输入的值太大就等于65535
                   }
                     _listByte[4] = (byte)((buf & 0xff00) >> 8);//(数据数值高8位),& 0xff00
                     _listByte[5] = (byte)(buf & 0x00ff);  //(数值低8位),
                     _listByte[7] = Convert.ToByte(_StringCom[7], 16);
                    break;

                default:
                    break;
            }
            _listByte[6] = (byte)(_listByte[1] + _listByte[2] + _listByte[3] + _listByte[4] + _listByte[5]);//校验
            sp.Write(_listByte, 0, IntLen);
            Thread.Sleep(200);
        }



        public void CheckHardware()
        {

            //进入校准模式01
            string[] _StartInt01 = { "EF","01", "00", "00", "00", "00", "01","FF" };
            ComSend(_StartInt01);
            //命令发送数据02,(通道号1,2,3),(数值类型1-AD，2-TEMP),(),(),校验
           // string[] _CommInt02 = { "239", "02", "01", "01", "00", "00", "04", "255" };
            //校准开始03,    (通道号1,2,3),(校准类型1-传感器，2-测量硬件)
            string[] _CommStartInt03 = { "EF", "03", CheckCHIndex.ToString("00"), "01", "00", "00", "00", "FF" };
            ComSend(_CommStartInt03);

            //发送校准数据04,(数值类型1-AD，2-TEMP),(1-10点数序号),(数据数值高8位),(数值低8位),
            string[] _CommCheckAdValue1 = { "EF", "04", "01", "01", CheckAdValue1.Text, "00", "00", "FF" };
            ComSend(_CommCheckAdValue1);

            string[] _CommCheckTempHigh = { "EF", "04", "02", "01", CheckTempLow.Text, "00", "00", "FF" };
            ComSend(_CommCheckTempHigh);

            string[] _CommCheckAdValue2 = { "EF", "04", "01", "02", CheckAdValue2.Text, "00", "00", "FF" };
            ComSend(_CommCheckAdValue2);

            string[] _CommCheckTempLow = { "EF", "04", "02", "02", CheckTempHigh.Text, "00", "00", "FF" };
            ComSend(_CommCheckTempLow);

            //配置1单毯或者0双毯模式
            if (radioButSingle.Checked)
            {
                string[] _CommOutInt07 = { "EF", "07", "01", "00", "00", "00", "06", "FF" };
                ComSend(_CommOutInt07);
            }
            else
            {
                string[] _CommOutInt07 = { "EF", "07", "00", "00", "00", "00", "06", "FF" };
                ComSend(_CommOutInt07);
            }
            //命令校准结束05, (校准模式1-两点校准，2-多点校准，3-多项式),(校准总点数)
            string[] _CommEndInt05 = { "EF", "05", "00", "00", "00", "00", "06", "FF" };
            ComSend(_CommEndInt05);
            //退出校准模式06
            string[] _CommOutInt06 = { "EF", "06", "00", "00", "00", "00", "06", "FF" };
            ComSend(_CommOutInt06);
            


            //获取通道AD值  ,(通道号1,2,3)
           // string[] _AdValutInt10 = { "239", "10", "1", "00", "00", "00", "11", "255" };



            //计算k值.b值
            int [] x_V=new int[2];
             x_V[0]=Convert.ToInt32(CheckAdValue1.Text);
            x_V[1]=Convert.ToInt32(CheckAdValue2.Text);

             int [] y_V=new int[2];
             y_V[0] = Convert.ToInt32(CheckTempLow.Text);
             y_V[1] = Convert.ToInt32(CheckTempHigh.Text);

            m_K=calculateSlope(x_V, y_V);
            text_K.Text = m_K.ToString();
            m_B=calculateConstant(x_V, y_V);
            text_B.Text = m_B.ToString();


        }

        double m_K;
        double m_B;

        public string[] CheckString(string[] CheckStr)
        {
            int[] check = new int [6];
           // check[1] = Convert.ToInt32();

            
            
            
            
            return CheckStr;
        }

        public void test()
        {
            //string[] _lstInt16 = { "cb", "04", "02", "a9", "08" };
            //byte[] _lstByte = new byte[_lstInt16.Length];
            //for (int i = 0; i < _lstInt16.Length; i++)
            //{
            //    _lstByte[i] = Convert.ToByte(_lstInt16[i], 16);
            //}
            //ushort buf = 0x252e;
            //UInt16 buf = 0x252e;
            //byte cmd = (byte)((buf & 0xff00) >> 8);
            //byte data = (byte)(buf & 0x00ff);
           // SendSetTempVal(16, 0x252e);
            //测试k值.b值
            int[] ix = new int[2];
            int[] iy = new int[2];
            ix[0] = 100;
            ix[1] = 200;
            iy[0] = 200;
            iy[1] = 300;

            //int k=calculateSlope(ix,iy);
            //int b = calculateConstant(ix, iy);



        }

     


        /// <summary>
        /// 选择通道
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CheckCH_SelectedIndexChanged(object sender, EventArgs e)
        {
            CheckCHIndex = CheckCH.SelectedIndex + 1;
        }

        /// <summary>
        /// 点击硬件校准按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void butHardwareCheck_Click(object sender, EventArgs e)
        {
            CheckHardware();
        }

        public void ShowTempValue(int ch)
        {
            try
            {
                if (sp.IsOpen)//判断串口是否打开
                {
                    int n = 8;
                    byte[] buf = new byte[n];
                    buf[0] = 0xef; //包头
                    buf[1] = 0x02;   //发送命令,上传温度值
                    buf[2] = (byte)ch;//通道数
                    buf[3] = 0x02;//1-AD，2-TEMP
                    buf[4] = 0x00;
                    buf[5] = 0x00;
                    buf[6] = (byte)(buf[1] + buf[2] + buf[3] + buf[4] + buf[5]);
                    buf[7] = 0xff; //包尾
                    sp.Write(buf, 0, buf.Length);
                    ReadComData();
                }
            }
            catch (Exception ex)
            {

            }
        }


        public void ReadComData()
        {
            int n = sp.BytesToRead;//待读字节个数
           
            byte[] buf = new byte[n];//创建n个字节的缓存
            byte[] ReceiveBytes = new byte[n];
            sp.Read(buf, 0, n);//读到在数据存储到buf
            //1.缓存数据
            buffer.AddRange(buf);//不断地将接收到的数据加入到buffer链表中
            //2.完整性判断
            while (buffer.Count >= 10) //根据设计文档定义的字节数
            {
                //2.1 查找数据头
                if (buffer[0] == 0xef) //传输数据有帧头用于判断找到帧头
                {
                    byte bufCheck = (byte)(buffer[1] + buffer[2] + buffer[3] + buffer[4] + buffer[5]);
                    if (bufCheck == buffer[8]) //校验
                    {
                        Console.Write((i++).ToString() + "\r\n");
                        if (buffer[1] == 0x01)
                        {
                            this.Invoke((EventHandler)(delegate { this.ADValue.Text = buffer[6].ToString() + "." + buffer[7].ToString(); }
                              ));
                        }
                        if (buffer[1] == 0x02)
                        {
                            this.Invoke((EventHandler)(delegate { this.CheckTemp.Text = buffer[6].ToString() + "." + buffer[7].ToString(); }
                              ));
                        }
                        Console.Write((i++).ToString()+"\r\n");

                    }
                    buffer.Clear();//处理完后,要把数据清除,准备接受下一次的数据信息
                    
                    return;
                }
                else //帧头不正确时，记得清除
                {
                    buffer.RemoveAt(0);//清除第一个字节，继续检测下一个。
                }

            }
        }

        private void ThreadMethod()
        {
            int status = 0;
            while (true)
            {
                ReadComData();
                Thread.Sleep(10);
            }
        }



        /// <summary>
        /// 显示温度按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void butCheckTemp_Click(object sender, EventArgs e)
        {
            ShowTempValue(CheckCHIndex);int []a = new int[2];

            
        }

        /// <summary>
        ///  计算k值
        /// </summary>
        /// <param name="x_V"></param>
        /// <param name="y_V"></param>
        /// <returns></returns>
   
        public  double calculateSlope(int [] x_V, int [] y_V)
        {
            double v = 0;
            double v1=0;
            double v2=0;
            v1=y_V[1] - y_V[0];
            v2 = x_V[1] - x_V[0];
            v=v1/v2;
            //v = (y_V[1] - y_V[0]) / (x_V[1] - x_V[0]);
             return v;
        }

        /// <summary>
        ///  计算常数b值
        /// </summary>
        /// <param name="x_V"></param>
        /// <param name="y_V"></param>
        /// <returns></returns>
        public double calculateConstant(int[] x_V, int[] y_V)
        {

            double return_Vlaue;
            double y_x = (y_V[1] * (x_V[1] - x_V[0]) - x_V[1] * (y_V[1] - y_V[0]));
            double xx = (x_V[1] - x_V[0]);
            return_Vlaue=y_x/xx;

            return return_Vlaue;
            
            //return (y_V[1]*(x_V[1] - x_V[0]) - x_V[1]*(y_V[1] - y_V[0])) / (x_V[1] - x_V[0]);
        }

        private void ADValue_TextChanged(object sender, EventArgs e)
        {

            CheckTemp.Text = (Convert.ToInt32(ADValue.Text) * m_K + m_B).ToString();
        }


    }
}
