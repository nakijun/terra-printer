/************************************************************************************
TerraLib - a library for developing GIS applications.
Copyright � 2001-2007 INPE and Tecgraf/PUC-Rio.

This code is part of the TerraLib library.
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

You should have received a copy of the GNU Lesser General Public
License along with this library.

The authors reassure the license terms regarding the warranties.
They specifically disclaim any warranties, including, but not limited to,
the implied warranties of merchantability and fitness for a particular purpose.
The library provided hereunder is on an "as is" basis, and the authors have no
obligation to provide maintenance, support, updates, enhancements, or modifications.
In no event shall INPE and Tecgraf / PUC-Rio be held liable to any party for direct,
indirect, special, incidental, or consequential damages arising out of the use
of this library and its documentation.
*************************************************************************************/

#include "TeDatabaseFactoryParams.h"


TeDatabaseFactoryParams::TeDatabaseFactoryParams()
{
  dbms_name_ = "";
  host_ = "";
  user_ = "";
  password_ = "";
  database_ = "";
  port_ = 0;
}


TeDatabaseFactoryParams::~TeDatabaseFactoryParams()
{
}


bool TeDatabaseFactoryParams::operator==( 
  const TeDatabaseFactoryParams& external ) const
{
  if( ( dbms_name_ == external.dbms_name_ ) &&
      ( host_ == external.host_ ) &&
      ( user_ == external.user_ ) &&
      ( password_ == external.password_ ) &&
      ( database_ == external.database_ ) &&
      ( port_ == external.port_ ) ) {
  
    return true;
  } else {
    return false;
  }
}


const TeDatabaseFactoryParams& TeDatabaseFactoryParams::operator=( 
  const TeDatabaseFactoryParams& external )
{
  dbms_name_ = external.dbms_name_;
  host_ = external.host_;
  user_ = external.user_;
  password_ = external.password_;
  database_ = external.database_;
  port_ = external.port_;
  
  return external;
}


std::string TeDatabaseFactoryParams::decName() const
{
  return dbms_name_;
}
