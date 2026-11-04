#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UICtrlManager.h"
#include "classes/ui/UIInputManager.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuCallManager.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UICtrlManager.h"
#include "classes/ui/UIInputManager.h"
#include "classes/ui/UIAnimationManager.h"
#include "classes/ui/UITimerManager.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIEventNumberCondition.h"
#include "classes/ui/UIEventDispCondition.h"
#include "classes/ui/UIEventPosCondition.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "classes/ui/UIObjectPosPlugin.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIListInfoBase.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "ui/UIUtil.h"

namespace gf {

GfMenuObject::GfMenuObject(unsigned int handle) : m_handle(handle), m_stateFlags(0) {}

GfMenuObject::~GfMenuObject() {
    ;  // the body stores the table only
}

void GfMenuObject::initialize() {
    m_stateFlags |= 1;
}

void GfMenuObject::finalize() {
    m_handle = 0;
    m_stateFlags |= 2;
}

void GfMenuObject::update() {}

void GfMenuObject::reloadParam() {}

void GfMenuObject::attachExternalCall(unsigned int id, unsigned int handle) {
    if (GfMenuCallManager::get() != nullptr) {
        GfMenuCallManager::get()->attachCall(id, handle);
    }
}

void GfMenuObject::detachExternalCall(unsigned int id) {
    if (GfMenuCallManager::get() != nullptr) {
        GfMenuCallManager::get()->detachCall(id);
    }
}

bool GfMenuObject::existAttachedObject(unsigned int id) {
    if (GfMenuCallManager::get() != nullptr) {
        return GfMenuCallManager::get()->canCall(id);
    }
    return false;
}

unsigned int GfMenuObject::getAttachedObject(unsigned int id) {
    if (GfMenuCallManager::get() != nullptr) {
        return GfMenuCallManager::get()->getAttachedObject(id);
    }
    return 0;
}

unsigned short GfMenuObject::registString(const ui::UIStr& text) {
    if (GfMenuCallManager::get() != nullptr) {
        return GfMenuCallManager::get()->registString(text);
    }
    return 0;
}

void GfMenuObject::releaseString(unsigned short id) {
    if (GfMenuCallManager::get() != nullptr) {
        GfMenuCallManager::get()->releaseString(id);
    }
}

const ui::UIStr& GfMenuObject::getString(unsigned short id) {
    return GfMenuCallManager::get()->getString(id);
}

void GfMenuObject::startCallContext(GfMenuCallContext* context, unsigned int id, unsigned int handle) {
    if (GfMenuCallManager::get() != nullptr) {
        GfMenuCallManager::get()->startCallContext(context, id, handle);
    }
}

void GfMenuObject::nextCallContext(GfMenuCallContext* context, unsigned int id) {
    if (GfMenuCallManager::get() != nullptr) {
        GfMenuCallManager::get()->nextCallContext(context, id);
    }
}

void GfMenuObject::addResultCallContext(unsigned int handle, unsigned int result, int value) {
    ui::EventData event;
    event.m_param0 = result;
    event.m_param1 = value;
    event.m_type = 8;
    ui::UIManager::get()->requestGameEvent(handle, event);
}

void GfMenuObject::termCallContext(unsigned int handle) {
    ui::EventData event;
    event.m_type = 9;
    ui::UIManager::get()->requestGameEvent(handle, event);
}

void GfMenuObject::setCallContextEventHandler(GfMenuCallContext* context, unsigned int handle) {
    if (GfMenuCallManager::get() != nullptr) {
        GfMenuCallManager::get()->setCallContextEventHandler(context, handle);
    }
}

void GfMenuObject::setupInputSelection(unsigned int handle, int index, unsigned int count) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->setupInputSelection(input, index, count);
    }
}

void GfMenuObject::resetInputSelection(unsigned int handle) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->resetInputSelection(input);
    }
}

void GfMenuObject::setupInputSelectionFromList(unsigned int handle, const ui::UIListInfoBase& list) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->setupInputSelection(input, list.getIndex(false), list.getSize());
        if (list.getColumnSize() == 1) {
            ui::UIInputManager::get()->setPadPageSize(input, list.getPageRowSize());
        }
    }
}

