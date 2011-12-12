using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using TeComPrinterLib;


namespace GisPrinter
{
    public partial class frmMain : Form
    {
        protected int _vDisplacement=0;
        protected int _hDisplacement = 0;
        protected bool _enableZoom = false;
        frmProperty _frmProperty = null;
        protected bool _enableScroll = false;
        protected IDatabase _database;
        protected string _fileName="";
        

        public frmMain()
        {
            InitializeComponent();
            _database = null;   
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frmMain_Load(object sender, EventArgs e)
        {
            axPrinter.execute();
            clsZoomCombo.insertZoomValue(cmbZoom, (int)axPrinter.zoomFactor);
            hsbCanvas.Maximum = axPrinter.wClientArea;
            vsbCanvas.Maximum = axPrinter.hClientArea;
            hsbCanvas.Value = (int)(axPrinter.wClientArea/2);
            vsbCanvas.Value = (int)(axPrinter.hClientArea/2);
            _hDisplacement = hsbCanvas.Value;
            _vDisplacement = vsbCanvas.Value;
            _enableZoom = true;
            _enableScroll = true;
        }

        
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btExit_Click(object sender, EventArgs e)
        {
            Close();
        }


        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (MessageBox.Show("Do you wish close the application?", Application.ProductName, MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No)
            {
                e.Cancel = true;
            }
            
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btLeftAlign_Click(object sender, EventArgs e)
        {
            axPrinter.setAlign(Alignment.Left_Align);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btRightAlign_Click(object sender, EventArgs e)
        {
            axPrinter.setAlign(Alignment.Right_Align);
        }


        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btHrzCenterAlign_Click(object sender, EventArgs e)
        {
            axPrinter.setAlign(Alignment.Horizontal_Center_Align);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btVrtCenterAlign_Click(object sender, EventArgs e)
        {
            axPrinter.setAlign(Alignment.Vertical_Center_Align);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btTopAlign_Click(object sender, EventArgs e)
        {
            axPrinter.setAlign(Alignment.Top_Align);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btBottomAlign_Click(object sender, EventArgs e)
        {
            axPrinter.setAlign(Alignment.Bottom_Align);
        }


        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmInsertImage_Click(object sender, EventArgs e)
        {
            if (ofdOpen.ShowDialog() == DialogResult.OK)
            {
                axPrinter.addImage(ofdOpen.FileName);
                tstStatus.Text = "Insert Image";
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbZoom_SelectedValueChanged(object sender, EventArgs e)
        {
            if (_enableZoom)
            {
                axPrinter.zoomFactor = System.Convert.ToDouble(cmbZoom.Text.Remove(cmbZoom.Text.Length - 1));
                
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btZoomIn_Click(object sender, EventArgs e)
        {
            axPrinter.setLayoutMode(LAYOUT_MODE.LZoomArea);
            axPrinter.setMapMode(MAP_MODE.None);
            tstStatus.Text = "Zoom In";
        }

      
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btRecompose_Click(object sender, EventArgs e)
        {
            axPrinter.recompose();
            _enableScroll = false;

            hsbCanvas.Maximum = axPrinter.wClientArea;
            vsbCanvas.Maximum = axPrinter.hClientArea;
            hsbCanvas.Value = (int)(axPrinter.wClientArea / 2);
            vsbCanvas.Value = (int)(axPrinter.hClientArea / 2);
            _hDisplacement = hsbCanvas.Value;
            _vDisplacement = vsbCanvas.Value;
            clsZoomCombo.insertZoomValue(cmbZoom, (int)axPrinter.zoomFactor);
            _enableScroll = true;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmInsertRectangle_Click(object sender, EventArgs e)
        {
            axPrinter.addRectangle();
            tstStatus.Text = "Insert Rectangle";
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmInsertLine_Click(object sender, EventArgs e)
        {
            axPrinter.addLine();
            tstStatus.Text = "Insert Line";
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tmsInsertEllipse_Click(object sender, EventArgs e)
        {
            axPrinter.addEllipse();
            tstStatus.Text = "Insert Ellipse";
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmInsertScale_Click(object sender, EventArgs e)
        {
            axPrinter.addScale();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btDelete_Click(object sender, EventArgs e)
        {
            axPrinter.removeSelectedItems();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmInsertNorth_Click(object sender, EventArgs e)
        {
            axPrinter.addNorth();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmInsertText_Click(object sender, EventArgs e)
        {
            frmInputBox form = new frmInputBox() ;

            if (form.ShowDialog(Application.ProductName, "Insert the new Text","", "") == DialogResult.OK)
            {
                axPrinter.addText(form.getTextValue);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="fullFileName"></param>
        /// <returns></returns>
        private string getFileName(string fullFileName)
        {
            string fileName;
            fileName=System.IO.Path.GetFileName(fullFileName);
            int pos=fileName.IndexOf(".");
            if(pos>0)   
                return fileName.Remove(pos);
            return fileName;
        }
      
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btPrint_Click(object sender, EventArgs e)
        {
            if (_fileName.Length == 0) axPrinter.printExecute("GisPrinter");
            else
            {
                this.Cursor = Cursors.WaitCursor;
                axPrinter.printExecute(getFileName(_fileName));
                this.Cursor = Cursors.Default;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btProperties_Click(object sender, EventArgs e)
        {
            if ((_frmProperty == null) || (_frmProperty.IsDisposed == true))
            {
                _frmProperty = new frmProperty(axPrinter);
                clsProperty.insertObjectsName(axPrinter, _frmProperty.objectsName);
                _frmProperty.Show(this);

                tspProgress.Value = 0;
                Application.DoEvents();

                if (axPrinter.getLayoutSelectObjectCount() > 0)
                {
                    gbAlignment.Enabled = true;
                    enableMapView();
                    if (axPrinter.getLayoutSelectObjectCount() == 1)
                        _frmProperty.setObjectName(axPrinter.getLayoutSelectObjectName(0));

                }
                else
                {
                    gbAlignment.Enabled = false;
                    bgMapViewing.Enabled = false;
                    axPrinter.setMapMode(MAP_MODE.None);
                    _frmProperty.clear();
                }
            }
            _frmProperty.Focus();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void axPrinter_selectObjectEvent(object sender, AxTeComPrinterLib._ITePrinterEvents_selectObjectEvent e)
        {
            if (e.selItem)
            {
                if (axPrinter.getLayoutSelectObjectCount() == 1)
                {
                    clsProperty.setCurrentItem(_frmProperty.objectsName, axPrinter.getLayoutSelectObjectName(0));
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frmMain_Activated(object sender, EventArgs e)
        {
            tsmPaste.Enabled = !axPrinter.clipboardIsEmpty();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btPan_Click(object sender, EventArgs e)
        {
            axPrinter.setLayoutMode(LAYOUT_MODE.LPan);
            axPrinter.setMapMode(MAP_MODE.None);
            tstStatus.Text = "Pan";
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btSelect_Click(object sender, EventArgs e)
        {
            axPrinter.setLayoutMode(LAYOUT_MODE.LNone);
            axPrinter.setMapMode(MAP_MODE.None);
            tstStatus.Text = "Read";
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btZoomOut_Click(object sender, EventArgs e)
        {
            axPrinter.setLayoutMode(LAYOUT_MODE.LZoomOut);
            axPrinter.setMapMode(MAP_MODE.None);
            tstStatus.Text = "Zoom Out";
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void axPrinter_zoomAreaEvent(object sender, EventArgs e)
        {
            clsZoomCombo.insertZoomValue(cmbZoom, (int)axPrinter.zoomFactor);
            _enableScroll = false;
            hsbCanvas.Value = axPrinter.centerVisibleAreaX;
            vsbCanvas.Value = axPrinter.centerVisibleAreaY;
            _hDisplacement = hsbCanvas.Value;
            _vDisplacement = vsbCanvas.Value;
            _enableScroll = true;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void axPrinter_zoomOutEvent(object sender, EventArgs e)
        {
            clsZoomCombo.insertZoomValue(cmbZoom, (int)axPrinter.zoomFactor);
            _enableScroll = false;
            hsbCanvas.Value = axPrinter.centerVisibleAreaX;
            vsbCanvas.Value = axPrinter.centerVisibleAreaY;
            _hDisplacement = hsbCanvas.Value;
            _vDisplacement = vsbCanvas.Value;
            _enableScroll = true;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void axPrinter_panEvent(object sender, AxTeComPrinterLib._ITePrinterEvents_panEventEvent e)
        {
            _enableScroll = false;
            hsbCanvas.Value = axPrinter.centerVisibleAreaX;
            vsbCanvas.Value = axPrinter.centerVisibleAreaY;
            _hDisplacement = hsbCanvas.Value;
            _vDisplacement = vsbCanvas.Value;
            _enableScroll = true;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void hsbCanvas_Scroll(object sender, ScrollEventArgs e)
        {
            int value;
            try
            {
                if (_enableScroll)
                {
                    value = hsbCanvas.Value - _hDisplacement;
                    axPrinter.hrzDisplacement(value);
                    _hDisplacement = hsbCanvas.Value;
                }
                
            }
            finally
            {

            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void vsbCanvas_Scroll(object sender, ScrollEventArgs e)
        {
            int value;
            try
            {
                if (_enableScroll)
                {
                    value = vsbCanvas.Value - _vDisplacement;
                    axPrinter.vrtDisplacement(value);
                    _vDisplacement = vsbCanvas.Value;
                }
            }
            finally
            {

            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void axPrinter_mouseMoveEvent(object sender, AxTeComPrinterLib._ITePrinterEvents_mouseMoveEvent e)
        {
            tstPosition.Text = "Mouse Position x : " + ((int)e.x).ToString() + " | y : " + ((int)e.y).ToString();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void axPrinter_insertObjectEvent(object sender, EventArgs e)
        {
            tstStatus.Text = "Read";
            ComboBox cmb;
            if ((_frmProperty != null) && (_frmProperty.IsDisposed == false))
            {
                cmb = _frmProperty.objectsName;
                clsProperty.insertObjectsName(axPrinter, cmb);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void axPrinter_mouseUpEvent(object sender, AxTeComPrinterLib._ITePrinterEvents_mouseUpEvent e)
        {
          
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void axPrinter_endProcess(object sender, AxTeComPrinterLib._ITePrinterEvents_endProcessEvent e)
        {
            tspProgress.Value = 0;
            tsmPaste.Enabled = !axPrinter.clipboardIsEmpty();
            Application.DoEvents();

            if ( (axPrinter.getLayoutSelectObjectCount() > 0) && (e.partial==false) )
            {
                gbAlignment.Enabled = true;
                enableMapView();
                if (axPrinter.getLayoutSelectObjectCount() == 1)
                {
                    _frmProperty.setObjectName(axPrinter.getLayoutSelectObjectName(0));
                }
                
            }else if(e.partial == false)
            {
                gbAlignment.Enabled = false;
                bgMapViewing.Enabled = false;
                axPrinter.setMapMode(MAP_MODE.None);
                _frmProperty.clear();
            }
           
        }

        /// <summary>
        /// 
        /// </summary>
        private void enableMapView()
        {
            int i;

            //Melhorar esta opção!
            //Fazer um método que retorne se existe algum objeto do tipo especificado selecionado!!!
            
            bgMapViewing.Enabled = false;
            for (i = 0; i < axPrinter.getLayoutSelectObjectCount(); i++)
            {
                if (axPrinter.getLayoutObjectType(axPrinter.getLayoutSelectObjectName(i)) == LAYOUT_TYPES.LT_MAP)
                {
                    bgMapViewing.Enabled = true;
                    break;
                }
            }
            
        }
     
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmPageSetup_Click(object sender, EventArgs e)
        {
            frmPageSetup form;

            form = new frmPageSetup();
            form.pageSize = (int)axPrinter.paperSize;
            form.orientation = (int)axPrinter.orientation;
            if (form.ShowDialog() == DialogResult.OK)
            {
                axPrinter.paperSize = (pageSize)form.pageSize;
                axPrinter.orientation = (pageOrientation)form.orientation;
                axPrinter.execute();
                clsZoomCombo.insertZoomValue(cmbZoom, (int)axPrinter.zoomFactor);

                _enableScroll = false;
                hsbCanvas.Maximum = axPrinter.wClientArea;
                vsbCanvas.Maximum = axPrinter.hClientArea;
                hsbCanvas.Value = (int)(axPrinter.wClientArea / 2);
                vsbCanvas.Value = (int)(axPrinter.hClientArea / 2);
                _hDisplacement = hsbCanvas.Value;
                _vDisplacement = vsbCanvas.Value;
                _enableScroll = true;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmInsertMap_Click(object sender, EventArgs e)
        {
            axPrinter.addMap("TerraPrint");
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmAccess_Click(object sender, EventArgs e)
        {
            _database = new accessDB();
            if (_database.showConnectionDialog() == DialogResult.OK)
            {
                _database.connect();
                if (_database.isConnected())
                    axPrinter.connection = _database.adoConnection;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btMapZoomIn_Click(object sender, EventArgs e)
        {
            axPrinter.setMapMode(MAP_MODE.ZoomIn);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btMapZoomOut_Click(object sender, EventArgs e)
        {
            axPrinter.setMapMode(MAP_MODE.ZoomOut);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btMapPan_Click(object sender, EventArgs e)
        {
            axPrinter.setMapMode(MAP_MODE.Pan);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void axPrinter_processEvent(object sender, AxTeComPrinterLib._ITePrinterEvents_processEventEvent e)
        {
            tspProgress.Maximum = e.maxValue;
            tspProgress.Value = e.value;
            Application.DoEvents();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="status"></param>
        private void setEnableCanvasPopupMenu(bool status)
        {
            tsmSendToBack.Enabled = status;
            tsmBringToFront.Enabled = status;
            tsmDelete.Enabled = status;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void axPrinter_atlMouseUp(object sender, AxTeComPrinterLib._ITePrinterEvents_atlMouseUpEvent e)
        {
            if (e.button == 1)
            {
                if (axPrinter.getLayoutSelectObjectCount() > 0) setEnableCanvasPopupMenu(true);
                else setEnableCanvasPopupMenu(false);
                cmsCanvasMenu.Show(pnBackCanvas.Location.X + e.x, pnBackCanvas.Location.Y + e.y);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmSendToBack_Click(object sender, EventArgs e)
        {
            axPrinter.sendObjectToBack();
            axPrinter.execute();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmBringToFront_Click(object sender, EventArgs e)
        {
            axPrinter.bringObjectToFront();
            axPrinter.execute();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmDelete_Click(object sender, EventArgs e)
        {
            axPrinter.removeSelectedItems();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbZoom_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btRefresh_Click(object sender, EventArgs e)
        {
            Application.UseWaitCursor=true;
            this.Cursor = Cursors.WaitCursor;
            axPrinter.forceFullUpdate();
            this.Cursor = Cursors.Default;
            Application.UseWaitCursor = false;

        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void axPrinter_atlMouseDown(object sender, AxTeComPrinterLib._ITePrinterEvents_atlMouseDownEvent e)
        {
            axPrinter.Focus();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void databaseToolStripMenuItem_Click(object sender, EventArgs e)
        {
            axPrinter.addDatabase();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(_fileName.Length != 0)
                axPrinter.save(_fileName);
            else if (sfdSave.ShowDialog() == DialogResult.OK)
            {
                axPrinter.save(sfdSave.FileName);
                _fileName = sfdSave.FileName;
                tsmSaveAs.Enabled = true;
            }
            if(_fileName.Length !=0)
                this.Text = Application.ProductName + " [" + _fileName + "]";
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmNewPage_Click(object sender, EventArgs e)
        {
            axPrinter.newEmptyPage();
            tsmSaveAs.Enabled = false;
            _fileName = "";
            this.Text = Application.ProductName;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmOpen_Click(object sender, EventArgs e)
        {
            if (ofdOpenXml.ShowDialog() == DialogResult.OK)
            {
                Application.UseWaitCursor = true;
                this.Cursor = Cursors.WaitCursor;
                if (axPrinter.open(ofdOpenXml.FileName))
                {
                    tsmSaveAs.Enabled = true;
                    _fileName = ofdOpenXml.FileName;
                    this.Text = Application.ProductName + " [" + _fileName + "]";
                    clsZoomCombo.insertZoomValue(cmbZoom, (int)axPrinter.zoomFactor);
                }
                Application.UseWaitCursor = false;
                this.Cursor = Cursors.Default;
            }
        }
        
        /// <summary>
        /// 
        /// </summary>
        /// 
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmSaveAs_Click(object sender, EventArgs e)
        {
            if (sfdSave.ShowDialog() == DialogResult.OK)
            {
                axPrinter.save(sfdSave.FileName);
                _fileName = sfdSave.FileName;
                this.Text = Application.ProductName + " [" + _fileName + "]";
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mainToolBarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            tabMenuControl.Visible = !tabMenuControl.Visible;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmInsertTitle_Click(object sender, EventArgs e)
        {
            frmMText newText = new frmMText();
            if(newText.ShowDialog() == DialogResult.OK)
            {
                axPrinter.addMText(newText.mText);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmInsertMapLocalization_Click(object sender, EventArgs e)
        {
            axPrinter.addPoliticalDivision();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmCopy_Click(object sender, EventArgs e)
        {
            axPrinter.copyToClipboard();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmPaste_Click(object sender, EventArgs e)
        {
            axPrinter.pasteFromClipboard();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnsMain_MenuActivate(object sender, EventArgs e)
        {
            tsmPaste.Enabled = !axPrinter.clipboardIsEmpty();
        }


        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmViewHelp_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("help.chm");
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            frmAbout form = new frmAbout();
            form.ShowDialog();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmInsertBarcode_Click(object sender, EventArgs e)
        {
            frmInputBox form = new frmInputBox() ;

            if (form.ShowDialog(Application.ProductName, "Insert the new Text","", "") == DialogResult.OK)
            {
                //axPrinter.addaddBarcode(form.getTextValue);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btMapFullExtend_Click(object sender, EventArgs e)
        {
            axPrinter.setMapMode(MAP_MODE.FullExtend);
            axPrinter.execute();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmVLineControl_Click(object sender, EventArgs e)
        {
            axPrinter.addVLineControl();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tsmHLineControl_Click(object sender, EventArgs e)
        {
            axPrinter.addHLineControl();
        }

        private void tsmPostgres_Click(object sender, EventArgs e)
        {
            _database = new postgresDB();
            if (_database.showConnectionDialog() == DialogResult.OK)
            {
                
                if (_database.connect())
                {
                    axPrinter.provider = CONNECTION_TYPE.PostgreSQL;
                    axPrinter.connection = ((postgresDB)_database).connection;
                }
            }

        }

        private void tsmSqlServer_Click(object sender, EventArgs e)
        {

        }

    }
}
