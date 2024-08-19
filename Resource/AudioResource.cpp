#include "AudioResource.h"

AudioResource::~AudioResource()
{
	UnloadData();
}

void AudioResource::LoadData(const std::string& name)
{
	data = new AEAudio;
	*(static_cast<AEAudio*>(data)) = AEAudioLoadMusic(name.c_str());
}

void AudioResource::UnloadData()
{
	if (data)
	{
		AEAudioUnloadAudio(*(static_cast<AEAudio*>(data)));
		delete data;
	}

	data = nullptr;
}
