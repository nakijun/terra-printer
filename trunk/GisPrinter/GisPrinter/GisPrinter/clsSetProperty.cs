using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AxTeComPrinterLib;

namespace GisPrinter
{
    class clsSetProperty
    {

        protected AxTePrinter _printer=null;

        public clsSetProperty( AxTePrinter printer )
        {
            _printer = printer;
        }


        protected string getDatabaseProvider(string objectName, string propertyName, string properValue)
        {
            string objValue ="";
            TeComPrinterLib.LAYOUT_TYPES objType;

            if ((_printer == null)) return "";
            objType=_printer.getLayoutObjectType(objectName);
            if (TeComPrinterLib.LAYOUT_TYPES.LT_DATABASE == objType)
            {
                if (propertyName.ToUpper() == "DatabaseType_Property".ToUpper())
                {
                    if (properValue == "Sql Server") objValue = "1";
                    else if (properValue == "Oracle") objValue = "2";
                    else if (properValue == "FireBird") objValue = "3";
                    else if (properValue == "Postgres") objValue = "4";
                }
            }
            return objValue;
        }

        public void setPropertyValue(string objectName, string propertyName, string properValue)
        {
            string propName="";
            object objValue=0;
            string newValue;

            if ((_printer == null)) return;

            
            propName = clsProperty.getRealPropertyName(_printer, objectName, propertyName);
            newValue = getDatabaseProvider(objectName, propName, properValue);
            if(newValue.Length>0)
            {
                properValue = newValue;
            }

            if (_printer.getLayoutPropertyType(objectName, propName) == TeComPrinterLib.PROPERTY_TYPE.PNumber)
                    objValue = Convert.ToDouble(properValue);
            else if (_printer.getLayoutPropertyType(objectName, propName) == TeComPrinterLib.PROPERTY_TYPE.PBoolean)
            {
                if (properValue.ToUpper() == "TRUE") objValue = true;
                else objValue = false;
            }
            else
            {
                objValue = properValue;
            }
            _printer.setObjectPropertyValueByName(objectName, propName, objValue);
            _printer.execute();
        }
        
    }
}
