using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ADODB;
using System.Windows.Forms;

namespace GisPrinter
{
    class accessDB : IDatabase
    {
        protected string _connectionString;
        protected Connection _connection;
        protected string _databaseName;

        public accessDB()
        {
            _connection = new Connection();
            _connectionString = "";
            _databaseName = "";
        }

        public string connectionString
        {
            get
            {
                return _connectionString;
            }
        }

        public DialogResult showConnectionDialog()
        {
             OpenFileDialog openFD = new OpenFileDialog();

             //openFD.InitialDirectory = "c:\\";
             openFD.Filter = "Access files (*.mdb)|*.mdb|All files (*.*)|*.*";
             openFD.FilterIndex = 1;
             openFD.RestoreDirectory = true;
             if (openFD.ShowDialog() == DialogResult.OK)
            {
                _connectionString="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
                _connectionString += openFD.FileName;
                _connectionString += ";User Id=admin;Password=;";
                _databaseName = openFD.FileName;
                return DialogResult.OK;
            }
             return DialogResult.Cancel;
        }

        public bool connect()
        {
            _connection.Open(_connectionString, "", "", -1);
            return this.isConnected();
        }

        public Connection adoConnection
        {
            get
            {
                return _connection;   
            }
        }

        public short provider
        {
            get
            {
                return 0;
            }
        }

        public bool isConnected()
        {
            if (_connection != null)
            {
                if (_connection.State != 0) return true;
            }
            return false;
        }

        public string user
        {
            get
            {
                return "";
            }
        }

        public string password
        {
            get
            {
                return "";
            }
        }

        public string host
        {
            get
            {
                return "";
            }
        }

        public string databaseName
        {
            get
            {
                return _databaseName;
            }
        }

    }
}
