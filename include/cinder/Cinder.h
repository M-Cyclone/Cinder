#pragma once

// core files
#include "cinder/core/Scene.h"

// accelerate files
#include "cinder/accelerate/AcceSortFunc.h"
#include "cinder/accelerate/AcceTree.h"

// geometry files
#include "cinder/geometry/AABB.h"
#include "cinder/geometry/Camera.h"
#include "cinder/geometry/Intersect.h"
#include "cinder/geometry/Primitive.h"
#include "cinder/geometry/Ray.h"
#include "cinder/geometry/Triangle.h"
#include "cinder/geometry/Vertex.h"

// integrator
#include "cinder/integrator/DirectLightingIntegrator.h"
#include "cinder/integrator/Integrator.h"

// renderer
#include "cinder/render/BasicDiffuseMaterial.h"
#include "cinder/render/BasicEmitMaterial.h"
#include "cinder/render/Material.h"
#include "cinder/render/Renderer.h"

// sampler
#include "cinder/sampler/Sampler.h"

// utils files
#include "cinder/utils/Constants.h"
#include "cinder/utils/MathHelper.h"