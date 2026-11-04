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
// GfGameManager::BattleChallengeRecord). 2.0.0's symbols name it (no RTTI; 1.0.0 has no such file: its
// gf_menu_blade_data_adapter.cpp sat here, with another table).
class GfMenuBtlchAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ListConverter;
    class ReferenceConverter;
    // a display callback and the plugin create makes for it (the table at 0x7100B5A670, in create's type order)
    struct TypeSetup {
        bool (GfMenuBtlchAdapter::*func)(unsigned int id);
        GfMenuAdapter::PluginSetup plugin;
    };
    GfMenuBtlchAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_update(), m_id(0), m_mode(6), m_converter(nullptr) {}
    virtual ~GfMenuBtlchAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    // 2.0.0's symbols name them. create: a plugin of that type on the handle (an entry of the 0x20-byte table) and an
    // adapter for it with the challenge id, null without one (the adapters' create).
    static GfMenuBtlchAdapter* create(unsigned int handle, unsigned int type, unsigned int id, bool changed);
    // The callbacks (the table's entries 0..14): each fills a GfGameManager::BattleChallengeRecord for the id and
    // GfMenuReference::getReferenceBtlchDifficulty()'s mode and shows one of its fields (false when there is none):
    // update_TextTitle: text 0x1A1's message m_valueE; update_DispComplete: whether m_rule.m_value0 is set;
    // update_NumDifficulty: number m_valueC - 1 (none for 0); update_TextSummary: text 0x1A1's message m_value10;
    // update_TextNotAvailable: text 0x1A1's message m_text14 (m_value18 when m_flag12 is set and m_text14's flag is not;
    // none when both are set); update_TimeLimit: time m_value4 seconds; update_NumLimitLv: number m_value8 (none for 0);
    // update_DispLimitLv: m_value8 != 0 unless m_kind is 3; update_DispWpnLimit: a non-empty m_listE0 unless m_kind is 3;
    // update_DispPartyLimit: m_valueA < 3, or any of m_value1E/20/22 set; update_NumWaveCount: number GfBdatBtl::getBTL_ChBtlWave(id);
    // update_TimeRecord: time m_rule.m_value0 seconds; update_NumRecordEcube: number m_rule.m_value8;
    // update_NumRecordScore: number m_rule.m_value4 when getScoreType(id) is not 0; update_TimeClear: when m_flagAEC is set, the time
    // GfGameManager::getBattleArenaMenuInfo()'s record's m_value30 seconds.
    bool update_TextTitle(unsigned int id);
    bool update_DispComplete(unsigned int id);
    bool update_NumDifficulty(unsigned int id);
    bool update_TextSummary(unsigned int id);
    bool update_TextNotAvailable(unsigned int id);
    bool update_TimeLimit(unsigned int id);
    bool update_NumLimitLv(unsigned int id);
    bool update_DispLimitLv(unsigned int id);
    bool update_DispWpnLimit(unsigned int id);
    bool update_DispPartyLimit(unsigned int id);
    bool update_NumWaveCount(unsigned int id);
    bool update_TimeRecord(unsigned int id);
    bool update_NumRecordEcube(unsigned int id);
    bool update_NumRecordScore(unsigned int id);
    bool update_TimeClear(unsigned int id);
    // createFromList: an adapter whose id follows a list's entry at an index of the page shown (-1: its selected one)
    // (ListConverter); createFromReference: one whose id follows a GfMenuReferenceNumber (ReferenceConverter).
    static GfMenuBtlchAdapter* createFromList(unsigned int handle, unsigned int type, GfMenuIDList* list, int index,
                                      bool changed);
    static GfMenuBtlchAdapter* createFromReference(unsigned int handle, unsigned int type,
                                      mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference, bool changed);
    // getScoreType: m_kind of the id's record (0 when there is none); nothing in the module calls it.
    static unsigned short getScoreType(unsigned int id);
    // the adapters' createFromCoverter (inline: no copy of its own)
    static inline GfMenuBtlchAdapter* createFromCoverter(unsigned int handle, unsigned int type, IConverter* converter,
                                                  bool changed);
    mm::mtl::Delegate<bool(unsigned int)> m_update;  // its type's callback; update passes m_id
    unsigned int m_id;  // the challenge; 0 shows nothing
    unsigned int m_mode;  // GfMenuReference::getReferenceBtlchDifficulty()'s, 6 at first; update marks the adapter changed on a change
    IConverter* m_converter;  // update takes m_id from it; owned
};
}  // namespace gf

#endif
