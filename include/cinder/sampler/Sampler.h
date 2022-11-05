#pragma once
#include <cassert>
#include <random>
#include <memory>
#include <mutex>

namespace cinder
{
namespace sampler
{

class Sampler
{
public:
    Sampler() noexcept
        : m_random_engine{ s_random_seed++ }, m_random_distribution(0.0f, 1.0f)
    {}
    virtual ~Sampler() noexcept = default;

    float getUniformFloat01()
    {
        float res = m_random_distribution(m_random_engine);
        assert((res >= 0.0f && res < 1.0f) &&
               "Invalid random value in getUniformFloat01().");
        return res;
    }

    std::unique_ptr<Sampler> create() const
    {
        return std::make_unique<Sampler>();
    }

private:
    std::default_random_engine            m_random_engine;
    std::uniform_real_distribution<float> m_random_distribution;

    inline static size_t s_random_seed = 0;
};

}  // namespace sampler
}  // namespace cinder