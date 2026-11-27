#include "Audio2D.h"
#include "logger/Logger.h"

#include <string>

Audio2D::~Audio2D() {
	unload();
}

void Audio2D::load(const std::string& soundPath) {
	if (AudioEngine2D::getEngine() == nullptr) {
		Logger::fatal("Audio Engine not initialized. Please contact the developer for more information");
	}
	else {
		if (m_audio == nullptr) {
			m_audio = new ma_sound;
		}

		ma_result res = ma_sound_init_from_file(AudioEngine2D::getEngine(), soundPath.c_str(), 0, nullptr, nullptr, m_audio);

		if (res != MA_SUCCESS) {
			delete m_audio;
			m_audio = nullptr;
			Logger::error("The sound file was not successfully uploaded");
		}
	}
}

void Audio2D::pause() {
	if (m_audio != nullptr) {
		if (AudioEngine2D::getEngine() == nullptr) {
			Logger::fatal("Audio Engine not initialized. Please contact the developer for more information");
		}
		else {
			ma_sound_stop(m_audio);
		}
	}
}

void Audio2D::play() {
	if (m_audio != nullptr) {
		if (AudioEngine2D::getEngine() == nullptr) {
			Logger::fatal("Audio Engine not initialized. Please contact the developer for more information");
		}
		else {
			ma_sound_start(m_audio);
		}
	}
}

void Audio2D::stop() {
	if (m_audio != nullptr) {
		if (AudioEngine2D::getEngine() == nullptr) {
			Logger::fatal("Audio Engine not initialized. Please contact the developer for more information");
		}
		else {
			ma_sound_stop(m_audio);
			ma_sound_seek_to_pcm_frame(m_audio, 0);
		}
	}
}

void Audio2D::setLoop(bool isLoop) {
	if (m_audio != nullptr) {
		if (AudioEngine2D::getEngine() == nullptr) {
			Logger::fatal("Audio Engine not initialized. Please contact the developer for more information");
		}
		else {
			if (isLoop == true) {
				ma_sound_set_looping(m_audio, MA_TRUE);
			}
			else {
				ma_sound_set_looping(m_audio, MA_FALSE);
			}
		}
	}
}

void Audio2D::setVolume(float volume) {
	if (m_audio != nullptr) {
		if (AudioEngine2D::getEngine() == nullptr) {
			Logger::fatal("Audio Engine not initialized. Please contact the developer for more information");
		}
		else {
			ma_sound_set_volume(m_audio, volume);
		}
	}
}

void Audio2D::setGeneralVolume(float volume) {
	if (AudioEngine2D::getEngine() == nullptr) {
		Logger::fatal("Audio Engine not initialized. Please contact the developer for more information");
	}
	else {
		AudioEngine2D::setMasterVolume(volume);
	}
}

void Audio2D::unload() {
	if (m_audio != nullptr) {
		if (AudioEngine2D::getEngine() == nullptr) {
			Logger::fatal("Audio Engine not initialized. Please contact the developer for more information");
		}
		else {
			ma_sound_uninit(m_audio);
			delete m_audio;
			m_audio = nullptr;
		}
	}
}