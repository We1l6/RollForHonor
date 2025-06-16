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
  static FontManager &GetInstance();
  FontManager(const FontManager &) = delete;
  FontManager &operator=(const FontManager &) = delete;
  std::shared_ptr<Font> LoadFont(const std::string &path);
  void UnloadAll();

private:
  FontManager() = default;
  ~FontManager() { UnloadAll(); }
  std::unordered_map<std::string, std::shared_ptr<Font>> m_fonts;
};
