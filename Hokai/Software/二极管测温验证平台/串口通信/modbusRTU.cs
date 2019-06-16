/*----------------------------------------------------------------
// 和佳医疗设备股份有限公司
// 版权所有。 
// 
// 文件名：modbusRTU.cs
// 文件功能描述：协议功能块。
// 
// 
// 创建标识：创建人：汤道涛 2014.12.04
// 
// 修改标识：
// 修改描述：
//----------------------------------------------------------------*/

using System.Windows.Forms;
using System;

namespace Module_HardWare
{

    /// <summary>从机ID
    /// 
    /// </summary>
    public enum slaveID : byte
    {
        /// 控制台
        mcuControlCentre = 0x01,
        /// 主机屏幕
        mcuScreenShow = 0x02,
        /// 测温仪
        mcuThermodetecotr = 0x01,
        /// 
        Temperature_1 = 0xF6,
        /// 
        Temperature_2 = 0xF3,
        /// 
        MCU = 0x01

    }


    #region 状态位

    /// <summary>状态位
    /// 
    /// </summary>
    public enum errorCode : int
    {
        /*------------------通信状态位-------------------------*/
        /// 
        errorNoError = 0,
        /// 
        errorSlaveFun = 1,
        /// 
        errorSlaveAddr = 2,
        /// 
        errorSlavePDU = 3,
        /// 
        errorSlaveNum = 4,
        /// 
        errorSlaveisBusy = 5,
        /// 
        errorCheckCRC = 6,
        /// 
        errorFrameInfLack = 7,
        /// 
        errorSendFrame = 8,
        /// 
        errorReceiveFrame = 9,
        /// 
        errorSlaveID = 10,
        /*------------------功能状态位-------------------------*/
        /// 
        errorReadSingleRegister = 11,
        /// 
        errorWriteSingleRegister = 12,
        /// 
        errorWriteMultiRegister = 13,
        /*-------------------忙状态位-------------------------*/
        /// 
        errorisBusyDeviceInit = 21,
        /// 
        errorisBusyDeviceOn = 22,
        /// 
        errorisBusyDeviceStart = 23,
        /// 
        errorisBusyDevicePause = 24,
        /// 
        errorisBusyDeviceReset = 25,
        /// 
        errorisBusyDeviceShutdown = 26,
        /// 
        errorisBusyDeviceEnd = 27,
        /// 
        errorisBusyWarning = 28,
        /*---------------执行过程异常状态位-------------------*/
        /// 
        errorProgcessThreadRun = 31,
        ///
        errorProgcessPort = 32

    }

    #endregion

    /// <summary>协议
    /// 
    /// </summary>
    public class modbusRTU
    {

        #region 枚举类型

        /// <summary>功能码
        /// 
        /// </summary>
        private enum slaveFun : byte
        {
            readSingleRegister_00 = 0x03,
            readSingleRegister_01 = 0x04, //测温仪
            writeSingleRegister = 0x06,
            writeMultiRegister = 0x10
        }

        /// <summary>故障码
        /// 
        /// </summary>
        private enum slaveWarningFun : byte
        {
            warnReadSingleRegister = 0x83,
            warnWriteSingleRegister = 0x86,
            warnWriteMultiRegister = 0x90
        }


        #endregion

        #region 内部函数
        /// <summary>返回桢，验证读单路寄存器并读取寄存器返回数值
        /// 
        /// </summary>
        /// <param name="idata">接收到的数据</param>
        /// <param name="odata">拆包成功后读回的数据</param>
        /// <returns>错误码</returns>
        public int TempModDataCheck(byte[] idata, ref byte[] odata)
        {
            int status = (int)errorCode.errorNoError;
            string teststr = "";
            for (int n = 0; n < idata.Length; n++)
                teststr = teststr + idata[n].ToString("X2") + " ";
            //Console.Write("<LGL接收帧>" + teststr);
            //Console.WriteLine("");
            try
            {
                ushort wCRC = 0xffff;
                wCRC = CRCUpdateN(idata, wCRC, 5);
                if (idata[5] != (byte)wCRC || idata[6] != (byte)(wCRC >> 8))
                {
                   // Console.Write(idata[5] + " ");
                   // Console.Write((byte)wCRC + " ");
                   // Console.Write(idata[6] + " ");
                   // Console.Write((byte)(wCRC >> 8) + " ");
                   // Console.WriteLine("");
                    status = (int)errorCode.errorCheckCRC;
                }
                if (status == (int)errorCode.errorNoError)
                {
                    odata[0] = idata[3];
                    odata[1] = idata[4];
                }
            }
            catch
            {
                return (int)errorCode.errorWriteSingleRegister;
            }
            return status;
        }

