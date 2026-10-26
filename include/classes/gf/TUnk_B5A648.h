#ifndef CLASSES_GF_TUNK_B5A648_H
#define CLASSES_GF_TUNK_B5A648_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace gf { class GfMenuIDList; }

namespace gf {
// table 0x7100B5A648; gf_menu_btlch_adapter.cpp's adapter (a battle challenge's data: the callbacks read
// GfGameManager::BattleChallengeRecord). The symbols leave the class unnamed (no RTTI; 1.0.0 has no such file:
// its gf_menu_blade_data_adapter.cpp sat here, with another table), so the name follows the table's address; the
// file name suggests GfMenuBtlChAdapter.
class TUnk_B5A648 : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    // a display callback and the plugin create makes for it (the table at 0x7100B5A670, in create's type order)
    struct TypeSetup {
        bool (TUnk_B5A648::*func)(unsigned int id);
        GfMenuAdapter::PluginSetup plugin;
    };
    TUnk_B5A648(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_update(), m_id(0), m_mode(6), m_converter(nullptr) {}
    virtual ~TUnk_B5A648();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    // Placeholder names (all of this class's functions): new in 3.0.1, nothing in 1.0.0's place names them. Members
    // because their code fills this unit and they work on this class's fields or its table.
    // fn_7100333BF4: a plugin of that type on the handle (an entry of the 0x20-byte table) and an adapter for it with
    // the challenge id, null without one (the adapters' create).
    static TUnk_B5A648* fn_7100333BF4(unsigned int handle, unsigned int type, unsigned int id, bool changed);
    // The callbacks (the table's entries 0..14): each fills a GfGameManager::BattleChallengeRecord for the id and
    // GfMenuReference::fn_7100369304()'s mode and shows one of its fields (false when there is none):
    // fn_7100333D34: text 0x1A1's message m_valueE; fn_7100333E14: whether m_rule.m_value0 is set;
    // fn_7100333EC4: number m_valueC - 1 (none for 0); fn_7100333F94: text 0x1A1's message m_value10;
    // fn_7100334074: text 0x1A1's message m_text14 (m_value18 when m_flag12 is set and m_text14's flag is not;
    // none when both are set); fn_710033417C: time m_value4 seconds; fn_7100334274: number m_value8 (none for 0);
    // fn_7100334340: m_value8 != 0 unless m_kind is 3; fn_7100334404: a non-empty m_listE0 unless m_kind is 3;
    // fn_71003344C0: m_valueA < 3, or any of m_value1E/20/22 set; fn_7100334594: number GfBdatBtl::fn_71001E968C(id);
    // fn_71003345D0: time m_rule.m_value0 seconds; fn_71003346C8: number m_rule.m_value8;
    // fn_710033478C: number m_rule.m_value4 when fn_7100334C1C(id) is not 0; fn_71003348D0: when m_flagAEC is set, the time
    // GfGameManager::fn_71002AC5D8()'s record's m_value30 seconds.
    bool fn_7100333D34(unsigned int id);
    bool fn_7100333E14(unsigned int id);
    bool fn_7100333EC4(unsigned int id);
    bool fn_7100333F94(unsigned int id);
    bool fn_7100334074(unsigned int id);
    bool fn_710033417C(unsigned int id);
    bool fn_7100334274(unsigned int id);
    bool fn_7100334340(unsigned int id);
    bool fn_7100334404(unsigned int id);
    bool fn_71003344C0(unsigned int id);
    bool fn_7100334594(unsigned int id);
    bool fn_71003345D0(unsigned int id);
    bool fn_71003346C8(unsigned int id);
    bool fn_710033478C(unsigned int id);
    bool fn_71003348D0(unsigned int id);
    // fn_71003349CC: an adapter whose id follows a list's entry at an index of the page shown (-1: its selected one)
    // (the TUnk_B5A850 converter); fn_7100334B10: one whose id follows a GfMenuReferenceNumber (TUnk_B5A878).
    static TUnk_B5A648* fn_71003349CC(unsigned int handle, unsigned int type, GfMenuIDList* list, int index,
                                      bool changed);
    static TUnk_B5A648* fn_7100334B10(unsigned int handle, unsigned int type,
                                      mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference, bool changed);
    // fn_7100334C1C: m_kind of the id's record (0 when there is none); nothing in the module calls it.
    static unsigned short fn_7100334C1C(unsigned int id);
    // the adapters' createFromCoverter (inline: no copy of its own)
    static inline TUnk_B5A648* createFromCoverter(unsigned int handle, unsigned int type, IConverter* converter,
                                                  bool changed);
    mm::mtl::Delegate<bool(unsigned int)> m_update;  // its type's callback; update passes m_id
    unsigned int m_id;  // the challenge; 0 shows nothing
    unsigned int m_mode;  // GfMenuReference::fn_7100369304()'s, 6 at first; update marks the adapter changed on a change
    IConverter* m_converter;  // update takes m_id from it; owned
};
}  // namespace gf

#endif
