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
    public partial class frmMText : Form
    {
        string _text;

        public frmMText()
        {
            _text = "";
            InitializeComponent();
        }

        private void btOk_Click(object sender, EventArgs e)
        {
            _text = txtText.Text;
            this.DialogResult = DialogResult.OK;
            Close();
        }

        public string mText
        {
            get
            {
                return _text;
            }
        }

    }
}
