#ifndef CLASSES_GMK_GMKMANAGER_H
#define CLASSES_GMK_GMKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gmk/IGmkList.h"
#include "mm/mtl/Vector.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedList.h"
#include "classes/gmk/GmkBdat.h"
#include "classes/gmk/GmkPhantomManager.h"
#include "classes/gmk/GmkLandmarkManager.h"
#include "classes/gmk/GmkBgmCondInfoManager.h"
#include "classes/gmk/GmkSquadManager.h"
#include "classes/gmk/TGmkActiveList.h"

namespace gmk { class GmkManager; }
namespace gmk { class GmkPrecious; class GmkSe; class GmkSeLine; class GmkEvent; class GmkTutorial; }

namespace gmk {
// table 0x7100B6BBD0
class GmkManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkManager> {
public:
    // what create reads (GfFieldGimmick's constructor fills one on the stack: allocator 9's memory,
    // "bdat/common_gmk.bdat", "RSC_GmkSetList", 1; the names are not the original's)
    struct CreateInfo {
        // inline: GmkManager's constructor inlines it (no symbol); 2 is what it stores
        CreateInfo() : m_param(2) {}
        mtl::ALLOC_HANDLE m_handle;
        ::mm::mtl::FixStr<32> m_bdatPath;
        ::mm::mtl::FixStr<32> m_tableName;
        int m_param;
    };

