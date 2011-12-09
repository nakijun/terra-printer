/** \file TdkPrimitiveCoord.h
  * This file contains XXXXXX.
  */

#ifndef  __TDK_INTERNAL_PRIMITIVECOORD_H
#define  __TDK_INTERNAL_PRIMITIVECOORD_H

#include <tdk.h>

//! Defines the TdkPrimitiveCoord class.
/*!
@ingroup graphics
*/

/** \struct TdkPrimitiveCoord
  * \brief A primitive type for drawing porpouses.
  *
  *
  * A class that defines primitive coordinates to be used by generic canvas.
  *
  * \sa TdkCanvas
  */
struct TDK_API TdkPrimitiveCoord
{
	double x_;	//!< x coordinate value
	double y_;	//!< y coordinate value
};

#endif	// __TDK_INTERNAL_PRIMITIVECOORD_H

