#include "spdlog/spdlog.h"
#include <fmt/base.h>
#include "managers/loggerManager/loggerManager.h"
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


int main() 
{
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
        LOG_WARN("Failed to initialize ImGuiManager");
    }
#else
    std::shared_ptr<ImGuiManager> imGuiManager = nullptr;
#endif

    renderManager->SetImGuiManager(imGuiManager);
    if (isWorking)
    {
        sceneManager->PushScene(
            SceneFactory::createScene(SceneType::MAIN_MENU));
		float dt = GetFrameTime();
        while (!sceneManager->isEmpty())
        {
            dt = GetFrameTime();
            sceneManager->Update(dt);
            sceneManager->Render();
        }
    }

    textureManager->UnloadAll();
    soundManager->UnloadAll();
    fontManager->UnloadAll();
    renderManager->Shutdown();
}
