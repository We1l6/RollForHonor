#include "mainMenuScene.h"


void MainMenuScene::Init(std::shared_ptr<RenderManager> renderManager,
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

    m_playButton = Button(
        RectanglePro({{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
                      {200.0f, 100.0f},
                      0,
                      10.0f}),
        UISkin(WHITE), TextPro("Play"), nullptr, []() {});

    m_settingsButton =
        Button(RectanglePro({{GetScreenWidth() / 2.0f,
                              GetScreenHeight() / 2.0f + 110.0f},
                             {200.0f, 100.0f},
                             0,
                             10.0f}),
               UISkin(WHITE), TextPro("Settings"), nullptr,
               [this]()
               {
                   if (auto manager = m_sceneManager.lock())
                   {
                       manager->PushScene(
                           SceneFactory::createScene(SceneType::SETTINGS));
                   }
               });

    m_exitButton = Button(RectanglePro({{GetScreenWidth() / 2.0f,
                                         GetScreenHeight() / 2.0f + 220.0f},
                                        {200.0f, 100.0f},
                                        0,
                                        10.0f}),
                          UISkin(WHITE), TextPro("Exit"), nullptr,
                          [this]() { m_shouldExit = true; });
}


void MainMenuScene::Update(float deltaTime) { UpdateMenuButtons(); }
void MainMenuScene::Render()
{
    DrawBackground();
    DrawMenuButtons();
}

void MainMenuScene::Unload() {}
bool MainMenuScene::ShouldExit() { return WindowShouldClose() || m_shouldExit; }


void MainMenuScene::LoadResources() {}
void MainMenuScene::DrawBackground() {}
void MainMenuScene::DrawMenuButtons()
{
    m_playButton.Draw();
    m_settingsButton.Draw();
    m_exitButton.Draw();
}

void MainMenuScene::UpdateMenuButtons()
{
    m_playButton.Update();
    m_settingsButton.Update();
    m_exitButton.Update();
}