        public static ushort[] crctab = new ushort[256]{
        0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
        0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
        0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
        0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
        0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
        0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
        0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
        0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
        0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
        0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
        0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
        0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
        0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
        0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
        0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
        0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
        0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
        0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
        0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
        0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
        0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
        0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
        0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
        0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
        0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
        0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
        0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
        0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
        0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
        0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
        0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
        0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040
};
        ushort CRCUpdate1(byte data1, ushort crc)
        {
            return ((ushort)((crc >> 8) ^ crctab[(byte)(crc ^ data1)]));
        }
        ushort CRCUpdateN(byte[] dataptr, ushort crc, int nbytes)
        {
            for (int i = 0; i < nbytes; i++)
            {
                crc = CRCUpdate1(dataptr[i], crc);
            }
            //while (nbytes-- > 0)
            //    crc = CRCUpdate1(*dataptr++,crc);
            return (crc);
        }

        public int TempModReadData(byte uslaveID, ref byte[] oSendFrame)
        {
            try
            {
                //byte[] data = new byte[6];
                ushort wCRC = 0xffff;
                oSendFrame[0] = uslaveID;
                oSendFrame[1] = 4;
                oSendFrame[2] = 1;
                oSendFrame[3] = 0;
                oSendFrame[4] = 0;
                wCRC = CRCUpdateN(oSendFrame, wCRC, 5);
                oSendFrame[5] = (byte)wCRC;
                oSendFrame[6] = (byte)(wCRC >> 8);
                string teststr = "";
                for (int n = 0; n < oSendFrame.Length; n++)
                    teststr = teststr + oSendFrame[n].ToString("X2") + " ";
                //Console.Write("<LGL发送帧>-读单寄存器" + teststr);
                //Console.WriteLine("");
                return (int)errorCode.errorNoError;
            }
            catch
            {
                return (int)errorCode.errorSendFrame;
            }
        }
        /// <summary>CRC计算
        /// 
        /// </summary>
        /// <param name="pByte">需要计算CRC的数组</param>
        /// <param name="hi">   计算CRC高位</param>
        /// <param name="lo">   计算CRC地位</param>
        private static void calculateCRC(byte[] pByte, out byte hi, out byte lo)
        {
            int nBit, nNumberOfBytes = pByte.Length;
            ushort nShiftedBit,
            pChecksum = 0xFFFF;

            for (int nByte = 0; nByte < nNumberOfBytes; nByte++)
            {
                pChecksum ^= pByte[nByte];
                for (nBit = 0; nBit < 8; nBit++)
                {
                    if ((pChecksum & 0x1) == 1)
                    {
                        nShiftedBit = 1;
                    }
                    else
                    {
                        nShiftedBit = 0;
                    }
                    pChecksum >>= 1;
                    if (nShiftedBit != 0)
                    {
                        pChecksum ^= 0xA001;
                    }
                }
            }

            hi = (byte)(pChecksum & 0xFF);
            lo = (byte)((pChecksum & 0xFF00) >> 8);

        }

        /// <summary>数据附加CRC
        /// 
        /// </summary>
        /// <param name="iByte">输入数据</param>
        /// <param name="oByte">打包完成输出数据</param>
        private static void dataWithCRC(byte[] iByte, byte[] oByte)
        {

            byte crch = 0;
            byte crcl = 0;

            calculateCRC(iByte, out crch, out crcl);

            for (int i = 0; i < iByte.Length; i++)
            {
                oByte[i] = iByte[i];
            }

            oByte[iByte.Length] = crch;
            oByte[iByte.Length + 1] = crcl;


        }

