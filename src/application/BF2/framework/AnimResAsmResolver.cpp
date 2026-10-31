#include "classes/fw/AnimResAsmResolver.h"
#include "anm/AnimationImporter.h"
#include "anm/Factory.h"
#include "anm/Util.h"
#include "classes/anm/MirrorMapper.h"
#include "classes/anm/ResASM.h"
#include "classes/anm/SimpleMapper.h"
#include "classes/anm/Skeleton.h"
#include "string.h"

namespace fw {

AnimResAsmResolver::AnimResAsmResolver(mm::mtl::IAllocator& allocator)
    : m_arcs(&allocator), m_pSkeleton(nullptr), m_pMirrorMapper(nullptr), m_pSimpleMapper(nullptr),
      m_pAllocator(&allocator) {}

AnimResAsmResolver::~AnimResAsmResolver() {
    if (m_pMirrorMapper != nullptr) {
        m_pMirrorMapper->release();
        m_pMirrorMapper = nullptr;
    }
    if (m_pSimpleMapper != nullptr) {
        m_pSimpleMapper->release();
        m_pSimpleMapper = nullptr;
    }
}

void AnimResAsmResolver::bindSkeleton(const anm::Skeleton* pSkeleton, const anm::Skeleton* pSrcSkeleton) {
    m_pSkeleton = pSkeleton;

    mm::mtl::Vector<anm::Util::IgnoreName> ignoreNames(m_pAllocator);
    ignoreNames.reserve(2);
    {
        anm::Util::IgnoreName ignoreName;
        ignoreName.m_name = "DJ_";
        ignoreNames.push_back(ignoreName);
    }
    {
        anm::Util::IgnoreName ignoreName;
        ignoreName.m_name = "EX_";
        ignoreNames.push_back(ignoreName);
    }

    mm::mtl::Vector<signed char> ignores(m_pAllocator);
    ignores.reserve(m_pSkeleton->m_bones.size());
    anm::Util::computeIgnoreMirrorFromName(ignoreNames, m_pSkeleton, &ignores);
    unsigned short ride = m_pSkeleton->getBoneIndex("EX_ride");
    if (ride != 0xFFFF) {
        ignores[static_cast<short>(ride)] = 0;
    }

    mm::mtl::Vector<anm::Util::PairName> pairs(m_pAllocator);
    pairs.reserve(1);
    {
        anm::Util::PairName pair;
        pair.m_nameA = "_L";
        pair.m_nameB = "_R";
        pairs.push_back(pair);
    }

    mm::mtl::Vector<short> pairTable(m_pAllocator);
    pairTable.reserve(m_pSkeleton->m_bones.size());
    anm::Util::computeBonePairFromName(pairs, m_pSkeleton, ignores, &pairTable);
    m_pMirrorMapper = anm::Factory::createMirrorMapper(m_pSkeleton, pairTable.data(), anm::MIRROR_AXIS(0),
                                                       m_pAllocator);
    if (pSrcSkeleton != nullptr) {
        m_pSimpleMapper = anm::Factory::createSimpleMapper(pSrcSkeleton, m_pSkeleton, m_pAllocator);
    }
}

void AnimResAsmResolver::resolvePackFiles(const anm::ResStateArray& states, unsigned int count,
                                          arc::CArcData* pArcs) {
    m_arcs.resize(states.m_packNames.size());
    for (unsigned int i = 0; i != count; i++) {
        arc::CArcData& arc = pArcs[i];
        if (arc.m_data != nullptr) {
            const char* name = arc.getStr();
            for (unsigned int j = 0; j < states.m_packNames.size(); j++) {
                if (states.m_packNames[j] != nullptr && strcmp(states.m_packNames[j], name) == 0) {
                    m_arcs[j] = arc;
                    break;
                }
            }
        }
    }
}

const anm::Binding* AnimResAsmResolver::importBinding(const char* name, unsigned int index) const {
    if (name != nullptr && m_arcs[index].m_data != nullptr) {
        if (void* binary = m_arcs[index].getFileAdr(name)) {
            return anm::AnimationImporter::import(binary);
        }
    }
    return nullptr;
}

bool AnimResAsmResolver::restoreBinding(const char* name, unsigned int index) const {
    if (name != nullptr && m_arcs[index].m_data != nullptr) {
        if (void* binary = m_arcs[index].getFileAdr(name)) {
            return anm::AnimationImporter::restore(binary);
        }
    }
    return false;
}

const anm::Skeleton* AnimResAsmResolver::getSkekelton() const {
    return m_pSkeleton;
}

const anm::MirrorMapper* AnimResAsmResolver::getMirrorMapper() const {
    return m_pMirrorMapper;
}

const anm::SimpleMapper* AnimResAsmResolver::getSimpleMapper() const {
    return m_pSimpleMapper;
}

}  // namespace fw
