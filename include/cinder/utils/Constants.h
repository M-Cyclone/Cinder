#pragma once
#include <cstddef>
#include <limits>
#include <numeric>

namespace cinder
{
namespace utils
{

static constexpr float k_eps = 1e-4f;

static constexpr float k_float_max = std::numeric_limits<float>::max();
static constexpr float k_float_min = std::numeric_limits<float>::min();

static constexpr size_t k_size_t_max = std::numeric_limits<size_t>::max();

static constexpr float k_pi     = 3.1415927f;
static constexpr float k_pi_inv = 1.0f / k_pi;

static constexpr float k_russian_roulette = 0.8f;

}  // namespace utils
}  // namespace cinder