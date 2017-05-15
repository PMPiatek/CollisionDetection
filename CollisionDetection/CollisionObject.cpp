#include "CollisionObject.h"


int CCollisionObject::iAddBaseShape(CShape::EDefinedShapes iShapeTypeId, 
									std::vector<double>& vShapeData)
{
	int i_response = v_shapes.size();
	
	switch (iShapeTypeId)
	{
	case CShape::EDefinedShapes::CIRCLE :
		if (vShapeData.size() == I_CIRCLE_PARAM_NUMBER)
		{
			CCircle* pc_circle = new CCircle(vShapeData[0], vShapeData[1], vShapeData[2]);
			v_shapes.push_back(pc_circle);
		}
		else i_response = I_INSUFFICENT_PARAM_NUMBER_ERROR;
		break;
	case CShape::EDefinedShapes::TRIANGLE :
		if (vShapeData.size() == I_TRIANGLE_PARAM_NUMBER)
		{
			CTriangle* pc_triangle = new CTriangle(vShapeData);
			v_shapes.push_back(pc_triangle);
		}
		else i_response = I_INSUFFICENT_PARAM_NUMBER_ERROR;
		break;
	case CShape::EDefinedShapes::RECTANGLE :
		if (vShapeData.size() == I_RECTANGLE_PARAM_NUMBER)
		{
			v_normalize_data(vShapeData);
			if (b_check_rectangle_data(vShapeData))
			{
				CRectangle* pc_rectangle = new CRectangle(vShapeData);
				v_shapes.push_back(pc_rectangle);
			}
			else i_response = I_INVALID_RECTANGLE_DATA;
		}
		else i_response = I_INSUFFICENT_PARAM_NUMBER_ERROR;
	}
	
	return i_response;
}

bool CCollisionObject::bIsColliding(CCollisionObject* pcOtherObject)
{
	bool b_found_collision = false;

	for (int i = 0; i < v_shapes.size() && !b_found_collision; i++)
	{
		for (int j = 0; j < pcOtherObject->v_shapes.size() && !b_found_collision; j++)
		{
			if (v_shapes[i]->bIsColliding(pcOtherObject->v_shapes[j]))
				b_found_collision = true;
		}
	}

	return b_found_collision;
}

bool CCollisionObject::b_check_rectangle_data(std::vector<double>& vRectangleData)
{
	bool b_valid_rectangle_data = true;

	std::vector<double> v_sides;
	for (int i = 0; i < vRectangleData.size(); i += 2)
	{
		double d_delta_x = vRectangleData[i] - vRectangleData[(i + 2) % 8];
		double d_delta_y = vRectangleData[i + 1] - vRectangleData[(i + 3) % 8];
		v_sides.push_back(std::hypot(d_delta_x, d_delta_y));
	}

	for (int i = 0; i < v_sides.size() && b_valid_rectangle_data; i++)
	{
		bool b_found_matching_side = false;
		for (int j = 0; j < v_sides.size(); j++)
		{
			if (i != j)
			{
				if (v_sides[i] == v_sides[j])
					b_found_matching_side = true;
			}
		}
		if (!b_found_matching_side)
			b_valid_rectangle_data = false;
	}
	
	if (b_valid_rectangle_data)
	{
		double d_hypot;
		if (v_sides[0] == v_sides[1])
		{
			d_hypot = std::hypot(v_sides[0], v_sides[2]);
		}
		else
		{
			d_hypot = std::hypot(v_sides[0], v_sides[1]);
		}

		double d_diagonal = 0;
		for (int i = 2; i < vRectangleData.size() && d_diagonal == 0; i += 2)
		{
			double d_delta_x = vRectangleData[0] - vRectangleData[i];
			double d_delta_y = vRectangleData[1] - vRectangleData[i + 1];
			double d_length = std::hypot(d_delta_x, d_delta_y);
			bool b_found_matching_side = false;
			for (int j = 0; j < v_sides.size(); j++)
			{
				if (d_length == v_sides[j])
					b_found_matching_side = true;
			}

			if (!b_found_matching_side)
			{
				d_diagonal = d_length;
			}
		}

		if (d_hypot != d_diagonal)
			b_valid_rectangle_data = false;
	}



	return b_valid_rectangle_data;
}

void CCollisionObject::v_normalize_data(std::vector<double>& vData)
{
	std::vector<std::pair<double, double>> v_work_data;
	for (int i = 0; i < vData.size(); i += 2)
	{
		v_work_data.push_back(
			std::pair<double, double>(vData[i], vData[i + 1]));
	}

	std::vector<std::pair<double, double>> v_work_data_2(v_work_data.size());
	v_work_data_2[0] = v_work_data[0];
	std::vector<int> v_added(1);
	for (int i = 0; i < v_work_data_2.size() - 1; i++)
	{
		std::vector<std::pair<double, int>> v_length_and_pos;
		
		for (int j = 1; j < v_work_data.size(); j++)
		{
			bool b_continue = true;
			for (int k = 0; k < v_added.size() && b_continue; k++)
			{
				if (v_added[k] == j)
				{
					b_continue = false;
				}	
			}
			if (b_continue)
			{
				double d_delta_x = v_work_data_2[i].first - v_work_data[j].first;
				double d_delta_y = v_work_data_2[i].second - v_work_data[j].second;
				v_length_and_pos.push_back(
					std::pair<double, int>(std::hypot(d_delta_x, d_delta_y), j));
			}
		}

		int i_min_length_pos = 0;
		for (int i = 1; i < v_length_and_pos.size(); i++)
		{
			if (v_length_and_pos[i_min_length_pos] > v_length_and_pos[i])
			{
				i_min_length_pos = i;
			}
		}

		v_added.push_back(v_length_and_pos[i_min_length_pos].second);
		v_work_data_2[i + 1] = v_work_data[v_length_and_pos[i_min_length_pos].second];
	}

	for (int i = 0, j = 0; i < vData.size() && j < v_work_data_2.size(); i += 2, j++)
	{
		vData[i] = v_work_data_2[j].first;
		vData[i + 1] = v_work_data_2[j].second;
	}
	
}