void GfMenuObject::setInputSelectionChecker(unsigned int handle, ui::IUIInputSelectionChecker* checker) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->setSelectionChecker(input, checker);
    }
}

void GfMenuObject::setupPadLineSelection(unsigned int handle, unsigned int count) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->setPadLineSelection(input, count);
    }
}

void GfMenuObject::setupPadLineSelectionForce(unsigned int handle, unsigned int value) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->setPadLineSelectionForce(input, value);
    }
}

void GfMenuObject::setPadLineSelectionLoop(unsigned int handle, bool loop) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->setPadLineSelectionLoop(input, loop);
    }
}

void GfMenuObject::setPadLoopSetting(unsigned int handle, bool loop) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->setPadLoopSetting(input, loop);
    }
}

void GfMenuObject::setupPointerSelection(unsigned int handle, const ui::UIInputPointer::SelectionSetup& setup) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->setupPointerSelection(input, setup);
    }
}

void GfMenuObject::changePointerPos(unsigned int handle, const mm::Pnt<short>& pos) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->changePointerPos(input, pos);
    }
}

void GfMenuObject::changePointerRegionScale(unsigned int handle, float scale) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->changeRegionScale(input, scale);
    }
}

void GfMenuObject::migrateInput(unsigned int handle, unsigned int object) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->migrateInput(input, object);
    }
}

void GfMenuObject::enableInput(unsigned int handle) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->enableInput(input);
    }
}

void GfMenuObject::disableInput(unsigned int handle) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->disableInput(input);
    }
}

bool GfMenuObject::setFSInputObject(unsigned int index, unsigned int handle) {
    return GfMenuFullScreen::setInputObject(index, handle);
}

unsigned int GfMenuObject::getFSInputObject(unsigned int index) {
    return GfMenuFullScreen::getInputObject(index);
}

void GfMenuObject::enableFSInput(unsigned int index) {
    GfMenuFullScreen::enableInput(index);
}

void GfMenuObject::disableFSInput() {
    GfMenuFullScreen::disableInput();
}

void GfMenuObject::setInputActionEnable(unsigned int handle, unsigned int action, bool enable) {
    unsigned int input = ui::UIInputManager::get()->searchInputHandle(handle);
    if (input != 0) {
        ui::UIInputManager::get()->setInputActionEnable(input, action, enable);
    }
}

void GfMenuObject::sendEvent(unsigned int handle, const ui::EventData& event, float delay) {
    if (handle != 0) {
        ui::UIManager::get()->requestObjectEvent(handle, event, delay);
    }
}

void GfMenuObject::sendOpenEvent(unsigned int handle, int param, float delay) {
    if (handle != 0) {
        ui::EventData event;
        event.m_param0 = param;
        event.m_type = 0x21;
        ui::UIManager::get()->requestObjectEvent(handle, event, delay);
    }
}

void GfMenuObject::sendCloseEvent(unsigned int handle, int param, float delay) {
    if (handle != 0) {
        ui::EventData event;
        event.m_param0 = param;
        event.m_type = 0x22;
        ui::UIManager::get()->requestObjectEvent(handle, event, delay);
    }
}

void GfMenuObject::sendEventToParent(unsigned int handle, const ui::EventData& event, float delay) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object != nullptr) {
        unsigned int parent = acc.getParentHandle();
        if (parent != 0) {
            ui::UIManager::get()->requestObjectEvent(parent, event, delay);
        }
    }
}

void GfMenuObject::addNumberEventCondition(unsigned int handle, const char* child, unsigned int event,
                                           unsigned int value, float rate) {
    if (handle == 0 || !ui::UIUtil::getObject(handle)->m_flags.test(1)) {
        return;
    }
    unsigned int target = handle;
    if (child != nullptr) {
        ui::UIObjectAcc acc(handle);
        target = acc.searchChild(child);
    }
    ui::UIObject* object = ui::UIUtil::getObject(target);
    if (object == nullptr) {
        return;
    }
    ui::UIObjectPlugin* plugin = object->m_plugins;
    if (plugin == nullptr || !plugin->getRTTI()->isKindOf(&ui::UIObjectNumberPlugin::m_rtti)) {
        return;
    }
    ui::UIEventCondition* condition =
        ui::UIEventNumberCondition::create(event, value, static_cast<ui::UIObjectNumberPlugin*>(plugin), rate);
    ui::UIEventManager::get()->addCondition(handle, condition);
    if (condition != nullptr) {
        condition->release();
    }
}

