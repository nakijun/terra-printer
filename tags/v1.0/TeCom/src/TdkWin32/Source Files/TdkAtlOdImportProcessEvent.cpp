
#include <atlbase.h>
#include <atlctl.h>
#include <TdkAtlProcessEvent.h>
#include <TdkAtlOdImportProcessEvent.h>
#include <TeLayer.h>
#include <TeDatabase.h>
#include <OdImport.h>



TdkAtlOdImportProcessEvent::TdkAtlOdImportProcessEvent(COdImport *ev)
{
	_event=ev;
}

TdkAtlOdImportProcessEvent::~TdkAtlOdImportProcessEvent()
{

}

void TdkAtlOdImportProcessEvent::processStatusEvent(const long &maxValue, const long &currentValue)
{
	if(_event) _event->Fire_processEvent(maxValue,currentValue);
}