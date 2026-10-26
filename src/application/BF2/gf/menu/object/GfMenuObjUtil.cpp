#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/SDataBlade.h"
#include "gf/GfDataParty.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/SDataBlade.h"
#include "gf/GfDataParty.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "classes/ui/UIObjectDockPlugin.h"
#include "classes/ui/UIObjectScrollBarPlugin.h"
#include "classes/ui/UIObjectSyncPlugin.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "fw/PadData.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/SDataEnemy.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyCharacter.h"
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

void GfMenuObjUtil::createDockPlugin(unsigned int handle, unsigned int target, unsigned int side,
                                     const mm::Pnt<short>& offset, unsigned int align) {
    ui::UIObjectDockPlugin* plugin = ui::UIObjectDockPlugin::create(handle, offset.x, offset.y, target);
    if (plugin != nullptr) {
        plugin->m_side = side;
        plugin->m_align = align;
        plugin->release();
    }
}

void GfMenuObjUtil::createDockPluginEx(unsigned int handle, unsigned int target, unsigned int side,
                                       const DockingOption& option) {
    ui::UIObjectDockPlugin* plugin =
        ui::UIObjectDockPlugin::create(handle, option.m_offset.x, option.m_offset.y, target);
    if (plugin != nullptr) {
        plugin->m_side = side;
        plugin->m_align = option.m_align;
        plugin->m_area = option.m_area;
        plugin->release();
    }
}

void GfMenuObjUtil::createVScrollBarPlugin(unsigned int handle, ui::UIListInfoBase* list, const char* base,
                                           bool scale) {
    ui::UIObjectScrollBarPlugin* plugin = ui::UIObjectScrollBarPlugin::create(handle, 0, list, base);
    if (plugin != nullptr) {
        plugin->setScaleEnable(scale);
        plugin->release();
    }
}

void GfMenuObjUtil::createFollowDispPlugin(unsigned int handle, unsigned int follow) {
    ui::UIObjectDispPlugin* plugin = ui::UIObjectDispPlugin::create(handle);
    if (plugin != nullptr) {
        plugin->setFollowObjHandle(follow);
        plugin->release();
    }
}

void GfMenuObjUtil::createSyncPlugin(unsigned int handle, unsigned int target, unsigned int flag) {
    ui::UIObjectSyncPlugin* plugin = ui::UIObjectSyncPlugin::create(handle);
    if (plugin != nullptr) {
        plugin->setTargetObject(target);
        plugin->setTargetFlag(flag);
        plugin->release();
    }
}