void GfMenuObject::addNumberEventCondition(unsigned int handle, const char* child, unsigned int event,
                                           unsigned int value) {
    if (handle == 0 || !ui::UIUtil::getObject(handle)->m_flags.test(1)) {
        return;
    }
    unsigned int target = handle;
    if (child != nullptr) {
        ui::UIObjectAcc acc(handle);
        target = acc.searchChild(child);
    }
    ui::UIObject* object = ui::UIUtil::getObject(target);
    if (object == nullptr) {
        return;
    }
    ui::UIObjectPlugin* plugin = object->m_plugins;
    if (plugin == nullptr || !plugin->getRTTI()->isKindOf(&ui::UIObjectNumberPlugin::m_rtti)) {
        return;
    }
    ui::UIEventCondition* condition =
        ui::UIEventNumberCondition::create(event, value, static_cast<ui::UIObjectNumberPlugin*>(plugin));
    ui::UIEventManager::get()->addCondition(handle, condition);
    if (condition != nullptr) {
        condition->release();
    }
}

void GfMenuObject::addDispEventCondition(unsigned int handle, const char* child, unsigned int event,
                                         unsigned int value, bool duplicated) {
    if (handle == 0 || !ui::UIUtil::getObject(handle)->m_flags.test(1)) {
        return;
    }
    unsigned int target = handle;
    if (child != nullptr) {
        target = !duplicated ? ui::UIObjectAcc(handle).searchChild(child)
                             : ui::UIObjectAcc(handle).searchDuplicatedChild(child, value);
    }
    ui::UIObject* object = ui::UIUtil::getObject(target);
    if (object == nullptr) {
        return;
    }
    ui::UIObjectPlugin* plugin = object->m_plugins;
    if (plugin == nullptr || !plugin->getRTTI()->isKindOf(&ui::UIObjectDispPlugin::m_rtti)) {
        return;
    }
    ui::UIEventCondition* condition =
        ui::UIEventDispCondition::create(event, value, static_cast<ui::UIObjectDispPlugin*>(plugin));
    ui::UIEventManager::get()->addCondition(handle, condition);
    if (condition != nullptr) {
        condition->release();
    }
}

void GfMenuObject::addPosEventCondition(unsigned int handle, const char* child, unsigned int event,
                                        unsigned int value) {
    if (handle == 0 || !ui::UIUtil::getObject(handle)->m_flags.test(1)) {
        return;
    }
    unsigned int target = handle;
    if (child != nullptr) {
        ui::UIObjectAcc acc(handle);
        target = acc.searchChild(child);
    }
    ui::UIObject* object = ui::UIUtil::getObject(target);
    if (object == nullptr) {
        return;
    }
    ui::UIObjectPlugin* plugin = object->m_plugins;
    if (plugin == nullptr || !plugin->getRTTI()->isKindOf(&ui::UIObjectPosPlugin::m_rtti)) {
        return;
    }
    ui::UIEventCondition* condition =
        ui::UIEventPosCondition::create(event, value, static_cast<ui::UIObjectPosPlugin*>(plugin));
    ui::UIEventManager::get()->addCondition(handle, condition);
    if (condition != nullptr) {
        condition->release();
    }
}

void GfMenuObject::hookCtrlEvent(unsigned int handle, int ctrl) {
    ui::UICtrlManager::get()->changeEventHandleObject(ctrl, handle);
}

void GfMenuObject::hookAnimationEvent(unsigned int handle, unsigned int target, unsigned int param) {
    ui::UIAnimationManager::get()->changeEventHandleObject(target, handle, param);
}

void GfMenuObject::closeFSLayer(unsigned int handle, bool flag0, bool flag1) {
    ui::EventData event(7);
    event.m_param0 = flag0;
    event.m_param1 = flag1;
    ui::UIManager::get()->requestGameEvent(handle, event);
}

unsigned int GfMenuObject::getMenuLayerID(unsigned int menuId) {
    unsigned char* bdat = GfDataBdat::getFP(0x173);
    if (bdat != nullptr && GfMenuBdat::isValidBdatID(bdat, menuId)) {
        return static_cast<unsigned short>(Bdat::getVal(bdat, "layer_id", menuId));
    }
    return 1;
}