        /// <summary>接收字节码CRC校验
        /// 
        /// </summary>
        /// <param name="data">接收数据</param>
        /// <returns>错误码</returns>
        private static bool checkCRC(byte[] data)
        {
            byte crch = 0;
            byte crcl = 0;

            if (data.Length >= 3)
            {
                byte[] idata = new byte[data.Length - 2];
                for (int i = 0; i < data.Length - 2; i++)
                {
                    idata[i] = data[i];
                }
                calculateCRC(idata, out  crch, out crcl);
                if (data[data.Length - 2] == crch && data[data.Length - 1] == crcl)
                {
                    return true;
                }
                else { return false; }

            }

            return false;

        }

        /// <summary>忙检查
        /// 
        /// </summary>
        /// <param name="data">忙状态检查</param>
        /// <returns>忙状态</returns>
        private static int busyCheck(byte data)
        {
            switch (data)
            {
                case 0xF1:
                    return (int)errorCode.errorisBusyDeviceInit;
                case 0xF2:
                    return (int)errorCode.errorisBusyDeviceOn;
                case 0xF3:
                    return (int)errorCode.errorisBusyDeviceStart;
                case 0xF4:
                    return (int)errorCode.errorisBusyDevicePause;
                case 0xF5:
                    return (int)errorCode.errorisBusyDeviceReset;
                case 0xF6:
                    return (int)errorCode.errorisBusyDeviceShutdown;
                case 0xF7:
                    return (int)errorCode.errorisBusyDeviceEnd;
                case 0xF8:
                    return (int)errorCode.errorisBusyWarning;


                default:
                    return (int)errorCode.errorSlavePDU;



            }
        }

        /// <summary>接收桢校验
        /// 
        /// </summary>
        /// <param name="idata">接收的数据</param>
        /// <param name="uslaveID">从机地址</param>
        /// <param name="eMode">桢反馈命令</param>
        /// <returns>错误码</returns>
        private static int mbReceiveFrame(byte[] idata, byte uslaveID, ref string eMode)
        {
            try
            {

                if (idata.Length < 5) {
                    return (int)errorCode.errorReceiveFrame;
                }
                if (checkCRC(idata) == false) return (int)errorCode.errorCheckCRC;
                else
                {
                    if (idata[0] != uslaveID) return (int)errorCode.errorSlaveID;
                    else
                    {
                        switch (idata[1])//MB function bit
                        {
                            case (byte)slaveFun.readSingleRegister_00:
                                eMode = "readSingleRegister";
                                return (int)errorCode.errorNoError;
                            case (byte)slaveFun.readSingleRegister_01:
                                eMode = "readSingleRegister";
                                return (int)errorCode.errorNoError;

                            case (byte)slaveFun.writeSingleRegister:
                                eMode = "writeSingleRegister";
                                return (int)errorCode.errorNoError;

                            case (byte)slaveFun.writeMultiRegister:
                                eMode = "writeMultiRegister";
                                return (int)errorCode.errorNoError;

                            case (byte)slaveWarningFun.warnReadSingleRegister:
                                eMode = "warnReadSingleRegister";
                                return busyCheck(idata[2]);

                            case (byte)slaveWarningFun.warnWriteSingleRegister:
                                eMode = "warnWriteSingleRegister";
                                return busyCheck(idata[2]);

                            case (byte)slaveWarningFun.warnWriteMultiRegister:
                                eMode = "warnWriteMultiRegister";
                                return busyCheck(idata[2]);

                            default:
                                return (int)errorCode.errorSlaveFun;

                        }
                    }
                }

            }
            catch
            {
                return (int)errorCode.errorReceiveFrame;
            }

        }


        #endregion

        #region  外部函数

