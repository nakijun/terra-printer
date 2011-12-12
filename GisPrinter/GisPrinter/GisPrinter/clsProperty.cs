using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms; 
using AxTeComPrinterLib;
using CustomListView;
using System.Collections;
using System.Collections.Specialized;

namespace GisPrinter
{
    class clsProperty
    {
        public enum property_types
        {
            ptUnkwon=-1,
            ptInteger = 0,
            ptDouble = 1,
            ptBoolean = 2,
            ptColor = 3,
            ptList = 4,
            ptString = 5
        };

        protected struct property_data
        {
            public string  name;
            public property_types type;
            public string[] list;
        };


        protected static StringDictionary _lineType;
        protected static  property_data[] _propertiesType;
        protected static StringDictionary _rectangleType;
        protected static StringDictionary _ellipseType;
        protected static StringDictionary _imageType;
        protected static StringDictionary _textType;
        protected static StringDictionary _scaleType;
        protected static StringDictionary _northType;
        protected static StringDictionary _mapType;
        protected static StringDictionary _databaseType;


        /// <summary>
        /// 
        /// </summary>
        protected static void init()
        {
            init_lineType();
            init_rectangleType();
            init_imageType();
            init_ellipseType();
            init_textType();
            init_scaleType();
            init_propertiesType();
            init_northType();
            init_mapType();
            init_databaseType();
        }


