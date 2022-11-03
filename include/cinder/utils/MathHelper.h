#pragma once

#include "cinder/utils/Constants.h"

namespace cinder
{
namespace utils
{

static float angleToRadius(float angle)
{
    return angle * k_pi * (1.0f / 180.0f);
}

}  // namespace utils
}  // namespace cinder