using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;
using System.Text.RegularExpressions;
using System.Collections;
using System.Threading;
using Module_HardWare;
using Hokai;
using Module_Omega;
using Module_WaterTank;
using EXCEL_LGL;
using Excel = Microsoft.Office.Interop.Excel;

namespace 串口通信
{
    public partial class Form1 : Form
    {
        //public SerialPort _serialPort;

        //***************画图需要*************
        Hokai.CurveF cf_Temp01;       //温度曲线
        Hokai.CurveF cf_Temp02;       //温度曲线
        Hokai.CurveF cf_Temp03;       //温度曲线
        Hokai.CurveF cf_Temp04;       //温度曲线
        Hokai.CurveF cf_Temp05;       //温度曲线
        Hokai.CurveF cf_Temp06;       //温度曲线
        Hokai.CurveF cf_Temp07;       //温度曲线
        Hokai.CurveF cf_TempSrcC;       //温度曲线
        /// <summary>
        /// 基准温度曲线
        /// </summary>
        Hokai.CurveF cf_TempSrc;//基准温度曲线
        /// <summary>
        /// 设定温度曲线
        /// </summary>
        Hokai.CurveF cf_TempSet;       //设定温度曲线
        /// <summary>
        /// 真实温度曲线
        /// </summary>
        Hokai.CurveF cf_TempReal;       //真实温度曲线
        /// <summary>
        /// X轴结束值
        /// </summary>
        private double timeRange2 = 180;    //X轴结束值
        /// <summary>
        /// X轴起始值
        /// </summary>
        private double timeRange1 = 0;      //X轴起始值
        /// <summary>
        /// 曲线绘制时间
        /// </summary>
        private float time_CureDraw = 0;      //曲线绘制时间
        /// <summary>
        /// 启动治疗时间点
        /// </summary>
        private DateTime dt_CureStart;  //启动治疗时间点

        /// <summary>
        /// 图表的温度最大值
        /// </summary>
        private double CureDrawMax;
        /// <summary>
        /// 图表的温度最小值
        /// </summary>
        private double CureDrawMin;

       /// <summary>
        /// 温度稳定时间
       /// </summary>
        private int m_StableTime;
        /// <summary>
        /// 温度设定值
        /// </summary>
        private double m_SetTemp;
        /// <summary>
        /// 温度最大值
        /// </summary>
        private int m_MaxSetTemp;
        /// <summary>
        /// 温度最小值
        /// </summary>
        private int m_MinSetTemp;
        /// <summary>
        /// 温度采样时间
        /// </summary>
        private int m_SimgleTime;
        /// <summary>
        /// 温度控制步幅
        /// </summary>
        private int m_StepCount;

        private int m_ADsrc;
        private bool m_TestStatus;
        /// <summary>
        /// 温度稳定+温度采样的总时间
        /// </summary>
        private int m_CmdCycleTime;
        /// <summary>
        /// 点击开始按钮的时候当前时间,
        /// </summary>
        private DateTime m_CmdCycleCount;

        private Int16 m_SendIndex=0;
        private Int16[] m_AdData = new Int16[7];
        private Int16[] m_TempData = new Int16[7];
        /// <summary>
        /// 软键盘
        /// </summary>
        internal DlgNumPad dlgNumPad;
        /// <summary>
        /// 保存温度测试数据的路径
        /// </summary>
        private string TestDataFileStr = "";
        /// <summary>
        /// 保存AD数据的路径
        /// </summary>
        private string AD_DataFileStr = "";
        /// <summary>
        /// 保存日志信息
        /// </summary>
        private string LogDataFileStr = "";
        /// <summary>
        /// 保存温度excel路径
        /// </summary>
        private string TestDataPath = "";
        /// <summary>
        /// 保存AD-excel路径
        /// </summary>
        private string AD_DataPath = "";


