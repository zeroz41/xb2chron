#ifndef CLASSES_GMK_GMKPHANTOM_H
#define CLASSES_GMK_GMKPHANTOM_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/gmk/GmkPhantomManager.h"
namespace gmk {
// table 0x7100B6BF68
// its node (a non-polymorphic base, so at 0x8 after the table) links it into GmkPhantomManager's list
class GmkPhantom : public mm::mtl::IntrusiveListNodeBase {
public:
    // 1.0.0 has it out of line (GmkPhantom(CreateInfo const*): these stores, create when given one, then the link);
    // 3.0.1 inlines it into the gimmicks that embed one (construct_n<GmkSe>)
    GmkPhantom() {
        pad_60 = nullptr;
        pad_68 = false;
        pad_58 = 0;
        pad_50 = nullptr;
        pad_80 = 0;
        pad_78 = nullptr;
        pad_70 = nullptr;
        GmkPhantomManager::get()->m_phantoms.push_back(this);
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GmkPhantom();  // slot 1
    static mm::mtl::RTTI m_rtti;
    // fields: 1.0.0's constructor clears each (0x50..0x80 in its body, in this order) (meaning unknown; the names are not the original's)
    unsigned char pad_18[0x8];
    int pad_20 = 0;
    unsigned char pad_24[0xc];
    void* pad_30 = nullptr;
    int pad_38 = 0;
    void* pad_40 = nullptr;
    int pad_48 = 0;
    void* pad_50;
    int pad_58;
    void* pad_60;
    bool pad_68;
    void* pad_70;
    void* pad_78;
    int pad_80;
};
}  // namespace gmk

#endif
