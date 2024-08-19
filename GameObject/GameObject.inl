template<typename T>
inline T* GameObject::AddComponent()
{
	T* temp = GetComponent<T>();
	if (temp != nullptr)
	{
		return nullptr;
	}

	T* comp = new T(this);
	component.insert({ typeid(T).name(), comp });
}

template <typename T>
inline T* GameObject::AddComponent(BaseComponent* comp)
{
	T* temp = GetComponent<T>();
	if (temp != nullptr)
	{
		return nullptr;
	}

	component.insert({ typeid(T).name(), comp });
}


template<typename T>
inline T* GameObject::GetComponent()
{
	auto it = component.find(typeid(T).name());
	if (it != component.end())
	{
		return static_cast<T*>(it->second);
	}

	return nullptr;
}

template<typename T>
inline void GameObject::DeleteComponent()
{
	auto it = component.find(typeid(T).name());
	if (it != component.end())
	{
		delete it->second;
		component.erase(it);
	}
}
