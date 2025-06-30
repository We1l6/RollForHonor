#include "settingsScene.h"
#include "raylib.h"


void SettingsScene::Init(std::shared_ptr<RenderManager> renderManager,
                         std::shared_ptr<TextureManager> textureManager,
                         std::shared_ptr<FontManager> fontManager,
                         std::shared_ptr<SoundManager> soundManager,
                         std::weak_ptr<SceneManager> sceneManager)
{
    m_renderManager = renderManager;
    m_textureManager = textureManager;
    m_fontManager = fontManager;
    m_soundManager = soundManager;
    m_sceneManager = sceneManager;

    m_saveButton = Button(
        RectanglePro({{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
                      {200.0f, 100.0f},
                      0,
                      10.0f}),
        UISkin(WHITE), TextPro("Save"), nullptr, []() {});

    m_backButton = Button(RectanglePro({{GetScreenWidth() / 2.0f,
                                         GetScreenHeight() / 2.0f + 110.0f},
                                        {200.0f, 100.0f},
                                        0,
                                        10.0f}),
                          UISkin(WHITE), TextPro("Back"), nullptr,
                          [this]() { m_shouldExit = true; });
}


void SettingsScene::Update(float deltaTime) { UpdateMenuButtons(); }
void SettingsScene::Render()
{
    DrawBackground();
    DrawMenuButtons();
}

void SettingsScene::Unload() {}
bool SettingsScene::ShouldExit() { return WindowShouldClose() || m_shouldExit; }


void SettingsScene::LoadResources() {}
void SettingsScene::DrawBackground() {}
void SettingsScene::DrawMenuButtons()
{
    m_saveButton.Draw();
    m_backButton.Draw();
}

void SettingsScene::UpdateMenuButtons()
{
    m_saveButton.Update();
    m_backButton.Update();
}