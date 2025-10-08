/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once

namespace CLI
{
  enum Result
  {
    SUCCESS,
    ERROR,
    GUI
  };

  Result run(int argc, char** argv);
};
