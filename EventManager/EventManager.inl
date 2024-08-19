template<typename T>
inline void EventManager::AddEvent(Entity* _src, Entity* _dst)
{
	Event* event = new T(_src, _dst);
	allEvents.push(event);
}
