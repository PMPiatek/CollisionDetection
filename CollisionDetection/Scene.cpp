#include "Scene.h"

void CScene::vGetCollidingPairs(std::vector<CColidingObjectPair>* vCollisions)
{
	vCollisions->clear();

	for (int i = 0; i < v_objects.size(); i++)
	{
		for (int j = i + 1; j < v_objects.size(); j++)
		{
			if (v_objects[i]->bIsColliding(v_objects[j]))
				vCollisions->push_back(CColidingObjectPair(v_objects[i], v_objects[j]));
		}
	}
}