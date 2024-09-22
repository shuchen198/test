#include <iostream>
#include <memory>
#include "app/Application.h"
#include "audio/AudioManager.h"
#include "voice/VoiceCloneManager.h"

int main(int argc, char* argv[]) {
    try {
        // 初始化应用程序
        auto app = std::make_unique<Application>();
        
        // 初始化音频管理器
        auto audioManager = std::make_unique<AudioManager>();
        
        // 初始化语音克隆管理器
        auto voiceCloneManager = std::make_unique<VoiceCloneManager>();
        
        // 设置应用程序组件
        app->setAudioManager(audioManager.get());
        app->setVoiceCloneManager(voiceCloneManager.get());
        
        // 运行应用程序
        return app->run(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
}