        /// <summary>发送帧，读单路寄存器
        /// 
        /// </summary>
        /// <param name="isThermodetector">是否测温仪</param>
        /// <param name="uslaveID">从机地址</param>
        /// <param name="uslaveAddr">寄存器地址</param>
        /// <param name="uslaveNum">寄存器数量</param>
        /// <param name="oSendFrame">打包好的发送帧</param>
        /// <returns>返回错误码</returns>
        public int sendReadSingleRegister(bool isThermodetector, byte uslaveID, byte[] uslaveAddr, byte[] uslaveNum, ref byte[] oSendFrame)
        {
            try
            {
                byte[] data = new byte[6];
                data[0] = uslaveID;
                if (isThermodetector)
                    data[1] = (byte)slaveFun.readSingleRegister_01;
                else
                    data[1] = (byte)slaveFun.readSingleRegister_00;
                data[2] = uslaveAddr[0];
                data[3] = uslaveAddr[1];
                data[4] = uslaveNum[0];
                data[5] = uslaveNum[1];
                dataWithCRC(data, oSendFrame);

                string teststr = "";
                for (int n = 0; n < oSendFrame.Length; n++)
                    teststr = teststr + oSendFrame[n].ToString("X2") + " ";

                if (uslaveID == (byte)slaveID.mcuScreenShow)
                {
                    Console.Write("<发送帧>-读单寄存器" + teststr);
                    Console.WriteLine("");
                }


                return (int)errorCode.errorNoError;
            }
            catch
            {
                return (int)errorCode.errorSendFrame;
            }
        }

        /// <summary>发送帧，写单路寄存器
        /// 
        /// </summary>
        /// <param name="uslaveID">从机地址</param>
        /// <param name="uslaveAddr">寄存器地址</param>
        /// <param name="uslaveNum">寄存器数量</param>
        /// <param name="oSendFrame">打包好的发送帧</param>
        /// <returns>返回错误码</returns>
        public int sendWriteSingleRegister(byte uslaveID, byte[] uslaveAddr, byte[] uslaveNum, ref byte[] oSendFrame)
        {
            try
            {
                byte[] data = new byte[6];
                data[0] = uslaveID;
                data[1] = (byte)slaveFun.writeSingleRegister;
                data[2] = uslaveAddr[0];
                data[3] = uslaveAddr[1];
                data[4] = uslaveNum[0];
                data[5] = uslaveNum[1];
                dataWithCRC(data, oSendFrame);

                string teststr = "";
                for (int n = 0; n < oSendFrame.Length; n++)
                    teststr = teststr + oSendFrame[n].ToString("X2") + " ";

                if (uslaveID == (byte)slaveID.mcuScreenShow)
                {
                    Console.Write("<发送帧>-写单寄存器" + teststr);
                    Console.WriteLine("");
                }

                return (int)errorCode.errorNoError;

            }
            catch
            {
                return (int)errorCode.errorSendFrame;
            }
        }

        /// <summary>发送帧，写多路寄存器
        /// 
        /// </summary>
        /// <param name="uslaveID">从机地址</param>
        /// <param name="uslaveAddr">寄存器地址</param>
        /// <param name="uslaveNum">寄存器数量</param>
        /// <param name="uslaveData">多路写入的数据</param>
        /// <param name="oSendFrame">打包好的发送帧</param>
        /// <returns>返回错误码</returns>
        public int sendWriteMultiRegister(byte uslaveID, byte[] uslaveAddr, byte[] uslaveNum,
                                           byte[] uslaveData, ref byte[] oSendFrame)
        {
            try
            {
                int uDataLength, i;
                uDataLength = uslaveData.Length;
                byte[] data = new byte[7 + uDataLength];
                data[0] = uslaveID;
                data[1] = (byte)slaveFun.writeMultiRegister;
                data[2] = uslaveAddr[0];
                data[3] = uslaveAddr[1];
                data[4] = uslaveNum[0];
                data[5] = uslaveNum[1];
                data[6] = (byte)(uslaveNum[1] * 2);

                for (i = 0; i < uDataLength; i++)
                    data[7 + i] = uslaveData[i];
                dataWithCRC(data, oSendFrame);

                string teststr = "";
                for (int n = 0; n < oSendFrame.Length; n++)
                    teststr = teststr + oSendFrame[n].ToString("X2") + " ";
                if (uslaveID == (byte)slaveID.mcuScreenShow)
                {
                    Console.Write("<发送帧>-写多寄存器" + teststr);
                    Console.WriteLine("");
                }

                return (int)errorCode.errorNoError;
            }
            catch
            {
                return (int)errorCode.errorSendFrame;
            }
        }

