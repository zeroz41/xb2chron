#ifndef CLASSES_MM_MTL_REFERENCEOBJECT_H
#define CLASSES_MM_MTL_REFERENCEOBJECT_H

namespace mm { namespace mtl {
// table 0x7100B78250
class ReferenceObject {
public:
    ReferenceObject() : m_RefCount(1) {}
    virtual ~ReferenceObject() {}  // slot 0
    int m_RefCount;  // reference_object.h asserts `m_RefCount > 0` as it releases one
};
}}  // namespace mm::mtl

#endif
