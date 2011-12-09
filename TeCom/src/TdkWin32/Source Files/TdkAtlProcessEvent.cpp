#include <atlbase.h>
#include <atlctl.h>
#include <TdkAtlProcessEvent.h>
#include <OdExport.h>


TdkAtlProcessEvent::TdkAtlProcessEvent(COdExport *ev)
{
	_event=ev;
}

TdkAtlProcessEvent::~TdkAtlProcessEvent()
{

}

void TdkAtlProcessEvent::processStatusEvent(const long &maxValue, const long &currentValue)
{
	if(_event) _event->Fire_processEvent(maxValue,currentValue);
}

void TdkAtlProcessEvent::buildingGeometryEvent(const short &representation, const long &geom_id, const std::string &object_id)
{
	if(_event)
	{
		CComBSTR ret;
		ret = object_id.c_str();
		_event->Fire_buildingGeometry(representation,geom_id,ret);
	}
}