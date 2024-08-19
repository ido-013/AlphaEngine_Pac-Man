#pragma once
#include <iostream>
#include <string>
#include "../ComponentManager/BaseComponent.h"
#include "AEAudio.h"

class AudioComp : public BaseComponent
{
private:
	AudioComp(const AudioComp& other) = delete;
	AudioComp& operator=(const AudioComp& other) = delete;

	AEAudioGroup group;
	AEAudio audio;

	std::string audioName;

	float volume = 0.5f;
	float pitch = 1;

	bool loop = true;
	bool playing = false;

public:
	AudioComp(GameObject* owner);
	~AudioComp();

	void Update();

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void SetAudio(std::string s);
	void UnloadAudio();

	static BaseRTTI* CreateAudioComponent(GameObject* owner);
	static constexpr const char* TypeName = "AudioComp";
};