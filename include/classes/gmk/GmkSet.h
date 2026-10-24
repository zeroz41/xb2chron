#ifndef CLASSES_GMK_GMKSET_H
#define CLASSES_GMK_GMKSET_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkNpcManager.h"
#include "mm/Vec3.h"
#include "mtl/AllocHandle.h"

namespace gmk { class IGmkList; }

namespace gmk {
// table 0x7100B6BDF0
class GmkSet {
public:
    virtual ~GmkSet();  // slot 0
    virtual void createGmkLists(int);  // slot 2
    // its list of the gimmicks of a kind, none when it has none
    const IGmkList* getGmkList(GmkType type) const;
    IGmkList* getGmkList(GmkType type);
    // how many kinds of gimmicks a set can hold: a list per GmkType
    static const int GMK_LIST_NUM = 64;
    unsigned char pad_8[0x8];
    mtl::ALLOC_HANDLE m_allocHandle;  // 0x10: its lists' memory (createGmkLists passes it on; the name is not the original's)
    unsigned char pad_14[0xc];
    mm::Vec3 m_pos;  // 0x20: passed to its lists (the name is not the original's)
    float m_rotY;  // 0x30: its lists' rotation (the name is not the original's)
    unsigned char pad_34[0x144];
    GmkNpcManager m_npcManager;  // 0x178 (the name is not the original's)
    unsigned char pad_180[0x2c];
    // createGmkLists sets it to 0x20 before anything else (nothing else here reads it; the name is not the original's)
    int m_listParam;  // 0x1ac
    unsigned char pad_1b0[0x8];
    IGmkList* m_gmkLists[GMK_LIST_NUM];  // 0x1b8: its list of each kind, by GmkType (the name is not the original's)
};
}  // namespace gmk

#endif
