/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once

#include "scene.h"
#include "simdjson.h"

std::string Project::SceneConf::serialize() const {
  simdjson::builder::string_builder builder{};
  builder.start_object();
  builder.append_key_value<"name">(name);
  builder.end_object();
  return {builder.c_str()};
}

Project::Scene::Scene(int id_)
  : id{id_}
{
  printf("Load scene %d\n", id);
}
