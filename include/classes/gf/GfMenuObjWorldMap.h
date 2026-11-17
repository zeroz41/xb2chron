#ifndef CLASSES_GF_GFMENUOBJWORLDMAP_H
#define CLASSES_GF_GFMENUOBJWORLDMAP_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfGmkLocatorAtlas.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuSequence.h"
#include "classes/ui/UIManager.h"
#include "ui/EventData.h"
#include "mm/Aabb.h"
#include "mm/Col3.h"
#include "mm/Pnt.h"
#include "mm/Vec2.h"
#include "mm/mtl/Array.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"

namespace gmk { class AGmkBase; }
namespace ui { class UIObjectAcc; class UIListInfoBase; class UISelectObjList; class UICtrlCursorSelect; class UICtrlFrame; }

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
    // 8 bytes: Array<MapJumpInfo>::reserve allocates size * 8 and constructs each element with (0, -1), as
    // seqTexDelete's reset writes them; trivially destructible (the destructor frees the array without destroying
    // elements). What the fields hold is not known yet.
    struct MapJumpInfo {
        MapJumpInfo() : pad_0(0), pad_4(-1) {}
        unsigned int pad_0;
        int pad_4;
    };

    GfMenuObjWorldMap(unsigned int handle);
    virtual ~GfMenuObjWorldMap();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name it. What it does: true when the 1-bit local game flag 51161 + id is 1;
    // GfMenuZoneMapAdapter::update_ZonePointName passes its map id and shows the point's name only then (else
    // GfDataBdat 0xF5's row 0x67C). isEnableJump inlines it.
    static bool isOpenLandmark(unsigned int id);
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
        if (flag) {
            param.m_startFlag1 = true;
        }
        int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    // 2.0.0's sendEvent (0x71005D16F0; out of line there, inlined in 3.0.1): a UI event of the type, with its first
    // parameter, requested of the object after the frames (at 30 a second)
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param, unsigned int frames) {
        ui::EventData ev;
        ev.m_type = type;
        ev.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, ev, frames * (1.0f / 30.0f));
    }
    // 2.0.0's ctrlScrollBar (0x71005D36C0; out of line there, inlined in 3.0.1): fades the scroll bar in (method 1)
    // or out (method 2) over 0.3 s
    static void ctrlScrollBar(unsigned int handle, bool out) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = out ? 2 : 1;
        param.m_time = 0.3f;
        param.m_curve = 1;
        GfMenuObjUtil::startCtrl(handle, param, nullptr);
    }
    // 2.0.0's symbols name it. What it does: clears the list, then adds each map of the selectable-map table whose
    // chkMapCond holds: maps 52 and 53 when add-on menu layer 3 is usable (GfMenuObjUtil::isValidExpansion(3)), else
    // 3-6, 9-16, 18, 20 and 21.
    static void setupMapList(GfMenuIDList* list);
    // fills list with the zone rows (GfDataBdat 0x17B) whose include_map is the referenced world map's resource and
    // whose condition does not hold, when a gimmick row of the zone's menuGroup has a MAPJUMPID and is on the current
    // floor or its jump flag is set; true when it holds any
    bool setupZoneList(GfMenuZoneMapList* list);
    static void refreshMapSelect(ui::UIObjectAcc& acc, GfMenuIDList* list, ui::UISelectObjList* selectList, int index);
    // 2.0.0's symbols name it. What it does: setupPointSelect's work for the zone list (9 TXT_zonename_@NN adapters
    // with their LAY_zonespot@NN rows, IMG_sonestay_@NN hidden, the zone scroll bar), and the scroll bar synced to
    // LAY_zone_focus when add-on menu layer 3 is usable.
    static void setupZoneSelect(ui::UIObjectAcc& acc, GfMenuZoneMapList* list);
    // starts each of the list's first count objects' return control (the selected one's move back, the others'
    // fade-in motion) and gives them display priority 8; the last control's slot, -1 for none
    static int ctrlGroupReturn(ui::UISelectObjList* list, unsigned int count);
    static void setupPointSelect(ui::UIObjectAcc& acc, GfMenuZoneMapList* list);
    static bool chkMapCond(unsigned int mapId, mm::Pnt<short>* pos);
    static void setupMapSelect(ui::UIObjectAcc& acc, GfMenuIDList* list);
    static void refreshPointSelect(ui::UIObjectAcc& acc, GfMenuZoneMapList* list, ui::UISelectObjList* selectList,
                                   unsigned int mapId);
    static void refreshPointText(ui::UIObjectAcc& acc, GfMenuZoneMapList* list, ui::UISelectObjList* selectList);
    // 2.0.0's symbols name it. What it does: shows each of the 9 first icons of nd_lay_icon_node_tbl under
    // "LAY_zonemap" when its m_iconFilter bit is set; with fadeFirst the first (LAY_icon_mapjump) stays shown and gets
    // alpha 1 or 0 instead. ZoneMapListener::reciveEvent, IconFilterListener::reciveEvent and seqGimik call it.
    void updateDispIconNode(bool fadeFirst);
    // fills tables with the icons of list's points (seqGimik passes m_iconTables and m_pointList)
    void setupIconTable(ui::UIObjectAcc& acc, mm::mtl::FixedArray<mm::mtl::FixedVector<unsigned int, 256>, 10>& tables,
                        GfMenuZoneMapList* list, mm::Pnt<short> offset, mm::Vec2 scale, mm::Pnt<short> center,
                        bool curMap);
    // the floor shown: the zone list's selected map, or in group mode the selected point's "menuMapImage" (u16)
    unsigned int getFloor();
    // a copy of LAY_icon's IMG_zoneicon under the icon type's layout (nd_lay_icon_node_tbl), shown at pos with the
    // type's image, added to icons; 0 when icons is full
    static unsigned int setupIconTableSub(ui::UIObjectAcc& acc, mm::mtl::FixedVector<unsigned int, 256>& icons,
                                          unsigned int type, mm::Pnt<short> pos, mm::Vec2 scale);
    // 2.0.0's symbols name it. What it does: true for a gimmick whose getGmkType() is 3 or 4 and whose bound bdat
    // row's "ShopID" column (u16) is 222; GfMenuMapInfo::postUpdate and GfMenuMapInfo::convGmkToIcon pass it gimmicks.
    static bool isShopMinstrel(const gmk::AGmkBase& gmk);
    // 2.0.0's symbols name it. What it does: returns entry id of a guarded function-static table of two colours, (1, 1,
    // 1) and (0.78, 1, 0), entry 0 for an id past 1; GfMenuObjMinimap2::update calls it.
    static mm::Col3 getShopIconColor(unsigned int id);
    static bool isEnableJump(const MenuZoneMapInfo& info);
    static void getFloorAABB(unsigned int mapId, unsigned int floor, mm::Aabb& aabb, mm::Pnt<short>& center);
    int getTotalFieldSkillLv(unsigned int fieldSkill);
    static unsigned int getFieldSkillFromGimmik(unsigned char* bdat, unsigned int row, unsigned int type);
    void refreshIconFilter();
    // when the floor shown changed: queues the floor image's reload (seqTexDelete .. seqNext)
    void loadTex();
    bool seqTexDelete();
    bool seqTexDeleteWait();
    bool seqTexLoad();
    bool seqTexLoadWait();
    bool seqTexDraw();
    bool seqGimik();
    bool seqNext();

    // the names of the members are not the original's; types from initialize's create calls
    GfMenuIDList* m_mapList;                    // 0x28
    ui::UISelectObjList* m_mapSelectList;       // 0x30
    bool pad_38;                                // the constructor sets it
    GfMenuZoneMapList* m_zoneList;              // 0x40
    ui::UISelectObjList* m_zoneSelectList;      // 0x48
    GfMenuSequence<GfMenuObjWorldMap, 8> m_seq;  // 0x50
    // seqNext's frame control over LAY_frame (the destructor releases it twice; the name is not the original's)
    ui::UICtrlFrame* m_frame;                   // 0x2E0
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
    // setupIconTable's offset, scale and center: an icon's position is offset + scale * 2 * (world - center)
    // (seqGimik passes them; the names are not the original's)
    mm::Pnt<short> m_iconOffset;                // 0x2F1C
    mm::Vec2 m_iconScale;                       // 0x2F20 (16 bytes)
    mm::Pnt<short> m_iconCenter;                // 0x2F30
    unsigned char pad_2F34[0x2C];
    bool pad_2F60;
    bool pad_2F61;
    GfMenuCallContext* m_context;               // 0x2F68
    bool pad_2F70;
    unsigned char* m_gmkBdat;                   // 0x2F78: initialize's Bdat::getFP of the gimmick sheet
    unsigned short m_floor;                     // 0x2F80: the floor loadTex last loaded (the name is not the original's)
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
