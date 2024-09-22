#include "Application.h"
#include <iostream>

Application::Application() : m_audioManager(nullptr), m_voiceCloneManager(nullptr) {}

Application::~Application() {}

void Application::setAudioManager(AudioManager* manager) {
    m_audioManager = manager;
}

void Application::setVoiceCloneManager(VoiceCloneManager* manager) {
    m_voiceCloneManager = manager;
}

int Application::run(int argc, char* argv[]) {
    std::cout << "语音克隆应用程序启动..." << std::endl;
    
    // 这里添加应用程序的主要逻辑
    
    return 0;
}