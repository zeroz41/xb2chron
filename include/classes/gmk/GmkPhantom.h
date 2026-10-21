#ifndef CLASSES_GMK_GMKPHANTOM_H
#define CLASSES_GMK_GMKPHANTOM_H

#include "mm/mtl/RTTI.h"
namespace gmk {
// table 0x7100B6BF68
class GmkPhantom {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GmkPhantom();  // slot 1
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gmk

#endif
