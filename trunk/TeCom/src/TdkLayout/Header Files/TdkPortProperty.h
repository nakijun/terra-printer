/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkPortProperty.h
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

#ifndef __TDK_PORT_PROPERTY_H
#define __TDK_PORT_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkPortProperty
/*! Class to represent the port property
*/

class TdkPortProperty : public TdkAbstractProperty
{
protected :

	std::string		_port;

public :
			//! Constructor
			TdkPortProperty();

			//! Destructor
			~TdkPortProperty();

			//! \brief setValue
			/*! Method to set the new value to
				port property
				\param		newVal		new host value
			*/
			virtual void setValue(const std::string &newVal);

			//! \brief getValue
			/*! Method to return the port value
				\return		returns the string value
			*/
			virtual std::string getValue();

			//! \brief getValue
			/*! Method to return the port value
				by reference
			*/
			virtual void getValue(std::string &value);

			//! \brief operator
			/*! Operator = overload
				\param		other		other TdkPortProperty object
				\return		returns the object with same values that old object
			*/
			TdkPortProperty& operator=(const TdkPortProperty &other);

			//! \brief operator
			/*! Operator = overload
				\param		other		other TdkAbstractProperty object
				\return		returns the object with same values that old object
			*/
			TdkPortProperty& operator=(const TdkAbstractProperty &other);
};

#endif