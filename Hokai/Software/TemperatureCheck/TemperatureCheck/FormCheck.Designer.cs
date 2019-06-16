namespace TemperatureCheck
{
    partial class FormCheck
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.butCloseCom = new System.Windows.Forms.Button();
            this.butOpenCom = new System.Windows.Forms.Button();
            this.ComStatus = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.comStop = new System.Windows.Forms.ComboBox();
            this.comData = new System.Windows.Forms.ComboBox();
            this.comCheck = new System.Windows.Forms.ComboBox();
            this.comBaud = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.comPort = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label14 = new System.Windows.Forms.Label();
            this.text_B = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.text_K = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.CheckTemp = new System.Windows.Forms.TextBox();
            this.butCheckTemp = new System.Windows.Forms.Button();
            this.butHardwareCheck = new System.Windows.Forms.Button();
            this.CheckTempHigh = new System.Windows.Forms.TextBox();
            this.CheckTempLow = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.CheckAdValue2 = new System.Windows.Forms.TextBox();
            this.CheckAdValue1 = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.ADValue = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.CheckCH = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.radioButSingle = new System.Windows.Forms.RadioButton();
            this.radioButDouble = new System.Windows.Forms.RadioButton();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.butCloseCom);
            this.groupBox1.Controls.Add(this.butOpenCom);
            this.groupBox1.Controls.Add(this.ComStatus);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.comStop);
            this.groupBox1.Controls.Add(this.comData);
            this.groupBox1.Controls.Add(this.comCheck);
            this.groupBox1.Controls.Add(this.comBaud);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.comPort);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(181, 254);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "串口设置";
            // 
            // butCloseCom
            // 
            this.butCloseCom.Location = new System.Drawing.Point(86, 157);
            this.butCloseCom.Name = "butCloseCom";
            this.butCloseCom.Size = new System.Drawing.Size(75, 23);
            this.butCloseCom.TabIndex = 12;
            this.butCloseCom.Text = "关闭串口";
            this.butCloseCom.UseVisualStyleBackColor = true;
            this.butCloseCom.Click += new System.EventHandler(this.butCloseCom_Click);
            // 
            // butOpenCom
            // 
            this.butOpenCom.Location = new System.Drawing.Point(8, 157);
            this.butOpenCom.Name = "butOpenCom";
            this.butOpenCom.Size = new System.Drawing.Size(75, 23);
            this.butOpenCom.TabIndex = 11;
            this.butOpenCom.Text = "打开串口";
            this.butOpenCom.UseVisualStyleBackColor = true;
            this.butOpenCom.Click += new System.EventHandler(this.butOpenCom_Click);
            // 
            // ComStatus
            // 
            this.ComStatus.Location = new System.Drawing.Point(75, 186);
            this.ComStatus.Name = "ComStatus";
            this.ComStatus.Size = new System.Drawing.Size(100, 21);
            this.ComStatus.TabIndex = 10;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 191);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 12);
            this.label6.TabIndex = 1;
            this.label6.Text = "串口状态：";
            // 
            // comStop
            // 
            this.comStop.FormattingEnabled = true;
            this.comStop.Location = new System.Drawing.Point(65, 120);
            this.comStop.Name = "comStop";
            this.comStop.Size = new System.Drawing.Size(96, 20);
            this.comStop.TabIndex = 9;
            // 
            // comData
            // 
            this.comData.FormattingEnabled = true;
            this.comData.Location = new System.Drawing.Point(65, 94);
            this.comData.Name = "comData";
            this.comData.Size = new System.Drawing.Size(96, 20);
            this.comData.TabIndex = 8;
            // 
            // comCheck
            // 
            this.comCheck.FormattingEnabled = true;
            this.comCheck.Location = new System.Drawing.Point(65, 68);
            this.comCheck.Name = "comCheck";
            this.comCheck.Size = new System.Drawing.Size(96, 20);
            this.comCheck.TabIndex = 7;
            // 
            // comBaud
            // 
            this.comBaud.FormattingEnabled = true;
            this.comBaud.Location = new System.Drawing.Point(65, 42);
            this.comBaud.Name = "comBaud";
            this.comBaud.Size = new System.Drawing.Size(96, 20);
            this.comBaud.TabIndex = 6;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 127);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 12);
            this.label5.TabIndex = 5;
            this.label5.Text = "停止位：";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 100);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 4;
            this.label4.Text = "数据位：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 73);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "校验位：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 46);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "波特率：";
            // 
            // comPort
            // 
            this.comPort.FormattingEnabled = true;
            this.comPort.Location = new System.Drawing.Point(65, 16);
            this.comPort.Name = "comPort";
            this.comPort.Size = new System.Drawing.Size(96, 20);
            this.comPort.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "串口号：";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.groupBox3);
            this.groupBox2.Controls.Add(this.label14);
            this.groupBox2.Controls.Add(this.text_B);
            this.groupBox2.Controls.Add(this.label13);
            this.groupBox2.Controls.Add(this.text_K);
            this.groupBox2.Controls.Add(this.label12);
            this.groupBox2.Controls.Add(this.CheckTemp);
            this.groupBox2.Controls.Add(this.butCheckTemp);
            this.groupBox2.Controls.Add(this.butHardwareCheck);
            this.groupBox2.Controls.Add(this.CheckTempHigh);
            this.groupBox2.Controls.Add(this.CheckTempLow);
            this.groupBox2.Controls.Add(this.label10);
            this.groupBox2.Controls.Add(this.label11);
            this.groupBox2.Controls.Add(this.CheckAdValue2);
            this.groupBox2.Controls.Add(this.CheckAdValue1);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.ADValue);
            this.groupBox2.Controls.Add(this.button3);
            this.groupBox2.Controls.Add(this.CheckCH);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Location = new System.Drawing.Point(199, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(567, 263);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "硬件校准";
            this.groupBox2.Enter += new System.EventHandler(this.groupBox2_Enter);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(138, 221);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(29, 12);
            this.label14.TabIndex = 19;
            this.label14.Text = "B值:";
            // 
            // text_B
            // 
            this.text_B.Location = new System.Drawing.Point(173, 217);
            this.text_B.Name = "text_B";
            this.text_B.Size = new System.Drawing.Size(53, 21);
            this.text_B.TabIndex = 18;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(19, 222);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(29, 12);
            this.label13.TabIndex = 17;
            this.label13.Text = "K值:";
            // 
            // text_K
            // 
            this.text_K.Location = new System.Drawing.Point(54, 218);
            this.text_K.Name = "text_K";
            this.text_K.Size = new System.Drawing.Size(53, 21);
            this.text_K.TabIndex = 16;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(295, 40);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(35, 12);
            this.label12.TabIndex = 15;
            this.label12.Text = "AD值:";
            // 
            // CheckTemp
            // 
            this.CheckTemp.Location = new System.Drawing.Point(383, 217);
            this.CheckTemp.Name = "CheckTemp";
            this.CheckTemp.Size = new System.Drawing.Size(100, 21);
            this.CheckTemp.TabIndex = 14;
            // 
            // butCheckTemp
            // 
            this.butCheckTemp.Location = new System.Drawing.Point(275, 216);
            this.butCheckTemp.Name = "butCheckTemp";
            this.butCheckTemp.Size = new System.Drawing.Size(75, 23);
            this.butCheckTemp.TabIndex = 13;
            this.butCheckTemp.Text = "温度";
            this.butCheckTemp.UseVisualStyleBackColor = true;
            this.butCheckTemp.Click += new System.EventHandler(this.butCheckTemp_Click);
            // 
            // butHardwareCheck
            // 
            this.butHardwareCheck.Location = new System.Drawing.Point(275, 162);
            this.butHardwareCheck.Name = "butHardwareCheck";
            this.butHardwareCheck.Size = new System.Drawing.Size(100, 23);
            this.butHardwareCheck.TabIndex = 12;
            this.butHardwareCheck.Text = "硬件校准";
            this.butHardwareCheck.UseVisualStyleBackColor = true;
            this.butHardwareCheck.Click += new System.EventHandler(this.butHardwareCheck_Click);
            // 
            // CheckTempHigh
            // 
            this.CheckTempHigh.Location = new System.Drawing.Point(383, 109);
            this.CheckTempHigh.Name = "CheckTempHigh";
            this.CheckTempHigh.Size = new System.Drawing.Size(100, 21);
            this.CheckTempHigh.TabIndex = 11;
            // 
            // CheckTempLow
            // 
            this.CheckTempLow.Location = new System.Drawing.Point(383, 68);
            this.CheckTempLow.Name = "CheckTempLow";
            this.CheckTempLow.Size = new System.Drawing.Size(100, 21);
            this.CheckTempLow.TabIndex = 10;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(273, 72);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(95, 12);
            this.label10.TabIndex = 9;
            this.label10.Text = "输入测温最小值:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(273, 113);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(95, 12);
            this.label11.TabIndex = 8;
            this.label11.Text = "输入测温最大值:";
            // 
            // CheckAdValue2
            // 
            this.CheckAdValue2.Location = new System.Drawing.Point(140, 109);
            this.CheckAdValue2.Name = "CheckAdValue2";
            this.CheckAdValue2.Size = new System.Drawing.Size(100, 21);
            this.CheckAdValue2.TabIndex = 7;
            // 
            // CheckAdValue1
            // 
            this.CheckAdValue1.Location = new System.Drawing.Point(140, 68);
            this.CheckAdValue1.Name = "CheckAdValue1";
            this.CheckAdValue1.Size = new System.Drawing.Size(100, 21);
            this.CheckAdValue1.TabIndex = 6;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(33, 113);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(77, 12);
            this.label9.TabIndex = 5;
            this.label9.Text = "校准的AD值2:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(33, 72);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(77, 12);
            this.label8.TabIndex = 4;
            this.label8.Text = "校准的AD值1:";
            // 
            // ADValue
            // 
            this.ADValue.Location = new System.Drawing.Point(383, 36);
            this.ADValue.Name = "ADValue";
            this.ADValue.Size = new System.Drawing.Size(100, 21);
            this.ADValue.TabIndex = 3;
            this.ADValue.TextChanged += new System.EventHandler(this.ADValue_TextChanged);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(383, 162);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(100, 23);
            this.button3.TabIndex = 2;
            this.button3.Text = "显示AD值";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // CheckCH
            // 
            this.CheckCH.FormattingEnabled = true;
            this.CheckCH.Location = new System.Drawing.Point(140, 36);
            this.CheckCH.Name = "CheckCH";
            this.CheckCH.Size = new System.Drawing.Size(100, 20);
            this.CheckCH.TabIndex = 1;
            this.CheckCH.SelectedIndexChanged += new System.EventHandler(this.CheckCH_SelectedIndexChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(30, 40);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(83, 12);
            this.label7.TabIndex = 0;
            this.label7.Text = "校准通道选择:";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.radioButDouble);
            this.groupBox3.Controls.Add(this.radioButSingle);
            this.groupBox3.Location = new System.Drawing.Point(30, 136);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(205, 62);
            this.groupBox3.TabIndex = 20;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "单双毯模式";
            // 
            // radioButSingle
            // 
            this.radioButSingle.AutoSize = true;
            this.radioButSingle.Location = new System.Drawing.Point(138, 29);
            this.radioButSingle.Name = "radioButSingle";
            this.radioButSingle.Size = new System.Drawing.Size(47, 16);
            this.radioButSingle.TabIndex = 0;
            this.radioButSingle.TabStop = true;
            this.radioButSingle.Text = "单毯";
            this.radioButSingle.UseVisualStyleBackColor = true;
            // 
            // radioButDouble
            // 
            this.radioButDouble.AutoSize = true;
            this.radioButDouble.Location = new System.Drawing.Point(54, 29);
            this.radioButDouble.Name = "radioButDouble";
            this.radioButDouble.Size = new System.Drawing.Size(47, 16);
            this.radioButDouble.TabIndex = 1;
            this.radioButDouble.TabStop = true;
            this.radioButDouble.Text = "双毯";
            this.radioButDouble.UseVisualStyleBackColor = true;
            // 
            // FormCheck
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(778, 492);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "FormCheck";
            this.Text = "亚低温硬件校准平台";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button butCloseCom;
        private System.Windows.Forms.Button butOpenCom;
        private System.Windows.Forms.TextBox ComStatus;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox comStop;
        private System.Windows.Forms.ComboBox comData;
        private System.Windows.Forms.ComboBox comCheck;
        private System.Windows.Forms.ComboBox comBaud;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comPort;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox ADValue;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.ComboBox CheckCH;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox CheckTemp;
        private System.Windows.Forms.Button butCheckTemp;
        private System.Windows.Forms.Button butHardwareCheck;
        private System.Windows.Forms.TextBox CheckTempHigh;
        private System.Windows.Forms.TextBox CheckTempLow;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox CheckAdValue2;
        private System.Windows.Forms.TextBox CheckAdValue1;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox text_B;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox text_K;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RadioButton radioButDouble;
        private System.Windows.Forms.RadioButton radioButSingle;
    }
}

