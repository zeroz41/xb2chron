#include "classes/gf/GfMenuObjBtlchOrder.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameParty.h"
#include "gf/ArenaMenuInfo.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjOption.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuBtlchAdapter.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfGameUtilSaveData.h"
#include "gf/SDataOption.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuObjBtlchOrder::GfMenuObjBtlchOrder(unsigned int handle)
    : GfMenuObject(handle), m_idList(nullptr), m_driverList(nullptr), m_cursor(nullptr), m_context(nullptr), pad_48(0),
      m_difficulty(0), m_difficultyCount(0), m_limitDrivers(nullptr), m_limitBlades(nullptr), m_voice(nullptr),
      m_seq(this) {
    m_idList = GfMenuIDList::create();
    m_driverList = GfMenuDriverList::create();
    {
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = 3;
        m_driverList->setup(getAllocator(ALLOCATOR(0)), param);
    }
    m_difficulty = GfMenuObjOption::getDifficultyIndex(GfGameUtilSaveData::getValidOptionData()->m_soundUi.m_keyD);
    m_difficultyCount = GfMenuObjOption::getDifficultyMax();
    GfMenuReference::setReferenceBtlchDifficulty(
        static_cast<GFDIFF>(GfMenuObjOption::getDifficultyFromIndex(m_difficulty)));
    m_context = GfMenuCallContext::create();
    m_limitDrivers = GfMenuDriverList::create();
    {
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = 3;
        m_limitDrivers->setup(getAllocator(ALLOCATOR(0)), param);
    }
    m_limitBlades = GfMenuBladeList::create();
    {
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = 11;
        m_limitBlades->setup(getAllocator(ALLOCATOR(0)), param);
    }
    GfMenuObjOperationInfo::open(0, 0, 0, 0);
    GfMenuObjOperationInfo::setGuideDisp(false);
    m_seq.clear();
}

GfMenuObjBtlchOrder::~GfMenuObjBtlchOrder() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
}

void GfMenuObjBtlchOrder::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBtlchOrder::update() {
    m_seq.update();
    GfMenuObject::update();
}

// Proposed names, not the original's: the symbols leave them unnamed (lbl_7100B60738, lbl_7100B607B0). The colour
// of each difficulty's list item, and the animation of each option value.
static const char* const s_difficultyColors[] = {"txt_party_dmg_mul", "elemental03", "txt_enemy_dmg_mul", "tgt_cursor_lv02"};
static const char* s_difficultyAnims[] = {"normal", "easy", "hard", nullptr, "ultimate"};

// a table's entry (the name is not the original's). The original's tables are writable data (.data): clang 3.9 makes
// a static table constant unless its address is passed on before inlining (gf_bdat_rsc's _gfbrs::getSlot).
template <unsigned long N, typename Index>
inline const char* getEntry(const char* (&table)[N], Index index) {
    return table[index];
}

void GfMenuObjBtlchOrder::refreshDifficulty() {
    int value = GfMenuObjOption::getDifficultyFromIndex(m_difficulty);
    {
        ui::UIObjectAcc text(m_handle, "TXT_difficulty_index");
        if (GfDataBdat::getFP(0x169) == nullptr) {
            return;
        }
        unsigned short message = GfMenuObjUtil::getMsgIDFromList(0x169, m_difficulty + 1);
        ui::UIStr str(GfDataBdat::getFP(0x135), message);
        text.setText(str);
    }
    if ((unsigned int)value < 5) {
        const char* anim = getEntry(s_difficultyAnims, value);
        if (value != 3) {
        ui::UIObjectAcc list(m_handle, "IMG_list_base");
        ui::UIObjectAcc base(m_handle, "IMG_difficulty_base");
        list.startAnimation(anim, false);
        base.startAnimation(anim, false);
        }
    }
    {
        ui::UIObjectAcc item(m_handle, "IMG_list_item_base@01");
        item.setMulColor(s_difficultyColors[m_difficulty]);
    }
    GfMenuReference::setReferenceBtlchDifficulty(static_cast<GFDIFF>(value));
}

