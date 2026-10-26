#include "gf/SDataOption.h"
#include "gf/GfGameUtilSaveData.h"
#include "classes/gf/GfMenuObjOption.h"
#include "classes/gf/GfMenuObjOption/MainListener.h"
#include "classes/gf/GfMenuObjOption/SubMenuListener.h"
#include "classes/gf/GfMenuObjOption/ItemListListener.h"
#include "classes/gf/GfMenuObjOption/ItemSettingListener.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfReqCommand.h"
#include "classes/gf/GfReqManager.h"
#include "classes/gf/GfMenuObjFade.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "ui/UIStr.h"
#include "ui/EventData.h"

namespace gf {

namespace {
// Proposed names, not the original's: the symbols leave them unnamed (lbl_7100B63DC0; the compiler merges the two, s_difficultyListAll at +8).
// The difficulty values GfMenuObjOption's statics list: 2 of them, or 4 once the game is cleared or the save data
// allows it
int s_difficultyList[2] = {1, 0};
int s_difficultyListAll[4] = {1, 0, 2, 4};
}  // namespace

GfMenuObjOption::GfMenuObjOption(unsigned int handle)
    : GfMenuObject(handle), m_mainList(nullptr), m_itemList(nullptr), m_cursor(nullptr), m_capBdat(nullptr),
      m_infoHandle(0), m_settingHandle(0), m_callContext(nullptr), m_seq(this), m_flag3F0(false), m_saveReq(-1),
      m_byte3F8(false), m_guideFlag(false), m_category(-1), m_flag3FB(false), m_flag3FC(false) {
    m_callContext = GfMenuCallContext::create();
}

GfMenuObjOption::~GfMenuObjOption() {
    if (m_callContext != nullptr) {
        m_callContext->release();
        m_callContext = nullptr;
    }
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
    if (m_mainList != nullptr) {
        m_mainList->release();
        m_mainList = nullptr;
    }
}

void GfMenuObjOption::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjOption::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjOption::dispItemBase(unsigned int category, unsigned int index, bool disp) {
    mm::mtl::FixStr<32> name;
    switch (category) {
    case 0:
        name.format("IMG_cam_item_base@%02d", index + 1);
        break;
    case 1:
        name.format("IMG_snd_item_base@%02d", index + 1);
        break;
    case 2:
        name.format("IMG_dis_item_base@%02d", index + 1);
        break;
    case 3:
        name.format("IMG_gam_item_base@%02d", index + 1);
        break;
    case 4:
        name.format("IMG_gam_dlc_item_base@%02d", index + 1);
        break;
    case 5:
        name.format("IMG_dif_item_base@%02d", index + 1);
        break;
    }
    ui::UIObjectAcc acc(m_handle, name.m_str);
    acc.setAlpha(disp ? 1.0f : 0.0f);
}

void GfMenuObjOption::updateInfo(unsigned int index) {
    ui::UIObjectAcc acc(m_infoHandle);
    if (acc.m_object != nullptr) {
        acc.setText(ui::UIStr(GfDataBdat::getFP(0x136), (unsigned short)Bdat::getVal(m_capBdat, "cap_id", index + 1)));
    }
}

bool GfMenuObjOption::seqSave() {
    ui::UIObjectAcc acc(m_handle, "LAY_submenu");
    GfMenuObject::disableInput(acc.m_handle);
    GfMenuObjMainMenu2::setCloseKeyEnable(false);
    m_saveReq = GfReqCommand::reqSaveOption();
    GfMenuObjFade::dispSaving(true, 0);
    return true;
}

bool GfMenuObjOption::seqSaveWait() {
    if (GfReqManager::isValid(m_saveReq)) {
        return false;
    }
    {
        GfMenuObjFade::dispSaving(false, 0);
        m_saveReq = -1;
        ui::UIObjectAcc main(m_handle, "LAY_main");
        GfMenuObject::termCallContext(main.m_handle);
        main.setTerm();
        GfMenuObjMainMenu2::setCloseKeyEnable(true);
        ui::UIObjectAcc submenu(m_handle, "LAY_submenu");
        GfMenuObject::enableInput(submenu.m_handle);
    }
    return true;
}

void GfMenuObjOption::ItemSettingListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
    } else if (event.m_type == 0x21) {
        acc.setDisp(true);
        GfMenuObject::enableInput(acc.m_handle);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
    } else if (event.m_type == 0x22) {
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
    } else {
        ui::UIObjectListener::reciveEvent(event, handle);
    }
}

bool GfMenuObjOption::attach(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x86));
    if (acc.m_object == nullptr) {
        return false;
    }
    GfMenuObject::startCallContext(context, 0x86, acc.m_handle);
    return true;
}

static inline bool isAllDifficulty() {
    return (GfMenuObjUtil::fn_710048FD30(3) && GfGameManager::isClearGame()) || GfGameUtilSaveData::fn_71002EDCEC();
}

// the index-th value of the list in use, of the two it is handed (the name is not the original's)
static inline int getDifficulty(const int* list, const int* listAll, unsigned long index) {
    return (isAllDifficulty() ? listAll : list)[index];
}

unsigned int GfMenuObjOption::fn_7100452ADC(int value) {
    for (unsigned int i = 0; i < fn_7100452B84(); i++) {
        if (getDifficulty(s_difficultyList, s_difficultyListAll, i) == value) {
            return i;
        }
    }
    return 0;
}

unsigned int GfMenuObjOption::fn_7100452B84() {
    return isAllDifficulty() ? 4 : 2;
}

int GfMenuObjOption::fn_7100452BC0(unsigned int index) {
    if (index < fn_7100452B84()) {
        return getDifficulty(s_difficultyList, s_difficultyListAll, index);
    }
    return 0;
}

}  // namespace gf
