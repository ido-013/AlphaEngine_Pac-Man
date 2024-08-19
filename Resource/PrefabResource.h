#pragma once
#include "../Prefab/Prefab.h"
#include "Resource.h"

class PrefabResource : public Resource
{
public:
	~PrefabResource();
	void LoadData(const std::string& filename) override;
	void UnloadData() override;
};