        /// <summary>
        /// 
        /// </summary>
        protected static void init_propertiesType()
        {
            _propertiesType = new property_data[39];

            _propertiesType[0].name = "width";
            _propertiesType[0].type = property_types.ptInteger;
            _propertiesType[1].name = "Left";
            _propertiesType[1].type = property_types.ptInteger;
            _propertiesType[2].name = "Top";
            _propertiesType[2].type = property_types.ptInteger;
            _propertiesType[3].name = "Height";
            _propertiesType[3].type = property_types.ptInteger;
            _propertiesType[4].name = "Angle";
            _propertiesType[4].type = property_types.ptDouble;
            _propertiesType[5].name = "Line Width";
            _propertiesType[5].type = property_types.ptInteger;
            _propertiesType[6].name = "Line Type";
            _propertiesType[6].type = property_types.ptList;
            _propertiesType[6].list = new string[5];
            _propertiesType[6].list[0] = "Continuous";
            _propertiesType[6].list[1] = "Dash";
            _propertiesType[7].name = "Color";
            _propertiesType[7].type = property_types.ptColor;
            _propertiesType[8].name = "Fill";
            _propertiesType[8].type = property_types.ptList;
            _propertiesType[9].name = "Fill Color";
            _propertiesType[9].type = property_types.ptColor;
            _propertiesType[10].name = "Line Color";
            _propertiesType[10].type = property_types.ptColor;
            _propertiesType[11].name = "File Name";
            _propertiesType[11].type = property_types.ptString;
            _propertiesType[12].name = "Bold";
            _propertiesType[12].type = property_types.ptBoolean;
            _propertiesType[13].name = "Italic";
            _propertiesType[13].type = property_types.ptBoolean;
            _propertiesType[14].name = "Text";
            _propertiesType[14].type = property_types.ptString;
            _propertiesType[15].name = "Font Size";
            _propertiesType[15].type = property_types.ptInteger;
            _propertiesType[16].name = "Font Name";
            _propertiesType[16].type = property_types.ptList;
            _propertiesType[16].list = new string[5];
            _propertiesType[16].list[0] = "Arial";
            _propertiesType[16].list[1] = "Symbol";
            _propertiesType[16].list[2] = "Times New Roman";
            _propertiesType[16].list[3] = "Verdana";
            _propertiesType[16].list[4] = "Teste";
            _propertiesType[17].name = "Font Color";
            _propertiesType[17].type = property_types.ptColor;

            _propertiesType[18].type = property_types.ptList;
            _propertiesType[18].list = new String[13];
            _propertiesType[18].name = "Type";
            _propertiesType[18].list[0] = "North01";
            _propertiesType[18].list[1] = "North02";
            _propertiesType[18].list[2] = "North03";
            _propertiesType[18].list[3] = "North04";
            _propertiesType[18].list[4] = "North05";
            _propertiesType[18].list[5] = "North06";
            _propertiesType[18].list[6] = "North07";
            _propertiesType[18].list[7] = "North08";
            _propertiesType[18].list[8] = "North09";
            _propertiesType[18].list[9] = "North10";
            _propertiesType[18].list[10] = "North11";
            _propertiesType[18].list[11] = "North12";
            _propertiesType[18].list[12] = "North13";

            _propertiesType[19].type = property_types.ptList;
            _propertiesType[19].list = new String[15];
            _propertiesType[19].name = "Scale"; 
            _propertiesType[19].list[0] = "1";
            _propertiesType[19].list[1] = "100";
            _propertiesType[19].list[2] = "1000";
            _propertiesType[19].list[3] = "2000";
            _propertiesType[19].list[4] = "2500";
            _propertiesType[19].list[5] = "5000";
            _propertiesType[19].list[6] = "10000";
            _propertiesType[19].list[7] = "20000";
            _propertiesType[19].list[8] = "25000";
            _propertiesType[19].list[9] = "50000";
            _propertiesType[19].list[10] = "100000";
            _propertiesType[19].list[11] = "200000";
            _propertiesType[19].list[12] = "250000";
            _propertiesType[19].list[13] = "500000";
            _propertiesType[19].list[14] = "1000000";

            _propertiesType[20].type = property_types.ptList;
            _propertiesType[20].list = new String[2];
            _propertiesType[20].name = "Unit";
            _propertiesType[20].list[0] = "Meter";
            _propertiesType[20].list[1] = "Kilometer";

            _propertiesType[21].type = property_types.ptBoolean;
            _propertiesType[21].name = "Fixed Scale";

            _propertiesType[22].type = property_types.ptString;
            _propertiesType[22].name = "User Name";

            _propertiesType[23].type = property_types.ptString;
            _propertiesType[23].name = "Password";

            _propertiesType[24].type = property_types.ptString;
            _propertiesType[24].name = "Host";

            _propertiesType[25].type = property_types.ptString;
            _propertiesType[25].name = "Database Name";


            _propertiesType[26].type = property_types.ptBoolean;
            _propertiesType[26].name = "Connected";

            _propertiesType[27].type = property_types.ptString;
            _propertiesType[27].name="Connection";

            _propertiesType[28].type = property_types.ptList;
            _propertiesType[28].name = "Provider";
            _propertiesType[28].list = new String[4];
            _propertiesType[28].list[0] = "Sql Server";
            _propertiesType[28].list[1] = "Oracle";
            _propertiesType[28].list[2] = "FireBird";
            _propertiesType[28].list[3] = "Postgres";

            _propertiesType[29].type = property_types.ptString;
            _propertiesType[29].name = "View Name";

            _propertiesType[30].type = property_types.ptString;
            _propertiesType[30].name = "View User";

            _propertiesType[31].name = "X1";
            _propertiesType[31].type = property_types.ptDouble;

            _propertiesType[32].name = "Y1";
            _propertiesType[32].type = property_types.ptDouble;

            _propertiesType[33].name = "X2";
            _propertiesType[33].type = property_types.ptDouble;

            _propertiesType[34].name = "Y2";
            _propertiesType[34].type = property_types.ptDouble;

            _propertiesType[35].type = property_types.ptString;
            _propertiesType[35].name = "Selected Theme";

            _propertiesType[36].type = property_types.ptString;
            _propertiesType[36].name = "Selected Features";

            _propertiesType[37].name = "Selection Color";
            _propertiesType[37].type = property_types.ptDouble;

            _propertiesType[38].name = "Selection Transparency";
            _propertiesType[38].type = property_types.ptDouble;
            

            

        }