        public Form1()
        {
            InitializeComponent();
            Timelabel.Visible = false;//开始的时候,使倒计时文本框不可见
            TestDataPath = System.Windows.Forms.Application.StartupPath + @"\Record\TestData";
            AD_DataPath = System.Windows.Forms.Application.StartupPath + @"\Record\AD_Data";
            LogDataFileStr = System.Windows.Forms.Application.StartupPath + @"\Record\LOG.txt";
            this.AutoScroll = true;//滚动条
            Excel_Lgl.LogFilePath = LogDataFileStr;//写日志的路径
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;//???
            dlgNumPad = new DlgNumPad();
            Init();
            /* ***************************串口设置****************************************/
        }
        private void Init()
        {
            cf_Temp01 = new Hokai.CurveF();
            cf_Temp02 = new Hokai.CurveF();
            cf_Temp03 = new Hokai.CurveF();
            cf_Temp04 = new Hokai.CurveF();
            cf_Temp05 = new Hokai.CurveF();
            cf_Temp06 = new Hokai.CurveF();
            cf_Temp07 = new Hokai.CurveF();
            cf_TempSrcC= new Hokai.CurveF();

            cf_TempReal = new Hokai.CurveF();
            cf_TempSet = new Hokai.CurveF();
            cf_TempSrc = new Hokai.CurveF();

            dt_CureStart = new DateTime();
            timer1.Enabled = true;

            btnOpenSenial.Enabled = true;
            btnCloseSenial.Enabled = false;

            tBCtrlMax.Enabled = false;
            tBCtrlMin.Enabled = false;
            tbCtrlStep.Enabled = false;
            tbCtrlSet.Enabled = true;
            tbSimgleTime.Enabled = false;
            m_StableTime = 25  ;
            tbStableTime.Text = m_StableTime.ToString();

            m_SetTemp = 5.0;
            tbCtrlSet.Text = m_SetTemp.ToString();

            m_MaxSetTemp = 50;
            tBCtrlMax.Text = m_MaxSetTemp.ToString();
            m_MinSetTemp = 30;
            tBCtrlMin.Text = m_MinSetTemp.ToString();

            m_SimgleTime = 5;
            tbSimgleTime.Text = m_SimgleTime.ToString();

            m_StepCount = 4;
            tbCtrlStep.Text = m_StepCount.ToString();

            m_ADsrc = 33300;
            double tmp = m_ADsrc / 10000.0;

            btTestStop.Enabled = false;
            btTestStart.Enabled = true;
            m_TestStatus = false;
        }
         //设置绘图控件的时间刻度
        private void Curve_SetCurveTimeTick(double timeRange)
        {
            int TickNum = 7;
            double i = 0;
            if (timeRange < 60)
                i = timeRange;
            else if (timeRange < 60 * TickNum)
                i = 60;
            else
            {
                i = Math.Floor(timeRange / 60);        //获取分钟的整数部分
                i = Math.Round(i / TickNum);           //四舍五入
                i *= 60;                               //转化成秒
            }
            CureDraw_Temp.TimeTick = i;
            CureDraw_Temp.SmallTimeTick = i / 4;

            CureDraw_Src.TimeTick = i;
            CureDraw_Src.SmallTimeTick = i / 4;
        }

        private void Curve_SetCurveDraw()
        {
            //清除绘图控件的显示数据
            CureDraw_Temp.ClearCurves();
            CureDraw_Src.ClearCurves();

            //重新设置Temp刻度范围
            CureDraw_Temp.LeftValueRange = new double[] { CureDrawMin, CureDrawMax };
            CureDraw_Temp.RightValueRange = new double[] { CureDrawMin, CureDrawMax };
            CureDraw_Src.LeftValueRange = new double[] { CureDrawMin, CureDrawMax };
            CureDraw_Src.RightValueRange = new double[] { CureDrawMin, CureDrawMax };

            //重新设置时间刻度范围
            CureDraw_Temp.TimeRange = new double[] { timeRange1, timeRange2 };
            CureDraw_Src.TimeRange = new double[] { timeRange1, timeRange2 };
            Curve_SetCurveTimeTick(timeRange2);

            //第二绘图控件
            CureDraw_Temp.AddCurve(cf_Temp01);
            CureDraw_Temp.AddCurve(cf_Temp02);
            CureDraw_Temp.AddCurve(cf_Temp03);
            CureDraw_Temp.AddCurve(cf_Temp04);
            CureDraw_Temp.AddCurve(cf_Temp05);
            CureDraw_Temp.AddCurve(cf_Temp06);
            CureDraw_Temp.AddCurve(cf_Temp07);
            CureDraw_Temp.AddCurve(cf_TempSrcC);
            cf_Temp01.Name = "CH1 (℃)";
            cf_Temp02.Name = "CH2 (℃)";
            cf_Temp03.Name = "CH3 (℃)";
            cf_Temp04.Name = "CH4 (℃)";
            cf_Temp05.Name = "CH5 (℃)";
            cf_Temp06.Name = "CH6 (℃)";
            cf_Temp07.Name = "CH7 (℃)";
            cf_TempSrcC.Name = "基准源 (℃)";
            cf_Temp01.CurvePen = new Pen(Color.LightBlue, 2);
            cf_Temp02.CurvePen = new Pen(Color.LightCoral, 2);
            cf_Temp03.CurvePen = new Pen(Color.LightCyan, 2);
            cf_Temp04.CurvePen = new Pen(Color.LightGoldenrodYellow, 2);
            cf_Temp05.CurvePen = new Pen(Color.LightGreen, 2);
            cf_Temp06.CurvePen = new Pen(Color.LightYellow, 2);
            cf_Temp07.CurvePen = new Pen(Color.LightSteelBlue, 2);
            cf_TempSrcC.CurvePen = new Pen(Color.Cyan, 2);

            CureDraw_Src.AddCurve(cf_TempSrc);
            CureDraw_Src.AddCurve(cf_TempSet);
            CureDraw_Src.AddCurve(cf_TempReal);
            cf_TempSrc.Name = "基准源 (℃)";
            cf_TempSet.Name = "设定值 (℃)";
            cf_TempReal.Name = "显示值 (℃)";
            cf_TempSrc.CurvePen = new Pen(Color.Cyan, 2);
            cf_TempSet.CurvePen = new Pen(Color.LightCoral, 2);
            cf_TempReal.CurvePen = new Pen(Color.LightCyan, 2);

            //设置默认的曲线
            CureDraw_Temp.SelectableCurveIndex = 0;
            CureDraw_Src.SelectableCurveIndex = 0;
        }

