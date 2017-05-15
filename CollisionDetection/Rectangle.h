#pragma once

#include "Polygon.h"

#define I_RECTANGLE_PARAM_NUMBER 8

class CRectangle :
	public CPolygon
{
public:
	CRectangle(std::vector<double>& vVerticesData) :CPolygon(vVerticesData){};

	EDefinedShapes eGetShapeType()
	{
		return EDefinedShapes::RECTANGLE;
	}
};