        protected static void init_databaseType()
        {

            _databaseType = new StringDictionary();
            _databaseType["Width"] = "Width";
            _databaseType["Left"] = "Left";
            _databaseType["Top"] = "Top";
            _databaseType["Height"] = "Height";
            _databaseType["Angle"] = "Angle";
            _databaseType["UserName"] = "User Name";
            _databaseType["Password"]= "Password";
            _databaseType["Host"] = "Host";
            _databaseType["DatabaseName"] = "Database Name";
            _databaseType["DatabaseConnected"] = "Connected";
            _databaseType["DatabaseType"] = "Provider";
        }

        /// <summary>
        /// 
        /// </summary>
        protected static void init_lineType()
        {
            _lineType = new StringDictionary();
            _lineType["Width"] = "Width";
            _lineType["Left"] = "Left";
            _lineType["Top"] = "Top";
            _lineType["Height"] = "Height";
            _lineType["Angle"] = "Angle";
            _lineType["LineWidth"] = "Line Width";
            _lineType["LineType"] = "Line Type";
            _lineType["RedColor"] = "Color";
        }

        /// <summary>
        /// 
        /// </summary>
        protected static void init_rectangleType()
        {
            _rectangleType = new StringDictionary();
            _rectangleType["Width"] = "Width";
            _rectangleType["Left"] = "Left";
            _rectangleType["Top"] = "Top";
            _rectangleType["Height"] = "Height";
            _rectangleType["Angle"] = "Angle";
            _rectangleType["LineWidth"] = "Line Width";
            _rectangleType["LineType"] = "Line Type";
            _rectangleType["BackgroundType"] = "Fill";
            _rectangleType["BackgroundRed"] = "Fill Color";
            _rectangleType["RedColor"]="Line Color";

        }

        
        /// <summary>
        /// 
        /// </summary>
        protected static void init_ellipseType()
        {
            _ellipseType = new StringDictionary();
            _ellipseType["Width"] = "Width";
            _ellipseType["Left"] = "Left";
            _ellipseType["Top"] = "Top";
            _ellipseType["Height"] = "Height";
            _ellipseType["Angle"] = "Angle";
            _ellipseType["LineWidth"] = "Line Width";
            _ellipseType["LineType"] = "Line Type";
            _ellipseType["BackgroundType"] = "Fill";
            _ellipseType["BackgroundRed"] = "Fill Color";
            _ellipseType["RedColor"] = "Line Color";

        }

        /// <summary>
        /// 
        /// </summary>
        protected static void init_imageType()
        {
            _imageType = new StringDictionary();
            _imageType["Width"] = "Width";
            _imageType["Left"] = "Left";
            _imageType["Top"] = "Top";
            _imageType["Height"] = "Height";
            _imageType["Angle"] = "Angle";
            _imageType["ImageFileName"] = "File Name";

        }

        protected static void init_northType()
        {
            _northType = new StringDictionary();
            _northType["Width"] = "Width";
            _northType["Left"] = "Left";
            _northType["Top"] = "Top";
            _northType["Height"] = "Height";
            _northType["Angle"] = "Angle";
            _northType["North"] = "Type";
        }

        protected static void init_textType()
        {
            _textType = new StringDictionary();
            _textType["Width"] = "Width";
            _textType["Left"] = "Left";
            _textType["Top"] = "Top";
            _textType["Height"] = "Height";
            _textType["Angle"] = "Angle";
            _textType["TextValue"] = "Text";
            _textType["TextSize"] = "Font Size";
            _textType["TextFontName"] = "Font Name";
            _textType["TextBold"] = "Bold";
            _textType["TextItalic"] = "Italic";
            _textType["ForeTextColorR"] = "Font Color";

        }

        protected static void init_scaleType()
        {
            _scaleType = new StringDictionary();
            _scaleType["Width"] = "Width";
            _scaleType["Left"] = "Left";
            _scaleType["Top"] = "Top";
            _scaleType["Height"] = "Height";
            _scaleType["Angle"] = "Angle";
            _scaleType["MapScale"] = "Scale";
            _scaleType["ScaleUnit"] = "Unit";
            _scaleType["ForeTextColorR"] = "Fore Color";
            _scaleType["RedColor"] = "Back Color";
        }

