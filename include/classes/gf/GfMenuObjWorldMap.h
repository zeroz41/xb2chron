#ifndef CLASSES_GF_GFMENUOBJWORLDMAP_H
#define CLASSES_GF_GFMENUOBJWORLDMAP_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfGmkLocatorAtlas.h"
#include "gf/GfMenuSequence.h"
#include "mm/Aabb.h"
#include "mm/Pnt.h"
#include "mm/mtl/Array.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"

namespace ui { class UIListInfoBase; class UISelectObjList; class UICtrlCursorSelect; }

namespace gf {
class GfMenuIDList;
class GfMenuZoneMapList;
class GfMenuFieldSkillList;
class GfMenuCallContext;
struct MenuZoneMapInfo;

// table 0x7100B64FC8
class GfMenuObjWorldMap : public ::gf::GfMenuObject {
public:
    class IconFilterListener;
    class MainListener;
    class MapSelectListener;
    class PointSelectListener;
    class WorldListener;
    class WorldMapListener;
    class ZoneMapListener;
    class ZoneSelectListener;
    struct MapJumpInfo;

    GfMenuObjWorldMap(unsigned int handle);
    virtual ~GfMenuObjWorldMap();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it is the first function
    // of gf_menu_obj_world_map's .text, which GfMenuObjWorldMap's functions fill. What it does: true when the
    // 1-bit local game flag 51161 + id is 1; GfMenuZoneMapAdapter::update_ZonePointName passes its map id and shows
    // the point's name only then (else GfDataBdat 0xF5's row 0x67C). isEnableJump inlines it.
    static bool fn_7100495A98(unsigned int id);
    static bool isEnterMap(unsigned int mapId);
    static bool isEnableJump(const MenuZoneMapInfo& info);
    static void getFloorAABB(unsigned int mapId, unsigned int floor, mm::Aabb& aabb, mm::Pnt<short>& center);
    int getTotalFieldSkillLv(unsigned int fieldSkill);
    void refreshIconFilter();
    bool seqTexDeleteWait();
    bool seqTexLoadWait();

    // the names of the members are not the original's; types from initialize's create calls
    GfMenuIDList* m_mapList;                    // 0x28
    ui::UISelectObjList* m_mapSelectList;       // 0x30
    bool pad_38;                                // the constructor sets it
    GfMenuZoneMapList* m_zoneList;              // 0x40
    ui::UISelectObjList* m_zoneSelectList;      // 0x48
    GfMenuSequence<GfMenuObjWorldMap, 8> m_seq;  // 0x50
    ui::UIListInfoBase* m_list2E0;              // the destructor releases it twice
    float m_mapScale;                           // 0x2E8, the constructor's 1.0f
    GfMenuZoneMapList* m_pointList;             // 0x2F0
    ui::UISelectObjList* m_pointSelectList;     // 0x2F8
    mm::mtl::Array<MapJumpInfo> m_jumpInfos;    // 0x300
    unsigned int pad_318;
    GfMenuZoneMapList* m_zoneMapList1;          // 0x320
    GfMenuZoneMapList* m_zoneMapList2;          // 0x328
    GfMenuZoneMapList* m_zoneMapList3;          // 0x330 (the constructor leaves it)
    GfMenuFieldSkillList* m_fieldSkillList;     // 0x338
    // the blades with field skills (GfDataBlade::getListForFieldSkill fills it; getTotalFieldSkillLv sums them)
    mm::mtl::FixedVector<unsigned short, 422> m_fieldSkillBlades;  // 0x340
    bool pad_698;
    unsigned char pad_699[3];
    bool pad_69C;
    unsigned char pad_69D[0x1F];
    unsigned int pad_6BC;
    ui::UISelectObjList* m_iconSelectList;      // 0x6C0
    mm::mtl::FixedArray<mm::mtl::FixedVector<unsigned int, 256>, 10> m_iconTables;  // 0x6C8
    unsigned int pad_2F18;
    unsigned char pad_2F1C[0x44];
    bool pad_2F60;
    bool pad_2F61;
    GfMenuCallContext* m_context;               // 0x2F68
    bool pad_2F70;
    unsigned char* m_gmkBdat;                   // 0x2F78: initialize's Bdat::getFP of the gimmick sheet
    unsigned short pad_2F80;
    unsigned int m_iconFilter;                  // 0x2F84: one bit per icon filter row (GfMenuFlag 1)
    ui::UISelectObjList* m_iconFilterList;      // 0x2F88
    ui::UICtrlCursorSelect* m_iconFilterCursor;  // 0x2F90
    unsigned char pad_2F98[8];
    GfGmkLocatorAtlas::CreateInfo m_atlasInfo;  // 0x2FA0: finalize recreates the field's atlas from it
    unsigned int pad_2FD0;
    bool pad_2FD4;
};
}  // namespace gf

#endif
