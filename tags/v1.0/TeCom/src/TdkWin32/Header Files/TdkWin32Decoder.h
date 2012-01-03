#ifndef __TDK_WIN32_DECODER_H
#define __TDK_WIN32_DECODER_H

#include <oaidl.h>

class TdkAbstractProperty;

class TdkWin32Decoder
{
protected:
	static double	getAsDoubleValue(VARIANT pVal);
public :

	TdkWin32Decoder();

	virtual ~TdkWin32Decoder();

	static bool decoder(TdkAbstractProperty *prop, VARIANT *pVal);

	static bool encoder(TdkAbstractProperty *prop, VARIANT pVal);
};


#endif
