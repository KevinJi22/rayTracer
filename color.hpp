#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

#include <iostream>

void writeColor(std::ostream &out, color pixelColor) {
    // write the translated value of each color component (in [0, 255])
    out << static_cast<int>(255.999 * pixelColor.x()) << ' '
        << static_cast<int>(255.999 * pixelColor.y()) << ' '
        << static_cast<int>(255.999 * pixelColor.z()) << '\n';
}

#endif