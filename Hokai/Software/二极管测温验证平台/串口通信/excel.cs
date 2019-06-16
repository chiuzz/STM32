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
using Excel = Microsoft.Office.Interop.Excel;
using System.Runtime.InteropServices;

namespace EXCEL_LGL 
{
    public class Excel_Lgl 
    {

        private static string logFile = "";
        
        public static string  LogFilePath
        {
            get { return logFile; }
            set { logFile = value; }
        }

        /// <summary>  
        /// If the supplied excel File does not exist then Create it  
        /// </summary>  
        /// <param name="FileName"></param>  
        public static void CreateExcelFile(string FileName)
        {
            try { 
            //create  
            object Nothing = System.Reflection.Missing.Value;  
            var app = new Excel.Application();  
            app.Visible = false;  
            Excel.Workbook workBook = app.Workbooks.Add(Nothing);  
            Excel.Worksheet worksheet = (Excel.Worksheet)workBook.Sheets[1];  
            worksheet.Name = "Work";  
            //headline  
            worksheet.Cells[1, 1] = "序号";
            worksheet.Cells[1, 2] = "时间";  
            worksheet.Cells[1, 3] = "基准源温度";  
            worksheet.Cells[1, 4] = "设定温度";  
            worksheet.Cells[1, 5] = "显示温度";  
            worksheet.Cells[1, 6] = "CH0温度";  
            worksheet.Cells[1, 7] = "CH1温度";  
            worksheet.Cells[1, 8] = "CH2温度";  
            worksheet.Cells[1, 9] = "CH3温度";  
            worksheet.Cells[1, 10] = "CH4温度";  
            worksheet.Cells[1, 11] = "CH5温度";  
            worksheet.Cells[1, 12] = "CH6温度";  
  
            worksheet.SaveAs(FileName, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Excel.XlSaveAsAccessMode.xlNoChange, Type.Missing, Type.Missing, Type.Missing);  
            workBook.Close(false, Type.Missing, Type.Missing);  
            app.Quit();
            //关闭进程（EXCEL.EXE）释放资源
            if (app != null)
            {
                int lpdwProcessId;
                GetWindowThreadProcessId(new IntPtr(app.Hwnd), out lpdwProcessId);

                System.Diagnostics.Process.GetProcessById(lpdwProcessId).Kill();
            }
            Console.WriteLine("Excel file Success.\n");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }  
  
        /// <summary>  
        /// open an excel file,then write the content to file  
        /// </summary>  
        /// <param name="FileName">file name</param>  
        /// <param name="findString">first cloumn</param>  
        /// <param name="replaceString">second cloumn</param>  
        public static void WriteToExcel(string excelName, string time, string src, string set, string real, double[] ch, int len)  
        {
            try
            {
            if (!File.Exists(excelName))
            {
                Console.WriteLine("Excel文件不存在:"+ excelName);
            }
            
            //open  
            object Nothing = System.Reflection.Missing.Value;  
            var app = new Excel.Application();  
            app.Visible = false;  
            Excel.Workbook mybook = app.Workbooks.Open(excelName, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing);  
            Excel.Worksheet mysheet = (Excel.Worksheet)mybook.Worksheets[1];  
            mysheet.Activate(); 
                
                
            //get activate sheet max row count  
            int maxrow = mysheet.UsedRange.Rows.Count + 1;
            mysheet.Cells[maxrow, 1] = mysheet.UsedRange.Rows.Count.ToString();
                //设置单元格式
            mysheet.Cells[maxrow, 2].NumberFormat = "yyyy/MM/dd hh:mm:ss";
            mysheet.Cells[maxrow, 2].EntireColumn.AutoFit();
            mysheet.Cells[maxrow, 2] = time;  
            mysheet.Cells[maxrow, 3] = src;  
            mysheet.Cells[maxrow, 4] = set;  
            mysheet.Cells[maxrow, 5] = real;
            for (int i = 0; i < len; i++)
            {
                mysheet.Cells[maxrow, 6+i] = ch[i].ToString();
            }
            mybook.Save();  
            mybook.Close(false, Type.Missing, Type.Missing);  
            mybook = null;  
            //quit excel app  
            app.Quit();
            //关闭进程（EXCEL.EXE）释放资源
            if (app != null)
            {
                int lpdwProcessId;
                GetWindowThreadProcessId(new IntPtr(app.Hwnd), out lpdwProcessId);

                System.Diagnostics.Process.GetProcessById(lpdwProcessId).Kill();
            }
           }
            catch (Exception ex)
            {

            }
        }


        public static void CreateAdExcelFile(string FileName)
        {
            try 
            {
            //create  
            object Nothing = System.Reflection.Missing.Value;
            var app = new Excel.Application();
            app.Visible = false;
            Excel.Workbook workBook = app.Workbooks.Add(Nothing);
            Excel.Worksheet worksheet = (Excel.Worksheet)workBook.Sheets[1];
            worksheet.Name = "Work";
            //headline
            worksheet.Cells[1, 1] = "序号";
            worksheet.Cells[1, 2] = "时间";
            worksheet.Cells[1, 3] = "基准源温度";
            worksheet.Cells[1, 4] = "设定温度";
            worksheet.Cells[1, 5] = "显示温度";
            worksheet.Cells[1, 6] = "AD0值";
            worksheet.Cells[1, 7] = "AD1值";
            worksheet.Cells[1, 8] = "AD2值";
            worksheet.Cells[1, 9] = "AD3值";
            worksheet.Cells[1, 10] = "AD4值";
            worksheet.Cells[1, 11] = "AD5值";
            worksheet.Cells[1, 12] = "AD6值";
            
            worksheet.SaveAs(FileName, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Excel.XlSaveAsAccessMode.xlNoChange, Type.Missing, Type.Missing, Type.Missing);
            workBook.Close(false, Type.Missing, Type.Missing);
            app.Quit();
            //关闭进程（EXCEL.EXE）释放资源
            if (app != null)
            {
                int lpdwProcessId;
                GetWindowThreadProcessId(new IntPtr(app.Hwnd), out lpdwProcessId);

                System.Diagnostics.Process.GetProcessById(lpdwProcessId).Kill();
            }

            Console.WriteLine("Excel file Success.\n"); 
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
        #region Kill Special Excel Process
        [DllImport("user32.dll", SetLastError = true)]
        static extern int GetWindowThreadProcessId(IntPtr hWnd, out int lpdwProcessId);
        #endregion


        /// <summary>
        /// 写log
        /// </summary>
        /// <param name="Logfile">log的文件路径</param>
        /// <param name="logString">log的字符信息</param>
        public static void SaveLog(string LogfilePath ,string logString)
        {
            try
            {
                string fileFolder = LogfilePath;
                if (!Directory.Exists(fileFolder))
                {
                    File.Create(fileFolder).Close();
                }
             FileStream fs = new FileStream(fileFolder, FileMode.OpenOrCreate, FileAccess.Write);
            StreamWriter m_streamWriter = new StreamWriter(fs);
            m_streamWriter.BaseStream.Seek(0, SeekOrigin.End);
            m_streamWriter.WriteLine("[" + DateTime.Now.ToString() +"]"+logString+ "\r\n");
            m_streamWriter.Flush();
            m_streamWriter.Close();
            fs.Close();
            }
            catch
            { }
        }

        /// <summary>
        /// 写log
        /// </summary>
        /// <param name="logString">log的字符信息</param>
        public static void SaveLog(string logString)
        {
            try
            {
                string fileFolder = logFile;
                if (!File.Exists(fileFolder))
                {
                    //新建完后 马上关闭文件流File.Create("upload").Close();如果不Close(),那么这个文件一直被创建进程占着
                    File.Create(fileFolder).Close();
                 
                }
                FileStream fs = new FileStream(fileFolder, FileMode.OpenOrCreate, FileAccess.Write);
                StreamWriter m_streamWriter = new StreamWriter(fs);
                m_streamWriter.BaseStream.Seek(0, SeekOrigin.End);
                m_streamWriter.WriteLine("[" + DateTime.Now.ToLocalTime().ToString() + "]" + logString );
                m_streamWriter.Flush();
                m_streamWriter.Close();
                fs.Close();
            }
            catch (Exception ex)
            {
               // fs.Close();
            }
        }



    }
}
