#pragma once

#include "../audio/AudioManager.h"
#include "../voice/VoiceCloneManager.h"

class Application {
public:
    Application();
    ~Application();

    void setAudioManager(AudioManager* manager);
    void setVoiceCloneManager(VoiceCloneManager* manager);
    int run(int argc, char* argv[]);

private:
    AudioManager* m_audioManager;
    VoiceCloneManager* m_voiceCloneManager;
};