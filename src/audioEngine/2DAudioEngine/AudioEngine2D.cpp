#define MINIAUDIO_IMPLEMENTATION

#include "miniaudio/miniaudio.h"
#include "AudioEngine2D.h"
#include "logger/Logger.h"

#include <string>
#include <algorithm>

bool AudioEngine2D::init() {
    m_result = ma_engine_init(nullptr, &m_engine);
    
    if (m_result != MA_SUCCESS) {
        Logger::fatal("Failed to initialize Audio Engine 2D");
        return false;
    }

    m_isInit = true;
    return m_isInit;
}

void AudioEngine2D::shutdown() {
    if (m_isInit) {
        ma_engine_uninit(&m_engine); //Disable the audio engine
        m_isInit = false;
    }
    else {
        Logger::fatal("The sound engine 2D was not initialized, yet an attempt was made to clear the sound engine's memory");
        return;
    }
}

void AudioEngine2D::playOneShot(const std::string& audioPath) {
    if (m_isInit) {
        ma_engine_play_sound(&m_engine, audioPath.c_str(), NULL);
    }
    else {
        Logger::fatal("The sound engine 2D has not been initialized. Initialize the engine before playing any sound");
        return;
    }
}

void AudioEngine2D::setMasterVolume(float volume) {
    if (m_isInit) {
        ma_engine_set_volume(&m_engine, std::clamp(volume, 0.0f, 1.0f));
    }
    else {
        Logger::fatal("The sound engine 2D has not been initialized. Initialize the engine before setting volume");
    }
}

ma_engine* AudioEngine2D::getEngine() {
    if (&m_engine == NULL) {
        Logger::fatal("The sound engine 2D has not been initialized. Initialize the engine before getting engine information");
    }
    else {
        return &m_engine;
    }
}