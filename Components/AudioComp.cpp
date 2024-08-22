#include "AEEngine.h"
#include "AEAudio.h"
#include "AudioComp.h"
#include "../ComponentManager/ComponentManager.h"
#include "../ResourceManager/ResourceManager.h"

AudioComp::AudioComp(GameObject* owner) : BaseComponent(owner), group(), audio(), audioName()
{
	ComponentManager<AudioComp>::GetInstance().AddComp(this);
	group = AEAudioCreateGroup();
}

AudioComp::~AudioComp()  
{
	//AEAudioUnloadAudioGroup(group);
	ResourceManager::GetInstance().UnloadResource(audioName);
	ComponentManager<AudioComp>::GetInstance().DelComp(this);
}

void AudioComp::Update()
{
	int loops = 0;
	if (loop)
		loops = -1;

	if (!playing)
	{
		playing = true;
		AEAudioPlay(audio, group, volume, pitch, loops);
	}
}

void AudioComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("audioName");
		audioName = it.value();
		SetAudio(audioName);

		it = compData->find("volume");
		volume = it.value();

		it = compData->find("pitch");
		pitch = it.value();

		it = compData->find("loop");
		loop = it.value();

		it = compData->find("playing");
		playing = it.value();
	}
}

json AudioComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["audioName"] = audioName;
	compData["volume"] = volume;
	compData["pitch"] = pitch;
	compData["loop"] = loop;
	compData["playing"] = playing;
	data["compData"] = compData;

	return data;
}

void AudioComp::SetAudio(std::string _name)
{
	audioName = _name;
	audio = *ResourceManager::GetInstance().GetResource<AEAudio>(_name);
}

void AudioComp::UnloadAudio()
{
}

BaseRTTI* AudioComp::CreateAudioComponent(GameObject* owner)
{
	BaseRTTI* p = new AudioComp(owner);

	owner->AddComponent<AudioComp>(static_cast<BaseComponent*>(p));

	return p;
}

