#pragma once
#include "raylib.h"
#include <memory>
#include <string>
#include <unordered_map>

class FontManager {
public:
  static std::shared_ptr<Font> LoadFont(const std::string &path);
  static void UnloadAll();

private:
  static std::unordered_map<std::string, std::shared_ptr<Font>> m_fonts;
};
