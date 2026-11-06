#ifndef CLASSES_GMK_GMKSET_H
#define CLASSES_GMK_GMKSET_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkBdat.h"
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
    // whether the set has reached its update step and none of its lists is still loading (a list with a memory
    // handle and a path that is not valid yet)
    bool isGmkListsCreated() const;
    // whether the set has reached its update step and every valid gimmick of its loaded lists passes
    // isGmkInstValidView
    bool isValidView() const;
    static bool isGmkInstValidView(const AGmkBase& gmk);
    void create(const CreateInfo& info);
    void dispose();
    void update(float delta);
    // GmkManager::updateImmediate's step for each set: false while the set is not in its update step
    bool updateImmediate();
    // its list of the gimmicks of a kind, none when it has none
    const IGmkList* getGmkList(GmkType type) const;
    IGmkList* getGmkList(GmkType type);
    // the first gimmick of a kind whose BDAT row is bdatId, none when it has none (1.0.0's name: 1.0.0's
    // GfGameUtil::findNpcMat44 calls it in the place of 3.0.1's findFirstGmkInstByBdatId, with the same arguments)
    AGmkBase* findFirstGmkInstByBdatId(GmkType type, int bdatId) const;
    // its steps (named by the symbols): wait for the game manager's map, create the lists, then update them
    void seqWaitToValidate_GfGameManager_m_mapID(float dt);
    void seqCreateMapBdat(float dt);
    void seqUpdate(float dt);
    // how many kinds of gimmicks a set can hold: a list per GmkType
    static const int GMK_LIST_NUM = 64;
    unsigned char pad_8[0x8];
    // 0x10: create's parameter, kept (dispose resets it from a default one: a struct copy; the name is not the
    // original's). Its m_allocHandle is its lists' memory (createGmkLists passes it on), m_bdatId its
    // RSC_GmkSetList row (GfAutoTalkManager::seqInit reads its autoTalk columns by it), m_pos and m_rotY its lists'
    // position and rotation
    CreateInfo m_createInfo;
    GmkBdat m_bdat;  // 0x40: the constructor stores its table (the name is not the original's)
    GmkNpcManager m_npcManager;  // 0x178 (0x40 bytes; the name is not the original's)
    IGmkList* m_gmkLists[GMK_LIST_NUM];  // 0x1b8: its list of each kind, by GmkType (the name is not the original's)
    // the step update runs (create stores seqWaitToValidate_GfGameManager_m_mapID, which moves on to
    // seqCreateMapBdat, then seqUpdate); 0x3D0 bytes in all (GfGmkLocatorAtlas holds one at 0x70, its next member at
    // 0x440); the name is not the original's
    void (GmkSet::*m_seq)(float dt);  // 0x3b8
};
}  // namespace gmk

#endif
