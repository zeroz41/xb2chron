#include "classes/fw/EffectManager.h"
#include "classes/fw/MovieManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComAnimation.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfMenuObjMovieLayer.h"
#include "classes/gf/GfMovieManager.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjUtil.h"
#include "gf/GfVolumeFade.h"

namespace gf {

GfComAnimation::GfComAnimation() {}

GfComAnimation::~GfComAnimation() {}

mm::mtl::RTTI GfComAnimation::m_rtti("GfComAnimation", &GfComponent::m_rtti, nullptr);

}  // namespace gf
