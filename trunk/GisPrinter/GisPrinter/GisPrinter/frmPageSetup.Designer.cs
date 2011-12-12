namespace GisPrinter
{
    partial class frmPageSetup
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmPageSetup));
            this.gbPaper = new System.Windows.Forms.GroupBox();
            this.lbSource = new System.Windows.Forms.Label();
            this.lbSize = new System.Windows.Forms.Label();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.cmbPageSize = new System.Windows.Forms.ComboBox();
            this.gbPreview = new System.Windows.Forms.GroupBox();
            this.pbLandscape = new System.Windows.Forms.PictureBox();
            this.pbPortrait = new System.Windows.Forms.PictureBox();
            this.gbOrientation = new System.Windows.Forms.GroupBox();
            this.rbLandscape = new System.Windows.Forms.RadioButton();
            this.rbPortrait = new System.Windows.Forms.RadioButton();
            this.gbMargin = new System.Windows.Forms.GroupBox();
            this.lbBottom = new System.Windows.Forms.Label();
            this.lbRight = new System.Windows.Forms.Label();
            this.lbTop = new System.Windows.Forms.Label();
            this.lbLeft = new System.Windows.Forms.Label();
            this.txbBottom = new System.Windows.Forms.TextBox();
            this.txbRight = new System.Windows.Forms.TextBox();
            this.txbTop = new System.Windows.Forms.TextBox();
            this.txbLeft = new System.Windows.Forms.TextBox();
            this.btOK = new System.Windows.Forms.Button();
            this.btCancel = new System.Windows.Forms.Button();
            this.printerD = new System.Windows.Forms.PrintDialog();
            this.lbPrinter = new System.Windows.Forms.Label();
            this.gbPaper.SuspendLayout();
            this.gbPreview.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbLandscape)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbPortrait)).BeginInit();
            this.gbOrientation.SuspendLayout();
            this.gbMargin.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbPaper
            // 
            this.gbPaper.Controls.Add(this.lbSource);
            this.gbPaper.Controls.Add(this.lbSize);
            this.gbPaper.Controls.Add(this.comboBox2);
            this.gbPaper.Controls.Add(this.cmbPageSize);
            this.gbPaper.Location = new System.Drawing.Point(12, 12);
            this.gbPaper.Name = "gbPaper";
            this.gbPaper.Size = new System.Drawing.Size(358, 118);
            this.gbPaper.TabIndex = 1;
            this.gbPaper.TabStop = false;
            this.gbPaper.Text = "Paper";
            // 
            // lbSource
            // 
            this.lbSource.AutoSize = true;
            this.lbSource.Enabled = false;
            this.lbSource.Location = new System.Drawing.Point(17, 89);
            this.lbSource.Name = "lbSource";
            this.lbSource.Size = new System.Drawing.Size(41, 13);
            this.lbSource.TabIndex = 4;
            this.lbSource.Text = "Source";
            // 
            // lbSize
            // 
            this.lbSize.AutoSize = true;
            this.lbSize.Location = new System.Drawing.Point(16, 38);
            this.lbSize.Name = "lbSize";
            this.lbSize.Size = new System.Drawing.Size(27, 13);
            this.lbSize.TabIndex = 3;
            this.lbSize.Text = "Size";
            // 
            // comboBox2
            // 
            this.comboBox2.Enabled = false;
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Location = new System.Drawing.Point(64, 89);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(277, 21);
            this.comboBox2.TabIndex = 2;
            // 
            // cmbPageSize
            // 
            this.cmbPageSize.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbPageSize.FormattingEnabled = true;
            this.cmbPageSize.Items.AddRange(new object[] {
            "ISO A0   :    841 x 1189 mm",
            "ISO A1   :    594 x 841 mm",
            "ISO A2   :    420 x 594 mm",
            "ISO A3   :    297 x 420 mm",
            "ISO A4   :    210 x 297 mm",
            "ISO A5   :    148 x 210 mm",
            "ISO A6   :    105 x 148 mm",
            "Custom"});
            this.cmbPageSize.Location = new System.Drawing.Point(64, 38);
            this.cmbPageSize.Name = "cmbPageSize";
            this.cmbPageSize.Size = new System.Drawing.Size(277, 21);
            this.cmbPageSize.TabIndex = 1;
            // 
            // gbPreview
            // 
            this.gbPreview.Controls.Add(this.pbLandscape);
            this.gbPreview.Controls.Add(this.pbPortrait);
            this.gbPreview.Location = new System.Drawing.Point(376, 12);
            this.gbPreview.Name = "gbPreview";
            this.gbPreview.Size = new System.Drawing.Size(175, 207);
            this.gbPreview.TabIndex = 2;
            this.gbPreview.TabStop = false;
            this.gbPreview.Text = "Preview";
            // 
            // pbLandscape
            // 
            this.pbLandscape.Image = ((System.Drawing.Image)(resources.GetObject("pbLandscape.Image")));
            this.pbLandscape.Location = new System.Drawing.Point(8, 42);
            this.pbLandscape.Name = "pbLandscape";
            this.pbLandscape.Size = new System.Drawing.Size(159, 123);
            this.pbLandscape.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pbLandscape.TabIndex = 1;
            this.pbLandscape.TabStop = false;
            this.pbLandscape.Visible = false;
            // 
            // pbPortrait
            // 
            this.pbPortrait.Image = ((System.Drawing.Image)(resources.GetObject("pbPortrait.Image")));
            this.pbPortrait.Location = new System.Drawing.Point(25, 24);
            this.pbPortrait.Name = "pbPortrait";
            this.pbPortrait.Size = new System.Drawing.Size(124, 158);
            this.pbPortrait.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pbPortrait.TabIndex = 0;
            this.pbPortrait.TabStop = false;
            // 
            // gbOrientation
            // 
            this.gbOrientation.Controls.Add(this.rbLandscape);
            this.gbOrientation.Controls.Add(this.rbPortrait);
            this.gbOrientation.Location = new System.Drawing.Point(14, 141);
            this.gbOrientation.Name = "gbOrientation";
            this.gbOrientation.Size = new System.Drawing.Size(135, 78);
            this.gbOrientation.TabIndex = 3;
            this.gbOrientation.TabStop = false;
            this.gbOrientation.Text = "Orientation";
            // 
            // rbLandscape
            // 
            this.rbLandscape.AutoSize = true;
            this.rbLandscape.Location = new System.Drawing.Point(20, 48);
            this.rbLandscape.Name = "rbLandscape";
            this.rbLandscape.Size = new System.Drawing.Size(78, 17);
            this.rbLandscape.TabIndex = 1;
            this.rbLandscape.Text = "Landscape";
            this.rbLandscape.UseVisualStyleBackColor = true;
            this.rbLandscape.CheckedChanged += new System.EventHandler(this.rbLandscape_CheckedChanged);
            // 
            // rbPortrait
            // 
            this.rbPortrait.AutoSize = true;
            this.rbPortrait.Checked = true;
            this.rbPortrait.Location = new System.Drawing.Point(20, 25);
            this.rbPortrait.Name = "rbPortrait";
            this.rbPortrait.Size = new System.Drawing.Size(58, 17);
            this.rbPortrait.TabIndex = 0;
            this.rbPortrait.TabStop = true;
            this.rbPortrait.Text = "Portrait";
            this.rbPortrait.UseVisualStyleBackColor = true;
            this.rbPortrait.CheckedChanged += new System.EventHandler(this.rbLandscape_CheckedChanged);
            // 
            // gbMargin
            // 
            this.gbMargin.Controls.Add(this.lbBottom);
            this.gbMargin.Controls.Add(this.lbRight);
            this.gbMargin.Controls.Add(this.lbTop);
            this.gbMargin.Controls.Add(this.lbLeft);
            this.gbMargin.Controls.Add(this.txbBottom);
            this.gbMargin.Controls.Add(this.txbRight);
            this.gbMargin.Controls.Add(this.txbTop);
            this.gbMargin.Controls.Add(this.txbLeft);
            this.gbMargin.Location = new System.Drawing.Point(155, 141);
            this.gbMargin.Name = "gbMargin";
            this.gbMargin.Size = new System.Drawing.Size(215, 78);
            this.gbMargin.TabIndex = 4;
            this.gbMargin.TabStop = false;
            this.gbMargin.Text = "Margins (millimeters)";
            // 
            // lbBottom
            // 
            this.lbBottom.AutoSize = true;
            this.lbBottom.Location = new System.Drawing.Point(113, 51);
            this.lbBottom.Name = "lbBottom";
            this.lbBottom.Size = new System.Drawing.Size(40, 13);
            this.lbBottom.TabIndex = 7;
            this.lbBottom.Text = "Bottom";
            // 
            // lbRight
            // 
            this.lbRight.AutoSize = true;
            this.lbRight.Location = new System.Drawing.Point(113, 23);
            this.lbRight.Name = "lbRight";
            this.lbRight.Size = new System.Drawing.Size(32, 13);
            this.lbRight.TabIndex = 6;
            this.lbRight.Text = "Right";
            // 
            // lbTop
            // 
            this.lbTop.AutoSize = true;
            this.lbTop.Location = new System.Drawing.Point(9, 55);
            this.lbTop.Name = "lbTop";
            this.lbTop.Size = new System.Drawing.Size(26, 13);
            this.lbTop.TabIndex = 5;
            this.lbTop.Text = "Top";
            // 
            // lbLeft
            // 
            this.lbLeft.AutoSize = true;
            this.lbLeft.Location = new System.Drawing.Point(9, 23);
            this.lbLeft.Name = "lbLeft";
            this.lbLeft.Size = new System.Drawing.Size(25, 13);
            this.lbLeft.TabIndex = 4;
            this.lbLeft.Text = "Left";
            // 
            // txbBottom
            // 
            this.txbBottom.Location = new System.Drawing.Point(154, 45);
            this.txbBottom.Name = "txbBottom";
            this.txbBottom.ReadOnly = true;
            this.txbBottom.Size = new System.Drawing.Size(55, 20);
            this.txbBottom.TabIndex = 3;
            // 
            // txbRight
            // 
            this.txbRight.Location = new System.Drawing.Point(154, 19);
            this.txbRight.Name = "txbRight";
            this.txbRight.ReadOnly = true;
            this.txbRight.Size = new System.Drawing.Size(55, 20);
            this.txbRight.TabIndex = 2;
            // 
            // txbTop
            // 
            this.txbTop.Location = new System.Drawing.Point(40, 48);
            this.txbTop.Name = "txbTop";
            this.txbTop.ReadOnly = true;
            this.txbTop.Size = new System.Drawing.Size(55, 20);
            this.txbTop.TabIndex = 1;
            // 
            // txbLeft
            // 
            this.txbLeft.Location = new System.Drawing.Point(40, 19);
            this.txbLeft.Name = "txbLeft";
            this.txbLeft.ReadOnly = true;
            this.txbLeft.Size = new System.Drawing.Size(55, 20);
            this.txbLeft.TabIndex = 0;
            // 
            // btOK
            // 
            this.btOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btOK.Location = new System.Drawing.Point(246, 233);
            this.btOK.Name = "btOK";
            this.btOK.Size = new System.Drawing.Size(75, 23);
            this.btOK.TabIndex = 5;
            this.btOK.Text = "Ok";
            this.btOK.UseVisualStyleBackColor = true;
            // 
            // btCancel
            // 
            this.btCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btCancel.Location = new System.Drawing.Point(450, 233);
            this.btCancel.Name = "btCancel";
            this.btCancel.Size = new System.Drawing.Size(75, 23);
            this.btCancel.TabIndex = 6;
            this.btCancel.Text = "Cancel";
            this.btCancel.UseVisualStyleBackColor = true;
            // 
            // printerD
            // 
            this.printerD.UseEXDialog = true;
            // 
            // lbPrinter
            // 
            this.lbPrinter.AutoSize = true;
            this.lbPrinter.Location = new System.Drawing.Point(16, 238);
            this.lbPrinter.Name = "lbPrinter";
            this.lbPrinter.Size = new System.Drawing.Size(53, 13);
            this.lbPrinter.TabIndex = 8;
            this.lbPrinter.Text = "No printer";
            // 
            // frmPageSetup
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(559, 262);
            this.Controls.Add(this.lbPrinter);
            this.Controls.Add(this.btCancel);
            this.Controls.Add(this.btOK);
            this.Controls.Add(this.gbMargin);
            this.Controls.Add(this.gbOrientation);
            this.Controls.Add(this.gbPreview);
            this.Controls.Add(this.gbPaper);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frmPageSetup";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Page Setup";
            this.gbPaper.ResumeLayout(false);
            this.gbPaper.PerformLayout();
            this.gbPreview.ResumeLayout(false);
            this.gbPreview.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbLandscape)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbPortrait)).EndInit();
            this.gbOrientation.ResumeLayout(false);
            this.gbOrientation.PerformLayout();
            this.gbMargin.ResumeLayout(false);
            this.gbMargin.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox gbPaper;
        private System.Windows.Forms.Label lbSource;
        private System.Windows.Forms.Label lbSize;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.ComboBox cmbPageSize;
        private System.Windows.Forms.GroupBox gbPreview;
        private System.Windows.Forms.GroupBox gbOrientation;
        private System.Windows.Forms.GroupBox gbMargin;
        private System.Windows.Forms.RadioButton rbLandscape;
        private System.Windows.Forms.RadioButton rbPortrait;
        private System.Windows.Forms.TextBox txbBottom;
        private System.Windows.Forms.TextBox txbRight;
        private System.Windows.Forms.TextBox txbTop;
        private System.Windows.Forms.TextBox txbLeft;
        private System.Windows.Forms.Label lbBottom;
        private System.Windows.Forms.Label lbRight;
        private System.Windows.Forms.Label lbTop;
        private System.Windows.Forms.Label lbLeft;
        private System.Windows.Forms.PictureBox pbPortrait;
        private System.Windows.Forms.PictureBox pbLandscape;
        private System.Windows.Forms.Button btOK;
        private System.Windows.Forms.Button btCancel;
        private System.Windows.Forms.PrintDialog printerD;
        private System.Windows.Forms.Label lbPrinter;
    }
}