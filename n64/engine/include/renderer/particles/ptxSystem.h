/**
* @copyright 2024 - Max Bebök
* @license MIT
*/
#pragma once
#include <t3d/t3d.h>
#include <t3d/tpx.h>

namespace P64::PTX
{
  struct System
  {
    fm_vec3_t pos{};
    T3DMat4FP *mat{};
    TPXParticle *particles{};
    uint32_t countMax{};
    uint32_t count{};
    uint32_t id{};
    float timer{0.0f};

    System(uint32_t maxSize = 0);
    ~System();

    [[nodiscard]] bool isFull() const { return count == countMax; }

    void removeParticle(uint32_t index) {
      tpx_buffer_copy(particles, index, --count);
      if(count & 1) {
        *tpx_buffer_get_size(particles, count + 1u) = 0;
      }
    }

    void draw() const;
    void drawTextured() const;
  };
}