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
    public partial class frmInputBox : Form
    {
        /// <summary>
        /// 
        /// </summary>
        public frmInputBox()
        {
            InitializeComponent();
        }

        private void btOK_Click(object sender, EventArgs e)
        {
           
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="Caption"></param>
        /// <param name="Title"></param>
        /// <param name="groupText"></param>
        /// <param name="defaultValue"></param>
        /// <returns></returns>
        public DialogResult ShowDialog(string Caption, string Title,string groupText, string defaultValue)
        {
            this.Text = Caption;
            lbTitle.Text = Title;
            txbText.Text = defaultValue;
            gbGround.Text = groupText;
            return this.ShowDialog();

        }

        /// <summary>
        /// 
        /// </summary>
        public string getTextValue
        {
            get
            {
                return txbText.Text;
            }
        }
    }
}
