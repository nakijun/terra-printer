#include <TdkGraphicViewService.h>
#include <TdkAbstractCanvasDraw.h>
#include <TdkAbstractEvents.h>
#include <TdkProjectionUtils.h>
#include <TeGeometryAlgorithms.h>
#include <TdkProcessEvent.h>
#include <TeView.h>
#include <TeTheme.h>
#include <TeVisual.h>
#include <TeDatabase.h>
#include <TeRasterTransform.h>
#include <TeVectorRemap.h>
#include <TeDecoderMemory.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkGraphicViewService::TdkGraphicViewService(TdkAbstractEvents *ev, bool *stop)
{
	_events=ev;
	_backRaster=NULL;
	_stopProcess=stop;
	_lastLegend=InvalidLegend;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkGraphicViewService::~TdkGraphicViewService()
{
	resetBackRaster();
}


///////////////////////////////////////////////////////////////////////////////
//Draw a terralib view
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawView(TeView *view, TdkAbstractCanvasDraw *canvas,const double &mapScale)
{
	bool											status=false;
	std::vector<TeViewNode*>::reverse_iterator		rItNodes;
	std::vector<TeViewNode*>						nodes;

	if(view == NULL)		throw "Invalid null view pointer";
	if(canvas == NULL)		throw "Invalid null canvas pointer";
	
	setWorldRasterParams(view->projection(),canvas);
	nodes=view->themes();
	for(rItNodes=nodes.rbegin();rItNodes!=nodes.rend();rItNodes++)		
	{
		if(validScale(view->projection(),(TeAbstractTheme*)*rItNodes,canvas,mapScale) == true)	status&=drawTheme((TeAbstractTheme*) \
																						*rItNodes,view->projection(),canvas);

		if(_stopProcess)
		{
			if(*_stopProcess)	break;
		}
						
	}
	return status;
}

///////////////////////////////////////////////////////////////////////////////
//Draw the selected features
//Author : Rui Mauricio Gregório 
//Date : 12/2011
///////////////////////////////////////////////////////////////////////////////

bool TdkGraphicViewService::drawSelectedFeatures(TeView *view,TeTheme *theme, TeVisual *visual, TdkAbstractCanvasDraw *canvas,const double &mapScale,const std::vector<std::string> &features )
{
	bool		status=false;

	if(view == NULL)			throw "Invalid null view pointer";
	else if(theme == NULL)		throw "Invalid null theme pointer";
	else if(canvas == NULL)		throw "Invalid null canvas pointer";
	else if(visual == NULL)		throw "Invalid null visual pointer";

	if(validScale(view->projection(),(TeAbstractTheme*)theme,canvas,mapScale) == true)	status=drawSelectedFeaturesFromTheme(theme,view->projection(),canvas,visual, features);
	return status;
}


bool TdkGraphicViewService::drawSelectedFeaturesFromTheme(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas, TeVisual *visual, const std::vector<std::string> &features)
{
	if(theme == NULL)		throw "Invalid null theme pointer";
	else if(canvas == NULL)		throw "Invalid null canvas pointer";
	else if(visual == NULL)		throw "Invalid null visual pointer";

	if(features.empty() == true) return false;

	if( (theme->visibleRep() & TePOLYGONS))		return drawThemePolygonsForSelectOperation(theme,outProj,canvas,visual,features);
	if((theme->visibleRep() & TeLINES))			return drawThemeLinesForSelectOperation(theme,outProj,canvas,visual,features);
	if((theme->visibleRep() & TePOINTS))		return drawThemePointsForSelectOperation(theme,outProj,canvas,visual,features);
	/*if((theme->visibleRep() & TeTEXT))			drawThemeTexts(theme,outProj,canvas);
	*/
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Draw a terralib theme
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawTheme(TeAbstractTheme *theme,TeProjection *outProj, TdkAbstractCanvasDraw *canvas)
{
	_lastLegend=InvalidLegend;
	if(theme->visibility() !=1) return false;
	if((theme->visibleRep() & TeRASTER))		drawThemeRasters(theme,outProj,canvas);
	if( (theme->visibleRep() & TePOLYGONS))		drawThemePolygons(theme,outProj,canvas);
	if((theme->visibleRep() & TeLINES))			drawThemeLines(theme,outProj,canvas);
	if((theme->visibleRep() & TeTEXT))			drawThemeTexts(theme,outProj,canvas);
	if((theme->visibleRep() & TePOINTS))		drawThemePoints(theme,outProj,canvas);
	
	
	return false;
}


///////////////////////////////////////////////////////////////////////////////
//Check whether theme scale is valid
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::validScale(TeProjection *viewProj, TeAbstractTheme* theme,TdkAbstractCanvasDraw *canvas,const double &mapScale)
{
	double	scale;
	if( (viewProj == 0) || (theme == 0) || (canvas == 0) ) throw "Invalid null pointer";
	if(mapScale == 0.0)		scale=canvas->getScale(viewProj);
	else					scale=mapScale;

	if(theme->minScale() == theme->maxScale()) return true;
	if((theme->minScale()<=scale) && (theme->maxScale()>=scale)) return true;
	return false;
}


///////////////////////////////////////////////////////////////////////////////
//drawThemeRasters
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemeRasters(TeAbstractTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas)
{
	switch(theme->type())
	{
		case TeTHEME: return drawThemeRasters((TeTheme*)theme,outProj,canvas);
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//drawThemeRasters
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemeRasters(TeTheme* theme,TeProjection *outProj, TdkAbstractCanvasDraw* canvas)
{
	TeBox						viewport;
	TeRasterTransform*			transform;
	TeRaster*					raster;

	raster=theme->layer()->raster();
	if(raster==0) return false;
	transform=theme->rasterVisual();
	_rasterParams.fileName_ = raster->params().fileName_;
	
	canvas->getViewport(viewport); 

	if(fabs(viewport.height() * viewport.width()) < (ImageLimit * ImageLimit))
	{
		if (buildRaster(canvas))	fillDecoder(canvas, raster, transform); 
		canvas->drawRaster(_backRaster);
	}else
	{
		TeBox	window;
		int		ncols,nlines;

		canvas->getWindow(window);

		ncols  = (int)((window.width())/(raster->params().resx_) + 0.5);
		nlines = (int)((window.height())/(raster->params().resy_) + 0.5);
		if(abs(ncols*nlines)<(ImageLimit * ImageLimit))
		{
			_rasterParams.boundingBoxLinesColumns(window.x1(),window.y1(),window.x2(),window.y2(),nlines,ncols);
			if (buildRaster(canvas))	fillDecoder(canvas, raster, transform);
			canvas->drawRaster(_backRaster);
			return true;
		}
		drawRasterSlice(canvas,raster,transform,0,TeCoord2D(0,0));//rui
	}
	if(_events) _events->endProcessEvent();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//drawThemePolygons
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemePolygons(TeAbstractTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas)
{
	switch(theme->type())
	{
		case TeTHEME: 
						if( (theme->grouping().groupMode_ != TeNoGrouping) )	return drawThemePolygonsWithCollection((TeTheme*)theme,outProj,canvas);
						else													return drawThemePolygons((TeTheme*)theme,outProj,canvas);
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//drawThemePolygons
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemePolygons(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas)
{
	bool					sameProjection=false;
	bool					blFlag;
	TeBox					boxTheme;
	TeBox					boxWindow;
	TeDatabase				*database;
	TeDatabasePortal		*dbPortal;
	std::string				strWhere;
	std::string				strSQL;
	TdkProcessEvent			ev;
	std::string				generateWhere;
	std::string				tableName;

	if( (outProj == 0) || (theme == 0) || (canvas == 0) ) throw "Invalid null pointer";

	if(*outProj == *theme->layer()->projection()) sameProjection=true;

	boxTheme=theme->layer()->box();
	canvas->getWindow(boxWindow);
	if(!sameProjection)	
		changeProjection(theme->layer()->projection(),outProj,boxTheme);
	//if(!TeIntersection(boxTheme,boxWindow,boxTheme)) return false;
	if(!(database=theme->layer()->database()))		throw "Invalid null database pointer";
	if(!(dbPortal=database->getPortal()))			throw "Invalid null database portal";
	if(!sameProjection)
			changeProjection(outProj,theme->layer()->projection(),boxWindow);

	
	generateWhere = theme->attributeRest();
	TeTrim(generateWhere);
	
	strWhere=theme->layer()->database()->getSQLBoxWhere(boxWindow,TePOLYGONS,tableName);
	strSQL="select count(*) as Total from " + theme->layer()->tableName(TePOLYGONS);
	strSQL+=" where ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;

	if((dbPortal->query(strSQL) == true) && (dbPortal->fetchRow() == true))	ev._maxValue=(unsigned int)dbPortal->getInt("Total");
	dbPortal->freeResult();

	strSQL="select * from " + theme->layer()->tableName(TePOLYGONS);
	strSQL+=" where ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;
	
	if((dbPortal->query(strSQL,TeSERVERSIDE,TeUNIDIRECTIONAL,TeREADONLY,TeBINARYCURSOR) == true) && (dbPortal->fetchRow() == true))
	{
		setVisual(theme,canvas,TePOLYGONS);
		do
		{
			TePolygon	pol;
			blFlag=dbPortal->fetchGeometry(pol);
			if(!sameProjection) changeProjection(theme->layer()->projection(),outProj,pol);
			canvas->drawPolygonW(pol);
			if(_events)	
			{
				ev._value++;
				_events->processEvent(&ev);
				if(_stopProcess)
				{
					if(*_stopProcess) 
					{
						delete dbPortal;
						return true;
					}
				}
			}
		}while(blFlag == true);
	}
	dbPortal->freeResult();
	delete dbPortal;
	if(_events) _events->endProcessEvent();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Draw selected polygons
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

bool TdkGraphicViewService::drawThemePolygonsForSelectOperation(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas, TeVisual *visual, const std::vector<std::string> &feature)
{
	bool					sameProjection=false;
	bool					blFlag;
	TeBox					boxTheme;
	TeBox					boxWindow;
	TeDatabase				*database;
	TeDatabasePortal		*dbPortal;
	std::string				strWhere;
	std::string				strSQL;
	TdkProcessEvent			ev;
	std::string				generateWhere;
	std::string				whereToSelect;
	unsigned int			i;
	std::string				tableName;

	if( (outProj == 0) || (theme == 0) || (canvas == 0) ) throw "Invalid null pointer";

	if(*outProj == *theme->layer()->projection()) sameProjection=true;

	boxTheme=theme->layer()->box();
	canvas->getWindow(boxWindow);
	if(!sameProjection)	
		changeProjection(theme->layer()->projection(),outProj,boxTheme);
	if(!(database=theme->layer()->database()))		throw "Invalid null database pointer";
	if(!(dbPortal=database->getPortal()))			throw "Invalid null database portal";
	if(!sameProjection)
			changeProjection(outProj,theme->layer()->projection(),boxWindow);

	
	generateWhere = theme->attributeRest();
	TeTrim(generateWhere);

	for(i=0;i<feature.size();i++)
	{
		if(whereToSelect.empty() == false) whereToSelect+=",";
		whereToSelect+="'";
		whereToSelect+=feature[i];
		whereToSelect+="'";
	}
	
	strWhere=theme->layer()->database()->getSQLBoxWhere(boxWindow,TePOLYGONS,tableName);
	strSQL="select count(*) as Total from " + theme->layer()->tableName(TePOLYGONS);
	strSQL+=" where ";
	if(!whereToSelect.empty())  strSQL+="( object_id in (" + whereToSelect + ")) AND ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;

	if((dbPortal->query(strSQL) == true) && (dbPortal->fetchRow() == true))	ev._maxValue=(unsigned int)dbPortal->getInt("Total");
	dbPortal->freeResult();

	strSQL="select * from " + theme->layer()->tableName(TePOLYGONS);
	strSQL+=" where ";
	if(!whereToSelect.empty())  strSQL+="( object_id in (" + whereToSelect + ")) AND ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;
	
	if((dbPortal->query(strSQL,TeSERVERSIDE,TeUNIDIRECTIONAL,TeREADONLY,TeBINARYCURSOR) == true) && (dbPortal->fetchRow() == true))
	{
		setVisualForSelection(theme,canvas,TePOLYGONS,visual);
		do
		{
			TePolygon	pol;
			blFlag=dbPortal->fetchGeometry(pol);
			if(!sameProjection) changeProjection(theme->layer()->projection(),outProj,pol);
			canvas->drawPolygonW(pol);
			if(_events)	
			{
				ev._value++;
				_events->processEvent(&ev);
				if(_stopProcess)
				{
					if(*_stopProcess) 
					{
						delete dbPortal;
						return true;
					}
				}
			}
		}while(blFlag == true);
	}
	dbPortal->freeResult();
	delete dbPortal;
	if(_events) _events->endProcessEvent();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//drawThemePolygonsWithCollection
//Author : Rui Mauricio Gregório 
//Date : 07/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemePolygonsWithCollection(TeTheme* theme,TeProjection *outProj, TdkAbstractCanvasDraw* canvas)
{
	bool					sameProjection=false;
	bool					blFlag;
	TeBox					boxTheme;
	TeBox					boxWindow;
	TeDatabase				*database;
	TeDatabasePortal		*dbPortal;
	std::string				strWhere;
	std::string				strSQL;
	TdkProcessEvent			ev;
	int						legend_id;
	std::string				generateWhere;
	std::string				tableName;

	if( (outProj == 0) || (theme == 0) || (canvas == 0) ) throw "Invalid null pointer";

	if(*outProj == *theme->layer()->projection()) sameProjection=true;

	boxTheme=theme->layer()->box();
	canvas->getWindow(boxWindow);
	if(!sameProjection)	changeProjection(theme->layer()->projection(),outProj,boxTheme);
	if(!TeIntersection(boxTheme,boxWindow,boxTheme)) return false;
	if(!(database=theme->layer()->database()))		throw "Invalid null database pointer";
	if(!(dbPortal=database->getPortal()))			throw "Invalid null database portal";
	if(!sameProjection)
			changeProjection(outProj,theme->layer()->projection(),boxWindow);
	strWhere=theme->layer()->database()->getSQLBoxWhere(boxWindow,TePOLYGONS,tableName);

	generateWhere = theme->attributeRest();
	TeTrim(generateWhere);

	strSQL="select count(*) as Total from " + theme->layer()->tableName(TePOLYGONS);
	strSQL+=" where ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;

	if((dbPortal->query(strSQL,TeSERVERSIDE,TeUNIDIRECTIONAL,TeREADONLY,TeBINARYCURSOR) == true) && (dbPortal->fetchRow() == true))	ev._maxValue=(unsigned int)dbPortal->getInt("Total");
	dbPortal->freeResult();

	strSQL="select " + theme->layer()->tableName(TePOLYGONS) + ".*, c_legend_id from " + theme->layer()->tableName(TePOLYGONS);
	strSQL+="," + theme->collectionTable();
	strSQL+=" where object_id = c_object_id and ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;
	strSQL+=" order by c_legend_id, object_id asc, ext_max desc";

	if((dbPortal->query(strSQL,TeSERVERSIDE,TeUNIDIRECTIONAL,TeREADONLY,TeBINARYCURSOR) == true) && (dbPortal->fetchRow() == true))
	{
		do
		{
			TePolygon	pol;
			legend_id=dbPortal->getInt("c_legend_id");
			setCollectionVisual(theme,canvas,TePOLYGONS,legend_id);
			blFlag=dbPortal->fetchGeometry(pol);
			if(!sameProjection) changeProjection(theme->layer()->projection(),outProj,pol);
			canvas->drawPolygonW(pol);
			if(_events)	
			{
				ev._value++;
				_events->processEvent(&ev);
				if(_stopProcess)
				{
					if(*_stopProcess) 
					{
						delete dbPortal;
						return true;
					}
				}
			}
		}while(blFlag == true);
	}
	dbPortal->freeResult();
	delete dbPortal;
	if(_events) _events->endProcessEvent();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//drawThemeLines
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemeLines(TeAbstractTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas)
{
	switch(theme->type())
	{
		case TeTHEME: return drawThemeLines((TeTheme*)theme,outProj,canvas);
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//drawThemeLines
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemeLines(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas)
{
	bool					sameProjection=false;
	bool					blFlag;
	TeBox					boxTheme;
	TeBox					boxWindow;
	TeDatabase				*database;
	TeDatabasePortal		*dbPortal;
	std::string				strWhere;
	std::string				strSQL;
	TdkProcessEvent			ev;
	std::string				generateWhere;
	std::string				tableName;

	if( (outProj == 0) || (theme == 0) || (canvas == 0) ) throw "Invalid null pointer";

	if(*outProj == *theme->layer()->projection()) sameProjection=true;

	boxTheme=theme->layer()->box();
	canvas->getWindow(boxWindow);
	if(!sameProjection)	changeProjection(theme->layer()->projection(),outProj,boxTheme);
	if(!TeIntersection(boxTheme,boxWindow,boxTheme)) return false;
	if(!(database=theme->layer()->database()))		throw "Invalid null database pointer";
	if(!(dbPortal=database->getPortal()))			throw "Invalid null database portal";
	if(!sameProjection)
			changeProjection(outProj,theme->layer()->projection(),boxWindow);
	strWhere=theme->layer()->database()->getSQLBoxWhere(boxWindow,TeLINES,tableName);

	generateWhere = theme->attributeRest();
	TeTrim(generateWhere);

	strSQL="select count(*) as Total from " + theme->layer()->tableName(TeLINES);
	strSQL+=" where ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;

	if((dbPortal->query(strSQL) == true) && (dbPortal->fetchRow() == true))	ev._maxValue=(unsigned int)dbPortal->getInt("Total");
	dbPortal->freeResult();

	strSQL="select * from " + theme->layer()->tableName(TeLINES);
	strSQL+=" where ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;
	
	if((dbPortal->query(strSQL,TeSERVERSIDE,TeUNIDIRECTIONAL,TeREADONLY,TeBINARYCURSOR) == true) && (dbPortal->fetchRow() == true))
	{
		setVisual(theme,canvas,TeLINES);
		do
		{
			TeLine2D	lne;
			blFlag=dbPortal->fetchGeometry(lne);
			if(!sameProjection) changeProjection(theme->layer()->projection(),outProj,lne);
			canvas->drawLineW(lne);
			if(_events)	
			{
				ev._value++;
				_events->processEvent(&ev);
				if(_stopProcess) 
				{
					if(*_stopProcess)
					{
						delete dbPortal;
						return true;
					}
				}
			}
		}while(blFlag == true);
	}
	dbPortal->freeResult();
	delete dbPortal;
	if(_events) _events->endProcessEvent();
	return true;
}


///////////////////////////////////////////////////////////////////////////////
//Draw Selected Lines
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemeLinesForSelectOperation(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas,TeVisual *visual, const std::vector<std::string> &feature)
{
	bool					sameProjection=false;
	bool					blFlag;
	TeBox					boxTheme;
	TeBox					boxWindow;
	TeDatabase				*database;
	TeDatabasePortal		*dbPortal;
	std::string				strWhere;
	std::string				strSQL;
	TdkProcessEvent			ev;
	std::string				generateWhere;
	std::string				whereToSelect;
	unsigned int			i;
	std::string				tableName;

	if( (outProj == 0) || (theme == 0) || (canvas == 0) ) throw "Invalid null pointer";

	if(*outProj == *theme->layer()->projection()) sameProjection=true;

	boxTheme=theme->layer()->box();
	canvas->getWindow(boxWindow);
	if(!sameProjection)	changeProjection(theme->layer()->projection(),outProj,boxTheme);
	if(!TeIntersection(boxTheme,boxWindow,boxTheme)) return false;
	if(!(database=theme->layer()->database()))		throw "Invalid null database pointer";
	if(!(dbPortal=database->getPortal()))			throw "Invalid null database portal";
	if(!sameProjection)
			changeProjection(outProj,theme->layer()->projection(),boxWindow);
	strWhere=theme->layer()->database()->getSQLBoxWhere(boxWindow,TeLINES,tableName);

	generateWhere = theme->attributeRest();
	TeTrim(generateWhere);

	for(i=0;i<feature.size();i++)
	{
		if(whereToSelect.empty() == false) whereToSelect+=",";
		whereToSelect+="'";
		whereToSelect+=feature[i];
		whereToSelect+="'";
	}

	strSQL="select count(*) as Total from " + theme->layer()->tableName(TeLINES);
	strSQL+=" where ";
	if(!whereToSelect.empty())  strSQL+="( object_id in (" + whereToSelect + ")) AND ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;

	if((dbPortal->query(strSQL) == true) && (dbPortal->fetchRow() == true))	ev._maxValue=(unsigned int)dbPortal->getInt("Total");
	dbPortal->freeResult();

	strSQL="select * from " + theme->layer()->tableName(TeLINES);
	strSQL+=" where ";
	if(!whereToSelect.empty())  strSQL+="( object_id in (" + whereToSelect + ")) AND ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;
	
	if((dbPortal->query(strSQL,TeSERVERSIDE,TeUNIDIRECTIONAL,TeREADONLY,TeBINARYCURSOR) == true) && (dbPortal->fetchRow() == true))
	{
		setVisualForSelection(theme,canvas,TeLINES,visual);
		do
		{
			TeLine2D	lne;
			blFlag=dbPortal->fetchGeometry(lne);
			if(!sameProjection) changeProjection(theme->layer()->projection(),outProj,lne);
			canvas->drawLineW(lne);
			if(_events)	
			{
				ev._value++;
				_events->processEvent(&ev);
				if(_stopProcess) 
				{
					if(*_stopProcess)
					{
						delete dbPortal;
						return true;
					}
				}
			}
		}while(blFlag == true);
	}
	dbPortal->freeResult();
	delete dbPortal;
	if(_events) _events->endProcessEvent();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//drawThemeTexts
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemeTexts(TeAbstractTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas)
{
	switch(theme->type())
	{
		case TeTHEME: return drawThemeTexts((TeTheme*)theme,outProj,canvas);
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//drawThemeTexts
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemeTexts(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas)
{
	bool					sameProjection=false;
	bool					blFlag;
	TeBox					boxTheme;
	TeBox					boxWindow;
	TeDatabase				*database;
	TeDatabasePortal		*dbPortal;
	std::string				strWhere;
	std::string				strSQL;
	TdkProcessEvent			ev;
	std::string				generateWhere;
	std::string				tableName;

	if( (outProj == 0) || (theme == 0) || (canvas == 0) ) throw "Invalid null pointer";

	if(*outProj == *theme->layer()->projection()) sameProjection=true;

	boxTheme=theme->layer()->box();
	canvas->getWindow(boxWindow);
	if(!sameProjection)	changeProjection(theme->layer()->projection(),outProj,boxTheme);
	if(!TeIntersection(boxTheme,boxWindow,boxTheme)) return false;
	if(!(database=theme->layer()->database()))		throw "Invalid null database pointer";
	if(!(dbPortal=database->getPortal()))			throw "Invalid null database portal";
	if(!sameProjection)
			changeProjection(outProj,theme->layer()->projection(),boxWindow);
	strWhere=theme->layer()->database()->getSQLBoxWhere(boxWindow,TeTEXT,tableName);

	generateWhere = theme->attributeRest();
	TeTrim(generateWhere);

	strSQL="select count(*) as Total from " + theme->layer()->tableName(TeTEXT);
	strSQL+=" where ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;

	if((dbPortal->query(strSQL) == true) && (dbPortal->fetchRow() == true))	ev._maxValue=(unsigned int)dbPortal->getInt("Total");
	dbPortal->freeResult();

	strSQL="select * from " + theme->layer()->tableName(TeTEXT);
	strSQL+=" where ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;
	
	if((dbPortal->query(strSQL) == true) && (dbPortal->fetchRow() == true))
	{
		setVisual(theme,canvas,TeTEXT);
		do
		{
			TeText	txt;
			blFlag=dbPortal->fetchGeometry(txt);
			if(!sameProjection) 
			{
				TeCoord2D	localization = txt.location();
				changeProjection(theme->layer()->projection(),outProj,localization);
				txt.setLocation(localization);
			}
			canvas->setTextAngle(txt.angle()); 
			canvas->drawTextW(txt);
			if(_events)	
			{
				ev._value++;
				_events->processEvent(&ev);
				if(_stopProcess) 
				{
					if(*_stopProcess)
					{
						delete dbPortal;
						return true;
					}
				}
			}
		}while(blFlag == true);
	}
	dbPortal->freeResult();
	delete dbPortal;
	if(_events) _events->endProcessEvent();
	return true;

}

///////////////////////////////////////////////////////////////////////////////
//drawThemePoints (Abstract Theme)
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemePoints(TeAbstractTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas)
{
	switch(theme->type())
	{
		case TeTHEME: return drawThemePoints((TeTheme*)theme,outProj,canvas);
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//drawThemePoints (TeTheme)
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemePoints(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas)
{
	bool					sameProjection=false;
	bool					blFlag;
	TeBox					boxTheme;
	TeBox					boxWindow;
	TeDatabase				*database;
	TeDatabasePortal		*dbPortal;
	std::string				strWhere;
	std::string				strSQL;
	TdkProcessEvent			ev;
	std::string				generateWhere;
	std::string				tableName;

	if( (outProj == 0) || (theme == 0) || (canvas == 0) ) throw "Invalid null pointer";

	if(*outProj == *theme->layer()->projection()) sameProjection=true;

	boxTheme=theme->layer()->box();
	canvas->getWindow(boxWindow);
	if(!sameProjection)	changeProjection(theme->layer()->projection(),outProj,boxTheme);
	if(!TeIntersection(boxTheme,boxWindow,boxTheme)) return false;
	if(!(database=theme->layer()->database()))		throw "Invalid null database pointer";
	if(!(dbPortal=database->getPortal()))			throw "Invalid null database portal";
	if(!sameProjection)
			changeProjection(outProj,theme->layer()->projection(),boxWindow);
	strWhere=theme->layer()->database()->getSQLBoxWhere(boxWindow,TeTEXT,tableName);

	generateWhere = theme->attributeRest();
	TeTrim(generateWhere);

	strSQL="select count(*) as Total from " + theme->layer()->tableName(TePOINTS);
	strSQL+=" where ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;

	if((dbPortal->query(strSQL) == true) && (dbPortal->fetchRow() == true))	ev._maxValue=(unsigned int)dbPortal->getInt("Total");
	dbPortal->freeResult();

	strSQL="select * from " + theme->layer()->tableName(TePOINTS);
	strSQL+=" where ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;
	
	if((dbPortal->query(strSQL) == true) && (dbPortal->fetchRow() == true))
	{
		setVisual(theme,canvas,TePOINTS);
		do
		{
			TePoint	pto;
			blFlag=dbPortal->fetchGeometry(pto);
			if(!sameProjection) 
			{
				TeCoord2D	localization = pto.location();
				changeProjection(theme->layer()->projection(),outProj,localization);
				pto=TePoint(localization);
			}
			canvas->drawPointW(pto);
			if(_events)	
			{
				ev._value++;
				_events->processEvent(&ev);
				if(_stopProcess) 
				{
					if(*_stopProcess)
					{
						delete dbPortal;
						return true;
					}
				}
			}
		}while(blFlag == true);
	}
	dbPortal->freeResult();
	delete dbPortal;
	if(_events) _events->endProcessEvent();
	return true;
}


///////////////////////////////////////////////////////////////////////////////
//drawThemePoints (TeTheme)
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::drawThemePointsForSelectOperation(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas,TeVisual *visual, const std::vector<std::string> &feature)
{
	bool					sameProjection=false;
	bool					blFlag;
	TeBox					boxTheme;
	TeBox					boxWindow;
	TeDatabase				*database;
	TeDatabasePortal		*dbPortal;
	std::string				strWhere;
	std::string				strSQL;
	TdkProcessEvent			ev;
	std::string				generateWhere;
	std::string				whereToSelect;
	unsigned int			i;
	std::string				tableName;

	if( (outProj == 0) || (theme == 0) || (canvas == 0) ) throw "Invalid null pointer";

	if(*outProj == *theme->layer()->projection()) sameProjection=true;

	boxTheme=theme->layer()->box();
	canvas->getWindow(boxWindow);
	if(!sameProjection)	changeProjection(theme->layer()->projection(),outProj,boxTheme);
	if(!TeIntersection(boxTheme,boxWindow,boxTheme)) return false;
	if(!(database=theme->layer()->database()))		throw "Invalid null database pointer";
	if(!(dbPortal=database->getPortal()))			throw "Invalid null database portal";
	if(!sameProjection)
			changeProjection(outProj,theme->layer()->projection(),boxWindow);
	strWhere=theme->layer()->database()->getSQLBoxWhere(boxWindow,TeTEXT,tableName);

	generateWhere = theme->attributeRest();
	TeTrim(generateWhere);

	for(i=0;i<feature.size();i++)
	{
		if(whereToSelect.empty() == false) whereToSelect+=",";
		whereToSelect+="'";
		whereToSelect+=feature[i];
		whereToSelect+="'";
	}

	strSQL="select count(*) as Total from " + theme->layer()->tableName(TePOINTS);
	strSQL+=" where ";
	if(!whereToSelect.empty())  strSQL+="( object_id in (" + whereToSelect + ")) AND ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;

	if((dbPortal->query(strSQL) == true) && (dbPortal->fetchRow() == true))	ev._maxValue=(unsigned int)dbPortal->getInt("Total");
	dbPortal->freeResult();

	strSQL="select * from " + theme->layer()->tableName(TePOINTS);
	strSQL+=" where ";
	if(!whereToSelect.empty())  strSQL+="( object_id in (" + whereToSelect + ")) AND ";
	if(!generateWhere.empty())	strSQL+= "(" + generateWhere + ") AND ";
	strSQL+=strWhere;
	
	if((dbPortal->query(strSQL) == true) && (dbPortal->fetchRow() == true))
	{
		setVisualForSelection(theme,canvas,TePOINTS,visual);
		do
		{
			TePoint	pto;
			blFlag=dbPortal->fetchGeometry(pto);
			if(!sameProjection) 
			{
				TeCoord2D	localization = pto.location();
				changeProjection(theme->layer()->projection(),outProj,localization);
				pto=TePoint(localization);
			}
			canvas->drawPointW(pto);
			if(_events)	
			{
				ev._value++;
				_events->processEvent(&ev);
				if(_stopProcess) 
				{
					if(*_stopProcess)
					{
						delete dbPortal;
						return true;
					}
				}
			}
		}while(blFlag == true);
	}
	dbPortal->freeResult();
	delete dbPortal;
	if(_events) _events->endProcessEvent();
	return true;
}

void TdkGraphicViewService::setCollectionVisual(TeTheme *theme, TdkAbstractCanvasDraw *canvas, const TeGeomRep &rep, const int &legend_id)
{
	TeDatabasePortal	*dbPortal;
	std::string			strSQL;
	TeVisual			*visual=NULL;

	if(legend_id == _lastLegend) return;
	if(theme == NULL) return;
	if( (dbPortal=theme->layer()->database()->getPortal()) == NULL) return;
	strSQL="select * from te_visual where legend_id=" + Te2String(legend_id);
	if( (dbPortal->query(strSQL)==true) && (dbPortal->fetchRow() == true))
	{
		visual=new TeVisual(rep);
		dbPortal->getVisual(visual,(TeGeomRep)rep,0);
	}
	delete dbPortal;
	if(visual)
	{
		setVisual(theme,canvas,rep,visual);
		delete visual;
		_lastLegend=legend_id;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set visual
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGraphicViewService::setVisual(TeTheme *theme, TdkAbstractCanvasDraw *canvas, const TeGeomRep &rep,TeVisual *vis)
{
	TeVisual	*visual;
	TeColor		color;

	if(theme->visibleRep() & TePOLYGONS & rep)	
	{
		if(vis == NULL)		visual=theme->defaultLegend().visual(TePOLYGONS);
		else				visual=vis;

		color=visual->contourColor();
		canvas->setPolygonBorderColor(color.red_,color.green_,color.blue_);
		canvas->setPolygonBorderWidth(visual->contourWidth());
		canvas->setPolygonBorderType(visual->contourStyle());

		color=visual->color();
		canvas->setPolygonType((visual->style()<=7 ?  visual->style()- 2 : visual->style()));
		canvas->setPolygonColor(color.red_,color.green_,color.blue_,255 - ((255 * visual->transparency()))/100);
		
	}else if(theme->visibleRep() & TeLINES & rep)
	{
		visual=theme->defaultLegend().visual(TeLINES);
		if(vis != NULL)		color=vis->color();
		else				color=visual->color();
		canvas->setLineColor(color.red_,color.green_,color.blue_);
		canvas->setLineType(visual->style());
		canvas->setLineWidth(visual->width());
	}else if(theme->visibleRep() & TePOINTS & rep)
	{
		visual=theme->defaultLegend().visual(TePOINTS);
		if(vis != NULL)		color=vis->color();
		else				color=visual->color();
		
		canvas->setPointColor(color,255);
		canvas->setPointSize(visual->size());
		canvas->setPointType(visual->style());
	}else if(theme->visibleRep() & TeTEXT & rep)
	{
		visual=theme->defaultLegend().visual(TeTEXT);
		color=visual->color();
		canvas->setTextColor(color,255);
		canvas->setTextFont(visual->family());
		canvas->setTextSize(visual->size());
		canvas->setTextBold(visual->bold());
		canvas->setTextItalic(visual->italic());
		canvas->setTextAlign(1,1);
	}
}


///////////////////////////////////////////////////////////////////////////////
//Set visual for selection
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGraphicViewService::setVisualForSelection(TeTheme *theme, TdkAbstractCanvasDraw *canvas, const TeGeomRep &rep,TeVisual *vis)
{
	TeVisual	*visual;
	TeColor		color;

	if(theme->visibleRep() & TePOLYGONS & rep)	
	{
		visual=theme->defaultLegend().visual(TePOLYGONS);
		color=vis->contourColor();
		canvas->setPolygonBorderColor(color.red_,color.green_,color.blue_);
		canvas->setPolygonBorderWidth(visual->contourWidth());
		canvas->setPolygonBorderType(visual->contourStyle());

		color=vis->color();
		if(vis->transparency() != 100)	canvas->setPolygonType((visual->style()<=7 ?  visual->style()- 2 : visual->style()));
		else							canvas->setPolygonType(-2);
		canvas->setPolygonColor(color.red_,color.green_,color.blue_,255 - ((255 * vis->transparency()))/100);
		
	}else if(theme->visibleRep() & TeLINES & rep)
	{
		visual=theme->defaultLegend().visual(TeLINES);
		color=vis->color();
		canvas->setLineColor(color.red_,color.green_,color.blue_);
		canvas->setLineType(visual->style());
		canvas->setLineWidth(visual->width());
	}else if(theme->visibleRep() & TePOINTS & rep)
	{
		visual=theme->defaultLegend().visual(TePOINTS);
		color=vis->color();
		canvas->setPointColor(color,255);
		canvas->setPointSize(visual->size());
		canvas->setPointType(visual->style());
	}else if(theme->visibleRep() & TeTEXT & rep)
	{
		visual=theme->defaultLegend().visual(TeTEXT);
		color=vis->color();
		canvas->setTextColor(color,255);
		canvas->setTextFont(visual->family());
		canvas->setTextSize(visual->size());
		canvas->setTextBold(visual->bold());
		canvas->setTextItalic(visual->italic());
		canvas->setTextAlign(1,1);
	}
}

///////////////////////////////////////////////////////////////////////////////
//build raster
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGraphicViewService::buildRaster(TdkAbstractCanvasDraw* canvas) 
{
    if(canvas == NULL)
    {
        return false;
    }

    if (!_backRaster)
    {
		_rasterParams.mode_ = 'c';
		_rasterParams.useDummy_ = false;
		_rasterParams.setDummy(255);
		_backRaster = new TeRaster();
		canvas->setRasterDecoder(_backRaster, _rasterParams);
		
		if(!_backRaster->init())
		{
			return false;
		}
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
//Fill terralib decoder
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGraphicViewService::fillDecoder(TdkAbstractCanvasDraw* canvas, TeRaster* raster, TeRasterTransform* transf )
{
    // Calculates the box of input image that intersects the box of the canvas
    TeBox bboxBackRaster = _backRaster->params().boundingBox();		

    TeBox bboxSearched = TeRemapBox( bboxBackRaster, 
        _backRaster->projection(), 
        raster->projection());

    TeBox bboxIntersection;

    if (!TeIntersection (raster->params().boundingBox(),
            bboxSearched, bboxIntersection))
    {
        return ; // no intersection 
    }

    // Create a remapping tool to back raster
    TeRasterRemap remap;
    if (transf)
    {
        remap.setTransformer(transf);

		canvas->setRasterTransparency(_backRaster->decoder(), transf->getTransparency());
    }

    remap.setOutput(_backRaster);
    _backRaster->params().status_ = TeRasterParams::TeReadyToWrite;

    // Calculates best resolution level to display the input image on this canvas
	TeBox temp_box;
	canvas->getWindow(temp_box);
    int res = raster->decoder()->bestResolution(temp_box, 
        _rasterParams.ncols_, _rasterParams.nlines_,
        _rasterParams.projection());
	
	// Check if raster blocks in best level of resolution that 
    // intersects the canvas box
    TeRasterParams parBlock;

    //lineColor_  = CD_RED;

    if (raster->selectBlocks(bboxIntersection,res,parBlock))        
    {
        processBlocks(raster, parBlock, remap, bboxIntersection, res); //rui
    }
    else		// no blocks found try to remap the whole raster
    {
        remap.setInput(raster);
        remap.apply(true);
    }
}

///////////////////////////////////////////////////////////////////////////////
//Process raster select blocks
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGraphicViewService::processBlocks(TeRaster* raster, const TeRasterParams& parBlock,
                                TeRasterRemap& remap, TeBox& bboxIntersection,
                                const int& res)
{
  //  _rasterParams.resolution_ = res;	

    // Process each block as an independent raster decoded in memory
    TeRaster* block = new TeRaster;
    TeDecoderMemory* decMem = new TeDecoderMemory(parBlock);
    decMem->init();

	remap.setInput(block);

	int count = 0;

    // Portal of raster block selection behaves as portal of geometries
    // use the "bool flag - do - while" scheme
    bool flag = true;
	TdkProcessEvent			ev;
	ev._maxValue=(unsigned int)raster->numberOfSelectedBlocks()/3;
    do
    {
        flag = raster->fetchRasterBlock(decMem);
        block->setDecoder(decMem);
        remap.apply();
		++count;
		ev._value=count;
		if(_events)	_events->processEvent(&ev);
		if(_stopProcess)
		{
			if(*_stopProcess)
				break;
		}

    } while (flag);

    decMem->clear();
    delete block;
    raster->clearBlockSelection();
}

///////////////////////////////////////////////////////////////////////////////
//draw raster in slice process
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGraphicViewService::drawRasterSlice(TdkAbstractCanvasDraw* canvas, TeRaster* raster, 
                                            TeRasterTransform* transform, const double& angle, 
											const TeCoord2D& rotatePoint)
{
	int			ncols,nlines;
	int			cont;
	TeBox		viewport;
	TeBox		window;
	double		height;
	double		py;
	double		resX,resY;
	double		resolutionX,resolutionY;
	double		w,h,h1;

	
	canvas->getWindow(window);
	canvas->getViewport(viewport);

	resX=raster->params().resx_;
	resY=raster->params().resy_;

	resolutionX=window.width()/viewport.width();
	resolutionY=window.height()/viewport.height();

	if(resolutionX>resX || resolutionY>resY)
	{
		resX=resolutionX;
		resY=resolutionY;
	}

	ncols  = (int)((window.width())/resX + 0.5);
	nlines = (int)((window.height())/resY + 0.5);

	canvas->viewport2Window(0,SliceValue,w,h1);
	canvas->viewport2Window(0,0,w,h);

	height=fabs(h1-h);
	for(py=window.y1(),cont=1;py<=window.y2();py+=height,cont++)
	{
		TeBox win;
		
		canvas->setWindow(window.x1(),py,window.x2(),py + height);
		canvas->setViewport(viewport.x1(),viewport.y1() - ((cont+1) * SliceValue),viewport.x2(),viewport.y1() - ((cont)*SliceValue));
		canvas->getWindow(win);
		_rasterParams.boundingBoxLinesColumns(win.x1(),win.y1(),win.x2(),win.y2(),SliceValue,ncols);
		if (buildRaster(canvas))	fillDecoder(canvas, raster, transform);
		TeBox bboxBackRaster = _backRaster->params().boundingBox();		
		TeBox bboxSearched = TeRemapBox( bboxBackRaster,   _backRaster->projection(),  raster->projection());
		TeBox bboxIntersection;
		if (TeIntersection (raster->params().boundingBox(), bboxSearched, bboxIntersection))	canvas->drawRaster(_backRaster);
		this->resetBackRaster();
		if(cont >=3 )
			break;
	}
	canvas->setWindow(window);
	canvas->setViewport(viewport);
}

///////////////////////////////////////////////////////////////////////////////
//resetBackRaster
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGraphicViewService::resetBackRaster()
{
    if(_backRaster != NULL)
    {
        delete _backRaster;
    }

    _backRaster = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//SetWorldRasterParams
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGraphicViewService::setWorldRasterParams(TeProjection* proj, TdkAbstractCanvasDraw* canvas)
{
	double llx,lly,urx,ury;
	double w,h;


    if(canvas == NULL)
    {
        return;
    }

    TeRasterParams rparams;
    rparams.nBands(3);
    TeBox window;

    canvas->getWindow(window);
    
    canvas->getViewport(llx,lly,urx,ury);

	w=fabs(urx-llx);
	h=fabs(ury-lly);

    rparams.boundingBoxLinesColumns(window.x1(), window.y1(), window.x2(), window.y2(), TeRound(h), TeRound(w));

    rparams.projection(proj);
    rparams.mode_ = 'w';
    rparams.decoderIdentifier_ = "";

    _rasterParams=rparams;
}