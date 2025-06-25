#pragma once

#include "../../scenes/scene/scene.h"

class MainMenuScene : public Scene
{
  public:
    MainMenuScene() = default;
    ~MainMenuScene() override = default;

    void Init(std::shared_ptr<RenderManager> &renderManager,
              std::shared_ptr<TextureManager> &textureManager,
              std::shared_ptr<FontManager> &fontManager,
              std::shared_ptr<SoundManager> &soundManager) override;

    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;
    bool ShouldExit() override;

  private:
    std::shared_ptr<RenderManager> m_renderManager;
    std::shared_ptr<TextureManager> m_textureManager;
    std::shared_ptr<FontManager> m_fontManager;
    std::shared_ptr<SoundManager> m_soundManager;
    bool m_shouldExit = false;
    Texture2D m_playerTexture;
};