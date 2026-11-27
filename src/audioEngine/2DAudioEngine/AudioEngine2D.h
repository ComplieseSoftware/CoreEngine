#pragma once
#include "miniaudio/miniaudio.h"

#include <string>

class AudioEngine2D {
public:
	static bool init();
	static void shutdown();

	static void playOneShot(const std::string& soundPath);
	static void playSound(const std::string& soundPath);
	static void setMasterVolume(float volume);

	static ma_engine* getEngine();
private:
	inline static ma_engine m_engine{};
	inline static ma_result m_result{};

	inline static bool m_isInit{ false };
};