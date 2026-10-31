#include "classes/anm/ResASM.h"

#include "algorithm"
#include "anm/Factory.h"
#include "anm/ResResolver.h"
#include "anm/Util.h"
#include "classes/anm/Animation.h"
#include "classes/anm/Binding.h"
#include "classes/anm/Skeleton.h"
#include "mm/Math.h"
#include "mm/mtl/Vector.h"
#include "new"

namespace anm {

ResASM::ResASM(const ResStateArray& states, const ResResolver& resolver, mm::mtl::IAllocator& allocator)
    : ReferenceObject(&allocator), m_pStates(&states) {
    unsigned int count = states.m_states.size();
    ResStateData* pBuffer = static_cast<ResStateData*>(allocator.allocate(count * sizeof(ResStateData), 8));
    m_pStateBuffer = pBuffer;
    for (unsigned int i = 0; i < count; i++) {
        new (&pBuffer[i]) ResStateData;
    }
    m_states.m_pElements = m_pStateBuffer;
    m_states.m_size = count;
    for (unsigned int i = 0; i < m_states.size(); i++) {
        m_states[i].setup(*m_pStates->m_states[i], resolver, allocator);
    }
    m_pSkeleton = resolver.getSkekelton();
}

ResASM::~ResASM() {
    if (m_pSkeleton != nullptr) {
        m_pSkeleton->release();
        m_pSkeleton = nullptr;
    }
    for (unsigned int i = 0; i < m_states.size(); i++) {
        m_states[i].cleanup();
        m_states[i].~ResStateData();
    }
    m_states.m_pElements = nullptr;
    m_states.m_size = 0;
    m_pAllocator->deallocate(m_pStateBuffer);
    m_pStateBuffer = nullptr;
}

const ResStateData* ResASM::findResStateData(const char* name) const {
    ArrayIterartor<const ResStateData> it = std::lower_bound(m_states.begin(), m_states.end(), name, Comp());
    if (it == m_states.end() || strcmp(it->m_pInfo->m_name, name) != 0) {
        return nullptr;
    }
    return it.operator->();
}

bool ResASM::setEnterAnnotation(unsigned int kind, const char* stateName, const AsmAnnotetion& annotation) {
    ArrayIterartor<ResStateData> it = std::lower_bound(m_states.begin(), m_states.end(), stateName, Comp());
    if (it == m_states.end() || strcmp(it->m_pInfo->m_name, stateName) != 0) {
        return false;
    }
    it->m_enterAnnotations[kind].push_back(annotation);
    return true;
}

bool ResASM::setLeaveAnnotation(unsigned int kind, const char* stateName, const AsmAnnotetion& annotation) {
    ArrayIterartor<ResStateData> it = std::lower_bound(m_states.begin(), m_states.end(), stateName, Comp());
    if (it == m_states.end() || strcmp(it->m_pInfo->m_name, stateName) != 0) {
        return false;
    }
    it->m_leaveAnnotations[kind].push_back(annotation);
    return true;
}

bool ResASM::setFrameAnnotation(unsigned int kind, const char* stateName, float frame,
                                const AsmAnnotetion& annotation) {
    ArrayIterartor<ResStateData> it = std::lower_bound(m_states.begin(), m_states.end(), stateName, Comp());
    if (it == m_states.end() || strcmp(it->m_pInfo->m_name, stateName) != 0) {
        return false;
    }
    it->setFrameAnnotation(kind, 0, frame, annotation);
    return true;
}

void ResASM::sortAnnotation(unsigned int kind) {
    for (ArrayIterartor<ResStateData> it = m_states.begin(), end = m_states.end(); it != end; ++it) {
        it->sortAnnotation(kind);
    }
}

ResClipData::ResClipData() : m_pInfo(nullptr), m_pBinding(nullptr), m_start(0.0f), m_end(0.0f), m_unsorted(false) {}

void ResClipData::setup(const ResClipInfo& info, const ResResolver& resolver, mm::mtl::IAllocator& allocator) {
#line 42
    MM_ASSERT(m_pBinding == nullptr);
    m_pInfo = &info;
    m_pBinding = resolver.importBinding(info.m_animationName, info.m_animationIndex);
    if (m_pBinding != nullptr) {
        if (info.m_flags & 8) {
            if (const SimpleMapper* pMapper = resolver.getSimpleMapper()) {
                m_pBinding = Factory::createRetargetAnimation(m_pBinding, pMapper, &allocator);
            }
        }
        if (info.m_flags & 1) {
            if (const MirrorMapper* pMapper = resolver.getMirrorMapper()) {
                m_pBinding = Factory::createMirrorAnimation(m_pBinding, pMapper, &allocator);
            }
        }
    }
    if (m_pBinding == nullptr) {
        m_pBinding = Factory::createReferencePoseAnimation(resolver.getSkekelton(), &allocator);
    }
    if (m_pBinding != nullptr && info.m_start < 0.0f) {
        m_start = Util::getPlayBackTime(*m_pBinding);
    } else {
        m_start = info.m_start;
    }
    if (m_pBinding != nullptr && info.m_end < 0.0f) {
        m_end = Util::getPlayBackTime(*m_pBinding) - m_start;
    } else {
        m_end = info.m_end - m_start;
    }
    for (int kind = 0; kind < 5; kind++) {
        m_frameAnnotations[kind].setAllocator(&allocator);
    }
    if (m_pBinding != nullptr) {
        const Animation* pAnimation = m_pBinding->m_pAnimation;
        m_frameAnnotations[0].reserve(pAnimation->m_events.size(), 8);
        for (unsigned int i = 0; i < pAnimation->m_events.size(); i++) {
            const Animation::Event& event = pAnimation->m_events[i];
            AsmKeyframeAnnotation keyframe;
            keyframe.m_frame = event.m_frame * m_pBinding->m_pAnimation->m_interval;
            keyframe.m_annotation.m_name = event.m_name;
            keyframe.m_annotation.m_type = 1;
            keyframe.m_annotation.m_data = event.m_data;
            m_frameAnnotations[0].push_back(keyframe);
        }
    }
}

void ResClipData::cleanup() {
    if (m_pBinding != nullptr) {
        m_pBinding->release();
        m_pBinding = nullptr;
    }
    for (int kind = 0; kind < 5; kind++) {
        m_frameAnnotations[kind].clear();
    }
}

bool ResClipData::getReference(float time, QsTransform* pOut) const {
    if (m_pBinding == nullptr) {
        return false;
    }
    const Animation* pAnimation = m_pBinding->m_pAnimation;
#line 161
    MM_ASSERT(pAnimation);
    float to = mm::clamp(time, m_start, m_start + m_end);
    return pAnimation->getDeltaExtractMotion(m_start, to, false, pOut);
}

bool ResClipData::getDeltaReference(float time, float dt, QsTransform* pOut) const {
    if (m_pBinding == nullptr) {
        return false;
    }
    const Animation* pAnimation = m_pBinding->m_pAnimation;
#line 182
    MM_ASSERT(pAnimation);
    float from = mm::clamp(time, m_start, m_start + m_end);
    float to = mm::clamp(dt, m_start, m_start + m_end);
    return pAnimation->getDeltaExtractMotion(from, to - from, false, pOut);
}

void ResClipData::setFrameAnnotation(unsigned int kind, float frame, const AsmAnnotetion& annotation) {
    if (m_pBinding != nullptr) {
        AsmKeyframeAnnotation keyframe;
        keyframe.m_frame = frame * m_pBinding->m_pAnimation->m_interval;
        keyframe.m_annotation = annotation;
        m_frameAnnotations[kind].push_back(keyframe);
        m_unsorted = true;
    }
}

bool lessAsmKeyframeAnnotation(const AsmKeyframeAnnotation& lhs, const AsmKeyframeAnnotation& rhs) {
    return lhs.m_frame < rhs.m_frame;
}

void ResClipData::sortAnnotation(unsigned int kind) {
    std::sort(m_frameAnnotations[kind].begin(), m_frameAnnotations[kind].end(), lessAsmKeyframeAnnotation);
    m_unsorted = false;
}

}  // namespace anm
