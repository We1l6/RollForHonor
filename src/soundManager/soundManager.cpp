#include "soundManager.h"

std::shared_ptr<Sound> SoundManager::LoadSound(const std::string &path) {
  auto it = m_sounds.find(path);
  if (it != m_sounds.end()) {
    return it->second;
  }

  Sound rawSound = ::LoadSound(path.c_str());

  auto soundPtr = std::shared_ptr<Sound>(new Sound(rawSound), [](Sound *snd) {
    ::UnloadSound(*snd);
    delete snd;
  });

  m_sounds[path] = soundPtr;
  return soundPtr;
}

void SoundManager::UnloadAll() { m_sounds.clear(); }

SoundManager &SoundManager::GetInstance() {
  static SoundManager instance;
  return instance;
}