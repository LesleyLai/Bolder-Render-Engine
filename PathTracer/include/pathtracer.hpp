#ifndef PATHTRACER_HPP
#define PATHTRACER_HPP

#include <cstddef>
#include <random>

class Scene;
struct Ray;
struct Color;


class Path_tracer
{
    static constexpr size_t max_depth = 5;

public:
    Path_tracer();

    Color trace(const Scene& scene, const Ray& ray, size_t depth = max_depth) const noexcept;

private:
    mutable std::mt19937 gen = std::mt19937{ std::random_device{}() }; //Standard mersenne_twister_engine seeded with rd()
};

#endif // PATHTRACER_HPP
