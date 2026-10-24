#include "classes/ui/UICtrlManager.h"
#include "classes/fw/SoundManager.h"
#include "ui/UIUtil.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UICtrlManager.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuSoundManager.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameManager.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/PadManager.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfQuestInfo.h"
#include "gf/QuestID.h"
#include "ui/UIUtil.h"
#include "plugin/Bdat.h"
#include "mm/mtl/FixStr.h"
#include "mm/Pnt.h"

namespace gf {
namespace {
// a menu sound table row's sound (BDAT 0x187's resource_id), played when the sound manager exists: its handle, 0
// when nothing plays (the name is not the original's)
inline unsigned int playMenuSe(unsigned int row) {
    if (mm::mtl::PtrSingleton<fw::SoundManager>::get() != nullptr) {
        unsigned short id = static_cast<unsigned short>(
            reinterpret_cast<unsigned long>(Bdat::getVal(GfDataBdat::getFP(0x187), "resource_id", row)));
        if (id != 0) {
            return mm::mtl::PtrSingleton<fw::SoundManager>::get()->playSe(id, nullptr, 1.0f,
                                                                           static_cast<fw::SoundCategory>(0));
        }
    }
    return 0;
}
}  // namespace

short GfMenuObjUtil::getBtnIconNumber(unsigned int button) {
    // each button bit's icon number, in the order they are looked for
    static const struct {
        unsigned int button;
        unsigned int icon;
    } s_icons[] = {
        {0x1000, 0x1A}, {0x2000, 0x1D}, {0x4000, 0x1B}, {0x8000, 0x1C}, {0x8, 0xA},   {0x4, 0xC},
        {0x2, 0xD},     {0x1, 0xB},     {0x20, 0x13},   {0x80, 0x19},   {0x800, 0xF}, {0x10, 0x12},
        {0x40, 0x18},   {0x400, 0xE},   {0x200, 0x9},   {0x100, 0x8},
    };
    for (unsigned int i = 0; i < sizeof(s_icons) / sizeof(s_icons[0]); i++) {
        if (button & s_icons[i].button) {
            return s_icons[i].icon;
        }
    }
    return 0xFFFF;
}

short GfMenuObjUtil::getPadSelectIconNumber(unsigned int select) {
    // each pad selection's icon number
    static const struct {
        unsigned int select;
        unsigned int icon;
    } s_icons[] = {
        {1, 0x1E}, {2, 0x1F}, {6, 0x5}, {3, 0x13}, {5, 0x10}, {4, 0x10}, {9, 0x11}, {8, 0x11},
    };
    for (unsigned int i = 0; i < sizeof(s_icons) / sizeof(s_icons[0]); i++) {
        if (select == s_icons[i].select) {
            return s_icons[i].icon;
        }
    }
    return 0xFFFF;
}

short GfMenuObjUtil::getPointerSelectIconNumber() {
    return 17;
}

void GfMenuObjUtil::setChildDisp(unsigned int handle, const char* child, bool disp) {
    ui::UIObjectAcc acc(handle, child);
    if (acc.m_object != nullptr) {
        acc.setDisp(disp);
    }
}

void GfMenuObjUtil::setChildAddColor(unsigned int handle, const char* child, const char* color) {
    ui::UIObjectAcc acc(handle, child);
    if (acc.m_object != nullptr) {
        acc.setAddColor(color);
    }
}

void GfMenuObjUtil::setChildText(unsigned int handle, const char* child, unsigned short text) {
    ui::UIObjectAcc acc(handle, child);
    if (acc.m_object != nullptr) {
        GfMenuObject::setText(acc.m_handle, text);
    }
}

void GfMenuObjUtil::setChildText(unsigned int handle, const char* child, const ui::UIStr& text) {
    ui::UIObjectAcc acc(handle, child);
    if (acc.m_object != nullptr) {
        acc.setText(text);
    }
}

void GfMenuObjUtil::setChildIcon(unsigned int handle, const char* child, unsigned short icon) {
    ui::UIObjectAcc acc(handle, child);
    if (acc.m_object != nullptr) {
        acc.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
    }
}

unsigned int GfMenuObjUtil::playAnime(unsigned int handle, const char* child, const char* anime) {
    ui::UIObjectAcc acc(handle, child);
    if (acc.m_object == nullptr) {
        return 0;
    }
    acc.setDisp(true);
    acc.startAnimation(anime, false);
    return acc.m_handle;
}

void GfMenuObjUtil::setDockPos(unsigned int handle, unsigned int target, unsigned char pos, bool outer) {
    ui::UIUtil::setDockPos(handle, target, pos, outer);
}

void GfMenuObjUtil::addPos(unsigned int handle, short x, short y) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object != nullptr) {
        mm::Pnt<short> pos;
        acc.getPos(pos);
        pos.x += x;
        pos.y += y;
        acc.setPos(pos);
    }
}

bool GfMenuObjUtil::isMenuObjectFull() {
    if (ui::UIEventManager::get()->isObjectListenerFull()) {
        return true;
    }
    return GfMenuAdapterManager::isAdapterFull();
}

void GfMenuObjUtil::setColMulandAdd(unsigned int handle, const char* name) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object != nullptr) {
        mm::mtl::FixStr<64> color;
        color.format("%s_mul", name);
        acc.setMulColor(color.m_str);
        color.format("%s_add", name);
        acc.setAddColor(color.m_str);
    }
}

