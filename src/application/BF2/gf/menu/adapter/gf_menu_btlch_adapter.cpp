#include "classes/gf/GfMenuBtlchAdapter.h"
#include "classes/gf/GfMenuBtlchAdapter/IConverter.h"
#include "classes/gf/TUnk_B5A850.h"
#include "classes/gf/TUnk_B5A878.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "ui/UIStr.h"
#include "ui/uiDateTime.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B5A670). The display callback and plugin
// settings for each adapter type, in create's index order.
static GfMenuBtlchAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuBtlchAdapter::update_TextTitle, {2, 0, 0}},
    {&GfMenuBtlchAdapter::update_DispComplete, {3, 0, 0}},
    {&GfMenuBtlchAdapter::update_NumDifficulty, {0, 0, 9}},
    {&GfMenuBtlchAdapter::update_TextSummary, {2, 0, 0}},
    {&GfMenuBtlchAdapter::update_TextNotAvailable, {2, 0, 0}},
    {&GfMenuBtlchAdapter::update_TimeLimit, {7, 4, 0}},
    {&GfMenuBtlchAdapter::update_NumLimitLv, {0, 0, 99}},
    {&GfMenuBtlchAdapter::update_DispLimitLv, {3, 0, 0}},
    {&GfMenuBtlchAdapter::update_DispWpnLimit, {3, 0, 0}},
    {&GfMenuBtlchAdapter::update_DispPartyLimit, {3, 0, 0}},
    {&GfMenuBtlchAdapter::update_NumWaveCount, {0, 0, 99}},
    {&GfMenuBtlchAdapter::update_TimeRecord, {7, 4, 0}},
    {&GfMenuBtlchAdapter::update_NumRecordEcube, {0, 0, 99999}},
    {&GfMenuBtlchAdapter::update_NumRecordScore, {0, 0, 99999}},
    {&GfMenuBtlchAdapter::update_TimeClear, {7, 4, 0}},
};

GfMenuBtlchAdapter::~GfMenuBtlchAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuBtlchAdapter* GfMenuBtlchAdapter::create(unsigned int handle, unsigned int type, unsigned int id, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 157
    GfMenuBtlchAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuBtlchAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_id = id;
    plugin->release();
    return adapter;
}

bool GfMenuBtlchAdapter::update_TextTitle(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0x1A1), record.m_valueE);
    setText(text);
    return true;
}

bool GfMenuBtlchAdapter::update_DispComplete(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return false;
    }
    return record.m_rule.m_value0 != 0;
}

bool GfMenuBtlchAdapter::update_NumDifficulty(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return false;
    }
    if (record.m_valueC == 0) {
        return false;
    }
    setNumber(record.m_valueC - 1);
    return true;
}

bool GfMenuBtlchAdapter::update_TextSummary(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0x1A1), record.m_value10);
    setText(text);
    return true;
}

bool GfMenuBtlchAdapter::update_TextNotAvailable(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return false;
    }
    GfGameManager::BattleChallengeRecord::Text text14 = record.getText14();
    unsigned int message;
    if (record.m_flag12) {
        if (text14.m_flag != 0) {
            return false;
        }
        message = record.m_value18;
    } else {
        message = text14.m_message;
    }
    ui::UIStr text(GfDataBdat::getFP(0x1A1), message);
    setText(text);
    return true;
}

bool GfMenuBtlchAdapter::update_TimeLimit(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return false;
    }
    unsigned int seconds = record.m_value4;
    if (seconds == 0) {
        return false;
    }
    ui::uiDateTime time = {};
    time.minute = seconds / 60;
    time.sec = seconds % 60;
    setTime(time);
    return true;
}

bool GfMenuBtlchAdapter::update_NumLimitLv(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return false;
    }
    if (record.m_value8 == 0) {
        return false;
    }
    setNumber(record.m_value8);
    return true;
}

bool GfMenuBtlchAdapter::update_DispLimitLv(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return false;
    }
    if (record.m_kind == 3) {
        return false;
    }
    return record.m_value8 != 0;
}

bool GfMenuBtlchAdapter::update_DispWpnLimit(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return false;
    }
    if (record.m_kind == 3) {
        return false;
    }
    return !record.m_lists.m_listE0.empty();
}

bool GfMenuBtlchAdapter::update_DispPartyLimit(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return false;
    }
    if (record.m_valueA < 3) {
        return true;
    }
    for (int i = 0; i < 3; i++) {
        if (record.m_values1E[i] != 0) {
            return true;
        }
    }
    return false;
}

bool GfMenuBtlchAdapter::update_NumWaveCount(unsigned int id) {
    setNumber(GfBdatBtl::sys()->getBTL_ChBtlWave(id));
    return true;
}

bool GfMenuBtlchAdapter::update_TimeRecord(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return false;
    }
    unsigned int seconds = record.m_rule.m_value0;
    if (seconds == 0) {
        return false;
    }
    ui::uiDateTime time = {};
    time.minute = seconds / 60;
    time.sec = seconds % 60;
    setTime(time);
    return true;
}

bool GfMenuBtlchAdapter::update_NumRecordEcube(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return false;
    }
    setNumber(record.getRule().m_value8);
    return true;
}

bool GfMenuBtlchAdapter::update_NumRecordScore(unsigned int id) {
    bool found;
    {
        GfGameManager::BattleChallengeRecord record;
        found = GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty()) && record.m_kind != 0;
    }
    if (!found) {
        return false;
    }
    GfGameManager::BattleChallengeRecord record;
    GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty());
    setNumber(record.m_rule.m_value4);
    return true;
}

bool GfMenuBtlchAdapter::update_TimeClear(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty()) || !record.m_flagAEC) {
        return false;
    }
    unsigned int seconds = GfGameManager::getBattleArenaMenuInfo()->m_value30;
    ui::uiDateTime time = {};
    time.minute = seconds / 60;
    time.sec = seconds % 60;
    setTime(time);
    return true;
}

GfMenuBtlchAdapter* GfMenuBtlchAdapter::createFromCoverter(unsigned int handle, unsigned int type, IConverter* converter,
                                             bool changed) {
    GfMenuBtlchAdapter* adapter = create(handle, type, converter->fn_7100334D68(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuBtlchAdapter* GfMenuBtlchAdapter::createFromList(unsigned int handle, unsigned int type, GfMenuIDList* list, int index,
                                        bool changed) {
#line 173
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B5A850(list, index);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuBtlchAdapter* GfMenuBtlchAdapter::createFromReference(unsigned int handle, unsigned int type,
                                        mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference, bool changed) {
#line 182
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B5A878(reference);
    return createFromCoverter(handle, type, converter, changed);
}

unsigned short GfMenuBtlchAdapter::getScoreType(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::getReferenceBtlchDifficulty())) {
        return 0;
    }
    return record.m_kind;
}

void GfMenuBtlchAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int id = m_converter->fn_7100334D68();
        if (m_id != id) {
            m_id = id;
            setChange();
        }
    }
    if (m_mode != GfMenuReference::getReferenceBtlchDifficulty()) {
        m_mode = GfMenuReference::getReferenceBtlchDifficulty();
        setChange();
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        if (m_id == 0) {
            setDisp(false);
        } else {
            setDisp(m_update(m_id));
        }
        m_flags &= ~1;
    }
}

}  // namespace gf
