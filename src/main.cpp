#include "spdlog/spdlog.h"
#include <fmt/base.h>

#include "managers/renderManager/renderManager.h"
#include "managers/resourceManagers/fontManager/fontManager.h"
#include "managers/resourceManagers/soundManager/soundManager.h"
#include "managers/resourceManagers/textureManager/textureManager.h"
#include "managers/sceneManager/sceneManager.h"
#include "scenes/mainMenuScene/mainMenuScene.h"
#include "scenes/scene/sceneFactory.h"
#include "userInterface/UIUtils/TextBox/TextBox.h"
#include <memory>
#include <raylib.h>


#include <thread>
#include <atomic>

std::atomic<bool> loadCpu1(false);
std::atomic<bool> loadCpu2(false);
std::atomic<bool> loadCpu3(false);

void CpuLoadTask(std::atomic<bool>& flag)
{
    while (true) {
        if (flag.load()) {
            volatile double x = 0.0001;
            for (int i = 0; i < 1000000; ++i)
                x += std::sqrt(x);
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

static bool g_memoryLoadActive = false;

void MemoryLoadTask()
{
    std::vector<char*> allocatedBlocks;

    while (true) {
        if (g_memoryLoadActive) {
            char* block = new char[10 * 1024 * 1024];
            allocatedBlocks.push_back(block);

            memset(block, 1, 10 * 1024 * 1024);

            if (allocatedBlocks.size() > 50) {
                delete[] allocatedBlocks.front();
                allocatedBlocks.erase(allocatedBlocks.begin());
            }
        }
        else {
            for (auto ptr : allocatedBlocks)
                delete[] ptr;
            allocatedBlocks.clear();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    std::thread cpuThread1(CpuLoadTask, std::ref(loadCpu1));
    std::thread cpuThread2(CpuLoadTask, std::ref(loadCpu2));
    std::thread cpuThread3(CpuLoadTask, std::ref(loadCpu3));

    std::thread memoryThread(MemoryLoadTask);
    
    auto renderManager = std::make_shared<RenderManager>();
    auto textureManager = std::make_shared<TextureManager>();
    auto soundManager = std::make_shared<SoundManager>();
    auto fontManager = std::make_shared<FontManager>();
    auto sceneManager = std::make_shared<SceneManager>(
        renderManager, textureManager, fontManager, soundManager);

    bool isWorking = renderManager->Init(GetScreenWidth(), GetScreenHeight(),
        "RollForHonor");
#ifdef ENABLE_DEV_TOOLS
    auto imGuiManager = std::make_shared<ImGuiManager>();
    if (!imGuiManager->Init())
    {
        spdlog::error("Failed to initialize ImGuiManager");
    }
#else
    std::shared_ptr<ImGuiManager> imGuiManager = nullptr;
#endif
    renderManager->SetImGuiManager(imGuiManager);

    if (isWorking)
    {
        sceneManager->PushScene(
            SceneFactory::createScene(SceneType::MAIN_MENU));
        while (!sceneManager->isEmpty())
        {
            float dt = GetFrameTime();
            sceneManager->Update(dt);
            sceneManager->Render();

            if (IsKeyPressed(KEY_ONE)) {
                bool newState = !loadCpu1.load();
                loadCpu1.store(newState);
                std::cout << "CPU Thread 1 " << (newState ? "ON" : "OFF") << "\n";
            }
            if (IsKeyPressed(KEY_TWO)) {
                bool newState = !loadCpu2.load();
                loadCpu2.store(newState);
                std::cout << "CPU Thread 2 " << (newState ? "ON" : "OFF") << "\n";
            }
            if (IsKeyPressed(KEY_THREE)) {
                bool newState = !loadCpu3.load();
                loadCpu3.store(newState);
                std::cout << "CPU Thread 3 " << (newState ? "ON" : "OFF") << "\n";
            }
            if (IsKeyPressed(KEY_FOUR)) {
                g_memoryLoadActive = !g_memoryLoadActive;
                std::cout << "Memory Load " << (g_memoryLoadActive ? "ON" : "OFF") << "\n";
            }
        }
    }
	memoryThread.detach();

    cpuThread1.detach();
    cpuThread2.detach();
    cpuThread3.detach();
    textureManager->UnloadAll();
    soundManager->UnloadAll();
    fontManager->UnloadAll();
    renderManager->Shutdown();
    PerformanceMonitor::StopGPUMonitoring();
}