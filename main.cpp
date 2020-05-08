#include "useful_defs.hpp"
#include "color.hpp"
#include "hittableList.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "material.hpp"

#include <iostream>


color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // ray bounce limit
    if (depth <= 0) {
        return color(0, 0, 0);
    }
    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation*ray_color(scattered, world, depth-1);
        return color(0, 0, 0);
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
    const int max_depth = 50;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    hittable_list world;

    world.add(make_shared<sphere>(
        point3(0,0,-1), 0.5, make_shared<lambertian>(color(0.7, 0.3, 0.3))));

    world.add(make_shared<sphere>(
        point3(0,-100.5,-1), 100, make_shared<lambertian>(color(0.8, 0.8, 0.0))));

    world.add(make_shared<sphere>(point3(1,0,-1), 0.5, make_shared<metal>(color(.8, .6, .2), 0.0)));
    world.add(make_shared<sphere>(point3(-1,0,-1), 0.5, make_shared<metal>(color(.8,.8,.8), 0.3)));
    
    camera cam;

    for (int j = imageHeight-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            color pixelColor(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (imageWidth - 1);  
                auto v = (j + random_double()) / (imageHeight - 1);
                ray r = cam.get_ray(u, v);
                pixelColor += ray_color(r, world, max_depth);
               
            }
            writeColor(std::cout, pixelColor, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}
