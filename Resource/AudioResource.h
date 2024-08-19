#pragma once
#include "AEEngine.h"
#include "Resource.h"

class AudioResource : public Resource
{
public:
	~AudioResource();
	void LoadData(const std::string& filename) override;
	void UnloadData() override;
};