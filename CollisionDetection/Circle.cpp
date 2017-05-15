#include "Circle.h"

void CCircle::vRotate(double dAngle)
{
	double d_new_x_val = c_center.dX * std::cos(dAngle) 
						- c_center.dY * std::sin(dAngle);
	double d_new_y_val = c_center.dX * std::sin(dAngle) 
						+ c_center.dY * std::cos(dAngle);

	c_center.dX = d_new_x_val;
	c_center.dY = d_new_y_val;
}

bool CCircle::bIsColliding(CShape* cShape)
{
	bool result = false;
	
	if (cShape->eGetShapeType() == CIRCLE)
	{
		result = b_is_colliding((CCircle*)cShape);
	}
	else
	{
		result = cShape->bIsColliding(this);
	}

	return result;
}

bool CCircle::b_is_colliding(CCircle* cCircle)
{
	double d_delta_x = c_center.dX - cCircle->c_center.dX;
	double d_delta_y = c_center.dY - cCircle->c_center.dY;
	double d_distance = std::hypot(d_delta_x, d_delta_y);

	return d_distance <= d_radius + cCircle->d_radius;
}
