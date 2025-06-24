#include "spdlog/spdlog.h"
#include <fmt/base.h>

#include <raylib.h>
#include "memory"
#include "userInterface/UIUtils/TextBox/TextBox.h"
#include "managers/resourceManagers/textureManager/textureManager.h"
#include "managers/resourceManagers/fontManager/fontManager.h"
#include "managers/resourceManagers/soundManager/soundManager.h"
#include "managers/renderManager/renderManager.h"

int main() {
  auto renderManager = std::make_shared<RenderManager>();
  auto textureManager = std::make_shared<TextureManager>();
  auto soundManager = std::make_shared<SoundManager>();
  auto fontManager = std::make_shared<FontManager>();


  if(renderManager->Init(GetScreenWidth(), GetScreenHeight(), "RollForHonor")){
    Texture2D playerTexture = *textureManager->LoadTexture("resources/DavidATTACK.png");
    while (!WindowShouldClose()) {
      renderManager->BeginFrame();
      DrawTexture(playerTexture, 0, 0, WHITE);
      renderManager->EndFrame();
    } 
  }
  
  textureManager->UnloadAll();
  soundManager->UnloadAll();
  fontManager->UnloadAll();
  renderManager->Shutdown();
}