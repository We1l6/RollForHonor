#include "mainMenuScene.h"


void MainMenuScene::Init(std::shared_ptr<RenderManager> &renderManager,
                         std::shared_ptr<TextureManager> &textureManager,
                         std::shared_ptr<FontManager> &fontManager,
                         std::shared_ptr<SoundManager> &soundManager)
{
    m_renderManager = renderManager;
    m_textureManager = textureManager;
    m_fontManager = fontManager;
    m_soundManager = soundManager;
    m_playerTexture = *textureManager->LoadTexture(
        "resources/DavidATTACK.png"); // test texture
}


void MainMenuScene::Update(float deltaTime) {}
void MainMenuScene::Render() { DrawTexture(m_playerTexture, 0, 0, WHITE); }
void MainMenuScene::Unload() {}
bool MainMenuScene::ShouldExit() { return WindowShouldClose() || m_shouldExit; }