#include "fontManager.h"

std::shared_ptr<Font> FontManager::LoadFont(const std::string &path) {
  auto it = m_fonts.find(path);
  if (it != m_fonts.end()) {
    return it->second;
  }

  Font rawFont = ::LoadFont(path.c_str());

  auto fontPtr = std::shared_ptr<Font>(new Font(rawFont), [](Font *fnt) {
    ::UnloadFont(*fnt);
    delete fnt;
  });

  m_fonts[path] = fontPtr;
  return fontPtr;
}

void FontManager::UnloadAll() { m_fonts.clear(); }

FontManager &FontManager::GetInstance() {
  static FontManager instance;
  return instance;
}