#include "Prefab.h"
#include <fstream>
#include "json.hpp"
#include "../ComponentManager/BaseComponent.h"

using json = nlohmann::ordered_json;

void Prefab::SavePrefab(const std::string& filename)
{
	json obj;
	obj["object"] = name;

	json components;
	for (auto comp : component)
	{
		BaseComponent* c = comp;
		components.push_back(c->SaveToJson());
	}
	obj["components"] = components;

	std::fstream file;
	file.open(filename, std::fstream::out);

	if (!file.is_open())
		throw std::invalid_argument("Prefab::SavePrefab file write error " + filename);

	file << std::setw(2) << obj;

	file.close();
}
