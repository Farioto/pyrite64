/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <string>
#include <vector>

namespace Project
{
  struct SceneConf
  {
    std::string name{};

    std::string serialize() const;
  };

  class Scene
  {
    private:
      int id{};

    public:
      Scene(int id_);
  };
}