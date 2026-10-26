#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjFactory.h"
#include "classes/ui/UIStreamManager.h"
#include "ui/UIUtil.h"
#include "classes/ui/UIManager.h"
#include "fw/Allocator.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIAnimationManager.h"
#include "classes/ui/UIColorLibrary.h"
#include "classes/ui/UICtrlManager.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIFontManager.h"
#include "classes/ui/UIInputManager.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UIMotionLibrary.h"
#include "classes/ui/UIObjFactory.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "classes/ui/UIParticleManager.h"
#include "classes/ui/UIStreamManager.h"
#include "classes/ui/UITagParser.h"
#include "classes/ui/UITextManager.h"
#include "classes/ui/UITimerManager.h"
#include "classes/ui/UIUioLibrary.h"
#include "classes/ui/UIUpdateCallback.h"
#include "mm/Col4.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIUtil.h"

namespace ui {

#line 50
UIManager::UIManager(const UIPadRead* padRead, mtl::ALLOC_HANDLE handle)
    : m_groups(), m_layers(), m_mode(1), m_padRead(padRead), m_updateCallback(nullptr) {
    UIUtil::initLayerLib();
    UIUtil::setupAllocator(handle);
#line 54
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIFontManager();
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UITextManager();
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIObjFactory();
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIEventManager();
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIInputManager();
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UICtrlManager();
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UITimerManager();
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIAnimationManager();
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIColorLibrary();
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIMotionLibrary();
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIUioLibrary();
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIStreamManager(UIUtil::getResourceAllocator());
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIParticleManager();
    new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UITagParser(UIUtil::getProgAllocator());
    resetData();
    m_groups[0].setup(4);
    m_groups[0].suspend(false);
    m_groups[1].setup(4);
    m_groups[1].suspend(false);
    m_groups[2].setup(32);
    m_groups[2].suspend(false);
    m_groups[3].setup(4);
    m_groups[3].suspend(false);
    m_groups[4].setup(32);
    m_groups[4].suspend(false);
    m_groups[5].setup(4);
    m_groups[5].suspend(false);
    m_groups[6].setup(4);
    m_groups[6].suspend(false);
    m_groups[7].setup(4);
    m_groups[7].suspend(false);
}

void UIManager::resetData() {
    UIUtil::initBdatFP();
    if (UIColorLibrary::get() == nullptr) {
#line 282
        new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIColorLibrary();
    }
    unsigned char* fp = UIUtil::getBdatFP(12);
    if (fp != nullptr) {
        for (int i = 0; i < Bdat::getIdCount(fp); ++i) {
            int id = Bdat::getIdTop(fp) + i;
            const char* name = Bdat::getVal(fp, "name", id);
            if (name != nullptr && *name != '\0') {
                // the components are bytes (0-255)
                mm::Col4 color;
                unsigned int r = (unsigned char)(unsigned long)Bdat::getVal(fp, "col_r", id);
                color.r = r / 255.0f;
                unsigned int g = (unsigned char)(unsigned long)Bdat::getVal(fp, "col_g", id);
                color.g = g / 255.0f;
                unsigned int b = (unsigned char)(unsigned long)Bdat::getVal(fp, "col_b", id);
                color.b = b / 255.0f;
                color.a = 1.0f;
                UIColorLibrary::get()->add(name, color);
            }
        }
    }
    UIMotionLibrary::get()->reset();
    fp = UIUtil::getBdatFP(14);
    if (fp != nullptr) {
        for (int i = 0; i < Bdat::getIdCount(fp); ++i) {
            const char* file = Bdat::getVal(fp, "file", i + 1);
            UIMotionLibrary::get()->add(file);
        }
    }
    UIUioLibrary::get()->reset();
    fp = UIUtil::getBdatFP(15);
    if (fp != nullptr) {
        for (int id = Bdat::getIdTop(fp); id <= Bdat::getIdEnd(fp); ++id) {
            const char* file = Bdat::getVal(fp, "file", id);
            UIUioLibrary::get()->add(file);
        }
    }
}

UIManager::~UIManager() {
    for (int i = 0; i < 8; ++i) {
        m_groups[i].clean();
    }
    delete UITagParser::get();
    delete UIParticleManager::get();
    delete UIStreamManager::get();
    delete UIColorLibrary::get();
    delete UIAnimationManager::get();
    delete UITimerManager::get();
    delete UIInputManager::get();
    delete UICtrlManager::get();
    delete UIMotionLibrary::get();
    delete UIUioLibrary::get();
    delete UIEventManager::get();
    delete UIObjFactory::get();
    delete UITextManager::get();
    delete UIFontManager::get();
    UIUtil::termLayerLib();
}

void UIManager::update(const fw::UpdateInfo& info) {
    UIFontManager::get()->update(info);
    if (UIFontManager::get()->isLoading()) {
        return;
    }
    UIObjFactory::get()->update(info);
    UIMotionLibrary::get()->update(info);
    UIInputManager::get()->update(info);
    UIUioLibrary::get()->update(info);
    UITimerManager::get()->update(info);
    UIStreamManager::get()->update(info);
    UIAnimationManager::get()->update(info);
    UIEventManager::get()->update(info);
    UICtrlManager::get()->update(info);
    UIParticleManager::get()->update(info);
    if (m_updateCallback != nullptr) {
        m_updateCallback->beginUpdate(info);
    }
    for (int i = 0; i < 8; ++i) {
        m_groups[i].updateObject(info);
    }
    if (m_updateCallback != nullptr) {
        m_updateCallback->endUpdate(info);
    }
    if (!UIObjFactory::get()->isLoading()) {
        for (LayerInfo* it = m_layers.begin(); it != m_layers.end();) {
            if (m_groups[it->m_group].isActiveLayer(it->m_id)) {
                ++it;
            } else {
                UIEventManager::EventInfo event;
                event.m_handle = 0;
                event.m_data.m_type = 4;
                event.m_data.m_param0 = it->m_id;
                UIEventManager::get()->pushGameEvent(event);
                it = m_layers.erase(it);
            }
        }
    }
    if (m_updateCallback != nullptr) {
        m_updateCallback->beginApply();
    }
    for (int i = 0; i < 8; ++i) {
        m_groups[i].applyObject();
    }
    if (m_updateCallback != nullptr) {
        m_updateCallback->endApply();
    }
}

void UIManager::terminate() {
    for (int i = 0; i < 8; ++i) {
        m_groups[i].terminateObjectAll(true);
    }
}

bool UIManager::createLayer(unsigned int id) {
    unsigned char* bdat;
    if (id < 100) {
        bdat = UIUtil::fn_7100696A28(0);
    } else {
        if (!UIUtil::fn_7100696970(id / 100)) {
            return false;
        }
        bdat = UIUtil::fn_7100696A28(id / 100);
    }
    return fn_710068F208(bdat, id, false);
}

unsigned int UIManager::searchObject(const char* name, unsigned short group) {
    if (name != nullptr && group < 8 && *name != '\0') {
        return m_groups[group].searchObject(name);
    }
    return 0;
}

void UIManager::terminateLayer(unsigned int id, bool release) {
    if (id < 100) {
        fn_710068F58C(UIUtil::getBdatFP(6), id, release);
    } else if (UIUtil::fn_7100696970(id / 100)) {
        fn_710068F58C(UIUtil::fn_7100696A28(id / 100), id, release);
    }
}

void UIManager::fn_710068F58C(unsigned char* bdat, unsigned int id, bool release) {
    if (!isLayerCreated(id) || bdat == nullptr) {
        return;
    }
    unsigned char group = (unsigned char)(unsigned long)Bdat::getVal(bdat, "group", id);
    // the columns after "group" come in pairs: a sheet's object and its priority
    int sheets = (Bdat::getMemberSize(bdat) - 1) / 2;
    mm::mtl::FixStr<32> column;
    for (unsigned int i = 0; i < sheets; ++i) {
        column.format("sheet%02d", i + 1);
        const char* name = Bdat::getVal(bdat, column.m_str, id);
        if (name != nullptr && *name != '\0' && m_groups[group].isAssignedLayer(name, id)) {
            m_groups[group].terminateObject(name, release);
        }
    }
}

void UIManager::releaseLayer(unsigned int id) {
    unsigned char* bdat;
    if (id < 100) {
        bdat = UIUtil::getBdatFP(6);
    } else {
        if (!UIUtil::fn_7100696970(id / 100)) {
            return;
        }
        bdat = UIUtil::fn_7100696A28(id / 100);
    }
    fn_710068F744(bdat, id);
}

void UIManager::fn_710068F744(unsigned char* bdat, unsigned int id) {
    if (!isLayerCreated(id) || bdat == nullptr) {
        return;
    }
    unsigned char group = (unsigned char)(unsigned long)Bdat::getVal(bdat, "group", id);
    // the columns after "group" come in pairs: a sheet's object and its priority
    int sheets = (Bdat::getMemberSize(bdat) - 1) / 2;
    mm::mtl::FixStr<32> column;
    for (unsigned int i = 0; i < sheets; ++i) {
        column.format("sheet%02d", i + 1);
        const char* name = Bdat::getVal(bdat, column.m_str, id);
        if (name != nullptr && *name != '\0') {
            m_groups[group].releaseObject(name);
        }
    }
}

bool UIManager::preloadLayer(unsigned int id) {
    unsigned char* bdat = UIUtil::getBdatFP(6);
    if (bdat == nullptr) {
        return false;
    }
    Bdat::getVal(bdat, "group", id);
    // the columns after "group" come in pairs: a sheet's object and its priority
    int sheets = (Bdat::getMemberSize(bdat) - 1) / 2;
    mm::mtl::FixStr<32> column;
    for (unsigned int i = 0; i < sheets; ++i) {
        column.format("sheet%02d", i + 1);
        if (Bdat::getMember(bdat, column.m_str) == nullptr) {
            continue;
        }
        const char* name = Bdat::getVal(bdat, column.m_str, id);
        if (name != nullptr && *name != '\0') {
            UIObjFactory::get()->registPreloadResource(1, name);
        }
    }
    return true;
}

void UIManager::fn_710068F958() {
    UIObjFactory::get()->fn_71006757FC();
}

void UIManager::terminateObject(const char* name, unsigned char group, bool release) {
    if (name != nullptr && group < 8 && *name != '\0') {
        m_groups[group].terminateObject(name, release);
    }
}

void UIManager::requestObjectEvent(unsigned int handle, const EventData& event, float delay) {
    if (UIUtil::isValid(handle)) {
        UIEventManager::EventInfo info;
        info.m_handle = handle;
        info.m_data.copyFrom(event);
        info.m_delay = delay;
        UIEventManager::get()->pushObjectEvent(info);
    }
}

void UIManager::requestGameEvent(unsigned int handle, const EventData& event) {
    if (UIUtil::isValid(handle)) {
        UIEventManager::EventInfo info;
        info.m_handle = handle;
        info.m_data.copyFrom(event);
        UIEventManager::get()->pushGameEvent(info);
    }
}

void UIManager::setGameEventLisenter(UIGameListener* listener) {
    UIEventManager::get()->setGameListener(listener);
}

void UIManager::setUpdateCallback(UIUpdateCallback* callback) {
    m_updateCallback = callback;
}

void UIManager::registObjectTimer(unsigned int handle, unsigned short id, unsigned long time, bool loop) {
    UITimerManager::get()->registTimer(handle, id, time, loop);
}

void UIManager::releaseObjectTimer(unsigned int handle) {
    unsigned int timer = UITimerManager::get()->getTimerHandle(handle);
    if (timer != 0) {
        UITimerManager::get()->releaseTimer(timer);
    }
}

void UIManager::setDisp(unsigned short group, bool disp) {
    if (group < 8) {
        m_groups[group].disp(disp);
    }
}

bool UIManager::isLoading() const {
    return UIObjFactory::get()->isLoading();
}

void UIManager::reloadText() {
    UIObjectNumberPlugin::refreshMoneySeparetor();
    UITextManager::get()->reloadAll();
    for (int i = 0; i < 8; ++i) {
        m_groups[i].reloadText();
    }
}

bool UIManager::isTerminated() const {
    for (int i = 0; i < 8; ++i) {
        if (m_groups[i].hasObject()) {
            return false;
        }
    }
    return true;
}

}  // namespace ui