        #region 列出本机所有串口
        /// <summary>
        /// 列出本机所有串口
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            listBox1.Items.AddRange(ports);
            listBox2.Items.AddRange(ports);
            listBox3.Items.AddRange(ports);
        }
        #endregion

        #region 打开串口
        /// <summary>
        /// 打开串口
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOpenSenial_Click(object sender, EventArgs e)
        {
            try
            {
                string port_name = listBox1.SelectedItem.ToString();                  //获取并显示串口端口
                TempSensor.COM_Name = port_name;

                if (TempSensor.Open_sPort() == true)
                {
                    labelTempStatus.Text = "Port Open Success";//tommy 2017-2-22
                }
                else
                {
                    labelTempStatus.Text = "Port Open Fail";//tommy 2017-2-22
                    return;
                }

                double tmp01 = TempSensor.Temperature_01;
                double tmp02 = TempSensor.Temperature_02;
                double tmp03 = TempSensor.Temperature_03;
                double tmp04 = TempSensor.Temperature_04;
                double tmp05 = TempSensor.Temperature_05;
                double tmp06 = TempSensor.Temperature_06;
                double tmp07 = TempSensor.Temperature_07;

                double tmp08 = (tmp01 + tmp02 + tmp03 + tmp04 + tmp05 + tmp06 + tmp07) / 7;

                label36.Text = tmp08.ToString("0.00"); ;

                Int16 iAd01 = TempSensor.AD_01;
                Int16 iAd02 = TempSensor.AD_02;
                Int16 iAd03 = TempSensor.AD_03;
                Int16 iAd04 = TempSensor.AD_04;
                Int16 iAd05 = TempSensor.AD_05;
                Int16 iAd06 = TempSensor.AD_06;
                Int16 iAd07 = TempSensor.AD_07;



                for (int i = 0; i < 7; i++)
                {
                    //TempSensor.GetData(i, true);
                }
                btnOpenSenial.Enabled = false;
                btnCloseSenial.Enabled = true;
            }
            catch (Exception ex)
            {
                Excel_Lgl.SaveLog("[btnOpenSenial_Click]" + ex.ToString());
            }

        }
        #endregion

        #region 关闭串口
        /// <summary>
        /// 串口停止工作
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCloseSenial_Click(object sender, EventArgs e)
        {
            TempSensor.Close_sPort();
            //设置按钮的状态
            btnOpenSenial.Enabled = true;
            btnCloseSenial.Enabled = false;
        }
        #endregion

        private void Curve_SetCurveTimerRange()
        {
            CureDraw_Temp.TimeRange = new double[] { 0, timeRange2 };
            CureDraw_Src.TimeRange = new double[] { 0, timeRange2 };
            Curve_SetCurveTimeTick(timeRange2);
        }

        #region 定时处理函数

