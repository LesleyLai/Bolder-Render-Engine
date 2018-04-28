#include "pathtracer.hpp"

#include <iostream>
#include <limits>
#include <random>
#include <memory>

#include "camera.hpp"
#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "image.hpp"
#include "sphere.hpp"
#include "scene.hpp"

constexpr size_t samples_count = 200;

static const std::uniform_real_distribution<> dis(-1, 1);



Color Path_tracer::trace(const Scene &scene, const Ray &ray, size_t depth) const noexcept
{
    // depth exceed some threshold
    if (depth == 0) {
        return Color{}; // return black
    }

    constexpr double inf = std::numeric_limits<double>::infinity();
    constexpr float damping = 0.5;

    if (auto hit = scene.intersect_at(ray, 0.0001, inf)) {
//        Material mat;
//        auto ref = mat.scatter(ray, *hit);
//        if (ref) {
//            return damping * trace(scene, *ref, depth-1);
//        } else {
//            return Color{};
//        }


    }

    const auto unit_direction = ray.direction / ray.direction.length();
    const auto t = static_cast<float>(0.5 * (unit_direction.y + 1));
    return (1.f - t) * Color{1,1,1} + t * Color(0.5f, 0.7f, 1);
}

Path_tracer::Path_tracer()
{
    Image image(200, 100);

    // Camera
    Camera camera;

    Scene scene {};
    scene.add_object<Sphere>(Vec3d(0,0,-1), 0.5);
    scene.add_object<Sphere>(Vec3d(0,-100.5,-1), 100);

    const auto width = image.width(), height = image.height();

    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (index_t j = 0; j < height; ++j) {
        for (index_t i = 0; i < width; ++i) {
            Color c;
            for (index_t sample = 0; sample < samples_count; ++sample) {
                const double u = (i + dis(gen)) / width;
                const double v = (j + dis(gen)) / height;

                const auto r = camera.getRay(u, v);
                c += trace(scene, r);
            }
            c /= static_cast<float>(samples_count);
            image.color_at(i, j) = c;
        }
        std::cout << (j / static_cast<double>(height) * 100) << "%\n" << std::flush;
    }

    std::string filename {"test.ppm"};
    image.saveto(filename);
    std::cout << "Save image to " << filename << '\n';
}