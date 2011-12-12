using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;


namespace GisPrinter
{
    public partial class frmPageSetup : Form
    {
        /// <summary>
        /// 
        /// </summary>
        public frmPageSetup()
        {
            double x, y;
            InitializeComponent();

            x = (printerD.PrinterSettings.DefaultPageSettings.HardMarginX * 0.254);
            y = (printerD.PrinterSettings.DefaultPageSettings.HardMarginY * 0.254);
            lbPrinter.Text = printerD.PrinterSettings.PrinterName;
            txbLeft.Text= x.ToString();
            txbTop.Text = y.ToString();
            txbRight.Text = x.ToString();
            txbBottom.Text = y.ToString();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void rbLandscape_CheckedChanged(object sender, EventArgs e)
        {
            pbLandscape.Visible = rbLandscape.Checked;
            pbPortrait.Visible = rbPortrait.Checked;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="indexSize"></param>
        public int pageSize 
        {
            get
            {
                return cmbPageSize.SelectedIndex;
            }
    
            set
            {
                cmbPageSize.SelectedIndex=value;
            }
        }

        public int orientation
        {
            get
            {
                if (rbPortrait.Checked) return 0;
                return 1;
            }
            set
            {
                if(value == 1) rbLandscape.Checked=true;
                else           rbPortrait.Checked=true;
            }      
        }
	                            
	}
}
