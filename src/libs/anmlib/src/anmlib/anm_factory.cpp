#include <new>
#include "anm/Factory.h"
#include "classes/anm/ASMControl.h"
#include "classes/anm/Animation.h"
#include "classes/anm/Binding.h"
#include "classes/anm/Blender.h"
#include "classes/anm/Control.h"
#include "classes/anm/ExtraTruckBuffer.h"
#include "classes/anm/MirrorAnimation.h"
#include "classes/anm/MirrorMapper.h"
#include "classes/anm/Pose.h"
#include "classes/anm/ReferencePoseAnimation.h"
#include "classes/anm/ResASM.h"
#include "classes/anm/SimpleMapper.h"
#include "classes/anm/SimpleRetargetAnimation.h"
#include "classes/anm/Skeleton.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/MMStdBase.h"
#include "mm/Quat.h"

namespace anm {

Pose* Factory::createPose(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator) {
#line 37
    MM_ASSERT(pAllocator);
    if (pSkeleton == nullptr) {
        return nullptr;
    }
    Pose* pose = new (pAllocator->allocate(sizeof(Pose), 8)) Pose(pSkeleton, pAllocator);
    pose->addRef();
    return pose;
}

Control* Factory::createControl(const Binding* pBinding, mm::mtl::IAllocator* pAllocator) {
#line 59
    MM_ASSERT(pAllocator);
    if (pBinding == nullptr || pBinding->m_pAnimation == nullptr) {
        return nullptr;
    }
    Control* control = new (pAllocator->allocate(sizeof(Control), 8)) Control(pBinding, pAllocator);
    control->addRef();
    return control;
}

Blender* Factory::createBlender(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator) {
#line 81
    MM_ASSERT(pAllocator);
    if (pSkeleton == nullptr) {
        return nullptr;
    }
    Blender* blender = new (pAllocator->allocate(sizeof(Blender), 8)) Blender(pSkeleton, pAllocator);
    blender->addRef();
    return blender;
}

ExtraTruckBuffer* Factory::createExtraTruckBuffer(const Skeleton* pSkeleton, const char* name,
                                                  mm::mtl::IAllocator* pAllocator) {
#line 104
    MM_ASSERT(pAllocator);
    if (pSkeleton != nullptr) {
        unsigned short id = pSkeleton->getExtraTruckSlotID(name);
        if (id != 0xFFFF) {
            const ExtraTruckSlot& slot = pSkeleton->m_extraTruckSlots[id];
            if (slot.m_defaults.size() != 0) {
                ExtraTruckBuffer* buffer = new (pAllocator->allocate(sizeof(ExtraTruckBuffer), 8))
                    ExtraTruckBuffer(*pSkeleton, slot, pAllocator);
                buffer->addRef();
                return buffer;
            }
        }
    }
    return nullptr;
}

MirrorMapper* Factory::createMirrorMapper(const Skeleton* pSkeleton, short* pBonePairTable, MIRROR_AXIS axis,
                                          mm::mtl::IAllocator* pAllocator) {
#line 142
    MM_ASSERT(pBonePairTable);
#line 143
    MM_ASSERT(pAllocator);
    if (pSkeleton == nullptr) {
        return nullptr;
    }
    // the planes the axes name: indexed by the axis, though only the first is defined (the name is not the
    // original's)
    static const mm::Quat s_mirrorPlanes[] = {mm::Quat(1.0f, 0.0f, 0.0f, 0.0f)};
    MirrorMapper* mapper = new (pAllocator->allocate(sizeof(MirrorMapper), 8))
        MirrorMapper(pSkeleton, pBonePairTable, s_mirrorPlanes[axis], pAllocator);
    mapper->addRef();
    return mapper;
}

Binding* Factory::createMirrorAnimation(const Binding* pBinding, const MirrorMapper* pMapper,
                                        mm::mtl::IAllocator* pAllocator) {
#line 173
    MM_ASSERT(pAllocator);
    if (pBinding == nullptr || pMapper == nullptr ||
        pBinding->m_indexTable.size() != pMapper->m_pSkeleton->m_bones.size() ||
        pBinding->m_pAnimation->m_noMirror == 1) {
        return nullptr;
    }
    MirrorAnimation* animation =
        new (pAllocator->allocate(sizeof(MirrorAnimation), 8)) MirrorAnimation(pBinding, pMapper, pAllocator);
    return animation->createBinding();
}

SimpleMapper* Factory::createSimpleMapper(const Skeleton* pSrc, const Skeleton* pDst,
                                          mm::mtl::IAllocator* pAllocator) {
#line 248
    MM_ASSERT(pAllocator);
    SimpleMapper* mapper = nullptr;
    if (pSrc != nullptr && pDst != nullptr) {
        mapper = new (pAllocator->allocate(sizeof(SimpleMapper), 8)) SimpleMapper(*pSrc, *pDst, pAllocator);
        mapper->addRef();
    }
    return mapper;
}

Binding* Factory::createRetargetAnimation(const Binding* pBinding, const SimpleMapper* pMapper,
                                          mm::mtl::IAllocator* pAllocator) {
#line 272
    MM_ASSERT(pAllocator);
    if (pBinding == nullptr || pBinding->m_indexTable.size() != pMapper->m_pSkeleton->m_bones.size()) {
        return nullptr;
    }
    SimpleRetargetAnimation* animation = new (pAllocator->allocate(sizeof(SimpleRetargetAnimation), 8))
        SimpleRetargetAnimation(pBinding, pMapper, pAllocator);
    return animation->createBinding();
}

Binding* Factory::createReferencePoseAnimation(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator) {
#line 300
    MM_ASSERT(pAllocator);
    if (pSkeleton == nullptr) {
        return nullptr;
    }
    ReferencePoseAnimation* animation = new (pAllocator->allocate(sizeof(ReferencePoseAnimation), 8))
        ReferencePoseAnimation(pSkeleton, pAllocator);
    return animation->createBinding();
}

bool Factory::createASMResource(const ResStateArray& states, const ResResolver& resolver,
                                mm::mtl::IAllocator& allocator, ResASM** ppAsm) {
    ResASM* res = new (allocator.allocate(sizeof(ResASM), 8)) ResASM(states, resolver, allocator);
    res->addRef();
    bool result = true;
    const Skeleton* skeleton = res->m_pSkeleton;
    if (skeleton != nullptr) {
        // read-only: the const index operator's assertions (anm_array-inl.h lines 231 and 232)
        const Array<ResStateData>& stateData = res->m_states;
        for (unsigned int i = 0; i < stateData.size(); i++) {
            const ResStateData& state = stateData[i];
            for (unsigned int j = 0; j < state.m_clips.size(); j++) {
                const Binding* binding = state.m_clips[j].m_pBinding;
                if (binding != nullptr && skeleton->m_bones.size() != binding->m_indexTable.size()) {
                    mm::MMStdBase::mmPrint("モーションと骨の数が不一致[skl:%s/anm:%s]\n", skeleton->m_name,
                                           binding->m_pAnimation->m_name);
                    result = false;
                }
            }
        }
    }
    *ppAsm = res;
    return result;
}

ASMControl* Factory::createASMControl(const ResASM& res, mm::mtl::IAllocator& allocator) {
    ASMControl* control = new (allocator.allocate(sizeof(ASMControl), 16)) ASMControl(res, allocator);
    control->addRef();
    return control;
}

}  // namespace anm