        protected static void init_mapType()
        {
            _mapType = new StringDictionary();
            _mapType["Width"] = "Width";
            _mapType["Left"] = "Left";
            _mapType["Top"] = "Top";
            _mapType["Height"] = "Height";
            _mapType["Angle"] = "Angle";
            _mapType["MapScale"] = "Scale";
            _mapType["FixedScale"] = "Fixed Scale";
            _mapType["Connection"]= "Connection";
            _mapType["ViewName"] = "View Name";
            _mapType["ViewUser"] = "View User";
            _mapType["MapWorld_X1"] = "X1";
            _mapType["MapWorld_Y1"] = "Y1";
            _mapType["MapWorld_X2"] = "X2";
            _mapType["MapWorld_Y2"] = "Y2";
            _mapType["SelectedThemeName"] = "Selected Theme";
            _mapType["SelectedFeatures"] = "Selected Features";
            _mapType["SelectionColor"]="Selection Color";
            _mapType["SelectionTransparency"] = "Selection Transparency";
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="axPrinter"></param>
        /// <param name="combo"></param>
        public static void insertObjectsName(AxTePrinter axPrinter, ComboBox combo)
        {
            int i;
            if (combo == null) return;
            combo.Items.Clear();

            for (i = 0; i < axPrinter.getLayoutObjectCount(); i++)
            {
                combo.Items.Add(axPrinter.getLayoutObjectName(i));
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="combo"></param>
        /// <param name="itemValue"></param>
        public static void setCurrentItem(ComboBox combo, string itemValue)
        {
            combo.SelectedIndex=combo.FindString(itemValue);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="axPrinter"></param>
        /// <param name="objectName"></param>
        public static void setSelectLayoutObjectItem(AxTePrinter axPrinter, string objectName)
        {
            if (axPrinter.selectObject(objectName))
            {

                axPrinter.execute();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="objectName"></param>
        /// <param name="axPrinter"></param>
        /// <param name="listEx"></param>
        public static void setListItemsCount(string objectName, AxTePrinter axPrinter,ListViewEx  listEx)
        {
            int             objCount;
            int             listCount;
            ListViewItem    listItem;

            listEx.clearCell();
            objCount=axPrinter.getLayoutObjectPropertiesCount(objectName);
            listCount=listEx.Items.Count;
            if (objCount > listCount)
            {
                while (listEx.Items.Count < objCount)
                {
                    listItem = listEx.Items.Add("Undefined");
                    listItem.SubItems.Add("");
                }
            }
            else if (objCount < listCount)
            {
                while (objCount < listEx.Items.Count)
                    listEx.Items.Remove(listEx.Items[listEx.Items.Count - 1]);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="objectName"></param>
        /// <param name="axPrinter"></param>
        /// <param name="listEx"></param>
        public static void setListItemsName(string objectName, AxTePrinter axPrinter, ListView listEx)
        {
            int i;
            string propertyName;

            for (i = 0; i < axPrinter.getLayoutObjectPropertiesCount(objectName); i++)
            {
                propertyName=axPrinter.getLayoutObjectPropertyName(objectName, i);
                propertyName = getAlias(objectName, axPrinter, propertyName.Replace("_Property", ""));//  propertyName.Replace("_Property", "");//
                listEx.Items[i].Text = propertyName;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="objectName"></param>
        /// <param name="axPrinter"></param>
        /// <param name="propertyName"></param>
        /// <returns></returns>
        protected static string getAlias(string objectName, AxTePrinter axPrinter, string propertyName)
        {
            TeComPrinterLib.LAYOUT_TYPES    objType;
            if (_lineType == null) init();
            objType = axPrinter.getLayoutObjectType(objectName);
            switch (objType)
            {
                case TeComPrinterLib.LAYOUT_TYPES.LT_LINE: return _lineType[propertyName];
                case TeComPrinterLib.LAYOUT_TYPES.LT_RECTANGLE: return _rectangleType[propertyName];
                case TeComPrinterLib.LAYOUT_TYPES.LT_ELLIPSE: return _ellipseType[propertyName];
                case TeComPrinterLib.LAYOUT_TYPES.LT_IMAGE: return _imageType[propertyName];
                case TeComPrinterLib.LAYOUT_TYPES.LT_TEXT: return _textType[propertyName];
                case TeComPrinterLib.LAYOUT_TYPES.LT_SCALE: return _scaleType[propertyName];
                case TeComPrinterLib.LAYOUT_TYPES.LT_NORTH: return _northType[propertyName];
                case TeComPrinterLib.LAYOUT_TYPES.LT_MAP: return _mapType[propertyName];
                case TeComPrinterLib.LAYOUT_TYPES.LT_DATABASE: return _databaseType[propertyName];
            }
            return "";
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="listEx"></param>
        public static void removeEmptyItems(ListView listEx)
        {
            int i;

            for (i = listEx.Items.Count-1 ; i >0; i--)
            {
                if (listEx.Items[i].Text.Length == 0)
                {
                    listEx.Items.Remove(listEx.Items[i]);
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="propertyName"></param>
        /// <param name="listEx"></param>
        /// <returns></returns>
        protected static int getRowPropertyIndex(string propertyName, ListView listEx)
        {
            int i;
            if (propertyName != null)
            {
                if (propertyName.Length == 0) return -1;

                for (i = 0; i < listEx.Items.Count; i++)
                {
                    if (listEx.Items[i].Text.ToUpper() == propertyName.ToUpper())
                        return i;
                }
            }
            return -1;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="propertyName"></param>
        /// <returns></returns>
        protected static property_types getType(string propertyName)
        {
            foreach (property_data obj in _propertiesType)
            {
                if (obj.name.ToUpper() == propertyName.ToUpper())
                    return obj.type;
            }
            return property_types.ptUnkwon;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="propertyName"></param>
        /// <returns></returns>
        protected static string[] getList(string propertyName)
        {
            foreach (property_data obj in _propertiesType)
            {
                if (obj.name.ToUpper() == propertyName.ToUpper())
                    return obj.list;
            }
            return null;

        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="row"></param>
        /// <param name="type"></param>
        /// <param name="listEx"></param>
        protected static void setListType(int row, property_types type, ListViewEx listEx,string [] listValue)
        {
            string[] strBoolean = { "True", "False"};

            switch (type)
            {
                case property_types.ptInteger: 
                case property_types.ptDouble:
                case property_types.ptString:   listEx.AddEditableCell(row, 1);
                                                break;
                case property_types.ptBoolean:
                                                listEx.AddComboBoxCell(row, 1, strBoolean);
                                                break;
                case property_types.ptList :
                                                listEx.AddComboBoxCell(row, 1, listValue);
                                                break;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="row"></param>
        /// <param name="type"></param>
        /// <param name="listEx"></param>
        /// <param name="value"></param>
        protected static void setListValue(int row, property_types type, ListView listEx, object value)
        {
            switch (type)
            {
                case property_types.ptInteger:  listEx.Items[row].SubItems[1].Text = String.Format("{0:D}", Convert.ToInt32(value));
                                                break;
                case property_types.ptDouble:   
                                                listEx.Items[row].SubItems[1].Text = String.Format("{0:F}",value);
                                                break;
                case property_types.ptString: 
                                                listEx.Items[row].SubItems[1].Text = Convert.ToString(value);
                                                break;
                case property_types.ptBoolean:
                                                listEx.Items[row].SubItems[1].Text = Convert.ToString(value);
                                                break;
                case property_types.ptList :
                                                listEx.Items[row].SubItems[1].Text = Convert.ToString(value);            
                                                break;
                
            }

        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="axPrinter"></param>
        /// <param name="objectName"></param>
        /// <param name="propertName"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        protected static object getAliasValue(AxTePrinter axPrinter,string objectName, string propertName, object value)
        {
            object result=null;
            TeComPrinterLib.LAYOUT_TYPES objType;
            objType = axPrinter.getLayoutObjectType(objectName);

            switch (objType)
            {
                case TeComPrinterLib.LAYOUT_TYPES.LT_DATABASE:
                    {
                        if (propertName == "Provider")
                        {
                            switch (Convert.ToInt32(value))
                            {
                                case 1: result = "Sql Server";
                                    break;
                                case 2: result = "Oracle";
                                    break;
                                case 3: result = "FireBird";
                                    break;
                                case 4: result = "Postgres";
                                    break;
                            }
                        }
                    }break;
            }
            return result;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="objectName"></param>
        /// <param name="axPrinter"></param>
        /// <param name="listEx"></param>
        public static void setListItemsValue(string objectName, AxTePrinter axPrinter, ListViewEx listEx)
        {
            int i;
            int row;
            string propertyName;
            property_types type;
            object aliasValue;

            for (i = 0; i < axPrinter.getLayoutObjectPropertiesCount(objectName); i++)
            {
                propertyName = axPrinter.getLayoutObjectPropertyName(objectName, i);
                propertyName = getAlias(objectName, axPrinter, propertyName.Replace("_Property", ""));
                row = getRowPropertyIndex(propertyName, listEx);
                if (row != -1)
                {
                    type = getType(propertyName);
                    setListType(row, type, listEx, getList(propertyName));
                    aliasValue = getAliasValue(axPrinter, objectName, propertyName, axPrinter.getLayoutObjectPropertyValue(objectName, i));
                    if (aliasValue != null) setListValue(row, type, listEx, aliasValue);
                    else                    setListValue(row,type,listEx,axPrinter.getLayoutObjectPropertyValue(objectName,i));
                }
            }

        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="axPrinter"></param>
        /// <param name="objectName"></param>
        /// <param name="propertyName"></param>
        /// <returns></returns>
        public static string getRealPropertyName(AxTePrinter axPrinter,string objectName, string propertyName)
        {

            TeComPrinterLib.LAYOUT_TYPES objType;
            
            objType = axPrinter.getLayoutObjectType(objectName);
            switch (objType)
            {
                case TeComPrinterLib.LAYOUT_TYPES.LT_LINE: return getRealPropertyNameFromLine(_lineType, propertyName);
                case TeComPrinterLib.LAYOUT_TYPES.LT_RECTANGLE: return getRealPropertyNameFromLine(_rectangleType, propertyName);
                case TeComPrinterLib.LAYOUT_TYPES.LT_ELLIPSE: return getRealPropertyNameFromLine(_ellipseType, propertyName);
                case TeComPrinterLib.LAYOUT_TYPES.LT_IMAGE: return getRealPropertyNameFromLine(_imageType, propertyName);
                case TeComPrinterLib.LAYOUT_TYPES.LT_TEXT: return getRealPropertyNameFromLine(_textType, propertyName);
                case TeComPrinterLib.LAYOUT_TYPES.LT_SCALE: return getRealPropertyNameFromLine(_scaleType, propertyName);
                case TeComPrinterLib.LAYOUT_TYPES.LT_NORTH: return getRealPropertyNameFromLine(_northType, propertyName);
                case TeComPrinterLib.LAYOUT_TYPES.LT_MAP: return getRealPropertyNameFromLine(_mapType, propertyName);
                case TeComPrinterLib.LAYOUT_TYPES.LT_DATABASE: return getRealPropertyNameFromLine(_databaseType, propertyName);
            }
            return "";
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="dic"></param>
        /// <param name="propertyName"></param>
        /// <returns></returns>
        protected static string getRealPropertyNameFromLine(StringDictionary dic, string propertyName)
        {
            string result = "";
            IEnumerator myEnumerator = dic.GetEnumerator();
            DictionaryEntry de;
            while ( myEnumerator.MoveNext() )  
            {
                de = (DictionaryEntry) myEnumerator.Current;
                if (de.Value.ToString() == propertyName)
                {
                    result = de.Key.ToString() + "_Property";
                    break;
                }
            }
            return result;
        }

    }
}

