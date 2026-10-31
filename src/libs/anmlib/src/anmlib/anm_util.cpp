#include "anm/Util.h"
#include <math.h>
#include <string.h>
#include <algorithm>
#include "anm/Array.h"
#include "anm/AsmVariable.h"
#include "anm/Locomotion.h"
#include "anm/QsTransform.h"
#include "anm/SpaceResolveUtil.h"
#include "classes/anm/Animation.h"
#include "classes/anm/Binding.h"
#include "classes/anm/Control.h"
#include "classes/anm/MirrorAnimation.h"
#include "classes/anm/MirrorMapper.h"
#include "classes/anm/Pose.h"
#include "classes/anm/ResASM.h"
#include "classes/anm/SimpleRetargetAnimation.h"
#include "classes/anm/Skeleton.h"
#include "mm/Math.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/Vector.h"

namespace anm {

// orders an animation state machine's states against a name (std::lower_bound's comparator in
// Util::getVariableMinMax; the name is the symbol's)
struct CompResState {
    bool operator()(const ResState* state, const char* name) const { return strcmp(state->m_name, name) < 0; }
};

// orders an animation state machine's appendices against a name (std::lower_bound's comparator in
// Util::findAppendix; the name is the symbol's)
struct lessAppendix {
    bool operator()(const ResAppendix& appendix, const char* name) const { return strcmp(appendix.m_name, name) < 0; }
};

// a (speed) lerp blend tree's first and last points' positions when it follows the variable (Util::getVariableMinMax
// inlines it for both kinds; the name is not the original's)
template <typename T>
static inline bool getLerpVariableMinMax(const T& tree, const ResStateArray& states, const char* variable, float* pMin,
                                         float* pMax) {
    if (states.m_variables.size() > tree.m_variableIndex &&
        strcmp(states.m_variables[tree.m_variableIndex].m_name, variable) == 0) {
        *pMin = tree.m_nodes.m_pElements->m_position;
        *pMax = tree.m_nodes[tree.m_nodes.size() - 1].m_position;
        return true;
    }
    return false;
}

void Util::computeIgnoreMirrorFromName(const mm::mtl::Vector<IgnoreName>& names, const Skeleton* pSkeleton,
                                       mm::mtl::Vector<signed char>* pOut) {
    if (pSkeleton == nullptr) {
        return;
    }
    pOut->clear();
    unsigned int count = pSkeleton->m_bones.size();
    if (pOut->capacity() < count) {
        pOut->reserve(count, 8);
    }
    for (unsigned int i = 0; i < count; i++) {
        signed char ignore = 0;
        for (unsigned int j = 0; j < names.size(); j++) {
            if (strncmp(pSkeleton->getBone(i).m_name, names[j].m_name.m_str, names[j].m_name.length()) == 0) {
                ignore = -1;
                break;
            }
        }
        pOut->push_back(ignore);
    }
}

PlayMode Util::getPlayMode(const Binding& binding) {
#line 179
    MM_ASSERT(binding.m_pAnimation);
    return static_cast<PlayMode>(binding.m_pAnimation->m_clampTime);
}

char Util::getBlendHint(const Binding& binding) {
#line 191
    MM_ASSERT(binding.m_pAnimation);
    return binding.m_pAnimation->m_blendHint;
}

float Util::getPlayBackTime(const Binding& binding) {
    const Animation* pAnimation = binding.m_pAnimation;
#line 216
    MM_ASSERT(pAnimation);
    return pAnimation->m_interval * (pAnimation->m_frameCount - 1);
}

float Util::getInvFps(const Binding& binding) {
#line 254
    MM_ASSERT(binding.m_pAnimation);
    return binding.m_pAnimation->m_interval;
}

void Util::clampLimitExtraTruck(const ExtraTruckSlot& slot, unsigned int count, float* pValues) {
    for (unsigned int i = 0; i < count; i++) {
        const ExtraTruckSlot::Limit& limit = slot.m_limits[i];
        pValues[i] = mm::clamp(pValues[i], limit.m_min, limit.m_max);
    }
}

float Util::calcLocalTime(float time, float start, float end, PlayMode mode) {
    if (mode == PLAY_MODE_LOOP) {
        return fmodf(time - start, end) + start;
    }
    return mm::clamp(time, start, end);
}

bool Util::calcDeltaExtractMotion(const Binding& binding, float time, float dt, float start, float end,
                                  QsTransform* pOut) {
    if (end <= 0.0f) {
        return false;
    }
    const Animation* pAnimation = binding.m_pAnimation;
#line 349
    MM_ASSERT(pAnimation);
    const Locomotion* pLocomotion;
    switch (pAnimation->m_kind) {
    case 0xFF: {
        const MirrorAnimation* pMirror = static_cast<const MirrorAnimation*>(pAnimation);
        const Binding* pOriginalBinding = pMirror->m_pOriginal;
#line 354
        MM_ASSERT(pOriginalBinding);
        const Animation* pOriginalAnim = pOriginalBinding->m_pAnimation;
#line 356
        MM_ASSERT(pOriginalAnim);
        pLocomotion = pOriginalAnim->m_pLocomotion;
        if (pLocomotion == nullptr) {
            return false;
        }
        bool loop = getPlayMode(*pOriginalBinding) == PLAY_MODE_LOOP;
        QsTransform motion;
        pLocomotion->getDeltaReference(time, dt, start, start + end, loop, &motion);
        pMirror->m_pMapper->mirrorExtractMotion(motion, pOut);
        return true;
    }
    case 0xFD:
        pLocomotion = static_cast<const SimpleRetargetAnimation*>(pAnimation)->m_pOriginal->m_pAnimation->m_pLocomotion;
        if (pLocomotion == nullptr) {
            return false;
        }
        break;
    default:
        pLocomotion = pAnimation->m_pLocomotion;
        if (pLocomotion == nullptr) {
            return false;
        }
        break;
    }
    bool loop = getPlayMode(binding) == PLAY_MODE_LOOP;
    pLocomotion->getDeltaReference(time, dt, start, start + end, loop, pOut);
    return true;
}

bool Util::getVariableMinMax(const ResASM& res, const char* stateName, const char* variable, float* pMin,
                             float* pMax) {
#line 423
    MM_ASSERT(stateName);
    const ResStateArray* pStates = res.m_pStates;
    if (pStates == nullptr) {
        return false;
    }
    ArrayIterartor<ResState* const> it =
        std::lower_bound(pStates->m_states.begin(), pStates->m_states.end(), stateName, CompResState());
    if (it != pStates->m_states.end()) {
        const ResState* pState = *it;
        if (strcmp(pState->m_name, stateName) == 0 && pState->m_type == 2) {
            const ResBlendTree* pTree = pState->m_pTree;
            switch (pTree->m_type) {
            case 0:
                return getLerpVariableMinMax(*static_cast<const ResLerpTree*>(pTree), *pStates, variable, pMin, pMax);
            case 2:
                return getLerpVariableMinMax(*static_cast<const ResSpeedLerpTree*>(pTree), *pStates, variable, pMin,
                                             pMax);
            }
        }
    }
    return false;
}

bool Util::getAsmPlaybackTime(const ResASM& res, const char* state, unsigned int index, float* pTime) {
    const ResStateData* pData = res.findResStateData(state);
    if (pData == nullptr || index >= pData->m_clips.size()) {
        return false;
    }
    *pTime = pData->m_clips[index].m_end;
    return true;
}

const Binding* Util::getAsmBinding(const ResASM& res, const char* state, unsigned int index) {
    if (state == nullptr) {
        return nullptr;
    }
    const ResStateData* pData = res.findResStateData(state);
    if (pData == nullptr || index >= pData->m_clips.size()) {
        return nullptr;
    }
    return pData->m_clips[index].m_pBinding;
}

bool Util::getAsmLocomotionReference(const ResASM& res, const char* state, float time, unsigned int index,
                                     QsTransform* pOut) {
    const ResStateData* pData = res.findResStateData(state);
    if (pData == nullptr || index >= pData->m_clips.size()) {
        return false;
    }
    return pData->m_clips[index].getReference(time, pOut);
}

bool Util::getAsmLocomotionDeltaReference(const ResASM& res, const char* state, float time, float dt,
                                          unsigned int index, QsTransform* pOut) {
    const ResStateData* pData = res.findResStateData(state);
    if (pData == nullptr || index >= pData->m_clips.size()) {
        return false;
    }
    return pData->m_clips[index].getDeltaReference(time, dt, pOut);
}

const ResAppendix* Util::findAppendix(const ResASM& res, const char* name) {
    const ResStateArray* pStates = res.m_pStates;
    if (pStates == nullptr || pStates->m_appendices.size() == 0) {
        return nullptr;
    }
    ArrayIterartor<const ResAppendix> it =
        std::lower_bound(pStates->m_appendices.begin(), pStates->m_appendices.end(), name, lessAppendix());
    if (it == pStates->m_appendices.end() || strcmp(it.m_pData->m_name, name) != 0) {
        return nullptr;
    }
    return it.m_pData;
}

void Util::samplePoseSmartFromControl(Control* control, Pose* pose, bool flag) {
    if (control == nullptr || pose == nullptr) {
        return;
    }
    const Binding* pBinding = control->m_pBinding;
#line 1207
    MM_ASSERT(pBinding);
    unsigned char space = pBinding->m_pAnimation->m_noMirror;
    if (flag) {
        switch (space) {
        case 1: {
            mm::mtl::Vector<QsTransform>& local = pose->accessSyncedPoseLocalSpace();
            control->sampleTrucks(local.size(), local.data());
            const Skeleton* pSkeleton = pose->m_pSkeleton;
#line 1225
            MM_ASSERT(pSkeleton);
            SpaceResolveUtil::clacPoseMSNoTruck(pBinding, pSkeleton, local.data());
            SpaceResolveUtil::convertMStoLS(pSkeleton, local.data());
            break;
        }
        case 0: {
            mm::mtl::Vector<QsTransform>& local = pose->accessSyncedPoseLocalSpace();
            control->sampleTrucks(local.size(), local.data());
            break;
        }
        default:
            return;
        }
        pose->syncModelSpace();
    } else {
        switch (space) {
        case 1: {
            mm::mtl::Vector<QsTransform>& model = pose->accessSyncedPoseModelSpace();
            control->sampleTrucks(model.size(), model.data());
            break;
        }
        case 0: {
            mm::mtl::Vector<QsTransform>& model = pose->accessSyncedPoseModelSpace();
            control->sampleTrucks(model.size(), model.data());
            const Skeleton* pSkeleton = pose->m_pSkeleton;
#line 1242
            MM_ASSERT(pSkeleton);
            SpaceResolveUtil::setReferencePoseNoTruck(pBinding, pSkeleton, model.data());
            SpaceResolveUtil::convertLStoMS(pSkeleton, model.data());
            break;
        }
        }
    }
}

}  // namespace anm
