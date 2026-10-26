#include "mm/mtl/FixedQueue.h"
#include "classes/gf/GfMenuScriptManager.h"
#include "classes/gf/GfMenuScriptManager/ScriptListener.h"
#include "classes/ui/UIObjectAcc.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "string.h"
#include "ui/EventData.h"

namespace gf {

GfMenuScriptManager::~GfMenuScriptManager() {}

inline void GfMenuScriptManager::initialize(const GfSetupParam& param) {
    for (unsigned int i = 0; i < 32; i++) {
        m_slots[i].m_handle = i + 4;
        m_slots[i].m_used = false;
    }
#line 234
    m_listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ScriptListener();
    m_listener->addRef();
    m_initialized = true;
}

void GfMenuScriptManager::build(const GfSetupParam& param) {
#line 38
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuScriptManager(param);
}

inline void GfMenuScriptManager::finalize() {
    if (m_listener != nullptr) {
        m_listener->release();
        m_listener = nullptr;
    }
    m_initialized = false;
}

void GfMenuScriptManager::destroy() {
    GfMenuScriptManager* manager = get();
    manager->finalize();
    delete manager;
}

bool GfMenuScriptManager::isInitialized() {
    GfMenuScriptManager* manager = get();
    if (manager == nullptr) {
        return false;
    }
    return manager->m_initialized;
}

void GfMenuScriptManager::postUpdate(const fw::UpdateInfo& info) {}

// 1.0.0 has regist, getEmptySlot, unregist and freeSlot here too; 3.0.1's linker dropped them and getScriptName
// as unused, leaving only getScriptName's strings in this file's .rodata.

const char* GfMenuScriptManager::getScriptName(unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    const char* name = acc.getName();
    unsigned char* fp = Bdat::getFP("MNU_ScriptList");
    for (int id = Bdat::getIdTop(fp); id <= Bdat::getIdEnd(fp); id++) {
        if (strcmp(reinterpret_cast<const char*>(Bdat::getVal(fp, "name", id)), name) == 0) {
            return reinterpret_cast<const char*>(Bdat::getVal(fp, "script", id));
        }
    }
    return nullptr;
}

unsigned int GfMenuScriptManager::getHandle(unsigned int id) {
    GfMenuScriptManager* manager = get();
    for (Script* it = manager->m_scripts.begin(); it != manager->m_scripts.end(); ++it) {
        if (it->m_id == id) {
            return it->m_handle;
        }
    }
    return 0;
}

bool GfMenuScriptManager::checkEvent(unsigned int handle) {
    GfMenuScriptManager* manager = get();
    for (Script* it = manager->m_scripts.begin(); it != manager->m_scripts.end(); ++it) {
        if (it->m_handle == handle && it->m_events.size() != 0) {
            it->m_event = it->m_events.pop_front();
            return true;
        }
    }
    return false;
}

bool GfMenuScriptManager::getEventData(unsigned int handle, ui::EventData& event) {
    GfMenuScriptManager* manager = get();
    for (Script* it = manager->m_scripts.begin(); it != manager->m_scripts.end(); ++it) {
        if (it->m_handle == handle) {
            event = it->m_event;
            return true;
        }
    }
    return false;
}

int GfMenuScriptManager::getCtrlId(unsigned int handle) {
    GfMenuScriptManager* manager = get();
    for (Script* it = manager->m_scripts.begin(); it != manager->m_scripts.end(); ++it) {
        if (it->m_handle == handle) {
            return it->m_ctrlId;
        }
    }
    return -1;
}

void GfMenuScriptManager::setCtrlId(unsigned int handle, int ctrlId) {
    GfMenuScriptManager* manager = get();
    for (Script* it = manager->m_scripts.begin(); it != manager->m_scripts.end(); ++it) {
        if (it->m_handle == handle) {
            it->m_ctrlId = ctrlId;
        }
    }
}

void GfMenuScriptManager::ScriptListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    GfMenuScriptManager* manager = GfMenuScriptManager::get();
    for (Script* it = manager->m_scripts.begin(); it != manager->m_scripts.end(); ++it) {
        if (it->m_handle == handle) {
            if (!it->m_events.full()) {
                it->m_events.push_back(event);
            }
            return;
        }
    }
}

}  // namespace gf
