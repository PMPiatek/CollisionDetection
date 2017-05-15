#pragma once

#include <vector>
#include "CollisionObject.h"

class CScene
{
public:
	CScene(){}
	~CScene()
	{
		for (int i = 0; i < v_objects.size(); i++) delete v_objects[i];
		v_objects.clear();
	}

	int iAddObject()
	{
		CCollisionObject* pc_new_object = new CCollisionObject();
		v_objects.push_back(pc_new_object);
		return v_objects.size() - 1;
	}
	CCollisionObject* pcGetObject(int iId){ return iId < v_objects.size() ? v_objects[iId] : nullptr; }

	typedef std::pair < CCollisionObject*, CCollisionObject* > CColidingObjectPair;
	void vGetCollidingPairs(std::vector<CColidingObjectPair>* vCollisions);
	

private:
	std::vector<CCollisionObject*> v_objects;
};

