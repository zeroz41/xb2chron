#include "classes/gf/TUnk_B5A648.h"
#include "classes/gf/TUnk_B5A648/IConverter.h"
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
// settings for each adapter type, in fn_7100333BF4's index order.
static TUnk_B5A648::TypeSetup s_typeSetups[] = {
    {&TUnk_B5A648::fn_7100333D34, {2, 0, 0}},
    {&TUnk_B5A648::fn_7100333E14, {3, 0, 0}},
    {&TUnk_B5A648::fn_7100333EC4, {0, 0, 9}},
    {&TUnk_B5A648::fn_7100333F94, {2, 0, 0}},
    {&TUnk_B5A648::fn_7100334074, {2, 0, 0}},
    {&TUnk_B5A648::fn_710033417C, {7, 4, 0}},
    {&TUnk_B5A648::fn_7100334274, {0, 0, 99}},
    {&TUnk_B5A648::fn_7100334340, {3, 0, 0}},
    {&TUnk_B5A648::fn_7100334404, {3, 0, 0}},
    {&TUnk_B5A648::fn_71003344C0, {3, 0, 0}},
    {&TUnk_B5A648::fn_7100334594, {0, 0, 99}},
    {&TUnk_B5A648::fn_71003345D0, {7, 4, 0}},
    {&TUnk_B5A648::fn_71003346C8, {0, 0, 99999}},
    {&TUnk_B5A648::fn_710033478C, {0, 0, 99999}},
    {&TUnk_B5A648::fn_71003348D0, {7, 4, 0}},
};

TUnk_B5A648::~TUnk_B5A648() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

TUnk_B5A648* TUnk_B5A648::fn_7100333BF4(unsigned int handle, unsigned int type, unsigned int id, bool changed) {
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
    TUnk_B5A648* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B5A648(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_id = id;
    plugin->release();
    return adapter;
}

bool TUnk_B5A648::fn_7100333D34(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0x1A1), record.m_valueE);
    setText(text);
    return true;
}

bool TUnk_B5A648::fn_7100333E14(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
        return false;
    }
    return record.m_rule.m_value0 != 0;
}

bool TUnk_B5A648::fn_7100333EC4(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
        return false;
    }
    if (record.m_valueC == 0) {
        return false;
    }
    setNumber(record.m_valueC - 1);
    return true;
}

bool TUnk_B5A648::fn_7100333F94(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0x1A1), record.m_value10);
    setText(text);
    return true;
}

bool TUnk_B5A648::fn_7100334074(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
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

bool TUnk_B5A648::fn_710033417C(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
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

bool TUnk_B5A648::fn_7100334274(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
        return false;
    }
    if (record.m_value8 == 0) {
        return false;
    }
    setNumber(record.m_value8);
    return true;
}

bool TUnk_B5A648::fn_7100334340(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
        return false;
    }
    if (record.m_kind == 3) {
        return false;
    }
    return record.m_value8 != 0;
}

bool TUnk_B5A648::fn_7100334404(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
        return false;
    }
    if (record.m_kind == 3) {
        return false;
    }
    return !record.m_lists.m_listE0.empty();
}

bool TUnk_B5A648::fn_71003344C0(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
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

bool TUnk_B5A648::fn_7100334594(unsigned int id) {
    setNumber(GfBdatBtl::sys()->fn_71001E968C(id));
    return true;
}

bool TUnk_B5A648::fn_71003345D0(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
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

bool TUnk_B5A648::fn_71003346C8(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
        return false;
    }
    setNumber(record.getRule().m_value8);
    return true;
}

bool TUnk_B5A648::fn_710033478C(unsigned int id) {
    bool found;
    {
        GfGameManager::BattleChallengeRecord record;
        found = GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304()) && record.m_kind != 0;
    }
    if (!found) {
        return false;
    }
    GfGameManager::BattleChallengeRecord record;
    GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304());
    setNumber(record.m_rule.m_value4);
    return true;
}

bool TUnk_B5A648::fn_71003348D0(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304()) || !record.m_flagAEC) {
        return false;
    }
    unsigned int seconds = GfGameManager::fn_71002AC5D8()->m_value30;
    ui::uiDateTime time = {};
    time.minute = seconds / 60;
    time.sec = seconds % 60;
    setTime(time);
    return true;
}

TUnk_B5A648* TUnk_B5A648::createFromCoverter(unsigned int handle, unsigned int type, IConverter* converter,
                                             bool changed) {
    TUnk_B5A648* adapter = fn_7100333BF4(handle, type, converter->fn_7100334D68(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

TUnk_B5A648* TUnk_B5A648::fn_71003349CC(unsigned int handle, unsigned int type, GfMenuIDList* list, int index,
                                        bool changed) {
#line 173
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B5A850(list, index);
    return createFromCoverter(handle, type, converter, changed);
}

TUnk_B5A648* TUnk_B5A648::fn_7100334B10(unsigned int handle, unsigned int type,
                                        mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference, bool changed) {
#line 182
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B5A878(reference);
    return createFromCoverter(handle, type, converter, changed);
}

unsigned short TUnk_B5A648::fn_7100334C1C(unsigned int id) {
    GfGameManager::BattleChallengeRecord record;
    if (!GfGameManager::fn_71002AC60C(&record, id, GfMenuReference::fn_7100369304())) {
        return 0;
    }
    return record.m_kind;
}

void TUnk_B5A648::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int id = m_converter->fn_7100334D68();
        if (m_id != id) {
            m_id = id;
            setChange();
        }
    }
    if (m_mode != GfMenuReference::fn_7100369304()) {
        m_mode = GfMenuReference::fn_7100369304();
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
