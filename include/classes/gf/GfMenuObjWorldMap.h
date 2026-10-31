#ifndef CLASSES_GF_GFMENUOBJWORLDMAP_H
#define CLASSES_GF_GFMENUOBJWORLDMAP_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfGmkLocatorAtlas.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuSequence.h"
#include "mm/Aabb.h"
#include "mm/Col3.h"
#include "mm/Pnt.h"
#include "mm/Vec2.h"
#include "mm/mtl/Array.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"

namespace gmk { class AGmkBase; }
namespace ui { class UIObjectAcc; class UIListInfoBase; class UISelectObjList; class UICtrlCursorSelect; }

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
    // 0x18 bytes: Array<MapJumpInfo>::erase (fn_710049FDF4) steps 0x18; trivially destructible (the destructor
    // frees the array without destroying elements). Fields not known yet.
    struct MapJumpInfo {
        unsigned char pad_0[0x18];
    };

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
    // 1.0.0's setFadeIn/setFadeOut (0x71004E6D2C, 0x71004E6E18; out of line there, inlined into MainListener in 3.0.1)
    static int setFadeIn(unsigned int handle) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static int setFadeOut(unsigned int handle, bool flag) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_out = 1;
        param.m_preset = 6;
        param.m_eventId = 2;
        param.m_startFlag1 = flag;
        int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its code sits in
    // gf_menu_obj_world_map's .text right after initialize, which calls it (as WorldMapListener::reciveEvent does).
    // What it does: clears the list, then adds each map of the selectable-map table whose chkMapCond holds: maps 52
    // and 53 when add-on menu layer 3 is usable (GfMenuObjUtil::fn_710048FD30(3)), else 3-6, 9-16, 18, 20 and 21.
    static void fn_710049761C(GfMenuIDList* list);
    static void refreshMapSelect(ui::UIObjectAcc& acc, GfMenuIDList* list, ui::UISelectObjList* selectList, int index);
    static void setupPointSelect(ui::UIObjectAcc& acc, GfMenuZoneMapList* list);
    static bool chkMapCond(unsigned int mapId, mm::Pnt<short>* pos);
    static void setupMapSelect(ui::UIObjectAcc& acc, GfMenuIDList* list);
    static void refreshPointSelect(ui::UIObjectAcc& acc, GfMenuZoneMapList* list, ui::UISelectObjList* selectList,
                                   unsigned int mapId);
    static void refreshPointText(ui::UIObjectAcc& acc, GfMenuZoneMapList* list, ui::UISelectObjList* selectList);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: it reads m_handle and m_iconFilter
    // through `this`. What it does: shows each of the 9 first icons of nd_lay_icon_node_tbl under "LAY_zonemap" when
    // its m_iconFilter bit is set; with fadeFirst the first (LAY_icon_mapjump) stays shown and gets alpha 1 or 0
    // instead. ZoneMapListener::reciveEvent, IconFilterListener::reciveEvent and seqGimik call it.
    void fn_710049D2A4(bool fadeFirst);
    // the floor shown: the zone list's selected map, or in group mode the selected point's "menuMapImage" (u16)
    unsigned int getFloor();
    // a copy of LAY_icon's IMG_zoneicon under the icon type's layout (nd_lay_icon_node_tbl), shown at pos with the
    // type's image, added to icons; 0 when icons is full
    static unsigned int setupIconTableSub(ui::UIObjectAcc& acc, mm::mtl::FixedVector<unsigned int, 256>& icons,
                                          unsigned int type, mm::Pnt<short> pos, mm::Vec2 scale);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its code sits in
    // gf_menu_obj_world_map's .text among GfMenuObjWorldMap's functions (after getFieldSkillFromGimmik). What it does:
    // true for a gimmick whose getGmkType() is 3 or 4 and whose bound bdat row's "ShopID" column (u16) is 222;
    // GfMenuMapInfo::postUpdate and fn_71003601DC pass it gimmicks.
    static bool fn_710049FB94(const gmk::AGmkBase* gmk);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its code sits in
    // gf_menu_obj_world_map's .text after setupIconTableSub. What it does: returns entry id of a guarded function-static
    // table of two colours, (1, 1, 1) and (0.78, 1, 0), entry 0 for an id past 1; GfMenuObjMinimap2::update calls it.
    static mm::Col3 fn_710049FD30(unsigned int id);
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
    // a floor image is streamed in: MainListener's close deletes m_floorImage from LAY_floor and clears both (the
    // names are not the original's)
    bool m_floorLoaded;
    mm::mtl::FixStr<32> m_floorImage;           // 0x69C
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
