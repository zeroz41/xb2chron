#include "classes/anm/Blender.h"

#include <algorithm>
#include <float.h>
#include "anm/BlendUtil.h"
#include "anm/ExtraBinding.h"
#include "anm/ExtraTruck.h"
#include "anm/SpaceResolveUtil.h"
#include "anm/TransformUtil.h"
#include "classes/anm/Animation.h"
#include "classes/anm/Binding.h"
#include "classes/anm/Control.h"
#include "classes/anm/Skeleton.h"
#include "mm/Math.h"
#include "mm/MMStdBase.h"

namespace anm {

Blender::Blender(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator)
    : ReferenceObject(pAllocator), m_controls(pAllocator), m_pSkeleton(pSkeleton) {
#line 46
    MM_ASSERT(m_pSkeleton);
    m_pSkeleton->addRef();
    m_controls.reserve(8);
    unsigned int boneCount = m_pSkeleton->m_bones.size();
    m_pWork = new (pAllocator->allocate(sizeof(Work), 8)) Work;
    unsigned int slotCount = m_pSkeleton->m_extraTruckSlots.size();
    unsigned int extraCount = 0;
    for (unsigned int i = 0; i < slotCount; i++) {
        unsigned int count = m_pSkeleton->getExtraTruckSlot(i).m_defaults.size();
        extraCount = extraCount > count ? extraCount : count;
    }
    m_pWork->m_extraValues.setAllocator(pAllocator);
    m_pWork->m_extraValues.resize(extraCount);
    m_pWork->m_weights.setAllocator(pAllocator);
    m_pWork->m_weights.resize(boneCount > extraCount ? boneCount : extraCount);
    m_pWork->m_transforms.setAllocator(pAllocator);
    m_pWork->m_transforms.resize(boneCount);
    m_pWork->m_partial.setAllocator(pAllocator);
    m_pWork->m_partial.resize(boneCount);
}

Blender::~Blender() {
    for (unsigned int i = 0; i < m_controls.size(); i++) {
        m_controls[i]->release();
    }
    m_controls.clear();
    if (m_pSkeleton != nullptr) {
        m_pSkeleton->release();
        m_pSkeleton = nullptr;
    }
    m_pWork->~Work();
    m_pAllocator->deallocate(m_pWork);
    m_pWork = nullptr;
}

Blender::Work::~Work() {}

bool Blender::addControl(Control* pControl) {
#line 105
    MM_ASSERT(pControl);
    if (pControl->m_pBinding->m_indexTable.size() == m_pSkeleton->m_bones.size()) {
        pControl->addRef();
        m_controls.push_back(pControl);
        return true;
    }
    return false;
}

bool Blender::removeControl(Control* pControl) {
    mm::mtl::Vector<Control*>::iterator it = std::find(m_controls.begin(), m_controls.end(), pControl);
    if (it == m_controls.end()) {
        return false;
    }
    m_controls.erase(it);
    pControl->release();
    return true;
}

void Blender::update(float dt) {
    for (mm::mtl::Vector<Control*>::iterator it = m_controls.begin(), end = m_controls.end(); it != end; ++it) {
        (*it)->update(dt);
    }
}

// sampleTrucks and sampleTrucksMS (0x71008731DC, 0x71008737F8): not identical yet, see wip/sampleTrucks_and_MS.cpp

void Blender::sampleExtraTrucks(unsigned short slot, unsigned int count, float* pOut) {
    Work* pWork = m_pWork;
    for (unsigned int i = 0; i < count; i++) {
        pOut[i] = 0.0f;
    }
    std::fill(pWork->m_weights.begin(), pWork->m_weights.end(), 0.0f);
    {
        BlendNormalExtraTruckDst normalDst = {pOut, pWork->m_weights.data()};
        for (unsigned int i = 0; i < m_controls.size(); i++) {
            float weight = m_controls[i]->m_weight;
            if (!(weight < FLT_EPSILON)) {
                const Binding* pBinding = m_controls[i]->m_pBinding;
    #line 573
                MM_ASSERT(pBinding);
                if (pBinding->m_extraBindings.size() > slot) {
                    const ExtraBinding& extra = pBinding->m_extraBindings[slot];
                    const ExtraTruck* pTruck = extra.m_pTruck;
                    if (pTruck != nullptr && pTruck->m_blendHint == 0 && pTruck->m_type != 2) {
                        float* pValues = m_pWork->m_extraValues.data();
                        if (m_controls[i]->sampleExtraTrucks(slot, count, pValues)) {
                            BlendExtraTruckSrc src = {count, pValues, &extra.m_indices, weight};
                            BlendUtil::blendNormalExtraTruck(src, &normalDst);
                        }
                    }
                }
            }
        }
    }
    const ExtraTruckSlot& truckSlot = m_pSkeleton->m_extraTruckSlots[slot];
    {
        NormalizeExtraTruckSrc src = {count, &truckSlot.m_defaults, pWork->m_weights.data(), &truckSlot};
        BlendUtil::normalizeExtraTruck(src, pOut);
    }
    {
        BlendAddExtraTruckDst addDst = {pOut};
        for (unsigned int i = 0; i < m_controls.size(); i++) {
            float weight = m_controls[i]->m_weight;
            if (!(weight < FLT_EPSILON)) {
                const Binding* pBinding = m_controls[i]->m_pBinding;
    #line 640
                MM_ASSERT(pBinding);
                if (pBinding->m_extraBindings.size() > slot) {
                    const ExtraBinding& extra = pBinding->m_extraBindings[slot];
                    const ExtraTruck* pTruck = extra.m_pTruck;
                    if (pTruck != nullptr && pTruck->m_blendHint == 1 && pTruck->m_type != 2) {
                        float* pValues = m_pWork->m_extraValues.data();
                        if (m_controls[i]->sampleExtraTrucks(slot, count, pValues)) {
                            BlendExtraTruckSrc src = {count, pValues, &extra.m_indices, weight};
                            BlendUtil::blendAddExtraTruck(src, &addDst);
                        }
                    }
                }
            }
        }
    }
    for (unsigned int i = 0; i < count; i++) {
        const ExtraTruckSlot::Limit& limit = truckSlot.m_limits[i];
        pOut[i] = mm::clamp(pOut[i], limit.m_min, limit.m_max);
    }
}

}  // namespace anm
