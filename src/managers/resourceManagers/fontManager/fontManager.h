#pragma once

/**
 * @file fontManager.h
 * @brief Font Manager
 * @details With Meyer's Singleton, I retrieve instances and load Fonts.
 * @author We1l6.f
 * @date 13/06/2025
 */

#include "raylib.h"
#include <memory>
#include <string>
#include <unordered_map>

class FontManager {
public:
  std::shared_ptr<Font> LoadFont(const std::string &path);
  void UnloadAll();
  FontManager() = default;
  ~FontManager() { UnloadAll(); }
private:

  std::unordered_map<std::string, std::shared_ptr<Font>> m_fonts;
};
