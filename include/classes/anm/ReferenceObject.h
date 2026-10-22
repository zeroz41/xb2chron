#ifndef CLASSES_ANM_REFERENCEOBJECT_H
#define CLASSES_ANM_REFERENCEOBJECT_H

#include "mm/MMStdBase.h"
#include "classes/mm/mtl/IAllocator.h"

// anmlib's anm_reference_object.h, as the including file's include path named it: the game's own files reach it
// from application/BF2, anmlib's own (MM_LIB_FROM_LIBS) from their build folder, skdlib's (SKD_LIB_PROJECT) from
// theirs (skd::Packet's destructor cites it so)
#if defined(SKD_LIB_PROJECT)
#define ANM_REFERENCE_OBJECT_PATH "../../../anmlib/src\\anmlib/base/anm_reference_object.h"
#elif defined(MM_LIB_FROM_LIBS)
#define ANM_REFERENCE_OBJECT_PATH "../../src\\anmlib/base/anm_reference_object.h"
#else
#define ANM_REFERENCE_OBJECT_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/anmlib/src\\anmlib/base/anm_reference_object.h"
#endif

namespace anm {
// table 0x7100B81078; an anmlib object its allocator made, counted while m_refEnable is set and handed back to
// m_pAllocator when the last reference goes
class ReferenceObject {
public:
    // an object in place in its binary (skd::DynamicsImporter::import): only its table is installed
    ReferenceObject() {}
    ReferenceObject(mm::mtl::IAllocator* pAllocator) : m_refCount(0), m_refEnable(0xFFFF), m_pAllocator(pAllocator) {
#line 34 ANM_REFERENCE_OBJECT_PATH
        MM_ASSERT(pAllocator);
    }
    virtual ~ReferenceObject() {}  // slot 0
    void addRef() const {
        if (m_refEnable != 0) {
            ++m_refCount;
        }
    }
    void release() const {
        if (m_refEnable != 0) {
            if (--m_refCount <= 0) {
#line 82 ANM_REFERENCE_OBJECT_PATH
                MM_ASSERT(m_pAllocator);
                const_cast<ReferenceObject*>(this)->~ReferenceObject();
                m_pAllocator->deallocate(const_cast<ReferenceObject*>(this));
            }
        }
    }

    mutable short m_refCount;  // addRef/release count it, const objects' too (Control holds a const Binding);
                               // the name is not the original's
    unsigned short m_refEnable;         // the constructor sets it; 0 stops the counting. The name is not the original's
    mm::mtl::IAllocator* m_pAllocator;  // anm_reference_object.h asserts `pAllocator` and `m_pAllocator`
};
}  // namespace anm

#endif
