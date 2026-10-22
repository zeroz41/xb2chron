#ifndef CLASSES_ANM_BINDING_H
#define CLASSES_ANM_BINDING_H

#include "anm/Array.h"
#include "anm/ExtraBinding.h"
#include "classes/anm/ReferenceObject.h"

namespace anm { class Animation; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {
// table 0x7100B811B8; an animation tied to a skeleton: per bone, the animation's track that drives it
class Binding : public ::anm::ReferenceObject {
public:
    explicit Binding(mm::mtl::IAllocator* pAllocator);
    virtual ~Binding();  // slot 0

    const Animation* m_pAnimation;  // anm_util.cpp asserts `binding.m_pAnimation`
    Array<short> m_indexTable;      // anm_control.cpp asserts `count == m_pBinding->m_indexTable.size()`
    Array<ExtraBinding> m_extraBindings;  // per extra-track slot (the name is not the original's)
};
}  // namespace anm

#endif
