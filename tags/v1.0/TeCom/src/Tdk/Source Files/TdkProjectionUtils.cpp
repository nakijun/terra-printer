//TDK include files
#include <TdkProjectionUtils.h>
#include <TdkException.h>

//TerraLib include files
#include <TeGeometry.h>
#include <TeDatabase.h>
#include <TeVectorRemap.h>


TeBox tetrahedronBBox(const TeCoord2D& pt0, const TeCoord2D& pt1, 
                const TeCoord2D& pt2, const TeCoord2D& pt3)
{
  double xmin, ymin, xmax, ymax;

  if (pt0.x() < pt1.x())
  {
    if (pt2.x() < pt3.x())
    {
      xmin = MIN(pt0.x(), pt2.x());
      xmax = MAX(pt1.x(), pt3.x());
    }else
    {
      xmin = MIN(pt0.x(), pt3.x());
      xmax = MAX(pt1.x(), pt2.x());
    }
  }else
  {
    if (pt2.x() < pt3.x())
    {
      xmin = MIN(pt1.x(), pt2.x());
      xmax = MAX(pt0.x(), pt3.x());
    }else
    {
      xmin = MIN(pt1.x(), pt3.x());
      xmax = MAX(pt0.x(), pt2.x());
    }
  }

  if (pt0.y() < pt1.y())
  {
    if (pt2.y() < pt3.y())
    {
      ymin = MIN(pt0.y(), pt2.y());
      ymax = MAX(pt1.y(), pt3.y());
    }else
    {
      ymin = MIN(pt0.y(), pt3.y());
      ymax = MAX(pt1.y(), pt2.y());
    }
  }else
  {
    if (pt2.y() < pt3.y())
    {
      ymin = MIN(pt1.y(), pt2.y());
      ymax = MAX(pt0.y(), pt3.y());
    }else
    {
      ymin = MIN(pt1.y(), pt3.y());
      ymax = MAX(pt0.y(), pt2.y());
    }
  }

  return TeBox(xmin, ymin, xmax, ymax);
}

void changeProjection(TeProjection* fromProj, TeProjection* toProj, TeBox& box)
{
  if (fromProj == NULL || toProj == NULL)
  {
      return;
  }

  if (*fromProj == *toProj)
  {
      return;
  }

  box = TeRemapBox(box, fromProj, toProj);

  box = tetrahedronBBox(box.lowerLeft(), TeCoord2D(box.x2(), box.y1()), 
	  box.upperRight(), TeCoord2D(box.x1(), box.y2()));
}

void changeProjection(TeProjection* fromProj, TeProjection* toProj, 
                                                  TeCoord2D& coord)
{
    if (!(fromProj == NULL || toProj == NULL))
    {
        TeCoord2D c = coord;
        fromProj->setDestinationProjection(toProj);
        c = fromProj->PC2LL(c);
        c = toProj->LL2PC(c);
        
        coord.x_ = c.x();
        coord.y_ = c.y();
    }
}

void changeProjection(TeProjection* fromProj, TeProjection* toProj, 
                                                  TePoint& point)
{
    if (!(fromProj == NULL || toProj == NULL))
    {
        TeCoord2D c = point.location();
        fromProj->setDestinationProjection(toProj);
        c = fromProj->PC2LL(c);
        c = toProj->LL2PC(c);

        point.add(c);
    }
}

void changeProjection(TeProjection* fromProj, TeProjection* toProj, 
                                                  TePointSet& pointSet)
{
	TePointSet::iterator it;
	for(it = pointSet.begin(); it != pointSet.end(); ++it)
	{
		changeProjection(fromProj, toProj, (*it));
	}
	TeBox box = pointSet.box();
	changeProjection(fromProj, toProj, box);
	pointSet.setBox(box);
}

void changeProjection(TeProjection* fromProj, TeProjection* toProj, 
                                                  TeLine2D& line)
{
    TeLine2D::iterator it;

    for(it = line.begin(); it != line.end(); ++it)
    {
        changeProjection(fromProj, toProj, (*it));		
    }
	TeBox box = line.box();
	changeProjection(fromProj, toProj, box);
	line.setBox(box);
}

void changeProjection(TeProjection* fromProj, TeProjection* toProj, 
                                                  TeLineSet& lineSet)
{
	TeLineSet::iterator it;
	for(it = lineSet.begin(); it != lineSet.end(); ++it)
	{
		changeProjection(fromProj, toProj, (*it));		
	}
	TeBox box = lineSet.box();
	changeProjection(fromProj, toProj, box);
	lineSet.setBox(box);
}

