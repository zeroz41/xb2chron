#ifndef CLASSES_GF_GFMENUGFOBJADAPTER_H
#define CLASSES_GF_GFMENUGFOBJADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// a base of gf::GfMenuGfObjAdapter no evidence names yet
class TUnk_B5C118 {
public:
    virtual void changeGfObj(gf::GF_OBJ_HANDLE*) = 0;
};
// a base of gf::GfMenuGfObjAdapter no evidence names yet
class TUnk_B5C130 {
public:
    virtual void changePartyDriver(unsigned char) = 0;
};
// a base of gf::GfMenuGfObjAdapter no evidence names yet
class TUnk_B5C148 {
public:
    virtual void changePartyBlade(unsigned char, unsigned char) = 0;
};
// table 0x7100B5C0D8; base at 0x0 GfMenuAdapter (create constructs it as one, then installs this table), base at 0x30 unknown (TUnk_B5C118), base at 0x38 unknown (TUnk_B5C130), base at 0x40 unknown (TUnk_B5C148)
class GfMenuGfObjAdapter : public ::gf::GfMenuAdapter, public TUnk_B5C118, public TUnk_B5C130, public TUnk_B5C148 {
public:
    class IConverter;
    class PartyBladeConverter;
    class PartyDriverConverter;
    class TargetEnemyConverter;
    // a display callback and the plugin create makes for it (the table at 0x7100B5C160, in create's type order)
    struct TypeSetup {
        bool (GfMenuGfObjAdapter::*func)(GF_OBJ_HANDLE*);
        GfMenuAdapter::PluginSetup plugin;
    };
    GfMenuGfObjAdapter(ui::UIObjectPlugin* plugin, bool managerFlag, bool changed)
        : GfMenuAdapter(plugin, managerFlag, changed), m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_update(),
          m_index(0), m_converter(nullptr) {}
    virtual ~GfMenuGfObjAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void changeGfObj(gf::GF_OBJ_HANDLE*);  // slot 3
    virtual void changePartyDriver(unsigned char);  // slot 4
    virtual void changePartyBlade(unsigned char, unsigned char);  // slot 5
    // a plugin of that type (an entry of its 0x20-byte table) on the handle and an adapter showing the object
    // (null without a plugin)
    static GfMenuGfObjAdapter* create(unsigned int handle, unsigned int type, GF_OBJ_HANDLE* obj, bool changed);
    // the same for a party driver's object, which a PartyDriverConverter follows
    static GfMenuGfObjAdapter* createFromPartyDriver(unsigned int handle, unsigned int type, unsigned char driver,
                                                     bool changed);
    // an adapter on the handle with a plugin of that type, whose GF object a PartyBladeConverter picks
    static GfMenuGfObjAdapter* createFromPartyBlade(unsigned int handle, unsigned int type, unsigned char driver,
                                                    int blade, bool changed, bool flag);
    // the same for the menu's target, which a TargetEnemyConverter follows
    static GfMenuGfObjAdapter* createFromTargetEnemy(unsigned int handle, unsigned int type, bool changed);
    bool update_NowHp(GF_OBJ_HANDLE* handle);
    bool update_Battle(GF_OBJ_HANDLE* handle);
    bool update_InfoBody(GF_OBJ_HANDLE* handle);
    bool update_InfoDisp(GF_OBJ_HANDLE* handle);
    bool update_InfoIcon(GF_OBJ_HANDLE* handle);
    bool update_TargetDisp(GF_OBJ_HANDLE* handle);
    bool update_AccessDisp(GF_OBJ_HANDLE* handle);
    bool update_EN_Lv(GF_OBJ_HANDLE* handle);
    bool update_EN_ArtsName(GF_OBJ_HANDLE* handle);
    bool update_EN_ArtsID(GF_OBJ_HANDLE* handle);
    bool update_EN_ElemComboName(GF_OBJ_HANDLE* handle);
    bool update_EN_Aggressive(GF_OBJ_HANDLE* handle);
    bool update_EN_Link(GF_OBJ_HANDLE* handle);
    bool update_EN_Arts(GF_OBJ_HANDLE* handle);
    bool update_EN_FightComboIcon(GF_OBJ_HANDLE* handle);
    bool update_EN_FightComboName(GF_OBJ_HANDLE* handle);
    bool update_EN_FightComboTime(GF_OBJ_HANDLE* handle);
    bool update_EN_FightComboSuspend(GF_OBJ_HANDLE* handle);
    bool update_EN_ElemComboLv(GF_OBJ_HANDLE* handle);
    bool update_EN_ElemComboTime(GF_OBJ_HANDLE* handle);
    bool update_EN_ElemComboState(GF_OBJ_HANDLE* handle);
    bool update_EN_ElemComboAttrIcon(GF_OBJ_HANDLE* handle);
    bool update_EN_ElemComboAttrCol(GF_OBJ_HANDLE* handle);
    bool update_EN_ElemComboAttrPtn(GF_OBJ_HANDLE* handle);
    bool update_EN_ElemComboSuspend(GF_OBJ_HANDLE* handle);
    bool update_EN_WeakAttrIcon(GF_OBJ_HANDLE* handle);
    bool update_EN_WeakAttrColor(GF_OBJ_HANDLE* handle);
    bool update_EN_ResAttrOn(GF_OBJ_HANDLE* handle);
    bool update_EN_ResAttrTarget(GF_OBJ_HANDLE* handle);
    bool update_EN_ResAttrBurst(GF_OBJ_HANDLE* handle);
    bool update_EN_ResAttrHP(GF_OBJ_HANDLE* handle);
    bool update_EN_ElemEffID(GF_OBJ_HANDLE* handle);
    bool update_EN_TypeIcon(GF_OBJ_HANDLE* handle);
    bool update_EN_Scout(GF_OBJ_HANDLE* handle);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (1.0.0 goes from update_EN_Scout to
    // update_BL_Kizuna). Members because they are entries 34 and 35 of this class's TypeSetup table (disp
    // plugins). What they do: when the object is an enemy, return its property's byte at 0x154 / 0x155 (the
    // second only when GfMenuObjUtil::fn_710048FD30(1) or (3)).
    bool fn_710033FB0C(GF_OBJ_HANDLE* handle);
    bool fn_710033FB70(GF_OBJ_HANDLE* handle);
    bool update_BL_Kizuna(GF_OBJ_HANDLE* handle);
    bool update_BL_Special(GF_OBJ_HANDLE* handle);
    bool update_BL_SpecialLv(GF_OBJ_HANDLE* handle);
    bool update_BL_ChangeRecast(GF_OBJ_HANDLE* handle);
    bool update_BL_ChangeRecast2(GF_OBJ_HANDLE* handle);
    bool update_BL_DispCurrent(GF_OBJ_HANDLE* handle);
    bool update_BL_DispComboReady(GF_OBJ_HANDLE* handle);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (1.0.0's callbacks end with
    // update_BL_DispComboReady). Members because they are entries 43 and 44 of this class's TypeSetup table.
    // What they do, when GfMenuObjUtil::fn_710048FD30(3): fn_7100340094, for an object of type 6, sets the number
    // to 1 for fn_710024DD94(its BDAT id) 1 or 3, to 0 for 0 or 2 when fn_71002D9B5C(handle);
    // fn_7100340154 sets the number to the UI HP plus the int at 0x8 of the property's character, its max to the
    // UI max HP.
    bool fn_7100340094(GF_OBJ_HANDLE* handle);
    bool fn_7100340154(GF_OBJ_HANDLE* handle);
    GF_OBJ_HANDLE* m_handle;  // the object shown (-1: none); changeGfObj sets it (the name is not the original's)
    // create's: the table entry's callback, called with m_handle (the name is not the original's)
    mm::mtl::Delegate<bool(GF_OBJ_HANDLE*)> m_update;
    // which one of its kind it shows: create clears it, callers set it (GfMenuObjSpecialGauge's gauge levels)
    // (the name is not the original's)
    unsigned int m_index;
    unsigned char pad_74[4];
    // where update takes the object from (createFrom*'s); the destructor deletes it (the name is not the
    // original's)
    IConverter* m_converter;
};
}  // namespace gf

#endif