        bool timeStart = false;
        private void timer1_Tick(object sender, EventArgs e)
        {
            /// Omega设备的温度
            double OmegaTemp = Omega.GetModuleVal();
            ///水槽现在的温度
            double TankTemp = WaterTank.GetModuleVal();
            ///水槽需要设置的温度
            double TankSet = WaterTank.GetModuleSetVal();

            labelOmegaStatus.Text = Omega.GetModuleStatus();
            labelOmegaTemp.Text = OmegaTemp .ToString();
            labelTankStatus.Text = WaterTank.GetModuleStatus();
            labelTankTemp.Text =TankTemp.ToString() ;
            labelTankSet.Text = TankSet.ToString() ;

            if (m_TestStatus== true)
            {
                time_CureDraw = (float)((DateTime.Now - dt_CureStart).TotalSeconds);
                if (time_CureDraw >= timeRange2)
                {
                    timeRange2 = timeRange2 + 1;
                    Curve_SetCurveTimerRange();    //重设时间刻度
                }

                double tmp01 = TempSensor.Temperature_01;
                double tmp02 = TempSensor.Temperature_02;
                double tmp03 = TempSensor.Temperature_03;
                double tmp04 = TempSensor.Temperature_04;
                double tmp05 = TempSensor.Temperature_05;
                double tmp06 = TempSensor.Temperature_06;
                double tmp07 = TempSensor.Temperature_07;
                switch (cbSelectMode.SelectedItem.ToString())
                {
                    case "两点校准":
                    case "多点校准":
                    case "二次项校准":
                        tmp01 = 0;tmp02 = 0;tmp03 = 0;tmp04 = 0;
                        tmp05 = 0;tmp06 = 0;tmp07 = 0;
                        break;
                    default: break;
                }

                Console.WriteLine(tmp01.ToString()+" "+tmp02.ToString()+" "+tmp03.ToString()+" "+
                    tmp04.ToString()+" "+tmp05.ToString()+" "+tmp06.ToString()+" "+tmp07.ToString());

                cf_Temp01.AddPoint(new PointF(time_CureDraw, (float)tmp01));
                cf_Temp02.AddPoint(new PointF(time_CureDraw, (float)tmp02));
                cf_Temp03.AddPoint(new PointF(time_CureDraw, (float)tmp03));
                cf_Temp04.AddPoint(new PointF(time_CureDraw, (float)tmp04));
                cf_Temp05.AddPoint(new PointF(time_CureDraw, (float)tmp05));
                cf_Temp06.AddPoint(new PointF(time_CureDraw, (float)tmp06));
                cf_Temp07.AddPoint(new PointF(time_CureDraw, (float)tmp07));
                cf_TempSrcC.AddPoint(new PointF(time_CureDraw, (float)OmegaTemp));

                CureDraw_Temp.UpdateCurves();
                CureDraw_Temp.Update();

                cf_TempSrc.AddPoint(new PointF(time_CureDraw, (float)OmegaTemp));
                cf_TempSet.AddPoint(new PointF(time_CureDraw, (float)TankSet));
                cf_TempReal.AddPoint(new PointF(time_CureDraw, (float)TankTemp));
                CureDraw_Src.UpdateCurves();
                CureDraw_Src.Update();
                //-----------------------
                //Int16 iAd01 = TempSensor.AD_01;
                //Int16 iAd02 = TempSensor.AD_02;
                //Int16 iAd03 = TempSensor.AD_03;
                //Int16 iAd04 = TempSensor.AD_04;
                //Int16 iAd05 = TempSensor.AD_05;
                //Int16 iAd06 = TempSensor.AD_06;
                //Int16 iAd07 = TempSensor.AD_07;

                //Excel_Lgl.SaveLog("[timer1_Tick]" + "AD:" + iAd01.ToString() + iAd02.ToString() + iAd03.ToString() + iAd04.ToString() + iAd05.ToString() + iAd06.ToString() + iAd07.ToString());

                switch (cbSelectMode.SelectedItem.ToString())
                {
                    case "单点测试":
                        Timer_SingleProc();
                        break;
                    case "温域测试":
                        Timer_FiledProc();
                        break;
                    case "两点校准":
                        Timer_KBPointCalcProc();
                        break;
                    case "多点校准":
                        Timer_MitPointCalcProc();
                        break;
                    case "二次项校准":
                        break;
                    default: break;
                }
            }

            //显示剩余时间
            if (Timelabel.Visible)
            {
                if (ts.TotalSeconds >0)
                {
                    Timelabel.Text = ts.Hours.ToString().PadLeft(2, '0') + ":" + ts.Minutes.ToString().PadLeft(2, '0') + ":" + ts.Seconds.ToString().PadLeft(2, '0');
                    ts = ts.Subtract(new TimeSpan(0, 0, 1));

                }
                else
                {
                    Timelabel.Text = "00:00:00";
                }
            
            }
        }
        #endregion

        Thread ThreadExcel;//写excel文件的进程


        /// <summary>
        /// 单点测试
        /// </summary>
        private void Timer_SingleProc() //周期处理定时，单点测试
        {
            try
            {
                float time;
                time = (float)((DateTime.Now - dt_CureStart).TotalSeconds);
                if (time > m_StableTime * 60)
                {
                    //ThreadExcel = new Thread(SaveData);
                    //ThreadExcel.Start();
                     SaveData();
                }
            }
            catch (Exception ex)
            {
                Excel_Lgl.SaveLog("[Timer_SingleProc]" + ex.ToString());
            }


           
        }

