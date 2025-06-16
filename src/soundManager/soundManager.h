#pragma once
#include "raylib.h"
#include <memory>
#include <string>
#include <unordered_map>

class SoundManager {
public:
  static std::shared_ptr<Sound> LoadSound(const std::string &path);
  static void UnloadAll();

private:
  static std::unordered_map<std::string, std::shared_ptr<Sound>> m_sounds;
};
