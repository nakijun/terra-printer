/******************************************************************************
* FUNCATE - GIS development team
* 
* @(#) TdkConvertLayerToOdLayer.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/03/22 12:13:07 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_CONVERT_LAYER_TO_OD_LAYER_H
#define __TDK_CONVERT_LAYER_TO_OD_LAYER_H

#include <iostream>
#include <TeVisual.h>

class TeDatabase;
class TeLayer;
class TeOdaExport;
class TdkAbstractProcessEvent;
class TdkGeometrySettings;

using namespace std;


//! \class TdkConvertLayerToOdLayer
/*! Method to conver a terralib layer to Od layer
*/
class TdkConvertLayerToOdLayer
{
public :
	bool*						_cancel;		//!< cancel operation
protected:
	TeLayer*					_layer;			//!< layer pointer to export
	TeOdaExport*				_odExport;		//!< Od export pointer
	TeDatabase*					_database;		//!< database pointer
	TdkAbstractProcessEvent*	_process;		//!< Process status
	unsigned int				_iProcess;		//!< current process
	unsigned int				_maxProcess;	//!< maximum process value
protected:
	
	//! \brief getLayer
	/*! Method to return the terralib layer pointer
		when necessary the layer is loaded
		\param		layerName		layer name
		\return		returns the layer pointer
	*/
	virtual TeLayer*	getLayer(const std::string &layerName);

	//! \brief convertPolygons
	/*! Method to convert all polygons from layer to od entity
		\param		layer		terralib layer pointer
		\param		color		color's layer
		\return		returns true whether sucess
	*/
	virtual bool convertPolygons(TeLayer * layer,const TeColor &tcolor, \
								 const std::string &restriction="", TdkGeometrySettings *settings=NULL);

	//! \brief convertLines
	/*! Method to convert the all lines from layer to od entity
		\param		layer		terralib layer pointer
		\param		color		color's layer
		\return		returns true whether sucess
	*/
	virtual bool convertLines(TeLayer * layer, const TeColor &tcolor, const std::string &restriction="", \
							  TdkGeometrySettings *settings=NULL);

	virtual bool convertTexts(TeLayer * layer, const TeColor &tcolor, const std::string &restriction="", \
							  TdkGeometrySettings *settings=NULL);

	//! \brief getTotalItems
	/*! Method to return the total items to export
		\param		table name
		\return		returns the total items fromt table
	*/
	virtual unsigned int getTotalItems(const std::string &tableName,const std::string &restriction="");

	//! \brief getTotalItemsfromLayer
	/*! Method to return to total items from layer
		\param		layer		layer pointer
		\param		rep			representation to export
		\return		returns the total items from layer
	*/
	virtual unsigned int getTotalItemsfromLayer(TeLayer *layer, const short &rep, const std::string &restriction="");

public:

	//! \brief Constructor
	TdkConvertLayerToOdLayer(TeOdaExport *odExport, TeDatabase *database, TdkAbstractProcessEvent *process=NULL);

	//! \brief Destructor
	virtual ~TdkConvertLayerToOdLayer();

	//! \brief convert
	/*! Method to convert the terralib layer to Od layer
		\param		layerName		layer name
		\param		rep				representation to export
		\param		color			color's layer
		\return		returns true whether sucess
	*/
	virtual bool convert(const std::string &layerName, const short &rep, const std::string &restriction="", \
						 const TeColor &color=TeColor(255,0,0), TdkGeometrySettings* settings=NULL); 

};

#endif

