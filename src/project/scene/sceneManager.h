/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <string>
#include <vector>

#include "scene.h"

namespace Project
{
  struct SceneEntry
  {
    int id{};
    std::string name;
  };

  class SceneManager
  {
    private:
      std::vector<SceneEntry> entries{};
      Scene *loadedScene{nullptr};

    public:
      SceneManager();
      ~SceneManager();

      void reload();
      void save();

      [[nodiscard]] const std::vector<SceneEntry> &getEntries() const { return entries; }

      void add();

      void loadScene(int id);
      [[nodiscard]] Scene* getLoadedScene() const { return loadedScene; }
  };
}
