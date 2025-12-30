/**
* @copyright 2024 - Max Bebök
* @license MIT
*/
#include "renderer/particles/ptxSystem.h"
#include "lib/matrixManager.h"

P64::PTX::System::System(uint32_t maxSize)
  : countMax{maxSize}, count{0}
{
  assert(sizeof(countMax) % 2 == 0);
  if(countMax > 0) {
    mat = MatrixManager::alloc(1);
    particles = static_cast<TPXParticle*>(malloc_uncached(countMax * sizeof(TPXParticle) / 2));
  }
}

P64::PTX::System::~System() {
  if(countMax > 0) {
    MatrixManager::free(mat, 1);
    free_uncached(particles);
  }
}

void P64::PTX::System::draw() const {
  if(count == 0)return;
  tpx_matrix_push(mat);
  uint32_t safeCount = count & ~1;
  tpx_particle_draw(particles, safeCount);
  tpx_matrix_pop(1);
}

void P64::PTX::System::drawTextured() const {
  if(count == 0)return;
  tpx_matrix_push(mat);
  uint32_t safeCount = count & ~1;
  tpx_particle_draw_tex(particles, safeCount);
  tpx_matrix_pop(1);
}