        private void Timer_FiledProc() //周期处理定时，温域测试
        {
            float time;
            time = (float)((DateTime.Now - m_CmdCycleCount).TotalSeconds);
            if (time > m_CmdCycleTime * 60)
            {
                m_CmdCycleCount = DateTime.Now;
                //m_SetTemp += (m_MaxSetTemp - m_MinSetTemp) / m_StepCount;
                m_SetTemp = m_SetTemp+Convert.ToDouble(m_StepCount);
                if (m_SetTemp > m_MaxSetTemp)
                {
                    TestStop();
                }
                else
                {
                    WaterTank.SetTempVal(m_SetTemp);
                   // labelTankStatus.Text = WaterTank.GetModuleStatus();//水槽
                }
            }
            else if (time > m_StableTime * 60)
            {
                SaveData();
            }
        }
        /// <summary>
        /// 多点校准
        /// </summary>
        private void Timer_MitPointCalcProc()
        { 
            float time;
            time = (float)((DateTime.Now - m_CmdCycleCount).TotalSeconds);
            if (time > m_CmdCycleTime * 60)
            {
                m_CmdCycleCount = DateTime.Now;
                //m_SetTemp += (m_MaxSetTemp - m_MinSetTemp) / m_StepCount;
                m_SetTemp = m_SetTemp + Convert.ToDouble(m_StepCount);
                if (m_SetTemp > m_MaxSetTemp)
                {
                    TestStop();
                    TempSensor.SendCalcStop();
                }
                else
                {
                    //写入AD数据到文件
                    //Thread.Sleep(100);
                    //TempSensor.SendSetAdVal(0, 1000, 1001, 1002, 1000, 1500, 1000, 100);
                    //Thread.Sleep(100);
                    //TempSensor.SendSetTempVal(0, 2000, 2001, 2002, 2000, 2500, 2000, 200);
                    //Thread.Sleep(100);
                    Int16 iAd01 = TempSensor.AD_01;
                    Int16 iAd02 = TempSensor.AD_02;
                    Int16 iAd03 = TempSensor.AD_03;
                    Int16 iAd04 = TempSensor.AD_04;
                    Int16 iAd05 = TempSensor.AD_05;
                    Int16 iAd06 = TempSensor.AD_06;
                    Int16 iAd07 = TempSensor.AD_07;
                    TempSensor.SendSetAdVal(m_SendIndex, TempSensor.AD_01, TempSensor.AD_02, TempSensor.AD_03, TempSensor.AD_04,
                        TempSensor.AD_05, TempSensor.AD_06, TempSensor.AD_07);

                    Console.WriteLine("AD:" + iAd01.ToString() + iAd02.ToString() + iAd03.ToString() + iAd04.ToString() + iAd05.ToString() + iAd06.ToString() + iAd07.ToString());
                    Console.WriteLine("Temp:" + WaterTank.GetModuleVal().ToString());
                    SaveAdData();
                    Thread.Sleep(100);
                    Int16 TankTemp = (Int16)(WaterTank.GetModuleVal() * 100);

                    Int16 tmp = (Int16)(Omega.GetModuleVal() * 100);
                    TempSensor.SendSetTempVal(m_SendIndex, tmp);
                    Thread.Sleep(100);
                    m_SendIndex++;
                    WaterTank.SetTempVal(m_SetTemp);
                 }

            }
            else if (time > m_StableTime * 60)
            {
                //处理AD数据
            }
        }
        /// <summary>
        /// 倒计时TimeSpan
        /// </summary>
        TimeSpan ts = new TimeSpan(0, 0, 0);
        /// <summary>
        /// 两点校准
        /// </summary>
        private void Timer_KBPointCalcProc()
        {

            float time;
            time = (float)((DateTime.Now - m_CmdCycleCount).TotalSeconds);
            Console.WriteLine("Runtime: "+time+" CycleTime: "+m_CmdCycleTime*60 );
            if (time > m_CmdCycleTime * 60)
            {
                m_CmdCycleCount = DateTime.Now;
                m_SetTemp += m_MaxSetTemp - m_MinSetTemp;
                
                //写入AD数据到文件
                //Thread.Sleep(100);
                Int16 iAd01 = TempSensor.AD_01;
                Int16 iAd02 = TempSensor.AD_02;
                Int16 iAd03 = TempSensor.AD_03;
                Int16 iAd04 = TempSensor.AD_04;
                Int16 iAd05 = TempSensor.AD_05;
                Int16 iAd06 = TempSensor.AD_06;
                Int16 iAd07 = TempSensor.AD_07;
                TempSensor.SendSetAdVal(m_SendIndex, TempSensor.AD_01, TempSensor.AD_02, TempSensor.AD_03, TempSensor.AD_04,
                    TempSensor.AD_05, TempSensor.AD_06, TempSensor.AD_07);

                Console.WriteLine("AD:" + iAd01.ToString() + iAd02.ToString() + iAd03.ToString() + iAd04.ToString() + iAd05.ToString() + iAd06.ToString() + iAd07.ToString());
                Console.WriteLine("Temp:" + WaterTank.GetModuleVal().ToString());
                SaveAdData();
                if (m_SetTemp > m_MaxSetTemp)
                {
                    TestStop();
                    TempSensor.SendCalcStop();
                    return;
                }
               

                Thread.Sleep(100);
                Int16 TankTemp = (Int16)(WaterTank.GetModuleVal() * 100);
                Int16 tmp = (Int16)(Omega.GetModuleVal() * 100);
                TempSensor.SendSetTempVal(m_SendIndex, tmp);
                Thread.Sleep(100);
                m_SendIndex++;
                WaterTank.SetTempVal(m_SetTemp);

            }
        }
        /// <summary>
        /// 打开串口
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btOmegaOpen_Click(object sender, EventArgs e)
        {
          
            try
            {
                string port_name = listBox2.SelectedItem.ToString();
                 //获取并显示串口端口
                 Omega.COM_Name = port_name;
                 if (Omega.Open_sPort() == true)
                 {
                     btOmegaOpen.Enabled = false;
                     btOmegaClose.Enabled = true;
                 }
            }
            catch (Exception ex)
            {
                Excel_Lgl.SaveLog("[btOmegaOpen_Click]" + ex.ToString());
            }

        }

