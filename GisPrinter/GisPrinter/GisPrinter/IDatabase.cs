﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ADODB;

namespace GisPrinter
{
    public interface IDatabase
    {
        /// <summary>
        /// 
        /// </summary>
        string connectionString
        {
            get;
        }

        /// <summary>
        /// 
        /// </summary>
        DialogResult showConnectionDialog();

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        bool connect();

        /// <summary>
        /// 
        /// </summary>
        Connection adoConnection
        {
            get;
        }

        /// <summary>
        /// 
        /// </summary>
        short provider
        {
            get;
        }


        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        bool isConnected();

        /// <summary>
        /// 
        /// </summary>
        string user
        {
            get;
        }

        /// <summary>
        /// 
        /// </summary>
        string password
        {
            get;
        }

        /// <summary>
        /// 
        /// </summary>
        string host
        {
            get;
        }

        /// <summary>
        /// 
        /// </summary>
        string databaseName
        {
            get;
        }
    }
}
