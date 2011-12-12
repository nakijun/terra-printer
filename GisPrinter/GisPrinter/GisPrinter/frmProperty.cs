using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AxTeComPrinterLib;
using CustomListView;

namespace GisPrinter
{
    public partial class frmProperty : Form
    {
        protected AxTePrinter _axPrinter;

        protected bool Showed = false;

        /// <summary>
        /// 
        /// </summary>
        public frmProperty()
        {
            InitializeComponent();
            _axPrinter = null;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="axPrinter"></param>
        public frmProperty(AxTePrinter axPrinter)
        {
            InitializeComponent();
            _axPrinter = axPrinter;
        }

        

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frmProperty_Load(object sender, EventArgs e)
        {
            
        }

        /// <summary>
        /// 
        /// </summary>
        public ComboBox objectsName
        {
            get
            {
                return cmbObjects;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public bool status
        {
            get
            {
                return Showed;
            }
        }
        
        /// <summary>
        /// 
        /// </summary>
        /// <param name="objName"></param>
        public void setObjectName(string objName)
        {
            bool update = false;

            if (objName == cmbObjects.Text) update = true;
            if(objName.Length>0)    cmbObjects.Text = objName;
            else
            {
                cmbObjects.SelectedIndex = -1;
            }
            if (update == true) 
                cmbObjects_SelectedValueChanged(null, null);
        }

        /// <summary>
        /// 
        /// </summary>
        public void clear()
        {
            cmbObjects.SelectedIndex = -1;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbObjects_SelectedValueChanged(object sender, EventArgs e)
        {
            if (cmbObjects.Text.Length > 0)
            {
                clsProperty.setSelectLayoutObjectItem(_axPrinter, cmbObjects.Text);
                clsProperty.setListItemsCount(cmbObjects.Text, _axPrinter, lvProperties);
                clsProperty.setListItemsName(cmbObjects.Text, _axPrinter, lvProperties);
                clsProperty.removeEmptyItems(lvProperties);
                clsProperty.setListItemsValue(cmbObjects.Text, _axPrinter, lvProperties);
            }
            else
            {
                lvProperties.clearCell();
                lvProperties.Items.Clear();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void lvProperties_updateCell(object sender, propertyEventArgs e)
        {
            clsSetProperty setProp = new clsSetProperty(_axPrinter);
            setProp.setPropertyValue(cmbObjects.Text, e.propertName, e.propertyValue.ToString());
        }


        private void lvProperties_SelectedIndexChanged(object sender, EventArgs e)
        {
            
        }

        private void frmProperty_Shown(object sender, EventArgs e)
        {
            Showed = true;
        }

        private void frmProperty_FormClosed(object sender, FormClosedEventArgs e)
        {
            Showed = false;
        }

        

    }
}
