using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TeComConnectionLib;
using System.Windows.Forms;
using ADODB;

namespace GisPrinter
{
    class postgresDB : IDatabase
    {
        protected string _user="";
        protected string _pass = "";
        protected string _database = "";
        protected string _host = "";
        protected int _port=5432;

        protected TeAcXConnection _postgresConn = null;

        public postgresDB()
        {
            _postgresConn = new TeAcXConnection();
        }

        public string connectionString
        {
            get
            {
                return "";
            }
        }

        public DialogResult showConnectionDialog()
        {
            frmPostgreSQL form = new frmPostgreSQL();

            if (form.ShowDialog() == DialogResult.OK)
            {
                _user = form.user;
                _pass = form.password;
                _database = form.database;
                _host = form.host;
                _port = form.port;
                return DialogResult.OK;
            }
            return DialogResult.Cancel;
        }

        public bool connect()
        {
            if ( (_user == "") || (_pass == "") || (_database == "")) return false;
            if (_host == "") _host = "localhost";
            return _postgresConn.open(_user, _pass, _database, _host, _port);
            
        }

        public object connection
        {
            get
            {
                return _postgresConn.objectConnection_;
            }
        }

        public Connection adoConnection
        {
            get
            {
                return null;   
            }
        }

        public short provider
        {
            get
            {
                return 4;
            }
        }

        public bool isConnected()
        {
            return false;
        }

        public string user
        {
            get
            {
                return _user;
            }
        }

        public string password
        {
            get
            {
                return _pass;
            }
        }

        public string host
        {
            get
            {
                return _host;
            }
        }

        public string databaseName
        {
            get
            {
                return _database;
            }
        }
    }
}