void GfMenuObjUtil::createNumberPlugin(unsigned int handle, int number) {
    ui::UIObjectNumberPlugin* plugin = ui::UIObjectNumberPlugin::create(handle);
    if (plugin != nullptr) {
        plugin->setMin(number);
        plugin->setMax(number);
        plugin->setNumber(number);
        plugin->release();
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

void GfMenuObjUtil::changeCursorTarget(ui::UICtrlCursorSelect* cursor, unsigned int handle, const char* format) {
    if (cursor == nullptr) {
        return;
    }
    ui::UISelectObjList* list = cursor->m_list;
    if (list == nullptr) {
        return;
    }
    list->clear();
    list->pickupObject(handle, format, 1);
    list->getSize();  // the count is not used (the call is the original's)
}

void GfMenuObjUtil::changeCursorTarget(ui::UICtrlCursorSelect* cursor, unsigned int handle, const char** names,
                                       unsigned short count) {
    if (cursor == nullptr) {
        return;
    }
    ui::UISelectObjList* list = cursor->m_list;
    if (list == nullptr) {
        return;
    }
    list->clear();
    if (names != nullptr) {
        ui::UIObjectAcc acc(handle);
        for (unsigned short i = 0; i < count; i++) {
            unsigned int child = acc.searchChild(names[i]);
            if (child != 0) {
                list->addContents(child);
            }
        }
    }
    list->getSize();  // the count is not used (the call is the original's)
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

bool GfMenuObjUtil::isValidBlade(unsigned int blade) {
    return blade != 0 && !GfDataBlade::isDummyBlade(blade);
}

bool GfMenuObjUtil::isBladeEnableOffset(unsigned int driver, int offset) {
    if (ui::UIUtil::fn_7100696970(3) && GfGameManager::fn_71002A9E68()) {
        return true;
    }
    unsigned int blade = GfDataDriver::getBlade(GfDataParty::getDriver(0, 0), -1);
    return blade != 0 && !GfDataBlade::isDummyBlade(blade);
}

gf::GF_OBJ_HANDLE* GfMenuObjUtil::getLeaderBladeHandle(bool flag) {
    int set = 0;
    {
        DataParamAcc acc(3, GfDataParty::getDriver(0, 0), static_cast<GimmickType>(0));
        if (acc.isValid()) {
            set = acc.getBladeSet(false);
        }
    }
    if (set == -1) {
        return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    return GfGameParty::getHandleBlade(0, set);
}

gf::GF_OBJ_HANDLE* GfMenuObjUtil::getBladeHandleFromPartySlot(unsigned int driver, int slot, bool flag) {
    int set = getSetBladeID(driver, slot, flag);
    if (set == -1) {
        return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    return GfGameParty::getHandleBlade(driver, set);
}

unsigned int GfMenuObjUtil::getBladeAttributeIconID(unsigned int blade) {
    if (!GfDataBlade::isValid(blade)) {
        return 0x9E;
    }
    return static_cast<unsigned char>(GfDataBlade::getAttribute(blade)) + 0x9E;
}

unsigned short GfMenuObjUtil::getBladeRareIconID(unsigned int blade) {
    unsigned short icon = 0x89;
    if (GfDataBlade::isValid(blade)) {
        icon = GfDataBlade::isRareBlade(blade) ? 0x8A : 0x89;
    }
    return icon;
}

unsigned short GfMenuObjUtil::getBladeAttributeID(unsigned int blade) {
    if (!GfDataBlade::isValid(blade)) {
        return 0;
    }
    return GfDataBlade::getSDataBlade(blade)->m_attribute;
}

bool GfMenuObjUtil::isBladeDifferentImage(unsigned int blade, unsigned int other) {
    return convMenuBladeID(blade) != convMenuBladeID(other);
}

unsigned int GfMenuObjUtil::getBladeRank(unsigned int blade) {
    if (isScenarioBlade(blade) || GfDataBlade::isRareBlade(blade)) {
        return 5;
    }
    unsigned int max = GfDataBlade::getKizunaringMax(blade);
    if (max >= 38) {
        return 4;
    }
    if (max >= 29) {
        return 3;
    }
    if (max >= 19) {
        return 2;
    }
    return 1;
}

bool GfMenuObjUtil::isScenarioBlade(unsigned int blade) {
    return GfDataBlade::isRegularBlade(blade) || blade == 1014;
}

unsigned int GfMenuObjUtil::getBladeRarity(unsigned int blade) {
    if (isScenarioBlade(blade)) {
        return 2;
    }
    return GfDataBlade::isRareBlade(blade);
}

bool GfMenuObjUtil::canRemoveBlade(unsigned int blade, const mm::mtl::FixedVector<unsigned short, 422>* list) {
    return canRemoveBladeEx(blade, 0, list) == 0;
}

bool GfMenuObjUtil::hasHomura(unsigned int driver) {
    DataParamAcc acc(3, driver, static_cast<GimmickType>(0));
    bool has = false;
    if (acc.isValid()) {
        has = GfDataBlade::getCreator(1001) == driver && !GfDataBlade::isActivateUnuse(1001);
    }
    return has;
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

bool GfMenuObjUtil::isEnemyNamed(gf::GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    const SDataEnemy* enemy = acc.getSDataEnemy();
    return enemy != nullptr && enemy->m_named;
}

bool GfMenuObjUtil::isEnemyBoss(gf::GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    const SDataEnemy* enemy = acc.getSDataEnemy();
    return enemy != nullptr && enemy->m_boss;
}

bool GfMenuObjUtil::checkCCStart(GfMenuCallContext* context) {
    return context != nullptr && !context->isActive();
}

bool GfMenuObjUtil::checkCCNext(GfMenuCallContext* context, unsigned int id) {
    return context != nullptr && context->m_objectId == id;
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

bool GfMenuObjUtil::fn_7100492C88() {
    if ((ui::UIUtil::getPadData()->m_down & 4) != 0) {
        return true;
    }
    return (ui::UIUtil::getPadData()->m_down & 2) != 0;
}

void GfMenuObjUtil::playVibration(fw::VibrationID id, float scale) {
    ml::PadVibrationInfo info(id);
    info.m_scale0 = scale;
    info.m_scale2 = scale;
    fw::PadManager::playVibration(info);
}

unsigned char GfMenuObjUtil::getElementComboAtr(unsigned int combo) {
    unsigned char* fp = Bdat::getFP("BTL_ElementalCombo");
    if (!GfMenuBdat::isValidBdatID(fp, combo)) {
        return 0;
    }
    return static_cast<unsigned char>(reinterpret_cast<unsigned long>(Bdat::getVal(fp, "Atr", combo)));
}

unsigned char GfMenuObjUtil::getElementComboEffect(unsigned int combo) {
    return 1;
}

bool GfMenuObjUtil::isInBattle(gf::GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() == 5) {
        GfObjProperty* property = GfObjUtil::getProperty(handle);
        if (property == nullptr) {
            return false;
        }
        if (property->m_character != nullptr) {
            return property->m_character->pad_30;
        }
    }
    return false;
}

bool GfMenuObjUtil::isQuestCompleted(QuestID id) {
    return GfQuestInfo::isQuestFin(id);
}

unsigned int GfMenuObjUtil::getFavoriteStat(unsigned int type, unsigned int id, FAVORITE favorite) {
    switch (type) {
    case 3:
        if (GfDataDriver::getFavorite(id, favorite) == 0) {
            return 2;
        }
        return !GfDataDriver::isUsedFavorite(id, favorite);
    case 4:
        if (GfDataBlade::getFavorite(id, favorite) == 0) {
            return 2;
        }
        return !GfDataBlade::isUsedFavorite(id, favorite);
    }
    return 2;
}

}  // namespace gf
