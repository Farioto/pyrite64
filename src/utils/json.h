/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include "simdjson.h"
#include "SDL3/SDL_iostream.h"

namespace Utils::JSON
{
  inline simdjson::dom::parser parser{};

  inline simdjson::simdjson_result<simdjson::dom::element> loadFile(const std::string &path) {
    auto jsonData = (char*)SDL_LoadFile(path.c_str(), nullptr);
    assert(jsonData);

    if (!jsonData) {
      return {};
    }


    auto doc = parser.parse(std::string_view{jsonData});
    SDL_free(jsonData);
    return doc;
  }

  inline std::string readString(const simdjson::simdjson_result<simdjson::dom::element> &el, const std::string &key) {
    auto val = el[key];
    if (val.error() != simdjson::SUCCESS) {
      return "";
    }
    auto str = val.get_string();
    if (str.error() != simdjson::SUCCESS) {
      return "";
    }
    return std::string{str->data(), str->length()};
  }
}

#define JSON_GET_STR(key) conf.key = Utils::JSON::readString(doc, #key);

#define JSON_SET_STR_LAST(key) \
builder.append_key_value<#key>(conf.key);

#define JSON_SET_STR(key) \
  JSON_SET_STR_LAST(key) \
  builder.append_comma();

