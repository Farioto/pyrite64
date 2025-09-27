/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <string>

#include "simdjson.h"

namespace Project
{
  class Project
  {
    private:
      std::string path;
      std::string pathConfig;

      struct
      {
        std::string name{};
        std::string romName{};
        std::string pathEmu{};
        std::string pathLibdragon{};
        std::string pathN64Inst{};
      } conf{};

      void deserialize(const simdjson::simdjson_result<simdjson::dom::element> &doc);
      std::string serialize() const;


    public:
      Project(const std::string &path);

      void save();

  };
}