        private void btOmegaClose_Click(object sender, EventArgs e)
        {
            if (Omega.Close_sPort() == true)
            {
                btOmegaOpen.Enabled = true;
                btOmegaClose.Enabled = false;
            }
        }

        private void btTankOpen_Click(object sender, EventArgs e)
        {
            string port_name = listBox3.SelectedItem.ToString();                  //获取并显示串口端口
            WaterTank.COM_Name = port_name;
            if (WaterTank.Open_sPort() == true)
            {
                btTankOpen.Enabled = false;
                btTankClose.Enabled = true;
            }
        }

        private void btTankClose_Click(object sender, EventArgs e)
        {
            if (WaterTank.Close_sPort() == true)
            {
                btTankOpen.Enabled = true;
                btTankClose.Enabled = false;
            }
        }
        /// <summary>
        /// 开始按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btTestStart_Click(object sender, EventArgs e)
        {
            btTestStart.Enabled = false;
            btTestStop.Enabled = true;

            //Curve_SetCurveDraw();
            dt_CureStart = DateTime.Now;
            int tsInt = 0;
            switch (cbSelectMode.SelectedItem.ToString())
            {
                case "单点测试":
                    WaterTank.SetTempVal(m_SetTemp);
                    TestDataFileStr = TestDataPath + DateTime.Now.ToLocalTime().ToString("yyyy年MM月dd日HH时mm分ss秒") + @".xlsx";
                    Excel_Lgl.CreateExcelFile(TestDataFileStr);
                     tsInt = m_StableTime;
                     Timelabel.Visible = true;//倒计时文本框可以见
                     ts = new TimeSpan(0,  tsInt, 0);//倒计时
                    
                     CureDrawMin=m_SetTemp-10;
                     CureDrawMax = m_SetTemp+ 10;
                    break;
                case "温域测试":
                    m_CmdCycleTime = m_SimgleTime + m_StableTime;
                    m_CmdCycleCount = DateTime.Now;//点击开始按钮的当前时间
                    WaterTank.SetTempVal(m_MinSetTemp);
                    //labelTankStatus.Text = WaterTank.GetModuleStatus();//水槽
                    m_SetTemp = m_MinSetTemp;
                    TestDataFileStr = TestDataPath + DateTime.Now.ToLocalTime().ToString("yyyy年MM月dd日HH时mm分ss秒") + @".xlsx";
                    Excel_Lgl.CreateExcelFile(TestDataFileStr);
                    //温域测试的总时间是.(温度稳定时间+温度采样时间)*((最大温度-最小温度)/控制步幅)
                    tsInt = (m_CmdCycleTime*60) * ((m_MaxSetTemp - m_MinSetTemp) / m_StepCount + 1);
                    Timelabel.Visible = true;//倒计时文本框可以见
                    ts = new TimeSpan(0,0,tsInt);//倒计时
                    CureDrawMin = m_MinSetTemp -5;
                    CureDrawMax = m_MaxSetTemp + 5;
                    break;
                case "两点校准":
                    m_SendIndex = 0;
                    m_CmdCycleTime = m_SimgleTime + m_StableTime;
                    m_CmdCycleCount = DateTime.Now;
                    WaterTank.SetTempVal(m_MinSetTemp);
                    m_SetTemp = m_MinSetTemp;
                    TempSensor.SendStartCalcCmdPkg("两点校准", 2);
                    Thread.Sleep(100);
                    TempSensor.SendSetVref(m_ADsrc);
                    AD_DataFileStr = AD_DataPath + DateTime.Now.ToLocalTime().ToString("yyyy年MM月dd日HH时mm分ss秒") + @".xlsx";
                    Excel_Lgl.CreateAdExcelFile(AD_DataFileStr);
                    //两点校准的总时间是,(温度稳定时间+温度采样时间)*2
                    tsInt = (m_CmdCycleTime *2*60);
                     Timelabel.Visible = true;//倒计时文本框可以见
                     ts = new TimeSpan(0, 0, tsInt);//倒计时
                    CureDrawMin = m_MinSetTemp -5;
                    CureDrawMax = m_MaxSetTemp + 5;
                    break;
                case "多点校准":
                    m_SendIndex = 0;
                    m_CmdCycleTime = m_SimgleTime + m_StableTime;
                    m_CmdCycleCount = DateTime.Now;
                    WaterTank.SetTempVal(m_MinSetTemp);
                    m_SetTemp = m_MinSetTemp;
                    TempSensor.SendStartCalcCmdPkg("多点校准", (m_MaxSetTemp-m_MinSetTemp)/m_StepCount+1);
                    Thread.Sleep(100);
                    TempSensor.SendSetVref(m_ADsrc);
                    //TempSensor.SendStartCalcCmdPkg("多点校准", 4);
                    AD_DataFileStr = AD_DataPath + DateTime.Now.ToLocalTime().ToString("yyyy年MM月dd日HH时mm分ss秒") + @".xlsx";
                    Excel_Lgl.CreateAdExcelFile(AD_DataFileStr);
                    //多点校准的总时间是.(温度稳定时间+温度采样时间)*((最大温度-最小温度)/控制步幅)
                    tsInt = (m_CmdCycleTime*60) * ((m_MaxSetTemp - m_MinSetTemp) / m_StepCount + 1);
                     Timelabel.Visible = true;//倒计时文本框可以见
                     ts = new TimeSpan(0,0,tsInt);//倒计时
                    CureDrawMin = m_MinSetTemp -5;
                    CureDrawMax = m_MaxSetTemp + 5;
                    break;
                case "二次项校准":
                    //TempSensor.SendStartCalcCmdPkg("二次项校准", 3);
                    break;
                default:break;
            }

            Curve_SetCurveDraw();
            m_TestStatus = true;
        }
        /// <summary>
        /// 停止按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btTestStop_Click(object sender, EventArgs e)
        {
            try
            {
                Timelabel.Visible = false;
                TestStop();
                //ThreadExcel.Abort();
               
            }
            catch (Exception ex)
            {
                Excel_Lgl.SaveLog("[btTestStop_Click]" + ex.ToString());
            }

        }