void changeProjection(TeProjection* fromProj, TeProjection* toProj, 
                                                  TePolygon& poly)
{
    TePolygon::iterator it;

    for(it = poly.begin(); it != poly.end(); ++it)
    {
        changeProjection(fromProj, toProj, (*it));		
    }
	TeBox box = poly.box();
	changeProjection(fromProj, toProj, box);
	poly.setBox(box);
}

void changeProjection(TeProjection* fromProj, TeProjection* toProj, 
                                                  TePolygonSet& polygonSet)
{
	TePolygonSet::iterator it;
	for(it = polygonSet.begin(); it != polygonSet.end(); ++it)
	{
		changeProjection(fromProj, toProj, (*it));		
	}
	TeBox box = polygonSet.box();
	changeProjection(fromProj, toProj, box);
	polygonSet.setBox(box);
}

void changeLayerProjection(TeLayer& layer, TeProjection* toProj)
{
}

void changeViewProjection(TeView* view, TeProjection* newProjection, TeDatabase* db)
{
    if((view == NULL) || (newProjection == NULL))
    {
        return;
    }

    TeProjection* oldProj = view->projection();
    TeProjection* newProj = NULL;

    newProj = TeProjectionFactory::make(newProjection->params());
    
    TeBox viewBox = view->getCurrentBox();

    changeProjection(oldProj, newProj, viewBox);

    if((newProj != NULL) && (!(*oldProj == *newProj)))
    {
        int id = oldProj->id();
        delete oldProj;

        newProj->id(id);

        view->setCurrentBox(viewBox);
        view->projection(newProj);

        if((db != NULL) && !db->updateView(view))
        {
            throw TdkException("externalDBThemeWindow.cpp", -1, -1, 
                "Error trying update view bounding box.");
        }
    }
}

TeProjection* findProjection(TeViewNode* node)
{
	TeProjection* proj = NULL;

	if(node->type() == TeTREE)
	{
		TeViewTree* vtree = dynamic_cast<TeViewTree*>(node);
		std::vector<TeViewNode*>::iterator it;

		for(it = vtree->nodes().begin(); it != vtree->nodes().end(); ++it)
		{
			proj = findProjection(*it);

			if(proj != NULL)
				return proj;
		}
	}
	else if(proj == NULL)
	{
		TeAbstractTheme* theme = dynamic_cast<TeAbstractTheme*>(node);
		proj = theme->getThemeProjection();
	}

	return proj;
}

bool isProjectionsCompatible(TeProjection* viewProj, TeProjection* layerProj, 
									 std::string& errorMsg)
{
	std::string viewProjName = viewProj->name(),
				layerProjName = layerProj->name();

	if((viewProjName == "NoProjection") && (layerProjName != "NoProjection"))
	{
		errorMsg = " the view has no projection.";
	}
	else if((viewProjName != "NoProjection") && (layerProjName == "NoProjection"))
	{
		errorMsg = " the layer has no projection.";
	}

	if(!errorMsg.empty())
	{
		errorMsg = "Could not create theme because the view projection and layer projection are different: "
			+ errorMsg;

		return false;
	}

	return true;
}

TDK_API void DD2DMS(const double& decimalDegrees, int& degrees, int& minutes, double& seconds)
{
	degrees = (int) decimalDegrees;
	double interMinutes = (decimalDegrees - degrees) * 60.;
	minutes = (int) interMinutes;
	seconds = (interMinutes - minutes) * 60.;
}

TDK_API double DMS2DD(const int& degrees, const int& minutes, const double& seconds)
{
	return degrees + minutes / 60. + seconds / 3600.;
}

TDK_API std::string DD2DMSLabel(const double& decimalDegrees)
{
	int degrees, minutes;
	double seconds;
	DD2DMS(decimalDegrees, degrees, minutes, seconds);
	return DMSLabel(degrees, minutes, seconds);
}

TDK_API std::string DMSLabel(const int& degrees, const int& minutes, const double& seconds)
{
	std::string dms = Te2String(degrees);
	dms += "° ";
	dms += Te2String(minutes);
	dms += "\' ";
	dms += Te2String(seconds, 2);
	dms += "\"";

	return dms;
}
