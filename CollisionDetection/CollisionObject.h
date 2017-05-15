#pragma once

#include <vector>
#include <cmath>
#include "Shape.h"
#include "Circle.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Triangle.h"

#define I_INSUFFICENT_PARAM_NUMBER_ERROR -1
#define I_INVALID_RECTANGLE_DATA -2

class CCollisionObject
{
public:
	CCollisionObject(){}
	~CCollisionObject()
	{ 
		for (int i = 0; i < v_shapes.size(); i++) delete v_shapes[i]; 
		v_shapes.clear(); 
	}

	int iAddBaseShape(CShape::EDefinedShapes iShapeTypeId, 
						std::vector<double>& vShapeData);
	CShape* pcGetShape(int iId){ return iId < v_shapes.size() ? v_shapes[iId] : nullptr; }

	void vShift(double dX, double dY)
	{
		for (int i = 0; i < v_shapes.size(); i++)
		{
			v_shapes[i]->vShift(dX, dY);
		}
	}
	void vRotate(double dAngle) //dAngle is in radians
	{
		for (int i = 0; i < v_shapes.size(); i++)
		{
			v_shapes[i]->vRotate(dAngle);
		}
	}
	bool bIsColliding(CCollisionObject* pcOtherObject);
private:
	std::vector<CShape*> v_shapes;

	bool b_check_rectangle_data(std::vector<double>& vRectangleData);
	void v_normalize_data(std::vector<double>& vData);
};

