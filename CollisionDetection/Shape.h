#pragma once

class CShape
{
public:
	CShape(){}

	enum EDefinedShapes
	{
		CIRCLE,
		TRIANGLE,
		RECTANGLE
	};
	
	virtual void vShift(double dX, double dY) = 0;
	virtual void vRotate(double dAngle) = 0; //dAngle is in radians

	virtual EDefinedShapes eGetShapeType() = 0;

	virtual bool bIsColliding(CShape* cShape) = 0;

protected:
	struct CPoint
	{
		CPoint(double dX = 0, double dY = 0) :dX(dX), dY(dY){}
		double dX;
		double dY;
	};
};