unsigned int GfMenuObject::getMenuIconID(unsigned int menuId) {
    unsigned char* bdat = GfDataBdat::getFP(0x173);
    if (bdat != nullptr && GfMenuBdat::isValidBdatID(bdat, menuId)) {
        return static_cast<unsigned short>(Bdat::getVal(bdat, "icon", menuId));
    }
    return 0;
}

bool GfMenuObject::getMenuText(unsigned int menuId, unsigned char*& file, unsigned int& msgId) {
    unsigned char* bdat = GfDataBdat::getFP(0x173);
    if (bdat != nullptr && GfMenuBdat::isValidBdatID(bdat, menuId)) {
        msgId = static_cast<unsigned short>(Bdat::getVal(bdat, "text", menuId));
        file = GfDataBdat::getFP(0x119);
        return true;
    }
    return false;
}

bool GfMenuObject::getMenuDesc(unsigned int menuId, unsigned char*& file, unsigned int& msgId) {
    unsigned char* bdat = GfDataBdat::getFP(0x173);
    if (bdat != nullptr && GfMenuBdat::isValidBdatID(bdat, menuId)) {
        msgId = GfMenuObjUtil::getMsgIDFromList(0x164, static_cast<unsigned short>(Bdat::getVal(bdat, "desc", menuId)));
        file = GfDataBdat::getFP(0x119);
        return true;
    }
    return false;
}

void GfMenuObject::changeFSSubLayer(unsigned int handle, unsigned short group, unsigned short layer, bool flag) {
    int layerGroup = group;
    ui::EventData event(1);
    event.m_param0 = layer;
    event.m_param1 = layerGroup;
    event.m_param2 = flag;
    ui::UIManager::get()->requestGameEvent(handle, event);
}

void GfMenuObject::returnFSSubLayer(unsigned int handle, unsigned short group) {
    int layerGroup = group;
    ui::EventData event;
    event.m_type = 3;
    event.m_param0 = layerGroup;
    ui::UIManager::get()->requestGameEvent(handle, event);
}

void GfMenuObject::returnFSSubLayer(GfMenuObject* object) {
    returnFSSubLayer(object->m_handle, GfMenuFullScreen::getLayerGroup(object->m_fsLayer));
}

void GfMenuObject::registFSLayerObject(unsigned int layer, unsigned int handle) {
    GfMenuFullScreen::registLayerObject(layer, handle);
}

void GfMenuObject::setFSShadowLayer(unsigned int layer, bool shadow) {
    GfMenuFullScreen::setShadowLayer(layer, shadow);
}

void GfMenuObject::registFSLayerParam(unsigned int layer, const GfMenuTypes::Param& param) {
    GfMenuFullScreen::registLayerParam(layer, param);
}

bool GfMenuObject::getFSLayerParam(unsigned int layer, GfMenuTypes::Param& param) {
    return GfMenuFullScreen::getLayerParam(layer, param);
}

void GfMenuObject::removeFSLayerParam(unsigned int layer) {
    GfMenuFullScreen::removeLayerParam(layer);
}

void GfMenuObject::registTimer(unsigned int handle, unsigned short id, float time, bool loop) {
    ui::UIManager::get()->registObjectTimer(handle, id, ui::UIUtil::timeSecToUITime(time), loop);
}

void GfMenuObject::releaseTimer(unsigned int handle) {
    ui::UIManager::get()->releaseObjectTimer(handle);
}

void GfMenuObject::setTimerSpeedFactor(unsigned int handle, float factor) {
    unsigned int timer = ui::UITimerManager::get()->getTimerHandle(handle);
    if (timer != 0) {
        ui::UITimerManager::get()->setTimerSpeedFactor(timer, factor);
    }
}

void GfMenuObject::setText(unsigned int handle, unsigned short id) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object != nullptr) {
        const ui::UIStr& text = getString(id);
        if (text.isValid()) {
            acc.setText(text);
        }
    }
    releaseString(id);
}

void GfMenuObject::eventHudSceneChange(unsigned int) {}

}  // namespace gf
