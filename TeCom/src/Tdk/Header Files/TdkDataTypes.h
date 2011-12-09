#ifndef __TDK_DATA_TYPES_H
#define __TDK_DATA_TYPES_H

namespace TDK_Connection
{
	typedef enum enConnectionType
	{	
		Access			= 0,
		SqlServer		= 1,
		Oracle			= 2,
		FireBird		= 3,
		PostgreSQL		= 4
	}connType;
}

#endif

