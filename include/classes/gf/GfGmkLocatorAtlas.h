#ifndef CLASSES_GF_GFGMKLOCATORATLAS_H
#define CLASSES_GF_GFGMKLOCATORATLAS_H

#include "mm/Vec3.h"
#include "mm/mtl/Vector.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gf/GfGmkLocator.h"

namespace gf {
// GfFieldGimmick holds one at 0xF4C0 (its constructor's GfGmkLocatorAtlas(nullptr)); 0x480 bytes, up to
// GfFieldGimmick's next member at 0xF940
class GfGmkLocatorAtlas {
public:
    // what create builds the atlas for: the map and its bounds (create copies it to the atlas's start). Holders
    // construct it with no map and inverted bounds (GfMenuObjWorldMap's constructor); the names are not the original's
    struct CreateInfo {
        CreateInfo() : m_mapId(0), m_param(0), m_min(1e12f, 1e12f, 1e12f), m_max(-1e12f, -1e12f, -1e12f) {}
        int m_mapId;  // create compares it with GfGameManager::getMapID
        int m_param;
        mm::Vec3 m_min;
        mm::Vec3 m_max;
    };

    // a row of the level table (GfDataBdat 0x17A): createBdatInfos reads its "level_name" (a string) and
    // "level_priority" (u16) into one (0x10 bytes); the field names are not the original's
    struct BdatInfo {
        BdatInfo() : m_levelName(nullptr), m_levelPriority(0) {}
        const char* m_levelName;
        unsigned short m_levelPriority;
    };

    GfGmkLocatorAtlas(const CreateInfo* info);
    ~GfGmkLocatorAtlas();
    void create(const CreateInfo& info);
    void dispose();
    void createBdatInfos();
    void seqWaitToCreateCurMapGmkSet(float delta);
    void seqWaitToCreateGmkSet(float delta);
    void update(float delta);
    bool isBelongToCurMap(const mm::Vec3& pos) const;

    // the field names below are not the original's
    CreateInfo m_info;
    mm::mtl::Vector<BdatInfo> m_bdatInfos;  // 0x30: a row of the level table each
    int m_bdatIdTop;                        // 0x58: the level table's first id (-1 when none)
    // 0x60: the gimmick set the steps work on: GmkManager's first set on the current map, else m_gmkSet
    gmk::GmkSet* m_curGmkSet;
    unsigned char pad_68[0x8];
    gmk::GmkSet m_gmkSet;                   // 0x70: the set create builds for another map
    mm::mtl::Vector<GfGmkLocators> m_locators;  // 0x440
    void (GfGmkLocatorAtlas::*m_seq)(float);    // 0x468: the step update runs
};
}  // namespace gf

#endif
