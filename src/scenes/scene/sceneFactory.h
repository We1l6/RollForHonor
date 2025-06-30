#pragma once


#include "scene.h"
#include <memory>

class MainMenuScene;
class SettingsScene;

enum class SceneType
{
    MAIN_MENU,
    SETTINGS,
};

class SceneFactory
{
  public:
    SceneFactory() = delete;
    static std::unique_ptr<Scene> createScene(SceneType type);
};