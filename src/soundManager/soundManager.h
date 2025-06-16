#pragma once

/**
 * @file soundManager.h
 * @brief Sound Manager
 * @details With Meyer's Singleton, I retrieve instances and load Sounds.
 * @author We1l6.f
 * @date 13/06/2025
 */

#include "raylib.h"
#include <memory>
#include <string>
#include <unordered_map>

class SoundManager {
public:
  static SoundManager &GetInstance();
  SoundManager(const SoundManager &) = delete;
  SoundManager &operator=(const SoundManager &) = delete;
  std::shared_ptr<Sound> LoadSound(const std::string &path);
  void UnloadAll();

private:
  SoundManager() = default;
  ~SoundManager() { UnloadAll(); }
  std::unordered_map<std::string, std::shared_ptr<Sound>> m_sounds;
};
