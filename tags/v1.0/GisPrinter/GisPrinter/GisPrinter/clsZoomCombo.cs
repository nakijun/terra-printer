using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GisPrinter
{
    class clsZoomCombo
    {
        /// <summary>
        /// 
        /// </summary>
        private clsZoomCombo()
        {

        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="cmb"></param>
        /// <param name="value"></param>
        public static void insertZoomValue(ComboBox cmb, int value)
        {
            string cmbValue;

            int iValue;
            int i;
            
            for (i = 0; i < cmb.Items.Count; i++)
            {
               cmbValue=cmb.GetItemText(cmb.Items[i]);

               iValue = System.Convert.ToInt16(cmbValue.Remove(cmbValue.Length - 1));
               if (iValue > value) break;
               else if (iValue == value)
               {
                   if (i < cmb.Items.Count) cmb.SelectedIndex = i;
                   return;
               }
            }
            cmb.Items.Insert(i,value.ToString() + " %");
            if(i<cmb.Items.Count)   cmb.SelectedIndex = i;
        }
    }
}
