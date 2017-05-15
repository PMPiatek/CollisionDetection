#include "Polygon.h"

void CPolygon::vRotate(double dAngle)
{
	for (int i = 0; i < v_vertices.size(); i++)
	{
		double d_new_x_val = v_vertices[i].dX * std::cos(dAngle) 
							- v_vertices[i].dY * std::sin(dAngle);
		double d_new_y_val = v_vertices[i].dX * std::sin(dAngle) 
							+ v_vertices[i].dY * std::cos(dAngle);

		v_vertices[i].dX = d_new_x_val;
		v_vertices[i].dY = d_new_y_val;
	}
}

bool CPolygon::bIsColliding(CShape* cShape)
{
	bool result = false;

	if (cShape->eGetShapeType() == CIRCLE)
	{
		result = b_is_colliding((CCircle*)cShape);
	}
	else
	{
		result = b_is_colliding((CPolygon*)cShape);
	}

	return result;
}

bool CPolygon::b_is_colliding(CCircle* pcCircle)
{
	bool b_found_gap = false;

	for (int i = 0; i < v_vertices.size() && !b_found_gap; i++)
	{
		double d_delta_x = v_vertices[i].dX
			- v_vertices[(i + 1) % v_vertices.size()].dX;
		double d_delta_y = v_vertices[i].dY
			- v_vertices[(i + 1) % v_vertices.size()].dY;
		CPoint c_vect(d_delta_x, d_delta_y);
		double d_length = std::hypot(c_vect.dX, c_vect.dY);
		CPoint c_normal_vect(-(c_vect.dY / d_length), c_vect.dX / d_length);

		std::vector<double> v_vertex_projections_1;

		for (int i = 0; i < v_vertices.size(); i++)
		{
			double d_projection = v_vertices[i].dX * c_normal_vect.dX
				+ v_vertices[i].dY * c_normal_vect.dY;
			v_vertex_projections_1.push_back(d_projection);
		}

		double d_projection_max_1 = v_vertex_projections_1[0];
		double d_projection_min_1 = v_vertex_projections_1[0];
		for (int i = 1; i < v_vertex_projections_1.size(); i++)
		{
			if (v_vertex_projections_1[i] > d_projection_max_1)
			{
				d_projection_max_1 = v_vertex_projections_1[i];
			}
			else if (v_vertex_projections_1[i] < d_projection_min_1)
			{
				d_projection_min_1 = v_vertex_projections_1[i];
			}
		}

		double d_circle_center_projection = pcCircle->dGetCenterX() * c_normal_vect.dX
										+ pcCircle->dGetCenterY() * c_normal_vect.dY;;
		double d_projection_max_2 = d_circle_center_projection + pcCircle->dGetRadius();
		double d_projection_min_2 = d_circle_center_projection - pcCircle->dGetRadius();

		if ((d_projection_max_1 < d_projection_min_2) 
			|| (d_projection_max_2 < d_projection_min_1))
		{
			b_found_gap = true;
		}
	}

	if (!b_found_gap)
	{
		std::vector<CPoint> v_vects;

		for (int i = 0; i < v_vertices.size(); i++)
		{
			double d_delta_x = pcCircle->dGetCenterX() - v_vertices[i].dX;
			double d_delta_y = pcCircle->dGetCenterY() - v_vertices[i].dY;
			v_vects.push_back(CPoint(d_delta_x, d_delta_y));
		}
		
		double d_delta_x = v_vects[0].dX;
		double d_delta_y = v_vects[0].dY;
		double d_min_dist = std::hypot(d_delta_x, d_delta_y);
		for (int i = 1; i < v_vects.size(); i++)
		{
			if (std::hypot(v_vects[i].dX, v_vects[i].dY) < d_min_dist)
			{
				d_delta_x = v_vects[i].dX;
				d_delta_y = v_vects[i].dY;
			}
		}

		CPoint c_vect(d_delta_x, d_delta_y);
		double d_length = std::hypot(c_vect.dX, c_vect.dY);
		CPoint c_normal_vect(-(c_vect.dY / d_length), c_vect.dX / d_length);

		std::vector<double> v_vertex_projections_1;

		for (int i = 0; i < v_vertices.size(); i++)
		{
			double d_projection = v_vertices[i].dX * c_normal_vect.dX
				+ v_vertices[i].dY * c_normal_vect.dY;
			v_vertex_projections_1.push_back(d_projection);
		}

		double d_projection_max_1 = v_vertex_projections_1[0];
		double d_projection_min_1 = v_vertex_projections_1[0];
		for (int i = 1; i < v_vertex_projections_1.size(); i++)
		{
			if (v_vertex_projections_1[i] > d_projection_max_1)
			{
				d_projection_max_1 = v_vertex_projections_1[i];
			}
			else if (v_vertex_projections_1[i] < d_projection_min_1)
			{
				d_projection_min_1 = v_vertex_projections_1[i];
			}
		}

		double d_circle_center_projection = pcCircle->dGetCenterX() * c_normal_vect.dX
			+ pcCircle->dGetCenterY() * c_normal_vect.dY;;
		double d_projection_max_2 = d_circle_center_projection + pcCircle->dGetRadius();
		double d_projection_min_2 = d_circle_center_projection - pcCircle->dGetRadius();

		if ((d_projection_max_1 < d_projection_min_2)
			|| (d_projection_max_2 < d_projection_min_1))
		{
			b_found_gap = true;
		}
	}

	return !b_found_gap;
}

