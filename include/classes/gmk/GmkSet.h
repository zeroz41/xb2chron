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
    // what create takes (create copies it to 0x10 field by field after dispose resets them; GfGmkLocatorAtlas::create
    // builds one on its stack). The names are not the original's.
    struct CreateInfo {
        CreateInfo() : m_bdatId(-1), m_pos(0.0f, 0.0f, 0.0f), m_rotY(0.0f), m_flag(false) {}
        mtl::ALLOC_HANDLE m_allocHandle;  // its lists' memory
        int m_bdatId;                     // its RSC_GmkSetList row
        unsigned char pad_8[0x8];
        mm::Vec3 m_pos;  // 0x10
        float m_rotY;    // 0x20
        // 0x24: create stores its negation at 0x1b4 (GfGmkLocatorAtlas::create passes true)
        bool m_flag;
    };
    GmkSet(const CreateInfo* info);
    virtual ~GmkSet();  // slot 0
    virtual void createGmkLists(int);  // slot 2
    // whether the set is usable (gf_field_locator's collection locator tests it after GmkManager::findGmkSet)
    bool isValid() const;
    void create(const CreateInfo& info);
    void dispose();
    void update(float delta);
    // its list of the gimmicks of a kind, none when it has none
    const IGmkList* getGmkList(GmkType type) const;
    IGmkList* getGmkList(GmkType type);
    // how many kinds of gimmicks a set can hold: a list per GmkType
    static const int GMK_LIST_NUM = 64;
    unsigned char pad_8[0x8];
    mtl::ALLOC_HANDLE m_allocHandle;  // 0x10: its lists' memory (createGmkLists passes it on; the name is not the original's)
    int m_bdatId;  // 0x14: its RSC_GmkSetList row (GfAutoTalkManager::seqInit reads its autoTalk columns by it; the name is not the original's)
    unsigned char pad_18[0x8];
    mm::Vec3 m_pos;  // 0x20: passed to its lists (the name is not the original's)
    float m_rotY;  // 0x30: its lists' rotation (the name is not the original's)
    unsigned char pad_34[0x144];
    GmkNpcManager m_npcManager;  // 0x178 (the name is not the original's)
    unsigned char pad_180[0x2c];
    // createGmkLists sets it to 0x20 before anything else (nothing else here reads it; the name is not the original's)
    int m_listParam;  // 0x1ac
    unsigned char pad_1b0[0x8];
    IGmkList* m_gmkLists[GMK_LIST_NUM];  // 0x1b8: its list of each kind, by GmkType (the name is not the original's)
    // 0x3b8: create stores its step function there (seqWaitToValidate_GfGameManager_m_mapID); 0x3D0 bytes in all
    // (GfGmkLocatorAtlas holds one at 0x70, its next member at 0x440)
    unsigned char pad_3b8[0x10];
};
}  // namespace gmk

#endif
