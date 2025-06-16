#pragma once

/**
 * @file resourceManager.h
 * @brief Resource Manager
 * @details With Meyer's Singleton, I retrieve instances and load resources
 * like textures, sounds, and fonts. This allows for efficient resource
 * management and easy access throughout the application.
 * @author We1l6.f
 * @date 13/06/2025
 */

#include "../fontManager/fontManager.h"
#include "../soundManager/soundManager.h"
#include "../textureManager/textureManager.h"
#include "raylib.h"
#include <memory>

class ResourceManager {
public:
  /**
   * @brief Returns a Texture2D texture via an instance by accessing the
   * TextureManager
   * @param path The path to the texture relative to the executable
   * @return A shared pointer to Texture2D from raylib.
   * @note Texture are automatically cached for better performance
   * @warning Path must be relative to executable directory
   * @example Example usage of LoadTexture:
   * @code
   * Texture2D result =
   * *ResourceManager::LoadTexture("resources/textures/texture.png");
   * @endcode
   */
  static std::shared_ptr<Texture2D> LoadTexture(const std::string &path);
  static bool FlipTexture(Texture2D &texture, bool horizontal, bool vertical);

  static bool ResizeTexture(Texture2D &texture, float newWidth,
                            float newHeight);
  /**
   * @brief Returns a Sound sound via an instance by accessing the
   * SoundManager
   * @param path The path to the sound relative to the executable
   * @return A shared pointer to Sound from raylib.
   * @note Sounds are automatically cached for better performance
   * @warning Path must be relative to executable directory
   * @example Example usage of LoadSound:
   * @code
   * Sound result =
   * *ResourceManager::LoadSound("resources/sounds/sound.mp3");
   * @endcode
   */
  static std::shared_ptr<Sound> LoadSound(const std::string &path);

  /**
   * @brief Returns a Font font via an instance by accessing the
   * FontManager
   * @param path The path to the font relative to the executable
   * @return A shared pointer to Font from raylib.
   * @note Font are automatically cached for better performance
   * @warning Path must be relative to executable directory
   * @example Example usage of LoadFont:
   * @code
   * Font result =
   * *ResourceManager::LoadFont("resources/fonts/font.ttf");
   * @endcode
   */
  static std::shared_ptr<Font> LoadFont(const std::string &path);

  /**
   * @brief Unloads all cached textures
   * @note Called automatically on program exit
   */
  static void UnloadTextures();

  /**
   * @brief Unloads all cached sounds
   * @note Called automatically on program exit
   */
  static void UnloadSounds();

  /**
   * @brief Unloads all cached fonts
   * @note Called automatically on program exit
   */
  static void UnloadFonts();
};