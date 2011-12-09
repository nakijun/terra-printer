/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkScaleUnitProperty.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/08/23 13:21:19 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_NORTH_TYPE_PROPERTY_H
#define __TDK_NORTH_TYPE_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkNorthTypeProperty
/*! Class to manipulate the north type property of object
*/
class TdkNorthTypeProperty : public TdkAbstractProperty
{
protected :
	std::string		_northFileName;
	std::string		_northPathFileName;
public :

	//! \brief TdkScaleUnitProperty
	/*! Constructor
		\param		newVal		new width value
	*/
	TdkNorthTypeProperty(const std::string &pathFileName, const std::string &newVal="North01");

	//! \brief Destructor
	virtual ~TdkNorthTypeProperty();

	//! \brief setValue
	/*! Method to set the new value
		to width property
		\param	newVal		new width value
	*/
	virtual void setValue(const std::string &newVal);

	//! \brief getValue
	/*! Method to returns the north value
		\return returns the string with the north name
	*/
	std::string getValue();

	//! \brief getValue
	/*! Method to returns the north value
	*/
	virtual void getValue(std::string &value);

	//! \brief getFullValue
	/*! Method to return the full value to north filename,
		it's include the path more filename
	*/	
	std::string getFullValue();
	
	//! \brief getValue
	/*! Method to return the width value
		\return returns th width value of object
	*/
	//virtual Unit getValue();

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkScaleUnitProperty object
		\return		returns the object with same values that old object
	*/
	TdkNorthTypeProperty& operator=(const TdkNorthTypeProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	//TdkNorthTypeProperty& operator=(const TdkNorthTypeProperty &other);
};


#endif
