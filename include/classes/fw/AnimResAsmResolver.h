#ifndef CLASSES_FW_ANIMRESASMRESOLVER_H
#define CLASSES_FW_ANIMRESASMRESOLVER_H

#include "anm/ResResolver.h"
#include "arc/CArcData.h"
#include "mm/mtl/Vector.h"

namespace anm { class ResStateArray; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B40D70; what an animation state machine resource's clips are bound with: per state machine pack,
// its archive (resolvePackFiles), and the skeleton with its mirror and retarget mappers (bindSkeleton).
// The field names are not the original's (the getters' and the constructor's argument tell them).
class AnimResAsmResolver : public ::anm::ResResolver {
public:
    explicit AnimResAsmResolver(mm::mtl::IAllocator& allocator);
    ~AnimResAsmResolver();
    // the skeleton the clips play on; its mirror mapper pairs bones by their "L_"/"R_" name parts, and with
    // pSrcSkeleton a simple mapper retargets from it
    void bindSkeleton(const anm::Skeleton* pSkeleton, const anm::Skeleton* pSrcSkeleton);
    // per pack name of states, the archive (of count) whose name it is
    void resolvePackFiles(const anm::ResStateArray& states, unsigned int count, arc::CArcData* pArcs);

    virtual const anm::Binding* importBinding(const char* name, unsigned int index) const;  // slot 0
    virtual bool restoreBinding(const char* name, unsigned int index) const;  // slot 1
    virtual const anm::Skeleton* getSkekelton() const;  // slot 2
    virtual const anm::MirrorMapper* getMirrorMapper() const;  // slot 3
    virtual const anm::SimpleMapper* getSimpleMapper() const;  // slot 4

    mm::mtl::Vector<arc::CArcData> m_arcs;  // per pack (importBinding's index)
    const anm::Skeleton* m_pSkeleton;
    anm::MirrorMapper* m_pMirrorMapper;
    anm::SimpleMapper* m_pSimpleMapper;
    mm::mtl::IAllocator* m_pAllocator;
};
}  // namespace fw

#endif
