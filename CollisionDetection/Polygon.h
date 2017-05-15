#pragma once

#include <vector>
#include <cmath>
#include "Shape.h"
#include "Circle.h"

class CCircle;

class CPolygon :
	public CShape
{
public:
	CPolygon(std::vector<double>& vVerticesData)
	{
		for (int i = 0; i < vVerticesData.size() - 1; i += 2)
		{
			v_vertices.push_back(CPoint(vVerticesData[i],
										vVerticesData[i + 1]));
		}
	}

	void vShift(double dX, double dY)
	{
		for (int i = 0; i < v_vertices.size(); i++)
		{
			v_vertices[i].dX += dX;
			v_vertices[i].dY += dY;
		}
	}
	void vRotate(double dAngle); //dAngle is in radians

	bool bIsColliding(CShape* cShape);

protected:
	std::vector<CPoint> v_vertices;

	bool b_is_colliding(CCircle* cCircle);
	bool b_is_colliding(CPolygon* pcPolygon);
	bool b_sat(CPolygon* pcPolygon);
};

