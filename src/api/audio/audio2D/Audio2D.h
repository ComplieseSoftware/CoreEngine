#pragma once

#include "audioEngine/2DAudioEngine/AudioEngine2D.h"
#include "miniaudio/miniaudio.h"
#include <string>

class Audio2D {
public:
	~Audio2D();

	void load(const std::string& soundPath);
	void play();
	void pause();
	void stop();
	void setLoop(bool Loop);
	void setVolume(float volume);
	void setGeneralVolume(float volume);

	void unload();
private:
	ma_sound* m_audio{ nullptr };
};