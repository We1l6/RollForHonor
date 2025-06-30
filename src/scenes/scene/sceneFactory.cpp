#include "sceneFactory.h"
#include "../mainMenuScene/mainMenuScene.h"
#include "../settingsScene/settingsScene.h"

std::unique_ptr<Scene> SceneFactory::createScene(SceneType type)
{
    switch (type)
    {
    case SceneType::MAIN_MENU:
        return std::make_unique<MainMenuScene>();
    case SceneType::SETTINGS:
        return std::make_unique<SettingsScene>();
    default:
        throw std::invalid_argument("Unknown scene type");
    }
}