        private void TestStop()
        {
            m_TestStatus = false;
            btTestStart.Enabled = true;
            btTestStop.Enabled = false;

            cf_Temp01.data.Clear();
            cf_Temp02.data.Clear();
            cf_Temp03.data.Clear();
            cf_Temp04.data.Clear();
            cf_Temp05.data.Clear();
            cf_Temp06.data.Clear();
            cf_Temp07.data.Clear();
            cf_TempSrcC.data.Clear();
            CureDraw_Temp.ClearCurves();
            CureDraw_Temp.ClearTimeSeparator();

            cf_TempSrc.data.Clear();
            cf_TempSet.data.Clear();
            cf_TempReal.data.Clear();
            CureDraw_Src.ClearCurves();
            CureDraw_Src.ClearTimeSeparator();
        }

        private void cbSelectMode_SelectedValueChanged(object sender, EventArgs e)
        {
            switch (cbSelectMode.SelectedItem.ToString())
            {
                case "单点测试":
                    tBCtrlMax.Enabled = false;
                    tBCtrlMin.Enabled = false;
                    tbCtrlStep.Enabled = false;
                    tbCtrlSet.Enabled = true;
                    tbSimgleTime.Enabled = false;
                    break;
                case "温域测试":
                    tBCtrlMax.Enabled = true;
                    tBCtrlMin.Enabled = true;
                    tbCtrlStep.Enabled = true;
                    tbCtrlSet.Enabled = false;
                    tbSimgleTime.Enabled = true;
                    break;
                case "两点校准":
                    tBCtrlMax.Enabled = true;
                    tBCtrlMin.Enabled = true;
                    tbCtrlStep.Enabled = false;
                    tbCtrlSet.Enabled = false;
                    tbSimgleTime.Enabled = true;
                    break;
                case "多点校准":
                    tBCtrlMax.Enabled = true;
                    tBCtrlMin.Enabled = true;
                    tbCtrlStep.Enabled = true;
                    tbCtrlSet.Enabled = false;
                    tbSimgleTime.Enabled = true;
                    break;
                case "二次项校准":
                    tBCtrlMax.Enabled = true;
                    tBCtrlMin.Enabled = true;
                    tbCtrlStep.Enabled = false;
                    tbCtrlSet.Enabled = false;
                    tbSimgleTime.Enabled = true;
                    break;
                default: break;
            }
        }

