#pragma once

class Scene;
#include "../../scenes/scene/scene.h"
#include <memory>
#include <stack>

class SceneManager : public std::enable_shared_from_this<SceneManager>
{
  public:
    SceneManager(std::shared_ptr<RenderManager> renderManager,
                 std::shared_ptr<TextureManager> textureManager,
                 std::shared_ptr<FontManager> fontManager,
                 std::shared_ptr<SoundManager> soundManager)
        : m_renderManager(std::move(renderManager)),
          m_textureManager(std::move(textureManager)),
          m_fontManager(std::move(fontManager)),
          m_soundManager(std::move(soundManager))
    {
    }
    ~SceneManager();

    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();
    void ChangeScene(std::unique_ptr<Scene> scene);
    void Update(float deltaTime);
    void Render();
    [[nodiscard]] bool isEmpty() const;

  private:
    std::stack<std::unique_ptr<Scene>> m_scenes;
    std::shared_ptr<RenderManager> m_renderManager;
    std::shared_ptr<TextureManager> m_textureManager;
    std::shared_ptr<FontManager> m_fontManager;
    std::shared_ptr<SoundManager> m_soundManager;
};