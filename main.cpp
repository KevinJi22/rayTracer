#include "useful_defs.hpp"
#include "color.hpp"
#include "hittableList.hpp"
#include "sphere.hpp"
#include "camera.hpp"

#include <iostream>


color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    // linearly blend colors
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int imageWidth = 384;
    const int imageHeight = static_cast<int>(imageWidth / aspect_ratio);
    const int samples_per_pixel = 100;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    point3 lower_left_corner(-2.0, -1.0, -1.0);
    point3 origin(0.0, 0.0, 0.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.25, 0.0);
    
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    camera cam;

    for (int j = imageHeight-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            color pixelColor(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = double(i + random_double()) / (imageWidth - 1);  
                auto v = double(j + random_double()) / (imageHeight - 1);
                ray r = cam.get_ray(u, v);
                pixelColor += ray_color(r, world);
               
            }
            writeColor(std::cout, pixelColor, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}