    GmkManager();
    virtual ~GmkManager();  // slot 0
    void create(const CreateInfo& info);
    // whether create has run and dispose has not (GfFieldGimmick checks it before every call)
    bool isValid() const;
    void dispose();
    // builds a gimmick set (an RSC_GmkSetList row) in that memory at a position and rotation
    void createGmkSet(mtl::ALLOC_HANDLE handle, int bdatId, const mm::Vec3& pos, float rot);
    void disposeGmkSet(int bdatId);
    bool isGmkSetsReady() const;
    void update(float dt);
    bool updateImmediate();
    // its steps (named by the symbols): wait for the gimmick-set BDAT, then update
    void seqWaitValidateResDefBdatFp(float dt);
    void seqUpdate(float dt);
    bool isValidView() const;
    AGmkBase* findFirstGmkInstByBdatId(GmkType type, int bdatId) const;
    // the RSC_GmkSetList row of the first gimmick set holding a gimmick of this type and id (<= 0: none)
    int findFirstBdatId_RSC_GmkSetList(GmkType type, int bdatId) const;
    // the RSC_GmkSetList row of the first gimmick set of a FLD_maplist map (LocatorTalk_NpcID passes its "MapID")
    int findFirstBdatId_RSC_GmkSetList(int mapId) const;
    // whether the gimmick set of an RSC_GmkSetList row (> 0) names a BDAT table for this gimmick kind that is loaded
    // and holds the row bdatId (1.0.0's name)
    bool isBdatIdOfGmkInstExist(int id, GmkType type, int bdatId) const;
    // the gimmick set of an RSC_GmkSetList row, none when it is not loaded
    GmkSet* findGmkSet(int bdatId) const;
    // the BDAT table name the gimmick-set table's row id gives for a gimmick kind ("<kind>_bdat"), none when the
    // table has no such column
    const char* getSheetnameByType(int id, GmkType type) const;
    // the "mapId" of a gimmick-set table row, -1 for an id outside the table
    int getMapBdatId(int id) const;
    // calls f with every gimmick of a kind in every gimmick set; false while the sets are not ready
    template <typename F>
    bool traverseGmkInst(GmkType type, F& f) const {
        if (!isGmkSetsReady()) {
            return false;
        }
        for (const GmkSet* const* it = m_gmkSets.begin(); it != m_gmkSets.end(); ++it) {
            if (*it == nullptr) {
                continue;
            }
            const IGmkList* list = (*it)->getGmkList(type);
            if (list == nullptr) {
                continue;
            }
            unsigned int num = list->getInstNum();
            for (unsigned int i = 0; i < num; ++i) {
                const AGmkBase* gmk = list->getInst(i);
                if (gmk != nullptr) {
                    f(*gmk);
                }
            }
        }
        return true;
    }
    // adds the game object of every valid gimmick of kind T (T::getGobInst; -1: none) in every gimmick set
    template <typename T>
    void collectGameObjs(mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 1024>& list) const {
        size_t num = m_gmkSets.size();
        for (size_t i = 0; i < num; ++i) {
            const GmkSet* set = m_gmkSets[i];
            if (set == nullptr) {
                continue;
            }
            const IGmkList* gmkList = set->getGmkList(T::TYPE);
            if (gmkList == nullptr) {
                continue;
            }
            unsigned int instNum = gmkList->getInstNum();
            for (unsigned int j = 0; j < instNum; ++j) {
                const T* gmk = static_cast<const T*>(gmkList->getInst(j));
                if (gmk == nullptr || !gmk->isValid()) {
                    continue;
                }
                gf::GF_OBJ_HANDLE* handle = gmk->getGobInst();
                if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
                    list.push_back(handle);
                }
            }
        }
    }
    // the same for the kinds that pop several objects (T::getGobInstNum, T::getGobInst)
    template <typename T>
    void collectGameObjsUnbound(mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 1024>& list) const {
        size_t num = m_gmkSets.size();
        for (size_t i = 0; i < num; ++i) {
            const GmkSet* set = m_gmkSets[i];
            if (set == nullptr) {
                continue;
            }
            const IGmkList* gmkList = set->getGmkList(T::TYPE);
            if (gmkList == nullptr) {
                continue;
            }
            unsigned int instNum = gmkList->getInstNum();
            for (unsigned int j = 0; j < instNum; ++j) {
                const T* gmk = static_cast<const T*>(gmkList->getInst(j));
                if (gmk == nullptr || !gmk->isValid()) {
                    continue;
                }
                unsigned int gobNum = gmk->getGobInstNum();
                for (unsigned int k = 0; k < gobNum; ++k) {
                    gf::GF_OBJ_HANDLE* handle = gmk->getGobInst(k);
                    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
                        list.push_back(handle);
                    }
                }
            }
        }
    }

    // what create copies (the member names below are not the original's)
    CreateInfo m_createInfo;  // 0x8
    // the BDAT file of the map's gimmick sets (m_bdatFp below: a row per set, a column per gimmick kind naming its
    // resource and one ("<kind>_bdat") naming its BDAT table; GmkSet::createGmkLists reads it)
    GmkBdat m_bdat;  // 0x58
    // 0x190: the loaded BDAT file (seqWaitValidateResDefBdatFp stores Bdat::getFP's result; the name is not the
    // original's)
    unsigned char* m_bdatFp;
    int pad_198;
    GmkPhantomManager m_phantomManager;  // 0x1a0
    GmkLandmarkManager m_landmarkManager;  // 0xf220
    GmkBgmCondInfoManager m_bgmCondInfoManager;  // 0xf248
    GmkSquadManager m_squadManager;  // 0xf270
    TGmkActiveList<GmkPrecious> m_preciousActiveList;  // 0xf290
    TGmkActiveList<GmkSe> m_seActiveList;  // 0xf2b8
    TGmkActiveList<GmkSeLine> m_seLineActiveList;  // 0xf2e0
    TGmkActiveList<GmkEvent> m_eventActiveList;  // 0xf308
    TGmkActiveList<GmkTutorial> m_tutorialActiveList;  // 0xf330
    mm::mtl::Vector<GmkSet*> m_gmkSets;  // the gimmick sets (the name is not the original's)
    // 0xf380: the step update runs (seqWaitValidateResDefBdatFp, then seqUpdate; the name is not the original's)
    void (GmkManager::*m_seq)(float);
};
// a quest-target icon type's id in the icon sheet (< 0: none; the field locators then use 0x19f). A free
// function among GmkManager's in the same unit (GmkElevator.cpp's range).
int getBdatIdOfQuestTargetIcon(unsigned int iconType);
}  // namespace gmk

#endif
