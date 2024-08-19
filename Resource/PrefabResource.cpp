#include "PrefabResource.h"

PrefabResource::~PrefabResource()
{
	UnloadData();
}

void PrefabResource::LoadData(const std::string& filename)
{
	
}

void PrefabResource::UnloadData()
{
	data = nullptr;
}
