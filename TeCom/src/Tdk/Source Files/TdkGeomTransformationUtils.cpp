//TDK include files
#include <TdkGeomTransformationUtils.h>

//TerraLib include files
#include <TeGeometryAlgorithms.h>

void TdkRotate(const TeCoord2D &coordControl, const TeCoord2D &coordToRotate, const double &angle, TeCoord2D &coordOut)
{
	double		alfa;
	double		dx,dy;
	double		xr,yr;
	double		x,y;
		
	alfa=(4.*atan(1.)*angle)/180.;
	
	dx=coordControl.x();
	dy=coordControl.y();
	
	x=coordToRotate.x() - dx;
	y=coordToRotate.y() - dy;

	xr=x*cos(alfa) - y * sin(alfa);
	yr=x*sin(alfa) + y * cos(alfa);

	coordOut.x(xr+dx);
	coordOut.y(yr+dy);
}


void TdkAdjustCoordinate(const TeCoord2D &P0, const TeCoord2D &P1,const double &distance, TeCoord2D &P0out, TeCoord2D &P1out)
{
	
	double		vL_norm1;
	double		vL_norm2;

	if( P0 == P1 )
	{
		return;
	}
	
	TeCoord2D vL1( (P1.x() - P0.x()), (P1.y() - P0.y()) );
	TeCoord2D vL2( -1 * (P1.x() - P0.x()), -1 * (P1.y() - P0.y()) );
	vL_norm1 = sqrt( vL1.x() * vL1.x() + vL1.y() * vL1.y() );
	vL_norm2 = sqrt( vL2.x() * vL2.x() + vL2.y() * vL2.y() );

	TeCoord2D uL1( ( vL1.x() / vL_norm1 ), ( vL1.y() / vL_norm1 ) );
	TeCoord2D uL2( ( vL2.x() / vL_norm2 ), ( vL2.y() / vL_norm2 ) );
	TeCoord2D pEnd1 (P0.x() + uL1.x() * distance, P0.y() + uL1.y() * distance);
	TeCoord2D pEnd2 (P0.x() + uL2.x() * distance, P0.y() + uL2.y() * distance);

	if ( TeDistance(pEnd1, P1) <= TeDistance(pEnd2, P1) )
	{
		P0out = P0;
		P1out = pEnd1; 
	}
	else
	{
		P0out = P0;
		P1out = pEnd2;
	}
}

void TdkRecalculateBox(TeBox& box, const double& wMM, TeProjection* usedProjection, 
                       const double& newScale, const double& scaleApx)
{
	double wT = wMM;

    if(usedProjection)
	{
		string unit = usedProjection->units();
		if(unit == "Meters")
			wT = wMM / 1000.;
		else if(unit == "Kilometers")
			wT = wMM / 1000000.;
		else if(unit == "Centimeters")
			wT = wMM / 100.;
		else if(unit == "Millimeters")
			wT = wMM;
		else if(unit == "Feet")
			wT = wMM / (12. * 25.4);
		else if(unit == "Inches")
			wT = wMM / 25.4;
		else if(unit == "DecimalDegrees")
			wT = wMM / 110000000.;
	}

	double ff = newScale / scaleApx;
	double xmin, ymin, xmax, ymax;
	if(ff < 1)
	{
		double dx = (box.width() - (box.width() * ff)) / 2.;
		double dy = (box.height() - (box.height() * ff)) / 2.;
        xmin = box.x1() + dx;
		ymin = box.y1() + dy;
		xmax = box.x2() - dx;
		ymax = box.y2() - dy;
	}
	else
	{
		double dx = ((box.width() * ff) - box.width()) / 2.;
		double dy = ((box.height() * ff) - box.height()) / 2.;
		xmin = box.x1() - dx;
		ymin = box.y1() - dy;
		xmax = box.x2() + dx;
		ymax = box.y2() + dy;
	}

    box = TeBox(xmin, ymin, xmax, ymax);
}

TeCoord2D TdkTranslate(const TeCoord2D& crdInput, const double &dx, const double &dy)
{
	return TeCoord2D(crdInput.x() - dx, crdInput.y() - dy);
}

TeLine2D TdkTranslate(const TeLine2D& lneInput, const double &dx, const double &dy)
{
	TeLine2D		lneTranslated;
	unsigned int	i;

	for(i=0;i<lneInput.size();i++)
	{
		lneTranslated.add(TeCoord2D(lneInput[i].x() - dx, lneInput[i].y() - dy));
	}
	lneTranslated.geomId(lneInput.geomId());
	lneTranslated.objectId(lneInput.objectId());
	return lneTranslated;
}

TePolygon TdkTranslate(const TePolygon& polInput, const double &dx, const double &dy)
{
	TePolygon		polTranslated;
	unsigned int	i;

	for(i=0;i<polInput.size();i++)
	{
		TeLine2D	lneNew;
		lneNew=TdkTranslate(polInput[i],dx,dy);
		polTranslated.add(lneNew);
	}
	polTranslated.geomId(polInput.geomId());
	polTranslated.objectId(polInput.objectId());
	return polTranslated;

}

double TdkAngle(const TeCoord2D &coord1, const TeCoord2D &coord2)
{
	double distance = TeDistance (coord1,coord2); 
	if(distance == 0)
		return 0;

	double ang = 0;

	if ((coord2.x() > coord1.x()) && (coord1.y() <= coord2.y()))  // Primeiro quadrante
		ang = ang += acos ((coord2.x() - coord1.x())/distance) + (0*  (4.0 * atan(1.)) / 180.0);
 
	if ((coord2.x() <=coord1.x()) && (coord1.y() < coord2.y()))  // Segundo  quadrante
		ang = ang += asin ((coord1.x() - coord2.x())/distance) + (90* (4.0 * atan(1.)) / 180.0);

	if ((coord2.x() < coord1.x()) && (coord1.y() >= coord2.y()))  // Terceiro quadrante
		ang = ang += acos ((coord1.x() - coord2.x())/distance) + (180*(4.0 * atan(1.)) / 180.0);

	if ((coord2.x() >= coord1.x()) && (coord1.y() > coord2.y()))  // Quarto   quadrante
		ang = ang += asin ((coord2.x() - coord1.x())/distance) + (270* (4.0 * atan(1.)) / 180.0);

	return (ang * 180. / (4. * atan(1.0)));
}


void TdkRotate(TeLine2D& lneInOut, const TeCoord2D &coordControl,const double& angle)
{
	TeLine2D			lneAux;
	unsigned int		i;


	for(i=0;i<lneInOut.size();i++)
	{
		TeCoord2D	coordOut;
		TdkRotate(coordControl,lneInOut[i],angle,coordOut);
		lneAux.add(coordOut);
	}
	lneAux.geomId(lneInOut.geomId());
	lneAux.objectId(lneInOut.objectId());
	lneInOut.clear();
	lneInOut.copyElements(lneAux);
}

void TdkRotate(TePolygon& polInOut, const TeCoord2D &coordControl, const double& angle)
{
	TePolygon		polAux;
	unsigned int	i;

	polAux.geomId(polInOut.geomId());
	polAux.objectId(polInOut.objectId());

	for(i=0;i<polInOut.size();i++)
	{
		TeLine2D	lneAux;
		lneAux.copyElements(polInOut[i]);
		TdkRotate(lneAux,coordControl,angle);
		polAux.add(lneAux);
	}
	polInOut.clear();
	polInOut.copyElements(polAux);
}
