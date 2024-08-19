template<typename T>
inline void EventManager::AddEvent(Entity* _owner)
{
	Event* event = new T(_owner);
	allEvents.push(event);
}

template<typename T>
inline void EventManager::RegisterEntity(Entity* entity)
{
	auto it = regEvents.find(typeid(T).name());

	if (it != regEvents.end())
	{
		it->second.push_back(entity);
	}
	else
	{
		regEvents.insert({ typeid(T).name(), std::list<Entity*>({entity}) });
	}
}

template<typename T>
inline void EventManager::UnregisterEntity(Entity* entity)
{
	auto it = regEvents.find(typeid(T).name());

	if (it != regEvents.end())
	{
		for (auto list_it = it->second.begin(); list_it != it->second.end(); list_it++)
		{
			if (entity == *list_it) 
			{
				it->second.erase(list_it);
				break;
			}
		}
	}
}
