#pragma once

#include "Polygon.h"

#define I_TRIANGLE_PARAM_NUMBER 6

class CTriangle :
	public CPolygon
{
public:
	CTriangle(std::vector<double>& vVerticesData): 
		CPolygon(vVerticesData){}

	EDefinedShapes eGetShapeType()
	{
		return EDefinedShapes::TRIANGLE;
	}
};