        /// <summary>返回桢，验证读单路寄存器并读取寄存器返回数值
        /// 
        /// </summary>
        /// <param name="idata">接收到的数据</param>
        /// <param name="uslaveID">从机地址</param>
        /// <param name="uslaveNum">寄存器数量</param>
        /// <param name="odata">拆包成功后读回的数据</param>
        /// <returns>错误码</returns>
        public int recReadSingleRegister(byte[] idata, byte uslaveID, byte uslaveNum, ref byte[] odata)
        {
            try
            {
                string str = "";
                int i, status;

                status = mbReceiveFrame(idata, uslaveID, ref str);

                string teststr = "";
                for (int n = 0; n < idata.Length; n++)
                    teststr = teststr + idata[n].ToString("X2") + " ";

                if (uslaveID == (byte)slaveID.mcuScreenShow)
                {
                    Console.Write("<接收帧>-读单寄存器" + teststr);
                    Console.WriteLine("");
                }

                if (mbReceiveFrame(idata, uslaveID, ref str) != (int)errorCode.errorNoError)
                    return (int)errorCode.errorReceiveFrame;
                else
                {
                    if (str != "readSingleRegister") return (int)errorCode.errorSlaveFun;
                    else
                    {
                        if (idata[2] != (byte)(uslaveNum * 2)) return (int)errorCode.errorSlaveNum;
                        else
                        {
                            for (i = 0; i < idata.Length - 5; i++)
                            {
                                odata[i] = idata[i + 3];
                            }
                            return (int)errorCode.errorNoError;
                        }

                    }

                }

            }
            catch
            {
                return (int)errorCode.errorWriteSingleRegister;
            }
        }

        /// <summary>返回桢，验证写单路写多路寄存器是否正确
        /// 
        /// </summary>
        /// <param name="idata">接收到的数据</param>
        /// <param name="uslaveID">从机地址</param>
        /// <param name="uslaveAddr">寄存器数量</param>
        /// <param name="uslaveNum">寄存器数量</param>
        /// <returns>错误码</returns>
        public int recWriteSingleMultiRegister(byte[] idata, byte uslaveID, byte[] uslaveAddr, byte[] uslaveNum)
        {
            try
            {
                string str = "";
                int status;
                status = mbReceiveFrame(idata, uslaveID, ref str);

                string teststr = "";
                for (int n = 0; n < idata.Length; n++)
                    teststr = teststr + idata[n].ToString("X2") + " ";
                if (uslaveID == (byte)slaveID.mcuScreenShow)
                {
                    Console.Write("<接收帧>-写单或多寄存器" + teststr);
                    Console.WriteLine("");
                }
                   // Console.WriteLine("============ERRSTATUS+++++++"+status.ToString());

                if (status > (int)errorCode.errorNoError && status < (int)errorCode.errorisBusyDeviceInit)
                { 
                    return (int)errorCode.errorReceiveFrame;
                }
                else
                {
                    switch (str)
                    {
                        case "writeSingleRegister":
                            if (idata[2] != uslaveAddr[0] || idata[3] != uslaveAddr[1]) 
                                return (int)errorCode.errorSlaveAddr;
                            else
                            {
                                if (idata[4] != uslaveNum[0] || idata[5] != uslaveNum[1]) return (int)errorCode.errorSlaveNum;
                                else
                                    return (int)errorCode.errorNoError;
                            }

                        case "writeMultiRegister":
                            if (idata[2] != uslaveAddr[0] || idata[3] != uslaveAddr[1])
                                return (int)errorCode.errorSlaveAddr;
                            else
                            {
                                if (idata[4] != uslaveNum[0] || idata[5] != uslaveNum[1]) return (int)errorCode.errorSlaveNum;
                                else
                                    return (int)errorCode.errorNoError;
                            }

                        case "warnReadSingleRegister":
                            return status;
                        case "warnWriteSingleRegister":
                            return status;
                        case "warnWriteMultiRegister":
                            return status;

                        default:
                            return (int)errorCode.errorWriteSingleRegister;

                    }
                }
            }
            catch
            {
                return (int)errorCode.errorWriteSingleRegister;
            }
        }

        #endregion


    }
}
