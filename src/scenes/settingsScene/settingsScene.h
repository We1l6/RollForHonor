#pragma once

#include "../../scenes/scene/scene.h"
#include "../../userInterface/button/button.h"

class SettingsScene : public Scene
{
  public:
    SettingsScene() = default;
    ~SettingsScene() override = default;

    void Init(std::shared_ptr<RenderManager> renderManager,
              std::shared_ptr<TextureManager> textureManager,
              std::shared_ptr<FontManager> fontManager,
              std::shared_ptr<SoundManager> soundManager,
              std::weak_ptr<SceneManager> sceneManager) override;

    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;
    bool ShouldExit() override;

  private:
    void LoadResources();
    void DrawBackground();
    void DrawMenuButtons();
    void UpdateMenuButtons();

    Button m_saveButton;
    Button m_backButton;

  private:
    std::shared_ptr<RenderManager> m_renderManager;
    std::shared_ptr<TextureManager> m_textureManager;
    std::shared_ptr<FontManager> m_fontManager;
    std::shared_ptr<SoundManager> m_soundManager;
    bool m_shouldExit = false;
};