bool CPolygon::b_is_colliding(CPolygon* pcPolygon)
{
	bool b_found_gap = false;

	b_found_gap = b_sat(pcPolygon);

	if (!b_found_gap)
		b_found_gap = pcPolygon->b_sat(this);

	return !b_found_gap;
}

bool CPolygon::b_sat(CPolygon* pcPolygon)
{
	bool b_found_gap = false;

	for (int i = 0; i < v_vertices.size() && !b_found_gap; i++)
	{
		double d_delta_x = v_vertices[i].dX
			- v_vertices[(i + 1) % v_vertices.size()].dX;
		double d_delta_y = v_vertices[i].dY
			- v_vertices[(i + 1) % v_vertices.size()].dY;
		CPoint c_vect(d_delta_x, d_delta_y);
		double d_length = std::hypot(c_vect.dX, c_vect.dY);
		CPoint c_normal_vect(-(c_vect.dY / d_length), c_vect.dX / d_length);

		std::vector<double> v_vertex_projections_1;

		for (int i = 0; i < v_vertices.size(); i++)
		{
			double d_projection = v_vertices[i].dX * c_normal_vect.dX
				+ v_vertices[i].dY * c_normal_vect.dY;
			v_vertex_projections_1.push_back(d_projection);
		}

		std::vector<double> v_vertex_projections_2;

		for (int i = 0; i < pcPolygon->v_vertices.size(); i++)
		{
			double d_projection = pcPolygon->v_vertices[i].dX * c_normal_vect.dX
				+ pcPolygon->v_vertices[i].dY * c_normal_vect.dY;
			v_vertex_projections_2.push_back(d_projection);
		}

		double d_projection_max_1 = v_vertex_projections_1[0];
		double d_projection_min_1 = v_vertex_projections_1[0];
		for (int i = 1; i < v_vertex_projections_1.size(); i++)
		{
			if (v_vertex_projections_1[i] > d_projection_max_1)
			{
				d_projection_max_1 = v_vertex_projections_1[i];
			}
			else if (v_vertex_projections_1[i] < d_projection_min_1)
			{
				d_projection_min_1 = v_vertex_projections_1[i];
			}
		}

		double d_projection_max_2 = v_vertex_projections_2[0];
		double d_projection_min_2 = v_vertex_projections_2[0];
		for (int i = 1; i < v_vertex_projections_2.size(); i++)
		{
			if (v_vertex_projections_2[i] > d_projection_max_2)
			{
				d_projection_max_2 = v_vertex_projections_2[i];
			}
			else if (v_vertex_projections_2[i] < d_projection_min_2)
			{
				d_projection_min_2 = v_vertex_projections_2[i];
			}
		}

		if ((d_projection_max_1 < d_projection_min_2)
			|| (d_projection_max_2 < d_projection_max_1))
		{
			b_found_gap = true;
		}
	}

	return b_found_gap;
}
