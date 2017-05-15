#include <iostream>
#include "Scene.h"

using namespace std;

void main()
{
	CScene cScene;
	int i_object_1 = cScene.iAddObject();
	CCollisionObject* pc_object_1 = cScene.pcGetObject(i_object_1);
	cout << "Object 1: " << pc_object_1 << endl;

	int i_circle_1 = pc_object_1->iAddBaseShape(CShape::EDefinedShapes::CIRCLE, std::vector<double>{ 0, 4, 3 });
	int i_triangle_1 = pc_object_1->iAddBaseShape(CShape::EDefinedShapes::TRIANGLE, std::vector<double>{ 4, 7, -4, 7, 0, 9 });
	int i_rectangle_1 = pc_object_1->iAddBaseShape(CShape::EDefinedShapes::RECTANGLE, std::vector<double>{ -2, 0, 5, 0, 5, 3, -2, 3 });

	int i_object_2 = cScene.iAddObject();
	CCollisionObject* pc_object_2 = cScene.pcGetObject(i_object_2);
	cout << "Object 2: " << pc_object_2 << endl;

	int i_circle_2 = pc_object_2->iAddBaseShape(CShape::EDefinedShapes::CIRCLE, std::vector<double>{ 7, 8, 2.5 });
	int i_triangle_2 = pc_object_2->iAddBaseShape(CShape::EDefinedShapes::TRIANGLE, std::vector<double>{ -5, -2, 2, -3, 0, -1 });
	//int i_rectangle_2 = pc_object_2->iAddBaseShape(CShape::EDefinedShapes::RECTANGLE, std::vector<double>{ 5, -2, 7, -1, 6, -3, 3, 2 });

	int i_object_3 = cScene.iAddObject();
	CCollisionObject* pc_object_3 = cScene.pcGetObject(i_object_3);
	cout << "Object 3: " << pc_object_3 << endl;

	//int i_circle_3 = pc_object_3->iAddBaseShape(CShape::EDefinedShapes::CIRCLE, std::vector<double>{ 0, 0, 2 });
	//int i_triangle_3 = pc_object_3->iAddBaseShape(CShape::EDefinedShapes::TRIANGLE, std::vector<double>{ 0, 0, 2, 0, 1, 2 });
	//int i_rectangle_3 = pc_object_3->iAddBaseShape(CShape::EDefinedShapes::RECTANGLE, std::vector<double>{ 0, 0, 2, 0, 0, 2, 2, 2 });
	
	vector<CScene::CColidingObjectPair> v_collisions;
	cScene.vGetCollidingPairs(&v_collisions);
	for (int i = 0; i < v_collisions.size(); i++)
	{
		cout << "Collision of objects: " << v_collisions[i].first 
			 << " " << v_collisions[i].second << endl;
	}

	cin.ignore(1);
}