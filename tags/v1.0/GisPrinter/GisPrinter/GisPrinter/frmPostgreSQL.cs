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
    public partial class frmPostgreSQL : Form
    {
        /// <summary>
        /// 
        /// </summary>
        protected string _user="";
        /// <summary>
        /// 
        /// </summary>
        protected string _pass="";
        /// <summary>
        /// 
        /// </summary>
        protected string _database="";
        /// <summary>
        /// 
        /// </summary>
        protected string _host="";
        /// <summary>
        /// 
        /// </summary>
        protected int _port=5432;
        /// <summary>
        /// 
        /// </summary>
        public frmPostgreSQL()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btOk_Click(object sender, EventArgs e)
        {
            if (txtUser.Text == "")
            {
                MessageBox.Show("Invalid Null user name", "GisPrinter", MessageBoxButtons.OKCancel, MessageBoxIcon.Error);
                txtUser.Focus();
            }
            else if (txtPass.Text == "")
            {
                MessageBox.Show("Invalid Null Password", "GisPrinter", MessageBoxButtons.OKCancel, MessageBoxIcon.Error);
                txtPass.Focus();
            }
            else if (txtDatabase.Text == "")
            {
                MessageBox.Show("Invalid Null Database Name", "GisPrinter", MessageBoxButtons.OKCancel, MessageBoxIcon.Error);
                txtDatabase.Focus();
            }
            else if (txtHost.Text == "")
            {
                MessageBox.Show("Invalid Null Host Name", "GisPrinter", MessageBoxButtons.OKCancel, MessageBoxIcon.Error);
                txtHost.Focus();
            }
            _user =txtUser.Text;
            _database = txtDatabase.Text;
            _pass = txtPass.Text;
            _host = txtHost.Text;
            if (txtPort.Text != "") _port = Convert.ToInt16(txtPort.Text);
            else                    _port = 5432;
            this.DialogResult = DialogResult.OK;
            Close();
        }

        /// <summary>
        /// 
        /// </summary>
        public string user
        {
            get
            {
                return _user;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public string password
        {
            get
            {
                return _pass;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public string database
        {
            get
            {
                return _database;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public string host
        {
            get
            {
                return _host;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public int port
        {
            get
            {
                return _port;
            }
        }

    }
}
