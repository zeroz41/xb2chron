#include "classes/gf/GfMenuObjNamedDialog.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfGameUtil.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuObjNamedList.h"
#include "classes/gf/GfMenuObjOption.h"
#include "classes/ui/UIEventManager.h"
#include "gf/GfGameUtilSaveData.h"
#include "gf/SDataOption.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuObjNamedDialog::GfMenuObjNamedDialog(unsigned int handle) : GfMenuObject(handle), m_list(nullptr) {
    m_list = GfMenuIDList::create();
}

GfMenuObjNamedDialog::~GfMenuObjNamedDialog() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

void GfMenuObjNamedDialog::open(unsigned int row) {
    bool enable = GfMenuObjUtil::isValidExpansion(3) ? GfGameManager::isClearGame() : GfGameManager::isEnableNamedRecord();
    if (!enable) {
        return;
    }
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8A));
    if (acc.m_object != nullptr) {
        int index = GfGameUtil::getNamedListIndex(row);
        if (index != 0) {
            GfMenuObject::sendOpenEvent(acc.m_handle, index, 0.0f);
        }
    }
}

void GfMenuObjNamedDialog::close() {
    bool enable = GfMenuObjUtil::isValidExpansion(3) ? GfGameManager::isClearGame() : GfGameManager::isEnableNamedRecord();
    if (!enable) {
        return;
    }
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8A));
    if (acc.m_object != nullptr) {
        GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
    }
}

void GfMenuObjNamedDialog::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x8A, acc.m_handle);
#line 107
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    {
        ui::UIListInfoBase::SetupParam param;
        m_list->setup(getAllocator(ALLOCATOR(0)), param);
    }
    GfMenuAdapterManager::beginAddAfter();
    GfMenuCharDataAdapter::createFromNamedList(acc.searchChild("TXT_en_name"), 2, m_list, 0, false);
    GfMenuCharDataAdapter::createFromNamedList(acc.searchChild("TXT_en_lv_num"), 0x5C, m_list, 0, false);
    GfMenuCharDataAdapter::createFromNamedList(acc.searchChild("TXT_en_record_time"), 0x62, m_list, 0, false);
    GfMenuAdapterManager::endAddAfter();
    GfMenuObject::initialize();
}

void GfMenuObjNamedDialog::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjNamedDialog::update() {
    GfMenuObject::update();
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B638D0). The animation of each
// difficulty, as gf_menu_obj_named_list's s_difficultyAnims.
static const char* s_difficultyAnims[] = {"normal", "easy", "hard", nullptr, "ultimate"};

// a table's entry (the name is not the original's). The original's table is writable data (.data): clang 3.9 makes
// a static table constant unless its address is passed on before inlining (gf_menu_obj_btlch_order's getEntry).
template <unsigned long N, typename Index>
inline const char* getEntry(const char* (&table)[N], Index index) {
    return table[index];
}

void GfMenuObjNamedDialog::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state = 0;
        break;
    case 3:
        if (event.m_param0 == 2) {
            m_owner->m_list->clear();
        }
        break;
    case 0x21: {
        unsigned int row = event.m_param0;
        if (row == 0) {
            break;
        }
        m_owner->m_list->clear();
        m_owner->m_list->addContents(MenuID{row, 0});
        unsigned char difficulty = GfGameUtilSaveData::getValidOptionData()->m_soundUi.m_keyD;
        unsigned int index = GfMenuObjOption::getDifficultyIndex(difficulty);
        {
            ui::UIObjectAcc text(acc.m_handle, "TXT_en_diff");
            if (GfDataBdat::getFP(0x169) == nullptr) {
                break;
            }
            unsigned short message = GfMenuObjUtil::getMsgIDFromList(0x169, index + 1);
            ui::UIStr str(GfDataBdat::getFP(0x135), message);
            text.setText(str);
        }
        if (difficulty < 5 && difficulty != 3) {
            const char* anim = getEntry(s_difficultyAnims, static_cast<signed char>(difficulty));
            ui::UIObjectAcc base(acc.m_handle, "IMG_en_diff_base");
            base.startAnimation(anim, false);
        }
        acc.setDispChild(GfMenuObjNamedList::isDefeated(row), "LAY_en_record");
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 0);
        m_state = 1;
        break;
    }
    case 0x22:
        if (m_state == 1) {
            GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
            m_state = 0;
        }
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