        private void tbStableTime_TextChanged(object sender, EventArgs e)
        {
           try
           {
            m_StableTime = Convert.ToInt32(tbStableTime.Text);
            Console.WriteLine("StableTime: "+m_StableTime.ToString());
           }
            catch(Exception ex)
           {

            }
        }

        private void tbSimgleTime_TextChanged(object sender, EventArgs e)
        {
            try
           {
            m_SimgleTime = Convert.ToInt32(tbSimgleTime.Text);
            Console.WriteLine("SimgleTime: " + m_SimgleTime.ToString());
            }
            catch(Exception ex)
           {

            }
        }

        private void tBCtrlMin_TextChanged(object sender, EventArgs e)
        {
            try
           {
            m_MinSetTemp = Convert.ToInt32(tBCtrlMin.Text);
            Console.WriteLine("CtrlMin: " + m_MinSetTemp.ToString());
           }
            catch(Exception ex)
           {

            }
        }

        private void tBCtrlMax_TextChanged(object sender, EventArgs e)
        {
            try
           {
            m_MaxSetTemp = Convert.ToInt32(tBCtrlMax.Text);
            Console.WriteLine("CtrlMax: " + m_MaxSetTemp.ToString());
           }
            catch(Exception ex)
           {

            }
        }

        private void tbCtrlStep_TextChanged(object sender, EventArgs e)
        {
            try
           {
            m_StepCount = Convert.ToInt32(tbCtrlStep.Text);
            Console.WriteLine("Step: " + m_StepCount.ToString());
           }
            catch(Exception ex)
           {

            }
        }

        private void tbCtrlSet_TextChanged(object sender, EventArgs e)
        {
            try
           {
            m_SetTemp = Convert.ToDouble(tbCtrlSet.Text);
            Console.WriteLine("SetTemp: " + m_SetTemp.ToString());
           }
            catch (Exception ex)
            {

            }
        }
        /// <summary>
        /// 序列的开始
        /// </summary>
        int numberInt = 0;
        /// <summary>
        /// 保存excel数据
        /// </summary>
        private void SaveData()
        {
            double[] tmp = new double[7];
            double src= Omega.GetModuleVal();
            double TankTemp = WaterTank.GetModuleVal();
            double TankSet = WaterTank.GetModuleSetVal();
            tmp[0] = TempSensor.Temperature_01;
            tmp[1] = TempSensor.Temperature_02;
            tmp[2] = TempSensor.Temperature_03;
            tmp[3] = TempSensor.Temperature_04;
            tmp[4] = TempSensor.Temperature_05;
            tmp[5] = TempSensor.Temperature_06;
            tmp[6] = TempSensor.Temperature_07;
            float time = (float)((DateTime.Now - dt_CureStart).TotalSeconds);
            Excel_Lgl.WriteToExcel(TestDataFileStr, DateTime.Now.ToLocalTime().ToString(), src.ToString(), TankSet.ToString(), TankTemp.ToString(),
                tmp, 7);
        }
        /// <summary>
        /// 把Ad数据写到excel表
        /// </summary>
        private void SaveAdData()
        {
            double[] tmp = new double[7];
            double src = Omega.GetModuleVal();
            double TankTemp = WaterTank.GetModuleVal();
            double TankSet = WaterTank.GetModuleSetVal();
            tmp[0] = TempSensor.AD_01;
            tmp[1] = TempSensor.AD_02;
            tmp[2] = TempSensor.AD_03;
            tmp[3] = TempSensor.AD_04;
            tmp[4] = TempSensor.AD_05;
            tmp[5] = TempSensor.AD_06;
            tmp[6] = TempSensor.AD_07;
            float time = (float)((DateTime.Now - dt_CureStart).TotalSeconds);
            Excel_Lgl.WriteToExcel(AD_DataFileStr, DateTime.Now.ToLocalTime().ToString(), src.ToString(), TankSet.ToString(), TankTemp.ToString(),
                tmp, 7);
        }
        //测试
        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                Omega.Close_sPort();
                WaterTank.Close_sPort();
                TempSensor.Close_sPort();
                System.Environment.Exit(0); 
            }
            catch (Exception ex)
            {
                System.Environment.Exit(0); 
            }

        }


    }
}

           