void GfMenuObjUtil::setColDefault(unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object != nullptr) {
        acc.loadDefColor();
    }
}

int GfMenuObjUtil::getCtrlID(unsigned int handle) {
    return ui::UICtrlManager::get()->getCtrlSlot(handle);
}

void GfMenuObjUtil::stopCtrl(int slot) {
    if (slot != -1) {
        ui::UICtrlManager::get()->stopCtrl(slot, true, false);
    }
}

void GfMenuObjUtil::suspendCtrl(int slot) {
    if (slot != -1) {
        ui::UICtrlManager::get()->stopCtrl(slot, false, false);
    }
}

void GfMenuObjUtil::releaseCtrl(int slot) {
    if (slot != -1) {
        ui::UICtrlManager::get()->releaseCtrlSlot(slot);
    }
}

bool GfMenuObjUtil::isBusyCtrl(int slot) {
    if (slot != -1) {
        return ui::UICtrlManager::get()->isBusyCtrl(slot);
    }
    return false;
}

void GfMenuObjUtil::setCtrlDefault(int slot) {
    if (slot != -1) {
        ui::UICtrlManager::get()->setDefault(slot);
    }
}

void GfMenuObjUtil::setCtrlSpeedFactor(int slot, float factor) {
    if (slot != -1) {
        ui::UICtrlManager::get()->setSpeedFactor(slot, factor);
    }
}

int GfMenuObjUtil::getPresetCtrlCurve(unsigned int preset) {
    return 1;
}

const char* GfMenuObjUtil::getMenuMS(unsigned int id) {
    if (id == 0) {
        return nullptr;
    }
    return Bdat::getMSText(GfDataBdat::getFP(0xF5), id);
}

unsigned int GfMenuObjUtil::getLeaderPartyID() {
    return 0;
}

bool GfMenuObjUtil::isExitDriver(unsigned int index) {
    if (index >= 3) {
        index %= 3;
    }
    return GfGameParty::getHandleDriver(index, 0) != reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

bool GfMenuObjUtil::fn_710048FD30(unsigned int layer) {
    if (ui::UIUtil::fn_7100696970(layer)) {
        if (layer == 1) {
            if (GfGameManager::fn_71002AC598()) {
                return true;
            }
        } else if (layer == 2) {
            return true;
        } else if (layer == 3) {
            if (GfGameManager::fn_71002A9E68()) {
                return true;
            }
        }
    }
    return false;
}

unsigned short GfMenuObjUtil::getMsgIDFromList(unsigned int list, unsigned short index) {
    if (unsigned char* fp = GfDataBdat::getFP(list)) {
        return static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getVal(fp, "name", index)));
    }
    return 0;
}

unsigned int GfMenuObjUtil::playSE(unsigned int se) {
    return playMenuSe(se);
}

unsigned int GfMenuObjUtil::playSE(const char* se) {
    if (fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get()) {
        return sound->playSe(se, nullptr, 1.0f, static_cast<fw::SoundCategory>(3));
    }
    return 0;
}

unsigned int GfMenuObjUtil::playSECommonDecide() {
    return playMenuSe(1);
}

unsigned int GfMenuObjUtil::playSECommon(unsigned int se) {
    static const unsigned short s_rows[] = {1, 2, 7};
    if (se > 2) {
        return 0;
    }
    return playMenuSe(s_rows[se]);
}

unsigned int GfMenuObjUtil::playSECommonCancel() {
    return playMenuSe(2);
}

unsigned int GfMenuObjUtil::playSECommonCursor() {
    return playMenuSe(6);
}

unsigned int GfMenuObjUtil::playSECommonTab() {
    return playMenuSe(5);
}

unsigned int GfMenuObjUtil::playSECommonSort() {
    return playMenuSe(0xB);
}

unsigned int GfMenuObjUtil::playSECommonOpenSubMenu() {
    return playMenuSe(0xC);
}

unsigned int GfMenuObjUtil::playSECommonCloseSubMenu() {
    return playMenuSe(0xE);
}

void GfMenuObjUtil::playSECommonFromInput(unsigned int input) {
    if (input == 1) {
        playSECommonDecide();
    } else if (input == 2) {
        playSECommonCancel();
    } else if (input == 3) {
        playSECommonCancel();
    }
}

void GfMenuObjUtil::stopSE(unsigned int handle, float time) {
    if (fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get()) {
        sound->stopSe(handle, time);
    }
}

void GfMenuObjUtil::stopBGM(unsigned int handle, float time) {
    if (handle != 0) {
        if (fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get()) {
            sound->stopBgm(handle, time);
        }
    }
}

void GfMenuObjUtil::playJingle(unsigned int jingle) {
    GfMenuSoundManager::playJingle(jingle);
}

void GfMenuObjUtil::playVibration(fw::VibrationID id, float scale) {
    ml::PadVibrationInfo info(id);
    info.m_scale0 = scale;
    info.m_scale2 = scale;
    fw::PadManager::playVibration(info);
}

unsigned char GfMenuObjUtil::getElementComboEffect(unsigned int combo) {
    return 1;
}

bool GfMenuObjUtil::isQuestCompleted(QuestID id) {
    return GfQuestInfo::isQuestFin(id);
}
}  // namespace gf