// whether challenge id's two conditions hold (inlined in updateInputEnable and canOrder; the name is not the
// original's)
static inline bool isConditionMet(unsigned int id) {
    ArenaMenuInfo info;
    if (!GfGameManager::getBattleArenaMenuInfo(info, id,
                                               static_cast<GFDIFF>(GfMenuReference::getReferenceBtlchDifficulty()))) {
        return false;
    }
    if (!info.m_flag12) {
        return false;
    }
    return info.m_text14.m_flag != 0;
}

void GfMenuObjBtlchOrder::updateInputEnable(unsigned int id) {
    ArenaMenuInfo info;
    if (GfGameManager::getBattleArenaMenuInfo(info, id,
                                              static_cast<GFDIFF>(GfMenuReference::getReferenceBtlchDifficulty()))) {
        ui::UIObjectAcc list(m_handle, "LAY_list");
        bool enable = info.m_kind == 3 ? false : isConditionMet(id);
        GfMenuObjOperationInfo::setActionEnable(list.m_handle, 9, enable);
    }
}

bool GfMenuObjBtlchOrder::canOrder(unsigned int id) {
    if (!isConditionMet(id)) {
        return false;
    }
    ArenaMenuInfo info;
    if (!GfGameManager::getBattleArenaMenuInfo(info, id,
                                               static_cast<GFDIFF>(GfMenuReference::getReferenceBtlchDifficulty()))) {
        return false;
    }
    if (info.m_kind == 3) {
        return true;
    }
    mm::mtl::FixedVector<unsigned short, 32> drivers;
    for (unsigned int i = 0; i < 3; i++) {
        unsigned int driver = GfGameParty::getDriverBdatId(i, PTPOS(0));
        if (driver != 0) {
            drivers.push_back(driver);
        }
    }
    if (info.m_valueA < drivers.size()) {
        return false;
    }
    for (unsigned long i = 0; i < drivers.size(); i++) {
        if (info.m_values1E[i] != 0 && drivers[i] != info.m_values1E[i]) {
            return false;
        }
    }
    return true;
}

bool GfMenuObjBtlchOrder::seqWaitVoice() {
    if (GfMenuObjUtil::isVoiceSkip()) {
        GfGameVoice::playStop(m_voice);
        m_voice = nullptr;
        return true;
    }
    if (m_voice != nullptr) {
        if (GfGameVoice::getResult(m_voice) >= 3) {
            m_voice = nullptr;
            return true;
        }
    }
    return false;
}

bool GfMenuObjBtlchOrder::seqClose() {
    ui::UIManager::get()->terminateLayer(m_fsLayer, true);
    return true;
}

bool GfMenuObjBtlchOrder::seqWaitTutorial() {
    return !GfMenuManager::isOpenBtlchTutorial();
}

bool GfMenuObjBtlchOrder::seqReturn() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObjUtil::setCommonFadeIn(main.searchChild("LAY_header"), 1, 1);
    GfMenuObjUtil::setCommonFadeIn(main.searchChild("LAY_list"), 1, 1);
    GfMenuObjUtil::setCommonFadeIn(main.searchChild("LAY_detail"), 1, 2);
    return true;
}

void GfMenuObjBtlchOrder::LimitListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        }
        break;
    case 8:
        if (event.m_param1 - 1U < 2) {
            ui::UIObjectAcc main(m_owner->m_handle, "LAY_main");
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObjUtil::setCommonFadeIn(main.searchChild("LAY_list"), 1, 1);
            GfMenuObjUtil::setCommonFadeIn(main.searchChild("LAY_detail"), 1, 2);
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
        }
        break;
    case 0x21:
        if (m_owner->m_limitDrivers->getSize() != 0) {
            GfMenuObjUtil::placeObjectHFromLayout(acc.m_handle, "LAY_limit_dr@%02d", m_owner->m_limitDrivers->getSize(),
                                         "limit_driver");
        }
        if (m_owner->m_limitBlades->getSize() != 0) {
            GfMenuObjUtil::placeObjectHFromLayout(acc.m_handle, "LAY_limit_bl@%02d", m_owner->m_limitBlades->getSize(),
                                         "limit_blade");
        }
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 1);
        break;
    case 0x22:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 1);
        break;
    }
}

}  // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBtlchOrder>(const mm::mtl::Delegate<bool()>*);
