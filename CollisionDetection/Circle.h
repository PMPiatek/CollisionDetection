#pragma once

#include <cmath>
#include "Shape.h"

#define I_CIRCLE_PARAM_NUMBER 3

class CPolygon;

class CCircle :
	public CShape
{
public:
	CCircle(double dCenterX, double dCenterY, double fRadius) 
			:c_center(dCenterX, dCenterY), d_radius(fRadius){}

	double dGetCenterX(){ return c_center.dX; }
	double dGetCenterY(){ return c_center.dY; }
	double dGetRadius(){ return d_radius; }

	void vShift(double dX, double dY)
	{
		c_center.dX += dX;
		c_center.dY += dY;
	}
	void vRotate(double dAngle); //dAngle is in radians

	EDefinedShapes eGetShapeType()
	{
		return EDefinedShapes::CIRCLE;
	}

	bool bIsColliding(CShape* cShape);
private:
	CPoint c_center;
	double d_radius;

	bool b_is_colliding(CCircle* cCircle);
};

