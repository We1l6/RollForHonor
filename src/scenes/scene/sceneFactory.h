#pragma once

#include "../mainMenuScene/mainMenuScene.h"
#include "scene.h"
#include <memory>


enum class SceneType
{
    MAIN_MENU,
    GAME
};

class SceneFactory
{
  public:
    SceneFactory() = delete;
    static std::unique_ptr<Scene> createScene(SceneType type)
    {
        switch (type)
        {
        case SceneType::MAIN_MENU:
            return std::make_unique<MainMenuScene>();
        case SceneType::GAME:
            // return std::make_unique<GameScene>();
            throw std::runtime_error("Game scene not implemented yet");
        default:
            throw std::invalid_argument("Unknown scene type");
        }
    }
};