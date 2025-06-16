#pragma once

#include "../fontManager/fontManager.h"
#include "../soundManager/soundManager.h"
#include "../textureManager/textureManager.h"
#include "raylib.h"
#include <memory>

class ResourceManager {
public:
  static std::shared_ptr<Texture2D> LoadTexture(const std::string &path);
  static std::shared_ptr<Sound> LoadSound(const std::string &path);
  static std::shared_ptr<Font> LoadFont(const std::string &path);

  static void UnloadTextures();
  static void UnloadSounds();
  static void UnloadFonts();
};