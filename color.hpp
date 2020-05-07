#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

#include <iostream>

void writeColor(std::ostream &out, color pixelColor, int samples_per_pixel) {
  auto r = pixelColor.x();
  auto g = pixelColor.y();
  auto b = pixelColor.z();
  
  // divide color total by the number of samples
  auto scale = 1.0 / samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;

  // write the translated value of each color component (in [0, 255])
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif